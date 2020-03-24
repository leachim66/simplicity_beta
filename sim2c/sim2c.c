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
IMPORT int main_argc;
IMPORT char **main_argv;
IMPORT void initialize_runtime(void);
IMPORT void register_module_info(MODULE_INFO *info);
IMPORT NODE *from_double(double val);
IMPORT NODE *from_uchar32(unsigned int chr);
IMPORT NODE *from_uint64(uint64_t val);
IMPORT NODE *from_uint32(uint32_t val);
IMPORT NODE *from_digit_string(const char *str);
IMPORT void initialize_phase_3(void);
IMPORT void resolve_symbols(void);
IMPORT void set_module(const char *name);
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
IMPORT NODE *create_function(FUNC func, int par_count);
IMPORT NODE *from_latin_1_string(const char *str, long len);
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
#define IS_OLD(addr) false
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
static NODE_GETTER get__sim2c__write_to_phase_6;
static NODE_SETTER define__sim2c__write_to_phase_6;
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
static FRAME_INFO frame__7_1 = {33, {"filenames", "is_main", "return__9", "mangle_filename", "fragments", "trees", "all_defined_names", "all_used_names", "all_actions", "top_level_names", "all_definitions", "all_statements", "max_temp_idx", "need", "generated_declarations", "generated_top_level_variable_names", "generated_top_level_variable_declarations", "generated_global_variable_declarations", "generated_continuation_table", "generated_delayed_continuation_table", "generated_functions", "generated_phase_1", "generated_phase_2", "generated_phase_3", "generated_phase_4", "generated_phase_5", "generated_phase_6", "generated_code", "generated_collections", "delayed_statements", "used_literals", "def_count", "depth"}};
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
static FRAME_INFO frame__7_373 = {3, {"args", "generated_phase_6", "txt"}};
static void cont__7_374(void);
static NODE *func__7_375;
static void entry__7_375(void);
static FRAME_INFO frame__7_375 = {2, {"generated_phase_6", "txt"}};
static void cont__7_376(void);
static void cont__7_377(void);
static NODE *func__7_378;
static void entry__7_378(void);
static FRAME_INFO frame__7_378 = {3, {"name", "literal", "used_literals"}};
static NODE *func__7_379;
static void entry__7_379(void);
static FRAME_INFO frame__7_379 = {3, {"used_literals", "name", "literal"}};
static void cont__7_380(void);
static void cont__7_381(void);
static NODE *func__7_382;
static void entry__7_382(void);
static FRAME_INFO frame__7_382 = {3, {"args", "generated_collections", "txt"}};
static void cont__7_383(void);
static NODE *func__7_384;
static void entry__7_384(void);
static FRAME_INFO frame__7_384 = {2, {"generated_collections", "txt"}};
static void cont__7_385(void);
static void cont__7_386(void);
static NODE *func__7_387;
static void entry__7_387(void);
static FRAME_INFO frame__7_387 = {3, {"args", "delayed_statements", "txt"}};
static void cont__7_388(void);
static NODE *func__7_389;
static void entry__7_389(void);
static FRAME_INFO frame__7_389 = {2, {"delayed_statements", "txt"}};
static void cont__7_390(void);
static void cont__7_391(void);
static NODE *func__7_392;
static void entry__7_392(void);
static FRAME_INFO frame__7_392 = {2, {"ident", "need"}};
static NODE *string__7_393;
static void cont__7_394(void);
static NODE *func__7_395;
static void entry__7_395(void);
static FRAME_INFO frame__7_395 = {3, {"ident", "need", "name"}};
static void cont__7_396(void);
static void cont__7_397(void);
static NODE *string__7_398;
static void cont__7_399(void);
static NODE *func__7_400;
static void entry__7_400(void);
static FRAME_INFO frame__7_400 = {6, {"stmt_idx", "defs", "return__5", "generated_code", "all_actions", "code"}};
static NODE *string__7_401;
static void cont__7_402(void);
static NODE *func__7_403;
static void entry__7_403(void);
static FRAME_INFO frame__7_403 = {1, {"defs"}};
static NODE *func__7_404;
static void entry__7_404(void);
static FRAME_INFO frame__7_404 = {2, {"definition", "source"}};
static void cont__7_405(void);
static NODE *func__7_406;
static void entry__7_406(void);
static FRAME_INFO frame__7_406 = {2, {"source", "definition"}};
static void cont__7_407(void);
static void cont__7_408(void);
static void cont__7_409(void);
static void cont__7_410(void);
static NODE *func__7_411;
static void entry__7_411(void);
static FRAME_INFO frame__7_411 = {1, {"definition"}};
static NODE *func__7_412;
static void entry__7_412(void);
static FRAME_INFO frame__7_412 = {2, {"source", "definition"}};
static void cont__7_413(void);
static NODE *func__7_414;
static void entry__7_414(void);
static FRAME_INFO frame__7_414 = {1, {"source"}};
static void cont__7_415(void);
static void cont__7_416(void);
static NODE *func__7_417;
static void entry__7_417(void);
static FRAME_INFO frame__7_417 = {2, {"definition", "source"}};
static void cont__7_418(void);
static NODE *func__7_419;
static void entry__7_419(void);
static FRAME_INFO frame__7_419 = {2, {"definition", "source"}};
static void cont__7_420(void);
static NODE *func__7_421;
static void entry__7_421(void);
static FRAME_INFO frame__7_421 = {2, {"definition", "source"}};
static NODE *func__7_422;
static void entry__7_422(void);
static FRAME_INFO frame__7_422 = {2, {"definition", "source"}};
static void cont__7_423(void);
static void cont__7_424(void);
static NODE *func__7_425;
static void entry__7_425(void);
static FRAME_INFO frame__7_425 = {2, {"definition", "source"}};
static NODE *func__7_426;
static void entry__7_426(void);
static FRAME_INFO frame__7_426 = {2, {"definition", "source"}};
static NODE *func__7_427;
static void entry__7_427(void);
static FRAME_INFO frame__7_427 = {2, {"definition", "source"}};
static void cont__7_428(void);
static void cont__7_429(void);
static void cont__7_430(void);
static NODE *func__7_431;
static void entry__7_431(void);
static FRAME_INFO frame__7_431 = {0, {}};
static void cont__7_432(void);
static NODE *func__7_433;
static void entry__7_433(void);
static FRAME_INFO frame__7_433 = {2, {"generated_code", "code"}};
static void cont__7_434(void);
static void cont__7_435(void);
static void cont__7_436(void);
static void cont__7_437(void);
static NODE *string__7_438;
static void cont__7_439(void);
static NODE *func__7_440;
static void entry__7_440(void);
static FRAME_INFO frame__7_440 = {7, {"return__6", "is_main", "max_temp_idx", "mangle_filename", "generated_code", "all_actions", "code"}};
static NODE *func__7_441;
static void entry__7_441(void);
static FRAME_INFO frame__7_441 = {3, {"is_main", "max_temp_idx", "mangle_filename"}};
static NODE *func__7_442;
static void entry__7_442(void);
static FRAME_INFO frame__7_442 = {1, {"max_temp_idx"}};
static NODE *string__7_443;
static void cont__7_444(void);
static void cont__7_445(void);
static NODE *func__7_446;
static void entry__7_446(void);
static FRAME_INFO frame__7_446 = {1, {"max_temp_idx"}};
static NODE *string__7_447;
static NODE *string__7_448;
static void cont__7_449(void);
static NODE *func__7_450;
static void entry__7_450(void);
static FRAME_INFO frame__7_450 = {1, {"max_temp_idx"}};
static NODE *string__7_451;
static NODE *string__7_452;
static void cont__7_453(void);
static void cont__7_454(void);
static NODE *string__7_455;
static NODE *string__7_456;
static NODE *string__7_457;
static void cont__7_458(void);
static void cont__7_459(void);
static NODE *func__7_460;
static void entry__7_460(void);
static FRAME_INFO frame__7_460 = {4, {"name", "info", "mangle_filename", "continuation"}};
static void cont__7_461(void);
static void cont__7_462(void);
static void cont__7_463(void);
static NODE *string__7_464;
static NODE *string__7_465;
static NODE *string__7_466;
static void cont__7_467(void);
static void cont__7_468(void);
static void cont__7_469(void);
static NODE *string__7_470;
static void cont__7_471(void);
static void cont__7_472(void);
static NODE *func__7_473;
static void entry__7_473(void);
static FRAME_INFO frame__7_473 = {2, {"generated_code", "code"}};
static void cont__7_474(void);
static void cont__7_475(void);
static void cont__7_476(void);
static void cont__7_477(void);
static void cont__7_478(void);
static NODE *func__7_479;
static void entry__7_479(void);
static FRAME_INFO frame__7_479 = {7, {"stmt_idx", "stmts", "return__7", "def_count", "generated_code", "all_actions", "code"}};
static void cont__7_480(void);
static NODE *string__7_481;
static void cont__7_482(void);
static NODE *func__7_483;
static void entry__7_483(void);
static FRAME_INFO frame__7_483 = {1, {"stmts"}};
static NODE *func__7_484;
static void entry__7_484(void);
static FRAME_INFO frame__7_484 = {1, {"stmt"}};
static void cont__7_485(void);
static void cont__7_486(void);
static void cont__7_487(void);
static NODE *func__7_488;
static void entry__7_488(void);
static FRAME_INFO frame__7_488 = {0, {}};
static void cont__7_489(void);
static NODE *func__7_490;
static void entry__7_490(void);
static FRAME_INFO frame__7_490 = {2, {"generated_code", "code"}};
static void cont__7_491(void);
static void cont__7_492(void);
static void cont__7_493(void);
static void cont__7_494(void);
static NODE *func__7_495;
static void entry__7_495(void);
static FRAME_INFO frame__7_495 = {5, {"return__8", "is_main", "generated_code", "all_actions", "code"}};
static NODE *func__7_496;
static void entry__7_496(void);
static FRAME_INFO frame__7_496 = {1, {"is_main"}};
static NODE *func__7_497;
static void entry__7_497(void);
static FRAME_INFO frame__7_497 = {0, {}};
static NODE *string__7_498;
static NODE *func__7_499;
static void entry__7_499(void);
static FRAME_INFO frame__7_499 = {0, {}};
static NODE *string__7_500;
static void cont__7_501(void);
static void cont__7_502(void);
static NODE *func__7_503;
static void entry__7_503(void);
static FRAME_INFO frame__7_503 = {2, {"generated_code", "code"}};
static void cont__7_504(void);
static void cont__7_505(void);
static void cont__7_506(void);
static void cont__7_507(void);
static NODE *func__7_508;
static void entry__7_508(void);
static FRAME_INFO frame__7_508 = {1, {"stmt_actions"}};
static NODE *func__7_509;
static void entry__7_509(void);
static FRAME_INFO frame__7_509 = {1, {"action"}};
static void cont__7_510(void);
static NODE *func__7_511;
static void entry__7_511(void);
static FRAME_INFO frame__7_511 = {2, {"name", "info"}};
static NODE *string__7_512;
static void cont__7_513(void);
static void cont__7_514(void);
static NODE *func__7_515;
static void entry__7_515(void);
static FRAME_INFO frame__7_515 = {1, {"name"}};
static NODE *string__7_516;
static void cont__7_517(void);
static void cont__7_518(void);
static NODE *func__7_519;
static void entry__7_519(void);
static FRAME_INFO frame__7_519 = {1, {"filemask"}};
static NODE *string__7_520;
static void cont__7_521(void);
static void cont__7_522(void);
static void cont__7_523(void);
static void cont__7_524(void);
static NODE *func__7_525;
static void entry__7_525(void);
static FRAME_INFO frame__7_525 = {0, {}};
static NODE *string__7_526;
static void cont__7_527(void);
static NODE *string__7_528;
static void cont__7_529(void);
static void cont__7_530(void);
static NODE *func__7_531;
static void entry__7_531(void);
static FRAME_INFO frame__7_531 = {1, {"name"}};
static NODE *string__7_532;
static NODE *string__7_533;
static void cont__7_534(void);
static void cont__7_535(void);
static NODE *string__7_536;
static void cont__7_537(void);
static NODE *string__7_538;
static void cont__7_539(void);
static NODE *func__7_540;
static void entry__7_540(void);
static FRAME_INFO frame__7_540 = {0, {}};
static NODE *string__7_541;
static void cont__7_542(void);
static NODE *string__7_543;
static void cont__7_544(void);
static NODE *func__7_545;
static void entry__7_545(void);
static FRAME_INFO frame__7_545 = {0, {}};
static NODE *string__7_546;
static void cont__7_547(void);
static void cont__7_548(void);
static NODE *func__7_549;
static void entry__7_549(void);
static FRAME_INFO frame__7_549 = {0, {}};
static NODE *string__7_550;
static void cont__7_551(void);
static NODE *string__7_552;
static void cont__7_553(void);
static NODE *func__7_554;
static void entry__7_554(void);
static FRAME_INFO frame__7_554 = {2, {"name", "info"}};
static void cont__7_555(void);
static void cont__7_556(void);
static NODE *func__7_557;
static void entry__7_557(void);
static FRAME_INFO frame__7_557 = {1, {"name"}};
static NODE *string__7_558;
static NODE *string__7_559;
static void cont__7_560(void);
static void cont__7_561(void);
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
static void cont__7_580(void);
static void cont__7_581(void);
static NODE *func__7_582;
static void entry__7_582(void);
static FRAME_INFO frame__7_582 = {1, {"name"}};
static NODE *string__7_583;
static NODE *string__7_584;
static void cont__7_585(void);
static void cont__7_586(void);
static NODE *string__7_587;
static void cont__7_588(void);
static void cont__7_589(void);
static void cont__7_590(void);
static NODE *string__7_591;
static void cont__7_592(void);
static NODE *string__7_593;
static void cont__7_594(void);
static void cont__7_595(void);
static void cont__7_596(void);
static NODE *func__7_597;
static void entry__7_597(void);
static FRAME_INFO frame__7_597 = {1, {"generated_top_level_variable_names"}};
static void cont__7_598(void);
static void cont__7_599(void);
static void cont__7_600(void);
static NODE *string__7_601;
static void cont__7_602(void);
static void cont__7_603(void);
static NODE *func__7_604;
static void entry__7_604(void);
static FRAME_INFO frame__7_604 = {0, {}};
static NODE *string__7_605;
static NODE *func__7_606;
static void entry__7_606(void);
static FRAME_INFO frame__7_606 = {0, {}};
static NODE *string__7_607;
static NODE *string__7_608;
static void cont__7_609(void);
static void cont__7_610(void);
static NODE *string__7_611;
static void cont__7_612(void);
static void cont__7_613(void);
static void cont__7_614(void);
static void cont__7_615(void);
static NODE *func__7_616;
static void entry__7_616(void);
static FRAME_INFO frame__7_616 = {1, {"generated_continuation_table"}};
static void cont__7_617(void);
static void cont__7_618(void);
static void cont__7_619(void);
static NODE *string__7_620;
static void cont__7_621(void);
static NODE *string__7_622;
static void cont__7_623(void);
static NODE *func__7_624;
static void entry__7_624(void);
static FRAME_INFO frame__7_624 = {0, {}};
static NODE *func__7_625;
static void entry__7_625(void);
static FRAME_INFO frame__7_625 = {2, {"name", "node"}};
static void cont__7_626(void);
static NODE *string__7_627;
static NODE *string__7_628;
static NODE *string__7_629;
static void cont__7_630(void);
static void cont__7_631(void);
static NODE *string__7_632;
static void cont__7_633(void);
static void cont__7_634(void);
static NODE *func__7_635;
static void entry__7_635(void);
static FRAME_INFO frame__7_635 = {2, {"name", "literal"}};
static NODE *string__7_636;
static NODE *string__7_637;
static void cont__7_638(void);
static void cont__7_639(void);
static NODE *string__7_640;
static void cont__7_641(void);
static NODE *func__7_642;
static void entry__7_642(void);
static FRAME_INFO frame__7_642 = {1, {"name"}};
static NODE *string__7_643;
static NODE *string__7_644;
static void cont__7_645(void);
static void cont__7_646(void);
static NODE *string__7_647;
static NODE *string__7_648;
static void cont__7_649(void);
static void cont__7_650(void);
static NODE *string__7_651;
static void cont__7_652(void);
static NODE *func__7_653;
static void entry__7_653(void);
static FRAME_INFO frame__7_653 = {2, {"filename", "depth"}};
static void cont__7_654(void);
static void cont__7_655(void);
static void cont__7_656(void);
static NODE *string__7_657;
static NODE *string__7_658;
static void cont__7_659(void);
static NODE *func__7_660;
static void entry__7_660(void);
static FRAME_INFO frame__7_660 = {0, {}};
static NODE *string__7_661;
static void cont__7_662(void);
static NODE *string__7_663;
static void cont__7_664(void);
static NODE *func__7_665;
static void entry__7_665(void);
static FRAME_INFO frame__7_665 = {4, {"name", "info", "mangle_filename", "fname"}};
static void cont__7_666(void);
static NODE *string__7_667;
static NODE *string__7_668;
static NODE *string__7_669;
static NODE *string__7_670;
static NODE *string__7_671;
static NODE *string__7_672;
static NODE *string__7_673;
static NODE *string__7_674;
static NODE *string__7_675;
static void cont__7_676(void);
static void cont__7_677(void);
static void cont__7_678(void);
static void cont__7_679(void);
static NODE *string__7_680;
static NODE *string__7_681;
static void cont__7_682(void);
static void cont__7_683(void);
static void cont__7_684(void);
static NODE *string__7_685;
static void cont__7_686(void);
static NODE *func__7_687;
static void entry__7_687(void);
static FRAME_INFO frame__7_687 = {0, {}};
static NODE *string__7_688;
static NODE *func__7_689;
static void entry__7_689(void);
static FRAME_INFO frame__7_689 = {0, {}};
static NODE *string__7_690;
static NODE *string__7_691;
static void cont__7_692(void);
static void cont__7_693(void);
static NODE *func__7_694;
static void entry__7_694(void);
static FRAME_INFO frame__7_694 = {4, {"name", "info", "mangle_filename", "mangled_name"}};
static void cont__7_695(void);
static NODE *string__7_696;
static NODE *string__7_697;
static void cont__7_698(void);
static void cont__7_699(void);
static NODE *string__7_700;
static void cont__7_701(void);
static void cont__7_702(void);
static NODE *func__7_703;
static void entry__7_703(void);
static FRAME_INFO frame__7_703 = {0, {}};
static NODE *string__7_704;
static NODE *func__7_705;
static void entry__7_705(void);
static FRAME_INFO frame__7_705 = {0, {}};
static NODE *string__7_706;
static NODE *string__7_707;
static void cont__7_708(void);
static void cont__7_709(void);
static NODE *func__7_710;
static void entry__7_710(void);
static FRAME_INFO frame__7_710 = {3, {"name", "info", "mangle_filename"}};
static void cont__7_711(void);
static NODE *string__7_712;
static NODE *string__7_713;
static void cont__7_714(void);
static void cont__7_715(void);
static NODE *func__7_716;
static void entry__7_716(void);
static FRAME_INFO frame__7_716 = {2, {"name", "literal"}};
static NODE *string__7_717;
static NODE *string__7_718;
static void cont__7_719(void);
static void cont__7_720(void);
static NODE *func__7_721;
static void entry__7_721(void);
static FRAME_INFO frame__7_721 = {1, {"literal"}};
static void cont__7_722(void);
static NODE *func__7_723;
static void entry__7_723(void);
static FRAME_INFO frame__7_723 = {2, {"literal", "value"}};
static void cont__7_724(void);
static void cont__7_725(void);
static void cont__7_726(void);
static NODE *string__7_727;
static void cont__7_728(void);
static void cont__7_729(void);
static NODE *func__7_730;
static void entry__7_730(void);
static FRAME_INFO frame__7_730 = {1, {"value"}};
static void cont__7_731(void);
static void cont__7_732(void);
static void cont__7_733(void);
static NODE *func__7_734;
static void entry__7_734(void);
static FRAME_INFO frame__7_734 = {1, {"value"}};
static NODE *string__7_735;
static NODE *string__7_736;
static void cont__7_737(void);
static NODE *func__7_738;
static void entry__7_738(void);
static FRAME_INFO frame__7_738 = {2, {"value", "int_val"}};
static void cont__7_739(void);
static NODE *func__7_740;
static void entry__7_740(void);
static FRAME_INFO frame__7_740 = {1, {"int_val"}};
static void cont__7_741(void);
static void cont__7_742(void);
static NODE *func__7_743;
static void entry__7_743(void);
static FRAME_INFO frame__7_743 = {1, {"int_val"}};
static NODE *string__7_744;
static NODE *string__7_745;
static void cont__7_746(void);
static NODE *func__7_747;
static void entry__7_747(void);
static FRAME_INFO frame__7_747 = {1, {"int_val"}};
static void cont__7_748(void);
static void cont__7_749(void);
static NODE *func__7_750;
static void entry__7_750(void);
static FRAME_INFO frame__7_750 = {1, {"int_val"}};
static NODE *string__7_751;
static NODE *string__7_752;
static void cont__7_753(void);
static NODE *func__7_754;
static void entry__7_754(void);
static FRAME_INFO frame__7_754 = {1, {"value"}};
static NODE *string__7_755;
static NODE *string__7_756;
static void cont__7_757(void);
static NODE *func__7_758;
static void entry__7_758(void);
static FRAME_INFO frame__7_758 = {1, {"literal"}};
static void cont__7_759(void);
static NODE *func__7_760;
static void entry__7_760(void);
static FRAME_INFO frame__7_760 = {1, {"literal"}};
static void cont__7_761(void);
static void cont__7_762(void);
static NODE *string__7_763;
static NODE *string__7_764;
static void cont__7_765(void);
static void cont__7_766(void);
static void cont__7_767(void);
static NODE *func__7_768;
static void entry__7_768(void);
static FRAME_INFO frame__7_768 = {0, {}};
static NODE *string__7_769;
static NODE *func__7_770;
static void entry__7_770(void);
static FRAME_INFO frame__7_770 = {0, {}};
static NODE *string__7_771;
static NODE *string__7_772;
static void cont__7_773(void);
static void cont__7_774(void);
static NODE *func__7_775;
static void entry__7_775(void);
static FRAME_INFO frame__7_775 = {3, {"name", "info", "mangle_filename"}};
static void cont__7_776(void);
static NODE *string__7_777;
static NODE *string__7_778;
static void cont__7_779(void);
static void cont__7_780(void);
static NODE *string__7_781;
static NODE *string__7_782;
static void cont__7_783(void);
static void cont__7_784(void);
static void cont__7_785(void);
static NODE *func__7_786;
static void entry__7_786(void);
static FRAME_INFO frame__7_786 = {0, {}};
static NODE *string__7_787;
static NODE *func__7_788;
static void entry__7_788(void);
static FRAME_INFO frame__7_788 = {0, {}};
static NODE *string__7_789;
static NODE *string__7_790;
static void cont__7_791(void);
static void cont__7_792(void);
static NODE *func__7_793;
static void entry__7_793(void);
static FRAME_INFO frame__7_793 = {3, {"name", "info", "mangle_filename"}};
static void cont__7_794(void);
static NODE *string__7_795;
static NODE *string__7_796;
static void cont__7_797(void);
static void cont__7_798(void);
static NODE *string__7_799;
static NODE *string__7_800;
static void cont__7_801(void);
static void cont__7_802(void);
static NODE *func__7_803;
static void entry__7_803(void);
static FRAME_INFO frame__7_803 = {2, {"name", "info"}};
static void cont__7_804(void);
static void cont__7_805(void);
static NODE *func__7_806;
static void entry__7_806(void);
static FRAME_INFO frame__7_806 = {4, {"name", "info", "namespace", "basename"}};
static NODE *string__7_807;
static void cont__7_808(void);
static NODE *func__7_809;
static void entry__7_809(void);
static FRAME_INFO frame__7_809 = {1, {"name"}};
static NODE *string__7_810;
static void cont__7_811(void);
static void cont__7_812(void);
static NODE *func__7_813;
static void entry__7_813(void);
static FRAME_INFO frame__7_813 = {0, {}};
static NODE *string__7_814;
static void cont__7_815(void);
static NODE *string__7_816;
static void cont__7_817(void);
static void cont__7_818(void);
static NODE *func__7_819;
static void entry__7_819(void);
static FRAME_INFO frame__7_819 = {3, {"namespace", "basename", "name"}};
static NODE *string__7_820;
static NODE *string__7_821;
static NODE *string__7_822;
static NODE *string__7_823;
static NODE *string__7_824;
static void cont__7_825(void);
static NODE *func__7_826;
static void entry__7_826(void);
static FRAME_INFO frame__7_826 = {3, {"namespace", "basename", "name"}};
static NODE *string__7_827;
static NODE *string__7_828;
static NODE *string__7_829;
static NODE *string__7_830;
static NODE *string__7_831;
static void cont__7_832(void);
static NODE *func__7_833;
static void entry__7_833(void);
static FRAME_INFO frame__7_833 = {3, {"namespace", "basename", "name"}};
static NODE *string__7_834;
static NODE *string__7_835;
static NODE *string__7_836;
static NODE *string__7_837;
static NODE *string__7_838;
static void cont__7_839(void);
static NODE *func__7_840;
static void entry__7_840(void);
static FRAME_INFO frame__7_840 = {3, {"namespace", "basename", "name"}};
static NODE *string__7_841;
static NODE *string__7_842;
static NODE *string__7_843;
static NODE *string__7_844;
static NODE *string__7_845;
static void cont__7_846(void);
static NODE *func__7_847;
static void entry__7_847(void);
static FRAME_INFO frame__7_847 = {3, {"namespace", "basename", "name"}};
static NODE *string__7_848;
static NODE *string__7_849;
static NODE *string__7_850;
static NODE *string__7_851;
static NODE *string__7_852;
static NODE *string__7_853;
static void cont__7_854(void);
static void cont__7_855(void);
static void cont__7_856(void);
static NODE *func__7_857;
static void entry__7_857(void);
static FRAME_INFO frame__7_857 = {0, {}};
static NODE *string__7_858;
static void cont__7_859(void);
static NODE *func__7_860;
static void entry__7_860(void);
static FRAME_INFO frame__7_860 = {0, {}};
static NODE *string__7_861;
static NODE *func__7_862;
static void entry__7_862(void);
static FRAME_INFO frame__7_862 = {0, {}};
static NODE *string__7_863;
static NODE *string__7_864;
static void cont__7_865(void);
static void cont__7_866(void);
static NODE *func__7_867;
static void entry__7_867(void);
static FRAME_INFO frame__7_867 = {3, {"name", "info", "mangle_filename"}};
static void cont__7_868(void);
static NODE *string__7_869;
static NODE *string__7_870;
static void cont__7_871(void);
static void cont__7_872(void);
static void cont__7_873(void);
static NODE *func__7_874;
static void entry__7_874(void);
static FRAME_INFO frame__7_874 = {0, {}};
static NODE *string__7_875;
static NODE *func__7_876;
static void entry__7_876(void);
static FRAME_INFO frame__7_876 = {0, {}};
static NODE *string__7_877;
static NODE *string__7_878;
static void cont__7_879(void);
static void cont__7_880(void);
static NODE *func__7_881;
static void entry__7_881(void);
static FRAME_INFO frame__7_881 = {3, {"name", "info", "mangle_filename"}};
static void cont__7_882(void);
static NODE *string__7_883;
static NODE *string__7_884;
static void cont__7_885(void);
static void cont__7_886(void);
static void cont__7_887(void);
static NODE *string__7_888;
static NODE *string__7_889;
static void cont__7_890(void);
static void cont__7_891(void);
static NODE *func__7_892;
static void entry__7_892(void);
static FRAME_INFO frame__7_892 = {0, {}};
static NODE *string__7_893;
static void cont__7_894(void);
static NODE *string__7_895;
static void cont__7_896(void);
static NODE *func__7_897;
static void entry__7_897(void);
static FRAME_INFO frame__7_897 = {1, {"filenames"}};
static void cont__7_898(void);
static NODE *string__7_899;
static void cont__7_900(void);
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
  {entry__7_315, NULL, 492, 492, 20, 53},
  {cont__7_316, &frame__7_315, 492, 492, 53, 53},
  {entry__7_313, NULL, 491, 491, 5, 22},
  {cont__7_314, &frame__7_313, 492, 492, 5, 53},
  {cont__7_317, &frame__7_313, 492, 492, 53, 53},
  {entry__7_320, NULL, 496, 496, 20, 65},
  {cont__7_321, &frame__7_320, 496, 496, 65, 65},
  {entry__7_318, NULL, 495, 495, 5, 22},
  {cont__7_319, &frame__7_318, 496, 496, 5, 65},
  {cont__7_322, &frame__7_318, 496, 496, 65, 65},
  {entry__7_325, NULL, 500, 500, 20, 72},
  {cont__7_326, &frame__7_325, 500, 500, 72, 72},
  {entry__7_323, NULL, 499, 499, 5, 22},
  {cont__7_324, &frame__7_323, 500, 500, 5, 72},
  {cont__7_327, &frame__7_323, 500, 500, 72, 72},
  {entry__7_330, NULL, 504, 504, 20, 69},
  {cont__7_331, &frame__7_330, 504, 504, 69, 69},
  {entry__7_328, NULL, 503, 503, 5, 22},
  {cont__7_329, &frame__7_328, 504, 504, 5, 69},
  {cont__7_332, &frame__7_328, 504, 504, 69, 69},
  {entry__7_335, NULL, 508, 508, 20, 59},
  {cont__7_336, &frame__7_335, 508, 508, 59, 59},
  {entry__7_333, NULL, 507, 507, 5, 22},
  {cont__7_334, &frame__7_333, 508, 508, 5, 59},
  {cont__7_337, &frame__7_333, 508, 508, 59, 59},
  {entry__7_340, NULL, 512, 512, 20, 67},
  {cont__7_341, &frame__7_340, 512, 512, 67, 67},
  {entry__7_338, NULL, 511, 511, 5, 22},
  {cont__7_339, &frame__7_338, 512, 512, 5, 67},
  {cont__7_342, &frame__7_338, 512, 512, 67, 67},
  {entry__7_345, NULL, 516, 516, 20, 50},
  {cont__7_346, &frame__7_345, 516, 516, 50, 50},
  {entry__7_343, NULL, 515, 515, 5, 22},
  {cont__7_344, &frame__7_343, 516, 516, 5, 50},
  {cont__7_347, &frame__7_343, 516, 516, 50, 50},
  {entry__7_350, NULL, 520, 520, 20, 48},
  {cont__7_351, &frame__7_350, 520, 520, 48, 48},
  {entry__7_348, NULL, 519, 519, 5, 22},
  {cont__7_349, &frame__7_348, 520, 520, 5, 48},
  {cont__7_352, &frame__7_348, 520, 520, 48, 48},
  {entry__7_355, NULL, 524, 524, 20, 48},
  {cont__7_356, &frame__7_355, 524, 524, 48, 48},
  {entry__7_353, NULL, 523, 523, 5, 22},
  {cont__7_354, &frame__7_353, 524, 524, 5, 48},
  {cont__7_357, &frame__7_353, 524, 524, 48, 48},
  {entry__7_360, NULL, 528, 528, 20, 48},
  {cont__7_361, &frame__7_360, 528, 528, 48, 48},
  {entry__7_358, NULL, 527, 527, 5, 22},
  {cont__7_359, &frame__7_358, 528, 528, 5, 48},
  {cont__7_362, &frame__7_358, 528, 528, 48, 48},
  {entry__7_365, NULL, 532, 532, 20, 48},
  {cont__7_366, &frame__7_365, 532, 532, 48, 48},
  {entry__7_363, NULL, 531, 531, 5, 22},
  {cont__7_364, &frame__7_363, 532, 532, 5, 48},
  {cont__7_367, &frame__7_363, 532, 532, 48, 48},
  {entry__7_370, NULL, 536, 536, 20, 48},
  {cont__7_371, &frame__7_370, 536, 536, 48, 48},
  {entry__7_368, NULL, 535, 535, 5, 22},
  {cont__7_369, &frame__7_368, 536, 536, 5, 48},
  {cont__7_372, &frame__7_368, 536, 536, 48, 48},
  {entry__7_375, NULL, 540, 540, 20, 48},
  {cont__7_376, &frame__7_375, 540, 540, 48, 48},
  {entry__7_373, NULL, 539, 539, 5, 22},
  {cont__7_374, &frame__7_373, 540, 540, 5, 48},
  {cont__7_377, &frame__7_373, 540, 540, 48, 48},
  {entry__7_379, NULL, 543, 543, 20, 39},
  {cont__7_380, &frame__7_379, 543, 543, 47, 47},
  {entry__7_378, NULL, 543, 543, 5, 47},
  {cont__7_381, &frame__7_378, 543, 543, 47, 47},
  {entry__7_384, NULL, 547, 547, 20, 52},
  {cont__7_385, &frame__7_384, 547, 547, 52, 52},
  {entry__7_382, NULL, 546, 546, 5, 22},
  {cont__7_383, &frame__7_382, 547, 547, 5, 52},
  {cont__7_386, &frame__7_382, 547, 547, 52, 52},
  {entry__7_389, NULL, 551, 551, 20, 49},
  {cont__7_390, &frame__7_389, 551, 551, 49, 49},
  {entry__7_387, NULL, 550, 550, 5, 22},
  {cont__7_388, &frame__7_387, 551, 551, 5, 49},
  {cont__7_391, &frame__7_387, 551, 551, 49, 49},
  {entry__7_395, NULL, 555, 555, 28, 28},
  {cont__7_396, &frame__7_395, 555, 555, 7, 29},
  {cont__7_397, &frame__7_395, 556, 556, 7, 68},
  {entry__7_392, NULL, 554, 554, 8, 33},
  {cont__7_394, &frame__7_392, 554, 556, 5, 68},
  {entry__7_406, NULL, 568, 568, 11, 43},
  {cont__7_407, &frame__7_406, 569, 569, 11, 40},
  {cont__7_408, &frame__7_406, 569, 569, 40, 40},
  {entry__7_411, NULL, 572, 572, 13, 36},
  {entry__7_414, NULL, 575, 575, 36, 76},
  {cont__7_415, &frame__7_414, 575, 575, 36, 76},
  {entry__7_417, NULL, 576, 576, 56, 73},
  {cont__7_418, &frame__7_417, 576, 576, 17, 73},
  {entry__7_421, NULL, 581, 581, 21, 54},
  {entry__7_425, NULL, 585, 585, 25, 55},
  {entry__7_426, NULL, 587, 587, 25, 62},
  {entry__7_422, NULL, 584, 584, 23, 46},
  {cont__7_423, &frame__7_422, 584, 584, 23, 57},
  {cont__7_424, &frame__7_422, 583, 587, 21, 63},
  {entry__7_427, NULL, 589, 589, 21, 53},
  {entry__7_419, NULL, 579, 579, 19, 47},
  {cont__7_420, &frame__7_419, 578, 589, 17, 54},
  {entry__7_412, NULL, 575, 575, 15, 31},
  {cont__7_413, &frame__7_412, 575, 575, 15, 76},
  {cont__7_416, &frame__7_412, 574, 589, 13, 56},
  {entry__7_404, NULL, 567, 567, 12, 41},
  {cont__7_405, &frame__7_404, 567, 569, 9, 40},
  {cont__7_409, &frame__7_404, 571, 571, 11, 30},
  {cont__7_410, &frame__7_404, 570, 589, 9, 58},
  {entry__7_403, NULL, 565, 589, 7, 59},
  {entry__7_431, NULL, 590, 590, 28, 67},
  {entry__7_433, NULL, 591, 591, 20, 46},
  {cont__7_434, &frame__7_433, 591, 591, 46, 46},
  {entry__7_400, NULL, 562, 562, 5, 40},
  {cont__7_402, &frame__7_400, 564, 589, 5, 60},
  {cont__7_428, &frame__7_400, 590, 590, 8, 25},
  {cont__7_429, &frame__7_400, 590, 590, 8, 25},
  {cont__7_430, &frame__7_400, 590, 590, 5, 67},
  {cont__7_432, &frame__7_400, 591, 591, 5, 46},
  {cont__7_435, &frame__7_400, 592, 592, 5, 29},
  {cont__7_436, &frame__7_400, },
  {entry__7_446, NULL, 603, 603, 21, 74},
  {cont__7_449, &frame__7_446, 603, 603, 13, 74},
  {entry__7_442, NULL, 601, 601, 11, 41},
  {cont__7_444, &frame__7_442, 602, 602, 14, 29},
  {cont__7_445, &frame__7_442, 602, 603, 11, 74},
  {entry__7_450, NULL, 605, 605, 39, 70},
  {cont__7_453, &frame__7_450, 605, 605, 11, 70},
  {cont__7_454, &frame__7_450, 606, 616, 17, 66},
  {cont__7_458, &frame__7_450, 606, 616, 11, 66},
  {entry__7_460, NULL, 618, 618, 9, 35},
  {cont__7_461, &frame__7_460, 620, 620, 29, 49},
  {cont__7_462, &frame__7_460, 621, 621, 42, 62},
  {cont__7_463, &frame__7_460, 619, 622, 15, 11},
  {cont__7_467, &frame__7_460, 619, 622, 9, 11},
  {cont__7_468, &frame__7_460, 623, 623, 37, 57},
  {cont__7_469, &frame__7_460, 623, 623, 9, 59},
  {cont__7_471, &frame__7_460, 624, 624, 9, 38},
  {entry__7_441, NULL, 599, 616, 7, 68},
  {cont__7_459, &frame__7_441, 617, 624, 7, 38},
  {entry__7_473, NULL, 625, 625, 20, 46},
  {cont__7_474, &frame__7_473, 625, 625, 46, 46},
  {entry__7_440, NULL, 598, 624, 5, 39},
  {cont__7_472, &frame__7_440, 625, 625, 5, 46},
  {cont__7_475, &frame__7_440, 626, 626, 5, 29},
  {cont__7_476, &frame__7_440, },
  {entry__7_484, NULL, 633, 633, 50, 72},
  {entry__7_483, NULL, 633, 633, 27, 72},
  {entry__7_488, NULL, 634, 634, 28, 67},
  {entry__7_490, NULL, 635, 635, 20, 46},
  {cont__7_491, &frame__7_490, 635, 635, 46, 46},
  {entry__7_479, NULL, 631, 631, 32, 49},
  {cont__7_480, &frame__7_479, 631, 631, 5, 50},
  {cont__7_482, &frame__7_479, 633, 633, 5, 72},
  {cont__7_485, &frame__7_479, 634, 634, 8, 25},
  {cont__7_486, &frame__7_479, 634, 634, 8, 25},
  {cont__7_487, &frame__7_479, 634, 634, 5, 67},
  {cont__7_489, &frame__7_479, 635, 635, 5, 46},
  {cont__7_492, &frame__7_479, 636, 636, 5, 29},
  {cont__7_493, &frame__7_479, },
  {entry__7_497, NULL, 642, 644, 11, 13},
  {entry__7_499, NULL, 646, 650, 11, 13},
  {entry__7_496, NULL, 640, 650, 7, 15},
  {cont__7_501, &frame__7_496, 651, 651, 7, 22},
  {entry__7_503, NULL, 652, 652, 20, 46},
  {cont__7_504, &frame__7_503, 652, 652, 46, 46},
  {entry__7_495, NULL, 639, 651, 5, 22},
  {cont__7_502, &frame__7_495, 652, 652, 5, 46},
  {cont__7_505, &frame__7_495, 653, 653, 5, 29},
  {cont__7_506, &frame__7_495, },
  {entry__7_509, NULL, 654, 654, 72, 77},
  {entry__7_508, NULL, 654, 654, 40, 77},
  {entry__7_511, NULL, 655, 655, 51, 71},
  {cont__7_513, &frame__7_511, 655, 655, 43, 71},
  {entry__7_515, NULL, 656, 656, 45, 62},
  {cont__7_517, &frame__7_515, 656, 656, 37, 62},
  {entry__7_519, NULL, 657, 657, 47, 68},
  {cont__7_521, &frame__7_519, 657, 657, 39, 68},
  {entry__7_525, NULL, 660, 660, 5, 31},
  {cont__7_527, &frame__7_525, 661, 661, 5, 31},
  {cont__7_529, &frame__7_525, 661, 661, 36, 36},
  {entry__7_531, NULL, 662, 662, 43, 62},
  {cont__7_534, &frame__7_531, 662, 662, 35, 62},
  {entry__7_540, NULL, 682, 717, 5, 12},
  {entry__7_545, NULL, 718, 718, 40, 65},
  {cont__7_547, &frame__7_545, 718, 718, 40, 65},
  {entry__7_549, NULL, 719, 720, 5, 35},
  {entry__7_557, NULL, 767, 767, 15, 45},
  {cont__7_560, &frame__7_557, 767, 767, 7, 45},
  {entry__7_568, NULL, 770, 770, 15, 64},
  {cont__7_571, &frame__7_568, 770, 770, 7, 64},
  {entry__7_575, NULL, 772, 772, 15, 48},
  {cont__7_578, &frame__7_575, 772, 772, 7, 48},
  {entry__7_582, NULL, 774, 774, 15, 51},
  {cont__7_585, &frame__7_582, 774, 774, 7, 51},
  {entry__7_554, NULL, 766, 766, 8, 29},
  {cont__7_555, &frame__7_554, 766, 766, 8, 44},
  {cont__7_556, &frame__7_554, 766, 767, 5, 45},
  {cont__7_561, &frame__7_554, 768, 768, 13, 46},
  {cont__7_564, &frame__7_554, 768, 768, 5, 46},
  {cont__7_565, &frame__7_554, 769, 769, 8, 29},
  {cont__7_566, &frame__7_554, 769, 769, 8, 46},
  {cont__7_567, &frame__7_554, 769, 770, 5, 64},
  {cont__7_572, &frame__7_554, 771, 771, 10, 31},
  {cont__7_573, &frame__7_554, 771, 771, 33, 59},
  {cont__7_574, &frame__7_554, 771, 772, 5, 48},
  {cont__7_579, &frame__7_554, 773, 773, 10, 31},
  {cont__7_580, &frame__7_554, 773, 773, 33, 61},
  {cont__7_581, &frame__7_554, 773, 774, 5, 51},
  {entry__7_597, NULL, 784, 784, 57, 57},
  {cont__7_598, &frame__7_597, 784, 784, 13, 58},
  {cont__7_599, &frame__7_597, 784, 784, 5, 58},
  {entry__7_604, NULL, 796, 796, 7, 45},
  {entry__7_606, NULL, 798, 798, 15, 47},
  {cont__7_609, &frame__7_606, 798, 798, 7, 47},
  {entry__7_616, NULL, 804, 804, 51, 51},
  {cont__7_617, &frame__7_616, 804, 804, 13, 52},
  {cont__7_618, &frame__7_616, 804, 804, 5, 52},
  {entry__7_625, NULL, 818, 818, 26, 43},
  {cont__7_626, &frame__7_625, 818, 818, 13, 50},
  {cont__7_630, &frame__7_625, 818, 818, 7, 50},
  {entry__7_624, NULL, 817, 818, 5, 50},
  {entry__7_635, NULL, 821, 821, 49, 75},
  {cont__7_638, &frame__7_635, 821, 821, 43, 75},
  {entry__7_642, NULL, 825, 825, 42, 69},
  {cont__7_645, &frame__7_642, 825, 825, 36, 69},
  {entry__7_653, NULL, 843, 843, 38, 44},
  {cont__7_654, &frame__7_653, 843, 843, 38, 45},
  {cont__7_655, &frame__7_653, 843, 843, 7, 45},
  {cont__7_656, &frame__7_653, 844, 845, 13, 43},
  {cont__7_659, &frame__7_653, 844, 845, 7, 43},
  {entry__7_660, NULL, 847, 847, 7, 16},
  {entry__7_665, NULL, 857, 857, 5, 32},
  {cont__7_666, &frame__7_665, 858, 866, 11, 38},
  {cont__7_676, &frame__7_665, 858, 866, 5, 38},
  {entry__7_687, NULL, 877, 885, 7, 10},
  {entry__7_689, NULL, 887, 893, 13, 39},
  {cont__7_692, &frame__7_689, 887, 893, 7, 39},
  {entry__7_694, NULL, 895, 895, 5, 39},
  {cont__7_695, &frame__7_694, 896, 896, 13, 43},
  {cont__7_698, &frame__7_694, 896, 896, 5, 43},
  {entry__7_703, NULL, 903, 906, 7, 37},
  {entry__7_705, NULL, 908, 915, 13, 39},
  {cont__7_708, &frame__7_705, 908, 915, 7, 39},
  {entry__7_710, NULL, 917, 917, 27, 47},
  {cont__7_711, &frame__7_710, 917, 917, 13, 52},
  {cont__7_714, &frame__7_710, 917, 917, 5, 52},
  {entry__7_730, NULL, 924, 924, 60, 75},
  {cont__7_731, &frame__7_730, 924, 924, 43, 75},
  {cont__7_732, &frame__7_730, 924, 924, 43, 75},
  {entry__7_734, NULL, 925, 925, 19, 46},
  {cont__7_737, &frame__7_734, 925, 925, 13, 46},
  {entry__7_743, NULL, 930, 931, 23, 43},
  {cont__7_746, &frame__7_743, 930, 931, 17, 43},
  {entry__7_740, NULL, 929, 929, 18, 38},
  {cont__7_741, &frame__7_740, 929, 929, 18, 38},
  {cont__7_742, &frame__7_740, 929, 931, 15, 44},
  {entry__7_750, NULL, 933, 934, 23, 45},
  {cont__7_753, &frame__7_750, 933, 934, 17, 45},
  {entry__7_747, NULL, 932, 932, 18, 46},
  {cont__7_748, &frame__7_747, 932, 932, 18, 46},
  {cont__7_749, &frame__7_747, 932, 934, 15, 46},
  {entry__7_754, NULL, 936, 937, 23, 48},
  {cont__7_757, &frame__7_754, 936, 937, 17, 48},
  {entry__7_738, NULL, 927, 927, 13, 37},
  {cont__7_739, &frame__7_738, 928, 937, 13, 50},
  {entry__7_723, NULL, 922, 922, 28, 50},
  {cont__7_724, &frame__7_723, 922, 922, 52, 64},
  {cont__7_725, &frame__7_723, 922, 922, 9, 65},
  {cont__7_726, &frame__7_723, 924, 924, 15, 37},
  {cont__7_728, &frame__7_723, 924, 924, 11, 38},
  {cont__7_729, &frame__7_723, 924, 924, 11, 75},
  {cont__7_733, &frame__7_723, 923, 937, 9, 52},
  {entry__7_721, NULL, 921, 921, 10, 37},
  {cont__7_722, &frame__7_721, 921, 937, 7, 53},
  {entry__7_760, NULL, 939, 939, 33, 55},
  {cont__7_761, &frame__7_760, 939, 939, 33, 66},
  {cont__7_762, &frame__7_760, 939, 939, 17, 70},
  {cont__7_765, &frame__7_760, 939, 939, 9, 70},
  {entry__7_758, NULL, 938, 938, 10, 39},
  {cont__7_759, &frame__7_758, 938, 939, 7, 70},
  {entry__7_716, NULL, 919, 919, 11, 24},
  {cont__7_719, &frame__7_716, 919, 919, 5, 24},
  {cont__7_720, &frame__7_716, 920, 939, 5, 71},
  {entry__7_768, NULL, 943, 949, 7, 30},
  {entry__7_770, NULL, 951, 958, 13, 39},
  {cont__7_773, &frame__7_770, 951, 958, 7, 39},
  {entry__7_775, NULL, 960, 960, 27, 47},
  {cont__7_776, &frame__7_775, 960, 960, 13, 52},
  {cont__7_779, &frame__7_775, 960, 960, 5, 52},
  {entry__7_786, NULL, 968, 973, 7, 33},
  {entry__7_788, NULL, 975, 982, 13, 39},
  {cont__7_791, &frame__7_788, 975, 982, 7, 39},
  {entry__7_793, NULL, 984, 984, 27, 47},
  {cont__7_794, &frame__7_793, 984, 984, 13, 52},
  {cont__7_797, &frame__7_793, 984, 984, 5, 52},
  {entry__7_809, NULL, 994, 994, 30, 47},
  {cont__7_811, &frame__7_809, 994, 994, 14, 57},
  {cont__7_812, &frame__7_809, 994, 994, 11, 57},
  {entry__7_813, NULL, 995, 995, 11, 19},
  {entry__7_819, NULL, 1001, 1004, 17, 47},
  {cont__7_825, &frame__7_819, 1001, 1004, 11, 47},
  {entry__7_826, NULL, 1006, 1009, 17, 43},
  {cont__7_832, &frame__7_826, 1006, 1009, 11, 43},
  {entry__7_833, NULL, 1011, 1014, 17, 27},
  {cont__7_839, &frame__7_833, 1011, 1014, 11, 27},
  {entry__7_840, NULL, 1016, 1019, 17, 45},
  {cont__7_846, &frame__7_840, 1016, 1019, 11, 45},
  {entry__7_847, NULL, 1021, 1024, 17, 60},
  {cont__7_854, &frame__7_847, 1021, 1024, 11, 60},
  {entry__7_806, NULL, 993, 993, 11, 30},
  {cont__7_808, &frame__7_806, 991, 995, 7, 20},
  {cont__7_815, &frame__7_806, 997, 997, 7, 42},
  {cont__7_817, &frame__7_806, 999, 999, 9, 30},
  {cont__7_818, &frame__7_806, 998, 1024, 7, 62},
  {entry__7_803, NULL, 990, 990, 12, 29},
  {cont__7_804, &frame__7_803, 990, 990, 12, 40},
  {cont__7_805, &frame__7_803, 990, 1024, 5, 63},
  {entry__7_857, NULL, 1027, 1029, 5, 31},
  {entry__7_860, NULL, 1032, 1035, 7, 10},
  {entry__7_862, NULL, 1037, 1044, 13, 39},
  {cont__7_865, &frame__7_862, 1037, 1044, 7, 39},
  {entry__7_867, NULL, 1046, 1046, 27, 47},
  {cont__7_868, &frame__7_867, 1046, 1046, 13, 52},
  {cont__7_871, &frame__7_867, 1046, 1046, 5, 52},
  {entry__7_874, NULL, 1050, 1054, 7, 10},
  {entry__7_876, NULL, 1056, 1063, 13, 39},
  {cont__7_879, &frame__7_876, 1056, 1063, 7, 39},
  {entry__7_881, NULL, 1065, 1065, 27, 47},
  {cont__7_882, &frame__7_881, 1065, 1065, 13, 52},
  {cont__7_885, &frame__7_881, 1065, 1065, 5, 52},
  {entry__7_892, NULL, 1069, 1071, 5, 30},
  {entry__7_897, NULL, 1073, 1073, 53, 64},
  {cont__7_898, &frame__7_897, 1073, 1073, 22, 64},
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
  {cont__7_312, &frame__7_1, 558, 558, 3, 49},
  {cont__7_399, &frame__7_1, 559, 592, 3, 29},
  {cont__7_437, &frame__7_1, 593, 593, 3, 48},
  {cont__7_439, &frame__7_1, 595, 626, 3, 29},
  {cont__7_477, &frame__7_1, 627, 627, 3, 39},
  {cont__7_478, &frame__7_1, 628, 636, 3, 29},
  {cont__7_494, &frame__7_1, 637, 653, 3, 29},
  {cont__7_507, &frame__7_1, 654, 654, 3, 77},
  {cont__7_510, &frame__7_1, 655, 655, 3, 71},
  {cont__7_514, &frame__7_1, 656, 656, 3, 62},
  {cont__7_518, &frame__7_1, 657, 657, 3, 68},
  {cont__7_522, &frame__7_1, 658, 658, 10, 34},
  {cont__7_523, &frame__7_1, 658, 658, 3, 42},
  {cont__7_524, &frame__7_1, 659, 661, 3, 36},
  {cont__7_530, &frame__7_1, 662, 662, 3, 62},
  {cont__7_535, &frame__7_1, 663, 680, 3, 18},
  {cont__7_537, &frame__7_1, 681, 681, 10, 35},
  {cont__7_539, &frame__7_1, 681, 717, 3, 13},
  {cont__7_542, &frame__7_1, 718, 718, 10, 35},
  {cont__7_544, &frame__7_1, 718, 718, 10, 65},
  {cont__7_548, &frame__7_1, 718, 720, 3, 36},
  {cont__7_551, &frame__7_1, 721, 764, 3, 10},
  {cont__7_553, &frame__7_1, 765, 774, 3, 52},
  {cont__7_586, &frame__7_1, 775, 776, 3, 19},
  {cont__7_588, &frame__7_1, 777, 777, 3, 49},
  {cont__7_589, &frame__7_1, 778, 778, 3, 46},
  {cont__7_590, &frame__7_1, 779, 780, 3, 10},
  {cont__7_592, &frame__7_1, 781, 782, 3, 38},
  {cont__7_594, &frame__7_1, 783, 783, 6, 45},
  {cont__7_595, &frame__7_1, 783, 783, 6, 45},
  {cont__7_596, &frame__7_1, 783, 784, 3, 58},
  {cont__7_600, &frame__7_1, 785, 785, 3, 16},
  {cont__7_602, &frame__7_1, 786, 786, 3, 30},
  {cont__7_603, &frame__7_1, 794, 798, 3, 48},
  {cont__7_610, &frame__7_1, 799, 801, 3, 52},
  {cont__7_612, &frame__7_1, 802, 802, 3, 75},
  {cont__7_613, &frame__7_1, 803, 803, 6, 39},
  {cont__7_614, &frame__7_1, 803, 803, 6, 39},
  {cont__7_615, &frame__7_1, 803, 804, 3, 52},
  {cont__7_619, &frame__7_1, 805, 807, 3, 6},
  {cont__7_621, &frame__7_1, 808, 815, 3, 24},
  {cont__7_623, &frame__7_1, 816, 818, 3, 51},
  {cont__7_631, &frame__7_1, 819, 819, 3, 16},
  {cont__7_633, &frame__7_1, 820, 820, 3, 27},
  {cont__7_634, &frame__7_1, 821, 821, 3, 75},
  {cont__7_639, &frame__7_1, 822, 824, 3, 44},
  {cont__7_641, &frame__7_1, 825, 825, 3, 69},
  {cont__7_646, &frame__7_1, 826, 839, 9, 10},
  {cont__7_649, &frame__7_1, 826, 839, 3, 10},
  {cont__7_650, &frame__7_1, 840, 840, 3, 44},
  {cont__7_652, &frame__7_1, 841, 847, 3, 17},
  {cont__7_662, &frame__7_1, 848, 855, 3, 6},
  {cont__7_664, &frame__7_1, 856, 866, 3, 39},
  {cont__7_677, &frame__7_1, 867, 867, 3, 22},
  {cont__7_678, &frame__7_1, 868, 868, 3, 26},
  {cont__7_679, &frame__7_1, 869, 870, 9, 47},
  {cont__7_682, &frame__7_1, 869, 870, 3, 47},
  {cont__7_683, &frame__7_1, 871, 871, 3, 29},
  {cont__7_684, &frame__7_1, 874, 874, 3, 15},
  {cont__7_686, &frame__7_1, 875, 893, 3, 41},
  {cont__7_693, &frame__7_1, 894, 896, 3, 43},
  {cont__7_699, &frame__7_1, 897, 899, 3, 43},
  {cont__7_701, &frame__7_1, 900, 900, 3, 25},
  {cont__7_702, &frame__7_1, 901, 915, 3, 41},
  {cont__7_709, &frame__7_1, 916, 917, 3, 52},
  {cont__7_715, &frame__7_1, 918, 939, 3, 72},
  {cont__7_766, &frame__7_1, 940, 940, 3, 25},
  {cont__7_767, &frame__7_1, 941, 958, 3, 41},
  {cont__7_774, &frame__7_1, 959, 960, 3, 52},
  {cont__7_780, &frame__7_1, 961, 964, 9, 45},
  {cont__7_783, &frame__7_1, 961, 964, 3, 45},
  {cont__7_784, &frame__7_1, 965, 965, 3, 25},
  {cont__7_785, &frame__7_1, 966, 982, 3, 41},
  {cont__7_792, &frame__7_1, 983, 984, 3, 52},
  {cont__7_798, &frame__7_1, 985, 988, 9, 45},
  {cont__7_801, &frame__7_1, 985, 988, 3, 45},
  {cont__7_802, &frame__7_1, 989, 1024, 3, 64},
  {cont__7_855, &frame__7_1, 1025, 1025, 3, 25},
  {cont__7_856, &frame__7_1, 1026, 1029, 3, 32},
  {cont__7_859, &frame__7_1, 1030, 1044, 3, 41},
  {cont__7_866, &frame__7_1, 1045, 1046, 3, 52},
  {cont__7_872, &frame__7_1, 1047, 1047, 3, 25},
  {cont__7_873, &frame__7_1, 1048, 1063, 3, 41},
  {cont__7_880, &frame__7_1, 1064, 1065, 3, 52},
  {cont__7_886, &frame__7_1, 1066, 1066, 3, 25},
  {cont__7_887, &frame__7_1, 1067, 1067, 11, 58},
  {cont__7_890, &frame__7_1, 1067, 1067, 3, 58},
  {cont__7_891, &frame__7_1, 1068, 1071, 3, 31},
  {cont__7_894, &frame__7_1, 1072, 1072, 3, 15},
  {cont__7_896, &frame__7_1, 1073, 1073, 3, 64},
  {cont__7_900, &frame__7_1, 1073, 1073, 64, 64}
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
  allocate_initialized_frame_gc(0, 7);
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
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
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
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
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
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
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
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
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
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
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
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
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
  frame->slots[6] /* temp__7 */ = arguments->slots[0];
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
  allocate_initialized_frame_gc(3, 36);
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
  // generated_phase_6: 26
  // generated_code: 27
  // generated_collections: 28
  // delayed_statements: 29
  // used_literals: 30
  // def_count: 31
  // depth: 32
  frame->slots[2] /* return__9 */ = create_continuation();
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
  frame->slots[3] /* mangle_filename */ = func__7_2;
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
  frame->slots[26] /* generated_phase_6 */ = create_cell();
  frame->slots[27] /* generated_code */ = create_cell();
  frame->slots[28] /* generated_collections */ = create_cell();
  frame->slots[29] /* delayed_statements */ = create_cell();
  frame->slots[30] /* used_literals */ = create_cell();
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
  define__sim2c__write_to_phase_6(create_future());
  define__sim2c__use_literal(create_future());
  define__sim2c__write_to_generated_collections(create_future());
  define__sim2c__write_to_delayed_statements(create_future());
  define__sim2c__use_identifier(create_future());
  define__sim2c__current_continuation_info(undefined);
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
    frame->slots[34] /* temp__2 */ = temp;

  }
  // 232: ... "SIMPLE_NODE" = c_code(.source_of "")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7_50;
  arguments->slots[1] = frame->slots[34] /* temp__2 */;
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
  frame->slots[33] /* temp__1 */ = arguments->slots[0];
  // 232: %%sim2c::defined_nodes table("SIMPLE_NODE" = c_code(.source_of ""))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[33] /* temp__1 */;
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
  frame->slots[33] /* temp__1 */ = create_closure(entry__7_53, 2);
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
  arguments->slots[1] = frame->slots[33] /* temp__1 */;
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
  frame->slots[33] /* temp__1 */ = create_closure(entry__7_120, 1);
  // 273: for_each fragments: (fragment) push &trees parse_statement(fragment)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* fragments */;
  arguments->slots[1] = frame->slots[33] /* temp__1 */;
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
  frame->slots[33] /* temp__1 */ = create_closure(entry__7_124, 0);
  // 274: if do_time_passes: write_timing_info "parsing" filenames(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = frame->slots[33] /* temp__1 */;
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
  frame->slots[33] /* temp__1 */ = create_closure(entry__7_128, 0);
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
  arguments->slots[1] = frame->slots[33] /* temp__1 */;
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
  frame->slots[33] /* temp__1 */ = create_closure(entry__7_131, 0);
  // 286: if is_main: # the main program should terminate cleanly
  // 287:   push &trees procedure_call(.functor_of std_identifier("terminate"))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* is_main */;
  arguments->slots[1] = frame->slots[33] /* temp__1 */;
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
  frame->slots[33] /* temp__1 */ = create_closure(entry__7_139, 0);
  // 291: if do_time_passes: write_timing_info "expanding" filenames(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = frame->slots[33] /* temp__1 */;
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
  frame->slots[33] /* temp__1 */ = create_closure(entry__7_143, 1);
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
  arguments->slots[1] = frame->slots[33] /* temp__1 */;
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
  frame->slots[33] /* temp__1 */ = create_closure(entry__7_148, 0);
  // 299: if do_time_passes: write_timing_info "annotating" filenames(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = frame->slots[33] /* temp__1 */;
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
  frame->slots[34] /* temp__2 */ = arguments->slots[0];
  // 305: ... is_main
  frame->slots[35] /* temp__3 */ = create_closure(entry__7_156, 0);
  // 305: ... required_modules.is_empty && is_main
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[34] /* temp__2 */;
  arguments->slots[1] = frame->slots[35] /* temp__3 */;
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
  frame->slots[33] /* temp__1 */ = arguments->slots[0];
  // 305: if required_modules.is_empty && is_main:
  // 306:   !required_modules("basic/stdlib") types::grammar_node
  // 307:   !required_modules("system/stdlib") types::grammar_node
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[33] /* temp__1 */;
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
  frame->slots[33] /* temp__1 */ = get__undefined();
  // 308: !required_modules("nothing")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7_164;
  arguments->slots[1] = frame->slots[33] /* temp__1 */;
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
  frame->slots[33] /* temp__1 */ = arguments->slots[0];
  // 309: if used_namespaces.is_empty: !used_namespaces("std") true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[33] /* temp__1 */;
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
  frame->slots[33] /* temp__1 */ = get__false();
  // 310: !used_namespaces("nothing")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7_171;
  arguments->slots[1] = frame->slots[33] /* temp__1 */;
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
  frame->slots[33] /* temp__1 */ = create_closure(entry__7_173, 1);
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
  arguments->slots[1] = frame->slots[33] /* temp__1 */;
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
  frame->slots[33] /* temp__1 */ = create_closure(entry__7_254, 0);
  // 353: if do_print_warnings:
  // 354:   $$top_level_used_names empty_insert_order_table
  // 355:   for_each all_used_names: (used_names)
  // 356:     for_each used_names: (mangled_name info)
  // 357:       !top_level_used_names(mangled_name) info
  // 358:   check_definitions top_level_names top_level_used_names
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_print_warnings();
  arguments->slots[1] = frame->slots[33] /* temp__1 */;
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
  frame->slots[33] /* temp__1 */ = create_closure(entry__7_260, 0);
  // 359: if do_time_passes: write_timing_info "analyzing" filenames(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = frame->slots[33] /* temp__1 */;
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
  frame->slots[33] /* temp__1 */ = create_closure(entry__7_264, 0);
  // 360: if do_dump_trees:
  // 361:   for_each trees: (tree) write debug_string(strip(tree) 0 99)
  // 362:   terminate
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_dump_trees();
  arguments->slots[1] = frame->slots[33] /* temp__1 */;
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
  frame->slots[33] /* temp__1 */ = create_closure(entry__7_270, 1);
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
  arguments->slots[1] = frame->slots[33] /* temp__1 */;
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
  frame->slots[33] /* temp__1 */ = create_closure(entry__7_287, 0);
  // 381: if do_time_passes: write_timing_info "simplifying" filenames(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = frame->slots[33] /* temp__1 */;
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
  frame->slots[33] /* temp__1 */ = create_closure(entry__7_291, 0);
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
  arguments->slots[1] = frame->slots[33] /* temp__1 */;
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
  frame->slots[33] /* temp__1 */ = create_closure(entry__7_305, 1);
  // 413: for_each all_used_names: (used_names)
  // 414:   for_each used_names: (mangled_name info) need mangled_name info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[7])->contents /* all_used_names */;
  arguments->slots[1] = frame->slots[33] /* temp__1 */;
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
  frame->slots[33] /* temp__1 */ = create_closure(entry__7_308, 0);
  // 415: if do_time_passes: write_timing_info "mangling" filenames(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = frame->slots[33] /* temp__1 */;
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
  // 438: $$generated_phase_3 ""
  ((CELL *)frame->slots[23])->contents /* generated_phase_3 */ = empty_string;
  // 449: $$generated_phase_4 ""
  ((CELL *)frame->slots[24])->contents /* generated_phase_4 */ = empty_string;
  // 467: $$generated_phase_5 ""
  ((CELL *)frame->slots[25])->contents /* generated_phase_5 */ = empty_string;
  // 482: $$generated_phase_6 ""
  ((CELL *)frame->slots[26])->contents /* generated_phase_6 */ = empty_string;
  // 485: $$generated_code ""
  ((CELL *)frame->slots[27])->contents /* generated_code */ = empty_string;
  // 486: $$generated_collections ""
  ((CELL *)frame->slots[28])->contents /* generated_collections */ = empty_string;
  // 487: $$delayed_statements ""
  ((CELL *)frame->slots[29])->contents /* delayed_statements */ = empty_string;
  // 488: $$used_literals empty_table
  ((CELL *)frame->slots[30])->contents /* used_literals */ = get__empty_table();
  // 490: ... : (args*)
  // 491:   $txt string(args*)
  // 492:   push &actions: append &generated_declarations txt
  frame->slots[33] /* temp__1 */ = create_closure(entry__7_313, -1);
  // 490: %sim2c::write_to_declarations: (args*)
  // 491:   $txt string(args*)
  // 492:   push &actions: append &generated_declarations txt
  initialize_future(get__sim2c__write_to_declarations(), frame->slots[33] /* temp__1 */);
  // 494: ... : (args*)
  // 495:   $txt string(args*)
  // 496:   push &actions: append &generated_top_level_variable_names txt
  frame->slots[33] /* temp__1 */ = create_closure(entry__7_318, -1);
  // 494: %sim2c::write_to_top_level_variable_names: (args*)
  // 495:   $txt string(args*)
  // 496:   push &actions: append &generated_top_level_variable_names txt
  initialize_future(get__sim2c__write_to_top_level_variable_names(), frame->slots[33] /* temp__1 */);
  // 498: ... : (args*)
  // 499:   $txt string(args*)
  // 500:   push &actions: append &generated_top_level_variable_declarations txt
  frame->slots[33] /* temp__1 */ = create_closure(entry__7_323, -1);
  // 498: %sim2c::write_to_top_level_variable_declarations: (args*)
  // 499:   $txt string(args*)
  // 500:   push &actions: append &generated_top_level_variable_declarations txt
  initialize_future(get__sim2c__write_to_top_level_variable_declarations(), frame->slots[33] /* temp__1 */);
  // 502: ... : (args*)
  // 503:   $txt string(args*)
  // 504:   push &actions: append &generated_global_variable_declarations txt
  frame->slots[33] /* temp__1 */ = create_closure(entry__7_328, -1);
  // 502: %sim2c::write_to_global_variable_declarations: (args*)
  // 503:   $txt string(args*)
  // 504:   push &actions: append &generated_global_variable_declarations txt
  initialize_future(get__sim2c__write_to_global_variable_declarations(), frame->slots[33] /* temp__1 */);
  // 506: ... : (args*)
  // 507:   $txt string(args*)
  // 508:   push &actions: append &generated_continuation_table txt
  frame->slots[33] /* temp__1 */ = create_closure(entry__7_333, -1);
  // 506: %sim2c::write_to_continuation_table: (args*)
  // 507:   $txt string(args*)
  // 508:   push &actions: append &generated_continuation_table txt
  initialize_future(get__sim2c__write_to_continuation_table(), frame->slots[33] /* temp__1 */);
  // 510: ... : (args*)
  // 511:   $txt string(args*)
  // 512:   push &actions: append &generated_delayed_continuation_table txt
  frame->slots[33] /* temp__1 */ = create_closure(entry__7_338, -1);
  // 510: %sim2c::write_to_delayed_continuation_table: (args*)
  // 511:   $txt string(args*)
  // 512:   push &actions: append &generated_delayed_continuation_table txt
  initialize_future(get__sim2c__write_to_delayed_continuation_table(), frame->slots[33] /* temp__1 */);
  // 514: ... : (args*)
  // 515:   $txt string(args*)
  // 516:   push &actions: append &generated_functions txt
  frame->slots[33] /* temp__1 */ = create_closure(entry__7_343, -1);
  // 514: %sim2c::write_to_functions: (args*)
  // 515:   $txt string(args*)
  // 516:   push &actions: append &generated_functions txt
  initialize_future(get__sim2c__write_to_functions(), frame->slots[33] /* temp__1 */);
  // 518: ... : (args*)
  // 519:   $txt string(args*)
  // 520:   push &actions: append &generated_phase_1 txt
  frame->slots[33] /* temp__1 */ = create_closure(entry__7_348, -1);
  // 518: %sim2c::write_to_phase_1: (args*)
  // 519:   $txt string(args*)
  // 520:   push &actions: append &generated_phase_1 txt
  initialize_future(get__sim2c__write_to_phase_1(), frame->slots[33] /* temp__1 */);
  // 522: ... : (args*)
  // 523:   $txt string(args*)
  // 524:   push &actions: append &generated_phase_2 txt
  frame->slots[33] /* temp__1 */ = create_closure(entry__7_353, -1);
  // 522: %sim2c::write_to_phase_2: (args*)
  // 523:   $txt string(args*)
  // 524:   push &actions: append &generated_phase_2 txt
  initialize_future(get__sim2c__write_to_phase_2(), frame->slots[33] /* temp__1 */);
  // 526: ... : (args*)
  // 527:   $txt string(args*)
  // 528:   push &actions: append &generated_phase_3 txt
  frame->slots[33] /* temp__1 */ = create_closure(entry__7_358, -1);
  // 526: %sim2c::write_to_phase_3: (args*)
  // 527:   $txt string(args*)
  // 528:   push &actions: append &generated_phase_3 txt
  initialize_future(get__sim2c__write_to_phase_3(), frame->slots[33] /* temp__1 */);
  // 530: ... : (args*)
  // 531:   $txt string(args*)
  // 532:   push &actions: append &generated_phase_4 txt
  frame->slots[33] /* temp__1 */ = create_closure(entry__7_363, -1);
  // 530: %sim2c::write_to_phase_4: (args*)
  // 531:   $txt string(args*)
  // 532:   push &actions: append &generated_phase_4 txt
  initialize_future(get__sim2c__write_to_phase_4(), frame->slots[33] /* temp__1 */);
  // 534: ... : (args*)
  // 535:   $txt string(args*)
  // 536:   push &actions: append &generated_phase_5 txt
  frame->slots[33] /* temp__1 */ = create_closure(entry__7_368, -1);
  // 534: %sim2c::write_to_phase_5: (args*)
  // 535:   $txt string(args*)
  // 536:   push &actions: append &generated_phase_5 txt
  initialize_future(get__sim2c__write_to_phase_5(), frame->slots[33] /* temp__1 */);
  // 538: ... : (args*)
  // 539:   $txt string(args*)
  // 540:   push &actions: append &generated_phase_6 txt
  frame->slots[33] /* temp__1 */ = create_closure(entry__7_373, -1);
  // 538: %sim2c::write_to_phase_6: (args*)
  // 539:   $txt string(args*)
  // 540:   push &actions: append &generated_phase_6 txt
  initialize_future(get__sim2c__write_to_phase_6(), frame->slots[33] /* temp__1 */);
  // 542: ... : (name literal)
  // 543:   push &actions: !used_literals(name) literal
  frame->slots[33] /* temp__1 */ = create_closure(entry__7_378, 2);
  // 542: %sim2c::use_literal: (name literal)
  // 543:   push &actions: !used_literals(name) literal
  initialize_future(get__sim2c__use_literal(), frame->slots[33] /* temp__1 */);
  // 545: ... : (args*)
  // 546:   $txt string(args*)
  // 547:   push &actions: append &generated_collections txt
  frame->slots[33] /* temp__1 */ = create_closure(entry__7_382, -1);
  // 545: %sim2c::write_to_generated_collections: (args*)
  // 546:   $txt string(args*)
  // 547:   push &actions: append &generated_collections txt
  initialize_future(get__sim2c__write_to_generated_collections(), frame->slots[33] /* temp__1 */);
  // 549: ... : (args*)
  // 550:   $txt string(args*)
  // 551:   push &actions: append &delayed_statements txt
  frame->slots[33] /* temp__1 */ = create_closure(entry__7_387, -1);
  // 549: %sim2c::write_to_delayed_statements: (args*)
  // 550:   $txt string(args*)
  // 551:   push &actions: append &delayed_statements txt
  initialize_future(get__sim2c__write_to_delayed_statements(), frame->slots[33] /* temp__1 */);
  // 553: ... : (ident)
  // 554:   if ident .has_prefix. "get__":
  // 555:     $name range(ident 6 -1)
  // 556:     need name types::grammar_node(.variable_kind_of STATIC_SINGLE)
  frame->slots[33] /* temp__1 */ = create_closure(entry__7_392, 1);
  // 553: %sim2c::use_identifier: (ident)
  // 554:   if ident .has_prefix. "get__":
  // 555:     $name range(ident 6 -1)
  // 556:     need name types::grammar_node(.variable_kind_of STATIC_SINGLE)
  initialize_future(get__sim2c__use_identifier(), frame->slots[33] /* temp__1 */);
  // 558: show_compiler_debug_info "GENERATE DEFINITIONS"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_398;
  result_count = 0;
  myself = get__show_compiler_debug_info();
  func = myself->type;
  frame->cont = cont__7_399;
}
static void entry__7_395(void) {
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
  // 555: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__7_396;
}
static void cont__7_396(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 555: $name range(ident 6 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* ident */;
  arguments->slots[1] = number__6;
  arguments->slots[2] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__7_397;
}
static void cont__7_397(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* name */, arguments->slots[0]);
  // 556: ... types::grammar_node(.variable_kind_of STATIC_SINGLE)
  {
    NODE *temp = clone_object_and_attributes(get__types__grammar_node());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__variable_kind_of, get__STATIC_SINGLE());
    frame->slots[3] /* temp__1 */ = temp;

  }
  // 556: need name types::grammar_node(.variable_kind_of STATIC_SINGLE)
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
  // 491: $txt string(args*)
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
  // 492: ... : append &generated_declarations txt
  frame->slots[3] /* temp__1 */ = create_closure(entry__7_315, 0);
  // 492: push &actions: append &generated_declarations txt
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
  // 492: ... append &generated_declarations txt
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
  // 495: $txt string(args*)
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
  // 496: ... : append &generated_top_level_variable_names txt
  frame->slots[3] /* temp__1 */ = create_closure(entry__7_320, 0);
  // 496: push &actions: append &generated_top_level_variable_names txt
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
  // 496: ... append &generated_top_level_variable_names txt
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
  // 499: $txt string(args*)
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
  // 500: ... : append &generated_top_level_variable_declarations txt
  frame->slots[3] /* temp__1 */ = create_closure(entry__7_325, 0);
  // 500: push &actions: append &generated_top_level_variable_declarations txt
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
  // 500: ... append &generated_top_level_variable_declarations txt
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
  // 503: $txt string(args*)
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
  // 504: ... : append &generated_global_variable_declarations txt
  frame->slots[3] /* temp__1 */ = create_closure(entry__7_330, 0);
  // 504: push &actions: append &generated_global_variable_declarations txt
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
  // 504: ... append &generated_global_variable_declarations txt
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
  // 507: $txt string(args*)
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
  // 508: ... : append &generated_continuation_table txt
  frame->slots[3] /* temp__1 */ = create_closure(entry__7_335, 0);
  // 508: push &actions: append &generated_continuation_table txt
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
  // 508: ... append &generated_continuation_table txt
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
  // 511: $txt string(args*)
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
  // 512: ... : append &generated_delayed_continuation_table txt
  frame->slots[3] /* temp__1 */ = create_closure(entry__7_340, 0);
  // 512: push &actions: append &generated_delayed_continuation_table txt
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
  // 512: ... append &generated_delayed_continuation_table txt
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
  // 515: $txt string(args*)
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
  // 516: ... : append &generated_functions txt
  frame->slots[3] /* temp__1 */ = create_closure(entry__7_345, 0);
  // 516: push &actions: append &generated_functions txt
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
  // 516: ... append &generated_functions txt
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
  // 519: $txt string(args*)
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
  // 520: ... : append &generated_phase_1 txt
  frame->slots[3] /* temp__1 */ = create_closure(entry__7_350, 0);
  // 520: push &actions: append &generated_phase_1 txt
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
  // 520: ... append &generated_phase_1 txt
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
  // 523: $txt string(args*)
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
  // 524: ... : append &generated_phase_2 txt
  frame->slots[3] /* temp__1 */ = create_closure(entry__7_355, 0);
  // 524: push &actions: append &generated_phase_2 txt
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
  // 524: ... append &generated_phase_2 txt
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
  // 527: $txt string(args*)
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
  // 528: ... : append &generated_phase_3 txt
  frame->slots[3] /* temp__1 */ = create_closure(entry__7_360, 0);
  // 528: push &actions: append &generated_phase_3 txt
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
  // 528: ... append &generated_phase_3 txt
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
  // 531: $txt string(args*)
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
  // 532: ... : append &generated_phase_4 txt
  frame->slots[3] /* temp__1 */ = create_closure(entry__7_365, 0);
  // 532: push &actions: append &generated_phase_4 txt
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
  // 532: ... append &generated_phase_4 txt
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
  // 535: $txt string(args*)
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
  // 536: ... : append &generated_phase_5 txt
  frame->slots[3] /* temp__1 */ = create_closure(entry__7_370, 0);
  // 536: push &actions: append &generated_phase_5 txt
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
  // 536: ... append &generated_phase_5 txt
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
  allocate_arguments();
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // args: 0
  // generated_phase_6: 1
  // txt: 2
  frame->slots[1] = myself->closure.frame->slots[26]; /* generated_phase_6 */
  frame->slots[2] /* txt */ = create_future();
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 539: $txt string(args*)
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__7_374;
}
static void cont__7_374(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* txt */, arguments->slots[0]);
  // 540: ... : append &generated_phase_6 txt
  frame->slots[3] /* temp__1 */ = create_closure(entry__7_375, 0);
  // 540: push &actions: append &generated_phase_6 txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__7_377;
}
static void entry__7_375(void) {
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
  // 540: ... append &generated_phase_6 txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_phase_6 */;
  arguments->slots[1] = frame->slots[1] /* txt */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__7_376;
}
static void cont__7_376(void) {
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
static void cont__7_377(void) {
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
static void entry__7_378(void) {
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
  // 543: ... : !used_literals(name) literal
  frame->slots[3] /* temp__1 */ = create_closure(entry__7_379, 0);
  // 543: push &actions: !used_literals(name) literal
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
  // 543: ... !used_literals(name) literal
  frame->slots[3] /* temp__1 */ = frame->slots[2] /* literal */;
  // 543: ... !used_literals(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* name */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* used_literals */;
  func = myself->type;
  frame->cont = cont__7_380;
}
static void cont__7_380(void) {
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
  // generated_collections: 1
  // txt: 2
  frame->slots[1] = myself->closure.frame->slots[28]; /* generated_collections */
  frame->slots[2] /* txt */ = create_future();
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 546: $txt string(args*)
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
  // 547: ... : append &generated_collections txt
  frame->slots[3] /* temp__1 */ = create_closure(entry__7_384, 0);
  // 547: push &actions: append &generated_collections txt
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
  // generated_collections: 0
  // txt: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* generated_collections */
  frame->slots[1] = myself->closure.frame->slots[2]; /* txt */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 547: ... append &generated_collections txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_collections */;
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
  ((CELL *)frame->slots[0])->contents /* generated_collections */ = arguments->slots[0];
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
  allocate_arguments();
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // args: 0
  // delayed_statements: 1
  // txt: 2
  frame->slots[1] = myself->closure.frame->slots[29]; /* delayed_statements */
  frame->slots[2] /* txt */ = create_future();
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 550: $txt string(args*)
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__7_388;
}
static void cont__7_388(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* txt */, arguments->slots[0]);
  // 551: ... : append &delayed_statements txt
  frame->slots[3] /* temp__1 */ = create_closure(entry__7_389, 0);
  // 551: push &actions: append &delayed_statements txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__7_391;
}
static void entry__7_389(void) {
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
  // 551: ... append &delayed_statements txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* delayed_statements */;
  arguments->slots[1] = frame->slots[1] /* txt */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__7_390;
}
static void cont__7_390(void) {
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
static void cont__7_391(void) {
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
static void entry__7_392(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // ident: 0
  // need: 1
  frame->slots[1] = myself->closure.frame->slots[13]; /* need */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 554: ... ident .has_prefix. "get__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* ident */;
  arguments->slots[1] = string__7_393;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__7_394;
}
static void cont__7_394(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 554: ... :
  // 555:   $name range(ident 6 -1)
  // 556:   need name types::grammar_node(.variable_kind_of STATIC_SINGLE)
  frame->slots[3] /* temp__2 */ = create_closure(entry__7_395, 0);
  // 554: if ident .has_prefix. "get__":
  // 555:   $name range(ident 6 -1)
  // 556:   need name types::grammar_node(.variable_kind_of STATIC_SINGLE)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_399(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 559: ... : (stmt_idx defs)
  // 560:   %%sim2c::actions empty_list
  // 561:   %%sim2c::delayed_code ""
  // 562:   %sim2c::suffix string("__" stmt_idx)
  // 563:   %%sim2c::index 0
  // 564:   collect_output $code:
  // 565:     for_each defs: ($definition)
  // 566:       $$source undefined
  // 567:       if definition.is_a_key_value_pair:
  // 568:         !source std::value_of(definition)
  // ...
  frame->slots[33] /* temp__1 */ = create_closure(entry__7_400, 2);
  // 559: for_each all_definitions: (stmt_idx defs)
  // 560:   %%sim2c::actions empty_list
  // 561:   %%sim2c::delayed_code ""
  // 562:   %sim2c::suffix string("__" stmt_idx)
  // 563:   %%sim2c::index 0
  // 564:   collect_output $code:
  // 565:     for_each defs: ($definition)
  // 566:       $$source undefined
  // 567:       if definition.is_a_key_value_pair:
  // 568:         !source std::value_of(definition)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[10])->contents /* all_definitions */;
  arguments->slots[1] = frame->slots[33] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__7_437;
}
static void entry__7_400(void) {
  allocate_initialized_frame_gc(5, 8);
  // slot allocations:
  // stmt_idx: 0
  // defs: 1
  // return__5: 2
  // generated_code: 3
  // all_actions: 4
  // code: 5
  frame->slots[2] /* return__5 */ = create_continuation();
  frame->slots[3] = myself->closure.frame->slots[27]; /* generated_code */
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
  // 560: %%sim2c::actions empty_list
  set__sim2c__actions(get__empty_list());
  // 561: %%sim2c::delayed_code ""
  set__sim2c__delayed_code(empty_string);
  // 562: %sim2c::suffix string("__" stmt_idx)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7_401;
  arguments->slots[1] = frame->slots[0] /* stmt_idx */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__7_402;
}
static void cont__7_402(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(get__sim2c__suffix(), arguments->slots[0]);
  // 563: %%sim2c::index 0
  set__sim2c__index(number__0);
  // 564: ... :
  // 565:   for_each defs: ($definition)
  // 566:     $$source undefined
  // 567:     if definition.is_a_key_value_pair:
  // 568:       !source std::value_of(definition)
  // 569:       !definition key_of(definition)
  // 570:     if
  // 571:       definition.is_c_code:
  // 572:         define_c_code definition
  // 573:       :
  // ...
  frame->slots[6] /* temp__1 */ = create_closure(entry__7_403, 0);
  // 564: collect_output $code:
  // 565:   for_each defs: ($definition)
  // 566:     $$source undefined
  // 567:     if definition.is_a_key_value_pair:
  // 568:       !source std::value_of(definition)
  // 569:       !definition key_of(definition)
  // 570:     if
  // 571:       definition.is_c_code:
  // 572:         define_c_code definition
  // 573:       :
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__7_428;
}
static void entry__7_425(void) {
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
  // 585: define_method definition source
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* definition */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* source */;
  result_count = frame->caller_result_count;
  myself = get__define_method();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_426(void) {
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
  // 587: define_type_function definition source
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* definition */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* source */;
  result_count = frame->caller_result_count;
  myself = get__define_type_function();
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
  // 581: define_attribute definition source
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* definition */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* source */;
  result_count = frame->caller_result_count;
  myself = get__define_attribute();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_422(void) {
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
  // 584: attribute_of(definition)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* definition */;
  result_count = 1;
  myself = get__attribute_of();
  func = myself->type;
  frame->cont = cont__7_423;
}
static void cont__7_423(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 584: attribute_of(definition).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__7_424;
}
static void cont__7_424(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 584: ... :
  // 585:   define_method definition source
  frame->slots[4] /* temp__3 */ = create_closure(entry__7_425, 0);
  // 586: :
  // 587:   define_type_function definition source
  frame->slots[5] /* temp__4 */ = create_closure(entry__7_426, 0);
  // 583: if
  // 584:   attribute_of(definition).is_defined:
  // 585:     define_method definition source
  // 586:   :
  // 587:     define_type_function definition source
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
static void entry__7_427(void) {
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
  // 589: define_variable definition source
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* definition */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* source */;
  result_count = frame->caller_result_count;
  myself = get__define_variable();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_417(void) {
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
  // 576: ... source.is_a_setter
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* source */;
  result_count = 1;
  myself = get__is_a_setter();
  func = myself->type;
  frame->cont = cont__7_418;
}
static void cont__7_418(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 576: define_polymorphic_function definition source.is_a_setter
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* definition */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__define_polymorphic_function();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_419(void) {
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
  // 579: attribute_kind_of(definition)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* definition */;
  result_count = 1;
  myself = get__attribute_kind_of();
  func = myself->type;
  frame->cont = cont__7_420;
}
static void cont__7_420(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 580: ... :
  // 581:   define_attribute definition source
  frame->slots[3] /* temp__2 */ = create_closure(entry__7_421, 0);
  // 582: ... :
  // 583:   if
  // 584:     attribute_of(definition).is_defined:
  // 585:       define_method definition source
  // 586:     :
  // 587:       define_type_function definition source
  frame->slots[4] /* temp__3 */ = create_closure(entry__7_422, 0);
  // 588: :
  // 589:   define_variable definition source
  frame->slots[5] /* temp__4 */ = create_closure(entry__7_427, 0);
  // 578: case
  // 579:   attribute_kind_of(definition)
  // 580:   ATTRIBUTE_KIND:
  // 581:     define_attribute definition source
  // 582:   METHOD_KIND:
  // 583:     if
  // 584:       attribute_of(definition).is_defined:
  // 585:         define_method definition source
  // 586:       :
  // 587:         define_type_function definition source
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
static void entry__7_411(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // definition: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* definition */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 572: define_c_code definition
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* definition */;
  result_count = frame->caller_result_count;
  myself = get__define_c_code();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_412(void) {
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
  // 575: source.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* source */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__7_413;
}
static void cont__7_413(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 575: ... source.is_a_polymorphic_function_constant
  frame->slots[4] /* temp__3 */ = create_closure(entry__7_414, 0);
  // 575: source.is_defined && source.is_a_polymorphic_function_constant
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__7_416;
}
static void entry__7_414(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // source: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* source */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 575: ... source.is_a_polymorphic_function_constant
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* source */;
  result_count = 1;
  myself = get__is_a_polymorphic_function_constant();
  func = myself->type;
  frame->cont = cont__7_415;
}
static void cont__7_415(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 575: ... source.is_a_polymorphic_function_constant
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__7_416(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 575: ... :
  // 576:   define_polymorphic_function definition source.is_a_setter
  frame->slots[5] /* temp__4 */ = create_closure(entry__7_417, 0);
  // 577: :
  // 578:   case
  // 579:     attribute_kind_of(definition)
  // 580:     ATTRIBUTE_KIND:
  // 581:       define_attribute definition source
  // 582:     METHOD_KIND:
  // 583:       if
  // 584:         attribute_of(definition).is_defined:
  // 585:           define_method definition source
  // 586:         :
  // ...
  frame->slots[6] /* temp__5 */ = create_closure(entry__7_419, 0);
  // 574: if
  // 575:   source.is_defined && source.is_a_polymorphic_function_constant:
  // 576:     define_polymorphic_function definition source.is_a_setter
  // 577:   :
  // 578:     case
  // 579:       attribute_kind_of(definition)
  // 580:       ATTRIBUTE_KIND:
  // 581:         define_attribute definition source
  // 582:       METHOD_KIND:
  // 583:         if
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
static void entry__7_404(void) {
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
  // 566: $$source undefined
  ((CELL *)frame->slots[1])->contents /* source */ = get__undefined();
  // 567: ... definition.is_a_key_value_pair
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* definition */;
  result_count = 1;
  myself = get__is_a_key_value_pair();
  func = myself->type;
  frame->cont = cont__7_405;
}
static void cont__7_405(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 567: ... :
  // 568:   !source std::value_of(definition)
  // 569:   !definition key_of(definition)
  frame->slots[3] /* temp__2 */ = create_closure(entry__7_406, 0);
  // 567: if definition.is_a_key_value_pair:
  // 568:   !source std::value_of(definition)
  // 569:   !definition key_of(definition)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_409;
}
static void entry__7_406(void) {
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
  // 568: !source std::value_of(definition)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* definition */;
  result_count = 1;
  myself = get__std__value_of();
  func = myself->type;
  frame->cont = cont__7_407;
}
static void cont__7_407(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* source */ = arguments->slots[0];
  // 569: !definition key_of(definition)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* definition */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__7_408;
}
static void cont__7_408(void) {
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
static void cont__7_409(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 571: definition.is_c_code
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* definition */;
  result_count = 1;
  myself = get__is_c_code();
  func = myself->type;
  frame->cont = cont__7_410;
}
static void cont__7_410(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 571: ... :
  // 572:   define_c_code definition
  frame->slots[3] /* temp__2 */ = create_closure(entry__7_411, 0);
  // 573: :
  // 574:   if
  // 575:     source.is_defined && source.is_a_polymorphic_function_constant:
  // 576:       define_polymorphic_function definition source.is_a_setter
  // 577:     :
  // 578:       case
  // 579:         attribute_kind_of(definition)
  // 580:         ATTRIBUTE_KIND:
  // 581:           define_attribute definition source
  // 582:         METHOD_KIND:
  // ...
  frame->slots[4] /* temp__3 */ = create_closure(entry__7_412, 0);
  // 570: if
  // 571:   definition.is_c_code:
  // 572:     define_c_code definition
  // 573:   :
  // 574:     if
  // 575:       source.is_defined && source.is_a_polymorphic_function_constant:
  // 576:         define_polymorphic_function definition source.is_a_setter
  // 577:       :
  // 578:         case
  // 579:           attribute_kind_of(definition)
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
static void entry__7_403(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // defs: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* defs */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 565: for_each defs: ($definition)
  // 566:   $$source undefined
  // 567:   if definition.is_a_key_value_pair:
  // 568:     !source std::value_of(definition)
  // 569:     !definition key_of(definition)
  // 570:   if
  // 571:     definition.is_c_code:
  // 572:       define_c_code definition
  // 573:     :
  // 574:       if
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* defs */;
  arguments->slots[1] = func__7_404;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_428(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* code */, arguments->slots[0]);
  // 590: ... delayed_code != ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__delayed_code();
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__7_429;
}
static void cont__7_429(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 590: ... delayed_code != ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__7_430;
}
static void cont__7_430(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 590: if delayed_code != "": write_to_delayed_statements delayed_code
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = func__7_431;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_432;
}
static void entry__7_431(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 590: ... write_to_delayed_statements delayed_code
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__delayed_code();
  result_count = frame->caller_result_count;
  myself = get__write_to_delayed_statements();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_432(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 591: ... : append &generated_code code
  frame->slots[6] /* temp__1 */ = create_closure(entry__7_433, 0);
  // 591: push &actions: append &generated_code code
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__7_435;
}
static void entry__7_433(void) {
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
  // 591: ... append &generated_code code
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_code */;
  arguments->slots[1] = frame->slots[1] /* code */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__7_434;
}
static void cont__7_434(void) {
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
static void cont__7_435(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__actions(arguments->slots[0]);
  // 592: push &all_actions actions
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* all_actions */;
  arguments->slots[1] = get__actions();
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__7_436;
}
static void cont__7_436(void) {
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
static void cont__7_437(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 593: show_compiler_debug_info "GENERATE STATEMENTS"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_438;
  result_count = 0;
  myself = get__show_compiler_debug_info();
  func = myself->type;
  frame->cont = cont__7_439;
}
static void cont__7_439(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 594: %%sim2c::current_continuation_info undefined
  set__sim2c__current_continuation_info(get__undefined());
  // 595: ... :
  // 596:   %%sim2c::actions empty_list
  // 597:   %%sim2c::delayed_code ""
  // 598:   collect_output $code:
  // 599:     if
  // 600:       is_main:
  // 601:         begin_continuation "main_entry"
  // 602:         if max_temp_idx > 0:
  // 603:           writeln "  allocate_initialized_frame_gc(0, @(max_temp_idx));"
  // 604:       :
  // ...
  frame->slots[33] /* temp__1 */ = create_closure(entry__7_440, 0);
  // 595: do:
  // 596:   %%sim2c::actions empty_list
  // 597:   %%sim2c::delayed_code ""
  // 598:   collect_output $code:
  // 599:     if
  // 600:       is_main:
  // 601:         begin_continuation "main_entry"
  // 602:         if max_temp_idx > 0:
  // 603:           writeln "  allocate_initialized_frame_gc(0, @(max_temp_idx));"
  // 604:       :
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[33] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__7_477;
}
static void entry__7_440(void) {
  allocate_initialized_frame_gc(6, 8);
  // slot allocations:
  // return__6: 0
  // is_main: 1
  // max_temp_idx: 2
  // mangle_filename: 3
  // generated_code: 4
  // all_actions: 5
  // code: 6
  frame->slots[0] /* return__6 */ = create_continuation();
  frame->slots[1] = myself->closure.frame->slots[1]; /* is_main */
  frame->slots[2] = myself->closure.frame->slots[12]; /* max_temp_idx */
  frame->slots[3] = myself->closure.frame->slots[3]; /* mangle_filename */
  frame->slots[4] = myself->closure.frame->slots[27]; /* generated_code */
  frame->slots[5] = myself->closure.frame->slots[8]; /* all_actions */
  define__sim2c__actions(undefined);
  define__sim2c__delayed_code(undefined);
  frame->slots[6] /* code */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 596: %%sim2c::actions empty_list
  set__sim2c__actions(get__empty_list());
  // 597: %%sim2c::delayed_code ""
  set__sim2c__delayed_code(empty_string);
  // 598: ... :
  // 599:   if
  // 600:     is_main:
  // 601:       begin_continuation "main_entry"
  // 602:       if max_temp_idx > 0:
  // 603:         writeln "  allocate_initialized_frame_gc(0, @(max_temp_idx));"
  // 604:     :
  // 605:       write_to_continuation_table "  {run__@(module_name), NULL, "
  // 606:       write "
  // 607:         static int already_run = false;
  // ...
  frame->slots[7] /* temp__1 */ = create_closure(entry__7_441, 0);
  // 598: collect_output $code:
  // 599:   if
  // 600:     is_main:
  // 601:       begin_continuation "main_entry"
  // 602:       if max_temp_idx > 0:
  // 603:         writeln "  allocate_initialized_frame_gc(0, @(max_temp_idx));"
  // 604:     :
  // 605:       write_to_continuation_table "  {run__@(module_name), NULL, "
  // 606:       write "
  // 607:         static int already_run = false;
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__7_472;
}
static void entry__7_460(void) {
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
  // 618: write_source_as_remark info
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 0;
  myself = get__write_source_as_remark();
  func = myself->type;
  frame->cont = cont__7_461;
}
static void cont__7_461(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 620: ... mangle_filename(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = frame->slots[2] /* mangle_filename */;
  func = myself->type;
  frame->cont = cont__7_462;
}
static void cont__7_462(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 621: ... mangle_filename(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = frame->slots[2] /* mangle_filename */;
  func = myself->type;
  frame->cont = cont__7_463;
}
static void cont__7_463(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 619: ... "
  // 620:     func = run__@(mangle_filename(name));
  // 621:     frame->cont = cont__run__@(mangle_filename(name));
  // 622:   }
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__7_464;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = string__7_465;
  arguments->slots[3] = frame->slots[6] /* temp__3 */;
  arguments->slots[4] = string__7_466;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_467;
}
static void cont__7_467(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 619: write "
  // 620:     func = run__@(mangle_filename(name));
  // 621:     frame->cont = cont__run__@(mangle_filename(name));
  // 622:   }
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_468;
}
static void cont__7_468(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 623: ... mangle_filename(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = frame->slots[2] /* mangle_filename */;
  func = myself->type;
  frame->cont = cont__7_469;
}
static void cont__7_469(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 623: $continuation "cont__run__@(mangle_filename(name))"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7_470;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_471;
}
static void cont__7_471(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* continuation */, arguments->slots[0]);
  // 624: next_continuation continuation
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* continuation */;
  result_count = frame->caller_result_count;
  myself = get__next_continuation();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_441(void) {
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
  // 600: ... :
  // 601:   begin_continuation "main_entry"
  // 602:   if max_temp_idx > 0:
  // 603:     writeln "  allocate_initialized_frame_gc(0, @(max_temp_idx));"
  frame->slots[3] /* temp__1 */ = create_closure(entry__7_442, 0);
  // 604: :
  // 605:   write_to_continuation_table "  {run__@(module_name), NULL, "
  // 606:   write "
  // 607:     static int already_run = false;
  // 608:     
  // 609:     EXPORT void run__@(module_name)(void) {
  // 610:       if (already_run) {
  // 611:         func = frame->cont;
  // 612:         frame->cont = invalid_continuation;
  // 613:         return;
  // ...
  frame->slots[4] /* temp__2 */ = create_closure(entry__7_450, 0);
  // 599: if
  // 600:   is_main:
  // 601:     begin_continuation "main_entry"
  // 602:     if max_temp_idx > 0:
  // 603:       writeln "  allocate_initialized_frame_gc(0, @(max_temp_idx));"
  // 604:   :
  // 605:     write_to_continuation_table "  {run__@(module_name), NULL, "
  // 606:     write "
  // 607:       static int already_run = false;
  // 608:       
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* is_main */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  arguments->slots[2] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_459;
}
static void entry__7_446(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // max_temp_idx: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* max_temp_idx */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 603: ... "  allocate_initialized_frame_gc(0, @(max_temp_idx));"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_447;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* max_temp_idx */;
  arguments->slots[2] = string__7_448;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_449;
}
static void cont__7_449(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 603: writeln "  allocate_initialized_frame_gc(0, @(max_temp_idx));"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_442(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // max_temp_idx: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* max_temp_idx */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 601: begin_continuation "main_entry"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_443;
  result_count = 0;
  myself = get__begin_continuation();
  func = myself->type;
  frame->cont = cont__7_444;
}
static void cont__7_444(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 602: ... max_temp_idx > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* max_temp_idx */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__7_445;
}
static void cont__7_445(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 602: ... :
  // 603:   writeln "  allocate_initialized_frame_gc(0, @(max_temp_idx));"
  frame->slots[2] /* temp__2 */ = create_closure(entry__7_446, 0);
  // 602: if max_temp_idx > 0:
  // 603:   writeln "  allocate_initialized_frame_gc(0, @(max_temp_idx));"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_450(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // max_temp_idx: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* max_temp_idx */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 605: ... "  {run__@(module_name), NULL, "
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_451;
  arguments->slots[1] = get__module_name();
  arguments->slots[2] = string__7_452;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_453;
}
static void cont__7_453(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 605: write_to_continuation_table "  {run__@(module_name), NULL, "
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 0;
  myself = get__write_to_continuation_table();
  func = myself->type;
  frame->cont = cont__7_454;
}
static void cont__7_454(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 606: ... "
  // 607:   static int already_run = false;
  // 608:   
  // 609:   EXPORT void run__@(module_name)(void) {
  // 610:     if (already_run) {
  // 611:       func = frame->cont;
  // 612:       frame->cont = invalid_continuation;
  // 613:       return;
  // 614:     }
  // 615:     already_run = true;
  // ...
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__7_455;
  arguments->slots[1] = get__module_name();
  arguments->slots[2] = string__7_456;
  arguments->slots[3] = ((CELL *)frame->slots[0])->contents /* max_temp_idx */;
  arguments->slots[4] = string__7_457;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_458;
}
static void cont__7_458(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 606: write "
  // 607:   static int already_run = false;
  // 608:   
  // 609:   EXPORT void run__@(module_name)(void) {
  // 610:     if (already_run) {
  // 611:       func = frame->cont;
  // 612:       frame->cont = invalid_continuation;
  // 613:       return;
  // 614:     }
  // 615:     already_run = true;
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_459(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 617: ... : (name info)
  // 618:   write_source_as_remark info
  // 619:   write "
  // 620:       func = run__@(mangle_filename(name));
  // 621:       frame->cont = cont__run__@(mangle_filename(name));
  // 622:     }
  // 623:   $continuation "cont__run__@(mangle_filename(name))"
  // 624:   next_continuation continuation
  frame->slots[3] /* temp__1 */ = create_closure(entry__7_460, 2);
  // 617: for_each required_modules: (name info)
  // 618:   write_source_as_remark info
  // 619:   write "
  // 620:       func = run__@(mangle_filename(name));
  // 621:       frame->cont = cont__run__@(mangle_filename(name));
  // 622:     }
  // 623:   $continuation "cont__run__@(mangle_filename(name))"
  // 624:   next_continuation continuation
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__required_modules();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_472(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* code */, arguments->slots[0]);
  // 625: ... : append &generated_code code
  frame->slots[7] /* temp__1 */ = create_closure(entry__7_473, 0);
  // 625: push &actions: append &generated_code code
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[7] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__7_475;
}
static void entry__7_473(void) {
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
  // 625: ... append &generated_code code
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_code */;
  arguments->slots[1] = frame->slots[1] /* code */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__7_474;
}
static void cont__7_474(void) {
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
static void cont__7_475(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__actions(arguments->slots[0]);
  // 626: push &all_actions actions
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* all_actions */;
  arguments->slots[1] = get__actions();
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__7_476;
}
static void cont__7_476(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[5])->contents /* all_actions */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  myself = frame->slots[0] /* return__6 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__7_477(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 627: $def_count length_of(all_definitions)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[10])->contents /* all_definitions */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__7_478;
}
static void cont__7_478(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[31] /* def_count */, arguments->slots[0]);
  // 628: ... : (stmt_idx stmts)
  // 629:   %%sim2c::actions empty_list
  // 630:   %%sim2c::delayed_code ""
  // 631:   %sim2c::suffix string("__" stmt_idx+def_count)
  // 632:   %%sim2c::index 0
  // 633:   collect_output $code: for_each stmts: (stmt) generate_statement stmt
  // 634:   if delayed_code != "": write_to_delayed_statements delayed_code
  // 635:   push &actions: append &generated_code code
  // 636:   push &all_actions actions
  frame->slots[33] /* temp__1 */ = create_closure(entry__7_479, 2);
  // 628: for_each all_statements: (stmt_idx stmts)
  // 629:   %%sim2c::actions empty_list
  // 630:   %%sim2c::delayed_code ""
  // 631:   %sim2c::suffix string("__" stmt_idx+def_count)
  // 632:   %%sim2c::index 0
  // 633:   collect_output $code: for_each stmts: (stmt) generate_statement stmt
  // 634:   if delayed_code != "": write_to_delayed_statements delayed_code
  // 635:   push &actions: append &generated_code code
  // 636:   push &all_actions actions
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[11])->contents /* all_statements */;
  arguments->slots[1] = frame->slots[33] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__7_494;
}
static void entry__7_479(void) {
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
  frame->slots[3] = myself->closure.frame->slots[31]; /* def_count */
  frame->slots[4] = myself->closure.frame->slots[27]; /* generated_code */
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
  // 629: %%sim2c::actions empty_list
  set__sim2c__actions(get__empty_list());
  // 630: %%sim2c::delayed_code ""
  set__sim2c__delayed_code(empty_string);
  // 631: ... stmt_idx+def_count
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stmt_idx */;
  arguments->slots[1] = frame->slots[3] /* def_count */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__7_480;
}
static void cont__7_480(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 631: %sim2c::suffix string("__" stmt_idx+def_count)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7_481;
  arguments->slots[1] = frame->slots[7] /* temp__1 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__7_482;
}
static void cont__7_482(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(get__sim2c__suffix(), arguments->slots[0]);
  // 632: %%sim2c::index 0
  set__sim2c__index(number__0);
  // 633: ... : for_each stmts: (stmt) generate_statement stmt
  frame->slots[7] /* temp__1 */ = create_closure(entry__7_483, 0);
  // 633: collect_output $code: for_each stmts: (stmt) generate_statement stmt
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__7_485;
}
static void entry__7_484(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // stmt: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 633: ... generate_statement stmt
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stmt */;
  result_count = frame->caller_result_count;
  myself = get__generate_statement();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_483(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // stmts: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* stmts */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 633: ... for_each stmts: (stmt) generate_statement stmt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stmts */;
  arguments->slots[1] = func__7_484;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_485(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* code */, arguments->slots[0]);
  // 634: ... delayed_code != ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__delayed_code();
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__7_486;
}
static void cont__7_486(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 634: ... delayed_code != ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__7_487;
}
static void cont__7_487(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 634: if delayed_code != "": write_to_delayed_statements delayed_code
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = func__7_488;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_489;
}
static void entry__7_488(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 634: ... write_to_delayed_statements delayed_code
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__delayed_code();
  result_count = frame->caller_result_count;
  myself = get__write_to_delayed_statements();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_489(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 635: ... : append &generated_code code
  frame->slots[7] /* temp__1 */ = create_closure(entry__7_490, 0);
  // 635: push &actions: append &generated_code code
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[7] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__7_492;
}
static void entry__7_490(void) {
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
  // 635: ... append &generated_code code
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_code */;
  arguments->slots[1] = frame->slots[1] /* code */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__7_491;
}
static void cont__7_491(void) {
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
static void cont__7_492(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__actions(arguments->slots[0]);
  // 636: push &all_actions actions
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* all_actions */;
  arguments->slots[1] = get__actions();
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__7_493;
}
static void cont__7_493(void) {
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
static void cont__7_494(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 637: ... :
  // 638:   %%sim2c::actions empty_list
  // 639:   collect_output $code:
  // 640:     if
  // 641:       is_main:
  // 642:         write "
  // 643:             terminate(0); // should never be reached
  // 644:           }
  // 645:       :
  // 646:         write "
  // ...
  frame->slots[33] /* temp__1 */ = create_closure(entry__7_495, 0);
  // 637: do:
  // 638:   %%sim2c::actions empty_list
  // 639:   collect_output $code:
  // 640:     if
  // 641:       is_main:
  // 642:         write "
  // 643:             terminate(0); // should never be reached
  // 644:           }
  // 645:       :
  // 646:         write "
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[33] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__7_507;
}
static void entry__7_495(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // return__8: 0
  // is_main: 1
  // generated_code: 2
  // all_actions: 3
  // code: 4
  frame->slots[0] /* return__8 */ = create_continuation();
  frame->slots[1] = myself->closure.frame->slots[1]; /* is_main */
  frame->slots[2] = myself->closure.frame->slots[27]; /* generated_code */
  frame->slots[3] = myself->closure.frame->slots[8]; /* all_actions */
  define__sim2c__actions(undefined);
  frame->slots[4] /* code */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 638: %%sim2c::actions empty_list
  set__sim2c__actions(get__empty_list());
  // 639: ... :
  // 640:   if
  // 641:     is_main:
  // 642:       write "
  // 643:           terminate(0); // should never be reached
  // 644:         }
  // 645:     :
  // 646:       write "
  // 647:           frame = frame->caller_frame;
  // 648:           func = frame->cont;
  // ...
  frame->slots[5] /* temp__1 */ = create_closure(entry__7_496, 0);
  // 639: collect_output $code:
  // 640:   if
  // 641:     is_main:
  // 642:       write "
  // 643:           terminate(0); // should never be reached
  // 644:         }
  // 645:     :
  // 646:       write "
  // 647:           frame = frame->caller_frame;
  // 648:           func = frame->cont;
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__7_502;
}
static void entry__7_496(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // is_main: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* is_main */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 640: if
  // 641:   is_main:
  // 642:     write "
  // 643:         terminate(0); // should never be reached
  // 644:       }
  // 645:   :
  // 646:     write "
  // 647:         frame = frame->caller_frame;
  // 648:         func = frame->cont;
  // 649:         frame->cont = invalid_continuation;
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* is_main */;
  arguments->slots[1] = func__7_497;
  arguments->slots[2] = func__7_499;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_501;
}
static void entry__7_497(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 642: write "
  // 643:     terminate(0); // should never be reached
  // 644:   }
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_498;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_499(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 646: write "
  // 647:     frame = frame->caller_frame;
  // 648:     func = frame->cont;
  // 649:     frame->cont = invalid_continuation;
  // 650:   }
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_500;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_501(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 651: end_continuation
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__end_continuation();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_502(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* code */, arguments->slots[0]);
  // 652: ... : append &generated_code code
  frame->slots[5] /* temp__1 */ = create_closure(entry__7_503, 0);
  // 652: push &actions: append &generated_code code
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__7_505;
}
static void entry__7_503(void) {
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
  // 652: ... append &generated_code code
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_code */;
  arguments->slots[1] = frame->slots[1] /* code */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__7_504;
}
static void cont__7_504(void) {
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
static void cont__7_505(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__actions(arguments->slots[0]);
  // 653: push &all_actions actions
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* all_actions */;
  arguments->slots[1] = get__actions();
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__7_506;
}
static void cont__7_506(void) {
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
static void cont__7_507(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 654: for_each all_actions: (stmt_actions) for_each stmt_actions: (action) action
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[8])->contents /* all_actions */;
  arguments->slots[1] = func__7_508;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__7_510;
}
static void entry__7_509(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // action: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 654: ... action
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* action */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_508(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // stmt_actions: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 654: ... for_each stmt_actions: (action) action
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stmt_actions */;
  arguments->slots[1] = func__7_509;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_510(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 655: for_each required_modules: (name _info) writeln "/// require @(name)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__required_modules();
  arguments->slots[1] = func__7_511;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__7_514;
}
static void entry__7_511(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // name: 0
  // info: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 655: ... "/// require @(name)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7_512;
  arguments->slots[1] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_513;
}
static void cont__7_513(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 655: ... writeln "/// require @(name)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_514(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 656: for_each linked_libraries: (name) writeln "/// link @(name)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__linked_libraries();
  arguments->slots[1] = func__7_515;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__7_518;
}
static void entry__7_515(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // name: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 656: ... "/// link @(name)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7_516;
  arguments->slots[1] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_517;
}
static void cont__7_517(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 656: ... writeln "/// link @(name)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_518(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 657: for_each dependent_data: (filemask) writeln "/// data @(filemask)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__dependent_data();
  arguments->slots[1] = func__7_519;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__7_522;
}
static void entry__7_519(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // filemask: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 657: ... "/// data @(filemask)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7_520;
  arguments->slots[1] = frame->slots[0] /* filemask */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_521;
}
static void cont__7_521(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 657: ... writeln "/// data @(filemask)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_522(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 658: ... required_modules.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__required_modules();
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__7_523;
}
static void cont__7_523(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[33] /* temp__1 */ = arguments->slots[0];
  // 658: unless required_modules.is_empty writeln
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[33] /* temp__1 */;
  arguments->slots[1] = get__writeln();
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__7_524;
}
static void cont__7_524(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 659: if use_inline_c:
  // 660:   !included_files("stdint.h") true
  // 661:   !included_files("stdlib.h") true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__use_inline_c();
  arguments->slots[1] = func__7_525;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_530;
}
static void entry__7_525(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 660: !included_files("stdint.h") true
  frame->slots[0] /* temp__1 */ = get__true();
  // 660: !included_files("stdint.h")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7_526;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
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
  set__included_files(arguments->slots[0]);
  // 661: !included_files("stdlib.h") true
  frame->slots[0] /* temp__1 */ = get__true();
  // 661: !included_files("stdlib.h")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7_528;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__included_files();
  func = myself->type;
  frame->cont = cont__7_529;
}
static void cont__7_529(void) {
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
static void cont__7_530(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 662: for_each included_files: (name) writeln "#include <@(name)>"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__included_files();
  arguments->slots[1] = func__7_531;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__7_535;
}
static void entry__7_531(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // name: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 662: ... "#include <@(name)>"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_532;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__7_533;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_534;
}
static void cont__7_534(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 662: ... writeln "#include <@(name)>"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_535(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 663: write "
  // 664:   /**********************
  // 665:   D E C L A R A T I O N S
  // 666:   **********************/
  // 667:   
  // 668:   #ifndef IMPORT
  // 669:     #define IMPORT extern
  // 670:   #endif
  // 671:   
  // 672:   #ifndef EXPORT
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_536;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_537;
}
static void cont__7_537(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 681: ... included_files("stdint.h")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_538;
  result_count = 1;
  myself = get__included_files();
  func = myself->type;
  frame->cont = cont__7_539;
}
static void cont__7_539(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[33] /* temp__1 */ = arguments->slots[0];
  // 681: unless included_files("stdint.h"):
  // 682:   write "
  // 683:     typedef __INT8_TYPE__ int8_t;
  // 684:     typedef __INT16_TYPE__ int16_t;
  // 685:     typedef __INT32_TYPE__ int32_t;
  // 686:     typedef __INT64_TYPE__ int64_t;
  // 687:     typedef __INTPTR_TYPE__ intptr_t;
  // 688:     
  // 689:     #ifdef __UINT8_TYPE__
  // 690:       typedef __UINT8_TYPE__ uint8_t;
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[33] /* temp__1 */;
  arguments->slots[1] = func__7_540;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__7_542;
}
static void entry__7_540(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 682: write "
  // 683:   typedef __INT8_TYPE__ int8_t;
  // 684:   typedef __INT16_TYPE__ int16_t;
  // 685:   typedef __INT32_TYPE__ int32_t;
  // 686:   typedef __INT64_TYPE__ int64_t;
  // 687:   typedef __INTPTR_TYPE__ intptr_t;
  // 688:   
  // 689:   #ifdef __UINT8_TYPE__
  // 690:     typedef __UINT8_TYPE__ uint8_t;
  // 691:   #else
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_541;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_542(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 718: ... included_files("stdlib.h")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_543;
  result_count = 1;
  myself = get__included_files();
  func = myself->type;
  frame->cont = cont__7_544;
}
static void cont__7_544(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[34] /* temp__2 */ = arguments->slots[0];
  // 718: ... included_files("stdlib.h") || included_files("stddef.h")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[34] /* temp__2 */;
  arguments->slots[1] = func__7_545;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__7_548;
}
static void entry__7_545(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 718: ... included_files("stddef.h")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_546;
  result_count = 1;
  myself = get__included_files();
  func = myself->type;
  frame->cont = cont__7_547;
}
static void cont__7_547(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 718: ... included_files("stddef.h")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__7_548(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[33] /* temp__1 */ = arguments->slots[0];
  // 718: unless included_files("stdlib.h") || included_files("stddef.h"):
  // 719:   write "
  // 720:     typedef __SIZE_TYPE__ size_t;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[33] /* temp__1 */;
  arguments->slots[1] = func__7_549;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__7_551;
}
static void entry__7_549(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 719: write "
  // 720:   typedef __SIZE_TYPE__ size_t;
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_550;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_551(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 721: write "
  // 722:   // INSERT HERE //
  // 723:   
  // 724:   #if UINTPTR_MAX == 0xffffffffffffffff
  // 725:     #define FIRST_INVALID_ADDRESS 0xc000000000000000UL
  // 726:     #define SAMPLE_POINTER ((void *)0x123456789abcdef0UL)
  // 727:   #else
  // 728:     #define FIRST_INVALID_ADDRESS 0xc0000000
  // 729:     #define SAMPLE_POINTER ((void *)0x12345678)
  // 730:   #endif
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_552;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_553;
}
static void cont__7_553(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 765: for_each needed_names: (name info)
  // 766:   if variable_kind_of(info) == POLYMORPHIC:
  // 767:     writeln "static int poly_idx__@(name);"
  // 768:   writeln "static NODE_GETTER get__@(name);"
  // 769:   if variable_kind_of(info) == STATIC_SINGLE:
  // 770:     writeln "static NODE_GETTER get_value_or_future__@(name);"
  // 771:   case variable_kind_of(info) STATIC_MULTI, DYNAMIC_MULTI:
  // 772:     writeln "static NODE_SETTER set__@(name);"
  // 773:   case variable_kind_of(info) DYNAMIC_SINGLE, DYNAMIC_MULTI:
  // 774:     writeln "static NODE_SETTER define__@(name);"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__needed_names();
  arguments->slots[1] = func__7_554;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__7_586;
}
static void entry__7_582(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 774: ... "static NODE_SETTER define__@(name);"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_583;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__7_584;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_585;
}
static void cont__7_585(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 774: writeln "static NODE_SETTER define__@(name);"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_554(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // name: 0
  // info: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 766: ... variable_kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__variable_kind_of();
  func = myself->type;
  frame->cont = cont__7_555;
}
static void cont__7_555(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 766: ... variable_kind_of(info) == POLYMORPHIC
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = get__POLYMORPHIC();
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__7_556;
}
static void cont__7_556(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 766: ... :
  // 767:   writeln "static int poly_idx__@(name);"
  frame->slots[4] /* temp__3 */ = create_closure(entry__7_557, 0);
  // 766: if variable_kind_of(info) == POLYMORPHIC:
  // 767:   writeln "static int poly_idx__@(name);"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_561;
}
static void entry__7_557(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 767: ... "static int poly_idx__@(name);"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_558;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__7_559;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_560;
}
static void cont__7_560(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 767: writeln "static int poly_idx__@(name);"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_561(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 768: ... "static NODE_GETTER get__@(name);"
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
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 768: writeln "static NODE_GETTER get__@(name);"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__writeln();
  func = myself->type;
  frame->cont = cont__7_565;
}
static void cont__7_565(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 769: ... variable_kind_of(info)
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
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 769: ... variable_kind_of(info) == STATIC_SINGLE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = get__STATIC_SINGLE();
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__7_567;
}
static void cont__7_567(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 769: ... :
  // 770:   writeln "static NODE_GETTER get_value_or_future__@(name);"
  frame->slots[4] /* temp__3 */ = create_closure(entry__7_568, 0);
  // 769: if variable_kind_of(info) == STATIC_SINGLE:
  // 770:   writeln "static NODE_GETTER get_value_or_future__@(name);"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 0;
  myself = get__if();
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
  // 770: ... "static NODE_GETTER get_value_or_future__@(name);"
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
  // 770: writeln "static NODE_GETTER get_value_or_future__@(name);"
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
  // 771: ... variable_kind_of(info)
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
  // 771: ... STATIC_MULTI, DYNAMIC_MULTI
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__STATIC_MULTI();
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
  // 771: ... :
  // 772:   writeln "static NODE_SETTER set__@(name);"
  frame->slots[4] /* temp__3 */ = create_closure(entry__7_575, 0);
  // 771: case variable_kind_of(info) STATIC_MULTI, DYNAMIC_MULTI:
  // 772:   writeln "static NODE_SETTER set__@(name);"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = frame->slots[4] /* temp__3 */;
  result_count = 0;
  myself = get__case();
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
  // 772: ... "static NODE_SETTER set__@(name);"
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
  // 772: writeln "static NODE_SETTER set__@(name);"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_579(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 773: ... variable_kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__variable_kind_of();
  func = myself->type;
  frame->cont = cont__7_580;
}
static void cont__7_580(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 773: ... DYNAMIC_SINGLE, DYNAMIC_MULTI
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__DYNAMIC_SINGLE();
  arguments->slots[1] = get__DYNAMIC_MULTI();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__7_581;
}
static void cont__7_581(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 773: ... :
  // 774:   writeln "static NODE_SETTER define__@(name);"
  frame->slots[4] /* temp__3 */ = create_closure(entry__7_582, 0);
  // 773: case variable_kind_of(info) DYNAMIC_SINGLE, DYNAMIC_MULTI:
  // 774:   writeln "static NODE_SETTER define__@(name);"
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
static void cont__7_586(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 775: write "
  // 776:   static struct {
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_587;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_588;
}
static void cont__7_588(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 777: write generated_top_level_variable_declarations
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[16])->contents /* generated_top_level_variable_declarations */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_589;
}
static void cont__7_589(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 778: write generated_global_variable_declarations
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[17])->contents /* generated_global_variable_declarations */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_590;
}
static void cont__7_590(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 779: write "
  // 780:   } var;
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_591;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_592;
}
static void cont__7_592(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 781: write "
  // 782:   static const char *var_names[] = {
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_593;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_594;
}
static void cont__7_594(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 783: ... generated_top_level_variable_names != ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[15])->contents /* generated_top_level_variable_names */;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__7_595;
}
static void cont__7_595(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[34] /* temp__2 */ = arguments->slots[0];
  // 783: ... generated_top_level_variable_names != ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[34] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__7_596;
}
static void cont__7_596(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[33] /* temp__1 */ = arguments->slots[0];
  // 783: ... :
  // 784:   writeln range(generated_top_level_variable_names 1 -3)
  frame->slots[35] /* temp__3 */ = create_closure(entry__7_597, 0);
  // 783: if generated_top_level_variable_names != "":
  // 784:   writeln range(generated_top_level_variable_names 1 -3)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[33] /* temp__1 */;
  arguments->slots[1] = frame->slots[35] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_600;
}
static void entry__7_597(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // generated_top_level_variable_names: 0
  frame->slots[0] = myself->closure.frame->slots[15]; /* generated_top_level_variable_names */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 784: ... 3
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__3;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__7_598;
}
static void cont__7_598(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 784: ... range(generated_top_level_variable_names 1 -3)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_top_level_variable_names */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__7_599;
}
static void cont__7_599(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 784: writeln range(generated_top_level_variable_names 1 -3)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_600(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 785: write "};@nl;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_601;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_602;
}
static void cont__7_602(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 786: write generated_declarations
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[14])->contents /* generated_declarations */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_603;
}
static void cont__7_603(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 794: if
  // 795:   is_main:
  // 796:     writeln "static void main_entry(void);"
  // 797:   :
  // 798:     writeln "void run__@(module_name)(void);"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* is_main */;
  arguments->slots[1] = func__7_604;
  arguments->slots[2] = func__7_606;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_610;
}
static void entry__7_604(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 796: writeln "static void main_entry(void);"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_605;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_606(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 798: ... "void run__@(module_name)(void);"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_607;
  arguments->slots[1] = get__module_name();
  arguments->slots[2] = string__7_608;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_609;
}
static void cont__7_609(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 798: writeln "void run__@(module_name)(void);"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_610(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 799: write "
  // 800:   
  // 801:   static CONTINUATION_INFO continuation_info[] = {
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_611;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_612;
}
static void cont__7_612(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 802: append &generated_continuation_table generated_delayed_continuation_table
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[18])->contents /* generated_continuation_table */;
  arguments->slots[1] = ((CELL *)frame->slots[19])->contents /* generated_delayed_continuation_table */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__7_613;
}
static void cont__7_613(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[18])->contents /* generated_continuation_table */ = arguments->slots[0];
  // 803: ... generated_continuation_table != ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[18])->contents /* generated_continuation_table */;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__7_614;
}
static void cont__7_614(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[34] /* temp__2 */ = arguments->slots[0];
  // 803: ... generated_continuation_table != ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[34] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__7_615;
}
static void cont__7_615(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[33] /* temp__1 */ = arguments->slots[0];
  // 803: ... :
  // 804:   writeln range(generated_continuation_table 1 -3)
  frame->slots[35] /* temp__3 */ = create_closure(entry__7_616, 0);
  // 803: if generated_continuation_table != "":
  // 804:   writeln range(generated_continuation_table 1 -3)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[33] /* temp__1 */;
  arguments->slots[1] = frame->slots[35] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_619;
}
static void entry__7_616(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // generated_continuation_table: 0
  frame->slots[0] = myself->closure.frame->slots[18]; /* generated_continuation_table */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 804: ... 3
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__3;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__7_617;
}
static void cont__7_617(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 804: ... range(generated_continuation_table 1 -3)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_continuation_table */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__7_618;
}
static void cont__7_618(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 804: writeln range(generated_continuation_table 1 -3)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_619(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 805: write "
  // 806:   };
  // 807:   @;
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_620;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_621;
}
static void cont__7_621(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 808: write "
  // 809:   union NODE {
  // 810:     struct {
  // 811:       FUNC type;
  // 812:       ATTRIBUTES *attributes;
  // 813:     };
  // 814:     CONTINUATION continuation;
  // 815:     CLOSURE closure;
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_622;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_623;
}
static void cont__7_623(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 816: if use_inline_c:
  // 817:   for_each defined_nodes: (name _node)
  // 818:     write "  @(name) @(name.to_lower_case);@nl;"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__use_inline_c();
  arguments->slots[1] = func__7_624;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_631;
}
static void entry__7_625(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // name: 0
  // node: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 818: ... name.to_lower_case
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__to_lower_case();
  func = myself->type;
  frame->cont = cont__7_626;
}
static void cont__7_626(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 818: ... "  @(name) @(name.to_lower_case);@nl;"
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__7_627;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__7_628;
  arguments->slots[3] = frame->slots[3] /* temp__2 */;
  arguments->slots[4] = string__7_629;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_630;
}
static void cont__7_630(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 818: write "  @(name) @(name.to_lower_case);@nl;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_624(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 817: for_each defined_nodes: (name _node)
  // 818:   write "  @(name) @(name.to_lower_case);@nl;"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__defined_nodes();
  arguments->slots[1] = func__7_625;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_631(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 819: write "};@nl;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_632;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_633;
}
static void cont__7_633(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 820: write generated_functions
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[20])->contents /* generated_functions */;
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
  // 821: for_each used_literals: (name _literal) write "static NODE *@(name);@nl;"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[30])->contents /* used_literals */;
  arguments->slots[1] = func__7_635;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__7_639;
}
static void entry__7_635(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // name: 0
  // literal: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 821: ... "static NODE *@(name);@nl;"
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
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 821: ... write "static NODE *@(name);@nl;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
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
  // 822: write "
  // 823:   
  // 824:   static const char *used_namespaces[] = {
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_640;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_641;
}
static void cont__7_641(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 825: for_each used_namespaces: (name) write "  @quot;@(name)@quot;,@nl;"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__used_namespaces();
  arguments->slots[1] = func__7_642;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__7_646;
}
static void entry__7_642(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // name: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 825: ... "  @quot;@(name)@quot;,@nl;"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_643;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__7_644;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_645;
}
static void cont__7_645(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 825: ... write "  @quot;@(name)@quot;,@nl;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_646(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 826: ... "
  // 827:     NULL
  // 828:   };
  // 829:   
  // 830:   static MODULE_INFO module_info = {
  // 831:     NULL,
  // 832:     "@(module_name)",
  // 833:     continuation_info,
  // 834:     sizeof(continuation_info)/sizeof(CONTINUATION_INFO),
  // 835:     (NODE **)&var,
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_647;
  arguments->slots[1] = get__module_name();
  arguments->slots[2] = string__7_648;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_649;
}
static void cont__7_649(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[33] /* temp__1 */ = arguments->slots[0];
  // 826: write "
  // 827:     NULL
  // 828:   };
  // 829:   
  // 830:   static MODULE_INFO module_info = {
  // 831:     NULL,
  // 832:     "@(module_name)",
  // 833:     continuation_info,
  // 834:     sizeof(continuation_info)/sizeof(CONTINUATION_INFO),
  // 835:     (NODE **)&var,
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[33] /* temp__1 */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_650;
}
static void cont__7_650(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 840: $depth count_occurrences(module_name "__")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__module_name();
  arguments->slots[1] = string__7_651;
  result_count = 1;
  myself = get__count_occurrences();
  func = myself->type;
  frame->cont = cont__7_652;
}
static void cont__7_652(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[32] /* depth */, arguments->slots[0]);
  // 842: ... : ($filename)
  // 843:   truncate_until &filename '/' -(depth+1)
  // 844:   write "
  // 845:     DEBUG_FILENAME("@(filename)@quot;)@
  frame->slots[33] /* temp__1 */ = create_closure(entry__7_653, 1);
  // 841: for_each
  // 842:   filenames: ($filename)
  // 843:     truncate_until &filename '/' -(depth+1)
  // 844:     write "
  // 845:       DEBUG_FILENAME("@(filename)@quot;)@
  // 846:   :
  // 847:     write ", "
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filenames */;
  arguments->slots[1] = frame->slots[33] /* temp__1 */;
  arguments->slots[2] = func__7_660;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__7_662;
}
static void entry__7_653(void) {
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
  // 843: ... depth+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* depth */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__7_654;
}
static void cont__7_654(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 843: ... depth+1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__7_655;
}
static void cont__7_655(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 843: truncate_until &filename '/' -(depth+1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* filename */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__7_656;
}
static void cont__7_656(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* filename */ = arguments->slots[0];
  // 844: ... "
  // 845:   DEBUG_FILENAME("@(filename)@quot;)@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_657;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* filename */;
  arguments->slots[2] = string__7_658;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_659;
}
static void cont__7_659(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 844: write "
  // 845:   DEBUG_FILENAME("@(filename)@quot;)@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_660(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 847: write ", "
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_661;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_662(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 848: write "
  // 849:   }
  // 850:   };
  // 851:   
  // 852:   /******
  // 853:   C O D E
  // 854:   ******/
  // 855:   @;
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_663;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_664;
}
static void cont__7_664(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 856: ... : (name _info)
  // 857:   $fname mangle_filename(name)
  // 858:   write "
  // 859:     IMPORT void collect__@(fname)(void);
  // 860:     IMPORT void phase_1__@(fname)(void);
  // 861:     IMPORT void phase_2__@(fname)(void);
  // 862:     IMPORT void phase_3__@(fname)(void);
  // 863:     IMPORT void phase_4__@(fname)(void);
  // 864:     IMPORT void phase_5__@(fname)(void);
  // 865:     IMPORT void phase_6__@(fname)(void);
  // ...
  frame->slots[33] /* temp__1 */ = create_closure(entry__7_665, 2);
  // 856: for_each required_modules: (name _info)
  // 857:   $fname mangle_filename(name)
  // 858:   write "
  // 859:     IMPORT void collect__@(fname)(void);
  // 860:     IMPORT void phase_1__@(fname)(void);
  // 861:     IMPORT void phase_2__@(fname)(void);
  // 862:     IMPORT void phase_3__@(fname)(void);
  // 863:     IMPORT void phase_4__@(fname)(void);
  // 864:     IMPORT void phase_5__@(fname)(void);
  // 865:     IMPORT void phase_6__@(fname)(void);
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__required_modules();
  arguments->slots[1] = frame->slots[33] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__7_677;
}
static void entry__7_665(void) {
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
  // 857: $fname mangle_filename(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = frame->slots[2] /* mangle_filename */;
  func = myself->type;
  frame->cont = cont__7_666;
}
static void cont__7_666(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* fname */, arguments->slots[0]);
  // 858: ... "
  // 859:   IMPORT void collect__@(fname)(void);
  // 860:   IMPORT void phase_1__@(fname)(void);
  // 861:   IMPORT void phase_2__@(fname)(void);
  // 862:   IMPORT void phase_3__@(fname)(void);
  // 863:   IMPORT void phase_4__@(fname)(void);
  // 864:   IMPORT void phase_5__@(fname)(void);
  // 865:   IMPORT void phase_6__@(fname)(void);
  // 866:   IMPORT void run__@(fname)(void);
  argument_count = 17;
  arguments = node_p;
  arguments->slots[0] = string__7_667;
  arguments->slots[1] = frame->slots[3] /* fname */;
  arguments->slots[2] = string__7_668;
  arguments->slots[3] = frame->slots[3] /* fname */;
  arguments->slots[4] = string__7_669;
  arguments->slots[5] = frame->slots[3] /* fname */;
  arguments->slots[6] = string__7_670;
  arguments->slots[7] = frame->slots[3] /* fname */;
  arguments->slots[8] = string__7_671;
  arguments->slots[9] = frame->slots[3] /* fname */;
  arguments->slots[10] = string__7_672;
  arguments->slots[11] = frame->slots[3] /* fname */;
  arguments->slots[12] = string__7_673;
  arguments->slots[13] = frame->slots[3] /* fname */;
  arguments->slots[14] = string__7_674;
  arguments->slots[15] = frame->slots[3] /* fname */;
  arguments->slots[16] = string__7_675;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_676;
}
static void cont__7_676(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 858: write "
  // 859:   IMPORT void collect__@(fname)(void);
  // 860:   IMPORT void phase_1__@(fname)(void);
  // 861:   IMPORT void phase_2__@(fname)(void);
  // 862:   IMPORT void phase_3__@(fname)(void);
  // 863:   IMPORT void phase_4__@(fname)(void);
  // 864:   IMPORT void phase_5__@(fname)(void);
  // 865:   IMPORT void phase_6__@(fname)(void);
  // 866:   IMPORT void run__@(fname)(void);
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_677(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 867: write generated_code
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[27])->contents /* generated_code */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_678;
}
static void cont__7_678(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 868: write delayed_statements
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[29])->contents /* delayed_statements */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_679;
}
static void cont__7_679(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 869: ... "
  // 870:   EXPORT void collect__@(module_name)(void) {
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_680;
  arguments->slots[1] = get__module_name();
  arguments->slots[2] = string__7_681;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_682;
}
static void cont__7_682(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[33] /* temp__1 */ = arguments->slots[0];
  // 869: write "
  // 870:   EXPORT void collect__@(module_name)(void) {
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[33] /* temp__1 */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_683;
}
static void cont__7_683(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 871: write generated_collections
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[28])->contents /* generated_collections */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_684;
}
static void cont__7_684(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 874: write "}@nl;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_685;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_686;
}
static void cont__7_686(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 875: if
  // 876:   is_main:
  // 877:     write "
  // 878:       
  // 879:       int main(int argc, char **argv) {
  // 880:         main_argc = argc;
  // 881:         main_argv = argv;
  // 882:         initialize_runtime();
  // 883:       
  // 884:         // initialization phase 1
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* is_main */;
  arguments->slots[1] = func__7_687;
  arguments->slots[2] = func__7_689;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_693;
}
static void entry__7_687(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 877: write "
  // 878:   
  // 879:   int main(int argc, char **argv) {
  // 880:     main_argc = argc;
  // 881:     main_argv = argv;
  // 882:     initialize_runtime();
  // 883:   
  // 884:     // initialization phase 1
  // 885:   @;
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_688;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_689(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 887: ... "
  // 888:   
  // 889:   static int already_run_phase_1 = false;
  // 890:   
  // 891:   EXPORT void phase_1__@(module_name)(void) {
  // 892:     if (already_run_phase_1) return;
  // 893:     already_run_phase_1 = true;
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_690;
  arguments->slots[1] = get__module_name();
  arguments->slots[2] = string__7_691;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_692;
}
static void cont__7_692(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 887: write "
  // 888:   
  // 889:   static int already_run_phase_1 = false;
  // 890:   
  // 891:   EXPORT void phase_1__@(module_name)(void) {
  // 892:     if (already_run_phase_1) return;
  // 893:     already_run_phase_1 = true;
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_693(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 894: ... : (name _info)
  // 895:   $mangled_name mangle_filename(name)
  // 896:   writeln "  phase_1__@(mangled_name)();"
  frame->slots[33] /* temp__1 */ = create_closure(entry__7_694, 2);
  // 894: for_each required_modules: (name _info)
  // 895:   $mangled_name mangle_filename(name)
  // 896:   writeln "  phase_1__@(mangled_name)();"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__required_modules();
  arguments->slots[1] = frame->slots[33] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__7_699;
}
static void entry__7_694(void) {
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
  // 895: $mangled_name mangle_filename(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = frame->slots[2] /* mangle_filename */;
  func = myself->type;
  frame->cont = cont__7_695;
}
static void cont__7_695(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* mangled_name */, arguments->slots[0]);
  // 896: ... "  phase_1__@(mangled_name)();"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_696;
  arguments->slots[1] = frame->slots[3] /* mangled_name */;
  arguments->slots[2] = string__7_697;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_698;
}
static void cont__7_698(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 896: writeln "  phase_1__@(mangled_name)();"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_699(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 897: write "
  // 898:   @
  // 899:     register_module_info(&module_info);
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_700;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_701;
}
static void cont__7_701(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 900: write generated_phase_1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[21])->contents /* generated_phase_1 */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_702;
}
static void cont__7_702(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 901: if
  // 902:   is_main:
  // 903:     write "
  // 904:       @
  // 905:       
  // 906:         // initialization phase 2
  // 907:   :
  // 908:     write "
  // 909:       }
  // 910:       
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* is_main */;
  arguments->slots[1] = func__7_703;
  arguments->slots[2] = func__7_705;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_709;
}
static void entry__7_703(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 903: write "
  // 904:   @
  // 905:   
  // 906:     // initialization phase 2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_704;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_705(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 908: ... "
  // 909:   }
  // 910:   
  // 911:   static int already_run_phase_2 = false;
  // 912:   
  // 913:   EXPORT void phase_2__@(module_name)(void) {
  // 914:     if (already_run_phase_2) return;
  // 915:     already_run_phase_2 = true;
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_706;
  arguments->slots[1] = get__module_name();
  arguments->slots[2] = string__7_707;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_708;
}
static void cont__7_708(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 908: write "
  // 909:   }
  // 910:   
  // 911:   static int already_run_phase_2 = false;
  // 912:   
  // 913:   EXPORT void phase_2__@(module_name)(void) {
  // 914:     if (already_run_phase_2) return;
  // 915:     already_run_phase_2 = true;
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_709(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 916: ... : (name _info)
  // 917:   writeln "  phase_2__@(mangle_filename(name))();"
  frame->slots[33] /* temp__1 */ = create_closure(entry__7_710, 2);
  // 916: for_each required_modules: (name _info)
  // 917:   writeln "  phase_2__@(mangle_filename(name))();"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__required_modules();
  arguments->slots[1] = frame->slots[33] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__7_715;
}
static void entry__7_710(void) {
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
  // 917: ... mangle_filename(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = frame->slots[2] /* mangle_filename */;
  func = myself->type;
  frame->cont = cont__7_711;
}
static void cont__7_711(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 917: ... "  phase_2__@(mangle_filename(name))();"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_712;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = string__7_713;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_714;
}
static void cont__7_714(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 917: writeln "  phase_2__@(mangle_filename(name))();"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_715(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 918: for_each used_literals: (name literal)
  // 919:   write "  @(name) = "
  // 920:   cond
  // 921:     -> literal.is_a_numeric_literal:
  // 922:       $value replace_all(node::value_of(literal) '@apos;' = "")
  // 923:       if
  // 924:         not(value .has_prefix. "0x") && value .contains. alt('.' 'e' 'E'):
  // 925:           write "from_double(@(value));@nl;"
  // 926:         :
  // 927:           $int_val value.to_integer
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[30])->contents /* used_literals */;
  arguments->slots[1] = func__7_716;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__7_766;
}
static void entry__7_760(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // literal: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* literal */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 939: ... node::value_of(literal)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* literal */;
  result_count = 1;
  myself = get__node__value_of();
  func = myself->type;
  frame->cont = cont__7_761;
}
static void cont__7_761(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 939: ... node::value_of(literal).to_integer
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__to_integer();
  func = myself->type;
  frame->cont = cont__7_762;
}
static void cont__7_762(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 939: ... "from_uchar32(@(node::value_of(literal).to_integer));"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_763;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  arguments->slots[2] = string__7_764;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_765;
}
static void cont__7_765(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 939: writeln "from_uchar32(@(node::value_of(literal).to_integer));"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_750(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // int_val: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* int_val */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 933: ... "
  // 934:   from_uint64(@(int_val)ULL);
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_751;
  arguments->slots[1] = frame->slots[0] /* int_val */;
  arguments->slots[2] = string__7_752;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_753;
}
static void cont__7_753(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 933: write "
  // 934:   from_uint64(@(int_val)ULL);
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_743(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // int_val: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* int_val */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 930: ... "
  // 931:   from_uint32(@(int_val)U);
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_744;
  arguments->slots[1] = frame->slots[0] /* int_val */;
  arguments->slots[2] = string__7_745;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_746;
}
static void cont__7_746(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 930: write "
  // 931:   from_uint32(@(int_val)U);
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_740(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // int_val: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* int_val */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 929: ... int_val <= 0xffffffff
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0xffffffff;
  arguments->slots[1] = frame->slots[0] /* int_val */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__7_741;
}
static void cont__7_741(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 929: ... int_val <= 0xffffffff
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__7_742;
}
static void cont__7_742(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 929: ... :
  // 930:   write "
  // 931:     from_uint32(@(int_val)U);
  frame->slots[3] /* temp__3 */ = create_closure(entry__7_743, 0);
  // 929: -> int_val <= 0xffffffff:
  // 930:   write "
  // 931:     from_uint32(@(int_val)U);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__7_747(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // int_val: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* int_val */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 932: ... int_val <= 0xffffffffffffffff
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0xffffffffffffffff;
  arguments->slots[1] = frame->slots[0] /* int_val */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__7_748;
}
static void cont__7_748(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 932: ... int_val <= 0xffffffffffffffff
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__7_749;
}
static void cont__7_749(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 932: ... :
  // 933:   write "
  // 934:     from_uint64(@(int_val)ULL);
  frame->slots[3] /* temp__3 */ = create_closure(entry__7_750, 0);
  // 932: -> int_val <= 0xffffffffffffffff:
  // 933:   write "
  // 934:     from_uint64(@(int_val)ULL);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__7_754(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // value: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 936: ... "
  // 937:   from_digit_string("@(value)");
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_755;
  arguments->slots[1] = frame->slots[0] /* value */;
  arguments->slots[2] = string__7_756;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_757;
}
static void cont__7_757(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 936: write "
  // 937:   from_digit_string("@(value)");
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_734(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // value: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 925: ... "from_double(@(value));@nl;"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_735;
  arguments->slots[1] = frame->slots[0] /* value */;
  arguments->slots[2] = string__7_736;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_737;
}
static void cont__7_737(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 925: write "from_double(@(value));@nl;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_738(void) {
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
  // 927: $int_val value.to_integer
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* value */;
  result_count = 1;
  myself = get__to_integer();
  func = myself->type;
  frame->cont = cont__7_739;
}
static void cont__7_739(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* int_val */, arguments->slots[0]);
  // 929: -> int_val <= 0xffffffff:
  // 930:   write "
  // 931:     from_uint32(@(int_val)U);
  frame->slots[2] /* temp__1 */ = create_closure(entry__7_740, 0);
  // 932: -> int_val <= 0xffffffffffffffff:
  // 933:   write "
  // 934:     from_uint64(@(int_val)ULL);
  frame->slots[3] /* temp__2 */ = create_closure(entry__7_747, 0);
  // 935: :
  // 936:   write "
  // 937:     from_digit_string("@(value)");
  frame->slots[4] /* temp__3 */ = create_closure(entry__7_754, 0);
  // 928: cond
  // 929:   -> int_val <= 0xffffffff:
  // 930:     write "
  // 931:       from_uint32(@(int_val)U);
  // 932:   -> int_val <= 0xffffffffffffffff:
  // 933:     write "
  // 934:       from_uint64(@(int_val)ULL);
  // 935:   :
  // 936:     write "
  // 937:       from_digit_string("@(value)");
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
static void entry__7_723(void) {
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
  // 922: ... node::value_of(literal)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* literal */;
  result_count = 1;
  myself = get__node__value_of();
  func = myself->type;
  frame->cont = cont__7_724;
}
static void cont__7_724(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 922: ... '@apos;' = ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__39;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__7_725;
}
static void cont__7_725(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 922: $value replace_all(node::value_of(literal) '@apos;' = "")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__7_726;
}
static void cont__7_726(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* value */, arguments->slots[0]);
  // 924: ... value .has_prefix. "0x"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* value */;
  arguments->slots[1] = string__7_727;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__7_728;
}
static void cont__7_728(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 924: not(value .has_prefix. "0x")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__not();
  func = myself->type;
  frame->cont = cont__7_729;
}
static void cont__7_729(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 924: ... value .contains. alt('.' 'e' 'E')
  frame->slots[5] /* temp__4 */ = create_closure(entry__7_730, 0);
  // 924: not(value .has_prefix. "0x") && value .contains. alt('.' 'e' 'E')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__7_733;
}
static void entry__7_730(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // value: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 924: ... alt('.' 'e' 'E')
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__46;
  arguments->slots[1] = character__101;
  arguments->slots[2] = character__69;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__7_731;
}
static void cont__7_731(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 924: ... value .contains. alt('.' 'e' 'E')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* value */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__7_732;
}
static void cont__7_732(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 924: ... value .contains. alt('.' 'e' 'E')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__7_733(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 924: ... :
  // 925:   write "from_double(@(value));@nl;"
  frame->slots[6] /* temp__5 */ = create_closure(entry__7_734, 0);
  // 926: :
  // 927:   $int_val value.to_integer
  // 928:   cond
  // 929:     -> int_val <= 0xffffffff:
  // 930:       write "
  // 931:         from_uint32(@(int_val)U);
  // 932:     -> int_val <= 0xffffffffffffffff:
  // 933:       write "
  // 934:         from_uint64(@(int_val)ULL);
  // 935:     :
  // ...
  frame->slots[7] /* temp__6 */ = create_closure(entry__7_738, 0);
  // 923: if
  // 924:   not(value .has_prefix. "0x") && value .contains. alt('.' 'e' 'E'):
  // 925:     write "from_double(@(value));@nl;"
  // 926:   :
  // 927:     $int_val value.to_integer
  // 928:     cond
  // 929:       -> int_val <= 0xffffffff:
  // 930:         write "
  // 931:           from_uint32(@(int_val)U);
  // 932:       -> int_val <= 0xffffffffffffffff:
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
static void entry__7_721(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // literal: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* literal */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 921: ... literal.is_a_numeric_literal
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* literal */;
  result_count = 1;
  myself = get__is_a_numeric_literal();
  func = myself->type;
  frame->cont = cont__7_722;
}
static void cont__7_722(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 921: ... :
  // 922:   $value replace_all(node::value_of(literal) '@apos;' = "")
  // 923:   if
  // 924:     not(value .has_prefix. "0x") && value .contains. alt('.' 'e' 'E'):
  // 925:       write "from_double(@(value));@nl;"
  // 926:     :
  // 927:       $int_val value.to_integer
  // 928:       cond
  // 929:         -> int_val <= 0xffffffff:
  // 930:           write "
  // ...
  frame->slots[2] /* temp__2 */ = create_closure(entry__7_723, 0);
  // 921: -> literal.is_a_numeric_literal:
  // 922:   $value replace_all(node::value_of(literal) '@apos;' = "")
  // 923:   if
  // 924:     not(value .has_prefix. "0x") && value .contains. alt('.' 'e' 'E'):
  // 925:       write "from_double(@(value));@nl;"
  // 926:     :
  // 927:       $int_val value.to_integer
  // 928:       cond
  // 929:         -> int_val <= 0xffffffff:
  // 930:           write "
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__7_758(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // literal: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* literal */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 938: ... literal.is_a_character_literal
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* literal */;
  result_count = 1;
  myself = get__is_a_character_literal();
  func = myself->type;
  frame->cont = cont__7_759;
}
static void cont__7_759(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 938: ... :
  // 939:   writeln "from_uchar32(@(node::value_of(literal).to_integer));"
  frame->slots[2] /* temp__2 */ = create_closure(entry__7_760, 0);
  // 938: -> literal.is_a_character_literal:
  // 939:   writeln "from_uchar32(@(node::value_of(literal).to_integer));"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__7_716(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // name: 0
  // literal: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 919: ... "  @(name) = "
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_717;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__7_718;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_719;
}
static void cont__7_719(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 919: write "  @(name) = "
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_720;
}
static void cont__7_720(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 921: -> literal.is_a_numeric_literal:
  // 922:   $value replace_all(node::value_of(literal) '@apos;' = "")
  // 923:   if
  // 924:     not(value .has_prefix. "0x") && value .contains. alt('.' 'e' 'E'):
  // 925:       write "from_double(@(value));@nl;"
  // 926:     :
  // 927:       $int_val value.to_integer
  // 928:       cond
  // 929:         -> int_val <= 0xffffffff:
  // 930:           write "
  // ...
  frame->slots[2] /* temp__1 */ = create_closure(entry__7_721, 0);
  // 938: -> literal.is_a_character_literal:
  // 939:   writeln "from_uchar32(@(node::value_of(literal).to_integer));"
  frame->slots[3] /* temp__2 */ = create_closure(entry__7_758, 0);
  // 920: cond
  // 921:   -> literal.is_a_numeric_literal:
  // 922:     $value replace_all(node::value_of(literal) '@apos;' = "")
  // 923:     if
  // 924:       not(value .has_prefix. "0x") && value .contains. alt('.' 'e' 'E'):
  // 925:         write "from_double(@(value));@nl;"
  // 926:       :
  // 927:         $int_val value.to_integer
  // 928:         cond
  // 929:           -> int_val <= 0xffffffff:
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
static void cont__7_766(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 940: write generated_phase_2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[22])->contents /* generated_phase_2 */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_767;
}
static void cont__7_767(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 941: if
  // 942:   is_main:
  // 943:     write "
  // 944:       @
  // 945:       
  // 946:         // initialization phase 3
  // 947:       
  // 948:         initialize_phase_3();
  // 949:         resolve_symbols();
  // 950:   :
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* is_main */;
  arguments->slots[1] = func__7_768;
  arguments->slots[2] = func__7_770;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_774;
}
static void entry__7_768(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 943: write "
  // 944:   @
  // 945:   
  // 946:     // initialization phase 3
  // 947:   
  // 948:     initialize_phase_3();
  // 949:     resolve_symbols();
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_769;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_770(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 951: ... "
  // 952:   }
  // 953:   
  // 954:   static int already_run_phase_3 = false;
  // 955:   
  // 956:   EXPORT void phase_3__@(module_name)(void) {
  // 957:     if (already_run_phase_3) return;
  // 958:     already_run_phase_3 = true;
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_771;
  arguments->slots[1] = get__module_name();
  arguments->slots[2] = string__7_772;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_773;
}
static void cont__7_773(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 951: write "
  // 952:   }
  // 953:   
  // 954:   static int already_run_phase_3 = false;
  // 955:   
  // 956:   EXPORT void phase_3__@(module_name)(void) {
  // 957:     if (already_run_phase_3) return;
  // 958:     already_run_phase_3 = true;
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_774(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 959: ... : (name _info)
  // 960:   writeln "  phase_3__@(mangle_filename(name))();"
  frame->slots[33] /* temp__1 */ = create_closure(entry__7_775, 2);
  // 959: for_each required_modules: (name _info)
  // 960:   writeln "  phase_3__@(mangle_filename(name))();"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__required_modules();
  arguments->slots[1] = frame->slots[33] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__7_780;
}
static void entry__7_775(void) {
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
  // 960: ... mangle_filename(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = frame->slots[2] /* mangle_filename */;
  func = myself->type;
  frame->cont = cont__7_776;
}
static void cont__7_776(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 960: ... "  phase_3__@(mangle_filename(name))();"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_777;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = string__7_778;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_779;
}
static void cont__7_779(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 960: writeln "  phase_3__@(mangle_filename(name))();"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_780(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 961: ... "
  // 962:   @
  // 963:     set_module("@(module_name)");
  // 964:     set_used_namespaces(used_namespaces);
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_781;
  arguments->slots[1] = get__module_name();
  arguments->slots[2] = string__7_782;
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
  frame->slots[33] /* temp__1 */ = arguments->slots[0];
  // 961: write "
  // 962:   @
  // 963:     set_module("@(module_name)");
  // 964:     set_used_namespaces(used_namespaces);
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[33] /* temp__1 */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_784;
}
static void cont__7_784(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 965: write generated_phase_3
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[23])->contents /* generated_phase_3 */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_785;
}
static void cont__7_785(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 966: if
  // 967:   is_main:
  // 968:     write "
  // 969:       @
  // 970:       
  // 971:         // initialization phase 4
  // 972:       
  // 973:         initialize_phase_4();
  // 974:   :
  // 975:     write "
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* is_main */;
  arguments->slots[1] = func__7_786;
  arguments->slots[2] = func__7_788;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_792;
}
static void entry__7_786(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 968: write "
  // 969:   @
  // 970:   
  // 971:     // initialization phase 4
  // 972:   
  // 973:     initialize_phase_4();
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_787;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_788(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 975: ... "
  // 976:   }
  // 977:   
  // 978:   static int already_run_phase_4 = false;
  // 979:   
  // 980:   EXPORT void phase_4__@(module_name)(void) {
  // 981:     if (already_run_phase_4) return;
  // 982:     already_run_phase_4 = true;
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_789;
  arguments->slots[1] = get__module_name();
  arguments->slots[2] = string__7_790;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_791;
}
static void cont__7_791(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 975: write "
  // 976:   }
  // 977:   
  // 978:   static int already_run_phase_4 = false;
  // 979:   
  // 980:   EXPORT void phase_4__@(module_name)(void) {
  // 981:     if (already_run_phase_4) return;
  // 982:     already_run_phase_4 = true;
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_792(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 983: ... : (name _info)
  // 984:   writeln "  phase_4__@(mangle_filename(name))();"
  frame->slots[33] /* temp__1 */ = create_closure(entry__7_793, 2);
  // 983: for_each required_modules: (name _info)
  // 984:   writeln "  phase_4__@(mangle_filename(name))();"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__required_modules();
  arguments->slots[1] = frame->slots[33] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__7_798;
}
static void entry__7_793(void) {
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
  // 984: ... mangle_filename(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = frame->slots[2] /* mangle_filename */;
  func = myself->type;
  frame->cont = cont__7_794;
}
static void cont__7_794(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 984: ... "  phase_4__@(mangle_filename(name))();"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_795;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = string__7_796;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_797;
}
static void cont__7_797(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 984: writeln "  phase_4__@(mangle_filename(name))();"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_798(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 985: ... "
  // 986:   @
  // 987:     set_module("@(module_name)");
  // 988:     set_used_namespaces(used_namespaces);
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_799;
  arguments->slots[1] = get__module_name();
  arguments->slots[2] = string__7_800;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_801;
}
static void cont__7_801(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[33] /* temp__1 */ = arguments->slots[0];
  // 985: write "
  // 986:   @
  // 987:     set_module("@(module_name)");
  // 988:     set_used_namespaces(used_namespaces);
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[33] /* temp__1 */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_802;
}
static void cont__7_802(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 989: for_each needed_names: (name info)
  // 990:   unless global_names(name).is_defined:
  // 991:     $namespace
  // 992:       if
  // 993:         name .contains. "__"
  // 994:         -> string('@quot;' name .before. "__" '@quot;')
  // 995:         -> "NULL"
  // 996:     
  // 997:     $basename name .truncate_until. "__"
  // 998:     case
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__needed_names();
  arguments->slots[1] = func__7_803;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__7_855;
}
static void entry__7_819(void) {
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
  // 1001: ... "
  // 1002:   @
  // 1003:     use_polymorphic_function(@(namespace), @quot;@(basename)", @
  // 1004:   &get__@(name), &poly_idx__@(name));
  argument_count = 9;
  arguments = node_p;
  arguments->slots[0] = string__7_820;
  arguments->slots[1] = frame->slots[0] /* namespace */;
  arguments->slots[2] = string__7_821;
  arguments->slots[3] = frame->slots[1] /* basename */;
  arguments->slots[4] = string__7_822;
  arguments->slots[5] = frame->slots[2] /* name */;
  arguments->slots[6] = string__7_823;
  arguments->slots[7] = frame->slots[2] /* name */;
  arguments->slots[8] = string__7_824;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_825;
}
static void cont__7_825(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1001: write "
  // 1002:   @
  // 1003:     use_polymorphic_function(@(namespace), @quot;@(basename)", @
  // 1004:   &get__@(name), &poly_idx__@(name));
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_826(void) {
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
  // 1006: ... "
  // 1007:   @
  // 1008:     use_read_only(@(namespace), @quot;@(basename)", &get__@(name), @
  // 1009:   &get_value_or_future__@(name));
  argument_count = 9;
  arguments = node_p;
  arguments->slots[0] = string__7_827;
  arguments->slots[1] = frame->slots[0] /* namespace */;
  arguments->slots[2] = string__7_828;
  arguments->slots[3] = frame->slots[1] /* basename */;
  arguments->slots[4] = string__7_829;
  arguments->slots[5] = frame->slots[2] /* name */;
  arguments->slots[6] = string__7_830;
  arguments->slots[7] = frame->slots[2] /* name */;
  arguments->slots[8] = string__7_831;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_832;
}
static void cont__7_832(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1006: write "
  // 1007:   @
  // 1008:     use_read_only(@(namespace), @quot;@(basename)", &get__@(name), @
  // 1009:   &get_value_or_future__@(name));
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_833(void) {
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
  // 1011: ... "
  // 1012:   @
  // 1013:     use_read_write(@(namespace), @quot;@(basename)", &get__@(name), @
  // 1014:   &set__@(name));
  argument_count = 9;
  arguments = node_p;
  arguments->slots[0] = string__7_834;
  arguments->slots[1] = frame->slots[0] /* namespace */;
  arguments->slots[2] = string__7_835;
  arguments->slots[3] = frame->slots[1] /* basename */;
  arguments->slots[4] = string__7_836;
  arguments->slots[5] = frame->slots[2] /* name */;
  arguments->slots[6] = string__7_837;
  arguments->slots[7] = frame->slots[2] /* name */;
  arguments->slots[8] = string__7_838;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_839;
}
static void cont__7_839(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1011: write "
  // 1012:   @
  // 1013:     use_read_write(@(namespace), @quot;@(basename)", &get__@(name), @
  // 1014:   &set__@(name));
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_840(void) {
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
  // 1016: ... "
  // 1017:   @
  // 1018:     use_single_assign_dynamic(@(namespace), @quot;@(basename)", @
  // 1019:   &get__@(name), &define__@(name));
  argument_count = 9;
  arguments = node_p;
  arguments->slots[0] = string__7_841;
  arguments->slots[1] = frame->slots[0] /* namespace */;
  arguments->slots[2] = string__7_842;
  arguments->slots[3] = frame->slots[1] /* basename */;
  arguments->slots[4] = string__7_843;
  arguments->slots[5] = frame->slots[2] /* name */;
  arguments->slots[6] = string__7_844;
  arguments->slots[7] = frame->slots[2] /* name */;
  arguments->slots[8] = string__7_845;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_846;
}
static void cont__7_846(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1016: write "
  // 1017:   @
  // 1018:     use_single_assign_dynamic(@(namespace), @quot;@(basename)", @
  // 1019:   &get__@(name), &define__@(name));
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_847(void) {
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
  // 1021: ... "
  // 1022:   @
  // 1023:     use_multi_assign_dynamic(@(namespace), @quot;@(basename)", @
  // 1024:   &get__@(name), &set__@(name), &define__@(name));
  argument_count = 11;
  arguments = node_p;
  arguments->slots[0] = string__7_848;
  arguments->slots[1] = frame->slots[0] /* namespace */;
  arguments->slots[2] = string__7_849;
  arguments->slots[3] = frame->slots[1] /* basename */;
  arguments->slots[4] = string__7_850;
  arguments->slots[5] = frame->slots[2] /* name */;
  arguments->slots[6] = string__7_851;
  arguments->slots[7] = frame->slots[2] /* name */;
  arguments->slots[8] = string__7_852;
  arguments->slots[9] = frame->slots[2] /* name */;
  arguments->slots[10] = string__7_853;
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
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1021: write "
  // 1022:   @
  // 1023:     use_multi_assign_dynamic(@(namespace), @quot;@(basename)", @
  // 1024:   &get__@(name), &set__@(name), &define__@(name));
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_806(void) {
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
  // 993: name .contains. "__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = string__7_807;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__7_808;
}
static void cont__7_808(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 994: -> string('@quot;' name .before. "__" '@quot;')
  frame->slots[5] /* temp__2 */ = create_closure(entry__7_809, 0);
  // 991: $namespace
  // 992:   if
  // 993:     name .contains. "__"
  // 994:     -> string('@quot;' name .before. "__" '@quot;')
  // 995:     -> "NULL"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = func__7_813;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_815;
}
static void entry__7_809(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 994: ... name .before. "__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = string__7_810;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__7_811;
}
static void cont__7_811(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 994: ... string('@quot;' name .before. "__" '@quot;')
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__34;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  arguments->slots[2] = character__34;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__7_812;
}
static void cont__7_812(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 994: -> string('@quot;' name .before. "__" '@quot;')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__7_813(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 995: -> "NULL"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_814;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__7_815(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* namespace */, arguments->slots[0]);
  // 997: $basename name .truncate_until. "__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = string__7_816;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__7_817;
}
static void cont__7_817(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* basename */, arguments->slots[0]);
  // 999: variable_kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__variable_kind_of();
  func = myself->type;
  frame->cont = cont__7_818;
}
static void cont__7_818(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 1000: ... :
  // 1001:   write "
  // 1002:     @
  // 1003:       use_polymorphic_function(@(namespace), @quot;@(basename)", @
  // 1004:     &get__@(name), &poly_idx__@(name));
  frame->slots[5] /* temp__2 */ = create_closure(entry__7_819, 0);
  // 1005: ... :
  // 1006:   write "
  // 1007:     @
  // 1008:       use_read_only(@(namespace), @quot;@(basename)", &get__@(name), @
  // 1009:     &get_value_or_future__@(name));
  frame->slots[6] /* temp__3 */ = create_closure(entry__7_826, 0);
  // 1010: ... :
  // 1011:   write "
  // 1012:     @
  // 1013:       use_read_write(@(namespace), @quot;@(basename)", &get__@(name), @
  // 1014:     &set__@(name));
  frame->slots[7] /* temp__4 */ = create_closure(entry__7_833, 0);
  // 1015: ... :
  // 1016:   write "
  // 1017:     @
  // 1018:       use_single_assign_dynamic(@(namespace), @quot;@(basename)", @
  // 1019:     &get__@(name), &define__@(name));
  frame->slots[8] /* temp__5 */ = create_closure(entry__7_840, 0);
  // 1020: ... :
  // 1021:   write "
  // 1022:     @
  // 1023:       use_multi_assign_dynamic(@(namespace), @quot;@(basename)", @
  // 1024:     &get__@(name), &set__@(name), &define__@(name));
  frame->slots[9] /* temp__6 */ = create_closure(entry__7_847, 0);
  //  998: case
  //  999:   variable_kind_of(info)
  // 1000:   POLYMORPHIC:
  // 1001:     write "
  // 1002:       @
  // 1003:         use_polymorphic_function(@(namespace), @quot;@(basename)", @
  // 1004:       &get__@(name), &poly_idx__@(name));
  // 1005:   STATIC_SINGLE:
  // 1006:     write "
  // 1007:       @
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
static void entry__7_803(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // name: 0
  // info: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 990: ... global_names(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__global_names();
  func = myself->type;
  frame->cont = cont__7_804;
}
static void cont__7_804(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 990: ... global_names(name).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__7_805;
}
static void cont__7_805(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 990: ... :
  // 991:   $namespace
  // 992:     if
  // 993:       name .contains. "__"
  // 994:       -> string('@quot;' name .before. "__" '@quot;')
  // 995:       -> "NULL"
  // 996:   
  // 997:   $basename name .truncate_until. "__"
  // 998:   case
  // 999:     variable_kind_of(info)
  // ...
  frame->slots[4] /* temp__3 */ = create_closure(entry__7_806, 0);
  // 990: unless global_names(name).is_defined:
  // 991:   $namespace
  // 992:     if
  // 993:       name .contains. "__"
  // 994:       -> string('@quot;' name .before. "__" '@quot;')
  // 995:       -> "NULL"
  // 996:   
  // 997:   $basename name .truncate_until. "__"
  // 998:   case
  // 999:     variable_kind_of(info)
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
static void cont__7_855(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1025: write generated_phase_4
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[24])->contents /* generated_phase_4 */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_856;
}
static void cont__7_856(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1026: if is_main:
  // 1027:   write "
  // 1028:     @
  // 1029:       resolve_attributes();
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* is_main */;
  arguments->slots[1] = func__7_857;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_859;
}
static void entry__7_857(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1027: write "
  // 1028:   @
  // 1029:     resolve_attributes();
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_858;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_859(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1030: if
  // 1031:   is_main:
  // 1032:     write "
  // 1033:       
  // 1034:         // initialization phase 5
  // 1035:       @;
  // 1036:   :
  // 1037:     write "
  // 1038:       }
  // 1039:       
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* is_main */;
  arguments->slots[1] = func__7_860;
  arguments->slots[2] = func__7_862;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_866;
}
static void entry__7_860(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1032: write "
  // 1033:   
  // 1034:     // initialization phase 5
  // 1035:   @;
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_861;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_862(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1037: ... "
  // 1038:   }
  // 1039:   
  // 1040:   static int already_run_phase_5 = false;
  // 1041:   
  // 1042:   EXPORT void phase_5__@(module_name)(void) {
  // 1043:     if (already_run_phase_5) return;
  // 1044:     already_run_phase_5 = true;
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_863;
  arguments->slots[1] = get__module_name();
  arguments->slots[2] = string__7_864;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_865;
}
static void cont__7_865(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1037: write "
  // 1038:   }
  // 1039:   
  // 1040:   static int already_run_phase_5 = false;
  // 1041:   
  // 1042:   EXPORT void phase_5__@(module_name)(void) {
  // 1043:     if (already_run_phase_5) return;
  // 1044:     already_run_phase_5 = true;
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_866(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1045: ... : (name _info)
  // 1046:   writeln "  phase_5__@(mangle_filename(name))();"
  frame->slots[33] /* temp__1 */ = create_closure(entry__7_867, 2);
  // 1045: for_each required_modules: (name _info)
  // 1046:   writeln "  phase_5__@(mangle_filename(name))();"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__required_modules();
  arguments->slots[1] = frame->slots[33] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__7_872;
}
static void entry__7_867(void) {
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
  // 1046: ... mangle_filename(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = frame->slots[2] /* mangle_filename */;
  func = myself->type;
  frame->cont = cont__7_868;
}
static void cont__7_868(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 1046: ... "  phase_5__@(mangle_filename(name))();"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_869;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = string__7_870;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_871;
}
static void cont__7_871(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1046: writeln "  phase_5__@(mangle_filename(name))();"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_872(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1047: write generated_phase_5
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[25])->contents /* generated_phase_5 */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_873;
}
static void cont__7_873(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1048: if
  // 1049:   is_main:
  // 1050:     write "
  // 1051:         initialize_function_attributes();
  // 1052:       
  // 1053:         // initialization phase 6
  // 1054:       @;
  // 1055:   :
  // 1056:     write "
  // 1057:       }
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* is_main */;
  arguments->slots[1] = func__7_874;
  arguments->slots[2] = func__7_876;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_880;
}
static void entry__7_874(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1050: write "
  // 1051:     initialize_function_attributes();
  // 1052:   
  // 1053:     // initialization phase 6
  // 1054:   @;
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_875;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_876(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1056: ... "
  // 1057:   }
  // 1058:   
  // 1059:   static int already_run_phase_6 = false;
  // 1060:   
  // 1061:   EXPORT void phase_6__@(module_name)(void) {
  // 1062:     if (already_run_phase_6) return;
  // 1063:     already_run_phase_6 = true;
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_877;
  arguments->slots[1] = get__module_name();
  arguments->slots[2] = string__7_878;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_879;
}
static void cont__7_879(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1056: write "
  // 1057:   }
  // 1058:   
  // 1059:   static int already_run_phase_6 = false;
  // 1060:   
  // 1061:   EXPORT void phase_6__@(module_name)(void) {
  // 1062:     if (already_run_phase_6) return;
  // 1063:     already_run_phase_6 = true;
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_880(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1064: ... : (name _info)
  // 1065:   writeln "  phase_6__@(mangle_filename(name))();"
  frame->slots[33] /* temp__1 */ = create_closure(entry__7_881, 2);
  // 1064: for_each required_modules: (name _info)
  // 1065:   writeln "  phase_6__@(mangle_filename(name))();"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__required_modules();
  arguments->slots[1] = frame->slots[33] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__7_886;
}
static void entry__7_881(void) {
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
  // 1065: ... mangle_filename(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = frame->slots[2] /* mangle_filename */;
  func = myself->type;
  frame->cont = cont__7_882;
}
static void cont__7_882(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 1065: ... "  phase_6__@(mangle_filename(name))();"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_883;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
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
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1065: writeln "  phase_6__@(mangle_filename(name))();"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_886(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1066: write generated_phase_6
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[26])->contents /* generated_phase_6 */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_887;
}
static void cont__7_887(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1067: ... "  register_collector(collect__@(module_name));"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_888;
  arguments->slots[1] = get__module_name();
  arguments->slots[2] = string__7_889;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_890;
}
static void cont__7_890(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[33] /* temp__1 */ = arguments->slots[0];
  // 1067: writeln "  register_collector(collect__@(module_name));"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[33] /* temp__1 */;
  result_count = 0;
  myself = get__writeln();
  func = myself->type;
  frame->cont = cont__7_891;
}
static void cont__7_891(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1068: if is_main:
  // 1069:   write "
  // 1070:     @
  // 1071:       execute(main_entry);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* is_main */;
  arguments->slots[1] = func__7_892;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_894;
}
static void entry__7_892(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1069: write "
  // 1070:   @
  // 1071:     execute(main_entry);
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_893;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_894(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1072: write "}@nl;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_895;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_896;
}
static void cont__7_896(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1073: ... : write_timing_info "generating" filenames(1)
  frame->slots[33] /* temp__1 */ = create_closure(entry__7_897, 0);
  // 1073: if do_time_passes: write_timing_info "generating" filenames(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = frame->slots[33] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_900;
}
static void entry__7_897(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // filenames: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* filenames */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1073: ... filenames(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* filenames */;
  func = myself->type;
  frame->cont = cont__7_898;
}
static void cont__7_898(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1073: ... write_timing_info "generating" filenames(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7_899;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write_timing_info();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_900(void) {
  myself = frame->slots[2] /* return__9 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
EXPORT void collect__sim2c(void) {
  var.sim2c__print_source = collect_node(var.sim2c__print_source);
  string__1_5 = collect_node(string__1_5);
  string__1_7 = collect_node(string__1_7);
  string__1_9 = collect_node(string__1_9);
  var.sim2c__eprint_source = collect_node(var.sim2c__eprint_source);
  string__2_5 = collect_node(string__2_5);
  string__2_7 = collect_node(string__2_7);
  string__2_9 = collect_node(string__2_9);
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
  var._demangled = collect_node(var._demangled);
  string__5_2 = collect_node(string__5_2);
  string__5_3 = collect_node(string__5_3);
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
  var.sim2c__sim2c = collect_node(var.sim2c__sim2c);
  string__7_3 = collect_node(string__7_3);
  string__7_6 = collect_node(string__7_6);
  string__7_10 = collect_node(string__7_10);
  string__7_19 = collect_node(string__7_19);
  string__7_23 = collect_node(string__7_23);
  string__7_26 = collect_node(string__7_26);
  string__7_28 = collect_node(string__7_28);
  string__7_48 = collect_node(string__7_48);
  string__7_50 = collect_node(string__7_50);
  string__7_58 = collect_node(string__7_58);
  string__7_61 = collect_node(string__7_61);
  string__7_62 = collect_node(string__7_62);
  string__7_66 = collect_node(string__7_66);
  string__7_71 = collect_node(string__7_71);
  string__7_77 = collect_node(string__7_77);
  string__7_84 = collect_node(string__7_84);
  string__7_86 = collect_node(string__7_86);
  string__7_93 = collect_node(string__7_93);
  string__7_99 = collect_node(string__7_99);
  string__7_126 = collect_node(string__7_126);
  string__7_132 = collect_node(string__7_132);
  string__7_141 = collect_node(string__7_141);
  string__7_150 = collect_node(string__7_150);
  string__7_159 = collect_node(string__7_159);
  string__7_161 = collect_node(string__7_161);
  string__7_164 = collect_node(string__7_164);
  string__7_168 = collect_node(string__7_168);
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
  string__7_289 = collect_node(string__7_289);
  string__7_298 = collect_node(string__7_298);
  string__7_300 = collect_node(string__7_300);
  string__7_310 = collect_node(string__7_310);
  string__7_393 = collect_node(string__7_393);
  string__7_398 = collect_node(string__7_398);
  string__7_401 = collect_node(string__7_401);
  string__7_438 = collect_node(string__7_438);
  string__7_443 = collect_node(string__7_443);
  string__7_447 = collect_node(string__7_447);
  string__7_448 = collect_node(string__7_448);
  string__7_451 = collect_node(string__7_451);
  string__7_452 = collect_node(string__7_452);
  string__7_455 = collect_node(string__7_455);
  string__7_456 = collect_node(string__7_456);
  string__7_457 = collect_node(string__7_457);
  string__7_464 = collect_node(string__7_464);
  string__7_465 = collect_node(string__7_465);
  string__7_466 = collect_node(string__7_466);
  string__7_470 = collect_node(string__7_470);
  string__7_481 = collect_node(string__7_481);
  string__7_498 = collect_node(string__7_498);
  string__7_500 = collect_node(string__7_500);
  string__7_512 = collect_node(string__7_512);
  string__7_516 = collect_node(string__7_516);
  string__7_520 = collect_node(string__7_520);
  string__7_526 = collect_node(string__7_526);
  string__7_528 = collect_node(string__7_528);
  string__7_532 = collect_node(string__7_532);
  string__7_533 = collect_node(string__7_533);
  string__7_536 = collect_node(string__7_536);
  string__7_538 = collect_node(string__7_538);
  string__7_541 = collect_node(string__7_541);
  string__7_543 = collect_node(string__7_543);
  string__7_546 = collect_node(string__7_546);
  string__7_550 = collect_node(string__7_550);
  string__7_552 = collect_node(string__7_552);
  string__7_558 = collect_node(string__7_558);
  string__7_559 = collect_node(string__7_559);
  string__7_562 = collect_node(string__7_562);
  string__7_563 = collect_node(string__7_563);
  string__7_569 = collect_node(string__7_569);
  string__7_570 = collect_node(string__7_570);
  string__7_576 = collect_node(string__7_576);
  string__7_577 = collect_node(string__7_577);
  string__7_583 = collect_node(string__7_583);
  string__7_584 = collect_node(string__7_584);
  string__7_587 = collect_node(string__7_587);
  string__7_591 = collect_node(string__7_591);
  string__7_593 = collect_node(string__7_593);
  string__7_601 = collect_node(string__7_601);
  string__7_605 = collect_node(string__7_605);
  string__7_607 = collect_node(string__7_607);
  string__7_608 = collect_node(string__7_608);
  string__7_611 = collect_node(string__7_611);
  string__7_620 = collect_node(string__7_620);
  string__7_622 = collect_node(string__7_622);
  string__7_627 = collect_node(string__7_627);
  string__7_628 = collect_node(string__7_628);
  string__7_629 = collect_node(string__7_629);
  string__7_632 = collect_node(string__7_632);
  string__7_636 = collect_node(string__7_636);
  string__7_637 = collect_node(string__7_637);
  string__7_640 = collect_node(string__7_640);
  string__7_643 = collect_node(string__7_643);
  string__7_644 = collect_node(string__7_644);
  string__7_647 = collect_node(string__7_647);
  string__7_648 = collect_node(string__7_648);
  string__7_651 = collect_node(string__7_651);
  string__7_657 = collect_node(string__7_657);
  string__7_658 = collect_node(string__7_658);
  string__7_661 = collect_node(string__7_661);
  string__7_663 = collect_node(string__7_663);
  string__7_667 = collect_node(string__7_667);
  string__7_668 = collect_node(string__7_668);
  string__7_669 = collect_node(string__7_669);
  string__7_670 = collect_node(string__7_670);
  string__7_671 = collect_node(string__7_671);
  string__7_672 = collect_node(string__7_672);
  string__7_673 = collect_node(string__7_673);
  string__7_674 = collect_node(string__7_674);
  string__7_675 = collect_node(string__7_675);
  string__7_680 = collect_node(string__7_680);
  string__7_681 = collect_node(string__7_681);
  string__7_685 = collect_node(string__7_685);
  string__7_688 = collect_node(string__7_688);
  string__7_690 = collect_node(string__7_690);
  string__7_691 = collect_node(string__7_691);
  string__7_696 = collect_node(string__7_696);
  string__7_697 = collect_node(string__7_697);
  string__7_700 = collect_node(string__7_700);
  string__7_704 = collect_node(string__7_704);
  string__7_706 = collect_node(string__7_706);
  string__7_707 = collect_node(string__7_707);
  string__7_712 = collect_node(string__7_712);
  string__7_713 = collect_node(string__7_713);
  string__7_717 = collect_node(string__7_717);
  string__7_718 = collect_node(string__7_718);
  string__7_727 = collect_node(string__7_727);
  string__7_735 = collect_node(string__7_735);
  string__7_736 = collect_node(string__7_736);
  string__7_744 = collect_node(string__7_744);
  string__7_745 = collect_node(string__7_745);
  string__7_751 = collect_node(string__7_751);
  string__7_752 = collect_node(string__7_752);
  string__7_755 = collect_node(string__7_755);
  string__7_756 = collect_node(string__7_756);
  string__7_763 = collect_node(string__7_763);
  string__7_764 = collect_node(string__7_764);
  string__7_769 = collect_node(string__7_769);
  string__7_771 = collect_node(string__7_771);
  string__7_772 = collect_node(string__7_772);
  string__7_777 = collect_node(string__7_777);
  string__7_778 = collect_node(string__7_778);
  string__7_781 = collect_node(string__7_781);
  string__7_782 = collect_node(string__7_782);
  string__7_787 = collect_node(string__7_787);
  string__7_789 = collect_node(string__7_789);
  string__7_790 = collect_node(string__7_790);
  string__7_795 = collect_node(string__7_795);
  string__7_796 = collect_node(string__7_796);
  string__7_799 = collect_node(string__7_799);
  string__7_800 = collect_node(string__7_800);
  string__7_807 = collect_node(string__7_807);
  string__7_810 = collect_node(string__7_810);
  string__7_814 = collect_node(string__7_814);
  string__7_816 = collect_node(string__7_816);
  string__7_820 = collect_node(string__7_820);
  string__7_821 = collect_node(string__7_821);
  string__7_822 = collect_node(string__7_822);
  string__7_823 = collect_node(string__7_823);
  string__7_824 = collect_node(string__7_824);
  string__7_827 = collect_node(string__7_827);
  string__7_828 = collect_node(string__7_828);
  string__7_829 = collect_node(string__7_829);
  string__7_830 = collect_node(string__7_830);
  string__7_831 = collect_node(string__7_831);
  string__7_834 = collect_node(string__7_834);
  string__7_835 = collect_node(string__7_835);
  string__7_836 = collect_node(string__7_836);
  string__7_837 = collect_node(string__7_837);
  string__7_838 = collect_node(string__7_838);
  string__7_841 = collect_node(string__7_841);
  string__7_842 = collect_node(string__7_842);
  string__7_843 = collect_node(string__7_843);
  string__7_844 = collect_node(string__7_844);
  string__7_845 = collect_node(string__7_845);
  string__7_848 = collect_node(string__7_848);
  string__7_849 = collect_node(string__7_849);
  string__7_850 = collect_node(string__7_850);
  string__7_851 = collect_node(string__7_851);
  string__7_852 = collect_node(string__7_852);
  string__7_853 = collect_node(string__7_853);
  string__7_858 = collect_node(string__7_858);
  string__7_861 = collect_node(string__7_861);
  string__7_863 = collect_node(string__7_863);
  string__7_864 = collect_node(string__7_864);
  string__7_869 = collect_node(string__7_869);
  string__7_870 = collect_node(string__7_870);
  string__7_875 = collect_node(string__7_875);
  string__7_877 = collect_node(string__7_877);
  string__7_878 = collect_node(string__7_878);
  string__7_883 = collect_node(string__7_883);
  string__7_884 = collect_node(string__7_884);
  string__7_888 = collect_node(string__7_888);
  string__7_889 = collect_node(string__7_889);
  string__7_893 = collect_node(string__7_893);
  string__7_895 = collect_node(string__7_895);
  string__7_899 = collect_node(string__7_899);
  string__10_1 = collect_node(string__10_1);
  string__10_3 = collect_node(string__10_3);
  string__10_5 = collect_node(string__10_5);
  string__10_7 = collect_node(string__10_7);
  string__10_9 = collect_node(string__10_9);
  string__10_11 = collect_node(string__10_11);
  string__10_13 = collect_node(string__10_13);
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
  func__1_4 = create_function(entry__1_4, 0);
  func__1_6 = create_function(entry__1_6, 0);
  func__1_8 = create_function(entry__1_8, 0);
  func__1_2 = create_function(entry__1_2, 1);
  func__1_1 = create_function(entry__1_1, 1);
  func__2_4 = create_function(entry__2_4, 0);
  func__2_6 = create_function(entry__2_6, 0);
  func__2_8 = create_function(entry__2_8, 0);
  func__2_2 = create_function(entry__2_2, 1);
  func__2_1 = create_function(entry__2_1, 1);
  func__4_1 = create_function(entry__4_1, 1);
  func__5_1 = create_function(entry__5_1, 1);
  func__6_1 = create_function(entry__6_1, 3);
  func__7_2 = create_function(entry__7_2, 1);
  func__7_22 = create_function(entry__7_22, 2);
  func__7_57 = create_function(entry__7_57, 0);
  func__7_70 = create_function(entry__7_70, 0);
  func__7_76 = create_function(entry__7_76, 0);
  func__7_83 = create_function(entry__7_83, 0);
  func__7_95 = create_function(entry__7_95, 1);
  func__7_136 = create_function(entry__7_136, 1);
  func__7_152 = create_function(entry__7_152, 0);
  func__7_153 = create_function(entry__7_153, 0);
  func__7_158 = create_function(entry__7_158, 0);
  func__7_167 = create_function(entry__7_167, 0);
  func__7_265 = create_function(entry__7_265, 1);
  func__7_285 = create_function(entry__7_285, 1);
  func__7_284 = create_function(entry__7_284, 1);
  func__7_293 = create_function(entry__7_293, 1);
  func__7_292 = create_function(entry__7_292, 1);
  func__7_302 = create_function(entry__7_302, 1);
  func__7_404 = create_function(entry__7_404, 1);
  func__7_431 = create_function(entry__7_431, 0);
  func__7_484 = create_function(entry__7_484, 1);
  func__7_488 = create_function(entry__7_488, 0);
  func__7_497 = create_function(entry__7_497, 0);
  func__7_499 = create_function(entry__7_499, 0);
  func__7_509 = create_function(entry__7_509, 1);
  func__7_508 = create_function(entry__7_508, 1);
  func__7_511 = create_function(entry__7_511, 2);
  func__7_515 = create_function(entry__7_515, 1);
  func__7_519 = create_function(entry__7_519, 1);
  func__7_525 = create_function(entry__7_525, 0);
  func__7_531 = create_function(entry__7_531, 1);
  func__7_540 = create_function(entry__7_540, 0);
  func__7_545 = create_function(entry__7_545, 0);
  func__7_549 = create_function(entry__7_549, 0);
  func__7_554 = create_function(entry__7_554, 2);
  func__7_604 = create_function(entry__7_604, 0);
  func__7_606 = create_function(entry__7_606, 0);
  func__7_625 = create_function(entry__7_625, 2);
  func__7_624 = create_function(entry__7_624, 0);
  func__7_635 = create_function(entry__7_635, 2);
  func__7_642 = create_function(entry__7_642, 1);
  func__7_660 = create_function(entry__7_660, 0);
  func__7_687 = create_function(entry__7_687, 0);
  func__7_689 = create_function(entry__7_689, 0);
  func__7_703 = create_function(entry__7_703, 0);
  func__7_705 = create_function(entry__7_705, 0);
  func__7_716 = create_function(entry__7_716, 2);
  func__7_768 = create_function(entry__7_768, 0);
  func__7_770 = create_function(entry__7_770, 0);
  func__7_786 = create_function(entry__7_786, 0);
  func__7_788 = create_function(entry__7_788, 0);
  func__7_813 = create_function(entry__7_813, 0);
  func__7_803 = create_function(entry__7_803, 2);
  func__7_857 = create_function(entry__7_857, 0);
  func__7_860 = create_function(entry__7_860, 0);
  func__7_862 = create_function(entry__7_862, 0);
  func__7_874 = create_function(entry__7_874, 0);
  func__7_876 = create_function(entry__7_876, 0);
  func__7_892 = create_function(entry__7_892, 0);
  func__7_1 = create_function(entry__7_1, -1);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__sim2c(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("sim2c");
  set_used_namespaces(used_namespaces);
  string__1_5 = from_latin_1_string("<newline>", 9);
  string__1_7 = from_latin_1_string("<indent_marker>", 15);
  string__1_9 = from_latin_1_string("<outdent_marker>", 16);
  define_single_assign_static("sim2c", "print_source", get__sim2c__print_source, &var.sim2c__print_source);
  string__2_5 = from_latin_1_string("<newline>", 9);
  string__2_7 = from_latin_1_string("<indent_marker>", 15);
  string__2_9 = from_latin_1_string("<outdent_marker>", 16);
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
  define_single_assign_static("sim2c", "generate_dispatcher_function", get__sim2c__generate_dispatcher_function, &var.sim2c__generate_dispatcher_function);
  string__5_2 = from_latin_1_string("__", 2);
  string__5_3 = from_latin_1_string("::", 2);
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
  define_single_assign_static("sim2c", "update_info", get__sim2c__update_info, &var.sim2c__update_info);
  string__7_3 = from_latin_1_string("./", 2);
  string__7_6 = from_latin_1_string("__", 2);
  string__7_10 = from_latin_1_string("__", 2);
  string__7_19 = from_latin_1_string("__", 2);
  string__7_23 = from_latin_1_string("__", 2);
  string__7_26 = from_latin_1_string("__", 2);
  string__7_28 = from_latin_1_string("__", 2);
  string__7_48 = from_latin_1_string("NODE", 4);
  string__7_50 = from_latin_1_string("SIMPLE_NODE", 11);
  string__7_58 = from_latin_1_string("Source file is not in a valid utf-8-encoding!", 45);
  string__7_61 = from_latin_1_string("load \042", 6);
  string__7_62 = from_latin_1_string("\042\012", 2);
  string__7_66 = from_latin_1_string("loading", 7);
  string__7_71 = from_latin_1_string("Empty source text!", 18);
  string__7_77 = from_latin_1_string("Whitespace at start of source text!", 35);
  string__7_84 = from_latin_1_string("Missing newline at end of source text!", 38);
  string__7_86 = from_latin_1_string("#!", 2);
  string__7_93 = from_latin_1_string("fragmenting", 11);
  string__7_99 = from_latin_1_string("tokenizing", 10);
  string__7_126 = from_latin_1_string("parsing", 7);
  string__7_132 = from_latin_1_string("terminate", 9);
  string__7_141 = from_latin_1_string("expanding", 9);
  string__7_150 = from_latin_1_string("annotating", 10);
  string__7_159 = from_latin_1_string("basic/stdlib", 12);
  string__7_161 = from_latin_1_string("system/stdlib", 13);
  string__7_164 = from_latin_1_string("nothing", 7);
  string__7_168 = from_latin_1_string("std", 3);
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
  string__7_289 = from_latin_1_string("simplifying", 11);
  string__7_298 = from_latin_1_string("_define ", 8);
  string__7_300 = from_latin_1_string("_define ", 8);
  string__7_310 = from_latin_1_string("mangling", 8);
  string__7_393 = from_latin_1_string("get__", 5);
  string__7_398 = from_latin_1_string("GENERATE DEFINITIONS", 20);
  string__7_401 = from_latin_1_string("__", 2);
  string__7_438 = from_latin_1_string("GENERATE STATEMENTS", 19);
  string__7_443 = from_latin_1_string("main_entry", 10);
  string__7_447 = from_latin_1_string("  allocate_initialized_frame_gc(0, ", 35);
  string__7_448 = from_latin_1_string(");", 2);
  string__7_451 = from_latin_1_string("  {run__", 8);
  string__7_452 = from_latin_1_string(", NULL, ", 8);
  string__7_455 = from_latin_1_string("static int already_run = false;\012\012EXPORT void run__", 50);
  string__7_456 = from_latin_1_string("(void) {\012  if (already_run) {\012    func = frame->cont;\012    frame->cont = invalid_continuation;\012    return;\012  }\012  already_run = true;\012  allocate_initialized_frame_gc(0, ", 167);
  string__7_457 = from_latin_1_string(");\012", 3);
  string__7_464 = from_latin_1_string("  func = run__", 14);
  string__7_465 = from_latin_1_string(";\012  frame->cont = cont__run__", 29);
  string__7_466 = from_latin_1_string(";\012}\012", 4);
  string__7_470 = from_latin_1_string("cont__run__", 11);
  string__7_481 = from_latin_1_string("__", 2);
  string__7_498 = from_latin_1_string("  terminate(0); // should never be reached\012}\012", 45);
  string__7_500 = from_latin_1_string("  frame = frame->caller_frame;\012  func = frame->cont;\012  frame->cont = invalid_continuation;\012}\012", 93);
  string__7_512 = from_latin_1_string("/// require ", 12);
  string__7_516 = from_latin_1_string("/// link ", 9);
  string__7_520 = from_latin_1_string("/// data ", 9);
  string__7_526 = from_latin_1_string("stdint.h", 8);
  string__7_528 = from_latin_1_string("stdlib.h", 8);
  string__7_532 = from_latin_1_string("#include <", 10);
  string__7_533 = from_latin_1_string(">", 1);
  string__7_536 = from_latin_1_string("/**********************\012D E C L A R A T I O N S\012**********************/\012\012#ifndef IMPORT\012  #define IMPORT extern\012#endif\012\012#ifndef EXPORT\012  #define EXPORT\012#endif\012\012#ifndef NULL\012  #define NULL ((void *)0)\012#endif\012#define false 0\012#define true 1\012", 238);
  string__7_538 = from_latin_1_string("stdint.h", 8);
  string__7_541 = from_latin_1_string("typedef __INT8_TYPE__ int8_t;\012typedef __INT16_TYPE__ int16_t;\012typedef __INT32_TYPE__ int32_t;\012typedef __INT64_TYPE__ int64_t;\012typedef __INTPTR_TYPE__ intptr_t;\012\012#ifdef __UINT8_TYPE__\012  typedef __UINT8_TYPE__ uint8_t;\012#else\012  typedef unsigned __INT8_TYPE__ uint8_t;\012#endif\012\012#ifdef __UINT16_TYPE__\012  typedef __UINT16_TYPE__ uint16_t;\012#else\012  typedef unsigned __INT16_TYPE__ uint16_t;\012#endif\012\012#ifdef __UINT32_TYPE__\012  typedef __UINT32_TYPE__ uint32_t;\012#else\012  typedef unsigned __INT32_TYPE__ uint32_t;\012#endif\012\012#ifdef __UINT64_TYPE__\012  typedef __UINT64_TYPE__ uint64_t;\012#else\012  typedef unsigned __INT64_TYPE__ uint64_t;\012#endif\012\012#ifdef __UINTPTR_TYPE__\012  typedef __UINTPTR_TYPE__ uintptr_t;\012#else\012  typedef unsigned __INTPTR_TYPE__ uintptr_t;\012#endif\012", 745);
  string__7_543 = from_latin_1_string("stdlib.h", 8);
  string__7_546 = from_latin_1_string("stddef.h", 8);
  string__7_550 = from_latin_1_string("typedef __SIZE_TYPE__ size_t;\012", 30);
  string__7_552 = from_latin_1_string("// INSERT HERE //\012\012#if UINTPTR_MAX == 0xffffffffffffffff\012  #define FIRST_INVALID_ADDRESS 0xc000000000000000UL\012  #define SAMPLE_POINTER ((void *)0x123456789abcdef0UL)\012#else\012  #define FIRST_INVALID_ADDRESS 0xc0000000\012  #define SAMPLE_POINTER ((void *)0x12345678)\012#endif\012\012#define MAKE_ATTRIBUTE_VALUE(node) ((NODE *)(((uintptr_t)node)+1))\012#define RETRIEVE_ATTRIBUTE_VALUE(node) ((NODE *)(((uintptr_t)node)-1))\012#define CONTAINS_AN_ATTRIBUTE_VALUE(node) (((uintptr_t)node)&1)\012\012#define ENCODE_ADDRESS(addr) ((void *)((uintptr_t)addr | 2))\012#define DECODE_ADDRESS(addr) ((void *)((uintptr_t)addr & -3))\012#define IS_AN_INVALID_ADDRESS(addr) ((uintptr_t)addr & 2)\012\012#define MSB (1L << (8*sizeof(void *)-1))\012#define ENCODE_TO_LENGTH(addr) ((void *)(((uintptr_t)addr >> 1) | MSB))\012#define DECODE_FROM_LENGTH(addr) ((void *)((uintptr_t)addr << 1))\012#define IS_AN_INVALID_LENGTH(addr) ((uintptr_t)addr & MSB)\012\012#define IS_COLLECTED(addr) (((void *)(addr)) >= coll_node_buf && ((void *)(addr)) < coll_node_buf_end)\012#define IS_STATIC(addr) (((void *)(addr)) >= static_node_buf && ((void *)(addr)) < static_node_buf_end)\012#define MARK(addr) (((MEMORY_BLOCK *)(addr))-1)->mark = current_mark;\012\012#define ALLOCATION_SIZE(size) (((size)+sizeof(void *)-1)&-sizeof(void *))\012#define TYPEOF(node) (node)->type\012#define SIZEOF(node) (node)->attributes->vtable->size\012\012#ifdef WITHIN_LIBRARY\012  #define DEBUG_FILENAME(filename) filename\012#else\012  #define DEBUG_FILENAME(filename) \042./\042 filename\012#endif\012\012#ifdef __CYGWIN__\012  extern FUNC invalid_continuation;\012#else\012  extern void invalid_continuation(void);\012#endif\012", 1572);
  string__7_558 = from_latin_1_string("static int poly_idx__", 21);
  string__7_559 = from_latin_1_string(";", 1);
  string__7_562 = from_latin_1_string("static NODE_GETTER get__", 24);
  string__7_563 = from_latin_1_string(";", 1);
  string__7_569 = from_latin_1_string("static NODE_GETTER get_value_or_future__", 40);
  string__7_570 = from_latin_1_string(";", 1);
  string__7_576 = from_latin_1_string("static NODE_SETTER set__", 24);
  string__7_577 = from_latin_1_string(";", 1);
  string__7_583 = from_latin_1_string("static NODE_SETTER define__", 27);
  string__7_584 = from_latin_1_string(";", 1);
  string__7_587 = from_latin_1_string("static struct {\012", 16);
  string__7_591 = from_latin_1_string("} var;\012", 7);
  string__7_593 = from_latin_1_string("static const char *var_names[] = {\012", 35);
  string__7_601 = from_latin_1_string("};\012", 3);
  string__7_605 = from_latin_1_string("static void main_entry(void);", 29);
  string__7_607 = from_latin_1_string("void run__", 10);
  string__7_608 = from_latin_1_string("(void);", 7);
  string__7_611 = from_latin_1_string("\012static CONTINUATION_INFO continuation_info[] = {\012", 50);
  string__7_620 = from_latin_1_string("};\012\012", 4);
  string__7_622 = from_latin_1_string("union NODE {\012  struct {\012    FUNC type;\012    ATTRIBUTES *attributes;\012  };\012  CONTINUATION continuation;\012  CLOSURE closure;\012", 120);
  string__7_627 = from_latin_1_string("  ", 2);
  string__7_628 = from_latin_1_string(" ", 1);
  string__7_629 = from_latin_1_string(";\012", 2);
  string__7_632 = from_latin_1_string("};\012", 3);
  string__7_636 = from_latin_1_string("static NODE *", 13);
  string__7_637 = from_latin_1_string(";\012", 2);
  string__7_640 = from_latin_1_string("\012static const char *used_namespaces[] = {\012", 42);
  string__7_643 = from_latin_1_string("  \042", 3);
  string__7_644 = from_latin_1_string("\042,\012", 3);
  string__7_647 = from_latin_1_string("  NULL\012};\012\012static MODULE_INFO module_info = {\012  NULL,\012  \042", 57);
  string__7_648 = from_latin_1_string("\042,\012  continuation_info,\012  sizeof(continuation_info)/sizeof(CONTINUATION_INFO),\012  (NODE **)&var,\012  var_names,\012  sizeof(var_names)/sizeof(const char *),\012  used_namespaces,\012  {", 173);
  string__7_651 = from_latin_1_string("__", 2);
  string__7_657 = from_latin_1_string("DEBUG_FILENAME(\042", 16);
  string__7_658 = from_latin_1_string("\042)", 2);
  string__7_661 = from_latin_1_string(", ", 2);
  string__7_663 = from_latin_1_string("}\012};\012\012/******\012C O D E\012******/\012\012", 31);
  string__7_667 = from_latin_1_string("IMPORT void collect__", 21);
  string__7_668 = from_latin_1_string("(void);\012IMPORT void phase_1__", 29);
  string__7_669 = from_latin_1_string("(void);\012IMPORT void phase_2__", 29);
  string__7_670 = from_latin_1_string("(void);\012IMPORT void phase_3__", 29);
  string__7_671 = from_latin_1_string("(void);\012IMPORT void phase_4__", 29);
  string__7_672 = from_latin_1_string("(void);\012IMPORT void phase_5__", 29);
  string__7_673 = from_latin_1_string("(void);\012IMPORT void phase_6__", 29);
  string__7_674 = from_latin_1_string("(void);\012IMPORT void run__", 25);
  string__7_675 = from_latin_1_string("(void);\012", 8);
  string__7_680 = from_latin_1_string("EXPORT void collect__", 21);
  string__7_681 = from_latin_1_string("(void) {\012", 9);
  string__7_685 = from_latin_1_string("}\012", 2);
  string__7_688 = from_latin_1_string("\012int main(int argc, char **argv) {\012  main_argc = argc;\012  main_argv = argv;\012  initialize_runtime();\012\012  // initialization phase 1\012\012", 129);
  string__7_690 = from_latin_1_string("\012static int already_run_phase_1 = false;\012\012EXPORT void phase_1__", 63);
  string__7_691 = from_latin_1_string("(void) {\012  if (already_run_phase_1) return;\012  already_run_phase_1 = true;\012", 74);
  string__7_696 = from_latin_1_string("  phase_1__", 11);
  string__7_697 = from_latin_1_string("();", 3);
  string__7_700 = from_latin_1_string("  register_module_info(&module_info);\012", 38);
  string__7_704 = from_latin_1_string("\012  // initialization phase 2\012", 29);
  string__7_706 = from_latin_1_string("}\012\012static int already_run_phase_2 = false;\012\012EXPORT void phase_2__", 65);
  string__7_707 = from_latin_1_string("(void) {\012  if (already_run_phase_2) return;\012  already_run_phase_2 = true;\012", 74);
  string__7_712 = from_latin_1_string("  phase_2__", 11);
  string__7_713 = from_latin_1_string("();", 3);
  string__7_717 = from_latin_1_string("  ", 2);
  string__7_718 = from_latin_1_string(" = ", 3);
  string__7_727 = from_latin_1_string("0x", 2);
  string__7_735 = from_latin_1_string("from_double(", 12);
  string__7_736 = from_latin_1_string(");\012", 3);
  string__7_744 = from_latin_1_string("from_uint32(", 12);
  string__7_745 = from_latin_1_string("U);\012", 4);
  string__7_751 = from_latin_1_string("from_uint64(", 12);
  string__7_752 = from_latin_1_string("ULL);\012", 6);
  string__7_755 = from_latin_1_string("from_digit_string(\042", 19);
  string__7_756 = from_latin_1_string("\042);\012", 4);
  string__7_763 = from_latin_1_string("from_uchar32(", 13);
  string__7_764 = from_latin_1_string(");", 2);
  string__7_769 = from_latin_1_string("\012  // initialization phase 3\012\012  initialize_phase_3();\012  resolve_symbols();\012", 75);
  string__7_771 = from_latin_1_string("}\012\012static int already_run_phase_3 = false;\012\012EXPORT void phase_3__", 65);
  string__7_772 = from_latin_1_string("(void) {\012  if (already_run_phase_3) return;\012  already_run_phase_3 = true;\012", 74);
  string__7_777 = from_latin_1_string("  phase_3__", 11);
  string__7_778 = from_latin_1_string("();", 3);
  string__7_781 = from_latin_1_string("  set_module(\042", 14);
  string__7_782 = from_latin_1_string("\042);\012  set_used_namespaces(used_namespaces);\012", 44);
  string__7_787 = from_latin_1_string("\012  // initialization phase 4\012\012  initialize_phase_4();\012", 54);
  string__7_789 = from_latin_1_string("}\012\012static int already_run_phase_4 = false;\012\012EXPORT void phase_4__", 65);
  string__7_790 = from_latin_1_string("(void) {\012  if (already_run_phase_4) return;\012  already_run_phase_4 = true;\012", 74);
  string__7_795 = from_latin_1_string("  phase_4__", 11);
  string__7_796 = from_latin_1_string("();", 3);
  string__7_799 = from_latin_1_string("  set_module(\042", 14);
  string__7_800 = from_latin_1_string("\042);\012  set_used_namespaces(used_namespaces);\012", 44);
  string__7_807 = from_latin_1_string("__", 2);
  string__7_810 = from_latin_1_string("__", 2);
  string__7_814 = from_latin_1_string("NULL", 4);
  string__7_816 = from_latin_1_string("__", 2);
  string__7_820 = from_latin_1_string("  use_polymorphic_function(", 27);
  string__7_821 = from_latin_1_string(", \042", 3);
  string__7_822 = from_latin_1_string("\042, &get__", 9);
  string__7_823 = from_latin_1_string(", &poly_idx__", 13);
  string__7_824 = from_latin_1_string(");\012", 3);
  string__7_827 = from_latin_1_string("  use_read_only(", 16);
  string__7_828 = from_latin_1_string(", \042", 3);
  string__7_829 = from_latin_1_string("\042, &get__", 9);
  string__7_830 = from_latin_1_string(", &get_value_or_future__", 24);
  string__7_831 = from_latin_1_string(");\012", 3);
  string__7_834 = from_latin_1_string("  use_read_write(", 17);
  string__7_835 = from_latin_1_string(", \042", 3);
  string__7_836 = from_latin_1_string("\042, &get__", 9);
  string__7_837 = from_latin_1_string(", &set__", 8);
  string__7_838 = from_latin_1_string(");\012", 3);
  string__7_841 = from_latin_1_string("  use_single_assign_dynamic(", 28);
  string__7_842 = from_latin_1_string(", \042", 3);
  string__7_843 = from_latin_1_string("\042, &get__", 9);
  string__7_844 = from_latin_1_string(", &define__", 11);
  string__7_845 = from_latin_1_string(");\012", 3);
  string__7_848 = from_latin_1_string("  use_multi_assign_dynamic(", 27);
  string__7_849 = from_latin_1_string(", \042", 3);
  string__7_850 = from_latin_1_string("\042, &get__", 9);
  string__7_851 = from_latin_1_string(", &set__", 8);
  string__7_852 = from_latin_1_string(", &define__", 11);
  string__7_853 = from_latin_1_string(");\012", 3);
  string__7_858 = from_latin_1_string("  resolve_attributes();\012", 24);
  string__7_861 = from_latin_1_string("\012  // initialization phase 5\012\012", 30);
  string__7_863 = from_latin_1_string("}\012\012static int already_run_phase_5 = false;\012\012EXPORT void phase_5__", 65);
  string__7_864 = from_latin_1_string("(void) {\012  if (already_run_phase_5) return;\012  already_run_phase_5 = true;\012", 74);
  string__7_869 = from_latin_1_string("  phase_5__", 11);
  string__7_870 = from_latin_1_string("();", 3);
  string__7_875 = from_latin_1_string("  initialize_function_attributes();\012\012  // initialization phase 6\012\012", 66);
  string__7_877 = from_latin_1_string("}\012\012static int already_run_phase_6 = false;\012\012EXPORT void phase_6__", 65);
  string__7_878 = from_latin_1_string("(void) {\012  if (already_run_phase_6) return;\012  already_run_phase_6 = true;\012", 74);
  string__7_883 = from_latin_1_string("  phase_6__", 11);
  string__7_884 = from_latin_1_string("();", 3);
  string__7_888 = from_latin_1_string("  register_collector(collect__", 30);
  string__7_889 = from_latin_1_string(");", 2);
  string__7_893 = from_latin_1_string("  execute(main_entry);\012", 23);
  string__7_895 = from_latin_1_string("}\012", 2);
  string__7_899 = from_latin_1_string("generating", 10);
  define_single_assign_static("sim2c", "sim2c", get__sim2c__sim2c, &var.sim2c__sim2c);
  string__10_1 = from_latin_1_string("std__if", 7);
  string__10_3 = from_latin_1_string("std__is_defined", 15);
  string__10_5 = from_latin_1_string("std__equal", 10);
  string__10_7 = from_latin_1_string("std__less", 9);
  string__10_9 = from_latin_1_string("std__length_of", 14);
  string__10_11 = from_latin_1_string("std__is_empty", 13);
  string__10_13 = from_latin_1_string("std__unless", 11);
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
  use_single_assign_dynamic("sim2c", "write_to_phase_6", &get__sim2c__write_to_phase_6, &define__sim2c__write_to_phase_6);
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

static int already_run_phase_5 = false;

EXPORT void phase_5__sim2c(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  assign_variable(&var.sim2c__print_source, &func__1_1);
  assign_variable(&var.sim2c__eprint_source, &func__2_1);
  assign_variable(&var.sim2c__generate_dispatcher_function, &func__4_1);
  assign_variable(&var._demangled, &func__5_1);
  assign_variable(&var.sim2c__update_info, &func__6_1);
  assign_variable(&var.sim2c__sim2c, &func__7_1);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__sim2c(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__sim2c);
}
