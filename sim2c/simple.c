/// require basic/exceptions
/// require basic/serialize
/// require basic/deserialize
/// require basic/branches
/// require basic/debug
/// require basic/environment
/// require basic/event
/// require basic/exec
/// require basic/functional
/// require basic/grammar
/// require basic/io
/// require basic/loops
/// require basic/math
/// require basic/options
/// require basic/parameters
/// require basic/platform
/// require basic/polymorphic_functions
/// require basic/primitives
/// require basic/runtime
/// require basic/types/boolean
/// require basic/types/character
/// require basic/types/continuation
/// require basic/types/date_and_time
/// require basic/types/function
/// require basic/types/insert_order_set
/// require basic/types/insert_order_table
/// require basic/types/list
/// require basic/types/multi_dimensional_set
/// require basic/types/multi_dimensional_table
/// require basic/types/number
/// require basic/types/object
/// require basic/types/key_order_table
/// require basic/types/key_value_pair
/// require basic/types/set
/// require basic/types/key_order_set
/// require basic/types/string_primitives
/// require basic/types/string
/// require basic/types/table
/// require basic/types/undefined
/// require basic/types/unique_item
/// require basic/types/unordered_set
/// require basic/types/unordered_table
/// require basic/types/value_range
/// require system/export/html
/// require ./character_names
/// require ./fragments
/// require ./tokenizer
/// require ./shared_variables
/// require ./nodes
/// require ./parser
/// require ./expander
/// require ./annotator
/// require ./simplifier
/// require ./macros
/// require ./c_code_generator
/// require ./pretty_printer
/// require ./sim2c
/// require ./extractor
/// require ./runtime_definitions

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
IMPORT NODE *undefined;
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
IMPORT NODE *get_dynamic_slot(int id);
IMPORT void define_dynamic_slot(int id, NODE *node);
typedef struct FRAME_INFO {
  int var_count;
  const char *var_names[];
} FRAME_INFO;
IMPORT NODE *get_dynamic_cell(int id);
IMPORT void set_dynamic_cell(int id, NODE *node);
IMPORT void define_dynamic_cell(int id, NODE *node);
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
IMPORT void allocate_initialized_frame_gc(int slot_idx, int slot_count);
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
REGISTER int argument_count ASM("ebx");
REGISTER FRAME *arguments ASM("r12");
IMPORT void *node_p;
IMPORT int result_count;
REGISTER NODE *myself ASM("r13");
IMPORT void invalid_results_error(void);
IMPORT int runtime_major_version(void);
IMPORT void initialize_future(NODE *var, NODE *val);
IMPORT int runtime_minor_version(void);
IMPORT int runtime_revision(void);
IMPORT void invalid_arguments_error(void);
IMPORT NODE *create_continuation(void);
IMPORT NODE *create_closure(FUNC type, int par_count);
IMPORT NODE *create_future(void);
typedef struct CELL {
  FUNC type;
  struct ATTRIBUTES *attributes;
  NODE *contents;
} CELL;
IMPORT NODE *create_cell(void);
IMPORT int print(char **buf_p, const char *format, ...);
IMPORT void initialize_maybe_future(NODE *var, NODE *val);
IMPORT void terminate(int exit_code);
IMPORT void allocate_arguments(void);
IMPORT NODE *from_arguments(int first_idx, int count);
IMPORT NODE *create_cell_with_contents(NODE *contents);
IMPORT void too_few_arguments_error(void);
IMPORT void too_many_arguments_error(void);
IMPORT NODE *empty_string;
IMPORT NODE *collect_node(NODE *node);
IMPORT int main_argc;
IMPORT char **main_argv;
IMPORT void initialize_runtime(void);
IMPORT void register_module_info(MODULE_INFO *info);
IMPORT NODE *from_uchar32(unsigned int chr);
IMPORT NODE *from_uint32(uint32_t val);
IMPORT NODE *register_unique_item(const char *name);
IMPORT NODE *create_function(FUNC func, int par_count);
IMPORT NODE *from_latin_1_string(const char *str, long len);
IMPORT void initialize_phase_3(void);
IMPORT void resolve_symbols(void);
IMPORT void set_module(const char *name);
IMPORT void set_used_namespaces(const char **namespaces);
IMPORT void assign_value(NODE **dest, NODE *val);
IMPORT void define_multi_assign_static(
  const char *namespace, const char *name,
  NODE_GETTER getter, NODE_SETTER setter
);
IMPORT void register_dynamic(int *id_p);
IMPORT void define_single_assign_static(
  const char *namespace, const char *name,
  NODE_GETTER getter, NODE **var_p
);
IMPORT void initialize_phase_4(void);
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
IMPORT void resolve_attributes(void);
IMPORT void assign_variable(NODE **dest, NODE **var_p);
IMPORT void maybe_initialize_future(NODE *var, NODE *val);
IMPORT void initialize_function_attributes(void);
IMPORT void register_collector(FUNC collector);
IMPORT __attribute__ ((noreturn)) void execute(FUNC entry);


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
static NODE_GETTER get__Error;
static NODE_GETTER get_value_or_future__Error;
static NODE_GETTER get__NAME;
static NODE_GETTER get_value_or_future__NAME;
static NODE_GETTER get__SORT;
static NODE_GETTER get_value_or_future__SORT;
static NODE_GETTER get__VALUED_OPTION;
static NODE_GETTER get_value_or_future__VALUED_OPTION;
static NODE_GETTER get__append;
static NODE_GETTER get_value_or_future__append;
static NODE_GETTER get__before;
static NODE_GETTER get_value_or_future__before;
static NODE_GETTER get__behind;
static NODE_GETTER get_value_or_future__behind;
static NODE_GETTER get__between;
static NODE_GETTER get_value_or_future__between;
static NODE_GETTER get__c_compiler;
static NODE_GETTER get_value_or_future__c_compiler;
static NODE_GETTER get__case;
static NODE_GETTER get_value_or_future__case;
static NODE_GETTER get__change_directory;
static NODE_GETTER get_value_or_future__change_directory;
static NODE_GETTER get__collect_output;
static NODE_GETTER get_value_or_future__collect_output;
static NODE_GETTER get__command_line_arguments;
static NODE_GETTER get_value_or_future__command_line_arguments;
static NODE_GETTER get__cond;
static NODE_GETTER get_value_or_future__cond;
static NODE_GETTER get__contains;
static NODE_GETTER get_value_or_future__contains;
static NODE_GETTER get__copyright;
static NODE_GETTER get_value_or_future__copyright;
static NODE_GETTER get__count_occurrences;
static NODE_GETTER get_value_or_future__count_occurrences;
static NODE_GETTER get__current_path;
static NODE_GETTER get_value_or_future__current_path;
static NODE_GETTER get__current_time;
static NODE_GETTER get_value_or_future__current_time;
static NODE_GETTER get__dec;
static NODE_GETTER get_value_or_future__dec;
static NODE_GETTER get__default_value;
static NODE_GETTER get_value_or_future__default_value;
static NODE_GETTER get__directory;
static NODE_GETTER get_value_or_future__directory;
static NODE_GETTER get__do;
static NODE_GETTER get_value_or_future__do;
static NODE_GETTER get__do_check_only;
static NODE_GETTER get_value_or_future__do_check_only;
static NODE_GETTER get__do_dump_trees;
static NODE_GETTER get_value_or_future__do_dump_trees;
static NODE_GETTER get__do_extract_documentation;
static NODE_SETTER set__do_extract_documentation;
static NODE_GETTER get__do_pretty_print;
static NODE_GETTER get_value_or_future__do_pretty_print;
static NODE_GETTER get__do_print_simplified_source;
static NODE_GETTER get_value_or_future__do_print_simplified_source;
static NODE_GETTER get__do_show_compiler_debug_infos;
static NODE_GETTER get_value_or_future__do_show_compiler_debug_infos;
static NODE_GETTER get__do_show_debug_infos;
static NODE_GETTER get_value_or_future__do_show_debug_infos;
static NODE_GETTER get__do_time_passes;
static NODE_SETTER set__do_time_passes;
static NODE_GETTER get__do_while;
static NODE_GETTER get_value_or_future__do_while;
static NODE_GETTER get__dup;
static NODE_GETTER get_value_or_future__dup;
static NODE_GETTER get__empty_insert_order_set;
static NODE_GETTER get_value_or_future__empty_insert_order_set;
static NODE_GETTER get__empty_key_order_set;
static NODE_GETTER get_value_or_future__empty_key_order_set;
static NODE_GETTER get__empty_key_order_table;
static NODE_GETTER get_value_or_future__empty_key_order_table;
static NODE_GETTER get__empty_list;
static NODE_GETTER get_value_or_future__empty_list;
static NODE_GETTER get__empty_set;
static NODE_GETTER get_value_or_future__empty_set;
static NODE_GETTER get__empty_table;
static NODE_GETTER get_value_or_future__empty_table;
static NODE_GETTER get__environment;
static NODE_GETTER get_value_or_future__environment;
static NODE_GETTER get__ewrite;
static NODE_GETTER get_value_or_future__ewrite;
static NODE_GETTER get__ewriteln;
static NODE_GETTER get_value_or_future__ewriteln;
static NODE_GETTER get__exec;
static NODE_GETTER get_value_or_future__exec;
static NODE_GETTER get__extern;
static NODE_GETTER get_value_or_future__extern;
static NODE_GETTER get__extract_documentation;
static NODE_GETTER get_value_or_future__extract_documentation;
static NODE_GETTER get__false;
static NODE_GETTER get_value_or_future__false;
static NODE_GETTER get__file_exists;
static NODE_GETTER get_value_or_future__file_exists;
static NODE_GETTER get__for_each;
static NODE_GETTER get_value_or_future__for_each;
static NODE_GETTER get__for_each_line;
static NODE_GETTER get_value_or_future__for_each_line;
static NODE_GETTER get__forever;
static NODE_GETTER get_value_or_future__forever;
static NODE_GETTER get__from;
static NODE_GETTER get_value_or_future__from;
static NODE_GETTER get__from_utf8;
static NODE_GETTER get_value_or_future__from_utf8;
static NODE_GETTER get__fullname;
static NODE_GETTER get_value_or_future__fullname;
static NODE_GETTER get__fullname_of;
static NODE_GETTER get_value_or_future__fullname_of;
static NODE_GETTER get__hardware_architecture;
static NODE_GETTER get_value_or_future__hardware_architecture;
static NODE_GETTER get__has_prefix;
static NODE_GETTER get_value_or_future__has_prefix;
static NODE_GETTER get__has_suffix;
static NODE_GETTER get_value_or_future__has_suffix;
static NODE_GETTER get__if;
static NODE_GETTER get_value_or_future__if;
static NODE_GETTER get__inc;
static NODE_GETTER get_value_or_future__inc;
static NODE_GETTER get__is_a_digit;
static NODE_GETTER get_value_or_future__is_a_digit;
static NODE_GETTER get__is_a_directory;
static NODE_GETTER get_value_or_future__is_a_directory;
static NODE_GETTER get__is_a_letter;
static NODE_GETTER get_value_or_future__is_a_letter;
static NODE_GETTER get__is_defined;
static NODE_GETTER get_value_or_future__is_defined;
static NODE_GETTER get__is_empty;
static NODE_GETTER get_value_or_future__is_empty;
static NODE_GETTER get__is_undefined;
static NODE_GETTER get_value_or_future__is_undefined;
static NODE_GETTER get__join;
static NODE_GETTER get_value_or_future__join;
static NODE_GETTER get__key_order_table;
static NODE_GETTER get_value_or_future__key_order_table;
static NODE_GETTER get__length_of;
static NODE_GETTER get_value_or_future__length_of;
static NODE_GETTER get__list;
static NODE_GETTER get_value_or_future__list;
static NODE_GETTER get__load;
static NODE_GETTER get_value_or_future__load;
static NODE_GETTER get__many;
static NODE_GETTER get_value_or_future__many;
static NODE_GETTER get__matches;
static NODE_GETTER get_value_or_future__matches;
static NODE_GETTER get__modification_time_of;
static NODE_GETTER get_value_or_future__modification_time_of;
static NODE_GETTER get__module_name;
static NODE_GETTER get_value_or_future__module_name;
static NODE_GETTER get__multi_dimensional_table;
static NODE_GETTER get_value_or_future__multi_dimensional_table;
static NODE_GETTER get__not;
static NODE_GETTER get_value_or_future__not;
static NODE_GETTER get__operating_system;
static NODE_GETTER get_value_or_future__operating_system;
static NODE_GETTER get__parameter_count_of;
static NODE_GETTER get_value_or_future__parameter_count_of;
static NODE_GETTER get__program_name;
static NODE_GETTER get_value_or_future__program_name;
static NODE_GETTER get__program_parameters;
static NODE_GETTER get_value_or_future__program_parameters;
static NODE_GETTER get__push;
static NODE_GETTER get_value_or_future__push;
static NODE_GETTER get__range;
static NODE_GETTER get_value_or_future__range;
static NODE_GETTER get__replace_all;
static NODE_GETTER get_value_or_future__replace_all;
static NODE_GETTER get__runtime_major_version;
static NODE_GETTER get_value_or_future__runtime_major_version;
static NODE_GETTER get__runtime_minor_version;
static NODE_GETTER get_value_or_future__runtime_minor_version;
static NODE_GETTER get__runtime_revision;
static NODE_GETTER get_value_or_future__runtime_revision;
static NODE_GETTER get__runtime_symbols;
static NODE_GETTER get_value_or_future__runtime_symbols;
static NODE_GETTER get__save;
static NODE_GETTER get_value_or_future__save;
static NODE_GETTER get__serialize;
static NODE_GETTER get_value_or_future__serialize;
static NODE_GETTER get__sim2c;
static NODE_GETTER get_value_or_future__sim2c;
static NODE_GETTER get__sim2c__module_name;
static NODE_SETTER define__sim2c__module_name;
static NODE_GETTER get__some;
static NODE_GETTER get_value_or_future__some;
static NODE_GETTER get__split;
static NODE_GETTER get_value_or_future__split;
static NODE_GETTER get__stat;
static NODE_GETTER get_value_or_future__stat;
static NODE_GETTER get__std__MANDATORY_PARAMETER;
static NODE_GETTER get_value_or_future__std__MANDATORY_PARAMETER;
static NODE_GETTER get__std__and;
static NODE_GETTER get_value_or_future__std__and;
static NODE_GETTER get__std__call;
static NODE_GETTER get_value_or_future__std__call;
static NODE_GETTER get__std__equal;
static NODE_GETTER get_value_or_future__std__equal;
static NODE_GETTER get__std__filename_of;
static NODE_GETTER get_value_or_future__std__filename_of;
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
static NODE_GETTER get__std__over;
static NODE_GETTER get_value_or_future__std__over;
static NODE_GETTER get__std__plus;
static NODE_GETTER get_value_or_future__std__plus;
static NODE_GETTER get__std__sequence;
static NODE_GETTER get_value_or_future__std__sequence;
static NODE_GETTER get__std__string;
static NODE_GETTER get_value_or_future__std__string;
static NODE_GETTER get__std__terminate;
static NODE_GETTER get_value_or_future__std__terminate;
static NODE_GETTER get__std__true;
static NODE_GETTER get_value_or_future__std__true;
static NODE_GETTER get__string;
static NODE_GETTER get_value_or_future__string;
static NODE_GETTER get__table;
static NODE_GETTER get_value_or_future__table;
static NODE_GETTER get__to_string;
static NODE_GETTER get_value_or_future__to_string;
static NODE_GETTER get__to_utf8;
static NODE_GETTER get_value_or_future__to_utf8;
static NODE_GETTER get__trim;
static NODE_GETTER get_value_or_future__trim;
static NODE_GETTER get__true;
static NODE_GETTER get_value_or_future__true;
static NODE_GETTER get__truncate_from;
static NODE_GETTER get_value_or_future__truncate_from;
static NODE_GETTER get__truncate_until;
static NODE_GETTER get_value_or_future__truncate_until;
static NODE_GETTER get__types__table;
static NODE_GETTER get_value_or_future__types__table;
static NODE_GETTER get__undefined;
static NODE_GETTER get_value_or_future__undefined;
static NODE_GETTER get__unless;
static NODE_GETTER get_value_or_future__unless;
static NODE_GETTER get__until;
static NODE_GETTER get_value_or_future__until;
static NODE_GETTER get__verbose;
static NODE_SETTER set__verbose;
static NODE_GETTER get__version;
static NODE_GETTER get_value_or_future__version;
static NODE_GETTER get__while;
static NODE_GETTER get_value_or_future__while;
static NODE_GETTER get__without_prefix;
static NODE_GETTER get_value_or_future__without_prefix;
static NODE_GETTER get__without_suffix;
static NODE_GETTER get_value_or_future__without_suffix;
static NODE_GETTER get__write;
static NODE_GETTER get_value_or_future__write;
static NODE_GETTER get__write_timing_info;
static NODE_GETTER get_value_or_future__write_timing_info;
static NODE_GETTER get__write_to;
static NODE_GETTER get_value_or_future__write_to;
static NODE_GETTER get__writeln;
static NODE_GETTER get_value_or_future__writeln;
static struct {
  NODE *_MAJOR;
  NODE *_MINOR;
  NODE *_REVISION;
  NODE *_BUILD;
  NODE *_VERSION;
  NODE *_cc;
  NODE *_mkdir;
  NODE *_SIMLIBPATH;
  NODE *_SIMDATAPATH;
  NODE *_simlibpaths;
  NODE *_simdatapaths;
  NODE *_NONE;
  NODE *_supported_platforms;
  NODE *_platform_priority;
  NODE *_platform_specific_priority;
  NODE *_module_info;
  NODE *_meta_levels;
  NODE *_do_rebuild;
  NODE *_do_omit_meta;
  NODE *_do_print_c;
  NODE *_do_build_codeblocks_project;
  NODE *_do_list_dependencies;
  NODE *_do_build_static;
  NODE *_do_link_profiler;
  NODE *_module_prefix;
  NODE *_input_filename;
  NODE *_action;
  NODE *_EXE;
  NODE *_LIB;
  NODE *_WHITESPACE;
  NODE *_cc_basic_options;
  NODE *_gcc_options;
  NODE *_cc_hardware_specific_options;
  NODE *_cc_include_options;
  NODE *_cc_options;
  NODE *_c_sources;
  NODE *_dependencies;
  NODE *_resolved_libraries;
  NODE *_resolve_filename;
  NODE *_add_module_infos;
  NODE *_lookup;
  NODE *_CC;
  NODE *_compile_c;
  NODE *_compile_meta_module;
  NODE *_build_dependencies;
  NODE *_compile_module;
  NODE *_compile_modules;
  NODE *_show_file_list;
  NODE *_library_paths_and_file_list;
  NODE *_create_imports;
  NODE *_compile_exe;
  NODE *_dump_source_or_check;
  NODE *_print_c;
  NODE *_list_dependencies;
  NODE *_build_codeblocks_project;
  NODE *_build_library;
  NODE *_maybe_compile_c_file;
  NODE *_t;
  NODE *_format_number;
  NODE *_build_executable;
  NODE *sim2c__do_dump_trees;
  NODE *sim2c__do_pretty_print;
  NODE *sim2c__do_print_simplified_source;
  NODE *sim2c__do_show_debug_infos;
  NODE *sim2c__do_show_compiler_debug_infos;
  NODE *sim2c__do_check_only;
  NODE *sim2c__do_show_brief_messages;
  NODE *sim2c__do_print_warnings;
  NODE *sim2c__verbose;
  NODE *sim2c__do_extract_documentation;
  NODE *sim2c__do_time_passes;
  NODE *sim2c__show_compiler_debug_info;
  NODE *sim2c__write_timing_info;
} var;
static const char *var_names[] = {
  "MAJOR",
  "MINOR",
  "REVISION",
  "BUILD",
  "VERSION",
  "cc",
  "mkdir",
  "SIMLIBPATH",
  "SIMDATAPATH",
  "simlibpaths",
  "simdatapaths",
  "NONE",
  "supported_platforms",
  "platform_priority",
  "platform_specific_priority",
  "module_info",
  "meta_levels",
  "do_rebuild",
  "do_omit_meta",
  "do_print_c",
  "do_build_codeblocks_project",
  "do_list_dependencies",
  "do_build_static",
  "do_link_profiler",
  "module_prefix",
  "input_filename",
  "action",
  "EXE",
  "LIB",
  "WHITESPACE",
  "cc_basic_options",
  "gcc_options",
  "cc_hardware_specific_options",
  "cc_include_options",
  "cc_options",
  "c_sources",
  "dependencies",
  "resolved_libraries",
  "resolve_filename",
  "add_module_infos",
  "lookup",
  "CC",
  "compile_c",
  "compile_meta_module",
  "build_dependencies",
  "compile_module",
  "compile_modules",
  "show_file_list",
  "library_paths_and_file_list",
  "create_imports",
  "compile_exe",
  "dump_source_or_check",
  "print_c",
  "list_dependencies",
  "build_codeblocks_project",
  "build_library",
  "maybe_compile_c_file",
  "t",
  "format_number",
  "build_executable"
};
static NODE *unique__NONE;
static NODE *get__sim2c__do_dump_trees(void) {
  return var.sim2c__do_dump_trees;
}
static void set__sim2c__do_dump_trees(NODE *val) {
  var.sim2c__do_dump_trees = val;
}
static NODE *get__sim2c__do_pretty_print(void) {
  return var.sim2c__do_pretty_print;
}
static void set__sim2c__do_pretty_print(NODE *val) {
  var.sim2c__do_pretty_print = val;
}
static NODE *get__sim2c__do_print_simplified_source(void) {
  return var.sim2c__do_print_simplified_source;
}
static void set__sim2c__do_print_simplified_source(NODE *val) {
  var.sim2c__do_print_simplified_source = val;
}
static NODE *get__sim2c__do_show_debug_infos(void) {
  return var.sim2c__do_show_debug_infos;
}
static void set__sim2c__do_show_debug_infos(NODE *val) {
  var.sim2c__do_show_debug_infos = val;
}
static NODE *get__sim2c__do_show_compiler_debug_infos(void) {
  return var.sim2c__do_show_compiler_debug_infos;
}
static void set__sim2c__do_show_compiler_debug_infos(NODE *val) {
  var.sim2c__do_show_compiler_debug_infos = val;
}
static NODE *get__sim2c__do_check_only(void) {
  return var.sim2c__do_check_only;
}
static void set__sim2c__do_check_only(NODE *val) {
  var.sim2c__do_check_only = val;
}
static NODE *get__sim2c__do_show_brief_messages(void) {
  return var.sim2c__do_show_brief_messages;
}
static void set__sim2c__do_show_brief_messages(NODE *val) {
  var.sim2c__do_show_brief_messages = val;
}
static NODE *get__sim2c__do_print_warnings(void) {
  return var.sim2c__do_print_warnings;
}
static void set__sim2c__do_print_warnings(NODE *val) {
  var.sim2c__do_print_warnings = val;
}
static NODE *get__sim2c__verbose(void) {
  return var.sim2c__verbose;
}
static void set__sim2c__verbose(NODE *val) {
  var.sim2c__verbose = val;
}
static NODE *get__sim2c__do_extract_documentation(void) {
  return var.sim2c__do_extract_documentation;
}
static void set__sim2c__do_extract_documentation(NODE *val) {
  var.sim2c__do_extract_documentation = val;
}
static NODE *get__sim2c__do_time_passes(void) {
  return var.sim2c__do_time_passes;
}
static void set__sim2c__do_time_passes(NODE *val) {
  var.sim2c__do_time_passes = val;
}
static int dyna_idx__main_filename;
static NODE *get__main_filename(void) {
  return get_dynamic_slot(dyna_idx__main_filename);
}
static void define__main_filename(NODE *node) {
  define_dynamic_slot(dyna_idx__main_filename, node);
}
static int dyna_idx__main_info;
static NODE *get__main_info(void) {
  return get_dynamic_slot(dyna_idx__main_info);
}
static void define__main_info(NODE *node) {
  define_dynamic_slot(dyna_idx__main_info, node);
}
static int dyna_idx__do_build_static_executable;
static NODE *get__do_build_static_executable(void) {
  return get_dynamic_slot(dyna_idx__do_build_static_executable);
}
static void define__do_build_static_executable(NODE *node) {
  define_dynamic_slot(dyna_idx__do_build_static_executable, node);
}
static NODE *func__47_1_sim2c__show_compiler_debug_info;
static void entry__47_1_sim2c__show_compiler_debug_info(void);
static FRAME_INFO frame__47_1_sim2c__show_compiler_debug_info = {1, {"args"}};
static NODE *func__47_2;
static void entry__47_2(void);
static FRAME_INFO frame__47_2 = {1, {"args"}};
static NODE *get__sim2c__show_compiler_debug_info(void) {
  return var.sim2c__show_compiler_debug_info;
}
static NODE *unique__EXE;
static NODE *unique__LIB;
static int dyna_idx__mode;
static NODE *get__mode(void) {
  return get_dynamic_slot(dyna_idx__mode);
}
static void define__mode(NODE *node) {
  define_dynamic_slot(dyna_idx__mode, node);
}
static int dyna_idx__on_top_level;
static NODE *get__on_top_level(void) {
  return get_dynamic_slot(dyna_idx__on_top_level);
}
static void define__on_top_level(NODE *node) {
  define_dynamic_slot(dyna_idx__on_top_level, node);
}
static int dyna_idx__objects;
static NODE *get__objects(void) {
  return get_dynamic_cell(dyna_idx__objects);
}
static void set__objects(NODE *node) {
  set_dynamic_cell(dyna_idx__objects, node);
}
static void define__objects(NODE *node) {
  define_dynamic_cell(dyna_idx__objects, node);
}
static int dyna_idx__libraries;
static NODE *get__libraries(void) {
  return get_dynamic_cell(dyna_idx__libraries);
}
static void set__libraries(NODE *node) {
  set_dynamic_cell(dyna_idx__libraries, node);
}
static void define__libraries(NODE *node) {
  define_dynamic_cell(dyna_idx__libraries, node);
}
static int dyna_idx__do_link;
static NODE *get__do_link(void) {
  return get_dynamic_cell(dyna_idx__do_link);
}
static void set__do_link(NODE *node) {
  set_dynamic_cell(dyna_idx__do_link, node);
}
static void define__do_link(NODE *node) {
  define_dynamic_cell(dyna_idx__do_link, node);
}
static int dyna_idx__last_modification_time;
static NODE *get__last_modification_time(void) {
  return get_dynamic_cell(dyna_idx__last_modification_time);
}
static void set__last_modification_time(NODE *node) {
  set_dynamic_cell(dyna_idx__last_modification_time, node);
}
static void define__last_modification_time(NODE *node) {
  define_dynamic_cell(dyna_idx__last_modification_time, node);
}
static NODE *func__66_1_resolve_filename;
static void entry__66_1_resolve_filename(void);
static FRAME_INFO frame__66_1_resolve_filename = {3, {"filename", "libname", "libpath"}};
static void cont__66_2(void);
static NODE *func__66_3;
static void entry__66_3(void);
static FRAME_INFO frame__66_3 = {0, {}};
static NODE *func__66_4;
static void entry__66_4(void);
static FRAME_INFO frame__66_4 = {1, {"path"}};
static void cont__66_5(void);
static NODE *func__66_6;
static void entry__66_6(void);
static FRAME_INFO frame__66_6 = {1, {"path"}};
static void cont__66_7(void);
static NODE *func__66_8;
static void entry__66_8(void);
static FRAME_INFO frame__66_8 = {1, {"entry"}};
static void cont__66_9(void);
static NODE *func__66_10;
static void entry__66_10(void);
static FRAME_INFO frame__66_10 = {2, {"entry", "name"}};
static void cont__66_11(void);
static void cont__66_12(void);
static NODE *func__66_13;
static void entry__66_13(void);
static FRAME_INFO frame__66_13 = {2, {"name", "entry"}};
static void cont__66_14(void);
static void cont__66_15(void);
static void cont__66_16(void);
static void cont__66_17(void);
static void cont__66_18(void);
static void cont__66_19(void);
static NODE *func__66_20;
static void entry__66_20(void);
static FRAME_INFO frame__66_20 = {1, {"libname"}};
static NODE *string__66_21;
static NODE *string__66_22;
static void cont__66_23(void);
static void cont__66_24(void);
static void cont__66_25(void);
static void cont__66_26(void);
static NODE *func__67_1_add_module_infos;
static void entry__67_1_add_module_infos(void);
static FRAME_INFO frame__67_1_add_module_infos = {7, {"path", "mod_path", "return", "entries", "filenames", "directories", "modules"}};
static void cont__67_2(void);
static void cont__67_3(void);
static NODE *func__67_4;
static void entry__67_4(void);
static FRAME_INFO frame__67_4 = {6, {"entry", "directories", "filenames", "modules", "mod_path", "name"}};
static void cont__67_5(void);
static NODE *func__67_6;
static void entry__67_6(void);
static FRAME_INFO frame__67_6 = {3, {"entry", "name", "directories"}};
static void cont__67_7(void);
static NODE *func__67_8;
static void entry__67_8(void);
static FRAME_INFO frame__67_8 = {2, {"name", "directories"}};
static void cont__67_9(void);
static NODE *func__67_10;
static void entry__67_10(void);
static FRAME_INFO frame__67_10 = {2, {"directories", "name"}};
static void cont__67_11(void);
static NODE *func__67_12;
static void entry__67_12(void);
static FRAME_INFO frame__67_12 = {4, {"name", "filenames", "modules", "mod_path"}};
static NODE *string__67_13;
static void cont__67_14(void);
static NODE *func__67_15;
static void entry__67_15(void);
static FRAME_INFO frame__67_15 = {9, {"name", "filenames", "modules", "mod_path", "submodule_name", "meta_level", "stored_level", "basename", "mod_name"}};
static NODE *string__67_16;
static void cont__67_17(void);
static void cont__67_18(void);
static void cont__67_19(void);
static void cont__67_20(void);
static void cont__67_21(void);
static void cont__67_22(void);
static void cont__67_23(void);
static void cont__67_24(void);
static void cont__67_25(void);
static void cont__67_26(void);
static void cont__67_27(void);
static NODE *func__67_28;
static void entry__67_28(void);
static FRAME_INFO frame__67_28 = {2, {"stored_level", "meta_level"}};
static void cont__67_29(void);
static void cont__67_30(void);
static NODE *func__67_31;
static void entry__67_31(void);
static FRAME_INFO frame__67_31 = {2, {"submodule_name", "meta_level"}};
static void cont__67_32(void);
static void cont__67_33(void);
static void cont__67_34(void);
static void cont__67_35(void);
static void cont__67_36(void);
static void cont__67_37(void);
static void cont__67_38(void);
static NODE *func__67_39;
static void entry__67_39(void);
static FRAME_INFO frame__67_39 = {3, {"filename", "filenames", "mod_path"}};
static void cont__67_40(void);
static NODE *func__67_41;
static void entry__67_41(void);
static FRAME_INFO frame__67_41 = {3, {"filename", "filenames", "mod_path"}};
static NODE *string__67_42;
static void cont__67_43(void);
static NODE *func__67_44;
static void entry__67_44(void);
static FRAME_INFO frame__67_44 = {9, {"filenames", "filename", "mod_path", "maybe_push_common", "name", "mod_name", "platform", "parent", "files"}};
static NODE *func__67_45_maybe_push_common;
static void entry__67_45_maybe_push_common(void);
static FRAME_INFO frame__67_45_maybe_push_common = {5, {"plat", "name", "filenames", "files", "common_name"}};
static NODE *string__67_46;
static void cont__67_47(void);
static void cont__67_48(void);
static NODE *func__67_49;
static void entry__67_49(void);
static FRAME_INFO frame__67_49 = {2, {"files", "common_name"}};
static void cont__67_50(void);
static void cont__67_51(void);
static void cont__67_52(void);
static void cont__67_53(void);
static void cont__67_54(void);
static void cont__67_55(void);
static void cont__67_56(void);
static NODE *func__67_57;
static void entry__67_57(void);
static FRAME_INFO frame__67_57 = {1, {"platform"}};
static NODE *string__67_58;
static NODE *string__67_59;
static void cont__67_60(void);
static void cont__67_61(void);
static void cont__67_62(void);
static void cont__67_63(void);
static NODE *func__67_64;
static void entry__67_64(void);
static FRAME_INFO frame__67_64 = {2, {"parent", "maybe_push_common"}};
static void cont__67_65(void);
static void cont__67_66(void);
static NODE *func__67_67;
static void entry__67_67(void);
static FRAME_INFO frame__67_67 = {2, {"maybe_push_common", "parent"}};
static void cont__67_68(void);
static void cont__67_69(void);
static void cont__67_70(void);
static void cont__67_71(void);
static void cont__67_72(void);
static void cont__67_73(void);
static void cont__67_74(void);
static void cont__67_75(void);
static void cont__67_76(void);
static NODE *func__67_77;
static void entry__67_77(void);
static FRAME_INFO frame__67_77 = {3, {"return", "directories", "modules"}};
static void cont__67_78(void);
static NODE *func__68_1_lookup;
static void entry__68_1_lookup(void);
static FRAME_INFO frame__68_1_lookup = {3, {"mod_filename", "mod_name", "info"}};
static void cont__68_2(void);
static void cont__68_3(void);
static NODE *func__68_4;
static void entry__68_4(void);
static FRAME_INFO frame__68_4 = {1, {"info"}};
static NODE *func__68_5;
static void entry__68_5(void);
static FRAME_INFO frame__68_5 = {2, {"mod_filename", "mod_name"}};
static void cont__68_6(void);
static void cont__68_7(void);
static void cont__68_8(void);
static void cont__68_9(void);
static void cont__68_10(void);
static void cont__68_11(void);
static NODE *func__69_1_CC;
static void entry__69_1_CC(void);
static FRAME_INFO frame__69_1_CC = {1, {"args"}};
static NODE *func__69_2;
static void entry__69_2(void);
static FRAME_INFO frame__69_2 = {1, {"args"}};
static void cont__69_3(void);
static void cont__69_4(void);
static void cont__69_5(void);
static NODE *func__70_1_compile_c;
static void entry__70_1_compile_c(void);
static FRAME_INFO frame__70_1_compile_c = {2, {"c_filename", "o_filename"}};
static NODE *func__70_2;
static void entry__70_2(void);
static FRAME_INFO frame__70_2 = {0, {}};
static void cont__70_3(void);
static NODE *func__70_4;
static void entry__70_4(void);
static FRAME_INFO frame__70_4 = {5, {"c_filename", "o_filename", "out", "err", "success"}};
static NODE *string__70_5;
static NODE *string__70_6;
static void cont__70_7(void);
static NODE *func__70_8;
static void entry__70_8(void);
static FRAME_INFO frame__70_8 = {2, {"c_filename", "err"}};
static void cont__70_9(void);
static NODE *string__70_10;
static NODE *string__70_11;
static void cont__70_12(void);
static void cont__70_13(void);
static NODE *func__71_1_compile_meta_module;
static void entry__71_1_compile_meta_module(void);
static FRAME_INFO frame__71_1_compile_meta_module = {3, {"mod_filename", "mod_name", "meta_level"}};
static NODE *func__71_2;
static void entry__71_2(void);
static FRAME_INFO frame__71_2 = {11, {"mod_filename", "meta_level", "meta_path", "filename", "meta_filename", "meta_c_filename", "sim_filename", "meta_info", "sim_info", "meta_c_info", "force_rebuild"}};
static void cont__71_3(void);
static void cont__71_4(void);
static void cont__71_5(void);
static void cont__71_6(void);
static void cont__71_7(void);
static void cont__71_8(void);
static NODE *string__71_9;
static void cont__71_10(void);
static void cont__71_11(void);
static void cont__71_12(void);
static void cont__71_13(void);
static void cont__71_14(void);
static void cont__71_15(void);
static void cont__71_16(void);
static NODE *func__71_17;
static void entry__71_17(void);
static FRAME_INFO frame__71_17 = {3, {"sim_info", "meta_c_info", "meta_info"}};
static void cont__71_18(void);
static NODE *func__71_19;
static void entry__71_19(void);
static FRAME_INFO frame__71_19 = {3, {"meta_c_info", "meta_info", "sim_info"}};
static void cont__71_20(void);
static NODE *func__71_21;
static void entry__71_21(void);
static FRAME_INFO frame__71_21 = {3, {"meta_c_info", "meta_info", "sim_info"}};
static void cont__71_22(void);
static void cont__71_23(void);
static void cont__71_24(void);
static NODE *func__71_25;
static void entry__71_25(void);
static FRAME_INFO frame__71_25 = {2, {"sim_info", "meta_c_info"}};
static void cont__71_26(void);
static void cont__71_27(void);
static void cont__71_28(void);
static void cont__71_29(void);
static void cont__71_30(void);
static void cont__71_31(void);
static void cont__71_32(void);
static NODE *func__71_33;
static void entry__71_33(void);
static FRAME_INFO frame__71_33 = {6, {"sim_info", "meta_c_filename", "force_rebuild", "meta_path", "modification_time", "meta_c_buf"}};
static void cont__71_34(void);
static void cont__71_35(void);
static NODE *func__71_36;
static void entry__71_36(void);
static FRAME_INFO frame__71_36 = {5, {"break", "meta_c_buf", "modification_time", "force_rebuild", "meta_path"}};
static NODE *func__71_37;
static void entry__71_37(void);
static FRAME_INFO frame__71_37 = {8, {"line", "modification_time", "force_rebuild", "break", "meta_path", "check", "command", "argument"}};
static NODE *func__71_38_check;
static void entry__71_38_check(void);
static FRAME_INFO frame__71_38_check = {5, {"data_filename", "modification_time", "force_rebuild", "break", "data_info"}};
static void cont__71_39(void);
static void cont__71_40(void);
static NODE *func__71_41;
static void entry__71_41(void);
static FRAME_INFO frame__71_41 = {2, {"modification_time", "data_info"}};
static void cont__71_42(void);
static void cont__71_43(void);
static void cont__71_44(void);
static NODE *func__71_45;
static void entry__71_45(void);
static FRAME_INFO frame__71_45 = {2, {"force_rebuild", "break"}};
static NODE *string__71_46;
static void cont__71_47(void);
static void cont__71_48(void);
static void cont__71_49(void);
static void cont__71_50(void);
static void cont__71_51(void);
static void cont__71_52(void);
static NODE *string__71_53;
static void cont__71_54(void);
static NODE *func__71_55;
static void entry__71_55(void);
static FRAME_INFO frame__71_55 = {3, {"argument", "check", "meta_path"}};
static NODE *string__71_56;
static void cont__71_57(void);
static NODE *func__71_58;
static void entry__71_58(void);
static FRAME_INFO frame__71_58 = {3, {"check", "meta_path", "argument"}};
static void cont__71_59(void);
static void cont__71_60(void);
static void cont__71_61(void);
static NODE *func__71_62;
static void entry__71_62(void);
static FRAME_INFO frame__71_62 = {2, {"check", "argument"}};
static NODE *func__71_63;
static void entry__71_63(void);
static FRAME_INFO frame__71_63 = {3, {"path", "check", "argument"}};
static void cont__71_64(void);
static void cont__71_65(void);
static void cont__71_66(void);
static NODE *func__71_67;
static void entry__71_67(void);
static FRAME_INFO frame__71_67 = {9, {"return__1", "meta_filename", "meta_path", "filename", "sim_filename", "orig_path", "out", "err", "success"}};
static void cont__71_68(void);
static void cont__71_69(void);
static void cont__71_70(void);
static void cont__71_71(void);
static void cont__71_72(void);
static void cont__71_73(void);
static NODE *func__71_74;
static void entry__71_74(void);
static FRAME_INFO frame__71_74 = {1, {"err"}};
static void cont__71_75(void);
static void cont__71_76(void);
static void cont__71_77(void);
static void cont__71_78(void);
static void cont__71_79(void);
static void cont__71_80(void);
static void cont__71_81(void);
static NODE *func__72_1_build_dependencies;
static void entry__72_1_build_dependencies(void);
static FRAME_INFO frame__72_1_build_dependencies = {5, {"mod_filename", "mod_name", "c_buf", "do_compile_c", "return"}};
static NODE *func__72_2;
static void entry__72_2(void);
static FRAME_INFO frame__72_2 = {7, {"line", "return", "mod_filename", "mod_name", "do_compile_c", "command", "argument"}};
static void cont__72_3(void);
static void cont__72_4(void);
static void cont__72_5(void);
static void cont__72_6(void);
static void cont__72_7(void);
static void cont__72_8(void);
static NODE *func__72_9;
static void entry__72_9(void);
static FRAME_INFO frame__72_9 = {4, {"argument", "mod_filename", "mod_name", "do_compile_c"}};
static void cont__72_10(void);
static NODE *func__72_11;
static void entry__72_11(void);
static FRAME_INFO frame__72_11 = {3, {"argument", "mod_filename", "mod_name"}};
static void cont__72_12(void);
static NODE *func__72_13;
static void entry__72_13(void);
static FRAME_INFO frame__72_13 = {4, {"argument", "mod_filename", "mod_name", "req_name"}};
static void cont__72_14(void);
static void cont__72_15(void);
static void cont__72_16(void);
static void cont__72_17(void);
static void cont__72_18(void);
static void cont__72_19(void);
static void cont__72_20(void);
static void cont__72_21(void);
static NODE *func__72_22;
static void entry__72_22(void);
static FRAME_INFO frame__72_22 = {2, {"argument", "do_compile_c"}};
static NODE *func__72_23;
static void entry__72_23(void);
static FRAME_INFO frame__72_23 = {0, {}};
static NODE *func__72_24;
static void entry__72_24(void);
static FRAME_INFO frame__72_24 = {0, {}};
static void cont__72_25(void);
static void cont__72_26(void);
static NODE *func__72_27;
static void entry__72_27(void);
static FRAME_INFO frame__72_27 = {1, {"argument"}};
static void cont__72_28(void);
static NODE *func__72_29;
static void entry__72_29(void);
static FRAME_INFO frame__72_29 = {2, {"do_compile_c", "argument"}};
static NODE *func__72_30;
static void entry__72_30(void);
static FRAME_INFO frame__72_30 = {1, {"argument"}};
static void cont__72_31(void);
static NODE *string__72_32;
static void cont__72_33(void);
static void cont__72_34(void);
static NODE *func__72_35;
static void entry__72_35(void);
static FRAME_INFO frame__72_35 = {2, {"do_compile_c", "argument"}};
static NODE *func__72_36;
static void entry__72_36(void);
static FRAME_INFO frame__72_36 = {1, {"argument"}};
static void cont__72_37(void);
static void cont__72_38(void);
static NODE *string__72_39;
static NODE *string__72_40;
static void cont__72_41(void);
static NODE *func__73_1_compile_module;
static void entry__73_1_compile_module(void);
static FRAME_INFO frame__73_1_compile_module = {6, {"mod_filename", "mod_name", "return", "compile_submodule", "mod_info", "o_filename"}};
static NODE *func__73_2_compile_submodule;
static void entry__73_2_compile_submodule(void);
static FRAME_INFO frame__73_2_compile_submodule = {11, {"submodule_names", "do_compile_c", "suffix", "mod_filename", "mod_name", "o_filename", "modification_time", "sim_filenames", "c_filename", "c_info", "c_buf"}};
static NODE *func__73_3;
static void entry__73_3(void);
static FRAME_INFO frame__73_3 = {8, {"submodule_name", "mod_filename", "sim_filenames", "modification_time", "meta_level", "submodule_filename", "sim_filename", "sim_info"}};
static void cont__73_4(void);
static void cont__73_5(void);
static void cont__73_6(void);
static void cont__73_7(void);
static void cont__73_8(void);
static NODE *func__73_9;
static void entry__73_9(void);
static FRAME_INFO frame__73_9 = {0, {}};
static void cont__73_10(void);
static void cont__73_11(void);
static NODE *func__73_12;
static void entry__73_12(void);
static FRAME_INFO frame__73_12 = {3, {"submodule_filename", "submodule_name", "meta_level"}};
static void cont__73_13(void);
static void cont__73_14(void);
static void cont__73_15(void);
static void cont__73_16(void);
static void cont__73_17(void);
static NODE *func__73_18;
static void entry__73_18(void);
static FRAME_INFO frame__73_18 = {2, {"modification_time", "sim_info"}};
static void cont__73_19(void);
static void cont__73_20(void);
static void cont__73_21(void);
static NODE *func__73_22;
static void entry__73_22(void);
static FRAME_INFO frame__73_22 = {2, {"modification_time", "sim_info"}};
static void cont__73_23(void);
static void cont__73_24(void);
static void cont__73_25(void);
static void cont__73_26(void);
static NODE *func__73_27;
static void entry__73_27(void);
static FRAME_INFO frame__73_27 = {1, {"c_filename"}};
static void cont__73_28(void);
static void cont__73_29(void);
static NODE *func__73_30;
static void entry__73_30(void);
static FRAME_INFO frame__73_30 = {2, {"c_info", "modification_time"}};
static void cont__73_31(void);
static NODE *func__73_32;
static void entry__73_32(void);
static FRAME_INFO frame__73_32 = {2, {"c_info", "modification_time"}};
static void cont__73_33(void);
static void cont__73_34(void);
static void cont__73_35(void);
static void cont__73_36(void);
static NODE *func__73_37;
static void entry__73_37(void);
static FRAME_INFO frame__73_37 = {9, {"return__1", "mod_name", "suffix", "sim_filenames", "c_buf", "c_filename", "do_compile_c", "o_filename", "c_source"}};
static NODE *string__73_38;
static void cont__73_39(void);
static void cont__73_40(void);
static void cont__73_41(void);
static NODE *func__73_42;
static void entry__73_42(void);
static FRAME_INFO frame__73_42 = {1, {"suffix"}};
static NODE *string__73_43;
static void cont__73_44(void);
static NODE *func__73_45;
static void entry__73_45(void);
static FRAME_INFO frame__73_45 = {1, {"sim_filenames"}};
static void cont__73_46(void);
static NODE *func__73_47;
static void entry__73_47(void);
static FRAME_INFO frame__73_47 = {1, {"c_source"}};
static void cont__73_48(void);
static void cont__73_49(void);
static void cont__73_50(void);
static NODE *func__73_51;
static void entry__73_51(void);
static FRAME_INFO frame__73_51 = {2, {"c_filename", "o_filename"}};
static void cont__73_52(void);
static NODE *func__73_53;
static void entry__73_53(void);
static FRAME_INFO frame__73_53 = {6, {"c_buf", "c_filename", "o_filename", "c_info", "do_compile_c", "o_info"}};
static void cont__73_54(void);
static void cont__73_55(void);
static void cont__73_56(void);
static NODE *func__73_57;
static void entry__73_57(void);
static FRAME_INFO frame__73_57 = {2, {"o_info", "c_info"}};
static void cont__73_58(void);
static void cont__73_59(void);
static void cont__73_60(void);
static void cont__73_61(void);
static NODE *func__73_62;
static void entry__73_62(void);
static FRAME_INFO frame__73_62 = {3, {"do_compile_c", "c_filename", "o_filename"}};
static NODE *func__73_63;
static void entry__73_63(void);
static FRAME_INFO frame__73_63 = {2, {"c_filename", "o_filename"}};
static NODE *func__73_64;
static void entry__73_64(void);
static FRAME_INFO frame__73_64 = {1, {"o_info"}};
static void cont__73_65(void);
static NODE *func__73_66;
static void entry__73_66(void);
static FRAME_INFO frame__73_66 = {1, {"o_info"}};
static void cont__73_67(void);
static void cont__73_68(void);
static void cont__73_69(void);
static NODE *func__73_70;
static void entry__73_70(void);
static FRAME_INFO frame__73_70 = {1, {"o_info"}};
static void cont__73_71(void);
static void cont__73_72(void);
static void cont__73_73(void);
static void cont__73_74(void);
static NODE *func__73_75;
static void entry__73_75(void);
static FRAME_INFO frame__73_75 = {1, {"mod_name"}};
static NODE *string__73_76;
static NODE *string__73_77;
static void cont__73_78(void);
static void cont__73_79(void);
static NODE *string__73_80;
static void cont__73_81(void);
static void cont__73_82(void);
static void cont__73_83(void);
static void cont__73_84(void);
static void cont__73_85(void);
static NODE *func__73_86;
static void entry__73_86(void);
static FRAME_INFO frame__73_86 = {3, {"compile_submodule", "mod_name", "mod_filename"}};
static void cont__73_87(void);
static void cont__73_88(void);
static void cont__73_89(void);
static void cont__73_90(void);
static NODE *func__73_91;
static void entry__73_91(void);
static FRAME_INFO frame__73_91 = {1, {"mod_filename"}};
static void cont__73_92(void);
static void cont__73_93(void);
static NODE *func__73_94;
static void entry__73_94(void);
static FRAME_INFO frame__73_94 = {3, {"mod_info", "compile_submodule", "mod_filename"}};
static NODE *func__73_95;
static void entry__73_95(void);
static FRAME_INFO frame__73_95 = {4, {"mod_info", "compile_submodule", "best_platform", "best_priority"}};
static NODE *func__73_96;
static void entry__73_96(void);
static FRAME_INFO frame__73_96 = {5, {"platform", "filenames", "best_priority", "best_platform", "priority"}};
static void cont__73_97(void);
static void cont__73_98(void);
static NODE *func__73_99;
static void entry__73_99(void);
static FRAME_INFO frame__73_99 = {2, {"priority", "best_priority"}};
static void cont__73_100(void);
static void cont__73_101(void);
static NODE *func__73_102;
static void entry__73_102(void);
static FRAME_INFO frame__73_102 = {4, {"best_platform", "platform", "best_priority", "priority"}};
static void cont__73_103(void);
static NODE *func__73_104;
static void entry__73_104(void);
static FRAME_INFO frame__73_104 = {4, {"platform", "filenames", "compile_submodule", "best_platform"}};
static void cont__73_105(void);
static void cont__73_106(void);
static void cont__73_107(void);
static NODE *func__73_108;
static void entry__73_108(void);
static FRAME_INFO frame__73_108 = {3, {"mod_info", "mod_filename", "used_by"}};
static NODE *func__73_109;
static void entry__73_109(void);
static FRAME_INFO frame__73_109 = {6, {"supported_platform", "parent_platform", "mod_info", "used_by", "best_platform", "best_priority"}};
static NODE *func__73_110;
static void entry__73_110(void);
static FRAME_INFO frame__73_110 = {6, {"platform", "filenames", "supported_platform", "best_priority", "best_platform", "priority"}};
static void cont__73_111(void);
static void cont__73_112(void);
static NODE *func__73_113;
static void entry__73_113(void);
static FRAME_INFO frame__73_113 = {2, {"priority", "best_priority"}};
static void cont__73_114(void);
static void cont__73_115(void);
static NODE *func__73_116;
static void entry__73_116(void);
static FRAME_INFO frame__73_116 = {4, {"best_platform", "platform", "best_priority", "priority"}};
static void cont__73_117(void);
static void cont__73_118(void);
static NODE *func__73_119;
static void entry__73_119(void);
static FRAME_INFO frame__73_119 = {4, {"used_by", "best_platform", "supported_platform", "ub"}};
static void cont__73_120(void);
static void cont__73_121(void);
static void cont__73_122(void);
static void cont__73_123(void);
static void cont__73_124(void);
static NODE *func__73_125;
static void entry__73_125(void);
static FRAME_INFO frame__73_125 = {6, {"platform", "filenames", "mod_filename", "used_by", "dependency", "platforms"}};
static void cont__73_126(void);
static void cont__73_127(void);
static void cont__73_128(void);
static NODE *func__73_129;
static void entry__73_129(void);
static FRAME_INFO frame__73_129 = {2, {"platforms", "dependency"}};
static NODE *func__73_130;
static void entry__73_130(void);
static FRAME_INFO frame__73_130 = {2, {"plat", "dependency"}};
static NODE *string__73_131;
static void cont__73_132(void);
static void cont__73_133(void);
static void cont__73_134(void);
static void cont__73_135(void);
static NODE *func__74_1_compile_modules;
static void entry__74_1_compile_modules(void);
static FRAME_INFO frame__74_1_compile_modules = {4, {"path", "mod_path", "directories", "modules"}};
static void cont__74_2(void);
static void cont__74_3(void);
static NODE *func__74_4;
static void entry__74_4(void);
static FRAME_INFO frame__74_4 = {3, {"name", "path", "mod_path"}};
static void cont__74_5(void);
static void cont__74_6(void);
static void cont__74_7(void);
static NODE *func__74_8;
static void entry__74_8(void);
static FRAME_INFO frame__74_8 = {3, {"name", "path", "mod_path"}};
static void cont__74_9(void);
static void cont__74_10(void);
static NODE *func__76_1_show_file_list;
static void entry__76_1_show_file_list(void);
static FRAME_INFO frame__76_1_show_file_list = {0, {}};
static NODE *func__76_2;
static void entry__76_2(void);
static FRAME_INFO frame__76_2 = {1, {"path"}};
static NODE *string__76_3;
static void cont__76_4(void);
static void cont__76_5(void);
static NODE *func__76_6;
static void entry__76_6(void);
static FRAME_INFO frame__76_6 = {1, {"path"}};
static NODE *string__76_7;
static void cont__76_8(void);
static void cont__76_9(void);
static void cont__76_10(void);
static NODE *string__76_11;
static void cont__76_12(void);
static void cont__76_13(void);
static NODE *string__76_14;
static NODE *func__77_1_library_paths_and_file_list;
static void entry__77_1_library_paths_and_file_list(void);
static FRAME_INFO frame__77_1_library_paths_and_file_list = {4, {"library_paths", "object_files", "library_files", "paths"}};
static void cont__77_2(void);
static void cont__77_3(void);
static void cont__77_4(void);
static NODE *func__77_5;
static void entry__77_5(void);
static FRAME_INFO frame__77_5 = {2, {"paths", "library_paths"}};
static void cont__77_6(void);
static NODE *func__77_7;
static void entry__77_7(void);
static FRAME_INFO frame__77_7 = {2, {"path", "library_paths"}};
static NODE *string__77_8;
static void cont__77_9(void);
static void cont__77_10(void);
static void cont__77_11(void);
static NODE *func__77_12;
static void entry__77_12(void);
static FRAME_INFO frame__77_12 = {1, {"library_paths"}};
static void cont__77_13(void);
static NODE *string__77_14;
static void cont__77_15(void);
static NODE *func__77_16;
static void entry__77_16(void);
static FRAME_INFO frame__77_16 = {2, {"object", "object_files"}};
static void cont__77_17(void);
static void cont__77_18(void);
static NODE *func__77_19;
static void entry__77_19(void);
static FRAME_INFO frame__77_19 = {2, {"library", "library_files"}};
static void cont__77_20(void);
static NODE *func__77_21;
static void entry__77_21(void);
static FRAME_INFO frame__77_21 = {1, {"library"}};
static void cont__77_22(void);
static NODE *string__77_23;
static void cont__77_24(void);
static NODE *func__77_25;
static void entry__77_25(void);
static FRAME_INFO frame__77_25 = {1, {"library"}};
static NODE *string__77_26;
static NODE *string__77_27;
static void cont__77_28(void);
static NODE *func__77_29;
static void entry__77_29(void);
static FRAME_INFO frame__77_29 = {1, {"library"}};
static NODE *string__77_30;
static void cont__77_31(void);
static void cont__77_32(void);
static NODE *func__77_33;
static void entry__77_33(void);
static FRAME_INFO frame__77_33 = {1, {"library"}};
static void cont__77_34(void);
static NODE *func__77_35;
static void entry__77_35(void);
static FRAME_INFO frame__77_35 = {1, {"library"}};
static void cont__77_36(void);
static void cont__77_37(void);
static void cont__77_38(void);
static NODE *func__77_39;
static void entry__77_39(void);
static FRAME_INFO frame__77_39 = {1, {"library"}};
static void cont__77_40(void);
static void cont__77_41(void);
static void cont__77_42(void);
static void cont__77_43(void);
static void cont__77_44(void);
static void cont__77_45(void);
static NODE *func__78_1_create_imports;
static void entry__78_1_create_imports(void);
static FRAME_INFO frame__78_1_create_imports = {5, {"source", "already_checked", "collect_declarations", "imports", "first_part"}};
static NODE *func__78_2_collect_declarations;
static void entry__78_2_collect_declarations(void);
static FRAME_INFO frame__78_2_collect_declarations = {4, {"buf", "already_checked", "collect_declarations", "s"}};
static NODE *func__78_3;
static void entry__78_3(void);
static FRAME_INFO frame__78_3 = {6, {"idx", "chr", "s", "buf", "already_checked", "collect_declarations"}};
static void cont__78_4(void);
static NODE *func__78_5;
static void entry__78_5(void);
static FRAME_INFO frame__78_5 = {6, {"chr", "buf", "s", "idx", "already_checked", "collect_declarations"}};
static void cont__78_6(void);
static NODE *func__78_7;
static void entry__78_7(void);
static FRAME_INFO frame__78_7 = {1, {"chr"}};
static void cont__78_8(void);
static NODE *func__78_9;
static void entry__78_9(void);
static FRAME_INFO frame__78_9 = {1, {"chr"}};
static void cont__78_10(void);
static void cont__78_11(void);
static void cont__78_12(void);
static NODE *func__78_13;
static void entry__78_13(void);
static FRAME_INFO frame__78_13 = {6, {"buf", "s", "idx", "already_checked", "collect_declarations", "symbol"}};
static void cont__78_14(void);
static void cont__78_15(void);
static void cont__78_16(void);
static NODE *func__78_17;
static void entry__78_17(void);
static FRAME_INFO frame__78_17 = {4, {"already_checked", "symbol", "collect_declarations", "declaration"}};
static void cont__78_18(void);
static void cont__78_19(void);
static void cont__78_20(void);
static NODE *func__78_21;
static void entry__78_21(void);
static FRAME_INFO frame__78_21 = {3, {"declaration", "collect_declarations", "do_import"}};
static void cont__78_22(void);
static void cont__78_23(void);
static void cont__78_24(void);
static NODE *func__78_25;
static void entry__78_25(void);
static FRAME_INFO frame__78_25 = {1, {"declaration"}};
static NODE *string__78_26;
static void cont__78_27(void);
static void cont__78_28(void);
static NODE *func__78_29;
static void entry__78_29(void);
static FRAME_INFO frame__78_29 = {1, {"declaration"}};
static NODE *string__78_30;
static void cont__78_31(void);
static void cont__78_32(void);
static void cont__78_33(void);
static void cont__78_34(void);
static NODE *func__78_35;
static void entry__78_35(void);
static FRAME_INFO frame__78_35 = {2, {"declaration", "collect_declarations"}};
static void cont__78_36(void);
static void cont__78_37(void);
static NODE *func__78_38;
static void entry__78_38(void);
static FRAME_INFO frame__78_38 = {1, {"declaration"}};
static void cont__78_39(void);
static void cont__78_40(void);
static NODE *func__78_41;
static void entry__78_41(void);
static FRAME_INFO frame__78_41 = {2, {"collect_declarations", "declaration"}};
static void cont__78_42(void);
static NODE *func__78_43;
static void entry__78_43(void);
static FRAME_INFO frame__78_43 = {2, {"declaration", "collect_declarations"}};
static NODE *string__78_44;
static void cont__78_45(void);
static NODE *func__78_46;
static void entry__78_46(void);
static FRAME_INFO frame__78_46 = {2, {"declaration", "collect_declarations"}};
static void cont__78_47(void);
static void cont__78_48(void);
static NODE *func__78_49;
static void entry__78_49(void);
static FRAME_INFO frame__78_49 = {2, {"line", "collect_declarations"}};
static void cont__78_50(void);
static void cont__78_51(void);
static NODE *func__78_52;
static void entry__78_52(void);
static FRAME_INFO frame__78_52 = {2, {"collect_declarations", "declaration"}};
static void cont__78_53(void);
static NODE *func__78_54;
static void entry__78_54(void);
static FRAME_INFO frame__78_54 = {0, {}};
static NODE *string__78_55;
static void cont__78_56(void);
static NODE *func__78_57;
static void entry__78_57(void);
static FRAME_INFO frame__78_57 = {3, {"chr", "s", "idx"}};
static void cont__78_58(void);
static NODE *func__78_59;
static void entry__78_59(void);
static FRAME_INFO frame__78_59 = {1, {"chr"}};
static void cont__78_60(void);
static void cont__78_61(void);
static NODE *func__78_62;
static void entry__78_62(void);
static FRAME_INFO frame__78_62 = {2, {"s", "idx"}};
static NODE *func__78_63;
static void entry__78_63(void);
static FRAME_INFO frame__78_63 = {2, {"collect_declarations", "source"}};
static void cont__78_64(void);
static NODE *string__78_65;
static void cont__78_66(void);
static void cont__78_67(void);
static void cont__78_68(void);
static void cont__78_69(void);
static void cont__78_70(void);
static void cont__78_71(void);
static void cont__78_72(void);
static void cont__78_73(void);
static NODE *func__78_74;
static void entry__78_74(void);
static FRAME_INFO frame__78_74 = {0, {}};
static NODE *string__78_75;
static NODE *func__79_1_compile_exe;
static void entry__79_1_compile_exe(void);
static FRAME_INFO frame__79_1_compile_exe = {4, {"body", "return__1", "mod_filename", "mod_name"}};
static void cont__79_2(void);
static NODE *func__79_3;
static void entry__79_3(void);
static FRAME_INFO frame__79_3 = {0, {}};
static NODE *string__79_4;
static void cont__79_5(void);
static void cont__79_6(void);
static NODE *func__79_7;
static void entry__79_7(void);
static FRAME_INFO frame__79_7 = {0, {}};
static NODE *string__79_8;
static void cont__79_9(void);
static void cont__79_10(void);
static void cont__79_11(void);
static void cont__79_12(void);
static void cont__79_13(void);
static NODE *func__80_1_dump_source_or_check;
static void entry__80_1_dump_source_or_check(void);
static FRAME_INFO frame__80_1_dump_source_or_check = {0, {}};
static NODE *func__80_2;
static void entry__80_2(void);
static FRAME_INFO frame__80_2 = {3, {"mod_filename", "mod_name", "return__1"}};
static void cont__80_3(void);
static void cont__80_4(void);
static NODE *func__81_1_print_c;
static void entry__81_1_print_c(void);
static FRAME_INFO frame__81_1_print_c = {0, {}};
static NODE *func__81_2;
static void entry__81_2(void);
static FRAME_INFO frame__81_2 = {4, {"mod_filename", "mod_name", "c_source", "c_buf"}};
static void cont__81_3(void);
static NODE *func__81_4;
static void entry__81_4(void);
static FRAME_INFO frame__81_4 = {1, {"mod_name"}};
static void cont__81_5(void);
static void cont__81_6(void);
static void cont__81_7(void);
static NODE *func__81_8;
static void entry__81_8(void);
static FRAME_INFO frame__81_8 = {2, {"return__1", "mod_name"}};
static void cont__81_9(void);
static void cont__81_10(void);
static void cont__81_11(void);
static void cont__81_12(void);
static void cont__81_13(void);
static void cont__81_14(void);
static NODE *func__81_15;
static void entry__81_15(void);
static FRAME_INFO frame__81_15 = {1, {"c_source"}};
static void cont__81_16(void);
static void cont__81_17(void);
static NODE *func__81_18;
static void entry__81_18(void);
static FRAME_INFO frame__81_18 = {0, {}};
static NODE *string__81_19;
static NODE *func__82_1_list_dependencies;
static void entry__82_1_list_dependencies(void);
static FRAME_INFO frame__82_1_list_dependencies = {1, {"prefix_path"}};
static void cont__82_2(void);
static NODE *func__82_3;
static void entry__82_3(void);
static FRAME_INFO frame__82_3 = {4, {"supported_platform", "parent_platform", "platform", "priority"}};
static NODE *func__82_4;
static void entry__82_4(void);
static FRAME_INFO frame__82_4 = {4, {"break", "platform", "priority", "supported_platform"}};
static NODE *func__82_5;
static void entry__82_5(void);
static FRAME_INFO frame__82_5 = {5, {"platform", "break", "priority", "supported_platform", "plat"}};
static void cont__82_6(void);
static void cont__82_7(void);
static void cont__82_8(void);
static void cont__82_9(void);
static void cont__82_10(void);
static void cont__82_11(void);
static void cont__82_12(void);
static void cont__82_13(void);
static void cont__82_14(void);
static void cont__82_15(void);
static NODE *func__82_16;
static void entry__82_16(void);
static FRAME_INFO frame__82_16 = {1, {"return__1"}};
static NODE *func__82_17;
static void entry__82_17(void);
static FRAME_INFO frame__82_17 = {0, {}};
static NODE *string__82_18;
static void cont__82_19(void);
static void cont__82_20(void);
static void cont__82_21(void);
static void cont__82_22(void);
static NODE *func__82_23;
static void entry__82_23(void);
static FRAME_INFO frame__82_23 = {0, {}};
static NODE *func__82_24;
static void entry__82_24(void);
static FRAME_INFO frame__82_24 = {2, {"mod_filename", "mod_name"}};
static NODE *func__82_25;
static void entry__82_25(void);
static FRAME_INFO frame__82_25 = {1, {"mod_filename"}};
static void cont__82_26(void);
static void cont__82_27(void);
static NODE *string__82_28;
static void cont__82_29(void);
static NODE *string__82_30;
static void cont__82_31(void);
static NODE *string__82_32;
static void cont__82_33(void);
static void cont__82_34(void);
static NODE *func__82_35;
static void entry__82_35(void);
static FRAME_INFO frame__82_35 = {2, {"filename", "prefix_path"}};
static void cont__82_36(void);
static void cont__82_37(void);
static NODE *func__83_1_build_codeblocks_project;
static void entry__83_1_build_codeblocks_project(void);
static FRAME_INFO frame__83_1_build_codeblocks_project = {0, {}};
static NODE *func__83_2;
static void entry__83_2(void);
static FRAME_INFO frame__83_2 = {10, {"mod_filename", "mod_name", "codeblocks_path", "info", "basename", "prefix_path", "depth", "path_prefix", "cbp_filename", "buf"}};
static NODE *string__83_3;
static void cont__83_4(void);
static void cont__83_5(void);
static void cont__83_6(void);
static NODE *func__83_7;
static void entry__83_7(void);
static FRAME_INFO frame__83_7 = {1, {"codeblocks_path"}};
static NODE *string__83_8;
static NODE *string__83_9;
static void cont__83_10(void);
static void cont__83_11(void);
static NODE *func__83_12;
static void entry__83_12(void);
static FRAME_INFO frame__83_12 = {1, {"codeblocks_path"}};
static NODE *string__83_13;
static void cont__83_14(void);
static void cont__83_15(void);
static void cont__83_16(void);
static void cont__83_17(void);
static void cont__83_18(void);
static void cont__83_19(void);
static void cont__83_20(void);
static void cont__83_21(void);
static void cont__83_22(void);
static NODE *string__83_23;
static void cont__83_24(void);
static NODE *string__83_25;
static NODE *string__83_26;
static void cont__83_27(void);
static void cont__83_28(void);
static NODE *string__83_29;
static NODE *string__83_30;
static NODE *string__83_31;
static void cont__83_32(void);
static void cont__83_33(void);
static NODE *func__83_34;
static void entry__83_34(void);
static FRAME_INFO frame__83_34 = {2, {"filename", "buf"}};
static NODE *string__83_35;
static NODE *string__83_36;
static void cont__83_37(void);
static void cont__83_38(void);
static void cont__83_39(void);
static void cont__83_40(void);
static void cont__83_41(void);
static void cont__83_42(void);
static NODE *string__83_43;
static NODE *string__83_44;
static NODE *string__83_45;
static NODE *string__83_46;
static NODE *string__83_47;
static NODE *string__83_48;
static NODE *string__83_49;
static NODE *string__83_50;
static void cont__83_51(void);
static void cont__83_52(void);
static NODE *func__83_53;
static void entry__83_53(void);
static FRAME_INFO frame__83_53 = {4, {"filename", "prefix_path", "buf", "path_prefix"}};
static void cont__83_54(void);
static void cont__83_55(void);
static void cont__83_56(void);
static NODE *string__83_57;
static NODE *string__83_58;
static void cont__83_59(void);
static void cont__83_60(void);
static void cont__83_61(void);
static NODE *string__83_62;
static void cont__83_63(void);
static NODE *func__84_1_build_library;
static void entry__84_1_build_library(void);
static FRAME_INFO frame__84_1_build_library = {1, {"return__1"}};
static NODE *string__84_2;
static void cont__84_3(void);
static NODE *func__84_4;
static void entry__84_4(void);
static FRAME_INFO frame__84_4 = {0, {}};
static NODE *string__84_5;
static void cont__84_6(void);
static NODE *func__84_7;
static void entry__84_7(void);
static FRAME_INFO frame__84_7 = {0, {}};
static NODE *func__84_8;
static void entry__84_8(void);
static FRAME_INFO frame__84_8 = {5, {"version", "so_version", "version_filename", "base_filename", "lib_filename"}};
static NODE *string__84_9;
static void cont__84_10(void);
static void cont__84_11(void);
static NODE *func__84_12;
static void entry__84_12(void);
static FRAME_INFO frame__84_12 = {3, {"version", "version_filename", "so_version"}};
static void cont__84_13(void);
static void cont__84_14(void);
static void cont__84_15(void);
static void cont__84_16(void);
static void cont__84_17(void);
static void cont__84_18(void);
static void cont__84_19(void);
static void cont__84_20(void);
static NODE *func__84_21;
static void entry__84_21(void);
static FRAME_INFO frame__84_21 = {2, {"base_filename", "version"}};
static void cont__84_22(void);
static NODE *string__84_23;
static void cont__84_24(void);
static NODE *func__84_25;
static void entry__84_25(void);
static FRAME_INFO frame__84_25 = {2, {"base_filename", "version"}};
static NODE *string__84_26;
static void cont__84_27(void);
static void cont__84_28(void);
static NODE *func__84_29;
static void entry__84_29(void);
static FRAME_INFO frame__84_29 = {2, {"base_filename", "version"}};
static NODE *string__84_30;
static void cont__84_31(void);
static void cont__84_32(void);
static NODE *func__84_33;
static void entry__84_33(void);
static FRAME_INFO frame__84_33 = {1, {"base_filename"}};
static NODE *string__84_34;
static void cont__84_35(void);
static NODE *string__84_36;
static NODE *string__84_37;
static void cont__84_38(void);
static NODE *func__84_39;
static void entry__84_39(void);
static FRAME_INFO frame__84_39 = {1, {"lib_filename"}};
static NODE *string__84_40;
static void cont__84_41(void);
static void cont__84_42(void);
static void cont__84_43(void);
static void cont__84_44(void);
static NODE *func__84_45;
static void entry__84_45(void);
static FRAME_INFO frame__84_45 = {2, {"lib_filename", "info"}};
static void cont__84_46(void);
static void cont__84_47(void);
static NODE *func__84_48;
static void entry__84_48(void);
static FRAME_INFO frame__84_48 = {1, {"info"}};
static void cont__84_49(void);
static void cont__84_50(void);
static void cont__84_51(void);
static NODE *func__84_52;
static void entry__84_52(void);
static FRAME_INFO frame__84_52 = {0, {}};
static void cont__84_53(void);
static NODE *func__84_54;
static void entry__84_54(void);
static FRAME_INFO frame__84_54 = {3, {"base_filename", "so_version", "lib_filename"}};
static NODE *func__84_55;
static void entry__84_55(void);
static FRAME_INFO frame__84_55 = {0, {}};
static NODE *string__84_56;
static void cont__84_57(void);
static void cont__84_58(void);
static NODE *string__84_59;
static void cont__84_60(void);
static NODE *func__84_61;
static void entry__84_61(void);
static FRAME_INFO frame__84_61 = {6, {"base_filename", "so_version", "lib_filename", "out", "err", "success"}};
static NODE *string__84_62;
static void cont__84_63(void);
static void cont__84_64(void);
static NODE *string__84_65;
static void cont__84_66(void);
static NODE *func__84_67;
static void entry__84_67(void);
static FRAME_INFO frame__84_67 = {1, {"err"}};
static void cont__84_68(void);
static NODE *func__84_69;
static void entry__84_69(void);
static FRAME_INFO frame__84_69 = {4, {"lib_filename", "out", "err", "success"}};
static void cont__84_70(void);
static NODE *string__84_71;
static void cont__84_72(void);
static void cont__84_73(void);
static NODE *func__84_74;
static void entry__84_74(void);
static FRAME_INFO frame__84_74 = {1, {"err"}};
static void cont__84_75(void);
static NODE *func__84_76;
static void entry__84_76(void);
static FRAME_INFO frame__84_76 = {6, {"base_filename", "so_version", "lib_filename", "out", "err", "success"}};
static NODE *string__84_77;
static void cont__84_78(void);
static void cont__84_79(void);
static void cont__84_80(void);
static NODE *string__84_81;
static void cont__84_82(void);
static NODE *func__84_83;
static void entry__84_83(void);
static FRAME_INFO frame__84_83 = {1, {"err"}};
static void cont__84_84(void);
static NODE *func__84_85;
static void entry__84_85(void);
static FRAME_INFO frame__84_85 = {4, {"lib_filename", "out", "err", "success"}};
static void cont__84_86(void);
static void cont__84_87(void);
static NODE *func__84_88;
static void entry__84_88(void);
static FRAME_INFO frame__84_88 = {1, {"err"}};
static void cont__84_89(void);
static void cont__84_90(void);
static NODE *func__85_1_maybe_compile_c_file;
static void entry__85_1_maybe_compile_c_file(void);
static FRAME_INFO frame__85_1_maybe_compile_c_file = {5, {"filename", "c_filename", "o_filename", "c_info", "o_info"}};
static void cont__85_2(void);
static void cont__85_3(void);
static void cont__85_4(void);
static void cont__85_5(void);
static NODE *func__85_6;
static void entry__85_6(void);
static FRAME_INFO frame__85_6 = {1, {"c_filename"}};
static NODE *string__85_7;
static NODE *string__85_8;
static void cont__85_9(void);
static void cont__85_10(void);
static void cont__85_11(void);
static void cont__85_12(void);
static NODE *func__85_13;
static void entry__85_13(void);
static FRAME_INFO frame__85_13 = {2, {"o_info", "c_info"}};
static void cont__85_14(void);
static void cont__85_15(void);
static void cont__85_16(void);
static void cont__85_17(void);
static NODE *func__85_18;
static void entry__85_18(void);
static FRAME_INFO frame__85_18 = {3, {"filename", "c_filename", "o_filename"}};
static NODE *func__85_19;
static void entry__85_19(void);
static FRAME_INFO frame__85_19 = {1, {"filename"}};
static NODE *string__85_20;
static void cont__85_21(void);
static void cont__85_22(void);
static NODE *func__87_1_format_number;
static void entry__87_1_format_number(void);
static FRAME_INFO frame__87_1_format_number = {4, {"val", "n", "m", "ac"}};
static void cont__87_2(void);
static NODE *func__87_3;
static void entry__87_3(void);
static FRAME_INFO frame__87_3 = {4, {"break", "val", "ac", "n"}};
static NODE *func__87_4;
static void entry__87_4(void);
static FRAME_INFO frame__87_4 = {6, {"i", "chr", "ac", "val", "n", "break"}};
static void cont__87_5(void);
static NODE *func__87_6;
static void entry__87_6(void);
static FRAME_INFO frame__87_6 = {5, {"ac", "val", "i", "n", "break"}};
static void cont__87_7(void);
static void cont__87_8(void);
static void cont__87_9(void);
static void cont__87_10(void);
static NODE *func__87_11;
static void entry__87_11(void);
static FRAME_INFO frame__87_11 = {3, {"val", "n", "i"}};
static void cont__87_12(void);
static void cont__87_13(void);
static NODE *string__87_14;
static void cont__87_15(void);
static void cont__87_16(void);
static void cont__87_17(void);
static void cont__87_18(void);
static void cont__87_19(void);
static void cont__87_20(void);
static NODE *func__87_21;
static void entry__87_21(void);
static FRAME_INFO frame__87_21 = {3, {"val", "m", "ac"}};
static void cont__87_22(void);
static NODE *string__87_23;
static void cont__87_24(void);
static void cont__87_25(void);
static NODE *func__87_26;
static void entry__87_26(void);
static FRAME_INFO frame__87_26 = {3, {"m", "ac", "val"}};
static void cont__87_27(void);
static NODE *func__87_28;
static void entry__87_28(void);
static FRAME_INFO frame__87_28 = {3, {"val", "ac", "m"}};
static void cont__87_29(void);
static void cont__87_30(void);
static void cont__87_31(void);
static void cont__87_32(void);
static void cont__87_33(void);
static NODE *func__88_1_sim2c__write_timing_info;
static void entry__88_1_sim2c__write_timing_info(void);
static FRAME_INFO frame__88_1_sim2c__write_timing_info = {3, {"description", "filename", "new_t"}};
static void cont__88_2(void);
static void cont__88_3(void);
static NODE *func__88_4;
static void entry__88_4(void);
static FRAME_INFO frame__88_4 = {3, {"filename", "description", "new_t"}};
static void cont__88_5(void);
static void cont__88_6(void);
static void cont__88_7(void);
static void cont__88_8(void);
static void cont__88_9(void);
static void cont__88_10(void);
static void cont__88_11(void);
static NODE *string__88_12;
static NODE *func__88_13;
static void entry__88_13(void);
static FRAME_INFO frame__88_13 = {2, {"description", "new_t"}};
static void cont__88_14(void);
static void cont__88_15(void);
static NODE *string__88_16;
static void cont__88_17(void);
static void cont__88_18(void);
static NODE *get__sim2c__write_timing_info(void) {
  return var.sim2c__write_timing_info;
}
static NODE *func__89_1_build_executable;
static void entry__89_1_build_executable(void);
static FRAME_INFO frame__89_1_build_executable = {0, {}};
static NODE *func__89_2;
static void entry__89_2(void);
static FRAME_INFO frame__89_2 = {9, {"mod_filename", "mod_name", "exe_filename", "c_filename", "o_filename", "sim_info", "c_info", "c_buf", "zz"}};
static void cont__89_3(void);
static void cont__89_4(void);
static NODE *func__89_5;
static void entry__89_5(void);
static FRAME_INFO frame__89_5 = {1, {"mod_filename"}};
static NODE *string__89_6;
static void cont__89_7(void);
static NODE *func__89_8;
static void entry__89_8(void);
static FRAME_INFO frame__89_8 = {1, {"mod_filename"}};
static void cont__89_9(void);
static NODE *func__89_10;
static void entry__89_10(void);
static FRAME_INFO frame__89_10 = {1, {"exe_filename"}};
static NODE *string__89_11;
static void cont__89_12(void);
static void cont__89_13(void);
static void cont__89_14(void);
static void cont__89_15(void);
static void cont__89_16(void);
static void cont__89_17(void);
static NODE *func__89_18;
static void entry__89_18(void);
static FRAME_INFO frame__89_18 = {2, {"c_info", "sim_info"}};
static void cont__89_19(void);
static NODE *func__89_20;
static void entry__89_20(void);
static FRAME_INFO frame__89_20 = {2, {"c_info", "sim_info"}};
static void cont__89_21(void);
static void cont__89_22(void);
static void cont__89_23(void);
static void cont__89_24(void);
static void cont__89_25(void);
static NODE *func__89_26;
static void entry__89_26(void);
static FRAME_INFO frame__89_26 = {6, {"return__1", "mod_name", "c_buf", "c_filename", "o_filename", "c_source"}};
static void cont__89_27(void);
static void cont__89_28(void);
static NODE *func__89_29;
static void entry__89_29(void);
static FRAME_INFO frame__89_29 = {0, {}};
static NODE *string__89_30;
static void cont__89_31(void);
static NODE *func__89_32;
static void entry__89_32(void);
static FRAME_INFO frame__89_32 = {0, {}};
static void cont__89_33(void);
static void cont__89_34(void);
static NODE *func__89_35;
static void entry__89_35(void);
static FRAME_INFO frame__89_35 = {1, {"c_source"}};
static void cont__89_36(void);
static void cont__89_37(void);
static void cont__89_38(void);
static NODE *func__89_39;
static void entry__89_39(void);
static FRAME_INFO frame__89_39 = {1, {"c_filename"}};
static NODE *string__89_40;
static void cont__89_41(void);
static void cont__89_42(void);
static NODE *func__89_43;
static void entry__89_43(void);
static FRAME_INFO frame__89_43 = {1, {"c_filename"}};
static NODE *string__89_44;
static void cont__89_45(void);
static NODE *func__89_46;
static void entry__89_46(void);
static FRAME_INFO frame__89_46 = {5, {"c_buf", "c_filename", "o_filename", "c_info", "o_info"}};
static void cont__89_47(void);
static void cont__89_48(void);
static void cont__89_49(void);
static NODE *func__89_50;
static void entry__89_50(void);
static FRAME_INFO frame__89_50 = {2, {"o_info", "c_info"}};
static void cont__89_51(void);
static void cont__89_52(void);
static void cont__89_53(void);
static void cont__89_54(void);
static NODE *func__89_55;
static void entry__89_55(void);
static FRAME_INFO frame__89_55 = {2, {"c_filename", "o_filename"}};
static NODE *func__89_56;
static void entry__89_56(void);
static FRAME_INFO frame__89_56 = {1, {"o_info"}};
static void cont__89_57(void);
static void cont__89_58(void);
static void cont__89_59(void);
static NODE *func__89_60;
static void entry__89_60(void);
static FRAME_INFO frame__89_60 = {0, {}};
static NODE *string__89_61;
static NODE *string__89_62;
static NODE *string__89_63;
static void cont__89_64(void);
static NODE *func__89_65;
static void entry__89_65(void);
static FRAME_INFO frame__89_65 = {1, {"filename"}};
static void cont__89_66(void);
static NODE *func__89_67;
static void entry__89_67(void);
static FRAME_INFO frame__89_67 = {2, {"exe_filename", "info"}};
static void cont__89_68(void);
static void cont__89_69(void);
static NODE *func__89_70;
static void entry__89_70(void);
static FRAME_INFO frame__89_70 = {1, {"info"}};
static void cont__89_71(void);
static NODE *func__89_72;
static void entry__89_72(void);
static FRAME_INFO frame__89_72 = {1, {"info"}};
static void cont__89_73(void);
static void cont__89_74(void);
static void cont__89_75(void);
static void cont__89_76(void);
static NODE *func__89_77;
static void entry__89_77(void);
static FRAME_INFO frame__89_77 = {0, {}};
static void cont__89_78(void);
static NODE *func__89_79;
static void entry__89_79(void);
static FRAME_INFO frame__89_79 = {2, {"exe_filename", "libs_and_files"}};
static void cont__89_80(void);
static NODE *func__89_81;
static void entry__89_81(void);
static FRAME_INFO frame__89_81 = {1, {"libs_and_files"}};
static NODE *string__89_82;
static void cont__89_83(void);
static void cont__89_84(void);
static NODE *func__89_85;
static void entry__89_85(void);
static FRAME_INFO frame__89_85 = {5, {"libs_and_files", "exe_filename", "out", "err", "success"}};
static NODE *func__89_86;
static void entry__89_86(void);
static FRAME_INFO frame__89_86 = {0, {}};
static NODE *string__89_87;
static void cont__89_88(void);
static NODE *string__89_89;
static NODE *string__89_90;
static NODE *string__89_91;
static void cont__89_92(void);
static NODE *func__89_93;
static void entry__89_93(void);
static FRAME_INFO frame__89_93 = {1, {"err"}};
static void cont__89_94(void);
static NODE *func__89_95;
static void entry__89_95(void);
static FRAME_INFO frame__89_95 = {5, {"libs_and_files", "exe_filename", "out", "err", "success"}};
static NODE *func__89_96;
static void entry__89_96(void);
static FRAME_INFO frame__89_96 = {0, {}};
static NODE *string__89_97;
static void cont__89_98(void);
static void cont__89_99(void);
static void cont__89_100(void);
static NODE *func__89_101;
static void entry__89_101(void);
static FRAME_INFO frame__89_101 = {0, {}};
static NODE *string__89_102;
static void cont__89_103(void);
static NODE *func__89_104;
static void entry__89_104(void);
static FRAME_INFO frame__89_104 = {0, {}};
static void cont__89_105(void);
static void cont__89_106(void);
static void cont__89_107(void);
static NODE *func__89_108;
static void entry__89_108(void);
static FRAME_INFO frame__89_108 = {1, {"err"}};
static void cont__89_109(void);
static void cont__89_110(void);
static void cont__89_111(void);
static void cont__89_112(void);
static NODE *func__89_113;
static void entry__89_113(void);
static FRAME_INFO frame__89_113 = {0, {}};
static void cont__89_114(void);
static void cont__89_115(void);
static NODE *func__89_116;
static void entry__89_116(void);
static FRAME_INFO frame__89_116 = {2, {"exe_filename", "zz"}};
static void cont__89_117(void);
static NODE *func__89_118;
static void entry__89_118(void);
static FRAME_INFO frame__89_118 = {1, {"exe_filename"}};
static NODE *func__89_119;
static void entry__89_119(void);
static FRAME_INFO frame__89_119 = {1, {"exe_filename"}};
static void cont__89_120(void);
static void cont__89_121(void);
static void main_entry(void);
static void cont__run__basic__exceptions(void);
static void cont__run__basic__serialize(void);
static void cont__run__basic__deserialize(void);
static void cont__run__basic__branches(void);
static void cont__run__basic__debug(void);
static void cont__run__basic__environment(void);
static void cont__run__basic__event(void);
static void cont__run__basic__exec(void);
static void cont__run__basic__functional(void);
static void cont__run__basic__grammar(void);
static void cont__run__basic__io(void);
static void cont__run__basic__loops(void);
static void cont__run__basic__math(void);
static void cont__run__basic__options(void);
static void cont__run__basic__parameters(void);
static void cont__run__basic__platform(void);
static void cont__run__basic__polymorphic_functions(void);
static void cont__run__basic__primitives(void);
static void cont__run__basic__runtime(void);
static void cont__run__basic__types__boolean(void);
static void cont__run__basic__types__character(void);
static void cont__run__basic__types__continuation(void);
static void cont__run__basic__types__date_and_time(void);
static void cont__run__basic__types__function(void);
static void cont__run__basic__types__insert_order_set(void);
static void cont__run__basic__types__insert_order_table(void);
static void cont__run__basic__types__list(void);
static void cont__run__basic__types__multi_dimensional_set(void);
static void cont__run__basic__types__multi_dimensional_table(void);
static void cont__run__basic__types__number(void);
static void cont__run__basic__types__object(void);
static void cont__run__basic__types__key_order_table(void);
static void cont__run__basic__types__key_value_pair(void);
static void cont__run__basic__types__set(void);
static void cont__run__basic__types__key_order_set(void);
static void cont__run__basic__types__string_primitives(void);
static void cont__run__basic__types__string(void);
static void cont__run__basic__types__table(void);
static void cont__run__basic__types__undefined(void);
static void cont__run__basic__types__unique_item(void);
static void cont__run__basic__types__unordered_set(void);
static void cont__run__basic__types__unordered_table(void);
static void cont__run__basic__types__value_range(void);
static void cont__run__system__export__html(void);
static void cont__run__character_names(void);
static void cont__run__fragments(void);
static void cont__run__tokenizer(void);
static void cont__run__shared_variables(void);
static void cont__run__nodes(void);
static void cont__run__parser(void);
static void cont__run__expander(void);
static void cont__run__annotator(void);
static void cont__run__simplifier(void);
static void cont__run__macros(void);
static void cont__run__c_code_generator(void);
static void cont__run__pretty_printer(void);
static void cont__run__sim2c(void);
static void cont__run__extractor(void);
static void cont__run__runtime_definitions(void);
static NODE *string__93_1;
static void cont__93_2(void);
static void cont__94_1(void);
static void cont__95_1(void);
static void cont__96_1(void);
static NODE *string__98_1;
static void cont__98_2(void);
static void cont__99_1(void);
static void cont__100_1(void);
static void cont__100_2(void);
static NODE *string__101_1;
static void cont__101_2(void);
static NODE *string__102_1;
static void cont__102_2(void);
static NODE *string__103_1;
static void cont__103_2(void);
static void cont__104_1(void);
static NODE *func__104_2;
static void entry__104_2(void);
static FRAME_INFO frame__104_2 = {0, {}};
static void cont__104_3(void);
static NODE *func__104_4;
static void entry__104_4(void);
static FRAME_INFO frame__104_4 = {0, {}};
static NODE *string__104_5;
static void cont__104_6(void);
static NODE *string__104_7;
static void cont__104_8(void);
static void cont__104_9(void);
static void cont__104_10(void);
static void cont__105_1(void);
static NODE *func__105_2;
static void entry__105_2(void);
static FRAME_INFO frame__105_2 = {0, {}};
static void cont__105_3(void);
static NODE *func__105_4;
static void entry__105_4(void);
static FRAME_INFO frame__105_4 = {0, {}};
static void cont__105_5(void);
static void cont__105_6(void);
static void cont__105_7(void);
static void cont__105_8(void);
static NODE *string__107_1;
static void cont__107_2(void);
static void cont__107_3(void);
static void cont__107_4(void);
static void cont__107_5(void);
static NODE *string__107_6;
static void cont__107_7(void);
static NODE *string__107_8;
static void cont__107_9(void);
static void cont__107_10(void);
static void cont__107_11(void);
static NODE *func__109_1;
static void entry__109_1(void);
static FRAME_INFO frame__109_1 = {2, {"platform", "priority"}};
static void cont__109_2(void);
static NODE *func__109_3;
static void entry__109_3(void);
static FRAME_INFO frame__109_3 = {3, {"break", "platform", "priority"}};
static NODE *func__109_4;
static void entry__109_4(void);
static FRAME_INFO frame__109_4 = {4, {"platform", "break", "priority", "plat"}};
static void cont__109_5(void);
static void cont__109_6(void);
static void cont__109_7(void);
static void cont__109_8(void);
static void cont__109_9(void);
static void cont__109_10(void);
static void cont__109_11(void);
static void cont__109_12(void);
static void cont__109_13(void);
static void cont__133_1(void);
static void cont__133_2(void);
static void cont__134_1(void);
static NODE *func__134_2;
static void entry__134_2(void);
static FRAME_INFO frame__134_2 = {0, {}};
static void cont__134_3(void);
static NODE *func__134_4;
static void entry__134_4(void);
static FRAME_INFO frame__134_4 = {0, {}};
static NODE *string__134_5;
static void cont__134_6(void);
static void cont__134_7(void);
static NODE *func__134_8;
static void entry__134_8(void);
static FRAME_INFO frame__134_8 = {0, {}};
static NODE *func__134_9;
static void entry__134_9(void);
static FRAME_INFO frame__134_9 = {0, {}};
static NODE *string__134_10;
static NODE *string__134_11;
static NODE *func__134_12;
static void entry__134_12(void);
static FRAME_INFO frame__134_12 = {0, {}};
static NODE *string__134_13;
static NODE *string__134_14;
static NODE *func__134_15;
static void entry__134_15(void);
static FRAME_INFO frame__134_15 = {0, {}};
static NODE *string__134_16;
static NODE *string__134_17;
static NODE *func__134_18;
static void entry__134_18(void);
static FRAME_INFO frame__134_18 = {0, {}};
static NODE *string__134_19;
static NODE *string__134_20;
static NODE *func__134_21;
static void entry__134_21(void);
static FRAME_INFO frame__134_21 = {0, {}};
static NODE *string__134_22;
static NODE *string__134_23;
static NODE *func__134_24;
static void entry__134_24(void);
static FRAME_INFO frame__134_24 = {0, {}};
static NODE *string__134_25;
static NODE *string__134_26;
static NODE *func__134_27;
static void entry__134_27(void);
static FRAME_INFO frame__134_27 = {0, {}};
static NODE *string__134_28;
static NODE *string__134_29;
static NODE *func__134_30;
static void entry__134_30(void);
static FRAME_INFO frame__134_30 = {0, {}};
static NODE *string__134_31;
static NODE *string__134_32;
static NODE *func__134_33;
static void entry__134_33(void);
static FRAME_INFO frame__134_33 = {0, {}};
static NODE *string__134_34;
static NODE *string__134_35;
static NODE *func__134_36;
static void entry__134_36(void);
static FRAME_INFO frame__134_36 = {0, {}};
static NODE *string__134_37;
static NODE *string__134_38;
static NODE *func__134_39;
static void entry__134_39(void);
static FRAME_INFO frame__134_39 = {0, {}};
static NODE *string__134_40;
static NODE *string__134_41;
static NODE *func__134_42;
static void entry__134_42(void);
static FRAME_INFO frame__134_42 = {0, {}};
static NODE *string__134_43;
static NODE *string__134_44;
static NODE *func__134_45;
static void entry__134_45(void);
static FRAME_INFO frame__134_45 = {0, {}};
static NODE *string__134_46;
static NODE *string__134_47;
static NODE *func__134_48;
static void entry__134_48(void);
static FRAME_INFO frame__134_48 = {0, {}};
static NODE *string__134_49;
static NODE *string__134_50;
static NODE *func__134_51;
static void entry__134_51(void);
static FRAME_INFO frame__134_51 = {0, {}};
static NODE *string__134_52;
static NODE *string__134_53;
static NODE *func__134_54;
static void entry__134_54(void);
static FRAME_INFO frame__134_54 = {0, {}};
static NODE *string__134_55;
static NODE *string__134_56;
static NODE *func__134_57;
static void entry__134_57(void);
static FRAME_INFO frame__134_57 = {0, {}};
static NODE *string__134_58;
static NODE *string__134_59;
static NODE *func__134_60;
static void entry__134_60(void);
static FRAME_INFO frame__134_60 = {0, {}};
static NODE *string__134_61;
static NODE *string__134_62;
static NODE *func__134_63;
static void entry__134_63(void);
static FRAME_INFO frame__134_63 = {0, {}};
static NODE *string__134_64;
static NODE *string__134_65;
static NODE *func__134_66;
static void entry__134_66(void);
static FRAME_INFO frame__134_66 = {0, {}};
static NODE *string__134_67;
static NODE *string__134_68;
static void cont__134_69(void);
static void cont__134_70(void);
static void cont__135_1(void);
static void cont__136_1(void);
static NODE *func__138_1;
static void entry__138_1(void);
static FRAME_INFO frame__138_1 = {0, {}};
static void cont__138_2(void);
static void cont__143_1(void);
static NODE *string__144_1;
static NODE *string__144_2;
static NODE *string__144_3;
static NODE *string__144_4;
static NODE *string__144_5;
static NODE *string__144_6;
static NODE *string__144_7;
static NODE *string__144_8;
static NODE *string__144_9;
static NODE *string__144_10;
static void cont__144_11(void);
static NODE *string__145_1;
static void cont__145_2(void);
static NODE *string__146_1;
static NODE *string__146_2;
static void cont__146_3(void);
static NODE *string__146_4;
static void cont__146_5(void);
static void cont__146_6(void);
static NODE *string__146_7;
static void cont__146_8(void);
static void cont__146_9(void);
static NODE *func__148_1;
static void entry__148_1(void);
static FRAME_INFO frame__148_1 = {1, {"path"}};
static NODE *string__148_2;
static void cont__148_3(void);
static void cont__148_4(void);
static void cont__148_5(void);
static void cont__149_1(void);
static void cont__149_2(void);
static void cont__149_3(void);
static void cont__149_4(void);
static NODE *string__149_5;
static void cont__149_6(void);
static NODE *func__149_7;
static void entry__149_7(void);
static FRAME_INFO frame__149_7 = {0, {}};
static NODE *func__149_8;
static void entry__149_8(void);
static FRAME_INFO frame__149_8 = {0, {}};
static void cont__149_9(void);
static void cont__149_10(void);
static void cont__149_11(void);
static void cont__149_12(void);
static void cont__167_1(void);
static NODE *func__167_2;
static void entry__167_2(void);
static FRAME_INFO frame__167_2 = {0, {}};
static NODE *string__167_3;
static NODE *string__167_4;
static void cont__167_5(void);
static void cont__167_6(void);
static NODE *func__182_1;
static void entry__182_1(void);
static FRAME_INFO frame__182_1 = {0, {}};
static void cont__182_2(void);
static void cont__182_3(void);
static NODE *func__183_1;
static void entry__183_1(void);
static FRAME_INFO frame__183_1 = {0, {}};
static NODE *func__183_2;
static void entry__183_2(void);
static FRAME_INFO frame__183_2 = {0, {}};
static NODE *func__183_3;
static void entry__183_3(void);
static FRAME_INFO frame__183_3 = {0, {}};
static NODE *func__183_4;
static void entry__183_4(void);
static FRAME_INFO frame__183_4 = {0, {}};
static void cont__183_5(void);
static void cont__183_6(void);
static void cont__183_7(void);
static NODE *func__183_8;
static void entry__183_8(void);
static FRAME_INFO frame__183_8 = {0, {}};
static NODE *func__183_9;
static void entry__183_9(void);
static FRAME_INFO frame__183_9 = {0, {}};
static NODE *func__183_10;
static void entry__183_10(void);
static FRAME_INFO frame__183_10 = {0, {}};
static NODE *func__183_11;
static void entry__183_11(void);
static FRAME_INFO frame__183_11 = {0, {}};
static void cont__183_12(void);
static void cont__183_13(void);
static void cont__184_1(void);
static void main_entry(void);

static CONTINUATION_INFO continuation_info[] = {
  {main_entry, NULL, 7, 7, 9, 26},
  {cont__run__basic__exceptions, NULL, 8, 8, 9, 25},
  {cont__run__basic__serialize, NULL, 9, 9, 9, 27},
  {cont__run__basic__deserialize, NULL, 10, 10, 9, 24},
  {cont__run__basic__branches, NULL, 11, 11, 9, 21},
  {cont__run__basic__debug, NULL, 12, 12, 9, 27},
  {cont__run__basic__environment, NULL, 13, 13, 9, 21},
  {cont__run__basic__event, NULL, 14, 14, 9, 20},
  {cont__run__basic__exec, NULL, 15, 15, 9, 26},
  {cont__run__basic__functional, NULL, 16, 16, 9, 23},
  {cont__run__basic__grammar, NULL, 17, 17, 9, 18},
  {cont__run__basic__io, NULL, 18, 18, 9, 21},
  {cont__run__basic__loops, NULL, 19, 19, 9, 20},
  {cont__run__basic__math, NULL, 20, 20, 9, 23},
  {cont__run__basic__options, NULL, 21, 21, 9, 26},
  {cont__run__basic__parameters, NULL, 22, 22, 9, 24},
  {cont__run__basic__platform, NULL, 23, 23, 9, 37},
  {cont__run__basic__polymorphic_functions, NULL, 24, 24, 9, 26},
  {cont__run__basic__primitives, NULL, 25, 25, 9, 23},
  {cont__run__basic__runtime, NULL, 26, 26, 9, 29},
  {cont__run__basic__types__boolean, NULL, 27, 27, 9, 31},
  {cont__run__basic__types__character, NULL, 28, 28, 9, 34},
  {cont__run__basic__types__continuation, NULL, 29, 29, 9, 35},
  {cont__run__basic__types__date_and_time, NULL, 30, 30, 9, 30},
  {cont__run__basic__types__function, NULL, 31, 31, 9, 38},
  {cont__run__basic__types__insert_order_set, NULL, 32, 32, 9, 40},
  {cont__run__basic__types__insert_order_table, NULL, 33, 33, 9, 26},
  {cont__run__basic__types__list, NULL, 34, 34, 9, 43},
  {cont__run__basic__types__multi_dimensional_set, NULL, 35, 35, 9, 45},
  {cont__run__basic__types__multi_dimensional_table, NULL, 36, 36, 9, 28},
  {cont__run__basic__types__number, NULL, 37, 37, 9, 28},
  {cont__run__basic__types__object, NULL, 38, 38, 9, 37},
  {cont__run__basic__types__key_order_table, NULL, 39, 39, 9, 36},
  {cont__run__basic__types__key_value_pair, NULL, 40, 40, 9, 25},
  {cont__run__basic__types__set, NULL, 41, 41, 9, 35},
  {cont__run__basic__types__key_order_set, NULL, 42, 42, 9, 39},
  {cont__run__basic__types__string_primitives, NULL, 43, 43, 9, 28},
  {cont__run__basic__types__string, NULL, 44, 44, 9, 27},
  {cont__run__basic__types__table, NULL, 45, 45, 9, 31},
  {cont__run__basic__types__undefined, NULL, 46, 46, 9, 33},
  {cont__run__basic__types__unique_item, NULL, 47, 47, 9, 35},
  {cont__run__basic__types__unordered_set, NULL, 48, 48, 9, 37},
  {cont__run__basic__types__unordered_table, NULL, 49, 49, 9, 33},
  {cont__run__basic__types__value_range, NULL, 50, 50, 9, 28},
  {cont__run__system__export__html, NULL, 51, 51, 9, 27},
  {cont__run__character_names, NULL, 52, 52, 9, 21},
  {cont__run__fragments, NULL, 53, 53, 9, 21},
  {cont__run__tokenizer, NULL, 54, 54, 9, 28},
  {cont__run__shared_variables, NULL, 55, 55, 9, 17},
  {cont__run__nodes, NULL, 56, 56, 9, 18},
  {cont__run__parser, NULL, 57, 57, 9, 20},
  {cont__run__expander, NULL, 58, 58, 9, 21},
  {cont__run__annotator, NULL, 59, 59, 9, 22},
  {cont__run__simplifier, NULL, 60, 60, 9, 18},
  {cont__run__macros, NULL, 61, 61, 9, 28},
  {cont__run__c_code_generator, NULL, 62, 62, 9, 26},
  {cont__run__pretty_printer, NULL, 63, 63, 9, 17},
  {cont__run__sim2c, NULL, 64, 64, 9, 21},
  {cont__run__extractor, NULL, 65, 65, 9, 31},
  {cont__run__runtime_definitions, NULL, 71, 90, 1, 62},
  {cont__93_2, NULL, 91, 91, 1, 30},
  {cont__94_1, NULL, 92, 92, 1, 30},
  {cont__95_1, NULL, 93, 93, 1, 28},
  {cont__96_1, NULL, 95, 95, 1, 49},
  {cont__98_2, NULL, 96, 96, 1, 15},
  {cont__99_1, NULL, 97, 97, 12, 23},
  {cont__100_1, NULL, 97, 97, 1, 23},
  {cont__100_2, NULL, 98, 98, 1, 72},
  {cont__101_2, NULL, 99, 99, 1, 37},
  {cont__102_2, NULL, 100, 100, 1, 39},
  {cont__103_2, NULL, 104, 104, 5, 25},
  {cont__104_1, NULL, 102, 109, 1, 45},
  {cont__104_10, NULL, 113, 113, 5, 26},
  {cont__105_1, NULL, 111, 118, 1, 45},
  {cont__105_8, NULL, 124, 124, 5, 19},
  {cont__107_2, NULL, 125, 125, 5, 22},
  {cont__107_3, NULL, 126, 126, 5, 22},
  {cont__107_4, NULL, 127, 127, 5, 21},
  {cont__107_5, NULL, 128, 128, 5, 19},
  {cont__107_7, NULL, 129, 129, 5, 17},
  {cont__107_9, NULL, 130, 130, 5, 16},
  {cont__107_10, NULL, 122, 130, 1, 17},
  {cont__107_11, NULL, 133, 143, 1, 22},
  {cont__109_13, NULL, 167, 167, 42, 42},
  {cont__133_1, NULL, 167, 167, 1, 43},
  {cont__133_2, NULL, 169, 169, 3, 20},
  {cont__134_1, NULL, 168, 243, 1, 49},
  {cont__134_70, NULL, 244, 244, 1, 39},
  {cont__135_1, NULL, 245, 245, 1, 30},
  {cont__136_1, NULL, 247, 247, 1, 37},
  {cont__138_2, NULL, 256, 256, 1, 21},
  {cont__143_1, NULL, 258, 269, 1, 27},
  {cont__144_11, NULL, 271, 273, 1, 31},
  {cont__145_2, NULL, 281, 281, 16, 44},
  {cont__146_3, NULL, 281, 281, 5, 44},
  {cont__146_5, NULL, 282, 282, 16, 44},
  {cont__146_6, NULL, 282, 282, 5, 44},
  {cont__146_8, NULL, 279, 282, 1, 45},
  {cont__146_9, NULL, 285, 286, 1, 38},
  {cont__148_5, NULL, 293, 293, 38, 60},
  {cont__149_1, NULL, 293, 293, 9, 61},
  {cont__149_2, NULL, 292, 294, 7, 17},
  {cont__149_3, NULL, 297, 297, 11, 22},
  {cont__149_4, NULL, 297, 297, 11, 31},
  {cont__149_6, NULL, 296, 299, 9, 22},
  {cont__149_9, NULL, 295, 300, 7, 25},
  {cont__149_10, NULL, 291, 300, 5, 26},
  {cont__149_11, NULL, 288, 300, 1, 29},
  {cont__149_12, NULL, 638, 638, 4, 25},
  {cont__167_1, NULL, 638, 640, 1, 52},
  {cont__167_6, NULL, 1085, 1085, 1, 36},
  {cont__182_3, NULL, 1086, 1098, 1, 18},
  {cont__183_13, NULL, },
  {cont__184_1, NULL, },
  {entry__47_2, NULL, 250, 250, 36, 49},
  {entry__47_1_sim2c__show_compiler_debug_info, NULL, 250, 250, 3, 49},
  {entry__66_13, NULL, 319, 319, 37, 80},
  {cont__66_14, &frame__66_13, 319, 319, 37, 61},
  {cont__66_15, &frame__66_13, 319, 319, 80, 80},
  {entry__66_10, NULL, 318, 318, 13, 41},
  {cont__66_11, &frame__66_10, 319, 319, 16, 34},
  {cont__66_12, &frame__66_10, 319, 319, 13, 80},
  {entry__66_8, NULL, 317, 317, 14, 33},
  {cont__66_9, &frame__66_8, 317, 319, 11, 80},
  {entry__66_6, NULL, 316, 316, 18, 32},
  {cont__66_7, &frame__66_6, 316, 319, 9, 81},
  {entry__66_4, NULL, 315, 315, 10, 26},
  {cont__66_5, &frame__66_4, 315, 319, 7, 82},
  {entry__66_3, NULL, 314, 319, 5, 83},
  {entry__66_20, NULL, 323, 324, 11, 57},
  {cont__66_23, &frame__66_20, 323, 324, 5, 57},
  {entry__66_1_resolve_filename, NULL, 312, 312, 6, 36},
  {cont__66_2, &frame__66_1_resolve_filename, 312, 319, 3, 84},
  {cont__66_16, &frame__66_1_resolve_filename, 320, 320, 3, 32},
  {cont__66_17, &frame__66_1_resolve_filename, 321, 321, 3, 38},
  {cont__66_18, &frame__66_1_resolve_filename, 322, 322, 6, 25},
  {cont__66_19, &frame__66_1_resolve_filename, 322, 324, 3, 58},
  {cont__66_24, &frame__66_1_resolve_filename, 325, 325, 21, 39},
  {cont__66_25, &frame__66_1_resolve_filename, 325, 325, 6, 40},
  {cont__66_26, &frame__66_1_resolve_filename, 325, 325, 3, 40},
  {entry__67_10, NULL, 343, 343, 56, 77},
  {cont__67_11, &frame__67_10, 343, 343, 77, 77},
  {entry__67_8, NULL, 343, 343, 35, 53},
  {cont__67_9, &frame__67_8, 343, 343, 32, 77},
  {entry__67_6, NULL, 343, 343, 10, 29},
  {cont__67_7, &frame__67_6, 343, 343, 7, 77},
  {entry__67_28, NULL, 349, 349, 41, 65},
  {cont__67_29, &frame__67_28, 349, 349, 41, 65},
  {entry__67_31, NULL, 350, 350, 11, 38},
  {cont__67_32, &frame__67_31, 350, 350, 49, 49},
  {entry__67_15, NULL, 345, 345, 48, 60},
  {cont__67_17, &frame__67_15, 345, 345, 48, 68},
  {cont__67_18, &frame__67_15, 345, 345, 9, 69},
  {cont__67_19, &frame__67_15, 346, 346, 9, 34},
  {cont__67_20, &frame__67_15, 347, 347, 22, 36},
  {cont__67_21, &frame__67_15, 347, 347, 38, 62},
  {cont__67_22, &frame__67_15, 347, 347, 22, 62},
  {cont__67_23, &frame__67_15, 347, 347, 22, 64},
  {cont__67_24, &frame__67_15, 347, 347, 9, 67},
  {cont__67_25, &frame__67_15, 348, 348, 9, 49},
  {cont__67_26, &frame__67_15, 349, 349, 12, 36},
  {cont__67_27, &frame__67_15, 349, 349, 12, 65},
  {cont__67_30, &frame__67_15, 349, 350, 9, 49},
  {cont__67_33, &frame__67_15, 351, 351, 9, 52},
  {cont__67_34, &frame__67_15, 352, 352, 9, 26},
  {cont__67_35, &frame__67_15, 353, 353, 9, 43},
  {cont__67_36, &frame__67_15, 354, 354, 9, 30},
  {cont__67_37, &frame__67_15, 354, 354, 52, 52},
  {entry__67_12, NULL, 344, 344, 10, 33},
  {cont__67_14, &frame__67_12, 344, 354, 7, 52},
  {entry__67_4, NULL, 341, 341, 5, 33},
  {cont__67_5, &frame__67_4, 342, 354, 5, 53},
  {entry__67_49, NULL, 360, 360, 38, 60},
  {cont__67_50, &frame__67_49, 360, 360, 60, 60},
  {entry__67_45_maybe_push_common, NULL, 359, 359, 11, 54},
  {cont__67_47, &frame__67_45_maybe_push_common, 360, 360, 14, 35},
  {cont__67_48, &frame__67_45_maybe_push_common, 360, 360, 11, 60},
  {entry__67_57, NULL, 367, 368, 17, 57},
  {cont__67_60, &frame__67_57, 367, 368, 11, 57},
  {entry__67_67, NULL, 372, 372, 11, 34},
  {cont__67_68, &frame__67_67, 373, 373, 11, 45},
  {cont__67_69, &frame__67_67, 373, 373, 45, 45},
  {entry__67_64, NULL, 371, 371, 18, 31},
  {cont__67_65, &frame__67_64, 371, 371, 18, 31},
  {cont__67_66, &frame__67_64, 371, 373, 15, 45},
  {entry__67_44, NULL, 362, 362, 9, 35},
  {cont__67_51, &frame__67_44, 363, 363, 35, 58},
  {cont__67_52, &frame__67_44, 363, 363, 9, 59},
  {cont__67_53, &frame__67_44, 364, 364, 9, 39},
  {cont__67_54, &frame__67_44, 365, 365, 9, 46},
  {cont__67_55, &frame__67_44, 366, 366, 16, 32},
  {cont__67_56, &frame__67_44, 366, 368, 9, 58},
  {cont__67_61, &frame__67_44, 369, 369, 9, 30},
  {cont__67_62, &frame__67_44, 370, 370, 9, 34},
  {cont__67_63, &frame__67_44, 371, 373, 9, 45},
  {cont__67_70, &frame__67_44, 374, 374, 10, 30},
  {cont__67_71, &frame__67_44, 374, 374, 9, 40},
  {cont__67_72, &frame__67_44, 374, 374, 9, 30},
  {cont__67_73, &frame__67_44, 374, 374, 46, 46},
  {entry__67_41, NULL, 357, 357, 14, 44},
  {cont__67_43, &frame__67_41, 357, 374, 7, 46},
  {entry__67_39, NULL, 356, 356, 8, 30},
  {cont__67_40, &frame__67_39, 356, 374, 5, 47},
  {entry__67_77, NULL, 375, 375, 39, 64},
  {entry__67_1_add_module_infos, NULL, 336, 336, 22, 27},
  {cont__67_2, &frame__67_1_add_module_infos, 336, 336, 3, 33},
  {cont__67_3, &frame__67_1_add_module_infos, 340, 354, 3, 54},
  {cont__67_38, &frame__67_1_add_module_infos, 355, 374, 3, 48},
  {cont__67_74, &frame__67_1_add_module_infos, 375, 375, 6, 31},
  {cont__67_75, &frame__67_1_add_module_infos, 375, 375, 6, 36},
  {cont__67_76, &frame__67_1_add_module_infos, 375, 375, 3, 64},
  {cont__67_78, &frame__67_1_add_module_infos, 375, 375, 64, 64},
  {entry__68_4, NULL, 386, 386, 23, 29},
  {entry__68_5, NULL, 387, 387, 47, 47},
  {cont__68_6, &frame__68_5, 387, 387, 22, 48},
  {cont__68_7, &frame__68_5, 387, 387, 70, 70},
  {cont__68_8, &frame__68_5, 387, 387, 50, 71},
  {cont__68_9, &frame__68_5, 387, 387, 5, 71},
  {cont__68_10, &frame__68_5, 388, 388, 8, 28},
  {cont__68_11, &frame__68_5, 388, 388, 5, 28},
  {entry__68_1_lookup, NULL, 385, 385, 3, 29},
  {cont__68_2, &frame__68_1_lookup, 386, 386, 6, 20},
  {cont__68_3, &frame__68_1_lookup, 386, 388, 3, 28},
  {entry__69_2, NULL, 391, 391, 36, 47},
  {cont__69_3, &frame__69_2, 391, 391, 53, 62},
  {cont__69_4, &frame__69_2, 391, 391, 27, 62},
  {entry__69_1_CC, NULL, 391, 391, 3, 62},
  {cont__69_5, &frame__69_1_CC, 392, 392, 3, 10},
  {entry__70_2, NULL, 395, 395, 41, 60},
  {entry__70_8, NULL, 400, 400, 11, 23},
  {cont__70_9, &frame__70_8, 398, 400, 13, 24},
  {cont__70_12, &frame__70_8, 398, 400, 7, 24},
  {entry__70_4, NULL, 396, 396, 5, 70},
  {cont__70_7, &frame__70_4, 397, 400, 5, 25},
  {cont__70_13, &frame__70_4, 401, 401, 17, 17},
  {entry__70_1_compile_c, NULL, 395, 395, 10, 60},
  {cont__70_3, &frame__70_1_compile_c, 395, 401, 3, 17},
  {entry__71_25, NULL, 428, 428, 45, 74},
  {cont__71_26, &frame__71_25, 428, 428, 9, 41},
  {cont__71_27, &frame__71_25, 428, 428, 9, 74},
  {cont__71_28, &frame__71_25, 428, 428, 9, 74},
  {entry__71_21, NULL, 427, 427, 43, 75},
  {cont__71_22, &frame__71_21, 427, 427, 9, 39},
  {cont__71_23, &frame__71_21, 427, 427, 9, 75},
  {cont__71_24, &frame__71_21, 428, 428, 9, 74},
  {cont__71_29, &frame__71_21, },
  {entry__71_19, NULL, 426, 426, 9, 32},
  {cont__71_20, &frame__71_19, },
  {cont__71_30, &frame__71_19, },
  {entry__71_17, NULL, 425, 425, 9, 29},
  {cont__71_18, &frame__71_17, },
  {cont__71_31, &frame__71_17, },
  {entry__71_41, NULL, 440, 440, 17, 47},
  {cont__71_42, &frame__71_41, 440, 440, 17, 67},
  {cont__71_43, &frame__71_41, 440, 440, 17, 67},
  {entry__71_45, NULL, 443, 443, 17, 21},
  {entry__71_38_check, NULL, 436, 436, 13, 42},
  {cont__71_39, &frame__71_38_check, 439, 439, 17, 38},
  {cont__71_40, &frame__71_38_check, 438, 440, 15, 66},
  {cont__71_44, &frame__71_38_check, 437, 443, 13, 22},
  {entry__71_58, NULL, 453, 453, 58, 58},
  {cont__71_59, &frame__71_58, 453, 453, 40, 59},
  {cont__71_60, &frame__71_58, 453, 453, 23, 60},
  {cont__71_61, &frame__71_58, 453, 453, 17, 60},
  {entry__71_63, NULL, 455, 455, 53, 77},
  {cont__71_64, &frame__71_63, 455, 455, 47, 77},
  {entry__71_62, NULL, 455, 455, 17, 77},
  {entry__71_55, NULL, 452, 452, 15, 40},
  {cont__71_57, &frame__71_55, 451, 455, 13, 78},
  {entry__71_37, NULL, 445, 445, 18, 41},
  {cont__71_47, &frame__71_37, 445, 445, 11, 47},
  {cont__71_48, &frame__71_37, 446, 446, 11, 26},
  {cont__71_49, &frame__71_37, 447, 447, 11, 20},
  {cont__71_50, &frame__71_37, 448, 448, 11, 50},
  {cont__71_51, &frame__71_37, 449, 449, 11, 44},
  {cont__71_52, &frame__71_37, 450, 450, 14, 30},
  {cont__71_54, &frame__71_37, 450, 455, 11, 79},
  {entry__71_36, NULL, 434, 455, 9, 80},
  {cont__71_65, &frame__71_36, 455, 455, 80, 80},
  {entry__71_33, NULL, 431, 431, 7, 55},
  {cont__71_34, &frame__71_33, 432, 432, 7, 38},
  {cont__71_35, &frame__71_33, 433, 455, 7, 81},
  {entry__71_74, NULL, 470, 470, 29, 41},
  {cont__71_75, &frame__71_74, 470, 470, 23, 41},
  {entry__71_67, NULL, 464, 464, 7, 36},
  {cont__71_68, &frame__71_67, 465, 465, 7, 22},
  {cont__71_69, &frame__71_67, 466, 466, 7, 31},
  {cont__71_70, &frame__71_67, 467, 467, 7, 32},
  {cont__71_71, &frame__71_67, 468, 468, 7, 43},
  {cont__71_72, &frame__71_67, 469, 469, 7, 32},
  {cont__71_73, &frame__71_67, 470, 470, 7, 41},
  {cont__71_76, &frame__71_67, 471, 471, 25, 35},
  {cont__71_77, &frame__71_67, 471, 471, 7, 35},
  {cont__71_78, &frame__71_67, 471, 471, 35, 35},
  {entry__71_2, NULL, 413, 413, 48, 48},
  {cont__71_3, &frame__71_2, 413, 413, 5, 49},
  {cont__71_4, &frame__71_2, 414, 414, 35, 57},
  {cont__71_5, &frame__71_2, 414, 414, 5, 58},
  {cont__71_6, &frame__71_2, 415, 415, 5, 42},
  {cont__71_7, &frame__71_2, 416, 416, 42, 64},
  {cont__71_8, &frame__71_2, 416, 416, 5, 70},
  {cont__71_10, &frame__71_2, 417, 417, 51, 62},
  {cont__71_11, &frame__71_2, 417, 417, 39, 63},
  {cont__71_12, &frame__71_2, 417, 417, 5, 71},
  {cont__71_13, &frame__71_2, 418, 418, 5, 34},
  {cont__71_14, &frame__71_2, 419, 419, 5, 32},
  {cont__71_15, &frame__71_2, 420, 420, 5, 38},
  {cont__71_16, &frame__71_2, 422, 428, 5, 75},
  {cont__71_32, &frame__71_2, 430, 455, 5, 82},
  {cont__71_66, &frame__71_2, 456, 471, 5, 35},
  {cont__71_79, &frame__71_2, 472, 472, 5, 19},
  {cont__71_80, &frame__71_2, 473, 473, 8, 21},
  {cont__71_81, &frame__71_2, 473, 473, 5, 21},
  {entry__71_1_compile_meta_module, NULL, 412, 473, 3, 21},
  {entry__72_13, NULL, 498, 498, 43, 43},
  {cont__72_14, &frame__72_13, 498, 498, 15, 44},
  {cont__72_15, &frame__72_13, 500, 500, 48, 48},
  {cont__72_16, &frame__72_13, 500, 500, 24, 49},
  {cont__72_17, &frame__72_13, 500, 500, 17, 59},
  {cont__72_18, &frame__72_13, 501, 501, 44, 44},
  {cont__72_19, &frame__72_13, 501, 501, 24, 45},
  {cont__72_20, &frame__72_13, 501, 501, 17, 55},
  {cont__72_21, &frame__72_13, 499, 501, 15, 55},
  {entry__72_11, NULL, 497, 497, 16, 26},
  {cont__72_12, &frame__72_11, 497, 501, 13, 56},
  {entry__72_24, NULL, 507, 507, 17, 36},
  {entry__72_23, NULL, },
  {cont__72_25, &frame__72_23, },
  {entry__72_27, NULL, 509, 509, 32, 57},
  {cont__72_28, &frame__72_27, 509, 509, 17, 66},
  {entry__72_30, NULL, 512, 512, 44, 71},
  {cont__72_31, &frame__72_30, 512, 512, 30, 72},
  {cont__72_33, &frame__72_30, 512, 512, 19, 73},
  {cont__72_34, &frame__72_30, 512, 512, 78, 78},
  {entry__72_29, NULL, 511, 512, 17, 78},
  {entry__72_22, NULL, },
  {cont__72_26, &frame__72_22, 503, 512, 13, 80},
  {entry__72_9, NULL, 496, 496, 11, 36},
  {cont__72_10, &frame__72_9, 495, 512, 9, 82},
  {entry__72_36, NULL, 514, 514, 37, 64},
  {cont__72_37, &frame__72_36, 514, 514, 26, 65},
  {cont__72_38, &frame__72_36, 514, 514, 70, 70},
  {entry__72_35, NULL, 514, 514, 9, 70},
  {entry__72_2, NULL, 487, 487, 12, 35},
  {cont__72_3, &frame__72_2, 487, 487, 5, 42},
  {cont__72_4, &frame__72_2, 488, 488, 5, 20},
  {cont__72_5, &frame__72_2, 489, 489, 5, 14},
  {cont__72_6, &frame__72_2, 490, 490, 5, 44},
  {cont__72_7, &frame__72_2, 491, 491, 5, 38},
  {cont__72_8, &frame__72_2, 492, 514, 5, 71},
  {entry__72_1_build_dependencies, NULL, 486, 514, 3, 72},
  {cont__72_41, &frame__72_1_build_dependencies, 514, 514, 72, 72},
  {entry__73_9, NULL, 536, 536, 28, 44},
  {cont__73_10, &frame__73_9, 536, 536, 28, 44},
  {entry__73_12, NULL, 537, 537, 9, 72},
  {entry__73_18, NULL, 544, 544, 11, 40},
  {cont__73_19, &frame__73_18, 544, 544, 11, 60},
  {cont__73_20, &frame__73_18, 544, 544, 11, 60},
  {entry__73_22, NULL, 546, 546, 11, 59},
  {cont__73_23, &frame__73_22, 546, 546, 59, 59},
  {entry__73_3, NULL, 534, 534, 7, 45},
  {cont__73_4, &frame__73_3, 535, 535, 58, 58},
  {cont__73_5, &frame__73_3, 535, 535, 34, 59},
  {cont__73_6, &frame__73_3, 535, 535, 7, 75},
  {cont__73_7, &frame__73_3, 536, 536, 10, 23},
  {cont__73_8, &frame__73_3, 536, 536, 10, 44},
  {cont__73_11, &frame__73_3, 536, 537, 7, 72},
  {cont__73_13, &frame__73_3, 538, 538, 7, 53},
  {cont__73_14, &frame__73_3, 539, 539, 7, 38},
  {cont__73_15, &frame__73_3, 540, 540, 7, 34},
  {cont__73_16, &frame__73_3, 543, 543, 11, 40},
  {cont__73_17, &frame__73_3, 542, 544, 9, 59},
  {cont__73_21, &frame__73_3, 541, 546, 7, 60},
  {entry__73_27, NULL, 549, 549, 22, 43},
  {cont__73_28, &frame__73_27, 549, 549, 48, 48},
  {entry__73_32, NULL, 555, 555, 29, 56},
  {cont__73_33, &frame__73_32, 555, 555, 9, 56},
  {cont__73_34, &frame__73_32, 555, 555, 9, 56},
  {entry__73_30, NULL, 554, 554, 9, 27},
  {cont__73_31, &frame__73_30, 555, 555, 9, 56},
  {cont__73_35, &frame__73_30, },
  {entry__73_42, NULL, 558, 558, 21, 63},
  {entry__73_45, NULL, 559, 559, 35, 53},
  {entry__73_47, NULL, 560, 560, 32, 54},
  {entry__73_51, NULL, 562, 562, 26, 56},
  {entry__73_37, NULL, 557, 557, 50, 59},
  {cont__73_39, &frame__73_37, 557, 557, 61, 70},
  {cont__73_40, &frame__73_37, 557, 557, 9, 71},
  {cont__73_41, &frame__73_37, 558, 558, 9, 63},
  {cont__73_44, &frame__73_37, 559, 559, 9, 53},
  {cont__73_46, &frame__73_37, 560, 560, 9, 54},
  {cont__73_48, &frame__73_37, 561, 561, 25, 37},
  {cont__73_49, &frame__73_37, 561, 561, 9, 37},
  {cont__73_50, &frame__73_37, 562, 562, 9, 56},
  {cont__73_52, &frame__73_37, 562, 562, 56, 56},
  {entry__73_57, NULL, 569, 569, 44, 71},
  {cont__73_58, &frame__73_57, 569, 569, 13, 40},
  {cont__73_59, &frame__73_57, 569, 569, 13, 71},
  {cont__73_60, &frame__73_57, 569, 569, 13, 71},
  {entry__73_63, NULL, 571, 571, 30, 60},
  {entry__73_62, NULL, 571, 571, 13, 60},
  {entry__73_66, NULL, 576, 576, 17, 44},
  {cont__73_67, &frame__73_66, 576, 576, 17, 69},
  {cont__73_68, &frame__73_66, 576, 576, 17, 69},
  {entry__73_70, NULL, 578, 578, 17, 68},
  {cont__73_71, &frame__73_70, 578, 578, 68, 68},
  {entry__73_64, NULL, 575, 575, 17, 51},
  {cont__73_65, &frame__73_64, 574, 576, 15, 68},
  {cont__73_69, &frame__73_64, 573, 578, 13, 69},
  {entry__73_53, NULL, 564, 564, 9, 30},
  {cont__73_54, &frame__73_53, 565, 565, 9, 32},
  {cont__73_55, &frame__73_53, 568, 568, 13, 31},
  {cont__73_56, &frame__73_53, 567, 569, 11, 70},
  {cont__73_61, &frame__73_53, 566, 578, 9, 71},
  {entry__73_2_compile_submodule, NULL, 533, 546, 5, 61},
  {cont__73_24, &frame__73_2_compile_submodule, 547, 547, 5, 48},
  {cont__73_25, &frame__73_2_compile_submodule, 548, 548, 5, 28},
  {cont__73_26, &frame__73_2_compile_submodule, 549, 549, 5, 48},
  {cont__73_29, &frame__73_2_compile_submodule, 550, 550, 5, 21},
  {cont__73_36, &frame__73_2_compile_submodule, 551, 578, 5, 73},
  {cont__73_72, &frame__73_2_compile_submodule, 579, 579, 5, 63},
  {entry__73_75, NULL, 583, 584, 11, 56},
  {cont__73_78, &frame__73_75, 583, 584, 5, 56},
  {entry__73_91, NULL, 591, 591, 51, 75},
  {cont__73_92, &frame__73_91, 591, 591, 32, 75},
  {cont__73_93, &frame__73_91, 591, 591, 75, 75},
  {entry__73_86, NULL, 590, 590, 59, 59},
  {cont__73_87, &frame__73_86, 590, 590, 30, 60},
  {cont__73_88, &frame__73_86, 590, 590, 25, 61},
  {cont__73_89, &frame__73_86, 590, 590, 7, 61},
  {cont__73_90, &frame__73_86, 591, 591, 7, 75},
  {entry__73_99, NULL, 598, 598, 37, 60},
  {cont__73_100, &frame__73_99, 598, 598, 37, 60},
  {entry__73_102, NULL, 600, 600, 35, 35},
  {entry__73_96, NULL, 597, 597, 11, 47},
  {cont__73_97, &frame__73_96, 598, 598, 14, 32},
  {cont__73_98, &frame__73_96, 598, 598, 14, 60},
  {cont__73_101, &frame__73_96, 598, 600, 11, 35},
  {entry__73_104, NULL, 604, 604, 13, 37},
  {cont__73_105, &frame__73_104, 605, 605, 13, 32},
  {cont__73_106, &frame__73_104, 602, 605, 11, 32},
  {entry__73_95, NULL, 596, 600, 9, 36},
  {cont__73_103, &frame__73_95, 601, 605, 9, 33},
  {entry__73_113, NULL, 613, 613, 39, 62},
  {cont__73_114, &frame__73_113, 613, 613, 39, 62},
  {entry__73_116, NULL, 615, 615, 37, 37},
  {entry__73_110, NULL, 612, 612, 13, 77},
  {cont__73_111, &frame__73_110, 613, 613, 16, 34},
  {cont__73_112, &frame__73_110, 613, 613, 16, 62},
  {cont__73_115, &frame__73_110, 613, 615, 13, 37},
  {entry__73_119, NULL, 617, 617, 32, 53},
  {cont__73_120, &frame__73_119, 617, 617, 13, 65},
  {cont__73_121, &frame__73_119, 618, 618, 13, 39},
  {cont__73_122, &frame__73_119, 619, 619, 13, 35},
  {cont__73_123, &frame__73_119, 619, 619, 38, 38},
  {entry__73_109, NULL, 611, 615, 11, 38},
  {cont__73_117, &frame__73_109, 616, 616, 14, 37},
  {cont__73_118, &frame__73_109, 616, 619, 11, 38},
  {entry__73_130, NULL, 624, 624, 40, 69},
  {cont__73_132, &frame__73_130, 624, 624, 69, 69},
  {entry__73_129, NULL, 624, 624, 13, 69},
  {entry__73_125, NULL, 621, 621, 11, 61},
  {cont__73_126, &frame__73_125, 622, 622, 11, 38},
  {cont__73_127, &frame__73_125, 623, 623, 14, 33},
  {cont__73_128, &frame__73_125, 623, 624, 11, 69},
  {cont__73_133, &frame__73_125, 625, 625, 11, 39},
  {cont__73_134, &frame__73_125, 625, 625, 39, 39},
  {entry__73_108, NULL, 608, 619, 9, 39},
  {cont__73_124, &frame__73_108, 620, 625, 9, 39},
  {entry__73_94, NULL, 593, 605, 7, 34},
  {cont__73_107, &frame__73_94, 606, 625, 7, 40},
  {entry__73_1_compile_module, NULL, 581, 581, 3, 40},
  {cont__73_73, &frame__73_1_compile_module, 582, 582, 10, 28},
  {cont__73_74, &frame__73_1_compile_module, 582, 584, 3, 57},
  {cont__73_79, &frame__73_1_compile_module, 585, 585, 3, 39},
  {cont__73_81, &frame__73_1_compile_module, 586, 586, 6, 24},
  {cont__73_82, &frame__73_1_compile_module, 586, 586, 3, 31},
  {cont__73_83, &frame__73_1_compile_module, 587, 587, 3, 22},
  {cont__73_84, &frame__73_1_compile_module, 589, 589, 5, 21},
  {cont__73_85, &frame__73_1_compile_module, 588, 625, 3, 42},
  {cont__73_135, &frame__73_1_compile_module, 625, 625, 42, 42},
  {entry__74_4, NULL, 634, 634, 21, 41},
  {cont__74_5, &frame__74_4, 634, 634, 43, 67},
  {cont__74_6, &frame__74_4, 634, 634, 5, 67},
  {entry__74_8, NULL, 636, 636, 20, 40},
  {cont__74_9, &frame__74_8, 636, 636, 42, 66},
  {cont__74_10, &frame__74_8, 636, 636, 5, 66},
  {entry__74_1_compile_modules, NULL, 632, 632, 47, 66},
  {cont__74_2, &frame__74_1_compile_modules, 632, 632, 3, 66},
  {cont__74_3, &frame__74_1_compile_modules, 633, 634, 3, 67},
  {cont__74_7, &frame__74_1_compile_modules, 635, 636, 3, 66},
  {entry__76_6, NULL, 645, 645, 34, 58},
  {cont__76_8, &frame__76_6, 645, 645, 25, 58},
  {entry__76_2, NULL, 644, 644, 5, 40},
  {cont__76_4, &frame__76_2, 645, 645, 8, 22},
  {cont__76_5, &frame__76_2, 645, 645, 5, 58},
  {cont__76_9, &frame__76_2, 646, 646, 40, 57},
  {cont__76_10, &frame__76_2, 646, 646, 5, 57},
  {cont__76_12, &frame__76_2, 647, 647, 35, 54},
  {cont__76_13, &frame__76_2, 647, 647, 5, 54},
  {entry__76_1_show_file_list, NULL, 643, 647, 3, 54},
  {entry__77_7, NULL, 656, 656, 60, 70},
  {cont__77_9, &frame__77_7, 656, 656, 40, 70},
  {cont__77_10, &frame__77_7, 656, 656, 70, 70},
  {entry__77_5, NULL, 656, 656, 14, 30},
  {cont__77_6, &frame__77_5, 656, 656, 5, 70},
  {entry__77_12, NULL, 657, 657, 54, 77},
  {cont__77_13, &frame__77_12, 657, 657, 27, 77},
  {entry__77_16, NULL, 658, 658, 30, 54},
  {cont__77_17, &frame__77_16, 658, 658, 54, 54},
  {entry__77_25, NULL, 667, 667, 16, 45},
  {cont__77_28, &frame__77_25, 667, 667, 13, 45},
  {entry__77_29, NULL, 668, 668, 16, 38},
  {cont__77_31, &frame__77_29, 668, 668, 13, 38},
  {entry__77_21, NULL, 666, 666, 13, 30},
  {cont__77_22, &frame__77_21, 666, 666, 13, 41},
  {cont__77_24, &frame__77_21, 665, 668, 11, 37},
  {cont__77_32, &frame__77_21, 664, 668, 9, 39},
  {entry__77_35, NULL, 672, 672, 25, 44},
  {cont__77_36, &frame__77_35, 672, 672, 52, 71},
  {cont__77_37, &frame__77_35, 672, 672, 16, 73},
  {cont__77_38, &frame__77_35, 672, 673, 13, 26},
  {entry__77_39, NULL, 674, 674, 16, 29},
  {cont__77_40, &frame__77_39, 674, 674, 13, 29},
  {entry__77_33, NULL, 671, 671, 13, 34},
  {cont__77_34, &frame__77_33, 670, 674, 11, 28},
  {cont__77_41, &frame__77_33, 669, 674, 9, 30},
  {entry__77_19, NULL, 663, 663, 9, 35},
  {cont__77_20, &frame__77_19, 662, 674, 7, 30},
  {cont__77_42, &frame__77_19, 660, 674, 5, 32},
  {cont__77_43, &frame__77_19, 674, 674, 33, 33},
  {entry__77_1_library_paths_and_file_list, NULL, 650, 650, 3, 16},
  {cont__77_2, &frame__77_1_library_paths_and_file_list, 654, 654, 3, 39},
  {cont__77_3, &frame__77_1_library_paths_and_file_list, 655, 655, 6, 21},
  {cont__77_4, &frame__77_1_library_paths_and_file_list, 655, 656, 3, 70},
  {cont__77_11, &frame__77_1_library_paths_and_file_list, 657, 657, 3, 77},
  {cont__77_15, &frame__77_1_library_paths_and_file_list, 658, 658, 3, 54},
  {cont__77_18, &frame__77_1_library_paths_and_file_list, 659, 674, 3, 33},
  {cont__77_44, &frame__77_1_library_paths_and_file_list, 675, 675, 24, 57},
  {cont__77_45, &frame__77_1_library_paths_and_file_list, 675, 675, 3, 57},
  {entry__78_9, NULL, 685, 685, 51, 64},
  {cont__78_10, &frame__78_9, 685, 685, 51, 64},
  {entry__78_7, NULL, 685, 685, 37, 46},
  {cont__78_8, &frame__78_7, 685, 685, 37, 64},
  {cont__78_11, &frame__78_7, 685, 685, 37, 64},
  {entry__78_29, NULL, 696, 696, 25, 59},
  {cont__78_31, &frame__78_29, 696, 696, 21, 60},
  {cont__78_32, &frame__78_29, 696, 696, 21, 60},
  {entry__78_25, NULL, 695, 695, 25, 58},
  {cont__78_27, &frame__78_25, 695, 695, 21, 59},
  {cont__78_28, &frame__78_25, 696, 696, 21, 60},
  {cont__78_33, &frame__78_25, },
  {entry__78_38, NULL, 700, 700, 46, 80},
  {cont__78_39, &frame__78_38, 700, 700, 46, 80},
  {entry__78_41, NULL, 702, 702, 44, 74},
  {cont__78_42, &frame__78_41, 702, 702, 23, 74},
  {entry__78_35, NULL, 700, 700, 21, 34},
  {cont__78_36, &frame__78_35, 700, 700, 21, 41},
  {cont__78_37, &frame__78_35, 700, 700, 21, 80},
  {cont__78_40, &frame__78_35, 699, 702, 19, 75},
  {entry__78_49, NULL, 705, 705, 60, 60},
  {cont__78_50, &frame__78_49, 705, 705, 44, 61},
  {cont__78_51, &frame__78_49, 705, 705, 23, 61},
  {entry__78_46, NULL, 704, 704, 35, 62},
  {cont__78_47, &frame__78_46, 704, 704, 35, 67},
  {cont__78_48, &frame__78_46, 704, 705, 21, 61},
  {entry__78_43, NULL, 703, 703, 22, 62},
  {cont__78_45, &frame__78_43, 703, 705, 19, 62},
  {entry__78_52, NULL, 707, 707, 21, 52},
  {entry__78_54, NULL, 708, 708, 31, 45},
  {entry__78_21, NULL, 694, 694, 21, 34},
  {cont__78_22, &frame__78_21, 694, 694, 21, 41},
  {cont__78_23, &frame__78_21, 694, 694, 21, 41},
  {cont__78_24, &frame__78_21, 692, 696, 17, 61},
  {cont__78_34, &frame__78_21, 698, 707, 17, 53},
  {cont__78_53, &frame__78_21, 708, 708, 17, 45},
  {cont__78_56, &frame__78_21, 709, 709, 17, 33},
  {entry__78_17, NULL, 689, 689, 15, 38},
  {cont__78_18, &frame__78_17, 690, 690, 15, 50},
  {cont__78_19, &frame__78_17, 691, 691, 18, 39},
  {cont__78_20, &frame__78_17, 691, 709, 15, 33},
  {entry__78_13, NULL, 686, 686, 33, 37},
  {cont__78_14, &frame__78_13, 686, 686, 13, 38},
  {cont__78_15, &frame__78_13, 688, 688, 20, 42},
  {cont__78_16, &frame__78_13, 688, 709, 13, 34},
  {entry__78_5, NULL, 685, 685, 18, 32},
  {cont__78_6, &frame__78_5, 685, 685, 18, 64},
  {cont__78_12, &frame__78_5, 685, 709, 11, 35},
  {entry__78_59, NULL, 711, 711, 33, 42},
  {cont__78_60, &frame__78_59, 711, 711, 33, 42},
  {entry__78_62, NULL, 711, 711, 50, 50},
  {entry__78_57, NULL, 711, 711, 14, 28},
  {cont__78_58, &frame__78_57, 711, 711, 14, 42},
  {cont__78_61, &frame__78_57, 711, 711, 11, 50},
  {entry__78_3, NULL, 684, 684, 9, 20},
  {cont__78_4, &frame__78_3, 683, 711, 7, 51},
  {entry__78_2_collect_declarations, NULL, 682, 711, 5, 52},
  {entry__78_63, NULL, 713, 713, 28, 54},
  {entry__78_74, NULL, 718, 718, 22, 59},
  {entry__78_1_create_imports, NULL, 713, 713, 3, 54},
  {cont__78_64, &frame__78_1_create_imports, 714, 714, 3, 49},
  {cont__78_66, &frame__78_1_create_imports, 715, 715, 3, 18},
  {cont__78_67, &frame__78_1_create_imports, 716, 716, 3, 15},
  {cont__78_68, &frame__78_1_create_imports, 717, 717, 22, 42},
  {cont__78_69, &frame__78_1_create_imports, 717, 717, 22, 45},
  {cont__78_70, &frame__78_1_create_imports, 717, 717, 48, 48},
  {cont__78_71, &frame__78_1_create_imports, 717, 717, 9, 49},
  {cont__78_72, &frame__78_1_create_imports, 717, 717, 3, 49},
  {cont__78_73, &frame__78_1_create_imports, 718, 718, 3, 59},
  {entry__79_3, NULL, 721, 721, 32, 67},
  {entry__79_7, NULL, 723, 724, 5, 57},
  {entry__79_1_compile_exe, NULL, 721, 721, 6, 29},
  {cont__79_2, &frame__79_1_compile_exe, 721, 721, 3, 67},
  {cont__79_5, &frame__79_1_compile_exe, 722, 722, 10, 42},
  {cont__79_6, &frame__79_1_compile_exe, 722, 724, 3, 58},
  {cont__79_9, &frame__79_1_compile_exe, 726, 726, 3, 53},
  {cont__79_10, &frame__79_1_compile_exe, 727, 727, 46, 46},
  {cont__79_11, &frame__79_1_compile_exe, 727, 727, 3, 47},
  {cont__79_12, &frame__79_1_compile_exe, 728, 728, 3, 28},
  {cont__79_13, &frame__79_1_compile_exe, 728, 728, 28, 28},
  {entry__80_2, NULL, 733, 733, 11, 29},
  {cont__80_3, &frame__80_2, 733, 733, 5, 29},
  {cont__80_4, &frame__80_2, 733, 733, 29, 29},
  {entry__80_1_dump_source_or_check, NULL, 731, 733, 3, 29},
  {entry__81_4, NULL, 737, 737, 41, 65},
  {cont__81_5, &frame__81_4, 737, 737, 34, 75},
  {cont__81_6, &frame__81_4, 737, 737, 75, 75},
  {entry__81_8, NULL, 739, 739, 48, 57},
  {cont__81_9, &frame__81_8, 739, 739, 59, 68},
  {cont__81_10, &frame__81_8, 739, 739, 7, 69},
  {cont__81_11, &frame__81_8, 740, 740, 13, 31},
  {cont__81_12, &frame__81_8, 740, 740, 7, 31},
  {cont__81_13, &frame__81_8, 740, 740, 31, 31},
  {entry__81_15, NULL, 741, 741, 28, 50},
  {entry__81_18, NULL, 743, 743, 24, 59},
  {entry__81_2, NULL, 737, 737, 8, 31},
  {cont__81_3, &frame__81_2, 737, 737, 5, 75},
  {cont__81_7, &frame__81_2, 738, 740, 5, 31},
  {cont__81_14, &frame__81_2, 741, 741, 5, 50},
  {cont__81_16, &frame__81_2, 742, 742, 5, 15},
  {cont__81_17, &frame__81_2, 743, 743, 5, 59},
  {entry__81_1_print_c, NULL, 736, 743, 3, 59},
  {entry__82_5, NULL, 752, 752, 9, 43},
  {cont__82_6, &frame__82_5, 753, 753, 12, 28},
  {cont__82_7, &frame__82_5, 753, 753, 9, 34},
  {cont__82_8, &frame__82_5, 754, 754, 9, 21},
  {cont__82_9, &frame__82_5, 755, 755, 9, 64},
  {cont__82_10, &frame__82_5, 756, 756, 12, 23},
  {cont__82_11, &frame__82_5, 756, 756, 9, 29},
  {cont__82_12, &frame__82_5, 757, 757, 22, 22},
  {entry__82_4, NULL, 751, 757, 7, 22},
  {cont__82_13, &frame__82_4, 757, 757, 22, 22},
  {entry__82_3, NULL, 750, 757, 5, 23},
  {entry__82_17, NULL, 761, 761, 19, 65},
  {entry__82_16, NULL, 761, 761, 7, 65},
  {cont__82_19, &frame__82_16, 762, 762, 63, 63},
  {cont__82_20, &frame__82_16, 762, 762, 37, 64},
  {cont__82_21, &frame__82_16, 762, 762, 7, 64},
  {cont__82_22, &frame__82_16, 762, 762, 64, 64},
  {entry__82_25, NULL, 765, 765, 21, 66},
  {entry__82_24, NULL, 765, 765, 9, 66},
  {cont__82_26, &frame__82_24, 766, 766, 9, 44},
  {entry__82_23, NULL, 764, 766, 7, 44},
  {cont__82_27, &frame__82_23, 767, 767, 7, 32},
  {cont__82_29, &frame__82_23, 768, 768, 7, 32},
  {cont__82_31, &frame__82_23, 769, 769, 7, 34},
  {entry__82_35, NULL, 772, 772, 5, 40},
  {cont__82_36, &frame__82_35, 773, 773, 5, 32},
  {cont__82_37, &frame__82_35, 774, 774, 5, 20},
  {entry__82_1_list_dependencies, NULL, 746, 746, 3, 80},
  {cont__82_2, &frame__82_1_list_dependencies, 747, 757, 3, 24},
  {cont__82_14, &frame__82_1_list_dependencies, 759, 759, 5, 28},
  {cont__82_15, &frame__82_1_list_dependencies, 758, 769, 3, 35},
  {cont__82_33, &frame__82_1_list_dependencies, 770, 770, 3, 29},
  {cont__82_34, &frame__82_1_list_dependencies, 771, 774, 3, 20},
  {entry__83_7, NULL, 781, 782, 14, 58},
  {cont__83_10, &frame__83_7, 781, 782, 7, 58},
  {entry__83_12, NULL, 783, 783, 17, 73},
  {entry__83_34, NULL, 815, 817, 21, 49},
  {cont__83_37, &frame__83_34, 815, 817, 7, 49},
  {cont__83_38, &frame__83_34, 817, 817, 50, 50},
  {entry__83_53, NULL, 837, 837, 7, 42},
  {cont__83_54, &frame__83_53, 838, 838, 7, 34},
  {cont__83_55, &frame__83_53, 843, 843, 44, 55},
  {cont__83_56, &frame__83_53, 839, 844, 21, 23},
  {cont__83_59, &frame__83_53, 839, 844, 7, 23},
  {cont__83_60, &frame__83_53, 844, 844, 24, 24},
  {entry__83_2, NULL, 778, 778, 5, 55},
  {cont__83_4, &frame__83_2, 779, 779, 5, 31},
  {cont__83_5, &frame__83_2, 780, 780, 8, 22},
  {cont__83_6, &frame__83_2, 780, 782, 5, 59},
  {cont__83_11, &frame__83_2, 783, 783, 5, 73},
  {cont__83_14, &frame__83_2, 784, 784, 5, 40},
  {cont__83_15, &frame__83_2, 785, 785, 5, 18},
  {cont__83_16, &frame__83_2, 786, 786, 49, 49},
  {cont__83_17, &frame__83_2, 786, 786, 15, 50},
  {cont__83_18, &frame__83_2, 786, 786, 5, 74},
  {cont__83_19, &frame__83_2, 787, 787, 5, 31},
  {cont__83_20, &frame__83_2, 788, 788, 30, 73},
  {cont__83_21, &frame__83_2, 788, 788, 5, 78},
  {cont__83_22, &frame__83_2, 789, 789, 5, 33},
  {cont__83_24, &frame__83_2, 790, 790, 5, 61},
  {cont__83_27, &frame__83_2, 791, 791, 5, 25},
  {cont__83_28, &frame__83_2, 793, 813, 19, 22},
  {cont__83_32, &frame__83_2, 793, 813, 5, 22},
  {cont__83_33, &frame__83_2, 814, 817, 5, 50},
  {cont__83_39, &frame__83_2, 828, 828, 42, 53},
  {cont__83_40, &frame__83_2, 831, 831, 42, 53},
  {cont__83_41, &frame__83_2, 834, 834, 42, 53},
  {cont__83_42, &frame__83_2, 818, 835, 19, 21},
  {cont__83_51, &frame__83_2, 818, 835, 5, 21},
  {cont__83_52, &frame__83_2, 836, 844, 5, 24},
  {cont__83_61, &frame__83_2, 845, 851, 5, 32},
  {cont__83_63, &frame__83_2, 852, 852, 5, 25},
  {entry__83_1_build_codeblocks_project, NULL, 777, 852, 3, 25},
  {entry__84_4, NULL, 855, 855, 26, 56},
  {entry__84_7, NULL, 859, 859, 7, 41},
  {entry__84_12, NULL, 865, 865, 29, 50},
  {cont__84_13, &frame__84_12, 865, 865, 29, 55},
  {cont__84_14, &frame__84_12, 865, 865, 9, 56},
  {cont__84_15, &frame__84_12, 866, 866, 9, 47},
  {cont__84_16, &frame__84_12, 866, 866, 47, 47},
  {entry__84_21, NULL, 873, 873, 53, 66},
  {cont__84_22, &frame__84_21, 873, 873, 14, 67},
  {cont__84_24, &frame__84_21, 873, 873, 11, 67},
  {entry__84_25, NULL, 875, 875, 53, 67},
  {cont__84_27, &frame__84_25, 875, 875, 14, 68},
  {cont__84_28, &frame__84_25, 875, 875, 11, 68},
  {entry__84_29, NULL, 877, 877, 53, 69},
  {cont__84_31, &frame__84_29, 877, 877, 14, 70},
  {cont__84_32, &frame__84_29, 877, 877, 11, 70},
  {entry__84_33, NULL, 878, 878, 14, 50},
  {cont__84_35, &frame__84_33, 878, 878, 11, 50},
  {entry__84_39, NULL, 880, 880, 19, 56},
  {entry__84_48, NULL, 887, 887, 38, 63},
  {cont__84_49, &frame__84_48, 887, 887, 13, 63},
  {cont__84_50, &frame__84_48, 887, 887, 13, 63},
  {entry__84_52, NULL, 889, 889, 25, 25},
  {entry__84_45, NULL, 883, 883, 9, 32},
  {cont__84_46, &frame__84_45, 886, 886, 13, 29},
  {cont__84_47, &frame__84_45, 885, 887, 11, 62},
  {cont__84_51, &frame__84_45, 884, 889, 9, 26},
  {entry__84_55, NULL, 891, 891, 21, 54},
  {entry__84_67, NULL, 901, 901, 35, 47},
  {cont__84_68, &frame__84_67, 901, 901, 29, 47},
  {entry__84_61, NULL, 897, 897, 15, 76},
  {cont__84_63, &frame__84_61, 898, 898, 15, 43},
  {cont__84_64, &frame__84_61, 895, 900, 13, 26},
  {cont__84_66, &frame__84_61, 901, 901, 13, 47},
  {entry__84_74, NULL, 909, 909, 35, 47},
  {cont__84_75, &frame__84_74, 909, 909, 29, 47},
  {entry__84_69, NULL, 905, 905, 15, 43},
  {cont__84_70, &frame__84_69, 906, 906, 15, 30},
  {cont__84_72, &frame__84_69, 903, 908, 13, 26},
  {cont__84_73, &frame__84_69, 909, 909, 13, 47},
  {entry__84_83, NULL, 920, 920, 35, 47},
  {cont__84_84, &frame__84_83, 920, 920, 29, 47},
  {entry__84_76, NULL, 913, 915, 15, 23},
  {cont__84_78, &frame__84_76, 916, 916, 15, 43},
  {cont__84_79, &frame__84_76, 917, 917, 15, 30},
  {cont__84_80, &frame__84_76, 911, 919, 13, 26},
  {cont__84_82, &frame__84_76, 920, 920, 13, 47},
  {entry__84_88, NULL, 927, 927, 35, 47},
  {cont__84_89, &frame__84_88, 927, 927, 29, 47},
  {entry__84_85, NULL, 924, 924, 15, 43},
  {cont__84_86, &frame__84_85, 922, 926, 13, 26},
  {cont__84_87, &frame__84_85, 927, 927, 13, 47},
  {entry__84_54, NULL, 891, 891, 9, 54},
  {cont__84_57, &frame__84_54, 893, 893, 11, 28},
  {cont__84_58, &frame__84_54, 894, 894, 11, 24},
  {cont__84_60, &frame__84_54, 892, 927, 9, 48},
  {entry__84_8, NULL, 863, 863, 7, 56},
  {cont__84_10, &frame__84_8, 864, 864, 10, 38},
  {cont__84_11, &frame__84_8, 864, 866, 7, 47},
  {cont__84_17, &frame__84_8, 867, 867, 56, 56},
  {cont__84_18, &frame__84_8, 867, 867, 7, 57},
  {cont__84_19, &frame__84_8, 871, 871, 11, 28},
  {cont__84_20, &frame__84_8, 869, 878, 7, 51},
  {cont__84_38, &frame__84_8, 880, 880, 7, 56},
  {cont__84_41, &frame__84_8, 881, 881, 63, 63},
  {cont__84_42, &frame__84_8, 881, 881, 37, 64},
  {cont__84_43, &frame__84_8, 881, 881, 7, 64},
  {cont__84_44, &frame__84_8, 882, 889, 7, 27},
  {cont__84_53, &frame__84_8, 890, 927, 7, 49},
  {entry__84_1_build_library, NULL, 855, 855, 6, 23},
  {cont__84_3, &frame__84_1_build_library, 855, 855, 3, 56},
  {cont__84_6, &frame__84_1_build_library, 857, 927, 3, 51},
  {cont__84_90, &frame__84_1_build_library, 927, 927, 51, 51},
  {entry__85_6, NULL, 934, 935, 11, 42},
  {cont__85_9, &frame__85_6, 934, 935, 5, 42},
  {entry__85_13, NULL, 940, 940, 38, 65},
  {cont__85_14, &frame__85_13, 940, 940, 7, 34},
  {cont__85_15, &frame__85_13, 940, 940, 7, 65},
  {cont__85_16, &frame__85_13, 940, 940, 7, 65},
  {entry__85_19, NULL, 942, 942, 28, 65},
  {cont__85_21, &frame__85_19, 942, 942, 19, 65},
  {entry__85_18, NULL, 942, 942, 7, 65},
  {cont__85_22, &frame__85_18, 943, 943, 7, 37},
  {entry__85_1_maybe_compile_c_file, NULL, 930, 930, 3, 35},
  {cont__85_2, &frame__85_1_maybe_compile_c_file, 931, 931, 3, 35},
  {cont__85_3, &frame__85_1_maybe_compile_c_file, 932, 932, 3, 26},
  {cont__85_4, &frame__85_1_maybe_compile_c_file, 933, 933, 6, 24},
  {cont__85_5, &frame__85_1_maybe_compile_c_file, 933, 935, 3, 43},
  {cont__85_10, &frame__85_1_maybe_compile_c_file, 936, 936, 3, 26},
  {cont__85_11, &frame__85_1_maybe_compile_c_file, 939, 939, 7, 25},
  {cont__85_12, &frame__85_1_maybe_compile_c_file, 938, 940, 5, 64},
  {cont__85_17, &frame__85_1_maybe_compile_c_file, 937, 943, 3, 38},
  {entry__87_11, NULL, 959, 959, 39, 41},
  {cont__87_12, &frame__87_11, 959, 959, 36, 41},
  {cont__87_13, &frame__87_11, 959, 959, 28, 43},
  {cont__87_15, &frame__87_11, 959, 959, 21, 48},
  {cont__87_16, &frame__87_11, 959, 959, 48, 48},
  {entry__87_6, NULL, 958, 958, 13, 26},
  {cont__87_7, &frame__87_6, 958, 958, 9, 28},
  {cont__87_8, &frame__87_6, 959, 959, 16, 18},
  {cont__87_9, &frame__87_6, 959, 959, 12, 18},
  {cont__87_10, &frame__87_6, 959, 959, 9, 48},
  {cont__87_17, &frame__87_6, 960, 960, 9, 13},
  {entry__87_4, NULL, 957, 957, 10, 19},
  {cont__87_5, &frame__87_4, 957, 960, 7, 13},
  {entry__87_3, NULL, 956, 960, 5, 14},
  {cont__87_18, &frame__87_3, 960, 960, 14, 14},
  {entry__87_21, NULL, 963, 963, 27, 30},
  {cont__87_22, &frame__87_21, 963, 963, 19, 31},
  {cont__87_24, &frame__87_21, 963, 963, 7, 31},
  {cont__87_25, &frame__87_21, 963, 963, 31, 31},
  {entry__87_28, NULL, 965, 965, 33, 36},
  {cont__87_29, &frame__87_28, 965, 965, 33, 38},
  {cont__87_30, &frame__87_28, 965, 965, 33, 39},
  {cont__87_31, &frame__87_28, 965, 965, 18, 39},
  {cont__87_32, &frame__87_28, 965, 965, 39, 39},
  {entry__87_26, NULL, 965, 965, 10, 15},
  {cont__87_27, &frame__87_26, 965, 965, 7, 39},
  {entry__87_1_format_number, NULL, 953, 953, 3, 16},
  {cont__87_2, &frame__87_1_format_number, 955, 960, 3, 15},
  {cont__87_19, &frame__87_1_format_number, 962, 962, 5, 10},
  {cont__87_20, &frame__87_1_format_number, 961, 965, 3, 40},
  {cont__87_33, &frame__87_1_format_number, 966, 966, 3, 8},
  {entry__88_4, NULL, 972, 972, 37, 37},
  {cont__88_5, &frame__88_4, 972, 972, 7, 37},
  {cont__88_6, &frame__88_4, 978, 978, 20, 41},
  {cont__88_7, &frame__88_4, 978, 978, 17, 41},
  {cont__88_8, &frame__88_4, 978, 978, 9, 42},
  {cont__88_9, &frame__88_4, 979, 979, 23, 29},
  {cont__88_10, &frame__88_4, 979, 979, 9, 34},
  {cont__88_11, &frame__88_4, 973, 980, 7, 12},
  {entry__88_13, NULL, 982, 982, 47, 53},
  {cont__88_14, &frame__88_13, 982, 982, 33, 58},
  {cont__88_15, &frame__88_13, 982, 982, 7, 63},
  {entry__88_1_sim2c__write_timing_info, NULL, 969, 969, 3, 23},
  {cont__88_2, &frame__88_1_sim2c__write_timing_info, 971, 971, 5, 23},
  {cont__88_3, &frame__88_1_sim2c__write_timing_info, 970, 982, 3, 64},
  {cont__88_17, &frame__88_1_sim2c__write_timing_info, 983, 983, 3, 19},
  {cont__88_18, &frame__88_1_sim2c__write_timing_info, 983, 983, 19, 19},
  {entry__89_5, NULL, 999, 999, 12, 38},
  {cont__89_7, &frame__89_5, 999, 999, 9, 38},
  {entry__89_8, NULL, 1000, 1000, 9, 23},
  {entry__89_10, NULL, 1002, 1002, 17, 57},
  {entry__89_20, NULL, 1013, 1013, 42, 69},
  {cont__89_21, &frame__89_20, 1013, 1013, 9, 38},
  {cont__89_22, &frame__89_20, 1013, 1013, 9, 69},
  {cont__89_23, &frame__89_20, 1013, 1013, 9, 69},
  {entry__89_18, NULL, 1012, 1012, 9, 27},
  {cont__89_19, &frame__89_18, 1013, 1013, 9, 69},
  {cont__89_24, &frame__89_18, },
  {entry__89_29, NULL, 1016, 1016, 21, 61},
  {entry__89_32, NULL, 1017, 1017, 41, 59},
  {cont__89_33, &frame__89_32, 1017, 1017, 35, 64},
  {entry__89_35, NULL, 1018, 1018, 32, 54},
  {entry__89_39, NULL, 1020, 1020, 28, 64},
  {entry__89_43, NULL, 1022, 1022, 28, 67},
  {entry__89_26, NULL, 1015, 1015, 55, 67},
  {cont__89_27, &frame__89_26, 1015, 1015, 9, 67},
  {cont__89_28, &frame__89_26, 1016, 1016, 9, 61},
  {cont__89_31, &frame__89_26, 1017, 1017, 9, 64},
  {cont__89_34, &frame__89_26, 1018, 1018, 9, 54},
  {cont__89_36, &frame__89_26, 1019, 1019, 25, 37},
  {cont__89_37, &frame__89_26, 1019, 1019, 9, 37},
  {cont__89_38, &frame__89_26, 1020, 1020, 9, 64},
  {cont__89_41, &frame__89_26, 1021, 1021, 9, 39},
  {cont__89_42, &frame__89_26, 1022, 1022, 9, 67},
  {cont__89_45, &frame__89_26, 1022, 1022, 67, 67},
  {entry__89_50, NULL, 1029, 1029, 44, 71},
  {cont__89_51, &frame__89_50, 1029, 1029, 13, 40},
  {cont__89_52, &frame__89_50, 1029, 1029, 13, 71},
  {cont__89_53, &frame__89_50, 1029, 1029, 13, 71},
  {entry__89_55, NULL, 1031, 1031, 13, 43},
  {entry__89_56, NULL, 1033, 1033, 13, 64},
  {cont__89_57, &frame__89_56, 1033, 1033, 64, 64},
  {entry__89_46, NULL, 1024, 1024, 9, 30},
  {cont__89_47, &frame__89_46, 1025, 1025, 9, 32},
  {cont__89_48, &frame__89_46, 1028, 1028, 13, 31},
  {cont__89_49, &frame__89_46, 1027, 1029, 11, 70},
  {cont__89_54, &frame__89_46, 1026, 1033, 9, 65},
  {entry__89_65, NULL, 1038, 1038, 11, 39},
  {entry__89_60, NULL, 1037, 1037, 9, 62},
  {cont__89_64, &frame__89_60, 1036, 1038, 7, 40},
  {entry__89_72, NULL, 1046, 1046, 38, 63},
  {cont__89_73, &frame__89_72, 1046, 1046, 13, 63},
  {cont__89_74, &frame__89_72, 1046, 1046, 13, 63},
  {entry__89_70, NULL, 1045, 1045, 13, 45},
  {cont__89_71, &frame__89_70, 1044, 1046, 11, 62},
  {cont__89_75, &frame__89_70, 1044, 1046, 11, 62},
  {entry__89_77, NULL, 1048, 1048, 23, 23},
  {entry__89_67, NULL, 1040, 1040, 7, 30},
  {cont__89_68, &frame__89_67, 1043, 1043, 11, 27},
  {cont__89_69, &frame__89_67, 1042, 1046, 9, 63},
  {cont__89_76, &frame__89_67, 1041, 1048, 7, 24},
  {entry__89_81, NULL, 1051, 1051, 28, 75},
  {cont__89_83, &frame__89_81, 1051, 1051, 75, 75},
  {entry__89_86, NULL, 1054, 1054, 23, 58},
  {entry__89_93, NULL, 1062, 1062, 33, 45},
  {cont__89_94, &frame__89_93, 1062, 1062, 27, 45},
  {entry__89_85, NULL, 1054, 1054, 11, 58},
  {cont__89_88, &frame__89_85, 1055, 1061, 11, 24},
  {cont__89_92, &frame__89_85, 1062, 1062, 11, 45},
  {entry__89_96, NULL, 1064, 1064, 23, 51},
  {entry__89_101, NULL, 1069, 1069, 18, 40},
  {cont__89_103, &frame__89_101, 1069, 1069, 15, 40},
  {entry__89_104, NULL, 1070, 1070, 18, 33},
  {cont__89_105, &frame__89_104, 1070, 1070, 15, 33},
  {entry__89_108, NULL, 1073, 1073, 33, 45},
  {cont__89_109, &frame__89_108, 1073, 1073, 27, 45},
  {entry__89_95, NULL, 1064, 1064, 11, 51},
  {cont__89_98, &frame__89_95, 1068, 1068, 15, 32},
  {cont__89_99, &frame__89_95, 1068, 1068, 15, 43},
  {cont__89_100, &frame__89_95, 1067, 1070, 13, 32},
  {cont__89_106, &frame__89_95, 1065, 1072, 11, 24},
  {cont__89_107, &frame__89_95, 1073, 1073, 11, 45},
  {entry__89_79, NULL, 1050, 1050, 7, 52},
  {cont__89_80, &frame__89_79, 1051, 1051, 7, 75},
  {cont__89_84, &frame__89_79, 1052, 1073, 7, 46},
  {entry__89_113, NULL, 1075, 1075, 24, 41},
  {cont__89_114, &frame__89_113, 1075, 1075, 24, 41},
  {entry__89_118, NULL, 1079, 1079, 11, 25},
  {entry__89_119, NULL, 1080, 1080, 14, 38},
  {cont__89_120, &frame__89_119, 1080, 1080, 11, 38},
  {entry__89_116, NULL, 1078, 1078, 11, 39},
  {cont__89_117, &frame__89_116, 1077, 1080, 9, 37},
  {cont__89_121, &frame__89_116, 1076, 1083, 7, 44},
  {entry__89_2, NULL, 998, 998, 9, 26},
  {cont__89_3, &frame__89_2, 998, 998, 9, 38},
  {cont__89_4, &frame__89_2, 996, 1000, 5, 24},
  {cont__89_9, &frame__89_2, 1002, 1002, 5, 57},
  {cont__89_12, &frame__89_2, 1003, 1003, 5, 41},
  {cont__89_13, &frame__89_2, 1004, 1004, 5, 41},
  {cont__89_14, &frame__89_2, 1005, 1005, 5, 33},
  {cont__89_15, &frame__89_2, 1006, 1006, 5, 28},
  {cont__89_16, &frame__89_2, 1008, 1008, 5, 24},
  {cont__89_17, &frame__89_2, },
  {cont__89_25, &frame__89_2, 1009, 1033, 5, 67},
  {cont__89_58, &frame__89_2, 1034, 1034, 5, 50},
  {cont__89_59, &frame__89_2, 1035, 1038, 5, 41},
  {cont__89_66, &frame__89_2, 1039, 1048, 5, 25},
  {cont__89_78, &frame__89_2, 1049, 1073, 5, 47},
  {cont__89_110, &frame__89_2, 1074, 1074, 41, 41},
  {cont__89_111, &frame__89_2, 1074, 1074, 5, 42},
  {cont__89_112, &frame__89_2, 1075, 1075, 8, 41},
  {cont__89_115, &frame__89_2, 1075, 1083, 5, 45},
  {entry__89_1_build_executable, NULL, 995, 1083, 3, 46},
  {entry__104_2, NULL, 105, 105, 8, 28},
  {cont__104_3, &frame__104_2, 105, 105, 5, 28},
  {entry__104_4, NULL, 108, 108, 9, 48},
  {cont__104_6, &frame__104_4, 109, 109, 9, 42},
  {cont__104_8, &frame__104_4, 107, 109, 7, 41},
  {cont__104_9, &frame__104_4, 106, 109, 5, 43},
  {entry__105_2, NULL, 114, 114, 8, 29},
  {cont__105_3, &frame__105_2, 114, 114, 5, 29},
  {entry__105_4, NULL, 117, 117, 9, 48},
  {cont__105_5, &frame__105_4, 118, 118, 9, 42},
  {cont__105_6, &frame__105_4, 116, 118, 7, 41},
  {cont__105_7, &frame__105_4, 115, 118, 5, 43},
  {entry__109_4, NULL, 138, 138, 7, 41},
  {cont__109_5, &frame__109_4, 139, 139, 10, 26},
  {cont__109_6, &frame__109_4, 139, 139, 7, 32},
  {cont__109_7, &frame__109_4, 140, 140, 7, 19},
  {cont__109_8, &frame__109_4, 141, 141, 7, 34},
  {cont__109_9, &frame__109_4, 142, 142, 10, 21},
  {cont__109_10, &frame__109_4, 142, 142, 7, 27},
  {cont__109_11, &frame__109_4, 143, 143, 20, 20},
  {entry__109_3, NULL, 137, 143, 5, 20},
  {cont__109_12, &frame__109_3, 143, 143, 20, 20},
  {entry__109_1, NULL, 134, 134, 3, 31},
  {cont__109_2, &frame__109_1, 136, 143, 3, 21},
  {entry__134_4, NULL, 170, 170, 41, 79},
  {entry__134_2, NULL, 170, 170, 8, 38},
  {cont__134_3, &frame__134_2, 170, 170, 5, 79},
  {cont__134_6, &frame__134_2, 171, 171, 5, 45},
  {cont__134_7, &frame__134_2, 171, 171, 45, 45},
  {entry__134_9, NULL, 177, 178, 7, 52},
  {entry__134_12, NULL, 180, 181, 7, 34},
  {entry__134_15, NULL, 183, 184, 7, 57},
  {entry__134_18, NULL, 186, 187, 7, 71},
  {entry__134_21, NULL, 189, 190, 7, 47},
  {entry__134_24, NULL, 192, 193, 7, 61},
  {entry__134_27, NULL, 195, 198, 9, 29},
  {entry__134_30, NULL, 202, 203, 7, 33},
  {entry__134_33, NULL, 205, 206, 7, 29},
  {entry__134_36, NULL, 208, 209, 7, 35},
  {entry__134_39, NULL, 211, 212, 7, 40},
  {entry__134_42, NULL, 214, 215, 9, 65},
  {entry__134_45, NULL, 219, 220, 7, 35},
  {entry__134_48, NULL, 222, 223, 7, 45},
  {entry__134_51, NULL, 225, 226, 9, 31},
  {entry__134_54, NULL, 230, 231, 7, 32},
  {entry__134_57, NULL, 233, 234, 7, 33},
  {entry__134_60, NULL, 236, 237, 7, 43},
  {entry__134_63, NULL, 239, 240, 7, 29},
  {entry__134_66, NULL, 242, 243, 7, 46},
  {entry__134_8, NULL, 173, 243, 5, 47},
  {cont__134_69, &frame__134_8, 243, 243, 48, 48},
  {entry__138_1, NULL, 247, 247, 37, 37},
  {entry__148_1, NULL, 286, 286, 28, 38},
  {cont__148_3, &frame__148_1, 286, 286, 3, 38},
  {cont__148_4, &frame__148_1, 286, 286, 38, 38},
  {entry__149_7, NULL, 298, 298, 11, 24},
  {entry__149_8, NULL, 299, 299, 11, 23},
  {entry__167_2, NULL, 639, 640, 9, 51},
  {cont__167_5, &frame__167_2, 639, 640, 3, 51},
  {entry__182_1, NULL, 1085, 1085, 20, 36},
  {cont__182_2, &frame__182_1, 1085, 1085, 36, 36},
  {entry__183_4, NULL, 1092, 1092, 7, 32},
  {entry__183_3, NULL, },
  {cont__183_5, &frame__183_3, },
  {entry__183_2, NULL, },
  {cont__183_6, &frame__183_2, },
  {entry__183_1, NULL, },
  {cont__183_7, &frame__183_1, 1087, 1093, 3, 24},
  {entry__183_8, NULL, 1094, 1094, 3, 23},
  {entry__183_9, NULL, 1095, 1095, 3, 43},
  {entry__183_10, NULL, 1096, 1096, 3, 57},
  {entry__183_11, NULL, 1097, 1097, 6, 29},
  {cont__183_12, &frame__183_11, 1097, 1097, 3, 43}
};

union NODE {
  struct {
    FUNC type;
    ATTRIBUTES *attributes;
  };
  CONTINUATION continuation;
  CLOSURE closure;
};
static NODE *character__35;
static NODE *character__47;
static NODE *number__12;
static NODE *character__45;
static NODE *character__58;
static NODE *number__0;
static NODE *number__3;
static NODE *number__4;
static NODE *character__95;
static NODE *number__5;
static NODE *character__123;
static NODE *character__32;
static NODE *character__125;
static NODE *number__1;
static NODE *number__18;
static NODE *character__46;
static NODE *number__2;
static NODE *number__999;

static const char *used_namespaces[] = {
  "std",
  "sim2c",
  "node",
  NULL
};

static MODULE_INFO module_info = {
  NULL,
  "simple",
  continuation_info,
  sizeof(continuation_info)/sizeof(CONTINUATION_INFO),
  (NODE **)&var,
  var_names,
  sizeof(var_names)/sizeof(const char *),
  used_namespaces,
  {DEBUG_FILENAME("simple.sim")}
};

/******
C O D E
******/

IMPORT void collect__basic__exceptions(void);
IMPORT void phase_1__basic__exceptions(void);
IMPORT void phase_2__basic__exceptions(void);
IMPORT void phase_3__basic__exceptions(void);
IMPORT void phase_4__basic__exceptions(void);
IMPORT void phase_5__basic__exceptions(void);
IMPORT void phase_6__basic__exceptions(void);
IMPORT void run__basic__exceptions(void);
IMPORT void collect__basic__serialize(void);
IMPORT void phase_1__basic__serialize(void);
IMPORT void phase_2__basic__serialize(void);
IMPORT void phase_3__basic__serialize(void);
IMPORT void phase_4__basic__serialize(void);
IMPORT void phase_5__basic__serialize(void);
IMPORT void phase_6__basic__serialize(void);
IMPORT void run__basic__serialize(void);
IMPORT void collect__basic__deserialize(void);
IMPORT void phase_1__basic__deserialize(void);
IMPORT void phase_2__basic__deserialize(void);
IMPORT void phase_3__basic__deserialize(void);
IMPORT void phase_4__basic__deserialize(void);
IMPORT void phase_5__basic__deserialize(void);
IMPORT void phase_6__basic__deserialize(void);
IMPORT void run__basic__deserialize(void);
IMPORT void collect__basic__branches(void);
IMPORT void phase_1__basic__branches(void);
IMPORT void phase_2__basic__branches(void);
IMPORT void phase_3__basic__branches(void);
IMPORT void phase_4__basic__branches(void);
IMPORT void phase_5__basic__branches(void);
IMPORT void phase_6__basic__branches(void);
IMPORT void run__basic__branches(void);
IMPORT void collect__basic__debug(void);
IMPORT void phase_1__basic__debug(void);
IMPORT void phase_2__basic__debug(void);
IMPORT void phase_3__basic__debug(void);
IMPORT void phase_4__basic__debug(void);
IMPORT void phase_5__basic__debug(void);
IMPORT void phase_6__basic__debug(void);
IMPORT void run__basic__debug(void);
IMPORT void collect__basic__environment(void);
IMPORT void phase_1__basic__environment(void);
IMPORT void phase_2__basic__environment(void);
IMPORT void phase_3__basic__environment(void);
IMPORT void phase_4__basic__environment(void);
IMPORT void phase_5__basic__environment(void);
IMPORT void phase_6__basic__environment(void);
IMPORT void run__basic__environment(void);
IMPORT void collect__basic__event(void);
IMPORT void phase_1__basic__event(void);
IMPORT void phase_2__basic__event(void);
IMPORT void phase_3__basic__event(void);
IMPORT void phase_4__basic__event(void);
IMPORT void phase_5__basic__event(void);
IMPORT void phase_6__basic__event(void);
IMPORT void run__basic__event(void);
IMPORT void collect__basic__exec(void);
IMPORT void phase_1__basic__exec(void);
IMPORT void phase_2__basic__exec(void);
IMPORT void phase_3__basic__exec(void);
IMPORT void phase_4__basic__exec(void);
IMPORT void phase_5__basic__exec(void);
IMPORT void phase_6__basic__exec(void);
IMPORT void run__basic__exec(void);
IMPORT void collect__basic__functional(void);
IMPORT void phase_1__basic__functional(void);
IMPORT void phase_2__basic__functional(void);
IMPORT void phase_3__basic__functional(void);
IMPORT void phase_4__basic__functional(void);
IMPORT void phase_5__basic__functional(void);
IMPORT void phase_6__basic__functional(void);
IMPORT void run__basic__functional(void);
IMPORT void collect__basic__grammar(void);
IMPORT void phase_1__basic__grammar(void);
IMPORT void phase_2__basic__grammar(void);
IMPORT void phase_3__basic__grammar(void);
IMPORT void phase_4__basic__grammar(void);
IMPORT void phase_5__basic__grammar(void);
IMPORT void phase_6__basic__grammar(void);
IMPORT void run__basic__grammar(void);
IMPORT void collect__basic__io(void);
IMPORT void phase_1__basic__io(void);
IMPORT void phase_2__basic__io(void);
IMPORT void phase_3__basic__io(void);
IMPORT void phase_4__basic__io(void);
IMPORT void phase_5__basic__io(void);
IMPORT void phase_6__basic__io(void);
IMPORT void run__basic__io(void);
IMPORT void collect__basic__loops(void);
IMPORT void phase_1__basic__loops(void);
IMPORT void phase_2__basic__loops(void);
IMPORT void phase_3__basic__loops(void);
IMPORT void phase_4__basic__loops(void);
IMPORT void phase_5__basic__loops(void);
IMPORT void phase_6__basic__loops(void);
IMPORT void run__basic__loops(void);
IMPORT void collect__basic__math(void);
IMPORT void phase_1__basic__math(void);
IMPORT void phase_2__basic__math(void);
IMPORT void phase_3__basic__math(void);
IMPORT void phase_4__basic__math(void);
IMPORT void phase_5__basic__math(void);
IMPORT void phase_6__basic__math(void);
IMPORT void run__basic__math(void);
IMPORT void collect__basic__options(void);
IMPORT void phase_1__basic__options(void);
IMPORT void phase_2__basic__options(void);
IMPORT void phase_3__basic__options(void);
IMPORT void phase_4__basic__options(void);
IMPORT void phase_5__basic__options(void);
IMPORT void phase_6__basic__options(void);
IMPORT void run__basic__options(void);
IMPORT void collect__basic__parameters(void);
IMPORT void phase_1__basic__parameters(void);
IMPORT void phase_2__basic__parameters(void);
IMPORT void phase_3__basic__parameters(void);
IMPORT void phase_4__basic__parameters(void);
IMPORT void phase_5__basic__parameters(void);
IMPORT void phase_6__basic__parameters(void);
IMPORT void run__basic__parameters(void);
IMPORT void collect__basic__platform(void);
IMPORT void phase_1__basic__platform(void);
IMPORT void phase_2__basic__platform(void);
IMPORT void phase_3__basic__platform(void);
IMPORT void phase_4__basic__platform(void);
IMPORT void phase_5__basic__platform(void);
IMPORT void phase_6__basic__platform(void);
IMPORT void run__basic__platform(void);
IMPORT void collect__basic__polymorphic_functions(void);
IMPORT void phase_1__basic__polymorphic_functions(void);
IMPORT void phase_2__basic__polymorphic_functions(void);
IMPORT void phase_3__basic__polymorphic_functions(void);
IMPORT void phase_4__basic__polymorphic_functions(void);
IMPORT void phase_5__basic__polymorphic_functions(void);
IMPORT void phase_6__basic__polymorphic_functions(void);
IMPORT void run__basic__polymorphic_functions(void);
IMPORT void collect__basic__primitives(void);
IMPORT void phase_1__basic__primitives(void);
IMPORT void phase_2__basic__primitives(void);
IMPORT void phase_3__basic__primitives(void);
IMPORT void phase_4__basic__primitives(void);
IMPORT void phase_5__basic__primitives(void);
IMPORT void phase_6__basic__primitives(void);
IMPORT void run__basic__primitives(void);
IMPORT void collect__basic__runtime(void);
IMPORT void phase_1__basic__runtime(void);
IMPORT void phase_2__basic__runtime(void);
IMPORT void phase_3__basic__runtime(void);
IMPORT void phase_4__basic__runtime(void);
IMPORT void phase_5__basic__runtime(void);
IMPORT void phase_6__basic__runtime(void);
IMPORT void run__basic__runtime(void);
IMPORT void collect__basic__types__boolean(void);
IMPORT void phase_1__basic__types__boolean(void);
IMPORT void phase_2__basic__types__boolean(void);
IMPORT void phase_3__basic__types__boolean(void);
IMPORT void phase_4__basic__types__boolean(void);
IMPORT void phase_5__basic__types__boolean(void);
IMPORT void phase_6__basic__types__boolean(void);
IMPORT void run__basic__types__boolean(void);
IMPORT void collect__basic__types__character(void);
IMPORT void phase_1__basic__types__character(void);
IMPORT void phase_2__basic__types__character(void);
IMPORT void phase_3__basic__types__character(void);
IMPORT void phase_4__basic__types__character(void);
IMPORT void phase_5__basic__types__character(void);
IMPORT void phase_6__basic__types__character(void);
IMPORT void run__basic__types__character(void);
IMPORT void collect__basic__types__continuation(void);
IMPORT void phase_1__basic__types__continuation(void);
IMPORT void phase_2__basic__types__continuation(void);
IMPORT void phase_3__basic__types__continuation(void);
IMPORT void phase_4__basic__types__continuation(void);
IMPORT void phase_5__basic__types__continuation(void);
IMPORT void phase_6__basic__types__continuation(void);
IMPORT void run__basic__types__continuation(void);
IMPORT void collect__basic__types__date_and_time(void);
IMPORT void phase_1__basic__types__date_and_time(void);
IMPORT void phase_2__basic__types__date_and_time(void);
IMPORT void phase_3__basic__types__date_and_time(void);
IMPORT void phase_4__basic__types__date_and_time(void);
IMPORT void phase_5__basic__types__date_and_time(void);
IMPORT void phase_6__basic__types__date_and_time(void);
IMPORT void run__basic__types__date_and_time(void);
IMPORT void collect__basic__types__function(void);
IMPORT void phase_1__basic__types__function(void);
IMPORT void phase_2__basic__types__function(void);
IMPORT void phase_3__basic__types__function(void);
IMPORT void phase_4__basic__types__function(void);
IMPORT void phase_5__basic__types__function(void);
IMPORT void phase_6__basic__types__function(void);
IMPORT void run__basic__types__function(void);
IMPORT void collect__basic__types__insert_order_set(void);
IMPORT void phase_1__basic__types__insert_order_set(void);
IMPORT void phase_2__basic__types__insert_order_set(void);
IMPORT void phase_3__basic__types__insert_order_set(void);
IMPORT void phase_4__basic__types__insert_order_set(void);
IMPORT void phase_5__basic__types__insert_order_set(void);
IMPORT void phase_6__basic__types__insert_order_set(void);
IMPORT void run__basic__types__insert_order_set(void);
IMPORT void collect__basic__types__insert_order_table(void);
IMPORT void phase_1__basic__types__insert_order_table(void);
IMPORT void phase_2__basic__types__insert_order_table(void);
IMPORT void phase_3__basic__types__insert_order_table(void);
IMPORT void phase_4__basic__types__insert_order_table(void);
IMPORT void phase_5__basic__types__insert_order_table(void);
IMPORT void phase_6__basic__types__insert_order_table(void);
IMPORT void run__basic__types__insert_order_table(void);
IMPORT void collect__basic__types__list(void);
IMPORT void phase_1__basic__types__list(void);
IMPORT void phase_2__basic__types__list(void);
IMPORT void phase_3__basic__types__list(void);
IMPORT void phase_4__basic__types__list(void);
IMPORT void phase_5__basic__types__list(void);
IMPORT void phase_6__basic__types__list(void);
IMPORT void run__basic__types__list(void);
IMPORT void collect__basic__types__multi_dimensional_set(void);
IMPORT void phase_1__basic__types__multi_dimensional_set(void);
IMPORT void phase_2__basic__types__multi_dimensional_set(void);
IMPORT void phase_3__basic__types__multi_dimensional_set(void);
IMPORT void phase_4__basic__types__multi_dimensional_set(void);
IMPORT void phase_5__basic__types__multi_dimensional_set(void);
IMPORT void phase_6__basic__types__multi_dimensional_set(void);
IMPORT void run__basic__types__multi_dimensional_set(void);
IMPORT void collect__basic__types__multi_dimensional_table(void);
IMPORT void phase_1__basic__types__multi_dimensional_table(void);
IMPORT void phase_2__basic__types__multi_dimensional_table(void);
IMPORT void phase_3__basic__types__multi_dimensional_table(void);
IMPORT void phase_4__basic__types__multi_dimensional_table(void);
IMPORT void phase_5__basic__types__multi_dimensional_table(void);
IMPORT void phase_6__basic__types__multi_dimensional_table(void);
IMPORT void run__basic__types__multi_dimensional_table(void);
IMPORT void collect__basic__types__number(void);
IMPORT void phase_1__basic__types__number(void);
IMPORT void phase_2__basic__types__number(void);
IMPORT void phase_3__basic__types__number(void);
IMPORT void phase_4__basic__types__number(void);
IMPORT void phase_5__basic__types__number(void);
IMPORT void phase_6__basic__types__number(void);
IMPORT void run__basic__types__number(void);
IMPORT void collect__basic__types__object(void);
IMPORT void phase_1__basic__types__object(void);
IMPORT void phase_2__basic__types__object(void);
IMPORT void phase_3__basic__types__object(void);
IMPORT void phase_4__basic__types__object(void);
IMPORT void phase_5__basic__types__object(void);
IMPORT void phase_6__basic__types__object(void);
IMPORT void run__basic__types__object(void);
IMPORT void collect__basic__types__key_order_table(void);
IMPORT void phase_1__basic__types__key_order_table(void);
IMPORT void phase_2__basic__types__key_order_table(void);
IMPORT void phase_3__basic__types__key_order_table(void);
IMPORT void phase_4__basic__types__key_order_table(void);
IMPORT void phase_5__basic__types__key_order_table(void);
IMPORT void phase_6__basic__types__key_order_table(void);
IMPORT void run__basic__types__key_order_table(void);
IMPORT void collect__basic__types__key_value_pair(void);
IMPORT void phase_1__basic__types__key_value_pair(void);
IMPORT void phase_2__basic__types__key_value_pair(void);
IMPORT void phase_3__basic__types__key_value_pair(void);
IMPORT void phase_4__basic__types__key_value_pair(void);
IMPORT void phase_5__basic__types__key_value_pair(void);
IMPORT void phase_6__basic__types__key_value_pair(void);
IMPORT void run__basic__types__key_value_pair(void);
IMPORT void collect__basic__types__set(void);
IMPORT void phase_1__basic__types__set(void);
IMPORT void phase_2__basic__types__set(void);
IMPORT void phase_3__basic__types__set(void);
IMPORT void phase_4__basic__types__set(void);
IMPORT void phase_5__basic__types__set(void);
IMPORT void phase_6__basic__types__set(void);
IMPORT void run__basic__types__set(void);
IMPORT void collect__basic__types__key_order_set(void);
IMPORT void phase_1__basic__types__key_order_set(void);
IMPORT void phase_2__basic__types__key_order_set(void);
IMPORT void phase_3__basic__types__key_order_set(void);
IMPORT void phase_4__basic__types__key_order_set(void);
IMPORT void phase_5__basic__types__key_order_set(void);
IMPORT void phase_6__basic__types__key_order_set(void);
IMPORT void run__basic__types__key_order_set(void);
IMPORT void collect__basic__types__string_primitives(void);
IMPORT void phase_1__basic__types__string_primitives(void);
IMPORT void phase_2__basic__types__string_primitives(void);
IMPORT void phase_3__basic__types__string_primitives(void);
IMPORT void phase_4__basic__types__string_primitives(void);
IMPORT void phase_5__basic__types__string_primitives(void);
IMPORT void phase_6__basic__types__string_primitives(void);
IMPORT void run__basic__types__string_primitives(void);
IMPORT void collect__basic__types__string(void);
IMPORT void phase_1__basic__types__string(void);
IMPORT void phase_2__basic__types__string(void);
IMPORT void phase_3__basic__types__string(void);
IMPORT void phase_4__basic__types__string(void);
IMPORT void phase_5__basic__types__string(void);
IMPORT void phase_6__basic__types__string(void);
IMPORT void run__basic__types__string(void);
IMPORT void collect__basic__types__table(void);
IMPORT void phase_1__basic__types__table(void);
IMPORT void phase_2__basic__types__table(void);
IMPORT void phase_3__basic__types__table(void);
IMPORT void phase_4__basic__types__table(void);
IMPORT void phase_5__basic__types__table(void);
IMPORT void phase_6__basic__types__table(void);
IMPORT void run__basic__types__table(void);
IMPORT void collect__basic__types__undefined(void);
IMPORT void phase_1__basic__types__undefined(void);
IMPORT void phase_2__basic__types__undefined(void);
IMPORT void phase_3__basic__types__undefined(void);
IMPORT void phase_4__basic__types__undefined(void);
IMPORT void phase_5__basic__types__undefined(void);
IMPORT void phase_6__basic__types__undefined(void);
IMPORT void run__basic__types__undefined(void);
IMPORT void collect__basic__types__unique_item(void);
IMPORT void phase_1__basic__types__unique_item(void);
IMPORT void phase_2__basic__types__unique_item(void);
IMPORT void phase_3__basic__types__unique_item(void);
IMPORT void phase_4__basic__types__unique_item(void);
IMPORT void phase_5__basic__types__unique_item(void);
IMPORT void phase_6__basic__types__unique_item(void);
IMPORT void run__basic__types__unique_item(void);
IMPORT void collect__basic__types__unordered_set(void);
IMPORT void phase_1__basic__types__unordered_set(void);
IMPORT void phase_2__basic__types__unordered_set(void);
IMPORT void phase_3__basic__types__unordered_set(void);
IMPORT void phase_4__basic__types__unordered_set(void);
IMPORT void phase_5__basic__types__unordered_set(void);
IMPORT void phase_6__basic__types__unordered_set(void);
IMPORT void run__basic__types__unordered_set(void);
IMPORT void collect__basic__types__unordered_table(void);
IMPORT void phase_1__basic__types__unordered_table(void);
IMPORT void phase_2__basic__types__unordered_table(void);
IMPORT void phase_3__basic__types__unordered_table(void);
IMPORT void phase_4__basic__types__unordered_table(void);
IMPORT void phase_5__basic__types__unordered_table(void);
IMPORT void phase_6__basic__types__unordered_table(void);
IMPORT void run__basic__types__unordered_table(void);
IMPORT void collect__basic__types__value_range(void);
IMPORT void phase_1__basic__types__value_range(void);
IMPORT void phase_2__basic__types__value_range(void);
IMPORT void phase_3__basic__types__value_range(void);
IMPORT void phase_4__basic__types__value_range(void);
IMPORT void phase_5__basic__types__value_range(void);
IMPORT void phase_6__basic__types__value_range(void);
IMPORT void run__basic__types__value_range(void);
IMPORT void collect__system__export__html(void);
IMPORT void phase_1__system__export__html(void);
IMPORT void phase_2__system__export__html(void);
IMPORT void phase_3__system__export__html(void);
IMPORT void phase_4__system__export__html(void);
IMPORT void phase_5__system__export__html(void);
IMPORT void phase_6__system__export__html(void);
IMPORT void run__system__export__html(void);
IMPORT void collect__character_names(void);
IMPORT void phase_1__character_names(void);
IMPORT void phase_2__character_names(void);
IMPORT void phase_3__character_names(void);
IMPORT void phase_4__character_names(void);
IMPORT void phase_5__character_names(void);
IMPORT void phase_6__character_names(void);
IMPORT void run__character_names(void);
IMPORT void collect__fragments(void);
IMPORT void phase_1__fragments(void);
IMPORT void phase_2__fragments(void);
IMPORT void phase_3__fragments(void);
IMPORT void phase_4__fragments(void);
IMPORT void phase_5__fragments(void);
IMPORT void phase_6__fragments(void);
IMPORT void run__fragments(void);
IMPORT void collect__tokenizer(void);
IMPORT void phase_1__tokenizer(void);
IMPORT void phase_2__tokenizer(void);
IMPORT void phase_3__tokenizer(void);
IMPORT void phase_4__tokenizer(void);
IMPORT void phase_5__tokenizer(void);
IMPORT void phase_6__tokenizer(void);
IMPORT void run__tokenizer(void);
IMPORT void collect__shared_variables(void);
IMPORT void phase_1__shared_variables(void);
IMPORT void phase_2__shared_variables(void);
IMPORT void phase_3__shared_variables(void);
IMPORT void phase_4__shared_variables(void);
IMPORT void phase_5__shared_variables(void);
IMPORT void phase_6__shared_variables(void);
IMPORT void run__shared_variables(void);
IMPORT void collect__nodes(void);
IMPORT void phase_1__nodes(void);
IMPORT void phase_2__nodes(void);
IMPORT void phase_3__nodes(void);
IMPORT void phase_4__nodes(void);
IMPORT void phase_5__nodes(void);
IMPORT void phase_6__nodes(void);
IMPORT void run__nodes(void);
IMPORT void collect__parser(void);
IMPORT void phase_1__parser(void);
IMPORT void phase_2__parser(void);
IMPORT void phase_3__parser(void);
IMPORT void phase_4__parser(void);
IMPORT void phase_5__parser(void);
IMPORT void phase_6__parser(void);
IMPORT void run__parser(void);
IMPORT void collect__expander(void);
IMPORT void phase_1__expander(void);
IMPORT void phase_2__expander(void);
IMPORT void phase_3__expander(void);
IMPORT void phase_4__expander(void);
IMPORT void phase_5__expander(void);
IMPORT void phase_6__expander(void);
IMPORT void run__expander(void);
IMPORT void collect__annotator(void);
IMPORT void phase_1__annotator(void);
IMPORT void phase_2__annotator(void);
IMPORT void phase_3__annotator(void);
IMPORT void phase_4__annotator(void);
IMPORT void phase_5__annotator(void);
IMPORT void phase_6__annotator(void);
IMPORT void run__annotator(void);
IMPORT void collect__simplifier(void);
IMPORT void phase_1__simplifier(void);
IMPORT void phase_2__simplifier(void);
IMPORT void phase_3__simplifier(void);
IMPORT void phase_4__simplifier(void);
IMPORT void phase_5__simplifier(void);
IMPORT void phase_6__simplifier(void);
IMPORT void run__simplifier(void);
IMPORT void collect__macros(void);
IMPORT void phase_1__macros(void);
IMPORT void phase_2__macros(void);
IMPORT void phase_3__macros(void);
IMPORT void phase_4__macros(void);
IMPORT void phase_5__macros(void);
IMPORT void phase_6__macros(void);
IMPORT void run__macros(void);
IMPORT void collect__c_code_generator(void);
IMPORT void phase_1__c_code_generator(void);
IMPORT void phase_2__c_code_generator(void);
IMPORT void phase_3__c_code_generator(void);
IMPORT void phase_4__c_code_generator(void);
IMPORT void phase_5__c_code_generator(void);
IMPORT void phase_6__c_code_generator(void);
IMPORT void run__c_code_generator(void);
IMPORT void collect__pretty_printer(void);
IMPORT void phase_1__pretty_printer(void);
IMPORT void phase_2__pretty_printer(void);
IMPORT void phase_3__pretty_printer(void);
IMPORT void phase_4__pretty_printer(void);
IMPORT void phase_5__pretty_printer(void);
IMPORT void phase_6__pretty_printer(void);
IMPORT void run__pretty_printer(void);
IMPORT void collect__sim2c(void);
IMPORT void phase_1__sim2c(void);
IMPORT void phase_2__sim2c(void);
IMPORT void phase_3__sim2c(void);
IMPORT void phase_4__sim2c(void);
IMPORT void phase_5__sim2c(void);
IMPORT void phase_6__sim2c(void);
IMPORT void run__sim2c(void);
IMPORT void collect__extractor(void);
IMPORT void phase_1__extractor(void);
IMPORT void phase_2__extractor(void);
IMPORT void phase_3__extractor(void);
IMPORT void phase_4__extractor(void);
IMPORT void phase_5__extractor(void);
IMPORT void phase_6__extractor(void);
IMPORT void run__extractor(void);
IMPORT void collect__runtime_definitions(void);
IMPORT void phase_1__runtime_definitions(void);
IMPORT void phase_2__runtime_definitions(void);
IMPORT void phase_3__runtime_definitions(void);
IMPORT void phase_4__runtime_definitions(void);
IMPORT void phase_5__runtime_definitions(void);
IMPORT void phase_6__runtime_definitions(void);
IMPORT void run__runtime_definitions(void);
static void main_entry(void) {
  allocate_initialized_frame_gc(0, 8);
  // 7: ...  basic/exceptions>
  func = run__basic__exceptions;
  frame->cont = cont__run__basic__exceptions;
}
static void cont__run__basic__exceptions(void) {
  // 8: ...  basic/serialize>
  func = run__basic__serialize;
  frame->cont = cont__run__basic__serialize;
}
static void cont__run__basic__serialize(void) {
  // 9: ...  basic/deserialize>
  func = run__basic__deserialize;
  frame->cont = cont__run__basic__deserialize;
}
static void cont__run__basic__deserialize(void) {
  // 10: ...  basic/branches>
  func = run__basic__branches;
  frame->cont = cont__run__basic__branches;
}
static void cont__run__basic__branches(void) {
  // 11: ...  basic/debug>
  func = run__basic__debug;
  frame->cont = cont__run__basic__debug;
}
static void cont__run__basic__debug(void) {
  // 12: ...  basic/environment>
  func = run__basic__environment;
  frame->cont = cont__run__basic__environment;
}
static void cont__run__basic__environment(void) {
  // 13: ...  basic/event>
  func = run__basic__event;
  frame->cont = cont__run__basic__event;
}
static void cont__run__basic__event(void) {
  // 14: ...  basic/exec>
  func = run__basic__exec;
  frame->cont = cont__run__basic__exec;
}
static void cont__run__basic__exec(void) {
  // 15: ...  basic/functional>
  func = run__basic__functional;
  frame->cont = cont__run__basic__functional;
}
static void cont__run__basic__functional(void) {
  // 16: ...  basic/grammar>
  func = run__basic__grammar;
  frame->cont = cont__run__basic__grammar;
}
static void cont__run__basic__grammar(void) {
  // 17: ...  basic/io>
  func = run__basic__io;
  frame->cont = cont__run__basic__io;
}
static void cont__run__basic__io(void) {
  // 18: ...  basic/loops>
  func = run__basic__loops;
  frame->cont = cont__run__basic__loops;
}
static void cont__run__basic__loops(void) {
  // 19: ...  basic/math>
  func = run__basic__math;
  frame->cont = cont__run__basic__math;
}
static void cont__run__basic__math(void) {
  // 20: ...  basic/options>
  func = run__basic__options;
  frame->cont = cont__run__basic__options;
}
static void cont__run__basic__options(void) {
  // 21: ...  basic/parameters>
  func = run__basic__parameters;
  frame->cont = cont__run__basic__parameters;
}
static void cont__run__basic__parameters(void) {
  // 22: ...  basic/platform>
  func = run__basic__platform;
  frame->cont = cont__run__basic__platform;
}
static void cont__run__basic__platform(void) {
  // 23: ...  basic/polymorphic_functions>
  func = run__basic__polymorphic_functions;
  frame->cont = cont__run__basic__polymorphic_functions;
}
static void cont__run__basic__polymorphic_functions(void) {
  // 24: ...  basic/primitives>
  func = run__basic__primitives;
  frame->cont = cont__run__basic__primitives;
}
static void cont__run__basic__primitives(void) {
  // 25: ...  basic/runtime>
  func = run__basic__runtime;
  frame->cont = cont__run__basic__runtime;
}
static void cont__run__basic__runtime(void) {
  // 26: ...  basic/types/boolean>
  func = run__basic__types__boolean;
  frame->cont = cont__run__basic__types__boolean;
}
static void cont__run__basic__types__boolean(void) {
  // 27: ...  basic/types/character>
  func = run__basic__types__character;
  frame->cont = cont__run__basic__types__character;
}
static void cont__run__basic__types__character(void) {
  // 28: ...  basic/types/continuation>
  func = run__basic__types__continuation;
  frame->cont = cont__run__basic__types__continuation;
}
static void cont__run__basic__types__continuation(void) {
  // 29: ...  basic/types/date_and_time>
  func = run__basic__types__date_and_time;
  frame->cont = cont__run__basic__types__date_and_time;
}
static void cont__run__basic__types__date_and_time(void) {
  // 30: ...  basic/types/function>
  func = run__basic__types__function;
  frame->cont = cont__run__basic__types__function;
}
static void cont__run__basic__types__function(void) {
  // 31: ...  basic/types/insert_order_set>
  func = run__basic__types__insert_order_set;
  frame->cont = cont__run__basic__types__insert_order_set;
}
static void cont__run__basic__types__insert_order_set(void) {
  // 32: ...  basic/types/insert_order_table>
  func = run__basic__types__insert_order_table;
  frame->cont = cont__run__basic__types__insert_order_table;
}
static void cont__run__basic__types__insert_order_table(void) {
  // 33: ...  basic/types/list>
  func = run__basic__types__list;
  frame->cont = cont__run__basic__types__list;
}
static void cont__run__basic__types__list(void) {
  // 34: ...  basic/types/multi_dimensional_set>
  func = run__basic__types__multi_dimensional_set;
  frame->cont = cont__run__basic__types__multi_dimensional_set;
}
static void cont__run__basic__types__multi_dimensional_set(void) {
  // 35: ...  basic/types/multi_dimensional_table>
  func = run__basic__types__multi_dimensional_table;
  frame->cont = cont__run__basic__types__multi_dimensional_table;
}
static void cont__run__basic__types__multi_dimensional_table(void) {
  // 36: ...  basic/types/number>
  func = run__basic__types__number;
  frame->cont = cont__run__basic__types__number;
}
static void cont__run__basic__types__number(void) {
  // 37: ...  basic/types/object>
  func = run__basic__types__object;
  frame->cont = cont__run__basic__types__object;
}
static void cont__run__basic__types__object(void) {
  // 38: ...  basic/types/key_order_table>
  func = run__basic__types__key_order_table;
  frame->cont = cont__run__basic__types__key_order_table;
}
static void cont__run__basic__types__key_order_table(void) {
  // 39: ...  basic/types/key_value_pair>
  func = run__basic__types__key_value_pair;
  frame->cont = cont__run__basic__types__key_value_pair;
}
static void cont__run__basic__types__key_value_pair(void) {
  // 40: ...  basic/types/set>
  func = run__basic__types__set;
  frame->cont = cont__run__basic__types__set;
}
static void cont__run__basic__types__set(void) {
  // 41: ...  basic/types/key_order_set>
  func = run__basic__types__key_order_set;
  frame->cont = cont__run__basic__types__key_order_set;
}
static void cont__run__basic__types__key_order_set(void) {
  // 42: ...  basic/types/string_primitives>
  func = run__basic__types__string_primitives;
  frame->cont = cont__run__basic__types__string_primitives;
}
static void cont__run__basic__types__string_primitives(void) {
  // 43: ...  basic/types/string>
  func = run__basic__types__string;
  frame->cont = cont__run__basic__types__string;
}
static void cont__run__basic__types__string(void) {
  // 44: ...  basic/types/table>
  func = run__basic__types__table;
  frame->cont = cont__run__basic__types__table;
}
static void cont__run__basic__types__table(void) {
  // 45: ...  basic/types/undefined>
  func = run__basic__types__undefined;
  frame->cont = cont__run__basic__types__undefined;
}
static void cont__run__basic__types__undefined(void) {
  // 46: ...  basic/types/unique_item>
  func = run__basic__types__unique_item;
  frame->cont = cont__run__basic__types__unique_item;
}
static void cont__run__basic__types__unique_item(void) {
  // 47: ...  basic/types/unordered_set>
  func = run__basic__types__unordered_set;
  frame->cont = cont__run__basic__types__unordered_set;
}
static void cont__run__basic__types__unordered_set(void) {
  // 48: ...  basic/types/unordered_table>
  func = run__basic__types__unordered_table;
  frame->cont = cont__run__basic__types__unordered_table;
}
static void cont__run__basic__types__unordered_table(void) {
  // 49: ...  basic/types/value_range>
  func = run__basic__types__value_range;
  frame->cont = cont__run__basic__types__value_range;
}
static void cont__run__basic__types__value_range(void) {
  // 50: ...  system/export/html>
  func = run__system__export__html;
  frame->cont = cont__run__system__export__html;
}
static void cont__run__system__export__html(void) {
  // 51: ...  ./character_names>
  func = run__character_names;
  frame->cont = cont__run__character_names;
}
static void cont__run__character_names(void) {
  // 52: ...  ./fragments>
  func = run__fragments;
  frame->cont = cont__run__fragments;
}
static void cont__run__fragments(void) {
  // 53: ...  ./tokenizer>
  func = run__tokenizer;
  frame->cont = cont__run__tokenizer;
}
static void cont__run__tokenizer(void) {
  // 54: ...  ./shared_variables>
  func = run__shared_variables;
  frame->cont = cont__run__shared_variables;
}
static void cont__run__shared_variables(void) {
  // 55: ...  ./nodes>
  func = run__nodes;
  frame->cont = cont__run__nodes;
}
static void cont__run__nodes(void) {
  // 56: ...  ./parser>
  func = run__parser;
  frame->cont = cont__run__parser;
}
static void cont__run__parser(void) {
  // 57: ...  ./expander>
  func = run__expander;
  frame->cont = cont__run__expander;
}
static void cont__run__expander(void) {
  // 58: ...  ./annotator>
  func = run__annotator;
  frame->cont = cont__run__annotator;
}
static void cont__run__annotator(void) {
  // 59: ...  ./simplifier>
  func = run__simplifier;
  frame->cont = cont__run__simplifier;
}
static void cont__run__simplifier(void) {
  // 60: ...  ./macros>
  func = run__macros;
  frame->cont = cont__run__macros;
}
static void cont__run__macros(void) {
  // 61: ...  ./c_code_generator>
  func = run__c_code_generator;
  frame->cont = cont__run__c_code_generator;
}
static void cont__run__c_code_generator(void) {
  // 62: ...  ./pretty_printer>
  func = run__pretty_printer;
  frame->cont = cont__run__pretty_printer;
}
static void cont__run__pretty_printer(void) {
  // 63: ...  ./sim2c>
  func = run__sim2c;
  frame->cont = cont__run__sim2c;
}
static void cont__run__sim2c(void) {
  // 64: ...  ./extractor>
  func = run__extractor;
  frame->cont = cont__run__extractor;
}
static void cont__run__extractor(void) {
  // 65: ...  ./runtime_definitions>
  func = run__runtime_definitions;
  frame->cont = cont__run__runtime_definitions;
}
static void cont__run__runtime_definitions(void) {
  // 71: copyright "
  // 72:   Copyright (C) 2020 by
  // 73:   Dipl.-Ing. Michael Niederle
  // 74:   
  // 75:   This program is free software; you can redistribute it and/or modify
  // 76:   it under the terms of the GNU General Public License, version 2, or
  // 77:   (at your option) version 3.
  // 78:   
  // 79:   This program is distributed in the hope that it will be useful,
  // 80:   but WITHOUT ANY WARRANTY; without even the implied warranty of
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__93_1;
  result_count = 0;
  myself = get__copyright();
  func = myself->type;
  frame->cont = cont__93_2;
}
static void cont__93_2(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 91: $MAJOR runtime_major_version()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__runtime_major_version();
  func = myself->type;
  frame->cont = cont__94_1;
}
static void cont__94_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._MAJOR, arguments->slots[0]);
  // 92: $MINOR runtime_minor_version()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__runtime_minor_version();
  func = myself->type;
  frame->cont = cont__95_1;
}
static void cont__95_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._MINOR, arguments->slots[0]);
  // 93: $REVISION runtime_revision()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__runtime_revision();
  func = myself->type;
  frame->cont = cont__96_1;
}
static void cont__96_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._REVISION, arguments->slots[0]);
  // 95: $VERSION "@(MAJOR).@(MINOR).@(REVISION).@(BUILD)"
  argument_count = 7;
  arguments = node_p;
  arguments->slots[0] = var._MAJOR;
  arguments->slots[1] = string__98_1;
  arguments->slots[2] = var._MINOR;
  arguments->slots[3] = string__98_1;
  arguments->slots[4] = var._REVISION;
  arguments->slots[5] = string__98_1;
  arguments->slots[6] = var._BUILD;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__98_2;
}
static void cont__98_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._VERSION, arguments->slots[0]);
  // 96: version VERSION
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._VERSION;
  result_count = 0;
  myself = get__version();
  func = myself->type;
  frame->cont = cont__99_1;
}
static void cont__99_1(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 97: ... c_compiler()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__c_compiler();
  func = myself->type;
  frame->cont = cont__100_1;
}
static void cont__100_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 97: extern $cc c_compiler()
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__extern();
  func = myself->type;
  frame->cont = cont__100_2;
}
static void cont__100_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._cc, arguments->slots[0]);
  // 98: extern $mkdir "mkdir" # would be nice to have one in the system library!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__101_1;
  result_count = 1;
  myself = get__extern();
  func = myself->type;
  frame->cont = cont__101_2;
}
static void cont__101_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._mkdir, arguments->slots[0]);
  // 99: $SIMLIBPATH environment("SIMLIBPATH")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__102_1;
  result_count = 1;
  myself = get__environment();
  func = myself->type;
  frame->cont = cont__102_2;
}
static void cont__102_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._SIMLIBPATH, arguments->slots[0]);
  // 100: $SIMDATAPATH environment("SIMDATAPATH")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__103_1;
  result_count = 1;
  myself = get__environment();
  func = myself->type;
  frame->cont = cont__103_2;
}
static void cont__103_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._SIMDATAPATH, arguments->slots[0]);
  // 104: SIMLIBPATH.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._SIMLIBPATH;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__104_1;
}
static void cont__104_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 102: $simlibpaths
  // 103:   if
  // 104:     SIMLIBPATH.is_defined
  // 105:     -> split(SIMLIBPATH ':')
  // 106:     ->
  // 107:       list
  // 108:         "/usr/local/share/simplicity-@(VERSION)"
  // 109:         "/usr/share/simplicity-@(VERSION)"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__104_2;
  arguments->slots[2] = func__104_4;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__104_10;
}
static void entry__104_2(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 105: ... split(SIMLIBPATH ':')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._SIMLIBPATH;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__split();
  func = myself->type;
  frame->cont = cont__104_3;
}
static void cont__104_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 105: -> split(SIMLIBPATH ':')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__104_4(void) {
  allocate_initialized_frame_gc(0, 3);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 108: "/usr/local/share/simplicity-@(VERSION)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__104_5;
  arguments->slots[1] = var._VERSION;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__104_6;
}
static void cont__104_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 109: "/usr/share/simplicity-@(VERSION)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__104_7;
  arguments->slots[1] = var._VERSION;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__104_8;
}
static void cont__104_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 107: list
  // 108:   "/usr/local/share/simplicity-@(VERSION)"
  // 109:   "/usr/share/simplicity-@(VERSION)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  arguments->slots[1] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__104_9;
}
static void cont__104_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 106: ->
  // 107:   list
  // 108:     "/usr/local/share/simplicity-@(VERSION)"
  // 109:     "/usr/share/simplicity-@(VERSION)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__104_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._simlibpaths, arguments->slots[0]);
  // 113: SIMDATAPATH.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._SIMDATAPATH;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__105_1;
}
static void cont__105_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 111: $simdatapaths
  // 112:   if
  // 113:     SIMDATAPATH.is_defined
  // 114:     -> split(SIMDATAPATH ':')
  // 115:     ->
  // 116:       list
  // 117:         "/usr/local/share/simplicity-@(VERSION)"
  // 118:         "/usr/share/simplicity-@(VERSION)"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__105_2;
  arguments->slots[2] = func__105_4;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__105_8;
}
static void entry__105_2(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 114: ... split(SIMDATAPATH ':')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._SIMDATAPATH;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__split();
  func = myself->type;
  frame->cont = cont__105_3;
}
static void cont__105_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 114: -> split(SIMDATAPATH ':')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__105_4(void) {
  allocate_initialized_frame_gc(0, 3);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 117: "/usr/local/share/simplicity-@(VERSION)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__104_5;
  arguments->slots[1] = var._VERSION;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__105_5;
}
static void cont__105_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 118: "/usr/share/simplicity-@(VERSION)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__104_7;
  arguments->slots[1] = var._VERSION;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__105_6;
}
static void cont__105_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 116: list
  // 117:   "/usr/local/share/simplicity-@(VERSION)"
  // 118:   "/usr/share/simplicity-@(VERSION)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  arguments->slots[1] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__105_7;
}
static void cont__105_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 115: ->
  // 116:   list
  // 117:     "/usr/local/share/simplicity-@(VERSION)"
  // 118:     "/usr/share/simplicity-@(VERSION)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__105_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._simdatapaths, arguments->slots[0]);
  // 124: "bsd" = "posix"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__84_59;
  arguments->slots[1] = string__107_1;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__107_2;
}
static void cont__107_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 125: "cygwin" = "posix"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__84_36;
  arguments->slots[1] = string__107_1;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__107_3;
}
static void cont__107_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 126: "darwin" = "posix"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__84_37;
  arguments->slots[1] = string__107_1;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__107_4;
}
static void cont__107_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 127: "linux" = "posix"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__77_23;
  arguments->slots[1] = string__107_1;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__107_5;
}
static void cont__107_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 128: "posix" = "all"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__107_1;
  arguments->slots[1] = string__107_6;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__107_7;
}
static void cont__107_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 129: "win" = "all"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__107_8;
  arguments->slots[1] = string__107_6;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__107_9;
}
static void cont__107_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 130: "all" = NONE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__107_6;
  arguments->slots[1] = var._NONE;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__107_10;
}
static void cont__107_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__7 */ = arguments->slots[0];
  // 122: $supported_platforms
  // 123:   key_order_table
  // 124:     "bsd" = "posix"
  // 125:     "cygwin" = "posix"
  // 126:     "darwin" = "posix"
  // 127:     "linux" = "posix"
  // 128:     "posix" = "all"
  // 129:     "win" = "all"
  // 130:     "all" = NONE
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
  myself = get__key_order_table();
  func = myself->type;
  frame->cont = cont__107_11;
}
static void cont__107_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._supported_platforms, arguments->slots[0]);
  // 132: $$platform_priority empty_table
  var._platform_priority = get__empty_table();
  // 133: do:
  // 134:   $$platform operating_system()
  // 135:   $$priority 0
  // 136:   do: (-> break)
  // 137:     forever:
  // 138:       $plat supported_platforms(platform)
  // 139:       if plat.is_undefined break
  // 140:       inc &priority
  // 141:       !platform_priority(platform) priority
  // 142:       if plat == NONE break
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__109_1;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__109_13;
}
static void entry__109_3(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // break: 0
  // platform: 1
  // priority: 2
  frame->slots[0] /* break */ = create_continuation();
  frame->slots[1] = myself->closure.frame->slots[0]; /* platform */
  frame->slots[2] = myself->closure.frame->slots[1]; /* priority */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 137: ... :
  // 138:   $plat supported_platforms(platform)
  // 139:   if plat.is_undefined break
  // 140:   inc &priority
  // 141:   !platform_priority(platform) priority
  // 142:   if plat == NONE break
  // 143:   !platform plat
  frame->slots[3] /* temp__1 */ = create_closure(entry__109_4, 0);
  // 137: forever:
  // 138:   $plat supported_platforms(platform)
  // 139:   if plat.is_undefined break
  // 140:   inc &priority
  // 141:   !platform_priority(platform) priority
  // 142:   if plat == NONE break
  // 143:   !platform plat
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame->cont = cont__109_12;
}
static void entry__109_4(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // platform: 0
  // break: 1
  // priority: 2
  // plat: 3
  frame->slots[0] = myself->closure.frame->slots[1]; /* platform */
  frame->slots[1] = myself->closure.frame->slots[0]; /* break */
  frame->slots[2] = myself->closure.frame->slots[2]; /* priority */
  frame->slots[3] /* plat */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 138: $plat supported_platforms(platform)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* platform */;
  result_count = 1;
  myself = var._supported_platforms;
  func = myself->type;
  frame->cont = cont__109_5;
}
static void cont__109_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* plat */, arguments->slots[0]);
  // 139: ... plat.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* plat */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__109_6;
}
static void cont__109_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 139: if plat.is_undefined break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* break */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__109_7;
}
static void cont__109_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 140: inc &priority
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* priority */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__109_8;
}
static void cont__109_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* priority */ = arguments->slots[0];
  // 141: !platform_priority(platform) priority
  frame->slots[4] /* temp__1 */ = ((CELL *)frame->slots[2])->contents /* priority */;
  // 141: !platform_priority(platform)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* platform */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = var._platform_priority;
  func = myself->type;
  frame->cont = cont__109_9;
}
static void cont__109_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._platform_priority = arguments->slots[0];
  // 142: ... plat == NONE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* plat */;
  arguments->slots[1] = var._NONE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__109_10;
}
static void cont__109_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 142: if plat == NONE break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* break */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__109_11;
}
static void cont__109_11(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 143: !platform plat
  ((CELL *)frame->slots[0])->contents /* platform */ = frame->slots[3] /* plat */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__109_12(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__109_1(void) {
  allocate_initialized_frame_gc(0, 3);
  // slot allocations:
  // platform: 0
  // priority: 1
  frame->slots[0] /* platform */ = create_cell();
  frame->slots[1] /* priority */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 134: $$platform operating_system()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__operating_system();
  func = myself->type;
  frame->cont = cont__109_2;
}
static void cont__109_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* platform */ = arguments->slots[0];
  // 135: $$priority 0
  ((CELL *)frame->slots[1])->contents /* priority */ = number__0;
  // 136: ... : (-> break)
  // 137:   forever:
  // 138:     $plat supported_platforms(platform)
  // 139:     if plat.is_undefined break
  // 140:     inc &priority
  // 141:     !platform_priority(platform) priority
  // 142:     if plat == NONE break
  // 143:     !platform plat
  frame->slots[2] /* temp__1 */ = create_closure(entry__109_3, 0);
  // 136: do: (-> break)
  // 137:   forever:
  // 138:     $plat supported_platforms(platform)
  // 139:     if plat.is_undefined break
  // 140:     inc &priority
  // 141:     !platform_priority(platform) priority
  // 142:     if plat == NONE break
  // 143:     !platform plat
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__do();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__109_13(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 144: $$platform_specific_priority undefined
  var._platform_specific_priority = get__undefined();
  // 145: $$module_info empty_table
  var._module_info = get__empty_table();
  // 146: $$meta_levels empty_table # 0 -> no meta files
  var._meta_levels = get__empty_table();
  // 147: $$do_rebuild false
  var._do_rebuild = get__false();
  // 148: $$do_omit_meta false
  var._do_omit_meta = get__false();
  // 149: $$sim2c::do_dump_trees false
  var.sim2c__do_dump_trees = get__false();
  // 150: $$sim2c::do_pretty_print false
  var.sim2c__do_pretty_print = get__false();
  // 151: $$sim2c::do_print_simplified_source false
  var.sim2c__do_print_simplified_source = get__false();
  // 152: $$sim2c::do_show_debug_infos false
  var.sim2c__do_show_debug_infos = get__false();
  // 153: $$sim2c::do_show_compiler_debug_infos false
  var.sim2c__do_show_compiler_debug_infos = get__false();
  // 154: $$sim2c::do_check_only false
  var.sim2c__do_check_only = get__false();
  // 155: $$sim2c::do_show_brief_messages false
  var.sim2c__do_show_brief_messages = get__false();
  // 156: $$sim2c::do_print_warnings false
  var.sim2c__do_print_warnings = get__false();
  // 157: $$sim2c::verbose false
  var.sim2c__verbose = get__false();
  // 158: $$do_print_c false
  var._do_print_c = get__false();
  // 159: $$sim2c::do_extract_documentation false
  var.sim2c__do_extract_documentation = get__false();
  // 160: $$do_build_codeblocks_project false
  var._do_build_codeblocks_project = get__false();
  // 161: $$do_list_dependencies false
  var._do_list_dependencies = get__false();
  // 162: $$do_build_static false
  var._do_build_static = get__false();
  // 163: $$do_link_profiler false
  var._do_link_profiler = get__false();
  // 164: $$sim2c::do_time_passes false
  var.sim2c__do_time_passes = get__false();
  // 165: $$module_prefix undefined
  var._module_prefix = get__undefined();
  // 166: $$input_filename undefined
  var._input_filename = get__undefined();
  // 167: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__133_1;
}
static void cont__133_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 167: $action truncate_until(program_name '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__program_name();
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__133_2;
}
static void cont__133_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._action, arguments->slots[0]);
  // 169: action == "simrun"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._action;
  arguments->slots[1] = string__84_2;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__134_1;
}
static void cont__134_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 168: if
  // 169:   action == "simrun":
  // 170:     if command_line_arguments.is_empty: Error "Missing command line arguments!"
  // 171:     !input_filename command_line_arguments(1)
  // 172:   :
  // 173:     program_parameters
  // 174:       # the following options act on a single file only
  // 175:       
  // 176:       !sim2c::do_check_only
  // 177:       -> "check-only" "
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__134_2;
  arguments->slots[2] = func__134_8;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__134_70;
}
static void entry__134_2(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 170: ... command_line_arguments.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__command_line_arguments();
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__134_3;
}
static void cont__134_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 170: if command_line_arguments.is_empty: Error "Missing command line arguments!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__134_4;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__134_6;
}
static void entry__134_4(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 170: ... Error "Missing command line arguments!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__134_5;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__134_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 171: !input_filename command_line_arguments(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__command_line_arguments();
  func = myself->type;
  frame->cont = cont__134_7;
}
static void cont__134_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._input_filename = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__134_8(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 173: program_parameters
  // 174:   # the following options act on a single file only
  // 175:   
  // 176:   !sim2c::do_check_only
  // 177:   -> "check-only" "
  // 178:     do not compile; just check for syntax errors
  // 179:   !sim2c::do_dump_trees
  // 180:   -> "dump-trees" "
  // 181:     dump abstract syntax trees
  // 182:   !sim2c::do_pretty_print
  // ...
  argument_count = 20;
  arguments = node_p;
  arguments->slots[0] = func__134_9;
  arguments->slots[1] = func__134_12;
  arguments->slots[2] = func__134_15;
  arguments->slots[3] = func__134_18;
  arguments->slots[4] = func__134_21;
  arguments->slots[5] = func__134_24;
  arguments->slots[6] = func__134_27;
  arguments->slots[7] = func__134_30;
  arguments->slots[8] = func__134_33;
  arguments->slots[9] = func__134_36;
  arguments->slots[10] = func__134_39;
  arguments->slots[11] = func__134_42;
  arguments->slots[12] = func__134_45;
  arguments->slots[13] = func__134_48;
  arguments->slots[14] = func__134_51;
  arguments->slots[15] = func__134_54;
  arguments->slots[16] = func__134_57;
  arguments->slots[17] = func__134_60;
  arguments->slots[18] = func__134_63;
  arguments->slots[19] = func__134_66;
  result_count = 20;
  myself = get__program_parameters();
  func = myself->type;
  frame->cont = cont__134_69;
}
static void entry__134_9(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 177: -> "check-only" "
  // 178:   do not compile; just check for syntax errors
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__134_10;
  arguments->slots[1] = string__134_11;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__134_12(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 180: -> "dump-trees" "
  // 181:   dump abstract syntax trees
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__134_13;
  arguments->slots[1] = string__134_14;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__134_15(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 183: -> "pretty-print" "
  // 184:   do not compile; just pretty print the source file
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__134_16;
  arguments->slots[1] = string__134_17;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__134_18(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 186: -> "print-simplified-source" "
  // 187:   do not generate a C-file; just print the simplified source text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__134_19;
  arguments->slots[1] = string__134_20;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__134_21(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 189: -> "print-c" "
  // 190:   print C source code for a single module
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__134_22;
  arguments->slots[1] = string__134_23;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__134_24(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 192: -> "time-passes" "
  // 193:   print running time for the individual compiler passes
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__134_25;
  arguments->slots[1] = string__134_26;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__134_27(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 195: -> VALUED_OPTION "module-prefix" "
  // 196:   needed to compile a single file within a subdirectory;
  // 197:   if the subdirectories are nested use slashes to separate
  // 198:   the directory names
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__VALUED_OPTION();
  arguments->slots[1] = string__134_28;
  arguments->slots[2] = string__134_29;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__134_30(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 202: -> "brief" "
  // 203:   show brief error messages
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__134_31;
  arguments->slots[1] = string__134_32;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__134_33(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 205: -> "warnings" "
  // 206:   show warning messages
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__134_34;
  arguments->slots[1] = string__134_35;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__134_36(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 208: -> "verbose" "
  // 209:   output verbose informations
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__134_37;
  arguments->slots[1] = string__134_38;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__134_39(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 211: -> "debug" "
  // 212:   show C-compiler and linker calls
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__134_40;
  arguments->slots[1] = string__134_41;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__134_42(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 214: -> "debug_compiler" "
  // 215:   show internal debug messages of the Simplicity compiler
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__134_43;
  arguments->slots[1] = string__134_44;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__134_45(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 219: -> "codeblocks" "
  // 220:   create Code::Blocks project
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__134_46;
  arguments->slots[1] = string__134_47;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__134_48(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 222: -> "extract-documentation" "
  // 223:   extract documentation encoded as HTML
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__134_49;
  arguments->slots[1] = string__134_50;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__134_51(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 225: -> "list-dependencies" "
  // 226:   list all dependencies
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__134_52;
  arguments->slots[1] = string__134_53;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__134_54(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 230: -> "rebuild" "
  // 231:   rebuild all source files
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__134_55;
  arguments->slots[1] = string__134_56;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__134_57(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 233: -> "omit-meta" "
  // 234:   do not rebuild meta files
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__134_58;
  arguments->slots[1] = string__134_59;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__134_60(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 236: -> "static" "
  // 237:   create statically linked executable
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__134_61;
  arguments->slots[1] = string__134_62;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__134_63(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 239: -> "profile" "
  // 240:   link with libprofiler
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__134_64;
  arguments->slots[1] = string__134_65;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__134_66(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 242: -> std::MANDATORY_PARAMETER "filename" "
  // 243:   the name of the source file to compile
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__std__MANDATORY_PARAMETER();
  arguments->slots[1] = string__134_67;
  arguments->slots[2] = string__134_68;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__134_69(void) {
  if (argument_count != 20) {
    invalid_results_error();
    return;
  }
  var.sim2c__do_check_only = arguments->slots[0];
  var.sim2c__do_dump_trees = arguments->slots[1];
  var.sim2c__do_pretty_print = arguments->slots[2];
  var.sim2c__do_print_simplified_source = arguments->slots[3];
  var._do_print_c = arguments->slots[4];
  set__do_time_passes(arguments->slots[5]);
  var._module_prefix = arguments->slots[6];
  var.sim2c__do_show_brief_messages = arguments->slots[7];
  var.sim2c__do_print_warnings = arguments->slots[8];
  var.sim2c__verbose = arguments->slots[9];
  var.sim2c__do_show_debug_infos = arguments->slots[10];
  var.sim2c__do_show_compiler_debug_infos = arguments->slots[11];
  var._do_build_codeblocks_project = arguments->slots[12];
  set__do_extract_documentation(arguments->slots[13]);
  var._do_list_dependencies = arguments->slots[14];
  var._do_rebuild = arguments->slots[15];
  var._do_omit_meta = arguments->slots[16];
  var._do_build_static = arguments->slots[17];
  var._do_link_profiler = arguments->slots[18];
  var._input_filename = arguments->slots[19];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__134_70(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 244: %main_filename fullname(input_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._input_filename;
  result_count = 1;
  myself = get__fullname();
  func = myself->type;
  frame->cont = cont__135_1;
}
static void cont__135_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(get__main_filename(), arguments->slots[0]);
  // 245: %main_info stat(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__136_1;
}
static void cont__136_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(get__main_info(), arguments->slots[0]);
  // 246: %do_build_static_executable do_build_static
  initialize_future(get__do_build_static_executable(), var._do_build_static);
  // 247: if do_show_debug_infos: !verbose true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_show_debug_infos();
  arguments->slots[1] = func__138_1;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__138_2;
}
static void entry__138_1(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 247: ... !verbose true
  set__verbose(get__true());
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__138_2(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 255: %mode undefined # EXE or LIB
  initialize_maybe_future(get__mode(), get__undefined());
  // 256: $WHITESPACE many(' ')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__32;
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__143_1;
}
static void cont__143_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._WHITESPACE, arguments->slots[0]);
  // 258: $cc_basic_options
  // 259:   list
  // 260:     "-Wall"
  // 261:     "-Wno-unused-function"
  // 262:     "-Wno-unused-variable"
  // 263:     "-Wno-parentheses"
  // 264:     "-Wno-switch"
  // 265:     "-Wno-trigraphs"
  // 266:     "-O1"
  // 267:     "-fPIC"
  // ...
  argument_count = 10;
  arguments = node_p;
  arguments->slots[0] = string__144_1;
  arguments->slots[1] = string__144_2;
  arguments->slots[2] = string__144_3;
  arguments->slots[3] = string__144_4;
  arguments->slots[4] = string__144_5;
  arguments->slots[5] = string__144_6;
  arguments->slots[6] = string__144_7;
  arguments->slots[7] = string__144_8;
  arguments->slots[8] = string__144_9;
  arguments->slots[9] = string__144_10;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__144_11;
}
static void cont__144_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._cc_basic_options, arguments->slots[0]);
  // 271: $gcc_options
  // 272:   list
  // 273:     "-Wno-maybe-uninitialized"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__145_1;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__145_2;
}
static void cont__145_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._gcc_options, arguments->slots[0]);
  // 281: ... list("-msse2" "-mfpmath=sse")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__146_1;
  arguments->slots[1] = string__146_2;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__146_3;
}
static void cont__146_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 281: "x86_32" = list("-msse2" "-mfpmath=sse")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__146_4;
  arguments->slots[1] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__146_5;
}
static void cont__146_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 282: ... list("-msse2" "-mfpmath=sse")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__146_1;
  arguments->slots[1] = string__146_2;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__146_6;
}
static void cont__146_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 282: "x86_64" = list("-msse2" "-mfpmath=sse")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__146_7;
  arguments->slots[1] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__146_8;
}
static void cont__146_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 279: $cc_hardware_specific_options
  // 280:   table
  // 281:     "x86_32" = list("-msse2" "-mfpmath=sse")
  // 282:     "x86_64" = list("-msse2" "-mfpmath=sse")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__table();
  func = myself->type;
  frame->cont = cont__146_9;
}
static void cont__146_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._cc_hardware_specific_options, arguments->slots[0]);
  // 284: $$cc_include_options empty_list
  var._cc_include_options = get__empty_list();
  // 285: for_each simdatapaths: (path)
  // 286:   push &cc_include_options "-I@(path)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._simdatapaths;
  arguments->slots[1] = func__148_1;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__148_5;
}
static void entry__148_1(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // path: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 286: ... "-I@(path)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__148_2;
  arguments->slots[1] = frame->slots[0] /* path */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__148_3;
}
static void cont__148_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 286: push &cc_include_options "-I@(path)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._cc_include_options;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__148_4;
}
static void cont__148_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._cc_include_options = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__148_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 293: ... hardware_architecture()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__hardware_architecture();
  func = myself->type;
  frame->cont = cont__149_1;
}
static void cont__149_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 293: cc_hardware_specific_options(hardware_architecture())
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = var._cc_hardware_specific_options;
  func = myself->type;
  frame->cont = cont__149_2;
}
static void cont__149_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 292: default_value
  // 293:   cc_hardware_specific_options(hardware_architecture())
  // 294:   empty_list
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__3 */;
  arguments->slots[1] = get__empty_list();
  result_count = 1;
  myself = get__default_value();
  func = myself->type;
  frame->cont = cont__149_3;
}
static void cont__149_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 297: c_compiler()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__c_compiler();
  func = myself->type;
  frame->cont = cont__149_4;
}
static void cont__149_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__8 */ = arguments->slots[0];
  // 297: c_compiler() == "gcc"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__8 */;
  arguments->slots[1] = string__149_5;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__149_6;
}
static void cont__149_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__7 */ = arguments->slots[0];
  // 296: if
  // 297:   c_compiler() == "gcc"
  // 298:   -> gcc_options
  // 299:   -> empty_list
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__7 */;
  arguments->slots[1] = func__149_7;
  arguments->slots[2] = func__149_8;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__149_9;
}
static void entry__149_7(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 298: -> gcc_options
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._gcc_options;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__149_8(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 299: -> empty_list
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__empty_list();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__149_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 295: append
  // 296:   if
  // 297:     c_compiler() == "gcc"
  // 298:     -> gcc_options
  // 299:     -> empty_list
  // 300:   cc_include_options
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__6 */;
  arguments->slots[1] = var._cc_include_options;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__149_10;
}
static void cont__149_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 291: append
  // 292:   default_value
  // 293:     cc_hardware_specific_options(hardware_architecture())
  // 294:     empty_list
  // 295:   append
  // 296:     if
  // 297:       c_compiler() == "gcc"
  // 298:       -> gcc_options
  // 299:       -> empty_list
  // 300:     cc_include_options
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__5 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__149_11;
}
static void cont__149_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 288: $cc_options
  // 289:   append
  // 290:     cc_basic_options
  // 291:     append
  // 292:       default_value
  // 293:         cc_hardware_specific_options(hardware_architecture())
  // 294:         empty_list
  // 295:       append
  // 296:         if
  // 297:           c_compiler() == "gcc"
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._cc_basic_options;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__149_12;
}
static void cont__149_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._cc_options, arguments->slots[0]);
  // 302: %on_top_level true # set to false while building meta-files
  initialize_maybe_future(get__on_top_level(), get__true());
  // 303: %%objects empty_insert_order_set
  set__objects(get__empty_insert_order_set());
  // 304: %%libraries empty_insert_order_set # contains "-lsim-..."-entries
  set__libraries(get__empty_insert_order_set());
  // 305: %%do_link false
  set__do_link(get__false());
  // 306: %%last_modification_time undefined
  set__last_modification_time(get__undefined());
  // 307: $$c_sources empty_insert_order_set
  var._c_sources = get__empty_insert_order_set();
  // 308: $$dependencies empty_list
  var._dependencies = get__empty_list();
  // 309: $$resolved_libraries undefined
  var._resolved_libraries = get__undefined();
  // 638: ... main_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_info();
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__167_1;
}
static void cont__167_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 638: if main_info.is_undefined:
  // 639:   Error "
  // 640:     Source file "@(main_filename)" does not exist!@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__167_2;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__167_6;
}
static void entry__167_2(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 639: ... "
  // 640:   Source file "@(main_filename)" does not exist!@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__167_3;
  arguments->slots[1] = get__main_filename();
  arguments->slots[2] = string__167_4;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__167_5;
}
static void cont__167_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 639: Error "
  // 640:   Source file "@(main_filename)" does not exist!@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__167_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 945: $$t undefined
  var._t = get__undefined();
  // 1085: if do_time_passes: !t current_time()
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = func__182_1;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__182_3;
}
static void entry__182_1(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1085: ... !t current_time()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__current_time();
  func = myself->type;
  frame->cont = cont__182_2;
}
static void cont__182_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._t = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__182_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1086: cond
  // 1087:   ->
  // 1088:     ||
  // 1089:       do_check_only
  // 1090:       do_dump_trees
  // 1091:       do_pretty_print
  // 1092:       do_print_simplified_source
  // 1093:     dump_source_or_check
  // 1094:   -> do_print_c print_c
  // 1095:   -> do_list_dependencies list_dependencies
  // ...
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = func__183_1;
  arguments->slots[1] = func__183_8;
  arguments->slots[2] = func__183_9;
  arguments->slots[3] = func__183_10;
  arguments->slots[4] = func__183_11;
  arguments->slots[5] = var._build_executable;
  result_count = 0;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__183_13;
}
static void entry__183_1(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_check_only();
  arguments->slots[1] = func__183_2;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__183_7;
}
static void entry__183_2(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_dump_trees();
  arguments->slots[1] = func__183_3;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__183_6;
}
static void entry__183_3(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_pretty_print();
  arguments->slots[1] = func__183_4;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__183_5;
}
static void entry__183_4(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1092: do_print_simplified_source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__do_print_simplified_source();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__183_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__183_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__183_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1087: ->
  // 1088:   ||
  // 1089:     do_check_only
  // 1090:     do_dump_trees
  // 1091:     do_pretty_print
  // 1092:     do_print_simplified_source
  // 1093:   dump_source_or_check
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = var._dump_source_or_check;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__183_8(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1094: -> do_print_c print_c
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_print_c;
  arguments->slots[1] = var._print_c;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__183_9(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1095: -> do_list_dependencies list_dependencies
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_list_dependencies;
  arguments->slots[1] = var._list_dependencies;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__183_10(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1096: -> do_build_codeblocks_project build_codeblocks_project
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_build_codeblocks_project;
  arguments->slots[1] = var._build_codeblocks_project;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__183_11(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1097: ... main_info.is_a_directory
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_info();
  result_count = 1;
  myself = get__is_a_directory();
  func = myself->type;
  frame->cont = cont__183_12;
}
static void cont__183_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1097: -> main_info.is_a_directory build_library
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = var._build_library;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__183_13(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = get__std__terminate();
  func = myself->type;
  frame->cont = cont__184_1;
}
static void cont__184_1(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  terminate(0); // should never be reached
}
static void entry__47_2(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // args: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* args */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 250: ... ewriteln args*
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__47_1_sim2c__show_compiler_debug_info(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // args: 0
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 250: ... : ewriteln args*
  frame->slots[1] /* temp__1 */ = create_closure(entry__47_2, 0);
  // 250: if do_show_compiler_debug_infos: ewriteln args*
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_show_compiler_debug_infos();
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__66_1_resolve_filename(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // filename: 0
  // libname: 1
  // libpath: 2
  frame->slots[1] /* libname */ = create_future();
  frame->slots[2] /* libpath */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 312: ... resolved_libraries.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._resolved_libraries;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__66_2;
}
static void cont__66_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 312: if resolved_libraries.is_undefined:
  // 313:   !resolved_libraries empty_table
  // 314:   for_each simlibpaths: (path)
  // 315:     if file_exists(path):
  // 316:       for_each directory(path): (entry)
  // 317:         if entry.is_a_directory:
  // 318:           $name std::filename_of(entry)
  // 319:           if name .matches. NAME: !resolved_libraries(name) fullname_of(entry)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = func__66_3;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__66_16;
}
static void entry__66_13(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // name: 0
  // entry: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  frame->slots[1] = myself->closure.frame->slots[0]; /* entry */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 319: ... !resolved_libraries(name) fullname_of(entry)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* entry */;
  result_count = 1;
  myself = get__fullname_of();
  func = myself->type;
  frame->cont = cont__66_14;
}
static void cont__66_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 319: ... !resolved_libraries(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = var._resolved_libraries;
  func = myself->type;
  frame->cont = cont__66_15;
}
static void cont__66_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._resolved_libraries = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__66_10(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // entry: 0
  // name: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* entry */
  frame->slots[1] /* name */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 318: $name std::filename_of(entry)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* entry */;
  result_count = 1;
  myself = get__std__filename_of();
  func = myself->type;
  frame->cont = cont__66_11;
}
static void cont__66_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* name */, arguments->slots[0]);
  // 319: ... name .matches. NAME
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* name */;
  arguments->slots[1] = get__NAME();
  result_count = 1;
  myself = get__matches();
  func = myself->type;
  frame->cont = cont__66_12;
}
static void cont__66_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 319: ... : !resolved_libraries(name) fullname_of(entry)
  frame->slots[3] /* temp__2 */ = create_closure(entry__66_13, 0);
  // 319: if name .matches. NAME: !resolved_libraries(name) fullname_of(entry)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__66_8(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // entry: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 317: ... entry.is_a_directory
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* entry */;
  result_count = 1;
  myself = get__is_a_directory();
  func = myself->type;
  frame->cont = cont__66_9;
}
static void cont__66_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 317: ... :
  // 318:   $name std::filename_of(entry)
  // 319:   if name .matches. NAME: !resolved_libraries(name) fullname_of(entry)
  frame->slots[2] /* temp__2 */ = create_closure(entry__66_10, 0);
  // 317: if entry.is_a_directory:
  // 318:   $name std::filename_of(entry)
  // 319:   if name .matches. NAME: !resolved_libraries(name) fullname_of(entry)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__66_6(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // path: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* path */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 316: ... directory(path)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* path */;
  result_count = 1;
  myself = get__directory();
  func = myself->type;
  frame->cont = cont__66_7;
}
static void cont__66_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 316: for_each directory(path): (entry)
  // 317:   if entry.is_a_directory:
  // 318:     $name std::filename_of(entry)
  // 319:     if name .matches. NAME: !resolved_libraries(name) fullname_of(entry)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__66_8;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__66_4(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // path: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 315: ... file_exists(path)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* path */;
  result_count = 1;
  myself = get__file_exists();
  func = myself->type;
  frame->cont = cont__66_5;
}
static void cont__66_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 315: ... :
  // 316:   for_each directory(path): (entry)
  // 317:     if entry.is_a_directory:
  // 318:       $name std::filename_of(entry)
  // 319:       if name .matches. NAME: !resolved_libraries(name) fullname_of(entry)
  frame->slots[2] /* temp__2 */ = create_closure(entry__66_6, 0);
  // 315: if file_exists(path):
  // 316:   for_each directory(path): (entry)
  // 317:     if entry.is_a_directory:
  // 318:       $name std::filename_of(entry)
  // 319:       if name .matches. NAME: !resolved_libraries(name) fullname_of(entry)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__66_3(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 313: !resolved_libraries empty_table
  var._resolved_libraries = get__empty_table();
  // 314: for_each simlibpaths: (path)
  // 315:   if file_exists(path):
  // 316:     for_each directory(path): (entry)
  // 317:       if entry.is_a_directory:
  // 318:         $name std::filename_of(entry)
  // 319:         if name .matches. NAME: !resolved_libraries(name) fullname_of(entry)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._simlibpaths;
  arguments->slots[1] = func__66_4;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__66_16(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 320: $libname filename .before. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__66_17;
}
static void cont__66_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* libname */, arguments->slots[0]);
  // 321: $libpath resolved_libraries(libname)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* libname */;
  result_count = 1;
  myself = var._resolved_libraries;
  func = myself->type;
  frame->cont = cont__66_18;
}
static void cont__66_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* libpath */, arguments->slots[0]);
  // 322: ... libpath.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* libpath */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__66_19;
}
static void cont__66_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 322: ... :
  // 323:   Error "
  // 324:     Cannot resolve required library "@(libname)@quot;!@
  frame->slots[4] /* temp__2 */ = create_closure(entry__66_20, 0);
  // 322: if libpath.is_undefined:
  // 323:   Error "
  // 324:     Cannot resolve required library "@(libname)@quot;!@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__66_24;
}
static void entry__66_20(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // libname: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* libname */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 323: ... "
  // 324:   Cannot resolve required library "@(libname)@quot;!@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__66_21;
  arguments->slots[1] = frame->slots[0] /* libname */;
  arguments->slots[2] = string__66_22;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__66_23;
}
static void cont__66_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 323: Error "
  // 324:   Cannot resolve required library "@(libname)@quot;!@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__66_24(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 325: ... filename .from. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__from();
  func = myself->type;
  frame->cont = cont__66_25;
}
static void cont__66_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 325: ... string(libpath filename .from. '/')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* libpath */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__66_26;
}
static void cont__66_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 325: -> string(libpath filename .from. '/')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__67_1_add_module_infos(void) {
  allocate_initialized_frame_gc(3, 10);
  // slot allocations:
  // path: 0
  // mod_path: 1
  // return: 2
  // entries: 3
  // filenames: 4
  // directories: 5
  // modules: 6
  frame->slots[2] /* return */ = create_continuation();
  frame->slots[3] /* entries */ = create_future();
  frame->slots[4] /* filenames */ = create_cell();
  frame->slots[5] /* directories */ = create_cell();
  frame->slots[6] /* modules */ = create_cell();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 336: ... --SORT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__SORT();
  arguments->slots[1] = get__std__true();
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__67_2;
}
static void cont__67_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 336: $entries directory(--SORT path)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[0] /* path */;
  result_count = 1;
  myself = get__directory();
  func = myself->type;
  frame->cont = cont__67_3;
}
static void cont__67_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* entries */, arguments->slots[0]);
  // 337: $$filenames empty_set
  ((CELL *)frame->slots[4])->contents /* filenames */ = get__empty_set();
  // 338: $$directories empty_list
  ((CELL *)frame->slots[5])->contents /* directories */ = get__empty_list();
  // 339: $$modules empty_key_order_set
  ((CELL *)frame->slots[6])->contents /* modules */ = get__empty_key_order_set();
  // 340: ... : (entry)
  // 341:   $name std::filename_of(entry)
  // 342:   cond
  // 343:     -> entry.is_a_directory: if name .matches. NAME: push &directories name
  // 344:     -> name .has_suffix. ".sim":
  // 345:       $submodule_name name .without_suffix. (some(".meta"), ".sim")
  // 346:       !filenames(submodule_name) true
  // 347:       $meta_level (length_of(name)-length_of(submodule_name)-4)/5
  // 348:       $stored_level meta_levels(submodule_name)
  // 349:       if stored_level.is_undefined || meta_level > stored_level:
  // ...
  frame->slots[7] /* temp__1 */ = create_closure(entry__67_4, 1);
  // 340: for_each entries: (entry)
  // 341:   $name std::filename_of(entry)
  // 342:   cond
  // 343:     -> entry.is_a_directory: if name .matches. NAME: push &directories name
  // 344:     -> name .has_suffix. ".sim":
  // 345:       $submodule_name name .without_suffix. (some(".meta"), ".sim")
  // 346:       !filenames(submodule_name) true
  // 347:       $meta_level (length_of(name)-length_of(submodule_name)-4)/5
  // 348:       $stored_level meta_levels(submodule_name)
  // 349:       if stored_level.is_undefined || meta_level > stored_level:
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* entries */;
  arguments->slots[1] = frame->slots[7] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__67_38;
}
static void entry__67_15(void) {
  allocate_initialized_frame_gc(4, 13);
  // slot allocations:
  // name: 0
  // filenames: 1
  // modules: 2
  // mod_path: 3
  // submodule_name: 4
  // meta_level: 5
  // stored_level: 6
  // basename: 7
  // mod_name: 8
  frame->slots[0] = myself->closure.frame->slots[0]; /* name */
  frame->slots[1] = myself->closure.frame->slots[1]; /* filenames */
  frame->slots[2] = myself->closure.frame->slots[2]; /* modules */
  frame->slots[3] = myself->closure.frame->slots[3]; /* mod_path */
  frame->slots[4] /* submodule_name */ = create_future();
  frame->slots[5] /* meta_level */ = create_future();
  frame->slots[6] /* stored_level */ = create_future();
  frame->slots[7] /* basename */ = create_future();
  frame->slots[8] /* mod_name */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 345: ... some(".meta")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__67_16;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__67_17;
}
static void cont__67_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__2 */ = arguments->slots[0];
  // 345: ... some(".meta"), ".sim"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__2 */;
  arguments->slots[1] = string__67_13;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__67_18;
}
static void cont__67_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 345: $submodule_name name .without_suffix. (some(".meta"), ".sim")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = get__without_suffix();
  func = myself->type;
  frame->cont = cont__67_19;
}
static void cont__67_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* submodule_name */, arguments->slots[0]);
  // 346: !filenames(submodule_name) true
  frame->slots[9] /* temp__1 */ = get__true();
  // 346: !filenames(submodule_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* submodule_name */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* filenames */;
  func = myself->type;
  frame->cont = cont__67_20;
}
static void cont__67_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* filenames */ = arguments->slots[0];
  // 347: ... length_of(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__67_21;
}
static void cont__67_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__3 */ = arguments->slots[0];
  // 347: ... length_of(submodule_name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* submodule_name */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__67_22;
}
static void cont__67_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__4 */ = arguments->slots[0];
  // 347: ... length_of(name)-length_of(submodule_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__3 */;
  arguments->slots[1] = frame->slots[12] /* temp__4 */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__67_23;
}
static void cont__67_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__2 */ = arguments->slots[0];
  // 347: ... length_of(name)-length_of(submodule_name)-4
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__2 */;
  arguments->slots[1] = number__4;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__67_24;
}
static void cont__67_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 347: $meta_level (length_of(name)-length_of(submodule_name)-4)/5
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__std__over();
  func = myself->type;
  frame->cont = cont__67_25;
}
static void cont__67_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* meta_level */, arguments->slots[0]);
  // 348: $stored_level meta_levels(submodule_name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* submodule_name */;
  result_count = 1;
  myself = var._meta_levels;
  func = myself->type;
  frame->cont = cont__67_26;
}
static void cont__67_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* stored_level */, arguments->slots[0]);
  // 349: ... stored_level.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* stored_level */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__67_27;
}
static void cont__67_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__2 */ = arguments->slots[0];
  // 349: ... meta_level > stored_level
  frame->slots[11] /* temp__3 */ = create_closure(entry__67_28, 0);
  // 349: ... stored_level.is_undefined || meta_level > stored_level
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__2 */;
  arguments->slots[1] = frame->slots[11] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__67_30;
}
static void entry__67_28(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // stored_level: 0
  // meta_level: 1
  frame->slots[0] = myself->closure.frame->slots[6]; /* stored_level */
  frame->slots[1] = myself->closure.frame->slots[5]; /* meta_level */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 349: ... meta_level > stored_level
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stored_level */;
  arguments->slots[1] = frame->slots[1] /* meta_level */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__67_29;
}
static void cont__67_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 349: ... meta_level > stored_level
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__67_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 349: ... :
  // 350:   !meta_levels(submodule_name) meta_level
  frame->slots[12] /* temp__4 */ = create_closure(entry__67_31, 0);
  // 349: if stored_level.is_undefined || meta_level > stored_level:
  // 350:   !meta_levels(submodule_name) meta_level
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = frame->slots[12] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__67_33;
}
static void entry__67_31(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // submodule_name: 0
  // meta_level: 1
  frame->slots[0] = myself->closure.frame->slots[4]; /* submodule_name */
  frame->slots[1] = myself->closure.frame->slots[5]; /* meta_level */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 350: !meta_levels(submodule_name) meta_level
  frame->slots[2] /* temp__1 */ = frame->slots[1] /* meta_level */;
  // 350: !meta_levels(submodule_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* submodule_name */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = var._meta_levels;
  func = myself->type;
  frame->cont = cont__67_32;
}
static void cont__67_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._meta_levels = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__67_33(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 351: $basename submodule_name .truncate_from. '-'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* submodule_name */;
  arguments->slots[1] = character__45;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__67_34;
}
static void cont__67_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[7] /* basename */, arguments->slots[0]);
  // 352: !modules(basename) true
  frame->slots[9] /* temp__1 */ = get__true();
  // 352: !modules(basename)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* basename */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[2])->contents /* modules */;
  func = myself->type;
  frame->cont = cont__67_35;
}
static void cont__67_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* modules */ = arguments->slots[0];
  // 353: $mod_name string(mod_path basename)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* mod_path */;
  arguments->slots[1] = frame->slots[7] /* basename */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__67_36;
}
static void cont__67_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[8] /* mod_name */, arguments->slots[0]);
  // 354: !module_info(mod_name) empty_key_order_table
  frame->slots[9] /* temp__1 */ = get__empty_key_order_table();
  // 354: !module_info(mod_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* mod_name */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = var._module_info;
  func = myself->type;
  frame->cont = cont__67_37;
}
static void cont__67_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._module_info = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__67_10(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // directories: 0
  // name: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* directories */
  frame->slots[1] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 343: ... push &directories name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* directories */;
  arguments->slots[1] = frame->slots[1] /* name */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__67_11;
}
static void cont__67_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* directories */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__67_8(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // name: 0
  // directories: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  frame->slots[1] = myself->closure.frame->slots[2]; /* directories */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 343: ... name .matches. NAME
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = get__NAME();
  result_count = 1;
  myself = get__matches();
  func = myself->type;
  frame->cont = cont__67_9;
}
static void cont__67_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 343: ... : push &directories name
  frame->slots[3] /* temp__2 */ = create_closure(entry__67_10, 0);
  // 343: ... if name .matches. NAME: push &directories name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__67_6(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // entry: 0
  // name: 1
  // directories: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* entry */
  frame->slots[1] = myself->closure.frame->slots[5]; /* name */
  frame->slots[2] = myself->closure.frame->slots[1]; /* directories */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 343: ... entry.is_a_directory
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* entry */;
  result_count = 1;
  myself = get__is_a_directory();
  func = myself->type;
  frame->cont = cont__67_7;
}
static void cont__67_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 343: ... : if name .matches. NAME: push &directories name
  frame->slots[4] /* temp__2 */ = create_closure(entry__67_8, 0);
  // 343: -> entry.is_a_directory: if name .matches. NAME: push &directories name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__67_12(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // name: 0
  // filenames: 1
  // modules: 2
  // mod_path: 3
  frame->slots[0] = myself->closure.frame->slots[5]; /* name */
  frame->slots[1] = myself->closure.frame->slots[2]; /* filenames */
  frame->slots[2] = myself->closure.frame->slots[3]; /* modules */
  frame->slots[3] = myself->closure.frame->slots[4]; /* mod_path */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 344: ... name .has_suffix. ".sim"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = string__67_13;
  result_count = 1;
  myself = get__has_suffix();
  func = myself->type;
  frame->cont = cont__67_14;
}
static void cont__67_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 344: ... :
  // 345:   $submodule_name name .without_suffix. (some(".meta"), ".sim")
  // 346:   !filenames(submodule_name) true
  // 347:   $meta_level (length_of(name)-length_of(submodule_name)-4)/5
  // 348:   $stored_level meta_levels(submodule_name)
  // 349:   if stored_level.is_undefined || meta_level > stored_level:
  // 350:     !meta_levels(submodule_name) meta_level
  // 351:   $basename submodule_name .truncate_from. '-'
  // 352:   !modules(basename) true
  // 353:   $mod_name string(mod_path basename)
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__67_15, 0);
  // 344: -> name .has_suffix. ".sim":
  // 345:   $submodule_name name .without_suffix. (some(".meta"), ".sim")
  // 346:   !filenames(submodule_name) true
  // 347:   $meta_level (length_of(name)-length_of(submodule_name)-4)/5
  // 348:   $stored_level meta_levels(submodule_name)
  // 349:   if stored_level.is_undefined || meta_level > stored_level:
  // 350:     !meta_levels(submodule_name) meta_level
  // 351:   $basename submodule_name .truncate_from. '-'
  // 352:   !modules(basename) true
  // 353:   $mod_name string(mod_path basename)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__67_4(void) {
  allocate_initialized_frame_gc(5, 8);
  // slot allocations:
  // entry: 0
  // directories: 1
  // filenames: 2
  // modules: 3
  // mod_path: 4
  // name: 5
  frame->slots[1] = myself->closure.frame->slots[5]; /* directories */
  frame->slots[2] = myself->closure.frame->slots[4]; /* filenames */
  frame->slots[3] = myself->closure.frame->slots[6]; /* modules */
  frame->slots[4] = myself->closure.frame->slots[1]; /* mod_path */
  frame->slots[5] /* name */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 341: $name std::filename_of(entry)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* entry */;
  result_count = 1;
  myself = get__std__filename_of();
  func = myself->type;
  frame->cont = cont__67_5;
}
static void cont__67_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* name */, arguments->slots[0]);
  // 343: -> entry.is_a_directory: if name .matches. NAME: push &directories name
  frame->slots[6] /* temp__1 */ = create_closure(entry__67_6, 0);
  // 344: -> name .has_suffix. ".sim":
  // 345:   $submodule_name name .without_suffix. (some(".meta"), ".sim")
  // 346:   !filenames(submodule_name) true
  // 347:   $meta_level (length_of(name)-length_of(submodule_name)-4)/5
  // 348:   $stored_level meta_levels(submodule_name)
  // 349:   if stored_level.is_undefined || meta_level > stored_level:
  // 350:     !meta_levels(submodule_name) meta_level
  // 351:   $basename submodule_name .truncate_from. '-'
  // 352:   !modules(basename) true
  // 353:   $mod_name string(mod_path basename)
  // ...
  frame->slots[7] /* temp__2 */ = create_closure(entry__67_12, 0);
  // 342: cond
  // 343:   -> entry.is_a_directory: if name .matches. NAME: push &directories name
  // 344:   -> name .has_suffix. ".sim":
  // 345:     $submodule_name name .without_suffix. (some(".meta"), ".sim")
  // 346:     !filenames(submodule_name) true
  // 347:     $meta_level (length_of(name)-length_of(submodule_name)-4)/5
  // 348:     $stored_level meta_levels(submodule_name)
  // 349:     if stored_level.is_undefined || meta_level > stored_level:
  // 350:       !meta_levels(submodule_name) meta_level
  // 351:     $basename submodule_name .truncate_from. '-'
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__cond();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__67_38(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 355: ... : (filename)
  // 356:   if filename .contains. '-':
  // 357:     unless filename .has_suffix. "-common":
  // 358:       $maybe_push_common: (plat)
  // 359:         $common_name string(name "-" plat "-common")
  // 360:         if filenames(common_name): push &files common_name
  // 361:       
  // 362:       $name filename .before. '-'
  // 363:       $mod_name string(mod_path name .truncate_from. '-')
  // 364:       $platform filename .behind. '-'
  // ...
  frame->slots[7] /* temp__1 */ = create_closure(entry__67_39, 1);
  // 355: for_each filenames: (filename)
  // 356:   if filename .contains. '-':
  // 357:     unless filename .has_suffix. "-common":
  // 358:       $maybe_push_common: (plat)
  // 359:         $common_name string(name "-" plat "-common")
  // 360:         if filenames(common_name): push &files common_name
  // 361:       
  // 362:       $name filename .before. '-'
  // 363:       $mod_name string(mod_path name .truncate_from. '-')
  // 364:       $platform filename .behind. '-'
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* filenames */;
  arguments->slots[1] = frame->slots[7] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__67_74;
}
static void entry__67_44(void) {
  allocate_initialized_frame_gc(3, 11);
  // slot allocations:
  // filenames: 0
  // filename: 1
  // mod_path: 2
  // maybe_push_common: 3
  // name: 4
  // mod_name: 5
  // platform: 6
  // parent: 7
  // files: 8
  frame->slots[0] = myself->closure.frame->slots[1]; /* filenames */
  frame->slots[1] = myself->closure.frame->slots[0]; /* filename */
  frame->slots[2] = myself->closure.frame->slots[2]; /* mod_path */
  frame->slots[3] /* maybe_push_common */ = create_future();
  frame->slots[4] /* name */ = create_future();
  frame->slots[5] /* mod_name */ = create_future();
  frame->slots[6] /* platform */ = create_future();
  frame->slots[7] /* parent */ = create_cell();
  frame->slots[8] /* files */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 358: ... : (plat)
  // 359:   $common_name string(name "-" plat "-common")
  // 360:   if filenames(common_name): push &files common_name
  frame->slots[9] /* temp__1 */ = create_closure(entry__67_45_maybe_push_common, 1);
  // 358: $maybe_push_common: (plat)
  // 359:   $common_name string(name "-" plat "-common")
  // 360:   if filenames(common_name): push &files common_name
  initialize_future(frame->slots[3] /* maybe_push_common */, frame->slots[9] /* temp__1 */);
  // 362: $name filename .before. '-'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* filename */;
  arguments->slots[1] = character__45;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__67_51;
}
static void entry__67_49(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // files: 0
  // common_name: 1
  frame->slots[0] = myself->closure.frame->slots[3]; /* files */
  frame->slots[1] = myself->closure.frame->slots[4]; /* common_name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 360: ... push &files common_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* files */;
  arguments->slots[1] = frame->slots[1] /* common_name */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__67_50;
}
static void cont__67_50(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* files */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__67_45_maybe_push_common(void) {
  allocate_initialized_frame_gc(4, 7);
  // slot allocations:
  // plat: 0
  // name: 1
  // filenames: 2
  // files: 3
  // common_name: 4
  frame->slots[1] = myself->closure.frame->slots[4]; /* name */
  frame->slots[2] = myself->closure.frame->slots[0]; /* filenames */
  frame->slots[3] = myself->closure.frame->slots[8]; /* files */
  frame->slots[4] /* common_name */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 359: $common_name string(name "-" plat "-common")
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* name */;
  arguments->slots[1] = string__67_46;
  arguments->slots[2] = frame->slots[0] /* plat */;
  arguments->slots[3] = string__67_42;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__67_47;
}
static void cont__67_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* common_name */, arguments->slots[0]);
  // 360: ... filenames(common_name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* common_name */;
  result_count = 1;
  myself = ((CELL *)frame->slots[2])->contents /* filenames */;
  func = myself->type;
  frame->cont = cont__67_48;
}
static void cont__67_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 360: ... : push &files common_name
  frame->slots[6] /* temp__2 */ = create_closure(entry__67_49, 0);
  // 360: if filenames(common_name): push &files common_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__67_51(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* name */, arguments->slots[0]);
  // 363: ... name .truncate_from. '-'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* name */;
  arguments->slots[1] = character__45;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__67_52;
}
static void cont__67_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 363: $mod_name string(mod_path name .truncate_from. '-')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* mod_path */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__67_53;
}
static void cont__67_53(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* mod_name */, arguments->slots[0]);
  // 364: $platform filename .behind. '-'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* filename */;
  arguments->slots[1] = character__45;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__67_54;
}
static void cont__67_54(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* platform */, arguments->slots[0]);
  // 365: $$parent supported_platforms(platform)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* platform */;
  result_count = 1;
  myself = var._supported_platforms;
  func = myself->type;
  frame->cont = cont__67_55;
}
static void cont__67_55(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[7])->contents /* parent */ = arguments->slots[0];
  // 366: ... parent.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[7])->contents /* parent */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__67_56;
}
static void cont__67_56(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 366: ... :
  // 367:   Error "
  // 368:     The platform "@(platform)" is not supported!@
  frame->slots[10] /* temp__2 */ = create_closure(entry__67_57, 0);
  // 366: unless parent.is_defined:
  // 367:   Error "
  // 368:     The platform "@(platform)" is not supported!@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__67_61;
}
static void entry__67_57(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // platform: 0
  frame->slots[0] = myself->closure.frame->slots[6]; /* platform */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 367: ... "
  // 368:   The platform "@(platform)" is not supported!@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__67_58;
  arguments->slots[1] = frame->slots[0] /* platform */;
  arguments->slots[2] = string__67_59;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__67_60;
}
static void cont__67_60(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 367: Error "
  // 368:   The platform "@(platform)" is not supported!@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__67_61(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 369: $$files list(filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* filename */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__67_62;
}
static void cont__67_62(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[8])->contents /* files */ = arguments->slots[0];
  // 370: maybe_push_common platform
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* platform */;
  result_count = 0;
  myself = frame->slots[3] /* maybe_push_common */;
  func = myself->type;
  frame->cont = cont__67_63;
}
static void cont__67_63(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 371: ... -> parent != NONE:
  // 372:   maybe_push_common parent
  // 373:   !parent supported_platforms(parent)
  frame->slots[9] /* temp__1 */ = create_closure(entry__67_64, 0);
  // 371: while -> parent != NONE:
  // 372:   maybe_push_common parent
  // 373:   !parent supported_platforms(parent)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  result_count = 0;
  myself = get__while();
  func = myself->type;
  frame->cont = cont__67_70;
}
static void entry__67_67(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // maybe_push_common: 0
  // parent: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* maybe_push_common */
  frame->slots[1] = myself->closure.frame->slots[0]; /* parent */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 372: maybe_push_common parent
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* parent */;
  result_count = 0;
  myself = frame->slots[0] /* maybe_push_common */;
  func = myself->type;
  frame->cont = cont__67_68;
}
static void cont__67_68(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 373: !parent supported_platforms(parent)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* parent */;
  result_count = 1;
  myself = var._supported_platforms;
  func = myself->type;
  frame->cont = cont__67_69;
}
static void cont__67_69(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* parent */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__67_64(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // parent: 0
  // maybe_push_common: 1
  frame->slots[0] = myself->closure.frame->slots[7]; /* parent */
  frame->slots[1] = myself->closure.frame->slots[3]; /* maybe_push_common */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 371: ... parent != NONE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parent */;
  arguments->slots[1] = var._NONE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__67_65;
}
static void cont__67_65(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 371: ... parent != NONE
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__67_66;
}
static void cont__67_66(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 371: ... :
  // 372:   maybe_push_common parent
  // 373:   !parent supported_platforms(parent)
  frame->slots[4] /* temp__3 */ = create_closure(entry__67_67, 0);
  // 371: ... -> parent != NONE:
  // 372:   maybe_push_common parent
  // 373:   !parent supported_platforms(parent)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__67_70(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 374: !module_info(mod_name)(platform) files
  frame->slots[9] /* temp__1 */ = ((CELL *)frame->slots[8])->contents /* files */;
  // 374: ... module_info(mod_name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* mod_name */;
  result_count = 1;
  myself = var._module_info;
  func = myself->type;
  frame->cont = cont__67_71;
}
static void cont__67_71(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__2 */ = arguments->slots[0];
  // 374: !module_info(mod_name)(platform)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* platform */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = frame->slots[10] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__67_72;
}
static void cont__67_72(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__2 */ = arguments->slots[0];
  // 374: !module_info(mod_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* mod_name */;
  arguments->slots[1] = frame->slots[10] /* temp__2 */;
  result_count = 1;
  myself = var._module_info;
  func = myself->type;
  frame->cont = cont__67_73;
}
static void cont__67_73(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._module_info = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__67_41(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // filename: 0
  // filenames: 1
  // mod_path: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* filename */
  frame->slots[1] = myself->closure.frame->slots[1]; /* filenames */
  frame->slots[2] = myself->closure.frame->slots[2]; /* mod_path */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 357: ... filename .has_suffix. "-common"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  arguments->slots[1] = string__67_42;
  result_count = 1;
  myself = get__has_suffix();
  func = myself->type;
  frame->cont = cont__67_43;
}
static void cont__67_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 357: ... :
  // 358:   $maybe_push_common: (plat)
  // 359:     $common_name string(name "-" plat "-common")
  // 360:     if filenames(common_name): push &files common_name
  // 361:   
  // 362:   $name filename .before. '-'
  // 363:   $mod_name string(mod_path name .truncate_from. '-')
  // 364:   $platform filename .behind. '-'
  // 365:   $$parent supported_platforms(platform)
  // 366:   unless parent.is_defined:
  // ...
  frame->slots[4] /* temp__2 */ = create_closure(entry__67_44, 0);
  // 357: unless filename .has_suffix. "-common":
  // 358:   $maybe_push_common: (plat)
  // 359:     $common_name string(name "-" plat "-common")
  // 360:     if filenames(common_name): push &files common_name
  // 361:   
  // 362:   $name filename .before. '-'
  // 363:   $mod_name string(mod_path name .truncate_from. '-')
  // 364:   $platform filename .behind. '-'
  // 365:   $$parent supported_platforms(platform)
  // 366:   unless parent.is_defined:
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
static void entry__67_39(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // filename: 0
  // filenames: 1
  // mod_path: 2
  frame->slots[1] = myself->closure.frame->slots[4]; /* filenames */
  frame->slots[2] = myself->closure.frame->slots[1]; /* mod_path */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 356: ... filename .contains. '-'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  arguments->slots[1] = character__45;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__67_40;
}
static void cont__67_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 356: ... :
  // 357:   unless filename .has_suffix. "-common":
  // 358:     $maybe_push_common: (plat)
  // 359:       $common_name string(name "-" plat "-common")
  // 360:       if filenames(common_name): push &files common_name
  // 361:     
  // 362:     $name filename .before. '-'
  // 363:     $mod_name string(mod_path name .truncate_from. '-')
  // 364:     $platform filename .behind. '-'
  // 365:     $$parent supported_platforms(platform)
  // ...
  frame->slots[4] /* temp__2 */ = create_closure(entry__67_41, 0);
  // 356: if filename .contains. '-':
  // 357:   unless filename .has_suffix. "-common":
  // 358:     $maybe_push_common: (plat)
  // 359:       $common_name string(name "-" plat "-common")
  // 360:       if filenames(common_name): push &files common_name
  // 361:     
  // 362:     $name filename .before. '-'
  // 363:     $mod_name string(mod_path name .truncate_from. '-')
  // 364:     $platform filename .behind. '-'
  // 365:     $$parent supported_platforms(platform)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__67_74(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 375: ... parameter_count_of(return)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* return */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__67_75;
}
static void cont__67_75(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 375: ... parameter_count_of(return) == 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__2 */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__67_76;
}
static void cont__67_76(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 375: ... : return directories modules
  frame->slots[9] /* temp__3 */ = create_closure(entry__67_77, 0);
  // 375: if parameter_count_of(return) == 2: return directories modules
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__67_78;
}
static void entry__67_77(void) {
  allocate_initialized_frame_gc(3, 3);
  // slot allocations:
  // return: 0
  // directories: 1
  // modules: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  frame->slots[1] = myself->closure.frame->slots[5]; /* directories */
  frame->slots[2] = myself->closure.frame->slots[6]; /* modules */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 375: ... return directories modules
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* directories */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* modules */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__67_78(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__68_4(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // info: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 386: ... -> info
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__68_5(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // mod_filename: 0
  // mod_name: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* mod_filename */
  frame->slots[1] = myself->closure.frame->slots[1]; /* mod_name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 387: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__68_6;
}
static void cont__68_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 387: ... before(mod_filename '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__68_7;
}
static void cont__68_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 387: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__68_8;
}
static void cont__68_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 387: ... until(mod_name '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* mod_name */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = get__until();
  func = myself->type;
  frame->cont = cont__68_9;
}
static void cont__68_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 387: add_module_infos before(mod_filename '/' -1) until(mod_name '/' -1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 0;
  myself = var._add_module_infos;
  func = myself->type;
  frame->cont = cont__68_10;
}
static void cont__68_10(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 388: ... module_info(mod_name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* mod_name */;
  result_count = 1;
  myself = var._module_info;
  func = myself->type;
  frame->cont = cont__68_11;
}
static void cont__68_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 388: -> module_info(mod_name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__68_1_lookup(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // mod_filename: 0
  // mod_name: 1
  // info: 2
  frame->slots[2] /* info */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 385: $info module_info(mod_name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* mod_name */;
  result_count = 1;
  myself = var._module_info;
  func = myself->type;
  frame->cont = cont__68_2;
}
static void cont__68_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* info */, arguments->slots[0]);
  // 386: ... info.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* info */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__68_3;
}
static void cont__68_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 386: ... -> info
  frame->slots[4] /* temp__2 */ = create_closure(entry__68_4, 0);
  // 386: ... :
  // 387:   add_module_infos before(mod_filename '/' -1) until(mod_name '/' -1)
  // 388:   -> module_info(mod_name)
  frame->slots[5] /* temp__3 */ = create_closure(entry__68_5, 0);
  // 386: if info.is_defined (-> info):
  // 387:   add_module_infos before(mod_filename '/' -1) until(mod_name '/' -1)
  // 388:   -> module_info(mod_name)
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
static void entry__69_1_CC(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // args: 0
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 391: ... : ewriteln c_compiler() ' ' join(args)
  frame->slots[1] /* temp__1 */ = create_closure(entry__69_2, 0);
  // 391: if do_show_debug_infos: ewriteln c_compiler() ' ' join(args)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_show_debug_infos();
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__69_5;
}
static void entry__69_2(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // args: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* args */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 391: ... c_compiler()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__c_compiler();
  func = myself->type;
  frame->cont = cont__69_3;
}
static void cont__69_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 391: ... join(args)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* args */;
  result_count = 1;
  myself = get__join();
  func = myself->type;
  frame->cont = cont__69_4;
}
static void cont__69_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 391: ... ewriteln c_compiler() ' ' join(args)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = character__32;
  arguments->slots[2] = frame->slots[2] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__69_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 392: cc args*
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = frame->caller_result_count;
  myself = var._cc;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__70_4(void) {
  allocate_initialized_frame_gc(2, 8);
  // slot allocations:
  // c_filename: 0
  // o_filename: 1
  // out: 2
  // err: 3
  // success: 4
  frame->slots[0] = myself->closure.frame->slots[0]; /* c_filename */
  frame->slots[1] = myself->closure.frame->slots[1]; /* o_filename */
  frame->slots[2] /* out */ = create_future();
  frame->slots[3] /* err */ = create_future();
  frame->slots[4] /* success */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 396: CC $_out $err $success cc_options* "-c" c_filename "-o" o_filename
  argument_count = 0;
  arguments = node_p;
  unfold(var._cc_options);
  arguments->slots[argument_count++] = string__70_5;
  arguments->slots[argument_count++] = frame->slots[0] /* c_filename */;
  arguments->slots[argument_count++] = string__70_6;
  arguments->slots[argument_count++] = frame->slots[1] /* o_filename */;
  result_count = 3;
  myself = var._CC;
  func = myself->type;
  frame->cont = cont__70_7;
}
static void cont__70_7(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  frame->slots[6] /* temp__2 */ = arguments->slots[1];
  frame->slots[7] /* temp__3 */ = arguments->slots[2];
  // 396: ... _out
  initialize_future(frame->slots[2] /* out */, frame->slots[5] /* temp__1 */);
  // 396: ... err
  initialize_future(frame->slots[3] /* err */, frame->slots[6] /* temp__2 */);
  // 396: ... success
  initialize_future(frame->slots[4] /* success */, frame->slots[7] /* temp__3 */);
  // 397: ... :
  // 398:   Error "
  // 399:     Failed to compile @(c_filename)
  // 400:     @(err.from_utf8)
  frame->slots[5] /* temp__1 */ = create_closure(entry__70_8, 0);
  // 397: unless success:
  // 398:   Error "
  // 399:     Failed to compile @(c_filename)
  // 400:     @(err.from_utf8)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* success */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__70_13;
}
static void entry__70_8(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // c_filename: 0
  // err: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* c_filename */
  frame->slots[1] = myself->closure.frame->slots[3]; /* err */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 400: ... err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* err */;
  result_count = 1;
  myself = get__from_utf8();
  func = myself->type;
  frame->cont = cont__70_9;
}
static void cont__70_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 398: ... "
  // 399:   Failed to compile @(c_filename)
  // 400:   @(err.from_utf8)
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__70_10;
  arguments->slots[1] = frame->slots[0] /* c_filename */;
  arguments->slots[2] = string__70_11;
  arguments->slots[3] = frame->slots[3] /* temp__2 */;
  arguments->slots[4] = string__70_11;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__70_12;
}
static void cont__70_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 398: Error "
  // 399:   Failed to compile @(c_filename)
  // 400:   @(err.from_utf8)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__70_13(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 401: !do_link true
  set__do_link(get__true());
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__70_1_compile_c(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // c_filename: 0
  // o_filename: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 395: ... do_build_codeblocks_project || do_list_dependencies
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_build_codeblocks_project;
  arguments->slots[1] = func__70_2;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__70_3;
}
static void entry__70_2(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 395: ... do_list_dependencies
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._do_list_dependencies;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__70_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 395: ... :
  // 396:   CC $_out $err $success cc_options* "-c" c_filename "-o" o_filename
  // 397:   unless success:
  // 398:     Error "
  // 399:       Failed to compile @(c_filename)
  // 400:       @(err.from_utf8)
  // 401:   !do_link true
  frame->slots[3] /* temp__2 */ = create_closure(entry__70_4, 0);
  // 395: unless do_build_codeblocks_project || do_list_dependencies:
  // 396:   CC $_out $err $success cc_options* "-c" c_filename "-o" o_filename
  // 397:   unless success:
  // 398:     Error "
  // 399:       Failed to compile @(c_filename)
  // 400:       @(err.from_utf8)
  // 401:   !do_link true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__71_2(void) {
  allocate_initialized_frame_gc(2, 13);
  // slot allocations:
  // mod_filename: 0
  // meta_level: 1
  // meta_path: 2
  // filename: 3
  // meta_filename: 4
  // meta_c_filename: 5
  // sim_filename: 6
  // meta_info: 7
  // sim_info: 8
  // meta_c_info: 9
  // force_rebuild: 10
  frame->slots[0] = myself->closure.frame->slots[0]; /* mod_filename */
  frame->slots[1] = myself->closure.frame->slots[2]; /* meta_level */
  frame->slots[2] /* meta_path */ = create_future();
  frame->slots[3] /* filename */ = create_future();
  frame->slots[4] /* meta_filename */ = create_future();
  frame->slots[5] /* meta_c_filename */ = create_future();
  frame->slots[6] /* sim_filename */ = create_future();
  frame->slots[7] /* meta_info */ = create_future();
  frame->slots[8] /* sim_info */ = create_future();
  frame->slots[9] /* meta_c_info */ = create_future();
  frame->slots[10] /* force_rebuild */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 413: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__71_3;
}
static void cont__71_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 413: $meta_path truncate_from(mod_filename '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[11] /* temp__1 */;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__71_4;
}
static void cont__71_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* meta_path */, arguments->slots[0]);
  // 414: ... dup(".meta" meta_level)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__67_16;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* meta_level */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__71_5;
}
static void cont__71_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 414: $filename string(mod_filename dup(".meta" meta_level))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = frame->slots[11] /* temp__1 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__71_6;
}
static void cont__71_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* filename */, arguments->slots[0]);
  // 415: $meta_filename string(filename ".sim")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* filename */;
  arguments->slots[1] = string__67_13;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__71_7;
}
static void cont__71_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* meta_filename */, arguments->slots[0]);
  // 416: ... dup(".meta" meta_level)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__67_16;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* meta_level */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__71_8;
}
static void cont__71_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 416: $meta_c_filename string(mod_filename dup(".meta" meta_level) ".c")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = frame->slots[11] /* temp__1 */;
  arguments->slots[2] = string__71_9;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__71_10;
}
static void cont__71_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* meta_c_filename */, arguments->slots[0]);
  // 417: ... meta_level-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* meta_level */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__71_11;
}
static void cont__71_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__2 */ = arguments->slots[0];
  // 417: ... dup(".meta" meta_level-1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__67_16;
  arguments->slots[1] = frame->slots[12] /* temp__2 */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__71_12;
}
static void cont__71_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 417: $sim_filename string(mod_filename dup(".meta" meta_level-1) ".sim")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = frame->slots[11] /* temp__1 */;
  arguments->slots[2] = string__67_13;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__71_13;
}
static void cont__71_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* sim_filename */, arguments->slots[0]);
  // 418: $meta_info stat(meta_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* meta_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__71_14;
}
static void cont__71_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[7] /* meta_info */, arguments->slots[0]);
  // 419: $sim_info stat(sim_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* sim_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__71_15;
}
static void cont__71_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[8] /* sim_info */, arguments->slots[0]);
  // 420: $meta_c_info stat(meta_c_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* meta_c_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__71_16;
}
static void cont__71_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[9] /* meta_c_info */, arguments->slots[0]);
  frame->slots[11] /* temp__1 */ = create_closure(entry__71_17, 0);
  // 422: $$force_rebuild
  // 423:   ||
  // 424:     do_rebuild
  // 425:     sim_info.is_undefined
  // 426:     meta_c_info.is_undefined
  // 427:     modification_time_of(meta_info) > modification_time_of(meta_c_info)
  // 428:     modification_time_of(meta_c_info) > modification_time_of(sim_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_rebuild;
  arguments->slots[1] = frame->slots[11] /* temp__1 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__71_32;
}
static void entry__71_17(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // sim_info: 0
  // meta_c_info: 1
  // meta_info: 2
  frame->slots[0] = myself->closure.frame->slots[8]; /* sim_info */
  frame->slots[1] = myself->closure.frame->slots[9]; /* meta_c_info */
  frame->slots[2] = myself->closure.frame->slots[7]; /* meta_info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 425: sim_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* sim_info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__71_18;
}
static void cont__71_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  frame->slots[5] /* temp__3 */ = create_closure(entry__71_19, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__71_31;
}
static void entry__71_19(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // meta_c_info: 0
  // meta_info: 1
  // sim_info: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* meta_c_info */
  frame->slots[1] = myself->closure.frame->slots[2]; /* meta_info */
  frame->slots[2] = myself->closure.frame->slots[0]; /* sim_info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 426: meta_c_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* meta_c_info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__71_20;
}
static void cont__71_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  frame->slots[5] /* temp__3 */ = create_closure(entry__71_21, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__71_30;
}
static void entry__71_21(void) {
  allocate_initialized_frame_gc(3, 8);
  // slot allocations:
  // meta_c_info: 0
  // meta_info: 1
  // sim_info: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* meta_c_info */
  frame->slots[1] = myself->closure.frame->slots[1]; /* meta_info */
  frame->slots[2] = myself->closure.frame->slots[2]; /* sim_info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 427: ... modification_time_of(meta_c_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* meta_c_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__71_22;
}
static void cont__71_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 427: modification_time_of(meta_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* meta_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__71_23;
}
static void cont__71_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__4 */ = arguments->slots[0];
  // 427: modification_time_of(meta_info) > modification_time_of(meta_c_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__71_24;
}
static void cont__71_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 428: modification_time_of(meta_c_info) > modification_time_of(sim_info)
  frame->slots[7] /* temp__5 */ = create_closure(entry__71_25, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__5 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__71_29;
}
static void entry__71_25(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // sim_info: 0
  // meta_c_info: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* sim_info */
  frame->slots[1] = myself->closure.frame->slots[0]; /* meta_c_info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 428: ... modification_time_of(sim_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* sim_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__71_26;
}
static void cont__71_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 428: modification_time_of(meta_c_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* meta_c_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__71_27;
}
static void cont__71_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 428: modification_time_of(meta_c_info) > modification_time_of(sim_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__71_28;
}
static void cont__71_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 428: modification_time_of(meta_c_info) > modification_time_of(sim_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__71_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__71_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__71_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__71_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[10])->contents /* force_rebuild */ = arguments->slots[0];
  // 430: ... :
  // 431:   $modification_time modification_time_of(sim_info)
  // 432:   load $meta_c_buf meta_c_filename
  // 433:   do: (-> break)
  // 434:     for_each_line meta_c_buf: ($line)
  // 435:       $check: (data_filename)
  // 436:         $data_info stat(data_filename)
  // 437:         if
  // 438:           ||
  // 439:             data_info.is_undefined
  // ...
  frame->slots[11] /* temp__1 */ = create_closure(entry__71_33, 0);
  // 430: unless force_rebuild:
  // 431:   $modification_time modification_time_of(sim_info)
  // 432:   load $meta_c_buf meta_c_filename
  // 433:   do: (-> break)
  // 434:     for_each_line meta_c_buf: ($line)
  // 435:       $check: (data_filename)
  // 436:         $data_info stat(data_filename)
  // 437:         if
  // 438:           ||
  // 439:             data_info.is_undefined
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[10])->contents /* force_rebuild */;
  arguments->slots[1] = frame->slots[11] /* temp__1 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__71_66;
}
static void entry__71_36(void) {
  allocate_initialized_frame_gc(5, 6);
  // slot allocations:
  // break: 0
  // meta_c_buf: 1
  // modification_time: 2
  // force_rebuild: 3
  // meta_path: 4
  frame->slots[0] /* break */ = create_continuation();
  frame->slots[1] = myself->closure.frame->slots[5]; /* meta_c_buf */
  frame->slots[2] = myself->closure.frame->slots[4]; /* modification_time */
  frame->slots[3] = myself->closure.frame->slots[2]; /* force_rebuild */
  frame->slots[4] = myself->closure.frame->slots[3]; /* meta_path */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 434: ... : ($line)
  // 435:   $check: (data_filename)
  // 436:     $data_info stat(data_filename)
  // 437:     if
  // 438:       ||
  // 439:         data_info.is_undefined
  // 440:         modification_time_of(data_info) > modification_time
  // 441:       :
  // 442:         !force_rebuild true
  // 443:         break
  // ...
  frame->slots[5] /* temp__1 */ = create_closure(entry__71_37, 1);
  // 434: for_each_line meta_c_buf: ($line)
  // 435:   $check: (data_filename)
  // 436:     $data_info stat(data_filename)
  // 437:     if
  // 438:       ||
  // 439:         data_info.is_undefined
  // 440:         modification_time_of(data_info) > modification_time
  // 441:       :
  // 442:         !force_rebuild true
  // 443:         break
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* meta_c_buf */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each_line();
  func = myself->type;
  frame->cont = cont__71_65;
}
static void entry__71_63(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // path: 0
  // check: 1
  // argument: 2
  frame->slots[1] = myself->closure.frame->slots[0]; /* check */
  frame->slots[2] = myself->closure.frame->slots[1]; /* argument */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 455: ... string(path '/' argument)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* path */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[2] /* argument */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__71_64;
}
static void cont__71_64(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 455: ... check string(path '/' argument)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* check */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__71_58(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // check: 0
  // meta_path: 1
  // argument: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* check */
  frame->slots[1] = myself->closure.frame->slots[2]; /* meta_path */
  frame->slots[2] = myself->closure.frame->slots[0]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 453: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__71_59;
}
static void cont__71_59(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 453: ... range(argument 2 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* argument */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__71_60;
}
static void cont__71_60(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 453: ... string(meta_path range(argument 2 -1))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* meta_path */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__71_61;
}
static void cont__71_61(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 453: check string(meta_path range(argument 2 -1))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* check */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__71_62(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // check: 0
  // argument: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* check */
  frame->slots[1] = myself->closure.frame->slots[0]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 455: ... : (path) check string(path '/' argument)
  frame->slots[2] /* temp__1 */ = create_closure(entry__71_63, 1);
  // 455: for_each simdatapaths: (path) check string(path '/' argument)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._simdatapaths;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__71_55(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // argument: 0
  // check: 1
  // meta_path: 2
  frame->slots[0] = myself->closure.frame->slots[7]; /* argument */
  frame->slots[1] = myself->closure.frame->slots[5]; /* check */
  frame->slots[2] = myself->closure.frame->slots[4]; /* meta_path */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 452: argument .has_prefix. "./"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* argument */;
  arguments->slots[1] = string__71_56;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__71_57;
}
static void cont__71_57(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 452: ... :
  // 453:   check string(meta_path range(argument 2 -1))
  frame->slots[4] /* temp__2 */ = create_closure(entry__71_58, 0);
  // 454: :
  // 455:   for_each simdatapaths: (path) check string(path '/' argument)
  frame->slots[5] /* temp__3 */ = create_closure(entry__71_62, 0);
  // 451: if
  // 452:   argument .has_prefix. "./":
  // 453:     check string(meta_path range(argument 2 -1))
  // 454:   :
  // 455:     for_each simdatapaths: (path) check string(path '/' argument)
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
static void entry__71_37(void) {
  allocate_initialized_frame_gc(5, 10);
  // slot allocations:
  // line: 0
  // modification_time: 1
  // force_rebuild: 2
  // break: 3
  // meta_path: 4
  // check: 5
  // command: 6
  // argument: 7
  frame->slots[1] = myself->closure.frame->slots[2]; /* modification_time */
  frame->slots[2] = myself->closure.frame->slots[3]; /* force_rebuild */
  frame->slots[3] = myself->closure.frame->slots[0]; /* break */
  frame->slots[4] = myself->closure.frame->slots[4]; /* meta_path */
  frame->slots[5] /* check */ = create_future();
  frame->slots[6] /* command */ = create_future();
  frame->slots[7] /* argument */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* line */ = create_cell_with_contents(arguments->slots[0]);
  // 435: ... : (data_filename)
  // 436:   $data_info stat(data_filename)
  // 437:   if
  // 438:     ||
  // 439:       data_info.is_undefined
  // 440:       modification_time_of(data_info) > modification_time
  // 441:     :
  // 442:       !force_rebuild true
  // 443:       break
  frame->slots[8] /* temp__1 */ = create_closure(entry__71_38_check, 1);
  // 435: $check: (data_filename)
  // 436:   $data_info stat(data_filename)
  // 437:   if
  // 438:     ||
  // 439:       data_info.is_undefined
  // 440:       modification_time_of(data_info) > modification_time
  // 441:     :
  // 442:       !force_rebuild true
  // 443:       break
  initialize_future(frame->slots[5] /* check */, frame->slots[8] /* temp__1 */);
  // 445: ... line .has_prefix. "/// "
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  arguments->slots[1] = string__71_46;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__71_47;
}
static void entry__71_45(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // force_rebuild: 0
  // break: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* force_rebuild */
  frame->slots[1] = myself->closure.frame->slots[3]; /* break */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 442: !force_rebuild true
  ((CELL *)frame->slots[0])->contents /* force_rebuild */ = get__true();
  // 443: break
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* break */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__71_38_check(void) {
  allocate_initialized_frame_gc(4, 9);
  // slot allocations:
  // data_filename: 0
  // modification_time: 1
  // force_rebuild: 2
  // break: 3
  // data_info: 4
  frame->slots[1] = myself->closure.frame->slots[1]; /* modification_time */
  frame->slots[2] = myself->closure.frame->slots[2]; /* force_rebuild */
  frame->slots[3] = myself->closure.frame->slots[3]; /* break */
  frame->slots[4] /* data_info */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 436: $data_info stat(data_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* data_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__71_39;
}
static void cont__71_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* data_info */, arguments->slots[0]);
  // 439: data_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* data_info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__71_40;
}
static void cont__71_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 440: modification_time_of(data_info) > modification_time
  frame->slots[7] /* temp__3 */ = create_closure(entry__71_41, 0);
  // 438: ||
  // 439:   data_info.is_undefined
  // 440:   modification_time_of(data_info) > modification_time
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__71_44;
}
static void entry__71_41(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // modification_time: 0
  // data_info: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* modification_time */
  frame->slots[1] = myself->closure.frame->slots[4]; /* data_info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 440: modification_time_of(data_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* data_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__71_42;
}
static void cont__71_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 440: modification_time_of(data_info) > modification_time
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* modification_time */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__71_43;
}
static void cont__71_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 440: modification_time_of(data_info) > modification_time
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__71_44(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 441: :
  // 442:   !force_rebuild true
  // 443:   break
  frame->slots[8] /* temp__4 */ = create_closure(entry__71_45, 0);
  // 437: if
  // 438:   ||
  // 439:     data_info.is_undefined
  // 440:     modification_time_of(data_info) > modification_time
  // 441:   :
  // 442:     !force_rebuild true
  // 443:     break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__71_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 445: unless line .has_prefix. "/// " break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* break */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__71_48;
}
static void cont__71_48(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 446: behind &line ' '
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  arguments->slots[1] = character__32;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__71_49;
}
static void cont__71_49(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* line */ = arguments->slots[0];
  // 447: trim &line
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__71_50;
}
static void cont__71_50(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* line */ = arguments->slots[0];
  // 448: $command line .truncate_from. WHITESPACE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  arguments->slots[1] = var._WHITESPACE;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__71_51;
}
static void cont__71_51(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* command */, arguments->slots[0]);
  // 449: $argument line .behind. WHITESPACE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  arguments->slots[1] = var._WHITESPACE;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__71_52;
}
static void cont__71_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[7] /* argument */, arguments->slots[0]);
  // 450: ... command == "data"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* command */;
  arguments->slots[1] = string__71_53;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__71_54;
}
static void cont__71_54(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 450: ... :
  // 451:   if
  // 452:     argument .has_prefix. "./":
  // 453:       check string(meta_path range(argument 2 -1))
  // 454:     :
  // 455:       for_each simdatapaths: (path) check string(path '/' argument)
  frame->slots[9] /* temp__2 */ = create_closure(entry__71_55, 0);
  // 450: if command == "data":
  // 451:   if
  // 452:     argument .has_prefix. "./":
  // 453:       check string(meta_path range(argument 2 -1))
  // 454:     :
  // 455:       for_each simdatapaths: (path) check string(path '/' argument)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__71_65(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__71_33(void) {
  allocate_initialized_frame_gc(4, 7);
  // slot allocations:
  // sim_info: 0
  // meta_c_filename: 1
  // force_rebuild: 2
  // meta_path: 3
  // modification_time: 4
  // meta_c_buf: 5
  frame->slots[0] = myself->closure.frame->slots[8]; /* sim_info */
  frame->slots[1] = myself->closure.frame->slots[5]; /* meta_c_filename */
  frame->slots[2] = myself->closure.frame->slots[10]; /* force_rebuild */
  frame->slots[3] = myself->closure.frame->slots[2]; /* meta_path */
  frame->slots[4] /* modification_time */ = create_future();
  frame->slots[5] /* meta_c_buf */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 431: $modification_time modification_time_of(sim_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* sim_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__71_34;
}
static void cont__71_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* modification_time */, arguments->slots[0]);
  // 432: load $meta_c_buf meta_c_filename
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* meta_c_filename */;
  result_count = 1;
  myself = get__load();
  func = myself->type;
  frame->cont = cont__71_35;
}
static void cont__71_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* meta_c_buf */, arguments->slots[0]);
  // 433: ... : (-> break)
  // 434:   for_each_line meta_c_buf: ($line)
  // 435:     $check: (data_filename)
  // 436:       $data_info stat(data_filename)
  // 437:       if
  // 438:         ||
  // 439:           data_info.is_undefined
  // 440:           modification_time_of(data_info) > modification_time
  // 441:         :
  // 442:           !force_rebuild true
  // ...
  frame->slots[6] /* temp__1 */ = create_closure(entry__71_36, 0);
  // 433: do: (-> break)
  // 434:   for_each_line meta_c_buf: ($line)
  // 435:     $check: (data_filename)
  // 436:       $data_info stat(data_filename)
  // 437:       if
  // 438:         ||
  // 439:           data_info.is_undefined
  // 440:           modification_time_of(data_info) > modification_time
  // 441:         :
  // 442:           !force_rebuild true
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__do();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__71_66(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 456: ... :
  // 457:   %on_top_level false
  // 458:   %%objects empty_insert_order_set
  // 459:   %%libraries empty_insert_order_set
  // 460:   %%do_link false
  // 461:   %%last_modification_time undefined
  // 462:   %do_build_static_executable false
  // 463:   %main_filename meta_filename
  // 464:   %main_info stat(main_filename)
  // 465:   build_executable
  // ...
  frame->slots[11] /* temp__1 */ = create_closure(entry__71_67, 0);
  // 456: if force_rebuild:
  // 457:   %on_top_level false
  // 458:   %%objects empty_insert_order_set
  // 459:   %%libraries empty_insert_order_set
  // 460:   %%do_link false
  // 461:   %%last_modification_time undefined
  // 462:   %do_build_static_executable false
  // 463:   %main_filename meta_filename
  // 464:   %main_info stat(main_filename)
  // 465:   build_executable
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[10])->contents /* force_rebuild */;
  arguments->slots[1] = frame->slots[11] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__71_79;
}
static void entry__71_67(void) {
  allocate_initialized_frame_gc(5, 12);
  // slot allocations:
  // return__1: 0
  // meta_filename: 1
  // meta_path: 2
  // filename: 3
  // sim_filename: 4
  // orig_path: 5
  // out: 6
  // err: 7
  // success: 8
  frame->slots[0] /* return__1 */ = create_continuation();
  frame->slots[1] = myself->closure.frame->slots[4]; /* meta_filename */
  frame->slots[2] = myself->closure.frame->slots[2]; /* meta_path */
  frame->slots[3] = myself->closure.frame->slots[3]; /* filename */
  frame->slots[4] = myself->closure.frame->slots[6]; /* sim_filename */
  // _define %on_top_level false
  define__on_top_level(get_value_or_future__false());
  define__objects(undefined);
  define__libraries(undefined);
  define__do_link(undefined);
  define__last_modification_time(undefined);
  // _define %do_build_static_executable false
  define__do_build_static_executable(get_value_or_future__false());
  // _define %main_filename meta_filename
  define__main_filename(frame->slots[1] /* meta_filename */);
  define__main_info(create_future());
  frame->slots[5] /* orig_path */ = create_future();
  frame->slots[6] /* out */ = create_future();
  frame->slots[7] /* err */ = create_future();
  frame->slots[8] /* success */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 457: %on_top_level false
  initialize_maybe_future(get__on_top_level(), get__false());
  // 458: %%objects empty_insert_order_set
  set__objects(get__empty_insert_order_set());
  // 459: %%libraries empty_insert_order_set
  set__libraries(get__empty_insert_order_set());
  // 460: %%do_link false
  set__do_link(get__false());
  // 461: %%last_modification_time undefined
  set__last_modification_time(get__undefined());
  // 462: %do_build_static_executable false
  initialize_maybe_future(get__do_build_static_executable(), get__false());
  // 463: %main_filename meta_filename
  initialize_maybe_future(get__main_filename(), frame->slots[1] /* meta_filename */);
  // 464: %main_info stat(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__71_68;
}
static void cont__71_68(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(get__main_info(), arguments->slots[0]);
  // 465: build_executable
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._build_executable;
  func = myself->type;
  frame->cont = cont__71_69;
}
static void cont__71_69(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 466: $orig_path current_path()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__current_path();
  func = myself->type;
  frame->cont = cont__71_70;
}
static void cont__71_70(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* orig_path */, arguments->slots[0]);
  // 467: change_directory meta_path
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* meta_path */;
  result_count = 0;
  myself = get__change_directory();
  func = myself->type;
  frame->cont = cont__71_71;
}
static void cont__71_71(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 468: std::call $out $err $success filename
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* filename */;
  result_count = 3;
  myself = get__std__call();
  func = myself->type;
  frame->cont = cont__71_72;
}
static void cont__71_72(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  frame->slots[10] /* temp__2 */ = arguments->slots[1];
  frame->slots[11] /* temp__3 */ = arguments->slots[2];
  // 468: ... out
  initialize_future(frame->slots[6] /* out */, frame->slots[9] /* temp__1 */);
  // 468: ... err
  initialize_future(frame->slots[7] /* err */, frame->slots[10] /* temp__2 */);
  // 468: ... success
  initialize_future(frame->slots[8] /* success */, frame->slots[11] /* temp__3 */);
  // 469: change_directory orig_path
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* orig_path */;
  result_count = 0;
  myself = get__change_directory();
  func = myself->type;
  frame->cont = cont__71_73;
}
static void cont__71_73(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 470: ... : Error err.from_utf8
  frame->slots[9] /* temp__1 */ = create_closure(entry__71_74, 0);
  // 470: unless success: Error err.from_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* success */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__71_76;
}
static void entry__71_74(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // err: 0
  frame->slots[0] = myself->closure.frame->slots[7]; /* err */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 470: ... err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* err */;
  result_count = 1;
  myself = get__from_utf8();
  func = myself->type;
  frame->cont = cont__71_75;
}
static void cont__71_75(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 470: ... Error err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__71_76(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 471: ... out.to_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* out */;
  result_count = 1;
  myself = get__to_utf8();
  func = myself->type;
  frame->cont = cont__71_77;
}
static void cont__71_77(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 471: save sim_filename out.to_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* sim_filename */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__save();
  func = myself->type;
  frame->cont = cont__71_78;
}
static void cont__71_78(void) {
  myself = frame->slots[0] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__71_79(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 472: dec &meta_level
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* meta_level */;
  result_count = 1;
  myself = get__dec();
  func = myself->type;
  frame->cont = cont__71_80;
}
static void cont__71_80(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* meta_level */ = arguments->slots[0];
  // 473: ... meta_level > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* meta_level */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__71_81;
}
static void cont__71_81(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 473: -> meta_level > 0
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__71_1_compile_meta_module(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // mod_filename: 0
  // mod_name: 1
  // meta_level: 2
  if (argument_count != 3) {
    invalid_arguments_error();
    return;
  }
  frame->slots[2] /* meta_level */ = create_cell_with_contents(arguments->slots[2]);
  // 412: ... :
  // 413:   $meta_path truncate_from(mod_filename '/' -1)
  // 414:   $filename string(mod_filename dup(".meta" meta_level))
  // 415:   $meta_filename string(filename ".sim")
  // 416:   $meta_c_filename string(mod_filename dup(".meta" meta_level) ".c")
  // 417:   $sim_filename string(mod_filename dup(".meta" meta_level-1) ".sim")
  // 418:   $meta_info stat(meta_filename)
  // 419:   $sim_info stat(sim_filename)
  // 420:   $meta_c_info stat(meta_c_filename)
  // 421:   
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__71_2, 0);
  // 412: do_while:
  // 413:   $meta_path truncate_from(mod_filename '/' -1)
  // 414:   $filename string(mod_filename dup(".meta" meta_level))
  // 415:   $meta_filename string(filename ".sim")
  // 416:   $meta_c_filename string(mod_filename dup(".meta" meta_level) ".c")
  // 417:   $sim_filename string(mod_filename dup(".meta" meta_level-1) ".sim")
  // 418:   $meta_info stat(meta_filename)
  // 419:   $sim_info stat(sim_filename)
  // 420:   $meta_c_info stat(meta_c_filename)
  // 421:   
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__do_while();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__72_1_build_dependencies(void) {
  allocate_initialized_frame_gc(5, 6);
  // slot allocations:
  // mod_filename: 0
  // mod_name: 1
  // c_buf: 2
  // do_compile_c: 3
  // return: 4
  frame->slots[4] /* return */ = create_continuation();
  if (argument_count < 3) {
    too_few_arguments_error();
    return;
  }
  if (argument_count > 4) {
    too_many_arguments_error();
    return;
  }
  switch(argument_count) {
    default: frame->slots[3] /* do_compile_c */ = arguments->slots[3];
    case 3:;
  }
  switch(argument_count) {
    case 3: frame->slots[3] /* do_compile_c */ = get__true();
  }
  // 486: ... : ($line)
  // 487:   unless line .has_prefix. "/// " return
  // 488:   behind &line ' '
  // 489:   trim &line
  // 490:   $command line .truncate_from. WHITESPACE
  // 491:   $argument line .behind. WHITESPACE
  // 492:   case
  // 493:     command
  // 494:     "require":
  // 495:       if
  // ...
  frame->slots[5] /* temp__1 */ = create_closure(entry__72_2, 1);
  // 486: for_each_line c_buf: ($line)
  // 487:   unless line .has_prefix. "/// " return
  // 488:   behind &line ' '
  // 489:   trim &line
  // 490:   $command line .truncate_from. WHITESPACE
  // 491:   $argument line .behind. WHITESPACE
  // 492:   case
  // 493:     command
  // 494:     "require":
  // 495:       if
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* c_buf */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each_line();
  func = myself->type;
  frame->cont = cont__72_41;
}
static void entry__72_36(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // argument: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 514: ... !libraries(argument .truncate_from. '/') true
  frame->slots[1] /* temp__1 */ = get__true();
  // 514: ... argument .truncate_from. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* argument */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__72_37;
}
static void cont__72_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 514: ... !libraries(argument .truncate_from. '/')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__libraries();
  func = myself->type;
  frame->cont = cont__72_38;
}
static void cont__72_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__libraries(arguments->slots[0]);
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__72_30(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // argument: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 512: !libraries(string("sim-" argument .truncate_from. '/')) true
  frame->slots[1] /* temp__1 */ = get__true();
  // 512: ... argument .truncate_from. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* argument */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__72_31;
}
static void cont__72_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 512: ... string("sim-" argument .truncate_from. '/')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__72_32;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__72_33;
}
static void cont__72_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 512: !libraries(string("sim-" argument .truncate_from. '/'))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__libraries();
  func = myself->type;
  frame->cont = cont__72_34;
}
static void cont__72_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__libraries(arguments->slots[0]);
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__72_27(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // argument: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 509: ... resolve_filename(argument)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* argument */;
  result_count = 1;
  myself = var._resolve_filename;
  func = myself->type;
  frame->cont = cont__72_28;
}
static void cont__72_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 509: compile_module resolve_filename(argument) argument
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[0] /* argument */;
  result_count = frame->caller_result_count;
  myself = var._compile_module;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__72_29(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // do_compile_c: 0
  // argument: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* do_compile_c */
  frame->slots[1] = myself->closure.frame->slots[0]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 511: ... :
  // 512:   !libraries(string("sim-" argument .truncate_from. '/')) true
  frame->slots[2] /* temp__1 */ = create_closure(entry__72_30, 0);
  // 511: if do_compile_c:
  // 512:   !libraries(string("sim-" argument .truncate_from. '/')) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* do_compile_c */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__72_13(void) {
  allocate_initialized_frame_gc(3, 10);
  // slot allocations:
  // argument: 0
  // mod_filename: 1
  // mod_name: 2
  // req_name: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* argument */
  frame->slots[1] = myself->closure.frame->slots[1]; /* mod_filename */
  frame->slots[2] = myself->closure.frame->slots[2]; /* mod_name */
  frame->slots[3] /* req_name */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 498: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__72_14;
}
static void cont__72_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 498: $req_name range(argument 3 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* argument */;
  arguments->slots[1] = number__3;
  arguments->slots[2] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__72_15;
}
static void cont__72_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* req_name */, arguments->slots[0]);
  // 500: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__72_16;
}
static void cont__72_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 500: ... until(mod_filename '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* mod_filename */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count = 1;
  myself = get__until();
  func = myself->type;
  frame->cont = cont__72_17;
}
static void cont__72_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 500: string(until(mod_filename '/' -1) req_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* req_name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__72_18;
}
static void cont__72_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 501: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__72_19;
}
static void cont__72_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__6 */ = arguments->slots[0];
  // 501: ... until(mod_name '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* mod_name */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[9] /* temp__6 */;
  result_count = 1;
  myself = get__until();
  func = myself->type;
  frame->cont = cont__72_20;
}
static void cont__72_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__5 */ = arguments->slots[0];
  // 501: string(until(mod_name '/' -1) req_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__5 */;
  arguments->slots[1] = frame->slots[3] /* req_name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__72_21;
}
static void cont__72_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__4 */ = arguments->slots[0];
  // 499: compile_module
  // 500:   string(until(mod_filename '/' -1) req_name)
  // 501:   string(until(mod_name '/' -1) req_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = var._compile_module;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__72_11(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // argument: 0
  // mod_filename: 1
  // mod_name: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* argument */
  frame->slots[1] = myself->closure.frame->slots[1]; /* mod_filename */
  frame->slots[2] = myself->closure.frame->slots[2]; /* mod_name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 497: ... mode == EXE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__mode();
  arguments->slots[1] = var._EXE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__72_12;
}
static void cont__72_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 497: ... :
  // 498:   $req_name range(argument 3 -1)
  // 499:   compile_module
  // 500:     string(until(mod_filename '/' -1) req_name)
  // 501:     string(until(mod_name '/' -1) req_name)
  frame->slots[4] /* temp__2 */ = create_closure(entry__72_13, 0);
  // 497: if mode == EXE:
  // 498:   $req_name range(argument 3 -1)
  // 499:   compile_module
  // 500:     string(until(mod_filename '/' -1) req_name)
  // 501:     string(until(mod_name '/' -1) req_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__72_22(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // argument: 0
  // do_compile_c: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* argument */
  frame->slots[1] = myself->closure.frame->slots[3]; /* do_compile_c */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_build_static_executable();
  arguments->slots[1] = func__72_23;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__72_26;
}
static void entry__72_23(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_build_codeblocks_project;
  arguments->slots[1] = func__72_24;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__72_25;
}
static void entry__72_24(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 507: do_list_dependencies
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._do_list_dependencies;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__72_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__72_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 508: :
  // 509:   compile_module resolve_filename(argument) argument
  frame->slots[3] /* temp__2 */ = create_closure(entry__72_27, 0);
  // 510: :
  // 511:   if do_compile_c:
  // 512:     !libraries(string("sim-" argument .truncate_from. '/')) true
  frame->slots[4] /* temp__3 */ = create_closure(entry__72_29, 0);
  // 503: if
  // 504:   ||
  // 505:     do_build_static_executable
  // 506:     do_build_codeblocks_project
  // 507:     do_list_dependencies
  // 508:   :
  // 509:     compile_module resolve_filename(argument) argument
  // 510:   :
  // 511:     if do_compile_c:
  // 512:       !libraries(string("sim-" argument .truncate_from. '/')) true
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
static void entry__72_9(void) {
  allocate_initialized_frame_gc(4, 7);
  // slot allocations:
  // argument: 0
  // mod_filename: 1
  // mod_name: 2
  // do_compile_c: 3
  frame->slots[0] = myself->closure.frame->slots[6]; /* argument */
  frame->slots[1] = myself->closure.frame->slots[2]; /* mod_filename */
  frame->slots[2] = myself->closure.frame->slots[3]; /* mod_name */
  frame->slots[3] = myself->closure.frame->slots[4]; /* do_compile_c */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 496: argument .has_prefix. "./"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* argument */;
  arguments->slots[1] = string__71_56;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__72_10;
}
static void cont__72_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 496: ... :
  // 497:   if mode == EXE:
  // 498:     $req_name range(argument 3 -1)
  // 499:     compile_module
  // 500:       string(until(mod_filename '/' -1) req_name)
  // 501:       string(until(mod_name '/' -1) req_name)
  frame->slots[5] /* temp__2 */ = create_closure(entry__72_11, 0);
  // 502: :
  // 503:   if
  // 504:     ||
  // 505:       do_build_static_executable
  // 506:       do_build_codeblocks_project
  // 507:       do_list_dependencies
  // 508:     :
  // 509:       compile_module resolve_filename(argument) argument
  // 510:     :
  // 511:       if do_compile_c:
  // ...
  frame->slots[6] /* temp__3 */ = create_closure(entry__72_22, 0);
  // 495: if
  // 496:   argument .has_prefix. "./":
  // 497:     if mode == EXE:
  // 498:       $req_name range(argument 3 -1)
  // 499:       compile_module
  // 500:         string(until(mod_filename '/' -1) req_name)
  // 501:         string(until(mod_name '/' -1) req_name)
  // 502:   :
  // 503:     if
  // 504:       ||
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
static void entry__72_35(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // do_compile_c: 0
  // argument: 1
  frame->slots[0] = myself->closure.frame->slots[4]; /* do_compile_c */
  frame->slots[1] = myself->closure.frame->slots[6]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 514: ... : !libraries(argument .truncate_from. '/') true
  frame->slots[2] /* temp__1 */ = create_closure(entry__72_36, 0);
  // 514: if do_compile_c: !libraries(argument .truncate_from. '/') true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* do_compile_c */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__72_2(void) {
  allocate_initialized_frame_gc(5, 9);
  // slot allocations:
  // line: 0
  // return: 1
  // mod_filename: 2
  // mod_name: 3
  // do_compile_c: 4
  // command: 5
  // argument: 6
  frame->slots[1] = myself->closure.frame->slots[4]; /* return */
  frame->slots[2] = myself->closure.frame->slots[0]; /* mod_filename */
  frame->slots[3] = myself->closure.frame->slots[1]; /* mod_name */
  frame->slots[4] = myself->closure.frame->slots[3]; /* do_compile_c */
  frame->slots[5] /* command */ = create_future();
  frame->slots[6] /* argument */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* line */ = create_cell_with_contents(arguments->slots[0]);
  // 487: ... line .has_prefix. "/// "
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  arguments->slots[1] = string__71_46;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__72_3;
}
static void cont__72_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 487: unless line .has_prefix. "/// " return
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* return */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__72_4;
}
static void cont__72_4(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 488: behind &line ' '
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  arguments->slots[1] = character__32;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__72_5;
}
static void cont__72_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* line */ = arguments->slots[0];
  // 489: trim &line
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__72_6;
}
static void cont__72_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* line */ = arguments->slots[0];
  // 490: $command line .truncate_from. WHITESPACE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  arguments->slots[1] = var._WHITESPACE;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__72_7;
}
static void cont__72_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* command */, arguments->slots[0]);
  // 491: $argument line .behind. WHITESPACE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  arguments->slots[1] = var._WHITESPACE;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__72_8;
}
static void cont__72_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* argument */, arguments->slots[0]);
  // 494: ... :
  // 495:   if
  // 496:     argument .has_prefix. "./":
  // 497:       if mode == EXE:
  // 498:         $req_name range(argument 3 -1)
  // 499:         compile_module
  // 500:           string(until(mod_filename '/' -1) req_name)
  // 501:           string(until(mod_name '/' -1) req_name)
  // 502:     :
  // 503:       if
  // ...
  frame->slots[7] /* temp__1 */ = create_closure(entry__72_9, 0);
  // 513: ... :
  // 514:   if do_compile_c: !libraries(argument .truncate_from. '/') true
  frame->slots[8] /* temp__2 */ = create_closure(entry__72_35, 0);
  // 492: case
  // 493:   command
  // 494:   "require":
  // 495:     if
  // 496:       argument .has_prefix. "./":
  // 497:         if mode == EXE:
  // 498:           $req_name range(argument 3 -1)
  // 499:           compile_module
  // 500:             string(until(mod_filename '/' -1) req_name)
  // 501:             string(until(mod_name '/' -1) req_name)
  // ...
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* command */;
  arguments->slots[1] = string__72_39;
  arguments->slots[2] = frame->slots[7] /* temp__1 */;
  arguments->slots[3] = string__72_40;
  arguments->slots[4] = frame->slots[8] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__72_41(void) {
  myself = frame->slots[4] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__73_1_compile_module(void) {
  allocate_initialized_frame_gc(3, 9);
  // slot allocations:
  // mod_filename: 0
  // mod_name: 1
  // return: 2
  // compile_submodule: 3
  // mod_info: 4
  // o_filename: 5
  frame->slots[2] /* return */ = create_continuation();
  frame->slots[3] /* compile_submodule */ = create_future();
  frame->slots[4] /* mod_info */ = create_future();
  frame->slots[5] /* o_filename */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 525: ... :
  // 526:   (
  // 527:     submodule_names # no paths; no extensions
  // 528:     do_compile_c = true
  // 529:     suffix = "" # a hyphen followed by the platform name
  // 530:   )
  // 531:   $$modification_time undefined
  // 532:   $$sim_filenames empty_list
  // 533:   for_each submodule_names: (submodule_name)
  // 534:     $meta_level meta_levels(submodule_name)
  // ...
  frame->slots[6] /* temp__1 */ = create_closure(entry__73_2_compile_submodule, -1);
  // 525: $compile_submodule:
  // 526:   (
  // 527:     submodule_names # no paths; no extensions
  // 528:     do_compile_c = true
  // 529:     suffix = "" # a hyphen followed by the platform name
  // 530:   )
  // 531:   $$modification_time undefined
  // 532:   $$sim_filenames empty_list
  // 533:   for_each submodule_names: (submodule_name)
  // 534:     $meta_level meta_levels(submodule_name)
  // ...
  initialize_future(frame->slots[3] /* compile_submodule */, frame->slots[6] /* temp__1 */);
  // 581: lookup $mod_info mod_filename mod_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = frame->slots[1] /* mod_name */;
  result_count = 1;
  myself = var._lookup;
  func = myself->type;
  frame->cont = cont__73_73;
}
static void entry__73_2_compile_submodule(void) {
  allocate_initialized_frame_gc(6, 15);
  // slot allocations:
  // submodule_names: 0
  // do_compile_c: 1
  // suffix: 2
  // mod_filename: 3
  // mod_name: 4
  // o_filename: 5
  // modification_time: 6
  // sim_filenames: 7
  // c_filename: 8
  // c_info: 9
  // c_buf: 10
  frame->slots[3] = myself->closure.frame->slots[0]; /* mod_filename */
  frame->slots[4] = myself->closure.frame->slots[1]; /* mod_name */
  frame->slots[5] = myself->closure.frame->slots[5]; /* o_filename */
  frame->slots[6] /* modification_time */ = create_cell();
  frame->slots[7] /* sim_filenames */ = create_cell();
  frame->slots[8] /* c_filename */ = create_future();
  frame->slots[9] /* c_info */ = create_future();
  frame->slots[10] /* c_buf */ = create_cell();
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  if (argument_count > 3) {
    too_many_arguments_error();
    return;
  }
  switch(argument_count) {
    default: frame->slots[2] /* suffix */ = arguments->slots[2];
    case 2: frame->slots[1] /* do_compile_c */ = arguments->slots[1];
    case 1:;
  }
  switch(argument_count) {
    case 1: frame->slots[1] /* do_compile_c */ = get__true();
    case 2: frame->slots[2] /* suffix */ = empty_string;
  }
  // 531: $$modification_time undefined
  ((CELL *)frame->slots[6])->contents /* modification_time */ = get__undefined();
  // 532: $$sim_filenames empty_list
  ((CELL *)frame->slots[7])->contents /* sim_filenames */ = get__empty_list();
  // 533: ... : (submodule_name)
  // 534:   $meta_level meta_levels(submodule_name)
  // 535:   $submodule_filename string(until(mod_filename '/' -1) submodule_name)
  // 536:   if meta_level > 0 && not(do_omit_meta):
  // 537:     compile_meta_module submodule_filename submodule_name meta_level
  // 538:   $sim_filename string(submodule_filename ".sim")
  // 539:   push &sim_filenames sim_filename
  // 540:   $sim_info stat(sim_filename)
  // 541:   if
  // 542:     ||
  // ...
  frame->slots[11] /* temp__1 */ = create_closure(entry__73_3, 1);
  // 533: for_each submodule_names: (submodule_name)
  // 534:   $meta_level meta_levels(submodule_name)
  // 535:   $submodule_filename string(until(mod_filename '/' -1) submodule_name)
  // 536:   if meta_level > 0 && not(do_omit_meta):
  // 537:     compile_meta_module submodule_filename submodule_name meta_level
  // 538:   $sim_filename string(submodule_filename ".sim")
  // 539:   push &sim_filenames sim_filename
  // 540:   $sim_info stat(sim_filename)
  // 541:   if
  // 542:     ||
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* submodule_names */;
  arguments->slots[1] = frame->slots[11] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__73_24;
}
static void entry__73_22(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // modification_time: 0
  // sim_info: 1
  frame->slots[0] = myself->closure.frame->slots[3]; /* modification_time */
  frame->slots[1] = myself->closure.frame->slots[7]; /* sim_info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 546: !modification_time modification_time_of(sim_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* sim_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__73_23;
}
static void cont__73_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* modification_time */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__73_3(void) {
  allocate_initialized_frame_gc(4, 12);
  // slot allocations:
  // submodule_name: 0
  // mod_filename: 1
  // sim_filenames: 2
  // modification_time: 3
  // meta_level: 4
  // submodule_filename: 5
  // sim_filename: 6
  // sim_info: 7
  frame->slots[1] = myself->closure.frame->slots[3]; /* mod_filename */
  frame->slots[2] = myself->closure.frame->slots[7]; /* sim_filenames */
  frame->slots[3] = myself->closure.frame->slots[6]; /* modification_time */
  frame->slots[4] /* meta_level */ = create_future();
  frame->slots[5] /* submodule_filename */ = create_future();
  frame->slots[6] /* sim_filename */ = create_future();
  frame->slots[7] /* sim_info */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 534: $meta_level meta_levels(submodule_name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* submodule_name */;
  result_count = 1;
  myself = var._meta_levels;
  func = myself->type;
  frame->cont = cont__73_4;
}
static void cont__73_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* meta_level */, arguments->slots[0]);
  // 535: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__73_5;
}
static void cont__73_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__2 */ = arguments->slots[0];
  // 535: ... until(mod_filename '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* mod_filename */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[9] /* temp__2 */;
  result_count = 1;
  myself = get__until();
  func = myself->type;
  frame->cont = cont__73_6;
}
static void cont__73_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 535: $submodule_filename string(until(mod_filename '/' -1) submodule_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = frame->slots[0] /* submodule_name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__73_7;
}
static void cont__73_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* submodule_filename */, arguments->slots[0]);
  // 536: ... meta_level > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = frame->slots[4] /* meta_level */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__73_8;
}
static void cont__73_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__2 */ = arguments->slots[0];
  // 536: ... meta_level > 0 && not(do_omit_meta)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__2 */;
  arguments->slots[1] = func__73_9;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__73_11;
}
static void entry__73_9(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 536: ... not(do_omit_meta)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._do_omit_meta;
  result_count = 1;
  myself = get__not();
  func = myself->type;
  frame->cont = cont__73_10;
}
static void cont__73_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 536: ... not(do_omit_meta)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__73_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 536: ... :
  // 537:   compile_meta_module submodule_filename submodule_name meta_level
  frame->slots[10] /* temp__3 */ = create_closure(entry__73_12, 0);
  // 536: if meta_level > 0 && not(do_omit_meta):
  // 537:   compile_meta_module submodule_filename submodule_name meta_level
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__73_13;
}
static void entry__73_12(void) {
  allocate_initialized_frame_gc(3, 3);
  // slot allocations:
  // submodule_filename: 0
  // submodule_name: 1
  // meta_level: 2
  frame->slots[0] = myself->closure.frame->slots[5]; /* submodule_filename */
  frame->slots[1] = myself->closure.frame->slots[0]; /* submodule_name */
  frame->slots[2] = myself->closure.frame->slots[4]; /* meta_level */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 537: compile_meta_module submodule_filename submodule_name meta_level
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* submodule_filename */;
  arguments->slots[1] = frame->slots[1] /* submodule_name */;
  arguments->slots[2] = frame->slots[2] /* meta_level */;
  result_count = frame->caller_result_count;
  myself = var._compile_meta_module;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__73_13(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 538: $sim_filename string(submodule_filename ".sim")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* submodule_filename */;
  arguments->slots[1] = string__67_13;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__73_14;
}
static void cont__73_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* sim_filename */, arguments->slots[0]);
  // 539: push &sim_filenames sim_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* sim_filenames */;
  arguments->slots[1] = frame->slots[6] /* sim_filename */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__73_15;
}
static void cont__73_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* sim_filenames */ = arguments->slots[0];
  // 540: $sim_info stat(sim_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* sim_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__73_16;
}
static void cont__73_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[7] /* sim_info */, arguments->slots[0]);
  // 543: modification_time.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* modification_time */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__73_17;
}
static void cont__73_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__2 */ = arguments->slots[0];
  // 544: modification_time_of(sim_info) > modification_time
  frame->slots[10] /* temp__3 */ = create_closure(entry__73_18, 0);
  // 542: ||
  // 543:   modification_time.is_undefined
  // 544:   modification_time_of(sim_info) > modification_time
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__2 */;
  arguments->slots[1] = frame->slots[10] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__73_21;
}
static void entry__73_18(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // modification_time: 0
  // sim_info: 1
  frame->slots[0] = myself->closure.frame->slots[3]; /* modification_time */
  frame->slots[1] = myself->closure.frame->slots[7]; /* sim_info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 544: modification_time_of(sim_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* sim_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__73_19;
}
static void cont__73_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 544: modification_time_of(sim_info) > modification_time
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* modification_time */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__73_20;
}
static void cont__73_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 544: modification_time_of(sim_info) > modification_time
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__73_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 545: :
  // 546:   !modification_time modification_time_of(sim_info)
  frame->slots[11] /* temp__4 */ = create_closure(entry__73_22, 0);
  // 541: if
  // 542:   ||
  // 543:     modification_time.is_undefined
  // 544:     modification_time_of(sim_info) > modification_time
  // 545:   :
  // 546:     !modification_time modification_time_of(sim_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = frame->slots[11] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__73_24(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 547: $c_filename string(mod_filename suffix ".c")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* mod_filename */;
  arguments->slots[1] = frame->slots[2] /* suffix */;
  arguments->slots[2] = string__71_9;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__73_25;
}
static void cont__73_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[8] /* c_filename */, arguments->slots[0]);
  // 548: $c_info stat(c_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* c_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__73_26;
}
static void cont__73_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[9] /* c_info */, arguments->slots[0]);
  // 549: ... : !c_sources(c_filename) true
  frame->slots[11] /* temp__1 */ = create_closure(entry__73_27, 0);
  // 549: if do_compile_c: !c_sources(c_filename) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* do_compile_c */;
  arguments->slots[1] = frame->slots[11] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__73_29;
}
static void entry__73_27(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // c_filename: 0
  frame->slots[0] = myself->closure.frame->slots[8]; /* c_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 549: ... !c_sources(c_filename) true
  frame->slots[1] /* temp__1 */ = get__true();
  // 549: ... !c_sources(c_filename)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_filename */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = var._c_sources;
  func = myself->type;
  frame->cont = cont__73_28;
}
static void cont__73_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._c_sources = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__73_29(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 550: $$c_buf undefined
  ((CELL *)frame->slots[10])->contents /* c_buf */ = get__undefined();
  frame->slots[12] /* temp__2 */ = create_closure(entry__73_30, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_rebuild;
  arguments->slots[1] = frame->slots[12] /* temp__2 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__73_36;
}
static void entry__73_30(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // c_info: 0
  // modification_time: 1
  frame->slots[0] = myself->closure.frame->slots[9]; /* c_info */
  frame->slots[1] = myself->closure.frame->slots[6]; /* modification_time */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 554: c_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__73_31;
}
static void cont__73_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 555: modification_time > modification_time_of(c_info)
  frame->slots[4] /* temp__3 */ = create_closure(entry__73_32, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__73_35;
}
static void entry__73_32(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // c_info: 0
  // modification_time: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* c_info */
  frame->slots[1] = myself->closure.frame->slots[1]; /* modification_time */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 555: ... modification_time_of(c_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__73_33;
}
static void cont__73_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 555: modification_time > modification_time_of(c_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* modification_time */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__73_34;
}
static void cont__73_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 555: modification_time > modification_time_of(c_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__73_35(void) {
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
static void cont__73_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 556: :
  // 557:   %sim2c::module_name replace_all(mod_name '/' = "__" '.' = "__")
  // 558:   if verbose: ewriteln "build module " module_name suffix
  // 559:   collect_output $c_source: sim2c sim_filenames
  // 560:   collect_output !c_buf: create_imports c_source
  // 561:   save c_filename c_buf.to_utf8
  // 562:   if do_compile_c: compile_c c_filename o_filename
  frame->slots[13] /* temp__3 */ = create_closure(entry__73_37, 0);
  // 563: :
  // 564:   load !c_buf c_filename
  // 565:   $o_info stat(o_filename)
  // 566:   if
  // 567:     ||
  // 568:       o_info.is_undefined
  // 569:       modification_time_of(c_info) > modification_time_of(o_info)
  // 570:     :
  // 571:       if do_compile_c: compile_c c_filename o_filename
  // 572:     :
  // ...
  frame->slots[14] /* temp__4 */ = create_closure(entry__73_53, 0);
  // 551: if
  // 552:   ||
  // 553:     do_rebuild
  // 554:     c_info.is_undefined
  // 555:     modification_time > modification_time_of(c_info)
  // 556:   :
  // 557:     %sim2c::module_name replace_all(mod_name '/' = "__" '.' = "__")
  // 558:     if verbose: ewriteln "build module " module_name suffix
  // 559:     collect_output $c_source: sim2c sim_filenames
  // 560:     collect_output !c_buf: create_imports c_source
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  arguments->slots[1] = frame->slots[13] /* temp__3 */;
  arguments->slots[2] = frame->slots[14] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__73_72;
}
static void entry__73_70(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // o_info: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* o_info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 578: !last_modification_time modification_time_of(o_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* o_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__73_71;
}
static void cont__73_71(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__last_modification_time(arguments->slots[0]);
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__73_63(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // c_filename: 0
  // o_filename: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* c_filename */
  frame->slots[1] = myself->closure.frame->slots[2]; /* o_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 571: ... compile_c c_filename o_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_filename */;
  arguments->slots[1] = frame->slots[1] /* o_filename */;
  result_count = frame->caller_result_count;
  myself = var._compile_c;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__73_62(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // do_compile_c: 0
  // c_filename: 1
  // o_filename: 2
  frame->slots[0] = myself->closure.frame->slots[4]; /* do_compile_c */
  frame->slots[1] = myself->closure.frame->slots[1]; /* c_filename */
  frame->slots[2] = myself->closure.frame->slots[2]; /* o_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 571: ... : compile_c c_filename o_filename
  frame->slots[3] /* temp__1 */ = create_closure(entry__73_63, 0);
  // 571: if do_compile_c: compile_c c_filename o_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* do_compile_c */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__73_64(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // o_info: 0
  frame->slots[0] = myself->closure.frame->slots[5]; /* o_info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 575: last_modification_time.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__last_modification_time();
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__73_65;
}
static void cont__73_65(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 576: modification_time_of(o_info) > last_modification_time
  frame->slots[3] /* temp__3 */ = create_closure(entry__73_66, 0);
  // 574: ||
  // 575:   last_modification_time.is_undefined
  // 576:   modification_time_of(o_info) > last_modification_time
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__73_69;
}
static void entry__73_66(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // o_info: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* o_info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 576: modification_time_of(o_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* o_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__73_67;
}
static void cont__73_67(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 576: modification_time_of(o_info) > last_modification_time
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__last_modification_time();
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__73_68;
}
static void cont__73_68(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 576: modification_time_of(o_info) > last_modification_time
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__73_69(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 577: :
  // 578:   !last_modification_time modification_time_of(o_info)
  frame->slots[4] /* temp__4 */ = create_closure(entry__73_70, 0);
  // 573: if
  // 574:   ||
  // 575:     last_modification_time.is_undefined
  // 576:     modification_time_of(o_info) > last_modification_time
  // 577:   :
  // 578:     !last_modification_time modification_time_of(o_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__73_37(void) {
  allocate_initialized_frame_gc(8, 11);
  // slot allocations:
  // return__1: 0
  // mod_name: 1
  // suffix: 2
  // sim_filenames: 3
  // c_buf: 4
  // c_filename: 5
  // do_compile_c: 6
  // o_filename: 7
  // c_source: 8
  frame->slots[0] /* return__1 */ = create_continuation();
  frame->slots[1] = myself->closure.frame->slots[4]; /* mod_name */
  frame->slots[2] = myself->closure.frame->slots[2]; /* suffix */
  frame->slots[3] = myself->closure.frame->slots[7]; /* sim_filenames */
  frame->slots[4] = myself->closure.frame->slots[10]; /* c_buf */
  frame->slots[5] = myself->closure.frame->slots[8]; /* c_filename */
  frame->slots[6] = myself->closure.frame->slots[1]; /* do_compile_c */
  frame->slots[7] = myself->closure.frame->slots[5]; /* o_filename */
  define__sim2c__module_name(create_future());
  frame->slots[8] /* c_source */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 557: ... '/' = "__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = string__73_38;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__73_39;
}
static void cont__73_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 557: ... '.' = "__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__46;
  arguments->slots[1] = string__73_38;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__73_40;
}
static void cont__73_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__2 */ = arguments->slots[0];
  // 557: %sim2c::module_name replace_all(mod_name '/' = "__" '.' = "__")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* mod_name */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  arguments->slots[2] = frame->slots[10] /* temp__2 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__73_41;
}
static void cont__73_41(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(get__sim2c__module_name(), arguments->slots[0]);
  // 558: ... : ewriteln "build module " module_name suffix
  frame->slots[9] /* temp__1 */ = create_closure(entry__73_42, 0);
  // 558: if verbose: ewriteln "build module " module_name suffix
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__73_44;
}
static void entry__73_42(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // suffix: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* suffix */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 558: ... ewriteln "build module " module_name suffix
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__73_43;
  arguments->slots[1] = get__module_name();
  arguments->slots[2] = frame->slots[0] /* suffix */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__73_44(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 559: ... : sim2c sim_filenames
  frame->slots[9] /* temp__1 */ = create_closure(entry__73_45, 0);
  // 559: collect_output $c_source: sim2c sim_filenames
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__73_46;
}
static void entry__73_45(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // sim_filenames: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* sim_filenames */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 559: ... sim2c sim_filenames
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* sim_filenames */;
  result_count = frame->caller_result_count;
  myself = get__sim2c();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__73_46(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[8] /* c_source */, arguments->slots[0]);
  // 560: ... : create_imports c_source
  frame->slots[9] /* temp__1 */ = create_closure(entry__73_47, 0);
  // 560: collect_output !c_buf: create_imports c_source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__73_48;
}
static void entry__73_47(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // c_source: 0
  frame->slots[0] = myself->closure.frame->slots[8]; /* c_source */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 560: ... create_imports c_source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_source */;
  result_count = frame->caller_result_count;
  myself = var._create_imports;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__73_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* c_buf */ = arguments->slots[0];
  // 561: ... c_buf.to_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* c_buf */;
  result_count = 1;
  myself = get__to_utf8();
  func = myself->type;
  frame->cont = cont__73_49;
}
static void cont__73_49(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 561: save c_filename c_buf.to_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* c_filename */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 0;
  myself = get__save();
  func = myself->type;
  frame->cont = cont__73_50;
}
static void cont__73_50(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 562: ... : compile_c c_filename o_filename
  frame->slots[9] /* temp__1 */ = create_closure(entry__73_51, 0);
  // 562: if do_compile_c: compile_c c_filename o_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* do_compile_c */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__73_52;
}
static void entry__73_51(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // c_filename: 0
  // o_filename: 1
  frame->slots[0] = myself->closure.frame->slots[5]; /* c_filename */
  frame->slots[1] = myself->closure.frame->slots[7]; /* o_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 562: ... compile_c c_filename o_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_filename */;
  arguments->slots[1] = frame->slots[1] /* o_filename */;
  result_count = frame->caller_result_count;
  myself = var._compile_c;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__73_52(void) {
  myself = frame->slots[0] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__73_53(void) {
  allocate_initialized_frame_gc(5, 11);
  // slot allocations:
  // c_buf: 0
  // c_filename: 1
  // o_filename: 2
  // c_info: 3
  // do_compile_c: 4
  // o_info: 5
  frame->slots[0] = myself->closure.frame->slots[10]; /* c_buf */
  frame->slots[1] = myself->closure.frame->slots[8]; /* c_filename */
  frame->slots[2] = myself->closure.frame->slots[5]; /* o_filename */
  frame->slots[3] = myself->closure.frame->slots[9]; /* c_info */
  frame->slots[4] = myself->closure.frame->slots[1]; /* do_compile_c */
  frame->slots[5] /* o_info */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 564: load !c_buf c_filename
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* c_filename */;
  result_count = 1;
  myself = get__load();
  func = myself->type;
  frame->cont = cont__73_54;
}
static void cont__73_54(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* c_buf */ = arguments->slots[0];
  // 565: $o_info stat(o_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* o_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__73_55;
}
static void cont__73_55(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* o_info */, arguments->slots[0]);
  // 568: o_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* o_info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__73_56;
}
static void cont__73_56(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 569: modification_time_of(c_info) > modification_time_of(o_info)
  frame->slots[8] /* temp__3 */ = create_closure(entry__73_57, 0);
  // 567: ||
  // 568:   o_info.is_undefined
  // 569:   modification_time_of(c_info) > modification_time_of(o_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  arguments->slots[1] = frame->slots[8] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__73_61;
}
static void entry__73_57(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // o_info: 0
  // c_info: 1
  frame->slots[0] = myself->closure.frame->slots[5]; /* o_info */
  frame->slots[1] = myself->closure.frame->slots[3]; /* c_info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 569: ... modification_time_of(o_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* o_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__73_58;
}
static void cont__73_58(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 569: modification_time_of(c_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* c_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__73_59;
}
static void cont__73_59(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 569: modification_time_of(c_info) > modification_time_of(o_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__73_60;
}
static void cont__73_60(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 569: modification_time_of(c_info) > modification_time_of(o_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__73_61(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 570: :
  // 571:   if do_compile_c: compile_c c_filename o_filename
  frame->slots[9] /* temp__4 */ = create_closure(entry__73_62, 0);
  // 572: :
  // 573:   if
  // 574:     ||
  // 575:       last_modification_time.is_undefined
  // 576:       modification_time_of(o_info) > last_modification_time
  // 577:     :
  // 578:       !last_modification_time modification_time_of(o_info)
  frame->slots[10] /* temp__5 */ = create_closure(entry__73_64, 0);
  // 566: if
  // 567:   ||
  // 568:     o_info.is_undefined
  // 569:     modification_time_of(c_info) > modification_time_of(o_info)
  // 570:   :
  // 571:     if do_compile_c: compile_c c_filename o_filename
  // 572:   :
  // 573:     if
  // 574:       ||
  // 575:         last_modification_time.is_undefined
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__4 */;
  arguments->slots[2] = frame->slots[10] /* temp__5 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__73_72(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 579: build_dependencies mod_filename mod_name c_buf do_compile_c
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* mod_filename */;
  arguments->slots[1] = frame->slots[4] /* mod_name */;
  arguments->slots[2] = ((CELL *)frame->slots[10])->contents /* c_buf */;
  arguments->slots[3] = frame->slots[1] /* do_compile_c */;
  result_count = frame->caller_result_count;
  myself = var._build_dependencies;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__73_73(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* mod_info */, arguments->slots[0]);
  // 582: ... mod_info.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* mod_info */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__73_74;
}
static void cont__73_74(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 582: ... :
  // 583:   Error "
  // 584:     No source file(s) for module "@(mod_name)" found!@
  frame->slots[7] /* temp__2 */ = create_closure(entry__73_75, 0);
  // 582: unless mod_info.is_defined:
  // 583:   Error "
  // 584:     No source file(s) for module "@(mod_name)" found!@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__73_79;
}
static void entry__73_75(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // mod_name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* mod_name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 583: ... "
  // 584:   No source file(s) for module "@(mod_name)" found!@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__73_76;
  arguments->slots[1] = frame->slots[0] /* mod_name */;
  arguments->slots[2] = string__73_77;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__73_78;
}
static void cont__73_78(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 583: Error "
  // 584:   No source file(s) for module "@(mod_name)" found!@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__73_79(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 585: $o_filename append(mod_filename ".o")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = string__73_80;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__73_81;
}
static void cont__73_81(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* o_filename */, arguments->slots[0]);
  // 586: ... objects(o_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* o_filename */;
  result_count = 1;
  myself = get__objects();
  func = myself->type;
  frame->cont = cont__73_82;
}
static void cont__73_82(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 586: if objects(o_filename) return
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* return */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__73_83;
}
static void cont__73_83(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 587: !objects(o_filename) true
  frame->slots[6] /* temp__1 */ = get__true();
  // 587: !objects(o_filename)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* o_filename */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = get__objects();
  func = myself->type;
  frame->cont = cont__73_84;
}
static void cont__73_84(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__objects(arguments->slots[0]);
  // 589: mod_info.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* mod_info */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__73_85;
}
static void cont__73_85(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 589: ... :
  // 590:   compile_submodule list(truncate_until(mod_name '/' -1))
  // 591:   if do_list_dependencies: push &dependencies string(mod_filename ".c")
  frame->slots[7] /* temp__2 */ = create_closure(entry__73_86, 0);
  // 592: :
  // 593:   do:
  // 594:     $$best_platform undefined
  // 595:     $$best_priority 999
  // 596:     for_each mod_info: (platform _filenames)
  // 597:       $priority platform_priority(platform)
  // 598:       if priority.is_defined && priority < best_priority:
  // 599:         !best_platform platform
  // 600:         !best_priority priority
  // 601:     for_each mod_info: (platform filenames)
  // ...
  frame->slots[8] /* temp__3 */ = create_closure(entry__73_94, 0);
  // 588: if
  // 589:   mod_info.is_empty:
  // 590:     compile_submodule list(truncate_until(mod_name '/' -1))
  // 591:     if do_list_dependencies: push &dependencies string(mod_filename ".c")
  // 592:   :
  // 593:     do:
  // 594:       $$best_platform undefined
  // 595:       $$best_priority 999
  // 596:       for_each mod_info: (platform _filenames)
  // 597:         $priority platform_priority(platform)
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  arguments->slots[2] = frame->slots[8] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__73_135;
}
static void entry__73_125(void) {
  allocate_initialized_frame_gc(4, 8);
  // slot allocations:
  // platform: 0
  // filenames: 1
  // mod_filename: 2
  // used_by: 3
  // dependency: 4
  // platforms: 5
  frame->slots[2] = myself->closure.frame->slots[1]; /* mod_filename */
  frame->slots[3] = myself->closure.frame->slots[2]; /* used_by */
  frame->slots[4] /* dependency */ = create_cell();
  frame->slots[5] /* platforms */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 621: $$dependency string(mod_filename "-" platform ".c")
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* mod_filename */;
  arguments->slots[1] = string__67_46;
  arguments->slots[2] = frame->slots[0] /* platform */;
  arguments->slots[3] = string__71_9;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__73_126;
}
static void cont__73_126(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* dependency */ = arguments->slots[0];
  // 622: $platforms used_by(platform)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* platform */;
  result_count = 1;
  myself = ((CELL *)frame->slots[3])->contents /* used_by */;
  func = myself->type;
  frame->cont = cont__73_127;
}
static void cont__73_127(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* platforms */, arguments->slots[0]);
  // 623: ... platforms.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* platforms */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__73_128;
}
static void cont__73_128(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 623: ... :
  // 624:   for_each platforms: (plat) write_to &dependency " #" plat
  frame->slots[7] /* temp__2 */ = create_closure(entry__73_129, 0);
  // 623: if platforms.is_defined:
  // 624:   for_each platforms: (plat) write_to &dependency " #" plat
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__73_133;
}
static void entry__73_130(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // plat: 0
  // dependency: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* dependency */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 624: ... write_to &dependency " #" plat
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* dependency */;
  arguments->slots[1] = string__73_131;
  arguments->slots[2] = frame->slots[0] /* plat */;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__73_132;
}
static void cont__73_132(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* dependency */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__73_129(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // platforms: 0
  // dependency: 1
  frame->slots[0] = myself->closure.frame->slots[5]; /* platforms */
  frame->slots[1] = myself->closure.frame->slots[4]; /* dependency */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 624: ... : (plat) write_to &dependency " #" plat
  frame->slots[2] /* temp__1 */ = create_closure(entry__73_130, 1);
  // 624: for_each platforms: (plat) write_to &dependency " #" plat
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* platforms */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__73_133(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 625: push &dependencies dependency
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._dependencies;
  arguments->slots[1] = ((CELL *)frame->slots[4])->contents /* dependency */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__73_134;
}
static void cont__73_134(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._dependencies = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__73_108(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // mod_info: 0
  // mod_filename: 1
  // used_by: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* mod_info */
  frame->slots[1] = myself->closure.frame->slots[2]; /* mod_filename */
  frame->slots[2] /* used_by */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 607: $$used_by empty_table
  ((CELL *)frame->slots[2])->contents /* used_by */ = get__empty_table();
  // 608: ... : (supported_platform _parent_platform)
  // 609:   $$best_platform undefined
  // 610:   $$best_priority 999
  // 611:   for_each mod_info: (platform _filenames)
  // 612:     $priority platform_specific_priority(supported_platform platform)
  // 613:     if priority.is_defined && priority < best_priority:
  // 614:       !best_platform platform
  // 615:       !best_priority priority
  // 616:   if best_platform.is_defined:
  // 617:     $$ub default_value(used_by(best_platform) empty_list)
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__73_109, 2);
  // 608: for_each supported_platforms: (supported_platform _parent_platform)
  // 609:   $$best_platform undefined
  // 610:   $$best_priority 999
  // 611:   for_each mod_info: (platform _filenames)
  // 612:     $priority platform_specific_priority(supported_platform platform)
  // 613:     if priority.is_defined && priority < best_priority:
  // 614:       !best_platform platform
  // 615:       !best_priority priority
  // 616:   if best_platform.is_defined:
  // 617:     $$ub default_value(used_by(best_platform) empty_list)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._supported_platforms;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__73_124;
}
static void entry__73_119(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // used_by: 0
  // best_platform: 1
  // supported_platform: 2
  // ub: 3
  frame->slots[0] = myself->closure.frame->slots[3]; /* used_by */
  frame->slots[1] = myself->closure.frame->slots[4]; /* best_platform */
  frame->slots[2] = myself->closure.frame->slots[0]; /* supported_platform */
  frame->slots[3] /* ub */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 617: ... used_by(best_platform)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* best_platform */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* used_by */;
  func = myself->type;
  frame->cont = cont__73_120;
}
static void cont__73_120(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 617: $$ub default_value(used_by(best_platform) empty_list)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = get__empty_list();
  result_count = 1;
  myself = get__default_value();
  func = myself->type;
  frame->cont = cont__73_121;
}
static void cont__73_121(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* ub */ = arguments->slots[0];
  // 618: push &ub supported_platform
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* ub */;
  arguments->slots[1] = frame->slots[2] /* supported_platform */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__73_122;
}
static void cont__73_122(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* ub */ = arguments->slots[0];
  // 619: !used_by(best_platform) ub
  frame->slots[4] /* temp__1 */ = ((CELL *)frame->slots[3])->contents /* ub */;
  // 619: !used_by(best_platform)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* best_platform */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* used_by */;
  func = myself->type;
  frame->cont = cont__73_123;
}
static void cont__73_123(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* used_by */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__73_109(void) {
  allocate_initialized_frame_gc(4, 8);
  // slot allocations:
  // supported_platform: 0
  // parent_platform: 1
  // mod_info: 2
  // used_by: 3
  // best_platform: 4
  // best_priority: 5
  frame->slots[2] = myself->closure.frame->slots[0]; /* mod_info */
  frame->slots[3] = myself->closure.frame->slots[2]; /* used_by */
  frame->slots[4] /* best_platform */ = create_cell();
  frame->slots[5] /* best_priority */ = create_cell();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 609: $$best_platform undefined
  ((CELL *)frame->slots[4])->contents /* best_platform */ = get__undefined();
  // 610: $$best_priority 999
  ((CELL *)frame->slots[5])->contents /* best_priority */ = number__999;
  // 611: ... : (platform _filenames)
  // 612:   $priority platform_specific_priority(supported_platform platform)
  // 613:   if priority.is_defined && priority < best_priority:
  // 614:     !best_platform platform
  // 615:     !best_priority priority
  frame->slots[6] /* temp__1 */ = create_closure(entry__73_110, 2);
  // 611: for_each mod_info: (platform _filenames)
  // 612:   $priority platform_specific_priority(supported_platform platform)
  // 613:   if priority.is_defined && priority < best_priority:
  // 614:     !best_platform platform
  // 615:     !best_priority priority
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* mod_info */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__73_117;
}
static void entry__73_116(void) {
  allocate_initialized_frame_gc(4, 4);
  // slot allocations:
  // best_platform: 0
  // platform: 1
  // best_priority: 2
  // priority: 3
  frame->slots[0] = myself->closure.frame->slots[4]; /* best_platform */
  frame->slots[1] = myself->closure.frame->slots[0]; /* platform */
  frame->slots[2] = myself->closure.frame->slots[3]; /* best_priority */
  frame->slots[3] = myself->closure.frame->slots[5]; /* priority */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 614: !best_platform platform
  ((CELL *)frame->slots[0])->contents /* best_platform */ = frame->slots[1] /* platform */;
  // 615: !best_priority priority
  ((CELL *)frame->slots[2])->contents /* best_priority */ = frame->slots[3] /* priority */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__73_110(void) {
  allocate_initialized_frame_gc(5, 10);
  // slot allocations:
  // platform: 0
  // filenames: 1
  // supported_platform: 2
  // best_priority: 3
  // best_platform: 4
  // priority: 5
  frame->slots[2] = myself->closure.frame->slots[0]; /* supported_platform */
  frame->slots[3] = myself->closure.frame->slots[5]; /* best_priority */
  frame->slots[4] = myself->closure.frame->slots[4]; /* best_platform */
  frame->slots[5] /* priority */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 612: $priority platform_specific_priority(supported_platform platform)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* supported_platform */;
  arguments->slots[1] = frame->slots[0] /* platform */;
  result_count = 1;
  myself = var._platform_specific_priority;
  func = myself->type;
  frame->cont = cont__73_111;
}
static void cont__73_111(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* priority */, arguments->slots[0]);
  // 613: ... priority.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* priority */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__73_112;
}
static void cont__73_112(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 613: ... priority < best_priority
  frame->slots[8] /* temp__3 */ = create_closure(entry__73_113, 0);
  // 613: ... priority.is_defined && priority < best_priority
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  arguments->slots[1] = frame->slots[8] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__73_115;
}
static void entry__73_113(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // priority: 0
  // best_priority: 1
  frame->slots[0] = myself->closure.frame->slots[5]; /* priority */
  frame->slots[1] = myself->closure.frame->slots[3]; /* best_priority */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 613: ... priority < best_priority
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* priority */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* best_priority */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__73_114;
}
static void cont__73_114(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 613: ... priority < best_priority
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__73_115(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 613: ... :
  // 614:   !best_platform platform
  // 615:   !best_priority priority
  frame->slots[9] /* temp__4 */ = create_closure(entry__73_116, 0);
  // 613: if priority.is_defined && priority < best_priority:
  // 614:   !best_platform platform
  // 615:   !best_priority priority
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__73_117(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 616: ... best_platform.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* best_platform */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__73_118;
}
static void cont__73_118(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 616: ... :
  // 617:   $$ub default_value(used_by(best_platform) empty_list)
  // 618:   push &ub supported_platform
  // 619:   !used_by(best_platform) ub
  frame->slots[7] /* temp__2 */ = create_closure(entry__73_119, 0);
  // 616: if best_platform.is_defined:
  // 617:   $$ub default_value(used_by(best_platform) empty_list)
  // 618:   push &ub supported_platform
  // 619:   !used_by(best_platform) ub
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__73_124(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 620: ... : (platform _filenames)
  // 621:   $$dependency string(mod_filename "-" platform ".c")
  // 622:   $platforms used_by(platform)
  // 623:   if platforms.is_defined:
  // 624:     for_each platforms: (plat) write_to &dependency " #" plat
  // 625:   push &dependencies dependency
  frame->slots[3] /* temp__1 */ = create_closure(entry__73_125, 2);
  // 620: for_each mod_info: (platform _filenames)
  // 621:   $$dependency string(mod_filename "-" platform ".c")
  // 622:   $platforms used_by(platform)
  // 623:   if platforms.is_defined:
  // 624:     for_each platforms: (plat) write_to &dependency " #" plat
  // 625:   push &dependencies dependency
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_info */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__73_91(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // mod_filename: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* mod_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 591: ... string(mod_filename ".c")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = string__71_9;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__73_92;
}
static void cont__73_92(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 591: ... push &dependencies string(mod_filename ".c")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._dependencies;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__73_93;
}
static void cont__73_93(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._dependencies = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__73_86(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // compile_submodule: 0
  // mod_name: 1
  // mod_filename: 2
  frame->slots[0] = myself->closure.frame->slots[3]; /* compile_submodule */
  frame->slots[1] = myself->closure.frame->slots[1]; /* mod_name */
  frame->slots[2] = myself->closure.frame->slots[0]; /* mod_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 590: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__73_87;
}
static void cont__73_87(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 590: ... truncate_until(mod_name '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* mod_name */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__73_88;
}
static void cont__73_88(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 590: ... list(truncate_until(mod_name '/' -1))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__73_89;
}
static void cont__73_89(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 590: compile_submodule list(truncate_until(mod_name '/' -1))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = frame->slots[0] /* compile_submodule */;
  func = myself->type;
  frame->cont = cont__73_90;
}
static void cont__73_90(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 591: ... : push &dependencies string(mod_filename ".c")
  frame->slots[3] /* temp__1 */ = create_closure(entry__73_91, 0);
  // 591: if do_list_dependencies: push &dependencies string(mod_filename ".c")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_list_dependencies;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__73_94(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // mod_info: 0
  // compile_submodule: 1
  // mod_filename: 2
  frame->slots[0] = myself->closure.frame->slots[4]; /* mod_info */
  frame->slots[1] = myself->closure.frame->slots[3]; /* compile_submodule */
  frame->slots[2] = myself->closure.frame->slots[0]; /* mod_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 593: ... :
  // 594:   $$best_platform undefined
  // 595:   $$best_priority 999
  // 596:   for_each mod_info: (platform _filenames)
  // 597:     $priority platform_priority(platform)
  // 598:     if priority.is_defined && priority < best_priority:
  // 599:       !best_platform platform
  // 600:       !best_priority priority
  // 601:   for_each mod_info: (platform filenames)
  // 602:     compile_submodule
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__73_95, 0);
  // 593: do:
  // 594:   $$best_platform undefined
  // 595:   $$best_priority 999
  // 596:   for_each mod_info: (platform _filenames)
  // 597:     $priority platform_priority(platform)
  // 598:     if priority.is_defined && priority < best_priority:
  // 599:       !best_platform platform
  // 600:       !best_priority priority
  // 601:   for_each mod_info: (platform filenames)
  // 602:     compile_submodule
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__73_107;
}
static void entry__73_104(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // platform: 0
  // filenames: 1
  // compile_submodule: 2
  // best_platform: 3
  frame->slots[2] = myself->closure.frame->slots[1]; /* compile_submodule */
  frame->slots[3] = myself->closure.frame->slots[2]; /* best_platform */
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 604: platform == best_platform
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* platform */;
  arguments->slots[1] = ((CELL *)frame->slots[3])->contents /* best_platform */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__73_105;
}
static void cont__73_105(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 605: string("-" platform)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__67_46;
  arguments->slots[1] = frame->slots[0] /* platform */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__73_106;
}
static void cont__73_106(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 602: compile_submodule
  // 603:   filenames
  // 604:   platform == best_platform
  // 605:   string("-" platform)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* filenames */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  arguments->slots[2] = frame->slots[5] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[2] /* compile_submodule */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__73_95(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // mod_info: 0
  // compile_submodule: 1
  // best_platform: 2
  // best_priority: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* mod_info */
  frame->slots[1] = myself->closure.frame->slots[1]; /* compile_submodule */
  frame->slots[2] /* best_platform */ = create_cell();
  frame->slots[3] /* best_priority */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 594: $$best_platform undefined
  ((CELL *)frame->slots[2])->contents /* best_platform */ = get__undefined();
  // 595: $$best_priority 999
  ((CELL *)frame->slots[3])->contents /* best_priority */ = number__999;
  // 596: ... : (platform _filenames)
  // 597:   $priority platform_priority(platform)
  // 598:   if priority.is_defined && priority < best_priority:
  // 599:     !best_platform platform
  // 600:     !best_priority priority
  frame->slots[4] /* temp__1 */ = create_closure(entry__73_96, 2);
  // 596: for_each mod_info: (platform _filenames)
  // 597:   $priority platform_priority(platform)
  // 598:   if priority.is_defined && priority < best_priority:
  // 599:     !best_platform platform
  // 600:     !best_priority priority
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_info */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__73_103;
}
static void entry__73_102(void) {
  allocate_initialized_frame_gc(4, 4);
  // slot allocations:
  // best_platform: 0
  // platform: 1
  // best_priority: 2
  // priority: 3
  frame->slots[0] = myself->closure.frame->slots[3]; /* best_platform */
  frame->slots[1] = myself->closure.frame->slots[0]; /* platform */
  frame->slots[2] = myself->closure.frame->slots[2]; /* best_priority */
  frame->slots[3] = myself->closure.frame->slots[4]; /* priority */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 599: !best_platform platform
  ((CELL *)frame->slots[0])->contents /* best_platform */ = frame->slots[1] /* platform */;
  // 600: !best_priority priority
  ((CELL *)frame->slots[2])->contents /* best_priority */ = frame->slots[3] /* priority */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__73_96(void) {
  allocate_initialized_frame_gc(4, 9);
  // slot allocations:
  // platform: 0
  // filenames: 1
  // best_priority: 2
  // best_platform: 3
  // priority: 4
  frame->slots[2] = myself->closure.frame->slots[3]; /* best_priority */
  frame->slots[3] = myself->closure.frame->slots[2]; /* best_platform */
  frame->slots[4] /* priority */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 597: $priority platform_priority(platform)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* platform */;
  result_count = 1;
  myself = var._platform_priority;
  func = myself->type;
  frame->cont = cont__73_97;
}
static void cont__73_97(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* priority */, arguments->slots[0]);
  // 598: ... priority.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* priority */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__73_98;
}
static void cont__73_98(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 598: ... priority < best_priority
  frame->slots[7] /* temp__3 */ = create_closure(entry__73_99, 0);
  // 598: ... priority.is_defined && priority < best_priority
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__73_101;
}
static void entry__73_99(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // priority: 0
  // best_priority: 1
  frame->slots[0] = myself->closure.frame->slots[4]; /* priority */
  frame->slots[1] = myself->closure.frame->slots[2]; /* best_priority */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 598: ... priority < best_priority
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* priority */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* best_priority */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__73_100;
}
static void cont__73_100(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 598: ... priority < best_priority
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__73_101(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 598: ... :
  // 599:   !best_platform platform
  // 600:   !best_priority priority
  frame->slots[8] /* temp__4 */ = create_closure(entry__73_102, 0);
  // 598: if priority.is_defined && priority < best_priority:
  // 599:   !best_platform platform
  // 600:   !best_priority priority
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__73_103(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 601: ... : (platform filenames)
  // 602:   compile_submodule
  // 603:     filenames
  // 604:     platform == best_platform
  // 605:     string("-" platform)
  frame->slots[4] /* temp__1 */ = create_closure(entry__73_104, 2);
  // 601: for_each mod_info: (platform filenames)
  // 602:   compile_submodule
  // 603:     filenames
  // 604:     platform == best_platform
  // 605:     string("-" platform)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_info */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__73_107(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 606: ... :
  // 607:   $$used_by empty_table
  // 608:   for_each supported_platforms: (supported_platform _parent_platform)
  // 609:     $$best_platform undefined
  // 610:     $$best_priority 999
  // 611:     for_each mod_info: (platform _filenames)
  // 612:       $priority platform_specific_priority(supported_platform platform)
  // 613:       if priority.is_defined && priority < best_priority:
  // 614:         !best_platform platform
  // 615:         !best_priority priority
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__73_108, 0);
  // 606: if do_list_dependencies:
  // 607:   $$used_by empty_table
  // 608:   for_each supported_platforms: (supported_platform _parent_platform)
  // 609:     $$best_platform undefined
  // 610:     $$best_priority 999
  // 611:     for_each mod_info: (platform _filenames)
  // 612:       $priority platform_specific_priority(supported_platform platform)
  // 613:       if priority.is_defined && priority < best_priority:
  // 614:         !best_platform platform
  // 615:         !best_priority priority
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_list_dependencies;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__73_135(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__74_8(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // name: 0
  // path: 1
  // mod_path: 2
  frame->slots[1] = myself->closure.frame->slots[0]; /* path */
  frame->slots[2] = myself->closure.frame->slots[1]; /* mod_path */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 636: ... string(path '/' name)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* path */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__74_9;
}
static void cont__74_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 636: ... string(mod_path '/' name)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* mod_path */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__74_10;
}
static void cont__74_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 636: compile_module string(path '/' name) string(mod_path '/' name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = var._compile_module;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__74_1_compile_modules(void) {
  allocate_initialized_frame_gc(2, 7);
  // slot allocations:
  // path: 0
  // mod_path: 1
  // directories: 2
  // modules: 3
  frame->slots[2] /* directories */ = create_future();
  frame->slots[3] /* modules */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 632: ... string(mod_path '/')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* mod_path */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__74_2;
}
static void cont__74_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 632: add_module_infos $directories $modules path string(mod_path '/')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* path */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 2;
  myself = var._add_module_infos;
  func = myself->type;
  frame->cont = cont__74_3;
}
static void cont__74_3(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  frame->slots[6] /* temp__3 */ = arguments->slots[1];
  // 632: ... directories
  initialize_future(frame->slots[2] /* directories */, frame->slots[5] /* temp__2 */);
  // 632: ... modules
  initialize_future(frame->slots[3] /* modules */, frame->slots[6] /* temp__3 */);
  // 633: ... : (name)
  // 634:   compile_modules string(path '/' name) string(mod_path '/' name)
  frame->slots[4] /* temp__1 */ = create_closure(entry__74_4, 1);
  // 633: for_each directories: (name)
  // 634:   compile_modules string(path '/' name) string(mod_path '/' name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* directories */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__74_7;
}
static void entry__74_4(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // name: 0
  // path: 1
  // mod_path: 2
  frame->slots[1] = myself->closure.frame->slots[0]; /* path */
  frame->slots[2] = myself->closure.frame->slots[1]; /* mod_path */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 634: ... string(path '/' name)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* path */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__74_5;
}
static void cont__74_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 634: ... string(mod_path '/' name)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* mod_path */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__74_6;
}
static void cont__74_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 634: compile_modules string(path '/' name) string(mod_path '/' name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = var._compile_modules;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__74_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 635: ... : (name)
  // 636:   compile_module string(path '/' name) string(mod_path '/' name)
  frame->slots[4] /* temp__1 */ = create_closure(entry__74_8, 1);
  // 635: for_each modules: (name)
  // 636:   compile_module string(path '/' name) string(mod_path '/' name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* modules */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__76_2(void) {
  allocate_initialized_frame_gc(0, 3);
  // slot allocations:
  // path: 0
  frame->slots[0] /* path */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 644: $path environment("LD_LIBRARY_PATH")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__76_3;
  result_count = 1;
  myself = get__environment();
  func = myself->type;
  frame->cont = cont__76_4;
}
static void cont__76_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[0] /* path */, arguments->slots[0]);
  // 645: ... path.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* path */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__76_5;
}
static void cont__76_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 645: ... : ewriteln "LD_LIBRARY_PATH=@(path)"
  frame->slots[2] /* temp__2 */ = create_closure(entry__76_6, 0);
  // 645: if path.is_defined: ewriteln "LD_LIBRARY_PATH=@(path)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__76_9;
}
static void entry__76_6(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // path: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* path */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 645: ... "LD_LIBRARY_PATH=@(path)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__76_7;
  arguments->slots[1] = frame->slots[0] /* path */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__76_8;
}
static void cont__76_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 645: ... ewriteln "LD_LIBRARY_PATH=@(path)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__76_9(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 646: ... serialize(objects)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__objects();
  result_count = 1;
  myself = get__serialize();
  func = myself->type;
  frame->cont = cont__76_10;
}
static void cont__76_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 646: ewriteln "included object files: " serialize(objects)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__76_11;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 0;
  myself = get__ewriteln();
  func = myself->type;
  frame->cont = cont__76_12;
}
static void cont__76_12(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 647: ... serialize(libraries)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__libraries();
  result_count = 1;
  myself = get__serialize();
  func = myself->type;
  frame->cont = cont__76_13;
}
static void cont__76_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 647: ewriteln "needed libraries: " serialize(libraries)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__76_14;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__76_1_show_file_list(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 643: if do_show_debug_infos:
  // 644:   $path environment("LD_LIBRARY_PATH")
  // 645:   if path.is_defined: ewriteln "LD_LIBRARY_PATH=@(path)"
  // 646:   ewriteln "included object files: " serialize(objects)
  // 647:   ewriteln "needed libraries: " serialize(libraries)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_show_debug_infos();
  arguments->slots[1] = func__76_2;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__77_1_library_paths_and_file_list(void) {
  allocate_initialized_frame_gc(0, 6);
  // slot allocations:
  // library_paths: 0
  // object_files: 1
  // library_files: 2
  // paths: 3
  frame->slots[0] /* library_paths */ = create_cell();
  frame->slots[1] /* object_files */ = create_cell();
  frame->slots[2] /* library_files */ = create_cell();
  frame->slots[3] /* paths */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 650: show_file_list
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._show_file_list;
  func = myself->type;
  frame->cont = cont__77_2;
}
static void cont__77_2(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 651: $$library_paths empty_list
  ((CELL *)frame->slots[0])->contents /* library_paths */ = get__empty_list();
  // 652: $$object_files empty_list
  ((CELL *)frame->slots[1])->contents /* object_files */ = get__empty_list();
  // 653: $$library_files empty_list
  ((CELL *)frame->slots[2])->contents /* library_files */ = get__empty_list();
  // 654: $paths environment("LD_LIBRARY_PATH")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__76_3;
  result_count = 1;
  myself = get__environment();
  func = myself->type;
  frame->cont = cont__77_3;
}
static void cont__77_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* paths */, arguments->slots[0]);
  // 655: ... paths.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* paths */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__77_4;
}
static void cont__77_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 655: ... :
  // 656:   for_each paths .split. ':': (path) push &library_paths "-L@(path)"
  frame->slots[5] /* temp__2 */ = create_closure(entry__77_5, 0);
  // 655: if paths.is_defined:
  // 656:   for_each paths .split. ':': (path) push &library_paths "-L@(path)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__77_11;
}
static void entry__77_7(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // path: 0
  // library_paths: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* library_paths */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 656: ... "-L@(path)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__77_8;
  arguments->slots[1] = frame->slots[0] /* path */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__77_9;
}
static void cont__77_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 656: ... push &library_paths "-L@(path)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* library_paths */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__77_10;
}
static void cont__77_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* library_paths */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__77_5(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // paths: 0
  // library_paths: 1
  frame->slots[0] = myself->closure.frame->slots[3]; /* paths */
  frame->slots[1] = myself->closure.frame->slots[0]; /* library_paths */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 656: ... paths .split. ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* paths */;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__split();
  func = myself->type;
  frame->cont = cont__77_6;
}
static void cont__77_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 656: ... : (path) push &library_paths "-L@(path)"
  frame->slots[3] /* temp__2 */ = create_closure(entry__77_7, 1);
  // 656: for_each paths .split. ':': (path) push &library_paths "-L@(path)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__77_11(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 657: ... : ewriteln "library paths: " serialize(library_paths)
  frame->slots[4] /* temp__1 */ = create_closure(entry__77_12, 0);
  // 657: if do_show_debug_infos: ewriteln "library paths: " serialize(library_paths)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_show_debug_infos();
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__77_15;
}
static void entry__77_12(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // library_paths: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* library_paths */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 657: ... serialize(library_paths)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* library_paths */;
  result_count = 1;
  myself = get__serialize();
  func = myself->type;
  frame->cont = cont__77_13;
}
static void cont__77_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 657: ... ewriteln "library paths: " serialize(library_paths)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__77_14;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__77_15(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 658: ... : (object) push &object_files object
  frame->slots[4] /* temp__1 */ = create_closure(entry__77_16, 1);
  // 658: for_each objects: (object) push &object_files object
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__objects();
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__77_18;
}
static void entry__77_16(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // object: 0
  // object_files: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* object_files */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 658: ... push &object_files object
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* object_files */;
  arguments->slots[1] = frame->slots[0] /* object */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__77_17;
}
static void cont__77_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* object_files */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__77_18(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 659: ... : (library)
  // 660:   push
  // 661:     &library_files
  // 662:     if
  // 663:       library .has_prefix. "sim-"
  // 664:       ->
  // 665:         if
  // 666:           operating_system() == "linux"
  // 667:           -> "-l:lib@(library).so.@(MAJOR)"
  // 668:           -> "-l@(library)-@(MAJOR)"
  // ...
  frame->slots[4] /* temp__1 */ = create_closure(entry__77_19, 1);
  // 659: for_each libraries: (library)
  // 660:   push
  // 661:     &library_files
  // 662:     if
  // 663:       library .has_prefix. "sim-"
  // 664:       ->
  // 665:         if
  // 666:           operating_system() == "linux"
  // 667:           -> "-l:lib@(library).so.@(MAJOR)"
  // 668:           -> "-l@(library)-@(MAJOR)"
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__libraries();
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__77_44;
}
static void entry__77_19(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // library: 0
  // library_files: 1
  frame->slots[1] = myself->closure.frame->slots[2]; /* library_files */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 663: library .has_prefix. "sim-"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* library */;
  arguments->slots[1] = string__72_32;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__77_20;
}
static void cont__77_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 664: ->
  // 665:   if
  // 666:     operating_system() == "linux"
  // 667:     -> "-l:lib@(library).so.@(MAJOR)"
  // 668:     -> "-l@(library)-@(MAJOR)"
  frame->slots[4] /* temp__3 */ = create_closure(entry__77_21, 0);
  // 669: ->
  // 670:   if
  // 671:     library .contains. '.'
  // 672:     -> "-l:lib@(library .before. '.').so.@(library .behind. '.')"
  // 673:       # Linux only
  // 674:     -> "-l@(library)"
  frame->slots[5] /* temp__4 */ = create_closure(entry__77_33, 0);
  // 662: if
  // 663:   library .has_prefix. "sim-"
  // 664:   ->
  // 665:     if
  // 666:       operating_system() == "linux"
  // 667:       -> "-l:lib@(library).so.@(MAJOR)"
  // 668:       -> "-l@(library)-@(MAJOR)"
  // 669:   ->
  // 670:     if
  // 671:       library .contains. '.'
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  arguments->slots[2] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__77_42;
}
static void entry__77_21(void) {
  allocate_initialized_frame_gc(1, 6);
  // slot allocations:
  // library: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* library */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 666: operating_system()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__operating_system();
  func = myself->type;
  frame->cont = cont__77_22;
}
static void cont__77_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 666: operating_system() == "linux"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = string__77_23;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__77_24;
}
static void cont__77_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 667: -> "-l:lib@(library).so.@(MAJOR)"
  frame->slots[4] /* temp__4 */ = create_closure(entry__77_25, 0);
  // 668: -> "-l@(library)-@(MAJOR)"
  frame->slots[5] /* temp__5 */ = create_closure(entry__77_29, 0);
  // 665: if
  // 666:   operating_system() == "linux"
  // 667:   -> "-l:lib@(library).so.@(MAJOR)"
  // 668:   -> "-l@(library)-@(MAJOR)"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  arguments->slots[2] = frame->slots[5] /* temp__5 */;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__77_32;
}
static void entry__77_25(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // library: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* library */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 667: ... "-l:lib@(library).so.@(MAJOR)"
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__77_26;
  arguments->slots[1] = frame->slots[0] /* library */;
  arguments->slots[2] = string__77_27;
  arguments->slots[3] = var._MAJOR;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__77_28;
}
static void cont__77_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 667: -> "-l:lib@(library).so.@(MAJOR)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__77_29(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // library: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* library */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 668: ... "-l@(library)-@(MAJOR)"
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__77_30;
  arguments->slots[1] = frame->slots[0] /* library */;
  arguments->slots[2] = string__67_46;
  arguments->slots[3] = var._MAJOR;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__77_31;
}
static void cont__77_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 668: -> "-l@(library)-@(MAJOR)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__77_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 664: ->
  // 665:   if
  // 666:     operating_system() == "linux"
  // 667:     -> "-l:lib@(library).so.@(MAJOR)"
  // 668:     -> "-l@(library)-@(MAJOR)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__77_33(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // library: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* library */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 671: library .contains. '.'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* library */;
  arguments->slots[1] = character__46;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__77_34;
}
static void cont__77_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 672: -> "-l:lib@(library .before. '.').so.@(library .behind. '.')"
  // 673:   # Linux only
  frame->slots[3] /* temp__3 */ = create_closure(entry__77_35, 0);
  // 674: -> "-l@(library)"
  frame->slots[4] /* temp__4 */ = create_closure(entry__77_39, 0);
  // 670: if
  // 671:   library .contains. '.'
  // 672:   -> "-l:lib@(library .before. '.').so.@(library .behind. '.')"
  // 673:     # Linux only
  // 674:   -> "-l@(library)"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  arguments->slots[2] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__77_41;
}
static void entry__77_35(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // library: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* library */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 672: ... library .before. '.'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* library */;
  arguments->slots[1] = character__46;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__77_36;
}
static void cont__77_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 672: ... library .behind. '.'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* library */;
  arguments->slots[1] = character__46;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__77_37;
}
static void cont__77_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 672: ... "-l:lib@(library .before. '.').so.@(library .behind. '.')"
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__77_26;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  arguments->slots[2] = string__77_27;
  arguments->slots[3] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__77_38;
}
static void cont__77_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 672: -> "-l:lib@(library .before. '.').so.@(library .behind. '.')"
  // 673:   # Linux only
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__77_39(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // library: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* library */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 674: ... "-l@(library)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__77_30;
  arguments->slots[1] = frame->slots[0] /* library */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__77_40;
}
static void cont__77_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 674: -> "-l@(library)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__77_41(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 669: ->
  // 670:   if
  // 671:     library .contains. '.'
  // 672:     -> "-l:lib@(library .before. '.').so.@(library .behind. '.')"
  // 673:       # Linux only
  // 674:     -> "-l@(library)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__77_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 660: push
  // 661:   &library_files
  // 662:   if
  // 663:     library .has_prefix. "sim-"
  // 664:     ->
  // 665:       if
  // 666:         operating_system() == "linux"
  // 667:         -> "-l:lib@(library).so.@(MAJOR)"
  // 668:         -> "-l@(library)-@(MAJOR)"
  // 669:     ->
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* library_files */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__77_43;
}
static void cont__77_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* library_files */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__77_44(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 675: ... append(object_files library_files)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* object_files */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* library_files */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__77_45;
}
static void cont__77_45(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 675: append library_paths append(object_files library_files)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* library_paths */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__append();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__78_74(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 718: ... write_timing_info "collecting imports"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__78_75;
  result_count = frame->caller_result_count;
  myself = get__write_timing_info();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__78_1_create_imports(void) {
  allocate_initialized_frame_gc(1, 9);
  // slot allocations:
  // source: 0
  // already_checked: 1
  // collect_declarations: 2
  // imports: 3
  // first_part: 4
  frame->slots[2] /* collect_declarations */ = create_future();
  frame->slots[1] /* already_checked */ = create_cell();
  frame->slots[3] /* imports */ = create_future();
  frame->slots[4] /* first_part */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 680: ... : (buf)
  // 681:   $$s undefined
  // 682:   for_each buf: (idx chr)
  // 683:     if
  // 684:       s.is_defined:
  // 685:         unless chr.is_a_letter || chr == '_' || chr.is_a_digit:
  // 686:           $symbol range(buf s idx-1)
  // 687:           !s undefined
  // 688:           unless already_checked(symbol):
  // 689:             !already_checked(symbol) true
  // ...
  frame->slots[5] /* temp__1 */ = create_closure(entry__78_2_collect_declarations, 1);
  // 680: $collect_declarations: (buf)
  // 681:   $$s undefined
  // 682:   for_each buf: (idx chr)
  // 683:     if
  // 684:       s.is_defined:
  // 685:         unless chr.is_a_letter || chr == '_' || chr.is_a_digit:
  // 686:           $symbol range(buf s idx-1)
  // 687:           !s undefined
  // 688:           unless already_checked(symbol):
  // 689:             !already_checked(symbol) true
  // ...
  initialize_future(frame->slots[2] /* collect_declarations */, frame->slots[5] /* temp__1 */);
  // 678: $$already_checked empty_set
  ((CELL *)frame->slots[1])->contents /* already_checked */ = get__empty_set();
  // 713: ... : collect_declarations source
  frame->slots[5] /* temp__1 */ = create_closure(entry__78_63, 0);
  // 713: collect_output $imports: collect_declarations source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__78_64;
}
static void entry__78_62(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // s: 0
  // idx: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* s */
  frame->slots[1] = myself->closure.frame->slots[2]; /* idx */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 711: ... !s idx
  ((CELL *)frame->slots[0])->contents /* s */ = frame->slots[1] /* idx */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__78_21(void) {
  allocate_initialized_frame_gc(2, 7);
  // slot allocations:
  // declaration: 0
  // collect_declarations: 1
  // do_import: 2
  frame->slots[0] = myself->closure.frame->slots[3]; /* declaration */
  frame->slots[1] = myself->closure.frame->slots[2]; /* collect_declarations */
  frame->slots[2] /* do_import */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 694: declaration(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* declaration */;
  func = myself->type;
  frame->cont = cont__78_22;
}
static void cont__78_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 694: declaration(1) != '#'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  arguments->slots[1] = character__35;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__78_23;
}
static void cont__78_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 694: declaration(1) != '#'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__78_24;
}
static void cont__78_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  frame->slots[6] /* temp__4 */ = create_closure(entry__78_25, 0);
  // 692: $do_import
  // 693:   &&
  // 694:     declaration(1) != '#'
  // 695:     not(declaration .has_prefix. "typedef")
  // 696:     not(declaration .has_prefix. "REGISTER")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__78_34;
}
static void entry__78_25(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // declaration: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* declaration */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 695: ... declaration .has_prefix. "typedef"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* declaration */;
  arguments->slots[1] = string__78_26;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__78_27;
}
static void cont__78_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 695: not(declaration .has_prefix. "typedef")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__not();
  func = myself->type;
  frame->cont = cont__78_28;
}
static void cont__78_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 696: not(declaration .has_prefix. "REGISTER")
  frame->slots[4] /* temp__4 */ = create_closure(entry__78_29, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__78_33;
}
static void entry__78_29(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // declaration: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* declaration */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 696: ... declaration .has_prefix. "REGISTER"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* declaration */;
  arguments->slots[1] = string__78_30;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__78_31;
}
static void cont__78_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 696: not(declaration .has_prefix. "REGISTER")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__not();
  func = myself->type;
  frame->cont = cont__78_32;
}
static void cont__78_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 696: not(declaration .has_prefix. "REGISTER")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__78_33(void) {
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
static void cont__78_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* do_import */, arguments->slots[0]);
  // 699: ->
  // 700:   declaration(1) == '#' || declaration .has_prefix. "REGISTER"
  // 701:   :
  // 702:     collect_declarations declaration .truncate_from. '{'
  frame->slots[3] /* temp__1 */ = create_closure(entry__78_35, 0);
  // 703: -> declaration .has_prefix. "typedef struct":
  // 704:   for_each_line between(declaration '{' '}').trim: (line)
  // 705:     collect_declarations until(line ' ' -1)
  frame->slots[4] /* temp__2 */ = create_closure(entry__78_43, 0);
  // 706: :
  // 707:   collect_declarations declaration
  frame->slots[5] /* temp__3 */ = create_closure(entry__78_52, 0);
  // 698: cond
  // 699:   ->
  // 700:     declaration(1) == '#' || declaration .has_prefix. "REGISTER"
  // 701:     :
  // 702:       collect_declarations declaration .truncate_from. '{'
  // 703:   -> declaration .has_prefix. "typedef struct":
  // 704:     for_each_line between(declaration '{' '}').trim: (line)
  // 705:       collect_declarations until(line ' ' -1)
  // 706:   :
  // 707:     collect_declarations declaration
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = frame->slots[5] /* temp__3 */;
  result_count = 0;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__78_53;
}
static void entry__78_49(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // line: 0
  // collect_declarations: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* collect_declarations */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 705: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__78_50;
}
static void cont__78_50(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 705: ... until(line ' ' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* line */;
  arguments->slots[1] = character__32;
  arguments->slots[2] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__until();
  func = myself->type;
  frame->cont = cont__78_51;
}
static void cont__78_51(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 705: collect_declarations until(line ' ' -1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* collect_declarations */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__78_46(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // declaration: 0
  // collect_declarations: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* declaration */
  frame->slots[1] = myself->closure.frame->slots[1]; /* collect_declarations */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 704: ... between(declaration '{' '}')
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* declaration */;
  arguments->slots[1] = character__123;
  arguments->slots[2] = character__125;
  result_count = 1;
  myself = get__between();
  func = myself->type;
  frame->cont = cont__78_47;
}
static void cont__78_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 704: ... between(declaration '{' '}').trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__78_48;
}
static void cont__78_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 704: ... : (line)
  // 705:   collect_declarations until(line ' ' -1)
  frame->slots[4] /* temp__3 */ = create_closure(entry__78_49, 1);
  // 704: for_each_line between(declaration '{' '}').trim: (line)
  // 705:   collect_declarations until(line ' ' -1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__for_each_line();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__78_41(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // collect_declarations: 0
  // declaration: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* collect_declarations */
  frame->slots[1] = myself->closure.frame->slots[0]; /* declaration */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 702: ... declaration .truncate_from. '{'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* declaration */;
  arguments->slots[1] = character__123;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__78_42;
}
static void cont__78_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 702: collect_declarations declaration .truncate_from. '{'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* collect_declarations */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__78_35(void) {
  allocate_initialized_frame_gc(2, 7);
  // slot allocations:
  // declaration: 0
  // collect_declarations: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* declaration */
  frame->slots[1] = myself->closure.frame->slots[1]; /* collect_declarations */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 700: declaration(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* declaration */;
  func = myself->type;
  frame->cont = cont__78_36;
}
static void cont__78_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 700: declaration(1) == '#'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  arguments->slots[1] = character__35;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__78_37;
}
static void cont__78_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 700: ... declaration .has_prefix. "REGISTER"
  frame->slots[5] /* temp__4 */ = create_closure(entry__78_38, 0);
  // 700: declaration(1) == '#' || declaration .has_prefix. "REGISTER"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__78_40;
}
static void entry__78_38(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // declaration: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* declaration */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 700: ... declaration .has_prefix. "REGISTER"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* declaration */;
  arguments->slots[1] = string__78_30;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__78_39;
}
static void cont__78_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 700: ... declaration .has_prefix. "REGISTER"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__78_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 701: :
  // 702:   collect_declarations declaration .truncate_from. '{'
  frame->slots[6] /* temp__5 */ = create_closure(entry__78_41, 0);
  // 699: ->
  // 700:   declaration(1) == '#' || declaration .has_prefix. "REGISTER"
  // 701:   :
  // 702:     collect_declarations declaration .truncate_from. '{'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__5 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__78_43(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // declaration: 0
  // collect_declarations: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* declaration */
  frame->slots[1] = myself->closure.frame->slots[1]; /* collect_declarations */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 703: ... declaration .has_prefix. "typedef struct"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* declaration */;
  arguments->slots[1] = string__78_44;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__78_45;
}
static void cont__78_45(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 703: ... :
  // 704:   for_each_line between(declaration '{' '}').trim: (line)
  // 705:     collect_declarations until(line ' ' -1)
  frame->slots[3] /* temp__2 */ = create_closure(entry__78_46, 0);
  // 703: -> declaration .has_prefix. "typedef struct":
  // 704:   for_each_line between(declaration '{' '}').trim: (line)
  // 705:     collect_declarations until(line ' ' -1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__78_52(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // collect_declarations: 0
  // declaration: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* collect_declarations */
  frame->slots[1] = myself->closure.frame->slots[0]; /* declaration */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 707: collect_declarations declaration
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* declaration */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* collect_declarations */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__78_53(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 708: if do_import: write "IMPORT "
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* do_import */;
  arguments->slots[1] = func__78_54;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__78_56;
}
static void entry__78_54(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 708: ... write "IMPORT "
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__78_55;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__78_56(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 709: write declaration
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* declaration */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__78_17(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // already_checked: 0
  // symbol: 1
  // collect_declarations: 2
  // declaration: 3
  frame->slots[0] = myself->closure.frame->slots[3]; /* already_checked */
  frame->slots[1] = myself->closure.frame->slots[5]; /* symbol */
  frame->slots[2] = myself->closure.frame->slots[4]; /* collect_declarations */
  frame->slots[3] /* declaration */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 689: !already_checked(symbol) true
  frame->slots[4] /* temp__1 */ = get__true();
  // 689: !already_checked(symbol)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* symbol */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* already_checked */;
  func = myself->type;
  frame->cont = cont__78_18;
}
static void cont__78_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* already_checked */ = arguments->slots[0];
  // 690: $declaration runtime_symbols(symbol)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* symbol */;
  result_count = 1;
  myself = get__runtime_symbols();
  func = myself->type;
  frame->cont = cont__78_19;
}
static void cont__78_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* declaration */, arguments->slots[0]);
  // 691: ... declaration.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* declaration */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__78_20;
}
static void cont__78_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 691: ... :
  // 692:   $do_import
  // 693:     &&
  // 694:       declaration(1) != '#'
  // 695:       not(declaration .has_prefix. "typedef")
  // 696:       not(declaration .has_prefix. "REGISTER")
  // 697:   
  // 698:   cond
  // 699:     ->
  // 700:       declaration(1) == '#' || declaration .has_prefix. "REGISTER"
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__78_21, 0);
  // 691: if declaration.is_defined:
  // 692:   $do_import
  // 693:     &&
  // 694:       declaration(1) != '#'
  // 695:       not(declaration .has_prefix. "typedef")
  // 696:       not(declaration .has_prefix. "REGISTER")
  // 697:   
  // 698:   cond
  // 699:     ->
  // 700:       declaration(1) == '#' || declaration .has_prefix. "REGISTER"
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__78_13(void) {
  allocate_initialized_frame_gc(5, 8);
  // slot allocations:
  // buf: 0
  // s: 1
  // idx: 2
  // already_checked: 3
  // collect_declarations: 4
  // symbol: 5
  frame->slots[0] = myself->closure.frame->slots[1]; /* buf */
  frame->slots[1] = myself->closure.frame->slots[2]; /* s */
  frame->slots[2] = myself->closure.frame->slots[3]; /* idx */
  frame->slots[3] = myself->closure.frame->slots[4]; /* already_checked */
  frame->slots[4] = myself->closure.frame->slots[5]; /* collect_declarations */
  frame->slots[5] /* symbol */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 686: ... idx-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* idx */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__78_14;
}
static void cont__78_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 686: $symbol range(buf s idx-1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* buf */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* s */;
  arguments->slots[2] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__78_15;
}
static void cont__78_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* symbol */, arguments->slots[0]);
  // 687: !s undefined
  ((CELL *)frame->slots[1])->contents /* s */ = get__undefined();
  // 688: ... already_checked(symbol)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* symbol */;
  result_count = 1;
  myself = ((CELL *)frame->slots[3])->contents /* already_checked */;
  func = myself->type;
  frame->cont = cont__78_16;
}
static void cont__78_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 688: ... :
  // 689:   !already_checked(symbol) true
  // 690:   $declaration runtime_symbols(symbol)
  // 691:   if declaration.is_defined:
  // 692:     $do_import
  // 693:       &&
  // 694:         declaration(1) != '#'
  // 695:         not(declaration .has_prefix. "typedef")
  // 696:         not(declaration .has_prefix. "REGISTER")
  // 697:     
  // ...
  frame->slots[7] /* temp__2 */ = create_closure(entry__78_17, 0);
  // 688: unless already_checked(symbol):
  // 689:   !already_checked(symbol) true
  // 690:   $declaration runtime_symbols(symbol)
  // 691:   if declaration.is_defined:
  // 692:     $do_import
  // 693:       &&
  // 694:         declaration(1) != '#'
  // 695:         not(declaration .has_prefix. "typedef")
  // 696:         not(declaration .has_prefix. "REGISTER")
  // 697:     
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__78_5(void) {
  allocate_initialized_frame_gc(6, 10);
  // slot allocations:
  // chr: 0
  // buf: 1
  // s: 2
  // idx: 3
  // already_checked: 4
  // collect_declarations: 5
  frame->slots[0] = myself->closure.frame->slots[1]; /* chr */
  frame->slots[1] = myself->closure.frame->slots[3]; /* buf */
  frame->slots[2] = myself->closure.frame->slots[2]; /* s */
  frame->slots[3] = myself->closure.frame->slots[0]; /* idx */
  frame->slots[4] = myself->closure.frame->slots[4]; /* already_checked */
  frame->slots[5] = myself->closure.frame->slots[5]; /* collect_declarations */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 685: ... chr.is_a_letter
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  result_count = 1;
  myself = get__is_a_letter();
  func = myself->type;
  frame->cont = cont__78_6;
}
static void cont__78_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 685: ... chr == '_' || chr.is_a_digit
  frame->slots[8] /* temp__3 */ = create_closure(entry__78_7, 0);
  // 685: ... chr.is_a_letter || chr == '_' || chr.is_a_digit
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  arguments->slots[1] = frame->slots[8] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__78_12;
}
static void entry__78_7(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 685: ... chr == '_'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__95;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__78_8;
}
static void cont__78_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 685: ... chr.is_a_digit
  frame->slots[3] /* temp__3 */ = create_closure(entry__78_9, 0);
  // 685: ... chr == '_' || chr.is_a_digit
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__78_11;
}
static void entry__78_9(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 685: ... chr.is_a_digit
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  result_count = 1;
  myself = get__is_a_digit();
  func = myself->type;
  frame->cont = cont__78_10;
}
static void cont__78_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 685: ... chr.is_a_digit
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__78_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 685: ... chr == '_' || chr.is_a_digit
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__78_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 685: ... :
  // 686:   $symbol range(buf s idx-1)
  // 687:   !s undefined
  // 688:   unless already_checked(symbol):
  // 689:     !already_checked(symbol) true
  // 690:     $declaration runtime_symbols(symbol)
  // 691:     if declaration.is_defined:
  // 692:       $do_import
  // 693:         &&
  // 694:           declaration(1) != '#'
  // ...
  frame->slots[9] /* temp__4 */ = create_closure(entry__78_13, 0);
  // 685: unless chr.is_a_letter || chr == '_' || chr.is_a_digit:
  // 686:   $symbol range(buf s idx-1)
  // 687:   !s undefined
  // 688:   unless already_checked(symbol):
  // 689:     !already_checked(symbol) true
  // 690:     $declaration runtime_symbols(symbol)
  // 691:     if declaration.is_defined:
  // 692:       $do_import
  // 693:         &&
  // 694:           declaration(1) != '#'
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
static void entry__78_57(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // chr: 0
  // s: 1
  // idx: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* chr */
  frame->slots[1] = myself->closure.frame->slots[2]; /* s */
  frame->slots[2] = myself->closure.frame->slots[0]; /* idx */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 711: ... chr.is_a_letter
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  result_count = 1;
  myself = get__is_a_letter();
  func = myself->type;
  frame->cont = cont__78_58;
}
static void cont__78_58(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 711: ... chr == '_'
  frame->slots[5] /* temp__3 */ = create_closure(entry__78_59, 0);
  // 711: ... chr.is_a_letter || chr == '_'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__78_61;
}
static void entry__78_59(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 711: ... chr == '_'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__95;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__78_60;
}
static void cont__78_60(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 711: ... chr == '_'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__78_61(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 711: ... : !s idx
  frame->slots[6] /* temp__4 */ = create_closure(entry__78_62, 0);
  // 711: if chr.is_a_letter || chr == '_': !s idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__78_3(void) {
  allocate_initialized_frame_gc(6, 9);
  // slot allocations:
  // idx: 0
  // chr: 1
  // s: 2
  // buf: 3
  // already_checked: 4
  // collect_declarations: 5
  frame->slots[2] = myself->closure.frame->slots[3]; /* s */
  frame->slots[3] = myself->closure.frame->slots[0]; /* buf */
  frame->slots[4] = myself->closure.frame->slots[1]; /* already_checked */
  frame->slots[5] = myself->closure.frame->slots[2]; /* collect_declarations */
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 684: s.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* s */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__78_4;
}
static void cont__78_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 684: ... :
  // 685:   unless chr.is_a_letter || chr == '_' || chr.is_a_digit:
  // 686:     $symbol range(buf s idx-1)
  // 687:     !s undefined
  // 688:     unless already_checked(symbol):
  // 689:       !already_checked(symbol) true
  // 690:       $declaration runtime_symbols(symbol)
  // 691:       if declaration.is_defined:
  // 692:         $do_import
  // 693:           &&
  // ...
  frame->slots[7] /* temp__2 */ = create_closure(entry__78_5, 0);
  // 710: :
  // 711:   if chr.is_a_letter || chr == '_': !s idx
  frame->slots[8] /* temp__3 */ = create_closure(entry__78_57, 0);
  // 683: if
  // 684:   s.is_defined:
  // 685:     unless chr.is_a_letter || chr == '_' || chr.is_a_digit:
  // 686:       $symbol range(buf s idx-1)
  // 687:       !s undefined
  // 688:       unless already_checked(symbol):
  // 689:         !already_checked(symbol) true
  // 690:         $declaration runtime_symbols(symbol)
  // 691:         if declaration.is_defined:
  // 692:           $do_import
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  arguments->slots[2] = frame->slots[8] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__78_2_collect_declarations(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // buf: 0
  // already_checked: 1
  // collect_declarations: 2
  // s: 3
  frame->slots[1] = myself->closure.frame->slots[1]; /* already_checked */
  frame->slots[2] = myself->closure.frame->slots[2]; /* collect_declarations */
  frame->slots[3] /* s */ = create_cell();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 681: $$s undefined
  ((CELL *)frame->slots[3])->contents /* s */ = get__undefined();
  // 682: ... : (idx chr)
  // 683:   if
  // 684:     s.is_defined:
  // 685:       unless chr.is_a_letter || chr == '_' || chr.is_a_digit:
  // 686:         $symbol range(buf s idx-1)
  // 687:         !s undefined
  // 688:         unless already_checked(symbol):
  // 689:           !already_checked(symbol) true
  // 690:           $declaration runtime_symbols(symbol)
  // 691:           if declaration.is_defined:
  // ...
  frame->slots[4] /* temp__1 */ = create_closure(entry__78_3, 2);
  // 682: for_each buf: (idx chr)
  // 683:   if
  // 684:     s.is_defined:
  // 685:       unless chr.is_a_letter || chr == '_' || chr.is_a_digit:
  // 686:         $symbol range(buf s idx-1)
  // 687:         !s undefined
  // 688:         unless already_checked(symbol):
  // 689:           !already_checked(symbol) true
  // 690:           $declaration runtime_symbols(symbol)
  // 691:           if declaration.is_defined:
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* buf */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__78_63(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // collect_declarations: 0
  // source: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* collect_declarations */
  frame->slots[1] = myself->closure.frame->slots[0]; /* source */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 713: ... collect_declarations source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* source */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* collect_declarations */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__78_64(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* imports */, arguments->slots[0]);
  // 714: $first_part source .before. "// INSERT HERE //"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  arguments->slots[1] = string__78_65;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__78_66;
}
static void cont__78_66(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* first_part */, arguments->slots[0]);
  // 715: write first_part
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* first_part */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__78_67;
}
static void cont__78_67(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 716: write imports
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* imports */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__78_68;
}
static void cont__78_68(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 717: ... length_of(first_part)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* first_part */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__78_69;
}
static void cont__78_69(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__3 */ = arguments->slots[0];
  // 717: ... length_of(first_part)+18
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__3 */;
  arguments->slots[1] = number__18;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__78_70;
}
static void cont__78_70(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 717: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__78_71;
}
static void cont__78_71(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__4 */ = arguments->slots[0];
  // 717: ... range(source length_of(first_part)+18 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  arguments->slots[2] = frame->slots[8] /* temp__4 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__78_72;
}
static void cont__78_72(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 717: write range(source length_of(first_part)+18 -1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__78_73;
}
static void cont__78_73(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 718: if do_time_passes: write_timing_info "collecting imports"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = func__78_74;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__79_1_compile_exe(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // body: 0
  // return__1: 1
  // mod_filename: 2
  // mod_name: 3
  frame->slots[1] /* return__1 */ = create_continuation();
  // _define %mode EXE
  define__mode(var._EXE);
  frame->slots[2] /* mod_filename */ = create_future();
  frame->slots[3] /* mod_name */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 721: ... main_info.is_a_directory
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_info();
  result_count = 1;
  myself = get__is_a_directory();
  func = myself->type;
  frame->cont = cont__79_2;
}
static void cont__79_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 721: if main_info.is_a_directory: Error "Expected a source code file!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = func__79_3;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__79_5;
}
static void entry__79_3(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 721: ... Error "Expected a source code file!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__79_4;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__79_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 722: ... main_filename .has_suffix. ".sim"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  arguments->slots[1] = string__67_13;
  result_count = 1;
  myself = get__has_suffix();
  func = myself->type;
  frame->cont = cont__79_6;
}
static void cont__79_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 722: unless main_filename .has_suffix. ".sim":
  // 723:   Error "
  // 724:     Expected ".sim" file extension in source filename!@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = func__79_7;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__79_9;
}
static void entry__79_7(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 723: Error "
  // 724:   Expected ".sim" file extension in source filename!@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__79_8;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__79_9(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 726: $mod_filename main_filename .without_suffix. ".sim"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  arguments->slots[1] = string__67_13;
  result_count = 1;
  myself = get__without_suffix();
  func = myself->type;
  frame->cont = cont__79_10;
}
static void cont__79_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* mod_filename */, arguments->slots[0]);
  // 727: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__79_11;
}
static void cont__79_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 727: $mod_name truncate_until(mod_filename '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* mod_filename */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__79_12;
}
static void cont__79_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* mod_name */, arguments->slots[0]);
  // 728: body mod_filename mod_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* mod_filename */;
  arguments->slots[1] = frame->slots[3] /* mod_name */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame->cont = cont__79_13;
}
static void cont__79_13(void) {
  myself = frame->slots[1] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__80_2(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // mod_filename: 0
  // mod_name: 1
  // return__1: 2
  frame->slots[2] /* return__1 */ = create_continuation();
  // _define %sim2c::module_name mod_name
  define__sim2c__module_name(frame->slots[1] /* mod_name */);
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 732: %sim2c::module_name mod_name
  initialize_maybe_future(get__sim2c__module_name(), frame->slots[1] /* mod_name */);
  // 733: ... list(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__80_3;
}
static void cont__80_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 733: sim2c list(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__sim2c();
  func = myself->type;
  frame->cont = cont__80_4;
}
static void cont__80_4(void) {
  myself = frame->slots[2] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__80_1_dump_source_or_check(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 731: compile_exe: (_mod_filename mod_name)
  // 732:   %sim2c::module_name mod_name
  // 733:   sim2c list(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__80_2;
  result_count = frame->caller_result_count;
  myself = var._compile_exe;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__81_18(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 743: ... write_timing_info "writing C-source"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__81_19;
  result_count = frame->caller_result_count;
  myself = get__write_timing_info();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__81_2(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // mod_filename: 0
  // mod_name: 1
  // c_source: 2
  // c_buf: 3
  frame->slots[2] /* c_source */ = create_future();
  frame->slots[3] /* c_buf */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  frame->slots[1] /* mod_name */ = create_cell_with_contents(arguments->slots[1]);
  // 737: ... module_prefix.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._module_prefix;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__81_3;
}
static void cont__81_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 737: ... : append string(module_prefix '/') &mod_name
  frame->slots[5] /* temp__2 */ = create_closure(entry__81_4, 0);
  // 737: if module_prefix.is_defined: append string(module_prefix '/') &mod_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__81_7;
}
static void entry__81_4(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // mod_name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* mod_name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 737: ... string(module_prefix '/')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._module_prefix;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__81_5;
}
static void cont__81_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 737: ... append string(module_prefix '/') &mod_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* mod_name */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__81_6;
}
static void cont__81_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* mod_name */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__81_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 738: ... :
  // 739:   %sim2c::module_name replace_all(mod_name '/' = "__" '.' = "__")
  // 740:   sim2c list(main_filename)
  frame->slots[4] /* temp__1 */ = create_closure(entry__81_8, 0);
  // 738: collect_output $c_source:
  // 739:   %sim2c::module_name replace_all(mod_name '/' = "__" '.' = "__")
  // 740:   sim2c list(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__81_14;
}
static void entry__81_8(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // return__1: 0
  // mod_name: 1
  frame->slots[0] /* return__1 */ = create_continuation();
  frame->slots[1] = myself->closure.frame->slots[1]; /* mod_name */
  define__sim2c__module_name(create_future());
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 739: ... '/' = "__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = string__73_38;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__81_9;
}
static void cont__81_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 739: ... '.' = "__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__46;
  arguments->slots[1] = string__73_38;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__81_10;
}
static void cont__81_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 739: %sim2c::module_name replace_all(mod_name '/' = "__" '.' = "__")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* mod_name */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  arguments->slots[2] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__81_11;
}
static void cont__81_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(get__sim2c__module_name(), arguments->slots[0]);
  // 740: ... list(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__81_12;
}
static void cont__81_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 740: sim2c list(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__sim2c();
  func = myself->type;
  frame->cont = cont__81_13;
}
static void cont__81_13(void) {
  myself = frame->slots[0] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__81_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* c_source */, arguments->slots[0]);
  // 741: ... : create_imports c_source
  frame->slots[4] /* temp__1 */ = create_closure(entry__81_15, 0);
  // 741: collect_output $c_buf: create_imports c_source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__81_16;
}
static void entry__81_15(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // c_source: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* c_source */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 741: ... create_imports c_source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_source */;
  result_count = frame->caller_result_count;
  myself = var._create_imports;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__81_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* c_buf */, arguments->slots[0]);
  // 742: write c_buf
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* c_buf */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__81_17;
}
static void cont__81_17(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 743: if do_time_passes: write_timing_info "writing C-source"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = func__81_18;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__81_1_print_c(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 736: compile_exe: (_mod_filename $mod_name)
  // 737:   if module_prefix.is_defined: append string(module_prefix '/') &mod_name
  // 738:   collect_output $c_source:
  // 739:     %sim2c::module_name replace_all(mod_name '/' = "__" '.' = "__")
  // 740:     sim2c list(main_filename)
  // 741:   collect_output $c_buf: create_imports c_source
  // 742:   write c_buf
  // 743:   if do_time_passes: write_timing_info "writing C-source"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__81_2;
  result_count = frame->caller_result_count;
  myself = var._compile_exe;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__82_35(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // filename: 0
  // prefix_path: 1
  frame->slots[1] = myself->closure.frame->slots[0]; /* prefix_path */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* filename */ = create_cell_with_contents(arguments->slots[0]);
  // 772: without_prefix &filename prefix_path
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* filename */;
  arguments->slots[1] = frame->slots[1] /* prefix_path */;
  result_count = 1;
  myself = get__without_prefix();
  func = myself->type;
  frame->cont = cont__82_36;
}
static void cont__82_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* filename */ = arguments->slots[0];
  // 773: without_prefix &filename '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* filename */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__without_prefix();
  func = myself->type;
  frame->cont = cont__82_37;
}
static void cont__82_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* filename */ = arguments->slots[0];
  // 774: writeln filename
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* filename */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__82_1_list_dependencies(void) {
  allocate_initialized_frame_gc(0, 2);
  // slot allocations:
  // prefix_path: 0
  frame->slots[0] /* prefix_path */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 746: !platform_specific_priority multi_dimensional_table(types::table types::table)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__types__table();
  arguments->slots[1] = get__types__table();
  result_count = 1;
  myself = get__multi_dimensional_table();
  func = myself->type;
  frame->cont = cont__82_2;
}
static void cont__82_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._platform_specific_priority = arguments->slots[0];
  // 747: for_each supported_platforms: (supported_platform _parent_platform)
  // 748:   $$platform supported_platform
  // 749:   $$priority 0
  // 750:   do: (-> break)
  // 751:     forever:
  // 752:       $plat supported_platforms(platform)
  // 753:       if plat.is_undefined break
  // 754:       inc &priority
  // 755:       !platform_specific_priority(supported_platform platform) priority
  // 756:       if plat == NONE break
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._supported_platforms;
  arguments->slots[1] = func__82_3;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__82_14;
}
static void entry__82_4(void) {
  allocate_initialized_frame_gc(4, 5);
  // slot allocations:
  // break: 0
  // platform: 1
  // priority: 2
  // supported_platform: 3
  frame->slots[0] /* break */ = create_continuation();
  frame->slots[1] = myself->closure.frame->slots[2]; /* platform */
  frame->slots[2] = myself->closure.frame->slots[3]; /* priority */
  frame->slots[3] = myself->closure.frame->slots[0]; /* supported_platform */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 751: ... :
  // 752:   $plat supported_platforms(platform)
  // 753:   if plat.is_undefined break
  // 754:   inc &priority
  // 755:   !platform_specific_priority(supported_platform platform) priority
  // 756:   if plat == NONE break
  // 757:   !platform plat
  frame->slots[4] /* temp__1 */ = create_closure(entry__82_5, 0);
  // 751: forever:
  // 752:   $plat supported_platforms(platform)
  // 753:   if plat.is_undefined break
  // 754:   inc &priority
  // 755:   !platform_specific_priority(supported_platform platform) priority
  // 756:   if plat == NONE break
  // 757:   !platform plat
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame->cont = cont__82_13;
}
static void entry__82_5(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // platform: 0
  // break: 1
  // priority: 2
  // supported_platform: 3
  // plat: 4
  frame->slots[0] = myself->closure.frame->slots[1]; /* platform */
  frame->slots[1] = myself->closure.frame->slots[0]; /* break */
  frame->slots[2] = myself->closure.frame->slots[2]; /* priority */
  frame->slots[3] = myself->closure.frame->slots[3]; /* supported_platform */
  frame->slots[4] /* plat */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 752: $plat supported_platforms(platform)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* platform */;
  result_count = 1;
  myself = var._supported_platforms;
  func = myself->type;
  frame->cont = cont__82_6;
}
static void cont__82_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* plat */, arguments->slots[0]);
  // 753: ... plat.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* plat */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__82_7;
}
static void cont__82_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 753: if plat.is_undefined break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* break */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__82_8;
}
static void cont__82_8(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 754: inc &priority
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* priority */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__82_9;
}
static void cont__82_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* priority */ = arguments->slots[0];
  // 755: !platform_specific_priority(supported_platform platform) priority
  frame->slots[5] /* temp__1 */ = ((CELL *)frame->slots[2])->contents /* priority */;
  // 755: !platform_specific_priority(supported_platform platform)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* supported_platform */;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* platform */;
  arguments->slots[2] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = var._platform_specific_priority;
  func = myself->type;
  frame->cont = cont__82_10;
}
static void cont__82_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._platform_specific_priority = arguments->slots[0];
  // 756: ... plat == NONE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* plat */;
  arguments->slots[1] = var._NONE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__82_11;
}
static void cont__82_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 756: if plat == NONE break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* break */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__82_12;
}
static void cont__82_12(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 757: !platform plat
  ((CELL *)frame->slots[0])->contents /* platform */ = frame->slots[4] /* plat */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__82_13(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__82_3(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // supported_platform: 0
  // parent_platform: 1
  // platform: 2
  // priority: 3
  frame->slots[2] /* platform */ = create_cell();
  frame->slots[3] /* priority */ = create_cell();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 748: $$platform supported_platform
  ((CELL *)frame->slots[2])->contents /* platform */ = frame->slots[0] /* supported_platform */;
  // 749: $$priority 0
  ((CELL *)frame->slots[3])->contents /* priority */ = number__0;
  // 750: ... : (-> break)
  // 751:   forever:
  // 752:     $plat supported_platforms(platform)
  // 753:     if plat.is_undefined break
  // 754:     inc &priority
  // 755:     !platform_specific_priority(supported_platform platform) priority
  // 756:     if plat == NONE break
  // 757:     !platform plat
  frame->slots[4] /* temp__1 */ = create_closure(entry__82_4, 0);
  // 750: do: (-> break)
  // 751:   forever:
  // 752:     $plat supported_platforms(platform)
  // 753:     if plat.is_undefined break
  // 754:     inc &priority
  // 755:     !platform_specific_priority(supported_platform platform) priority
  // 756:     if plat == NONE break
  // 757:     !platform plat
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__do();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__82_14(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 759: main_info.is_a_directory
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_info();
  result_count = 1;
  myself = get__is_a_directory();
  func = myself->type;
  frame->cont = cont__82_15;
}
static void cont__82_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 758: if
  // 759:   main_info.is_a_directory:
  // 760:     %mode LIB
  // 761:     if verbose: ewriteln "list dependencies for " main_filename
  // 762:     compile_modules main_filename behind(main_filename '/' -1)
  // 763:   :
  // 764:     compile_exe: (mod_filename mod_name)
  // 765:       if verbose: ewriteln "list dependencies for " mod_filename
  // 766:       compile_module mod_filename mod_name
  // 767:     writeln "runtime/linker.c"
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__82_16;
  arguments->slots[2] = func__82_23;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__82_33;
}
static void entry__82_16(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // return__1: 0
  frame->slots[0] /* return__1 */ = create_continuation();
  // _define %mode LIB
  define__mode(var._LIB);
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 761: if verbose: ewriteln "list dependencies for " main_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = func__82_17;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__82_19;
}
static void entry__82_17(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 761: ... ewriteln "list dependencies for " main_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__82_18;
  arguments->slots[1] = get__main_filename();
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__82_19(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 762: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__82_20;
}
static void cont__82_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 762: ... behind(main_filename '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__82_21;
}
static void cont__82_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 762: compile_modules main_filename behind(main_filename '/' -1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = var._compile_modules;
  func = myself->type;
  frame->cont = cont__82_22;
}
static void cont__82_22(void) {
  myself = frame->slots[0] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__82_23(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 764: compile_exe: (mod_filename mod_name)
  // 765:   if verbose: ewriteln "list dependencies for " mod_filename
  // 766:   compile_module mod_filename mod_name
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__82_24;
  result_count = 0;
  myself = var._compile_exe;
  func = myself->type;
  frame->cont = cont__82_27;
}
static void entry__82_24(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // mod_filename: 0
  // mod_name: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 765: ... : ewriteln "list dependencies for " mod_filename
  frame->slots[2] /* temp__1 */ = create_closure(entry__82_25, 0);
  // 765: if verbose: ewriteln "list dependencies for " mod_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__82_26;
}
static void entry__82_25(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // mod_filename: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* mod_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 765: ... ewriteln "list dependencies for " mod_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__82_18;
  arguments->slots[1] = frame->slots[0] /* mod_filename */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__82_26(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 766: compile_module mod_filename mod_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = frame->slots[1] /* mod_name */;
  result_count = frame->caller_result_count;
  myself = var._compile_module;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__82_27(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 767: writeln "runtime/linker.c"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__82_28;
  result_count = 0;
  myself = get__writeln();
  func = myself->type;
  frame->cont = cont__82_29;
}
static void cont__82_29(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 768: writeln "runtime/memory.c"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__82_30;
  result_count = 0;
  myself = get__writeln();
  func = myself->type;
  frame->cont = cont__82_31;
}
static void cont__82_31(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 769: writeln "runtime/debugger.c"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__82_32;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__82_33(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 770: $prefix_path current_path()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__current_path();
  func = myself->type;
  frame->cont = cont__82_34;
}
static void cont__82_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[0] /* prefix_path */, arguments->slots[0]);
  // 771: ... : ($filename)
  // 772:   without_prefix &filename prefix_path
  // 773:   without_prefix &filename '/'
  // 774:   writeln filename
  frame->slots[1] /* temp__1 */ = create_closure(entry__82_35, 1);
  // 771: for_each dependencies: ($filename)
  // 772:   without_prefix &filename prefix_path
  // 773:   without_prefix &filename '/'
  // 774:   writeln filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._dependencies;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__83_2(void) {
  allocate_initialized_frame_gc(2, 14);
  // slot allocations:
  // mod_filename: 0
  // mod_name: 1
  // codeblocks_path: 2
  // info: 3
  // basename: 4
  // prefix_path: 5
  // depth: 6
  // path_prefix: 7
  // cbp_filename: 8
  // buf: 9
  frame->slots[2] /* codeblocks_path */ = create_future();
  frame->slots[3] /* info */ = create_future();
  frame->slots[4] /* basename */ = create_future();
  frame->slots[5] /* prefix_path */ = create_future();
  frame->slots[6] /* depth */ = create_future();
  frame->slots[7] /* path_prefix */ = create_future();
  frame->slots[8] /* cbp_filename */ = create_future();
  frame->slots[9] /* buf */ = create_cell();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 778: $codeblocks_path string(mod_filename ".codeblocks")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = string__83_3;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__83_4;
}
static void cont__83_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* codeblocks_path */, arguments->slots[0]);
  // 779: $info stat(codeblocks_path)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* codeblocks_path */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__83_5;
}
static void cont__83_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* info */, arguments->slots[0]);
  // 780: ... info.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* info */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__83_6;
}
static void cont__83_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 780: ... :
  // 781:   ewrite "
  // 782:     The directory "@(codeblocks_path)" already exists!
  frame->slots[11] /* temp__2 */ = create_closure(entry__83_7, 0);
  // 780: if info.is_defined:
  // 781:   ewrite "
  // 782:     The directory "@(codeblocks_path)" already exists!
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__1 */;
  arguments->slots[1] = frame->slots[11] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__83_11;
}
static void entry__83_7(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // codeblocks_path: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* codeblocks_path */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 781: ... "
  // 782:   The directory "@(codeblocks_path)" already exists!
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__83_8;
  arguments->slots[1] = frame->slots[0] /* codeblocks_path */;
  arguments->slots[2] = string__83_9;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__83_10;
}
static void cont__83_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 781: ewrite "
  // 782:   The directory "@(codeblocks_path)" already exists!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewrite();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__83_11(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 783: ... : ewriteln "build Code::Blocks project in " codeblocks_path
  frame->slots[10] /* temp__1 */ = create_closure(entry__83_12, 0);
  // 783: if verbose: ewriteln "build Code::Blocks project in " codeblocks_path
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = frame->slots[10] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__83_14;
}
static void entry__83_12(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // codeblocks_path: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* codeblocks_path */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 783: ... ewriteln "build Code::Blocks project in " codeblocks_path
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__83_13;
  arguments->slots[1] = frame->slots[0] /* codeblocks_path */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__83_14(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 784: compile_module mod_filename mod_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = frame->slots[1] /* mod_name */;
  result_count = 0;
  myself = var._compile_module;
  func = myself->type;
  frame->cont = cont__83_15;
}
static void cont__83_15(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 785: show_file_list
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._show_file_list;
  func = myself->type;
  frame->cont = cont__83_16;
}
static void cont__83_16(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 786: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__83_17;
}
static void cont__83_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__2 */ = arguments->slots[0];
  // 786: ... truncate_until(main_filename '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[11] /* temp__2 */;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__83_18;
}
static void cont__83_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 786: $basename truncate_until(main_filename '/' -1) .without_suffix. ".sim"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__1 */;
  arguments->slots[1] = string__67_13;
  result_count = 1;
  myself = get__without_suffix();
  func = myself->type;
  frame->cont = cont__83_19;
}
static void cont__83_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* basename */, arguments->slots[0]);
  // 787: $prefix_path current_path()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__current_path();
  func = myself->type;
  frame->cont = cont__83_20;
}
static void cont__83_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* prefix_path */, arguments->slots[0]);
  // 788: ... codeblocks_path .without_prefix. prefix_path
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* codeblocks_path */;
  arguments->slots[1] = frame->slots[5] /* prefix_path */;
  result_count = 1;
  myself = get__without_prefix();
  func = myself->type;
  frame->cont = cont__83_21;
}
static void cont__83_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 788: $depth count_occurrences(codeblocks_path .without_prefix. prefix_path '/')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__1 */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__count_occurrences();
  func = myself->type;
  frame->cont = cont__83_22;
}
static void cont__83_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* depth */, arguments->slots[0]);
  // 789: $path_prefix dup("../" depth)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__83_23;
  arguments->slots[1] = frame->slots[6] /* depth */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__83_24;
}
static void cont__83_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[7] /* path_prefix */, arguments->slots[0]);
  // 790: $cbp_filename string(codeblocks_path "/" basename ".cbp")
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* codeblocks_path */;
  arguments->slots[1] = string__83_25;
  arguments->slots[2] = frame->slots[4] /* basename */;
  arguments->slots[3] = string__83_26;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__83_27;
}
static void cont__83_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[8] /* cbp_filename */, arguments->slots[0]);
  // 791: mkdir codeblocks_path
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* codeblocks_path */;
  result_count = 0;
  myself = var._mkdir;
  func = myself->type;
  frame->cont = cont__83_28;
}
static void cont__83_28(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 792: $$buf ""
  ((CELL *)frame->slots[9])->contents /* buf */ = empty_string;
  // 793: ... "
  // 794:   <?xml version="1.0" encoding="UTF-8" standalone="yes" ?>
  // 795:   <CodeBlocks_project_file>
  // 796:     <FileVersion major="1" minor="6" />
  // 797:     <Project>
  // 798:       <Option title="@(basename)" />
  // 799:       <Option pch_mode="2" />
  // 800:       <Option compiler=c_compiler() />
  // 801:       <Build>
  // 802:         <Target title="debug">
  // ...
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__83_29;
  arguments->slots[1] = frame->slots[4] /* basename */;
  arguments->slots[2] = string__83_30;
  arguments->slots[3] = frame->slots[4] /* basename */;
  arguments->slots[4] = string__83_31;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__83_32;
}
static void cont__83_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 793: write_to &buf "
  // 794:   <?xml version="1.0" encoding="UTF-8" standalone="yes" ?>
  // 795:   <CodeBlocks_project_file>
  // 796:     <FileVersion major="1" minor="6" />
  // 797:     <Project>
  // 798:       <Option title="@(basename)" />
  // 799:       <Option pch_mode="2" />
  // 800:       <Option compiler=c_compiler() />
  // 801:       <Build>
  // 802:         <Target title="debug">
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[9])->contents /* buf */;
  arguments->slots[1] = frame->slots[10] /* temp__1 */;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__83_33;
}
static void cont__83_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[9])->contents /* buf */ = arguments->slots[0];
  // 814: ... : (filename)
  // 815:   write_to &buf "
  // 816:     @
  // 817:           <Add library="@(filename)" />
  frame->slots[10] /* temp__1 */ = create_closure(entry__83_34, 1);
  // 814: for_each libraries: (filename)
  // 815:   write_to &buf "
  // 816:     @
  // 817:           <Add library="@(filename)" />
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__libraries();
  arguments->slots[1] = frame->slots[10] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__83_39;
}
static void entry__83_34(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // filename: 0
  // buf: 1
  frame->slots[1] = myself->closure.frame->slots[9]; /* buf */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 815: ... "
  // 816:   @
  // 817:         <Add library="@(filename)" />
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__83_35;
  arguments->slots[1] = frame->slots[0] /* filename */;
  arguments->slots[2] = string__83_36;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__83_37;
}
static void cont__83_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 815: write_to &buf "
  // 816:   @
  // 817:         <Add library="@(filename)" />
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* buf */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__83_38;
}
static void cont__83_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* buf */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__83_39(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 828: ... c_compiler()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__c_compiler();
  func = myself->type;
  frame->cont = cont__83_40;
}
static void cont__83_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__2 */ = arguments->slots[0];
  // 831: ... c_compiler()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__c_compiler();
  func = myself->type;
  frame->cont = cont__83_41;
}
static void cont__83_41(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__3 */ = arguments->slots[0];
  // 834: ... c_compiler()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__c_compiler();
  func = myself->type;
  frame->cont = cont__83_42;
}
static void cont__83_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__4 */ = arguments->slots[0];
  // 818: ... "
  // 819:   @
  // 820:   
  // 821:       </Linker>
  // 822:       <Compiler>
  // 823:         <Add option="-Wall" />
  // 824:       </Compiler>
  // 825:       <Unit filename="@(path_prefix)runtime/common.h" />
  // 826:       <Unit filename="@(path_prefix)runtime/linker.h" />
  // 827:       <Unit filename="@(path_prefix)runtime/memory.c">
  // ...
  argument_count = 17;
  arguments = node_p;
  arguments->slots[0] = string__83_43;
  arguments->slots[1] = frame->slots[7] /* path_prefix */;
  arguments->slots[2] = string__83_44;
  arguments->slots[3] = frame->slots[7] /* path_prefix */;
  arguments->slots[4] = string__83_45;
  arguments->slots[5] = frame->slots[7] /* path_prefix */;
  arguments->slots[6] = string__83_46;
  arguments->slots[7] = frame->slots[11] /* temp__2 */;
  arguments->slots[8] = string__83_47;
  arguments->slots[9] = frame->slots[7] /* path_prefix */;
  arguments->slots[10] = string__83_48;
  arguments->slots[11] = frame->slots[12] /* temp__3 */;
  arguments->slots[12] = string__83_47;
  arguments->slots[13] = frame->slots[7] /* path_prefix */;
  arguments->slots[14] = string__83_49;
  arguments->slots[15] = frame->slots[13] /* temp__4 */;
  arguments->slots[16] = string__83_50;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__83_51;
}
static void cont__83_51(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 818: write_to &buf "
  // 819:   @
  // 820:   
  // 821:       </Linker>
  // 822:       <Compiler>
  // 823:         <Add option="-Wall" />
  // 824:       </Compiler>
  // 825:       <Unit filename="@(path_prefix)runtime/common.h" />
  // 826:       <Unit filename="@(path_prefix)runtime/linker.h" />
  // 827:       <Unit filename="@(path_prefix)runtime/memory.c">
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[9])->contents /* buf */;
  arguments->slots[1] = frame->slots[10] /* temp__1 */;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__83_52;
}
static void cont__83_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[9])->contents /* buf */ = arguments->slots[0];
  // 836: ... : ($filename)
  // 837:   without_prefix &filename prefix_path
  // 838:   without_prefix &filename '/'
  // 839:   write_to &buf "
  // 840:     @
  // 841:     
  // 842:         <Unit filename="@(path_prefix)@(filename)">
  // 843:           <Option compilerVar="@(c_compiler())" />
  // 844:         </Unit>
  frame->slots[10] /* temp__1 */ = create_closure(entry__83_53, 1);
  // 836: for_each c_sources: ($filename)
  // 837:   without_prefix &filename prefix_path
  // 838:   without_prefix &filename '/'
  // 839:   write_to &buf "
  // 840:     @
  // 841:     
  // 842:         <Unit filename="@(path_prefix)@(filename)">
  // 843:           <Option compilerVar="@(c_compiler())" />
  // 844:         </Unit>
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._c_sources;
  arguments->slots[1] = frame->slots[10] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__83_61;
}
static void entry__83_53(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // filename: 0
  // prefix_path: 1
  // buf: 2
  // path_prefix: 3
  frame->slots[1] = myself->closure.frame->slots[5]; /* prefix_path */
  frame->slots[2] = myself->closure.frame->slots[9]; /* buf */
  frame->slots[3] = myself->closure.frame->slots[7]; /* path_prefix */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* filename */ = create_cell_with_contents(arguments->slots[0]);
  // 837: without_prefix &filename prefix_path
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* filename */;
  arguments->slots[1] = frame->slots[1] /* prefix_path */;
  result_count = 1;
  myself = get__without_prefix();
  func = myself->type;
  frame->cont = cont__83_54;
}
static void cont__83_54(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* filename */ = arguments->slots[0];
  // 838: without_prefix &filename '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* filename */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__without_prefix();
  func = myself->type;
  frame->cont = cont__83_55;
}
static void cont__83_55(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* filename */ = arguments->slots[0];
  // 843: ... c_compiler()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__c_compiler();
  func = myself->type;
  frame->cont = cont__83_56;
}
static void cont__83_56(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 839: ... "
  // 840:   @
  // 841:   
  // 842:       <Unit filename="@(path_prefix)@(filename)">
  // 843:         <Option compilerVar="@(c_compiler())" />
  // 844:       </Unit>
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = string__83_57;
  arguments->slots[1] = frame->slots[3] /* path_prefix */;
  arguments->slots[2] = ((CELL *)frame->slots[0])->contents /* filename */;
  arguments->slots[3] = string__83_58;
  arguments->slots[4] = frame->slots[5] /* temp__2 */;
  arguments->slots[5] = string__83_50;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__83_59;
}
static void cont__83_59(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 839: write_to &buf "
  // 840:   @
  // 841:   
  // 842:       <Unit filename="@(path_prefix)@(filename)">
  // 843:         <Option compilerVar="@(c_compiler())" />
  // 844:       </Unit>
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* buf */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__83_60;
}
static void cont__83_60(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* buf */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__83_61(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 845: write_to &buf "
  // 846:       <Extensions>
  // 847:         <code_completion />
  // 848:         <debugger />
  // 849:       </Extensions>
  // 850:     </Project>
  // 851:   </CodeBlocks_project_file>
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[9])->contents /* buf */;
  arguments->slots[1] = string__83_62;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__83_63;
}
static void cont__83_63(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[9])->contents /* buf */ = arguments->slots[0];
  // 852: save cbp_filename buf
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* cbp_filename */;
  arguments->slots[1] = ((CELL *)frame->slots[9])->contents /* buf */;
  result_count = frame->caller_result_count;
  myself = get__save();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__83_1_build_codeblocks_project(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 777: compile_exe: (mod_filename mod_name)
  // 778:   $codeblocks_path string(mod_filename ".codeblocks")
  // 779:   $info stat(codeblocks_path)
  // 780:   if info.is_defined:
  // 781:     ewrite "
  // 782:       The directory "@(codeblocks_path)" already exists!
  // 783:   if verbose: ewriteln "build Code::Blocks project in " codeblocks_path
  // 784:   compile_module mod_filename mod_name
  // 785:   show_file_list
  // 786:   $basename truncate_until(main_filename '/' -1) .without_suffix. ".sim"
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__83_2;
  result_count = frame->caller_result_count;
  myself = var._compile_exe;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__84_1_build_library(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // return__1: 0
  frame->slots[0] /* return__1 */ = create_continuation();
  // _define %mode LIB
  define__mode(var._LIB);
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 855: ... action == "simrun"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._action;
  arguments->slots[1] = string__84_2;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__84_3;
}
static void cont__84_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 855: if action == "simrun": Error "Cannot run a directory!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__84_4;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__84_6;
}
static void entry__84_4(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 855: ... Error "Cannot run a directory!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__84_5;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__84_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 857: if
  // 858:   do_extract_documentation:
  // 859:     extract_documentation main_filename
  // 860:   :
  // 861:     $$version ""
  // 862:     $$so_version ""
  // 863:     $version_filename string(main_filename "/VERSION")
  // 864:     if file_exists(version_filename):
  // 865:       !version string('-' load(version_filename).trim)
  // 866:       !so_version version .truncate_from. '.'
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__do_extract_documentation();
  arguments->slots[1] = func__84_7;
  arguments->slots[2] = func__84_8;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__84_90;
}
static void entry__84_88(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // err: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* err */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 927: ... err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* err */;
  result_count = 1;
  myself = get__from_utf8();
  func = myself->type;
  frame->cont = cont__84_89;
}
static void cont__84_89(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 927: ... Error err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__84_83(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // err: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* err */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 920: ... err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* err */;
  result_count = 1;
  myself = get__from_utf8();
  func = myself->type;
  frame->cont = cont__84_84;
}
static void cont__84_84(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 920: ... Error err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__84_74(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // err: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* err */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 909: ... err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* err */;
  result_count = 1;
  myself = get__from_utf8();
  func = myself->type;
  frame->cont = cont__84_75;
}
static void cont__84_75(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 909: ... Error err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__84_67(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // err: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* err */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 901: ... err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* err */;
  result_count = 1;
  myself = get__from_utf8();
  func = myself->type;
  frame->cont = cont__84_68;
}
static void cont__84_68(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 901: ... Error err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__84_61(void) {
  allocate_initialized_frame_gc(3, 11);
  // slot allocations:
  // base_filename: 0
  // so_version: 1
  // lib_filename: 2
  // out: 3
  // err: 4
  // success: 5
  frame->slots[0] = myself->closure.frame->slots[0]; /* base_filename */
  frame->slots[1] = myself->closure.frame->slots[1]; /* so_version */
  frame->slots[2] = myself->closure.frame->slots[2]; /* lib_filename */
  frame->slots[3] /* out */ = create_future();
  frame->slots[4] /* err */ = create_future();
  frame->slots[5] /* success */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 897: "-Wl,-soname,libsim-@(base_filename)@(so_version).so.@(MAJOR)"
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__84_62;
  arguments->slots[1] = frame->slots[0] /* base_filename */;
  arguments->slots[2] = ((CELL *)frame->slots[1])->contents /* so_version */;
  arguments->slots[3] = string__77_27;
  arguments->slots[4] = var._MAJOR;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__84_63;
}
static void cont__84_63(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 898: library_paths_and_file_list()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = var._library_paths_and_file_list;
  func = myself->type;
  frame->cont = cont__84_64;
}
static void cont__84_64(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 895: CC $_out $err $success
  // 896:   "-shared"
  // 897:   "-Wl,-soname,libsim-@(base_filename)@(so_version).so.@(MAJOR)"
  // 898:   library_paths_and_file_list()*
  // 899:   "-o"
  // 900:   lib_filename
  argument_count = 0;
  arguments = node_p;
  arguments->slots[argument_count++] = string__84_65;
  arguments->slots[argument_count++] = frame->slots[6] /* temp__1 */;
  unfold(frame->slots[7] /* temp__2 */);
  arguments->slots[argument_count++] = string__70_6;
  arguments->slots[argument_count++] = frame->slots[2] /* lib_filename */;
  result_count = 3;
  myself = var._CC;
  func = myself->type;
  frame->cont = cont__84_66;
}
static void cont__84_66(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__3 */ = arguments->slots[0];
  frame->slots[9] /* temp__4 */ = arguments->slots[1];
  frame->slots[10] /* temp__5 */ = arguments->slots[2];
  // 895: ... _out
  initialize_future(frame->slots[3] /* out */, frame->slots[8] /* temp__3 */);
  // 895: ... err
  initialize_future(frame->slots[4] /* err */, frame->slots[9] /* temp__4 */);
  // 895: ... success
  initialize_future(frame->slots[5] /* success */, frame->slots[10] /* temp__5 */);
  // 901: ... : Error err.from_utf8
  frame->slots[6] /* temp__1 */ = create_closure(entry__84_67, 0);
  // 901: unless success: Error err.from_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* success */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__84_69(void) {
  allocate_initialized_frame_gc(1, 9);
  // slot allocations:
  // lib_filename: 0
  // out: 1
  // err: 2
  // success: 3
  frame->slots[0] = myself->closure.frame->slots[2]; /* lib_filename */
  frame->slots[1] /* out */ = create_future();
  frame->slots[2] /* err */ = create_future();
  frame->slots[3] /* success */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 905: library_paths_and_file_list()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = var._library_paths_and_file_list;
  func = myself->type;
  frame->cont = cont__84_70;
}
static void cont__84_70(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 906: "-lsim-@(MAJOR)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__84_71;
  arguments->slots[1] = var._MAJOR;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__84_72;
}
static void cont__84_72(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 903: CC $_out $err $success
  // 904:   "-shared"
  // 905:   library_paths_and_file_list()*
  // 906:   "-lsim-@(MAJOR)"
  // 907:   "-o"
  // 908:   lib_filename
  argument_count = 0;
  arguments = node_p;
  arguments->slots[argument_count++] = string__84_65;
  unfold(frame->slots[4] /* temp__1 */);
  arguments->slots[argument_count++] = frame->slots[5] /* temp__2 */;
  arguments->slots[argument_count++] = string__70_6;
  arguments->slots[argument_count++] = frame->slots[0] /* lib_filename */;
  result_count = 3;
  myself = var._CC;
  func = myself->type;
  frame->cont = cont__84_73;
}
static void cont__84_73(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  frame->slots[7] /* temp__4 */ = arguments->slots[1];
  frame->slots[8] /* temp__5 */ = arguments->slots[2];
  // 903: ... _out
  initialize_future(frame->slots[1] /* out */, frame->slots[6] /* temp__3 */);
  // 903: ... err
  initialize_future(frame->slots[2] /* err */, frame->slots[7] /* temp__4 */);
  // 903: ... success
  initialize_future(frame->slots[3] /* success */, frame->slots[8] /* temp__5 */);
  // 909: ... : Error err.from_utf8
  frame->slots[4] /* temp__1 */ = create_closure(entry__84_74, 0);
  // 909: unless success: Error err.from_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* success */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__84_76(void) {
  allocate_initialized_frame_gc(3, 12);
  // slot allocations:
  // base_filename: 0
  // so_version: 1
  // lib_filename: 2
  // out: 3
  // err: 4
  // success: 5
  frame->slots[0] = myself->closure.frame->slots[0]; /* base_filename */
  frame->slots[1] = myself->closure.frame->slots[1]; /* so_version */
  frame->slots[2] = myself->closure.frame->slots[2]; /* lib_filename */
  frame->slots[3] /* out */ = create_future();
  frame->slots[4] /* err */ = create_future();
  frame->slots[5] /* success */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 913: "
  // 914:   -Wl,-install_name,libsim-@(base_filename)@(so_version)-@(MAJOR)@
  // 915:   .dylib@
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = string__84_77;
  arguments->slots[1] = frame->slots[0] /* base_filename */;
  arguments->slots[2] = ((CELL *)frame->slots[1])->contents /* so_version */;
  arguments->slots[3] = string__67_46;
  arguments->slots[4] = var._MAJOR;
  arguments->slots[5] = string__84_30;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__84_78;
}
static void cont__84_78(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 916: library_paths_and_file_list()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = var._library_paths_and_file_list;
  func = myself->type;
  frame->cont = cont__84_79;
}
static void cont__84_79(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 917: "-lsim-@(MAJOR)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__84_71;
  arguments->slots[1] = var._MAJOR;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__84_80;
}
static void cont__84_80(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__3 */ = arguments->slots[0];
  // 911: CC $_out $err $success
  // 912:   "-dynamiclib"
  // 913:   "
  // 914:     -Wl,-install_name,libsim-@(base_filename)@(so_version)-@(MAJOR)@
  // 915:     .dylib@
  // 916:   library_paths_and_file_list()*
  // 917:   "-lsim-@(MAJOR)"
  // 918:   "-o"
  // 919:   lib_filename
  argument_count = 0;
  arguments = node_p;
  arguments->slots[argument_count++] = string__84_81;
  arguments->slots[argument_count++] = frame->slots[6] /* temp__1 */;
  unfold(frame->slots[7] /* temp__2 */);
  arguments->slots[argument_count++] = frame->slots[8] /* temp__3 */;
  arguments->slots[argument_count++] = string__70_6;
  arguments->slots[argument_count++] = frame->slots[2] /* lib_filename */;
  result_count = 3;
  myself = var._CC;
  func = myself->type;
  frame->cont = cont__84_82;
}
static void cont__84_82(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__4 */ = arguments->slots[0];
  frame->slots[10] /* temp__5 */ = arguments->slots[1];
  frame->slots[11] /* temp__6 */ = arguments->slots[2];
  // 911: ... _out
  initialize_future(frame->slots[3] /* out */, frame->slots[9] /* temp__4 */);
  // 911: ... err
  initialize_future(frame->slots[4] /* err */, frame->slots[10] /* temp__5 */);
  // 911: ... success
  initialize_future(frame->slots[5] /* success */, frame->slots[11] /* temp__6 */);
  // 920: ... : Error err.from_utf8
  frame->slots[6] /* temp__1 */ = create_closure(entry__84_83, 0);
  // 920: unless success: Error err.from_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* success */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__84_85(void) {
  allocate_initialized_frame_gc(1, 8);
  // slot allocations:
  // lib_filename: 0
  // out: 1
  // err: 2
  // success: 3
  frame->slots[0] = myself->closure.frame->slots[2]; /* lib_filename */
  frame->slots[1] /* out */ = create_future();
  frame->slots[2] /* err */ = create_future();
  frame->slots[3] /* success */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 924: library_paths_and_file_list()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = var._library_paths_and_file_list;
  func = myself->type;
  frame->cont = cont__84_86;
}
static void cont__84_86(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 922: CC $_out $err $success
  // 923:   "-shared"
  // 924:   library_paths_and_file_list()*
  // 925:   "-o"
  // 926:   lib_filename
  argument_count = 0;
  arguments = node_p;
  arguments->slots[argument_count++] = string__84_65;
  unfold(frame->slots[4] /* temp__1 */);
  arguments->slots[argument_count++] = string__70_6;
  arguments->slots[argument_count++] = frame->slots[0] /* lib_filename */;
  result_count = 3;
  myself = var._CC;
  func = myself->type;
  frame->cont = cont__84_87;
}
static void cont__84_87(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  frame->slots[6] /* temp__3 */ = arguments->slots[1];
  frame->slots[7] /* temp__4 */ = arguments->slots[2];
  // 922: ... _out
  initialize_future(frame->slots[1] /* out */, frame->slots[5] /* temp__2 */);
  // 922: ... err
  initialize_future(frame->slots[2] /* err */, frame->slots[6] /* temp__3 */);
  // 922: ... success
  initialize_future(frame->slots[3] /* success */, frame->slots[7] /* temp__4 */);
  // 927: ... : Error err.from_utf8
  frame->slots[4] /* temp__1 */ = create_closure(entry__84_88, 0);
  // 927: unless success: Error err.from_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* success */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__84_54(void) {
  allocate_initialized_frame_gc(3, 9);
  // slot allocations:
  // base_filename: 0
  // so_version: 1
  // lib_filename: 2
  frame->slots[0] = myself->closure.frame->slots[3]; /* base_filename */
  frame->slots[1] = myself->closure.frame->slots[1]; /* so_version */
  frame->slots[2] = myself->closure.frame->slots[4]; /* lib_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 891: if verbose: ewriteln "linking dynamic library"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = func__84_55;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__84_57;
}
static void entry__84_55(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 891: ... ewriteln "linking dynamic library"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__84_56;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__84_57(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 893: operating_system()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__operating_system();
  func = myself->type;
  frame->cont = cont__84_58;
}
static void cont__84_58(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 894: "linux", "bsd"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__77_23;
  arguments->slots[1] = string__84_59;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__84_60;
}
static void cont__84_60(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 894: ... :
  // 895:   CC $_out $err $success
  // 896:     "-shared"
  // 897:     "-Wl,-soname,libsim-@(base_filename)@(so_version).so.@(MAJOR)"
  // 898:     library_paths_and_file_list()*
  // 899:     "-o"
  // 900:     lib_filename
  // 901:   unless success: Error err.from_utf8
  frame->slots[5] /* temp__3 */ = create_closure(entry__84_61, 0);
  // 902: ... :
  // 903:   CC $_out $err $success
  // 904:     "-shared"
  // 905:     library_paths_and_file_list()*
  // 906:     "-lsim-@(MAJOR)"
  // 907:     "-o"
  // 908:     lib_filename
  // 909:   unless success: Error err.from_utf8
  frame->slots[6] /* temp__4 */ = create_closure(entry__84_69, 0);
  // 910: ... :
  // 911:   CC $_out $err $success
  // 912:     "-dynamiclib"
  // 913:     "
  // 914:       -Wl,-install_name,libsim-@(base_filename)@(so_version)-@(MAJOR)@
  // 915:       .dylib@
  // 916:     library_paths_and_file_list()*
  // 917:     "-lsim-@(MAJOR)"
  // 918:     "-o"
  // 919:     lib_filename
  // ...
  frame->slots[7] /* temp__5 */ = create_closure(entry__84_76, 0);
  // 921: :
  // 922:   CC $_out $err $success
  // 923:     "-shared"
  // 924:     library_paths_and_file_list()*
  // 925:     "-o"
  // 926:     lib_filename
  // 927:   unless success: Error err.from_utf8
  frame->slots[8] /* temp__6 */ = create_closure(entry__84_85, 0);
  // 892: case
  // 893:   operating_system()
  // 894:   "linux", "bsd":
  // 895:     CC $_out $err $success
  // 896:       "-shared"
  // 897:       "-Wl,-soname,libsim-@(base_filename)@(so_version).so.@(MAJOR)"
  // 898:       library_paths_and_file_list()*
  // 899:       "-o"
  // 900:       lib_filename
  // 901:     unless success: Error err.from_utf8
  // ...
  argument_count = 8;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = frame->slots[5] /* temp__3 */;
  arguments->slots[3] = string__84_36;
  arguments->slots[4] = frame->slots[6] /* temp__4 */;
  arguments->slots[5] = string__84_37;
  arguments->slots[6] = frame->slots[7] /* temp__5 */;
  arguments->slots[7] = frame->slots[8] /* temp__6 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__84_7(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 859: extract_documentation main_filename
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  result_count = frame->caller_result_count;
  myself = get__extract_documentation();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__84_8(void) {
  allocate_initialized_frame_gc(0, 10);
  // slot allocations:
  // version: 0
  // so_version: 1
  // version_filename: 2
  // base_filename: 3
  // lib_filename: 4
  frame->slots[0] /* version */ = create_cell();
  frame->slots[1] /* so_version */ = create_cell();
  frame->slots[2] /* version_filename */ = create_future();
  frame->slots[3] /* base_filename */ = create_future();
  frame->slots[4] /* lib_filename */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 861: $$version ""
  ((CELL *)frame->slots[0])->contents /* version */ = empty_string;
  // 862: $$so_version ""
  ((CELL *)frame->slots[1])->contents /* so_version */ = empty_string;
  // 863: $version_filename string(main_filename "/VERSION")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  arguments->slots[1] = string__84_9;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__84_10;
}
static void cont__84_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* version_filename */, arguments->slots[0]);
  // 864: ... file_exists(version_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* version_filename */;
  result_count = 1;
  myself = get__file_exists();
  func = myself->type;
  frame->cont = cont__84_11;
}
static void cont__84_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 864: ... :
  // 865:   !version string('-' load(version_filename).trim)
  // 866:   !so_version version .truncate_from. '.'
  frame->slots[6] /* temp__2 */ = create_closure(entry__84_12, 0);
  // 864: if file_exists(version_filename):
  // 865:   !version string('-' load(version_filename).trim)
  // 866:   !so_version version .truncate_from. '.'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__84_17;
}
static void entry__84_12(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // version: 0
  // version_filename: 1
  // so_version: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* version */
  frame->slots[1] = myself->closure.frame->slots[2]; /* version_filename */
  frame->slots[2] = myself->closure.frame->slots[1]; /* so_version */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 865: ... load(version_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* version_filename */;
  result_count = 1;
  myself = get__load();
  func = myself->type;
  frame->cont = cont__84_13;
}
static void cont__84_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 865: ... load(version_filename).trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__84_14;
}
static void cont__84_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 865: !version string('-' load(version_filename).trim)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__45;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__84_15;
}
static void cont__84_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* version */ = arguments->slots[0];
  // 866: !so_version version .truncate_from. '.'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* version */;
  arguments->slots[1] = character__46;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__84_16;
}
static void cont__84_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* so_version */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__84_17(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 867: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__84_18;
}
static void cont__84_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 867: $base_filename truncate_until(main_filename '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__84_19;
}
static void cont__84_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* base_filename */, arguments->slots[0]);
  // 871: operating_system()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__operating_system();
  func = myself->type;
  frame->cont = cont__84_20;
}
static void cont__84_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 873: -> string("libsim-" base_filename version ".so.@(MAJOR)")
  frame->slots[6] /* temp__2 */ = create_closure(entry__84_21, 0);
  // 875: -> string("libsim-" base_filename version "-@(MAJOR).dll")
  frame->slots[7] /* temp__3 */ = create_closure(entry__84_25, 0);
  // 877: -> string("libsim-" base_filename version "-@(MAJOR).dylib")
  frame->slots[8] /* temp__4 */ = create_closure(entry__84_29, 0);
  // 878: -> string("libsim-" base_filename ".so")
  frame->slots[9] /* temp__5 */ = create_closure(entry__84_33, 0);
  // 869: $lib_filename
  // 870:   case
  // 871:     operating_system()
  // 872:     "linux"
  // 873:     -> string("libsim-" base_filename version ".so.@(MAJOR)")
  // 874:     "cygwin"
  // 875:     -> string("libsim-" base_filename version "-@(MAJOR).dll")
  // 876:     "darwin"
  // 877:     -> string("libsim-" base_filename version "-@(MAJOR).dylib")
  // 878:     -> string("libsim-" base_filename ".so")
  argument_count = 8;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = string__77_23;
  arguments->slots[2] = frame->slots[6] /* temp__2 */;
  arguments->slots[3] = string__84_36;
  arguments->slots[4] = frame->slots[7] /* temp__3 */;
  arguments->slots[5] = string__84_37;
  arguments->slots[6] = frame->slots[8] /* temp__4 */;
  arguments->slots[7] = frame->slots[9] /* temp__5 */;
  result_count = 1;
  myself = get__case();
  func = myself->type;
  frame->cont = cont__84_38;
}
static void entry__84_21(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // base_filename: 0
  // version: 1
  frame->slots[0] = myself->closure.frame->slots[3]; /* base_filename */
  frame->slots[1] = myself->closure.frame->slots[0]; /* version */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 873: ... ".so.@(MAJOR)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__77_27;
  arguments->slots[1] = var._MAJOR;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__84_22;
}
static void cont__84_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 873: ... string("libsim-" base_filename version ".so.@(MAJOR)")
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__84_23;
  arguments->slots[1] = frame->slots[0] /* base_filename */;
  arguments->slots[2] = ((CELL *)frame->slots[1])->contents /* version */;
  arguments->slots[3] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__84_24;
}
static void cont__84_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 873: -> string("libsim-" base_filename version ".so.@(MAJOR)")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__84_25(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // base_filename: 0
  // version: 1
  frame->slots[0] = myself->closure.frame->slots[3]; /* base_filename */
  frame->slots[1] = myself->closure.frame->slots[0]; /* version */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 875: ... "-@(MAJOR).dll"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__67_46;
  arguments->slots[1] = var._MAJOR;
  arguments->slots[2] = string__84_26;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__84_27;
}
static void cont__84_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 875: ... string("libsim-" base_filename version "-@(MAJOR).dll")
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__84_23;
  arguments->slots[1] = frame->slots[0] /* base_filename */;
  arguments->slots[2] = ((CELL *)frame->slots[1])->contents /* version */;
  arguments->slots[3] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__84_28;
}
static void cont__84_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 875: -> string("libsim-" base_filename version "-@(MAJOR).dll")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__84_29(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // base_filename: 0
  // version: 1
  frame->slots[0] = myself->closure.frame->slots[3]; /* base_filename */
  frame->slots[1] = myself->closure.frame->slots[0]; /* version */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 877: ... "-@(MAJOR).dylib"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__67_46;
  arguments->slots[1] = var._MAJOR;
  arguments->slots[2] = string__84_30;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__84_31;
}
static void cont__84_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 877: ... string("libsim-" base_filename version "-@(MAJOR).dylib")
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__84_23;
  arguments->slots[1] = frame->slots[0] /* base_filename */;
  arguments->slots[2] = ((CELL *)frame->slots[1])->contents /* version */;
  arguments->slots[3] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__84_32;
}
static void cont__84_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 877: -> string("libsim-" base_filename version "-@(MAJOR).dylib")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__84_33(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // base_filename: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* base_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 878: ... string("libsim-" base_filename ".so")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__84_23;
  arguments->slots[1] = frame->slots[0] /* base_filename */;
  arguments->slots[2] = string__84_34;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__84_35;
}
static void cont__84_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 878: -> string("libsim-" base_filename ".so")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__84_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* lib_filename */, arguments->slots[0]);
  // 880: ... : ewriteln "build library " lib_filename
  frame->slots[5] /* temp__1 */ = create_closure(entry__84_39, 0);
  // 880: if verbose: ewriteln "build library " lib_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__84_41;
}
static void entry__84_39(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // lib_filename: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* lib_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 880: ... ewriteln "build library " lib_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__84_40;
  arguments->slots[1] = frame->slots[0] /* lib_filename */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__84_41(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 881: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__84_42;
}
static void cont__84_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 881: ... behind(main_filename '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__84_43;
}
static void cont__84_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 881: compile_modules main_filename behind(main_filename '/' -1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = var._compile_modules;
  func = myself->type;
  frame->cont = cont__84_44;
}
static void cont__84_44(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 882: ... :
  // 883:   $info stat(lib_filename)
  // 884:   if
  // 885:     ||
  // 886:       info.is_undefined
  // 887:       last_modification_time > modification_time_of(info)
  // 888:     :
  // 889:       !do_link true
  frame->slots[5] /* temp__1 */ = create_closure(entry__84_45, 0);
  // 882: unless do_link:
  // 883:   $info stat(lib_filename)
  // 884:   if
  // 885:     ||
  // 886:       info.is_undefined
  // 887:       last_modification_time > modification_time_of(info)
  // 888:     :
  // 889:       !do_link true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_link();
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__84_53;
}
static void entry__84_52(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 889: !do_link true
  set__do_link(get__true());
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__84_45(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // lib_filename: 0
  // info: 1
  frame->slots[0] = myself->closure.frame->slots[4]; /* lib_filename */
  frame->slots[1] /* info */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 883: $info stat(lib_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* lib_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__84_46;
}
static void cont__84_46(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* info */, arguments->slots[0]);
  // 886: info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__84_47;
}
static void cont__84_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 887: last_modification_time > modification_time_of(info)
  frame->slots[4] /* temp__3 */ = create_closure(entry__84_48, 0);
  // 885: ||
  // 886:   info.is_undefined
  // 887:   last_modification_time > modification_time_of(info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__84_51;
}
static void entry__84_48(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // info: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 887: ... modification_time_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__84_49;
}
static void cont__84_49(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 887: last_modification_time > modification_time_of(info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = get__last_modification_time();
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__84_50;
}
static void cont__84_50(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 887: last_modification_time > modification_time_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__84_51(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 884: if
  // 885:   ||
  // 886:     info.is_undefined
  // 887:     last_modification_time > modification_time_of(info)
  // 888:   :
  // 889:     !do_link true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = func__84_52;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__84_53(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 890: ... :
  // 891:   if verbose: ewriteln "linking dynamic library"
  // 892:   case
  // 893:     operating_system()
  // 894:     "linux", "bsd":
  // 895:       CC $_out $err $success
  // 896:         "-shared"
  // 897:         "-Wl,-soname,libsim-@(base_filename)@(so_version).so.@(MAJOR)"
  // 898:         library_paths_and_file_list()*
  // 899:         "-o"
  // ...
  frame->slots[5] /* temp__1 */ = create_closure(entry__84_54, 0);
  // 890: if do_link:
  // 891:   if verbose: ewriteln "linking dynamic library"
  // 892:   case
  // 893:     operating_system()
  // 894:     "linux", "bsd":
  // 895:       CC $_out $err $success
  // 896:         "-shared"
  // 897:         "-Wl,-soname,libsim-@(base_filename)@(so_version).so.@(MAJOR)"
  // 898:         library_paths_and_file_list()*
  // 899:         "-o"
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_link();
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__84_90(void) {
  myself = frame->slots[0] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__85_18(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // filename: 0
  // c_filename: 1
  // o_filename: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* filename */
  frame->slots[1] = myself->closure.frame->slots[1]; /* c_filename */
  frame->slots[2] = myself->closure.frame->slots[2]; /* o_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 942: ... : ewriteln "compiling runtime module @(filename)"
  frame->slots[3] /* temp__1 */ = create_closure(entry__85_19, 0);
  // 942: if verbose: ewriteln "compiling runtime module @(filename)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__85_22;
}
static void entry__85_19(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // filename: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 942: ... "compiling runtime module @(filename)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__85_20;
  arguments->slots[1] = frame->slots[0] /* filename */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__85_21;
}
static void cont__85_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 942: ... ewriteln "compiling runtime module @(filename)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__85_22(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 943: compile_c c_filename o_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* c_filename */;
  arguments->slots[1] = frame->slots[2] /* o_filename */;
  result_count = frame->caller_result_count;
  myself = var._compile_c;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__85_1_maybe_compile_c_file(void) {
  allocate_initialized_frame_gc(1, 9);
  // slot allocations:
  // filename: 0
  // c_filename: 1
  // o_filename: 2
  // c_info: 3
  // o_info: 4
  frame->slots[1] /* c_filename */ = create_future();
  frame->slots[2] /* o_filename */ = create_future();
  frame->slots[3] /* c_info */ = create_future();
  frame->slots[4] /* o_info */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 930: $c_filename string(filename ".c")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  arguments->slots[1] = string__71_9;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__85_2;
}
static void cont__85_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* c_filename */, arguments->slots[0]);
  // 931: $o_filename string(filename ".o")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  arguments->slots[1] = string__73_80;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__85_3;
}
static void cont__85_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* o_filename */, arguments->slots[0]);
  // 932: $c_info stat(c_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* c_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__85_4;
}
static void cont__85_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* c_info */, arguments->slots[0]);
  // 933: ... c_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* c_info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__85_5;
}
static void cont__85_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 933: ... :
  // 934:   Error "
  // 935:     @quot;@(c_filename)" does not exist!
  frame->slots[6] /* temp__2 */ = create_closure(entry__85_6, 0);
  // 933: if c_info.is_undefined:
  // 934:   Error "
  // 935:     @quot;@(c_filename)" does not exist!
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__85_10;
}
static void entry__85_6(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // c_filename: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* c_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 934: ... "
  // 935:   @quot;@(c_filename)" does not exist!
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__85_7;
  arguments->slots[1] = frame->slots[0] /* c_filename */;
  arguments->slots[2] = string__85_8;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__85_9;
}
static void cont__85_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 934: Error "
  // 935:   @quot;@(c_filename)" does not exist!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__85_10(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 936: $o_info stat(o_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* o_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__85_11;
}
static void cont__85_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* o_info */, arguments->slots[0]);
  // 939: o_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* o_info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__85_12;
}
static void cont__85_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 940: modification_time_of(c_info) > modification_time_of(o_info)
  frame->slots[7] /* temp__3 */ = create_closure(entry__85_13, 0);
  // 938: ||
  // 939:   o_info.is_undefined
  // 940:   modification_time_of(c_info) > modification_time_of(o_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__85_17;
}
static void entry__85_13(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // o_info: 0
  // c_info: 1
  frame->slots[0] = myself->closure.frame->slots[4]; /* o_info */
  frame->slots[1] = myself->closure.frame->slots[3]; /* c_info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 940: ... modification_time_of(o_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* o_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__85_14;
}
static void cont__85_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 940: modification_time_of(c_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* c_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__85_15;
}
static void cont__85_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 940: modification_time_of(c_info) > modification_time_of(o_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__85_16;
}
static void cont__85_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 940: modification_time_of(c_info) > modification_time_of(o_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__85_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 941: :
  // 942:   if verbose: ewriteln "compiling runtime module @(filename)"
  // 943:   compile_c c_filename o_filename
  frame->slots[8] /* temp__4 */ = create_closure(entry__85_18, 0);
  // 937: if
  // 938:   ||
  // 939:     o_info.is_undefined
  // 940:     modification_time_of(c_info) > modification_time_of(o_info)
  // 941:   :
  // 942:     if verbose: ewriteln "compiling runtime module @(filename)"
  // 943:     compile_c c_filename o_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__87_1_format_number(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // val: 0
  // n: 1
  // m: 2
  // ac: 3
  frame->slots[3] /* ac */ = create_cell();
  if (argument_count < 2) {
    too_few_arguments_error();
    return;
  }
  if (argument_count > 3) {
    too_many_arguments_error();
    return;
  }
  frame->slots[0] /* val */ = create_cell_with_contents(arguments->slots[0]);
  switch(argument_count) {
    default: frame->slots[2] /* m */ = arguments->slots[2];
    case 2:;
  }
  switch(argument_count) {
    case 2: frame->slots[2] /* m */ = number__0;
  }
  // 953: to_string &val
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* val */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__87_2;
}
static void cont__87_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* val */ = arguments->slots[0];
  // 954: $$ac 0
  ((CELL *)frame->slots[3])->contents /* ac */ = number__0;
  // 955: ... : (-> break)
  // 956:   for_each val: (i chr)
  // 957:     if chr == '.':
  // 958:       !ac length_of(val)-i
  // 959:       if n > i-1: append dup(" " n-(i-1)) &val
  // 960:       break
  frame->slots[4] /* temp__1 */ = create_closure(entry__87_3, 0);
  // 955: do: (-> break)
  // 956:   for_each val: (i chr)
  // 957:     if chr == '.':
  // 958:       !ac length_of(val)-i
  // 959:       if n > i-1: append dup(" " n-(i-1)) &val
  // 960:       break
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__87_19;
}
static void entry__87_3(void) {
  allocate_initialized_frame_gc(4, 5);
  // slot allocations:
  // break: 0
  // val: 1
  // ac: 2
  // n: 3
  frame->slots[0] /* break */ = create_continuation();
  frame->slots[1] = myself->closure.frame->slots[0]; /* val */
  frame->slots[2] = myself->closure.frame->slots[3]; /* ac */
  frame->slots[3] = myself->closure.frame->slots[1]; /* n */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 956: ... : (i chr)
  // 957:   if chr == '.':
  // 958:     !ac length_of(val)-i
  // 959:     if n > i-1: append dup(" " n-(i-1)) &val
  // 960:     break
  frame->slots[4] /* temp__1 */ = create_closure(entry__87_4, 2);
  // 956: for_each val: (i chr)
  // 957:   if chr == '.':
  // 958:     !ac length_of(val)-i
  // 959:     if n > i-1: append dup(" " n-(i-1)) &val
  // 960:     break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* val */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__87_18;
}
static void entry__87_6(void) {
  allocate_initialized_frame_gc(5, 8);
  // slot allocations:
  // ac: 0
  // val: 1
  // i: 2
  // n: 3
  // break: 4
  frame->slots[0] = myself->closure.frame->slots[2]; /* ac */
  frame->slots[1] = myself->closure.frame->slots[3]; /* val */
  frame->slots[2] = myself->closure.frame->slots[0]; /* i */
  frame->slots[3] = myself->closure.frame->slots[4]; /* n */
  frame->slots[4] = myself->closure.frame->slots[5]; /* break */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 958: ... length_of(val)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* val */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__87_7;
}
static void cont__87_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 958: !ac length_of(val)-i
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* i */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__87_8;
}
static void cont__87_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* ac */ = arguments->slots[0];
  // 959: ... i-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* i */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__87_9;
}
static void cont__87_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 959: ... n > i-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* n */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__87_10;
}
static void cont__87_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 959: ... : append dup(" " n-(i-1)) &val
  frame->slots[7] /* temp__3 */ = create_closure(entry__87_11, 0);
  // 959: if n > i-1: append dup(" " n-(i-1)) &val
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__87_17;
}
static void entry__87_11(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // val: 0
  // n: 1
  // i: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* val */
  frame->slots[1] = myself->closure.frame->slots[3]; /* n */
  frame->slots[2] = myself->closure.frame->slots[2]; /* i */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 959: ... i-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* i */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__87_12;
}
static void cont__87_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 959: ... n-(i-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* n */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__87_13;
}
static void cont__87_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 959: ... dup(" " n-(i-1))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__87_14;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__87_15;
}
static void cont__87_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 959: ... append dup(" " n-(i-1)) &val
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* val */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__87_16;
}
static void cont__87_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* val */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__87_17(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 960: break
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[4] /* break */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__87_4(void) {
  allocate_initialized_frame_gc(6, 8);
  // slot allocations:
  // i: 0
  // chr: 1
  // ac: 2
  // val: 3
  // n: 4
  // break: 5
  frame->slots[2] = myself->closure.frame->slots[2]; /* ac */
  frame->slots[3] = myself->closure.frame->slots[1]; /* val */
  frame->slots[4] = myself->closure.frame->slots[3]; /* n */
  frame->slots[5] = myself->closure.frame->slots[0]; /* break */
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 957: ... chr == '.'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* chr */;
  arguments->slots[1] = character__46;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__87_5;
}
static void cont__87_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 957: ... :
  // 958:   !ac length_of(val)-i
  // 959:   if n > i-1: append dup(" " n-(i-1)) &val
  // 960:   break
  frame->slots[7] /* temp__2 */ = create_closure(entry__87_6, 0);
  // 957: if chr == '.':
  // 958:   !ac length_of(val)-i
  // 959:   if n > i-1: append dup(" " n-(i-1)) &val
  // 960:   break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__87_18(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__87_19(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 962: m > ac
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* ac */;
  arguments->slots[1] = frame->slots[2] /* m */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__87_20;
}
static void cont__87_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 962: ... :
  // 963:   append &val dup("0" m-ac)
  frame->slots[5] /* temp__2 */ = create_closure(entry__87_21, 0);
  // 964: :
  // 965:   if ac > m: range &val 1 -(ac-m+1)
  frame->slots[6] /* temp__3 */ = create_closure(entry__87_26, 0);
  // 961: if
  // 962:   m > ac:
  // 963:     append &val dup("0" m-ac)
  // 964:   :
  // 965:     if ac > m: range &val 1 -(ac-m+1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__87_33;
}
static void entry__87_28(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // val: 0
  // ac: 1
  // m: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* val */
  frame->slots[1] = myself->closure.frame->slots[1]; /* ac */
  frame->slots[2] = myself->closure.frame->slots[0]; /* m */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 965: ... ac-m
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* ac */;
  arguments->slots[1] = frame->slots[2] /* m */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__87_29;
}
static void cont__87_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 965: ... ac-m+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__87_30;
}
static void cont__87_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 965: ... ac-m+1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__87_31;
}
static void cont__87_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 965: ... range &val 1 -(ac-m+1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* val */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__87_32;
}
static void cont__87_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* val */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__87_21(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // val: 0
  // m: 1
  // ac: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* val */
  frame->slots[1] = myself->closure.frame->slots[2]; /* m */
  frame->slots[2] = myself->closure.frame->slots[3]; /* ac */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 963: ... m-ac
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* m */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* ac */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__87_22;
}
static void cont__87_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 963: ... dup("0" m-ac)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__87_23;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__87_24;
}
static void cont__87_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 963: append &val dup("0" m-ac)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* val */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__87_25;
}
static void cont__87_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* val */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__87_26(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // m: 0
  // ac: 1
  // val: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* m */
  frame->slots[1] = myself->closure.frame->slots[3]; /* ac */
  frame->slots[2] = myself->closure.frame->slots[0]; /* val */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 965: ... ac > m
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* m */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* ac */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__87_27;
}
static void cont__87_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 965: ... : range &val 1 -(ac-m+1)
  frame->slots[4] /* temp__2 */ = create_closure(entry__87_28, 0);
  // 965: if ac > m: range &val 1 -(ac-m+1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__87_33(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 966: -> val
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* val */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__88_1_sim2c__write_timing_info(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // description: 0
  // filename: 1
  // new_t: 2
  frame->slots[2] /* new_t */ = create_future();
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  if (argument_count > 2) {
    too_many_arguments_error();
    return;
  }
  switch(argument_count) {
    default: frame->slots[1] /* filename */ = create_cell_with_contents(arguments->slots[1]);
    case 1:;
  }
  switch(argument_count) {
    case 1: frame->slots[1] /* filename */ = create_cell_with_contents(undefined);
  }
  // 969: $new_t current_time()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__current_time();
  func = myself->type;
  frame->cont = cont__88_2;
}
static void cont__88_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* new_t */, arguments->slots[0]);
  // 971: filename.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* filename */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__88_3;
}
static void cont__88_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 971: ... :
  // 972:   truncate_until &filename '/' -1
  // 973:   ewriteln
  // 974:     description
  // 975:     ' '
  // 976:     filename
  // 977:     ':'
  // 978:     dup(" " 12-length_of(description))
  // 979:     format_number(new_t-t 2 3)
  // 980:     " s"
  frame->slots[4] /* temp__2 */ = create_closure(entry__88_4, 0);
  // 981: :
  // 982:   ewriteln description ": " format_number(new_t-t 0 3) " s"
  frame->slots[5] /* temp__3 */ = create_closure(entry__88_13, 0);
  // 970: if
  // 971:   filename.is_defined:
  // 972:     truncate_until &filename '/' -1
  // 973:     ewriteln
  // 974:       description
  // 975:       ' '
  // 976:       filename
  // 977:       ':'
  // 978:       dup(" " 12-length_of(description))
  // 979:       format_number(new_t-t 2 3)
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = frame->slots[5] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__88_17;
}
static void entry__88_4(void) {
  allocate_initialized_frame_gc(3, 8);
  // slot allocations:
  // filename: 0
  // description: 1
  // new_t: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* filename */
  frame->slots[1] = myself->closure.frame->slots[0]; /* description */
  frame->slots[2] = myself->closure.frame->slots[2]; /* new_t */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 972: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__88_5;
}
static void cont__88_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 972: truncate_until &filename '/' -1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* filename */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__88_6;
}
static void cont__88_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* filename */ = arguments->slots[0];
  // 978: ... length_of(description)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* description */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__88_7;
}
static void cont__88_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 978: ... 12-length_of(description)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__12;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__88_8;
}
static void cont__88_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 978: dup(" " 12-length_of(description))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__87_14;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__88_9;
}
static void cont__88_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 979: ... new_t-t
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* new_t */;
  arguments->slots[1] = var._t;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__88_10;
}
static void cont__88_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__5 */ = arguments->slots[0];
  // 979: format_number(new_t-t 2 3)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__5 */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = number__3;
  result_count = 1;
  myself = var._format_number;
  func = myself->type;
  frame->cont = cont__88_11;
}
static void cont__88_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__4 */ = arguments->slots[0];
  // 973: ewriteln
  // 974:   description
  // 975:   ' '
  // 976:   filename
  // 977:   ':'
  // 978:   dup(" " 12-length_of(description))
  // 979:   format_number(new_t-t 2 3)
  // 980:   " s"
  argument_count = 7;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* description */;
  arguments->slots[1] = character__32;
  arguments->slots[2] = ((CELL *)frame->slots[0])->contents /* filename */;
  arguments->slots[3] = character__58;
  arguments->slots[4] = frame->slots[3] /* temp__1 */;
  arguments->slots[5] = frame->slots[6] /* temp__4 */;
  arguments->slots[6] = string__88_12;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__88_13(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // description: 0
  // new_t: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* description */
  frame->slots[1] = myself->closure.frame->slots[2]; /* new_t */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 982: ... new_t-t
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* new_t */;
  arguments->slots[1] = var._t;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__88_14;
}
static void cont__88_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 982: ... format_number(new_t-t 0 3)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = number__0;
  arguments->slots[2] = number__3;
  result_count = 1;
  myself = var._format_number;
  func = myself->type;
  frame->cont = cont__88_15;
}
static void cont__88_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 982: ewriteln description ": " format_number(new_t-t 0 3) " s"
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* description */;
  arguments->slots[1] = string__88_16;
  arguments->slots[2] = frame->slots[2] /* temp__1 */;
  arguments->slots[3] = string__88_12;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__88_17(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 983: !t current_time()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__current_time();
  func = myself->type;
  frame->cont = cont__88_18;
}
static void cont__88_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._t = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__89_116(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // exe_filename: 0
  // zz: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* exe_filename */
  frame->slots[1] = myself->closure.frame->slots[8]; /* zz */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1078: exe_filename .has_prefix. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* exe_filename */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__89_117;
}
static void cont__89_117(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 1079: -> exe_filename
  frame->slots[4] /* temp__3 */ = create_closure(entry__89_118, 0);
  // 1080: -> string("./" exe_filename)
  frame->slots[5] /* temp__4 */ = create_closure(entry__89_119, 0);
  // 1077: if
  // 1078:   exe_filename .has_prefix. '/'
  // 1079:   -> exe_filename
  // 1080:   -> string("./" exe_filename)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  arguments->slots[2] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__89_121;
}
static void entry__89_118(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // exe_filename: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* exe_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1079: -> exe_filename
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* exe_filename */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__89_119(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // exe_filename: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* exe_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1080: ... string("./" exe_filename)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__71_56;
  arguments->slots[1] = frame->slots[0] /* exe_filename */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__89_120;
}
static void cont__89_120(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1080: -> string("./" exe_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__89_121(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1076: exec
  // 1077:   if
  // 1078:     exe_filename .has_prefix. '/'
  // 1079:     -> exe_filename
  // 1080:     -> string("./" exe_filename)
  // 1081:   zz*
  // 1082:   
  // 1083:   #range(command_line_arguments 2 -1)*
  argument_count = 0;
  arguments = node_p;
  arguments->slots[argument_count++] = frame->slots[2] /* temp__1 */;
  unfold(frame->slots[1] /* zz */);
  result_count = frame->caller_result_count;
  myself = get__exec();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__89_2(void) {
  allocate_initialized_frame_gc(2, 13);
  // slot allocations:
  // mod_filename: 0
  // mod_name: 1
  // exe_filename: 2
  // c_filename: 3
  // o_filename: 4
  // sim_info: 5
  // c_info: 6
  // c_buf: 7
  // zz: 8
  frame->slots[2] /* exe_filename */ = create_future();
  frame->slots[3] /* c_filename */ = create_future();
  frame->slots[4] /* o_filename */ = create_future();
  frame->slots[5] /* sim_info */ = create_future();
  frame->slots[6] /* c_info */ = create_future();
  frame->slots[7] /* c_buf */ = create_cell();
  frame->slots[8] /* zz */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 998: operating_system()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__operating_system();
  func = myself->type;
  frame->cont = cont__89_3;
}
static void cont__89_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__2 */ = arguments->slots[0];
  // 998: operating_system() == "cygwin"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__2 */;
  arguments->slots[1] = string__84_36;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__89_4;
}
static void cont__89_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 999: -> string(mod_filename ".exe")
  frame->slots[11] /* temp__3 */ = create_closure(entry__89_5, 0);
  // 1000: -> mod_filename
  frame->slots[12] /* temp__4 */ = create_closure(entry__89_8, 0);
  //  996: $exe_filename
  //  997:   if
  //  998:     operating_system() == "cygwin"
  //  999:     -> string(mod_filename ".exe")
  // 1000:     -> mod_filename
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = frame->slots[11] /* temp__3 */;
  arguments->slots[2] = frame->slots[12] /* temp__4 */;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__89_9;
}
static void entry__89_5(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // mod_filename: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* mod_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 999: ... string(mod_filename ".exe")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = string__89_6;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__89_7;
}
static void cont__89_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 999: -> string(mod_filename ".exe")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__89_8(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // mod_filename: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* mod_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1000: -> mod_filename
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__89_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* exe_filename */, arguments->slots[0]);
  // 1002: ... : ewriteln "build executable " exe_filename
  frame->slots[9] /* temp__1 */ = create_closure(entry__89_10, 0);
  // 1002: if verbose: ewriteln "build executable " exe_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__89_12;
}
static void entry__89_10(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // exe_filename: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* exe_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1002: ... ewriteln "build executable " exe_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__89_11;
  arguments->slots[1] = frame->slots[0] /* exe_filename */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__89_12(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1003: $c_filename string(mod_filename ".c")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = string__71_9;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__89_13;
}
static void cont__89_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* c_filename */, arguments->slots[0]);
  // 1004: $o_filename string(mod_filename ".o")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = string__73_80;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__89_14;
}
static void cont__89_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* o_filename */, arguments->slots[0]);
  // 1005: $sim_info stat(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__89_15;
}
static void cont__89_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* sim_info */, arguments->slots[0]);
  // 1006: $c_info stat(c_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* c_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__89_16;
}
static void cont__89_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* c_info */, arguments->slots[0]);
  // 1007: $$c_buf undefined
  ((CELL *)frame->slots[7])->contents /* c_buf */ = get__undefined();
  // 1008: !objects(o_filename) true
  frame->slots[9] /* temp__1 */ = get__true();
  // 1008: !objects(o_filename)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* o_filename */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = get__objects();
  func = myself->type;
  frame->cont = cont__89_17;
}
static void cont__89_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__objects(arguments->slots[0]);
  frame->slots[10] /* temp__2 */ = create_closure(entry__89_18, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_rebuild;
  arguments->slots[1] = frame->slots[10] /* temp__2 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__89_25;
}
static void entry__89_18(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // c_info: 0
  // sim_info: 1
  frame->slots[0] = myself->closure.frame->slots[6]; /* c_info */
  frame->slots[1] = myself->closure.frame->slots[5]; /* sim_info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1012: c_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__89_19;
}
static void cont__89_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 1013: modification_time_of(sim_info) > modification_time_of(c_info)
  frame->slots[4] /* temp__3 */ = create_closure(entry__89_20, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__89_24;
}
static void entry__89_20(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // c_info: 0
  // sim_info: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* c_info */
  frame->slots[1] = myself->closure.frame->slots[1]; /* sim_info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1013: ... modification_time_of(c_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__89_21;
}
static void cont__89_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 1013: modification_time_of(sim_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* sim_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__89_22;
}
static void cont__89_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 1013: modification_time_of(sim_info) > modification_time_of(c_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__89_23;
}
static void cont__89_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1013: modification_time_of(sim_info) > modification_time_of(c_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__89_24(void) {
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
static void cont__89_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 1014: :
  // 1015:   %sim2c::module_name mod_name .without_suffix. some(".meta")
  // 1016:   if verbose: ewriteln "build main module " module_name
  // 1017:   collect_output $c_source: sim2c list(main_filename) true
  // 1018:   collect_output !c_buf: create_imports c_source
  // 1019:   save c_filename c_buf.to_utf8
  // 1020:   if do_time_passes: write_timing_info "saving" c_filename
  // 1021:   compile_c c_filename o_filename
  // 1022:   if do_time_passes: write_timing_info "compiling" c_filename
  frame->slots[11] /* temp__3 */ = create_closure(entry__89_26, 0);
  // 1023: :
  // 1024:   load !c_buf c_filename
  // 1025:   $o_info stat(o_filename)
  // 1026:   if
  // 1027:     ||
  // 1028:       o_info.is_undefined
  // 1029:       modification_time_of(c_info) > modification_time_of(o_info)
  // 1030:     :
  // 1031:       compile_c c_filename o_filename
  // 1032:     :
  // ...
  frame->slots[12] /* temp__4 */ = create_closure(entry__89_46, 0);
  // 1009: if
  // 1010:   ||
  // 1011:     do_rebuild
  // 1012:     c_info.is_undefined
  // 1013:     modification_time_of(sim_info) > modification_time_of(c_info)
  // 1014:   :
  // 1015:     %sim2c::module_name mod_name .without_suffix. some(".meta")
  // 1016:     if verbose: ewriteln "build main module " module_name
  // 1017:     collect_output $c_source: sim2c list(main_filename) true
  // 1018:     collect_output !c_buf: create_imports c_source
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = frame->slots[11] /* temp__3 */;
  arguments->slots[2] = frame->slots[12] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__89_58;
}
static void entry__89_55(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // c_filename: 0
  // o_filename: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* c_filename */
  frame->slots[1] = myself->closure.frame->slots[2]; /* o_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1031: compile_c c_filename o_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_filename */;
  arguments->slots[1] = frame->slots[1] /* o_filename */;
  result_count = frame->caller_result_count;
  myself = var._compile_c;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__89_56(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // o_info: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* o_info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1033: !last_modification_time modification_time_of(o_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* o_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__89_57;
}
static void cont__89_57(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__last_modification_time(arguments->slots[0]);
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__89_26(void) {
  allocate_initialized_frame_gc(5, 7);
  // slot allocations:
  // return__1: 0
  // mod_name: 1
  // c_buf: 2
  // c_filename: 3
  // o_filename: 4
  // c_source: 5
  frame->slots[0] /* return__1 */ = create_continuation();
  frame->slots[1] = myself->closure.frame->slots[1]; /* mod_name */
  frame->slots[2] = myself->closure.frame->slots[7]; /* c_buf */
  frame->slots[3] = myself->closure.frame->slots[3]; /* c_filename */
  frame->slots[4] = myself->closure.frame->slots[4]; /* o_filename */
  define__sim2c__module_name(create_future());
  frame->slots[5] /* c_source */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1015: ... some(".meta")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__67_16;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__89_27;
}
static void cont__89_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 1015: %sim2c::module_name mod_name .without_suffix. some(".meta")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* mod_name */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = get__without_suffix();
  func = myself->type;
  frame->cont = cont__89_28;
}
static void cont__89_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(get__sim2c__module_name(), arguments->slots[0]);
  // 1016: if verbose: ewriteln "build main module " module_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = func__89_29;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__89_31;
}
static void entry__89_29(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1016: ... ewriteln "build main module " module_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__89_30;
  arguments->slots[1] = get__module_name();
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__89_31(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1017: collect_output $c_source: sim2c list(main_filename) true
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__89_32;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__89_34;
}
static void entry__89_32(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1017: ... list(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__89_33;
}
static void cont__89_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1017: ... sim2c list(main_filename) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = get__true();
  result_count = frame->caller_result_count;
  myself = get__sim2c();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__89_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* c_source */, arguments->slots[0]);
  // 1018: ... : create_imports c_source
  frame->slots[6] /* temp__1 */ = create_closure(entry__89_35, 0);
  // 1018: collect_output !c_buf: create_imports c_source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__89_36;
}
static void entry__89_35(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // c_source: 0
  frame->slots[0] = myself->closure.frame->slots[5]; /* c_source */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1018: ... create_imports c_source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_source */;
  result_count = frame->caller_result_count;
  myself = var._create_imports;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__89_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* c_buf */ = arguments->slots[0];
  // 1019: ... c_buf.to_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* c_buf */;
  result_count = 1;
  myself = get__to_utf8();
  func = myself->type;
  frame->cont = cont__89_37;
}
static void cont__89_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 1019: save c_filename c_buf.to_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* c_filename */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 0;
  myself = get__save();
  func = myself->type;
  frame->cont = cont__89_38;
}
static void cont__89_38(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1020: ... : write_timing_info "saving" c_filename
  frame->slots[6] /* temp__1 */ = create_closure(entry__89_39, 0);
  // 1020: if do_time_passes: write_timing_info "saving" c_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__89_41;
}
static void entry__89_39(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // c_filename: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* c_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1020: ... write_timing_info "saving" c_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__89_40;
  arguments->slots[1] = frame->slots[0] /* c_filename */;
  result_count = frame->caller_result_count;
  myself = get__write_timing_info();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__89_41(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1021: compile_c c_filename o_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* c_filename */;
  arguments->slots[1] = frame->slots[4] /* o_filename */;
  result_count = 0;
  myself = var._compile_c;
  func = myself->type;
  frame->cont = cont__89_42;
}
static void cont__89_42(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1022: ... : write_timing_info "compiling" c_filename
  frame->slots[6] /* temp__1 */ = create_closure(entry__89_43, 0);
  // 1022: if do_time_passes: write_timing_info "compiling" c_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__89_45;
}
static void entry__89_43(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // c_filename: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* c_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1022: ... write_timing_info "compiling" c_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__89_44;
  arguments->slots[1] = frame->slots[0] /* c_filename */;
  result_count = frame->caller_result_count;
  myself = get__write_timing_info();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__89_45(void) {
  myself = frame->slots[0] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__89_46(void) {
  allocate_initialized_frame_gc(4, 10);
  // slot allocations:
  // c_buf: 0
  // c_filename: 1
  // o_filename: 2
  // c_info: 3
  // o_info: 4
  frame->slots[0] = myself->closure.frame->slots[7]; /* c_buf */
  frame->slots[1] = myself->closure.frame->slots[3]; /* c_filename */
  frame->slots[2] = myself->closure.frame->slots[4]; /* o_filename */
  frame->slots[3] = myself->closure.frame->slots[6]; /* c_info */
  frame->slots[4] /* o_info */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1024: load !c_buf c_filename
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* c_filename */;
  result_count = 1;
  myself = get__load();
  func = myself->type;
  frame->cont = cont__89_47;
}
static void cont__89_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* c_buf */ = arguments->slots[0];
  // 1025: $o_info stat(o_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* o_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__89_48;
}
static void cont__89_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* o_info */, arguments->slots[0]);
  // 1028: o_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* o_info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__89_49;
}
static void cont__89_49(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 1029: modification_time_of(c_info) > modification_time_of(o_info)
  frame->slots[7] /* temp__3 */ = create_closure(entry__89_50, 0);
  // 1027: ||
  // 1028:   o_info.is_undefined
  // 1029:   modification_time_of(c_info) > modification_time_of(o_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__89_54;
}
static void entry__89_50(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // o_info: 0
  // c_info: 1
  frame->slots[0] = myself->closure.frame->slots[4]; /* o_info */
  frame->slots[1] = myself->closure.frame->slots[3]; /* c_info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1029: ... modification_time_of(o_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* o_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__89_51;
}
static void cont__89_51(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 1029: modification_time_of(c_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* c_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__89_52;
}
static void cont__89_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 1029: modification_time_of(c_info) > modification_time_of(o_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__89_53;
}
static void cont__89_53(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1029: modification_time_of(c_info) > modification_time_of(o_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__89_54(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 1030: :
  // 1031:   compile_c c_filename o_filename
  frame->slots[8] /* temp__4 */ = create_closure(entry__89_55, 0);
  // 1032: :
  // 1033:   !last_modification_time modification_time_of(o_info)
  frame->slots[9] /* temp__5 */ = create_closure(entry__89_56, 0);
  // 1026: if
  // 1027:   ||
  // 1028:     o_info.is_undefined
  // 1029:     modification_time_of(c_info) > modification_time_of(o_info)
  // 1030:   :
  // 1031:     compile_c c_filename o_filename
  // 1032:   :
  // 1033:     !last_modification_time modification_time_of(o_info)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  arguments->slots[2] = frame->slots[9] /* temp__5 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__89_58(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1034: build_dependencies mod_filename mod_name c_buf
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = frame->slots[1] /* mod_name */;
  arguments->slots[2] = ((CELL *)frame->slots[7])->contents /* c_buf */;
  result_count = 0;
  myself = var._build_dependencies;
  func = myself->type;
  frame->cont = cont__89_59;
}
static void cont__89_59(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1035: if do_build_static_executable:
  // 1036:   for_each
  // 1037:     "runtime/linker", "runtime/memory", "runtime/debugger": (filename)
  // 1038:       maybe_compile_c_file filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_build_static_executable();
  arguments->slots[1] = func__89_60;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__89_66;
}
static void entry__89_65(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // filename: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 1038: maybe_compile_c_file filename
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  result_count = frame->caller_result_count;
  myself = var._maybe_compile_c_file;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__89_60(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1037: "runtime/linker", "runtime/memory", "runtime/debugger"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__89_61;
  arguments->slots[1] = string__89_62;
  arguments->slots[2] = string__89_63;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__89_64;
}
static void cont__89_64(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1036: for_each
  // 1037:   "runtime/linker", "runtime/memory", "runtime/debugger": (filename)
  // 1038:     maybe_compile_c_file filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__89_65;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__89_66(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1039: ... :
  // 1040:   $info stat(exe_filename)
  // 1041:   if
  // 1042:     ||
  // 1043:       info.is_undefined
  // 1044:       &&
  // 1045:         last_modification_time.is_defined
  // 1046:         last_modification_time > modification_time_of(info)
  // 1047:     :
  // 1048:       !do_link true
  frame->slots[9] /* temp__1 */ = create_closure(entry__89_67, 0);
  // 1039: unless do_link:
  // 1040:   $info stat(exe_filename)
  // 1041:   if
  // 1042:     ||
  // 1043:       info.is_undefined
  // 1044:       &&
  // 1045:         last_modification_time.is_defined
  // 1046:         last_modification_time > modification_time_of(info)
  // 1047:     :
  // 1048:       !do_link true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_link();
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__89_78;
}
static void entry__89_77(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1048: !do_link true
  set__do_link(get__true());
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__89_67(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // exe_filename: 0
  // info: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* exe_filename */
  frame->slots[1] /* info */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1040: $info stat(exe_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* exe_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__89_68;
}
static void cont__89_68(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* info */, arguments->slots[0]);
  // 1043: info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__89_69;
}
static void cont__89_69(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 1044: &&
  // 1045:   last_modification_time.is_defined
  // 1046:   last_modification_time > modification_time_of(info)
  frame->slots[4] /* temp__3 */ = create_closure(entry__89_70, 0);
  // 1042: ||
  // 1043:   info.is_undefined
  // 1044:   &&
  // 1045:     last_modification_time.is_defined
  // 1046:     last_modification_time > modification_time_of(info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__89_76;
}
static void entry__89_70(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // info: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1045: last_modification_time.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__last_modification_time();
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__89_71;
}
static void cont__89_71(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 1046: last_modification_time > modification_time_of(info)
  frame->slots[3] /* temp__3 */ = create_closure(entry__89_72, 0);
  // 1044: &&
  // 1045:   last_modification_time.is_defined
  // 1046:   last_modification_time > modification_time_of(info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__89_75;
}
static void entry__89_72(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // info: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1046: ... modification_time_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__89_73;
}
static void cont__89_73(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 1046: last_modification_time > modification_time_of(info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = get__last_modification_time();
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__89_74;
}
static void cont__89_74(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1046: last_modification_time > modification_time_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__89_75(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1044: &&
  // 1045:   last_modification_time.is_defined
  // 1046:   last_modification_time > modification_time_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__89_76(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1041: if
  // 1042:   ||
  // 1043:     info.is_undefined
  // 1044:     &&
  // 1045:       last_modification_time.is_defined
  // 1046:       last_modification_time > modification_time_of(info)
  // 1047:   :
  // 1048:     !do_link true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = func__89_77;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__89_78(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1049: ... :
  // 1050:   $$libs_and_files library_paths_and_file_list()
  // 1051:   if do_link_profiler: push &libs_and_files "/usr/lib/libprofiler.so.0"
  // 1052:   if
  // 1053:     do_build_static_executable:
  // 1054:       if verbose: ewriteln "linking static executable"
  // 1055:       CC $_out $err $success
  // 1056:         "runtime/linker.o"
  // 1057:         "runtime/memory.o"
  // 1058:         "runtime/debugger.o"
  // ...
  frame->slots[9] /* temp__1 */ = create_closure(entry__89_79, 0);
  // 1049: if do_link:
  // 1050:   $$libs_and_files library_paths_and_file_list()
  // 1051:   if do_link_profiler: push &libs_and_files "/usr/lib/libprofiler.so.0"
  // 1052:   if
  // 1053:     do_build_static_executable:
  // 1054:       if verbose: ewriteln "linking static executable"
  // 1055:       CC $_out $err $success
  // 1056:         "runtime/linker.o"
  // 1057:         "runtime/memory.o"
  // 1058:         "runtime/debugger.o"
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_link();
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__89_110;
}
static void entry__89_108(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // err: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* err */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1073: ... err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* err */;
  result_count = 1;
  myself = get__from_utf8();
  func = myself->type;
  frame->cont = cont__89_109;
}
static void cont__89_109(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1073: ... Error err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__89_93(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // err: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* err */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1062: ... err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* err */;
  result_count = 1;
  myself = get__from_utf8();
  func = myself->type;
  frame->cont = cont__89_94;
}
static void cont__89_94(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1062: ... Error err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__89_85(void) {
  allocate_initialized_frame_gc(2, 8);
  // slot allocations:
  // libs_and_files: 0
  // exe_filename: 1
  // out: 2
  // err: 3
  // success: 4
  frame->slots[0] = myself->closure.frame->slots[1]; /* libs_and_files */
  frame->slots[1] = myself->closure.frame->slots[0]; /* exe_filename */
  frame->slots[2] /* out */ = create_future();
  frame->slots[3] /* err */ = create_future();
  frame->slots[4] /* success */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1054: if verbose: ewriteln "linking static executable"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = func__89_86;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__89_88;
}
static void entry__89_86(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1054: ... ewriteln "linking static executable"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__89_87;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__89_88(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1055: CC $_out $err $success
  // 1056:   "runtime/linker.o"
  // 1057:   "runtime/memory.o"
  // 1058:   "runtime/debugger.o"
  // 1059:   libs_and_files*
  // 1060:   "-o"
  // 1061:   exe_filename
  argument_count = 0;
  arguments = node_p;
  arguments->slots[argument_count++] = string__89_89;
  arguments->slots[argument_count++] = string__89_90;
  arguments->slots[argument_count++] = string__89_91;
  unfold(((CELL *)frame->slots[0])->contents /* libs_and_files */);
  arguments->slots[argument_count++] = string__70_6;
  arguments->slots[argument_count++] = frame->slots[1] /* exe_filename */;
  result_count = 3;
  myself = var._CC;
  func = myself->type;
  frame->cont = cont__89_92;
}
static void cont__89_92(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  frame->slots[6] /* temp__2 */ = arguments->slots[1];
  frame->slots[7] /* temp__3 */ = arguments->slots[2];
  // 1055: ... _out
  initialize_future(frame->slots[2] /* out */, frame->slots[5] /* temp__1 */);
  // 1055: ... err
  initialize_future(frame->slots[3] /* err */, frame->slots[6] /* temp__2 */);
  // 1055: ... success
  initialize_future(frame->slots[4] /* success */, frame->slots[7] /* temp__3 */);
  // 1062: ... : Error err.from_utf8
  frame->slots[5] /* temp__1 */ = create_closure(entry__89_93, 0);
  // 1062: unless success: Error err.from_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* success */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__89_95(void) {
  allocate_initialized_frame_gc(2, 11);
  // slot allocations:
  // libs_and_files: 0
  // exe_filename: 1
  // out: 2
  // err: 3
  // success: 4
  frame->slots[0] = myself->closure.frame->slots[1]; /* libs_and_files */
  frame->slots[1] = myself->closure.frame->slots[0]; /* exe_filename */
  frame->slots[2] /* out */ = create_future();
  frame->slots[3] /* err */ = create_future();
  frame->slots[4] /* success */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1064: if verbose: ewriteln "linking executable"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = func__89_96;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__89_98;
}
static void entry__89_96(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1064: ... ewriteln "linking executable"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__89_97;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__89_98(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1068: operating_system()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__operating_system();
  func = myself->type;
  frame->cont = cont__89_99;
}
static void cont__89_99(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__3 */ = arguments->slots[0];
  // 1068: operating_system() == "linux"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__3 */;
  arguments->slots[1] = string__77_23;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__89_100;
}
static void cont__89_100(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 1067: if
  // 1068:   operating_system() == "linux"
  // 1069:   -> "-l:libsim.so.@(MAJOR)"
  // 1070:   -> "-lsim-@(MAJOR)"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = func__89_101;
  arguments->slots[2] = func__89_104;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__89_106;
}
static void entry__89_101(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1069: ... "-l:libsim.so.@(MAJOR)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__89_102;
  arguments->slots[1] = var._MAJOR;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__89_103;
}
static void cont__89_103(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1069: -> "-l:libsim.so.@(MAJOR)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__89_104(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1070: ... "-lsim-@(MAJOR)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__84_71;
  arguments->slots[1] = var._MAJOR;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__89_105;
}
static void cont__89_105(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1070: -> "-lsim-@(MAJOR)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__89_106(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 1065: CC $_out $err $success
  // 1066:   libs_and_files*
  // 1067:   if
  // 1068:     operating_system() == "linux"
  // 1069:     -> "-l:libsim.so.@(MAJOR)"
  // 1070:     -> "-lsim-@(MAJOR)"
  // 1071:   "-o"
  // 1072:   exe_filename
  argument_count = 0;
  arguments = node_p;
  unfold(((CELL *)frame->slots[0])->contents /* libs_and_files */);
  arguments->slots[argument_count++] = frame->slots[5] /* temp__1 */;
  arguments->slots[argument_count++] = string__70_6;
  arguments->slots[argument_count++] = frame->slots[1] /* exe_filename */;
  result_count = 3;
  myself = var._CC;
  func = myself->type;
  frame->cont = cont__89_107;
}
static void cont__89_107(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__4 */ = arguments->slots[0];
  frame->slots[9] /* temp__5 */ = arguments->slots[1];
  frame->slots[10] /* temp__6 */ = arguments->slots[2];
  // 1065: ... _out
  initialize_future(frame->slots[2] /* out */, frame->slots[8] /* temp__4 */);
  // 1065: ... err
  initialize_future(frame->slots[3] /* err */, frame->slots[9] /* temp__5 */);
  // 1065: ... success
  initialize_future(frame->slots[4] /* success */, frame->slots[10] /* temp__6 */);
  // 1073: ... : Error err.from_utf8
  frame->slots[5] /* temp__1 */ = create_closure(entry__89_108, 0);
  // 1073: unless success: Error err.from_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* success */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__89_79(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // exe_filename: 0
  // libs_and_files: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* exe_filename */
  frame->slots[1] /* libs_and_files */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1050: $$libs_and_files library_paths_and_file_list()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = var._library_paths_and_file_list;
  func = myself->type;
  frame->cont = cont__89_80;
}
static void cont__89_80(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* libs_and_files */ = arguments->slots[0];
  // 1051: ... : push &libs_and_files "/usr/lib/libprofiler.so.0"
  frame->slots[2] /* temp__1 */ = create_closure(entry__89_81, 0);
  // 1051: if do_link_profiler: push &libs_and_files "/usr/lib/libprofiler.so.0"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_link_profiler;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__89_84;
}
static void entry__89_81(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // libs_and_files: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* libs_and_files */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1051: ... push &libs_and_files "/usr/lib/libprofiler.so.0"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* libs_and_files */;
  arguments->slots[1] = string__89_82;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__89_83;
}
static void cont__89_83(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* libs_and_files */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__89_84(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1053: ... :
  // 1054:   if verbose: ewriteln "linking static executable"
  // 1055:   CC $_out $err $success
  // 1056:     "runtime/linker.o"
  // 1057:     "runtime/memory.o"
  // 1058:     "runtime/debugger.o"
  // 1059:     libs_and_files*
  // 1060:     "-o"
  // 1061:     exe_filename
  // 1062:   unless success: Error err.from_utf8
  frame->slots[2] /* temp__1 */ = create_closure(entry__89_85, 0);
  // 1063: :
  // 1064:   if verbose: ewriteln "linking executable"
  // 1065:   CC $_out $err $success
  // 1066:     libs_and_files*
  // 1067:     if
  // 1068:       operating_system() == "linux"
  // 1069:       -> "-l:libsim.so.@(MAJOR)"
  // 1070:       -> "-lsim-@(MAJOR)"
  // 1071:     "-o"
  // 1072:     exe_filename
  // ...
  frame->slots[3] /* temp__2 */ = create_closure(entry__89_95, 0);
  // 1052: if
  // 1053:   do_build_static_executable:
  // 1054:     if verbose: ewriteln "linking static executable"
  // 1055:     CC $_out $err $success
  // 1056:       "runtime/linker.o"
  // 1057:       "runtime/memory.o"
  // 1058:       "runtime/debugger.o"
  // 1059:       libs_and_files*
  // 1060:       "-o"
  // 1061:       exe_filename
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__do_build_static_executable();
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  arguments->slots[2] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__89_110(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1074: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__89_111;
}
static void cont__89_111(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 1074: $zz range(command_line_arguments 2 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__command_line_arguments();
  arguments->slots[1] = number__2;
  arguments->slots[2] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__89_112;
}
static void cont__89_112(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[8] /* zz */, arguments->slots[0]);
  // 1075: ... on_top_level && action == "simrun"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__on_top_level();
  arguments->slots[1] = func__89_113;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__89_115;
}
static void entry__89_113(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1075: ... action == "simrun"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._action;
  arguments->slots[1] = string__84_2;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__89_114;
}
static void cont__89_114(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1075: ... action == "simrun"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__89_115(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 1075: ... :
  // 1076:   exec
  // 1077:     if
  // 1078:       exe_filename .has_prefix. '/'
  // 1079:       -> exe_filename
  // 1080:       -> string("./" exe_filename)
  // 1081:     zz*
  // 1082:     
  // 1083:     #range(command_line_arguments 2 -1)*
  frame->slots[10] /* temp__2 */ = create_closure(entry__89_116, 0);
  // 1075: if on_top_level && action == "simrun":
  // 1076:   exec
  // 1077:     if
  // 1078:       exe_filename .has_prefix. '/'
  // 1079:       -> exe_filename
  // 1080:       -> string("./" exe_filename)
  // 1081:     zz*
  // 1082:     
  // 1083:     #range(command_line_arguments 2 -1)*
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__89_1_build_executable(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  //  995: compile_exe: (mod_filename mod_name)
  //  996:   $exe_filename
  //  997:     if
  //  998:       operating_system() == "cygwin"
  //  999:       -> string(mod_filename ".exe")
  // 1000:       -> mod_filename
  // 1001:   
  // 1002:   if verbose: ewriteln "build executable " exe_filename
  // 1003:   $c_filename string(mod_filename ".c")
  // 1004:   $o_filename string(mod_filename ".o")
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__89_2;
  result_count = frame->caller_result_count;
  myself = var._compile_exe;
  func = myself->type;
  frame = frame->caller_frame;
}
EXPORT void collect__simple(void) {
  var._MAJOR = collect_node(var._MAJOR);
  var._MINOR = collect_node(var._MINOR);
  var._REVISION = collect_node(var._REVISION);
  var._BUILD = collect_node(var._BUILD);
  var._VERSION = collect_node(var._VERSION);
  var._cc = collect_node(var._cc);
  var._mkdir = collect_node(var._mkdir);
  var._SIMLIBPATH = collect_node(var._SIMLIBPATH);
  var._SIMDATAPATH = collect_node(var._SIMDATAPATH);
  var._simlibpaths = collect_node(var._simlibpaths);
  var._simdatapaths = collect_node(var._simdatapaths);
  var._NONE = collect_node(var._NONE);
  var._supported_platforms = collect_node(var._supported_platforms);
  var._platform_priority = collect_node(var._platform_priority);
  var._platform_specific_priority = collect_node(var._platform_specific_priority);
  var._module_info = collect_node(var._module_info);
  var._meta_levels = collect_node(var._meta_levels);
  var._do_rebuild = collect_node(var._do_rebuild);
  var._do_omit_meta = collect_node(var._do_omit_meta);
  var.sim2c__do_dump_trees = collect_node(var.sim2c__do_dump_trees);
  var.sim2c__do_pretty_print = collect_node(var.sim2c__do_pretty_print);
  var.sim2c__do_print_simplified_source = collect_node(var.sim2c__do_print_simplified_source);
  var.sim2c__do_show_debug_infos = collect_node(var.sim2c__do_show_debug_infos);
  var.sim2c__do_show_compiler_debug_infos = collect_node(var.sim2c__do_show_compiler_debug_infos);
  var.sim2c__do_check_only = collect_node(var.sim2c__do_check_only);
  var.sim2c__do_show_brief_messages = collect_node(var.sim2c__do_show_brief_messages);
  var.sim2c__do_print_warnings = collect_node(var.sim2c__do_print_warnings);
  var.sim2c__verbose = collect_node(var.sim2c__verbose);
  var._do_print_c = collect_node(var._do_print_c);
  var.sim2c__do_extract_documentation = collect_node(var.sim2c__do_extract_documentation);
  var._do_build_codeblocks_project = collect_node(var._do_build_codeblocks_project);
  var._do_list_dependencies = collect_node(var._do_list_dependencies);
  var._do_build_static = collect_node(var._do_build_static);
  var._do_link_profiler = collect_node(var._do_link_profiler);
  var.sim2c__do_time_passes = collect_node(var.sim2c__do_time_passes);
  var._module_prefix = collect_node(var._module_prefix);
  var._input_filename = collect_node(var._input_filename);
  var._action = collect_node(var._action);
  var.sim2c__show_compiler_debug_info = collect_node(var.sim2c__show_compiler_debug_info);
  var._EXE = collect_node(var._EXE);
  var._LIB = collect_node(var._LIB);
  var._WHITESPACE = collect_node(var._WHITESPACE);
  var._cc_basic_options = collect_node(var._cc_basic_options);
  var._gcc_options = collect_node(var._gcc_options);
  var._cc_hardware_specific_options = collect_node(var._cc_hardware_specific_options);
  var._cc_include_options = collect_node(var._cc_include_options);
  var._cc_options = collect_node(var._cc_options);
  var._c_sources = collect_node(var._c_sources);
  var._dependencies = collect_node(var._dependencies);
  var._resolved_libraries = collect_node(var._resolved_libraries);
  var._resolve_filename = collect_node(var._resolve_filename);
  var._add_module_infos = collect_node(var._add_module_infos);
  var._lookup = collect_node(var._lookup);
  var._CC = collect_node(var._CC);
  var._compile_c = collect_node(var._compile_c);
  var._compile_meta_module = collect_node(var._compile_meta_module);
  var._build_dependencies = collect_node(var._build_dependencies);
  var._compile_module = collect_node(var._compile_module);
  var._compile_modules = collect_node(var._compile_modules);
  var._show_file_list = collect_node(var._show_file_list);
  var._library_paths_and_file_list = collect_node(var._library_paths_and_file_list);
  var._create_imports = collect_node(var._create_imports);
  var._compile_exe = collect_node(var._compile_exe);
  var._dump_source_or_check = collect_node(var._dump_source_or_check);
  var._print_c = collect_node(var._print_c);
  var._list_dependencies = collect_node(var._list_dependencies);
  var._build_codeblocks_project = collect_node(var._build_codeblocks_project);
  var._build_library = collect_node(var._build_library);
  var._maybe_compile_c_file = collect_node(var._maybe_compile_c_file);
  var._t = collect_node(var._t);
  var._format_number = collect_node(var._format_number);
  var.sim2c__write_timing_info = collect_node(var.sim2c__write_timing_info);
  var._build_executable = collect_node(var._build_executable);
}

int main(int argc, char **argv) {
  main_argc = argc;
  main_argv = argv;
  initialize_runtime();

  // initialization phase 1

  phase_1__basic__exceptions();
  phase_1__basic__serialize();
  phase_1__basic__deserialize();
  phase_1__basic__branches();
  phase_1__basic__debug();
  phase_1__basic__environment();
  phase_1__basic__event();
  phase_1__basic__exec();
  phase_1__basic__functional();
  phase_1__basic__grammar();
  phase_1__basic__io();
  phase_1__basic__loops();
  phase_1__basic__math();
  phase_1__basic__options();
  phase_1__basic__parameters();
  phase_1__basic__platform();
  phase_1__basic__polymorphic_functions();
  phase_1__basic__primitives();
  phase_1__basic__runtime();
  phase_1__basic__types__boolean();
  phase_1__basic__types__character();
  phase_1__basic__types__continuation();
  phase_1__basic__types__date_and_time();
  phase_1__basic__types__function();
  phase_1__basic__types__insert_order_set();
  phase_1__basic__types__insert_order_table();
  phase_1__basic__types__list();
  phase_1__basic__types__multi_dimensional_set();
  phase_1__basic__types__multi_dimensional_table();
  phase_1__basic__types__number();
  phase_1__basic__types__object();
  phase_1__basic__types__key_order_table();
  phase_1__basic__types__key_value_pair();
  phase_1__basic__types__set();
  phase_1__basic__types__key_order_set();
  phase_1__basic__types__string_primitives();
  phase_1__basic__types__string();
  phase_1__basic__types__table();
  phase_1__basic__types__undefined();
  phase_1__basic__types__unique_item();
  phase_1__basic__types__unordered_set();
  phase_1__basic__types__unordered_table();
  phase_1__basic__types__value_range();
  phase_1__system__export__html();
  phase_1__character_names();
  phase_1__fragments();
  phase_1__tokenizer();
  phase_1__shared_variables();
  phase_1__nodes();
  phase_1__parser();
  phase_1__expander();
  phase_1__annotator();
  phase_1__simplifier();
  phase_1__macros();
  phase_1__c_code_generator();
  phase_1__pretty_printer();
  phase_1__sim2c();
  phase_1__extractor();
  phase_1__runtime_definitions();
  register_module_info(&module_info);

  // initialization phase 2
  phase_2__basic__exceptions();
  phase_2__basic__serialize();
  phase_2__basic__deserialize();
  phase_2__basic__branches();
  phase_2__basic__debug();
  phase_2__basic__environment();
  phase_2__basic__event();
  phase_2__basic__exec();
  phase_2__basic__functional();
  phase_2__basic__grammar();
  phase_2__basic__io();
  phase_2__basic__loops();
  phase_2__basic__math();
  phase_2__basic__options();
  phase_2__basic__parameters();
  phase_2__basic__platform();
  phase_2__basic__polymorphic_functions();
  phase_2__basic__primitives();
  phase_2__basic__runtime();
  phase_2__basic__types__boolean();
  phase_2__basic__types__character();
  phase_2__basic__types__continuation();
  phase_2__basic__types__date_and_time();
  phase_2__basic__types__function();
  phase_2__basic__types__insert_order_set();
  phase_2__basic__types__insert_order_table();
  phase_2__basic__types__list();
  phase_2__basic__types__multi_dimensional_set();
  phase_2__basic__types__multi_dimensional_table();
  phase_2__basic__types__number();
  phase_2__basic__types__object();
  phase_2__basic__types__key_order_table();
  phase_2__basic__types__key_value_pair();
  phase_2__basic__types__set();
  phase_2__basic__types__key_order_set();
  phase_2__basic__types__string_primitives();
  phase_2__basic__types__string();
  phase_2__basic__types__table();
  phase_2__basic__types__undefined();
  phase_2__basic__types__unique_item();
  phase_2__basic__types__unordered_set();
  phase_2__basic__types__unordered_table();
  phase_2__basic__types__value_range();
  phase_2__system__export__html();
  phase_2__character_names();
  phase_2__fragments();
  phase_2__tokenizer();
  phase_2__shared_variables();
  phase_2__nodes();
  phase_2__parser();
  phase_2__expander();
  phase_2__annotator();
  phase_2__simplifier();
  phase_2__macros();
  phase_2__c_code_generator();
  phase_2__pretty_printer();
  phase_2__sim2c();
  phase_2__extractor();
  phase_2__runtime_definitions();
  character__35 = from_uchar32(35);
  character__47 = from_uchar32(47);
  number__12 = from_uint32(12U);
  character__45 = from_uchar32(45);
  character__58 = from_uchar32(58);
  number__0 = from_uint32(0U);
  number__3 = from_uint32(3U);
  number__4 = from_uint32(4U);
  character__95 = from_uchar32(95);
  number__5 = from_uint32(5U);
  character__123 = from_uchar32(123);
  character__32 = from_uchar32(32);
  character__125 = from_uchar32(125);
  number__1 = from_uint32(1U);
  number__18 = from_uint32(18U);
  character__46 = from_uchar32(46);
  number__2 = from_uint32(2U);
  number__999 = from_uint32(999U);
  unique__NONE = register_unique_item("NONE");
  func__47_1_sim2c__show_compiler_debug_info = create_function(entry__47_1_sim2c__show_compiler_debug_info, -1);
  unique__EXE = register_unique_item("EXE");
  unique__LIB = register_unique_item("LIB");
  func__66_8 = create_function(entry__66_8, 1);
  func__66_4 = create_function(entry__66_4, 1);
  func__66_3 = create_function(entry__66_3, 0);
  string__66_21 = from_latin_1_string("Cannot resolve required library \042", 33);
  string__66_22 = from_latin_1_string("\042!", 2);
  func__66_1_resolve_filename = create_function(entry__66_1_resolve_filename, 1);
  string__67_13 = from_latin_1_string(".sim", 4);
  string__67_16 = from_latin_1_string(".meta", 5);
  string__67_42 = from_latin_1_string("-common", 7);
  string__67_46 = from_latin_1_string("-", 1);
  string__67_58 = from_latin_1_string("The platform \042", 14);
  string__67_59 = from_latin_1_string("\042 is not supported!", 19);
  func__67_1_add_module_infos = create_function(entry__67_1_add_module_infos, 2);
  func__68_1_lookup = create_function(entry__68_1_lookup, 2);
  func__69_1_CC = create_function(entry__69_1_CC, -1);
  func__70_2 = create_function(entry__70_2, 0);
  string__70_5 = from_latin_1_string("-c", 2);
  string__70_6 = from_latin_1_string("-o", 2);
  string__70_10 = from_latin_1_string("Failed to compile ", 18);
  string__70_11 = from_latin_1_string("\012", 1);
  func__70_1_compile_c = create_function(entry__70_1_compile_c, 2);
  string__71_9 = from_latin_1_string(".c", 2);
  string__71_46 = from_latin_1_string("/// ", 4);
  string__71_53 = from_latin_1_string("data", 4);
  string__71_56 = from_latin_1_string("./", 2);
  func__71_1_compile_meta_module = create_function(entry__71_1_compile_meta_module, 3);
  func__72_24 = create_function(entry__72_24, 0);
  func__72_23 = create_function(entry__72_23, 0);
  string__72_32 = from_latin_1_string("sim-", 4);
  string__72_39 = from_latin_1_string("require", 7);
  string__72_40 = from_latin_1_string("link", 4);
  func__72_1_build_dependencies = create_function(entry__72_1_build_dependencies, -1);
  func__73_9 = create_function(entry__73_9, 0);
  string__73_38 = from_latin_1_string("__", 2);
  string__73_43 = from_latin_1_string("build module ", 13);
  string__73_76 = from_latin_1_string("No source file(s) for module \042", 30);
  string__73_77 = from_latin_1_string("\042 found!", 8);
  string__73_80 = from_latin_1_string(".o", 2);
  string__73_131 = from_latin_1_string(" #", 2);
  func__73_1_compile_module = create_function(entry__73_1_compile_module, 2);
  func__74_1_compile_modules = create_function(entry__74_1_compile_modules, 2);
  string__76_3 = from_latin_1_string("LD_LIBRARY_PATH", 15);
  string__76_7 = from_latin_1_string("LD_LIBRARY_PATH=", 16);
  string__76_11 = from_latin_1_string("included object files: ", 23);
  string__76_14 = from_latin_1_string("needed libraries: ", 18);
  func__76_2 = create_function(entry__76_2, 0);
  func__76_1_show_file_list = create_function(entry__76_1_show_file_list, 0);
  string__77_8 = from_latin_1_string("-L", 2);
  string__77_14 = from_latin_1_string("library paths: ", 15);
  string__77_23 = from_latin_1_string("linux", 5);
  string__77_26 = from_latin_1_string("-l:lib", 6);
  string__77_27 = from_latin_1_string(".so.", 4);
  string__77_30 = from_latin_1_string("-l", 2);
  func__77_1_library_paths_and_file_list = create_function(entry__77_1_library_paths_and_file_list, 0);
  string__78_26 = from_latin_1_string("typedef", 7);
  string__78_30 = from_latin_1_string("REGISTER", 8);
  string__78_44 = from_latin_1_string("typedef struct", 14);
  string__78_55 = from_latin_1_string("IMPORT ", 7);
  func__78_54 = create_function(entry__78_54, 0);
  string__78_65 = from_latin_1_string("// INSERT HERE //", 17);
  string__78_75 = from_latin_1_string("collecting imports", 18);
  func__78_74 = create_function(entry__78_74, 0);
  func__78_1_create_imports = create_function(entry__78_1_create_imports, 1);
  string__79_4 = from_latin_1_string("Expected a source code file!", 28);
  func__79_3 = create_function(entry__79_3, 0);
  string__79_8 = from_latin_1_string("Expected \042.sim\042 file extension in source filename!", 50);
  func__79_7 = create_function(entry__79_7, 0);
  func__79_1_compile_exe = create_function(entry__79_1_compile_exe, 1);
  func__80_2 = create_function(entry__80_2, 2);
  func__80_1_dump_source_or_check = create_function(entry__80_1_dump_source_or_check, 0);
  string__81_19 = from_latin_1_string("writing C-source", 16);
  func__81_18 = create_function(entry__81_18, 0);
  func__81_2 = create_function(entry__81_2, 2);
  func__81_1_print_c = create_function(entry__81_1_print_c, 0);
  func__82_3 = create_function(entry__82_3, 2);
  string__82_18 = from_latin_1_string("list dependencies for ", 22);
  func__82_17 = create_function(entry__82_17, 0);
  func__82_16 = create_function(entry__82_16, 0);
  func__82_24 = create_function(entry__82_24, 2);
  string__82_28 = from_latin_1_string("runtime/linker.c", 16);
  string__82_30 = from_latin_1_string("runtime/memory.c", 16);
  string__82_32 = from_latin_1_string("runtime/debugger.c", 18);
  func__82_23 = create_function(entry__82_23, 0);
  func__82_1_list_dependencies = create_function(entry__82_1_list_dependencies, 0);
  string__83_3 = from_latin_1_string(".codeblocks", 11);
  string__83_8 = from_latin_1_string("The directory \042", 15);
  string__83_9 = from_latin_1_string("\042 already exists!\012", 18);
  string__83_13 = from_latin_1_string("build Code::Blocks project in ", 30);
  string__83_23 = from_latin_1_string("../", 3);
  string__83_25 = from_latin_1_string("/", 1);
  string__83_26 = from_latin_1_string(".cbp", 4);
  string__83_29 = from_latin_1_string("<?xml version=\0421.0\042 encoding=\042UTF-8\042 standalone=\042yes\042 ?>\012<CodeBlocks_project_file>\012  <FileVersion major=\0421\042 minor=\0426\042 />\012  <Project>\012    <Option title=\042", 152);
  string__83_30 = from_latin_1_string("\042 />\012    <Option pch_mode=\0422\042 />\012    <Option compiler=c_compiler() />\012    <Build>\012      <Target title=\042debug\042>\012        <Option output=\042bin/debug/", 145);
  string__83_31 = from_latin_1_string("\042 prefix_auto=\0421\042 extension_auto=\0421\042 />\012        <Option object_output=\042obj/debug/\042 />\012        <Option type=\0421\042 />\012        <Option compiler=c_compiler() />\012        <Compiler>\012          <Add option=\042-g\042 />\012        </Compiler>\012      </Target>\012    </Build>\012    <Linker>\012", 266);
  string__83_35 = from_latin_1_string("      <Add library=\042", 20);
  string__83_36 = from_latin_1_string("\042 />\012", 5);
  string__83_43 = from_latin_1_string("\012    </Linker>\012    <Compiler>\012      <Add option=\042-Wall\042 />\012    </Compiler>\012    <Unit filename=\042", 95);
  string__83_44 = from_latin_1_string("runtime/common.h\042 />\012    <Unit filename=\042", 41);
  string__83_45 = from_latin_1_string("runtime/linker.h\042 />\012    <Unit filename=\042", 41);
  string__83_46 = from_latin_1_string("runtime/memory.c\042>\012      <Option compilerVar=\042", 46);
  string__83_47 = from_latin_1_string("\042 />\012    </Unit>\012    <Unit filename=\042", 37);
  string__83_48 = from_latin_1_string("runtime/debugger.c\042>\012      <Option compilerVar=\042", 48);
  string__83_49 = from_latin_1_string("runtime/linker.c\042>\012      <Option compilerVar=\042", 46);
  string__83_50 = from_latin_1_string("\042 />\012    </Unit>\012", 17);
  string__83_57 = from_latin_1_string("\012    <Unit filename=\042", 21);
  string__83_58 = from_latin_1_string("\042>\012      <Option compilerVar=\042", 30);
  string__83_62 = from_latin_1_string("    <Extensions>\012      <code_completion />\012      <debugger />\012    </Extensions>\012  </Project>\012</CodeBlocks_project_file>\012", 120);
  func__83_2 = create_function(entry__83_2, 2);
  func__83_1_build_codeblocks_project = create_function(entry__83_1_build_codeblocks_project, 0);
  string__84_2 = from_latin_1_string("simrun", 6);
  string__84_5 = from_latin_1_string("Cannot run a directory!", 23);
  func__84_4 = create_function(entry__84_4, 0);
  func__84_7 = create_function(entry__84_7, 0);
  string__84_9 = from_latin_1_string("/VERSION", 8);
  string__84_23 = from_latin_1_string("libsim-", 7);
  string__84_26 = from_latin_1_string(".dll", 4);
  string__84_30 = from_latin_1_string(".dylib", 6);
  string__84_34 = from_latin_1_string(".so", 3);
  string__84_36 = from_latin_1_string("cygwin", 6);
  string__84_37 = from_latin_1_string("darwin", 6);
  string__84_40 = from_latin_1_string("build library ", 14);
  func__84_52 = create_function(entry__84_52, 0);
  string__84_56 = from_latin_1_string("linking dynamic library", 23);
  func__84_55 = create_function(entry__84_55, 0);
  string__84_59 = from_latin_1_string("bsd", 3);
  string__84_62 = from_latin_1_string("-Wl,-soname,libsim-", 19);
  string__84_65 = from_latin_1_string("-shared", 7);
  string__84_71 = from_latin_1_string("-lsim-", 6);
  string__84_77 = from_latin_1_string("-Wl,-install_name,libsim-", 25);
  string__84_81 = from_latin_1_string("-dynamiclib", 11);
  func__84_8 = create_function(entry__84_8, 0);
  func__84_1_build_library = create_function(entry__84_1_build_library, 0);
  string__85_7 = from_latin_1_string("\042", 1);
  string__85_8 = from_latin_1_string("\042 does not exist!\012", 18);
  string__85_20 = from_latin_1_string("compiling runtime module ", 25);
  func__85_1_maybe_compile_c_file = create_function(entry__85_1_maybe_compile_c_file, 1);
  string__87_14 = from_latin_1_string(" ", 1);
  string__87_23 = from_latin_1_string("0", 1);
  func__87_1_format_number = create_function(entry__87_1_format_number, -1);
  string__88_12 = from_latin_1_string(" s", 2);
  string__88_16 = from_latin_1_string(": ", 2);
  func__88_1_sim2c__write_timing_info = create_function(entry__88_1_sim2c__write_timing_info, -1);
  string__89_6 = from_latin_1_string(".exe", 4);
  string__89_11 = from_latin_1_string("build executable ", 17);
  string__89_30 = from_latin_1_string("build main module ", 18);
  func__89_29 = create_function(entry__89_29, 0);
  func__89_32 = create_function(entry__89_32, 0);
  string__89_40 = from_latin_1_string("saving", 6);
  string__89_44 = from_latin_1_string("compiling", 9);
  string__89_61 = from_latin_1_string("runtime/linker", 14);
  string__89_62 = from_latin_1_string("runtime/memory", 14);
  string__89_63 = from_latin_1_string("runtime/debugger", 16);
  func__89_65 = create_function(entry__89_65, 1);
  func__89_60 = create_function(entry__89_60, 0);
  func__89_77 = create_function(entry__89_77, 0);
  string__89_82 = from_latin_1_string("/usr/lib/libprofiler.so.0", 25);
  string__89_87 = from_latin_1_string("linking static executable", 25);
  func__89_86 = create_function(entry__89_86, 0);
  string__89_89 = from_latin_1_string("runtime/linker.o", 16);
  string__89_90 = from_latin_1_string("runtime/memory.o", 16);
  string__89_91 = from_latin_1_string("runtime/debugger.o", 18);
  string__89_97 = from_latin_1_string("linking executable", 18);
  func__89_96 = create_function(entry__89_96, 0);
  string__89_102 = from_latin_1_string("-l:libsim.so.", 13);
  func__89_101 = create_function(entry__89_101, 0);
  func__89_104 = create_function(entry__89_104, 0);
  func__89_113 = create_function(entry__89_113, 0);
  func__89_2 = create_function(entry__89_2, 2);
  func__89_1_build_executable = create_function(entry__89_1_build_executable, 0);
  string__93_1 = from_latin_1_string("Copyright (C) 2020 by\012Dipl.-Ing. Michael Niederle\012\012This program is free software; you can redistribute it and/or modify\012it under the terms of the GNU General Public License, version 2, or\012(at your option) version 3.\012\012This program is distributed in the hope that it will be useful,\012but WITHOUT ANY WARRANTY; without even the implied warranty of\012MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the\012GNU General Public License for more details.\012\012For details of the GNU General Public License see the accompanying\012files GPLv2.txt and GLPv3.txt or\012http://www.gnu.org/licenses/gpl-2.0.html\012http://www.gnu.org/licenses/gpl-3.0.html\012or write to the\012Free Software Foundation, Inc.,\01251 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.\012", 742);
  string__98_1 = from_latin_1_string(".", 1);
  string__101_1 = from_latin_1_string("mkdir", 5);
  string__102_1 = from_latin_1_string("SIMLIBPATH", 10);
  string__103_1 = from_latin_1_string("SIMDATAPATH", 11);
  func__104_2 = create_function(entry__104_2, 0);
  string__104_5 = from_latin_1_string("/usr/local/share/simplicity-", 28);
  string__104_7 = from_latin_1_string("/usr/share/simplicity-", 22);
  func__104_4 = create_function(entry__104_4, 0);
  func__105_2 = create_function(entry__105_2, 0);
  func__105_4 = create_function(entry__105_4, 0);
  string__107_1 = from_latin_1_string("posix", 5);
  string__107_6 = from_latin_1_string("all", 3);
  string__107_8 = from_latin_1_string("win", 3);
  func__109_1 = create_function(entry__109_1, 0);
  string__134_5 = from_latin_1_string("Missing command line arguments!", 31);
  func__134_4 = create_function(entry__134_4, 0);
  func__134_2 = create_function(entry__134_2, 0);
  string__134_10 = from_latin_1_string("check-only", 10);
  string__134_11 = from_latin_1_string("do not compile; just check for syntax errors\012", 45);
  func__134_9 = create_function(entry__134_9, 0);
  string__134_13 = from_latin_1_string("dump-trees", 10);
  string__134_14 = from_latin_1_string("dump abstract syntax trees\012", 27);
  func__134_12 = create_function(entry__134_12, 0);
  string__134_16 = from_latin_1_string("pretty-print", 12);
  string__134_17 = from_latin_1_string("do not compile; just pretty print the source file\012", 50);
  func__134_15 = create_function(entry__134_15, 0);
  string__134_19 = from_latin_1_string("print-simplified-source", 23);
  string__134_20 = from_latin_1_string("do not generate a C-file; just print the simplified source text\012", 64);
  func__134_18 = create_function(entry__134_18, 0);
  string__134_22 = from_latin_1_string("print-c", 7);
  string__134_23 = from_latin_1_string("print C source code for a single module\012", 40);
  func__134_21 = create_function(entry__134_21, 0);
  string__134_25 = from_latin_1_string("time-passes", 11);
  string__134_26 = from_latin_1_string("print running time for the individual compiler passes\012", 54);
  func__134_24 = create_function(entry__134_24, 0);
  string__134_28 = from_latin_1_string("module-prefix", 13);
  string__134_29 = from_latin_1_string("needed to compile a single file within a subdirectory;\012if the subdirectories are nested use slashes to separate\012the directory names\012", 132);
  func__134_27 = create_function(entry__134_27, 0);
  string__134_31 = from_latin_1_string("brief", 5);
  string__134_32 = from_latin_1_string("show brief error messages\012", 26);
  func__134_30 = create_function(entry__134_30, 0);
  string__134_34 = from_latin_1_string("warnings", 8);
  string__134_35 = from_latin_1_string("show warning messages\012", 22);
  func__134_33 = create_function(entry__134_33, 0);
  string__134_37 = from_latin_1_string("verbose", 7);
  string__134_38 = from_latin_1_string("output verbose informations\012", 28);
  func__134_36 = create_function(entry__134_36, 0);
  string__134_40 = from_latin_1_string("debug", 5);
  string__134_41 = from_latin_1_string("show C-compiler and linker calls\012", 33);
  func__134_39 = create_function(entry__134_39, 0);
  string__134_43 = from_latin_1_string("debug_compiler", 14);
  string__134_44 = from_latin_1_string("show internal debug messages of the Simplicity compiler\012", 56);
  func__134_42 = create_function(entry__134_42, 0);
  string__134_46 = from_latin_1_string("codeblocks", 10);
  string__134_47 = from_latin_1_string("create Code::Blocks project\012", 28);
  func__134_45 = create_function(entry__134_45, 0);
  string__134_49 = from_latin_1_string("extract-documentation", 21);
  string__134_50 = from_latin_1_string("extract documentation encoded as HTML\012", 38);
  func__134_48 = create_function(entry__134_48, 0);
  string__134_52 = from_latin_1_string("list-dependencies", 17);
  string__134_53 = from_latin_1_string("list all dependencies\012", 22);
  func__134_51 = create_function(entry__134_51, 0);
  string__134_55 = from_latin_1_string("rebuild", 7);
  string__134_56 = from_latin_1_string("rebuild all source files\012", 25);
  func__134_54 = create_function(entry__134_54, 0);
  string__134_58 = from_latin_1_string("omit-meta", 9);
  string__134_59 = from_latin_1_string("do not rebuild meta files\012", 26);
  func__134_57 = create_function(entry__134_57, 0);
  string__134_61 = from_latin_1_string("static", 6);
  string__134_62 = from_latin_1_string("create statically linked executable\012", 36);
  func__134_60 = create_function(entry__134_60, 0);
  string__134_64 = from_latin_1_string("profile", 7);
  string__134_65 = from_latin_1_string("link with libprofiler\012", 22);
  func__134_63 = create_function(entry__134_63, 0);
  string__134_67 = from_latin_1_string("filename", 8);
  string__134_68 = from_latin_1_string("the name of the source file to compile\012", 39);
  func__134_66 = create_function(entry__134_66, 0);
  func__134_8 = create_function(entry__134_8, 0);
  func__138_1 = create_function(entry__138_1, 0);
  string__144_1 = from_latin_1_string("-Wall", 5);
  string__144_2 = from_latin_1_string("-Wno-unused-function", 20);
  string__144_3 = from_latin_1_string("-Wno-unused-variable", 20);
  string__144_4 = from_latin_1_string("-Wno-parentheses", 16);
  string__144_5 = from_latin_1_string("-Wno-switch", 11);
  string__144_6 = from_latin_1_string("-Wno-trigraphs", 14);
  string__144_7 = from_latin_1_string("-O1", 3);
  string__144_8 = from_latin_1_string("-fPIC", 5);
  string__144_9 = from_latin_1_string("-fno-stack-protector", 20);
  string__144_10 = from_latin_1_string("-falign-functions=16", 20);
  string__145_1 = from_latin_1_string("-Wno-maybe-uninitialized", 24);
  string__146_1 = from_latin_1_string("-msse2", 6);
  string__146_2 = from_latin_1_string("-mfpmath=sse", 12);
  string__146_4 = from_latin_1_string("x86_32", 6);
  string__146_7 = from_latin_1_string("x86_64", 6);
  string__148_2 = from_latin_1_string("-I", 2);
  func__148_1 = create_function(entry__148_1, 1);
  string__149_5 = from_latin_1_string("gcc", 3);
  func__149_7 = create_function(entry__149_7, 0);
  func__149_8 = create_function(entry__149_8, 0);
  string__167_3 = from_latin_1_string("Source file \042", 13);
  string__167_4 = from_latin_1_string("\042 does not exist!", 17);
  func__167_2 = create_function(entry__167_2, 0);
  func__182_1 = create_function(entry__182_1, 0);
  func__183_4 = create_function(entry__183_4, 0);
  func__183_3 = create_function(entry__183_3, 0);
  func__183_2 = create_function(entry__183_2, 0);
  func__183_1 = create_function(entry__183_1, 0);
  func__183_8 = create_function(entry__183_8, 0);
  func__183_9 = create_function(entry__183_9, 0);
  func__183_10 = create_function(entry__183_10, 0);
  func__183_11 = create_function(entry__183_11, 0);

  // initialization phase 3

  initialize_phase_3();
  resolve_symbols();
  phase_3__basic__exceptions();
  phase_3__basic__serialize();
  phase_3__basic__deserialize();
  phase_3__basic__branches();
  phase_3__basic__debug();
  phase_3__basic__environment();
  phase_3__basic__event();
  phase_3__basic__exec();
  phase_3__basic__functional();
  phase_3__basic__grammar();
  phase_3__basic__io();
  phase_3__basic__loops();
  phase_3__basic__math();
  phase_3__basic__options();
  phase_3__basic__parameters();
  phase_3__basic__platform();
  phase_3__basic__polymorphic_functions();
  phase_3__basic__primitives();
  phase_3__basic__runtime();
  phase_3__basic__types__boolean();
  phase_3__basic__types__character();
  phase_3__basic__types__continuation();
  phase_3__basic__types__date_and_time();
  phase_3__basic__types__function();
  phase_3__basic__types__insert_order_set();
  phase_3__basic__types__insert_order_table();
  phase_3__basic__types__list();
  phase_3__basic__types__multi_dimensional_set();
  phase_3__basic__types__multi_dimensional_table();
  phase_3__basic__types__number();
  phase_3__basic__types__object();
  phase_3__basic__types__key_order_table();
  phase_3__basic__types__key_value_pair();
  phase_3__basic__types__set();
  phase_3__basic__types__key_order_set();
  phase_3__basic__types__string_primitives();
  phase_3__basic__types__string();
  phase_3__basic__types__table();
  phase_3__basic__types__undefined();
  phase_3__basic__types__unique_item();
  phase_3__basic__types__unordered_set();
  phase_3__basic__types__unordered_table();
  phase_3__basic__types__value_range();
  phase_3__system__export__html();
  phase_3__character_names();
  phase_3__fragments();
  phase_3__tokenizer();
  phase_3__shared_variables();
  phase_3__nodes();
  phase_3__parser();
  phase_3__expander();
  phase_3__annotator();
  phase_3__simplifier();
  phase_3__macros();
  phase_3__c_code_generator();
  phase_3__pretty_printer();
  phase_3__sim2c();
  phase_3__extractor();
  phase_3__runtime_definitions();
  set_module("simple");
  set_used_namespaces(used_namespaces);
  var._MAJOR = create_future();
  var._MINOR = create_future();
  var._REVISION = create_future();
  var._VERSION = create_future();
  var._cc = create_future();
  var._mkdir = create_future();
  var._SIMLIBPATH = create_future();
  var._SIMDATAPATH = create_future();
  var._simlibpaths = create_future();
  var._simdatapaths = create_future();
  assign_value(&var._NONE, unique__NONE);
  var._supported_platforms = create_future();
  define_multi_assign_static("sim2c", "do_dump_trees", get__sim2c__do_dump_trees, set__sim2c__do_dump_trees);
  define_multi_assign_static("sim2c", "do_pretty_print", get__sim2c__do_pretty_print, set__sim2c__do_pretty_print);
  define_multi_assign_static("sim2c", "do_print_simplified_source", get__sim2c__do_print_simplified_source, set__sim2c__do_print_simplified_source);
  define_multi_assign_static("sim2c", "do_show_debug_infos", get__sim2c__do_show_debug_infos, set__sim2c__do_show_debug_infos);
  define_multi_assign_static("sim2c", "do_show_compiler_debug_infos", get__sim2c__do_show_compiler_debug_infos, set__sim2c__do_show_compiler_debug_infos);
  define_multi_assign_static("sim2c", "do_check_only", get__sim2c__do_check_only, set__sim2c__do_check_only);
  define_multi_assign_static("sim2c", "do_show_brief_messages", get__sim2c__do_show_brief_messages, set__sim2c__do_show_brief_messages);
  define_multi_assign_static("sim2c", "do_print_warnings", get__sim2c__do_print_warnings, set__sim2c__do_print_warnings);
  define_multi_assign_static("sim2c", "verbose", get__sim2c__verbose, set__sim2c__verbose);
  define_multi_assign_static("sim2c", "do_extract_documentation", get__sim2c__do_extract_documentation, set__sim2c__do_extract_documentation);
  define_multi_assign_static("sim2c", "do_time_passes", get__sim2c__do_time_passes, set__sim2c__do_time_passes);
  var._action = create_future();
  register_dynamic(&dyna_idx__main_filename);
  define__main_filename(create_future());
  register_dynamic(&dyna_idx__main_info);
  define__main_info(create_future());
  register_dynamic(&dyna_idx__do_build_static_executable);
  define__do_build_static_executable(create_future());
  define_single_assign_static("sim2c", "show_compiler_debug_info", get__sim2c__show_compiler_debug_info, &var.sim2c__show_compiler_debug_info);
  assign_value(&var._EXE, unique__EXE);
  assign_value(&var._LIB, unique__LIB);
  register_dynamic(&dyna_idx__mode);
  define__mode(create_future());
  var._WHITESPACE = create_future();
  var._cc_basic_options = create_future();
  var._gcc_options = create_future();
  var._cc_hardware_specific_options = create_future();
  var._cc_options = create_future();
  register_dynamic(&dyna_idx__on_top_level);
  define__on_top_level(create_future());
  register_dynamic(&dyna_idx__objects);
  define__objects(undefined);
  register_dynamic(&dyna_idx__libraries);
  define__libraries(undefined);
  register_dynamic(&dyna_idx__do_link);
  define__do_link(undefined);
  register_dynamic(&dyna_idx__last_modification_time);
  define__last_modification_time(undefined);
  define_single_assign_static("sim2c", "write_timing_info", get__sim2c__write_timing_info, &var.sim2c__write_timing_info);

  // initialization phase 4

  initialize_phase_4();
  phase_4__basic__exceptions();
  phase_4__basic__serialize();
  phase_4__basic__deserialize();
  phase_4__basic__branches();
  phase_4__basic__debug();
  phase_4__basic__environment();
  phase_4__basic__event();
  phase_4__basic__exec();
  phase_4__basic__functional();
  phase_4__basic__grammar();
  phase_4__basic__io();
  phase_4__basic__loops();
  phase_4__basic__math();
  phase_4__basic__options();
  phase_4__basic__parameters();
  phase_4__basic__platform();
  phase_4__basic__polymorphic_functions();
  phase_4__basic__primitives();
  phase_4__basic__runtime();
  phase_4__basic__types__boolean();
  phase_4__basic__types__character();
  phase_4__basic__types__continuation();
  phase_4__basic__types__date_and_time();
  phase_4__basic__types__function();
  phase_4__basic__types__insert_order_set();
  phase_4__basic__types__insert_order_table();
  phase_4__basic__types__list();
  phase_4__basic__types__multi_dimensional_set();
  phase_4__basic__types__multi_dimensional_table();
  phase_4__basic__types__number();
  phase_4__basic__types__object();
  phase_4__basic__types__key_order_table();
  phase_4__basic__types__key_value_pair();
  phase_4__basic__types__set();
  phase_4__basic__types__key_order_set();
  phase_4__basic__types__string_primitives();
  phase_4__basic__types__string();
  phase_4__basic__types__table();
  phase_4__basic__types__undefined();
  phase_4__basic__types__unique_item();
  phase_4__basic__types__unordered_set();
  phase_4__basic__types__unordered_table();
  phase_4__basic__types__value_range();
  phase_4__system__export__html();
  phase_4__character_names();
  phase_4__fragments();
  phase_4__tokenizer();
  phase_4__shared_variables();
  phase_4__nodes();
  phase_4__parser();
  phase_4__expander();
  phase_4__annotator();
  phase_4__simplifier();
  phase_4__macros();
  phase_4__c_code_generator();
  phase_4__pretty_printer();
  phase_4__sim2c();
  phase_4__extractor();
  phase_4__runtime_definitions();
  set_module("simple");
  set_used_namespaces(used_namespaces);
  use_read_only(NULL, "Error", &get__Error, &get_value_or_future__Error);
  use_read_only(NULL, "NAME", &get__NAME, &get_value_or_future__NAME);
  use_read_only(NULL, "SORT", &get__SORT, &get_value_or_future__SORT);
  use_read_only(NULL, "VALUED_OPTION", &get__VALUED_OPTION, &get_value_or_future__VALUED_OPTION);
  use_read_only(NULL, "append", &get__append, &get_value_or_future__append);
  use_read_only(NULL, "before", &get__before, &get_value_or_future__before);
  use_read_only(NULL, "behind", &get__behind, &get_value_or_future__behind);
  use_read_only(NULL, "between", &get__between, &get_value_or_future__between);
  use_read_only(NULL, "c_compiler", &get__c_compiler, &get_value_or_future__c_compiler);
  use_read_only(NULL, "case", &get__case, &get_value_or_future__case);
  use_read_only(NULL, "change_directory", &get__change_directory, &get_value_or_future__change_directory);
  use_read_only(NULL, "collect_output", &get__collect_output, &get_value_or_future__collect_output);
  use_read_only(NULL, "command_line_arguments", &get__command_line_arguments, &get_value_or_future__command_line_arguments);
  use_read_only(NULL, "cond", &get__cond, &get_value_or_future__cond);
  use_read_only(NULL, "contains", &get__contains, &get_value_or_future__contains);
  use_read_only(NULL, "copyright", &get__copyright, &get_value_or_future__copyright);
  use_read_only(NULL, "count_occurrences", &get__count_occurrences, &get_value_or_future__count_occurrences);
  use_read_only(NULL, "current_path", &get__current_path, &get_value_or_future__current_path);
  use_read_only(NULL, "current_time", &get__current_time, &get_value_or_future__current_time);
  use_read_only(NULL, "dec", &get__dec, &get_value_or_future__dec);
  use_read_only(NULL, "default_value", &get__default_value, &get_value_or_future__default_value);
  use_read_only(NULL, "directory", &get__directory, &get_value_or_future__directory);
  use_read_only(NULL, "do", &get__do, &get_value_or_future__do);
  use_read_only(NULL, "do_check_only", &get__do_check_only, &get_value_or_future__do_check_only);
  use_read_only(NULL, "do_dump_trees", &get__do_dump_trees, &get_value_or_future__do_dump_trees);
  use_read_write(NULL, "do_extract_documentation", &get__do_extract_documentation, &set__do_extract_documentation);
  use_read_only(NULL, "do_pretty_print", &get__do_pretty_print, &get_value_or_future__do_pretty_print);
  use_read_only(NULL, "do_print_simplified_source", &get__do_print_simplified_source, &get_value_or_future__do_print_simplified_source);
  use_read_only(NULL, "do_show_compiler_debug_infos", &get__do_show_compiler_debug_infos, &get_value_or_future__do_show_compiler_debug_infos);
  use_read_only(NULL, "do_show_debug_infos", &get__do_show_debug_infos, &get_value_or_future__do_show_debug_infos);
  use_read_write(NULL, "do_time_passes", &get__do_time_passes, &set__do_time_passes);
  use_read_only(NULL, "do_while", &get__do_while, &get_value_or_future__do_while);
  use_read_only(NULL, "dup", &get__dup, &get_value_or_future__dup);
  use_read_only(NULL, "empty_insert_order_set", &get__empty_insert_order_set, &get_value_or_future__empty_insert_order_set);
  use_read_only(NULL, "empty_key_order_set", &get__empty_key_order_set, &get_value_or_future__empty_key_order_set);
  use_read_only(NULL, "empty_key_order_table", &get__empty_key_order_table, &get_value_or_future__empty_key_order_table);
  use_read_only(NULL, "empty_list", &get__empty_list, &get_value_or_future__empty_list);
  use_read_only(NULL, "empty_set", &get__empty_set, &get_value_or_future__empty_set);
  use_read_only(NULL, "empty_table", &get__empty_table, &get_value_or_future__empty_table);
  use_read_only(NULL, "environment", &get__environment, &get_value_or_future__environment);
  use_read_only(NULL, "ewrite", &get__ewrite, &get_value_or_future__ewrite);
  use_read_only(NULL, "ewriteln", &get__ewriteln, &get_value_or_future__ewriteln);
  use_read_only(NULL, "exec", &get__exec, &get_value_or_future__exec);
  use_read_only(NULL, "extern", &get__extern, &get_value_or_future__extern);
  use_read_only(NULL, "extract_documentation", &get__extract_documentation, &get_value_or_future__extract_documentation);
  use_read_only(NULL, "false", &get__false, &get_value_or_future__false);
  use_read_only(NULL, "file_exists", &get__file_exists, &get_value_or_future__file_exists);
  use_read_only(NULL, "for_each", &get__for_each, &get_value_or_future__for_each);
  use_read_only(NULL, "for_each_line", &get__for_each_line, &get_value_or_future__for_each_line);
  use_read_only(NULL, "forever", &get__forever, &get_value_or_future__forever);
  use_read_only(NULL, "from", &get__from, &get_value_or_future__from);
  use_read_only(NULL, "from_utf8", &get__from_utf8, &get_value_or_future__from_utf8);
  use_read_only(NULL, "fullname", &get__fullname, &get_value_or_future__fullname);
  use_read_only(NULL, "fullname_of", &get__fullname_of, &get_value_or_future__fullname_of);
  use_read_only(NULL, "hardware_architecture", &get__hardware_architecture, &get_value_or_future__hardware_architecture);
  use_read_only(NULL, "has_prefix", &get__has_prefix, &get_value_or_future__has_prefix);
  use_read_only(NULL, "has_suffix", &get__has_suffix, &get_value_or_future__has_suffix);
  use_read_only(NULL, "if", &get__if, &get_value_or_future__if);
  use_read_only(NULL, "inc", &get__inc, &get_value_or_future__inc);
  use_read_only(NULL, "is_a_digit", &get__is_a_digit, &get_value_or_future__is_a_digit);
  use_read_only(NULL, "is_a_directory", &get__is_a_directory, &get_value_or_future__is_a_directory);
  use_read_only(NULL, "is_a_letter", &get__is_a_letter, &get_value_or_future__is_a_letter);
  use_read_only(NULL, "is_defined", &get__is_defined, &get_value_or_future__is_defined);
  use_read_only(NULL, "is_empty", &get__is_empty, &get_value_or_future__is_empty);
  use_read_only(NULL, "is_undefined", &get__is_undefined, &get_value_or_future__is_undefined);
  use_read_only(NULL, "join", &get__join, &get_value_or_future__join);
  use_read_only(NULL, "key_order_table", &get__key_order_table, &get_value_or_future__key_order_table);
  use_read_only(NULL, "length_of", &get__length_of, &get_value_or_future__length_of);
  use_read_only(NULL, "list", &get__list, &get_value_or_future__list);
  use_read_only(NULL, "load", &get__load, &get_value_or_future__load);
  use_read_only(NULL, "many", &get__many, &get_value_or_future__many);
  use_read_only(NULL, "matches", &get__matches, &get_value_or_future__matches);
  use_read_only(NULL, "modification_time_of", &get__modification_time_of, &get_value_or_future__modification_time_of);
  use_read_only(NULL, "module_name", &get__module_name, &get_value_or_future__module_name);
  use_read_only(NULL, "multi_dimensional_table", &get__multi_dimensional_table, &get_value_or_future__multi_dimensional_table);
  use_read_only(NULL, "not", &get__not, &get_value_or_future__not);
  use_read_only(NULL, "operating_system", &get__operating_system, &get_value_or_future__operating_system);
  use_read_only(NULL, "parameter_count_of", &get__parameter_count_of, &get_value_or_future__parameter_count_of);
  use_read_only(NULL, "program_name", &get__program_name, &get_value_or_future__program_name);
  use_read_only(NULL, "program_parameters", &get__program_parameters, &get_value_or_future__program_parameters);
  use_read_only(NULL, "push", &get__push, &get_value_or_future__push);
  use_read_only(NULL, "range", &get__range, &get_value_or_future__range);
  use_read_only(NULL, "replace_all", &get__replace_all, &get_value_or_future__replace_all);
  use_read_only(NULL, "runtime_major_version", &get__runtime_major_version, &get_value_or_future__runtime_major_version);
  use_read_only(NULL, "runtime_minor_version", &get__runtime_minor_version, &get_value_or_future__runtime_minor_version);
  use_read_only(NULL, "runtime_revision", &get__runtime_revision, &get_value_or_future__runtime_revision);
  use_read_only(NULL, "runtime_symbols", &get__runtime_symbols, &get_value_or_future__runtime_symbols);
  use_read_only(NULL, "save", &get__save, &get_value_or_future__save);
  use_read_only(NULL, "serialize", &get__serialize, &get_value_or_future__serialize);
  use_read_only(NULL, "sim2c", &get__sim2c, &get_value_or_future__sim2c);
  use_single_assign_dynamic("sim2c", "module_name", &get__sim2c__module_name, &define__sim2c__module_name);
  use_read_only(NULL, "some", &get__some, &get_value_or_future__some);
  use_read_only(NULL, "split", &get__split, &get_value_or_future__split);
  use_read_only(NULL, "stat", &get__stat, &get_value_or_future__stat);
  use_read_only("std", "MANDATORY_PARAMETER", &get__std__MANDATORY_PARAMETER, &get_value_or_future__std__MANDATORY_PARAMETER);
  use_read_only("std", "and", &get__std__and, &get_value_or_future__std__and);
  use_read_only("std", "call", &get__std__call, &get_value_or_future__std__call);
  use_read_only("std", "equal", &get__std__equal, &get_value_or_future__std__equal);
  use_read_only("std", "filename_of", &get__std__filename_of, &get_value_or_future__std__filename_of);
  use_read_only("std", "key_value_pair", &get__std__key_value_pair, &get_value_or_future__std__key_value_pair);
  use_read_only("std", "less", &get__std__less, &get_value_or_future__std__less);
  use_read_only("std", "minus", &get__std__minus, &get_value_or_future__std__minus);
  use_read_only("std", "negate", &get__std__negate, &get_value_or_future__std__negate);
  use_read_only("std", "not", &get__std__not, &get_value_or_future__std__not);
  use_read_only("std", "or", &get__std__or, &get_value_or_future__std__or);
  use_read_only("std", "over", &get__std__over, &get_value_or_future__std__over);
  use_read_only("std", "plus", &get__std__plus, &get_value_or_future__std__plus);
  use_read_only("std", "sequence", &get__std__sequence, &get_value_or_future__std__sequence);
  use_read_only("std", "string", &get__std__string, &get_value_or_future__std__string);
  use_read_only("std", "terminate", &get__std__terminate, &get_value_or_future__std__terminate);
  use_read_only("std", "true", &get__std__true, &get_value_or_future__std__true);
  use_read_only(NULL, "string", &get__string, &get_value_or_future__string);
  use_read_only(NULL, "table", &get__table, &get_value_or_future__table);
  use_read_only(NULL, "to_string", &get__to_string, &get_value_or_future__to_string);
  use_read_only(NULL, "to_utf8", &get__to_utf8, &get_value_or_future__to_utf8);
  use_read_only(NULL, "trim", &get__trim, &get_value_or_future__trim);
  use_read_only(NULL, "true", &get__true, &get_value_or_future__true);
  use_read_only(NULL, "truncate_from", &get__truncate_from, &get_value_or_future__truncate_from);
  use_read_only(NULL, "truncate_until", &get__truncate_until, &get_value_or_future__truncate_until);
  use_read_only("types", "table", &get__types__table, &get_value_or_future__types__table);
  use_read_only(NULL, "undefined", &get__undefined, &get_value_or_future__undefined);
  use_read_only(NULL, "unless", &get__unless, &get_value_or_future__unless);
  use_read_only(NULL, "until", &get__until, &get_value_or_future__until);
  use_read_write(NULL, "verbose", &get__verbose, &set__verbose);
  use_read_only(NULL, "version", &get__version, &get_value_or_future__version);
  use_read_only(NULL, "while", &get__while, &get_value_or_future__while);
  use_read_only(NULL, "without_prefix", &get__without_prefix, &get_value_or_future__without_prefix);
  use_read_only(NULL, "without_suffix", &get__without_suffix, &get_value_or_future__without_suffix);
  use_read_only(NULL, "write", &get__write, &get_value_or_future__write);
  use_read_only(NULL, "write_timing_info", &get__write_timing_info, &get_value_or_future__write_timing_info);
  use_read_only(NULL, "write_to", &get__write_to, &get_value_or_future__write_to);
  use_read_only(NULL, "writeln", &get__writeln, &get_value_or_future__writeln);
  resolve_attributes();

  // initialization phase 5

  phase_5__basic__exceptions();
  phase_5__basic__serialize();
  phase_5__basic__deserialize();
  phase_5__basic__branches();
  phase_5__basic__debug();
  phase_5__basic__environment();
  phase_5__basic__event();
  phase_5__basic__exec();
  phase_5__basic__functional();
  phase_5__basic__grammar();
  phase_5__basic__io();
  phase_5__basic__loops();
  phase_5__basic__math();
  phase_5__basic__options();
  phase_5__basic__parameters();
  phase_5__basic__platform();
  phase_5__basic__polymorphic_functions();
  phase_5__basic__primitives();
  phase_5__basic__runtime();
  phase_5__basic__types__boolean();
  phase_5__basic__types__character();
  phase_5__basic__types__continuation();
  phase_5__basic__types__date_and_time();
  phase_5__basic__types__function();
  phase_5__basic__types__insert_order_set();
  phase_5__basic__types__insert_order_table();
  phase_5__basic__types__list();
  phase_5__basic__types__multi_dimensional_set();
  phase_5__basic__types__multi_dimensional_table();
  phase_5__basic__types__number();
  phase_5__basic__types__object();
  phase_5__basic__types__key_order_table();
  phase_5__basic__types__key_value_pair();
  phase_5__basic__types__set();
  phase_5__basic__types__key_order_set();
  phase_5__basic__types__string_primitives();
  phase_5__basic__types__string();
  phase_5__basic__types__table();
  phase_5__basic__types__undefined();
  phase_5__basic__types__unique_item();
  phase_5__basic__types__unordered_set();
  phase_5__basic__types__unordered_table();
  phase_5__basic__types__value_range();
  phase_5__system__export__html();
  phase_5__character_names();
  phase_5__fragments();
  phase_5__tokenizer();
  phase_5__shared_variables();
  phase_5__nodes();
  phase_5__parser();
  phase_5__expander();
  phase_5__annotator();
  phase_5__simplifier();
  phase_5__macros();
  phase_5__c_code_generator();
  phase_5__pretty_printer();
  phase_5__sim2c();
  phase_5__extractor();
  phase_5__runtime_definitions();
  assign_value(&var._BUILD, number__0);
  assign_variable(&var.sim2c__show_compiler_debug_info, &func__47_1_sim2c__show_compiler_debug_info);
  maybe_initialize_future(get__mode(), get__undefined());
  maybe_initialize_future(get__on_top_level(), get__true());
  assign_variable(&var._resolve_filename, &func__66_1_resolve_filename);
  assign_variable(&var._add_module_infos, &func__67_1_add_module_infos);
  assign_variable(&var._lookup, &func__68_1_lookup);
  assign_variable(&var._CC, &func__69_1_CC);
  assign_variable(&var._compile_c, &func__70_1_compile_c);
  assign_variable(&var._compile_meta_module, &func__71_1_compile_meta_module);
  assign_variable(&var._build_dependencies, &func__72_1_build_dependencies);
  assign_variable(&var._compile_module, &func__73_1_compile_module);
  assign_variable(&var._compile_modules, &func__74_1_compile_modules);
  assign_variable(&var._show_file_list, &func__76_1_show_file_list);
  assign_variable(&var._library_paths_and_file_list, &func__77_1_library_paths_and_file_list);
  assign_variable(&var._create_imports, &func__78_1_create_imports);
  assign_variable(&var._compile_exe, &func__79_1_compile_exe);
  assign_variable(&var._dump_source_or_check, &func__80_1_dump_source_or_check);
  assign_variable(&var._print_c, &func__81_1_print_c);
  assign_variable(&var._list_dependencies, &func__82_1_list_dependencies);
  assign_variable(&var._build_codeblocks_project, &func__83_1_build_codeblocks_project);
  assign_variable(&var._build_library, &func__84_1_build_library);
  assign_variable(&var._maybe_compile_c_file, &func__85_1_maybe_compile_c_file);
  assign_variable(&var._format_number, &func__87_1_format_number);
  assign_variable(&var.sim2c__write_timing_info, &func__88_1_sim2c__write_timing_info);
  assign_variable(&var._build_executable, &func__89_1_build_executable);
  initialize_function_attributes();

  // initialization phase 6

  phase_6__basic__exceptions();
  phase_6__basic__serialize();
  phase_6__basic__deserialize();
  phase_6__basic__branches();
  phase_6__basic__debug();
  phase_6__basic__environment();
  phase_6__basic__event();
  phase_6__basic__exec();
  phase_6__basic__functional();
  phase_6__basic__grammar();
  phase_6__basic__io();
  phase_6__basic__loops();
  phase_6__basic__math();
  phase_6__basic__options();
  phase_6__basic__parameters();
  phase_6__basic__platform();
  phase_6__basic__polymorphic_functions();
  phase_6__basic__primitives();
  phase_6__basic__runtime();
  phase_6__basic__types__boolean();
  phase_6__basic__types__character();
  phase_6__basic__types__continuation();
  phase_6__basic__types__date_and_time();
  phase_6__basic__types__function();
  phase_6__basic__types__insert_order_set();
  phase_6__basic__types__insert_order_table();
  phase_6__basic__types__list();
  phase_6__basic__types__multi_dimensional_set();
  phase_6__basic__types__multi_dimensional_table();
  phase_6__basic__types__number();
  phase_6__basic__types__object();
  phase_6__basic__types__key_order_table();
  phase_6__basic__types__key_value_pair();
  phase_6__basic__types__set();
  phase_6__basic__types__key_order_set();
  phase_6__basic__types__string_primitives();
  phase_6__basic__types__string();
  phase_6__basic__types__table();
  phase_6__basic__types__undefined();
  phase_6__basic__types__unique_item();
  phase_6__basic__types__unordered_set();
  phase_6__basic__types__unordered_table();
  phase_6__basic__types__value_range();
  phase_6__system__export__html();
  phase_6__character_names();
  phase_6__fragments();
  phase_6__tokenizer();
  phase_6__shared_variables();
  phase_6__nodes();
  phase_6__parser();
  phase_6__expander();
  phase_6__annotator();
  phase_6__simplifier();
  phase_6__macros();
  phase_6__c_code_generator();
  phase_6__pretty_printer();
  phase_6__sim2c();
  phase_6__extractor();
  phase_6__runtime_definitions();
  register_collector(collect__simple);
  execute(main_entry);
}
