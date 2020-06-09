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
REGISTER int argument_count ASM("ebx");
IMPORT void *node_p;
IMPORT int result_count;
REGISTER NODE *myself ASM("r13");
IMPORT void invalid_results_error(void);
IMPORT void initialize_future(NODE *var, NODE *val);
IMPORT void invalid_arguments_error(void);
IMPORT NODE *create_closure(FUNC type, int par_count);
IMPORT NODE *create_future(void);
IMPORT void too_few_arguments_error(void);
IMPORT NODE *get_attribute(NODE *node, int idx);
IMPORT NODE *clone_object_and_attributes(NODE *node);
IMPORT void *update_start_p;
IMPORT void set_attribute_value(ATTRIBUTES *attributes, int idx, void *attr);
IMPORT NODE *create_continuation(void);
IMPORT NODE *undefined;
IMPORT NODE *create_cell(void);
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
IMPORT void assign_value(NODE **dest, NODE *val);
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
static NODE_GETTER get__annotate_statement;
static NODE_GETTER get_value_or_future__annotate_statement;
static NODE_GETTER get__append;
static NODE_GETTER get_value_or_future__append;
static int poly_idx__arguments_of;
static NODE_GETTER get__arguments_of;
static NODE_GETTER get__assignment;
static NODE_GETTER get_value_or_future__assignment;
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
static NODE_GETTER get__compiler__unique_item_index;
static NODE_SETTER set__compiler__unique_item_index;
static NODE_SETTER define__compiler__unique_item_index;
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
static NODE_GETTER get__compiler__used_unique_items;
static NODE_SETTER set__compiler__used_unique_items;
static NODE_SETTER define__compiler__used_unique_items;
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
static NODE_GETTER get__ignore;
static NODE_GETTER get_value_or_future__ignore;
static NODE_GETTER get__included_files;
static NODE_SETTER set__included_files;
static NODE_GETTER get__indent_marker;
static NODE_GETTER get_value_or_future__indent_marker;
static NODE_GETTER get__is_a_body;
static NODE_GETTER get_value_or_future__is_a_body;
static NODE_GETTER get__is_a_c_body;
static NODE_GETTER get_value_or_future__is_a_c_body;
static NODE_GETTER get__is_a_character_literal;
static NODE_GETTER get_value_or_future__is_a_character_literal;
static NODE_GETTER get__is_a_constant;
static NODE_GETTER get_value_or_future__is_a_constant;
static NODE_GETTER get__is_a_key_value_pair;
static NODE_GETTER get_value_or_future__is_a_key_value_pair;
static NODE_GETTER get__is_a_meta_instruction;
static NODE_GETTER get_value_or_future__is_a_meta_instruction;
static NODE_GETTER get__is_a_numeric_literal;
static NODE_GETTER get_value_or_future__is_a_numeric_literal;
static NODE_GETTER get__is_a_polymorphic_function_constant;
static NODE_GETTER get_value_or_future__is_a_polymorphic_function_constant;
static int poly_idx__is_a_reference;
static NODE_GETTER get__is_a_reference;
static NODE_GETTER get__is_a_remark;
static NODE_GETTER get_value_or_future__is_a_remark;
static NODE_GETTER get__is_a_setter;
static NODE_GETTER get_value_or_future__is_a_setter;
static NODE_GETTER get__is_a_static_single_definition;
static NODE_GETTER get_value_or_future__is_a_static_single_definition;
static NODE_GETTER get__is_an_assignment;
static NODE_GETTER get_value_or_future__is_an_assignment;
static NODE_GETTER get__is_c_code;
static NODE_GETTER get_value_or_future__is_c_code;
static NODE_GETTER get__is_defined;
static NODE_GETTER get_value_or_future__is_defined;
static NODE_GETTER get__is_empty;
static NODE_GETTER get_value_or_future__is_empty;
static NODE_GETTER get__is_undefined;
static NODE_GETTER get_value_or_future__is_undefined;
static NODE_GETTER get__key_of;
static NODE_GETTER get_value_or_future__key_of;
static NODE_GETTER get__length_of;
static NODE_GETTER get_value_or_future__length_of;
static NODE_GETTER get__linked_libraries;
static NODE_GETTER get_value_or_future__linked_libraries;
static NODE_GETTER get__list;
static NODE_GETTER get_value_or_future__list;
static NODE_GETTER get__load;
static NODE_GETTER get_value_or_future__load;
static NODE_GETTER get__mangled_name_of;
static NODE_GETTER get_value_or_future__mangled_name_of;
static NODE_GETTER get__module_name;
static NODE_GETTER get_value_or_future__module_name;
static NODE_GETTER get__name_of;
static NODE_GETTER get_value_or_future__name_of;
static NODE_GETTER get__named_constants;
static NODE_SETTER set__named_constants;
static NODE_SETTER define__named_constants;
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
static NODE_GETTER get__to_c;
static NODE_GETTER get_value_or_future__to_c;
static NODE_GETTER get__to_integer;
static NODE_GETTER get_value_or_future__to_integer;
static NODE_GETTER get__to_lower_case;
static NODE_GETTER get_value_or_future__to_lower_case;
static NODE_GETTER get__to_string;
static NODE_GETTER get_value_or_future__to_string;
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
  NODE *compiler__print_source;
  NODE *compiler__eprint_source;
  NODE *compiler__privileged_polymorphic_functions;
  NODE *compiler__generate_dispatcher_function;
  NODE *compiler__update_info;
  NODE *compiler__sim2c;
} var;
static const char *var_names[] = {
};
static NODE *func__compiler__print_source;
static void entry__compiler__print_source(void);
static FRAME_INFO frame__compiler__print_source = {1, {"source"}};
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
static NODE *func__compiler__eprint_source;
static void entry__compiler__eprint_source(void);
static FRAME_INFO frame__compiler__eprint_source = {1, {"source"}};
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
static NODE *func__compiler__generate_dispatcher_function;
static void entry__compiler__generate_dispatcher_function(void);
static FRAME_INFO frame__compiler__generate_dispatcher_function = {2, {"name", "id"}};
static NODE *string__7fb24a3fca4aa852;
static NODE *string__66ccbf91860d092a;
static void cont__compiler__generate_dispatcher_function_4(void);
static void cont__compiler__generate_dispatcher_function_5(void);
static NODE *string__949b16e1d9f7528;
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
static NODE *func__demangled;
static void entry__demangled(void);
static FRAME_INFO frame__demangled = {1, {"name"}};
static NODE *string__2d7981f4e5f02b9a;
static NODE *string__2d7981f4e6d82bff;
static void cont__demangled_4(void);
static void cont__demangled_5(void);
static NODE *func__compiler__update_info;
static void entry__compiler__update_info(void);
static FRAME_INFO frame__compiler__update_info = {4, {"name", "curr_info", "info", "return"}};
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
static NODE *func__compiler__sim2c;
static void entry__compiler__sim2c(void);
static FRAME_INFO frame__compiler__sim2c = {34, {"filenames", "is_main", "return__10", "mangle_filename", "fragments", "trees", "all_defined_names", "all_used_names", "all_actions", "top_level_names", "all_definitions", "all_statements", "max_temp_idx", "need", "generated_declarations", "generated_top_level_variable_names", "generated_top_level_variable_declarations", "generated_global_variable_declarations", "generated_continuation_table", "generated_delayed_continuation_table", "generated_functions", "generated_phase_1", "generated_phase_2", "generated_phase_3", "generated_phase_4", "generated_phase_5", "generated_phase_6", "generated_code", "generated_collections", "delayed_statements", "used_literals", "is_a_prototype", "def_count", "depth"}};
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
static void cont__compiler__sim2c_107(void);
static void cont__compiler__sim2c_108(void);
static void cont__compiler__sim2c_109(void);
static void cont__compiler__sim2c_110(void);
static void cont__compiler__sim2c_111(void);
static void cont__compiler__sim2c_112(void);
static NODE *func__compiler__sim2c_113;
static void entry__compiler__sim2c_113(void);
static FRAME_INFO frame__compiler__sim2c_113 = {2, {"fragment", "trees"}};
static void cont__compiler__sim2c_114(void);
static void cont__compiler__sim2c_115(void);
static void cont__compiler__sim2c_116(void);
static NODE *func__compiler__sim2c_117;
static void entry__compiler__sim2c_117(void);
static FRAME_INFO frame__compiler__sim2c_117 = {1, {"filenames"}};
static void cont__compiler__sim2c_118(void);
static NODE *string__94440f9215cbe09d;
static void cont__compiler__sim2c_120(void);
static NODE *func__compiler__sim2c_121;
static void entry__compiler__sim2c_121(void);
static FRAME_INFO frame__compiler__sim2c_121 = {1, {"trees"}};
static void cont__compiler__sim2c_122(void);
static void cont__compiler__sim2c_123(void);
static NODE *func__compiler__sim2c_124;
static void entry__compiler__sim2c_124(void);
static FRAME_INFO frame__compiler__sim2c_124 = {1, {"trees"}};
static NODE *string__72f826ea16a3e460;
static void cont__compiler__sim2c_126(void);
static void cont__compiler__sim2c_127(void);
static void cont__compiler__sim2c_128(void);
static NODE *func__compiler__sim2c_129;
static void entry__compiler__sim2c_129(void);
static FRAME_INFO frame__compiler__sim2c_129 = {2, {"tree", "return__2"}};
static void exit__compiler__sim2c_129(void);
static void cont__compiler__sim2c_130(void);
static void cont__compiler__sim2c_131(void);
static NODE *func__compiler__sim2c_132;
static void entry__compiler__sim2c_132(void);
static FRAME_INFO frame__compiler__sim2c_132 = {1, {"filenames"}};
static void cont__compiler__sim2c_133(void);
static NODE *string__66f024ec077397c2;
static void cont__compiler__sim2c_135(void);
static NODE *func__compiler__sim2c_136;
static void entry__compiler__sim2c_136(void);
static FRAME_INFO frame__compiler__sim2c_136 = {4, {"tree", "return__3", "all_defined_names", "all_used_names"}};
static void exit__compiler__sim2c_136(void);
static void cont__compiler__sim2c_137(void);
static void cont__compiler__sim2c_138(void);
static void cont__compiler__sim2c_139(void);
static void cont__compiler__sim2c_140(void);
static NODE *func__compiler__sim2c_141;
static void entry__compiler__sim2c_141(void);
static FRAME_INFO frame__compiler__sim2c_141 = {1, {"filenames"}};
static void cont__compiler__sim2c_142(void);
static NODE *string__1d581a51a85b6426;
static void cont__compiler__sim2c_144(void);
static NODE *func__compiler__sim2c_145;
static void entry__compiler__sim2c_145(void);
static FRAME_INFO frame__compiler__sim2c_145 = {0, {}};
static NODE *func__compiler__sim2c_146;
static void entry__compiler__sim2c_146(void);
static FRAME_INFO frame__compiler__sim2c_146 = {0, {}};
static void cont__compiler__sim2c_147(void);
static void cont__compiler__sim2c_148(void);
static NODE *func__compiler__sim2c_149;
static void entry__compiler__sim2c_149(void);
static FRAME_INFO frame__compiler__sim2c_149 = {1, {"is_main"}};
static void cont__compiler__sim2c_150(void);
static NODE *func__compiler__sim2c_151;
static void entry__compiler__sim2c_151(void);
static FRAME_INFO frame__compiler__sim2c_151 = {0, {}};
static NODE *string__c3e1e344d34946eb;
static void cont__compiler__sim2c_153(void);
static NODE *string__b567219b137172d;
static void cont__compiler__sim2c_155(void);
static void cont__compiler__sim2c_156(void);
static NODE *string__a23c0f9515cb809d;
static void cont__compiler__sim2c_158(void);
static void cont__compiler__sim2c_159(void);
static NODE *func__compiler__sim2c_160;
static void entry__compiler__sim2c_160(void);
static FRAME_INFO frame__compiler__sim2c_160 = {0, {}};
static NODE *string__fa724815d896ba8;
static void cont__compiler__sim2c_162(void);
static void cont__compiler__sim2c_163(void);
static void cont__compiler__sim2c_164(void);
static NODE *func__compiler__sim2c_165;
static void entry__compiler__sim2c_165(void);
static FRAME_INFO frame__compiler__sim2c_165 = {2, {"defined_names", "top_level_names"}};
static NODE *func__compiler__sim2c_166;
static void entry__compiler__sim2c_166(void);
static FRAME_INFO frame__compiler__sim2c_166 = {3, {"info", "top_level_names", "ident"}};
static void cont__compiler__sim2c_167(void);
static void cont__compiler__sim2c_168(void);
static NODE *func__compiler__sim2c_169;
static void entry__compiler__sim2c_169(void);
static FRAME_INFO frame__compiler__sim2c_169 = {1, {"info"}};
static void cont__compiler__sim2c_170(void);
static void cont__compiler__sim2c_171(void);
static void cont__compiler__sim2c_172(void);
static NODE *func__compiler__sim2c_173;
static void entry__compiler__sim2c_173(void);
static FRAME_INFO frame__compiler__sim2c_173 = {5, {"ident", "info", "top_level_names", "namespace", "name"}};
static void cont__compiler__sim2c_174(void);
static void cont__compiler__sim2c_175(void);
static void cont__compiler__sim2c_176(void);
static NODE *func__compiler__sim2c_177;
static void entry__compiler__sim2c_177(void);
static FRAME_INFO frame__compiler__sim2c_177 = {5, {"name", "namespace", "info", "top_level_names", "namespaces"}};
static void cont__compiler__sim2c_178(void);
static void cont__compiler__sim2c_179(void);
static NODE *func__compiler__sim2c_180;
static void entry__compiler__sim2c_180(void);
static FRAME_INFO frame__compiler__sim2c_180 = {1, {"namespaces"}};
static void cont__compiler__sim2c_181(void);
static void cont__compiler__sim2c_182(void);
static void cont__compiler__sim2c_183(void);
static void cont__compiler__sim2c_184(void);
static NODE *func__compiler__sim2c_185;
static void entry__compiler__sim2c_185(void);
static FRAME_INFO frame__compiler__sim2c_185 = {3, {"info", "namespace", "name"}};
static void cont__compiler__sim2c_186(void);
static NODE *string__b18861f6a8c886ba;
static NODE *string__95b7f6cc14260ab8;
static void cont__compiler__sim2c_189(void);
static void cont__compiler__sim2c_190(void);
static void cont__compiler__sim2c_191(void);
static NODE *func__compiler__sim2c_192;
static void entry__compiler__sim2c_192(void);
static FRAME_INFO frame__compiler__sim2c_192 = {5, {"name", "info", "namespace", "top_level_names", "info_1"}};
static void cont__compiler__sim2c_193(void);
static void cont__compiler__sim2c_194(void);
static NODE *func__compiler__sim2c_195;
static void entry__compiler__sim2c_195(void);
static FRAME_INFO frame__compiler__sim2c_195 = {3, {"info", "namespace", "name"}};
static void cont__compiler__sim2c_196(void);
static NODE *string__69658745890c070;
static NODE *string__c419bd2045fe53aa;
static NODE *string__578a5af303e9cc3;
static void cont__compiler__sim2c_200(void);
static void cont__compiler__sim2c_201(void);
static void cont__compiler__sim2c_202(void);
static void cont__compiler__sim2c_203(void);
static NODE *func__compiler__sim2c_204;
static void entry__compiler__sim2c_204(void);
static FRAME_INFO frame__compiler__sim2c_204 = {4, {"info", "namespace", "name", "info_1"}};
static void cont__compiler__sim2c_205(void);
static void cont__compiler__sim2c_206(void);
static void cont__compiler__sim2c_207(void);
static NODE *string__b5bb4d11daae5f7a;
static NODE *string__6de219341b32224c;
static void cont__compiler__sim2c_210(void);
static void cont__compiler__sim2c_211(void);
static void cont__compiler__sim2c_212(void);
static void cont__compiler__sim2c_213(void);
static void cont__compiler__sim2c_214(void);
static void cont__compiler__sim2c_215(void);
static NODE *func__compiler__sim2c_216;
static void entry__compiler__sim2c_216(void);
static FRAME_INFO frame__compiler__sim2c_216 = {4, {"name", "info", "top_level_names", "namespaces"}};
static void cont__compiler__sim2c_217(void);
static void cont__compiler__sim2c_218(void);
static NODE *func__compiler__sim2c_219;
static void entry__compiler__sim2c_219(void);
static FRAME_INFO frame__compiler__sim2c_219 = {2, {"info", "name"}};
static void cont__compiler__sim2c_220(void);
static void cont__compiler__sim2c_221(void);
static void cont__compiler__sim2c_222(void);
static void cont__compiler__sim2c_223(void);
static void cont__compiler__sim2c_224(void);
static NODE *func__compiler__sim2c_225;
static void entry__compiler__sim2c_225(void);
static FRAME_INFO frame__compiler__sim2c_225 = {3, {"namespaces", "info", "name"}};
static NODE *func__compiler__sim2c_226;
static void entry__compiler__sim2c_226(void);
static FRAME_INFO frame__compiler__sim2c_226 = {4, {"nspace", "dummy", "info", "name"}};
static void cont__compiler__sim2c_227(void);
static NODE *func__compiler__sim2c_228;
static void entry__compiler__sim2c_228(void);
static FRAME_INFO frame__compiler__sim2c_228 = {3, {"info", "name", "nspace"}};
static void cont__compiler__sim2c_229(void);
static void cont__compiler__sim2c_230(void);
static void cont__compiler__sim2c_231(void);
static void cont__compiler__sim2c_232(void);
static void cont__compiler__sim2c_233(void);
static void cont__compiler__sim2c_234(void);
static NODE *func__compiler__sim2c_235;
static void entry__compiler__sim2c_235(void);
static FRAME_INFO frame__compiler__sim2c_235 = {3, {"all_used_names", "top_level_names", "top_level_used_names"}};
static NODE *func__compiler__sim2c_236;
static void entry__compiler__sim2c_236(void);
static FRAME_INFO frame__compiler__sim2c_236 = {2, {"used_names", "top_level_used_names"}};
static NODE *func__compiler__sim2c_237;
static void entry__compiler__sim2c_237(void);
static FRAME_INFO frame__compiler__sim2c_237 = {3, {"mangled_name", "info", "top_level_used_names"}};
static void cont__compiler__sim2c_238(void);
static void cont__compiler__sim2c_239(void);
static void cont__compiler__sim2c_240(void);
static NODE *func__compiler__sim2c_241;
static void entry__compiler__sim2c_241(void);
static FRAME_INFO frame__compiler__sim2c_241 = {1, {"filenames"}};
static void cont__compiler__sim2c_242(void);
static NODE *string__5ab424ea8372e502;
static void cont__compiler__sim2c_244(void);
static NODE *func__compiler__sim2c_245;
static void entry__compiler__sim2c_245(void);
static FRAME_INFO frame__compiler__sim2c_245 = {1, {"trees"}};
static NODE *func__compiler__sim2c_246;
static void entry__compiler__sim2c_246(void);
static FRAME_INFO frame__compiler__sim2c_246 = {1, {"tree"}};
static void cont__compiler__sim2c_247(void);
static void cont__compiler__sim2c_248(void);
static void cont__compiler__sim2c_249(void);
static void cont__compiler__sim2c_250(void);
static NODE *func__compiler__sim2c_251;
static void entry__compiler__sim2c_251(void);
static FRAME_INFO frame__compiler__sim2c_251 = {1, {"tree"}};
static void cont__compiler__sim2c_252(void);
static NODE *func__compiler__sim2c_253;
static void entry__compiler__sim2c_253(void);
static FRAME_INFO frame__compiler__sim2c_253 = {4, {"tree", "arguments", "destination", "source"}};
static void cont__compiler__sim2c_254(void);
static void cont__compiler__sim2c_255(void);
static void cont__compiler__sim2c_256(void);
static void cont__compiler__sim2c_257(void);
static NODE *func__compiler__sim2c_258;
static void entry__compiler__sim2c_258(void);
static FRAME_INFO frame__compiler__sim2c_258 = {2, {"destination", "source"}};
static void cont__compiler__sim2c_259(void);
static void cont__compiler__sim2c_260(void);
static void cont__compiler__sim2c_261(void);
static NODE *func__compiler__sim2c_262;
static void entry__compiler__sim2c_262(void);
static FRAME_INFO frame__compiler__sim2c_262 = {1, {"source"}};
static void cont__compiler__sim2c_263(void);
static void cont__compiler__sim2c_264(void);
static NODE *func__compiler__sim2c_265;
static void entry__compiler__sim2c_265(void);
static FRAME_INFO frame__compiler__sim2c_265 = {1, {"source"}};
static void cont__compiler__sim2c_266(void);
static void cont__compiler__sim2c_267(void);
static NODE *func__compiler__sim2c_268;
static void entry__compiler__sim2c_268(void);
static FRAME_INFO frame__compiler__sim2c_268 = {1, {"source"}};
static void cont__compiler__sim2c_269(void);
static void cont__compiler__sim2c_270(void);
static void cont__compiler__sim2c_271(void);
static void cont__compiler__sim2c_272(void);
static void cont__compiler__sim2c_273(void);
static NODE *func__compiler__sim2c_274;
static void entry__compiler__sim2c_274(void);
static FRAME_INFO frame__compiler__sim2c_274 = {2, {"destination", "source"}};
static void cont__compiler__sim2c_275(void);
static void cont__compiler__sim2c_276(void);
static void cont__compiler__sim2c_277(void);
static void cont__compiler__sim2c_278(void);
static NODE *func__compiler__sim2c_279;
static void entry__compiler__sim2c_279(void);
static FRAME_INFO frame__compiler__sim2c_279 = {1, {"tree"}};
static void cont__compiler__sim2c_280(void);
static NODE *func__compiler__sim2c_281;
static void entry__compiler__sim2c_281(void);
static FRAME_INFO frame__compiler__sim2c_281 = {2, {"tree", "destination"}};
static void cont__compiler__sim2c_282(void);
static void cont__compiler__sim2c_283(void);
static void cont__compiler__sim2c_284(void);
static NODE *func__compiler__sim2c_285;
static void entry__compiler__sim2c_285(void);
static FRAME_INFO frame__compiler__sim2c_285 = {1, {"destination"}};
static void cont__compiler__sim2c_286(void);
static void cont__compiler__sim2c_287(void);
static void cont__compiler__sim2c_288(void);
static void cont__compiler__sim2c_289(void);
static NODE *func__compiler__sim2c_290;
static void entry__compiler__sim2c_290(void);
static FRAME_INFO frame__compiler__sim2c_290 = {1, {"destination"}};
static void cont__compiler__sim2c_291(void);
static void cont__compiler__sim2c_292(void);
static void cont__compiler__sim2c_293(void);
static void cont__compiler__sim2c_294(void);
static NODE *func__compiler__sim2c_295;
static void entry__compiler__sim2c_295(void);
static FRAME_INFO frame__compiler__sim2c_295 = {6, {"tree", "top_level_names", "all_statements", "all_definitions", "max_temp_idx", "all_actions"}};
static void cont__compiler__sim2c_296(void);
static NODE *func__compiler__sim2c_297;
static void entry__compiler__sim2c_297(void);
static FRAME_INFO frame__compiler__sim2c_297 = {1, {"tree"}};
static void cont__compiler__sim2c_298(void);
static void cont__compiler__sim2c_299(void);
static NODE *func__compiler__sim2c_300;
static void entry__compiler__sim2c_300(void);
static FRAME_INFO frame__compiler__sim2c_300 = {8, {"return__4", "top_level_names", "tree", "all_statements", "all_definitions", "max_temp_idx", "all_actions", "tmp_idx"}};
static void cont__compiler__sim2c_301(void);
static void cont__compiler__sim2c_302(void);
static void cont__compiler__sim2c_303(void);
static NODE *func__compiler__sim2c_304;
static void entry__compiler__sim2c_304(void);
static FRAME_INFO frame__compiler__sim2c_304 = {2, {"max_temp_idx", "tmp_idx"}};
static void cont__compiler__sim2c_305(void);
static void cont__compiler__sim2c_306(void);
static void cont__compiler__sim2c_307(void);
static void cont__compiler__sim2c_308(void);
static NODE *func__compiler__sim2c_309;
static void entry__compiler__sim2c_309(void);
static FRAME_INFO frame__compiler__sim2c_309 = {1, {"stmt_actions"}};
static NODE *func__compiler__sim2c_310;
static void entry__compiler__sim2c_310(void);
static FRAME_INFO frame__compiler__sim2c_310 = {1, {"action"}};
static void cont__compiler__sim2c_311(void);
static NODE *func__compiler__sim2c_312;
static void entry__compiler__sim2c_312(void);
static FRAME_INFO frame__compiler__sim2c_312 = {1, {"filenames"}};
static void cont__compiler__sim2c_313(void);
static NODE *string__72ed7b1f2279c943;
static void cont__compiler__sim2c_315(void);
static NODE *func__compiler__sim2c_316;
static void entry__compiler__sim2c_316(void);
static FRAME_INFO frame__compiler__sim2c_316 = {2, {"all_definitions", "all_statements"}};
static NODE *func__compiler__sim2c_317;
static void entry__compiler__sim2c_317(void);
static FRAME_INFO frame__compiler__sim2c_317 = {1, {"defs"}};
static NODE *func__compiler__sim2c_318;
static void entry__compiler__sim2c_318(void);
static FRAME_INFO frame__compiler__sim2c_318 = {1, {"def"}};
static void cont__compiler__sim2c_319(void);
static NODE *func__compiler__sim2c_320;
static void entry__compiler__sim2c_320(void);
static FRAME_INFO frame__compiler__sim2c_320 = {1, {"def"}};
static void cont__compiler__sim2c_321(void);
static void cont__compiler__sim2c_322(void);
static void cont__compiler__sim2c_323(void);
static NODE *func__compiler__sim2c_324;
static void entry__compiler__sim2c_324(void);
static FRAME_INFO frame__compiler__sim2c_324 = {1, {"def"}};
static NODE *string__7c84ae5484fdf7e0;
static void cont__compiler__sim2c_326(void);
static NODE *func__compiler__sim2c_327;
static void entry__compiler__sim2c_327(void);
static FRAME_INFO frame__compiler__sim2c_327 = {1, {"stmts"}};
static void cont__compiler__sim2c_328(void);
static void cont__compiler__sim2c_329(void);
static NODE *func__compiler__sim2c_330;
static void entry__compiler__sim2c_330(void);
static FRAME_INFO frame__compiler__sim2c_330 = {2, {"used_names", "need"}};
static NODE *func__compiler__sim2c_331;
static void entry__compiler__sim2c_331(void);
static FRAME_INFO frame__compiler__sim2c_331 = {3, {"mangled_name", "info", "need"}};
static void cont__compiler__sim2c_332(void);
static NODE *func__compiler__sim2c_333;
static void entry__compiler__sim2c_333(void);
static FRAME_INFO frame__compiler__sim2c_333 = {1, {"filenames"}};
static void cont__compiler__sim2c_334(void);
static NODE *string__7690af9104a5e1e7;
static void cont__compiler__sim2c_336(void);
static void cont__compiler__sim2c_337(void);
static NODE *func__compiler__sim2c_338;
static void entry__compiler__sim2c_338(void);
static FRAME_INFO frame__compiler__sim2c_338 = {3, {"args", "generated_declarations", "txt"}};
static void cont__compiler__sim2c_339(void);
static NODE *func__compiler__sim2c_340;
static void entry__compiler__sim2c_340(void);
static FRAME_INFO frame__compiler__sim2c_340 = {2, {"generated_declarations", "txt"}};
static void cont__compiler__sim2c_341(void);
static void cont__compiler__sim2c_342(void);
static NODE *func__compiler__sim2c_343;
static void entry__compiler__sim2c_343(void);
static FRAME_INFO frame__compiler__sim2c_343 = {3, {"args", "generated_top_level_variable_names", "txt"}};
static void cont__compiler__sim2c_344(void);
static NODE *func__compiler__sim2c_345;
static void entry__compiler__sim2c_345(void);
static FRAME_INFO frame__compiler__sim2c_345 = {2, {"generated_top_level_variable_names", "txt"}};
static void cont__compiler__sim2c_346(void);
static void cont__compiler__sim2c_347(void);
static NODE *func__compiler__sim2c_348;
static void entry__compiler__sim2c_348(void);
static FRAME_INFO frame__compiler__sim2c_348 = {3, {"args", "generated_top_level_variable_declarations", "txt"}};
static void cont__compiler__sim2c_349(void);
static NODE *func__compiler__sim2c_350;
static void entry__compiler__sim2c_350(void);
static FRAME_INFO frame__compiler__sim2c_350 = {2, {"generated_top_level_variable_declarations", "txt"}};
static void cont__compiler__sim2c_351(void);
static void cont__compiler__sim2c_352(void);
static NODE *func__compiler__sim2c_353;
static void entry__compiler__sim2c_353(void);
static FRAME_INFO frame__compiler__sim2c_353 = {3, {"args", "generated_global_variable_declarations", "txt"}};
static void cont__compiler__sim2c_354(void);
static NODE *func__compiler__sim2c_355;
static void entry__compiler__sim2c_355(void);
static FRAME_INFO frame__compiler__sim2c_355 = {2, {"generated_global_variable_declarations", "txt"}};
static void cont__compiler__sim2c_356(void);
static void cont__compiler__sim2c_357(void);
static NODE *func__compiler__sim2c_358;
static void entry__compiler__sim2c_358(void);
static FRAME_INFO frame__compiler__sim2c_358 = {3, {"args", "generated_continuation_table", "txt"}};
static void cont__compiler__sim2c_359(void);
static NODE *func__compiler__sim2c_360;
static void entry__compiler__sim2c_360(void);
static FRAME_INFO frame__compiler__sim2c_360 = {2, {"generated_continuation_table", "txt"}};
static void cont__compiler__sim2c_361(void);
static void cont__compiler__sim2c_362(void);
static NODE *func__compiler__sim2c_363;
static void entry__compiler__sim2c_363(void);
static FRAME_INFO frame__compiler__sim2c_363 = {3, {"args", "generated_delayed_continuation_table", "txt"}};
static void cont__compiler__sim2c_364(void);
static NODE *func__compiler__sim2c_365;
static void entry__compiler__sim2c_365(void);
static FRAME_INFO frame__compiler__sim2c_365 = {2, {"generated_delayed_continuation_table", "txt"}};
static void cont__compiler__sim2c_366(void);
static void cont__compiler__sim2c_367(void);
static NODE *func__compiler__sim2c_368;
static void entry__compiler__sim2c_368(void);
static FRAME_INFO frame__compiler__sim2c_368 = {3, {"args", "generated_functions", "txt"}};
static void cont__compiler__sim2c_369(void);
static NODE *func__compiler__sim2c_370;
static void entry__compiler__sim2c_370(void);
static FRAME_INFO frame__compiler__sim2c_370 = {2, {"generated_functions", "txt"}};
static void cont__compiler__sim2c_371(void);
static void cont__compiler__sim2c_372(void);
static NODE *func__compiler__sim2c_373;
static void entry__compiler__sim2c_373(void);
static FRAME_INFO frame__compiler__sim2c_373 = {3, {"args", "generated_phase_1", "txt"}};
static void cont__compiler__sim2c_374(void);
static NODE *func__compiler__sim2c_375;
static void entry__compiler__sim2c_375(void);
static FRAME_INFO frame__compiler__sim2c_375 = {2, {"generated_phase_1", "txt"}};
static void cont__compiler__sim2c_376(void);
static void cont__compiler__sim2c_377(void);
static NODE *func__compiler__sim2c_378;
static void entry__compiler__sim2c_378(void);
static FRAME_INFO frame__compiler__sim2c_378 = {3, {"args", "generated_phase_2", "txt"}};
static void cont__compiler__sim2c_379(void);
static NODE *func__compiler__sim2c_380;
static void entry__compiler__sim2c_380(void);
static FRAME_INFO frame__compiler__sim2c_380 = {2, {"generated_phase_2", "txt"}};
static void cont__compiler__sim2c_381(void);
static void cont__compiler__sim2c_382(void);
static NODE *func__compiler__sim2c_383;
static void entry__compiler__sim2c_383(void);
static FRAME_INFO frame__compiler__sim2c_383 = {3, {"args", "generated_phase_3", "txt"}};
static void cont__compiler__sim2c_384(void);
static NODE *func__compiler__sim2c_385;
static void entry__compiler__sim2c_385(void);
static FRAME_INFO frame__compiler__sim2c_385 = {2, {"generated_phase_3", "txt"}};
static void cont__compiler__sim2c_386(void);
static void cont__compiler__sim2c_387(void);
static NODE *func__compiler__sim2c_388;
static void entry__compiler__sim2c_388(void);
static FRAME_INFO frame__compiler__sim2c_388 = {3, {"args", "generated_phase_4", "txt"}};
static void cont__compiler__sim2c_389(void);
static NODE *func__compiler__sim2c_390;
static void entry__compiler__sim2c_390(void);
static FRAME_INFO frame__compiler__sim2c_390 = {2, {"generated_phase_4", "txt"}};
static void cont__compiler__sim2c_391(void);
static void cont__compiler__sim2c_392(void);
static NODE *func__compiler__sim2c_393;
static void entry__compiler__sim2c_393(void);
static FRAME_INFO frame__compiler__sim2c_393 = {3, {"args", "generated_phase_5", "txt"}};
static void cont__compiler__sim2c_394(void);
static NODE *func__compiler__sim2c_395;
static void entry__compiler__sim2c_395(void);
static FRAME_INFO frame__compiler__sim2c_395 = {2, {"generated_phase_5", "txt"}};
static void cont__compiler__sim2c_396(void);
static void cont__compiler__sim2c_397(void);
static NODE *func__compiler__sim2c_398;
static void entry__compiler__sim2c_398(void);
static FRAME_INFO frame__compiler__sim2c_398 = {3, {"args", "generated_phase_6", "txt"}};
static void cont__compiler__sim2c_399(void);
static NODE *func__compiler__sim2c_400;
static void entry__compiler__sim2c_400(void);
static FRAME_INFO frame__compiler__sim2c_400 = {2, {"generated_phase_6", "txt"}};
static void cont__compiler__sim2c_401(void);
static void cont__compiler__sim2c_402(void);
static NODE *func__compiler__sim2c_403;
static void entry__compiler__sim2c_403(void);
static FRAME_INFO frame__compiler__sim2c_403 = {3, {"name", "literal", "used_literals"}};
static NODE *func__compiler__sim2c_404;
static void entry__compiler__sim2c_404(void);
static FRAME_INFO frame__compiler__sim2c_404 = {3, {"used_literals", "name", "literal"}};
static void cont__compiler__sim2c_405(void);
static void cont__compiler__sim2c_406(void);
static NODE *func__compiler__sim2c_407;
static void entry__compiler__sim2c_407(void);
static FRAME_INFO frame__compiler__sim2c_407 = {3, {"args", "generated_collections", "txt"}};
static void cont__compiler__sim2c_408(void);
static NODE *func__compiler__sim2c_409;
static void entry__compiler__sim2c_409(void);
static FRAME_INFO frame__compiler__sim2c_409 = {2, {"generated_collections", "txt"}};
static void cont__compiler__sim2c_410(void);
static void cont__compiler__sim2c_411(void);
static NODE *func__compiler__sim2c_412;
static void entry__compiler__sim2c_412(void);
static FRAME_INFO frame__compiler__sim2c_412 = {3, {"args", "delayed_statements", "txt"}};
static void cont__compiler__sim2c_413(void);
static NODE *func__compiler__sim2c_414;
static void entry__compiler__sim2c_414(void);
static FRAME_INFO frame__compiler__sim2c_414 = {2, {"delayed_statements", "txt"}};
static void cont__compiler__sim2c_415(void);
static void cont__compiler__sim2c_416(void);
static NODE *func__compiler__sim2c_417;
static void entry__compiler__sim2c_417(void);
static FRAME_INFO frame__compiler__sim2c_417 = {2, {"ident", "need"}};
static NODE *string__405aee03eb306008;
static void cont__compiler__sim2c_419(void);
static NODE *func__compiler__sim2c_420;
static void entry__compiler__sim2c_420(void);
static FRAME_INFO frame__compiler__sim2c_420 = {3, {"ident", "need", "name"}};
static void cont__compiler__sim2c_421(void);
static void cont__compiler__sim2c_422(void);
static NODE *string__c44673b4643f1172;
static void cont__compiler__sim2c_424(void);
static NODE *func__compiler__sim2c_425;
static void entry__compiler__sim2c_425(void);
static FRAME_INFO frame__compiler__sim2c_425 = {2, {"defs", "is_a_prototype"}};
static NODE *func__compiler__sim2c_426;
static void entry__compiler__sim2c_426(void);
static FRAME_INFO frame__compiler__sim2c_426 = {2, {"definition", "is_a_prototype"}};
static void cont__compiler__sim2c_427(void);
static NODE *func__compiler__sim2c_428;
static void entry__compiler__sim2c_428(void);
static FRAME_INFO frame__compiler__sim2c_428 = {2, {"definition", "is_a_prototype"}};
static void cont__compiler__sim2c_429(void);
static void cont__compiler__sim2c_430(void);
static void cont__compiler__sim2c_431(void);
static NODE *func__compiler__sim2c_432;
static void entry__compiler__sim2c_432(void);
static FRAME_INFO frame__compiler__sim2c_432 = {2, {"is_a_prototype", "definition"}};
static void cont__compiler__sim2c_433(void);
static void cont__compiler__sim2c_434(void);
static void cont__compiler__sim2c_435(void);
static void cont__compiler__sim2c_436(void);
static NODE *func__compiler__sim2c_437;
static void entry__compiler__sim2c_437(void);
static FRAME_INFO frame__compiler__sim2c_437 = {6, {"defs", "return__6", "is_a_prototype", "generated_code", "all_actions", "code"}};
static NODE *func__compiler__sim2c_438;
static void entry__compiler__sim2c_438(void);
static FRAME_INFO frame__compiler__sim2c_438 = {2, {"defs", "is_a_prototype"}};
static NODE *func__compiler__sim2c_439;
static void entry__compiler__sim2c_439(void);
static FRAME_INFO frame__compiler__sim2c_439 = {3, {"definition", "is_a_prototype", "source"}};
static void cont__compiler__sim2c_440(void);
static NODE *func__compiler__sim2c_441;
static void entry__compiler__sim2c_441(void);
static FRAME_INFO frame__compiler__sim2c_441 = {2, {"source", "definition"}};
static void cont__compiler__sim2c_442(void);
static void cont__compiler__sim2c_443(void);
static void cont__compiler__sim2c_444(void);
static void cont__compiler__sim2c_445(void);
static NODE *func__compiler__sim2c_446;
static void entry__compiler__sim2c_446(void);
static FRAME_INFO frame__compiler__sim2c_446 = {1, {"definition"}};
static NODE *func__compiler__sim2c_447;
static void entry__compiler__sim2c_447(void);
static FRAME_INFO frame__compiler__sim2c_447 = {6, {"return__5", "definition", "source", "is_a_prototype", "name", "attribute"}};
static void cont__compiler__sim2c_448(void);
static void cont__compiler__sim2c_449(void);
static void cont__compiler__sim2c_450(void);
static void cont__compiler__sim2c_451(void);
static NODE *func__compiler__sim2c_452;
static void entry__compiler__sim2c_452(void);
static FRAME_INFO frame__compiler__sim2c_452 = {2, {"name", "attribute"}};
static void cont__compiler__sim2c_453(void);
static void cont__compiler__sim2c_454(void);
static void cont__compiler__sim2c_455(void);
static void cont__compiler__sim2c_456(void);
static void cont__compiler__sim2c_457(void);
static void cont__compiler__sim2c_458(void);
static NODE *func__compiler__sim2c_459;
static void entry__compiler__sim2c_459(void);
static FRAME_INFO frame__compiler__sim2c_459 = {1, {"source"}};
static void cont__compiler__sim2c_460(void);
static void cont__compiler__sim2c_461(void);
static NODE *func__compiler__sim2c_462;
static void entry__compiler__sim2c_462(void);
static FRAME_INFO frame__compiler__sim2c_462 = {2, {"definition", "source"}};
static void cont__compiler__sim2c_463(void);
static NODE *func__compiler__sim2c_464;
static void entry__compiler__sim2c_464(void);
static FRAME_INFO frame__compiler__sim2c_464 = {3, {"definition", "source", "is_a_prototype"}};
static void cont__compiler__sim2c_465(void);
static NODE *func__compiler__sim2c_466;
static void entry__compiler__sim2c_466(void);
static FRAME_INFO frame__compiler__sim2c_466 = {2, {"definition", "source"}};
static NODE *func__compiler__sim2c_467;
static void entry__compiler__sim2c_467(void);
static FRAME_INFO frame__compiler__sim2c_467 = {2, {"definition", "source"}};
static void cont__compiler__sim2c_468(void);
static void cont__compiler__sim2c_469(void);
static NODE *func__compiler__sim2c_470;
static void entry__compiler__sim2c_470(void);
static FRAME_INFO frame__compiler__sim2c_470 = {2, {"definition", "source"}};
static NODE *func__compiler__sim2c_471;
static void entry__compiler__sim2c_471(void);
static FRAME_INFO frame__compiler__sim2c_471 = {2, {"definition", "source"}};
static NODE *func__compiler__sim2c_472;
static void entry__compiler__sim2c_472(void);
static FRAME_INFO frame__compiler__sim2c_472 = {4, {"definition", "source", "is_a_prototype", "identifier"}};
static void cont__compiler__sim2c_473(void);
static void cont__compiler__sim2c_474(void);
static void cont__compiler__sim2c_475(void);
static NODE *func__compiler__sim2c_476;
static void entry__compiler__sim2c_476(void);
static FRAME_INFO frame__compiler__sim2c_476 = {1, {"identifier"}};
static void cont__compiler__sim2c_477(void);
static void cont__compiler__sim2c_478(void);
static void cont__compiler__sim2c_479(void);
static void cont__compiler__sim2c_480(void);
static NODE *func__compiler__sim2c_481;
static void entry__compiler__sim2c_481(void);
static FRAME_INFO frame__compiler__sim2c_481 = {3, {"definition", "source", "is_a_prototype"}};
static void cont__compiler__sim2c_482(void);
static void cont__compiler__sim2c_483(void);
static void cont__compiler__sim2c_484(void);
static NODE *func__compiler__sim2c_485;
static void entry__compiler__sim2c_485(void);
static FRAME_INFO frame__compiler__sim2c_485 = {1, {"definition"}};
static void cont__compiler__sim2c_486(void);
static void cont__compiler__sim2c_487(void);
static void cont__compiler__sim2c_488(void);
static void cont__compiler__sim2c_489(void);
static NODE *func__compiler__sim2c_490;
static void entry__compiler__sim2c_490(void);
static FRAME_INFO frame__compiler__sim2c_490 = {1, {"source"}};
static void cont__compiler__sim2c_491(void);
static NODE *func__compiler__sim2c_492;
static void entry__compiler__sim2c_492(void);
static FRAME_INFO frame__compiler__sim2c_492 = {1, {"source"}};
static void cont__compiler__sim2c_493(void);
static void cont__compiler__sim2c_494(void);
static void cont__compiler__sim2c_495(void);
static void cont__compiler__sim2c_496(void);
static void cont__compiler__sim2c_497(void);
static NODE *func__compiler__sim2c_498;
static void entry__compiler__sim2c_498(void);
static FRAME_INFO frame__compiler__sim2c_498 = {0, {}};
static void cont__compiler__sim2c_499(void);
static NODE *func__compiler__sim2c_500;
static void entry__compiler__sim2c_500(void);
static FRAME_INFO frame__compiler__sim2c_500 = {2, {"generated_code", "code"}};
static void cont__compiler__sim2c_501(void);
static void cont__compiler__sim2c_502(void);
static void cont__compiler__sim2c_503(void);
static void cont__compiler__sim2c_504(void);
static NODE *string__c050814d5faecc7a;
static void cont__compiler__sim2c_506(void);
static NODE *func__compiler__sim2c_507;
static void entry__compiler__sim2c_507(void);
static FRAME_INFO frame__compiler__sim2c_507 = {7, {"return__7", "is_main", "max_temp_idx", "mangle_filename", "generated_code", "all_actions", "code"}};
static NODE *func__compiler__sim2c_508;
static void entry__compiler__sim2c_508(void);
static FRAME_INFO frame__compiler__sim2c_508 = {3, {"is_main", "max_temp_idx", "mangle_filename"}};
static NODE *func__compiler__sim2c_509;
static void entry__compiler__sim2c_509(void);
static FRAME_INFO frame__compiler__sim2c_509 = {1, {"max_temp_idx"}};
static NODE *string__295c7d0427bb24d8;
static void cont__compiler__sim2c_511(void);
static void cont__compiler__sim2c_512(void);
static NODE *func__compiler__sim2c_513;
static void entry__compiler__sim2c_513(void);
static FRAME_INFO frame__compiler__sim2c_513 = {1, {"max_temp_idx"}};
static NODE *string__41028e5a9545c479;
static NODE *string__2d7981f4e6402bfe;
static void cont__compiler__sim2c_516(void);
static NODE *func__compiler__sim2c_517;
static void entry__compiler__sim2c_517(void);
static FRAME_INFO frame__compiler__sim2c_517 = {1, {"max_temp_idx"}};
static NODE *string__4594ae5b852cb87f;
static NODE *string__3794a6c106b6c980;
static void cont__compiler__sim2c_520(void);
static void cont__compiler__sim2c_521(void);
static NODE *string__8eebb379fdb22853;
static NODE *string__bbab7a959fd798d;
static void cont__compiler__sim2c_524(void);
static void cont__compiler__sim2c_525(void);
static NODE *func__compiler__sim2c_526;
static void entry__compiler__sim2c_526(void);
static FRAME_INFO frame__compiler__sim2c_526 = {4, {"name", "info", "mangle_filename", "continuation"}};
static void cont__compiler__sim2c_527(void);
static void cont__compiler__sim2c_528(void);
static void cont__compiler__sim2c_529(void);
static NODE *string__ca75d5c2b6ab3b0c;
static NODE *string__3fab381eeea84c47;
static NODE *string__b40af3cb5d887d33;
static void cont__compiler__sim2c_533(void);
static void cont__compiler__sim2c_534(void);
static void cont__compiler__sim2c_535(void);
static NODE *string__6a214ac420f089ff;
static void cont__compiler__sim2c_537(void);
static void cont__compiler__sim2c_538(void);
static NODE *func__compiler__sim2c_539;
static void entry__compiler__sim2c_539(void);
static FRAME_INFO frame__compiler__sim2c_539 = {2, {"generated_code", "code"}};
static void cont__compiler__sim2c_540(void);
static void cont__compiler__sim2c_541(void);
static void cont__compiler__sim2c_542(void);
static void cont__compiler__sim2c_543(void);
static void cont__compiler__sim2c_544(void);
static NODE *func__compiler__sim2c_545;
static void entry__compiler__sim2c_545(void);
static FRAME_INFO frame__compiler__sim2c_545 = {7, {"stmt_idx", "stmts", "return__8", "def_count", "generated_code", "all_actions", "code"}};
static void cont__compiler__sim2c_546(void);
static void cont__compiler__sim2c_547(void);
static NODE *func__compiler__sim2c_548;
static void entry__compiler__sim2c_548(void);
static FRAME_INFO frame__compiler__sim2c_548 = {1, {"stmts"}};
static NODE *func__compiler__sim2c_549;
static void entry__compiler__sim2c_549(void);
static FRAME_INFO frame__compiler__sim2c_549 = {1, {"stmt"}};
static void cont__compiler__sim2c_550(void);
static void cont__compiler__sim2c_551(void);
static void cont__compiler__sim2c_552(void);
static NODE *func__compiler__sim2c_553;
static void entry__compiler__sim2c_553(void);
static FRAME_INFO frame__compiler__sim2c_553 = {0, {}};
static void cont__compiler__sim2c_554(void);
static NODE *func__compiler__sim2c_555;
static void entry__compiler__sim2c_555(void);
static FRAME_INFO frame__compiler__sim2c_555 = {2, {"generated_code", "code"}};
static void cont__compiler__sim2c_556(void);
static void cont__compiler__sim2c_557(void);
static void cont__compiler__sim2c_558(void);
static void cont__compiler__sim2c_559(void);
static NODE *func__compiler__sim2c_560;
static void entry__compiler__sim2c_560(void);
static FRAME_INFO frame__compiler__sim2c_560 = {5, {"return__9", "is_main", "generated_code", "all_actions", "code"}};
static NODE *func__compiler__sim2c_561;
static void entry__compiler__sim2c_561(void);
static FRAME_INFO frame__compiler__sim2c_561 = {1, {"is_main"}};
static NODE *func__compiler__sim2c_562;
static void entry__compiler__sim2c_562(void);
static FRAME_INFO frame__compiler__sim2c_562 = {0, {}};
static NODE *string__5c9d8231ad282235;
static NODE *func__compiler__sim2c_564;
static void entry__compiler__sim2c_564(void);
static FRAME_INFO frame__compiler__sim2c_564 = {0, {}};
static NODE *string__a61426acc3f10dab;
static void cont__compiler__sim2c_566(void);
static void cont__compiler__sim2c_567(void);
static NODE *func__compiler__sim2c_568;
static void entry__compiler__sim2c_568(void);
static FRAME_INFO frame__compiler__sim2c_568 = {2, {"generated_code", "code"}};
static void cont__compiler__sim2c_569(void);
static void cont__compiler__sim2c_570(void);
static void cont__compiler__sim2c_571(void);
static void cont__compiler__sim2c_572(void);
static NODE *func__compiler__sim2c_573;
static void entry__compiler__sim2c_573(void);
static FRAME_INFO frame__compiler__sim2c_573 = {1, {"stmt_actions"}};
static NODE *func__compiler__sim2c_574;
static void entry__compiler__sim2c_574(void);
static FRAME_INFO frame__compiler__sim2c_574 = {1, {"action"}};
static void cont__compiler__sim2c_575(void);
static NODE *func__compiler__sim2c_576;
static void entry__compiler__sim2c_576(void);
static FRAME_INFO frame__compiler__sim2c_576 = {2, {"name", "info"}};
static NODE *string__58cb04c59ab3549a;
static void cont__compiler__sim2c_578(void);
static void cont__compiler__sim2c_579(void);
static NODE *func__compiler__sim2c_580;
static void entry__compiler__sim2c_580(void);
static FRAME_INFO frame__compiler__sim2c_580 = {1, {"name"}};
static NODE *string__7d8c250ccd5bbd65;
static void cont__compiler__sim2c_582(void);
static void cont__compiler__sim2c_583(void);
static NODE *func__compiler__sim2c_584;
static void entry__compiler__sim2c_584(void);
static FRAME_INFO frame__compiler__sim2c_584 = {1, {"filemask"}};
static NODE *string__6d8c238ccd0b3d65;
static void cont__compiler__sim2c_586(void);
static void cont__compiler__sim2c_587(void);
static void cont__compiler__sim2c_588(void);
static void cont__compiler__sim2c_589(void);
static NODE *string__3ae3b0d72c49c8db;
static void cont__compiler__sim2c_591(void);
static NODE *func__compiler__sim2c_592;
static void entry__compiler__sim2c_592(void);
static FRAME_INFO frame__compiler__sim2c_592 = {0, {}};
static NODE *string__72c4a8d406a50228;
static void cont__compiler__sim2c_594(void);
static NODE *string__7cc4ad5406a55228;
static void cont__compiler__sim2c_596(void);
static void cont__compiler__sim2c_597(void);
static NODE *func__compiler__sim2c_598;
static void entry__compiler__sim2c_598(void);
static FRAME_INFO frame__compiler__sim2c_598 = {1, {"name"}};
static NODE *string__3d6a095dad2a247d;
static NODE *string__578a5af303e9cdf;
static void cont__compiler__sim2c_601(void);
static void cont__compiler__sim2c_602(void);
static void cont__compiler__sim2c_603(void);
static void cont__compiler__sim2c_604(void);
static NODE *string__36e833feb0906b55;
static void cont__compiler__sim2c_606(void);
static void cont__compiler__sim2c_607(void);
static NODE *func__compiler__sim2c_608;
static void entry__compiler__sim2c_608(void);
static FRAME_INFO frame__compiler__sim2c_608 = {0, {}};
static NODE *string__a047b2b18829c385;
static void cont__compiler__sim2c_610(void);
static void cont__compiler__sim2c_611(void);
static NODE *func__compiler__sim2c_612;
static void entry__compiler__sim2c_612(void);
static FRAME_INFO frame__compiler__sim2c_612 = {0, {}};
static NODE *string__64c4ac5406a5d228;
static void cont__compiler__sim2c_614(void);
static void cont__compiler__sim2c_615(void);
static NODE *func__compiler__sim2c_616;
static void entry__compiler__sim2c_616(void);
static FRAME_INFO frame__compiler__sim2c_616 = {0, {}};
static NODE *string__b0f44c3748f83ed0;
static void cont__compiler__sim2c_618(void);
static NODE *string__96a80854500bbe37;
static void cont__compiler__sim2c_620(void);
static NODE *func__compiler__sim2c_621;
static void entry__compiler__sim2c_621(void);
static FRAME_INFO frame__compiler__sim2c_621 = {2, {"name", "info"}};
static void cont__compiler__sim2c_622(void);
static void cont__compiler__sim2c_623(void);
static NODE *func__compiler__sim2c_624;
static void entry__compiler__sim2c_624(void);
static FRAME_INFO frame__compiler__sim2c_624 = {1, {"name"}};
static NODE *string__dd59fa996655f7be;
static NODE *string__578a5af303e9cda;
static void cont__compiler__sim2c_627(void);
static void cont__compiler__sim2c_628(void);
static NODE *string__7bc4c42d1b67ee3a;
static void cont__compiler__sim2c_630(void);
static void cont__compiler__sim2c_631(void);
static void cont__compiler__sim2c_632(void);
static void cont__compiler__sim2c_633(void);
static NODE *func__compiler__sim2c_634;
static void entry__compiler__sim2c_634(void);
static FRAME_INFO frame__compiler__sim2c_634 = {1, {"name"}};
static NODE *string__f144f4e2b96df7e3;
static void cont__compiler__sim2c_636(void);
static void cont__compiler__sim2c_637(void);
static void cont__compiler__sim2c_638(void);
static void cont__compiler__sim2c_639(void);
static NODE *func__compiler__sim2c_640;
static void entry__compiler__sim2c_640(void);
static FRAME_INFO frame__compiler__sim2c_640 = {1, {"name"}};
static NODE *string__7bc4c42d1b4eae3a;
static void cont__compiler__sim2c_642(void);
static void cont__compiler__sim2c_643(void);
static void cont__compiler__sim2c_644(void);
static void cont__compiler__sim2c_645(void);
static NODE *func__compiler__sim2c_646;
static void entry__compiler__sim2c_646(void);
static FRAME_INFO frame__compiler__sim2c_646 = {1, {"name"}};
static NODE *string__16f790c158cdffe3;
static void cont__compiler__sim2c_648(void);
static void cont__compiler__sim2c_649(void);
static NODE *string__ff4edce8b0a2fa27;
static void cont__compiler__sim2c_651(void);
static void cont__compiler__sim2c_652(void);
static void cont__compiler__sim2c_653(void);
static NODE *string__b07009729763a0f0;
static void cont__compiler__sim2c_655(void);
static NODE *string__75573d7e471fdc32;
static void cont__compiler__sim2c_657(void);
static void cont__compiler__sim2c_658(void);
static void cont__compiler__sim2c_659(void);
static NODE *func__compiler__sim2c_660;
static void entry__compiler__sim2c_660(void);
static FRAME_INFO frame__compiler__sim2c_660 = {1, {"generated_top_level_variable_names"}};
static void cont__compiler__sim2c_661(void);
static void cont__compiler__sim2c_662(void);
static void cont__compiler__sim2c_663(void);
static NODE *string__fa727015ff16bc6;
static void cont__compiler__sim2c_665(void);
static void cont__compiler__sim2c_666(void);
static NODE *func__compiler__sim2c_667;
static void entry__compiler__sim2c_667(void);
static FRAME_INFO frame__compiler__sim2c_667 = {0, {}};
static NODE *string__c3452dad239e6464;
static NODE *func__compiler__sim2c_669;
static void entry__compiler__sim2c_669(void);
static FRAME_INFO frame__compiler__sim2c_669 = {0, {}};
static NODE *string__1f74a3bba8d254fe;
static NODE *string__a1240cd997f230c1;
static void cont__compiler__sim2c_672(void);
static void cont__compiler__sim2c_673(void);
static NODE *string__b4688827b8af4941;
static void cont__compiler__sim2c_675(void);
static void cont__compiler__sim2c_676(void);
static void cont__compiler__sim2c_677(void);
static void cont__compiler__sim2c_678(void);
static NODE *func__compiler__sim2c_679;
static void entry__compiler__sim2c_679(void);
static FRAME_INFO frame__compiler__sim2c_679 = {1, {"generated_continuation_table"}};
static void cont__compiler__sim2c_680(void);
static void cont__compiler__sim2c_681(void);
static void cont__compiler__sim2c_682(void);
static NODE *string__380aff8b5e307d33;
static void cont__compiler__sim2c_684(void);
static NODE *string__817a259dab23f435;
static void cont__compiler__sim2c_686(void);
static NODE *func__compiler__sim2c_687;
static void entry__compiler__sim2c_687(void);
static FRAME_INFO frame__compiler__sim2c_687 = {0, {}};
static NODE *func__compiler__sim2c_688;
static void entry__compiler__sim2c_688(void);
static FRAME_INFO frame__compiler__sim2c_688 = {2, {"name", "node"}};
static void cont__compiler__sim2c_689(void);
static NODE *string__2d7981f4e6082be5;
static NODE *string__578a5af303e9cc1;
static NODE *string__2d7981f4e6d02bcf;
static void cont__compiler__sim2c_693(void);
static void cont__compiler__sim2c_694(void);
static void cont__compiler__sim2c_695(void);
static void cont__compiler__sim2c_696(void);
static NODE *func__compiler__sim2c_697;
static void entry__compiler__sim2c_697(void);
static FRAME_INFO frame__compiler__sim2c_697 = {2, {"name", "literal"}};
static NODE *string__cb6a78473f66a6a1;
static void cont__compiler__sim2c_699(void);
static void cont__compiler__sim2c_700(void);
static NODE *string__44a800d7e66fda5b;
static void cont__compiler__sim2c_702(void);
static NODE *func__compiler__sim2c_703;
static void entry__compiler__sim2c_703(void);
static FRAME_INFO frame__compiler__sim2c_703 = {1, {"name"}};
static NODE *string__fa730415f296bee;
static NODE *string__fa730c15f496bc6;
static void cont__compiler__sim2c_706(void);
static void cont__compiler__sim2c_707(void);
static NODE *string__5e3d918a06749390;
static NODE *string__b90701ef69cd6166;
static void cont__compiler__sim2c_710(void);
static void cont__compiler__sim2c_711(void);
static void cont__compiler__sim2c_712(void);
static NODE *func__compiler__sim2c_713;
static void entry__compiler__sim2c_713(void);
static FRAME_INFO frame__compiler__sim2c_713 = {2, {"filename", "depth"}};
static void cont__compiler__sim2c_714(void);
static void cont__compiler__sim2c_715(void);
static void cont__compiler__sim2c_716(void);
static NODE *string__9c11f7a3e8641900;
static NODE *string__2d7981f4e6182bec;
static void cont__compiler__sim2c_719(void);
static NODE *func__compiler__sim2c_720;
static void entry__compiler__sim2c_720(void);
static FRAME_INFO frame__compiler__sim2c_720 = {0, {}};
static NODE *string__2d7981f4e6682be5;
static void cont__compiler__sim2c_722(void);
static NODE *string__d1bc6cafcb964c0d;
static void cont__compiler__sim2c_724(void);
static NODE *func__compiler__sim2c_725;
static void entry__compiler__sim2c_725(void);
static FRAME_INFO frame__compiler__sim2c_725 = {4, {"name", "info", "mangle_filename", "fname"}};
static void cont__compiler__sim2c_726(void);
static NODE *string__7cb40b96062f3614;
static NODE *string__4b1f5385e2b9ec5c;
static NODE *string__4b1f5345e2b9ec5c;
static NODE *string__4b1f5305e2b9ec5c;
static NODE *string__4b1f52c5e2b9ec5c;
static NODE *string__4b1f5285e2b9ec5c;
static NODE *string__4b1f5245e2b9ec5c;
static NODE *string__fa3f5235fd3e2424;
static void cont__compiler__sim2c_735(void);
static void cont__compiler__sim2c_736(void);
static void cont__compiler__sim2c_737(void);
static void cont__compiler__sim2c_738(void);
static NODE *string__bcb42196062f3614;
static NODE *string__fc8c36a84adb366f;
static void cont__compiler__sim2c_741(void);
static void cont__compiler__sim2c_742(void);
static void cont__compiler__sim2c_743(void);
static NODE *string__2d7981f4e4e02bcf;
static void cont__compiler__sim2c_745(void);
static NODE *func__compiler__sim2c_746;
static void entry__compiler__sim2c_746(void);
static FRAME_INFO frame__compiler__sim2c_746 = {0, {}};
static NODE *string__25aa47136a75b74b;
static NODE *func__compiler__sim2c_748;
static void entry__compiler__sim2c_748(void);
static FRAME_INFO frame__compiler__sim2c_748 = {0, {}};
static NODE *string__1aafb345f496a1;
static NODE *string__d7e0d1a7b944caae;
static void cont__compiler__sim2c_751(void);
static void cont__compiler__sim2c_752(void);
static NODE *func__compiler__sim2c_753;
static void entry__compiler__sim2c_753(void);
static FRAME_INFO frame__compiler__sim2c_753 = {4, {"name", "info", "mangle_filename", "mangled_name"}};
static void cont__compiler__sim2c_754(void);
static NODE *string__fedb25123ef1fa6f;
static NODE *string__fa732415f616bf7;
static void cont__compiler__sim2c_757(void);
static void cont__compiler__sim2c_758(void);
static NODE *string__6759f0f7c95235d;
static void cont__compiler__sim2c_760(void);
static NODE *func__compiler__sim2c_761;
static void entry__compiler__sim2c_761(void);
static FRAME_INFO frame__compiler__sim2c_761 = {1, {"namespace"}};
static NODE *string__d93952e55b2e5d9;
static NODE *string__860afb0b5fb87d33;
static void cont__compiler__sim2c_764(void);
static void cont__compiler__sim2c_765(void);
static void cont__compiler__sim2c_766(void);
static NODE *func__compiler__sim2c_767;
static void entry__compiler__sim2c_767(void);
static FRAME_INFO frame__compiler__sim2c_767 = {0, {}};
static NODE *string__f5b495312d83add5;
static NODE *func__compiler__sim2c_769;
static void entry__compiler__sim2c_769(void);
static FRAME_INFO frame__compiler__sim2c_769 = {0, {}};
static NODE *string__b9a3b0acf1dfe8ab;
static NODE *string__d4e0c9a7b944caae;
static void cont__compiler__sim2c_772(void);
static void cont__compiler__sim2c_773(void);
static NODE *func__compiler__sim2c_774;
static void entry__compiler__sim2c_774(void);
static FRAME_INFO frame__compiler__sim2c_774 = {3, {"name", "info", "mangle_filename"}};
static void cont__compiler__sim2c_775(void);
static NODE *string__fedb25d23ef1fa6f;
static void cont__compiler__sim2c_777(void);
static void cont__compiler__sim2c_778(void);
static NODE *string__f93d0720893942d5;
static void cont__compiler__sim2c_780(void);
static void cont__compiler__sim2c_781(void);
static NODE *func__compiler__sim2c_782;
static void entry__compiler__sim2c_782(void);
static FRAME_INFO frame__compiler__sim2c_782 = {2, {"name", "literal"}};
static NODE *string__fa730415fc16bec;
static void cont__compiler__sim2c_784(void);
static void cont__compiler__sim2c_785(void);
static NODE *func__compiler__sim2c_786;
static void entry__compiler__sim2c_786(void);
static FRAME_INFO frame__compiler__sim2c_786 = {1, {"literal"}};
static void cont__compiler__sim2c_787(void);
static NODE *func__compiler__sim2c_788;
static void entry__compiler__sim2c_788(void);
static FRAME_INFO frame__compiler__sim2c_788 = {2, {"literal", "value"}};
static void cont__compiler__sim2c_789(void);
static void cont__compiler__sim2c_790(void);
static void cont__compiler__sim2c_791(void);
static NODE *string__2d7981f4e6882bbd;
static void cont__compiler__sim2c_793(void);
static void cont__compiler__sim2c_794(void);
static NODE *func__compiler__sim2c_795;
static void entry__compiler__sim2c_795(void);
static FRAME_INFO frame__compiler__sim2c_795 = {1, {"value"}};
static void cont__compiler__sim2c_796(void);
static void cont__compiler__sim2c_797(void);
static void cont__compiler__sim2c_798(void);
static NODE *func__compiler__sim2c_799;
static void entry__compiler__sim2c_799(void);
static FRAME_INFO frame__compiler__sim2c_799 = {1, {"value"}};
static NODE *string__ecd034ad7215125;
static void cont__compiler__sim2c_801(void);
static NODE *func__compiler__sim2c_802;
static void entry__compiler__sim2c_802(void);
static FRAME_INFO frame__compiler__sim2c_802 = {2, {"value", "int_val"}};
static void cont__compiler__sim2c_803(void);
static NODE *func__compiler__sim2c_804;
static void entry__compiler__sim2c_804(void);
static FRAME_INFO frame__compiler__sim2c_804 = {1, {"int_val"}};
static void cont__compiler__sim2c_805(void);
static void cont__compiler__sim2c_806(void);
static NODE *func__compiler__sim2c_807;
static void entry__compiler__sim2c_807(void);
static FRAME_INFO frame__compiler__sim2c_807 = {1, {"int_val"}};
static NODE *string__22891489d598e125;
static NODE *string__680afb0b5fb87d33;
static void cont__compiler__sim2c_810(void);
static NODE *func__compiler__sim2c_811;
static void entry__compiler__sim2c_811(void);
static FRAME_INFO frame__compiler__sim2c_811 = {1, {"int_val"}};
static void cont__compiler__sim2c_812(void);
static void cont__compiler__sim2c_813(void);
static NODE *func__compiler__sim2c_814;
static void entry__compiler__sim2c_814(void);
static FRAME_INFO frame__compiler__sim2c_814 = {1, {"int_val"}};
static NODE *string__228915c9d5a8e125;
static NODE *string__1f441a036092dd;
static void cont__compiler__sim2c_817(void);
static NODE *func__compiler__sim2c_818;
static void entry__compiler__sim2c_818(void);
static FRAME_INFO frame__compiler__sim2c_818 = {1, {"value"}};
static NODE *string__c470b0c3df48bfe1;
static void cont__compiler__sim2c_820(void);
static NODE *func__compiler__sim2c_821;
static void entry__compiler__sim2c_821(void);
static FRAME_INFO frame__compiler__sim2c_821 = {1, {"literal"}};
static void cont__compiler__sim2c_822(void);
static NODE *func__compiler__sim2c_823;
static void entry__compiler__sim2c_823(void);
static FRAME_INFO frame__compiler__sim2c_823 = {1, {"literal"}};
static void cont__compiler__sim2c_824(void);
static void cont__compiler__sim2c_825(void);
static NODE *string__2666ac8409f84460;
static void cont__compiler__sim2c_827(void);
static void cont__compiler__sim2c_828(void);
static void cont__compiler__sim2c_829(void);
static NODE *func__compiler__sim2c_830;
static void entry__compiler__sim2c_830(void);
static FRAME_INFO frame__compiler__sim2c_830 = {0, {}};
static NODE *string__cb22ed554b280fb1;
static NODE *func__compiler__sim2c_832;
static void entry__compiler__sim2c_832(void);
static FRAME_INFO frame__compiler__sim2c_832 = {0, {}};
static NODE *string__b9a3b0edf1dfe8ab;
static NODE *string__d5e0c1a7b944caae;
static void cont__compiler__sim2c_835(void);
static void cont__compiler__sim2c_836(void);
static NODE *func__compiler__sim2c_837;
static void entry__compiler__sim2c_837(void);
static FRAME_INFO frame__compiler__sim2c_837 = {3, {"name", "info", "mangle_filename"}};
static void cont__compiler__sim2c_838(void);
static NODE *string__fedb25923ef1fa6f;
static void cont__compiler__sim2c_840(void);
static void cont__compiler__sim2c_841(void);
static NODE *string__f647f212951f31f8;
static void cont__compiler__sim2c_843(void);
static void cont__compiler__sim2c_844(void);
static void cont__compiler__sim2c_845(void);
static NODE *func__compiler__sim2c_846;
static void entry__compiler__sim2c_846(void);
static FRAME_INFO frame__compiler__sim2c_846 = {0, {}};
static NODE *string__19b03dcd2fdc791;
static NODE *func__compiler__sim2c_848;
static void entry__compiler__sim2c_848(void);
static FRAME_INFO frame__compiler__sim2c_848 = {0, {}};
static NODE *string__b9a3b12af1dfe8ab;
static NODE *string__d2e0f9a7b944caae;
static void cont__compiler__sim2c_851(void);
static void cont__compiler__sim2c_852(void);
static NODE *func__compiler__sim2c_853;
static void entry__compiler__sim2c_853(void);
static FRAME_INFO frame__compiler__sim2c_853 = {3, {"name", "info", "mangle_filename"}};
static void cont__compiler__sim2c_854(void);
static NODE *string__fedb24523ef1fa6f;
static void cont__compiler__sim2c_856(void);
static void cont__compiler__sim2c_857(void);
static void cont__compiler__sim2c_858(void);
static void cont__compiler__sim2c_859(void);
static NODE *func__compiler__sim2c_860;
static void entry__compiler__sim2c_860(void);
static FRAME_INFO frame__compiler__sim2c_860 = {2, {"name", "info"}};
static void cont__compiler__sim2c_861(void);
static void cont__compiler__sim2c_862(void);
static NODE *func__compiler__sim2c_863;
static void entry__compiler__sim2c_863(void);
static FRAME_INFO frame__compiler__sim2c_863 = {4, {"name", "info", "namespace", "basename"}};
static void cont__compiler__sim2c_864(void);
static NODE *func__compiler__sim2c_865;
static void entry__compiler__sim2c_865(void);
static FRAME_INFO frame__compiler__sim2c_865 = {1, {"name"}};
static void cont__compiler__sim2c_866(void);
static void cont__compiler__sim2c_867(void);
static NODE *func__compiler__sim2c_868;
static void entry__compiler__sim2c_868(void);
static FRAME_INFO frame__compiler__sim2c_868 = {0, {}};
static NODE *string__5e0ae40b5c007d75;
static void cont__compiler__sim2c_870(void);
static void cont__compiler__sim2c_871(void);
static void cont__compiler__sim2c_872(void);
static NODE *func__compiler__sim2c_873;
static void entry__compiler__sim2c_873(void);
static FRAME_INFO frame__compiler__sim2c_873 = {3, {"namespace", "basename", "name"}};
static NODE *string__82877bb737e0bc50;
static NODE *string__fa733415f296bee;
static NODE *string__65b0238fc1fb0d7a;
static NODE *string__4a0e52ffba34c725;
static void cont__compiler__sim2c_878(void);
static NODE *func__compiler__sim2c_879;
static void entry__compiler__sim2c_879(void);
static FRAME_INFO frame__compiler__sim2c_879 = {3, {"namespace", "basename", "name"}};
static NODE *string__c1145f87c6ab68aa;
static NODE *string__f681eab2d5b5e9a9;
static void cont__compiler__sim2c_882(void);
static NODE *func__compiler__sim2c_883;
static void entry__compiler__sim2c_883(void);
static FRAME_INFO frame__compiler__sim2c_883 = {3, {"namespace", "basename", "name"}};
static NODE *string__f63e3617473fc88a;
static NODE *string__6594a8f5052ca9ff;
static void cont__compiler__sim2c_886(void);
static NODE *func__compiler__sim2c_887;
static void entry__compiler__sim2c_887(void);
static FRAME_INFO frame__compiler__sim2c_887 = {3, {"namespace", "basename", "name"}};
static NODE *string__b45bfb6d6d495155;
static NODE *string__9ccb3018e8f13bec;
static void cont__compiler__sim2c_890(void);
static NODE *func__compiler__sim2c_891;
static void entry__compiler__sim2c_891(void);
static FRAME_INFO frame__compiler__sim2c_891 = {3, {"namespace", "basename", "name"}};
static NODE *string__5b5ec7878e89a218;
static void cont__compiler__sim2c_893(void);
static void cont__compiler__sim2c_894(void);
static void cont__compiler__sim2c_895(void);
static NODE *func__compiler__sim2c_896;
static void entry__compiler__sim2c_896(void);
static FRAME_INFO frame__compiler__sim2c_896 = {0, {}};
static NODE *string__29050caaed294603;
static void cont__compiler__sim2c_898(void);
static NODE *func__compiler__sim2c_899;
static void entry__compiler__sim2c_899(void);
static FRAME_INFO frame__compiler__sim2c_899 = {0, {}};
static NODE *string__a9896ddd6eafadae;
static NODE *func__compiler__sim2c_901;
static void entry__compiler__sim2c_901(void);
static FRAME_INFO frame__compiler__sim2c_901 = {0, {}};
static NODE *string__b9a3b16bf1dfe8ab;
static NODE *string__d3e0f1a7b944caae;
static void cont__compiler__sim2c_904(void);
static void cont__compiler__sim2c_905(void);
static NODE *func__compiler__sim2c_906;
static void entry__compiler__sim2c_906(void);
static FRAME_INFO frame__compiler__sim2c_906 = {3, {"name", "info", "mangle_filename"}};
static void cont__compiler__sim2c_907(void);
static NODE *string__fedb24123ef1fa6f;
static void cont__compiler__sim2c_909(void);
static void cont__compiler__sim2c_910(void);
static void cont__compiler__sim2c_911(void);
static NODE *func__compiler__sim2c_912;
static void entry__compiler__sim2c_912(void);
static FRAME_INFO frame__compiler__sim2c_912 = {0, {}};
static NODE *string__1cd8a7b21f5517c3;
static NODE *func__compiler__sim2c_914;
static void entry__compiler__sim2c_914(void);
static FRAME_INFO frame__compiler__sim2c_914 = {0, {}};
static NODE *string__b9a3b1a8f1dfe8ab;
static NODE *string__d0e0e9a7b944caae;
static void cont__compiler__sim2c_917(void);
static void cont__compiler__sim2c_918(void);
static NODE *func__compiler__sim2c_919;
static void entry__compiler__sim2c_919(void);
static FRAME_INFO frame__compiler__sim2c_919 = {3, {"name", "info", "mangle_filename"}};
static void cont__compiler__sim2c_920(void);
static NODE *string__fedb24d23ef1fa6f;
static void cont__compiler__sim2c_922(void);
static void cont__compiler__sim2c_923(void);
static void cont__compiler__sim2c_924(void);
static NODE *string__476ac52a7f81f4a0;
static void cont__compiler__sim2c_926(void);
static void cont__compiler__sim2c_927(void);
static NODE *func__compiler__sim2c_928;
static void entry__compiler__sim2c_928(void);
static FRAME_INFO frame__compiler__sim2c_928 = {0, {}};
static NODE *string__3734ffa0d2ae2d12;
static void cont__compiler__sim2c_930(void);
static void cont__compiler__sim2c_931(void);
static NODE *func__compiler__sim2c_932;
static void entry__compiler__sim2c_932(void);
static FRAME_INFO frame__compiler__sim2c_932 = {1, {"filenames"}};
static void cont__compiler__sim2c_933(void);
static NODE *string__1d702a52a35b6426;
static void cont__compiler__sim2c_935(void);
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
  {run__sim2c, NULL, 55, 55, 5, 17},
  {cont__10_2, NULL, 56, 56, 5, 25},
  {cont__10_4, NULL, 57, 57, 5, 20},
  {cont__10_6, NULL, 58, 58, 5, 19},
  {cont__10_8, NULL, 59, 59, 5, 24},
  {cont__10_10, NULL, 60, 60, 5, 23},
  {cont__10_12, NULL, 61, 61, 5, 21},
  {cont__10_14, NULL, 53, 61, 1, 22},
  {cont__10_15, NULL, },
  {entry__compiler__print_source_3, NULL, 39, 39, 9, 17},
  {entry__compiler__print_source_4, NULL, 33, 33, 9, 27},
  {entry__compiler__print_source_6, NULL, 35, 35, 9, 33},
  {entry__compiler__print_source_8, NULL, 37, 37, 9, 34},
  {entry__compiler__print_source_2, NULL, 31, 39, 5, 18},
  {entry__compiler__print_source, NULL, 30, 39, 3, 19},
  {entry__compiler__eprint_source_3, NULL, 51, 51, 9, 18},
  {entry__compiler__eprint_source_4, NULL, 45, 45, 9, 28},
  {entry__compiler__eprint_source_5, NULL, 47, 47, 9, 34},
  {entry__compiler__eprint_source_6, NULL, 49, 49, 9, 35},
  {entry__compiler__eprint_source_2, NULL, 43, 51, 5, 19},
  {entry__compiler__eprint_source, NULL, 42, 51, 3, 20},
  {entry__compiler__generate_dispatcher_function_11, NULL, 89, 92, 26, 18},
  {cont__compiler__generate_dispatcher_function_15, &frame__compiler__generate_dispatcher_function_11, 89, 92, 7, 18},
  {entry__compiler__generate_dispatcher_function_16, NULL, 95, 95, 9, 79},
  {cont__compiler__generate_dispatcher_function_18, &frame__compiler__generate_dispatcher_function_16, 94, 95, 7, 79},
  {entry__compiler__generate_dispatcher_function, NULL, 64, 65, 25, 36},
  {cont__compiler__generate_dispatcher_function_4, &frame__compiler__generate_dispatcher_function, 64, 65, 3, 36},
  {cont__compiler__generate_dispatcher_function_5, &frame__compiler__generate_dispatcher_function, 66, 71, 22, 9},
  {cont__compiler__generate_dispatcher_function_7, &frame__compiler__generate_dispatcher_function, 66, 71, 3, 9},
  {cont__compiler__generate_dispatcher_function_8, &frame__compiler__generate_dispatcher_function, 72, 72, 3, 44},
  {cont__compiler__generate_dispatcher_function_9, &frame__compiler__generate_dispatcher_function, 74, 74, 5, 17},
  {cont__compiler__generate_dispatcher_function_10, &frame__compiler__generate_dispatcher_function, 73, 95, 3, 81},
  {cont__compiler__generate_dispatcher_function_19, &frame__compiler__generate_dispatcher_function, 100, 120, 22, 5},
  {cont__compiler__generate_dispatcher_function_22, &frame__compiler__generate_dispatcher_function, 100, 120, 3, 5},
  {entry__demangled, NULL, 122, 122, 40, 50},
  {cont__demangled_4, &frame__demangled, 122, 122, 23, 51},
  {cont__demangled_5, &frame__demangled, 122, 122, 20, 51},
  {entry__compiler__update_info_8, NULL, 138, 138, 15, 30},
  {entry__compiler__update_info_9, NULL, 141, 141, 31, 44},
  {cont__compiler__update_info_10, &frame__compiler__update_info_9, 140, 142, 21, 55},
  {cont__compiler__update_info_13, &frame__compiler__update_info_9, 140, 142, 15, 55},
  {entry__compiler__update_info_5, NULL, 136, 136, 13, 34},
  {cont__compiler__update_info_6, &frame__compiler__update_info_5, 137, 137, 13, 38},
  {cont__compiler__update_info_7, &frame__compiler__update_info_5, 135, 142, 11, 57},
  {entry__compiler__update_info_16, NULL, 147, 147, 15, 30},
  {entry__compiler__update_info_17, NULL, 149, 149, 15, 25},
  {entry__compiler__update_info_14, NULL, 145, 145, 13, 34},
  {cont__compiler__update_info_15, &frame__compiler__update_info_14, 144, 149, 11, 26},
  {entry__compiler__update_info_20, NULL, 154, 154, 31, 44},
  {cont__compiler__update_info_21, &frame__compiler__update_info_20, 153, 155, 21, 45},
  {cont__compiler__update_info_23, &frame__compiler__update_info_20, 153, 155, 15, 45},
  {entry__compiler__update_info_25, NULL, 157, 157, 15, 30},
  {entry__compiler__update_info_26, NULL, 160, 160, 31, 44},
  {cont__compiler__update_info_27, &frame__compiler__update_info_26, 159, 161, 21, 44},
  {cont__compiler__update_info_29, &frame__compiler__update_info_26, 159, 161, 15, 44},
  {entry__compiler__update_info_30, NULL, 163, 163, 15, 25},
  {entry__compiler__update_info_18, NULL, 151, 151, 16, 37},
  {cont__compiler__update_info_19, &frame__compiler__update_info_18, 156, 156, 13, 39},
  {cont__compiler__update_info_24, &frame__compiler__update_info_18, 151, 163, 11, 26},
  {entry__compiler__update_info_33, NULL, 168, 168, 31, 44},
  {cont__compiler__update_info_34, &frame__compiler__update_info_33, 167, 169, 21, 57},
  {cont__compiler__update_info_36, &frame__compiler__update_info_33, 167, 169, 15, 57},
  {entry__compiler__update_info_38, NULL, 171, 171, 15, 30},
  {entry__compiler__update_info_39, NULL, 174, 174, 31, 44},
  {cont__compiler__update_info_40, &frame__compiler__update_info_39, 173, 175, 21, 44},
  {cont__compiler__update_info_41, &frame__compiler__update_info_39, 173, 175, 15, 44},
  {entry__compiler__update_info_42, NULL, 178, 178, 31, 44},
  {cont__compiler__update_info_43, &frame__compiler__update_info_42, 177, 179, 21, 55},
  {cont__compiler__update_info_45, &frame__compiler__update_info_42, 177, 179, 15, 55},
  {entry__compiler__update_info_31, NULL, 165, 165, 16, 37},
  {cont__compiler__update_info_32, &frame__compiler__update_info_31, 170, 170, 13, 41},
  {cont__compiler__update_info_37, &frame__compiler__update_info_31, 165, 179, 11, 57},
  {entry__compiler__update_info_48, NULL, 184, 184, 31, 44},
  {cont__compiler__update_info_49, &frame__compiler__update_info_48, 183, 185, 21, 56},
  {cont__compiler__update_info_51, &frame__compiler__update_info_48, 183, 185, 15, 56},
  {entry__compiler__update_info_53, NULL, 187, 187, 15, 30},
  {entry__compiler__update_info_54, NULL, 190, 190, 31, 44},
  {cont__compiler__update_info_55, &frame__compiler__update_info_54, 189, 191, 21, 55},
  {cont__compiler__update_info_56, &frame__compiler__update_info_54, 189, 191, 15, 55},
  {entry__compiler__update_info_57, NULL, 193, 193, 15, 25},
  {entry__compiler__update_info_46, NULL, 181, 181, 16, 37},
  {cont__compiler__update_info_47, &frame__compiler__update_info_46, 186, 186, 13, 54},
  {cont__compiler__update_info_52, &frame__compiler__update_info_46, 181, 193, 11, 26},
  {entry__compiler__update_info_3, NULL, 133, 133, 12, 38},
  {cont__compiler__update_info_4, &frame__compiler__update_info_3, 133, 193, 7, 28},
  {entry__compiler__update_info_58, NULL, 195, 195, 7, 17},
  {entry__compiler__update_info, NULL, 132, 132, 5, 24},
  {cont__compiler__update_info_2, &frame__compiler__update_info, 131, 195, 3, 18},
  {cont__compiler__update_info_59, &frame__compiler__update_info, 195, 195, 18, 18},
  {entry__compiler__sim2c_7, NULL, 224, 224, 42, 42},
  {cont__compiler__sim2c_8, &frame__compiler__sim2c_7, 224, 224, 17, 43},
  {cont__compiler__sim2c_9, &frame__compiler__sim2c_7, 224, 224, 68, 68},
  {cont__compiler__sim2c_10, &frame__compiler__sim2c_7, 224, 224, 54, 69},
  {cont__compiler__sim2c_11, &frame__compiler__sim2c_7, 224, 224, 11, 69},
  {cont__compiler__sim2c_12, &frame__compiler__sim2c_7, 224, 224, 69, 69},
  {entry__compiler__sim2c_13, NULL, 226, 226, 31, 31},
  {cont__compiler__sim2c_14, &frame__compiler__sim2c_13, 226, 226, 11, 32},
  {cont__compiler__sim2c_15, &frame__compiler__sim2c_13, 226, 226, 32, 32},
  {entry__compiler__sim2c_5, NULL, 223, 223, 9, 35},
  {cont__compiler__sim2c_6, &frame__compiler__sim2c_5, 222, 226, 7, 33},
  {entry__compiler__sim2c_2, NULL, 221, 221, 8, 29},
  {cont__compiler__sim2c_4, &frame__compiler__sim2c_2, 221, 226, 5, 34},
  {cont__compiler__sim2c_16, &frame__compiler__sim2c_2, 227, 227, 25, 34},
  {cont__compiler__sim2c_17, &frame__compiler__sim2c_2, 227, 227, 8, 35},
  {cont__compiler__sim2c_18, &frame__compiler__sim2c_2, 227, 227, 5, 35},
  {entry__compiler__sim2c_26, NULL, 461, 461, 37, 57},
  {cont__compiler__sim2c_27, &frame__compiler__sim2c_26, 461, 461, 37, 68},
  {cont__compiler__sim2c_28, &frame__compiler__sim2c_26, 461, 461, 37, 68},
  {entry__compiler__sim2c_21, NULL, 458, 458, 9, 45},
  {cont__compiler__sim2c_22, &frame__compiler__sim2c_21, 459, 459, 9, 40},
  {cont__compiler__sim2c_23, &frame__compiler__sim2c_21, 460, 460, 9, 40},
  {cont__compiler__sim2c_24, &frame__compiler__sim2c_21, 461, 461, 12, 32},
  {cont__compiler__sim2c_25, &frame__compiler__sim2c_21, 461, 461, 12, 68},
  {cont__compiler__sim2c_29, &frame__compiler__sim2c_21, 461, 461, 9, 75},
  {entry__compiler__sim2c_33, NULL, 465, 465, 11, 50},
  {cont__compiler__sim2c_34, &frame__compiler__sim2c_33, 466, 466, 11, 16},
  {entry__compiler__sim2c_30, NULL, 463, 463, 9, 46},
  {cont__compiler__sim2c_31, &frame__compiler__sim2c_30, 464, 464, 12, 32},
  {cont__compiler__sim2c_32, &frame__compiler__sim2c_30, 464, 466, 9, 16},
  {entry__compiler__sim2c_39, NULL, 468, 468, 33, 59},
  {cont__compiler__sim2c_40, &frame__compiler__sim2c_39, 468, 468, 72, 72},
  {entry__compiler__sim2c_19, NULL, 457, 457, 7, 34},
  {cont__compiler__sim2c_20, &frame__compiler__sim2c_19, 456, 466, 5, 18},
  {cont__compiler__sim2c_35, &frame__compiler__sim2c_19, 467, 467, 44, 69},
  {cont__compiler__sim2c_36, &frame__compiler__sim2c_19, 467, 467, 5, 75},
  {cont__compiler__sim2c_37, &frame__compiler__sim2c_19, 468, 468, 8, 30},
  {cont__compiler__sim2c_38, &frame__compiler__sim2c_19, 468, 468, 5, 72},
  {cont__compiler__sim2c_41, &frame__compiler__sim2c_19, 468, 468, 72, 72},
  {entry__compiler__sim2c_49, NULL, 256, 256, 9, 22},
  {cont__compiler__sim2c_50, &frame__compiler__sim2c_49, 256, 256, 22, 22},
  {entry__compiler__sim2c_51, NULL, 258, 258, 9, 61},
  {entry__compiler__sim2c_54, NULL, 260, 261, 14, 31},
  {cont__compiler__sim2c_57, &frame__compiler__sim2c_54, 260, 261, 7, 31},
  {entry__compiler__sim2c_59, NULL, 262, 262, 24, 59},
  {entry__compiler__sim2c_64, NULL, 263, 263, 29, 54},
  {entry__compiler__sim2c_70, NULL, 264, 264, 23, 65},
  {entry__compiler__sim2c_77, NULL, 265, 265, 28, 73},
  {entry__compiler__sim2c_82, NULL, 266, 266, 43, 43},
  {entry__compiler__sim2c_86, NULL, 269, 269, 24, 63},
  {entry__compiler__sim2c_89, NULL, 270, 270, 51, 68},
  {cont__compiler__sim2c_90, &frame__compiler__sim2c_89, 270, 270, 68, 68},
  {entry__compiler__sim2c_92, NULL, 271, 271, 24, 62},
  {entry__compiler__sim2c_99, NULL, 277, 277, 13, 28},
  {cont__compiler__sim2c_100, &frame__compiler__sim2c_99, 278, 278, 25, 49},
  {cont__compiler__sim2c_101, &frame__compiler__sim2c_99, 278, 278, 13, 49},
  {cont__compiler__sim2c_102, &frame__compiler__sim2c_99, 278, 278, 49, 49},
  {entry__compiler__sim2c_103, NULL, 280, 280, 13, 28},
  {cont__compiler__sim2c_104, &frame__compiler__sim2c_103, 281, 281, 25, 56},
  {cont__compiler__sim2c_105, &frame__compiler__sim2c_103, 281, 281, 13, 56},
  {cont__compiler__sim2c_106, &frame__compiler__sim2c_103, 281, 281, 56, 56},
  {entry__compiler__sim2c_96, NULL, 275, 275, 14, 32},
  {cont__compiler__sim2c_97, &frame__compiler__sim2c_96, 275, 275, 14, 35},
  {cont__compiler__sim2c_98, &frame__compiler__sim2c_96, 275, 283, 9, 17},
  {entry__compiler__sim2c_95, NULL, 274, 283, 7, 18},
  {cont__compiler__sim2c_107, &frame__compiler__sim2c_95, 283, 283, 18, 18},
  {entry__compiler__sim2c_47, NULL, 253, 253, 5, 24},
  {cont__compiler__sim2c_48, &frame__compiler__sim2c_47, 254, 258, 5, 62},
  {cont__compiler__sim2c_53, &frame__compiler__sim2c_47, 259, 261, 5, 32},
  {cont__compiler__sim2c_58, &frame__compiler__sim2c_47, 262, 262, 5, 59},
  {cont__compiler__sim2c_61, &frame__compiler__sim2c_47, 263, 263, 8, 21},
  {cont__compiler__sim2c_62, &frame__compiler__sim2c_47, 263, 263, 8, 26},
  {cont__compiler__sim2c_63, &frame__compiler__sim2c_47, 263, 263, 5, 54},
  {cont__compiler__sim2c_66, &frame__compiler__sim2c_47, 264, 264, 8, 13},
  {cont__compiler__sim2c_67, &frame__compiler__sim2c_47, 264, 264, 8, 20},
  {cont__compiler__sim2c_68, &frame__compiler__sim2c_47, 264, 264, 8, 20},
  {cont__compiler__sim2c_69, &frame__compiler__sim2c_47, 264, 264, 5, 65},
  {cont__compiler__sim2c_72, &frame__compiler__sim2c_47, 265, 265, 13, 13},
  {cont__compiler__sim2c_73, &frame__compiler__sim2c_47, 265, 265, 8, 14},
  {cont__compiler__sim2c_74, &frame__compiler__sim2c_47, 265, 265, 8, 25},
  {cont__compiler__sim2c_75, &frame__compiler__sim2c_47, 265, 265, 8, 25},
  {cont__compiler__sim2c_76, &frame__compiler__sim2c_47, 265, 265, 5, 73},
  {cont__compiler__sim2c_79, &frame__compiler__sim2c_47, 266, 266, 8, 28},
  {cont__compiler__sim2c_81, &frame__compiler__sim2c_47, 266, 266, 5, 43},
  {cont__compiler__sim2c_83, &frame__compiler__sim2c_47, 267, 267, 5, 32},
  {cont__compiler__sim2c_84, &frame__compiler__sim2c_47, 268, 268, 5, 49},
  {cont__compiler__sim2c_85, &frame__compiler__sim2c_47, 269, 269, 5, 63},
  {cont__compiler__sim2c_88, &frame__compiler__sim2c_47, 270, 270, 5, 68},
  {cont__compiler__sim2c_91, &frame__compiler__sim2c_47, 271, 271, 5, 62},
  {cont__compiler__sim2c_94, &frame__compiler__sim2c_47, 273, 283, 5, 19},
  {cont__compiler__sim2c_108, &frame__compiler__sim2c_47, 284, 284, 60, 60},
  {cont__compiler__sim2c_109, &frame__compiler__sim2c_47, 284, 284, 23, 61},
  {cont__compiler__sim2c_110, &frame__compiler__sim2c_47, 284, 284, 5, 61},
  {cont__compiler__sim2c_111, &frame__compiler__sim2c_47, },
  {entry__compiler__sim2c_113, NULL, 285, 285, 46, 70},
  {cont__compiler__sim2c_114, &frame__compiler__sim2c_113, 285, 285, 34, 70},
  {cont__compiler__sim2c_115, &frame__compiler__sim2c_113, 285, 285, 70, 70},
  {entry__compiler__sim2c_117, NULL, 286, 286, 50, 61},
  {cont__compiler__sim2c_118, &frame__compiler__sim2c_117, 286, 286, 22, 61},
  {entry__compiler__sim2c_121, NULL, 296, 296, 5, 21},
  {cont__compiler__sim2c_122, &frame__compiler__sim2c_121, 297, 297, 5, 13},
  {entry__compiler__sim2c_124, NULL, 299, 299, 44, 70},
  {cont__compiler__sim2c_126, &frame__compiler__sim2c_124, 299, 299, 5, 71},
  {cont__compiler__sim2c_127, &frame__compiler__sim2c_124, 299, 299, 71, 71},
  {entry__compiler__sim2c_129, NULL, 302, 302, 5, 26},
  {cont__compiler__sim2c_130, &frame__compiler__sim2c_129, },
  {entry__compiler__sim2c_132, NULL, 303, 303, 52, 63},
  {cont__compiler__sim2c_133, &frame__compiler__sim2c_132, 303, 303, 22, 63},
  {entry__compiler__sim2c_136, NULL, 308, 308, 5, 28},
  {cont__compiler__sim2c_137, &frame__compiler__sim2c_136, 309, 309, 5, 51},
  {cont__compiler__sim2c_138, &frame__compiler__sim2c_136, 310, 310, 5, 45},
  {cont__compiler__sim2c_139, &frame__compiler__sim2c_136, },
  {entry__compiler__sim2c_141, NULL, 311, 311, 53, 64},
  {cont__compiler__sim2c_142, &frame__compiler__sim2c_141, 311, 311, 22, 64},
  {entry__compiler__sim2c_145, NULL, 317, 317, 7, 33},
  {entry__compiler__sim2c_146, NULL, 318, 318, 7, 20},
  {entry__compiler__sim2c_149, NULL, 320, 320, 35, 41},
  {entry__compiler__sim2c_151, NULL, 321, 321, 5, 37},
  {cont__compiler__sim2c_153, &frame__compiler__sim2c_151, 322, 322, 5, 38},
  {cont__compiler__sim2c_155, &frame__compiler__sim2c_151, 322, 322, 58, 58},
  {entry__compiler__sim2c_160, NULL, 324, 324, 32, 54},
  {cont__compiler__sim2c_162, &frame__compiler__sim2c_160, 324, 324, 59, 59},
  {entry__compiler__sim2c_169, NULL, 330, 330, 47, 64},
  {cont__compiler__sim2c_170, &frame__compiler__sim2c_169, 330, 330, 47, 75},
  {cont__compiler__sim2c_171, &frame__compiler__sim2c_169, 330, 330, 47, 75},
  {entry__compiler__sim2c_180, NULL, 336, 336, 45, 63},
  {cont__compiler__sim2c_181, &frame__compiler__sim2c_180, 336, 336, 63, 63},
  {entry__compiler__sim2c_185, NULL, 338, 338, 29, 47},
  {cont__compiler__sim2c_186, &frame__compiler__sim2c_185, 338, 340, 49, 26},
  {cont__compiler__sim2c_189, &frame__compiler__sim2c_185, 338, 340, 17, 26},
  {entry__compiler__sim2c_195, NULL, 343, 343, 31, 49},
  {cont__compiler__sim2c_196, &frame__compiler__sim2c_195, 343, 345, 51, 62},
  {cont__compiler__sim2c_200, &frame__compiler__sim2c_195, 343, 345, 19, 62},
  {entry__compiler__sim2c_204, NULL, 348, 348, 31, 49},
  {cont__compiler__sim2c_205, &frame__compiler__sim2c_204, 350, 350, 51, 71},
  {cont__compiler__sim2c_206, &frame__compiler__sim2c_204, 350, 350, 38, 72},
  {cont__compiler__sim2c_207, &frame__compiler__sim2c_204, 348, 351, 51, 64},
  {cont__compiler__sim2c_210, &frame__compiler__sim2c_204, 348, 351, 19, 64},
  {entry__compiler__sim2c_192, NULL, 342, 342, 20, 37},
  {cont__compiler__sim2c_193, &frame__compiler__sim2c_192, 342, 342, 20, 48},
  {cont__compiler__sim2c_194, &frame__compiler__sim2c_192, 342, 345, 17, 63},
  {cont__compiler__sim2c_201, &frame__compiler__sim2c_192, 346, 346, 17, 45},
  {cont__compiler__sim2c_202, &frame__compiler__sim2c_192, 347, 347, 20, 36},
  {cont__compiler__sim2c_203, &frame__compiler__sim2c_192, 347, 351, 17, 65},
  {cont__compiler__sim2c_211, &frame__compiler__sim2c_192, 352, 352, 17, 38},
  {cont__compiler__sim2c_212, &frame__compiler__sim2c_192, 352, 352, 43, 43},
  {entry__compiler__sim2c_177, NULL, 335, 335, 15, 47},
  {cont__compiler__sim2c_178, &frame__compiler__sim2c_177, 336, 336, 22, 42},
  {cont__compiler__sim2c_179, &frame__compiler__sim2c_177, 336, 336, 15, 63},
  {cont__compiler__sim2c_182, &frame__compiler__sim2c_177, 337, 337, 18, 38},
  {cont__compiler__sim2c_183, &frame__compiler__sim2c_177, 337, 337, 18, 49},
  {cont__compiler__sim2c_184, &frame__compiler__sim2c_177, 337, 340, 15, 27},
  {cont__compiler__sim2c_190, &frame__compiler__sim2c_177, 341, 341, 18, 43},
  {cont__compiler__sim2c_191, &frame__compiler__sim2c_177, 341, 352, 15, 43},
  {cont__compiler__sim2c_213, &frame__compiler__sim2c_177, 353, 353, 15, 36},
  {cont__compiler__sim2c_214, &frame__compiler__sim2c_177, 354, 354, 15, 35},
  {cont__compiler__sim2c_215, &frame__compiler__sim2c_177, 354, 354, 46, 46},
  {entry__compiler__sim2c_219, NULL, 357, 357, 29, 47},
  {cont__compiler__sim2c_220, &frame__compiler__sim2c_219, 357, 358, 49, 68},
  {cont__compiler__sim2c_221, &frame__compiler__sim2c_219, 357, 358, 17, 68},
  {entry__compiler__sim2c_228, NULL, 363, 363, 33, 51},
  {cont__compiler__sim2c_229, &frame__compiler__sim2c_228, 363, 365, 53, 67},
  {cont__compiler__sim2c_230, &frame__compiler__sim2c_228, 363, 365, 21, 67},
  {entry__compiler__sim2c_226, NULL, 362, 362, 22, 44},
  {cont__compiler__sim2c_227, &frame__compiler__sim2c_226, 362, 365, 19, 68},
  {entry__compiler__sim2c_225, NULL, 361, 365, 17, 69},
  {entry__compiler__sim2c_216, NULL, 356, 356, 18, 35},
  {cont__compiler__sim2c_217, &frame__compiler__sim2c_216, 356, 356, 18, 46},
  {cont__compiler__sim2c_218, &frame__compiler__sim2c_216, 356, 358, 15, 69},
  {cont__compiler__sim2c_222, &frame__compiler__sim2c_216, 359, 359, 15, 46},
  {cont__compiler__sim2c_223, &frame__compiler__sim2c_216, 360, 360, 18, 38},
  {cont__compiler__sim2c_224, &frame__compiler__sim2c_216, 360, 365, 15, 70},
  {cont__compiler__sim2c_231, &frame__compiler__sim2c_216, 366, 366, 15, 33},
  {cont__compiler__sim2c_232, &frame__compiler__sim2c_216, 367, 367, 15, 36},
  {cont__compiler__sim2c_233, &frame__compiler__sim2c_216, 367, 367, 41, 41},
  {entry__compiler__sim2c_173, NULL, 331, 331, 11, 40},
  {cont__compiler__sim2c_174, &frame__compiler__sim2c_173, 332, 332, 11, 30},
  {cont__compiler__sim2c_175, &frame__compiler__sim2c_173, 334, 334, 13, 32},
  {cont__compiler__sim2c_176, &frame__compiler__sim2c_173, 333, 367, 11, 42},
  {entry__compiler__sim2c_166, NULL, 328, 328, 7, 32},
  {cont__compiler__sim2c_167, &frame__compiler__sim2c_166, 330, 330, 9, 42},
  {cont__compiler__sim2c_168, &frame__compiler__sim2c_166, 330, 330, 9, 75},
  {cont__compiler__sim2c_172, &frame__compiler__sim2c_166, 329, 367, 7, 44},
  {entry__compiler__sim2c_165, NULL, 327, 367, 5, 45},
  {entry__compiler__sim2c_237, NULL, 372, 372, 9, 43},
  {cont__compiler__sim2c_238, &frame__compiler__sim2c_237, 372, 372, 48, 48},
  {entry__compiler__sim2c_236, NULL, 371, 372, 7, 48},
  {entry__compiler__sim2c_235, NULL, 370, 372, 5, 49},
  {cont__compiler__sim2c_239, &frame__compiler__sim2c_235, 373, 373, 5, 58},
  {entry__compiler__sim2c_241, NULL, 374, 374, 52, 63},
  {cont__compiler__sim2c_242, &frame__compiler__sim2c_241, 374, 374, 22, 63},
  {entry__compiler__sim2c_246, NULL, 376, 376, 47, 57},
  {cont__compiler__sim2c_247, &frame__compiler__sim2c_246, 376, 376, 34, 63},
  {cont__compiler__sim2c_248, &frame__compiler__sim2c_246, 376, 376, 28, 63},
  {entry__compiler__sim2c_245, NULL, 376, 376, 5, 63},
  {cont__compiler__sim2c_249, &frame__compiler__sim2c_245, 377, 377, 5, 13},
  {entry__compiler__sim2c_268, NULL, 399, 399, 11, 30},
  {cont__compiler__sim2c_269, &frame__compiler__sim2c_268, 399, 399, 11, 30},
  {entry__compiler__sim2c_265, NULL, 398, 398, 15, 32},
  {cont__compiler__sim2c_266, &frame__compiler__sim2c_265, 398, 398, 11, 33},
  {cont__compiler__sim2c_267, &frame__compiler__sim2c_265, 399, 399, 11, 30},
  {cont__compiler__sim2c_270, &frame__compiler__sim2c_265, },
  {entry__compiler__sim2c_262, NULL, 396, 396, 15, 55},
  {cont__compiler__sim2c_263, &frame__compiler__sim2c_262, 396, 396, 11, 56},
  {cont__compiler__sim2c_264, &frame__compiler__sim2c_262, },
  {cont__compiler__sim2c_271, &frame__compiler__sim2c_262, },
  {entry__compiler__sim2c_258, NULL, 395, 395, 24, 49},
  {cont__compiler__sim2c_259, &frame__compiler__sim2c_258, 395, 395, 11, 50},
  {cont__compiler__sim2c_260, &frame__compiler__sim2c_258, 395, 395, 11, 63},
  {cont__compiler__sim2c_261, &frame__compiler__sim2c_258, },
  {cont__compiler__sim2c_272, &frame__compiler__sim2c_258, },
  {entry__compiler__sim2c_274, NULL, 401, 401, 36, 61},
  {cont__compiler__sim2c_275, &frame__compiler__sim2c_274, 401, 401, 28, 62},
  {cont__compiler__sim2c_276, &frame__compiler__sim2c_274, 401, 401, 11, 63},
  {cont__compiler__sim2c_277, &frame__compiler__sim2c_274, 402, 402, 41, 41},
  {entry__compiler__sim2c_253, NULL, 385, 385, 7, 35},
  {cont__compiler__sim2c_254, &frame__compiler__sim2c_253, 386, 386, 7, 31},
  {cont__compiler__sim2c_255, &frame__compiler__sim2c_253, 387, 387, 7, 26},
  {cont__compiler__sim2c_256, &frame__compiler__sim2c_253, 394, 394, 11, 51},
  {cont__compiler__sim2c_257, &frame__compiler__sim2c_253, },
  {cont__compiler__sim2c_273, &frame__compiler__sim2c_253, 392, 402, 7, 42},
  {entry__compiler__sim2c_251, NULL, 384, 384, 8, 28},
  {cont__compiler__sim2c_252, &frame__compiler__sim2c_251, 384, 402, 5, 43},
  {entry__compiler__sim2c_285, NULL, 413, 413, 11, 40},
  {cont__compiler__sim2c_286, &frame__compiler__sim2c_285, 413, 413, 11, 48},
  {cont__compiler__sim2c_287, &frame__compiler__sim2c_285, 413, 413, 11, 48},
  {cont__compiler__sim2c_288, &frame__compiler__sim2c_285, 413, 413, 11, 48},
  {entry__compiler__sim2c_290, NULL, 415, 415, 28, 53},
  {cont__compiler__sim2c_291, &frame__compiler__sim2c_290, 415, 415, 28, 63},
  {cont__compiler__sim2c_292, &frame__compiler__sim2c_290, 415, 415, 11, 64},
  {cont__compiler__sim2c_293, &frame__compiler__sim2c_290, 415, 415, 74, 74},
  {entry__compiler__sim2c_281, NULL, 409, 409, 20, 37},
  {cont__compiler__sim2c_282, &frame__compiler__sim2c_281, 409, 409, 7, 40},
  {cont__compiler__sim2c_283, &frame__compiler__sim2c_281, 412, 412, 11, 51},
  {cont__compiler__sim2c_284, &frame__compiler__sim2c_281, 411, 413, 9, 48},
  {cont__compiler__sim2c_289, &frame__compiler__sim2c_281, 410, 415, 7, 75},
  {entry__compiler__sim2c_279, NULL, 408, 408, 8, 28},
  {cont__compiler__sim2c_280, &frame__compiler__sim2c_279, 408, 415, 5, 76},
  {entry__compiler__sim2c_297, NULL, 420, 420, 32, 57},
  {cont__compiler__sim2c_298, &frame__compiler__sim2c_297, 420, 420, 32, 57},
  {entry__compiler__sim2c_304, NULL, 430, 430, 22, 52},
  {cont__compiler__sim2c_305, &frame__compiler__sim2c_304, 430, 430, 52, 52},
  {entry__compiler__sim2c_300, NULL, 426, 426, 7, 29},
  {cont__compiler__sim2c_301, &frame__compiler__sim2c_300, 427, 427, 7, 37},
  {cont__compiler__sim2c_302, &frame__compiler__sim2c_300, 428, 428, 7, 39},
  {cont__compiler__sim2c_303, &frame__compiler__sim2c_300, 430, 430, 7, 52},
  {cont__compiler__sim2c_306, &frame__compiler__sim2c_300, 431, 431, 7, 31},
  {cont__compiler__sim2c_307, &frame__compiler__sim2c_300, },
  {entry__compiler__sim2c_295, NULL, 420, 420, 12, 27},
  {cont__compiler__sim2c_296, &frame__compiler__sim2c_295, 420, 420, 12, 57},
  {cont__compiler__sim2c_299, &frame__compiler__sim2c_295, 420, 431, 5, 31},
  {entry__compiler__sim2c_310, NULL, 432, 432, 72, 77},
  {entry__compiler__sim2c_309, NULL, 432, 432, 40, 77},
  {entry__compiler__sim2c_312, NULL, 434, 434, 54, 65},
  {cont__compiler__sim2c_313, &frame__compiler__sim2c_312, 434, 434, 22, 65},
  {entry__compiler__sim2c_320, NULL, 442, 442, 47, 57},
  {cont__compiler__sim2c_321, &frame__compiler__sim2c_320, 442, 442, 59, 76},
  {cont__compiler__sim2c_322, &frame__compiler__sim2c_320, 442, 442, 42, 77},
  {cont__compiler__sim2c_323, &frame__compiler__sim2c_320, 441, 442, 15, 78},
  {entry__compiler__sim2c_324, NULL, 444, 444, 15, 36},
  {entry__compiler__sim2c_318, NULL, 440, 440, 13, 35},
  {cont__compiler__sim2c_319, &frame__compiler__sim2c_318, 439, 444, 11, 37},
  {entry__compiler__sim2c_317, NULL, 438, 444, 9, 38},
  {entry__compiler__sim2c_327, NULL, 447, 447, 38, 54},
  {entry__compiler__sim2c_316, NULL, 436, 446, 5, 16},
  {cont__compiler__sim2c_326, &frame__compiler__sim2c_316, 447, 447, 5, 54},
  {cont__compiler__sim2c_328, &frame__compiler__sim2c_316, 448, 448, 5, 13},
  {entry__compiler__sim2c_331, NULL, 471, 471, 46, 67},
  {entry__compiler__sim2c_330, NULL, 471, 471, 5, 67},
  {entry__compiler__sim2c_333, NULL, 472, 472, 51, 62},
  {cont__compiler__sim2c_334, &frame__compiler__sim2c_333, 472, 472, 22, 62},
  {entry__compiler__sim2c_340, NULL, 557, 557, 20, 53},
  {cont__compiler__sim2c_341, &frame__compiler__sim2c_340, 557, 557, 53, 53},
  {entry__compiler__sim2c_338, NULL, 556, 556, 5, 22},
  {cont__compiler__sim2c_339, &frame__compiler__sim2c_338, 557, 557, 5, 53},
  {cont__compiler__sim2c_342, &frame__compiler__sim2c_338, 557, 557, 53, 53},
  {entry__compiler__sim2c_345, NULL, 561, 561, 20, 65},
  {cont__compiler__sim2c_346, &frame__compiler__sim2c_345, 561, 561, 65, 65},
  {entry__compiler__sim2c_343, NULL, 560, 560, 5, 22},
  {cont__compiler__sim2c_344, &frame__compiler__sim2c_343, 561, 561, 5, 65},
  {cont__compiler__sim2c_347, &frame__compiler__sim2c_343, 561, 561, 65, 65},
  {entry__compiler__sim2c_350, NULL, 565, 565, 20, 72},
  {cont__compiler__sim2c_351, &frame__compiler__sim2c_350, 565, 565, 72, 72},
  {entry__compiler__sim2c_348, NULL, 564, 564, 5, 22},
  {cont__compiler__sim2c_349, &frame__compiler__sim2c_348, 565, 565, 5, 72},
  {cont__compiler__sim2c_352, &frame__compiler__sim2c_348, 565, 565, 72, 72},
  {entry__compiler__sim2c_355, NULL, 569, 569, 20, 69},
  {cont__compiler__sim2c_356, &frame__compiler__sim2c_355, 569, 569, 69, 69},
  {entry__compiler__sim2c_353, NULL, 568, 568, 5, 22},
  {cont__compiler__sim2c_354, &frame__compiler__sim2c_353, 569, 569, 5, 69},
  {cont__compiler__sim2c_357, &frame__compiler__sim2c_353, 569, 569, 69, 69},
  {entry__compiler__sim2c_360, NULL, 573, 573, 20, 59},
  {cont__compiler__sim2c_361, &frame__compiler__sim2c_360, 573, 573, 59, 59},
  {entry__compiler__sim2c_358, NULL, 572, 572, 5, 22},
  {cont__compiler__sim2c_359, &frame__compiler__sim2c_358, 573, 573, 5, 59},
  {cont__compiler__sim2c_362, &frame__compiler__sim2c_358, 573, 573, 59, 59},
  {entry__compiler__sim2c_365, NULL, 577, 577, 20, 67},
  {cont__compiler__sim2c_366, &frame__compiler__sim2c_365, 577, 577, 67, 67},
  {entry__compiler__sim2c_363, NULL, 576, 576, 5, 22},
  {cont__compiler__sim2c_364, &frame__compiler__sim2c_363, 577, 577, 5, 67},
  {cont__compiler__sim2c_367, &frame__compiler__sim2c_363, 577, 577, 67, 67},
  {entry__compiler__sim2c_370, NULL, 581, 581, 20, 50},
  {cont__compiler__sim2c_371, &frame__compiler__sim2c_370, 581, 581, 50, 50},
  {entry__compiler__sim2c_368, NULL, 580, 580, 5, 22},
  {cont__compiler__sim2c_369, &frame__compiler__sim2c_368, 581, 581, 5, 50},
  {cont__compiler__sim2c_372, &frame__compiler__sim2c_368, 581, 581, 50, 50},
  {entry__compiler__sim2c_375, NULL, 585, 585, 20, 48},
  {cont__compiler__sim2c_376, &frame__compiler__sim2c_375, 585, 585, 48, 48},
  {entry__compiler__sim2c_373, NULL, 584, 584, 5, 22},
  {cont__compiler__sim2c_374, &frame__compiler__sim2c_373, 585, 585, 5, 48},
  {cont__compiler__sim2c_377, &frame__compiler__sim2c_373, 585, 585, 48, 48},
  {entry__compiler__sim2c_380, NULL, 589, 589, 20, 48},
  {cont__compiler__sim2c_381, &frame__compiler__sim2c_380, 589, 589, 48, 48},
  {entry__compiler__sim2c_378, NULL, 588, 588, 5, 22},
  {cont__compiler__sim2c_379, &frame__compiler__sim2c_378, 589, 589, 5, 48},
  {cont__compiler__sim2c_382, &frame__compiler__sim2c_378, 589, 589, 48, 48},
  {entry__compiler__sim2c_385, NULL, 593, 593, 20, 48},
  {cont__compiler__sim2c_386, &frame__compiler__sim2c_385, 593, 593, 48, 48},
  {entry__compiler__sim2c_383, NULL, 592, 592, 5, 22},
  {cont__compiler__sim2c_384, &frame__compiler__sim2c_383, 593, 593, 5, 48},
  {cont__compiler__sim2c_387, &frame__compiler__sim2c_383, 593, 593, 48, 48},
  {entry__compiler__sim2c_390, NULL, 597, 597, 20, 48},
  {cont__compiler__sim2c_391, &frame__compiler__sim2c_390, 597, 597, 48, 48},
  {entry__compiler__sim2c_388, NULL, 596, 596, 5, 22},
  {cont__compiler__sim2c_389, &frame__compiler__sim2c_388, 597, 597, 5, 48},
  {cont__compiler__sim2c_392, &frame__compiler__sim2c_388, 597, 597, 48, 48},
  {entry__compiler__sim2c_395, NULL, 601, 601, 20, 48},
  {cont__compiler__sim2c_396, &frame__compiler__sim2c_395, 601, 601, 48, 48},
  {entry__compiler__sim2c_393, NULL, 600, 600, 5, 22},
  {cont__compiler__sim2c_394, &frame__compiler__sim2c_393, 601, 601, 5, 48},
  {cont__compiler__sim2c_397, &frame__compiler__sim2c_393, 601, 601, 48, 48},
  {entry__compiler__sim2c_400, NULL, 605, 605, 20, 48},
  {cont__compiler__sim2c_401, &frame__compiler__sim2c_400, 605, 605, 48, 48},
  {entry__compiler__sim2c_398, NULL, 604, 604, 5, 22},
  {cont__compiler__sim2c_399, &frame__compiler__sim2c_398, 605, 605, 5, 48},
  {cont__compiler__sim2c_402, &frame__compiler__sim2c_398, 605, 605, 48, 48},
  {entry__compiler__sim2c_404, NULL, 608, 608, 20, 39},
  {cont__compiler__sim2c_405, &frame__compiler__sim2c_404, 608, 608, 47, 47},
  {entry__compiler__sim2c_403, NULL, 608, 608, 5, 47},
  {cont__compiler__sim2c_406, &frame__compiler__sim2c_403, 608, 608, 47, 47},
  {entry__compiler__sim2c_409, NULL, 612, 612, 20, 52},
  {cont__compiler__sim2c_410, &frame__compiler__sim2c_409, 612, 612, 52, 52},
  {entry__compiler__sim2c_407, NULL, 611, 611, 5, 22},
  {cont__compiler__sim2c_408, &frame__compiler__sim2c_407, 612, 612, 5, 52},
  {cont__compiler__sim2c_411, &frame__compiler__sim2c_407, 612, 612, 52, 52},
  {entry__compiler__sim2c_414, NULL, 616, 616, 20, 49},
  {cont__compiler__sim2c_415, &frame__compiler__sim2c_414, 616, 616, 49, 49},
  {entry__compiler__sim2c_412, NULL, 615, 615, 5, 22},
  {cont__compiler__sim2c_413, &frame__compiler__sim2c_412, 616, 616, 5, 49},
  {cont__compiler__sim2c_416, &frame__compiler__sim2c_412, 616, 616, 49, 49},
  {entry__compiler__sim2c_420, NULL, 620, 620, 28, 28},
  {cont__compiler__sim2c_421, &frame__compiler__sim2c_420, 620, 620, 7, 29},
  {cont__compiler__sim2c_422, &frame__compiler__sim2c_420, 621, 621, 7, 68},
  {entry__compiler__sim2c_417, NULL, 619, 619, 8, 33},
  {cont__compiler__sim2c_419, &frame__compiler__sim2c_417, 619, 621, 5, 68},
  {entry__compiler__sim2c_432, NULL, 630, 630, 27, 51},
  {cont__compiler__sim2c_433, &frame__compiler__sim2c_432, 630, 630, 27, 61},
  {cont__compiler__sim2c_434, &frame__compiler__sim2c_432, 630, 630, 11, 62},
  {cont__compiler__sim2c_435, &frame__compiler__sim2c_432, 630, 630, 67, 67},
  {entry__compiler__sim2c_428, NULL, 628, 628, 9, 38},
  {cont__compiler__sim2c_429, &frame__compiler__sim2c_428, 629, 629, 16, 44},
  {cont__compiler__sim2c_430, &frame__compiler__sim2c_428, 629, 629, 16, 52},
  {cont__compiler__sim2c_431, &frame__compiler__sim2c_428, 629, 630, 9, 67},
  {entry__compiler__sim2c_426, NULL, 627, 627, 10, 39},
  {cont__compiler__sim2c_427, &frame__compiler__sim2c_426, 627, 630, 7, 68},
  {entry__compiler__sim2c_425, NULL, 626, 630, 5, 69},
  {entry__compiler__sim2c_441, NULL, 639, 639, 11, 43},
  {cont__compiler__sim2c_442, &frame__compiler__sim2c_441, 640, 640, 11, 40},
  {cont__compiler__sim2c_443, &frame__compiler__sim2c_441, 640, 640, 40, 40},
  {entry__compiler__sim2c_446, NULL, 643, 643, 13, 36},
  {entry__compiler__sim2c_452, NULL, 648, 648, 15, 31},
  {cont__compiler__sim2c_453, &frame__compiler__sim2c_452, 649, 649, 28, 53},
  {cont__compiler__sim2c_454, &frame__compiler__sim2c_452, 649, 649, 15, 53},
  {cont__compiler__sim2c_455, &frame__compiler__sim2c_452, 649, 649, 53, 53},
  {entry__compiler__sim2c_459, NULL, 652, 652, 36, 76},
  {cont__compiler__sim2c_460, &frame__compiler__sim2c_459, 652, 652, 36, 76},
  {entry__compiler__sim2c_462, NULL, 653, 653, 56, 73},
  {cont__compiler__sim2c_463, &frame__compiler__sim2c_462, 653, 653, 17, 73},
  {entry__compiler__sim2c_466, NULL, 657, 657, 21, 54},
  {entry__compiler__sim2c_470, NULL, 661, 661, 25, 55},
  {entry__compiler__sim2c_471, NULL, 663, 663, 25, 62},
  {entry__compiler__sim2c_467, NULL, 660, 660, 23, 46},
  {cont__compiler__sim2c_468, &frame__compiler__sim2c_467, 660, 660, 23, 57},
  {cont__compiler__sim2c_469, &frame__compiler__sim2c_467, 659, 663, 21, 63},
  {entry__compiler__sim2c_476, NULL, 669, 669, 41, 59},
  {cont__compiler__sim2c_477, &frame__compiler__sim2c_476, 669, 669, 25, 60},
  {cont__compiler__sim2c_478, &frame__compiler__sim2c_476, 669, 669, 25, 73},
  {cont__compiler__sim2c_479, &frame__compiler__sim2c_476, 669, 669, 25, 73},
  {entry__compiler__sim2c_485, NULL, 676, 676, 42, 66},
  {cont__compiler__sim2c_486, &frame__compiler__sim2c_485, 676, 676, 29, 67},
  {cont__compiler__sim2c_487, &frame__compiler__sim2c_485, 676, 676, 29, 78},
  {cont__compiler__sim2c_488, &frame__compiler__sim2c_485, 676, 676, 29, 78},
  {entry__compiler__sim2c_481, NULL, 675, 675, 29, 53},
  {cont__compiler__sim2c_482, &frame__compiler__sim2c_481, 675, 675, 29, 63},
  {cont__compiler__sim2c_483, &frame__compiler__sim2c_481, 675, 675, 29, 78},
  {cont__compiler__sim2c_484, &frame__compiler__sim2c_481, 674, 676, 27, 78},
  {cont__compiler__sim2c_489, &frame__compiler__sim2c_481, 671, 676, 25, 79},
  {entry__compiler__sim2c_492, NULL, 678, 678, 53, 63},
  {cont__compiler__sim2c_493, &frame__compiler__sim2c_492, 678, 678, 46, 63},
  {entry__compiler__sim2c_490, NULL, 678, 678, 28, 43},
  {cont__compiler__sim2c_491, &frame__compiler__sim2c_490, 678, 678, 25, 63},
  {entry__compiler__sim2c_472, NULL, 665, 665, 21, 57},
  {cont__compiler__sim2c_473, &frame__compiler__sim2c_472, 668, 668, 25, 48},
  {cont__compiler__sim2c_474, &frame__compiler__sim2c_472, 668, 668, 25, 59},
  {cont__compiler__sim2c_475, &frame__compiler__sim2c_472, 667, 669, 23, 73},
  {cont__compiler__sim2c_480, &frame__compiler__sim2c_472, 666, 678, 21, 64},
  {entry__compiler__sim2c_464, NULL, 655, 655, 22, 50},
  {cont__compiler__sim2c_465, &frame__compiler__sim2c_464, 655, 678, 17, 66},
  {entry__compiler__sim2c_447, NULL, 645, 645, 36, 60},
  {cont__compiler__sim2c_448, &frame__compiler__sim2c_447, 645, 645, 13, 61},
  {cont__compiler__sim2c_449, &frame__compiler__sim2c_447, 646, 646, 13, 47},
  {cont__compiler__sim2c_450, &frame__compiler__sim2c_447, 647, 647, 16, 35},
  {cont__compiler__sim2c_451, &frame__compiler__sim2c_447, 647, 649, 13, 53},
  {cont__compiler__sim2c_456, &frame__compiler__sim2c_447, 650, 650, 13, 47},
  {cont__compiler__sim2c_457, &frame__compiler__sim2c_447, 652, 652, 15, 31},
  {cont__compiler__sim2c_458, &frame__compiler__sim2c_447, 652, 652, 15, 76},
  {cont__compiler__sim2c_461, &frame__compiler__sim2c_447, 651, 678, 13, 68},
  {cont__compiler__sim2c_494, &frame__compiler__sim2c_447, 678, 678, 68, 68},
  {entry__compiler__sim2c_439, NULL, 638, 638, 12, 41},
  {cont__compiler__sim2c_440, &frame__compiler__sim2c_439, 638, 640, 9, 40},
  {cont__compiler__sim2c_444, &frame__compiler__sim2c_439, 642, 642, 11, 30},
  {cont__compiler__sim2c_445, &frame__compiler__sim2c_439, 641, 678, 9, 70},
  {entry__compiler__sim2c_438, NULL, 636, 678, 7, 71},
  {entry__compiler__sim2c_498, NULL, 679, 679, 28, 67},
  {entry__compiler__sim2c_500, NULL, 680, 680, 20, 46},
  {cont__compiler__sim2c_501, &frame__compiler__sim2c_500, 680, 680, 46, 46},
  {entry__compiler__sim2c_437, NULL, 635, 678, 5, 72},
  {cont__compiler__sim2c_495, &frame__compiler__sim2c_437, 679, 679, 8, 25},
  {cont__compiler__sim2c_496, &frame__compiler__sim2c_437, 679, 679, 8, 25},
  {cont__compiler__sim2c_497, &frame__compiler__sim2c_437, 679, 679, 5, 67},
  {cont__compiler__sim2c_499, &frame__compiler__sim2c_437, 680, 680, 5, 46},
  {cont__compiler__sim2c_502, &frame__compiler__sim2c_437, 681, 681, 5, 29},
  {cont__compiler__sim2c_503, &frame__compiler__sim2c_437, },
  {entry__compiler__sim2c_513, NULL, 692, 692, 21, 74},
  {cont__compiler__sim2c_516, &frame__compiler__sim2c_513, 692, 692, 13, 74},
  {entry__compiler__sim2c_509, NULL, 690, 690, 11, 41},
  {cont__compiler__sim2c_511, &frame__compiler__sim2c_509, 691, 691, 14, 29},
  {cont__compiler__sim2c_512, &frame__compiler__sim2c_509, 691, 692, 11, 74},
  {entry__compiler__sim2c_517, NULL, 694, 694, 39, 70},
  {cont__compiler__sim2c_520, &frame__compiler__sim2c_517, 694, 694, 11, 70},
  {cont__compiler__sim2c_521, &frame__compiler__sim2c_517, 695, 705, 17, 66},
  {cont__compiler__sim2c_524, &frame__compiler__sim2c_517, 695, 705, 11, 66},
  {entry__compiler__sim2c_526, NULL, 707, 707, 9, 35},
  {cont__compiler__sim2c_527, &frame__compiler__sim2c_526, 709, 709, 29, 49},
  {cont__compiler__sim2c_528, &frame__compiler__sim2c_526, 710, 710, 42, 62},
  {cont__compiler__sim2c_529, &frame__compiler__sim2c_526, 708, 711, 15, 11},
  {cont__compiler__sim2c_533, &frame__compiler__sim2c_526, 708, 711, 9, 11},
  {cont__compiler__sim2c_534, &frame__compiler__sim2c_526, 712, 712, 37, 57},
  {cont__compiler__sim2c_535, &frame__compiler__sim2c_526, 712, 712, 9, 59},
  {cont__compiler__sim2c_537, &frame__compiler__sim2c_526, 713, 713, 9, 38},
  {entry__compiler__sim2c_508, NULL, 688, 705, 7, 68},
  {cont__compiler__sim2c_525, &frame__compiler__sim2c_508, 706, 713, 7, 38},
  {entry__compiler__sim2c_539, NULL, 714, 714, 20, 46},
  {cont__compiler__sim2c_540, &frame__compiler__sim2c_539, 714, 714, 46, 46},
  {entry__compiler__sim2c_507, NULL, 687, 713, 5, 39},
  {cont__compiler__sim2c_538, &frame__compiler__sim2c_507, 714, 714, 5, 46},
  {cont__compiler__sim2c_541, &frame__compiler__sim2c_507, 715, 715, 5, 29},
  {cont__compiler__sim2c_542, &frame__compiler__sim2c_507, },
  {entry__compiler__sim2c_549, NULL, 722, 722, 50, 72},
  {entry__compiler__sim2c_548, NULL, 722, 722, 27, 72},
  {entry__compiler__sim2c_553, NULL, 723, 723, 28, 67},
  {entry__compiler__sim2c_555, NULL, 724, 724, 20, 46},
  {cont__compiler__sim2c_556, &frame__compiler__sim2c_555, 724, 724, 46, 46},
  {entry__compiler__sim2c_545, NULL, 720, 720, 35, 52},
  {cont__compiler__sim2c_546, &frame__compiler__sim2c_545, 720, 720, 5, 53},
  {cont__compiler__sim2c_547, &frame__compiler__sim2c_545, 722, 722, 5, 72},
  {cont__compiler__sim2c_550, &frame__compiler__sim2c_545, 723, 723, 8, 25},
  {cont__compiler__sim2c_551, &frame__compiler__sim2c_545, 723, 723, 8, 25},
  {cont__compiler__sim2c_552, &frame__compiler__sim2c_545, 723, 723, 5, 67},
  {cont__compiler__sim2c_554, &frame__compiler__sim2c_545, 724, 724, 5, 46},
  {cont__compiler__sim2c_557, &frame__compiler__sim2c_545, 725, 725, 5, 29},
  {cont__compiler__sim2c_558, &frame__compiler__sim2c_545, },
  {entry__compiler__sim2c_562, NULL, 731, 733, 11, 13},
  {entry__compiler__sim2c_564, NULL, 735, 739, 11, 13},
  {entry__compiler__sim2c_561, NULL, 729, 739, 7, 15},
  {cont__compiler__sim2c_566, &frame__compiler__sim2c_561, 740, 740, 7, 22},
  {entry__compiler__sim2c_568, NULL, 741, 741, 20, 46},
  {cont__compiler__sim2c_569, &frame__compiler__sim2c_568, 741, 741, 46, 46},
  {entry__compiler__sim2c_560, NULL, 728, 740, 5, 22},
  {cont__compiler__sim2c_567, &frame__compiler__sim2c_560, 741, 741, 5, 46},
  {cont__compiler__sim2c_570, &frame__compiler__sim2c_560, 742, 742, 5, 29},
  {cont__compiler__sim2c_571, &frame__compiler__sim2c_560, },
  {entry__compiler__sim2c_574, NULL, 743, 743, 72, 77},
  {entry__compiler__sim2c_573, NULL, 743, 743, 40, 77},
  {entry__compiler__sim2c_576, NULL, 744, 744, 51, 71},
  {cont__compiler__sim2c_578, &frame__compiler__sim2c_576, 744, 744, 43, 71},
  {entry__compiler__sim2c_580, NULL, 745, 745, 45, 62},
  {cont__compiler__sim2c_582, &frame__compiler__sim2c_580, 745, 745, 37, 62},
  {entry__compiler__sim2c_584, NULL, 746, 746, 47, 68},
  {cont__compiler__sim2c_586, &frame__compiler__sim2c_584, 746, 746, 39, 68},
  {entry__compiler__sim2c_592, NULL, 750, 750, 5, 31},
  {cont__compiler__sim2c_594, &frame__compiler__sim2c_592, 751, 751, 5, 31},
  {cont__compiler__sim2c_596, &frame__compiler__sim2c_592, 751, 751, 36, 36},
  {entry__compiler__sim2c_598, NULL, 752, 752, 43, 62},
  {cont__compiler__sim2c_601, &frame__compiler__sim2c_598, 752, 752, 35, 62},
  {entry__compiler__sim2c_608, NULL, 773, 808, 5, 12},
  {entry__compiler__sim2c_612, NULL, 809, 809, 40, 65},
  {cont__compiler__sim2c_614, &frame__compiler__sim2c_612, 809, 809, 40, 65},
  {entry__compiler__sim2c_616, NULL, 810, 811, 5, 35},
  {entry__compiler__sim2c_624, NULL, 859, 859, 15, 45},
  {cont__compiler__sim2c_627, &frame__compiler__sim2c_624, 859, 859, 7, 45},
  {entry__compiler__sim2c_634, NULL, 862, 862, 15, 64},
  {cont__compiler__sim2c_636, &frame__compiler__sim2c_634, 862, 862, 7, 64},
  {entry__compiler__sim2c_640, NULL, 864, 864, 15, 48},
  {cont__compiler__sim2c_642, &frame__compiler__sim2c_640, 864, 864, 7, 48},
  {entry__compiler__sim2c_646, NULL, 866, 866, 15, 51},
  {cont__compiler__sim2c_648, &frame__compiler__sim2c_646, 866, 866, 7, 51},
  {entry__compiler__sim2c_621, NULL, 858, 858, 8, 29},
  {cont__compiler__sim2c_622, &frame__compiler__sim2c_621, 858, 858, 8, 44},
  {cont__compiler__sim2c_623, &frame__compiler__sim2c_621, 858, 859, 5, 45},
  {cont__compiler__sim2c_628, &frame__compiler__sim2c_621, 860, 860, 13, 46},
  {cont__compiler__sim2c_630, &frame__compiler__sim2c_621, 860, 860, 5, 46},
  {cont__compiler__sim2c_631, &frame__compiler__sim2c_621, 861, 861, 8, 29},
  {cont__compiler__sim2c_632, &frame__compiler__sim2c_621, 861, 861, 8, 46},
  {cont__compiler__sim2c_633, &frame__compiler__sim2c_621, 861, 862, 5, 64},
  {cont__compiler__sim2c_637, &frame__compiler__sim2c_621, 863, 863, 10, 31},
  {cont__compiler__sim2c_638, &frame__compiler__sim2c_621, 863, 863, 33, 59},
  {cont__compiler__sim2c_639, &frame__compiler__sim2c_621, 863, 864, 5, 48},
  {cont__compiler__sim2c_643, &frame__compiler__sim2c_621, 865, 865, 10, 31},
  {cont__compiler__sim2c_644, &frame__compiler__sim2c_621, 865, 865, 33, 61},
  {cont__compiler__sim2c_645, &frame__compiler__sim2c_621, 865, 866, 5, 51},
  {entry__compiler__sim2c_660, NULL, 876, 876, 57, 57},
  {cont__compiler__sim2c_661, &frame__compiler__sim2c_660, 876, 876, 13, 58},
  {cont__compiler__sim2c_662, &frame__compiler__sim2c_660, 876, 876, 5, 58},
  {entry__compiler__sim2c_667, NULL, 888, 888, 7, 45},
  {entry__compiler__sim2c_669, NULL, 890, 890, 15, 47},
  {cont__compiler__sim2c_672, &frame__compiler__sim2c_669, 890, 890, 7, 47},
  {entry__compiler__sim2c_679, NULL, 896, 896, 51, 51},
  {cont__compiler__sim2c_680, &frame__compiler__sim2c_679, 896, 896, 13, 52},
  {cont__compiler__sim2c_681, &frame__compiler__sim2c_679, 896, 896, 5, 52},
  {entry__compiler__sim2c_688, NULL, 910, 910, 26, 43},
  {cont__compiler__sim2c_689, &frame__compiler__sim2c_688, 910, 910, 13, 50},
  {cont__compiler__sim2c_693, &frame__compiler__sim2c_688, 910, 910, 7, 50},
  {entry__compiler__sim2c_687, NULL, 909, 910, 5, 50},
  {entry__compiler__sim2c_697, NULL, 913, 913, 49, 75},
  {cont__compiler__sim2c_699, &frame__compiler__sim2c_697, 913, 913, 43, 75},
  {entry__compiler__sim2c_703, NULL, 917, 917, 42, 69},
  {cont__compiler__sim2c_706, &frame__compiler__sim2c_703, 917, 917, 36, 69},
  {entry__compiler__sim2c_713, NULL, 935, 935, 38, 44},
  {cont__compiler__sim2c_714, &frame__compiler__sim2c_713, 935, 935, 38, 45},
  {cont__compiler__sim2c_715, &frame__compiler__sim2c_713, 935, 935, 7, 45},
  {cont__compiler__sim2c_716, &frame__compiler__sim2c_713, 936, 937, 13, 43},
  {cont__compiler__sim2c_719, &frame__compiler__sim2c_713, 936, 937, 7, 43},
  {entry__compiler__sim2c_720, NULL, 939, 939, 7, 16},
  {entry__compiler__sim2c_725, NULL, 949, 949, 5, 32},
  {cont__compiler__sim2c_726, &frame__compiler__sim2c_725, 950, 958, 11, 38},
  {cont__compiler__sim2c_735, &frame__compiler__sim2c_725, 950, 958, 5, 38},
  {entry__compiler__sim2c_746, NULL, 967, 975, 7, 10},
  {entry__compiler__sim2c_748, NULL, 977, 983, 13, 39},
  {cont__compiler__sim2c_751, &frame__compiler__sim2c_748, 977, 983, 7, 39},
  {entry__compiler__sim2c_753, NULL, 985, 985, 5, 39},
  {cont__compiler__sim2c_754, &frame__compiler__sim2c_753, 986, 986, 13, 43},
  {cont__compiler__sim2c_757, &frame__compiler__sim2c_753, 986, 986, 5, 43},
  {entry__compiler__sim2c_761, NULL, 991, 993, 11, 43},
  {cont__compiler__sim2c_764, &frame__compiler__sim2c_761, 991, 993, 5, 43},
  {entry__compiler__sim2c_767, NULL, 997, 1000, 7, 37},
  {entry__compiler__sim2c_769, NULL, 1002, 1009, 13, 39},
  {cont__compiler__sim2c_772, &frame__compiler__sim2c_769, 1002, 1009, 7, 39},
  {entry__compiler__sim2c_774, NULL, 1011, 1011, 27, 47},
  {cont__compiler__sim2c_775, &frame__compiler__sim2c_774, 1011, 1011, 13, 52},
  {cont__compiler__sim2c_777, &frame__compiler__sim2c_774, 1011, 1011, 5, 52},
  {entry__compiler__sim2c_795, NULL, 1021, 1021, 60, 75},
  {cont__compiler__sim2c_796, &frame__compiler__sim2c_795, 1021, 1021, 43, 75},
  {cont__compiler__sim2c_797, &frame__compiler__sim2c_795, 1021, 1021, 43, 75},
  {entry__compiler__sim2c_799, NULL, 1022, 1022, 19, 46},
  {cont__compiler__sim2c_801, &frame__compiler__sim2c_799, 1022, 1022, 13, 46},
  {entry__compiler__sim2c_807, NULL, 1027, 1028, 23, 43},
  {cont__compiler__sim2c_810, &frame__compiler__sim2c_807, 1027, 1028, 17, 43},
  {entry__compiler__sim2c_804, NULL, 1026, 1026, 18, 38},
  {cont__compiler__sim2c_805, &frame__compiler__sim2c_804, 1026, 1026, 18, 38},
  {cont__compiler__sim2c_806, &frame__compiler__sim2c_804, 1026, 1028, 15, 44},
  {entry__compiler__sim2c_814, NULL, 1030, 1031, 23, 45},
  {cont__compiler__sim2c_817, &frame__compiler__sim2c_814, 1030, 1031, 17, 45},
  {entry__compiler__sim2c_811, NULL, 1029, 1029, 18, 46},
  {cont__compiler__sim2c_812, &frame__compiler__sim2c_811, 1029, 1029, 18, 46},
  {cont__compiler__sim2c_813, &frame__compiler__sim2c_811, 1029, 1031, 15, 46},
  {entry__compiler__sim2c_818, NULL, 1033, 1034, 23, 48},
  {cont__compiler__sim2c_820, &frame__compiler__sim2c_818, 1033, 1034, 17, 48},
  {entry__compiler__sim2c_802, NULL, 1024, 1024, 13, 37},
  {cont__compiler__sim2c_803, &frame__compiler__sim2c_802, 1025, 1034, 13, 50},
  {entry__compiler__sim2c_788, NULL, 1019, 1019, 28, 50},
  {cont__compiler__sim2c_789, &frame__compiler__sim2c_788, 1019, 1019, 52, 64},
  {cont__compiler__sim2c_790, &frame__compiler__sim2c_788, 1019, 1019, 9, 65},
  {cont__compiler__sim2c_791, &frame__compiler__sim2c_788, 1021, 1021, 15, 37},
  {cont__compiler__sim2c_793, &frame__compiler__sim2c_788, 1021, 1021, 11, 38},
  {cont__compiler__sim2c_794, &frame__compiler__sim2c_788, 1021, 1021, 11, 75},
  {cont__compiler__sim2c_798, &frame__compiler__sim2c_788, 1020, 1034, 9, 52},
  {entry__compiler__sim2c_786, NULL, 1018, 1018, 10, 37},
  {cont__compiler__sim2c_787, &frame__compiler__sim2c_786, 1018, 1034, 7, 53},
  {entry__compiler__sim2c_823, NULL, 1036, 1036, 33, 55},
  {cont__compiler__sim2c_824, &frame__compiler__sim2c_823, 1036, 1036, 33, 66},
  {cont__compiler__sim2c_825, &frame__compiler__sim2c_823, 1036, 1036, 17, 70},
  {cont__compiler__sim2c_827, &frame__compiler__sim2c_823, 1036, 1036, 9, 70},
  {entry__compiler__sim2c_821, NULL, 1035, 1035, 10, 39},
  {cont__compiler__sim2c_822, &frame__compiler__sim2c_821, 1035, 1036, 7, 70},
  {entry__compiler__sim2c_782, NULL, 1016, 1016, 11, 24},
  {cont__compiler__sim2c_784, &frame__compiler__sim2c_782, 1016, 1016, 5, 24},
  {cont__compiler__sim2c_785, &frame__compiler__sim2c_782, 1017, 1036, 5, 71},
  {entry__compiler__sim2c_830, NULL, 1040, 1046, 7, 30},
  {entry__compiler__sim2c_832, NULL, 1048, 1055, 13, 39},
  {cont__compiler__sim2c_835, &frame__compiler__sim2c_832, 1048, 1055, 7, 39},
  {entry__compiler__sim2c_837, NULL, 1057, 1057, 27, 47},
  {cont__compiler__sim2c_838, &frame__compiler__sim2c_837, 1057, 1057, 13, 52},
  {cont__compiler__sim2c_840, &frame__compiler__sim2c_837, 1057, 1057, 5, 52},
  {entry__compiler__sim2c_846, NULL, 1065, 1070, 7, 33},
  {entry__compiler__sim2c_848, NULL, 1072, 1079, 13, 39},
  {cont__compiler__sim2c_851, &frame__compiler__sim2c_848, 1072, 1079, 7, 39},
  {entry__compiler__sim2c_853, NULL, 1081, 1081, 27, 47},
  {cont__compiler__sim2c_854, &frame__compiler__sim2c_853, 1081, 1081, 13, 52},
  {cont__compiler__sim2c_856, &frame__compiler__sim2c_853, 1081, 1081, 5, 52},
  {entry__compiler__sim2c_865, NULL, 1091, 1091, 30, 47},
  {cont__compiler__sim2c_866, &frame__compiler__sim2c_865, 1091, 1091, 14, 57},
  {cont__compiler__sim2c_867, &frame__compiler__sim2c_865, 1091, 1091, 11, 57},
  {entry__compiler__sim2c_868, NULL, 1092, 1092, 11, 19},
  {entry__compiler__sim2c_873, NULL, 1097, 1100, 17, 47},
  {cont__compiler__sim2c_878, &frame__compiler__sim2c_873, 1097, 1100, 11, 47},
  {entry__compiler__sim2c_879, NULL, 1102, 1105, 17, 43},
  {cont__compiler__sim2c_882, &frame__compiler__sim2c_879, 1102, 1105, 11, 43},
  {entry__compiler__sim2c_883, NULL, 1107, 1110, 17, 27},
  {cont__compiler__sim2c_886, &frame__compiler__sim2c_883, 1107, 1110, 11, 27},
  {entry__compiler__sim2c_887, NULL, 1112, 1115, 17, 45},
  {cont__compiler__sim2c_890, &frame__compiler__sim2c_887, 1112, 1115, 11, 45},
  {entry__compiler__sim2c_891, NULL, 1117, 1120, 17, 60},
  {cont__compiler__sim2c_893, &frame__compiler__sim2c_891, 1117, 1120, 11, 60},
  {entry__compiler__sim2c_863, NULL, 1090, 1090, 11, 30},
  {cont__compiler__sim2c_864, &frame__compiler__sim2c_863, 1088, 1092, 7, 20},
  {cont__compiler__sim2c_870, &frame__compiler__sim2c_863, 1094, 1094, 7, 42},
  {cont__compiler__sim2c_871, &frame__compiler__sim2c_863, 1095, 1095, 12, 33},
  {cont__compiler__sim2c_872, &frame__compiler__sim2c_863, 1095, 1120, 7, 62},
  {entry__compiler__sim2c_860, NULL, 1087, 1087, 12, 29},
  {cont__compiler__sim2c_861, &frame__compiler__sim2c_860, 1087, 1087, 12, 40},
  {cont__compiler__sim2c_862, &frame__compiler__sim2c_860, 1087, 1120, 5, 63},
  {entry__compiler__sim2c_896, NULL, 1123, 1125, 5, 31},
  {entry__compiler__sim2c_899, NULL, 1128, 1131, 7, 10},
  {entry__compiler__sim2c_901, NULL, 1133, 1140, 13, 39},
  {cont__compiler__sim2c_904, &frame__compiler__sim2c_901, 1133, 1140, 7, 39},
  {entry__compiler__sim2c_906, NULL, 1142, 1142, 27, 47},
  {cont__compiler__sim2c_907, &frame__compiler__sim2c_906, 1142, 1142, 13, 52},
  {cont__compiler__sim2c_909, &frame__compiler__sim2c_906, 1142, 1142, 5, 52},
  {entry__compiler__sim2c_912, NULL, 1146, 1150, 7, 10},
  {entry__compiler__sim2c_914, NULL, 1152, 1159, 13, 39},
  {cont__compiler__sim2c_917, &frame__compiler__sim2c_914, 1152, 1159, 7, 39},
  {entry__compiler__sim2c_919, NULL, 1161, 1161, 27, 47},
  {cont__compiler__sim2c_920, &frame__compiler__sim2c_919, 1161, 1161, 13, 52},
  {cont__compiler__sim2c_922, &frame__compiler__sim2c_919, 1161, 1161, 5, 52},
  {entry__compiler__sim2c_928, NULL, 1165, 1167, 5, 30},
  {entry__compiler__sim2c_932, NULL, 1169, 1169, 53, 64},
  {cont__compiler__sim2c_933, &frame__compiler__sim2c_932, 1169, 1169, 22, 64},
  {entry__compiler__sim2c, NULL, 244, 244, 3, 41},
  {cont__compiler__sim2c_43, &frame__compiler__sim2c, 245, 245, 35, 71},
  {cont__compiler__sim2c_45, &frame__compiler__sim2c, 245, 245, 3, 72},
  {cont__compiler__sim2c_46, &frame__compiler__sim2c, 252, 284, 3, 61},
  {cont__compiler__sim2c_112, &frame__compiler__sim2c, 285, 285, 3, 70},
  {cont__compiler__sim2c_116, &frame__compiler__sim2c, 286, 286, 3, 61},
  {cont__compiler__sim2c_120, &frame__compiler__sim2c, 287, 297, 3, 13},
  {cont__compiler__sim2c_123, &frame__compiler__sim2c, 298, 299, 3, 71},
  {cont__compiler__sim2c_128, &frame__compiler__sim2c, 300, 302, 3, 26},
  {cont__compiler__sim2c_131, &frame__compiler__sim2c, 303, 303, 3, 63},
  {cont__compiler__sim2c_135, &frame__compiler__sim2c, 304, 310, 3, 45},
  {cont__compiler__sim2c_140, &frame__compiler__sim2c, 311, 311, 3, 64},
  {cont__compiler__sim2c_144, &frame__compiler__sim2c, 314, 318, 3, 21},
  {cont__compiler__sim2c_147, &frame__compiler__sim2c, 320, 320, 6, 30},
  {cont__compiler__sim2c_148, &frame__compiler__sim2c, 320, 320, 6, 41},
  {cont__compiler__sim2c_150, &frame__compiler__sim2c, 320, 322, 3, 58},
  {cont__compiler__sim2c_156, &frame__compiler__sim2c, 323, 323, 3, 30},
  {cont__compiler__sim2c_158, &frame__compiler__sim2c, 324, 324, 6, 29},
  {cont__compiler__sim2c_159, &frame__compiler__sim2c, 324, 324, 3, 59},
  {cont__compiler__sim2c_163, &frame__compiler__sim2c, 325, 325, 3, 29},
  {cont__compiler__sim2c_164, &frame__compiler__sim2c, 326, 367, 3, 46},
  {cont__compiler__sim2c_234, &frame__compiler__sim2c, 368, 373, 3, 58},
  {cont__compiler__sim2c_240, &frame__compiler__sim2c, 374, 374, 3, 63},
  {cont__compiler__sim2c_244, &frame__compiler__sim2c, 375, 377, 3, 13},
  {cont__compiler__sim2c_250, &frame__compiler__sim2c, 383, 402, 3, 44},
  {cont__compiler__sim2c_278, &frame__compiler__sim2c, 407, 415, 3, 77},
  {cont__compiler__sim2c_294, &frame__compiler__sim2c, 419, 431, 3, 32},
  {cont__compiler__sim2c_308, &frame__compiler__sim2c, 432, 432, 3, 77},
  {cont__compiler__sim2c_311, &frame__compiler__sim2c, 434, 434, 3, 65},
  {cont__compiler__sim2c_315, &frame__compiler__sim2c, 435, 448, 3, 13},
  {cont__compiler__sim2c_329, &frame__compiler__sim2c, 470, 471, 3, 67},
  {cont__compiler__sim2c_332, &frame__compiler__sim2c, 472, 472, 3, 62},
  {cont__compiler__sim2c_336, &frame__compiler__sim2c, 473, 473, 3, 28},
  {cont__compiler__sim2c_337, &frame__compiler__sim2c, 623, 623, 3, 49},
  {cont__compiler__sim2c_424, &frame__compiler__sim2c, 625, 630, 3, 70},
  {cont__compiler__sim2c_436, &frame__compiler__sim2c, 631, 681, 3, 29},
  {cont__compiler__sim2c_504, &frame__compiler__sim2c, 682, 682, 3, 48},
  {cont__compiler__sim2c_506, &frame__compiler__sim2c, 684, 715, 3, 29},
  {cont__compiler__sim2c_543, &frame__compiler__sim2c, 716, 716, 3, 39},
  {cont__compiler__sim2c_544, &frame__compiler__sim2c, 717, 725, 3, 29},
  {cont__compiler__sim2c_559, &frame__compiler__sim2c, 726, 742, 3, 29},
  {cont__compiler__sim2c_572, &frame__compiler__sim2c, 743, 743, 3, 77},
  {cont__compiler__sim2c_575, &frame__compiler__sim2c, 744, 744, 3, 71},
  {cont__compiler__sim2c_579, &frame__compiler__sim2c, 745, 745, 3, 62},
  {cont__compiler__sim2c_583, &frame__compiler__sim2c, 746, 746, 3, 68},
  {cont__compiler__sim2c_587, &frame__compiler__sim2c, 747, 747, 10, 34},
  {cont__compiler__sim2c_588, &frame__compiler__sim2c, 747, 747, 3, 42},
  {cont__compiler__sim2c_589, &frame__compiler__sim2c, 748, 748, 3, 39},
  {cont__compiler__sim2c_591, &frame__compiler__sim2c, 749, 751, 3, 36},
  {cont__compiler__sim2c_597, &frame__compiler__sim2c, 752, 752, 3, 62},
  {cont__compiler__sim2c_602, &frame__compiler__sim2c, 753, 753, 10, 32},
  {cont__compiler__sim2c_603, &frame__compiler__sim2c, 753, 753, 3, 40},
  {cont__compiler__sim2c_604, &frame__compiler__sim2c, 754, 771, 3, 18},
  {cont__compiler__sim2c_606, &frame__compiler__sim2c, 772, 772, 10, 35},
  {cont__compiler__sim2c_607, &frame__compiler__sim2c, 772, 808, 3, 13},
  {cont__compiler__sim2c_610, &frame__compiler__sim2c, 809, 809, 10, 35},
  {cont__compiler__sim2c_611, &frame__compiler__sim2c, 809, 809, 10, 65},
  {cont__compiler__sim2c_615, &frame__compiler__sim2c, 809, 811, 3, 36},
  {cont__compiler__sim2c_618, &frame__compiler__sim2c, 812, 856, 3, 10},
  {cont__compiler__sim2c_620, &frame__compiler__sim2c, 857, 866, 3, 52},
  {cont__compiler__sim2c_649, &frame__compiler__sim2c, 867, 868, 3, 19},
  {cont__compiler__sim2c_651, &frame__compiler__sim2c, 869, 869, 3, 49},
  {cont__compiler__sim2c_652, &frame__compiler__sim2c, 870, 870, 3, 46},
  {cont__compiler__sim2c_653, &frame__compiler__sim2c, 871, 872, 3, 10},
  {cont__compiler__sim2c_655, &frame__compiler__sim2c, 873, 874, 3, 38},
  {cont__compiler__sim2c_657, &frame__compiler__sim2c, 875, 875, 6, 45},
  {cont__compiler__sim2c_658, &frame__compiler__sim2c, 875, 875, 6, 45},
  {cont__compiler__sim2c_659, &frame__compiler__sim2c, 875, 876, 3, 58},
  {cont__compiler__sim2c_663, &frame__compiler__sim2c, 877, 877, 3, 16},
  {cont__compiler__sim2c_665, &frame__compiler__sim2c, 878, 878, 3, 30},
  {cont__compiler__sim2c_666, &frame__compiler__sim2c, 886, 890, 3, 48},
  {cont__compiler__sim2c_673, &frame__compiler__sim2c, 891, 893, 3, 52},
  {cont__compiler__sim2c_675, &frame__compiler__sim2c, 894, 894, 3, 75},
  {cont__compiler__sim2c_676, &frame__compiler__sim2c, 895, 895, 6, 39},
  {cont__compiler__sim2c_677, &frame__compiler__sim2c, 895, 895, 6, 39},
  {cont__compiler__sim2c_678, &frame__compiler__sim2c, 895, 896, 3, 52},
  {cont__compiler__sim2c_682, &frame__compiler__sim2c, 897, 899, 3, 6},
  {cont__compiler__sim2c_684, &frame__compiler__sim2c, 900, 907, 3, 24},
  {cont__compiler__sim2c_686, &frame__compiler__sim2c, 908, 910, 3, 51},
  {cont__compiler__sim2c_694, &frame__compiler__sim2c, 911, 911, 3, 16},
  {cont__compiler__sim2c_695, &frame__compiler__sim2c, 912, 912, 3, 27},
  {cont__compiler__sim2c_696, &frame__compiler__sim2c, 913, 913, 3, 75},
  {cont__compiler__sim2c_700, &frame__compiler__sim2c, 914, 916, 3, 44},
  {cont__compiler__sim2c_702, &frame__compiler__sim2c, 917, 917, 3, 69},
  {cont__compiler__sim2c_707, &frame__compiler__sim2c, 918, 931, 9, 10},
  {cont__compiler__sim2c_710, &frame__compiler__sim2c, 918, 931, 3, 10},
  {cont__compiler__sim2c_711, &frame__compiler__sim2c, 932, 932, 3, 44},
  {cont__compiler__sim2c_712, &frame__compiler__sim2c, 933, 939, 3, 17},
  {cont__compiler__sim2c_722, &frame__compiler__sim2c, 940, 947, 3, 6},
  {cont__compiler__sim2c_724, &frame__compiler__sim2c, 948, 958, 3, 39},
  {cont__compiler__sim2c_736, &frame__compiler__sim2c, 959, 959, 3, 22},
  {cont__compiler__sim2c_737, &frame__compiler__sim2c, 960, 960, 3, 26},
  {cont__compiler__sim2c_738, &frame__compiler__sim2c, 961, 962, 9, 47},
  {cont__compiler__sim2c_741, &frame__compiler__sim2c, 961, 962, 3, 47},
  {cont__compiler__sim2c_742, &frame__compiler__sim2c, 963, 963, 3, 29},
  {cont__compiler__sim2c_743, &frame__compiler__sim2c, 964, 964, 3, 15},
  {cont__compiler__sim2c_745, &frame__compiler__sim2c, 965, 983, 3, 41},
  {cont__compiler__sim2c_752, &frame__compiler__sim2c, 984, 986, 3, 43},
  {cont__compiler__sim2c_758, &frame__compiler__sim2c, 987, 989, 3, 43},
  {cont__compiler__sim2c_760, &frame__compiler__sim2c, 990, 993, 3, 44},
  {cont__compiler__sim2c_765, &frame__compiler__sim2c, 994, 994, 3, 25},
  {cont__compiler__sim2c_766, &frame__compiler__sim2c, 995, 1009, 3, 41},
  {cont__compiler__sim2c_773, &frame__compiler__sim2c, 1010, 1011, 3, 52},
  {cont__compiler__sim2c_778, &frame__compiler__sim2c, 1012, 1014, 9, 37},
  {cont__compiler__sim2c_780, &frame__compiler__sim2c, 1012, 1014, 3, 37},
  {cont__compiler__sim2c_781, &frame__compiler__sim2c, 1015, 1036, 3, 72},
  {cont__compiler__sim2c_828, &frame__compiler__sim2c, 1037, 1037, 3, 25},
  {cont__compiler__sim2c_829, &frame__compiler__sim2c, 1038, 1055, 3, 41},
  {cont__compiler__sim2c_836, &frame__compiler__sim2c, 1056, 1057, 3, 52},
  {cont__compiler__sim2c_841, &frame__compiler__sim2c, 1058, 1061, 9, 45},
  {cont__compiler__sim2c_843, &frame__compiler__sim2c, 1058, 1061, 3, 45},
  {cont__compiler__sim2c_844, &frame__compiler__sim2c, 1062, 1062, 3, 25},
  {cont__compiler__sim2c_845, &frame__compiler__sim2c, 1063, 1079, 3, 41},
  {cont__compiler__sim2c_852, &frame__compiler__sim2c, 1080, 1081, 3, 52},
  {cont__compiler__sim2c_857, &frame__compiler__sim2c, 1082, 1085, 9, 45},
  {cont__compiler__sim2c_858, &frame__compiler__sim2c, 1082, 1085, 3, 45},
  {cont__compiler__sim2c_859, &frame__compiler__sim2c, 1086, 1120, 3, 64},
  {cont__compiler__sim2c_894, &frame__compiler__sim2c, 1121, 1121, 3, 25},
  {cont__compiler__sim2c_895, &frame__compiler__sim2c, 1122, 1125, 3, 32},
  {cont__compiler__sim2c_898, &frame__compiler__sim2c, 1126, 1140, 3, 41},
  {cont__compiler__sim2c_905, &frame__compiler__sim2c, 1141, 1142, 3, 52},
  {cont__compiler__sim2c_910, &frame__compiler__sim2c, 1143, 1143, 3, 25},
  {cont__compiler__sim2c_911, &frame__compiler__sim2c, 1144, 1159, 3, 41},
  {cont__compiler__sim2c_918, &frame__compiler__sim2c, 1160, 1161, 3, 52},
  {cont__compiler__sim2c_923, &frame__compiler__sim2c, 1162, 1162, 3, 25},
  {cont__compiler__sim2c_924, &frame__compiler__sim2c, 1163, 1163, 11, 58},
  {cont__compiler__sim2c_926, &frame__compiler__sim2c, 1163, 1163, 3, 58},
  {cont__compiler__sim2c_927, &frame__compiler__sim2c, 1164, 1167, 3, 31},
  {cont__compiler__sim2c_930, &frame__compiler__sim2c, 1168, 1168, 3, 15},
  {cont__compiler__sim2c_931, &frame__compiler__sim2c, 1169, 1169, 3, 64},
  {cont__compiler__sim2c_935, &frame__compiler__sim2c, 1169, 1169, 64, 64}
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
  // 55: "std__if" = 0
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
  // 56: "std__is_defined" = 1
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
  // 57: "std__equal" = 2
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
  // 58: "std__less" = 3
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
  // 59: "std__length_of" = 4
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
  // 60: "std__is_empty" = 5
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
  // 61: "std__unless" = 6
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
  // 53: $compiler::privileged_polymorphic_functions
  // 54:   table
  // 55:     "std__if" = 0
  // 56:     "std__is_defined" = 1
  // 57:     "std__equal" = 2
  // 58:     "std__less" = 3
  // 59:     "std__length_of" = 4
  // 60:     "std__is_empty" = 5
  // 61:     "std__unless" = 6
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
  // 39: write chr
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
  // 33: writeln "<newline>"
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
  // 35: writeln "<indent_marker>"
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
  // 37: writeln "<outdent_marker>"
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
  // 38: :
  // 39:   write chr
  frame->slots[1] /* temp__1 */ = create_closure(entry__compiler__print_source_3, 0);
  // 31: case chr
  // 32:   newline:
  // 33:     writeln "<newline>"
  // 34:   indent_marker:
  // 35:     writeln "<indent_marker>"
  // 36:   outdent_marker:
  // 37:     writeln "<outdent_marker>"
  // 38:   :
  // 39:     write chr
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
static void entry__compiler__print_source(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // source: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 30: for_each source: (chr)
  // 31:   case chr
  // 32:     newline:
  // 33:       writeln "<newline>"
  // 34:     indent_marker:
  // 35:       writeln "<indent_marker>"
  // 36:     outdent_marker:
  // 37:       writeln "<outdent_marker>"
  // 38:     :
  // 39:       write chr
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
  // 51: ewrite chr
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
  // 45: ewriteln "<newline>"
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
  // 47: ewriteln "<indent_marker>"
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
  // 49: ewriteln "<outdent_marker>"
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
  // 50: :
  // 51:   ewrite chr
  frame->slots[1] /* temp__1 */ = create_closure(entry__compiler__eprint_source_3, 0);
  // 43: case chr
  // 44:   newline:
  // 45:     ewriteln "<newline>"
  // 46:   indent_marker:
  // 47:     ewriteln "<indent_marker>"
  // 48:   outdent_marker:
  // 49:     ewriteln "<outdent_marker>"
  // 50:   :
  // 51:     ewrite chr
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
static void entry__compiler__eprint_source(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // source: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 42: for_each source: (chr)
  // 43:   case chr
  // 44:     newline:
  // 45:       ewriteln "<newline>"
  // 46:     indent_marker:
  // 47:       ewriteln "<indent_marker>"
  // 48:     outdent_marker:
  // 49:       ewriteln "<outdent_marker>"
  // 50:     :
  // 51:       ewrite chr
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  arguments->slots[1] = func__compiler__eprint_source_2;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__generate_dispatcher_function(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // name: 0
  // id: 1
  frame->slots[1] /* id */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 64: ... "
  // 65:   static void type__@(name)(void);
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
  // 64: write_to_declarations "
  // 65:   static void type__@(name)(void);
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
  // 66: ... "
  // 67:   static void type__@(name)(void) {
  // 68:     if (argument_count < 1) {
  // 69:       too_few_arguments_error();
  // 70:       return;
  // 71:     }
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7fb24a3fca4aa852;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__949b16e1d9f7528;
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
  // 66: write_to_functions "
  // 67:   static void type__@(name)(void) {
  // 68:     if (argument_count < 1) {
  // 69:       too_few_arguments_error();
  // 70:       return;
  // 71:     }
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
  // 72: $id privileged_polymorphic_functions(name)
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
  // 74: id.is_defined
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
  // 74: ... :
  // 75:   # ATTENTION: do not optimize to get better error messages
  // 76:   
  // 77:   #if
  // 78:     id < 8:
  // 79:       write_to_functions "
  // 80:         @
  // 81:           myself = (NODE @
  // 82:         *)arguments->slots[0]->attributes->nodes[0]->nodes[@(id)];
  // 83:     :
  // ...
  frame->slots[3] /* temp__2 */ = create_closure(entry__compiler__generate_dispatcher_function_11, 0);
  // 93: :
  // 94:   write_to_functions
  // 95:     "  myself = get_attribute(arguments->slots[0], poly_idx__@(name));@nl;"
  frame->slots[4] /* temp__3 */ = create_closure(entry__compiler__generate_dispatcher_function_16, 0);
  // 73: if
  // 74:   id.is_defined:
  // 75:     # ATTENTION: do not optimize to get better error messages
  // 76:     
  // 77:     #if
  // 78:       id < 8:
  // 79:         write_to_functions "
  // 80:           @
  // 81:             myself = (NODE @
  // 82:           *)arguments->slots[0]->attributes->nodes[0]->nodes[@(id)];
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
  // 89: ... "
  // 90:   @
  // 91:     myself = get_attribute(arguments->slots[0], poly_idx__@(name)); // @
  // 92:   @(id)@nl;@
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
  // 89: write_to_functions "
  // 90:   @
  // 91:     myself = get_attribute(arguments->slots[0], poly_idx__@(name)); // @
  // 92:   @(id)@nl;@
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
  // 95: "  myself = get_attribute(arguments->slots[0], poly_idx__@(name));@nl;"
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
  // 94: write_to_functions
  // 95:   "  myself = get_attribute(arguments->slots[0], poly_idx__@(name));@nl;"
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
  // 100: ... "
  // 101:     if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
  // 102:       if (argument_count != 1) {
  // 103:         if (argument_count != 2) invalid_arguments_error();
  // 104:         NODE *attr = arguments->slots[1];
  // 105:         NODE *temp = clone_object_and_attributes(arguments->slots[0]);
  // 106:         update_start_p = node_p;
  // 107:         set_attribute_value(temp->attributes, poly_idx__@(name), attr);
  // 108:         arguments = node_p;
  // 109:         argument_count = 1;
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
  // 100: write_to_functions "
  // 101:     if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
  // 102:       if (argument_count != 1) {
  // 103:         if (argument_count != 2) invalid_arguments_error();
  // 104:         NODE *attr = arguments->slots[1];
  // 105:         NODE *temp = clone_object_and_attributes(arguments->slots[0]);
  // 106:         update_start_p = node_p;
  // 107:         set_attribute_value(temp->attributes, poly_idx__@(name), attr);
  // 108:         arguments = node_p;
  // 109:         argument_count = 1;
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write_to_functions();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__demangled(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // name: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 122: ... "__" = "::"
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
  // 122: ... replace_all(name "__" = "::")
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
  // 122: ... -> replace_all(name "__" = "::")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__update_info(void) {
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
  // 132: curr_info.is_defined
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
  // 132: ... :
  // 133:   case variable_kind_of(curr_info)
  // 134:     POLYMORPHIC:
  // 135:       case
  // 136:         variable_kind_of(info)
  // 137:         POLYMORPHIC, STATIC_SINGLE:
  // 138:           return undefined
  // 139:         :
  // 140:           Error "
  // 141:             The symbol "@(name.demangled)" is used as a polymorphic @
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__compiler__update_info_3, 0);
  // 194: :
  // 195:   return info
  frame->slots[6] /* temp__3 */ = create_closure(entry__compiler__update_info_58, 0);
  // 131: if
  // 132:   curr_info.is_defined:
  // 133:     case variable_kind_of(curr_info)
  // 134:       POLYMORPHIC:
  // 135:         case
  // 136:           variable_kind_of(info)
  // 137:           POLYMORPHIC, STATIC_SINGLE:
  // 138:             return undefined
  // 139:           :
  // 140:             Error "
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
  // 187: return undefined
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
  // 190: ... name.demangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = func__demangled;
  func = myself->type;
  frame->cont = cont__compiler__update_info_55;
}
static void cont__compiler__update_info_55(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 189: ... "
  // 190:   The symbol "@(name.demangled)" is used as a single-assign @
  // 191:   dynamic and as a multi-assign dynamic!@
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
  // 189: Error "
  // 190:   The symbol "@(name.demangled)" is used as a single-assign @
  // 191:   dynamic and as a multi-assign dynamic!@
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
  // 193: return info
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
  // 171: return undefined
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
  // 174: ... name.demangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = func__demangled;
  func = myself->type;
  frame->cont = cont__compiler__update_info_40;
}
static void cont__compiler__update_info_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 173: ... "
  // 174:   The symbol "@(name.demangled)" is used as a single-assign @
  // 175:   dynamic and is assigned to!@
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
  // 173: Error "
  // 174:   The symbol "@(name.demangled)" is used as a single-assign @
  // 175:   dynamic and is assigned to!@
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
  // 178: ... name.demangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = func__demangled;
  func = myself->type;
  frame->cont = cont__compiler__update_info_43;
}
static void cont__compiler__update_info_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 177: ... "
  // 178:   The symbol "@(name.demangled)" is used as a single-assign @
  // 179:   dynamic and as a multi-assign dynamic!@
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
  // 177: Error "
  // 178:   The symbol "@(name.demangled)" is used as a single-assign @
  // 179:   dynamic and as a multi-assign dynamic!@
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
  myself = func__demangled;
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
  // 147: return undefined
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
  // 149: return info
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
  // 138: return undefined
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
  // 141: ... name.demangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = func__demangled;
  func = myself->type;
  frame->cont = cont__compiler__update_info_10;
}
static void cont__compiler__update_info_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 140: ... "
  // 141:   The symbol "@(name.demangled)" is used as a polymorphic @
  // 142:   function and cannot be used otherwise!@
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
  // 140: Error "
  // 141:   The symbol "@(name.demangled)" is used as a polymorphic @
  // 142:   function and cannot be used otherwise!@
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
  // 136: variable_kind_of(info)
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
  // 137: POLYMORPHIC, STATIC_SINGLE
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
  // 137: ... :
  // 138:   return undefined
  frame->slots[5] /* temp__3 */ = create_closure(entry__compiler__update_info_8, 0);
  // 139: :
  // 140:   Error "
  // 141:     The symbol "@(name.demangled)" is used as a polymorphic @
  // 142:     function and cannot be used otherwise!@
  frame->slots[6] /* temp__4 */ = create_closure(entry__compiler__update_info_9, 0);
  // 135: case
  // 136:   variable_kind_of(info)
  // 137:   POLYMORPHIC, STATIC_SINGLE:
  // 138:     return undefined
  // 139:   :
  // 140:     Error "
  // 141:       The symbol "@(name.demangled)" is used as a polymorphic @
  // 142:       function and cannot be used otherwise!@
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
  // 145: variable_kind_of(info)
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
  // 146: ... :
  // 147:   return undefined
  frame->slots[3] /* temp__2 */ = create_closure(entry__compiler__update_info_16, 0);
  // 148: :
  // 149:   return info
  frame->slots[4] /* temp__3 */ = create_closure(entry__compiler__update_info_17, 0);
  // 144: case
  // 145:   variable_kind_of(info)
  // 146:   STATIC_SINGLE:
  // 147:     return undefined
  // 148:   :
  // 149:     return info
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
  // 151: ... variable_kind_of(info)
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
  myself = func__demangled;
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
  // 151: case variable_kind_of(info)
  // 152:   POLYMORPHIC:
  // 153:     Error "
  // 154:       The symbol "@(name.demangled)" is used as a polymorphic @
  // 155:       function and id assigned to!@
  // 156:   STATIC_SINGLE, STATIC_MULTI:
  // 157:     return undefined
  // 158:   DYNAMIC_SINGLE:
  // 159:     Error "
  // 160:       The symbol "@(name.demangled)" is used as a single-assign @
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
  // 165: ... variable_kind_of(info)
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
  // 166: ... :
  // 167:   Error "
  // 168:     The symbol "@(name.demangled)" is used as a polymorphic @
  // 169:     function and as a single-assign dynamic!@
  frame->slots[4] /* temp__2 */ = create_closure(entry__compiler__update_info_33, 0);
  // 170: STATIC_SINGLE, DYNAMIC_SINGLE
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
  // 168: ... name.demangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = func__demangled;
  func = myself->type;
  frame->cont = cont__compiler__update_info_34;
}
static void cont__compiler__update_info_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 167: ... "
  // 168:   The symbol "@(name.demangled)" is used as a polymorphic @
  // 169:   function and as a single-assign dynamic!@
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
  // 167: Error "
  // 168:   The symbol "@(name.demangled)" is used as a polymorphic @
  // 169:   function and as a single-assign dynamic!@
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
  // 170: ... :
  // 171:   return undefined
  frame->slots[6] /* temp__4 */ = create_closure(entry__compiler__update_info_38, 0);
  // 172: ... :
  // 173:   Error "
  // 174:     The symbol "@(name.demangled)" is used as a single-assign @
  // 175:     dynamic and is assigned to!@
  frame->slots[7] /* temp__5 */ = create_closure(entry__compiler__update_info_39, 0);
  // 176: ... :
  // 177:   Error "
  // 178:     The symbol "@(name.demangled)" is used as a single-assign @
  // 179:     dynamic and as a multi-assign dynamic!@
  frame->slots[8] /* temp__6 */ = create_closure(entry__compiler__update_info_42, 0);
  // 165: case variable_kind_of(info)
  // 166:   POLYMORPHIC:
  // 167:     Error "
  // 168:       The symbol "@(name.demangled)" is used as a polymorphic @
  // 169:       function and as a single-assign dynamic!@
  // 170:   STATIC_SINGLE, DYNAMIC_SINGLE:
  // 171:     return undefined
  // 172:   STATIC_MULTI:
  // 173:     Error "
  // 174:       The symbol "@(name.demangled)" is used as a single-assign @
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
  // 181: ... variable_kind_of(info)
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
  // 182: ... :
  // 183:   Error "
  // 184:     The symbol "@(name.demangled)" is used as a polymorphic @
  // 185:     function and as a multi-assign dynamic!@
  frame->slots[4] /* temp__2 */ = create_closure(entry__compiler__update_info_48, 0);
  // 186: STATIC_SINGLE, STATIC_MULTI, DYNAMIC_MULTI
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
  // 184: ... name.demangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = func__demangled;
  func = myself->type;
  frame->cont = cont__compiler__update_info_49;
}
static void cont__compiler__update_info_49(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 183: ... "
  // 184:   The symbol "@(name.demangled)" is used as a polymorphic @
  // 185:   function and as a multi-assign dynamic!@
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
  // 183: Error "
  // 184:   The symbol "@(name.demangled)" is used as a polymorphic @
  // 185:   function and as a multi-assign dynamic!@
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
  // 186: ... :
  // 187:   return undefined
  frame->slots[6] /* temp__4 */ = create_closure(entry__compiler__update_info_53, 0);
  // 188: ... :
  // 189:   Error "
  // 190:     The symbol "@(name.demangled)" is used as a single-assign @
  // 191:     dynamic and as a multi-assign dynamic!@
  frame->slots[7] /* temp__5 */ = create_closure(entry__compiler__update_info_54, 0);
  // 192: :
  // 193:   return info
  frame->slots[8] /* temp__6 */ = create_closure(entry__compiler__update_info_57, 0);
  // 181: case variable_kind_of(info)
  // 182:   POLYMORPHIC:
  // 183:     Error "
  // 184:       The symbol "@(name.demangled)" is used as a polymorphic @
  // 185:       function and as a multi-assign dynamic!@
  // 186:   STATIC_SINGLE, STATIC_MULTI, DYNAMIC_MULTI:
  // 187:     return undefined
  // 188:   DYNAMIC_SINGLE:
  // 189:     Error "
  // 190:       The symbol "@(name.demangled)" is used as a single-assign @
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
  // 133: ... variable_kind_of(curr_info)
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
  // 134: ... :
  // 135:   case
  // 136:     variable_kind_of(info)
  // 137:     POLYMORPHIC, STATIC_SINGLE:
  // 138:       return undefined
  // 139:     :
  // 140:       Error "
  // 141:         The symbol "@(name.demangled)" is used as a polymorphic @
  // 142:         function and cannot be used otherwise!@
  frame->slots[5] /* temp__2 */ = create_closure(entry__compiler__update_info_5, 0);
  // 143: ... :
  // 144:   case
  // 145:     variable_kind_of(info)
  // 146:     STATIC_SINGLE:
  // 147:       return undefined
  // 148:     :
  // 149:       return info
  frame->slots[6] /* temp__3 */ = create_closure(entry__compiler__update_info_14, 0);
  // 150: ... :
  // 151:   case variable_kind_of(info)
  // 152:     POLYMORPHIC:
  // 153:       Error "
  // 154:         The symbol "@(name.demangled)" is used as a polymorphic @
  // 155:         function and id assigned to!@
  // 156:     STATIC_SINGLE, STATIC_MULTI:
  // 157:       return undefined
  // 158:     DYNAMIC_SINGLE:
  // 159:       Error "
  // ...
  frame->slots[7] /* temp__4 */ = create_closure(entry__compiler__update_info_18, 0);
  // 164: ... :
  // 165:   case variable_kind_of(info)
  // 166:     POLYMORPHIC:
  // 167:       Error "
  // 168:         The symbol "@(name.demangled)" is used as a polymorphic @
  // 169:         function and as a single-assign dynamic!@
  // 170:     STATIC_SINGLE, DYNAMIC_SINGLE:
  // 171:       return undefined
  // 172:     STATIC_MULTI:
  // 173:       Error "
  // ...
  frame->slots[8] /* temp__5 */ = create_closure(entry__compiler__update_info_31, 0);
  // 180: ... :
  // 181:   case variable_kind_of(info)
  // 182:     POLYMORPHIC:
  // 183:       Error "
  // 184:         The symbol "@(name.demangled)" is used as a polymorphic @
  // 185:         function and as a multi-assign dynamic!@
  // 186:     STATIC_SINGLE, STATIC_MULTI, DYNAMIC_MULTI:
  // 187:       return undefined
  // 188:     DYNAMIC_SINGLE:
  // 189:       Error "
  // ...
  frame->slots[9] /* temp__6 */ = create_closure(entry__compiler__update_info_46, 0);
  // 133: case variable_kind_of(curr_info)
  // 134:   POLYMORPHIC:
  // 135:     case
  // 136:       variable_kind_of(info)
  // 137:       POLYMORPHIC, STATIC_SINGLE:
  // 138:         return undefined
  // 139:       :
  // 140:         Error "
  // 141:           The symbol "@(name.demangled)" is used as a polymorphic @
  // 142:           function and cannot be used otherwise!@
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
  // 195: return info
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
static void entry__compiler__sim2c(void) {
  allocate_initialized_frame_gc(3, 37);
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
  // is_a_prototype: 31
  // def_count: 32
  // depth: 33
  frame->slots[2] /* return__10 */ = create_continuation();
  // _define $mangle_filename 
  // : ($name)
  //   has_prefix !temp__1 name "./"
  // 
  //   !temp__2:
  //     contains !temp__1 module_name "__"
  // 
  //     !temp__2:
  //       std::negate !temp__2 1
  //       before !temp__1 module_name "__" temp__2
  //       std::negate !temp__4 1
  //       range !temp__3 name 2 temp__4
  //       append !name temp__1 temp__3
  // 
  //     !temp__3:
  //       std::negate !temp__1 1
  //       range !name name 3 temp__1
  // 
  //     if temp__1 temp__2 temp__3
  // 
  //   if temp__1 temp__2
  //   std::key_value_pair !temp__2 '/' "__"
  //   replace_all !temp__1 name temp__2
  //   -> temp__1
  frame->slots[3] /* mangle_filename */ = func__compiler__sim2c_2;
  // _define $need 
  // :
  //   (
  //     mangled_name
  //     info
  //     -> return
  //   )
  //   contains !temp__1 mangled_name "__"
  // 
  //   !temp__2:
  //     before $namespace mangled_name "__"
  //     behind $name mangled_name "__"
  //     exported_names $namespaces name
  //     is_defined !temp__2 namespaces
  // 
  //     !temp__3:
  //       namespaces !temp__2 namespace
  //       is_defined !temp__1 temp__2
  //       -> temp__1
  // 
  //     std::and !temp__1 temp__2 temp__3
  //     if temp__1 return
  // 
  //   !temp__3:
  //     global_names $definition mangled_name
  //     is_defined !temp__1 definition
  // 
  //     !temp__2:
  //       check_usage mangled_name definition info
  //       return
  // 
  //     if temp__1 temp__2
  // 
  //   if temp__1 temp__2 temp__3
  //   needed_names !temp__1 mangled_name
  //   update_info $updated_info mangled_name temp__1 info
  //   is_defined !temp__1 updated_info
  // 
  //   !temp__2: needed_names !needed_names mangled_name updated_info
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
  define__compiler__unique_item_index(undefined);
  define__compiler__used_unique_items(undefined);
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
  define__named_constants(undefined);
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
  frame->slots[31] /* is_a_prototype */ = create_cell();
  define__compiler__current_continuation_info(undefined);
  frame->slots[32] /* def_count */ = create_future();
  frame->slots[33] /* depth */ = create_future();
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
  // 229: %%compiler::required_modules empty_insert_order_table
  set__compiler__required_modules(get__empty_insert_order_table());
  // 230: %%compiler::used_namespaces empty_insert_order_set
  set__compiler__used_namespaces(get__empty_insert_order_set());
  // 231: %%compiler::defined_namespaces empty_insert_order_set
  set__compiler__defined_namespaces(get__empty_insert_order_set());
  // 232: %%compiler::namespace_mappings empty_insert_order_table
  set__compiler__namespace_mappings(get__empty_insert_order_table());
  // 233: %%compiler::included_files empty_insert_order_set
  set__compiler__included_files(get__empty_insert_order_set());
  // 234: %%compiler::linked_libraries empty_insert_order_set
  set__compiler__linked_libraries(get__empty_insert_order_set());
  // 235: %%compiler::dependent_data empty_insert_order_set
  set__compiler__dependent_data(get__empty_insert_order_set());
  // 236: %%compiler::global_names empty_key_order_table
  set__compiler__global_names(get__empty_key_order_table());
  // 237: %%compiler::exported_names empty_key_order_table
  set__compiler__exported_names(get__empty_key_order_table());
  // 238: %%compiler::needed_names empty_key_order_table
  set__compiler__needed_names(get__empty_key_order_table());
  // 239: %%compiler::assigned_names empty_set
  set__compiler__assigned_names(get__empty_set());
  // 240: %%compiler::string_literals empty_table
  set__compiler__string_literals(get__empty_table());
  // 241: %%compiler::unique_item_index 0
  set__compiler__unique_item_index(number__0);
  // 242: %%compiler::used_unique_items empty_set
  set__compiler__used_unique_items(get__empty_set());
  // 243: %%compiler::use_inline_c false # set, if an inline-C expression is encountered
  set__compiler__use_inline_c(get__false());
  // 244: %%compiler::defined_structs set("NODE")
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
  // 221: ... name .has_prefix. "./"
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
  // 221: ... :
  // 222:   if
  // 223:     module_name .contains. "__":
  // 224:       !name before(module_name "__" -1) .append. range(name 2 -1)
  // 225:     :
  // 226:       !name range(name 3 -1)
  frame->slots[2] /* temp__2 */ = create_closure(entry__compiler__sim2c_5, 0);
  // 221: if name .has_prefix. "./":
  // 222:   if
  // 223:     module_name .contains. "__":
  // 224:       !name before(module_name "__" -1) .append. range(name 2 -1)
  // 225:     :
  // 226:       !name range(name 3 -1)
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
  // 224: ... 1
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
  // 224: ... before(module_name "__" -1)
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
  // 224: ... 1
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
  // 224: ... range(name 2 -1)
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
  // 224: !name before(module_name "__" -1) .append. range(name 2 -1)
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
  // 226: ... 1
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
  // 226: !name range(name 3 -1)
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
  // 223: module_name .contains. "__"
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
  // 223: ... :
  // 224:   !name before(module_name "__" -1) .append. range(name 2 -1)
  frame->slots[2] /* temp__2 */ = create_closure(entry__compiler__sim2c_7, 0);
  // 225: :
  // 226:   !name range(name 3 -1)
  frame->slots[3] /* temp__3 */ = create_closure(entry__compiler__sim2c_13, 0);
  // 222: if
  // 223:   module_name .contains. "__":
  // 224:     !name before(module_name "__" -1) .append. range(name 2 -1)
  // 225:   :
  // 226:     !name range(name 3 -1)
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
  // 227: ... '/' = "__"
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
  // 227: ... replace_all(name '/' = "__")
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
  // 227: -> replace_all(name '/' = "__")
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
  // 457: mangled_name .contains. "__"
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
  // 457: ... :
  // 458:   $namespace mangled_name .before. "__"
  // 459:   $name mangled_name .behind. "__"
  // 460:   $namespaces exported_names(name)
  // 461:   if namespaces.is_defined && namespaces(namespace).is_defined return
  frame->slots[5] /* temp__2 */ = create_closure(entry__compiler__sim2c_21, 0);
  // 462: :
  // 463:   $definition global_names(mangled_name)
  // 464:   if definition.is_defined:
  // 465:     check_usage mangled_name definition info
  // 466:     return
  frame->slots[6] /* temp__3 */ = create_closure(entry__compiler__sim2c_30, 0);
  // 456: if
  // 457:   mangled_name .contains. "__":
  // 458:     $namespace mangled_name .before. "__"
  // 459:     $name mangled_name .behind. "__"
  // 460:     $namespaces exported_names(name)
  // 461:     if namespaces.is_defined && namespaces(namespace).is_defined return
  // 462:   :
  // 463:     $definition global_names(mangled_name)
  // 464:     if definition.is_defined:
  // 465:       check_usage mangled_name definition info
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
  // 465: check_usage mangled_name definition info
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
  // 466: return
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
  // 458: $namespace mangled_name .before. "__"
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
  // 459: $name mangled_name .behind. "__"
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
  // 460: $namespaces exported_names(name)
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
  // 461: ... namespaces.is_defined
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
  // 461: ... namespaces(namespace).is_defined
  frame->slots[7] /* temp__3 */ = create_closure(entry__compiler__sim2c_26, 0);
  // 461: ... namespaces.is_defined && namespaces(namespace).is_defined
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
  // 461: ... namespaces(namespace)
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
  // 461: ... namespaces(namespace).is_defined
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
  // 461: ... namespaces(namespace).is_defined
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
  // 461: if namespaces.is_defined && namespaces(namespace).is_defined return
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
  // 463: $definition global_names(mangled_name)
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
  // 464: ... definition.is_defined
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
  // 464: ... :
  // 465:   check_usage mangled_name definition info
  // 466:   return
  frame->slots[5] /* temp__2 */ = create_closure(entry__compiler__sim2c_33, 0);
  // 464: if definition.is_defined:
  // 465:   check_usage mangled_name definition info
  // 466:   return
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
  // 467: ... needed_names(mangled_name)
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
  // 467: $updated_info update_info(mangled_name needed_names(mangled_name) info)
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
  // 468: ... updated_info.is_defined
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
  // 468: ... : !needed_names(mangled_name) updated_info
  frame->slots[5] /* temp__2 */ = create_closure(entry__compiler__sim2c_39, 0);
  // 468: if updated_info.is_defined: !needed_names(mangled_name) updated_info
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
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // mangled_name: 0
  // updated_info: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* mangled_name */
  frame->slots[1] = myself->closure.frame->slots[3]; /* updated_info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 468: ... !needed_names(mangled_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mangled_name */;
  arguments->slots[1] = frame->slots[1] /* updated_info */;
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
  // 245: ... c_code(.source_of "")
  {
    NODE *temp = clone_object_and_attributes(get__c_code());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__source_of, empty_string);
    frame->slots[35] /* temp__2 */ = temp;

  }
  // 245: ... "SIMPLE_NODE" = c_code(.source_of "")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__1c6c7289032a5d69;
  arguments->slots[1] = frame->slots[35] /* temp__2 */;
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
  frame->slots[34] /* temp__1 */ = arguments->slots[0];
  // 245: %%compiler::defined_nodes table("SIMPLE_NODE" = c_code(.source_of ""))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[34] /* temp__1 */;
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
  // 246: %%compiler::defined_functions empty_set
  set__compiler__defined_functions(get__empty_set());
  // 247: %%compiler::enumeration_count 0
  set__compiler__enumeration_count(number__0);
  // 248: $$fragments empty_list
  ((CELL *)frame->slots[4])->contents /* fragments */ = get__empty_list();
  // 249: $$trees empty_list
  ((CELL *)frame->slots[5])->contents /* trees */ = get__empty_list();
  // 250: $$all_defined_names empty_list
  ((CELL *)frame->slots[6])->contents /* all_defined_names */ = get__empty_list();
  // 251: $$all_used_names empty_list
  ((CELL *)frame->slots[7])->contents /* all_used_names */ = get__empty_list();
  // 252: ... : (no filename)
  // 253:   $$buf load(filename)
  // 254:   try
  // 255:     :
  // 256:       from_utf8 &buf
  // 257:     :
  // 258:       Error "Source file is not in a valid utf-8-encoding!"
  // 259:   if do_show_debug_infos:
  // 260:     ewrite "
  // 261:       load "@(filename)@quot;
  // ...
  frame->slots[34] /* temp__1 */ = create_closure(entry__compiler__sim2c_47, 2);
  // 252: for_each filenames: (no filename)
  // 253:   $$buf load(filename)
  // 254:   try
  // 255:     :
  // 256:       from_utf8 &buf
  // 257:     :
  // 258:       Error "Source file is not in a valid utf-8-encoding!"
  // 259:   if do_show_debug_infos:
  // 260:     ewrite "
  // 261:       load "@(filename)@quot;
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filenames */;
  arguments->slots[1] = frame->slots[34] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_112;
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
  // 253: $$buf load(filename)
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
  // 255: :
  // 256:   from_utf8 &buf
  frame->slots[9] /* temp__1 */ = create_closure(entry__compiler__sim2c_49, 0);
  // 254: try
  // 255:   :
  // 256:     from_utf8 &buf
  // 257:   :
  // 258:     Error "Source file is not in a valid utf-8-encoding!"
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
  // 256: from_utf8 &buf
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
  // 258: Error "Source file is not in a valid utf-8-encoding!"
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
  // 259: ... :
  // 260:   ewrite "
  // 261:     load "@(filename)@quot;
  frame->slots[9] /* temp__1 */ = create_closure(entry__compiler__sim2c_54, 0);
  // 259: if do_show_debug_infos:
  // 260:   ewrite "
  // 261:     load "@(filename)@quot;
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
  // 260: ... "
  // 261:   load "@(filename)@quot;
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
  // 260: ewrite "
  // 261:   load "@(filename)@quot;
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
  // 262: ... : write_timing_info "loading" filename
  frame->slots[9] /* temp__1 */ = create_closure(entry__compiler__sim2c_59, 0);
  // 262: if do_time_passes: write_timing_info "loading" filename
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
  // 262: ... write_timing_info "loading" filename
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
  // 263: ... length_of(buf)
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
  // 263: ... length_of(buf) == 0
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
  // 263: if length_of(buf) == 0: Error "Empty source text!"
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
  // 263: ... Error "Empty source text!"
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
  // 264: ... buf(1)
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
  // 264: ... buf(1) <= ' '
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
  // 264: ... buf(1) <= ' '
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
  // 264: if buf(1) <= ' ': Error "Whitespace at start of source text!"
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
  // 264: ... Error "Whitespace at start of source text!"
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
  // 265: ... 1
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
  // 265: ... buf(-1)
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
  // 265: ... buf(-1) != newline
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
  // 265: ... buf(-1) != newline
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
  // 265: if buf(-1) != newline: Error "Missing newline at end of source text!"
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
  // 265: ... Error "Missing newline at end of source text!"
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
  // 266: ... buf .has_prefix. "#!"
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
  // 266: ... : !is_main true
  frame->slots[10] /* temp__2 */ = create_closure(entry__compiler__sim2c_82, 0);
  // 266: if buf .has_prefix. "#!": !is_main true
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
  // 266: ... !is_main true
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
  // 267: %compiler::submodule_no no-1
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
  // 268: $$submodule_fragments cut_into_fragments(buf)
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
  // 269: ... : write_timing_info "fragmenting" filename
  frame->slots[9] /* temp__1 */ = create_closure(entry__compiler__sim2c_86, 0);
  // 269: if do_time_passes: write_timing_info "fragmenting" filename
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
  // 269: ... write_timing_info "fragmenting" filename
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
  // 270: update_each &submodule_fragments: (&fragment) tokenize &fragment
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
  // 270: ... tokenize &fragment
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
  // 271: ... : write_timing_info "tokenizing" filename
  frame->slots[9] /* temp__1 */ = create_closure(entry__compiler__sim2c_92, 0);
  // 271: if do_time_passes: write_timing_info "tokenizing" filename
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
  // 271: ... write_timing_info "tokenizing" filename
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
  // 272: $$first_idx 1
  ((CELL *)frame->slots[8])->contents /* first_idx */ = number__1;
  // 273: ... : (-> done)
  // 274:   for_each submodule_fragments: (idx fragment)
  // 275:     case source_of(fragment)(1)
  // 276:       '#':
  // 277:         !first_idx idx+1
  // 278:         push &trees parse_statement(fragment)
  // 279:       '<':
  // 280:         !first_idx idx+1
  // 281:         push &trees parse_meta_instruction(fragment)
  // 282:       :
  // ...
  frame->slots[9] /* temp__1 */ = create_closure(entry__compiler__sim2c_95, 0);
  // 273: do: (-> done)
  // 274:   for_each submodule_fragments: (idx fragment)
  // 275:     case source_of(fragment)(1)
  // 276:       '#':
  // 277:         !first_idx idx+1
  // 278:         push &trees parse_statement(fragment)
  // 279:       '<':
  // 280:         !first_idx idx+1
  // 281:         push &trees parse_meta_instruction(fragment)
  // 282:       :
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_108;
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
  // 274: ... : (idx fragment)
  // 275:   case source_of(fragment)(1)
  // 276:     '#':
  // 277:       !first_idx idx+1
  // 278:       push &trees parse_statement(fragment)
  // 279:     '<':
  // 280:       !first_idx idx+1
  // 281:       push &trees parse_meta_instruction(fragment)
  // 282:     :
  // 283:       done
  frame->slots[4] /* temp__1 */ = create_closure(entry__compiler__sim2c_96, 2);
  // 274: for_each submodule_fragments: (idx fragment)
  // 275:   case source_of(fragment)(1)
  // 276:     '#':
  // 277:       !first_idx idx+1
  // 278:       push &trees parse_statement(fragment)
  // 279:     '<':
  // 280:       !first_idx idx+1
  // 281:       push &trees parse_meta_instruction(fragment)
  // 282:     :
  // 283:       done
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* submodule_fragments */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_107;
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
  // 277: !first_idx idx+1
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
  // 278: ... parse_statement(fragment)
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
  // 278: push &trees parse_statement(fragment)
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
  // 280: !first_idx idx+1
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
  // 281: ... parse_meta_instruction(fragment)
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
  // 281: push &trees parse_meta_instruction(fragment)
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
static void entry__compiler__sim2c_96(void) {
  allocate_initialized_frame_gc(5, 9);
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
  // 275: ... source_of(fragment)
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
  // 275: ... source_of(fragment)(1)
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
  // 276: ... :
  // 277:   !first_idx idx+1
  // 278:   push &trees parse_statement(fragment)
  frame->slots[7] /* temp__3 */ = create_closure(entry__compiler__sim2c_99, 0);
  // 279: ... :
  // 280:   !first_idx idx+1
  // 281:   push &trees parse_meta_instruction(fragment)
  frame->slots[8] /* temp__4 */ = create_closure(entry__compiler__sim2c_103, 0);
  // 275: case source_of(fragment)(1)
  // 276:   '#':
  // 277:     !first_idx idx+1
  // 278:     push &trees parse_statement(fragment)
  // 279:   '<':
  // 280:     !first_idx idx+1
  // 281:     push &trees parse_meta_instruction(fragment)
  // 282:   :
  // 283:     done
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = character__35;
  arguments->slots[2] = frame->slots[7] /* temp__3 */;
  arguments->slots[3] = character__60;
  arguments->slots[4] = frame->slots[8] /* temp__4 */;
  arguments->slots[5] = frame->slots[4] /* done */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_107(void) {
  myself = frame->slots[0] /* done */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__compiler__sim2c_108(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 284: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_109;
}
static void cont__compiler__sim2c_109(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__2 */ = arguments->slots[0];
  // 284: ... range(submodule_fragments first_idx -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[7])->contents /* submodule_fragments */;
  arguments->slots[1] = ((CELL *)frame->slots[8])->contents /* first_idx */;
  arguments->slots[2] = frame->slots[10] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_110;
}
static void cont__compiler__sim2c_110(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 284: append &fragments range(submodule_fragments first_idx -1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* fragments */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_111;
}
static void cont__compiler__sim2c_111(void) {
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
static void cont__compiler__sim2c_112(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 285: ... : (fragment) push &trees parse_statement(fragment)
  frame->slots[34] /* temp__1 */ = create_closure(entry__compiler__sim2c_113, 1);
  // 285: for_each fragments: (fragment) push &trees parse_statement(fragment)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* fragments */;
  arguments->slots[1] = frame->slots[34] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_116;
}
static void entry__compiler__sim2c_113(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // fragment: 0
  // trees: 1
  frame->slots[1] = myself->closure.frame->slots[5]; /* trees */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 285: ... parse_statement(fragment)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fragment */;
  result_count = 1;
  myself = get__parse_statement();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_114;
}
static void cont__compiler__sim2c_114(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 285: ... push &trees parse_statement(fragment)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* trees */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_115;
}
static void cont__compiler__sim2c_115(void) {
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
static void cont__compiler__sim2c_116(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 286: ... : write_timing_info "parsing" filenames(1)
  frame->slots[34] /* temp__1 */ = create_closure(entry__compiler__sim2c_117, 0);
  // 286: if do_time_passes: write_timing_info "parsing" filenames(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = frame->slots[34] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_120;
}
static void entry__compiler__sim2c_117(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // filenames: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* filenames */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 286: ... filenames(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* filenames */;
  func = myself->type;
  frame->cont = cont__compiler__sim2c_118;
}
static void cont__compiler__sim2c_118(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 286: ... write_timing_info "parsing" filenames(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__94440f9215cbe09d;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write_timing_info();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_120(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 287: ... :
  // 288:   #if do_show_compiler_debug_infos:
  // 289:     $$header_printed false
  // 290:     for_each global_names: (name type)
  // 291:       unless header_printed:
  // 292:         print_line "# Global variables"
  // 293:         !header_printed true
  // 294:       print_line "  " name
  // 295:   
  // 296:   print_trees trees
  // ...
  frame->slots[34] /* temp__1 */ = create_closure(entry__compiler__sim2c_121, 0);
  // 287: if do_pretty_print:
  // 288:   #if do_show_compiler_debug_infos:
  // 289:     $$header_printed false
  // 290:     for_each global_names: (name type)
  // 291:       unless header_printed:
  // 292:         print_line "# Global variables"
  // 293:         !header_printed true
  // 294:       print_line "  " name
  // 295:   
  // 296:   print_trees trees
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_pretty_print();
  arguments->slots[1] = frame->slots[34] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_123;
}
static void entry__compiler__sim2c_121(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // trees: 0
  frame->slots[0] = myself->closure.frame->slots[5]; /* trees */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 296: print_trees trees
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* trees */;
  result_count = 0;
  myself = get__print_trees();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_122;
}
static void cont__compiler__sim2c_122(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 297: terminate
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__terminate();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_123(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 298: ... :
  // 299:   push &trees procedure_call(.functor_of std_identifier("terminate"))
  frame->slots[34] /* temp__1 */ = create_closure(entry__compiler__sim2c_124, 0);
  // 298: if is_main:
  // 299:   push &trees procedure_call(.functor_of std_identifier("terminate"))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* is_main */;
  arguments->slots[1] = frame->slots[34] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_128;
}
static void entry__compiler__sim2c_124(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // trees: 0
  frame->slots[0] = myself->closure.frame->slots[5]; /* trees */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 299: ... std_identifier("terminate")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__72f826ea16a3e460;
  result_count = 1;
  myself = get__std_identifier();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_126;
}
static void cont__compiler__sim2c_126(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 299: ... procedure_call(.functor_of std_identifier("terminate"))
  {
    NODE *temp = clone_object_and_attributes(get__procedure_call());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__functor_of, frame->slots[2] /* temp__2 */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 299: push &trees procedure_call(.functor_of std_identifier("terminate"))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* trees */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_127;
}
static void cont__compiler__sim2c_127(void) {
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
static void cont__compiler__sim2c_128(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 300: update_each &trees: (&tree)
  // 301:   %%compiler::index 1
  // 302:   expand_statement &tree
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* trees */;
  arguments->slots[1] = func__compiler__sim2c_129;
  result_count = 1;
  myself = get__update_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_131;
}
static void entry__compiler__sim2c_129(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // tree: 0
  // return__2: 1
  frame->slots[1] /* return__2 */ = create_continuation_with_exit(exit__compiler__sim2c_129);
  define__compiler__index(undefined);
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* tree */ = create_cell_with_contents(arguments->slots[0]);
  // 301: %%compiler::index 1
  set__compiler__index(number__1);
  // 302: expand_statement &tree
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* tree */;
  result_count = 1;
  myself = get__expand_statement();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_130;
}
static void cont__compiler__sim2c_130(void) {
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
static void exit__compiler__sim2c_129(void) {
  frame = ((CONTINUATION *)myself)->exit_frame;
  int i = argument_count;
  while (--i >= 0) {
    arguments->slots[i+1] = arguments->slots[i];
  }
  argument_count += 1;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* tree */;
  func = continuation_type_function;
}
static void cont__compiler__sim2c_131(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[5])->contents /* trees */ = arguments->slots[0];
  // 303: ... : write_timing_info "expanding" filenames(1)
  frame->slots[34] /* temp__1 */ = create_closure(entry__compiler__sim2c_132, 0);
  // 303: if do_time_passes: write_timing_info "expanding" filenames(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = frame->slots[34] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_135;
}
static void entry__compiler__sim2c_132(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // filenames: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* filenames */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 303: ... filenames(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* filenames */;
  func = myself->type;
  frame->cont = cont__compiler__sim2c_133;
}
static void cont__compiler__sim2c_133(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 303: ... write_timing_info "expanding" filenames(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__66f024ec077397c2;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write_timing_info();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_135(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 304: ... : (&tree)
  // 305:   %%compiler::defined_names empty_list
  // 306:   %%compiler::used_names empty_insert_order_table
  // 307:   %%compiler::index 1
  // 308:   annotate_statement &tree
  // 309:   push &all_defined_names compiler::defined_names
  // 310:   push &all_used_names compiler::used_names
  frame->slots[34] /* temp__1 */ = create_closure(entry__compiler__sim2c_136, 1);
  // 304: update_each &trees: (&tree)
  // 305:   %%compiler::defined_names empty_list
  // 306:   %%compiler::used_names empty_insert_order_table
  // 307:   %%compiler::index 1
  // 308:   annotate_statement &tree
  // 309:   push &all_defined_names compiler::defined_names
  // 310:   push &all_used_names compiler::used_names
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* trees */;
  arguments->slots[1] = frame->slots[34] /* temp__1 */;
  result_count = 1;
  myself = get__update_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_140;
}
static void entry__compiler__sim2c_136(void) {
  allocate_initialized_frame_gc(4, 4);
  // slot allocations:
  // tree: 0
  // return__3: 1
  // all_defined_names: 2
  // all_used_names: 3
  frame->slots[1] /* return__3 */ = create_continuation_with_exit(exit__compiler__sim2c_136);
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
  // 305: %%compiler::defined_names empty_list
  set__compiler__defined_names(get__empty_list());
  // 306: %%compiler::used_names empty_insert_order_table
  set__compiler__used_names(get__empty_insert_order_table());
  // 307: %%compiler::index 1
  set__compiler__index(number__1);
  // 308: annotate_statement &tree
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* tree */;
  result_count = 1;
  myself = get__annotate_statement();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_137;
}
static void cont__compiler__sim2c_137(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* tree */ = arguments->slots[0];
  // 309: push &all_defined_names compiler::defined_names
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* all_defined_names */;
  arguments->slots[1] = get__compiler__defined_names();
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_138;
}
static void cont__compiler__sim2c_138(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* all_defined_names */ = arguments->slots[0];
  // 310: push &all_used_names compiler::used_names
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* all_used_names */;
  arguments->slots[1] = get__compiler__used_names();
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
  ((CELL *)frame->slots[3])->contents /* all_used_names */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  myself = frame->slots[1] /* return__3 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void exit__compiler__sim2c_136(void) {
  frame = ((CONTINUATION *)myself)->exit_frame;
  int i = argument_count;
  while (--i >= 0) {
    arguments->slots[i+1] = arguments->slots[i];
  }
  argument_count += 1;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* tree */;
  func = continuation_type_function;
}
static void cont__compiler__sim2c_140(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[5])->contents /* trees */ = arguments->slots[0];
  // 311: ... : write_timing_info "annotating" filenames(1)
  frame->slots[34] /* temp__1 */ = create_closure(entry__compiler__sim2c_141, 0);
  // 311: if do_time_passes: write_timing_info "annotating" filenames(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = frame->slots[34] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_144;
}
static void entry__compiler__sim2c_141(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // filenames: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* filenames */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 311: ... filenames(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* filenames */;
  func = myself->type;
  frame->cont = cont__compiler__sim2c_142;
}
static void cont__compiler__sim2c_142(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 311: ... write_timing_info "annotating" filenames(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__1d581a51a85b6426;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write_timing_info();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_144(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 312: $$all_actions empty_list
  ((CELL *)frame->slots[8])->contents /* all_actions */ = get__empty_list();
  // 314: $$top_level_names
  // 315:   if
  // 316:     do_print_warnings
  // 317:     -> empty_insert_order_table
  // 318:     -> empty_table
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__do_print_warnings();
  arguments->slots[1] = func__compiler__sim2c_145;
  arguments->slots[2] = func__compiler__sim2c_146;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_147;
}
static void entry__compiler__sim2c_145(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 317: -> empty_insert_order_table
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__empty_insert_order_table();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__sim2c_146(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 318: -> empty_table
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__empty_table();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__sim2c_147(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[9])->contents /* top_level_names */ = arguments->slots[0];
  // 320: ... required_modules.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__required_modules();
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_148;
}
static void cont__compiler__sim2c_148(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[35] /* temp__2 */ = arguments->slots[0];
  // 320: ... is_main
  frame->slots[36] /* temp__3 */ = create_closure(entry__compiler__sim2c_149, 0);
  // 320: ... required_modules.is_empty && is_main
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[35] /* temp__2 */;
  arguments->slots[1] = frame->slots[36] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_150;
}
static void entry__compiler__sim2c_149(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // is_main: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* is_main */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 320: ... is_main
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* is_main */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__sim2c_150(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[34] /* temp__1 */ = arguments->slots[0];
  // 320: if required_modules.is_empty && is_main:
  // 321:   !required_modules("basic/stdlib") types::grammar_node
  // 322:   !required_modules("system/stdlib") types::grammar_node
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[34] /* temp__1 */;
  arguments->slots[1] = func__compiler__sim2c_151;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_156;
}
static void entry__compiler__sim2c_151(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 321: !required_modules("basic/stdlib")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__c3e1e344d34946eb;
  arguments->slots[1] = get__types__grammar_node();
  result_count = 1;
  myself = get__required_modules();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_153;
}
static void cont__compiler__sim2c_153(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__required_modules(arguments->slots[0]);
  // 322: !required_modules("system/stdlib")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__b567219b137172d;
  arguments->slots[1] = get__types__grammar_node();
  result_count = 1;
  myself = get__required_modules();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_155;
}
static void cont__compiler__sim2c_155(void) {
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
static void cont__compiler__sim2c_156(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 323: !required_modules("nothing")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__a23c0f9515cb809d;
  arguments->slots[1] = get__undefined();
  result_count = 1;
  myself = get__required_modules();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_158;
}
static void cont__compiler__sim2c_158(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__required_modules(arguments->slots[0]);
  // 324: ... used_namespaces.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__used_namespaces();
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_159;
}
static void cont__compiler__sim2c_159(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[34] /* temp__1 */ = arguments->slots[0];
  // 324: if used_namespaces.is_empty: !used_namespaces("std") true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[34] /* temp__1 */;
  arguments->slots[1] = func__compiler__sim2c_160;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_163;
}
static void entry__compiler__sim2c_160(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 324: ... !used_namespaces("std")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__fa724815d896ba8;
  arguments->slots[1] = get__true();
  result_count = 1;
  myself = get__used_namespaces();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_162;
}
static void cont__compiler__sim2c_162(void) {
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
static void cont__compiler__sim2c_163(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 325: !used_namespaces("nothing")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__a23c0f9515cb809d;
  arguments->slots[1] = get__false();
  result_count = 1;
  myself = get__used_namespaces();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_164;
}
static void cont__compiler__sim2c_164(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__used_namespaces(arguments->slots[0]);
  // 326: ... : (defined_names)
  // 327:   for_each defined_names: (info)
  // 328:     $ident identifier_of(info)
  // 329:     unless
  // 330:       info.is_a_static_single_definition && attribute_of(info).is_defined:
  // 331:         $namespace namespace_of(ident)
  // 332:         $name name_of(ident)
  // 333:         if
  // 334:           namespace.is_defined:
  // 335:             $$namespaces exported_names(name)
  // ...
  frame->slots[34] /* temp__1 */ = create_closure(entry__compiler__sim2c_165, 1);
  // 326: for_each all_defined_names: (defined_names)
  // 327:   for_each defined_names: (info)
  // 328:     $ident identifier_of(info)
  // 329:     unless
  // 330:       info.is_a_static_single_definition && attribute_of(info).is_defined:
  // 331:         $namespace namespace_of(ident)
  // 332:         $name name_of(ident)
  // 333:         if
  // 334:           namespace.is_defined:
  // 335:             $$namespaces exported_names(name)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[6])->contents /* all_defined_names */;
  arguments->slots[1] = frame->slots[34] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_234;
}
static void entry__compiler__sim2c_177(void) {
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
  // 335: $$namespaces exported_names(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__exported_names();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_178;
}
static void cont__compiler__sim2c_178(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* namespaces */ = arguments->slots[0];
  // 336: ... namespaces.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* namespaces */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_179;
}
static void cont__compiler__sim2c_179(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 336: ... : !namespaces table()
  frame->slots[6] /* temp__2 */ = create_closure(entry__compiler__sim2c_180, 0);
  // 336: unless namespaces.is_defined: !namespaces table()
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_182;
}
static void entry__compiler__sim2c_180(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // namespaces: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* namespaces */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 336: ... !namespaces table()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__table();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_181;
}
static void cont__compiler__sim2c_181(void) {
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
static void cont__compiler__sim2c_182(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 337: ... namespaces(namespace)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* namespace */;
  result_count = 1;
  myself = ((CELL *)frame->slots[4])->contents /* namespaces */;
  func = myself->type;
  frame->cont = cont__compiler__sim2c_183;
}
static void cont__compiler__sim2c_183(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 337: ... namespaces(namespace).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_184;
}
static void cont__compiler__sim2c_184(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 337: ... :
  // 338:   SyntaxError identifier_of(info) "
  // 339:     An identifier named "@(namespace)::@(name)" was already @
  // 340:     defined@
  frame->slots[7] /* temp__3 */ = create_closure(entry__compiler__sim2c_185, 0);
  // 337: if namespaces(namespace).is_defined:
  // 338:   SyntaxError identifier_of(info) "
  // 339:     An identifier named "@(namespace)::@(name)" was already @
  // 340:     defined@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_190;
}
static void entry__compiler__sim2c_185(void) {
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
  // 338: ... identifier_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_186;
}
static void cont__compiler__sim2c_186(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 338: ... "
  // 339:   An identifier named "@(namespace)::@(name)" was already @
  // 340:   defined@
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
  frame->cont = cont__compiler__sim2c_189;
}
static void cont__compiler__sim2c_189(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 338: SyntaxError identifier_of(info) "
  // 339:   An identifier named "@(namespace)::@(name)" was already @
  // 340:   defined@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__SyntaxError();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_190(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 341: ... used_namespaces(namespace)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* namespace */;
  result_count = 1;
  myself = get__used_namespaces();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_191;
}
static void cont__compiler__sim2c_191(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 341: ... :
  // 342:   if global_names(name).is_defined:
  // 343:     SyntaxError identifier_of(info) "
  // 344:       The definition of "@(namespace)::@(name)" clashes with the @
  // 345:       already defined identifier "@(name)@quot;@
  // 346:   $info_1 top_level_names(name)
  // 347:   if info_1.is_defined:
  // 348:     SyntaxError identifier_of(info) "
  // 349:       The definition of "@(namespace)::@(name)" clashes with the @
  // 350:       definition of "@(namespace_of(identifier_of(info_1)))@
  // ...
  frame->slots[6] /* temp__2 */ = create_closure(entry__compiler__sim2c_192, 0);
  // 341: if used_namespaces(namespace):
  // 342:   if global_names(name).is_defined:
  // 343:     SyntaxError identifier_of(info) "
  // 344:       The definition of "@(namespace)::@(name)" clashes with the @
  // 345:       already defined identifier "@(name)@quot;@
  // 346:   $info_1 top_level_names(name)
  // 347:   if info_1.is_defined:
  // 348:     SyntaxError identifier_of(info) "
  // 349:       The definition of "@(namespace)::@(name)" clashes with the @
  // 350:       definition of "@(namespace_of(identifier_of(info_1)))@
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_213;
}
static void entry__compiler__sim2c_192(void) {
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
  // 342: ... global_names(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__global_names();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_193;
}
static void cont__compiler__sim2c_193(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 342: ... global_names(name).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_194;
}
static void cont__compiler__sim2c_194(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 342: ... :
  // 343:   SyntaxError identifier_of(info) "
  // 344:     The definition of "@(namespace)::@(name)" clashes with the @
  // 345:     already defined identifier "@(name)@quot;@
  frame->slots[7] /* temp__3 */ = create_closure(entry__compiler__sim2c_195, 0);
  // 342: if global_names(name).is_defined:
  // 343:   SyntaxError identifier_of(info) "
  // 344:     The definition of "@(namespace)::@(name)" clashes with the @
  // 345:     already defined identifier "@(name)@quot;@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_201;
}
static void entry__compiler__sim2c_195(void) {
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
  // 343: ... identifier_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_196;
}
static void cont__compiler__sim2c_196(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 343: ... "
  // 344:   The definition of "@(namespace)::@(name)" clashes with the @
  // 345:   already defined identifier "@(name)@quot;@
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
  frame->cont = cont__compiler__sim2c_200;
}
static void cont__compiler__sim2c_200(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 343: SyntaxError identifier_of(info) "
  // 344:   The definition of "@(namespace)::@(name)" clashes with the @
  // 345:   already defined identifier "@(name)@quot;@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__SyntaxError();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_201(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 346: $info_1 top_level_names(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = ((CELL *)frame->slots[3])->contents /* top_level_names */;
  func = myself->type;
  frame->cont = cont__compiler__sim2c_202;
}
static void cont__compiler__sim2c_202(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* info_1 */, arguments->slots[0]);
  // 347: ... info_1.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* info_1 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_203;
}
static void cont__compiler__sim2c_203(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 347: ... :
  // 348:   SyntaxError identifier_of(info) "
  // 349:     The definition of "@(namespace)::@(name)" clashes with the @
  // 350:     definition of "@(namespace_of(identifier_of(info_1)))@
  // 351:     ::@(name)" because both namespaces are used@
  frame->slots[6] /* temp__2 */ = create_closure(entry__compiler__sim2c_204, 0);
  // 347: if info_1.is_defined:
  // 348:   SyntaxError identifier_of(info) "
  // 349:     The definition of "@(namespace)::@(name)" clashes with the @
  // 350:     definition of "@(namespace_of(identifier_of(info_1)))@
  // 351:     ::@(name)" because both namespaces are used@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_211;
}
static void entry__compiler__sim2c_204(void) {
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
  // 348: ... identifier_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_205;
}
static void cont__compiler__sim2c_205(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 350: ... identifier_of(info_1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* info_1 */;
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
  frame->slots[7] /* temp__4 */ = arguments->slots[0];
  // 350: ... namespace_of(identifier_of(info_1))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__4 */;
  result_count = 1;
  myself = get__namespace_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_207;
}
static void cont__compiler__sim2c_207(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 348: ... "
  // 349:   The definition of "@(namespace)::@(name)" clashes with the @
  // 350:   definition of "@(namespace_of(identifier_of(info_1)))@
  // 351:   ::@(name)" because both namespaces are used@
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
  frame->cont = cont__compiler__sim2c_210;
}
static void cont__compiler__sim2c_210(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 348: SyntaxError identifier_of(info) "
  // 349:   The definition of "@(namespace)::@(name)" clashes with the @
  // 350:   definition of "@(namespace_of(identifier_of(info_1)))@
  // 351:   ::@(name)" because both namespaces are used@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__SyntaxError();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_211(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 352: !top_level_names(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = frame->slots[1] /* info */;
  result_count = 1;
  myself = ((CELL *)frame->slots[3])->contents /* top_level_names */;
  func = myself->type;
  frame->cont = cont__compiler__sim2c_212;
}
static void cont__compiler__sim2c_212(void) {
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
static void cont__compiler__sim2c_213(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 353: !namespaces(namespace)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* namespace */;
  arguments->slots[1] = frame->slots[2] /* info */;
  result_count = 1;
  myself = ((CELL *)frame->slots[4])->contents /* namespaces */;
  func = myself->type;
  frame->cont = cont__compiler__sim2c_214;
}
static void cont__compiler__sim2c_214(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* namespaces */ = arguments->slots[0];
  // 354: !exported_names(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = ((CELL *)frame->slots[4])->contents /* namespaces */;
  result_count = 1;
  myself = get__exported_names();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_215;
}
static void cont__compiler__sim2c_215(void) {
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
static void entry__compiler__sim2c_216(void) {
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
  // 356: ... global_names(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__global_names();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_217;
}
static void cont__compiler__sim2c_217(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 356: ... global_names(name).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_218;
}
static void cont__compiler__sim2c_218(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 356: ... :
  // 357:   SyntaxError identifier_of(info) "
  // 358:     An identifier named "@(name)" was already defined@
  frame->slots[6] /* temp__3 */ = create_closure(entry__compiler__sim2c_219, 0);
  // 356: if global_names(name).is_defined:
  // 357:   SyntaxError identifier_of(info) "
  // 358:     An identifier named "@(name)" was already defined@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_222;
}
static void entry__compiler__sim2c_219(void) {
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
  // 357: ... identifier_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_220;
}
static void cont__compiler__sim2c_220(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 357: ... "
  // 358:   An identifier named "@(name)" was already defined@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__b18861f6a8c886ba;
  arguments->slots[1] = frame->slots[1] /* name */;
  arguments->slots[2] = string__95b7f6cc14260ab8;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_221;
}
static void cont__compiler__sim2c_221(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 357: SyntaxError identifier_of(info) "
  // 358:   An identifier named "@(name)" was already defined@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__SyntaxError();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_222(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 359: $namespaces exported_names(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__exported_names();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_223;
}
static void cont__compiler__sim2c_223(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* namespaces */, arguments->slots[0]);
  // 360: ... namespaces.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* namespaces */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_224;
}
static void cont__compiler__sim2c_224(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 360: ... :
  // 361:   for_each namespaces: (nspace _dummy)
  // 362:     if used_namespaces(nspace):
  // 363:       SyntaxError identifier_of(info) "
  // 364:         The definition of "@(name)" clashes with the already @
  // 365:         defined identifier "@(nspace)::@(name)@quot;@
  frame->slots[5] /* temp__2 */ = create_closure(entry__compiler__sim2c_225, 0);
  // 360: if namespaces.is_defined:
  // 361:   for_each namespaces: (nspace _dummy)
  // 362:     if used_namespaces(nspace):
  // 363:       SyntaxError identifier_of(info) "
  // 364:         The definition of "@(name)" clashes with the already @
  // 365:         defined identifier "@(nspace)::@(name)@quot;@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_231;
}
static void entry__compiler__sim2c_228(void) {
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
  // 363: ... identifier_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_229;
}
static void cont__compiler__sim2c_229(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 363: ... "
  // 364:   The definition of "@(name)" clashes with the already @
  // 365:   defined identifier "@(nspace)::@(name)@quot;@
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
  frame->cont = cont__compiler__sim2c_230;
}
static void cont__compiler__sim2c_230(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 363: SyntaxError identifier_of(info) "
  // 364:   The definition of "@(name)" clashes with the already @
  // 365:   defined identifier "@(nspace)::@(name)@quot;@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__SyntaxError();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_226(void) {
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
  // 362: ... used_namespaces(nspace)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* nspace */;
  result_count = 1;
  myself = get__used_namespaces();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_227;
}
static void cont__compiler__sim2c_227(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 362: ... :
  // 363:   SyntaxError identifier_of(info) "
  // 364:     The definition of "@(name)" clashes with the already @
  // 365:     defined identifier "@(nspace)::@(name)@quot;@
  frame->slots[5] /* temp__2 */ = create_closure(entry__compiler__sim2c_228, 0);
  // 362: if used_namespaces(nspace):
  // 363:   SyntaxError identifier_of(info) "
  // 364:     The definition of "@(name)" clashes with the already @
  // 365:     defined identifier "@(nspace)::@(name)@quot;@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_225(void) {
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
  // 361: ... : (nspace _dummy)
  // 362:   if used_namespaces(nspace):
  // 363:     SyntaxError identifier_of(info) "
  // 364:       The definition of "@(name)" clashes with the already @
  // 365:       defined identifier "@(nspace)::@(name)@quot;@
  frame->slots[3] /* temp__1 */ = create_closure(entry__compiler__sim2c_226, 2);
  // 361: for_each namespaces: (nspace _dummy)
  // 362:   if used_namespaces(nspace):
  // 363:     SyntaxError identifier_of(info) "
  // 364:       The definition of "@(name)" clashes with the already @
  // 365:       defined identifier "@(nspace)::@(name)@quot;@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* namespaces */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_231(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 366: !global_names(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__global_names();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_232;
}
static void cont__compiler__sim2c_232(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__global_names(arguments->slots[0]);
  // 367: !top_level_names(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = frame->slots[1] /* info */;
  result_count = 1;
  myself = ((CELL *)frame->slots[2])->contents /* top_level_names */;
  func = myself->type;
  frame->cont = cont__compiler__sim2c_233;
}
static void cont__compiler__sim2c_233(void) {
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
static void entry__compiler__sim2c_173(void) {
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
  // 331: $namespace namespace_of(ident)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* ident */;
  result_count = 1;
  myself = get__namespace_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_174;
}
static void cont__compiler__sim2c_174(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* namespace */, arguments->slots[0]);
  // 332: $name name_of(ident)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* ident */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_175;
}
static void cont__compiler__sim2c_175(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* name */, arguments->slots[0]);
  // 334: namespace.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* namespace */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_176;
}
static void cont__compiler__sim2c_176(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 334: ... :
  // 335:   $$namespaces exported_names(name)
  // 336:   unless namespaces.is_defined: !namespaces table()
  // 337:   if namespaces(namespace).is_defined:
  // 338:     SyntaxError identifier_of(info) "
  // 339:       An identifier named "@(namespace)::@(name)" was already @
  // 340:       defined@
  // 341:   if used_namespaces(namespace):
  // 342:     if global_names(name).is_defined:
  // 343:       SyntaxError identifier_of(info) "
  // ...
  frame->slots[6] /* temp__2 */ = create_closure(entry__compiler__sim2c_177, 0);
  // 355: :
  // 356:   if global_names(name).is_defined:
  // 357:     SyntaxError identifier_of(info) "
  // 358:       An identifier named "@(name)" was already defined@
  // 359:   $namespaces exported_names(name)
  // 360:   if namespaces.is_defined:
  // 361:     for_each namespaces: (nspace _dummy)
  // 362:       if used_namespaces(nspace):
  // 363:         SyntaxError identifier_of(info) "
  // 364:           The definition of "@(name)" clashes with the already @
  // ...
  frame->slots[7] /* temp__3 */ = create_closure(entry__compiler__sim2c_216, 0);
  // 333: if
  // 334:   namespace.is_defined:
  // 335:     $$namespaces exported_names(name)
  // 336:     unless namespaces.is_defined: !namespaces table()
  // 337:     if namespaces(namespace).is_defined:
  // 338:       SyntaxError identifier_of(info) "
  // 339:         An identifier named "@(namespace)::@(name)" was already @
  // 340:         defined@
  // 341:     if used_namespaces(namespace):
  // 342:       if global_names(name).is_defined:
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
static void entry__compiler__sim2c_166(void) {
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
  // 328: $ident identifier_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_167;
}
static void cont__compiler__sim2c_167(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* ident */, arguments->slots[0]);
  // 330: info.is_a_static_single_definition
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__is_a_static_single_definition();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_168;
}
static void cont__compiler__sim2c_168(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 330: ... attribute_of(info).is_defined
  frame->slots[5] /* temp__3 */ = create_closure(entry__compiler__sim2c_169, 0);
  // 330: info.is_a_static_single_definition && attribute_of(info).is_defined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_172;
}
static void entry__compiler__sim2c_169(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // info: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 330: ... attribute_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__attribute_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_170;
}
static void cont__compiler__sim2c_170(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 330: ... attribute_of(info).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_171;
}
static void cont__compiler__sim2c_171(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 330: ... attribute_of(info).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__sim2c_172(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 330: ... :
  // 331:   $namespace namespace_of(ident)
  // 332:   $name name_of(ident)
  // 333:   if
  // 334:     namespace.is_defined:
  // 335:       $$namespaces exported_names(name)
  // 336:       unless namespaces.is_defined: !namespaces table()
  // 337:       if namespaces(namespace).is_defined:
  // 338:         SyntaxError identifier_of(info) "
  // 339:           An identifier named "@(namespace)::@(name)" was already @
  // ...
  frame->slots[6] /* temp__4 */ = create_closure(entry__compiler__sim2c_173, 0);
  // 329: unless
  // 330:   info.is_a_static_single_definition && attribute_of(info).is_defined:
  // 331:     $namespace namespace_of(ident)
  // 332:     $name name_of(ident)
  // 333:     if
  // 334:       namespace.is_defined:
  // 335:         $$namespaces exported_names(name)
  // 336:         unless namespaces.is_defined: !namespaces table()
  // 337:         if namespaces(namespace).is_defined:
  // 338:           SyntaxError identifier_of(info) "
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
static void entry__compiler__sim2c_165(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // defined_names: 0
  // top_level_names: 1
  frame->slots[1] = myself->closure.frame->slots[9]; /* top_level_names */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 327: ... : (info)
  // 328:   $ident identifier_of(info)
  // 329:   unless
  // 330:     info.is_a_static_single_definition && attribute_of(info).is_defined:
  // 331:       $namespace namespace_of(ident)
  // 332:       $name name_of(ident)
  // 333:       if
  // 334:         namespace.is_defined:
  // 335:           $$namespaces exported_names(name)
  // 336:           unless namespaces.is_defined: !namespaces table()
  // ...
  frame->slots[2] /* temp__1 */ = create_closure(entry__compiler__sim2c_166, 1);
  // 327: for_each defined_names: (info)
  // 328:   $ident identifier_of(info)
  // 329:   unless
  // 330:     info.is_a_static_single_definition && attribute_of(info).is_defined:
  // 331:       $namespace namespace_of(ident)
  // 332:       $name name_of(ident)
  // 333:       if
  // 334:         namespace.is_defined:
  // 335:           $$namespaces exported_names(name)
  // 336:           unless namespaces.is_defined: !namespaces table()
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
static void cont__compiler__sim2c_234(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 368: ... :
  // 369:   $$top_level_used_names empty_insert_order_table
  // 370:   for_each all_used_names: (used_names)
  // 371:     for_each used_names: (mangled_name info)
  // 372:       !top_level_used_names(mangled_name) info
  // 373:   check_definitions top_level_names top_level_used_names
  frame->slots[34] /* temp__1 */ = create_closure(entry__compiler__sim2c_235, 0);
  // 368: if do_print_warnings:
  // 369:   $$top_level_used_names empty_insert_order_table
  // 370:   for_each all_used_names: (used_names)
  // 371:     for_each used_names: (mangled_name info)
  // 372:       !top_level_used_names(mangled_name) info
  // 373:   check_definitions top_level_names top_level_used_names
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_print_warnings();
  arguments->slots[1] = frame->slots[34] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_240;
}
static void entry__compiler__sim2c_235(void) {
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
  // 369: $$top_level_used_names empty_insert_order_table
  ((CELL *)frame->slots[2])->contents /* top_level_used_names */ = get__empty_insert_order_table();
  // 370: ... : (used_names)
  // 371:   for_each used_names: (mangled_name info)
  // 372:     !top_level_used_names(mangled_name) info
  frame->slots[3] /* temp__1 */ = create_closure(entry__compiler__sim2c_236, 1);
  // 370: for_each all_used_names: (used_names)
  // 371:   for_each used_names: (mangled_name info)
  // 372:     !top_level_used_names(mangled_name) info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* all_used_names */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_239;
}
static void entry__compiler__sim2c_237(void) {
  allocate_initialized_frame_gc(3, 3);
  // slot allocations:
  // mangled_name: 0
  // info: 1
  // top_level_used_names: 2
  frame->slots[2] = myself->closure.frame->slots[1]; /* top_level_used_names */
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 372: !top_level_used_names(mangled_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mangled_name */;
  arguments->slots[1] = frame->slots[1] /* info */;
  result_count = 1;
  myself = ((CELL *)frame->slots[2])->contents /* top_level_used_names */;
  func = myself->type;
  frame->cont = cont__compiler__sim2c_238;
}
static void cont__compiler__sim2c_238(void) {
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
static void entry__compiler__sim2c_236(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // used_names: 0
  // top_level_used_names: 1
  frame->slots[1] = myself->closure.frame->slots[2]; /* top_level_used_names */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 371: ... : (mangled_name info)
  // 372:   !top_level_used_names(mangled_name) info
  frame->slots[2] /* temp__1 */ = create_closure(entry__compiler__sim2c_237, 2);
  // 371: for_each used_names: (mangled_name info)
  // 372:   !top_level_used_names(mangled_name) info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* used_names */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_239(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 373: check_definitions top_level_names top_level_used_names
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* top_level_names */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* top_level_used_names */;
  result_count = frame->caller_result_count;
  myself = get__check_definitions();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_240(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 374: ... : write_timing_info "analyzing" filenames(1)
  frame->slots[34] /* temp__1 */ = create_closure(entry__compiler__sim2c_241, 0);
  // 374: if do_time_passes: write_timing_info "analyzing" filenames(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = frame->slots[34] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_244;
}
static void entry__compiler__sim2c_241(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // filenames: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* filenames */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 374: ... filenames(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* filenames */;
  func = myself->type;
  frame->cont = cont__compiler__sim2c_242;
}
static void cont__compiler__sim2c_242(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 374: ... write_timing_info "analyzing" filenames(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__5ab424ea8372e502;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write_timing_info();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_244(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 375: ... :
  // 376:   for_each trees: (tree) write debug_string(strip(tree) 0 99)
  // 377:   terminate
  frame->slots[34] /* temp__1 */ = create_closure(entry__compiler__sim2c_245, 0);
  // 375: if do_dump_trees:
  // 376:   for_each trees: (tree) write debug_string(strip(tree) 0 99)
  // 377:   terminate
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_dump_trees();
  arguments->slots[1] = frame->slots[34] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_250;
}
static void entry__compiler__sim2c_245(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // trees: 0
  frame->slots[0] = myself->closure.frame->slots[5]; /* trees */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 376: for_each trees: (tree) write debug_string(strip(tree) 0 99)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* trees */;
  arguments->slots[1] = func__compiler__sim2c_246;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_249;
}
static void entry__compiler__sim2c_246(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // tree: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 376: ... strip(tree)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* tree */;
  result_count = 1;
  myself = get__strip();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_247;
}
static void cont__compiler__sim2c_247(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 376: ... debug_string(strip(tree) 0 99)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = number__0;
  arguments->slots[2] = number__99;
  result_count = 1;
  myself = get__debug_string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_248;
}
static void cont__compiler__sim2c_248(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 376: ... write debug_string(strip(tree) 0 99)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_249(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 377: terminate
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__terminate();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_250(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 382: %%named_constants empty_table
  set__named_constants(get__empty_table());
  // 383: for_each trees: (tree)
  // 384:   if tree.is_an_assignment:
  // 385:     $arguments arguments_of(tree)
  // 386:     $destination arguments(1)
  // 387:     $source arguments(2)
  // 388:     
  // 389:     #
  // 390:       namespaced objects could be modified elsewhere
  // 391:     
  // 392:     if
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* trees */;
  arguments->slots[1] = func__compiler__sim2c_251;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_278;
}
static void entry__compiler__sim2c_274(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // destination: 0
  // source: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* destination */
  frame->slots[1] = myself->closure.frame->slots[3]; /* source */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 401: !named_constants(name_of(identifier_of(destination)))
  // 402:   source(.is_a_reference true)
  {
    NODE *temp = clone_object_and_attributes(frame->slots[1] /* source */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__is_a_reference, get__true());
    frame->slots[2] /* temp__1 */ = temp;

  }
  // 401: ... identifier_of(destination)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* destination */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_275;
}
static void cont__compiler__sim2c_275(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 401: ... name_of(identifier_of(destination))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_276;
}
static void cont__compiler__sim2c_276(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 401: !named_constants(name_of(identifier_of(destination)))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__named_constants();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_277;
}
static void cont__compiler__sim2c_277(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__named_constants(arguments->slots[0]);
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__sim2c_253(void) {
  allocate_initialized_frame_gc(1, 8);
  // slot allocations:
  // tree: 0
  // arguments: 1
  // destination: 2
  // source: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* tree */
  frame->slots[1] /* arguments */ = create_future();
  frame->slots[2] /* destination */ = create_future();
  frame->slots[3] /* source */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 385: $arguments arguments_of(tree)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* tree */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_254;
}
static void cont__compiler__sim2c_254(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* arguments */, arguments->slots[0]);
  // 386: $destination arguments(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[1] /* arguments */;
  func = myself->type;
  frame->cont = cont__compiler__sim2c_255;
}
static void cont__compiler__sim2c_255(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* destination */, arguments->slots[0]);
  // 387: $source arguments(2)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = frame->slots[1] /* arguments */;
  func = myself->type;
  frame->cont = cont__compiler__sim2c_256;
}
static void cont__compiler__sim2c_256(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* source */, arguments->slots[0]);
  // 394: destination.is_a_static_single_definition
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* destination */;
  result_count = 1;
  myself = get__is_a_static_single_definition();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_257;
}
static void cont__compiler__sim2c_257(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  frame->slots[6] /* temp__3 */ = create_closure(entry__compiler__sim2c_258, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_273;
}
static void entry__compiler__sim2c_258(void) {
  allocate_initialized_frame_gc(2, 7);
  // slot allocations:
  // destination: 0
  // source: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* destination */
  frame->slots[1] = myself->closure.frame->slots[3]; /* source */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 395: ... identifier_of(destination)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* destination */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_259;
}
static void cont__compiler__sim2c_259(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 395: namespace_of(identifier_of(destination))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = get__namespace_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_260;
}
static void cont__compiler__sim2c_260(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 395: namespace_of(identifier_of(destination)).is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_261;
}
static void cont__compiler__sim2c_261(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  frame->slots[6] /* temp__5 */ = create_closure(entry__compiler__sim2c_262, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[6] /* temp__5 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_272;
}
static void entry__compiler__sim2c_262(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // source: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* source */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 396: ... source.is_a_polymorphic_function_constant
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  result_count = 1;
  myself = get__is_a_polymorphic_function_constant();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_263;
}
static void cont__compiler__sim2c_263(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 396: not(source.is_a_polymorphic_function_constant)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__not();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_264;
}
static void cont__compiler__sim2c_264(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  frame->slots[4] /* temp__4 */ = create_closure(entry__compiler__sim2c_265, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_271;
}
static void entry__compiler__sim2c_265(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // source: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* source */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 398: ... source.is_a_c_body
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  result_count = 1;
  myself = get__is_a_c_body();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_266;
}
static void cont__compiler__sim2c_266(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 398: not(source.is_a_c_body)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__not();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_267;
}
static void cont__compiler__sim2c_267(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 399: source.is_a_constant
  frame->slots[4] /* temp__4 */ = create_closure(entry__compiler__sim2c_268, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_270;
}
static void entry__compiler__sim2c_268(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // source: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* source */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 399: source.is_a_constant
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  result_count = 1;
  myself = get__is_a_constant();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_269;
}
static void cont__compiler__sim2c_269(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 399: source.is_a_constant
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__sim2c_270(void) {
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
static void cont__compiler__sim2c_271(void) {
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
static void cont__compiler__sim2c_272(void) {
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
static void cont__compiler__sim2c_273(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 400: :
  // 401:   !named_constants(name_of(identifier_of(destination)))
  // 402:     source(.is_a_reference true)
  frame->slots[7] /* temp__4 */ = create_closure(entry__compiler__sim2c_274, 0);
  // 392: if
  // 393:   &&
  // 394:     destination.is_a_static_single_definition
  // 395:     namespace_of(identifier_of(destination)).is_undefined
  // 396:     not(source.is_a_polymorphic_function_constant)
  // 397:     #not(source.is_a_body)
  // 398:     not(source.is_a_c_body)
  // 399:     source.is_a_constant
  // 400:   :
  // 401:     !named_constants(name_of(identifier_of(destination)))
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_251(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // tree: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 384: ... tree.is_an_assignment
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* tree */;
  result_count = 1;
  myself = get__is_an_assignment();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_252;
}
static void cont__compiler__sim2c_252(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 384: ... :
  // 385:   $arguments arguments_of(tree)
  // 386:   $destination arguments(1)
  // 387:   $source arguments(2)
  // 388:   
  // 389:   #
  // 390:     namespaced objects could be modified elsewhere
  // 391:   
  // 392:   if
  // 393:     &&
  // ...
  frame->slots[2] /* temp__2 */ = create_closure(entry__compiler__sim2c_253, 0);
  // 384: if tree.is_an_assignment:
  // 385:   $arguments arguments_of(tree)
  // 386:   $destination arguments(1)
  // 387:   $source arguments(2)
  // 388:   
  // 389:   #
  // 390:     namespaced objects could be modified elsewhere
  // 391:   
  // 392:   if
  // 393:     &&
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_278(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 407: for_each trees: (tree)
  // 408:   if tree.is_an_assignment:
  // 409:     $destination arguments_of(tree)(1)
  // 410:     if
  // 411:       &&
  // 412:         destination.is_a_static_single_definition
  // 413:         attribute_kind_of(destination) != NONE
  // 414:       :
  // 415:         !named_constants(identifier_of(destination).to_string) undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* trees */;
  arguments->slots[1] = func__compiler__sim2c_279;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_294;
}
static void entry__compiler__sim2c_290(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // destination: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* destination */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 415: ... identifier_of(destination)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* destination */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_291;
}
static void cont__compiler__sim2c_291(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 415: ... identifier_of(destination).to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_292;
}
static void cont__compiler__sim2c_292(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 415: !named_constants(identifier_of(destination).to_string)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = get__undefined();
  result_count = 1;
  myself = get__named_constants();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_293;
}
static void cont__compiler__sim2c_293(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__named_constants(arguments->slots[0]);
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__sim2c_281(void) {
  allocate_initialized_frame_gc(1, 6);
  // slot allocations:
  // tree: 0
  // destination: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* tree */
  frame->slots[1] /* destination */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 409: ... arguments_of(tree)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* tree */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_282;
}
static void cont__compiler__sim2c_282(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 409: $destination arguments_of(tree)(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[2] /* temp__1 */;
  func = myself->type;
  frame->cont = cont__compiler__sim2c_283;
}
static void cont__compiler__sim2c_283(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* destination */, arguments->slots[0]);
  // 412: destination.is_a_static_single_definition
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* destination */;
  result_count = 1;
  myself = get__is_a_static_single_definition();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_284;
}
static void cont__compiler__sim2c_284(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 413: attribute_kind_of(destination) != NONE
  frame->slots[4] /* temp__3 */ = create_closure(entry__compiler__sim2c_285, 0);
  // 411: &&
  // 412:   destination.is_a_static_single_definition
  // 413:   attribute_kind_of(destination) != NONE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_289;
}
static void entry__compiler__sim2c_285(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // destination: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* destination */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 413: attribute_kind_of(destination)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* destination */;
  result_count = 1;
  myself = get__attribute_kind_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_286;
}
static void cont__compiler__sim2c_286(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 413: attribute_kind_of(destination) != NONE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = get__NONE();
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_287;
}
static void cont__compiler__sim2c_287(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 413: attribute_kind_of(destination) != NONE
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_288;
}
static void cont__compiler__sim2c_288(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 413: attribute_kind_of(destination) != NONE
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__sim2c_289(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 414: :
  // 415:   !named_constants(identifier_of(destination).to_string) undefined
  frame->slots[5] /* temp__4 */ = create_closure(entry__compiler__sim2c_290, 0);
  // 410: if
  // 411:   &&
  // 412:     destination.is_a_static_single_definition
  // 413:     attribute_kind_of(destination) != NONE
  // 414:   :
  // 415:     !named_constants(identifier_of(destination).to_string) undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_279(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // tree: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 408: ... tree.is_an_assignment
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* tree */;
  result_count = 1;
  myself = get__is_an_assignment();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_280;
}
static void cont__compiler__sim2c_280(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 408: ... :
  // 409:   $destination arguments_of(tree)(1)
  // 410:   if
  // 411:     &&
  // 412:       destination.is_a_static_single_definition
  // 413:       attribute_kind_of(destination) != NONE
  // 414:     :
  // 415:       !named_constants(identifier_of(destination).to_string) undefined
  frame->slots[2] /* temp__2 */ = create_closure(entry__compiler__sim2c_281, 0);
  // 408: if tree.is_an_assignment:
  // 409:   $destination arguments_of(tree)(1)
  // 410:   if
  // 411:     &&
  // 412:       destination.is_a_static_single_definition
  // 413:       attribute_kind_of(destination) != NONE
  // 414:     :
  // 415:       !named_constants(identifier_of(destination).to_string) undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_294(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 416: $$all_definitions empty_list
  ((CELL *)frame->slots[10])->contents /* all_definitions */ = get__empty_list();
  // 417: $$all_statements empty_list
  ((CELL *)frame->slots[11])->contents /* all_statements */ = get__empty_list();
  // 418: $$max_temp_idx 0
  ((CELL *)frame->slots[12])->contents /* max_temp_idx */ = number__0;
  // 419: ... : (tree)
  // 420:   unless tree.is_a_remark || tree.is_a_meta_instruction:
  // 421:     %%compiler::temp_idx 0
  // 422:     %%compiler::actions empty_list
  // 423:     %already_defined_names top_level_names
  // 424:     %%definitions empty_list
  // 425:     %%statements empty_list
  // 426:     simplify_statement tree
  // 427:     push &all_statements statements
  // 428:     push &all_definitions definitions
  // ...
  frame->slots[34] /* temp__1 */ = create_closure(entry__compiler__sim2c_295, 1);
  // 419: for_each trees: (tree)
  // 420:   unless tree.is_a_remark || tree.is_a_meta_instruction:
  // 421:     %%compiler::temp_idx 0
  // 422:     %%compiler::actions empty_list
  // 423:     %already_defined_names top_level_names
  // 424:     %%definitions empty_list
  // 425:     %%statements empty_list
  // 426:     simplify_statement tree
  // 427:     push &all_statements statements
  // 428:     push &all_definitions definitions
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* trees */;
  arguments->slots[1] = frame->slots[34] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_308;
}
static void entry__compiler__sim2c_300(void) {
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
  // 421: %%compiler::temp_idx 0
  set__compiler__temp_idx(number__0);
  // 422: %%compiler::actions empty_list
  set__compiler__actions(get__empty_list());
  // 423: %already_defined_names top_level_names
  initialize_maybe_future(get__already_defined_names(), ((CELL *)frame->slots[1])->contents /* top_level_names */);
  // 424: %%definitions empty_list
  set__definitions(get__empty_list());
  // 425: %%statements empty_list
  set__statements(get__empty_list());
  // 426: simplify_statement tree
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* tree */;
  result_count = 0;
  myself = get__simplify_statement();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_301;
}
static void cont__compiler__sim2c_301(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 427: push &all_statements statements
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* all_statements */;
  arguments->slots[1] = get__statements();
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_302;
}
static void cont__compiler__sim2c_302(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* all_statements */ = arguments->slots[0];
  // 428: push &all_definitions definitions
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* all_definitions */;
  arguments->slots[1] = get__definitions();
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_303;
}
static void cont__compiler__sim2c_303(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* all_definitions */ = arguments->slots[0];
  // 429: $tmp_idx temp_idx
  initialize_maybe_future(frame->slots[7] /* tmp_idx */, get__temp_idx());
  // 430: ... : extend_to &max_temp_idx tmp_idx
  frame->slots[8] /* temp__1 */ = create_closure(entry__compiler__sim2c_304, 0);
  // 430: push &actions: extend_to &max_temp_idx tmp_idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[8] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_306;
}
static void entry__compiler__sim2c_304(void) {
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
  // 430: ... extend_to &max_temp_idx tmp_idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* max_temp_idx */;
  arguments->slots[1] = frame->slots[1] /* tmp_idx */;
  result_count = 1;
  myself = get__extend_to();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_305;
}
static void cont__compiler__sim2c_305(void) {
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
static void cont__compiler__sim2c_306(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__actions(arguments->slots[0]);
  // 431: push &all_actions actions
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[6])->contents /* all_actions */;
  arguments->slots[1] = get__actions();
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_307;
}
static void cont__compiler__sim2c_307(void) {
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
static void entry__compiler__sim2c_295(void) {
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
  // 420: ... tree.is_a_remark
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* tree */;
  result_count = 1;
  myself = get__is_a_remark();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_296;
}
static void cont__compiler__sim2c_296(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 420: ... tree.is_a_meta_instruction
  frame->slots[8] /* temp__3 */ = create_closure(entry__compiler__sim2c_297, 0);
  // 420: ... tree.is_a_remark || tree.is_a_meta_instruction
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  arguments->slots[1] = frame->slots[8] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_299;
}
static void entry__compiler__sim2c_297(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // tree: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* tree */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 420: ... tree.is_a_meta_instruction
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* tree */;
  result_count = 1;
  myself = get__is_a_meta_instruction();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_298;
}
static void cont__compiler__sim2c_298(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 420: ... tree.is_a_meta_instruction
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__sim2c_299(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 420: ... :
  // 421:   %%compiler::temp_idx 0
  // 422:   %%compiler::actions empty_list
  // 423:   %already_defined_names top_level_names
  // 424:   %%definitions empty_list
  // 425:   %%statements empty_list
  // 426:   simplify_statement tree
  // 427:   push &all_statements statements
  // 428:   push &all_definitions definitions
  // 429:   $tmp_idx temp_idx
  // ...
  frame->slots[9] /* temp__4 */ = create_closure(entry__compiler__sim2c_300, 0);
  // 420: unless tree.is_a_remark || tree.is_a_meta_instruction:
  // 421:   %%compiler::temp_idx 0
  // 422:   %%compiler::actions empty_list
  // 423:   %already_defined_names top_level_names
  // 424:   %%definitions empty_list
  // 425:   %%statements empty_list
  // 426:   simplify_statement tree
  // 427:   push &all_statements statements
  // 428:   push &all_definitions definitions
  // 429:   $tmp_idx temp_idx
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
static void cont__compiler__sim2c_308(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 432: for_each all_actions: (stmt_actions) for_each stmt_actions: (action) action
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[8])->contents /* all_actions */;
  arguments->slots[1] = func__compiler__sim2c_309;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_311;
}
static void entry__compiler__sim2c_310(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // action: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 432: ... action
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* action */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_309(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // stmt_actions: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 432: ... for_each stmt_actions: (action) action
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stmt_actions */;
  arguments->slots[1] = func__compiler__sim2c_310;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_311(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 433: !all_actions empty_list
  ((CELL *)frame->slots[8])->contents /* all_actions */ = get__empty_list();
  // 434: ... : write_timing_info "simplifying" filenames(1)
  frame->slots[34] /* temp__1 */ = create_closure(entry__compiler__sim2c_312, 0);
  // 434: if do_time_passes: write_timing_info "simplifying" filenames(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = frame->slots[34] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_315;
}
static void entry__compiler__sim2c_312(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // filenames: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* filenames */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 434: ... filenames(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* filenames */;
  func = myself->type;
  frame->cont = cont__compiler__sim2c_313;
}
static void cont__compiler__sim2c_313(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 434: ... write_timing_info "simplifying" filenames(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__72ed7b1f2279c943;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write_timing_info();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_315(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 435: ... :
  // 436:   for_each
  // 437:     all_definitions: (defs)
  // 438:       for_each defs: (def)
  // 439:         if
  // 440:           def.is_a_key_value_pair:
  // 441:             writeln
  // 442:               assignment(.arguments_of list(key_of(def) std::value_of(def)))
  // 443:           :
  // 444:             writeln "_define " def
  // ...
  frame->slots[34] /* temp__1 */ = create_closure(entry__compiler__sim2c_316, 0);
  // 435: if do_print_simplified_source:
  // 436:   for_each
  // 437:     all_definitions: (defs)
  // 438:       for_each defs: (def)
  // 439:         if
  // 440:           def.is_a_key_value_pair:
  // 441:             writeln
  // 442:               assignment(.arguments_of list(key_of(def) std::value_of(def)))
  // 443:           :
  // 444:             writeln "_define " def
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_print_simplified_source();
  arguments->slots[1] = frame->slots[34] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_329;
}
static void entry__compiler__sim2c_316(void) {
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
  // 436: for_each
  // 437:   all_definitions: (defs)
  // 438:     for_each defs: (def)
  // 439:       if
  // 440:         def.is_a_key_value_pair:
  // 441:           writeln
  // 442:             assignment(.arguments_of list(key_of(def) std::value_of(def)))
  // 443:         :
  // 444:           writeln "_define " def
  // 445:   :
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* all_definitions */;
  arguments->slots[1] = func__compiler__sim2c_317;
  arguments->slots[2] = get__writeln();
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_326;
}
static void entry__compiler__sim2c_320(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // def: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* def */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 442: ... key_of(def)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* def */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_321;
}
static void cont__compiler__sim2c_321(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 442: ... std::value_of(def)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* def */;
  result_count = 1;
  myself = get__std__value_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_322;
}
static void cont__compiler__sim2c_322(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 442: ... list(key_of(def) std::value_of(def))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_323;
}
static void cont__compiler__sim2c_323(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 442: assignment(.arguments_of list(key_of(def) std::value_of(def)))
  {
    NODE *temp = clone_object_and_attributes(get__assignment());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[2] /* temp__2 */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 441: writeln
  // 442:   assignment(.arguments_of list(key_of(def) std::value_of(def)))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_324(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // def: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* def */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 444: writeln "_define " def
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7c84ae5484fdf7e0;
  arguments->slots[1] = frame->slots[0] /* def */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_318(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // def: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 440: def.is_a_key_value_pair
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* def */;
  result_count = 1;
  myself = get__is_a_key_value_pair();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_319;
}
static void cont__compiler__sim2c_319(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 440: ... :
  // 441:   writeln
  // 442:     assignment(.arguments_of list(key_of(def) std::value_of(def)))
  frame->slots[2] /* temp__2 */ = create_closure(entry__compiler__sim2c_320, 0);
  // 443: :
  // 444:   writeln "_define " def
  frame->slots[3] /* temp__3 */ = create_closure(entry__compiler__sim2c_324, 0);
  // 439: if
  // 440:   def.is_a_key_value_pair:
  // 441:     writeln
  // 442:       assignment(.arguments_of list(key_of(def) std::value_of(def)))
  // 443:   :
  // 444:     writeln "_define " def
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
static void entry__compiler__sim2c_317(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // defs: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 438: for_each defs: (def)
  // 439:   if
  // 440:     def.is_a_key_value_pair:
  // 441:       writeln
  // 442:         assignment(.arguments_of list(key_of(def) std::value_of(def)))
  // 443:     :
  // 444:       writeln "_define " def
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* defs */;
  arguments->slots[1] = func__compiler__sim2c_318;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_326(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 447: for_each all_statements: (stmts) print_trees stmts
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* all_statements */;
  arguments->slots[1] = func__compiler__sim2c_327;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_328;
}
static void entry__compiler__sim2c_327(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // stmts: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 447: ... print_trees stmts
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stmts */;
  result_count = frame->caller_result_count;
  myself = get__print_trees();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_328(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 448: terminate
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__terminate();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_329(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 470: ... : (used_names)
  // 471:   for_each used_names: (mangled_name info) need mangled_name info
  frame->slots[34] /* temp__1 */ = create_closure(entry__compiler__sim2c_330, 1);
  // 470: for_each all_used_names: (used_names)
  // 471:   for_each used_names: (mangled_name info) need mangled_name info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[7])->contents /* all_used_names */;
  arguments->slots[1] = frame->slots[34] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_332;
}
static void entry__compiler__sim2c_331(void) {
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
  // 471: ... need mangled_name info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mangled_name */;
  arguments->slots[1] = frame->slots[1] /* info */;
  result_count = frame->caller_result_count;
  myself = frame->slots[2] /* need */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_330(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // used_names: 0
  // need: 1
  frame->slots[1] = myself->closure.frame->slots[13]; /* need */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 471: ... : (mangled_name info) need mangled_name info
  frame->slots[2] /* temp__1 */ = create_closure(entry__compiler__sim2c_331, 2);
  // 471: for_each used_names: (mangled_name info) need mangled_name info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* used_names */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_332(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 472: ... : write_timing_info "mangling" filenames(1)
  frame->slots[34] /* temp__1 */ = create_closure(entry__compiler__sim2c_333, 0);
  // 472: if do_time_passes: write_timing_info "mangling" filenames(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = frame->slots[34] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_336;
}
static void entry__compiler__sim2c_333(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // filenames: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* filenames */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 472: ... filenames(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* filenames */;
  func = myself->type;
  frame->cont = cont__compiler__sim2c_334;
}
static void cont__compiler__sim2c_334(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 472: ... write_timing_info "mangling" filenames(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7690af9104a5e1e7;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write_timing_info();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_336(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 473: if do_check_only terminate
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_check_only();
  arguments->slots[1] = get__terminate();
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_337;
}
static void cont__compiler__sim2c_337(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 474: $$generated_declarations ""
  ((CELL *)frame->slots[14])->contents /* generated_declarations */ = empty_string;
  // 475: $$generated_top_level_variable_names ""
  ((CELL *)frame->slots[15])->contents /* generated_top_level_variable_names */ = empty_string;
  // 476: $$generated_top_level_variable_declarations ""
  ((CELL *)frame->slots[16])->contents /* generated_top_level_variable_declarations */ = empty_string;
  // 477: $$generated_global_variable_declarations ""
  ((CELL *)frame->slots[17])->contents /* generated_global_variable_declarations */ = empty_string;
  // 478: $$generated_continuation_table ""
  ((CELL *)frame->slots[18])->contents /* generated_continuation_table */ = empty_string;
  // 479: $$generated_delayed_continuation_table ""
  ((CELL *)frame->slots[19])->contents /* generated_delayed_continuation_table */ = empty_string;
  // 480: $$generated_functions ""
  ((CELL *)frame->slots[20])->contents /* generated_functions */ = empty_string;
  // 482: $$generated_phase_1 ""
  // 483:   #
  // 484:     register module information
  // 485:     define polymorphic functions
  // 486:     define privileged polymorphic functions (with short access paths)
  // 487:     define C functions
  // 488:     register (use) polymorphic functions
  ((CELL *)frame->slots[21])->contents /* generated_phase_1 */ = empty_string;
  // 490: $$generated_phase_2 ""
  // 491:   #
  // 492:     define non-garbage-collected objects:
  // 493:       numeric literals
  // 494:       character literals
  // 495:       string literals
  // 496:       function literals
  // 497:       inline-C functions
  ((CELL *)frame->slots[22])->contents /* generated_phase_2 */ = empty_string;
  // 499: $$generated_phase_3 ""
  // 500:   #
  // 501:     reassign memory pool to save literals from garbage collection
  // 502:     create futures
  // 503:     create futures with prototypes
  // 504:     define garbage-collectec objects:
  // 505:       single-assign static variables
  // 506:       multi-assign static variables
  // 507:       single-assign dynamic variables
  // 508:       multi-assign dynamic variables
  ((CELL *)frame->slots[23])->contents /* generated_phase_3 */ = empty_string;
  // 510: $$generated_phase_4 ""
  // 511:   #
  // 512:     define attributes
  // 513:     define methods
  // 514:     define type functions
  // 515:     
  // 516:     attributes and methods are not directly added to the type-objects, but to
  // 517:     the symbol tree
  // 518:     
  // 519:     at the end of phase 3 <resolve attributes> is called and for every object
  // ...
  ((CELL *)frame->slots[24])->contents /* generated_phase_4 */ = empty_string;
  // 529: $$generated_phase_5 ""
  // 530:   #
  // 531:     create functions
  // 532:     define constants
  // 533:     assign values # inherit attributes
  // 534:     assign variables
  // 535:     initialize futures
  // 536:     maybe initialize futures
  // 537:     
  // 538:     <assign_value> is responsible for attribute and method inheritance
  // ...
  ((CELL *)frame->slots[25])->contents /* generated_phase_5 */ = empty_string;
  // 545: $$generated_phase_6 ""
  // 546:   #
  // 547:     assign values
  ((CELL *)frame->slots[26])->contents /* generated_phase_6 */ = empty_string;
  // 549: $$generated_code ""
  ((CELL *)frame->slots[27])->contents /* generated_code */ = empty_string;
  // 550: $$generated_collections ""
  ((CELL *)frame->slots[28])->contents /* generated_collections */ = empty_string;
  // 551: $$delayed_statements ""
  ((CELL *)frame->slots[29])->contents /* delayed_statements */ = empty_string;
  // 552: $$used_literals empty_table
  ((CELL *)frame->slots[30])->contents /* used_literals */ = get__empty_table();
  // 553: %%used_string_literals empty_table
  set__used_string_literals(get__empty_table());
  // 555: ... : (args*)
  // 556:   $txt string(args*)
  // 557:   push &actions: append &generated_declarations txt
  frame->slots[34] /* temp__1 */ = create_closure(entry__compiler__sim2c_338, -1);
  // 555: %compiler::write_to_declarations: (args*)
  // 556:   $txt string(args*)
  // 557:   push &actions: append &generated_declarations txt
  initialize_future(get__compiler__write_to_declarations(), frame->slots[34] /* temp__1 */);
  // 559: ... : (args*)
  // 560:   $txt string(args*)
  // 561:   push &actions: append &generated_top_level_variable_names txt
  frame->slots[34] /* temp__1 */ = create_closure(entry__compiler__sim2c_343, -1);
  // 559: %compiler::write_to_top_level_variable_names: (args*)
  // 560:   $txt string(args*)
  // 561:   push &actions: append &generated_top_level_variable_names txt
  initialize_future(get__compiler__write_to_top_level_variable_names(), frame->slots[34] /* temp__1 */);
  // 563: ... : (args*)
  // 564:   $txt string(args*)
  // 565:   push &actions: append &generated_top_level_variable_declarations txt
  frame->slots[34] /* temp__1 */ = create_closure(entry__compiler__sim2c_348, -1);
  // 563: %compiler::write_to_top_level_variable_declarations: (args*)
  // 564:   $txt string(args*)
  // 565:   push &actions: append &generated_top_level_variable_declarations txt
  initialize_future(get__compiler__write_to_top_level_variable_declarations(), frame->slots[34] /* temp__1 */);
  // 567: ... : (args*)
  // 568:   $txt string(args*)
  // 569:   push &actions: append &generated_global_variable_declarations txt
  frame->slots[34] /* temp__1 */ = create_closure(entry__compiler__sim2c_353, -1);
  // 567: %compiler::write_to_global_variable_declarations: (args*)
  // 568:   $txt string(args*)
  // 569:   push &actions: append &generated_global_variable_declarations txt
  initialize_future(get__compiler__write_to_global_variable_declarations(), frame->slots[34] /* temp__1 */);
  // 571: ... : (args*)
  // 572:   $txt string(args*)
  // 573:   push &actions: append &generated_continuation_table txt
  frame->slots[34] /* temp__1 */ = create_closure(entry__compiler__sim2c_358, -1);
  // 571: %compiler::write_to_continuation_table: (args*)
  // 572:   $txt string(args*)
  // 573:   push &actions: append &generated_continuation_table txt
  initialize_future(get__compiler__write_to_continuation_table(), frame->slots[34] /* temp__1 */);
  // 575: ... : (args*)
  // 576:   $txt string(args*)
  // 577:   push &actions: append &generated_delayed_continuation_table txt
  frame->slots[34] /* temp__1 */ = create_closure(entry__compiler__sim2c_363, -1);
  // 575: %compiler::write_to_delayed_continuation_table: (args*)
  // 576:   $txt string(args*)
  // 577:   push &actions: append &generated_delayed_continuation_table txt
  initialize_future(get__compiler__write_to_delayed_continuation_table(), frame->slots[34] /* temp__1 */);
  // 579: ... : (args*)
  // 580:   $txt string(args*)
  // 581:   push &actions: append &generated_functions txt
  frame->slots[34] /* temp__1 */ = create_closure(entry__compiler__sim2c_368, -1);
  // 579: %compiler::write_to_functions: (args*)
  // 580:   $txt string(args*)
  // 581:   push &actions: append &generated_functions txt
  initialize_future(get__compiler__write_to_functions(), frame->slots[34] /* temp__1 */);
  // 583: ... : (args*)
  // 584:   $txt string(args*)
  // 585:   push &actions: append &generated_phase_1 txt
  frame->slots[34] /* temp__1 */ = create_closure(entry__compiler__sim2c_373, -1);
  // 583: %compiler::write_to_phase_1: (args*)
  // 584:   $txt string(args*)
  // 585:   push &actions: append &generated_phase_1 txt
  initialize_future(get__compiler__write_to_phase_1(), frame->slots[34] /* temp__1 */);
  // 587: ... : (args*)
  // 588:   $txt string(args*)
  // 589:   push &actions: append &generated_phase_2 txt
  frame->slots[34] /* temp__1 */ = create_closure(entry__compiler__sim2c_378, -1);
  // 587: %compiler::write_to_phase_2: (args*)
  // 588:   $txt string(args*)
  // 589:   push &actions: append &generated_phase_2 txt
  initialize_future(get__compiler__write_to_phase_2(), frame->slots[34] /* temp__1 */);
  // 591: ... : (args*)
  // 592:   $txt string(args*)
  // 593:   push &actions: append &generated_phase_3 txt
  frame->slots[34] /* temp__1 */ = create_closure(entry__compiler__sim2c_383, -1);
  // 591: %compiler::write_to_phase_3: (args*)
  // 592:   $txt string(args*)
  // 593:   push &actions: append &generated_phase_3 txt
  initialize_future(get__compiler__write_to_phase_3(), frame->slots[34] /* temp__1 */);
  // 595: ... : (args*)
  // 596:   $txt string(args*)
  // 597:   push &actions: append &generated_phase_4 txt
  frame->slots[34] /* temp__1 */ = create_closure(entry__compiler__sim2c_388, -1);
  // 595: %compiler::write_to_phase_4: (args*)
  // 596:   $txt string(args*)
  // 597:   push &actions: append &generated_phase_4 txt
  initialize_future(get__compiler__write_to_phase_4(), frame->slots[34] /* temp__1 */);
  // 599: ... : (args*)
  // 600:   $txt string(args*)
  // 601:   push &actions: append &generated_phase_5 txt
  frame->slots[34] /* temp__1 */ = create_closure(entry__compiler__sim2c_393, -1);
  // 599: %compiler::write_to_phase_5: (args*)
  // 600:   $txt string(args*)
  // 601:   push &actions: append &generated_phase_5 txt
  initialize_future(get__compiler__write_to_phase_5(), frame->slots[34] /* temp__1 */);
  // 603: ... : (args*)
  // 604:   $txt string(args*)
  // 605:   push &actions: append &generated_phase_6 txt
  frame->slots[34] /* temp__1 */ = create_closure(entry__compiler__sim2c_398, -1);
  // 603: %compiler::write_to_phase_6: (args*)
  // 604:   $txt string(args*)
  // 605:   push &actions: append &generated_phase_6 txt
  initialize_future(get__compiler__write_to_phase_6(), frame->slots[34] /* temp__1 */);
  // 607: ... : (name literal)
  // 608:   push &actions: !used_literals(name) literal
  frame->slots[34] /* temp__1 */ = create_closure(entry__compiler__sim2c_403, 2);
  // 607: %compiler::use_literal: (name literal)
  // 608:   push &actions: !used_literals(name) literal
  initialize_future(get__compiler__use_literal(), frame->slots[34] /* temp__1 */);
  // 610: ... : (args*)
  // 611:   $txt string(args*)
  // 612:   push &actions: append &generated_collections txt
  frame->slots[34] /* temp__1 */ = create_closure(entry__compiler__sim2c_407, -1);
  // 610: %compiler::write_to_generated_collections: (args*)
  // 611:   $txt string(args*)
  // 612:   push &actions: append &generated_collections txt
  initialize_future(get__compiler__write_to_generated_collections(), frame->slots[34] /* temp__1 */);
  // 614: ... : (args*)
  // 615:   $txt string(args*)
  // 616:   push &actions: append &delayed_statements txt
  frame->slots[34] /* temp__1 */ = create_closure(entry__compiler__sim2c_412, -1);
  // 614: %compiler::write_to_delayed_statements: (args*)
  // 615:   $txt string(args*)
  // 616:   push &actions: append &delayed_statements txt
  initialize_future(get__compiler__write_to_delayed_statements(), frame->slots[34] /* temp__1 */);
  // 618: ... : (ident)
  // 619:   if ident .has_prefix. "get__":
  // 620:     $name range(ident 6 -1)
  // 621:     need name types::grammar_node(.variable_kind_of STATIC_SINGLE)
  frame->slots[34] /* temp__1 */ = create_closure(entry__compiler__sim2c_417, 1);
  // 618: %compiler::use_identifier: (ident)
  // 619:   if ident .has_prefix. "get__":
  // 620:     $name range(ident 6 -1)
  // 621:     need name types::grammar_node(.variable_kind_of STATIC_SINGLE)
  initialize_future(get__compiler__use_identifier(), frame->slots[34] /* temp__1 */);
  // 623: show_compiler_debug_info "GENERATE DEFINITIONS"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__c44673b4643f1172;
  result_count = 0;
  myself = get__show_compiler_debug_info();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_424;
}
static void entry__compiler__sim2c_420(void) {
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
  // 620: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_421;
}
static void cont__compiler__sim2c_421(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 620: $name range(ident 6 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* ident */;
  arguments->slots[1] = number__6;
  arguments->slots[2] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_422;
}
static void cont__compiler__sim2c_422(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* name */, arguments->slots[0]);
  // 621: ... types::grammar_node(.variable_kind_of STATIC_SINGLE)
  {
    NODE *temp = clone_object_and_attributes(get__types__grammar_node());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__variable_kind_of, get__STATIC_SINGLE());
    frame->slots[3] /* temp__1 */ = temp;

  }
  // 621: need name types::grammar_node(.variable_kind_of STATIC_SINGLE)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* name */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* need */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_338(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // args: 0
  // generated_declarations: 1
  // txt: 2
  frame->slots[1] = myself->closure.frame->slots[14]; /* generated_declarations */
  frame->slots[2] /* txt */ = create_future();
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 556: $txt string(args*)
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_339;
}
static void cont__compiler__sim2c_339(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* txt */, arguments->slots[0]);
  // 557: ... : append &generated_declarations txt
  frame->slots[3] /* temp__1 */ = create_closure(entry__compiler__sim2c_340, 0);
  // 557: push &actions: append &generated_declarations txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_342;
}
static void entry__compiler__sim2c_340(void) {
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
  // 557: ... append &generated_declarations txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_declarations */;
  arguments->slots[1] = frame->slots[1] /* txt */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_341;
}
static void cont__compiler__sim2c_341(void) {
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
static void cont__compiler__sim2c_342(void) {
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
static void entry__compiler__sim2c_343(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // args: 0
  // generated_top_level_variable_names: 1
  // txt: 2
  frame->slots[1] = myself->closure.frame->slots[15]; /* generated_top_level_variable_names */
  frame->slots[2] /* txt */ = create_future();
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 560: $txt string(args*)
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_344;
}
static void cont__compiler__sim2c_344(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* txt */, arguments->slots[0]);
  // 561: ... : append &generated_top_level_variable_names txt
  frame->slots[3] /* temp__1 */ = create_closure(entry__compiler__sim2c_345, 0);
  // 561: push &actions: append &generated_top_level_variable_names txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_347;
}
static void entry__compiler__sim2c_345(void) {
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
  // 561: ... append &generated_top_level_variable_names txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_top_level_variable_names */;
  arguments->slots[1] = frame->slots[1] /* txt */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_346;
}
static void cont__compiler__sim2c_346(void) {
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
static void cont__compiler__sim2c_347(void) {
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
static void entry__compiler__sim2c_348(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // args: 0
  // generated_top_level_variable_declarations: 1
  // txt: 2
  frame->slots[1] = myself->closure.frame->slots[16]; /* generated_top_level_variable_declarations */
  frame->slots[2] /* txt */ = create_future();
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 564: $txt string(args*)
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_349;
}
static void cont__compiler__sim2c_349(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* txt */, arguments->slots[0]);
  // 565: ... : append &generated_top_level_variable_declarations txt
  frame->slots[3] /* temp__1 */ = create_closure(entry__compiler__sim2c_350, 0);
  // 565: push &actions: append &generated_top_level_variable_declarations txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_352;
}
static void entry__compiler__sim2c_350(void) {
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
  // 565: ... append &generated_top_level_variable_declarations txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_top_level_variable_declarations */;
  arguments->slots[1] = frame->slots[1] /* txt */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_351;
}
static void cont__compiler__sim2c_351(void) {
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
static void cont__compiler__sim2c_352(void) {
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
static void entry__compiler__sim2c_353(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // args: 0
  // generated_global_variable_declarations: 1
  // txt: 2
  frame->slots[1] = myself->closure.frame->slots[17]; /* generated_global_variable_declarations */
  frame->slots[2] /* txt */ = create_future();
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 568: $txt string(args*)
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_354;
}
static void cont__compiler__sim2c_354(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* txt */, arguments->slots[0]);
  // 569: ... : append &generated_global_variable_declarations txt
  frame->slots[3] /* temp__1 */ = create_closure(entry__compiler__sim2c_355, 0);
  // 569: push &actions: append &generated_global_variable_declarations txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_357;
}
static void entry__compiler__sim2c_355(void) {
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
  // 569: ... append &generated_global_variable_declarations txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_global_variable_declarations */;
  arguments->slots[1] = frame->slots[1] /* txt */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_356;
}
static void cont__compiler__sim2c_356(void) {
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
static void cont__compiler__sim2c_357(void) {
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
static void entry__compiler__sim2c_358(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // args: 0
  // generated_continuation_table: 1
  // txt: 2
  frame->slots[1] = myself->closure.frame->slots[18]; /* generated_continuation_table */
  frame->slots[2] /* txt */ = create_future();
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 572: $txt string(args*)
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_359;
}
static void cont__compiler__sim2c_359(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* txt */, arguments->slots[0]);
  // 573: ... : append &generated_continuation_table txt
  frame->slots[3] /* temp__1 */ = create_closure(entry__compiler__sim2c_360, 0);
  // 573: push &actions: append &generated_continuation_table txt
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
  // 573: ... append &generated_continuation_table txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_continuation_table */;
  arguments->slots[1] = frame->slots[1] /* txt */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_361;
}
static void cont__compiler__sim2c_361(void) {
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
  // generated_delayed_continuation_table: 1
  // txt: 2
  frame->slots[1] = myself->closure.frame->slots[19]; /* generated_delayed_continuation_table */
  frame->slots[2] /* txt */ = create_future();
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 576: $txt string(args*)
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
  // 577: ... : append &generated_delayed_continuation_table txt
  frame->slots[3] /* temp__1 */ = create_closure(entry__compiler__sim2c_365, 0);
  // 577: push &actions: append &generated_delayed_continuation_table txt
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
  // generated_delayed_continuation_table: 0
  // txt: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* generated_delayed_continuation_table */
  frame->slots[1] = myself->closure.frame->slots[2]; /* txt */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 577: ... append &generated_delayed_continuation_table txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_delayed_continuation_table */;
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
  ((CELL *)frame->slots[0])->contents /* generated_delayed_continuation_table */ = arguments->slots[0];
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
  // generated_functions: 1
  // txt: 2
  frame->slots[1] = myself->closure.frame->slots[20]; /* generated_functions */
  frame->slots[2] /* txt */ = create_future();
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 580: $txt string(args*)
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
  // 581: ... : append &generated_functions txt
  frame->slots[3] /* temp__1 */ = create_closure(entry__compiler__sim2c_370, 0);
  // 581: push &actions: append &generated_functions txt
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
  // generated_functions: 0
  // txt: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* generated_functions */
  frame->slots[1] = myself->closure.frame->slots[2]; /* txt */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 581: ... append &generated_functions txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_functions */;
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
  ((CELL *)frame->slots[0])->contents /* generated_functions */ = arguments->slots[0];
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
  allocate_arguments();
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // args: 0
  // generated_phase_1: 1
  // txt: 2
  frame->slots[1] = myself->closure.frame->slots[21]; /* generated_phase_1 */
  frame->slots[2] /* txt */ = create_future();
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 584: $txt string(args*)
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_374;
}
static void cont__compiler__sim2c_374(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* txt */, arguments->slots[0]);
  // 585: ... : append &generated_phase_1 txt
  frame->slots[3] /* temp__1 */ = create_closure(entry__compiler__sim2c_375, 0);
  // 585: push &actions: append &generated_phase_1 txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_377;
}
static void entry__compiler__sim2c_375(void) {
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
  // 585: ... append &generated_phase_1 txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_phase_1 */;
  arguments->slots[1] = frame->slots[1] /* txt */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_376;
}
static void cont__compiler__sim2c_376(void) {
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
static void cont__compiler__sim2c_377(void) {
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
static void entry__compiler__sim2c_378(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // args: 0
  // generated_phase_2: 1
  // txt: 2
  frame->slots[1] = myself->closure.frame->slots[22]; /* generated_phase_2 */
  frame->slots[2] /* txt */ = create_future();
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 588: $txt string(args*)
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_379;
}
static void cont__compiler__sim2c_379(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* txt */, arguments->slots[0]);
  // 589: ... : append &generated_phase_2 txt
  frame->slots[3] /* temp__1 */ = create_closure(entry__compiler__sim2c_380, 0);
  // 589: push &actions: append &generated_phase_2 txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_382;
}
static void entry__compiler__sim2c_380(void) {
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
  // 589: ... append &generated_phase_2 txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_phase_2 */;
  arguments->slots[1] = frame->slots[1] /* txt */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_381;
}
static void cont__compiler__sim2c_381(void) {
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
static void cont__compiler__sim2c_382(void) {
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
static void entry__compiler__sim2c_383(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // args: 0
  // generated_phase_3: 1
  // txt: 2
  frame->slots[1] = myself->closure.frame->slots[23]; /* generated_phase_3 */
  frame->slots[2] /* txt */ = create_future();
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 592: $txt string(args*)
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_384;
}
static void cont__compiler__sim2c_384(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* txt */, arguments->slots[0]);
  // 593: ... : append &generated_phase_3 txt
  frame->slots[3] /* temp__1 */ = create_closure(entry__compiler__sim2c_385, 0);
  // 593: push &actions: append &generated_phase_3 txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_387;
}
static void entry__compiler__sim2c_385(void) {
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
  // 593: ... append &generated_phase_3 txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_phase_3 */;
  arguments->slots[1] = frame->slots[1] /* txt */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_386;
}
static void cont__compiler__sim2c_386(void) {
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
static void cont__compiler__sim2c_387(void) {
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
static void entry__compiler__sim2c_388(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // args: 0
  // generated_phase_4: 1
  // txt: 2
  frame->slots[1] = myself->closure.frame->slots[24]; /* generated_phase_4 */
  frame->slots[2] /* txt */ = create_future();
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 596: $txt string(args*)
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_389;
}
static void cont__compiler__sim2c_389(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* txt */, arguments->slots[0]);
  // 597: ... : append &generated_phase_4 txt
  frame->slots[3] /* temp__1 */ = create_closure(entry__compiler__sim2c_390, 0);
  // 597: push &actions: append &generated_phase_4 txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_392;
}
static void entry__compiler__sim2c_390(void) {
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
  // 597: ... append &generated_phase_4 txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_phase_4 */;
  arguments->slots[1] = frame->slots[1] /* txt */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_391;
}
static void cont__compiler__sim2c_391(void) {
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
static void cont__compiler__sim2c_392(void) {
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
static void entry__compiler__sim2c_393(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // args: 0
  // generated_phase_5: 1
  // txt: 2
  frame->slots[1] = myself->closure.frame->slots[25]; /* generated_phase_5 */
  frame->slots[2] /* txt */ = create_future();
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 600: $txt string(args*)
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_394;
}
static void cont__compiler__sim2c_394(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* txt */, arguments->slots[0]);
  // 601: ... : append &generated_phase_5 txt
  frame->slots[3] /* temp__1 */ = create_closure(entry__compiler__sim2c_395, 0);
  // 601: push &actions: append &generated_phase_5 txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_397;
}
static void entry__compiler__sim2c_395(void) {
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
  // 601: ... append &generated_phase_5 txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_phase_5 */;
  arguments->slots[1] = frame->slots[1] /* txt */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_396;
}
static void cont__compiler__sim2c_396(void) {
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
static void cont__compiler__sim2c_397(void) {
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
static void entry__compiler__sim2c_398(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // args: 0
  // generated_phase_6: 1
  // txt: 2
  frame->slots[1] = myself->closure.frame->slots[26]; /* generated_phase_6 */
  frame->slots[2] /* txt */ = create_future();
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 604: $txt string(args*)
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_399;
}
static void cont__compiler__sim2c_399(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* txt */, arguments->slots[0]);
  // 605: ... : append &generated_phase_6 txt
  frame->slots[3] /* temp__1 */ = create_closure(entry__compiler__sim2c_400, 0);
  // 605: push &actions: append &generated_phase_6 txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_402;
}
static void entry__compiler__sim2c_400(void) {
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
  // 605: ... append &generated_phase_6 txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_phase_6 */;
  arguments->slots[1] = frame->slots[1] /* txt */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_401;
}
static void cont__compiler__sim2c_401(void) {
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
static void cont__compiler__sim2c_402(void) {
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
static void entry__compiler__sim2c_403(void) {
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
  // 608: ... : !used_literals(name) literal
  frame->slots[3] /* temp__1 */ = create_closure(entry__compiler__sim2c_404, 0);
  // 608: push &actions: !used_literals(name) literal
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_406;
}
static void entry__compiler__sim2c_404(void) {
  allocate_initialized_frame_gc(3, 3);
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
  // 608: ... !used_literals(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* name */;
  arguments->slots[1] = frame->slots[2] /* literal */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* used_literals */;
  func = myself->type;
  frame->cont = cont__compiler__sim2c_405;
}
static void cont__compiler__sim2c_405(void) {
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
static void cont__compiler__sim2c_406(void) {
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
static void entry__compiler__sim2c_407(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // args: 0
  // generated_collections: 1
  // txt: 2
  frame->slots[1] = myself->closure.frame->slots[28]; /* generated_collections */
  frame->slots[2] /* txt */ = create_future();
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 611: $txt string(args*)
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_408;
}
static void cont__compiler__sim2c_408(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* txt */, arguments->slots[0]);
  // 612: ... : append &generated_collections txt
  frame->slots[3] /* temp__1 */ = create_closure(entry__compiler__sim2c_409, 0);
  // 612: push &actions: append &generated_collections txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_411;
}
static void entry__compiler__sim2c_409(void) {
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
  // 612: ... append &generated_collections txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_collections */;
  arguments->slots[1] = frame->slots[1] /* txt */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_410;
}
static void cont__compiler__sim2c_410(void) {
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
static void cont__compiler__sim2c_411(void) {
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
static void entry__compiler__sim2c_412(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // args: 0
  // delayed_statements: 1
  // txt: 2
  frame->slots[1] = myself->closure.frame->slots[29]; /* delayed_statements */
  frame->slots[2] /* txt */ = create_future();
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 615: $txt string(args*)
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_413;
}
static void cont__compiler__sim2c_413(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* txt */, arguments->slots[0]);
  // 616: ... : append &delayed_statements txt
  frame->slots[3] /* temp__1 */ = create_closure(entry__compiler__sim2c_414, 0);
  // 616: push &actions: append &delayed_statements txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_416;
}
static void entry__compiler__sim2c_414(void) {
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
  // 616: ... append &delayed_statements txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* delayed_statements */;
  arguments->slots[1] = frame->slots[1] /* txt */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_415;
}
static void cont__compiler__sim2c_415(void) {
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
static void cont__compiler__sim2c_416(void) {
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
static void entry__compiler__sim2c_417(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // ident: 0
  // need: 1
  frame->slots[1] = myself->closure.frame->slots[13]; /* need */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 619: ... ident .has_prefix. "get__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* ident */;
  arguments->slots[1] = string__405aee03eb306008;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_419;
}
static void cont__compiler__sim2c_419(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 619: ... :
  // 620:   $name range(ident 6 -1)
  // 621:   need name types::grammar_node(.variable_kind_of STATIC_SINGLE)
  frame->slots[3] /* temp__2 */ = create_closure(entry__compiler__sim2c_420, 0);
  // 619: if ident .has_prefix. "get__":
  // 620:   $name range(ident 6 -1)
  // 621:   need name types::grammar_node(.variable_kind_of STATIC_SINGLE)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_424(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 624: $$is_a_prototype empty_set
  ((CELL *)frame->slots[31])->contents /* is_a_prototype */ = get__empty_set();
  // 625: ... : (defs)
  // 626:   for_each defs: ($definition)
  // 627:     if definition.is_a_key_value_pair:
  // 628:       !definition key_of(definition)
  // 629:       unless attribute_kind_of(definition) == NONE:
  // 630:         !is_a_prototype(identifier_of(definition).to_string) true
  frame->slots[34] /* temp__1 */ = create_closure(entry__compiler__sim2c_425, 1);
  // 625: for_each all_definitions: (defs)
  // 626:   for_each defs: ($definition)
  // 627:     if definition.is_a_key_value_pair:
  // 628:       !definition key_of(definition)
  // 629:       unless attribute_kind_of(definition) == NONE:
  // 630:         !is_a_prototype(identifier_of(definition).to_string) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[10])->contents /* all_definitions */;
  arguments->slots[1] = frame->slots[34] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_436;
}
static void entry__compiler__sim2c_432(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // is_a_prototype: 0
  // definition: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* is_a_prototype */
  frame->slots[1] = myself->closure.frame->slots[0]; /* definition */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 630: ... identifier_of(definition)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* definition */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_433;
}
static void cont__compiler__sim2c_433(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 630: ... identifier_of(definition).to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_434;
}
static void cont__compiler__sim2c_434(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 630: !is_a_prototype(identifier_of(definition).to_string)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = get__true();
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* is_a_prototype */;
  func = myself->type;
  frame->cont = cont__compiler__sim2c_435;
}
static void cont__compiler__sim2c_435(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* is_a_prototype */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__sim2c_428(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // definition: 0
  // is_a_prototype: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* definition */
  frame->slots[1] = myself->closure.frame->slots[1]; /* is_a_prototype */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 628: !definition key_of(definition)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* definition */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_429;
}
static void cont__compiler__sim2c_429(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* definition */ = arguments->slots[0];
  // 629: ... attribute_kind_of(definition)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* definition */;
  result_count = 1;
  myself = get__attribute_kind_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_430;
}
static void cont__compiler__sim2c_430(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 629: ... attribute_kind_of(definition) == NONE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = get__NONE();
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_431;
}
static void cont__compiler__sim2c_431(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 629: ... :
  // 630:   !is_a_prototype(identifier_of(definition).to_string) true
  frame->slots[4] /* temp__3 */ = create_closure(entry__compiler__sim2c_432, 0);
  // 629: unless attribute_kind_of(definition) == NONE:
  // 630:   !is_a_prototype(identifier_of(definition).to_string) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_426(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // definition: 0
  // is_a_prototype: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* is_a_prototype */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* definition */ = create_cell_with_contents(arguments->slots[0]);
  // 627: ... definition.is_a_key_value_pair
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* definition */;
  result_count = 1;
  myself = get__is_a_key_value_pair();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_427;
}
static void cont__compiler__sim2c_427(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 627: ... :
  // 628:   !definition key_of(definition)
  // 629:   unless attribute_kind_of(definition) == NONE:
  // 630:     !is_a_prototype(identifier_of(definition).to_string) true
  frame->slots[3] /* temp__2 */ = create_closure(entry__compiler__sim2c_428, 0);
  // 627: if definition.is_a_key_value_pair:
  // 628:   !definition key_of(definition)
  // 629:   unless attribute_kind_of(definition) == NONE:
  // 630:     !is_a_prototype(identifier_of(definition).to_string) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_425(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // defs: 0
  // is_a_prototype: 1
  frame->slots[1] = myself->closure.frame->slots[31]; /* is_a_prototype */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 626: ... : ($definition)
  // 627:   if definition.is_a_key_value_pair:
  // 628:     !definition key_of(definition)
  // 629:     unless attribute_kind_of(definition) == NONE:
  // 630:       !is_a_prototype(identifier_of(definition).to_string) true
  frame->slots[2] /* temp__1 */ = create_closure(entry__compiler__sim2c_426, 1);
  // 626: for_each defs: ($definition)
  // 627:   if definition.is_a_key_value_pair:
  // 628:     !definition key_of(definition)
  // 629:     unless attribute_kind_of(definition) == NONE:
  // 630:       !is_a_prototype(identifier_of(definition).to_string) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* defs */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_436(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 631: ... : (defs)
  // 632:   %%compiler::actions empty_list
  // 633:   %%compiler::delayed_code ""
  // 634:   %%compiler::index 0
  // 635:   collect_output $code:
  // 636:     for_each defs: ($definition)
  // 637:       $$source undefined
  // 638:       if definition.is_a_key_value_pair:
  // 639:         !source std::value_of(definition)
  // 640:         !definition key_of(definition)
  // ...
  frame->slots[34] /* temp__1 */ = create_closure(entry__compiler__sim2c_437, 1);
  // 631: for_each all_definitions: (defs)
  // 632:   %%compiler::actions empty_list
  // 633:   %%compiler::delayed_code ""
  // 634:   %%compiler::index 0
  // 635:   collect_output $code:
  // 636:     for_each defs: ($definition)
  // 637:       $$source undefined
  // 638:       if definition.is_a_key_value_pair:
  // 639:         !source std::value_of(definition)
  // 640:         !definition key_of(definition)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[10])->contents /* all_definitions */;
  arguments->slots[1] = frame->slots[34] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_504;
}
static void entry__compiler__sim2c_437(void) {
  allocate_initialized_frame_gc(5, 8);
  // slot allocations:
  // defs: 0
  // return__6: 1
  // is_a_prototype: 2
  // generated_code: 3
  // all_actions: 4
  // code: 5
  frame->slots[1] /* return__6 */ = create_continuation();
  frame->slots[2] = myself->closure.frame->slots[31]; /* is_a_prototype */
  frame->slots[3] = myself->closure.frame->slots[27]; /* generated_code */
  frame->slots[4] = myself->closure.frame->slots[8]; /* all_actions */
  define__compiler__actions(undefined);
  define__compiler__delayed_code(undefined);
  define__compiler__index(undefined);
  frame->slots[5] /* code */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 632: %%compiler::actions empty_list
  set__compiler__actions(get__empty_list());
  // 633: %%compiler::delayed_code ""
  set__compiler__delayed_code(empty_string);
  // 634: %%compiler::index 0
  set__compiler__index(number__0);
  // 635: ... :
  // 636:   for_each defs: ($definition)
  // 637:     $$source undefined
  // 638:     if definition.is_a_key_value_pair:
  // 639:       !source std::value_of(definition)
  // 640:       !definition key_of(definition)
  // 641:     if
  // 642:       definition.is_c_code:
  // 643:         define_c_code definition
  // 644:       :
  // ...
  frame->slots[6] /* temp__1 */ = create_closure(entry__compiler__sim2c_438, 0);
  // 635: collect_output $code:
  // 636:   for_each defs: ($definition)
  // 637:     $$source undefined
  // 638:     if definition.is_a_key_value_pair:
  // 639:       !source std::value_of(definition)
  // 640:       !definition key_of(definition)
  // 641:     if
  // 642:       definition.is_c_code:
  // 643:         define_c_code definition
  // 644:       :
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_495;
}
static void entry__compiler__sim2c_446(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // definition: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* definition */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 643: define_c_code definition
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* definition */;
  result_count = frame->caller_result_count;
  myself = get__define_c_code();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_447(void) {
  allocate_initialized_frame_gc(4, 11);
  // slot allocations:
  // return__5: 0
  // definition: 1
  // source: 2
  // is_a_prototype: 3
  // name: 4
  // attribute: 5
  frame->slots[0] /* return__5 */ = create_continuation();
  frame->slots[1] = myself->closure.frame->slots[0]; /* definition */
  frame->slots[2] = myself->closure.frame->slots[2]; /* source */
  frame->slots[3] = myself->closure.frame->slots[1]; /* is_a_prototype */
  frame->slots[4] /* name */ = create_cell();
  frame->slots[5] /* attribute */ = create_future();
  define__compiler__suffix(create_future());
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 645: ... identifier_of(definition)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* definition */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_448;
}
static void cont__compiler__sim2c_448(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 645: $$name mangled_name_of(identifier_of(definition))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = get__mangled_name_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_449;
}
static void cont__compiler__sim2c_449(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* name */ = arguments->slots[0];
  // 646: $attribute attribute_of(definition)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* definition */;
  result_count = 1;
  myself = get__attribute_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_450;
}
static void cont__compiler__sim2c_450(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* attribute */, arguments->slots[0]);
  // 647: ... attribute.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* attribute */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_451;
}
static void cont__compiler__sim2c_451(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 647: ... :
  // 648:   append &name "__"
  // 649:   append &name mangled_name_of(attribute)
  frame->slots[7] /* temp__2 */ = create_closure(entry__compiler__sim2c_452, 0);
  // 647: if attribute.is_defined:
  // 648:   append &name "__"
  // 649:   append &name mangled_name_of(attribute)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_456;
}
static void entry__compiler__sim2c_452(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // name: 0
  // attribute: 1
  frame->slots[0] = myself->closure.frame->slots[4]; /* name */
  frame->slots[1] = myself->closure.frame->slots[5]; /* attribute */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 648: append &name "__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* name */;
  arguments->slots[1] = string__2d7981f4e5f02b9a;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_453;
}
static void cont__compiler__sim2c_453(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* name */ = arguments->slots[0];
  // 649: ... mangled_name_of(attribute)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* attribute */;
  result_count = 1;
  myself = get__mangled_name_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_454;
}
static void cont__compiler__sim2c_454(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 649: append &name mangled_name_of(attribute)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* name */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_455;
}
static void cont__compiler__sim2c_455(void) {
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
static void cont__compiler__sim2c_456(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 650: %compiler::suffix string("__" name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e5f02b9a;
  arguments->slots[1] = ((CELL *)frame->slots[4])->contents /* name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_457;
}
static void cont__compiler__sim2c_457(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(get__compiler__suffix(), arguments->slots[0]);
  // 652: source.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* source */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_458;
}
static void cont__compiler__sim2c_458(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 652: ... source.is_a_polymorphic_function_constant
  frame->slots[8] /* temp__3 */ = create_closure(entry__compiler__sim2c_459, 0);
  // 652: source.is_defined && source.is_a_polymorphic_function_constant
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  arguments->slots[1] = frame->slots[8] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_461;
}
static void entry__compiler__sim2c_459(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // source: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* source */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 652: ... source.is_a_polymorphic_function_constant
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* source */;
  result_count = 1;
  myself = get__is_a_polymorphic_function_constant();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_460;
}
static void cont__compiler__sim2c_460(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 652: ... source.is_a_polymorphic_function_constant
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__sim2c_461(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 652: ... :
  // 653:   define_polymorphic_function definition source.is_a_setter
  frame->slots[9] /* temp__4 */ = create_closure(entry__compiler__sim2c_462, 0);
  // 654: :
  // 655:   case attribute_kind_of(definition)
  // 656:     ATTRIBUTE_KIND:
  // 657:       define_attribute definition source
  // 658:     METHOD_KIND:
  // 659:       if
  // 660:         attribute_of(definition).is_defined:
  // 661:           define_method definition source
  // 662:         :
  // 663:           define_type_function definition source
  // ...
  frame->slots[10] /* temp__5 */ = create_closure(entry__compiler__sim2c_464, 0);
  // 651: if
  // 652:   source.is_defined && source.is_a_polymorphic_function_constant:
  // 653:     define_polymorphic_function definition source.is_a_setter
  // 654:   :
  // 655:     case attribute_kind_of(definition)
  // 656:       ATTRIBUTE_KIND:
  // 657:         define_attribute definition source
  // 658:       METHOD_KIND:
  // 659:         if
  // 660:           attribute_of(definition).is_defined:
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__4 */;
  arguments->slots[2] = frame->slots[10] /* temp__5 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_494;
}
static void entry__compiler__sim2c_492(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // source: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* source */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 678: ... source.to_c
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* source */;
  result_count = 1;
  myself = get__to_c();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_493;
}
static void cont__compiler__sim2c_493(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 678: ... ignore source.to_c
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ignore();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_481(void) {
  allocate_initialized_frame_gc(3, 8);
  // slot allocations:
  // definition: 0
  // source: 1
  // is_a_prototype: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* definition */
  frame->slots[1] = myself->closure.frame->slots[1]; /* source */
  frame->slots[2] = myself->closure.frame->slots[2]; /* is_a_prototype */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 675: identifier_of(definition)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* definition */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_482;
}
static void cont__compiler__sim2c_482(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__4 */ = arguments->slots[0];
  // 675: identifier_of(definition).to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__4 */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_483;
}
static void cont__compiler__sim2c_483(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 675: identifier_of(definition).to_string.is_a_prototype
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[2])->contents /* is_a_prototype */;
  func = myself->type;
  frame->cont = cont__compiler__sim2c_484;
}
static void cont__compiler__sim2c_484(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 676: namespace_of(identifier_of(definition)).is_defined
  frame->slots[7] /* temp__5 */ = create_closure(entry__compiler__sim2c_485, 0);
  // 674: ||
  // 675:   identifier_of(definition).to_string.is_a_prototype
  // 676:   namespace_of(identifier_of(definition)).is_defined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__5 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_489;
}
static void entry__compiler__sim2c_485(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // definition: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* definition */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 676: ... identifier_of(definition)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* definition */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_486;
}
static void cont__compiler__sim2c_486(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 676: namespace_of(identifier_of(definition))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__namespace_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_487;
}
static void cont__compiler__sim2c_487(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 676: namespace_of(identifier_of(definition)).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_488;
}
static void cont__compiler__sim2c_488(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 676: namespace_of(identifier_of(definition)).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__sim2c_489(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 671: define_variable
  // 672:   definition
  // 673:   source
  // 674:   ||
  // 675:     identifier_of(definition).to_string.is_a_prototype
  // 676:     namespace_of(identifier_of(definition)).is_defined
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* definition */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* source */;
  arguments->slots[2] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__define_variable();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_490(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // source: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* source */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 678: ... source.is_a_body
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* source */;
  result_count = 1;
  myself = get__is_a_body();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_491;
}
static void cont__compiler__sim2c_491(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 678: ... : ignore source.to_c
  frame->slots[2] /* temp__2 */ = create_closure(entry__compiler__sim2c_492, 0);
  // 678: if source.is_a_body: ignore source.to_c
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_470(void) {
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
  // 661: define_method definition source
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* definition */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* source */;
  result_count = frame->caller_result_count;
  myself = get__define_method();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_471(void) {
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
  // 663: define_type_function definition source
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* definition */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* source */;
  result_count = frame->caller_result_count;
  myself = get__define_type_function();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_466(void) {
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
  // 657: define_attribute definition source
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* definition */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* source */;
  result_count = frame->caller_result_count;
  myself = get__define_attribute();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_467(void) {
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
  // 660: attribute_of(definition)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* definition */;
  result_count = 1;
  myself = get__attribute_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_468;
}
static void cont__compiler__sim2c_468(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 660: attribute_of(definition).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_469;
}
static void cont__compiler__sim2c_469(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 660: ... :
  // 661:   define_method definition source
  frame->slots[4] /* temp__3 */ = create_closure(entry__compiler__sim2c_470, 0);
  // 662: :
  // 663:   define_type_function definition source
  frame->slots[5] /* temp__4 */ = create_closure(entry__compiler__sim2c_471, 0);
  // 659: if
  // 660:   attribute_of(definition).is_defined:
  // 661:     define_method definition source
  // 662:   :
  // 663:     define_type_function definition source
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
static void entry__compiler__sim2c_472(void) {
  allocate_initialized_frame_gc(3, 10);
  // slot allocations:
  // definition: 0
  // source: 1
  // is_a_prototype: 2
  // identifier: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* definition */
  frame->slots[1] = myself->closure.frame->slots[1]; /* source */
  frame->slots[2] = myself->closure.frame->slots[2]; /* is_a_prototype */
  frame->slots[3] /* identifier */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 665: $identifier identifier_of(definition)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* definition */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_473;
}
static void cont__compiler__sim2c_473(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* identifier */, arguments->slots[0]);
  // 668: namespace_of(identifier)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* identifier */;
  result_count = 1;
  myself = get__namespace_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_474;
}
static void cont__compiler__sim2c_474(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 668: namespace_of(identifier).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__3 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_475;
}
static void cont__compiler__sim2c_475(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 669: named_constants(name_of(identifier)).is_undefined
  frame->slots[7] /* temp__4 */ = create_closure(entry__compiler__sim2c_476, 0);
  // 667: ||
  // 668:   namespace_of(identifier).is_defined
  // 669:   named_constants(name_of(identifier)).is_undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__4 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_480;
}
static void entry__compiler__sim2c_476(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // identifier: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* identifier */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 669: ... name_of(identifier)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* identifier */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_477;
}
static void cont__compiler__sim2c_477(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 669: named_constants(name_of(identifier))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__named_constants();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_478;
}
static void cont__compiler__sim2c_478(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 669: named_constants(name_of(identifier)).is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_479;
}
static void cont__compiler__sim2c_479(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 669: named_constants(name_of(identifier)).is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__sim2c_480(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 670: :
  // 671:   define_variable
  // 672:     definition
  // 673:     source
  // 674:     ||
  // 675:       identifier_of(definition).to_string.is_a_prototype
  // 676:       namespace_of(identifier_of(definition)).is_defined
  frame->slots[8] /* temp__5 */ = create_closure(entry__compiler__sim2c_481, 0);
  // 677: :
  // 678:   if source.is_a_body: ignore source.to_c
  frame->slots[9] /* temp__6 */ = create_closure(entry__compiler__sim2c_490, 0);
  // 666: if
  // 667:   ||
  // 668:     namespace_of(identifier).is_defined
  // 669:     named_constants(name_of(identifier)).is_undefined
  // 670:   :
  // 671:     define_variable
  // 672:       definition
  // 673:       source
  // 674:       ||
  // 675:         identifier_of(definition).to_string.is_a_prototype
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__5 */;
  arguments->slots[2] = frame->slots[9] /* temp__6 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_462(void) {
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
  // 653: ... source.is_a_setter
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* source */;
  result_count = 1;
  myself = get__is_a_setter();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_463;
}
static void cont__compiler__sim2c_463(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 653: define_polymorphic_function definition source.is_a_setter
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* definition */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__define_polymorphic_function();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_464(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // definition: 0
  // source: 1
  // is_a_prototype: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* definition */
  frame->slots[1] = myself->closure.frame->slots[2]; /* source */
  frame->slots[2] = myself->closure.frame->slots[3]; /* is_a_prototype */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 655: ... attribute_kind_of(definition)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* definition */;
  result_count = 1;
  myself = get__attribute_kind_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_465;
}
static void cont__compiler__sim2c_465(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 656: ... :
  // 657:   define_attribute definition source
  frame->slots[4] /* temp__2 */ = create_closure(entry__compiler__sim2c_466, 0);
  // 658: ... :
  // 659:   if
  // 660:     attribute_of(definition).is_defined:
  // 661:       define_method definition source
  // 662:     :
  // 663:       define_type_function definition source
  frame->slots[5] /* temp__3 */ = create_closure(entry__compiler__sim2c_467, 0);
  // 664: :
  // 665:   $identifier identifier_of(definition)
  // 666:   if
  // 667:     ||
  // 668:       namespace_of(identifier).is_defined
  // 669:       named_constants(name_of(identifier)).is_undefined
  // 670:     :
  // 671:       define_variable
  // 672:         definition
  // 673:         source
  // ...
  frame->slots[6] /* temp__4 */ = create_closure(entry__compiler__sim2c_472, 0);
  // 655: case attribute_kind_of(definition)
  // 656:   ATTRIBUTE_KIND:
  // 657:     define_attribute definition source
  // 658:   METHOD_KIND:
  // 659:     if
  // 660:       attribute_of(definition).is_defined:
  // 661:         define_method definition source
  // 662:       :
  // 663:         define_type_function definition source
  // 664:   :
  // ...
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = get__ATTRIBUTE_KIND();
  arguments->slots[2] = frame->slots[4] /* temp__2 */;
  arguments->slots[3] = get__METHOD_KIND();
  arguments->slots[4] = frame->slots[5] /* temp__3 */;
  arguments->slots[5] = frame->slots[6] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_494(void) {
  myself = frame->slots[0] /* return__5 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__compiler__sim2c_439(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // definition: 0
  // is_a_prototype: 1
  // source: 2
  frame->slots[1] = myself->closure.frame->slots[1]; /* is_a_prototype */
  frame->slots[2] /* source */ = create_cell();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* definition */ = create_cell_with_contents(arguments->slots[0]);
  // 637: $$source undefined
  ((CELL *)frame->slots[2])->contents /* source */ = get__undefined();
  // 638: ... definition.is_a_key_value_pair
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* definition */;
  result_count = 1;
  myself = get__is_a_key_value_pair();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_440;
}
static void cont__compiler__sim2c_440(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 638: ... :
  // 639:   !source std::value_of(definition)
  // 640:   !definition key_of(definition)
  frame->slots[4] /* temp__2 */ = create_closure(entry__compiler__sim2c_441, 0);
  // 638: if definition.is_a_key_value_pair:
  // 639:   !source std::value_of(definition)
  // 640:   !definition key_of(definition)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_444;
}
static void entry__compiler__sim2c_441(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // source: 0
  // definition: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* source */
  frame->slots[1] = myself->closure.frame->slots[0]; /* definition */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 639: !source std::value_of(definition)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* definition */;
  result_count = 1;
  myself = get__std__value_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_442;
}
static void cont__compiler__sim2c_442(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* source */ = arguments->slots[0];
  // 640: !definition key_of(definition)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* definition */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_443;
}
static void cont__compiler__sim2c_443(void) {
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
static void cont__compiler__sim2c_444(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 642: definition.is_c_code
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* definition */;
  result_count = 1;
  myself = get__is_c_code();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_445;
}
static void cont__compiler__sim2c_445(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 642: ... :
  // 643:   define_c_code definition
  frame->slots[4] /* temp__2 */ = create_closure(entry__compiler__sim2c_446, 0);
  // 644: :
  // 645:   $$name mangled_name_of(identifier_of(definition))
  // 646:   $attribute attribute_of(definition)
  // 647:   if attribute.is_defined:
  // 648:     append &name "__"
  // 649:     append &name mangled_name_of(attribute)
  // 650:   %compiler::suffix string("__" name)
  // 651:   if
  // 652:     source.is_defined && source.is_a_polymorphic_function_constant:
  // 653:       define_polymorphic_function definition source.is_a_setter
  // ...
  frame->slots[5] /* temp__3 */ = create_closure(entry__compiler__sim2c_447, 0);
  // 641: if
  // 642:   definition.is_c_code:
  // 643:     define_c_code definition
  // 644:   :
  // 645:     $$name mangled_name_of(identifier_of(definition))
  // 646:     $attribute attribute_of(definition)
  // 647:     if attribute.is_defined:
  // 648:       append &name "__"
  // 649:       append &name mangled_name_of(attribute)
  // 650:     %compiler::suffix string("__" name)
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
static void entry__compiler__sim2c_438(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // defs: 0
  // is_a_prototype: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* defs */
  frame->slots[1] = myself->closure.frame->slots[2]; /* is_a_prototype */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 636: ... : ($definition)
  // 637:   $$source undefined
  // 638:   if definition.is_a_key_value_pair:
  // 639:     !source std::value_of(definition)
  // 640:     !definition key_of(definition)
  // 641:   if
  // 642:     definition.is_c_code:
  // 643:       define_c_code definition
  // 644:     :
  // 645:       $$name mangled_name_of(identifier_of(definition))
  // ...
  frame->slots[2] /* temp__1 */ = create_closure(entry__compiler__sim2c_439, 1);
  // 636: for_each defs: ($definition)
  // 637:   $$source undefined
  // 638:   if definition.is_a_key_value_pair:
  // 639:     !source std::value_of(definition)
  // 640:     !definition key_of(definition)
  // 641:   if
  // 642:     definition.is_c_code:
  // 643:       define_c_code definition
  // 644:     :
  // 645:       $$name mangled_name_of(identifier_of(definition))
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* defs */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_495(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* code */, arguments->slots[0]);
  // 679: ... delayed_code != ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__delayed_code();
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_496;
}
static void cont__compiler__sim2c_496(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 679: ... delayed_code != ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_497;
}
static void cont__compiler__sim2c_497(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 679: if delayed_code != "": write_to_delayed_statements delayed_code
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = func__compiler__sim2c_498;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_499;
}
static void entry__compiler__sim2c_498(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 679: ... write_to_delayed_statements delayed_code
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__delayed_code();
  result_count = frame->caller_result_count;
  myself = get__write_to_delayed_statements();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_499(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 680: ... : append &generated_code code
  frame->slots[6] /* temp__1 */ = create_closure(entry__compiler__sim2c_500, 0);
  // 680: push &actions: append &generated_code code
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_502;
}
static void entry__compiler__sim2c_500(void) {
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
  // 680: ... append &generated_code code
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_code */;
  arguments->slots[1] = frame->slots[1] /* code */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_501;
}
static void cont__compiler__sim2c_501(void) {
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
static void cont__compiler__sim2c_502(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__actions(arguments->slots[0]);
  // 681: push &all_actions actions
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* all_actions */;
  arguments->slots[1] = get__actions();
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_503;
}
static void cont__compiler__sim2c_503(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* all_actions */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  myself = frame->slots[1] /* return__6 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__compiler__sim2c_504(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 682: show_compiler_debug_info "GENERATE STATEMENTS"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__c050814d5faecc7a;
  result_count = 0;
  myself = get__show_compiler_debug_info();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_506;
}
static void cont__compiler__sim2c_506(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 683: %%compiler::current_continuation_info undefined
  set__compiler__current_continuation_info(get__undefined());
  // 684: ... :
  // 685:   %%compiler::actions empty_list
  // 686:   %%compiler::delayed_code ""
  // 687:   collect_output $code:
  // 688:     if
  // 689:       is_main:
  // 690:         begin_continuation "main_entry"
  // 691:         if max_temp_idx > 0:
  // 692:           writeln "  allocate_initialized_frame_gc(0, @(max_temp_idx));"
  // 693:       :
  // ...
  frame->slots[34] /* temp__1 */ = create_closure(entry__compiler__sim2c_507, 0);
  // 684: do:
  // 685:   %%compiler::actions empty_list
  // 686:   %%compiler::delayed_code ""
  // 687:   collect_output $code:
  // 688:     if
  // 689:       is_main:
  // 690:         begin_continuation "main_entry"
  // 691:         if max_temp_idx > 0:
  // 692:           writeln "  allocate_initialized_frame_gc(0, @(max_temp_idx));"
  // 693:       :
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[34] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_543;
}
static void entry__compiler__sim2c_507(void) {
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
  // 685: %%compiler::actions empty_list
  set__compiler__actions(get__empty_list());
  // 686: %%compiler::delayed_code ""
  set__compiler__delayed_code(empty_string);
  // 687: ... :
  // 688:   if
  // 689:     is_main:
  // 690:       begin_continuation "main_entry"
  // 691:       if max_temp_idx > 0:
  // 692:         writeln "  allocate_initialized_frame_gc(0, @(max_temp_idx));"
  // 693:     :
  // 694:       write_to_continuation_table "  {run__@(module_name), NULL, "
  // 695:       write "
  // 696:         static int already_run = false;
  // ...
  frame->slots[7] /* temp__1 */ = create_closure(entry__compiler__sim2c_508, 0);
  // 687: collect_output $code:
  // 688:   if
  // 689:     is_main:
  // 690:       begin_continuation "main_entry"
  // 691:       if max_temp_idx > 0:
  // 692:         writeln "  allocate_initialized_frame_gc(0, @(max_temp_idx));"
  // 693:     :
  // 694:       write_to_continuation_table "  {run__@(module_name), NULL, "
  // 695:       write "
  // 696:         static int already_run = false;
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_538;
}
static void entry__compiler__sim2c_526(void) {
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
  // 707: write_source_as_remark info
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 0;
  myself = get__write_source_as_remark();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_527;
}
static void cont__compiler__sim2c_527(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 709: ... mangle_filename(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = frame->slots[2] /* mangle_filename */;
  func = myself->type;
  frame->cont = cont__compiler__sim2c_528;
}
static void cont__compiler__sim2c_528(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 710: ... mangle_filename(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = frame->slots[2] /* mangle_filename */;
  func = myself->type;
  frame->cont = cont__compiler__sim2c_529;
}
static void cont__compiler__sim2c_529(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 708: ... "
  // 709:     func = run__@(mangle_filename(name));
  // 710:     frame->cont = cont__run__@(mangle_filename(name));
  // 711:   }
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
  frame->cont = cont__compiler__sim2c_533;
}
static void cont__compiler__sim2c_533(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 708: write "
  // 709:     func = run__@(mangle_filename(name));
  // 710:     frame->cont = cont__run__@(mangle_filename(name));
  // 711:   }
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_534;
}
static void cont__compiler__sim2c_534(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 712: ... mangle_filename(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = frame->slots[2] /* mangle_filename */;
  func = myself->type;
  frame->cont = cont__compiler__sim2c_535;
}
static void cont__compiler__sim2c_535(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 712: $continuation "cont__run__@(mangle_filename(name))"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__6a214ac420f089ff;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_537;
}
static void cont__compiler__sim2c_537(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* continuation */, arguments->slots[0]);
  // 713: next_continuation continuation
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* continuation */;
  result_count = frame->caller_result_count;
  myself = get__next_continuation();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_508(void) {
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
  // 689: ... :
  // 690:   begin_continuation "main_entry"
  // 691:   if max_temp_idx > 0:
  // 692:     writeln "  allocate_initialized_frame_gc(0, @(max_temp_idx));"
  frame->slots[3] /* temp__1 */ = create_closure(entry__compiler__sim2c_509, 0);
  // 693: :
  // 694:   write_to_continuation_table "  {run__@(module_name), NULL, "
  // 695:   write "
  // 696:     static int already_run = false;
  // 697:     
  // 698:     EXPORT void run__@(module_name)(void) {
  // 699:       if (already_run) {
  // 700:         func = frame->cont;
  // 701:         frame->cont = invalid_continuation;
  // 702:         return;
  // ...
  frame->slots[4] /* temp__2 */ = create_closure(entry__compiler__sim2c_517, 0);
  // 688: if
  // 689:   is_main:
  // 690:     begin_continuation "main_entry"
  // 691:     if max_temp_idx > 0:
  // 692:       writeln "  allocate_initialized_frame_gc(0, @(max_temp_idx));"
  // 693:   :
  // 694:     write_to_continuation_table "  {run__@(module_name), NULL, "
  // 695:     write "
  // 696:       static int already_run = false;
  // 697:       
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* is_main */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  arguments->slots[2] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_525;
}
static void entry__compiler__sim2c_513(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // max_temp_idx: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* max_temp_idx */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 692: ... "  allocate_initialized_frame_gc(0, @(max_temp_idx));"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__41028e5a9545c479;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* max_temp_idx */;
  arguments->slots[2] = string__2d7981f4e6402bfe;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_516;
}
static void cont__compiler__sim2c_516(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 692: writeln "  allocate_initialized_frame_gc(0, @(max_temp_idx));"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_509(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // max_temp_idx: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* max_temp_idx */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 690: begin_continuation "main_entry"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__295c7d0427bb24d8;
  result_count = 0;
  myself = get__begin_continuation();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_511;
}
static void cont__compiler__sim2c_511(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 691: ... max_temp_idx > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* max_temp_idx */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_512;
}
static void cont__compiler__sim2c_512(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 691: ... :
  // 692:   writeln "  allocate_initialized_frame_gc(0, @(max_temp_idx));"
  frame->slots[2] /* temp__2 */ = create_closure(entry__compiler__sim2c_513, 0);
  // 691: if max_temp_idx > 0:
  // 692:   writeln "  allocate_initialized_frame_gc(0, @(max_temp_idx));"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_517(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // max_temp_idx: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* max_temp_idx */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 694: ... "  {run__@(module_name), NULL, "
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__4594ae5b852cb87f;
  arguments->slots[1] = get__module_name();
  arguments->slots[2] = string__3794a6c106b6c980;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_520;
}
static void cont__compiler__sim2c_520(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 694: write_to_continuation_table "  {run__@(module_name), NULL, "
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 0;
  myself = get__write_to_continuation_table();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_521;
}
static void cont__compiler__sim2c_521(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 695: ... "
  // 696:   static int already_run = false;
  // 697:   
  // 698:   EXPORT void run__@(module_name)(void) {
  // 699:     if (already_run) {
  // 700:       func = frame->cont;
  // 701:       frame->cont = invalid_continuation;
  // 702:       return;
  // 703:     }
  // 704:     already_run = true;
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
  frame->cont = cont__compiler__sim2c_524;
}
static void cont__compiler__sim2c_524(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 695: write "
  // 696:   static int already_run = false;
  // 697:   
  // 698:   EXPORT void run__@(module_name)(void) {
  // 699:     if (already_run) {
  // 700:       func = frame->cont;
  // 701:       frame->cont = invalid_continuation;
  // 702:       return;
  // 703:     }
  // 704:     already_run = true;
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_525(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 706: ... : (name info)
  // 707:   write_source_as_remark info
  // 708:   write "
  // 709:       func = run__@(mangle_filename(name));
  // 710:       frame->cont = cont__run__@(mangle_filename(name));
  // 711:     }
  // 712:   $continuation "cont__run__@(mangle_filename(name))"
  // 713:   next_continuation continuation
  frame->slots[3] /* temp__1 */ = create_closure(entry__compiler__sim2c_526, 2);
  // 706: for_each required_modules: (name info)
  // 707:   write_source_as_remark info
  // 708:   write "
  // 709:       func = run__@(mangle_filename(name));
  // 710:       frame->cont = cont__run__@(mangle_filename(name));
  // 711:     }
  // 712:   $continuation "cont__run__@(mangle_filename(name))"
  // 713:   next_continuation continuation
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__required_modules();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_538(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* code */, arguments->slots[0]);
  // 714: ... : append &generated_code code
  frame->slots[7] /* temp__1 */ = create_closure(entry__compiler__sim2c_539, 0);
  // 714: push &actions: append &generated_code code
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[7] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_541;
}
static void entry__compiler__sim2c_539(void) {
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
  // 714: ... append &generated_code code
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_code */;
  arguments->slots[1] = frame->slots[1] /* code */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_540;
}
static void cont__compiler__sim2c_540(void) {
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
static void cont__compiler__sim2c_541(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__actions(arguments->slots[0]);
  // 715: push &all_actions actions
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* all_actions */;
  arguments->slots[1] = get__actions();
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_542;
}
static void cont__compiler__sim2c_542(void) {
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
static void cont__compiler__sim2c_543(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 716: $def_count length_of(all_definitions)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[10])->contents /* all_definitions */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_544;
}
static void cont__compiler__sim2c_544(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[32] /* def_count */, arguments->slots[0]);
  // 717: ... : (stmt_idx stmts)
  // 718:   %%compiler::actions empty_list
  // 719:   %%compiler::delayed_code ""
  // 720:   %compiler::suffix string("__" stmt_idx+def_count)
  // 721:   %%compiler::index 0
  // 722:   collect_output $code: for_each stmts: (stmt) generate_statement stmt
  // 723:   if delayed_code != "": write_to_delayed_statements delayed_code
  // 724:   push &actions: append &generated_code code
  // 725:   push &all_actions actions
  frame->slots[34] /* temp__1 */ = create_closure(entry__compiler__sim2c_545, 2);
  // 717: for_each all_statements: (stmt_idx stmts)
  // 718:   %%compiler::actions empty_list
  // 719:   %%compiler::delayed_code ""
  // 720:   %compiler::suffix string("__" stmt_idx+def_count)
  // 721:   %%compiler::index 0
  // 722:   collect_output $code: for_each stmts: (stmt) generate_statement stmt
  // 723:   if delayed_code != "": write_to_delayed_statements delayed_code
  // 724:   push &actions: append &generated_code code
  // 725:   push &all_actions actions
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[11])->contents /* all_statements */;
  arguments->slots[1] = frame->slots[34] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_559;
}
static void entry__compiler__sim2c_545(void) {
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
  frame->slots[3] = myself->closure.frame->slots[32]; /* def_count */
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
  // 718: %%compiler::actions empty_list
  set__compiler__actions(get__empty_list());
  // 719: %%compiler::delayed_code ""
  set__compiler__delayed_code(empty_string);
  // 720: ... stmt_idx+def_count
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stmt_idx */;
  arguments->slots[1] = frame->slots[3] /* def_count */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_546;
}
static void cont__compiler__sim2c_546(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 720: %compiler::suffix string("__" stmt_idx+def_count)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e5f02b9a;
  arguments->slots[1] = frame->slots[7] /* temp__1 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_547;
}
static void cont__compiler__sim2c_547(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(get__compiler__suffix(), arguments->slots[0]);
  // 721: %%compiler::index 0
  set__compiler__index(number__0);
  // 722: ... : for_each stmts: (stmt) generate_statement stmt
  frame->slots[7] /* temp__1 */ = create_closure(entry__compiler__sim2c_548, 0);
  // 722: collect_output $code: for_each stmts: (stmt) generate_statement stmt
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_550;
}
static void entry__compiler__sim2c_549(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // stmt: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 722: ... generate_statement stmt
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stmt */;
  result_count = frame->caller_result_count;
  myself = get__generate_statement();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_548(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // stmts: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* stmts */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 722: ... for_each stmts: (stmt) generate_statement stmt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stmts */;
  arguments->slots[1] = func__compiler__sim2c_549;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_550(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* code */, arguments->slots[0]);
  // 723: ... delayed_code != ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__delayed_code();
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_551;
}
static void cont__compiler__sim2c_551(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 723: ... delayed_code != ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_552;
}
static void cont__compiler__sim2c_552(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 723: if delayed_code != "": write_to_delayed_statements delayed_code
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = func__compiler__sim2c_553;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_554;
}
static void entry__compiler__sim2c_553(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 723: ... write_to_delayed_statements delayed_code
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__delayed_code();
  result_count = frame->caller_result_count;
  myself = get__write_to_delayed_statements();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_554(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 724: ... : append &generated_code code
  frame->slots[7] /* temp__1 */ = create_closure(entry__compiler__sim2c_555, 0);
  // 724: push &actions: append &generated_code code
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[7] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_557;
}
static void entry__compiler__sim2c_555(void) {
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
  // 724: ... append &generated_code code
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_code */;
  arguments->slots[1] = frame->slots[1] /* code */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_556;
}
static void cont__compiler__sim2c_556(void) {
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
static void cont__compiler__sim2c_557(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__actions(arguments->slots[0]);
  // 725: push &all_actions actions
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* all_actions */;
  arguments->slots[1] = get__actions();
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_558;
}
static void cont__compiler__sim2c_558(void) {
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
static void cont__compiler__sim2c_559(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 726: ... :
  // 727:   %%compiler::actions empty_list
  // 728:   collect_output $code:
  // 729:     if
  // 730:       is_main:
  // 731:         write "
  // 732:             terminate(0); // should never be reached
  // 733:           }
  // 734:       :
  // 735:         write "
  // ...
  frame->slots[34] /* temp__1 */ = create_closure(entry__compiler__sim2c_560, 0);
  // 726: do:
  // 727:   %%compiler::actions empty_list
  // 728:   collect_output $code:
  // 729:     if
  // 730:       is_main:
  // 731:         write "
  // 732:             terminate(0); // should never be reached
  // 733:           }
  // 734:       :
  // 735:         write "
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[34] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_572;
}
static void entry__compiler__sim2c_560(void) {
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
  // 727: %%compiler::actions empty_list
  set__compiler__actions(get__empty_list());
  // 728: ... :
  // 729:   if
  // 730:     is_main:
  // 731:       write "
  // 732:           terminate(0); // should never be reached
  // 733:         }
  // 734:     :
  // 735:       write "
  // 736:           frame = frame->caller_frame;
  // 737:           func = frame->cont;
  // ...
  frame->slots[5] /* temp__1 */ = create_closure(entry__compiler__sim2c_561, 0);
  // 728: collect_output $code:
  // 729:   if
  // 730:     is_main:
  // 731:       write "
  // 732:           terminate(0); // should never be reached
  // 733:         }
  // 734:     :
  // 735:       write "
  // 736:           frame = frame->caller_frame;
  // 737:           func = frame->cont;
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_567;
}
static void entry__compiler__sim2c_561(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // is_main: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* is_main */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 729: if
  // 730:   is_main:
  // 731:     write "
  // 732:         terminate(0); // should never be reached
  // 733:       }
  // 734:   :
  // 735:     write "
  // 736:         frame = frame->caller_frame;
  // 737:         func = frame->cont;
  // 738:         frame->cont = invalid_continuation;
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* is_main */;
  arguments->slots[1] = func__compiler__sim2c_562;
  arguments->slots[2] = func__compiler__sim2c_564;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_566;
}
static void entry__compiler__sim2c_562(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 731: write "
  // 732:     terminate(0); // should never be reached
  // 733:   }
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__5c9d8231ad282235;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_564(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 735: write "
  // 736:     frame = frame->caller_frame;
  // 737:     func = frame->cont;
  // 738:     frame->cont = invalid_continuation;
  // 739:   }
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__a61426acc3f10dab;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_566(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 740: end_continuation
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__end_continuation();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_567(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* code */, arguments->slots[0]);
  // 741: ... : append &generated_code code
  frame->slots[5] /* temp__1 */ = create_closure(entry__compiler__sim2c_568, 0);
  // 741: push &actions: append &generated_code code
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_570;
}
static void entry__compiler__sim2c_568(void) {
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
  // 741: ... append &generated_code code
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_code */;
  arguments->slots[1] = frame->slots[1] /* code */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_569;
}
static void cont__compiler__sim2c_569(void) {
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
static void cont__compiler__sim2c_570(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__actions(arguments->slots[0]);
  // 742: push &all_actions actions
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* all_actions */;
  arguments->slots[1] = get__actions();
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_571;
}
static void cont__compiler__sim2c_571(void) {
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
static void cont__compiler__sim2c_572(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 743: for_each all_actions: (stmt_actions) for_each stmt_actions: (action) action
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[8])->contents /* all_actions */;
  arguments->slots[1] = func__compiler__sim2c_573;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_575;
}
static void entry__compiler__sim2c_574(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // action: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 743: ... action
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* action */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_573(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // stmt_actions: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 743: ... for_each stmt_actions: (action) action
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stmt_actions */;
  arguments->slots[1] = func__compiler__sim2c_574;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_575(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 744: for_each required_modules: (name _info) writeln "/// require @(name)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__required_modules();
  arguments->slots[1] = func__compiler__sim2c_576;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_579;
}
static void entry__compiler__sim2c_576(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // name: 0
  // info: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 744: ... "/// require @(name)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__58cb04c59ab3549a;
  arguments->slots[1] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_578;
}
static void cont__compiler__sim2c_578(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 744: ... writeln "/// require @(name)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_579(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 745: for_each linked_libraries: (name) writeln "/// link @(name)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__linked_libraries();
  arguments->slots[1] = func__compiler__sim2c_580;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_583;
}
static void entry__compiler__sim2c_580(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // name: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 745: ... "/// link @(name)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7d8c250ccd5bbd65;
  arguments->slots[1] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_582;
}
static void cont__compiler__sim2c_582(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 745: ... writeln "/// link @(name)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_583(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 746: for_each dependent_data: (filemask) writeln "/// data @(filemask)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__dependent_data();
  arguments->slots[1] = func__compiler__sim2c_584;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_587;
}
static void entry__compiler__sim2c_584(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // filemask: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 746: ... "/// data @(filemask)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__6d8c238ccd0b3d65;
  arguments->slots[1] = frame->slots[0] /* filemask */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_586;
}
static void cont__compiler__sim2c_586(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 746: ... writeln "/// data @(filemask)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_587(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 747: ... required_modules.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__required_modules();
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_588;
}
static void cont__compiler__sim2c_588(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[34] /* temp__1 */ = arguments->slots[0];
  // 747: unless required_modules.is_empty writeln
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[34] /* temp__1 */;
  arguments->slots[1] = get__writeln();
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_589;
}
static void cont__compiler__sim2c_589(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 748: !included_files("runtime/platform.h")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__3ae3b0d72c49c8db;
  arguments->slots[1] = get__true();
  result_count = 1;
  myself = get__included_files();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_591;
}
static void cont__compiler__sim2c_591(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__included_files(arguments->slots[0]);
  // 749: if use_inline_c:
  // 750:   !included_files("stdint.h") true
  // 751:   !included_files("stdlib.h") true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__use_inline_c();
  arguments->slots[1] = func__compiler__sim2c_592;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_597;
}
static void entry__compiler__sim2c_592(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 750: !included_files("stdint.h")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__72c4a8d406a50228;
  arguments->slots[1] = get__true();
  result_count = 1;
  myself = get__included_files();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_594;
}
static void cont__compiler__sim2c_594(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__included_files(arguments->slots[0]);
  // 751: !included_files("stdlib.h")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7cc4ad5406a55228;
  arguments->slots[1] = get__true();
  result_count = 1;
  myself = get__included_files();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_596;
}
static void cont__compiler__sim2c_596(void) {
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
static void cont__compiler__sim2c_597(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 752: for_each included_files: (name) writeln "#include <@(name)>"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__included_files();
  arguments->slots[1] = func__compiler__sim2c_598;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_602;
}
static void entry__compiler__sim2c_598(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // name: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 752: ... "#include <@(name)>"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__3d6a095dad2a247d;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__578a5af303e9cdf;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_601;
}
static void cont__compiler__sim2c_601(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 752: ... writeln "#include <@(name)>"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_602(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 753: ... included_files.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__included_files();
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_603;
}
static void cont__compiler__sim2c_603(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[34] /* temp__1 */ = arguments->slots[0];
  // 753: unless included_files.is_empty writeln
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[34] /* temp__1 */;
  arguments->slots[1] = get__writeln();
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_604;
}
static void cont__compiler__sim2c_604(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 754: write "
  // 755:   /**********************
  // 756:   D E C L A R A T I O N S
  // 757:   **********************/
  // 758:   
  // 759:   #ifndef IMPORT
  // 760:     #define IMPORT extern
  // 761:   #endif
  // 762:   
  // 763:   #ifndef EXPORT
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__36e833feb0906b55;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_606;
}
static void cont__compiler__sim2c_606(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 772: ... included_files("stdint.h")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__72c4a8d406a50228;
  result_count = 1;
  myself = get__included_files();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_607;
}
static void cont__compiler__sim2c_607(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[34] /* temp__1 */ = arguments->slots[0];
  // 772: unless included_files("stdint.h"):
  // 773:   write "
  // 774:     typedef __INT8_TYPE__ int8_t;
  // 775:     typedef __INT16_TYPE__ int16_t;
  // 776:     typedef __INT32_TYPE__ int32_t;
  // 777:     typedef __INT64_TYPE__ int64_t;
  // 778:     typedef __INTPTR_TYPE__ intptr_t;
  // 779:     
  // 780:     #ifdef __UINT8_TYPE__
  // 781:       typedef __UINT8_TYPE__ uint8_t;
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[34] /* temp__1 */;
  arguments->slots[1] = func__compiler__sim2c_608;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_610;
}
static void entry__compiler__sim2c_608(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 773: write "
  // 774:   typedef __INT8_TYPE__ int8_t;
  // 775:   typedef __INT16_TYPE__ int16_t;
  // 776:   typedef __INT32_TYPE__ int32_t;
  // 777:   typedef __INT64_TYPE__ int64_t;
  // 778:   typedef __INTPTR_TYPE__ intptr_t;
  // 779:   
  // 780:   #ifdef __UINT8_TYPE__
  // 781:     typedef __UINT8_TYPE__ uint8_t;
  // 782:   #else
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__a047b2b18829c385;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_610(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 809: ... included_files("stdlib.h")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7cc4ad5406a55228;
  result_count = 1;
  myself = get__included_files();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_611;
}
static void cont__compiler__sim2c_611(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[35] /* temp__2 */ = arguments->slots[0];
  // 809: ... included_files("stdlib.h") || included_files("stddef.h")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[35] /* temp__2 */;
  arguments->slots[1] = func__compiler__sim2c_612;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_615;
}
static void entry__compiler__sim2c_612(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 809: ... included_files("stddef.h")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__64c4ac5406a5d228;
  result_count = 1;
  myself = get__included_files();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_614;
}
static void cont__compiler__sim2c_614(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 809: ... included_files("stddef.h")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__sim2c_615(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[34] /* temp__1 */ = arguments->slots[0];
  // 809: unless included_files("stdlib.h") || included_files("stddef.h"):
  // 810:   write "
  // 811:     typedef __SIZE_TYPE__ size_t;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[34] /* temp__1 */;
  arguments->slots[1] = func__compiler__sim2c_616;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_618;
}
static void entry__compiler__sim2c_616(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 810: write "
  // 811:   typedef __SIZE_TYPE__ size_t;
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__b0f44c3748f83ed0;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_618(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 812: write "
  // 813:   // INSERT HERE //
  // 814:   
  // 815:   #if UINTPTR_MAX == 0xffffffffffffffff
  // 816:     #define FIRST_INVALID_ADDRESS 0xc000000000000000UL
  // 817:     #define SAMPLE_POINTER ((void *)0x123456789abcdef0UL)
  // 818:   #else
  // 819:     #define FIRST_INVALID_ADDRESS 0xc0000000
  // 820:     #define SAMPLE_POINTER ((void *)0x12345678)
  // 821:   #endif
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__96a80854500bbe37;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_620;
}
static void cont__compiler__sim2c_620(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 857: for_each needed_names: (name info)
  // 858:   if variable_kind_of(info) == POLYMORPHIC:
  // 859:     writeln "static int poly_idx__@(name);"
  // 860:   writeln "static NODE_GETTER get__@(name);"
  // 861:   if variable_kind_of(info) == STATIC_SINGLE:
  // 862:     writeln "static NODE_GETTER get_value_or_future__@(name);"
  // 863:   case variable_kind_of(info) STATIC_MULTI, DYNAMIC_MULTI:
  // 864:     writeln "static NODE_SETTER set__@(name);"
  // 865:   case variable_kind_of(info) DYNAMIC_SINGLE, DYNAMIC_MULTI:
  // 866:     writeln "static NODE_SETTER define__@(name);"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__needed_names();
  arguments->slots[1] = func__compiler__sim2c_621;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_649;
}
static void entry__compiler__sim2c_646(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 866: ... "static NODE_SETTER define__@(name);"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__16f790c158cdffe3;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__578a5af303e9cda;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_648;
}
static void cont__compiler__sim2c_648(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 866: writeln "static NODE_SETTER define__@(name);"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_621(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // name: 0
  // info: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 858: ... variable_kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__variable_kind_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_622;
}
static void cont__compiler__sim2c_622(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 858: ... variable_kind_of(info) == POLYMORPHIC
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = get__POLYMORPHIC();
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_623;
}
static void cont__compiler__sim2c_623(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 858: ... :
  // 859:   writeln "static int poly_idx__@(name);"
  frame->slots[4] /* temp__3 */ = create_closure(entry__compiler__sim2c_624, 0);
  // 858: if variable_kind_of(info) == POLYMORPHIC:
  // 859:   writeln "static int poly_idx__@(name);"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_628;
}
static void entry__compiler__sim2c_624(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 859: ... "static int poly_idx__@(name);"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__dd59fa996655f7be;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__578a5af303e9cda;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_627;
}
static void cont__compiler__sim2c_627(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 859: writeln "static int poly_idx__@(name);"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_628(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 860: ... "static NODE_GETTER get__@(name);"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7bc4c42d1b67ee3a;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__578a5af303e9cda;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_630;
}
static void cont__compiler__sim2c_630(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 860: writeln "static NODE_GETTER get__@(name);"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__writeln();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_631;
}
static void cont__compiler__sim2c_631(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 861: ... variable_kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__variable_kind_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_632;
}
static void cont__compiler__sim2c_632(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 861: ... variable_kind_of(info) == STATIC_SINGLE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = get__STATIC_SINGLE();
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_633;
}
static void cont__compiler__sim2c_633(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 861: ... :
  // 862:   writeln "static NODE_GETTER get_value_or_future__@(name);"
  frame->slots[4] /* temp__3 */ = create_closure(entry__compiler__sim2c_634, 0);
  // 861: if variable_kind_of(info) == STATIC_SINGLE:
  // 862:   writeln "static NODE_GETTER get_value_or_future__@(name);"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_637;
}
static void entry__compiler__sim2c_634(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 862: ... "static NODE_GETTER get_value_or_future__@(name);"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__f144f4e2b96df7e3;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__578a5af303e9cda;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_636;
}
static void cont__compiler__sim2c_636(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 862: writeln "static NODE_GETTER get_value_or_future__@(name);"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_637(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 863: ... variable_kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__variable_kind_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_638;
}
static void cont__compiler__sim2c_638(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 863: ... STATIC_MULTI, DYNAMIC_MULTI
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__STATIC_MULTI();
  arguments->slots[1] = get__DYNAMIC_MULTI();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_639;
}
static void cont__compiler__sim2c_639(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 863: ... :
  // 864:   writeln "static NODE_SETTER set__@(name);"
  frame->slots[4] /* temp__3 */ = create_closure(entry__compiler__sim2c_640, 0);
  // 863: case variable_kind_of(info) STATIC_MULTI, DYNAMIC_MULTI:
  // 864:   writeln "static NODE_SETTER set__@(name);"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = frame->slots[4] /* temp__3 */;
  result_count = 0;
  myself = get__case();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_643;
}
static void entry__compiler__sim2c_640(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 864: ... "static NODE_SETTER set__@(name);"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7bc4c42d1b4eae3a;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__578a5af303e9cda;
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
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 864: writeln "static NODE_SETTER set__@(name);"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_643(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 865: ... variable_kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__variable_kind_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_644;
}
static void cont__compiler__sim2c_644(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 865: ... DYNAMIC_SINGLE, DYNAMIC_MULTI
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__DYNAMIC_SINGLE();
  arguments->slots[1] = get__DYNAMIC_MULTI();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_645;
}
static void cont__compiler__sim2c_645(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 865: ... :
  // 866:   writeln "static NODE_SETTER define__@(name);"
  frame->slots[4] /* temp__3 */ = create_closure(entry__compiler__sim2c_646, 0);
  // 865: case variable_kind_of(info) DYNAMIC_SINGLE, DYNAMIC_MULTI:
  // 866:   writeln "static NODE_SETTER define__@(name);"
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
static void cont__compiler__sim2c_649(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 867: write "
  // 868:   static struct {
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__ff4edce8b0a2fa27;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_651;
}
static void cont__compiler__sim2c_651(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 869: write generated_top_level_variable_declarations
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[16])->contents /* generated_top_level_variable_declarations */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_652;
}
static void cont__compiler__sim2c_652(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 870: write generated_global_variable_declarations
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[17])->contents /* generated_global_variable_declarations */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_653;
}
static void cont__compiler__sim2c_653(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 871: write "
  // 872:   } var;
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__b07009729763a0f0;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_655;
}
static void cont__compiler__sim2c_655(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 873: write "
  // 874:   static const char *var_names[] = {
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__75573d7e471fdc32;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_657;
}
static void cont__compiler__sim2c_657(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 875: ... generated_top_level_variable_names != ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[15])->contents /* generated_top_level_variable_names */;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_658;
}
static void cont__compiler__sim2c_658(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[35] /* temp__2 */ = arguments->slots[0];
  // 875: ... generated_top_level_variable_names != ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[35] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_659;
}
static void cont__compiler__sim2c_659(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[34] /* temp__1 */ = arguments->slots[0];
  // 875: ... :
  // 876:   writeln range(generated_top_level_variable_names 1 -3)
  frame->slots[36] /* temp__3 */ = create_closure(entry__compiler__sim2c_660, 0);
  // 875: if generated_top_level_variable_names != "":
  // 876:   writeln range(generated_top_level_variable_names 1 -3)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[34] /* temp__1 */;
  arguments->slots[1] = frame->slots[36] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_663;
}
static void entry__compiler__sim2c_660(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // generated_top_level_variable_names: 0
  frame->slots[0] = myself->closure.frame->slots[15]; /* generated_top_level_variable_names */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 876: ... 3
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__3;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_661;
}
static void cont__compiler__sim2c_661(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 876: ... range(generated_top_level_variable_names 1 -3)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_top_level_variable_names */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_662;
}
static void cont__compiler__sim2c_662(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 876: writeln range(generated_top_level_variable_names 1 -3)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_663(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 877: write "};@nl;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__fa727015ff16bc6;
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
  // 878: write generated_declarations
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[14])->contents /* generated_declarations */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_666;
}
static void cont__compiler__sim2c_666(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 886: if
  // 887:   is_main:
  // 888:     writeln "static void main_entry(void);"
  // 889:   :
  // 890:     writeln "void run__@(module_name)(void);"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* is_main */;
  arguments->slots[1] = func__compiler__sim2c_667;
  arguments->slots[2] = func__compiler__sim2c_669;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_673;
}
static void entry__compiler__sim2c_667(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 888: writeln "static void main_entry(void);"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__c3452dad239e6464;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_669(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 890: ... "void run__@(module_name)(void);"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__1f74a3bba8d254fe;
  arguments->slots[1] = get__module_name();
  arguments->slots[2] = string__a1240cd997f230c1;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_672;
}
static void cont__compiler__sim2c_672(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 890: writeln "void run__@(module_name)(void);"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_673(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 891: write "
  // 892:   
  // 893:   static CONTINUATION_INFO continuation_info[] = {
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__b4688827b8af4941;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_675;
}
static void cont__compiler__sim2c_675(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 894: append &generated_continuation_table generated_delayed_continuation_table
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[18])->contents /* generated_continuation_table */;
  arguments->slots[1] = ((CELL *)frame->slots[19])->contents /* generated_delayed_continuation_table */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_676;
}
static void cont__compiler__sim2c_676(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[18])->contents /* generated_continuation_table */ = arguments->slots[0];
  // 895: ... generated_continuation_table != ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[18])->contents /* generated_continuation_table */;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_677;
}
static void cont__compiler__sim2c_677(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[35] /* temp__2 */ = arguments->slots[0];
  // 895: ... generated_continuation_table != ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[35] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_678;
}
static void cont__compiler__sim2c_678(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[34] /* temp__1 */ = arguments->slots[0];
  // 895: ... :
  // 896:   writeln range(generated_continuation_table 1 -3)
  frame->slots[36] /* temp__3 */ = create_closure(entry__compiler__sim2c_679, 0);
  // 895: if generated_continuation_table != "":
  // 896:   writeln range(generated_continuation_table 1 -3)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[34] /* temp__1 */;
  arguments->slots[1] = frame->slots[36] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_682;
}
static void entry__compiler__sim2c_679(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // generated_continuation_table: 0
  frame->slots[0] = myself->closure.frame->slots[18]; /* generated_continuation_table */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 896: ... 3
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__3;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_680;
}
static void cont__compiler__sim2c_680(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 896: ... range(generated_continuation_table 1 -3)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_continuation_table */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_681;
}
static void cont__compiler__sim2c_681(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 896: writeln range(generated_continuation_table 1 -3)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_682(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 897: write "
  // 898:   };
  // 899:   @;
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__380aff8b5e307d33;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_684;
}
static void cont__compiler__sim2c_684(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 900: write "
  // 901:   union NODE {
  // 902:     struct {
  // 903:       FUNC type;
  // 904:       ATTRIBUTES *attributes;
  // 905:     };
  // 906:     CONTINUATION continuation;
  // 907:     CLOSURE closure;
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__817a259dab23f435;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_686;
}
static void cont__compiler__sim2c_686(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 908: if use_inline_c:
  // 909:   for_each defined_nodes: (name _node)
  // 910:     write "  @(name) @(name.to_lower_case);@nl;"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__use_inline_c();
  arguments->slots[1] = func__compiler__sim2c_687;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_694;
}
static void entry__compiler__sim2c_688(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // name: 0
  // node: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 910: ... name.to_lower_case
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__to_lower_case();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_689;
}
static void cont__compiler__sim2c_689(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 910: ... "  @(name) @(name.to_lower_case);@nl;"
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
  frame->cont = cont__compiler__sim2c_693;
}
static void cont__compiler__sim2c_693(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 910: write "  @(name) @(name.to_lower_case);@nl;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_687(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 909: for_each defined_nodes: (name _node)
  // 910:   write "  @(name) @(name.to_lower_case);@nl;"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__defined_nodes();
  arguments->slots[1] = func__compiler__sim2c_688;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_694(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 911: write "};@nl;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__fa727015ff16bc6;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_695;
}
static void cont__compiler__sim2c_695(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 912: write generated_functions
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[20])->contents /* generated_functions */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_696;
}
static void cont__compiler__sim2c_696(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 913: for_each used_literals: (name _literal) write "static NODE *@(name);@nl;"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[30])->contents /* used_literals */;
  arguments->slots[1] = func__compiler__sim2c_697;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_700;
}
static void entry__compiler__sim2c_697(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // name: 0
  // literal: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 913: ... "static NODE *@(name);@nl;"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__cb6a78473f66a6a1;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__2d7981f4e6d02bcf;
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
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 913: ... write "static NODE *@(name);@nl;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_700(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 914: write "
  // 915:   
  // 916:   static const char *used_namespaces[] = {
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__44a800d7e66fda5b;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_702;
}
static void cont__compiler__sim2c_702(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 917: for_each used_namespaces: (name) write "  @quot;@(name)@quot;,@nl;"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__used_namespaces();
  arguments->slots[1] = func__compiler__sim2c_703;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_707;
}
static void entry__compiler__sim2c_703(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // name: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 917: ... "  @quot;@(name)@quot;,@nl;"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__fa730415f296bee;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__fa730c15f496bc6;
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
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 917: ... write "  @quot;@(name)@quot;,@nl;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_707(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 918: ... "
  // 919:     NULL
  // 920:   };
  // 921:   
  // 922:   static MODULE_INFO module_info = {
  // 923:     NULL,
  // 924:     "@(module_name)",
  // 925:     continuation_info,
  // 926:     sizeof(continuation_info)/sizeof(CONTINUATION_INFO),
  // 927:     (NODE **)&var,
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__5e3d918a06749390;
  arguments->slots[1] = get__module_name();
  arguments->slots[2] = string__b90701ef69cd6166;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_710;
}
static void cont__compiler__sim2c_710(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[34] /* temp__1 */ = arguments->slots[0];
  // 918: write "
  // 919:     NULL
  // 920:   };
  // 921:   
  // 922:   static MODULE_INFO module_info = {
  // 923:     NULL,
  // 924:     "@(module_name)",
  // 925:     continuation_info,
  // 926:     sizeof(continuation_info)/sizeof(CONTINUATION_INFO),
  // 927:     (NODE **)&var,
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[34] /* temp__1 */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_711;
}
static void cont__compiler__sim2c_711(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 932: $depth count_occurrences(module_name "__")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__module_name();
  arguments->slots[1] = string__2d7981f4e5f02b9a;
  result_count = 1;
  myself = get__count_occurrences();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_712;
}
static void cont__compiler__sim2c_712(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[33] /* depth */, arguments->slots[0]);
  // 934: ... : ($filename)
  // 935:   truncate_until &filename '/' -(depth+1)
  // 936:   write "
  // 937:     DEBUG_FILENAME("@(filename)@quot;)@
  frame->slots[34] /* temp__1 */ = create_closure(entry__compiler__sim2c_713, 1);
  // 933: for_each
  // 934:   filenames: ($filename)
  // 935:     truncate_until &filename '/' -(depth+1)
  // 936:     write "
  // 937:       DEBUG_FILENAME("@(filename)@quot;)@
  // 938:   :
  // 939:     write ", "
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filenames */;
  arguments->slots[1] = frame->slots[34] /* temp__1 */;
  arguments->slots[2] = func__compiler__sim2c_720;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_722;
}
static void entry__compiler__sim2c_713(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // filename: 0
  // depth: 1
  frame->slots[1] = myself->closure.frame->slots[33]; /* depth */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* filename */ = create_cell_with_contents(arguments->slots[0]);
  // 935: ... depth+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* depth */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_714;
}
static void cont__compiler__sim2c_714(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 935: ... depth+1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_715;
}
static void cont__compiler__sim2c_715(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 935: truncate_until &filename '/' -(depth+1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* filename */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_716;
}
static void cont__compiler__sim2c_716(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* filename */ = arguments->slots[0];
  // 936: ... "
  // 937:   DEBUG_FILENAME("@(filename)@quot;)@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__9c11f7a3e8641900;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* filename */;
  arguments->slots[2] = string__2d7981f4e6182bec;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_719;
}
static void cont__compiler__sim2c_719(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 936: write "
  // 937:   DEBUG_FILENAME("@(filename)@quot;)@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_720(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 939: write ", "
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6682be5;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_722(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 940: write "
  // 941:   }
  // 942:   };
  // 943:   
  // 944:   /******
  // 945:   C O D E
  // 946:   ******/
  // 947:   @;
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__d1bc6cafcb964c0d;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_724;
}
static void cont__compiler__sim2c_724(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 948: ... : (name _info)
  // 949:   $fname mangle_filename(name)
  // 950:   write "
  // 951:     IMPORT void collect__@(fname)(void);
  // 952:     IMPORT void phase_1__@(fname)(void);
  // 953:     IMPORT void phase_2__@(fname)(void);
  // 954:     IMPORT void phase_3__@(fname)(void);
  // 955:     IMPORT void phase_4__@(fname)(void);
  // 956:     IMPORT void phase_5__@(fname)(void);
  // 957:     IMPORT void phase_6__@(fname)(void);
  // ...
  frame->slots[34] /* temp__1 */ = create_closure(entry__compiler__sim2c_725, 2);
  // 948: for_each required_modules: (name _info)
  // 949:   $fname mangle_filename(name)
  // 950:   write "
  // 951:     IMPORT void collect__@(fname)(void);
  // 952:     IMPORT void phase_1__@(fname)(void);
  // 953:     IMPORT void phase_2__@(fname)(void);
  // 954:     IMPORT void phase_3__@(fname)(void);
  // 955:     IMPORT void phase_4__@(fname)(void);
  // 956:     IMPORT void phase_5__@(fname)(void);
  // 957:     IMPORT void phase_6__@(fname)(void);
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__required_modules();
  arguments->slots[1] = frame->slots[34] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_736;
}
static void entry__compiler__sim2c_725(void) {
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
  // 949: $fname mangle_filename(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = frame->slots[2] /* mangle_filename */;
  func = myself->type;
  frame->cont = cont__compiler__sim2c_726;
}
static void cont__compiler__sim2c_726(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* fname */, arguments->slots[0]);
  // 950: ... "
  // 951:   IMPORT void collect__@(fname)(void);
  // 952:   IMPORT void phase_1__@(fname)(void);
  // 953:   IMPORT void phase_2__@(fname)(void);
  // 954:   IMPORT void phase_3__@(fname)(void);
  // 955:   IMPORT void phase_4__@(fname)(void);
  // 956:   IMPORT void phase_5__@(fname)(void);
  // 957:   IMPORT void phase_6__@(fname)(void);
  // 958:   IMPORT void run__@(fname)(void);
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
  frame->cont = cont__compiler__sim2c_735;
}
static void cont__compiler__sim2c_735(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 950: write "
  // 951:   IMPORT void collect__@(fname)(void);
  // 952:   IMPORT void phase_1__@(fname)(void);
  // 953:   IMPORT void phase_2__@(fname)(void);
  // 954:   IMPORT void phase_3__@(fname)(void);
  // 955:   IMPORT void phase_4__@(fname)(void);
  // 956:   IMPORT void phase_5__@(fname)(void);
  // 957:   IMPORT void phase_6__@(fname)(void);
  // 958:   IMPORT void run__@(fname)(void);
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_736(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 959: write generated_code
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[27])->contents /* generated_code */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_737;
}
static void cont__compiler__sim2c_737(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 960: write delayed_statements
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[29])->contents /* delayed_statements */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_738;
}
static void cont__compiler__sim2c_738(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 961: ... "
  // 962:   EXPORT void collect__@(module_name)(void) {
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__bcb42196062f3614;
  arguments->slots[1] = get__module_name();
  arguments->slots[2] = string__fc8c36a84adb366f;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_741;
}
static void cont__compiler__sim2c_741(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[34] /* temp__1 */ = arguments->slots[0];
  // 961: write "
  // 962:   EXPORT void collect__@(module_name)(void) {
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[34] /* temp__1 */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_742;
}
static void cont__compiler__sim2c_742(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 963: write generated_collections
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[28])->contents /* generated_collections */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_743;
}
static void cont__compiler__sim2c_743(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 964: write "}@nl;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e4e02bcf;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_745;
}
static void cont__compiler__sim2c_745(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 965: if
  // 966:   is_main:
  // 967:     write "
  // 968:       
  // 969:       int main(int argc, char **argv) {
  // 970:         main_argc = argc;
  // 971:         main_argv = argv;
  // 972:         initialize_runtime();
  // 973:       
  // 974:         // initialization phase 1
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* is_main */;
  arguments->slots[1] = func__compiler__sim2c_746;
  arguments->slots[2] = func__compiler__sim2c_748;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_752;
}
static void entry__compiler__sim2c_746(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 967: write "
  // 968:   
  // 969:   int main(int argc, char **argv) {
  // 970:     main_argc = argc;
  // 971:     main_argv = argv;
  // 972:     initialize_runtime();
  // 973:   
  // 974:     // initialization phase 1
  // 975:   @;
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__25aa47136a75b74b;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_748(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 977: ... "
  // 978:   
  // 979:   static int already_run_phase_1 = false;
  // 980:   
  // 981:   EXPORT void phase_1__@(module_name)(void) {
  // 982:     if (already_run_phase_1) return;
  // 983:     already_run_phase_1 = true;
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__1aafb345f496a1;
  arguments->slots[1] = get__module_name();
  arguments->slots[2] = string__d7e0d1a7b944caae;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_751;
}
static void cont__compiler__sim2c_751(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 977: write "
  // 978:   
  // 979:   static int already_run_phase_1 = false;
  // 980:   
  // 981:   EXPORT void phase_1__@(module_name)(void) {
  // 982:     if (already_run_phase_1) return;
  // 983:     already_run_phase_1 = true;
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_752(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 984: ... : (name _info)
  // 985:   $mangled_name mangle_filename(name)
  // 986:   writeln "  phase_1__@(mangled_name)();"
  frame->slots[34] /* temp__1 */ = create_closure(entry__compiler__sim2c_753, 2);
  // 984: for_each required_modules: (name _info)
  // 985:   $mangled_name mangle_filename(name)
  // 986:   writeln "  phase_1__@(mangled_name)();"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__required_modules();
  arguments->slots[1] = frame->slots[34] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_758;
}
static void entry__compiler__sim2c_753(void) {
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
  // 985: $mangled_name mangle_filename(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = frame->slots[2] /* mangle_filename */;
  func = myself->type;
  frame->cont = cont__compiler__sim2c_754;
}
static void cont__compiler__sim2c_754(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* mangled_name */, arguments->slots[0]);
  // 986: ... "  phase_1__@(mangled_name)();"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__fedb25123ef1fa6f;
  arguments->slots[1] = frame->slots[3] /* mangled_name */;
  arguments->slots[2] = string__fa732415f616bf7;
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
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 986: writeln "  phase_1__@(mangled_name)();"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_758(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 987: write "
  // 988:   @
  // 989:     register_module_info(&module_info);
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__6759f0f7c95235d;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_760;
}
static void cont__compiler__sim2c_760(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 990: for_each defined_namespaces: (namespace)
  // 991:   write "
  // 992:     @
  // 993:       define_namespace("@(namespace)");
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__defined_namespaces();
  arguments->slots[1] = func__compiler__sim2c_761;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_765;
}
static void entry__compiler__sim2c_761(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // namespace: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 991: ... "
  // 992:   @
  // 993:     define_namespace("@(namespace)");
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__d93952e55b2e5d9;
  arguments->slots[1] = frame->slots[0] /* namespace */;
  arguments->slots[2] = string__860afb0b5fb87d33;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_764;
}
static void cont__compiler__sim2c_764(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 991: write "
  // 992:   @
  // 993:     define_namespace("@(namespace)");
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_765(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 994: write generated_phase_1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[21])->contents /* generated_phase_1 */;
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
  //  995: if
  //  996:   is_main:
  //  997:     write "
  //  998:       @
  //  999:       
  // 1000:         // initialization phase 2
  // 1001:   :
  // 1002:     write "
  // 1003:       }
  // 1004:       
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* is_main */;
  arguments->slots[1] = func__compiler__sim2c_767;
  arguments->slots[2] = func__compiler__sim2c_769;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_773;
}
static void entry__compiler__sim2c_767(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  //  997: write "
  //  998:   @
  //  999:   
  // 1000:     // initialization phase 2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__f5b495312d83add5;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_769(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1002: ... "
  // 1003:   }
  // 1004:   
  // 1005:   static int already_run_phase_2 = false;
  // 1006:   
  // 1007:   EXPORT void phase_2__@(module_name)(void) {
  // 1008:     if (already_run_phase_2) return;
  // 1009:     already_run_phase_2 = true;
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__b9a3b0acf1dfe8ab;
  arguments->slots[1] = get__module_name();
  arguments->slots[2] = string__d4e0c9a7b944caae;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_772;
}
static void cont__compiler__sim2c_772(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1002: write "
  // 1003:   }
  // 1004:   
  // 1005:   static int already_run_phase_2 = false;
  // 1006:   
  // 1007:   EXPORT void phase_2__@(module_name)(void) {
  // 1008:     if (already_run_phase_2) return;
  // 1009:     already_run_phase_2 = true;
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_773(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1010: ... : (name _info)
  // 1011:   writeln "  phase_2__@(mangle_filename(name))();"
  frame->slots[34] /* temp__1 */ = create_closure(entry__compiler__sim2c_774, 2);
  // 1010: for_each required_modules: (name _info)
  // 1011:   writeln "  phase_2__@(mangle_filename(name))();"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__required_modules();
  arguments->slots[1] = frame->slots[34] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_778;
}
static void entry__compiler__sim2c_774(void) {
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
  // 1011: ... mangle_filename(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = frame->slots[2] /* mangle_filename */;
  func = myself->type;
  frame->cont = cont__compiler__sim2c_775;
}
static void cont__compiler__sim2c_775(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 1011: ... "  phase_2__@(mangle_filename(name))();"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__fedb25d23ef1fa6f;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = string__fa732415f616bf7;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_777;
}
static void cont__compiler__sim2c_777(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1011: writeln "  phase_2__@(mangle_filename(name))();"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_778(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1012: ... "
  // 1013:   @
  // 1014:     set_module("@(module_name)");
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__f93d0720893942d5;
  arguments->slots[1] = get__module_name();
  arguments->slots[2] = string__860afb0b5fb87d33;
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
  frame->slots[34] /* temp__1 */ = arguments->slots[0];
  // 1012: write "
  // 1013:   @
  // 1014:     set_module("@(module_name)");
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[34] /* temp__1 */;
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
  // 1015: for_each used_literals: (name literal)
  // 1016:   write "  @(name) = "
  // 1017:   cond
  // 1018:     -> literal.is_a_numeric_literal:
  // 1019:       $value replace_all(node::value_of(literal) '@apos;' = "")
  // 1020:       if
  // 1021:         not(value .has_prefix. "0x") && value .contains. alt('.' 'e' 'E'):
  // 1022:           write "from_double(@(value));@nl;"
  // 1023:         :
  // 1024:           $int_val value.to_integer
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[30])->contents /* used_literals */;
  arguments->slots[1] = func__compiler__sim2c_782;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_828;
}
static void entry__compiler__sim2c_823(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // literal: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* literal */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1036: ... node::value_of(literal)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* literal */;
  result_count = 1;
  myself = get__node__value_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_824;
}
static void cont__compiler__sim2c_824(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 1036: ... node::value_of(literal).to_integer
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__to_integer();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_825;
}
static void cont__compiler__sim2c_825(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 1036: ... "from_uchar32(@(node::value_of(literal).to_integer));"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__2666ac8409f84460;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  arguments->slots[2] = string__2d7981f4e6402bfe;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_827;
}
static void cont__compiler__sim2c_827(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1036: writeln "from_uchar32(@(node::value_of(literal).to_integer));"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_814(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // int_val: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* int_val */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1030: ... "
  // 1031:   from_uint64(@(int_val)ULL);
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__228915c9d5a8e125;
  arguments->slots[1] = frame->slots[0] /* int_val */;
  arguments->slots[2] = string__1f441a036092dd;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_817;
}
static void cont__compiler__sim2c_817(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1030: write "
  // 1031:   from_uint64(@(int_val)ULL);
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_807(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // int_val: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* int_val */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1027: ... "
  // 1028:   from_uint32(@(int_val)U);
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__22891489d598e125;
  arguments->slots[1] = frame->slots[0] /* int_val */;
  arguments->slots[2] = string__680afb0b5fb87d33;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_810;
}
static void cont__compiler__sim2c_810(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1027: write "
  // 1028:   from_uint32(@(int_val)U);
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_804(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // int_val: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* int_val */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1026: ... int_val <= 0xffffffff
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0xffffffff;
  arguments->slots[1] = frame->slots[0] /* int_val */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_805;
}
static void cont__compiler__sim2c_805(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 1026: ... int_val <= 0xffffffff
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_806;
}
static void cont__compiler__sim2c_806(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1026: ... :
  // 1027:   write "
  // 1028:     from_uint32(@(int_val)U);
  frame->slots[3] /* temp__3 */ = create_closure(entry__compiler__sim2c_807, 0);
  // 1026: -> int_val <= 0xffffffff:
  // 1027:   write "
  // 1028:     from_uint32(@(int_val)U);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__sim2c_811(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // int_val: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* int_val */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1029: ... int_val <= 0xffffffffffffffff
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0xffffffffffffffff;
  arguments->slots[1] = frame->slots[0] /* int_val */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_812;
}
static void cont__compiler__sim2c_812(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 1029: ... int_val <= 0xffffffffffffffff
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_813;
}
static void cont__compiler__sim2c_813(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1029: ... :
  // 1030:   write "
  // 1031:     from_uint64(@(int_val)ULL);
  frame->slots[3] /* temp__3 */ = create_closure(entry__compiler__sim2c_814, 0);
  // 1029: -> int_val <= 0xffffffffffffffff:
  // 1030:   write "
  // 1031:     from_uint64(@(int_val)ULL);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__sim2c_818(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // value: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1033: ... "
  // 1034:   from_digit_string("@(value)");
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__c470b0c3df48bfe1;
  arguments->slots[1] = frame->slots[0] /* value */;
  arguments->slots[2] = string__860afb0b5fb87d33;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_820;
}
static void cont__compiler__sim2c_820(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1033: write "
  // 1034:   from_digit_string("@(value)");
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_799(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // value: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1022: ... "from_double(@(value));@nl;"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__ecd034ad7215125;
  arguments->slots[1] = frame->slots[0] /* value */;
  arguments->slots[2] = string__fa732015ff16bc6;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_801;
}
static void cont__compiler__sim2c_801(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1022: write "from_double(@(value));@nl;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_802(void) {
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
  // 1024: $int_val value.to_integer
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* value */;
  result_count = 1;
  myself = get__to_integer();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_803;
}
static void cont__compiler__sim2c_803(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* int_val */, arguments->slots[0]);
  // 1026: -> int_val <= 0xffffffff:
  // 1027:   write "
  // 1028:     from_uint32(@(int_val)U);
  frame->slots[2] /* temp__1 */ = create_closure(entry__compiler__sim2c_804, 0);
  // 1029: -> int_val <= 0xffffffffffffffff:
  // 1030:   write "
  // 1031:     from_uint64(@(int_val)ULL);
  frame->slots[3] /* temp__2 */ = create_closure(entry__compiler__sim2c_811, 0);
  // 1032: :
  // 1033:   write "
  // 1034:     from_digit_string("@(value)");
  frame->slots[4] /* temp__3 */ = create_closure(entry__compiler__sim2c_818, 0);
  // 1025: cond
  // 1026:   -> int_val <= 0xffffffff:
  // 1027:     write "
  // 1028:       from_uint32(@(int_val)U);
  // 1029:   -> int_val <= 0xffffffffffffffff:
  // 1030:     write "
  // 1031:       from_uint64(@(int_val)ULL);
  // 1032:   :
  // 1033:     write "
  // 1034:       from_digit_string("@(value)");
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
static void entry__compiler__sim2c_788(void) {
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
  // 1019: ... node::value_of(literal)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* literal */;
  result_count = 1;
  myself = get__node__value_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_789;
}
static void cont__compiler__sim2c_789(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1019: ... '@apos;' = ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__39;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_790;
}
static void cont__compiler__sim2c_790(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 1019: $value replace_all(node::value_of(literal) '@apos;' = "")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_791;
}
static void cont__compiler__sim2c_791(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* value */, arguments->slots[0]);
  // 1021: ... value .has_prefix. "0x"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* value */;
  arguments->slots[1] = string__2d7981f4e6882bbd;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_793;
}
static void cont__compiler__sim2c_793(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 1021: not(value .has_prefix. "0x")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__not();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_794;
}
static void cont__compiler__sim2c_794(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 1021: ... value .contains. alt('.' 'e' 'E')
  frame->slots[5] /* temp__4 */ = create_closure(entry__compiler__sim2c_795, 0);
  // 1021: not(value .has_prefix. "0x") && value .contains. alt('.' 'e' 'E')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_798;
}
static void entry__compiler__sim2c_795(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // value: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1021: ... alt('.' 'e' 'E')
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__46;
  arguments->slots[1] = character__101;
  arguments->slots[2] = character__69;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_796;
}
static void cont__compiler__sim2c_796(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 1021: ... value .contains. alt('.' 'e' 'E')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* value */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_797;
}
static void cont__compiler__sim2c_797(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1021: ... value .contains. alt('.' 'e' 'E')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__sim2c_798(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1021: ... :
  // 1022:   write "from_double(@(value));@nl;"
  frame->slots[6] /* temp__5 */ = create_closure(entry__compiler__sim2c_799, 0);
  // 1023: :
  // 1024:   $int_val value.to_integer
  // 1025:   cond
  // 1026:     -> int_val <= 0xffffffff:
  // 1027:       write "
  // 1028:         from_uint32(@(int_val)U);
  // 1029:     -> int_val <= 0xffffffffffffffff:
  // 1030:       write "
  // 1031:         from_uint64(@(int_val)ULL);
  // 1032:     :
  // ...
  frame->slots[7] /* temp__6 */ = create_closure(entry__compiler__sim2c_802, 0);
  // 1020: if
  // 1021:   not(value .has_prefix. "0x") && value .contains. alt('.' 'e' 'E'):
  // 1022:     write "from_double(@(value));@nl;"
  // 1023:   :
  // 1024:     $int_val value.to_integer
  // 1025:     cond
  // 1026:       -> int_val <= 0xffffffff:
  // 1027:         write "
  // 1028:           from_uint32(@(int_val)U);
  // 1029:       -> int_val <= 0xffffffffffffffff:
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
static void entry__compiler__sim2c_786(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // literal: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* literal */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1018: ... literal.is_a_numeric_literal
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* literal */;
  result_count = 1;
  myself = get__is_a_numeric_literal();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_787;
}
static void cont__compiler__sim2c_787(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1018: ... :
  // 1019:   $value replace_all(node::value_of(literal) '@apos;' = "")
  // 1020:   if
  // 1021:     not(value .has_prefix. "0x") && value .contains. alt('.' 'e' 'E'):
  // 1022:       write "from_double(@(value));@nl;"
  // 1023:     :
  // 1024:       $int_val value.to_integer
  // 1025:       cond
  // 1026:         -> int_val <= 0xffffffff:
  // 1027:           write "
  // ...
  frame->slots[2] /* temp__2 */ = create_closure(entry__compiler__sim2c_788, 0);
  // 1018: -> literal.is_a_numeric_literal:
  // 1019:   $value replace_all(node::value_of(literal) '@apos;' = "")
  // 1020:   if
  // 1021:     not(value .has_prefix. "0x") && value .contains. alt('.' 'e' 'E'):
  // 1022:       write "from_double(@(value));@nl;"
  // 1023:     :
  // 1024:       $int_val value.to_integer
  // 1025:       cond
  // 1026:         -> int_val <= 0xffffffff:
  // 1027:           write "
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__sim2c_821(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // literal: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* literal */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1035: ... literal.is_a_character_literal
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* literal */;
  result_count = 1;
  myself = get__is_a_character_literal();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_822;
}
static void cont__compiler__sim2c_822(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1035: ... :
  // 1036:   writeln "from_uchar32(@(node::value_of(literal).to_integer));"
  frame->slots[2] /* temp__2 */ = create_closure(entry__compiler__sim2c_823, 0);
  // 1035: -> literal.is_a_character_literal:
  // 1036:   writeln "from_uchar32(@(node::value_of(literal).to_integer));"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__sim2c_782(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // name: 0
  // literal: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 1016: ... "  @(name) = "
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6082be5;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__fa730415fc16bec;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_784;
}
static void cont__compiler__sim2c_784(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1016: write "  @(name) = "
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_785;
}
static void cont__compiler__sim2c_785(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1018: -> literal.is_a_numeric_literal:
  // 1019:   $value replace_all(node::value_of(literal) '@apos;' = "")
  // 1020:   if
  // 1021:     not(value .has_prefix. "0x") && value .contains. alt('.' 'e' 'E'):
  // 1022:       write "from_double(@(value));@nl;"
  // 1023:     :
  // 1024:       $int_val value.to_integer
  // 1025:       cond
  // 1026:         -> int_val <= 0xffffffff:
  // 1027:           write "
  // ...
  frame->slots[2] /* temp__1 */ = create_closure(entry__compiler__sim2c_786, 0);
  // 1035: -> literal.is_a_character_literal:
  // 1036:   writeln "from_uchar32(@(node::value_of(literal).to_integer));"
  frame->slots[3] /* temp__2 */ = create_closure(entry__compiler__sim2c_821, 0);
  // 1017: cond
  // 1018:   -> literal.is_a_numeric_literal:
  // 1019:     $value replace_all(node::value_of(literal) '@apos;' = "")
  // 1020:     if
  // 1021:       not(value .has_prefix. "0x") && value .contains. alt('.' 'e' 'E'):
  // 1022:         write "from_double(@(value));@nl;"
  // 1023:       :
  // 1024:         $int_val value.to_integer
  // 1025:         cond
  // 1026:           -> int_val <= 0xffffffff:
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
static void cont__compiler__sim2c_828(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1037: write generated_phase_2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[22])->contents /* generated_phase_2 */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_829;
}
static void cont__compiler__sim2c_829(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1038: if
  // 1039:   is_main:
  // 1040:     write "
  // 1041:       @
  // 1042:       
  // 1043:         // initialization phase 3
  // 1044:       
  // 1045:         initialize_phase_3();
  // 1046:         resolve_symbols();
  // 1047:   :
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* is_main */;
  arguments->slots[1] = func__compiler__sim2c_830;
  arguments->slots[2] = func__compiler__sim2c_832;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_836;
}
static void entry__compiler__sim2c_830(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1040: write "
  // 1041:   @
  // 1042:   
  // 1043:     // initialization phase 3
  // 1044:   
  // 1045:     initialize_phase_3();
  // 1046:     resolve_symbols();
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__cb22ed554b280fb1;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_832(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1048: ... "
  // 1049:   }
  // 1050:   
  // 1051:   static int already_run_phase_3 = false;
  // 1052:   
  // 1053:   EXPORT void phase_3__@(module_name)(void) {
  // 1054:     if (already_run_phase_3) return;
  // 1055:     already_run_phase_3 = true;
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__b9a3b0edf1dfe8ab;
  arguments->slots[1] = get__module_name();
  arguments->slots[2] = string__d5e0c1a7b944caae;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_835;
}
static void cont__compiler__sim2c_835(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1048: write "
  // 1049:   }
  // 1050:   
  // 1051:   static int already_run_phase_3 = false;
  // 1052:   
  // 1053:   EXPORT void phase_3__@(module_name)(void) {
  // 1054:     if (already_run_phase_3) return;
  // 1055:     already_run_phase_3 = true;
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_836(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1056: ... : (name _info)
  // 1057:   writeln "  phase_3__@(mangle_filename(name))();"
  frame->slots[34] /* temp__1 */ = create_closure(entry__compiler__sim2c_837, 2);
  // 1056: for_each required_modules: (name _info)
  // 1057:   writeln "  phase_3__@(mangle_filename(name))();"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__required_modules();
  arguments->slots[1] = frame->slots[34] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_841;
}
static void entry__compiler__sim2c_837(void) {
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
  // 1057: ... mangle_filename(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = frame->slots[2] /* mangle_filename */;
  func = myself->type;
  frame->cont = cont__compiler__sim2c_838;
}
static void cont__compiler__sim2c_838(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 1057: ... "  phase_3__@(mangle_filename(name))();"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__fedb25923ef1fa6f;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = string__fa732415f616bf7;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_840;
}
static void cont__compiler__sim2c_840(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1057: writeln "  phase_3__@(mangle_filename(name))();"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_841(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1058: ... "
  // 1059:   @
  // 1060:     set_module("@(module_name)");
  // 1061:     set_used_namespaces(used_namespaces);
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__f93d0720893942d5;
  arguments->slots[1] = get__module_name();
  arguments->slots[2] = string__f647f212951f31f8;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_843;
}
static void cont__compiler__sim2c_843(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[34] /* temp__1 */ = arguments->slots[0];
  // 1058: write "
  // 1059:   @
  // 1060:     set_module("@(module_name)");
  // 1061:     set_used_namespaces(used_namespaces);
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[34] /* temp__1 */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_844;
}
static void cont__compiler__sim2c_844(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1062: write generated_phase_3
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[23])->contents /* generated_phase_3 */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_845;
}
static void cont__compiler__sim2c_845(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1063: if
  // 1064:   is_main:
  // 1065:     write "
  // 1066:       @
  // 1067:       
  // 1068:         // initialization phase 4
  // 1069:       
  // 1070:         initialize_phase_4();
  // 1071:   :
  // 1072:     write "
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* is_main */;
  arguments->slots[1] = func__compiler__sim2c_846;
  arguments->slots[2] = func__compiler__sim2c_848;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_852;
}
static void entry__compiler__sim2c_846(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1065: write "
  // 1066:   @
  // 1067:   
  // 1068:     // initialization phase 4
  // 1069:   
  // 1070:     initialize_phase_4();
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__19b03dcd2fdc791;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_848(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1072: ... "
  // 1073:   }
  // 1074:   
  // 1075:   static int already_run_phase_4 = false;
  // 1076:   
  // 1077:   EXPORT void phase_4__@(module_name)(void) {
  // 1078:     if (already_run_phase_4) return;
  // 1079:     already_run_phase_4 = true;
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__b9a3b12af1dfe8ab;
  arguments->slots[1] = get__module_name();
  arguments->slots[2] = string__d2e0f9a7b944caae;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_851;
}
static void cont__compiler__sim2c_851(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1072: write "
  // 1073:   }
  // 1074:   
  // 1075:   static int already_run_phase_4 = false;
  // 1076:   
  // 1077:   EXPORT void phase_4__@(module_name)(void) {
  // 1078:     if (already_run_phase_4) return;
  // 1079:     already_run_phase_4 = true;
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
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
  // 1080: ... : (name _info)
  // 1081:   writeln "  phase_4__@(mangle_filename(name))();"
  frame->slots[34] /* temp__1 */ = create_closure(entry__compiler__sim2c_853, 2);
  // 1080: for_each required_modules: (name _info)
  // 1081:   writeln "  phase_4__@(mangle_filename(name))();"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__required_modules();
  arguments->slots[1] = frame->slots[34] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_857;
}
static void entry__compiler__sim2c_853(void) {
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
  frame->cont = cont__compiler__sim2c_854;
}
static void cont__compiler__sim2c_854(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 1081: ... "  phase_4__@(mangle_filename(name))();"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__fedb24523ef1fa6f;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = string__fa732415f616bf7;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_856;
}
static void cont__compiler__sim2c_856(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1081: writeln "  phase_4__@(mangle_filename(name))();"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_857(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1082: ... "
  // 1083:   @
  // 1084:     set_module("@(module_name)");
  // 1085:     set_used_namespaces(used_namespaces);
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__f93d0720893942d5;
  arguments->slots[1] = get__module_name();
  arguments->slots[2] = string__f647f212951f31f8;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_858;
}
static void cont__compiler__sim2c_858(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[34] /* temp__1 */ = arguments->slots[0];
  // 1082: write "
  // 1083:   @
  // 1084:     set_module("@(module_name)");
  // 1085:     set_used_namespaces(used_namespaces);
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[34] /* temp__1 */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_859;
}
static void cont__compiler__sim2c_859(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1086: for_each needed_names: (name info)
  // 1087:   unless global_names(name).is_defined:
  // 1088:     $namespace
  // 1089:       if
  // 1090:         name .contains. "__"
  // 1091:         -> string('@quot;' name .before. "__" '@quot;')
  // 1092:         -> "NULL"
  // 1093:     
  // 1094:     $basename name .truncate_until. "__"
  // 1095:     case variable_kind_of(info)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__needed_names();
  arguments->slots[1] = func__compiler__sim2c_860;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_894;
}
static void entry__compiler__sim2c_873(void) {
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
  // 1097: ... "
  // 1098:   @
  // 1099:     use_polymorphic_function(@(namespace), @quot;@(basename)", @
  // 1100:   &get__@(name), &poly_idx__@(name));
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
  frame->cont = cont__compiler__sim2c_878;
}
static void cont__compiler__sim2c_878(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1097: write "
  // 1098:   @
  // 1099:     use_polymorphic_function(@(namespace), @quot;@(basename)", @
  // 1100:   &get__@(name), &poly_idx__@(name));
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_879(void) {
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
  // 1102: ... "
  // 1103:   @
  // 1104:     use_read_only(@(namespace), @quot;@(basename)", &get__@(name), @
  // 1105:   &get_value_or_future__@(name));
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
  frame->cont = cont__compiler__sim2c_882;
}
static void cont__compiler__sim2c_882(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1102: write "
  // 1103:   @
  // 1104:     use_read_only(@(namespace), @quot;@(basename)", &get__@(name), @
  // 1105:   &get_value_or_future__@(name));
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_883(void) {
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
  // 1107: ... "
  // 1108:   @
  // 1109:     use_read_write(@(namespace), @quot;@(basename)", &get__@(name), @
  // 1110:   &set__@(name));
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
  frame->cont = cont__compiler__sim2c_886;
}
static void cont__compiler__sim2c_886(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1107: write "
  // 1108:   @
  // 1109:     use_read_write(@(namespace), @quot;@(basename)", &get__@(name), @
  // 1110:   &set__@(name));
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_887(void) {
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
  // 1112: ... "
  // 1113:   @
  // 1114:     use_single_assign_dynamic(@(namespace), @quot;@(basename)", @
  // 1115:   &get__@(name), &define__@(name));
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
  frame->cont = cont__compiler__sim2c_890;
}
static void cont__compiler__sim2c_890(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1112: write "
  // 1113:   @
  // 1114:     use_single_assign_dynamic(@(namespace), @quot;@(basename)", @
  // 1115:   &get__@(name), &define__@(name));
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_891(void) {
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
  // 1117: ... "
  // 1118:   @
  // 1119:     use_multi_assign_dynamic(@(namespace), @quot;@(basename)", @
  // 1120:   &get__@(name), &set__@(name), &define__@(name));
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
  frame->cont = cont__compiler__sim2c_893;
}
static void cont__compiler__sim2c_893(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1117: write "
  // 1118:   @
  // 1119:     use_multi_assign_dynamic(@(namespace), @quot;@(basename)", @
  // 1120:   &get__@(name), &set__@(name), &define__@(name));
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_863(void) {
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
  // 1090: name .contains. "__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = string__2d7981f4e5f02b9a;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_864;
}
static void cont__compiler__sim2c_864(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 1091: -> string('@quot;' name .before. "__" '@quot;')
  frame->slots[5] /* temp__2 */ = create_closure(entry__compiler__sim2c_865, 0);
  // 1088: $namespace
  // 1089:   if
  // 1090:     name .contains. "__"
  // 1091:     -> string('@quot;' name .before. "__" '@quot;')
  // 1092:     -> "NULL"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = func__compiler__sim2c_868;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_870;
}
static void entry__compiler__sim2c_865(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1091: ... name .before. "__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = string__2d7981f4e5f02b9a;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_866;
}
static void cont__compiler__sim2c_866(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 1091: ... string('@quot;' name .before. "__" '@quot;')
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__34;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  arguments->slots[2] = character__34;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_867;
}
static void cont__compiler__sim2c_867(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1091: -> string('@quot;' name .before. "__" '@quot;')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__sim2c_868(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1092: -> "NULL"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__5e0ae40b5c007d75;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__sim2c_870(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* namespace */, arguments->slots[0]);
  // 1094: $basename name .truncate_until. "__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = string__2d7981f4e5f02b9a;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_871;
}
static void cont__compiler__sim2c_871(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* basename */, arguments->slots[0]);
  // 1095: ... variable_kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__variable_kind_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_872;
}
static void cont__compiler__sim2c_872(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 1096: ... :
  // 1097:   write "
  // 1098:     @
  // 1099:       use_polymorphic_function(@(namespace), @quot;@(basename)", @
  // 1100:     &get__@(name), &poly_idx__@(name));
  frame->slots[5] /* temp__2 */ = create_closure(entry__compiler__sim2c_873, 0);
  // 1101: ... :
  // 1102:   write "
  // 1103:     @
  // 1104:       use_read_only(@(namespace), @quot;@(basename)", &get__@(name), @
  // 1105:     &get_value_or_future__@(name));
  frame->slots[6] /* temp__3 */ = create_closure(entry__compiler__sim2c_879, 0);
  // 1106: ... :
  // 1107:   write "
  // 1108:     @
  // 1109:       use_read_write(@(namespace), @quot;@(basename)", &get__@(name), @
  // 1110:     &set__@(name));
  frame->slots[7] /* temp__4 */ = create_closure(entry__compiler__sim2c_883, 0);
  // 1111: ... :
  // 1112:   write "
  // 1113:     @
  // 1114:       use_single_assign_dynamic(@(namespace), @quot;@(basename)", @
  // 1115:     &get__@(name), &define__@(name));
  frame->slots[8] /* temp__5 */ = create_closure(entry__compiler__sim2c_887, 0);
  // 1116: ... :
  // 1117:   write "
  // 1118:     @
  // 1119:       use_multi_assign_dynamic(@(namespace), @quot;@(basename)", @
  // 1120:     &get__@(name), &set__@(name), &define__@(name));
  frame->slots[9] /* temp__6 */ = create_closure(entry__compiler__sim2c_891, 0);
  // 1095: case variable_kind_of(info)
  // 1096:   POLYMORPHIC:
  // 1097:     write "
  // 1098:       @
  // 1099:         use_polymorphic_function(@(namespace), @quot;@(basename)", @
  // 1100:       &get__@(name), &poly_idx__@(name));
  // 1101:   STATIC_SINGLE:
  // 1102:     write "
  // 1103:       @
  // 1104:         use_read_only(@(namespace), @quot;@(basename)", &get__@(name), @
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
static void entry__compiler__sim2c_860(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // name: 0
  // info: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 1087: ... global_names(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__global_names();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_861;
}
static void cont__compiler__sim2c_861(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 1087: ... global_names(name).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_862;
}
static void cont__compiler__sim2c_862(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1087: ... :
  // 1088:   $namespace
  // 1089:     if
  // 1090:       name .contains. "__"
  // 1091:       -> string('@quot;' name .before. "__" '@quot;')
  // 1092:       -> "NULL"
  // 1093:   
  // 1094:   $basename name .truncate_until. "__"
  // 1095:   case variable_kind_of(info)
  // 1096:     POLYMORPHIC:
  // ...
  frame->slots[4] /* temp__3 */ = create_closure(entry__compiler__sim2c_863, 0);
  // 1087: unless global_names(name).is_defined:
  // 1088:   $namespace
  // 1089:     if
  // 1090:       name .contains. "__"
  // 1091:       -> string('@quot;' name .before. "__" '@quot;')
  // 1092:       -> "NULL"
  // 1093:   
  // 1094:   $basename name .truncate_until. "__"
  // 1095:   case variable_kind_of(info)
  // 1096:     POLYMORPHIC:
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
static void cont__compiler__sim2c_894(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1121: write generated_phase_4
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[24])->contents /* generated_phase_4 */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_895;
}
static void cont__compiler__sim2c_895(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1122: if is_main:
  // 1123:   write "
  // 1124:     @
  // 1125:       resolve_attributes();
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* is_main */;
  arguments->slots[1] = func__compiler__sim2c_896;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_898;
}
static void entry__compiler__sim2c_896(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1123: write "
  // 1124:   @
  // 1125:     resolve_attributes();
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__29050caaed294603;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_898(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1126: if
  // 1127:   is_main:
  // 1128:     write "
  // 1129:       
  // 1130:         // initialization phase 5
  // 1131:       @;
  // 1132:   :
  // 1133:     write "
  // 1134:       }
  // 1135:       
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* is_main */;
  arguments->slots[1] = func__compiler__sim2c_899;
  arguments->slots[2] = func__compiler__sim2c_901;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_905;
}
static void entry__compiler__sim2c_899(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1128: write "
  // 1129:   
  // 1130:     // initialization phase 5
  // 1131:   @;
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__a9896ddd6eafadae;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_901(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1133: ... "
  // 1134:   }
  // 1135:   
  // 1136:   static int already_run_phase_5 = false;
  // 1137:   
  // 1138:   EXPORT void phase_5__@(module_name)(void) {
  // 1139:     if (already_run_phase_5) return;
  // 1140:     already_run_phase_5 = true;
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__b9a3b16bf1dfe8ab;
  arguments->slots[1] = get__module_name();
  arguments->slots[2] = string__d3e0f1a7b944caae;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_904;
}
static void cont__compiler__sim2c_904(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1133: write "
  // 1134:   }
  // 1135:   
  // 1136:   static int already_run_phase_5 = false;
  // 1137:   
  // 1138:   EXPORT void phase_5__@(module_name)(void) {
  // 1139:     if (already_run_phase_5) return;
  // 1140:     already_run_phase_5 = true;
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_905(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1141: ... : (name _info)
  // 1142:   writeln "  phase_5__@(mangle_filename(name))();"
  frame->slots[34] /* temp__1 */ = create_closure(entry__compiler__sim2c_906, 2);
  // 1141: for_each required_modules: (name _info)
  // 1142:   writeln "  phase_5__@(mangle_filename(name))();"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__required_modules();
  arguments->slots[1] = frame->slots[34] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_910;
}
static void entry__compiler__sim2c_906(void) {
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
  // 1142: ... mangle_filename(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = frame->slots[2] /* mangle_filename */;
  func = myself->type;
  frame->cont = cont__compiler__sim2c_907;
}
static void cont__compiler__sim2c_907(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 1142: ... "  phase_5__@(mangle_filename(name))();"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__fedb24123ef1fa6f;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = string__fa732415f616bf7;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_909;
}
static void cont__compiler__sim2c_909(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1142: writeln "  phase_5__@(mangle_filename(name))();"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_910(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1143: write generated_phase_5
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[25])->contents /* generated_phase_5 */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_911;
}
static void cont__compiler__sim2c_911(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1144: if
  // 1145:   is_main:
  // 1146:     write "
  // 1147:         initialize_function_attributes();
  // 1148:       
  // 1149:         // initialization phase 6
  // 1150:       @;
  // 1151:   :
  // 1152:     write "
  // 1153:       }
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* is_main */;
  arguments->slots[1] = func__compiler__sim2c_912;
  arguments->slots[2] = func__compiler__sim2c_914;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_918;
}
static void entry__compiler__sim2c_912(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1146: write "
  // 1147:     initialize_function_attributes();
  // 1148:   
  // 1149:     // initialization phase 6
  // 1150:   @;
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__1cd8a7b21f5517c3;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_914(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1152: ... "
  // 1153:   }
  // 1154:   
  // 1155:   static int already_run_phase_6 = false;
  // 1156:   
  // 1157:   EXPORT void phase_6__@(module_name)(void) {
  // 1158:     if (already_run_phase_6) return;
  // 1159:     already_run_phase_6 = true;
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__b9a3b1a8f1dfe8ab;
  arguments->slots[1] = get__module_name();
  arguments->slots[2] = string__d0e0e9a7b944caae;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_917;
}
static void cont__compiler__sim2c_917(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1152: write "
  // 1153:   }
  // 1154:   
  // 1155:   static int already_run_phase_6 = false;
  // 1156:   
  // 1157:   EXPORT void phase_6__@(module_name)(void) {
  // 1158:     if (already_run_phase_6) return;
  // 1159:     already_run_phase_6 = true;
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_918(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1160: ... : (name _info)
  // 1161:   writeln "  phase_6__@(mangle_filename(name))();"
  frame->slots[34] /* temp__1 */ = create_closure(entry__compiler__sim2c_919, 2);
  // 1160: for_each required_modules: (name _info)
  // 1161:   writeln "  phase_6__@(mangle_filename(name))();"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__required_modules();
  arguments->slots[1] = frame->slots[34] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_923;
}
static void entry__compiler__sim2c_919(void) {
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
  // 1161: ... mangle_filename(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = frame->slots[2] /* mangle_filename */;
  func = myself->type;
  frame->cont = cont__compiler__sim2c_920;
}
static void cont__compiler__sim2c_920(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 1161: ... "  phase_6__@(mangle_filename(name))();"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__fedb24d23ef1fa6f;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = string__fa732415f616bf7;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_922;
}
static void cont__compiler__sim2c_922(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1161: writeln "  phase_6__@(mangle_filename(name))();"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_923(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1162: write generated_phase_6
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[26])->contents /* generated_phase_6 */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_924;
}
static void cont__compiler__sim2c_924(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1163: ... "  register_collector(collect__@(module_name));"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__476ac52a7f81f4a0;
  arguments->slots[1] = get__module_name();
  arguments->slots[2] = string__2d7981f4e6402bfe;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_926;
}
static void cont__compiler__sim2c_926(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[34] /* temp__1 */ = arguments->slots[0];
  // 1163: writeln "  register_collector(collect__@(module_name));"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[34] /* temp__1 */;
  result_count = 0;
  myself = get__writeln();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_927;
}
static void cont__compiler__sim2c_927(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1164: if is_main:
  // 1165:   write "
  // 1166:     @
  // 1167:       execute(main_entry);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* is_main */;
  arguments->slots[1] = func__compiler__sim2c_928;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_930;
}
static void entry__compiler__sim2c_928(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1165: write "
  // 1166:   @
  // 1167:     execute(main_entry);
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__3734ffa0d2ae2d12;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_930(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1168: write "}@nl;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e4e02bcf;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_931;
}
static void cont__compiler__sim2c_931(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1169: ... : write_timing_info "generating" filenames(1)
  frame->slots[34] /* temp__1 */ = create_closure(entry__compiler__sim2c_932, 0);
  // 1169: if do_time_passes: write_timing_info "generating" filenames(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = frame->slots[34] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_935;
}
static void entry__compiler__sim2c_932(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // filenames: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* filenames */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1169: ... filenames(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* filenames */;
  func = myself->type;
  frame->cont = cont__compiler__sim2c_933;
}
static void cont__compiler__sim2c_933(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1169: ... write_timing_info "generating" filenames(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__1d702a52a35b6426;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write_timing_info();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_935(void) {
  myself = frame->slots[2] /* return__10 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
EXPORT void collect__sim2c(void) {
  var.compiler__print_source = collect_node(var.compiler__print_source);
  var.compiler__eprint_source = collect_node(var.compiler__eprint_source);
  var.compiler__privileged_polymorphic_functions = collect_node(var.compiler__privileged_polymorphic_functions);
  var.compiler__generate_dispatcher_function = collect_node(var.compiler__generate_dispatcher_function);
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
  func__compiler__print_source = create_function(entry__compiler__print_source, 1);
  func__compiler__eprint_source_4 = create_function(entry__compiler__eprint_source_4, 0);
  func__compiler__eprint_source_5 = create_function(entry__compiler__eprint_source_5, 0);
  func__compiler__eprint_source_6 = create_function(entry__compiler__eprint_source_6, 0);
  func__compiler__eprint_source_2 = create_function(entry__compiler__eprint_source_2, 1);
  func__compiler__eprint_source = create_function(entry__compiler__eprint_source, 1);
  string__7fb24a3fca4aa852 = from_latin_1_string("static void type__", 18);
  string__66ccbf91860d092a = from_latin_1_string("(void);\012", 8);
  string__949b16e1d9f7528 = from_latin_1_string(
    "(void) {\n"
    "  if (argument_count < 1) {\n"
    "    too_few_arguments_error();\n"
    "    return;\n"
    "  }\n",
    84);
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
  func__compiler__generate_dispatcher_function = create_function(entry__compiler__generate_dispatcher_function, 1);
  string__2d7981f4e5f02b9a = from_latin_1_string("__", 2);
  string__2d7981f4e6d82bff = from_latin_1_string("::", 2);
  func__demangled = create_function(entry__demangled, 1);
  string__94b9534b986c24a9 = from_latin_1_string("The symbol \042", 12);
  string__634c61c70382d128 = from_latin_1_string("\042 is used as a polymorphic function and cannot be used otherwise!", 65);
  string__67c02c7b1bf18880 = from_latin_1_string("\042 is used as a polymorphic function and id assigned to!", 55);
  string__f8ba3c062f1b8631 = from_latin_1_string("\042 is used as a single-assign dynamic and is assigned to!", 56);
  string__aafcf41c458e8f41 = from_latin_1_string("\042 is used as a polymorphic function and as a single-assign dynamic!", 67);
  string__80670d894d05691d = from_latin_1_string("\042 is used as a single-assign dynamic and as a multi-assign dynamic!", 67);
  string__a09d645d506640e9 = from_latin_1_string("\042 is used as a polymorphic function and as a multi-assign dynamic!", 66);
  func__compiler__update_info = create_function(entry__compiler__update_info, 3);
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
  func__compiler__sim2c_129 = create_function(entry__compiler__sim2c_129, 1);
  string__66f024ec077397c2 = from_latin_1_string("expanding", 9);
  string__1d581a51a85b6426 = from_latin_1_string("annotating", 10);
  func__compiler__sim2c_145 = create_function(entry__compiler__sim2c_145, 0);
  func__compiler__sim2c_146 = create_function(entry__compiler__sim2c_146, 0);
  string__c3e1e344d34946eb = from_latin_1_string("basic/stdlib", 12);
  string__b567219b137172d = from_latin_1_string("system/stdlib", 13);
  func__compiler__sim2c_151 = create_function(entry__compiler__sim2c_151, 0);
  string__a23c0f9515cb809d = from_latin_1_string("nothing", 7);
  string__fa724815d896ba8 = from_latin_1_string("std", 3);
  func__compiler__sim2c_160 = create_function(entry__compiler__sim2c_160, 0);
  string__b18861f6a8c886ba = from_latin_1_string("An identifier named \042", 21);
  string__95b7f6cc14260ab8 = from_latin_1_string("\042 was already defined", 21);
  string__69658745890c070 = from_latin_1_string("The definition of \042", 19);
  string__c419bd2045fe53aa = from_latin_1_string("\042 clashes with the already defined identifier \042", 47);
  string__578a5af303e9cc3 = from_latin_1_string("\042", 1);
  string__b5bb4d11daae5f7a = from_latin_1_string("\042 clashes with the definition of \042", 34);
  string__6de219341b32224c = from_latin_1_string("\042 because both namespaces are used", 34);
  string__5ab424ea8372e502 = from_latin_1_string("analyzing", 9);
  func__compiler__sim2c_246 = create_function(entry__compiler__sim2c_246, 1);
  func__compiler__sim2c_251 = create_function(entry__compiler__sim2c_251, 1);
  func__compiler__sim2c_279 = create_function(entry__compiler__sim2c_279, 1);
  func__compiler__sim2c_310 = create_function(entry__compiler__sim2c_310, 1);
  func__compiler__sim2c_309 = create_function(entry__compiler__sim2c_309, 1);
  string__72ed7b1f2279c943 = from_latin_1_string("simplifying", 11);
  string__7c84ae5484fdf7e0 = from_latin_1_string("_define ", 8);
  func__compiler__sim2c_318 = create_function(entry__compiler__sim2c_318, 1);
  func__compiler__sim2c_317 = create_function(entry__compiler__sim2c_317, 1);
  func__compiler__sim2c_327 = create_function(entry__compiler__sim2c_327, 1);
  string__7690af9104a5e1e7 = from_latin_1_string("mangling", 8);
  string__405aee03eb306008 = from_latin_1_string("get__", 5);
  string__c44673b4643f1172 = from_latin_1_string("GENERATE DEFINITIONS", 20);
  func__compiler__sim2c_498 = create_function(entry__compiler__sim2c_498, 0);
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
  func__compiler__sim2c_549 = create_function(entry__compiler__sim2c_549, 1);
  func__compiler__sim2c_553 = create_function(entry__compiler__sim2c_553, 0);
  string__5c9d8231ad282235 = from_latin_1_string(
    "  terminate(0); // should never be reached\n"
    "}\n",
    45);
  func__compiler__sim2c_562 = create_function(entry__compiler__sim2c_562, 0);
  string__a61426acc3f10dab = from_latin_1_string(
    "  frame = frame->caller_frame;\n"
    "  func = frame->cont;\n"
    "  frame->cont = invalid_continuation;\n"
    "}\n",
    93);
  func__compiler__sim2c_564 = create_function(entry__compiler__sim2c_564, 0);
  func__compiler__sim2c_574 = create_function(entry__compiler__sim2c_574, 1);
  func__compiler__sim2c_573 = create_function(entry__compiler__sim2c_573, 1);
  string__58cb04c59ab3549a = from_latin_1_string("/// require ", 12);
  func__compiler__sim2c_576 = create_function(entry__compiler__sim2c_576, 2);
  string__7d8c250ccd5bbd65 = from_latin_1_string("/// link ", 9);
  func__compiler__sim2c_580 = create_function(entry__compiler__sim2c_580, 1);
  string__6d8c238ccd0b3d65 = from_latin_1_string("/// data ", 9);
  func__compiler__sim2c_584 = create_function(entry__compiler__sim2c_584, 1);
  string__3ae3b0d72c49c8db = from_latin_1_string("runtime/platform.h", 18);
  string__72c4a8d406a50228 = from_latin_1_string("stdint.h", 8);
  string__7cc4ad5406a55228 = from_latin_1_string("stdlib.h", 8);
  func__compiler__sim2c_592 = create_function(entry__compiler__sim2c_592, 0);
  string__3d6a095dad2a247d = from_latin_1_string("#include <", 10);
  string__578a5af303e9cdf = from_latin_1_string(">", 1);
  func__compiler__sim2c_598 = create_function(entry__compiler__sim2c_598, 1);
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
  func__compiler__sim2c_608 = create_function(entry__compiler__sim2c_608, 0);
  string__64c4ac5406a5d228 = from_latin_1_string("stddef.h", 8);
  func__compiler__sim2c_612 = create_function(entry__compiler__sim2c_612, 0);
  string__b0f44c3748f83ed0 = from_latin_1_string("typedef __SIZE_TYPE__ size_t;\012", 30);
  func__compiler__sim2c_616 = create_function(entry__compiler__sim2c_616, 0);
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
  func__compiler__sim2c_621 = create_function(entry__compiler__sim2c_621, 2);
  string__ff4edce8b0a2fa27 = from_latin_1_string("static struct {\012", 16);
  string__b07009729763a0f0 = from_latin_1_string("} var;\012", 7);
  string__75573d7e471fdc32 = from_latin_1_string("static const char *var_names[] = {\012", 35);
  string__fa727015ff16bc6 = from_latin_1_string("};\012", 3);
  string__c3452dad239e6464 = from_latin_1_string("static void main_entry(void);", 29);
  func__compiler__sim2c_667 = create_function(entry__compiler__sim2c_667, 0);
  string__1f74a3bba8d254fe = from_latin_1_string("void run__", 10);
  string__a1240cd997f230c1 = from_latin_1_string("(void);", 7);
  func__compiler__sim2c_669 = create_function(entry__compiler__sim2c_669, 0);
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
  func__compiler__sim2c_688 = create_function(entry__compiler__sim2c_688, 2);
  func__compiler__sim2c_687 = create_function(entry__compiler__sim2c_687, 0);
  string__cb6a78473f66a6a1 = from_latin_1_string("static NODE *", 13);
  func__compiler__sim2c_697 = create_function(entry__compiler__sim2c_697, 2);
  string__44a800d7e66fda5b = from_latin_1_string(
    "\n"
    "static const char *used_namespaces[] = {\n",
    42);
  string__fa730415f296bee = from_latin_1_string("  \042", 3);
  string__fa730c15f496bc6 = from_latin_1_string("\042,\012", 3);
  func__compiler__sim2c_703 = create_function(entry__compiler__sim2c_703, 1);
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
  func__compiler__sim2c_720 = create_function(entry__compiler__sim2c_720, 0);
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
  string__fc8c36a84adb366f = from_latin_1_string("(void) {\012", 9);
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
  func__compiler__sim2c_746 = create_function(entry__compiler__sim2c_746, 0);
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
  func__compiler__sim2c_748 = create_function(entry__compiler__sim2c_748, 0);
  string__fedb25123ef1fa6f = from_latin_1_string("  phase_1__", 11);
  string__fa732415f616bf7 = from_latin_1_string("();", 3);
  string__6759f0f7c95235d = from_latin_1_string("  register_module_info(&module_info);\012", 38);
  string__d93952e55b2e5d9 = from_latin_1_string("  define_namespace(\042", 20);
  string__860afb0b5fb87d33 = from_latin_1_string("\042);\012", 4);
  func__compiler__sim2c_761 = create_function(entry__compiler__sim2c_761, 1);
  string__f5b495312d83add5 = from_latin_1_string(
    "\n"
    "  // initialization phase 2\n",
    29);
  func__compiler__sim2c_767 = create_function(entry__compiler__sim2c_767, 0);
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
  func__compiler__sim2c_769 = create_function(entry__compiler__sim2c_769, 0);
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
  func__compiler__sim2c_782 = create_function(entry__compiler__sim2c_782, 2);
  string__cb22ed554b280fb1 = from_latin_1_string(
    "\n"
    "  // initialization phase 3\n"
    "\n"
    "  initialize_phase_3();\n"
    "  resolve_symbols();\n",
    75);
  func__compiler__sim2c_830 = create_function(entry__compiler__sim2c_830, 0);
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
  func__compiler__sim2c_832 = create_function(entry__compiler__sim2c_832, 0);
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
  func__compiler__sim2c_846 = create_function(entry__compiler__sim2c_846, 0);
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
  func__compiler__sim2c_848 = create_function(entry__compiler__sim2c_848, 0);
  string__fedb24523ef1fa6f = from_latin_1_string("  phase_4__", 11);
  string__5e0ae40b5c007d75 = from_latin_1_string("NULL", 4);
  func__compiler__sim2c_868 = create_function(entry__compiler__sim2c_868, 0);
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
  func__compiler__sim2c_860 = create_function(entry__compiler__sim2c_860, 2);
  string__29050caaed294603 = from_latin_1_string("  resolve_attributes();\012", 24);
  func__compiler__sim2c_896 = create_function(entry__compiler__sim2c_896, 0);
  string__a9896ddd6eafadae = from_latin_1_string(
    "\n"
    "  // initialization phase 5\n"
    "\n",
    30);
  func__compiler__sim2c_899 = create_function(entry__compiler__sim2c_899, 0);
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
  func__compiler__sim2c_901 = create_function(entry__compiler__sim2c_901, 0);
  string__fedb24123ef1fa6f = from_latin_1_string("  phase_5__", 11);
  string__1cd8a7b21f5517c3 = from_latin_1_string(
    "  initialize_function_attributes();\n"
    "\n"
    "  // initialization phase 6\n"
    "\n",
    66);
  func__compiler__sim2c_912 = create_function(entry__compiler__sim2c_912, 0);
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
  func__compiler__sim2c_914 = create_function(entry__compiler__sim2c_914, 0);
  string__fedb24d23ef1fa6f = from_latin_1_string("  phase_6__", 11);
  string__476ac52a7f81f4a0 = from_latin_1_string("  register_collector(collect__", 30);
  string__3734ffa0d2ae2d12 = from_latin_1_string("  execute(main_entry);\012", 23);
  func__compiler__sim2c_928 = create_function(entry__compiler__sim2c_928, 0);
  string__1d702a52a35b6426 = from_latin_1_string("generating", 10);
  func__compiler__sim2c = create_function(entry__compiler__sim2c, -1);
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
  var.compiler__print_source = create_future();
  define_single_assign_static("compiler", "print_source", get__compiler__print_source, &var.compiler__print_source);
  var.compiler__eprint_source = create_future();
  define_single_assign_static("compiler", "eprint_source", get__compiler__eprint_source, &var.compiler__eprint_source);
  define_single_assign_static("compiler", "privileged_polymorphic_functions", get__compiler__privileged_polymorphic_functions, &var.compiler__privileged_polymorphic_functions);
  var.compiler__generate_dispatcher_function = create_future();
  define_single_assign_static("compiler", "generate_dispatcher_function", get__compiler__generate_dispatcher_function, &var.compiler__generate_dispatcher_function);
  var.compiler__update_info = create_future();
  define_single_assign_static("compiler", "update_info", get__compiler__update_info, &var.compiler__update_info);
  var.compiler__sim2c = create_future();
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
  use_read_only(NULL, "NONE", &get__NONE, &get_value_or_future__NONE);
  use_read_only(NULL, "POLYMORPHIC", &get__POLYMORPHIC, &get_value_or_future__POLYMORPHIC);
  use_read_only(NULL, "STATIC_MULTI", &get__STATIC_MULTI, &get_value_or_future__STATIC_MULTI);
  use_read_only(NULL, "STATIC_SINGLE", &get__STATIC_SINGLE, &get_value_or_future__STATIC_SINGLE);
  use_read_only(NULL, "SyntaxError", &get__SyntaxError, &get_value_or_future__SyntaxError);
  use_read_write(NULL, "actions", &get__actions, &set__actions);
  use_single_assign_dynamic(NULL, "already_defined_names", &get__already_defined_names, &define__already_defined_names);
  use_read_only(NULL, "alt", &get__alt, &get_value_or_future__alt);
  use_read_only(NULL, "annotate_statement", &get__annotate_statement, &get_value_or_future__annotate_statement);
  use_read_only(NULL, "append", &get__append, &get_value_or_future__append);
  use_polymorphic_function(NULL, "arguments_of", &get__arguments_of, &poly_idx__arguments_of);
  use_read_only(NULL, "assignment", &get__assignment, &get_value_or_future__assignment);
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
  use_multi_assign_dynamic("compiler", "unique_item_index", &get__compiler__unique_item_index, &set__compiler__unique_item_index, &define__compiler__unique_item_index);
  use_single_assign_dynamic("compiler", "use_identifier", &get__compiler__use_identifier, &define__compiler__use_identifier);
  use_multi_assign_dynamic("compiler", "use_inline_c", &get__compiler__use_inline_c, &set__compiler__use_inline_c, &define__compiler__use_inline_c);
  use_single_assign_dynamic("compiler", "use_literal", &get__compiler__use_literal, &define__compiler__use_literal);
  use_multi_assign_dynamic("compiler", "used_names", &get__compiler__used_names, &set__compiler__used_names, &define__compiler__used_names);
  use_multi_assign_dynamic("compiler", "used_namespaces", &get__compiler__used_namespaces, &set__compiler__used_namespaces, &define__compiler__used_namespaces);
  use_multi_assign_dynamic("compiler", "used_unique_items", &get__compiler__used_unique_items, &set__compiler__used_unique_items, &define__compiler__used_unique_items);
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
  use_read_only(NULL, "ignore", &get__ignore, &get_value_or_future__ignore);
  use_read_write(NULL, "included_files", &get__included_files, &set__included_files);
  use_read_only(NULL, "indent_marker", &get__indent_marker, &get_value_or_future__indent_marker);
  use_read_only(NULL, "is_a_body", &get__is_a_body, &get_value_or_future__is_a_body);
  use_read_only(NULL, "is_a_c_body", &get__is_a_c_body, &get_value_or_future__is_a_c_body);
  use_read_only(NULL, "is_a_character_literal", &get__is_a_character_literal, &get_value_or_future__is_a_character_literal);
  use_read_only(NULL, "is_a_constant", &get__is_a_constant, &get_value_or_future__is_a_constant);
  use_read_only(NULL, "is_a_key_value_pair", &get__is_a_key_value_pair, &get_value_or_future__is_a_key_value_pair);
  use_read_only(NULL, "is_a_meta_instruction", &get__is_a_meta_instruction, &get_value_or_future__is_a_meta_instruction);
  use_read_only(NULL, "is_a_numeric_literal", &get__is_a_numeric_literal, &get_value_or_future__is_a_numeric_literal);
  use_read_only(NULL, "is_a_polymorphic_function_constant", &get__is_a_polymorphic_function_constant, &get_value_or_future__is_a_polymorphic_function_constant);
  use_polymorphic_function(NULL, "is_a_reference", &get__is_a_reference, &poly_idx__is_a_reference);
  use_read_only(NULL, "is_a_remark", &get__is_a_remark, &get_value_or_future__is_a_remark);
  use_read_only(NULL, "is_a_setter", &get__is_a_setter, &get_value_or_future__is_a_setter);
  use_read_only(NULL, "is_a_static_single_definition", &get__is_a_static_single_definition, &get_value_or_future__is_a_static_single_definition);
  use_read_only(NULL, "is_an_assignment", &get__is_an_assignment, &get_value_or_future__is_an_assignment);
  use_read_only(NULL, "is_c_code", &get__is_c_code, &get_value_or_future__is_c_code);
  use_read_only(NULL, "is_defined", &get__is_defined, &get_value_or_future__is_defined);
  use_read_only(NULL, "is_empty", &get__is_empty, &get_value_or_future__is_empty);
  use_read_only(NULL, "is_undefined", &get__is_undefined, &get_value_or_future__is_undefined);
  use_read_only(NULL, "key_of", &get__key_of, &get_value_or_future__key_of);
  use_read_only(NULL, "length_of", &get__length_of, &get_value_or_future__length_of);
  use_read_only(NULL, "linked_libraries", &get__linked_libraries, &get_value_or_future__linked_libraries);
  use_read_only(NULL, "list", &get__list, &get_value_or_future__list);
  use_read_only(NULL, "load", &get__load, &get_value_or_future__load);
  use_read_only(NULL, "mangled_name_of", &get__mangled_name_of, &get_value_or_future__mangled_name_of);
  use_read_only(NULL, "module_name", &get__module_name, &get_value_or_future__module_name);
  use_read_only(NULL, "name_of", &get__name_of, &get_value_or_future__name_of);
  use_multi_assign_dynamic(NULL, "named_constants", &get__named_constants, &set__named_constants, &define__named_constants);
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
  use_read_only(NULL, "to_c", &get__to_c, &get_value_or_future__to_c);
  use_read_only(NULL, "to_integer", &get__to_integer, &get_value_or_future__to_integer);
  use_read_only(NULL, "to_lower_case", &get__to_lower_case, &get_value_or_future__to_lower_case);
  use_read_only(NULL, "to_string", &get__to_string, &get_value_or_future__to_string);
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
  initialize_future(var.compiler__print_source, func__compiler__print_source);
  initialize_future(var.compiler__eprint_source, func__compiler__eprint_source);
  initialize_future(var.compiler__generate_dispatcher_function, func__compiler__generate_dispatcher_function);
  initialize_future(var.compiler__update_info, func__compiler__update_info);
  initialize_future(var.compiler__sim2c, func__compiler__sim2c);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__sim2c(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__sim2c);
}
