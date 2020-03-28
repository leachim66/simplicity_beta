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
  NODE *_gcc;
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
  NODE *_gcc_basic_options;
  NODE *_gcc_hardware_specific_options;
  NODE *_gcc_include_options;
  NODE *_gcc_options;
  NODE *_c_sources;
  NODE *_dependencies;
  NODE *_resolved_libraries;
  NODE *_resolve_filename;
  NODE *_add_module_infos;
  NODE *_lookup;
  NODE *_Gcc;
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
  "gcc",
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
  "gcc_basic_options",
  "gcc_hardware_specific_options",
  "gcc_include_options",
  "gcc_options",
  "c_sources",
  "dependencies",
  "resolved_libraries",
  "resolve_filename",
  "add_module_infos",
  "lookup",
  "Gcc",
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
static NODE *func__65_1_resolve_filename;
static void entry__65_1_resolve_filename(void);
static FRAME_INFO frame__65_1_resolve_filename = {3, {"filename", "libname", "libpath"}};
static void cont__65_2(void);
static NODE *func__65_3;
static void entry__65_3(void);
static FRAME_INFO frame__65_3 = {0, {}};
static NODE *func__65_4;
static void entry__65_4(void);
static FRAME_INFO frame__65_4 = {1, {"path"}};
static void cont__65_5(void);
static NODE *func__65_6;
static void entry__65_6(void);
static FRAME_INFO frame__65_6 = {1, {"path"}};
static void cont__65_7(void);
static NODE *func__65_8;
static void entry__65_8(void);
static FRAME_INFO frame__65_8 = {1, {"entry"}};
static void cont__65_9(void);
static NODE *func__65_10;
static void entry__65_10(void);
static FRAME_INFO frame__65_10 = {2, {"entry", "name"}};
static void cont__65_11(void);
static void cont__65_12(void);
static NODE *func__65_13;
static void entry__65_13(void);
static FRAME_INFO frame__65_13 = {2, {"name", "entry"}};
static void cont__65_14(void);
static void cont__65_15(void);
static void cont__65_16(void);
static void cont__65_17(void);
static void cont__65_18(void);
static void cont__65_19(void);
static NODE *func__65_20;
static void entry__65_20(void);
static FRAME_INFO frame__65_20 = {1, {"libname"}};
static NODE *string__65_21;
static NODE *string__65_22;
static void cont__65_23(void);
static void cont__65_24(void);
static void cont__65_25(void);
static void cont__65_26(void);
static NODE *func__66_1_add_module_infos;
static void entry__66_1_add_module_infos(void);
static FRAME_INFO frame__66_1_add_module_infos = {7, {"path", "mod_path", "return", "entries", "filenames", "directories", "modules"}};
static void cont__66_2(void);
static void cont__66_3(void);
static NODE *func__66_4;
static void entry__66_4(void);
static FRAME_INFO frame__66_4 = {6, {"entry", "directories", "filenames", "modules", "mod_path", "name"}};
static void cont__66_5(void);
static NODE *func__66_6;
static void entry__66_6(void);
static FRAME_INFO frame__66_6 = {3, {"entry", "name", "directories"}};
static void cont__66_7(void);
static NODE *func__66_8;
static void entry__66_8(void);
static FRAME_INFO frame__66_8 = {2, {"name", "directories"}};
static void cont__66_9(void);
static NODE *func__66_10;
static void entry__66_10(void);
static FRAME_INFO frame__66_10 = {2, {"directories", "name"}};
static void cont__66_11(void);
static NODE *func__66_12;
static void entry__66_12(void);
static FRAME_INFO frame__66_12 = {4, {"name", "filenames", "modules", "mod_path"}};
static NODE *string__66_13;
static void cont__66_14(void);
static NODE *func__66_15;
static void entry__66_15(void);
static FRAME_INFO frame__66_15 = {9, {"name", "filenames", "modules", "mod_path", "submodule_name", "meta_level", "stored_level", "basename", "mod_name"}};
static NODE *string__66_16;
static void cont__66_17(void);
static void cont__66_18(void);
static void cont__66_19(void);
static void cont__66_20(void);
static void cont__66_21(void);
static void cont__66_22(void);
static void cont__66_23(void);
static void cont__66_24(void);
static void cont__66_25(void);
static void cont__66_26(void);
static void cont__66_27(void);
static NODE *func__66_28;
static void entry__66_28(void);
static FRAME_INFO frame__66_28 = {2, {"stored_level", "meta_level"}};
static void cont__66_29(void);
static void cont__66_30(void);
static NODE *func__66_31;
static void entry__66_31(void);
static FRAME_INFO frame__66_31 = {2, {"submodule_name", "meta_level"}};
static void cont__66_32(void);
static void cont__66_33(void);
static void cont__66_34(void);
static void cont__66_35(void);
static void cont__66_36(void);
static void cont__66_37(void);
static void cont__66_38(void);
static NODE *func__66_39;
static void entry__66_39(void);
static FRAME_INFO frame__66_39 = {3, {"filename", "filenames", "mod_path"}};
static void cont__66_40(void);
static NODE *func__66_41;
static void entry__66_41(void);
static FRAME_INFO frame__66_41 = {3, {"filename", "filenames", "mod_path"}};
static NODE *string__66_42;
static void cont__66_43(void);
static NODE *func__66_44;
static void entry__66_44(void);
static FRAME_INFO frame__66_44 = {9, {"filenames", "filename", "mod_path", "maybe_push_common", "name", "mod_name", "platform", "parent", "files"}};
static NODE *func__66_45_maybe_push_common;
static void entry__66_45_maybe_push_common(void);
static FRAME_INFO frame__66_45_maybe_push_common = {5, {"plat", "name", "filenames", "files", "common_name"}};
static NODE *string__66_46;
static void cont__66_47(void);
static void cont__66_48(void);
static NODE *func__66_49;
static void entry__66_49(void);
static FRAME_INFO frame__66_49 = {2, {"files", "common_name"}};
static void cont__66_50(void);
static void cont__66_51(void);
static void cont__66_52(void);
static void cont__66_53(void);
static void cont__66_54(void);
static void cont__66_55(void);
static void cont__66_56(void);
static NODE *func__66_57;
static void entry__66_57(void);
static FRAME_INFO frame__66_57 = {1, {"platform"}};
static NODE *string__66_58;
static NODE *string__66_59;
static void cont__66_60(void);
static void cont__66_61(void);
static void cont__66_62(void);
static void cont__66_63(void);
static NODE *func__66_64;
static void entry__66_64(void);
static FRAME_INFO frame__66_64 = {2, {"parent", "maybe_push_common"}};
static void cont__66_65(void);
static void cont__66_66(void);
static NODE *func__66_67;
static void entry__66_67(void);
static FRAME_INFO frame__66_67 = {2, {"maybe_push_common", "parent"}};
static void cont__66_68(void);
static void cont__66_69(void);
static void cont__66_70(void);
static void cont__66_71(void);
static void cont__66_72(void);
static void cont__66_73(void);
static void cont__66_74(void);
static void cont__66_75(void);
static void cont__66_76(void);
static NODE *func__66_77;
static void entry__66_77(void);
static FRAME_INFO frame__66_77 = {3, {"return", "directories", "modules"}};
static void cont__66_78(void);
static NODE *func__67_1_lookup;
static void entry__67_1_lookup(void);
static FRAME_INFO frame__67_1_lookup = {3, {"mod_filename", "mod_name", "info"}};
static void cont__67_2(void);
static void cont__67_3(void);
static NODE *func__67_4;
static void entry__67_4(void);
static FRAME_INFO frame__67_4 = {1, {"info"}};
static NODE *func__67_5;
static void entry__67_5(void);
static FRAME_INFO frame__67_5 = {2, {"mod_filename", "mod_name"}};
static void cont__67_6(void);
static void cont__67_7(void);
static void cont__67_8(void);
static void cont__67_9(void);
static void cont__67_10(void);
static void cont__67_11(void);
static NODE *func__68_1_Gcc;
static void entry__68_1_Gcc(void);
static FRAME_INFO frame__68_1_Gcc = {1, {"args"}};
static NODE *func__68_2;
static void entry__68_2(void);
static FRAME_INFO frame__68_2 = {1, {"args"}};
static void cont__68_3(void);
static NODE *string__68_4;
static void cont__68_5(void);
static NODE *func__69_1_compile_c;
static void entry__69_1_compile_c(void);
static FRAME_INFO frame__69_1_compile_c = {2, {"c_filename", "o_filename"}};
static NODE *func__69_2;
static void entry__69_2(void);
static FRAME_INFO frame__69_2 = {0, {}};
static void cont__69_3(void);
static NODE *func__69_4;
static void entry__69_4(void);
static FRAME_INFO frame__69_4 = {5, {"c_filename", "o_filename", "out", "err", "success"}};
static NODE *string__69_5;
static NODE *string__69_6;
static void cont__69_7(void);
static NODE *func__69_8;
static void entry__69_8(void);
static FRAME_INFO frame__69_8 = {2, {"c_filename", "err"}};
static void cont__69_9(void);
static NODE *string__69_10;
static NODE *string__69_11;
static void cont__69_12(void);
static void cont__69_13(void);
static NODE *func__70_1_compile_meta_module;
static void entry__70_1_compile_meta_module(void);
static FRAME_INFO frame__70_1_compile_meta_module = {3, {"mod_filename", "mod_name", "meta_level"}};
static NODE *func__70_2;
static void entry__70_2(void);
static FRAME_INFO frame__70_2 = {11, {"mod_filename", "meta_level", "meta_path", "filename", "meta_filename", "meta_c_filename", "sim_filename", "meta_info", "sim_info", "meta_c_info", "force_rebuild"}};
static void cont__70_3(void);
static void cont__70_4(void);
static void cont__70_5(void);
static void cont__70_6(void);
static void cont__70_7(void);
static void cont__70_8(void);
static NODE *string__70_9;
static void cont__70_10(void);
static void cont__70_11(void);
static void cont__70_12(void);
static void cont__70_13(void);
static void cont__70_14(void);
static void cont__70_15(void);
static void cont__70_16(void);
static NODE *func__70_17;
static void entry__70_17(void);
static FRAME_INFO frame__70_17 = {3, {"sim_info", "meta_c_info", "meta_info"}};
static void cont__70_18(void);
static NODE *func__70_19;
static void entry__70_19(void);
static FRAME_INFO frame__70_19 = {3, {"meta_c_info", "meta_info", "sim_info"}};
static void cont__70_20(void);
static NODE *func__70_21;
static void entry__70_21(void);
static FRAME_INFO frame__70_21 = {3, {"meta_c_info", "meta_info", "sim_info"}};
static void cont__70_22(void);
static void cont__70_23(void);
static void cont__70_24(void);
static NODE *func__70_25;
static void entry__70_25(void);
static FRAME_INFO frame__70_25 = {2, {"sim_info", "meta_c_info"}};
static void cont__70_26(void);
static void cont__70_27(void);
static void cont__70_28(void);
static void cont__70_29(void);
static void cont__70_30(void);
static void cont__70_31(void);
static void cont__70_32(void);
static NODE *func__70_33;
static void entry__70_33(void);
static FRAME_INFO frame__70_33 = {6, {"sim_info", "meta_c_filename", "force_rebuild", "meta_path", "modification_time", "meta_c_buf"}};
static void cont__70_34(void);
static void cont__70_35(void);
static NODE *func__70_36;
static void entry__70_36(void);
static FRAME_INFO frame__70_36 = {5, {"break", "meta_c_buf", "modification_time", "force_rebuild", "meta_path"}};
static NODE *func__70_37;
static void entry__70_37(void);
static FRAME_INFO frame__70_37 = {8, {"line", "modification_time", "force_rebuild", "break", "meta_path", "check", "command", "argument"}};
static NODE *func__70_38_check;
static void entry__70_38_check(void);
static FRAME_INFO frame__70_38_check = {5, {"data_filename", "modification_time", "force_rebuild", "break", "data_info"}};
static void cont__70_39(void);
static void cont__70_40(void);
static NODE *func__70_41;
static void entry__70_41(void);
static FRAME_INFO frame__70_41 = {2, {"modification_time", "data_info"}};
static void cont__70_42(void);
static void cont__70_43(void);
static void cont__70_44(void);
static NODE *func__70_45;
static void entry__70_45(void);
static FRAME_INFO frame__70_45 = {2, {"force_rebuild", "break"}};
static NODE *string__70_46;
static void cont__70_47(void);
static void cont__70_48(void);
static void cont__70_49(void);
static void cont__70_50(void);
static void cont__70_51(void);
static void cont__70_52(void);
static NODE *string__70_53;
static void cont__70_54(void);
static NODE *func__70_55;
static void entry__70_55(void);
static FRAME_INFO frame__70_55 = {3, {"argument", "check", "meta_path"}};
static NODE *string__70_56;
static void cont__70_57(void);
static NODE *func__70_58;
static void entry__70_58(void);
static FRAME_INFO frame__70_58 = {3, {"check", "meta_path", "argument"}};
static void cont__70_59(void);
static void cont__70_60(void);
static void cont__70_61(void);
static NODE *func__70_62;
static void entry__70_62(void);
static FRAME_INFO frame__70_62 = {2, {"check", "argument"}};
static NODE *func__70_63;
static void entry__70_63(void);
static FRAME_INFO frame__70_63 = {3, {"path", "check", "argument"}};
static void cont__70_64(void);
static void cont__70_65(void);
static void cont__70_66(void);
static NODE *func__70_67;
static void entry__70_67(void);
static FRAME_INFO frame__70_67 = {9, {"return__1", "meta_filename", "meta_path", "filename", "sim_filename", "orig_path", "out", "err", "success"}};
static void cont__70_68(void);
static void cont__70_69(void);
static void cont__70_70(void);
static void cont__70_71(void);
static void cont__70_72(void);
static void cont__70_73(void);
static NODE *func__70_74;
static void entry__70_74(void);
static FRAME_INFO frame__70_74 = {1, {"err"}};
static void cont__70_75(void);
static void cont__70_76(void);
static void cont__70_77(void);
static void cont__70_78(void);
static void cont__70_79(void);
static void cont__70_80(void);
static void cont__70_81(void);
static NODE *func__71_1_build_dependencies;
static void entry__71_1_build_dependencies(void);
static FRAME_INFO frame__71_1_build_dependencies = {5, {"mod_filename", "mod_name", "c_buf", "do_compile_c", "return"}};
static NODE *func__71_2;
static void entry__71_2(void);
static FRAME_INFO frame__71_2 = {7, {"line", "return", "mod_filename", "mod_name", "do_compile_c", "command", "argument"}};
static void cont__71_3(void);
static void cont__71_4(void);
static void cont__71_5(void);
static void cont__71_6(void);
static void cont__71_7(void);
static void cont__71_8(void);
static NODE *func__71_9;
static void entry__71_9(void);
static FRAME_INFO frame__71_9 = {4, {"argument", "mod_filename", "mod_name", "do_compile_c"}};
static void cont__71_10(void);
static NODE *func__71_11;
static void entry__71_11(void);
static FRAME_INFO frame__71_11 = {3, {"argument", "mod_filename", "mod_name"}};
static void cont__71_12(void);
static NODE *func__71_13;
static void entry__71_13(void);
static FRAME_INFO frame__71_13 = {4, {"argument", "mod_filename", "mod_name", "req_name"}};
static void cont__71_14(void);
static void cont__71_15(void);
static void cont__71_16(void);
static void cont__71_17(void);
static void cont__71_18(void);
static void cont__71_19(void);
static void cont__71_20(void);
static void cont__71_21(void);
static NODE *func__71_22;
static void entry__71_22(void);
static FRAME_INFO frame__71_22 = {2, {"argument", "do_compile_c"}};
static NODE *func__71_23;
static void entry__71_23(void);
static FRAME_INFO frame__71_23 = {0, {}};
static NODE *func__71_24;
static void entry__71_24(void);
static FRAME_INFO frame__71_24 = {0, {}};
static void cont__71_25(void);
static void cont__71_26(void);
static NODE *func__71_27;
static void entry__71_27(void);
static FRAME_INFO frame__71_27 = {1, {"argument"}};
static void cont__71_28(void);
static NODE *func__71_29;
static void entry__71_29(void);
static FRAME_INFO frame__71_29 = {2, {"do_compile_c", "argument"}};
static NODE *func__71_30;
static void entry__71_30(void);
static FRAME_INFO frame__71_30 = {1, {"argument"}};
static void cont__71_31(void);
static NODE *string__71_32;
static void cont__71_33(void);
static void cont__71_34(void);
static NODE *func__71_35;
static void entry__71_35(void);
static FRAME_INFO frame__71_35 = {2, {"do_compile_c", "argument"}};
static NODE *func__71_36;
static void entry__71_36(void);
static FRAME_INFO frame__71_36 = {1, {"argument"}};
static void cont__71_37(void);
static void cont__71_38(void);
static NODE *string__71_39;
static NODE *string__71_40;
static void cont__71_41(void);
static NODE *func__72_1_compile_module;
static void entry__72_1_compile_module(void);
static FRAME_INFO frame__72_1_compile_module = {6, {"mod_filename", "mod_name", "return", "compile_submodule", "mod_info", "o_filename"}};
static NODE *func__72_2_compile_submodule;
static void entry__72_2_compile_submodule(void);
static FRAME_INFO frame__72_2_compile_submodule = {11, {"submodule_names", "do_compile_c", "suffix", "mod_filename", "mod_name", "o_filename", "modification_time", "sim_filenames", "c_filename", "c_info", "c_buf"}};
static NODE *func__72_3;
static void entry__72_3(void);
static FRAME_INFO frame__72_3 = {8, {"submodule_name", "mod_filename", "sim_filenames", "modification_time", "meta_level", "submodule_filename", "sim_filename", "sim_info"}};
static void cont__72_4(void);
static void cont__72_5(void);
static void cont__72_6(void);
static void cont__72_7(void);
static void cont__72_8(void);
static NODE *func__72_9;
static void entry__72_9(void);
static FRAME_INFO frame__72_9 = {0, {}};
static void cont__72_10(void);
static void cont__72_11(void);
static NODE *func__72_12;
static void entry__72_12(void);
static FRAME_INFO frame__72_12 = {3, {"submodule_filename", "submodule_name", "meta_level"}};
static void cont__72_13(void);
static void cont__72_14(void);
static void cont__72_15(void);
static void cont__72_16(void);
static void cont__72_17(void);
static NODE *func__72_18;
static void entry__72_18(void);
static FRAME_INFO frame__72_18 = {2, {"modification_time", "sim_info"}};
static void cont__72_19(void);
static void cont__72_20(void);
static void cont__72_21(void);
static NODE *func__72_22;
static void entry__72_22(void);
static FRAME_INFO frame__72_22 = {2, {"modification_time", "sim_info"}};
static void cont__72_23(void);
static void cont__72_24(void);
static void cont__72_25(void);
static void cont__72_26(void);
static NODE *func__72_27;
static void entry__72_27(void);
static FRAME_INFO frame__72_27 = {1, {"c_filename"}};
static void cont__72_28(void);
static void cont__72_29(void);
static NODE *func__72_30;
static void entry__72_30(void);
static FRAME_INFO frame__72_30 = {2, {"c_info", "modification_time"}};
static void cont__72_31(void);
static NODE *func__72_32;
static void entry__72_32(void);
static FRAME_INFO frame__72_32 = {2, {"c_info", "modification_time"}};
static void cont__72_33(void);
static void cont__72_34(void);
static void cont__72_35(void);
static void cont__72_36(void);
static NODE *func__72_37;
static void entry__72_37(void);
static FRAME_INFO frame__72_37 = {9, {"return__1", "mod_name", "suffix", "sim_filenames", "c_buf", "c_filename", "do_compile_c", "o_filename", "c_source"}};
static NODE *string__72_38;
static void cont__72_39(void);
static void cont__72_40(void);
static void cont__72_41(void);
static NODE *func__72_42;
static void entry__72_42(void);
static FRAME_INFO frame__72_42 = {1, {"suffix"}};
static NODE *string__72_43;
static void cont__72_44(void);
static NODE *func__72_45;
static void entry__72_45(void);
static FRAME_INFO frame__72_45 = {1, {"sim_filenames"}};
static void cont__72_46(void);
static NODE *func__72_47;
static void entry__72_47(void);
static FRAME_INFO frame__72_47 = {1, {"c_source"}};
static void cont__72_48(void);
static void cont__72_49(void);
static void cont__72_50(void);
static NODE *func__72_51;
static void entry__72_51(void);
static FRAME_INFO frame__72_51 = {2, {"c_filename", "o_filename"}};
static void cont__72_52(void);
static NODE *func__72_53;
static void entry__72_53(void);
static FRAME_INFO frame__72_53 = {6, {"c_buf", "c_filename", "o_filename", "c_info", "do_compile_c", "o_info"}};
static void cont__72_54(void);
static void cont__72_55(void);
static void cont__72_56(void);
static NODE *func__72_57;
static void entry__72_57(void);
static FRAME_INFO frame__72_57 = {2, {"o_info", "c_info"}};
static void cont__72_58(void);
static void cont__72_59(void);
static void cont__72_60(void);
static void cont__72_61(void);
static NODE *func__72_62;
static void entry__72_62(void);
static FRAME_INFO frame__72_62 = {3, {"do_compile_c", "c_filename", "o_filename"}};
static NODE *func__72_63;
static void entry__72_63(void);
static FRAME_INFO frame__72_63 = {2, {"c_filename", "o_filename"}};
static NODE *func__72_64;
static void entry__72_64(void);
static FRAME_INFO frame__72_64 = {1, {"o_info"}};
static void cont__72_65(void);
static NODE *func__72_66;
static void entry__72_66(void);
static FRAME_INFO frame__72_66 = {1, {"o_info"}};
static void cont__72_67(void);
static void cont__72_68(void);
static void cont__72_69(void);
static NODE *func__72_70;
static void entry__72_70(void);
static FRAME_INFO frame__72_70 = {1, {"o_info"}};
static void cont__72_71(void);
static void cont__72_72(void);
static void cont__72_73(void);
static void cont__72_74(void);
static NODE *func__72_75;
static void entry__72_75(void);
static FRAME_INFO frame__72_75 = {1, {"mod_name"}};
static NODE *string__72_76;
static NODE *string__72_77;
static void cont__72_78(void);
static void cont__72_79(void);
static NODE *string__72_80;
static void cont__72_81(void);
static void cont__72_82(void);
static void cont__72_83(void);
static void cont__72_84(void);
static void cont__72_85(void);
static NODE *func__72_86;
static void entry__72_86(void);
static FRAME_INFO frame__72_86 = {3, {"compile_submodule", "mod_name", "mod_filename"}};
static void cont__72_87(void);
static void cont__72_88(void);
static void cont__72_89(void);
static void cont__72_90(void);
static NODE *func__72_91;
static void entry__72_91(void);
static FRAME_INFO frame__72_91 = {1, {"mod_filename"}};
static void cont__72_92(void);
static void cont__72_93(void);
static NODE *func__72_94;
static void entry__72_94(void);
static FRAME_INFO frame__72_94 = {3, {"mod_info", "compile_submodule", "mod_filename"}};
static NODE *func__72_95;
static void entry__72_95(void);
static FRAME_INFO frame__72_95 = {4, {"mod_info", "compile_submodule", "best_platform", "best_priority"}};
static NODE *func__72_96;
static void entry__72_96(void);
static FRAME_INFO frame__72_96 = {5, {"platform", "filenames", "best_priority", "best_platform", "priority"}};
static void cont__72_97(void);
static void cont__72_98(void);
static NODE *func__72_99;
static void entry__72_99(void);
static FRAME_INFO frame__72_99 = {2, {"priority", "best_priority"}};
static void cont__72_100(void);
static void cont__72_101(void);
static NODE *func__72_102;
static void entry__72_102(void);
static FRAME_INFO frame__72_102 = {4, {"best_platform", "platform", "best_priority", "priority"}};
static void cont__72_103(void);
static NODE *func__72_104;
static void entry__72_104(void);
static FRAME_INFO frame__72_104 = {4, {"platform", "filenames", "compile_submodule", "best_platform"}};
static void cont__72_105(void);
static void cont__72_106(void);
static void cont__72_107(void);
static NODE *func__72_108;
static void entry__72_108(void);
static FRAME_INFO frame__72_108 = {3, {"mod_info", "mod_filename", "used_by"}};
static NODE *func__72_109;
static void entry__72_109(void);
static FRAME_INFO frame__72_109 = {6, {"supported_platform", "parent_platform", "mod_info", "used_by", "best_platform", "best_priority"}};
static NODE *func__72_110;
static void entry__72_110(void);
static FRAME_INFO frame__72_110 = {6, {"platform", "filenames", "supported_platform", "best_priority", "best_platform", "priority"}};
static void cont__72_111(void);
static void cont__72_112(void);
static NODE *func__72_113;
static void entry__72_113(void);
static FRAME_INFO frame__72_113 = {2, {"priority", "best_priority"}};
static void cont__72_114(void);
static void cont__72_115(void);
static NODE *func__72_116;
static void entry__72_116(void);
static FRAME_INFO frame__72_116 = {4, {"best_platform", "platform", "best_priority", "priority"}};
static void cont__72_117(void);
static void cont__72_118(void);
static NODE *func__72_119;
static void entry__72_119(void);
static FRAME_INFO frame__72_119 = {4, {"used_by", "best_platform", "supported_platform", "ub"}};
static void cont__72_120(void);
static void cont__72_121(void);
static void cont__72_122(void);
static void cont__72_123(void);
static void cont__72_124(void);
static NODE *func__72_125;
static void entry__72_125(void);
static FRAME_INFO frame__72_125 = {6, {"platform", "filenames", "mod_filename", "used_by", "dependency", "platforms"}};
static void cont__72_126(void);
static void cont__72_127(void);
static void cont__72_128(void);
static NODE *func__72_129;
static void entry__72_129(void);
static FRAME_INFO frame__72_129 = {2, {"platforms", "dependency"}};
static NODE *func__72_130;
static void entry__72_130(void);
static FRAME_INFO frame__72_130 = {2, {"plat", "dependency"}};
static NODE *string__72_131;
static void cont__72_132(void);
static void cont__72_133(void);
static void cont__72_134(void);
static void cont__72_135(void);
static NODE *func__73_1_compile_modules;
static void entry__73_1_compile_modules(void);
static FRAME_INFO frame__73_1_compile_modules = {4, {"path", "mod_path", "directories", "modules"}};
static void cont__73_2(void);
static void cont__73_3(void);
static NODE *func__73_4;
static void entry__73_4(void);
static FRAME_INFO frame__73_4 = {3, {"name", "path", "mod_path"}};
static void cont__73_5(void);
static void cont__73_6(void);
static void cont__73_7(void);
static NODE *func__73_8;
static void entry__73_8(void);
static FRAME_INFO frame__73_8 = {3, {"name", "path", "mod_path"}};
static void cont__73_9(void);
static void cont__73_10(void);
static NODE *func__75_1_show_file_list;
static void entry__75_1_show_file_list(void);
static FRAME_INFO frame__75_1_show_file_list = {0, {}};
static NODE *func__75_2;
static void entry__75_2(void);
static FRAME_INFO frame__75_2 = {1, {"path"}};
static NODE *string__75_3;
static void cont__75_4(void);
static void cont__75_5(void);
static NODE *func__75_6;
static void entry__75_6(void);
static FRAME_INFO frame__75_6 = {1, {"path"}};
static NODE *string__75_7;
static void cont__75_8(void);
static void cont__75_9(void);
static void cont__75_10(void);
static NODE *string__75_11;
static void cont__75_12(void);
static void cont__75_13(void);
static NODE *string__75_14;
static NODE *func__76_1_library_paths_and_file_list;
static void entry__76_1_library_paths_and_file_list(void);
static FRAME_INFO frame__76_1_library_paths_and_file_list = {4, {"library_paths", "object_files", "library_files", "paths"}};
static void cont__76_2(void);
static void cont__76_3(void);
static void cont__76_4(void);
static NODE *func__76_5;
static void entry__76_5(void);
static FRAME_INFO frame__76_5 = {2, {"paths", "library_paths"}};
static void cont__76_6(void);
static NODE *func__76_7;
static void entry__76_7(void);
static FRAME_INFO frame__76_7 = {2, {"path", "library_paths"}};
static NODE *string__76_8;
static void cont__76_9(void);
static void cont__76_10(void);
static void cont__76_11(void);
static NODE *func__76_12;
static void entry__76_12(void);
static FRAME_INFO frame__76_12 = {1, {"library_paths"}};
static void cont__76_13(void);
static NODE *string__76_14;
static void cont__76_15(void);
static NODE *func__76_16;
static void entry__76_16(void);
static FRAME_INFO frame__76_16 = {2, {"object", "object_files"}};
static void cont__76_17(void);
static void cont__76_18(void);
static NODE *func__76_19;
static void entry__76_19(void);
static FRAME_INFO frame__76_19 = {2, {"library", "library_files"}};
static void cont__76_20(void);
static NODE *func__76_21;
static void entry__76_21(void);
static FRAME_INFO frame__76_21 = {1, {"library"}};
static void cont__76_22(void);
static NODE *string__76_23;
static void cont__76_24(void);
static NODE *func__76_25;
static void entry__76_25(void);
static FRAME_INFO frame__76_25 = {1, {"library"}};
static NODE *string__76_26;
static NODE *string__76_27;
static void cont__76_28(void);
static NODE *func__76_29;
static void entry__76_29(void);
static FRAME_INFO frame__76_29 = {1, {"library"}};
static NODE *string__76_30;
static void cont__76_31(void);
static void cont__76_32(void);
static NODE *func__76_33;
static void entry__76_33(void);
static FRAME_INFO frame__76_33 = {1, {"library"}};
static void cont__76_34(void);
static NODE *func__76_35;
static void entry__76_35(void);
static FRAME_INFO frame__76_35 = {1, {"library"}};
static void cont__76_36(void);
static void cont__76_37(void);
static void cont__76_38(void);
static NODE *func__76_39;
static void entry__76_39(void);
static FRAME_INFO frame__76_39 = {1, {"library"}};
static void cont__76_40(void);
static void cont__76_41(void);
static void cont__76_42(void);
static void cont__76_43(void);
static void cont__76_44(void);
static void cont__76_45(void);
static NODE *func__77_1_create_imports;
static void entry__77_1_create_imports(void);
static FRAME_INFO frame__77_1_create_imports = {5, {"source", "already_checked", "collect_declarations", "imports", "first_part"}};
static NODE *func__77_2_collect_declarations;
static void entry__77_2_collect_declarations(void);
static FRAME_INFO frame__77_2_collect_declarations = {4, {"buf", "already_checked", "collect_declarations", "s"}};
static NODE *func__77_3;
static void entry__77_3(void);
static FRAME_INFO frame__77_3 = {6, {"idx", "chr", "s", "buf", "already_checked", "collect_declarations"}};
static void cont__77_4(void);
static NODE *func__77_5;
static void entry__77_5(void);
static FRAME_INFO frame__77_5 = {6, {"chr", "buf", "s", "idx", "already_checked", "collect_declarations"}};
static void cont__77_6(void);
static NODE *func__77_7;
static void entry__77_7(void);
static FRAME_INFO frame__77_7 = {1, {"chr"}};
static void cont__77_8(void);
static NODE *func__77_9;
static void entry__77_9(void);
static FRAME_INFO frame__77_9 = {1, {"chr"}};
static void cont__77_10(void);
static void cont__77_11(void);
static void cont__77_12(void);
static NODE *func__77_13;
static void entry__77_13(void);
static FRAME_INFO frame__77_13 = {6, {"buf", "s", "idx", "already_checked", "collect_declarations", "symbol"}};
static void cont__77_14(void);
static void cont__77_15(void);
static void cont__77_16(void);
static NODE *func__77_17;
static void entry__77_17(void);
static FRAME_INFO frame__77_17 = {4, {"already_checked", "symbol", "collect_declarations", "declaration"}};
static void cont__77_18(void);
static void cont__77_19(void);
static void cont__77_20(void);
static NODE *func__77_21;
static void entry__77_21(void);
static FRAME_INFO frame__77_21 = {3, {"declaration", "collect_declarations", "do_import"}};
static void cont__77_22(void);
static void cont__77_23(void);
static void cont__77_24(void);
static NODE *func__77_25;
static void entry__77_25(void);
static FRAME_INFO frame__77_25 = {1, {"declaration"}};
static NODE *string__77_26;
static void cont__77_27(void);
static void cont__77_28(void);
static NODE *func__77_29;
static void entry__77_29(void);
static FRAME_INFO frame__77_29 = {1, {"declaration"}};
static NODE *string__77_30;
static void cont__77_31(void);
static void cont__77_32(void);
static void cont__77_33(void);
static void cont__77_34(void);
static NODE *func__77_35;
static void entry__77_35(void);
static FRAME_INFO frame__77_35 = {2, {"declaration", "collect_declarations"}};
static void cont__77_36(void);
static void cont__77_37(void);
static NODE *func__77_38;
static void entry__77_38(void);
static FRAME_INFO frame__77_38 = {1, {"declaration"}};
static void cont__77_39(void);
static void cont__77_40(void);
static NODE *func__77_41;
static void entry__77_41(void);
static FRAME_INFO frame__77_41 = {2, {"collect_declarations", "declaration"}};
static void cont__77_42(void);
static NODE *func__77_43;
static void entry__77_43(void);
static FRAME_INFO frame__77_43 = {2, {"declaration", "collect_declarations"}};
static NODE *string__77_44;
static void cont__77_45(void);
static NODE *func__77_46;
static void entry__77_46(void);
static FRAME_INFO frame__77_46 = {2, {"declaration", "collect_declarations"}};
static void cont__77_47(void);
static void cont__77_48(void);
static NODE *func__77_49;
static void entry__77_49(void);
static FRAME_INFO frame__77_49 = {2, {"line", "collect_declarations"}};
static void cont__77_50(void);
static void cont__77_51(void);
static NODE *func__77_52;
static void entry__77_52(void);
static FRAME_INFO frame__77_52 = {2, {"collect_declarations", "declaration"}};
static void cont__77_53(void);
static NODE *func__77_54;
static void entry__77_54(void);
static FRAME_INFO frame__77_54 = {0, {}};
static NODE *string__77_55;
static void cont__77_56(void);
static NODE *func__77_57;
static void entry__77_57(void);
static FRAME_INFO frame__77_57 = {3, {"chr", "s", "idx"}};
static void cont__77_58(void);
static NODE *func__77_59;
static void entry__77_59(void);
static FRAME_INFO frame__77_59 = {1, {"chr"}};
static void cont__77_60(void);
static void cont__77_61(void);
static NODE *func__77_62;
static void entry__77_62(void);
static FRAME_INFO frame__77_62 = {2, {"s", "idx"}};
static NODE *func__77_63;
static void entry__77_63(void);
static FRAME_INFO frame__77_63 = {2, {"collect_declarations", "source"}};
static void cont__77_64(void);
static NODE *string__77_65;
static void cont__77_66(void);
static void cont__77_67(void);
static void cont__77_68(void);
static void cont__77_69(void);
static void cont__77_70(void);
static void cont__77_71(void);
static void cont__77_72(void);
static void cont__77_73(void);
static NODE *func__77_74;
static void entry__77_74(void);
static FRAME_INFO frame__77_74 = {0, {}};
static NODE *string__77_75;
static NODE *func__78_1_compile_exe;
static void entry__78_1_compile_exe(void);
static FRAME_INFO frame__78_1_compile_exe = {4, {"body", "return__1", "mod_filename", "mod_name"}};
static void cont__78_2(void);
static NODE *func__78_3;
static void entry__78_3(void);
static FRAME_INFO frame__78_3 = {0, {}};
static NODE *string__78_4;
static void cont__78_5(void);
static void cont__78_6(void);
static NODE *func__78_7;
static void entry__78_7(void);
static FRAME_INFO frame__78_7 = {0, {}};
static NODE *string__78_8;
static void cont__78_9(void);
static void cont__78_10(void);
static void cont__78_11(void);
static void cont__78_12(void);
static void cont__78_13(void);
static NODE *func__79_1_dump_source_or_check;
static void entry__79_1_dump_source_or_check(void);
static FRAME_INFO frame__79_1_dump_source_or_check = {0, {}};
static NODE *func__79_2;
static void entry__79_2(void);
static FRAME_INFO frame__79_2 = {3, {"mod_filename", "mod_name", "return__1"}};
static void cont__79_3(void);
static void cont__79_4(void);
static NODE *func__80_1_print_c;
static void entry__80_1_print_c(void);
static FRAME_INFO frame__80_1_print_c = {0, {}};
static NODE *func__80_2;
static void entry__80_2(void);
static FRAME_INFO frame__80_2 = {4, {"mod_filename", "mod_name", "c_source", "c_buf"}};
static void cont__80_3(void);
static NODE *func__80_4;
static void entry__80_4(void);
static FRAME_INFO frame__80_4 = {1, {"mod_name"}};
static void cont__80_5(void);
static void cont__80_6(void);
static void cont__80_7(void);
static NODE *func__80_8;
static void entry__80_8(void);
static FRAME_INFO frame__80_8 = {2, {"return__1", "mod_name"}};
static void cont__80_9(void);
static void cont__80_10(void);
static void cont__80_11(void);
static void cont__80_12(void);
static void cont__80_13(void);
static void cont__80_14(void);
static NODE *func__80_15;
static void entry__80_15(void);
static FRAME_INFO frame__80_15 = {1, {"c_source"}};
static void cont__80_16(void);
static void cont__80_17(void);
static NODE *func__80_18;
static void entry__80_18(void);
static FRAME_INFO frame__80_18 = {0, {}};
static NODE *string__80_19;
static NODE *func__81_1_list_dependencies;
static void entry__81_1_list_dependencies(void);
static FRAME_INFO frame__81_1_list_dependencies = {1, {"prefix_path"}};
static void cont__81_2(void);
static NODE *func__81_3;
static void entry__81_3(void);
static FRAME_INFO frame__81_3 = {4, {"supported_platform", "parent_platform", "platform", "priority"}};
static NODE *func__81_4;
static void entry__81_4(void);
static FRAME_INFO frame__81_4 = {4, {"break", "platform", "priority", "supported_platform"}};
static NODE *func__81_5;
static void entry__81_5(void);
static FRAME_INFO frame__81_5 = {5, {"platform", "break", "priority", "supported_platform", "plat"}};
static void cont__81_6(void);
static void cont__81_7(void);
static void cont__81_8(void);
static void cont__81_9(void);
static void cont__81_10(void);
static void cont__81_11(void);
static void cont__81_12(void);
static void cont__81_13(void);
static void cont__81_14(void);
static void cont__81_15(void);
static NODE *func__81_16;
static void entry__81_16(void);
static FRAME_INFO frame__81_16 = {1, {"return__1"}};
static NODE *func__81_17;
static void entry__81_17(void);
static FRAME_INFO frame__81_17 = {0, {}};
static NODE *string__81_18;
static void cont__81_19(void);
static void cont__81_20(void);
static void cont__81_21(void);
static void cont__81_22(void);
static NODE *func__81_23;
static void entry__81_23(void);
static FRAME_INFO frame__81_23 = {0, {}};
static NODE *func__81_24;
static void entry__81_24(void);
static FRAME_INFO frame__81_24 = {2, {"mod_filename", "mod_name"}};
static NODE *func__81_25;
static void entry__81_25(void);
static FRAME_INFO frame__81_25 = {1, {"mod_filename"}};
static void cont__81_26(void);
static void cont__81_27(void);
static NODE *string__81_28;
static void cont__81_29(void);
static NODE *string__81_30;
static void cont__81_31(void);
static NODE *string__81_32;
static void cont__81_33(void);
static void cont__81_34(void);
static NODE *func__81_35;
static void entry__81_35(void);
static FRAME_INFO frame__81_35 = {2, {"filename", "prefix_path"}};
static void cont__81_36(void);
static void cont__81_37(void);
static NODE *func__82_1_build_codeblocks_project;
static void entry__82_1_build_codeblocks_project(void);
static FRAME_INFO frame__82_1_build_codeblocks_project = {0, {}};
static NODE *func__82_2;
static void entry__82_2(void);
static FRAME_INFO frame__82_2 = {10, {"mod_filename", "mod_name", "codeblocks_path", "info", "basename", "prefix_path", "depth", "path_prefix", "cbp_filename", "buf"}};
static NODE *string__82_3;
static void cont__82_4(void);
static void cont__82_5(void);
static void cont__82_6(void);
static NODE *func__82_7;
static void entry__82_7(void);
static FRAME_INFO frame__82_7 = {1, {"codeblocks_path"}};
static NODE *string__82_8;
static NODE *string__82_9;
static void cont__82_10(void);
static void cont__82_11(void);
static NODE *func__82_12;
static void entry__82_12(void);
static FRAME_INFO frame__82_12 = {1, {"codeblocks_path"}};
static NODE *string__82_13;
static void cont__82_14(void);
static void cont__82_15(void);
static void cont__82_16(void);
static void cont__82_17(void);
static void cont__82_18(void);
static void cont__82_19(void);
static void cont__82_20(void);
static void cont__82_21(void);
static void cont__82_22(void);
static NODE *string__82_23;
static void cont__82_24(void);
static NODE *string__82_25;
static NODE *string__82_26;
static void cont__82_27(void);
static void cont__82_28(void);
static NODE *string__82_29;
static NODE *string__82_30;
static NODE *string__82_31;
static void cont__82_32(void);
static void cont__82_33(void);
static NODE *func__82_34;
static void entry__82_34(void);
static FRAME_INFO frame__82_34 = {2, {"filename", "buf"}};
static NODE *string__82_35;
static NODE *string__82_36;
static void cont__82_37(void);
static void cont__82_38(void);
static void cont__82_39(void);
static NODE *string__82_40;
static NODE *string__82_41;
static NODE *string__82_42;
static NODE *string__82_43;
static NODE *string__82_44;
static NODE *string__82_45;
static void cont__82_46(void);
static void cont__82_47(void);
static NODE *func__82_48;
static void entry__82_48(void);
static FRAME_INFO frame__82_48 = {4, {"filename", "prefix_path", "buf", "path_prefix"}};
static void cont__82_49(void);
static void cont__82_50(void);
static NODE *string__82_51;
static NODE *string__82_52;
static void cont__82_53(void);
static void cont__82_54(void);
static void cont__82_55(void);
static NODE *string__82_56;
static void cont__82_57(void);
static NODE *func__83_1_build_library;
static void entry__83_1_build_library(void);
static FRAME_INFO frame__83_1_build_library = {1, {"return__1"}};
static NODE *string__83_2;
static void cont__83_3(void);
static NODE *func__83_4;
static void entry__83_4(void);
static FRAME_INFO frame__83_4 = {0, {}};
static NODE *string__83_5;
static void cont__83_6(void);
static NODE *func__83_7;
static void entry__83_7(void);
static FRAME_INFO frame__83_7 = {0, {}};
static NODE *func__83_8;
static void entry__83_8(void);
static FRAME_INFO frame__83_8 = {5, {"version", "so_version", "version_filename", "base_filename", "lib_filename"}};
static NODE *string__83_9;
static void cont__83_10(void);
static void cont__83_11(void);
static NODE *func__83_12;
static void entry__83_12(void);
static FRAME_INFO frame__83_12 = {3, {"version", "version_filename", "so_version"}};
static void cont__83_13(void);
static void cont__83_14(void);
static void cont__83_15(void);
static void cont__83_16(void);
static void cont__83_17(void);
static void cont__83_18(void);
static void cont__83_19(void);
static void cont__83_20(void);
static NODE *func__83_21;
static void entry__83_21(void);
static FRAME_INFO frame__83_21 = {2, {"base_filename", "version"}};
static void cont__83_22(void);
static NODE *string__83_23;
static void cont__83_24(void);
static NODE *func__83_25;
static void entry__83_25(void);
static FRAME_INFO frame__83_25 = {2, {"base_filename", "version"}};
static NODE *string__83_26;
static void cont__83_27(void);
static void cont__83_28(void);
static NODE *func__83_29;
static void entry__83_29(void);
static FRAME_INFO frame__83_29 = {2, {"base_filename", "version"}};
static NODE *string__83_30;
static void cont__83_31(void);
static void cont__83_32(void);
static NODE *func__83_33;
static void entry__83_33(void);
static FRAME_INFO frame__83_33 = {1, {"base_filename"}};
static NODE *string__83_34;
static void cont__83_35(void);
static NODE *string__83_36;
static NODE *string__83_37;
static void cont__83_38(void);
static NODE *func__83_39;
static void entry__83_39(void);
static FRAME_INFO frame__83_39 = {1, {"lib_filename"}};
static NODE *string__83_40;
static void cont__83_41(void);
static void cont__83_42(void);
static void cont__83_43(void);
static void cont__83_44(void);
static NODE *func__83_45;
static void entry__83_45(void);
static FRAME_INFO frame__83_45 = {2, {"lib_filename", "info"}};
static void cont__83_46(void);
static void cont__83_47(void);
static NODE *func__83_48;
static void entry__83_48(void);
static FRAME_INFO frame__83_48 = {1, {"info"}};
static void cont__83_49(void);
static void cont__83_50(void);
static void cont__83_51(void);
static NODE *func__83_52;
static void entry__83_52(void);
static FRAME_INFO frame__83_52 = {0, {}};
static void cont__83_53(void);
static NODE *func__83_54;
static void entry__83_54(void);
static FRAME_INFO frame__83_54 = {3, {"base_filename", "so_version", "lib_filename"}};
static NODE *func__83_55;
static void entry__83_55(void);
static FRAME_INFO frame__83_55 = {0, {}};
static NODE *string__83_56;
static void cont__83_57(void);
static void cont__83_58(void);
static NODE *func__83_59;
static void entry__83_59(void);
static FRAME_INFO frame__83_59 = {6, {"base_filename", "so_version", "lib_filename", "out", "err", "success"}};
static NODE *string__83_60;
static void cont__83_61(void);
static void cont__83_62(void);
static NODE *string__83_63;
static void cont__83_64(void);
static NODE *func__83_65;
static void entry__83_65(void);
static FRAME_INFO frame__83_65 = {1, {"err"}};
static void cont__83_66(void);
static NODE *func__83_67;
static void entry__83_67(void);
static FRAME_INFO frame__83_67 = {4, {"lib_filename", "out", "err", "success"}};
static void cont__83_68(void);
static NODE *string__83_69;
static void cont__83_70(void);
static void cont__83_71(void);
static NODE *func__83_72;
static void entry__83_72(void);
static FRAME_INFO frame__83_72 = {1, {"err"}};
static void cont__83_73(void);
static NODE *func__83_74;
static void entry__83_74(void);
static FRAME_INFO frame__83_74 = {6, {"base_filename", "so_version", "lib_filename", "out", "err", "success"}};
static NODE *string__83_75;
static void cont__83_76(void);
static void cont__83_77(void);
static void cont__83_78(void);
static NODE *string__83_79;
static void cont__83_80(void);
static NODE *func__83_81;
static void entry__83_81(void);
static FRAME_INFO frame__83_81 = {1, {"err"}};
static void cont__83_82(void);
static NODE *func__83_83;
static void entry__83_83(void);
static FRAME_INFO frame__83_83 = {4, {"lib_filename", "out", "err", "success"}};
static void cont__83_84(void);
static void cont__83_85(void);
static NODE *func__83_86;
static void entry__83_86(void);
static FRAME_INFO frame__83_86 = {1, {"err"}};
static void cont__83_87(void);
static void cont__83_88(void);
static NODE *func__84_1_maybe_compile_c_file;
static void entry__84_1_maybe_compile_c_file(void);
static FRAME_INFO frame__84_1_maybe_compile_c_file = {5, {"filename", "c_filename", "o_filename", "c_info", "o_info"}};
static void cont__84_2(void);
static void cont__84_3(void);
static void cont__84_4(void);
static void cont__84_5(void);
static NODE *func__84_6;
static void entry__84_6(void);
static FRAME_INFO frame__84_6 = {1, {"c_filename"}};
static NODE *string__84_7;
static NODE *string__84_8;
static void cont__84_9(void);
static void cont__84_10(void);
static void cont__84_11(void);
static void cont__84_12(void);
static NODE *func__84_13;
static void entry__84_13(void);
static FRAME_INFO frame__84_13 = {2, {"o_info", "c_info"}};
static void cont__84_14(void);
static void cont__84_15(void);
static void cont__84_16(void);
static void cont__84_17(void);
static NODE *func__84_18;
static void entry__84_18(void);
static FRAME_INFO frame__84_18 = {3, {"filename", "c_filename", "o_filename"}};
static NODE *func__84_19;
static void entry__84_19(void);
static FRAME_INFO frame__84_19 = {1, {"filename"}};
static NODE *string__84_20;
static void cont__84_21(void);
static void cont__84_22(void);
static NODE *func__86_1_format_number;
static void entry__86_1_format_number(void);
static FRAME_INFO frame__86_1_format_number = {4, {"val", "n", "m", "ac"}};
static void cont__86_2(void);
static NODE *func__86_3;
static void entry__86_3(void);
static FRAME_INFO frame__86_3 = {4, {"break", "val", "ac", "n"}};
static NODE *func__86_4;
static void entry__86_4(void);
static FRAME_INFO frame__86_4 = {6, {"i", "chr", "ac", "val", "n", "break"}};
static void cont__86_5(void);
static NODE *func__86_6;
static void entry__86_6(void);
static FRAME_INFO frame__86_6 = {5, {"ac", "val", "i", "n", "break"}};
static void cont__86_7(void);
static void cont__86_8(void);
static void cont__86_9(void);
static void cont__86_10(void);
static NODE *func__86_11;
static void entry__86_11(void);
static FRAME_INFO frame__86_11 = {3, {"val", "n", "i"}};
static void cont__86_12(void);
static void cont__86_13(void);
static NODE *string__86_14;
static void cont__86_15(void);
static void cont__86_16(void);
static void cont__86_17(void);
static void cont__86_18(void);
static void cont__86_19(void);
static void cont__86_20(void);
static NODE *func__86_21;
static void entry__86_21(void);
static FRAME_INFO frame__86_21 = {3, {"val", "m", "ac"}};
static void cont__86_22(void);
static NODE *string__86_23;
static void cont__86_24(void);
static void cont__86_25(void);
static NODE *func__86_26;
static void entry__86_26(void);
static FRAME_INFO frame__86_26 = {3, {"m", "ac", "val"}};
static void cont__86_27(void);
static NODE *func__86_28;
static void entry__86_28(void);
static FRAME_INFO frame__86_28 = {3, {"val", "ac", "m"}};
static void cont__86_29(void);
static void cont__86_30(void);
static void cont__86_31(void);
static void cont__86_32(void);
static void cont__86_33(void);
static NODE *func__87_1_sim2c__write_timing_info;
static void entry__87_1_sim2c__write_timing_info(void);
static FRAME_INFO frame__87_1_sim2c__write_timing_info = {3, {"description", "filename", "new_t"}};
static void cont__87_2(void);
static void cont__87_3(void);
static NODE *func__87_4;
static void entry__87_4(void);
static FRAME_INFO frame__87_4 = {3, {"filename", "description", "new_t"}};
static void cont__87_5(void);
static void cont__87_6(void);
static void cont__87_7(void);
static void cont__87_8(void);
static void cont__87_9(void);
static void cont__87_10(void);
static void cont__87_11(void);
static NODE *string__87_12;
static NODE *func__87_13;
static void entry__87_13(void);
static FRAME_INFO frame__87_13 = {2, {"description", "new_t"}};
static void cont__87_14(void);
static void cont__87_15(void);
static NODE *string__87_16;
static void cont__87_17(void);
static void cont__87_18(void);
static NODE *get__sim2c__write_timing_info(void) {
  return var.sim2c__write_timing_info;
}
static NODE *func__88_1_build_executable;
static void entry__88_1_build_executable(void);
static FRAME_INFO frame__88_1_build_executable = {0, {}};
static NODE *func__88_2;
static void entry__88_2(void);
static FRAME_INFO frame__88_2 = {9, {"mod_filename", "mod_name", "exe_filename", "c_filename", "o_filename", "sim_info", "c_info", "c_buf", "zz"}};
static void cont__88_3(void);
static void cont__88_4(void);
static NODE *func__88_5;
static void entry__88_5(void);
static FRAME_INFO frame__88_5 = {1, {"mod_filename"}};
static NODE *string__88_6;
static void cont__88_7(void);
static NODE *func__88_8;
static void entry__88_8(void);
static FRAME_INFO frame__88_8 = {1, {"mod_filename"}};
static void cont__88_9(void);
static NODE *func__88_10;
static void entry__88_10(void);
static FRAME_INFO frame__88_10 = {1, {"exe_filename"}};
static NODE *string__88_11;
static void cont__88_12(void);
static void cont__88_13(void);
static void cont__88_14(void);
static void cont__88_15(void);
static void cont__88_16(void);
static void cont__88_17(void);
static NODE *func__88_18;
static void entry__88_18(void);
static FRAME_INFO frame__88_18 = {2, {"c_info", "sim_info"}};
static void cont__88_19(void);
static NODE *func__88_20;
static void entry__88_20(void);
static FRAME_INFO frame__88_20 = {2, {"c_info", "sim_info"}};
static void cont__88_21(void);
static void cont__88_22(void);
static void cont__88_23(void);
static void cont__88_24(void);
static void cont__88_25(void);
static NODE *func__88_26;
static void entry__88_26(void);
static FRAME_INFO frame__88_26 = {6, {"return__1", "mod_name", "c_buf", "c_filename", "o_filename", "c_source"}};
static void cont__88_27(void);
static void cont__88_28(void);
static NODE *func__88_29;
static void entry__88_29(void);
static FRAME_INFO frame__88_29 = {0, {}};
static NODE *string__88_30;
static void cont__88_31(void);
static NODE *func__88_32;
static void entry__88_32(void);
static FRAME_INFO frame__88_32 = {0, {}};
static void cont__88_33(void);
static void cont__88_34(void);
static NODE *func__88_35;
static void entry__88_35(void);
static FRAME_INFO frame__88_35 = {1, {"c_source"}};
static void cont__88_36(void);
static void cont__88_37(void);
static void cont__88_38(void);
static NODE *func__88_39;
static void entry__88_39(void);
static FRAME_INFO frame__88_39 = {1, {"c_filename"}};
static NODE *string__88_40;
static void cont__88_41(void);
static void cont__88_42(void);
static NODE *func__88_43;
static void entry__88_43(void);
static FRAME_INFO frame__88_43 = {1, {"c_filename"}};
static NODE *string__88_44;
static void cont__88_45(void);
static NODE *func__88_46;
static void entry__88_46(void);
static FRAME_INFO frame__88_46 = {5, {"c_buf", "c_filename", "o_filename", "c_info", "o_info"}};
static void cont__88_47(void);
static void cont__88_48(void);
static void cont__88_49(void);
static NODE *func__88_50;
static void entry__88_50(void);
static FRAME_INFO frame__88_50 = {2, {"o_info", "c_info"}};
static void cont__88_51(void);
static void cont__88_52(void);
static void cont__88_53(void);
static void cont__88_54(void);
static NODE *func__88_55;
static void entry__88_55(void);
static FRAME_INFO frame__88_55 = {2, {"c_filename", "o_filename"}};
static NODE *func__88_56;
static void entry__88_56(void);
static FRAME_INFO frame__88_56 = {1, {"o_info"}};
static void cont__88_57(void);
static void cont__88_58(void);
static void cont__88_59(void);
static NODE *func__88_60;
static void entry__88_60(void);
static FRAME_INFO frame__88_60 = {0, {}};
static NODE *string__88_61;
static NODE *string__88_62;
static NODE *string__88_63;
static void cont__88_64(void);
static NODE *func__88_65;
static void entry__88_65(void);
static FRAME_INFO frame__88_65 = {1, {"filename"}};
static void cont__88_66(void);
static NODE *func__88_67;
static void entry__88_67(void);
static FRAME_INFO frame__88_67 = {2, {"exe_filename", "info"}};
static void cont__88_68(void);
static void cont__88_69(void);
static NODE *func__88_70;
static void entry__88_70(void);
static FRAME_INFO frame__88_70 = {1, {"info"}};
static void cont__88_71(void);
static NODE *func__88_72;
static void entry__88_72(void);
static FRAME_INFO frame__88_72 = {1, {"info"}};
static void cont__88_73(void);
static void cont__88_74(void);
static void cont__88_75(void);
static void cont__88_76(void);
static NODE *func__88_77;
static void entry__88_77(void);
static FRAME_INFO frame__88_77 = {0, {}};
static void cont__88_78(void);
static NODE *func__88_79;
static void entry__88_79(void);
static FRAME_INFO frame__88_79 = {2, {"exe_filename", "libs_and_files"}};
static void cont__88_80(void);
static NODE *func__88_81;
static void entry__88_81(void);
static FRAME_INFO frame__88_81 = {1, {"libs_and_files"}};
static NODE *string__88_82;
static void cont__88_83(void);
static void cont__88_84(void);
static NODE *func__88_85;
static void entry__88_85(void);
static FRAME_INFO frame__88_85 = {5, {"libs_and_files", "exe_filename", "out", "err", "success"}};
static NODE *func__88_86;
static void entry__88_86(void);
static FRAME_INFO frame__88_86 = {0, {}};
static NODE *string__88_87;
static void cont__88_88(void);
static NODE *string__88_89;
static NODE *string__88_90;
static NODE *string__88_91;
static void cont__88_92(void);
static NODE *func__88_93;
static void entry__88_93(void);
static FRAME_INFO frame__88_93 = {1, {"err"}};
static void cont__88_94(void);
static NODE *func__88_95;
static void entry__88_95(void);
static FRAME_INFO frame__88_95 = {5, {"libs_and_files", "exe_filename", "out", "err", "success"}};
static NODE *func__88_96;
static void entry__88_96(void);
static FRAME_INFO frame__88_96 = {0, {}};
static NODE *string__88_97;
static void cont__88_98(void);
static void cont__88_99(void);
static void cont__88_100(void);
static NODE *func__88_101;
static void entry__88_101(void);
static FRAME_INFO frame__88_101 = {0, {}};
static NODE *string__88_102;
static void cont__88_103(void);
static NODE *func__88_104;
static void entry__88_104(void);
static FRAME_INFO frame__88_104 = {0, {}};
static void cont__88_105(void);
static void cont__88_106(void);
static void cont__88_107(void);
static NODE *func__88_108;
static void entry__88_108(void);
static FRAME_INFO frame__88_108 = {1, {"err"}};
static void cont__88_109(void);
static void cont__88_110(void);
static void cont__88_111(void);
static void cont__88_112(void);
static NODE *func__88_113;
static void entry__88_113(void);
static FRAME_INFO frame__88_113 = {0, {}};
static void cont__88_114(void);
static void cont__88_115(void);
static NODE *func__88_116;
static void entry__88_116(void);
static FRAME_INFO frame__88_116 = {2, {"exe_filename", "zz"}};
static void cont__88_117(void);
static NODE *func__88_118;
static void entry__88_118(void);
static FRAME_INFO frame__88_118 = {1, {"exe_filename"}};
static NODE *func__88_119;
static void entry__88_119(void);
static FRAME_INFO frame__88_119 = {1, {"exe_filename"}};
static void cont__88_120(void);
static void cont__88_121(void);
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
static NODE *string__92_1;
static void cont__92_2(void);
static void cont__93_1(void);
static void cont__94_1(void);
static void cont__95_1(void);
static NODE *string__97_1;
static void cont__97_2(void);
static void cont__98_1(void);
static NODE *string__99_1;
static void cont__99_2(void);
static NODE *string__100_1;
static void cont__100_2(void);
static NODE *string__101_1;
static void cont__101_2(void);
static NODE *string__102_1;
static void cont__102_2(void);
static void cont__103_1(void);
static NODE *func__103_2;
static void entry__103_2(void);
static FRAME_INFO frame__103_2 = {0, {}};
static void cont__103_3(void);
static NODE *func__103_4;
static void entry__103_4(void);
static FRAME_INFO frame__103_4 = {0, {}};
static NODE *string__103_5;
static void cont__103_6(void);
static NODE *string__103_7;
static void cont__103_8(void);
static void cont__103_9(void);
static void cont__103_10(void);
static void cont__104_1(void);
static NODE *func__104_2;
static void entry__104_2(void);
static FRAME_INFO frame__104_2 = {0, {}};
static void cont__104_3(void);
static NODE *func__104_4;
static void entry__104_4(void);
static FRAME_INFO frame__104_4 = {0, {}};
static void cont__104_5(void);
static void cont__104_6(void);
static void cont__104_7(void);
static void cont__104_8(void);
static NODE *string__106_1;
static NODE *string__106_2;
static void cont__106_3(void);
static void cont__106_4(void);
static void cont__106_5(void);
static void cont__106_6(void);
static NODE *string__106_7;
static void cont__106_8(void);
static NODE *string__106_9;
static void cont__106_10(void);
static void cont__106_11(void);
static void cont__106_12(void);
static NODE *func__108_1;
static void entry__108_1(void);
static FRAME_INFO frame__108_1 = {2, {"platform", "priority"}};
static void cont__108_2(void);
static NODE *func__108_3;
static void entry__108_3(void);
static FRAME_INFO frame__108_3 = {3, {"break", "platform", "priority"}};
static NODE *func__108_4;
static void entry__108_4(void);
static FRAME_INFO frame__108_4 = {4, {"platform", "break", "priority", "plat"}};
static void cont__108_5(void);
static void cont__108_6(void);
static void cont__108_7(void);
static void cont__108_8(void);
static void cont__108_9(void);
static void cont__108_10(void);
static void cont__108_11(void);
static void cont__108_12(void);
static void cont__108_13(void);
static void cont__132_1(void);
static void cont__132_2(void);
static void cont__133_1(void);
static NODE *func__133_2;
static void entry__133_2(void);
static FRAME_INFO frame__133_2 = {0, {}};
static void cont__133_3(void);
static NODE *func__133_4;
static void entry__133_4(void);
static FRAME_INFO frame__133_4 = {0, {}};
static NODE *string__133_5;
static void cont__133_6(void);
static void cont__133_7(void);
static NODE *func__133_8;
static void entry__133_8(void);
static FRAME_INFO frame__133_8 = {0, {}};
static NODE *func__133_9;
static void entry__133_9(void);
static FRAME_INFO frame__133_9 = {0, {}};
static NODE *string__133_10;
static NODE *string__133_11;
static NODE *func__133_12;
static void entry__133_12(void);
static FRAME_INFO frame__133_12 = {0, {}};
static NODE *string__133_13;
static NODE *string__133_14;
static NODE *func__133_15;
static void entry__133_15(void);
static FRAME_INFO frame__133_15 = {0, {}};
static NODE *string__133_16;
static NODE *string__133_17;
static NODE *func__133_18;
static void entry__133_18(void);
static FRAME_INFO frame__133_18 = {0, {}};
static NODE *string__133_19;
static NODE *string__133_20;
static NODE *func__133_21;
static void entry__133_21(void);
static FRAME_INFO frame__133_21 = {0, {}};
static NODE *string__133_22;
static NODE *string__133_23;
static NODE *func__133_24;
static void entry__133_24(void);
static FRAME_INFO frame__133_24 = {0, {}};
static NODE *string__133_25;
static NODE *string__133_26;
static NODE *func__133_27;
static void entry__133_27(void);
static FRAME_INFO frame__133_27 = {0, {}};
static NODE *string__133_28;
static NODE *string__133_29;
static NODE *func__133_30;
static void entry__133_30(void);
static FRAME_INFO frame__133_30 = {0, {}};
static NODE *string__133_31;
static NODE *string__133_32;
static NODE *func__133_33;
static void entry__133_33(void);
static FRAME_INFO frame__133_33 = {0, {}};
static NODE *string__133_34;
static NODE *string__133_35;
static NODE *func__133_36;
static void entry__133_36(void);
static FRAME_INFO frame__133_36 = {0, {}};
static NODE *string__133_37;
static NODE *string__133_38;
static NODE *func__133_39;
static void entry__133_39(void);
static FRAME_INFO frame__133_39 = {0, {}};
static NODE *string__133_40;
static NODE *string__133_41;
static NODE *func__133_42;
static void entry__133_42(void);
static FRAME_INFO frame__133_42 = {0, {}};
static NODE *string__133_43;
static NODE *string__133_44;
static NODE *func__133_45;
static void entry__133_45(void);
static FRAME_INFO frame__133_45 = {0, {}};
static NODE *string__133_46;
static NODE *string__133_47;
static NODE *func__133_48;
static void entry__133_48(void);
static FRAME_INFO frame__133_48 = {0, {}};
static NODE *string__133_49;
static NODE *string__133_50;
static NODE *func__133_51;
static void entry__133_51(void);
static FRAME_INFO frame__133_51 = {0, {}};
static NODE *string__133_52;
static NODE *string__133_53;
static NODE *func__133_54;
static void entry__133_54(void);
static FRAME_INFO frame__133_54 = {0, {}};
static NODE *string__133_55;
static NODE *string__133_56;
static NODE *func__133_57;
static void entry__133_57(void);
static FRAME_INFO frame__133_57 = {0, {}};
static NODE *string__133_58;
static NODE *string__133_59;
static NODE *func__133_60;
static void entry__133_60(void);
static FRAME_INFO frame__133_60 = {0, {}};
static NODE *string__133_61;
static NODE *string__133_62;
static NODE *func__133_63;
static void entry__133_63(void);
static FRAME_INFO frame__133_63 = {0, {}};
static NODE *string__133_64;
static NODE *string__133_65;
static NODE *func__133_66;
static void entry__133_66(void);
static FRAME_INFO frame__133_66 = {0, {}};
static NODE *string__133_67;
static NODE *string__133_68;
static void cont__133_69(void);
static void cont__133_70(void);
static void cont__134_1(void);
static void cont__135_1(void);
static NODE *func__137_1;
static void entry__137_1(void);
static FRAME_INFO frame__137_1 = {0, {}};
static void cont__137_2(void);
static void cont__142_1(void);
static NODE *string__143_1;
static NODE *string__143_2;
static NODE *string__143_3;
static NODE *string__143_4;
static NODE *string__143_5;
static NODE *string__143_6;
static NODE *string__143_7;
static NODE *string__143_8;
static NODE *string__143_9;
static NODE *string__143_10;
static NODE *string__143_11;
static void cont__143_12(void);
static NODE *string__144_1;
static NODE *string__144_2;
static void cont__144_3(void);
static NODE *string__144_4;
static void cont__144_5(void);
static void cont__144_6(void);
static NODE *string__144_7;
static void cont__144_8(void);
static void cont__144_9(void);
static NODE *func__146_1;
static void entry__146_1(void);
static FRAME_INFO frame__146_1 = {1, {"path"}};
static NODE *string__146_2;
static void cont__146_3(void);
static void cont__146_4(void);
static void cont__146_5(void);
static void cont__147_1(void);
static void cont__147_2(void);
static void cont__147_3(void);
static void cont__147_4(void);
static void cont__147_5(void);
static void cont__165_1(void);
static NODE *func__165_2;
static void entry__165_2(void);
static FRAME_INFO frame__165_2 = {0, {}};
static NODE *string__165_3;
static NODE *string__165_4;
static void cont__165_5(void);
static void cont__165_6(void);
static NODE *func__180_1;
static void entry__180_1(void);
static FRAME_INFO frame__180_1 = {0, {}};
static void cont__180_2(void);
static void cont__180_3(void);
static NODE *func__181_1;
static void entry__181_1(void);
static FRAME_INFO frame__181_1 = {0, {}};
static NODE *func__181_2;
static void entry__181_2(void);
static FRAME_INFO frame__181_2 = {0, {}};
static NODE *func__181_3;
static void entry__181_3(void);
static FRAME_INFO frame__181_3 = {0, {}};
static NODE *func__181_4;
static void entry__181_4(void);
static FRAME_INFO frame__181_4 = {0, {}};
static void cont__181_5(void);
static void cont__181_6(void);
static void cont__181_7(void);
static NODE *func__181_8;
static void entry__181_8(void);
static FRAME_INFO frame__181_8 = {0, {}};
static NODE *func__181_9;
static void entry__181_9(void);
static FRAME_INFO frame__181_9 = {0, {}};
static NODE *func__181_10;
static void entry__181_10(void);
static FRAME_INFO frame__181_10 = {0, {}};
static NODE *func__181_11;
static void entry__181_11(void);
static FRAME_INFO frame__181_11 = {0, {}};
static void cont__181_12(void);
static void cont__181_13(void);
static void cont__182_1(void);
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
  {cont__92_2, NULL, 91, 91, 1, 30},
  {cont__93_1, NULL, 92, 92, 1, 30},
  {cont__94_1, NULL, 93, 93, 1, 28},
  {cont__95_1, NULL, 95, 95, 1, 49},
  {cont__97_2, NULL, 96, 96, 1, 15},
  {cont__98_1, NULL, 97, 97, 1, 17},
  {cont__99_2, NULL, 98, 98, 1, 72},
  {cont__100_2, NULL, 99, 99, 1, 37},
  {cont__101_2, NULL, 100, 100, 1, 39},
  {cont__102_2, NULL, 104, 104, 5, 25},
  {cont__103_1, NULL, 102, 109, 1, 45},
  {cont__103_10, NULL, 113, 113, 5, 26},
  {cont__104_1, NULL, 111, 118, 1, 45},
  {cont__104_8, NULL, 124, 124, 5, 19},
  {cont__106_3, NULL, 125, 125, 5, 22},
  {cont__106_4, NULL, 126, 126, 5, 22},
  {cont__106_5, NULL, 127, 127, 5, 21},
  {cont__106_6, NULL, 128, 128, 5, 19},
  {cont__106_8, NULL, 129, 129, 5, 17},
  {cont__106_10, NULL, 130, 130, 5, 16},
  {cont__106_11, NULL, 122, 130, 1, 17},
  {cont__106_12, NULL, 133, 143, 1, 22},
  {cont__108_13, NULL, 167, 167, 42, 42},
  {cont__132_1, NULL, 167, 167, 1, 43},
  {cont__132_2, NULL, 169, 169, 3, 20},
  {cont__133_1, NULL, 168, 243, 1, 49},
  {cont__133_70, NULL, 244, 244, 1, 39},
  {cont__134_1, NULL, 245, 245, 1, 30},
  {cont__135_1, NULL, 247, 247, 1, 37},
  {cont__137_2, NULL, 256, 256, 1, 21},
  {cont__142_1, NULL, 258, 270, 1, 27},
  {cont__143_12, NULL, 274, 274, 16, 44},
  {cont__144_3, NULL, 274, 274, 5, 44},
  {cont__144_5, NULL, 275, 275, 16, 44},
  {cont__144_6, NULL, 275, 275, 5, 44},
  {cont__144_8, NULL, 272, 275, 1, 45},
  {cont__144_9, NULL, 278, 279, 1, 39},
  {cont__146_5, NULL, 286, 286, 39, 61},
  {cont__147_1, NULL, 286, 286, 9, 62},
  {cont__147_2, NULL, 285, 287, 7, 17},
  {cont__147_3, NULL, 284, 288, 5, 24},
  {cont__147_4, NULL, 281, 288, 1, 27},
  {cont__147_5, NULL, 626, 626, 4, 25},
  {cont__165_1, NULL, 626, 628, 1, 52},
  {cont__165_6, NULL, 1073, 1073, 1, 36},
  {cont__180_3, NULL, 1074, 1086, 1, 18},
  {cont__181_13, NULL, },
  {cont__182_1, NULL, },
  {entry__47_2, NULL, 250, 250, 36, 49},
  {entry__47_1_sim2c__show_compiler_debug_info, NULL, 250, 250, 3, 49},
  {entry__65_13, NULL, 307, 307, 37, 80},
  {cont__65_14, &frame__65_13, 307, 307, 37, 61},
  {cont__65_15, &frame__65_13, 307, 307, 80, 80},
  {entry__65_10, NULL, 306, 306, 13, 41},
  {cont__65_11, &frame__65_10, 307, 307, 16, 34},
  {cont__65_12, &frame__65_10, 307, 307, 13, 80},
  {entry__65_8, NULL, 305, 305, 14, 33},
  {cont__65_9, &frame__65_8, 305, 307, 11, 80},
  {entry__65_6, NULL, 304, 304, 18, 32},
  {cont__65_7, &frame__65_6, 304, 307, 9, 81},
  {entry__65_4, NULL, 303, 303, 10, 26},
  {cont__65_5, &frame__65_4, 303, 307, 7, 82},
  {entry__65_3, NULL, 302, 307, 5, 83},
  {entry__65_20, NULL, 311, 312, 11, 57},
  {cont__65_23, &frame__65_20, 311, 312, 5, 57},
  {entry__65_1_resolve_filename, NULL, 300, 300, 6, 36},
  {cont__65_2, &frame__65_1_resolve_filename, 300, 307, 3, 84},
  {cont__65_16, &frame__65_1_resolve_filename, 308, 308, 3, 32},
  {cont__65_17, &frame__65_1_resolve_filename, 309, 309, 3, 38},
  {cont__65_18, &frame__65_1_resolve_filename, 310, 310, 6, 25},
  {cont__65_19, &frame__65_1_resolve_filename, 310, 312, 3, 58},
  {cont__65_24, &frame__65_1_resolve_filename, 313, 313, 21, 39},
  {cont__65_25, &frame__65_1_resolve_filename, 313, 313, 6, 40},
  {cont__65_26, &frame__65_1_resolve_filename, 313, 313, 3, 40},
  {entry__66_10, NULL, 331, 331, 56, 77},
  {cont__66_11, &frame__66_10, 331, 331, 77, 77},
  {entry__66_8, NULL, 331, 331, 35, 53},
  {cont__66_9, &frame__66_8, 331, 331, 32, 77},
  {entry__66_6, NULL, 331, 331, 10, 29},
  {cont__66_7, &frame__66_6, 331, 331, 7, 77},
  {entry__66_28, NULL, 337, 337, 41, 65},
  {cont__66_29, &frame__66_28, 337, 337, 41, 65},
  {entry__66_31, NULL, 338, 338, 11, 38},
  {cont__66_32, &frame__66_31, 338, 338, 49, 49},
  {entry__66_15, NULL, 333, 333, 48, 60},
  {cont__66_17, &frame__66_15, 333, 333, 48, 68},
  {cont__66_18, &frame__66_15, 333, 333, 9, 69},
  {cont__66_19, &frame__66_15, 334, 334, 9, 34},
  {cont__66_20, &frame__66_15, 335, 335, 22, 36},
  {cont__66_21, &frame__66_15, 335, 335, 38, 62},
  {cont__66_22, &frame__66_15, 335, 335, 22, 62},
  {cont__66_23, &frame__66_15, 335, 335, 22, 64},
  {cont__66_24, &frame__66_15, 335, 335, 9, 67},
  {cont__66_25, &frame__66_15, 336, 336, 9, 49},
  {cont__66_26, &frame__66_15, 337, 337, 12, 36},
  {cont__66_27, &frame__66_15, 337, 337, 12, 65},
  {cont__66_30, &frame__66_15, 337, 338, 9, 49},
  {cont__66_33, &frame__66_15, 339, 339, 9, 52},
  {cont__66_34, &frame__66_15, 340, 340, 9, 26},
  {cont__66_35, &frame__66_15, 341, 341, 9, 43},
  {cont__66_36, &frame__66_15, 342, 342, 9, 30},
  {cont__66_37, &frame__66_15, 342, 342, 52, 52},
  {entry__66_12, NULL, 332, 332, 10, 33},
  {cont__66_14, &frame__66_12, 332, 342, 7, 52},
  {entry__66_4, NULL, 329, 329, 5, 33},
  {cont__66_5, &frame__66_4, 330, 342, 5, 53},
  {entry__66_49, NULL, 348, 348, 38, 60},
  {cont__66_50, &frame__66_49, 348, 348, 60, 60},
  {entry__66_45_maybe_push_common, NULL, 347, 347, 11, 54},
  {cont__66_47, &frame__66_45_maybe_push_common, 348, 348, 14, 35},
  {cont__66_48, &frame__66_45_maybe_push_common, 348, 348, 11, 60},
  {entry__66_57, NULL, 355, 356, 17, 57},
  {cont__66_60, &frame__66_57, 355, 356, 11, 57},
  {entry__66_67, NULL, 360, 360, 11, 34},
  {cont__66_68, &frame__66_67, 361, 361, 11, 45},
  {cont__66_69, &frame__66_67, 361, 361, 45, 45},
  {entry__66_64, NULL, 359, 359, 18, 31},
  {cont__66_65, &frame__66_64, 359, 359, 18, 31},
  {cont__66_66, &frame__66_64, 359, 361, 15, 45},
  {entry__66_44, NULL, 350, 350, 9, 35},
  {cont__66_51, &frame__66_44, 351, 351, 35, 58},
  {cont__66_52, &frame__66_44, 351, 351, 9, 59},
  {cont__66_53, &frame__66_44, 352, 352, 9, 39},
  {cont__66_54, &frame__66_44, 353, 353, 9, 46},
  {cont__66_55, &frame__66_44, 354, 354, 16, 32},
  {cont__66_56, &frame__66_44, 354, 356, 9, 58},
  {cont__66_61, &frame__66_44, 357, 357, 9, 30},
  {cont__66_62, &frame__66_44, 358, 358, 9, 34},
  {cont__66_63, &frame__66_44, 359, 361, 9, 45},
  {cont__66_70, &frame__66_44, 362, 362, 10, 30},
  {cont__66_71, &frame__66_44, 362, 362, 9, 40},
  {cont__66_72, &frame__66_44, 362, 362, 9, 30},
  {cont__66_73, &frame__66_44, 362, 362, 46, 46},
  {entry__66_41, NULL, 345, 345, 14, 44},
  {cont__66_43, &frame__66_41, 345, 362, 7, 46},
  {entry__66_39, NULL, 344, 344, 8, 30},
  {cont__66_40, &frame__66_39, 344, 362, 5, 47},
  {entry__66_77, NULL, 363, 363, 39, 64},
  {entry__66_1_add_module_infos, NULL, 324, 324, 22, 27},
  {cont__66_2, &frame__66_1_add_module_infos, 324, 324, 3, 33},
  {cont__66_3, &frame__66_1_add_module_infos, 328, 342, 3, 54},
  {cont__66_38, &frame__66_1_add_module_infos, 343, 362, 3, 48},
  {cont__66_74, &frame__66_1_add_module_infos, 363, 363, 6, 31},
  {cont__66_75, &frame__66_1_add_module_infos, 363, 363, 6, 36},
  {cont__66_76, &frame__66_1_add_module_infos, 363, 363, 3, 64},
  {cont__66_78, &frame__66_1_add_module_infos, 363, 363, 64, 64},
  {entry__67_4, NULL, 374, 374, 23, 29},
  {entry__67_5, NULL, 375, 375, 47, 47},
  {cont__67_6, &frame__67_5, 375, 375, 22, 48},
  {cont__67_7, &frame__67_5, 375, 375, 70, 70},
  {cont__67_8, &frame__67_5, 375, 375, 50, 71},
  {cont__67_9, &frame__67_5, 375, 375, 5, 71},
  {cont__67_10, &frame__67_5, 376, 376, 8, 28},
  {cont__67_11, &frame__67_5, 376, 376, 5, 28},
  {entry__67_1_lookup, NULL, 373, 373, 3, 29},
  {cont__67_2, &frame__67_1_lookup, 374, 374, 6, 20},
  {cont__67_3, &frame__67_1_lookup, 374, 376, 3, 28},
  {entry__68_2, NULL, 379, 379, 43, 52},
  {cont__68_3, &frame__68_2, 379, 379, 27, 52},
  {entry__68_1_Gcc, NULL, 379, 379, 3, 52},
  {cont__68_5, &frame__68_1_Gcc, 380, 380, 3, 11},
  {entry__69_2, NULL, 383, 383, 41, 60},
  {entry__69_8, NULL, 388, 388, 11, 23},
  {cont__69_9, &frame__69_8, 386, 388, 13, 24},
  {cont__69_12, &frame__69_8, 386, 388, 7, 24},
  {entry__69_4, NULL, 384, 384, 5, 72},
  {cont__69_7, &frame__69_4, 385, 388, 5, 25},
  {cont__69_13, &frame__69_4, 389, 389, 17, 17},
  {entry__69_1_compile_c, NULL, 383, 383, 10, 60},
  {cont__69_3, &frame__69_1_compile_c, 383, 389, 3, 17},
  {entry__70_25, NULL, 416, 416, 45, 74},
  {cont__70_26, &frame__70_25, 416, 416, 9, 41},
  {cont__70_27, &frame__70_25, 416, 416, 9, 74},
  {cont__70_28, &frame__70_25, 416, 416, 9, 74},
  {entry__70_21, NULL, 415, 415, 43, 75},
  {cont__70_22, &frame__70_21, 415, 415, 9, 39},
  {cont__70_23, &frame__70_21, 415, 415, 9, 75},
  {cont__70_24, &frame__70_21, 416, 416, 9, 74},
  {cont__70_29, &frame__70_21, },
  {entry__70_19, NULL, 414, 414, 9, 32},
  {cont__70_20, &frame__70_19, },
  {cont__70_30, &frame__70_19, },
  {entry__70_17, NULL, 413, 413, 9, 29},
  {cont__70_18, &frame__70_17, },
  {cont__70_31, &frame__70_17, },
  {entry__70_41, NULL, 428, 428, 17, 47},
  {cont__70_42, &frame__70_41, 428, 428, 17, 67},
  {cont__70_43, &frame__70_41, 428, 428, 17, 67},
  {entry__70_45, NULL, 431, 431, 17, 21},
  {entry__70_38_check, NULL, 424, 424, 13, 42},
  {cont__70_39, &frame__70_38_check, 427, 427, 17, 38},
  {cont__70_40, &frame__70_38_check, 426, 428, 15, 66},
  {cont__70_44, &frame__70_38_check, 425, 431, 13, 22},
  {entry__70_58, NULL, 441, 441, 58, 58},
  {cont__70_59, &frame__70_58, 441, 441, 40, 59},
  {cont__70_60, &frame__70_58, 441, 441, 23, 60},
  {cont__70_61, &frame__70_58, 441, 441, 17, 60},
  {entry__70_63, NULL, 443, 443, 53, 77},
  {cont__70_64, &frame__70_63, 443, 443, 47, 77},
  {entry__70_62, NULL, 443, 443, 17, 77},
  {entry__70_55, NULL, 440, 440, 15, 40},
  {cont__70_57, &frame__70_55, 439, 443, 13, 78},
  {entry__70_37, NULL, 433, 433, 18, 41},
  {cont__70_47, &frame__70_37, 433, 433, 11, 47},
  {cont__70_48, &frame__70_37, 434, 434, 11, 26},
  {cont__70_49, &frame__70_37, 435, 435, 11, 20},
  {cont__70_50, &frame__70_37, 436, 436, 11, 50},
  {cont__70_51, &frame__70_37, 437, 437, 11, 44},
  {cont__70_52, &frame__70_37, 438, 438, 14, 30},
  {cont__70_54, &frame__70_37, 438, 443, 11, 79},
  {entry__70_36, NULL, 422, 443, 9, 80},
  {cont__70_65, &frame__70_36, 443, 443, 80, 80},
  {entry__70_33, NULL, 419, 419, 7, 55},
  {cont__70_34, &frame__70_33, 420, 420, 7, 38},
  {cont__70_35, &frame__70_33, 421, 443, 7, 81},
  {entry__70_74, NULL, 458, 458, 29, 41},
  {cont__70_75, &frame__70_74, 458, 458, 23, 41},
  {entry__70_67, NULL, 452, 452, 7, 36},
  {cont__70_68, &frame__70_67, 453, 453, 7, 22},
  {cont__70_69, &frame__70_67, 454, 454, 7, 31},
  {cont__70_70, &frame__70_67, 455, 455, 7, 32},
  {cont__70_71, &frame__70_67, 456, 456, 7, 43},
  {cont__70_72, &frame__70_67, 457, 457, 7, 32},
  {cont__70_73, &frame__70_67, 458, 458, 7, 41},
  {cont__70_76, &frame__70_67, 459, 459, 25, 35},
  {cont__70_77, &frame__70_67, 459, 459, 7, 35},
  {cont__70_78, &frame__70_67, 459, 459, 35, 35},
  {entry__70_2, NULL, 401, 401, 48, 48},
  {cont__70_3, &frame__70_2, 401, 401, 5, 49},
  {cont__70_4, &frame__70_2, 402, 402, 35, 57},
  {cont__70_5, &frame__70_2, 402, 402, 5, 58},
  {cont__70_6, &frame__70_2, 403, 403, 5, 42},
  {cont__70_7, &frame__70_2, 404, 404, 42, 64},
  {cont__70_8, &frame__70_2, 404, 404, 5, 70},
  {cont__70_10, &frame__70_2, 405, 405, 51, 62},
  {cont__70_11, &frame__70_2, 405, 405, 39, 63},
  {cont__70_12, &frame__70_2, 405, 405, 5, 71},
  {cont__70_13, &frame__70_2, 406, 406, 5, 34},
  {cont__70_14, &frame__70_2, 407, 407, 5, 32},
  {cont__70_15, &frame__70_2, 408, 408, 5, 38},
  {cont__70_16, &frame__70_2, 410, 416, 5, 75},
  {cont__70_32, &frame__70_2, 418, 443, 5, 82},
  {cont__70_66, &frame__70_2, 444, 459, 5, 35},
  {cont__70_79, &frame__70_2, 460, 460, 5, 19},
  {cont__70_80, &frame__70_2, 461, 461, 8, 21},
  {cont__70_81, &frame__70_2, 461, 461, 5, 21},
  {entry__70_1_compile_meta_module, NULL, 400, 461, 3, 21},
  {entry__71_13, NULL, 486, 486, 43, 43},
  {cont__71_14, &frame__71_13, 486, 486, 15, 44},
  {cont__71_15, &frame__71_13, 488, 488, 48, 48},
  {cont__71_16, &frame__71_13, 488, 488, 24, 49},
  {cont__71_17, &frame__71_13, 488, 488, 17, 59},
  {cont__71_18, &frame__71_13, 489, 489, 44, 44},
  {cont__71_19, &frame__71_13, 489, 489, 24, 45},
  {cont__71_20, &frame__71_13, 489, 489, 17, 55},
  {cont__71_21, &frame__71_13, 487, 489, 15, 55},
  {entry__71_11, NULL, 485, 485, 16, 26},
  {cont__71_12, &frame__71_11, 485, 489, 13, 56},
  {entry__71_24, NULL, 495, 495, 17, 36},
  {entry__71_23, NULL, },
  {cont__71_25, &frame__71_23, },
  {entry__71_27, NULL, 497, 497, 32, 57},
  {cont__71_28, &frame__71_27, 497, 497, 17, 66},
  {entry__71_30, NULL, 500, 500, 44, 71},
  {cont__71_31, &frame__71_30, 500, 500, 30, 72},
  {cont__71_33, &frame__71_30, 500, 500, 19, 73},
  {cont__71_34, &frame__71_30, 500, 500, 78, 78},
  {entry__71_29, NULL, 499, 500, 17, 78},
  {entry__71_22, NULL, },
  {cont__71_26, &frame__71_22, 491, 500, 13, 80},
  {entry__71_9, NULL, 484, 484, 11, 36},
  {cont__71_10, &frame__71_9, 483, 500, 9, 82},
  {entry__71_36, NULL, 502, 502, 37, 64},
  {cont__71_37, &frame__71_36, 502, 502, 26, 65},
  {cont__71_38, &frame__71_36, 502, 502, 70, 70},
  {entry__71_35, NULL, 502, 502, 9, 70},
  {entry__71_2, NULL, 475, 475, 12, 35},
  {cont__71_3, &frame__71_2, 475, 475, 5, 42},
  {cont__71_4, &frame__71_2, 476, 476, 5, 20},
  {cont__71_5, &frame__71_2, 477, 477, 5, 14},
  {cont__71_6, &frame__71_2, 478, 478, 5, 44},
  {cont__71_7, &frame__71_2, 479, 479, 5, 38},
  {cont__71_8, &frame__71_2, 480, 502, 5, 71},
  {entry__71_1_build_dependencies, NULL, 474, 502, 3, 72},
  {cont__71_41, &frame__71_1_build_dependencies, 502, 502, 72, 72},
  {entry__72_9, NULL, 524, 524, 28, 44},
  {cont__72_10, &frame__72_9, 524, 524, 28, 44},
  {entry__72_12, NULL, 525, 525, 9, 72},
  {entry__72_18, NULL, 532, 532, 11, 40},
  {cont__72_19, &frame__72_18, 532, 532, 11, 60},
  {cont__72_20, &frame__72_18, 532, 532, 11, 60},
  {entry__72_22, NULL, 534, 534, 11, 59},
  {cont__72_23, &frame__72_22, 534, 534, 59, 59},
  {entry__72_3, NULL, 522, 522, 7, 45},
  {cont__72_4, &frame__72_3, 523, 523, 58, 58},
  {cont__72_5, &frame__72_3, 523, 523, 34, 59},
  {cont__72_6, &frame__72_3, 523, 523, 7, 75},
  {cont__72_7, &frame__72_3, 524, 524, 10, 23},
  {cont__72_8, &frame__72_3, 524, 524, 10, 44},
  {cont__72_11, &frame__72_3, 524, 525, 7, 72},
  {cont__72_13, &frame__72_3, 526, 526, 7, 53},
  {cont__72_14, &frame__72_3, 527, 527, 7, 38},
  {cont__72_15, &frame__72_3, 528, 528, 7, 34},
  {cont__72_16, &frame__72_3, 531, 531, 11, 40},
  {cont__72_17, &frame__72_3, 530, 532, 9, 59},
  {cont__72_21, &frame__72_3, 529, 534, 7, 60},
  {entry__72_27, NULL, 537, 537, 22, 43},
  {cont__72_28, &frame__72_27, 537, 537, 48, 48},
  {entry__72_32, NULL, 543, 543, 29, 56},
  {cont__72_33, &frame__72_32, 543, 543, 9, 56},
  {cont__72_34, &frame__72_32, 543, 543, 9, 56},
  {entry__72_30, NULL, 542, 542, 9, 27},
  {cont__72_31, &frame__72_30, 543, 543, 9, 56},
  {cont__72_35, &frame__72_30, },
  {entry__72_42, NULL, 546, 546, 21, 63},
  {entry__72_45, NULL, 547, 547, 35, 53},
  {entry__72_47, NULL, 548, 548, 32, 54},
  {entry__72_51, NULL, 550, 550, 26, 56},
  {entry__72_37, NULL, 545, 545, 50, 59},
  {cont__72_39, &frame__72_37, 545, 545, 61, 70},
  {cont__72_40, &frame__72_37, 545, 545, 9, 71},
  {cont__72_41, &frame__72_37, 546, 546, 9, 63},
  {cont__72_44, &frame__72_37, 547, 547, 9, 53},
  {cont__72_46, &frame__72_37, 548, 548, 9, 54},
  {cont__72_48, &frame__72_37, 549, 549, 25, 37},
  {cont__72_49, &frame__72_37, 549, 549, 9, 37},
  {cont__72_50, &frame__72_37, 550, 550, 9, 56},
  {cont__72_52, &frame__72_37, 550, 550, 56, 56},
  {entry__72_57, NULL, 557, 557, 44, 71},
  {cont__72_58, &frame__72_57, 557, 557, 13, 40},
  {cont__72_59, &frame__72_57, 557, 557, 13, 71},
  {cont__72_60, &frame__72_57, 557, 557, 13, 71},
  {entry__72_63, NULL, 559, 559, 30, 60},
  {entry__72_62, NULL, 559, 559, 13, 60},
  {entry__72_66, NULL, 564, 564, 17, 44},
  {cont__72_67, &frame__72_66, 564, 564, 17, 69},
  {cont__72_68, &frame__72_66, 564, 564, 17, 69},
  {entry__72_70, NULL, 566, 566, 17, 68},
  {cont__72_71, &frame__72_70, 566, 566, 68, 68},
  {entry__72_64, NULL, 563, 563, 17, 51},
  {cont__72_65, &frame__72_64, 562, 564, 15, 68},
  {cont__72_69, &frame__72_64, 561, 566, 13, 69},
  {entry__72_53, NULL, 552, 552, 9, 30},
  {cont__72_54, &frame__72_53, 553, 553, 9, 32},
  {cont__72_55, &frame__72_53, 556, 556, 13, 31},
  {cont__72_56, &frame__72_53, 555, 557, 11, 70},
  {cont__72_61, &frame__72_53, 554, 566, 9, 71},
  {entry__72_2_compile_submodule, NULL, 521, 534, 5, 61},
  {cont__72_24, &frame__72_2_compile_submodule, 535, 535, 5, 48},
  {cont__72_25, &frame__72_2_compile_submodule, 536, 536, 5, 28},
  {cont__72_26, &frame__72_2_compile_submodule, 537, 537, 5, 48},
  {cont__72_29, &frame__72_2_compile_submodule, 538, 538, 5, 21},
  {cont__72_36, &frame__72_2_compile_submodule, 539, 566, 5, 73},
  {cont__72_72, &frame__72_2_compile_submodule, 567, 567, 5, 63},
  {entry__72_75, NULL, 571, 572, 11, 56},
  {cont__72_78, &frame__72_75, 571, 572, 5, 56},
  {entry__72_91, NULL, 579, 579, 51, 75},
  {cont__72_92, &frame__72_91, 579, 579, 32, 75},
  {cont__72_93, &frame__72_91, 579, 579, 75, 75},
  {entry__72_86, NULL, 578, 578, 59, 59},
  {cont__72_87, &frame__72_86, 578, 578, 30, 60},
  {cont__72_88, &frame__72_86, 578, 578, 25, 61},
  {cont__72_89, &frame__72_86, 578, 578, 7, 61},
  {cont__72_90, &frame__72_86, 579, 579, 7, 75},
  {entry__72_99, NULL, 586, 586, 37, 60},
  {cont__72_100, &frame__72_99, 586, 586, 37, 60},
  {entry__72_102, NULL, 588, 588, 35, 35},
  {entry__72_96, NULL, 585, 585, 11, 47},
  {cont__72_97, &frame__72_96, 586, 586, 14, 32},
  {cont__72_98, &frame__72_96, 586, 586, 14, 60},
  {cont__72_101, &frame__72_96, 586, 588, 11, 35},
  {entry__72_104, NULL, 592, 592, 13, 37},
  {cont__72_105, &frame__72_104, 593, 593, 13, 32},
  {cont__72_106, &frame__72_104, 590, 593, 11, 32},
  {entry__72_95, NULL, 584, 588, 9, 36},
  {cont__72_103, &frame__72_95, 589, 593, 9, 33},
  {entry__72_113, NULL, 601, 601, 39, 62},
  {cont__72_114, &frame__72_113, 601, 601, 39, 62},
  {entry__72_116, NULL, 603, 603, 37, 37},
  {entry__72_110, NULL, 600, 600, 13, 77},
  {cont__72_111, &frame__72_110, 601, 601, 16, 34},
  {cont__72_112, &frame__72_110, 601, 601, 16, 62},
  {cont__72_115, &frame__72_110, 601, 603, 13, 37},
  {entry__72_119, NULL, 605, 605, 32, 53},
  {cont__72_120, &frame__72_119, 605, 605, 13, 65},
  {cont__72_121, &frame__72_119, 606, 606, 13, 39},
  {cont__72_122, &frame__72_119, 607, 607, 13, 35},
  {cont__72_123, &frame__72_119, 607, 607, 38, 38},
  {entry__72_109, NULL, 599, 603, 11, 38},
  {cont__72_117, &frame__72_109, 604, 604, 14, 37},
  {cont__72_118, &frame__72_109, 604, 607, 11, 38},
  {entry__72_130, NULL, 612, 612, 40, 69},
  {cont__72_132, &frame__72_130, 612, 612, 69, 69},
  {entry__72_129, NULL, 612, 612, 13, 69},
  {entry__72_125, NULL, 609, 609, 11, 61},
  {cont__72_126, &frame__72_125, 610, 610, 11, 38},
  {cont__72_127, &frame__72_125, 611, 611, 14, 33},
  {cont__72_128, &frame__72_125, 611, 612, 11, 69},
  {cont__72_133, &frame__72_125, 613, 613, 11, 39},
  {cont__72_134, &frame__72_125, 613, 613, 39, 39},
  {entry__72_108, NULL, 596, 607, 9, 39},
  {cont__72_124, &frame__72_108, 608, 613, 9, 39},
  {entry__72_94, NULL, 581, 593, 7, 34},
  {cont__72_107, &frame__72_94, 594, 613, 7, 40},
  {entry__72_1_compile_module, NULL, 569, 569, 3, 40},
  {cont__72_73, &frame__72_1_compile_module, 570, 570, 10, 28},
  {cont__72_74, &frame__72_1_compile_module, 570, 572, 3, 57},
  {cont__72_79, &frame__72_1_compile_module, 573, 573, 3, 39},
  {cont__72_81, &frame__72_1_compile_module, 574, 574, 6, 24},
  {cont__72_82, &frame__72_1_compile_module, 574, 574, 3, 31},
  {cont__72_83, &frame__72_1_compile_module, 575, 575, 3, 22},
  {cont__72_84, &frame__72_1_compile_module, 577, 577, 5, 21},
  {cont__72_85, &frame__72_1_compile_module, 576, 613, 3, 42},
  {cont__72_135, &frame__72_1_compile_module, 613, 613, 42, 42},
  {entry__73_4, NULL, 622, 622, 21, 41},
  {cont__73_5, &frame__73_4, 622, 622, 43, 67},
  {cont__73_6, &frame__73_4, 622, 622, 5, 67},
  {entry__73_8, NULL, 624, 624, 20, 40},
  {cont__73_9, &frame__73_8, 624, 624, 42, 66},
  {cont__73_10, &frame__73_8, 624, 624, 5, 66},
  {entry__73_1_compile_modules, NULL, 620, 620, 47, 66},
  {cont__73_2, &frame__73_1_compile_modules, 620, 620, 3, 66},
  {cont__73_3, &frame__73_1_compile_modules, 621, 622, 3, 67},
  {cont__73_7, &frame__73_1_compile_modules, 623, 624, 3, 66},
  {entry__75_6, NULL, 633, 633, 34, 58},
  {cont__75_8, &frame__75_6, 633, 633, 25, 58},
  {entry__75_2, NULL, 632, 632, 5, 40},
  {cont__75_4, &frame__75_2, 633, 633, 8, 22},
  {cont__75_5, &frame__75_2, 633, 633, 5, 58},
  {cont__75_9, &frame__75_2, 634, 634, 40, 57},
  {cont__75_10, &frame__75_2, 634, 634, 5, 57},
  {cont__75_12, &frame__75_2, 635, 635, 35, 54},
  {cont__75_13, &frame__75_2, 635, 635, 5, 54},
  {entry__75_1_show_file_list, NULL, 631, 635, 3, 54},
  {entry__76_7, NULL, 644, 644, 60, 70},
  {cont__76_9, &frame__76_7, 644, 644, 40, 70},
  {cont__76_10, &frame__76_7, 644, 644, 70, 70},
  {entry__76_5, NULL, 644, 644, 14, 30},
  {cont__76_6, &frame__76_5, 644, 644, 5, 70},
  {entry__76_12, NULL, 645, 645, 54, 77},
  {cont__76_13, &frame__76_12, 645, 645, 27, 77},
  {entry__76_16, NULL, 646, 646, 30, 54},
  {cont__76_17, &frame__76_16, 646, 646, 54, 54},
  {entry__76_25, NULL, 655, 655, 16, 45},
  {cont__76_28, &frame__76_25, 655, 655, 13, 45},
  {entry__76_29, NULL, 656, 656, 16, 38},
  {cont__76_31, &frame__76_29, 656, 656, 13, 38},
  {entry__76_21, NULL, 654, 654, 13, 30},
  {cont__76_22, &frame__76_21, 654, 654, 13, 41},
  {cont__76_24, &frame__76_21, 653, 656, 11, 37},
  {cont__76_32, &frame__76_21, 652, 656, 9, 39},
  {entry__76_35, NULL, 660, 660, 25, 44},
  {cont__76_36, &frame__76_35, 660, 660, 52, 71},
  {cont__76_37, &frame__76_35, 660, 660, 16, 73},
  {cont__76_38, &frame__76_35, 660, 661, 13, 26},
  {entry__76_39, NULL, 662, 662, 16, 29},
  {cont__76_40, &frame__76_39, 662, 662, 13, 29},
  {entry__76_33, NULL, 659, 659, 13, 34},
  {cont__76_34, &frame__76_33, 658, 662, 11, 28},
  {cont__76_41, &frame__76_33, 657, 662, 9, 30},
  {entry__76_19, NULL, 651, 651, 9, 35},
  {cont__76_20, &frame__76_19, 650, 662, 7, 30},
  {cont__76_42, &frame__76_19, 648, 662, 5, 32},
  {cont__76_43, &frame__76_19, 662, 662, 33, 33},
  {entry__76_1_library_paths_and_file_list, NULL, 638, 638, 3, 16},
  {cont__76_2, &frame__76_1_library_paths_and_file_list, 642, 642, 3, 39},
  {cont__76_3, &frame__76_1_library_paths_and_file_list, 643, 643, 6, 21},
  {cont__76_4, &frame__76_1_library_paths_and_file_list, 643, 644, 3, 70},
  {cont__76_11, &frame__76_1_library_paths_and_file_list, 645, 645, 3, 77},
  {cont__76_15, &frame__76_1_library_paths_and_file_list, 646, 646, 3, 54},
  {cont__76_18, &frame__76_1_library_paths_and_file_list, 647, 662, 3, 33},
  {cont__76_44, &frame__76_1_library_paths_and_file_list, 663, 663, 24, 57},
  {cont__76_45, &frame__76_1_library_paths_and_file_list, 663, 663, 3, 57},
  {entry__77_9, NULL, 673, 673, 51, 64},
  {cont__77_10, &frame__77_9, 673, 673, 51, 64},
  {entry__77_7, NULL, 673, 673, 37, 46},
  {cont__77_8, &frame__77_7, 673, 673, 37, 64},
  {cont__77_11, &frame__77_7, 673, 673, 37, 64},
  {entry__77_29, NULL, 684, 684, 25, 59},
  {cont__77_31, &frame__77_29, 684, 684, 21, 60},
  {cont__77_32, &frame__77_29, 684, 684, 21, 60},
  {entry__77_25, NULL, 683, 683, 25, 58},
  {cont__77_27, &frame__77_25, 683, 683, 21, 59},
  {cont__77_28, &frame__77_25, 684, 684, 21, 60},
  {cont__77_33, &frame__77_25, },
  {entry__77_38, NULL, 688, 688, 46, 80},
  {cont__77_39, &frame__77_38, 688, 688, 46, 80},
  {entry__77_41, NULL, 690, 690, 44, 74},
  {cont__77_42, &frame__77_41, 690, 690, 23, 74},
  {entry__77_35, NULL, 688, 688, 21, 34},
  {cont__77_36, &frame__77_35, 688, 688, 21, 41},
  {cont__77_37, &frame__77_35, 688, 688, 21, 80},
  {cont__77_40, &frame__77_35, 687, 690, 19, 75},
  {entry__77_49, NULL, 693, 693, 60, 60},
  {cont__77_50, &frame__77_49, 693, 693, 44, 61},
  {cont__77_51, &frame__77_49, 693, 693, 23, 61},
  {entry__77_46, NULL, 692, 692, 35, 62},
  {cont__77_47, &frame__77_46, 692, 692, 35, 67},
  {cont__77_48, &frame__77_46, 692, 693, 21, 61},
  {entry__77_43, NULL, 691, 691, 22, 62},
  {cont__77_45, &frame__77_43, 691, 693, 19, 62},
  {entry__77_52, NULL, 695, 695, 21, 52},
  {entry__77_54, NULL, 696, 696, 31, 45},
  {entry__77_21, NULL, 682, 682, 21, 34},
  {cont__77_22, &frame__77_21, 682, 682, 21, 41},
  {cont__77_23, &frame__77_21, 682, 682, 21, 41},
  {cont__77_24, &frame__77_21, 680, 684, 17, 61},
  {cont__77_34, &frame__77_21, 686, 695, 17, 53},
  {cont__77_53, &frame__77_21, 696, 696, 17, 45},
  {cont__77_56, &frame__77_21, 697, 697, 17, 33},
  {entry__77_17, NULL, 677, 677, 15, 38},
  {cont__77_18, &frame__77_17, 678, 678, 15, 50},
  {cont__77_19, &frame__77_17, 679, 679, 18, 39},
  {cont__77_20, &frame__77_17, 679, 697, 15, 33},
  {entry__77_13, NULL, 674, 674, 33, 37},
  {cont__77_14, &frame__77_13, 674, 674, 13, 38},
  {cont__77_15, &frame__77_13, 676, 676, 20, 42},
  {cont__77_16, &frame__77_13, 676, 697, 13, 34},
  {entry__77_5, NULL, 673, 673, 18, 32},
  {cont__77_6, &frame__77_5, 673, 673, 18, 64},
  {cont__77_12, &frame__77_5, 673, 697, 11, 35},
  {entry__77_59, NULL, 699, 699, 33, 42},
  {cont__77_60, &frame__77_59, 699, 699, 33, 42},
  {entry__77_62, NULL, 699, 699, 50, 50},
  {entry__77_57, NULL, 699, 699, 14, 28},
  {cont__77_58, &frame__77_57, 699, 699, 14, 42},
  {cont__77_61, &frame__77_57, 699, 699, 11, 50},
  {entry__77_3, NULL, 672, 672, 9, 20},
  {cont__77_4, &frame__77_3, 671, 699, 7, 51},
  {entry__77_2_collect_declarations, NULL, 670, 699, 5, 52},
  {entry__77_63, NULL, 701, 701, 28, 54},
  {entry__77_74, NULL, 706, 706, 22, 59},
  {entry__77_1_create_imports, NULL, 701, 701, 3, 54},
  {cont__77_64, &frame__77_1_create_imports, 702, 702, 3, 49},
  {cont__77_66, &frame__77_1_create_imports, 703, 703, 3, 18},
  {cont__77_67, &frame__77_1_create_imports, 704, 704, 3, 15},
  {cont__77_68, &frame__77_1_create_imports, 705, 705, 22, 42},
  {cont__77_69, &frame__77_1_create_imports, 705, 705, 22, 45},
  {cont__77_70, &frame__77_1_create_imports, 705, 705, 48, 48},
  {cont__77_71, &frame__77_1_create_imports, 705, 705, 9, 49},
  {cont__77_72, &frame__77_1_create_imports, 705, 705, 3, 49},
  {cont__77_73, &frame__77_1_create_imports, 706, 706, 3, 59},
  {entry__78_3, NULL, 709, 709, 32, 67},
  {entry__78_7, NULL, 711, 712, 5, 57},
  {entry__78_1_compile_exe, NULL, 709, 709, 6, 29},
  {cont__78_2, &frame__78_1_compile_exe, 709, 709, 3, 67},
  {cont__78_5, &frame__78_1_compile_exe, 710, 710, 10, 42},
  {cont__78_6, &frame__78_1_compile_exe, 710, 712, 3, 58},
  {cont__78_9, &frame__78_1_compile_exe, 714, 714, 3, 53},
  {cont__78_10, &frame__78_1_compile_exe, 715, 715, 46, 46},
  {cont__78_11, &frame__78_1_compile_exe, 715, 715, 3, 47},
  {cont__78_12, &frame__78_1_compile_exe, 716, 716, 3, 28},
  {cont__78_13, &frame__78_1_compile_exe, 716, 716, 28, 28},
  {entry__79_2, NULL, 721, 721, 11, 29},
  {cont__79_3, &frame__79_2, 721, 721, 5, 29},
  {cont__79_4, &frame__79_2, 721, 721, 29, 29},
  {entry__79_1_dump_source_or_check, NULL, 719, 721, 3, 29},
  {entry__80_4, NULL, 725, 725, 41, 65},
  {cont__80_5, &frame__80_4, 725, 725, 34, 75},
  {cont__80_6, &frame__80_4, 725, 725, 75, 75},
  {entry__80_8, NULL, 727, 727, 48, 57},
  {cont__80_9, &frame__80_8, 727, 727, 59, 68},
  {cont__80_10, &frame__80_8, 727, 727, 7, 69},
  {cont__80_11, &frame__80_8, 728, 728, 13, 31},
  {cont__80_12, &frame__80_8, 728, 728, 7, 31},
  {cont__80_13, &frame__80_8, 728, 728, 31, 31},
  {entry__80_15, NULL, 729, 729, 28, 50},
  {entry__80_18, NULL, 731, 731, 24, 59},
  {entry__80_2, NULL, 725, 725, 8, 31},
  {cont__80_3, &frame__80_2, 725, 725, 5, 75},
  {cont__80_7, &frame__80_2, 726, 728, 5, 31},
  {cont__80_14, &frame__80_2, 729, 729, 5, 50},
  {cont__80_16, &frame__80_2, 730, 730, 5, 15},
  {cont__80_17, &frame__80_2, 731, 731, 5, 59},
  {entry__80_1_print_c, NULL, 724, 731, 3, 59},
  {entry__81_5, NULL, 740, 740, 9, 43},
  {cont__81_6, &frame__81_5, 741, 741, 12, 28},
  {cont__81_7, &frame__81_5, 741, 741, 9, 34},
  {cont__81_8, &frame__81_5, 742, 742, 9, 21},
  {cont__81_9, &frame__81_5, 743, 743, 9, 64},
  {cont__81_10, &frame__81_5, 744, 744, 12, 23},
  {cont__81_11, &frame__81_5, 744, 744, 9, 29},
  {cont__81_12, &frame__81_5, 745, 745, 22, 22},
  {entry__81_4, NULL, 739, 745, 7, 22},
  {cont__81_13, &frame__81_4, 745, 745, 22, 22},
  {entry__81_3, NULL, 738, 745, 5, 23},
  {entry__81_17, NULL, 749, 749, 19, 65},
  {entry__81_16, NULL, 749, 749, 7, 65},
  {cont__81_19, &frame__81_16, 750, 750, 63, 63},
  {cont__81_20, &frame__81_16, 750, 750, 37, 64},
  {cont__81_21, &frame__81_16, 750, 750, 7, 64},
  {cont__81_22, &frame__81_16, 750, 750, 64, 64},
  {entry__81_25, NULL, 753, 753, 21, 66},
  {entry__81_24, NULL, 753, 753, 9, 66},
  {cont__81_26, &frame__81_24, 754, 754, 9, 44},
  {entry__81_23, NULL, 752, 754, 7, 44},
  {cont__81_27, &frame__81_23, 755, 755, 7, 32},
  {cont__81_29, &frame__81_23, 756, 756, 7, 32},
  {cont__81_31, &frame__81_23, 757, 757, 7, 34},
  {entry__81_35, NULL, 760, 760, 5, 40},
  {cont__81_36, &frame__81_35, 761, 761, 5, 32},
  {cont__81_37, &frame__81_35, 762, 762, 5, 20},
  {entry__81_1_list_dependencies, NULL, 734, 734, 3, 80},
  {cont__81_2, &frame__81_1_list_dependencies, 735, 745, 3, 24},
  {cont__81_14, &frame__81_1_list_dependencies, 747, 747, 5, 28},
  {cont__81_15, &frame__81_1_list_dependencies, 746, 757, 3, 35},
  {cont__81_33, &frame__81_1_list_dependencies, 758, 758, 3, 29},
  {cont__81_34, &frame__81_1_list_dependencies, 759, 762, 3, 20},
  {entry__82_7, NULL, 769, 770, 14, 58},
  {cont__82_10, &frame__82_7, 769, 770, 7, 58},
  {entry__82_12, NULL, 771, 771, 17, 73},
  {entry__82_34, NULL, 803, 805, 21, 49},
  {cont__82_37, &frame__82_34, 803, 805, 7, 49},
  {cont__82_38, &frame__82_34, 805, 805, 50, 50},
  {entry__82_48, NULL, 825, 825, 7, 42},
  {cont__82_49, &frame__82_48, 826, 826, 7, 34},
  {cont__82_50, &frame__82_48, 827, 832, 21, 23},
  {cont__82_53, &frame__82_48, 827, 832, 7, 23},
  {cont__82_54, &frame__82_48, 832, 832, 24, 24},
  {entry__82_2, NULL, 766, 766, 5, 55},
  {cont__82_4, &frame__82_2, 767, 767, 5, 31},
  {cont__82_5, &frame__82_2, 768, 768, 8, 22},
  {cont__82_6, &frame__82_2, 768, 770, 5, 59},
  {cont__82_11, &frame__82_2, 771, 771, 5, 73},
  {cont__82_14, &frame__82_2, 772, 772, 5, 40},
  {cont__82_15, &frame__82_2, 773, 773, 5, 18},
  {cont__82_16, &frame__82_2, 774, 774, 49, 49},
  {cont__82_17, &frame__82_2, 774, 774, 15, 50},
  {cont__82_18, &frame__82_2, 774, 774, 5, 74},
  {cont__82_19, &frame__82_2, 775, 775, 5, 31},
  {cont__82_20, &frame__82_2, 776, 776, 30, 73},
  {cont__82_21, &frame__82_2, 776, 776, 5, 78},
  {cont__82_22, &frame__82_2, 777, 777, 5, 33},
  {cont__82_24, &frame__82_2, 778, 778, 5, 61},
  {cont__82_27, &frame__82_2, 779, 779, 5, 25},
  {cont__82_28, &frame__82_2, 781, 801, 19, 22},
  {cont__82_32, &frame__82_2, 781, 801, 5, 22},
  {cont__82_33, &frame__82_2, 802, 805, 5, 50},
  {cont__82_39, &frame__82_2, 806, 823, 19, 21},
  {cont__82_46, &frame__82_2, 806, 823, 5, 21},
  {cont__82_47, &frame__82_2, 824, 832, 5, 24},
  {cont__82_55, &frame__82_2, 833, 839, 5, 32},
  {cont__82_57, &frame__82_2, 840, 840, 5, 25},
  {entry__82_1_build_codeblocks_project, NULL, 765, 840, 3, 25},
  {entry__83_4, NULL, 843, 843, 26, 56},
  {entry__83_7, NULL, 847, 847, 7, 41},
  {entry__83_12, NULL, 853, 853, 29, 50},
  {cont__83_13, &frame__83_12, 853, 853, 29, 55},
  {cont__83_14, &frame__83_12, 853, 853, 9, 56},
  {cont__83_15, &frame__83_12, 854, 854, 9, 47},
  {cont__83_16, &frame__83_12, 854, 854, 47, 47},
  {entry__83_21, NULL, 861, 861, 53, 66},
  {cont__83_22, &frame__83_21, 861, 861, 14, 67},
  {cont__83_24, &frame__83_21, 861, 861, 11, 67},
  {entry__83_25, NULL, 863, 863, 53, 67},
  {cont__83_27, &frame__83_25, 863, 863, 14, 68},
  {cont__83_28, &frame__83_25, 863, 863, 11, 68},
  {entry__83_29, NULL, 865, 865, 53, 69},
  {cont__83_31, &frame__83_29, 865, 865, 14, 70},
  {cont__83_32, &frame__83_29, 865, 865, 11, 70},
  {entry__83_33, NULL, 866, 866, 14, 50},
  {cont__83_35, &frame__83_33, 866, 866, 11, 50},
  {entry__83_39, NULL, 868, 868, 19, 56},
  {entry__83_48, NULL, 875, 875, 38, 63},
  {cont__83_49, &frame__83_48, 875, 875, 13, 63},
  {cont__83_50, &frame__83_48, 875, 875, 13, 63},
  {entry__83_52, NULL, 877, 877, 25, 25},
  {entry__83_45, NULL, 871, 871, 9, 32},
  {cont__83_46, &frame__83_45, 874, 874, 13, 29},
  {cont__83_47, &frame__83_45, 873, 875, 11, 62},
  {cont__83_51, &frame__83_45, 872, 877, 9, 26},
  {entry__83_55, NULL, 879, 879, 21, 54},
  {entry__83_65, NULL, 889, 889, 35, 47},
  {cont__83_66, &frame__83_65, 889, 889, 29, 47},
  {entry__83_59, NULL, 885, 885, 15, 76},
  {cont__83_61, &frame__83_59, 886, 886, 15, 43},
  {cont__83_62, &frame__83_59, 883, 888, 13, 26},
  {cont__83_64, &frame__83_59, 889, 889, 13, 47},
  {entry__83_72, NULL, 897, 897, 35, 47},
  {cont__83_73, &frame__83_72, 897, 897, 29, 47},
  {entry__83_67, NULL, 893, 893, 15, 43},
  {cont__83_68, &frame__83_67, 894, 894, 15, 30},
  {cont__83_70, &frame__83_67, 891, 896, 13, 26},
  {cont__83_71, &frame__83_67, 897, 897, 13, 47},
  {entry__83_81, NULL, 908, 908, 35, 47},
  {cont__83_82, &frame__83_81, 908, 908, 29, 47},
  {entry__83_74, NULL, 901, 903, 15, 23},
  {cont__83_76, &frame__83_74, 904, 904, 15, 43},
  {cont__83_77, &frame__83_74, 905, 905, 15, 30},
  {cont__83_78, &frame__83_74, 899, 907, 13, 26},
  {cont__83_80, &frame__83_74, 908, 908, 13, 47},
  {entry__83_86, NULL, 915, 915, 35, 47},
  {cont__83_87, &frame__83_86, 915, 915, 29, 47},
  {entry__83_83, NULL, 912, 912, 15, 43},
  {cont__83_84, &frame__83_83, 910, 914, 13, 26},
  {cont__83_85, &frame__83_83, 915, 915, 13, 47},
  {entry__83_54, NULL, 879, 879, 9, 54},
  {cont__83_57, &frame__83_54, 881, 881, 11, 28},
  {cont__83_58, &frame__83_54, 880, 915, 9, 48},
  {entry__83_8, NULL, 851, 851, 7, 56},
  {cont__83_10, &frame__83_8, 852, 852, 10, 38},
  {cont__83_11, &frame__83_8, 852, 854, 7, 47},
  {cont__83_17, &frame__83_8, 855, 855, 56, 56},
  {cont__83_18, &frame__83_8, 855, 855, 7, 57},
  {cont__83_19, &frame__83_8, 859, 859, 11, 28},
  {cont__83_20, &frame__83_8, 857, 866, 7, 51},
  {cont__83_38, &frame__83_8, 868, 868, 7, 56},
  {cont__83_41, &frame__83_8, 869, 869, 63, 63},
  {cont__83_42, &frame__83_8, 869, 869, 37, 64},
  {cont__83_43, &frame__83_8, 869, 869, 7, 64},
  {cont__83_44, &frame__83_8, 870, 877, 7, 27},
  {cont__83_53, &frame__83_8, 878, 915, 7, 49},
  {entry__83_1_build_library, NULL, 843, 843, 6, 23},
  {cont__83_3, &frame__83_1_build_library, 843, 843, 3, 56},
  {cont__83_6, &frame__83_1_build_library, 845, 915, 3, 51},
  {cont__83_88, &frame__83_1_build_library, 915, 915, 51, 51},
  {entry__84_6, NULL, 922, 923, 11, 42},
  {cont__84_9, &frame__84_6, 922, 923, 5, 42},
  {entry__84_13, NULL, 928, 928, 38, 65},
  {cont__84_14, &frame__84_13, 928, 928, 7, 34},
  {cont__84_15, &frame__84_13, 928, 928, 7, 65},
  {cont__84_16, &frame__84_13, 928, 928, 7, 65},
  {entry__84_19, NULL, 930, 930, 28, 65},
  {cont__84_21, &frame__84_19, 930, 930, 19, 65},
  {entry__84_18, NULL, 930, 930, 7, 65},
  {cont__84_22, &frame__84_18, 931, 931, 7, 37},
  {entry__84_1_maybe_compile_c_file, NULL, 918, 918, 3, 35},
  {cont__84_2, &frame__84_1_maybe_compile_c_file, 919, 919, 3, 35},
  {cont__84_3, &frame__84_1_maybe_compile_c_file, 920, 920, 3, 26},
  {cont__84_4, &frame__84_1_maybe_compile_c_file, 921, 921, 6, 24},
  {cont__84_5, &frame__84_1_maybe_compile_c_file, 921, 923, 3, 43},
  {cont__84_10, &frame__84_1_maybe_compile_c_file, 924, 924, 3, 26},
  {cont__84_11, &frame__84_1_maybe_compile_c_file, 927, 927, 7, 25},
  {cont__84_12, &frame__84_1_maybe_compile_c_file, 926, 928, 5, 64},
  {cont__84_17, &frame__84_1_maybe_compile_c_file, 925, 931, 3, 38},
  {entry__86_11, NULL, 947, 947, 39, 41},
  {cont__86_12, &frame__86_11, 947, 947, 36, 41},
  {cont__86_13, &frame__86_11, 947, 947, 28, 43},
  {cont__86_15, &frame__86_11, 947, 947, 21, 48},
  {cont__86_16, &frame__86_11, 947, 947, 48, 48},
  {entry__86_6, NULL, 946, 946, 13, 26},
  {cont__86_7, &frame__86_6, 946, 946, 9, 28},
  {cont__86_8, &frame__86_6, 947, 947, 16, 18},
  {cont__86_9, &frame__86_6, 947, 947, 12, 18},
  {cont__86_10, &frame__86_6, 947, 947, 9, 48},
  {cont__86_17, &frame__86_6, 948, 948, 9, 13},
  {entry__86_4, NULL, 945, 945, 10, 19},
  {cont__86_5, &frame__86_4, 945, 948, 7, 13},
  {entry__86_3, NULL, 944, 948, 5, 14},
  {cont__86_18, &frame__86_3, 948, 948, 14, 14},
  {entry__86_21, NULL, 951, 951, 27, 30},
  {cont__86_22, &frame__86_21, 951, 951, 19, 31},
  {cont__86_24, &frame__86_21, 951, 951, 7, 31},
  {cont__86_25, &frame__86_21, 951, 951, 31, 31},
  {entry__86_28, NULL, 953, 953, 33, 36},
  {cont__86_29, &frame__86_28, 953, 953, 33, 38},
  {cont__86_30, &frame__86_28, 953, 953, 33, 39},
  {cont__86_31, &frame__86_28, 953, 953, 18, 39},
  {cont__86_32, &frame__86_28, 953, 953, 39, 39},
  {entry__86_26, NULL, 953, 953, 10, 15},
  {cont__86_27, &frame__86_26, 953, 953, 7, 39},
  {entry__86_1_format_number, NULL, 941, 941, 3, 16},
  {cont__86_2, &frame__86_1_format_number, 943, 948, 3, 15},
  {cont__86_19, &frame__86_1_format_number, 950, 950, 5, 10},
  {cont__86_20, &frame__86_1_format_number, 949, 953, 3, 40},
  {cont__86_33, &frame__86_1_format_number, 954, 954, 3, 8},
  {entry__87_4, NULL, 960, 960, 37, 37},
  {cont__87_5, &frame__87_4, 960, 960, 7, 37},
  {cont__87_6, &frame__87_4, 966, 966, 20, 41},
  {cont__87_7, &frame__87_4, 966, 966, 17, 41},
  {cont__87_8, &frame__87_4, 966, 966, 9, 42},
  {cont__87_9, &frame__87_4, 967, 967, 23, 29},
  {cont__87_10, &frame__87_4, 967, 967, 9, 34},
  {cont__87_11, &frame__87_4, 961, 968, 7, 12},
  {entry__87_13, NULL, 970, 970, 47, 53},
  {cont__87_14, &frame__87_13, 970, 970, 33, 58},
  {cont__87_15, &frame__87_13, 970, 970, 7, 63},
  {entry__87_1_sim2c__write_timing_info, NULL, 957, 957, 3, 23},
  {cont__87_2, &frame__87_1_sim2c__write_timing_info, 959, 959, 5, 23},
  {cont__87_3, &frame__87_1_sim2c__write_timing_info, 958, 970, 3, 64},
  {cont__87_17, &frame__87_1_sim2c__write_timing_info, 971, 971, 3, 19},
  {cont__87_18, &frame__87_1_sim2c__write_timing_info, 971, 971, 19, 19},
  {entry__88_5, NULL, 987, 987, 12, 38},
  {cont__88_7, &frame__88_5, 987, 987, 9, 38},
  {entry__88_8, NULL, 988, 988, 9, 23},
  {entry__88_10, NULL, 990, 990, 17, 57},
  {entry__88_20, NULL, 1001, 1001, 42, 69},
  {cont__88_21, &frame__88_20, 1001, 1001, 9, 38},
  {cont__88_22, &frame__88_20, 1001, 1001, 9, 69},
  {cont__88_23, &frame__88_20, 1001, 1001, 9, 69},
  {entry__88_18, NULL, 1000, 1000, 9, 27},
  {cont__88_19, &frame__88_18, 1001, 1001, 9, 69},
  {cont__88_24, &frame__88_18, },
  {entry__88_29, NULL, 1004, 1004, 21, 61},
  {entry__88_32, NULL, 1005, 1005, 41, 59},
  {cont__88_33, &frame__88_32, 1005, 1005, 35, 64},
  {entry__88_35, NULL, 1006, 1006, 32, 54},
  {entry__88_39, NULL, 1008, 1008, 28, 64},
  {entry__88_43, NULL, 1010, 1010, 28, 67},
  {entry__88_26, NULL, 1003, 1003, 55, 67},
  {cont__88_27, &frame__88_26, 1003, 1003, 9, 67},
  {cont__88_28, &frame__88_26, 1004, 1004, 9, 61},
  {cont__88_31, &frame__88_26, 1005, 1005, 9, 64},
  {cont__88_34, &frame__88_26, 1006, 1006, 9, 54},
  {cont__88_36, &frame__88_26, 1007, 1007, 25, 37},
  {cont__88_37, &frame__88_26, 1007, 1007, 9, 37},
  {cont__88_38, &frame__88_26, 1008, 1008, 9, 64},
  {cont__88_41, &frame__88_26, 1009, 1009, 9, 39},
  {cont__88_42, &frame__88_26, 1010, 1010, 9, 67},
  {cont__88_45, &frame__88_26, 1010, 1010, 67, 67},
  {entry__88_50, NULL, 1017, 1017, 44, 71},
  {cont__88_51, &frame__88_50, 1017, 1017, 13, 40},
  {cont__88_52, &frame__88_50, 1017, 1017, 13, 71},
  {cont__88_53, &frame__88_50, 1017, 1017, 13, 71},
  {entry__88_55, NULL, 1019, 1019, 13, 43},
  {entry__88_56, NULL, 1021, 1021, 13, 64},
  {cont__88_57, &frame__88_56, 1021, 1021, 64, 64},
  {entry__88_46, NULL, 1012, 1012, 9, 30},
  {cont__88_47, &frame__88_46, 1013, 1013, 9, 32},
  {cont__88_48, &frame__88_46, 1016, 1016, 13, 31},
  {cont__88_49, &frame__88_46, 1015, 1017, 11, 70},
  {cont__88_54, &frame__88_46, 1014, 1021, 9, 65},
  {entry__88_65, NULL, 1026, 1026, 11, 39},
  {entry__88_60, NULL, 1025, 1025, 9, 62},
  {cont__88_64, &frame__88_60, 1024, 1026, 7, 40},
  {entry__88_72, NULL, 1034, 1034, 38, 63},
  {cont__88_73, &frame__88_72, 1034, 1034, 13, 63},
  {cont__88_74, &frame__88_72, 1034, 1034, 13, 63},
  {entry__88_70, NULL, 1033, 1033, 13, 45},
  {cont__88_71, &frame__88_70, 1032, 1034, 11, 62},
  {cont__88_75, &frame__88_70, 1032, 1034, 11, 62},
  {entry__88_77, NULL, 1036, 1036, 23, 23},
  {entry__88_67, NULL, 1028, 1028, 7, 30},
  {cont__88_68, &frame__88_67, 1031, 1031, 11, 27},
  {cont__88_69, &frame__88_67, 1030, 1034, 9, 63},
  {cont__88_76, &frame__88_67, 1029, 1036, 7, 24},
  {entry__88_81, NULL, 1039, 1039, 28, 75},
  {cont__88_83, &frame__88_81, 1039, 1039, 75, 75},
  {entry__88_86, NULL, 1042, 1042, 23, 58},
  {entry__88_93, NULL, 1050, 1050, 33, 45},
  {cont__88_94, &frame__88_93, 1050, 1050, 27, 45},
  {entry__88_85, NULL, 1042, 1042, 11, 58},
  {cont__88_88, &frame__88_85, 1043, 1049, 11, 24},
  {cont__88_92, &frame__88_85, 1050, 1050, 11, 45},
  {entry__88_96, NULL, 1052, 1052, 23, 51},
  {entry__88_101, NULL, 1057, 1057, 18, 40},
  {cont__88_103, &frame__88_101, 1057, 1057, 15, 40},
  {entry__88_104, NULL, 1058, 1058, 18, 33},
  {cont__88_105, &frame__88_104, 1058, 1058, 15, 33},
  {entry__88_108, NULL, 1061, 1061, 33, 45},
  {cont__88_109, &frame__88_108, 1061, 1061, 27, 45},
  {entry__88_95, NULL, 1052, 1052, 11, 51},
  {cont__88_98, &frame__88_95, 1056, 1056, 15, 32},
  {cont__88_99, &frame__88_95, 1056, 1056, 15, 43},
  {cont__88_100, &frame__88_95, 1055, 1058, 13, 32},
  {cont__88_106, &frame__88_95, 1053, 1060, 11, 24},
  {cont__88_107, &frame__88_95, 1061, 1061, 11, 45},
  {entry__88_79, NULL, 1038, 1038, 7, 52},
  {cont__88_80, &frame__88_79, 1039, 1039, 7, 75},
  {cont__88_84, &frame__88_79, 1040, 1061, 7, 46},
  {entry__88_113, NULL, 1063, 1063, 24, 41},
  {cont__88_114, &frame__88_113, 1063, 1063, 24, 41},
  {entry__88_118, NULL, 1067, 1067, 11, 25},
  {entry__88_119, NULL, 1068, 1068, 14, 38},
  {cont__88_120, &frame__88_119, 1068, 1068, 11, 38},
  {entry__88_116, NULL, 1066, 1066, 11, 39},
  {cont__88_117, &frame__88_116, 1065, 1068, 9, 37},
  {cont__88_121, &frame__88_116, 1064, 1071, 7, 44},
  {entry__88_2, NULL, 986, 986, 9, 26},
  {cont__88_3, &frame__88_2, 986, 986, 9, 38},
  {cont__88_4, &frame__88_2, 984, 988, 5, 24},
  {cont__88_9, &frame__88_2, 990, 990, 5, 57},
  {cont__88_12, &frame__88_2, 991, 991, 5, 41},
  {cont__88_13, &frame__88_2, 992, 992, 5, 41},
  {cont__88_14, &frame__88_2, 993, 993, 5, 33},
  {cont__88_15, &frame__88_2, 994, 994, 5, 28},
  {cont__88_16, &frame__88_2, 996, 996, 5, 24},
  {cont__88_17, &frame__88_2, },
  {cont__88_25, &frame__88_2, 997, 1021, 5, 67},
  {cont__88_58, &frame__88_2, 1022, 1022, 5, 50},
  {cont__88_59, &frame__88_2, 1023, 1026, 5, 41},
  {cont__88_66, &frame__88_2, 1027, 1036, 5, 25},
  {cont__88_78, &frame__88_2, 1037, 1061, 5, 47},
  {cont__88_110, &frame__88_2, 1062, 1062, 41, 41},
  {cont__88_111, &frame__88_2, 1062, 1062, 5, 42},
  {cont__88_112, &frame__88_2, 1063, 1063, 8, 41},
  {cont__88_115, &frame__88_2, 1063, 1071, 5, 45},
  {entry__88_1_build_executable, NULL, 983, 1071, 3, 46},
  {entry__103_2, NULL, 105, 105, 8, 28},
  {cont__103_3, &frame__103_2, 105, 105, 5, 28},
  {entry__103_4, NULL, 108, 108, 9, 48},
  {cont__103_6, &frame__103_4, 109, 109, 9, 42},
  {cont__103_8, &frame__103_4, 107, 109, 7, 41},
  {cont__103_9, &frame__103_4, 106, 109, 5, 43},
  {entry__104_2, NULL, 114, 114, 8, 29},
  {cont__104_3, &frame__104_2, 114, 114, 5, 29},
  {entry__104_4, NULL, 117, 117, 9, 48},
  {cont__104_5, &frame__104_4, 118, 118, 9, 42},
  {cont__104_6, &frame__104_4, 116, 118, 7, 41},
  {cont__104_7, &frame__104_4, 115, 118, 5, 43},
  {entry__108_4, NULL, 138, 138, 7, 41},
  {cont__108_5, &frame__108_4, 139, 139, 10, 26},
  {cont__108_6, &frame__108_4, 139, 139, 7, 32},
  {cont__108_7, &frame__108_4, 140, 140, 7, 19},
  {cont__108_8, &frame__108_4, 141, 141, 7, 34},
  {cont__108_9, &frame__108_4, 142, 142, 10, 21},
  {cont__108_10, &frame__108_4, 142, 142, 7, 27},
  {cont__108_11, &frame__108_4, 143, 143, 20, 20},
  {entry__108_3, NULL, 137, 143, 5, 20},
  {cont__108_12, &frame__108_3, 143, 143, 20, 20},
  {entry__108_1, NULL, 134, 134, 3, 31},
  {cont__108_2, &frame__108_1, 136, 143, 3, 21},
  {entry__133_4, NULL, 170, 170, 41, 79},
  {entry__133_2, NULL, 170, 170, 8, 38},
  {cont__133_3, &frame__133_2, 170, 170, 5, 79},
  {cont__133_6, &frame__133_2, 171, 171, 5, 45},
  {cont__133_7, &frame__133_2, 171, 171, 45, 45},
  {entry__133_9, NULL, 177, 178, 7, 52},
  {entry__133_12, NULL, 180, 181, 7, 34},
  {entry__133_15, NULL, 183, 184, 7, 57},
  {entry__133_18, NULL, 186, 187, 7, 71},
  {entry__133_21, NULL, 189, 190, 7, 47},
  {entry__133_24, NULL, 192, 193, 7, 61},
  {entry__133_27, NULL, 195, 198, 9, 29},
  {entry__133_30, NULL, 202, 203, 7, 33},
  {entry__133_33, NULL, 205, 206, 7, 29},
  {entry__133_36, NULL, 208, 209, 7, 35},
  {entry__133_39, NULL, 211, 212, 7, 40},
  {entry__133_42, NULL, 214, 215, 9, 65},
  {entry__133_45, NULL, 219, 220, 7, 35},
  {entry__133_48, NULL, 222, 223, 7, 45},
  {entry__133_51, NULL, 225, 226, 9, 31},
  {entry__133_54, NULL, 230, 231, 7, 32},
  {entry__133_57, NULL, 233, 234, 7, 33},
  {entry__133_60, NULL, 236, 237, 7, 43},
  {entry__133_63, NULL, 239, 240, 7, 29},
  {entry__133_66, NULL, 242, 243, 7, 46},
  {entry__133_8, NULL, 173, 243, 5, 47},
  {cont__133_69, &frame__133_8, 243, 243, 48, 48},
  {entry__137_1, NULL, 247, 247, 37, 37},
  {entry__146_1, NULL, 279, 279, 29, 39},
  {cont__146_3, &frame__146_1, 279, 279, 3, 39},
  {cont__146_4, &frame__146_1, 279, 279, 39, 39},
  {entry__165_2, NULL, 627, 628, 9, 51},
  {cont__165_5, &frame__165_2, 627, 628, 3, 51},
  {entry__180_1, NULL, 1073, 1073, 20, 36},
  {cont__180_2, &frame__180_1, 1073, 1073, 36, 36},
  {entry__181_4, NULL, 1080, 1080, 7, 32},
  {entry__181_3, NULL, },
  {cont__181_5, &frame__181_3, },
  {entry__181_2, NULL, },
  {cont__181_6, &frame__181_2, },
  {entry__181_1, NULL, },
  {cont__181_7, &frame__181_1, 1075, 1081, 3, 24},
  {entry__181_8, NULL, 1082, 1082, 3, 23},
  {entry__181_9, NULL, 1083, 1083, 3, 43},
  {entry__181_10, NULL, 1084, 1084, 3, 57},
  {entry__181_11, NULL, 1085, 1085, 6, 29},
  {cont__181_12, &frame__181_11, 1085, 1085, 3, 43}
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
  allocate_initialized_frame_gc(0, 7);
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
  arguments->slots[0] = string__92_1;
  result_count = 0;
  myself = get__copyright();
  func = myself->type;
  frame->cont = cont__92_2;
}
static void cont__92_2(void) {
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
  frame->cont = cont__93_1;
}
static void cont__93_1(void) {
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
  frame->cont = cont__94_1;
}
static void cont__94_1(void) {
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
  frame->cont = cont__95_1;
}
static void cont__95_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._REVISION, arguments->slots[0]);
  // 95: $VERSION "@(MAJOR).@(MINOR).@(REVISION).@(BUILD)"
  argument_count = 7;
  arguments = node_p;
  arguments->slots[0] = var._MAJOR;
  arguments->slots[1] = string__97_1;
  arguments->slots[2] = var._MINOR;
  arguments->slots[3] = string__97_1;
  arguments->slots[4] = var._REVISION;
  arguments->slots[5] = string__97_1;
  arguments->slots[6] = var._BUILD;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__97_2;
}
static void cont__97_2(void) {
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
  frame->cont = cont__98_1;
}
static void cont__98_1(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 97: extern $gcc "gcc"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__99_1;
  result_count = 1;
  myself = get__extern();
  func = myself->type;
  frame->cont = cont__99_2;
}
static void cont__99_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._gcc, arguments->slots[0]);
  // 98: extern $mkdir "mkdir" # would be nice to have one in the system library!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__100_1;
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
  initialize_future(var._mkdir, arguments->slots[0]);
  // 99: $SIMLIBPATH environment("SIMLIBPATH")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__101_1;
  result_count = 1;
  myself = get__environment();
  func = myself->type;
  frame->cont = cont__101_2;
}
static void cont__101_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._SIMLIBPATH, arguments->slots[0]);
  // 100: $SIMDATAPATH environment("SIMDATAPATH")
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
  initialize_future(var._SIMDATAPATH, arguments->slots[0]);
  // 104: SIMLIBPATH.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._SIMLIBPATH;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__103_1;
}
static void cont__103_1(void) {
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
  arguments->slots[1] = func__103_2;
  arguments->slots[2] = func__103_4;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__103_10;
}
static void entry__103_2(void) {
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
  frame->cont = cont__103_3;
}
static void cont__103_3(void) {
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
static void entry__103_4(void) {
  allocate_initialized_frame_gc(0, 3);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 108: "/usr/local/share/simplicity-@(VERSION)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__103_5;
  arguments->slots[1] = var._VERSION;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__103_6;
}
static void cont__103_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 109: "/usr/share/simplicity-@(VERSION)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__103_7;
  arguments->slots[1] = var._VERSION;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__103_8;
}
static void cont__103_8(void) {
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
  frame->cont = cont__103_9;
}
static void cont__103_9(void) {
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
static void cont__103_10(void) {
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
  frame->cont = cont__104_1;
}
static void cont__104_1(void) {
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
  arguments->slots[1] = func__104_2;
  arguments->slots[2] = func__104_4;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__104_8;
}
static void entry__104_2(void) {
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
  frame->cont = cont__104_3;
}
static void cont__104_3(void) {
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
static void entry__104_4(void) {
  allocate_initialized_frame_gc(0, 3);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 117: "/usr/local/share/simplicity-@(VERSION)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__103_5;
  arguments->slots[1] = var._VERSION;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__104_5;
}
static void cont__104_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 118: "/usr/share/simplicity-@(VERSION)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__103_7;
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
  frame->cont = cont__104_7;
}
static void cont__104_7(void) {
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
static void cont__104_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._simdatapaths, arguments->slots[0]);
  // 124: "bsd" = "posix"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__106_1;
  arguments->slots[1] = string__106_2;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__106_3;
}
static void cont__106_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 125: "cygwin" = "posix"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__83_36;
  arguments->slots[1] = string__106_2;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__106_4;
}
static void cont__106_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 126: "darwin" = "posix"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__83_37;
  arguments->slots[1] = string__106_2;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__106_5;
}
static void cont__106_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 127: "linux" = "posix"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__76_23;
  arguments->slots[1] = string__106_2;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__106_6;
}
static void cont__106_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 128: "posix" = "all"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__106_2;
  arguments->slots[1] = string__106_7;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__106_8;
}
static void cont__106_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 129: "win" = "all"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__106_9;
  arguments->slots[1] = string__106_7;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__106_10;
}
static void cont__106_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 130: "all" = NONE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__106_7;
  arguments->slots[1] = var._NONE;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__106_11;
}
static void cont__106_11(void) {
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
  frame->cont = cont__106_12;
}
static void cont__106_12(void) {
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
  arguments->slots[0] = func__108_1;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__108_13;
}
static void entry__108_3(void) {
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
  frame->slots[3] /* temp__1 */ = create_closure(entry__108_4, 0);
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
  frame->cont = cont__108_12;
}
static void entry__108_4(void) {
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
  frame->cont = cont__108_5;
}
static void cont__108_5(void) {
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
  frame->cont = cont__108_6;
}
static void cont__108_6(void) {
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
  frame->cont = cont__108_7;
}
static void cont__108_7(void) {
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
  frame->cont = cont__108_8;
}
static void cont__108_8(void) {
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
  frame->cont = cont__108_9;
}
static void cont__108_9(void) {
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
  frame->cont = cont__108_10;
}
static void cont__108_10(void) {
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
  frame->cont = cont__108_11;
}
static void cont__108_11(void) {
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
static void cont__108_12(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__108_1(void) {
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
  frame->cont = cont__108_2;
}
static void cont__108_2(void) {
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
  frame->slots[2] /* temp__1 */ = create_closure(entry__108_3, 0);
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
static void cont__108_13(void) {
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
  frame->cont = cont__132_1;
}
static void cont__132_1(void) {
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
  frame->cont = cont__132_2;
}
static void cont__132_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._action, arguments->slots[0]);
  // 169: action == "simrun"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._action;
  arguments->slots[1] = string__83_2;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__133_1;
}
static void cont__133_1(void) {
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
  arguments->slots[1] = func__133_2;
  arguments->slots[2] = func__133_8;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__133_70;
}
static void entry__133_2(void) {
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
  frame->cont = cont__133_3;
}
static void cont__133_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 170: if command_line_arguments.is_empty: Error "Missing command line arguments!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__133_4;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__133_6;
}
static void entry__133_4(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 170: ... Error "Missing command line arguments!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__133_5;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__133_6(void) {
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
  frame->cont = cont__133_7;
}
static void cont__133_7(void) {
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
static void entry__133_8(void) {
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
  arguments->slots[0] = func__133_9;
  arguments->slots[1] = func__133_12;
  arguments->slots[2] = func__133_15;
  arguments->slots[3] = func__133_18;
  arguments->slots[4] = func__133_21;
  arguments->slots[5] = func__133_24;
  arguments->slots[6] = func__133_27;
  arguments->slots[7] = func__133_30;
  arguments->slots[8] = func__133_33;
  arguments->slots[9] = func__133_36;
  arguments->slots[10] = func__133_39;
  arguments->slots[11] = func__133_42;
  arguments->slots[12] = func__133_45;
  arguments->slots[13] = func__133_48;
  arguments->slots[14] = func__133_51;
  arguments->slots[15] = func__133_54;
  arguments->slots[16] = func__133_57;
  arguments->slots[17] = func__133_60;
  arguments->slots[18] = func__133_63;
  arguments->slots[19] = func__133_66;
  result_count = 20;
  myself = get__program_parameters();
  func = myself->type;
  frame->cont = cont__133_69;
}
static void entry__133_9(void) {
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
  arguments->slots[0] = string__133_10;
  arguments->slots[1] = string__133_11;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__133_12(void) {
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
  arguments->slots[0] = string__133_13;
  arguments->slots[1] = string__133_14;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__133_15(void) {
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
  arguments->slots[0] = string__133_16;
  arguments->slots[1] = string__133_17;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__133_18(void) {
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
  arguments->slots[0] = string__133_19;
  arguments->slots[1] = string__133_20;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__133_21(void) {
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
  arguments->slots[0] = string__133_22;
  arguments->slots[1] = string__133_23;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__133_24(void) {
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
  arguments->slots[0] = string__133_25;
  arguments->slots[1] = string__133_26;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__133_27(void) {
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
  arguments->slots[1] = string__133_28;
  arguments->slots[2] = string__133_29;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__133_30(void) {
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
  arguments->slots[0] = string__133_31;
  arguments->slots[1] = string__133_32;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__133_33(void) {
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
  arguments->slots[0] = string__133_34;
  arguments->slots[1] = string__133_35;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__133_36(void) {
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
  arguments->slots[0] = string__133_37;
  arguments->slots[1] = string__133_38;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__133_39(void) {
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
  arguments->slots[0] = string__133_40;
  arguments->slots[1] = string__133_41;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__133_42(void) {
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
  arguments->slots[0] = string__133_43;
  arguments->slots[1] = string__133_44;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__133_45(void) {
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
  arguments->slots[0] = string__133_46;
  arguments->slots[1] = string__133_47;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__133_48(void) {
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
  arguments->slots[0] = string__133_49;
  arguments->slots[1] = string__133_50;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__133_51(void) {
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
  arguments->slots[0] = string__133_52;
  arguments->slots[1] = string__133_53;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__133_54(void) {
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
  arguments->slots[0] = string__133_55;
  arguments->slots[1] = string__133_56;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__133_57(void) {
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
  arguments->slots[0] = string__133_58;
  arguments->slots[1] = string__133_59;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__133_60(void) {
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
  arguments->slots[0] = string__133_61;
  arguments->slots[1] = string__133_62;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__133_63(void) {
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
  arguments->slots[0] = string__133_64;
  arguments->slots[1] = string__133_65;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__133_66(void) {
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
  arguments->slots[1] = string__133_67;
  arguments->slots[2] = string__133_68;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__133_69(void) {
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
static void cont__133_70(void) {
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
  frame->cont = cont__134_1;
}
static void cont__134_1(void) {
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
  frame->cont = cont__135_1;
}
static void cont__135_1(void) {
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
  arguments->slots[1] = func__137_1;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__137_2;
}
static void entry__137_1(void) {
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
static void cont__137_2(void) {
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
  frame->cont = cont__142_1;
}
static void cont__142_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._WHITESPACE, arguments->slots[0]);
  // 258: $gcc_basic_options
  // 259:   list
  // 260:     "-Wall"
  // 261:     "-Wno-unused-function"
  // 262:     "-Wno-unused-variable"
  // 263:     "-Wno-parentheses"
  // 264:     "-Wno-switch"
  // 265:     "-Wno-maybe-uninitialized"
  // 266:     "-Wno-trigraphs"
  // 267:     "-O1"
  // ...
  argument_count = 11;
  arguments = node_p;
  arguments->slots[0] = string__143_1;
  arguments->slots[1] = string__143_2;
  arguments->slots[2] = string__143_3;
  arguments->slots[3] = string__143_4;
  arguments->slots[4] = string__143_5;
  arguments->slots[5] = string__143_6;
  arguments->slots[6] = string__143_7;
  arguments->slots[7] = string__143_8;
  arguments->slots[8] = string__143_9;
  arguments->slots[9] = string__143_10;
  arguments->slots[10] = string__143_11;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__143_12;
}
static void cont__143_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._gcc_basic_options, arguments->slots[0]);
  // 274: ... list("-msse2" "-mfpmath=sse")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__144_1;
  arguments->slots[1] = string__144_2;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__144_3;
}
static void cont__144_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 274: "x86_32" = list("-msse2" "-mfpmath=sse")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__144_4;
  arguments->slots[1] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__144_5;
}
static void cont__144_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 275: ... list("-msse2" "-mfpmath=sse")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__144_1;
  arguments->slots[1] = string__144_2;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__144_6;
}
static void cont__144_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 275: "x86_64" = list("-msse2" "-mfpmath=sse")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__144_7;
  arguments->slots[1] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__144_8;
}
static void cont__144_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 272: $gcc_hardware_specific_options
  // 273:   table
  // 274:     "x86_32" = list("-msse2" "-mfpmath=sse")
  // 275:     "x86_64" = list("-msse2" "-mfpmath=sse")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__table();
  func = myself->type;
  frame->cont = cont__144_9;
}
static void cont__144_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._gcc_hardware_specific_options, arguments->slots[0]);
  // 277: $$gcc_include_options empty_list
  var._gcc_include_options = get__empty_list();
  // 278: for_each simdatapaths: (path)
  // 279:   push &gcc_include_options "-I@(path)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._simdatapaths;
  arguments->slots[1] = func__146_1;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__146_5;
}
static void entry__146_1(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // path: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 279: ... "-I@(path)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__146_2;
  arguments->slots[1] = frame->slots[0] /* path */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__146_3;
}
static void cont__146_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 279: push &gcc_include_options "-I@(path)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._gcc_include_options;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__146_4;
}
static void cont__146_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._gcc_include_options = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__146_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 286: ... hardware_architecture()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__hardware_architecture();
  func = myself->type;
  frame->cont = cont__147_1;
}
static void cont__147_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 286: gcc_hardware_specific_options(hardware_architecture())
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = var._gcc_hardware_specific_options;
  func = myself->type;
  frame->cont = cont__147_2;
}
static void cont__147_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 285: default_value
  // 286:   gcc_hardware_specific_options(hardware_architecture())
  // 287:   empty_list
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__3 */;
  arguments->slots[1] = get__empty_list();
  result_count = 1;
  myself = get__default_value();
  func = myself->type;
  frame->cont = cont__147_3;
}
static void cont__147_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 284: append
  // 285:   default_value
  // 286:     gcc_hardware_specific_options(hardware_architecture())
  // 287:     empty_list
  // 288:   gcc_include_options
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  arguments->slots[1] = var._gcc_include_options;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__147_4;
}
static void cont__147_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 281: $gcc_options
  // 282:   append
  // 283:     gcc_basic_options
  // 284:     append
  // 285:       default_value
  // 286:         gcc_hardware_specific_options(hardware_architecture())
  // 287:         empty_list
  // 288:       gcc_include_options
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._gcc_basic_options;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__147_5;
}
static void cont__147_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._gcc_options, arguments->slots[0]);
  // 290: %on_top_level true # set to false while building meta-files
  initialize_maybe_future(get__on_top_level(), get__true());
  // 291: %%objects empty_insert_order_set
  set__objects(get__empty_insert_order_set());
  // 292: %%libraries empty_insert_order_set # contains "-lsim-..."-entries
  set__libraries(get__empty_insert_order_set());
  // 293: %%do_link false
  set__do_link(get__false());
  // 294: %%last_modification_time undefined
  set__last_modification_time(get__undefined());
  // 295: $$c_sources empty_insert_order_set
  var._c_sources = get__empty_insert_order_set();
  // 296: $$dependencies empty_list
  var._dependencies = get__empty_list();
  // 297: $$resolved_libraries undefined
  var._resolved_libraries = get__undefined();
  // 626: ... main_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_info();
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__165_1;
}
static void cont__165_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 626: if main_info.is_undefined:
  // 627:   Error "
  // 628:     Source file "@(main_filename)" does not exist!@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__165_2;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__165_6;
}
static void entry__165_2(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 627: ... "
  // 628:   Source file "@(main_filename)" does not exist!@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__165_3;
  arguments->slots[1] = get__main_filename();
  arguments->slots[2] = string__165_4;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__165_5;
}
static void cont__165_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 627: Error "
  // 628:   Source file "@(main_filename)" does not exist!@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__165_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 933: $$t undefined
  var._t = get__undefined();
  // 1073: if do_time_passes: !t current_time()
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = func__180_1;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__180_3;
}
static void entry__180_1(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1073: ... !t current_time()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__current_time();
  func = myself->type;
  frame->cont = cont__180_2;
}
static void cont__180_2(void) {
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
static void cont__180_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1074: cond
  // 1075:   ->
  // 1076:     ||
  // 1077:       do_check_only
  // 1078:       do_dump_trees
  // 1079:       do_pretty_print
  // 1080:       do_print_simplified_source
  // 1081:     dump_source_or_check
  // 1082:   -> do_print_c print_c
  // 1083:   -> do_list_dependencies list_dependencies
  // ...
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = func__181_1;
  arguments->slots[1] = func__181_8;
  arguments->slots[2] = func__181_9;
  arguments->slots[3] = func__181_10;
  arguments->slots[4] = func__181_11;
  arguments->slots[5] = var._build_executable;
  result_count = 0;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__181_13;
}
static void entry__181_1(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_check_only();
  arguments->slots[1] = func__181_2;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__181_7;
}
static void entry__181_2(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_dump_trees();
  arguments->slots[1] = func__181_3;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__181_6;
}
static void entry__181_3(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_pretty_print();
  arguments->slots[1] = func__181_4;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__181_5;
}
static void entry__181_4(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1080: do_print_simplified_source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__do_print_simplified_source();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__181_5(void) {
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
static void cont__181_6(void) {
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
static void cont__181_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1075: ->
  // 1076:   ||
  // 1077:     do_check_only
  // 1078:     do_dump_trees
  // 1079:     do_pretty_print
  // 1080:     do_print_simplified_source
  // 1081:   dump_source_or_check
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = var._dump_source_or_check;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__181_8(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1082: -> do_print_c print_c
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_print_c;
  arguments->slots[1] = var._print_c;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__181_9(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1083: -> do_list_dependencies list_dependencies
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_list_dependencies;
  arguments->slots[1] = var._list_dependencies;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__181_10(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1084: -> do_build_codeblocks_project build_codeblocks_project
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_build_codeblocks_project;
  arguments->slots[1] = var._build_codeblocks_project;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__181_11(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1085: ... main_info.is_a_directory
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_info();
  result_count = 1;
  myself = get__is_a_directory();
  func = myself->type;
  frame->cont = cont__181_12;
}
static void cont__181_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1085: -> main_info.is_a_directory build_library
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = var._build_library;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__181_13(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = get__std__terminate();
  func = myself->type;
  frame->cont = cont__182_1;
}
static void cont__182_1(void) {
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
static void entry__65_1_resolve_filename(void) {
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
  // 300: ... resolved_libraries.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._resolved_libraries;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__65_2;
}
static void cont__65_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 300: if resolved_libraries.is_undefined:
  // 301:   !resolved_libraries empty_table
  // 302:   for_each simlibpaths: (path)
  // 303:     if file_exists(path):
  // 304:       for_each directory(path): (entry)
  // 305:         if entry.is_a_directory:
  // 306:           $name std::filename_of(entry)
  // 307:           if name .matches. NAME: !resolved_libraries(name) fullname_of(entry)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = func__65_3;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__65_16;
}
static void entry__65_13(void) {
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
  // 307: ... !resolved_libraries(name) fullname_of(entry)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* entry */;
  result_count = 1;
  myself = get__fullname_of();
  func = myself->type;
  frame->cont = cont__65_14;
}
static void cont__65_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 307: ... !resolved_libraries(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = var._resolved_libraries;
  func = myself->type;
  frame->cont = cont__65_15;
}
static void cont__65_15(void) {
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
static void entry__65_10(void) {
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
  // 306: $name std::filename_of(entry)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* entry */;
  result_count = 1;
  myself = get__std__filename_of();
  func = myself->type;
  frame->cont = cont__65_11;
}
static void cont__65_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* name */, arguments->slots[0]);
  // 307: ... name .matches. NAME
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* name */;
  arguments->slots[1] = get__NAME();
  result_count = 1;
  myself = get__matches();
  func = myself->type;
  frame->cont = cont__65_12;
}
static void cont__65_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 307: ... : !resolved_libraries(name) fullname_of(entry)
  frame->slots[3] /* temp__2 */ = create_closure(entry__65_13, 0);
  // 307: if name .matches. NAME: !resolved_libraries(name) fullname_of(entry)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__65_8(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // entry: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 305: ... entry.is_a_directory
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* entry */;
  result_count = 1;
  myself = get__is_a_directory();
  func = myself->type;
  frame->cont = cont__65_9;
}
static void cont__65_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 305: ... :
  // 306:   $name std::filename_of(entry)
  // 307:   if name .matches. NAME: !resolved_libraries(name) fullname_of(entry)
  frame->slots[2] /* temp__2 */ = create_closure(entry__65_10, 0);
  // 305: if entry.is_a_directory:
  // 306:   $name std::filename_of(entry)
  // 307:   if name .matches. NAME: !resolved_libraries(name) fullname_of(entry)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__65_6(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // path: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* path */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 304: ... directory(path)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* path */;
  result_count = 1;
  myself = get__directory();
  func = myself->type;
  frame->cont = cont__65_7;
}
static void cont__65_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 304: for_each directory(path): (entry)
  // 305:   if entry.is_a_directory:
  // 306:     $name std::filename_of(entry)
  // 307:     if name .matches. NAME: !resolved_libraries(name) fullname_of(entry)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__65_8;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__65_4(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // path: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 303: ... file_exists(path)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* path */;
  result_count = 1;
  myself = get__file_exists();
  func = myself->type;
  frame->cont = cont__65_5;
}
static void cont__65_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 303: ... :
  // 304:   for_each directory(path): (entry)
  // 305:     if entry.is_a_directory:
  // 306:       $name std::filename_of(entry)
  // 307:       if name .matches. NAME: !resolved_libraries(name) fullname_of(entry)
  frame->slots[2] /* temp__2 */ = create_closure(entry__65_6, 0);
  // 303: if file_exists(path):
  // 304:   for_each directory(path): (entry)
  // 305:     if entry.is_a_directory:
  // 306:       $name std::filename_of(entry)
  // 307:       if name .matches. NAME: !resolved_libraries(name) fullname_of(entry)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__65_3(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 301: !resolved_libraries empty_table
  var._resolved_libraries = get__empty_table();
  // 302: for_each simlibpaths: (path)
  // 303:   if file_exists(path):
  // 304:     for_each directory(path): (entry)
  // 305:       if entry.is_a_directory:
  // 306:         $name std::filename_of(entry)
  // 307:         if name .matches. NAME: !resolved_libraries(name) fullname_of(entry)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._simlibpaths;
  arguments->slots[1] = func__65_4;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__65_16(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 308: $libname filename .before. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__65_17;
}
static void cont__65_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* libname */, arguments->slots[0]);
  // 309: $libpath resolved_libraries(libname)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* libname */;
  result_count = 1;
  myself = var._resolved_libraries;
  func = myself->type;
  frame->cont = cont__65_18;
}
static void cont__65_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* libpath */, arguments->slots[0]);
  // 310: ... libpath.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* libpath */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__65_19;
}
static void cont__65_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 310: ... :
  // 311:   Error "
  // 312:     Cannot resolve required library "@(libname)@quot;!@
  frame->slots[4] /* temp__2 */ = create_closure(entry__65_20, 0);
  // 310: if libpath.is_undefined:
  // 311:   Error "
  // 312:     Cannot resolve required library "@(libname)@quot;!@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__65_24;
}
static void entry__65_20(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // libname: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* libname */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 311: ... "
  // 312:   Cannot resolve required library "@(libname)@quot;!@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__65_21;
  arguments->slots[1] = frame->slots[0] /* libname */;
  arguments->slots[2] = string__65_22;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__65_23;
}
static void cont__65_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 311: Error "
  // 312:   Cannot resolve required library "@(libname)@quot;!@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__65_24(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 313: ... filename .from. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__from();
  func = myself->type;
  frame->cont = cont__65_25;
}
static void cont__65_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 313: ... string(libpath filename .from. '/')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* libpath */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__65_26;
}
static void cont__65_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 313: -> string(libpath filename .from. '/')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__66_1_add_module_infos(void) {
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
  // 324: ... --SORT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__SORT();
  arguments->slots[1] = get__std__true();
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__66_2;
}
static void cont__66_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 324: $entries directory(--SORT path)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[0] /* path */;
  result_count = 1;
  myself = get__directory();
  func = myself->type;
  frame->cont = cont__66_3;
}
static void cont__66_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* entries */, arguments->slots[0]);
  // 325: $$filenames empty_set
  ((CELL *)frame->slots[4])->contents /* filenames */ = get__empty_set();
  // 326: $$directories empty_list
  ((CELL *)frame->slots[5])->contents /* directories */ = get__empty_list();
  // 327: $$modules empty_key_order_set
  ((CELL *)frame->slots[6])->contents /* modules */ = get__empty_key_order_set();
  // 328: ... : (entry)
  // 329:   $name std::filename_of(entry)
  // 330:   cond
  // 331:     -> entry.is_a_directory: if name .matches. NAME: push &directories name
  // 332:     -> name .has_suffix. ".sim":
  // 333:       $submodule_name name .without_suffix. (some(".meta"), ".sim")
  // 334:       !filenames(submodule_name) true
  // 335:       $meta_level (length_of(name)-length_of(submodule_name)-4)/5
  // 336:       $stored_level meta_levels(submodule_name)
  // 337:       if stored_level.is_undefined || meta_level > stored_level:
  // ...
  frame->slots[7] /* temp__1 */ = create_closure(entry__66_4, 1);
  // 328: for_each entries: (entry)
  // 329:   $name std::filename_of(entry)
  // 330:   cond
  // 331:     -> entry.is_a_directory: if name .matches. NAME: push &directories name
  // 332:     -> name .has_suffix. ".sim":
  // 333:       $submodule_name name .without_suffix. (some(".meta"), ".sim")
  // 334:       !filenames(submodule_name) true
  // 335:       $meta_level (length_of(name)-length_of(submodule_name)-4)/5
  // 336:       $stored_level meta_levels(submodule_name)
  // 337:       if stored_level.is_undefined || meta_level > stored_level:
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* entries */;
  arguments->slots[1] = frame->slots[7] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__66_38;
}
static void entry__66_15(void) {
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
  // 333: ... some(".meta")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__66_16;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__66_17;
}
static void cont__66_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__2 */ = arguments->slots[0];
  // 333: ... some(".meta"), ".sim"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__2 */;
  arguments->slots[1] = string__66_13;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__66_18;
}
static void cont__66_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 333: $submodule_name name .without_suffix. (some(".meta"), ".sim")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = get__without_suffix();
  func = myself->type;
  frame->cont = cont__66_19;
}
static void cont__66_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* submodule_name */, arguments->slots[0]);
  // 334: !filenames(submodule_name) true
  frame->slots[9] /* temp__1 */ = get__true();
  // 334: !filenames(submodule_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* submodule_name */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* filenames */;
  func = myself->type;
  frame->cont = cont__66_20;
}
static void cont__66_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* filenames */ = arguments->slots[0];
  // 335: ... length_of(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__66_21;
}
static void cont__66_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__3 */ = arguments->slots[0];
  // 335: ... length_of(submodule_name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* submodule_name */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__66_22;
}
static void cont__66_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__4 */ = arguments->slots[0];
  // 335: ... length_of(name)-length_of(submodule_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__3 */;
  arguments->slots[1] = frame->slots[12] /* temp__4 */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__66_23;
}
static void cont__66_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__2 */ = arguments->slots[0];
  // 335: ... length_of(name)-length_of(submodule_name)-4
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__2 */;
  arguments->slots[1] = number__4;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__66_24;
}
static void cont__66_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 335: $meta_level (length_of(name)-length_of(submodule_name)-4)/5
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__std__over();
  func = myself->type;
  frame->cont = cont__66_25;
}
static void cont__66_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* meta_level */, arguments->slots[0]);
  // 336: $stored_level meta_levels(submodule_name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* submodule_name */;
  result_count = 1;
  myself = var._meta_levels;
  func = myself->type;
  frame->cont = cont__66_26;
}
static void cont__66_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* stored_level */, arguments->slots[0]);
  // 337: ... stored_level.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* stored_level */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__66_27;
}
static void cont__66_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__2 */ = arguments->slots[0];
  // 337: ... meta_level > stored_level
  frame->slots[11] /* temp__3 */ = create_closure(entry__66_28, 0);
  // 337: ... stored_level.is_undefined || meta_level > stored_level
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__2 */;
  arguments->slots[1] = frame->slots[11] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__66_30;
}
static void entry__66_28(void) {
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
  // 337: ... meta_level > stored_level
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stored_level */;
  arguments->slots[1] = frame->slots[1] /* meta_level */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__66_29;
}
static void cont__66_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 337: ... meta_level > stored_level
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__66_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 337: ... :
  // 338:   !meta_levels(submodule_name) meta_level
  frame->slots[12] /* temp__4 */ = create_closure(entry__66_31, 0);
  // 337: if stored_level.is_undefined || meta_level > stored_level:
  // 338:   !meta_levels(submodule_name) meta_level
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = frame->slots[12] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__66_33;
}
static void entry__66_31(void) {
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
  // 338: !meta_levels(submodule_name) meta_level
  frame->slots[2] /* temp__1 */ = frame->slots[1] /* meta_level */;
  // 338: !meta_levels(submodule_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* submodule_name */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = var._meta_levels;
  func = myself->type;
  frame->cont = cont__66_32;
}
static void cont__66_32(void) {
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
static void cont__66_33(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 339: $basename submodule_name .truncate_from. '-'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* submodule_name */;
  arguments->slots[1] = character__45;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__66_34;
}
static void cont__66_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[7] /* basename */, arguments->slots[0]);
  // 340: !modules(basename) true
  frame->slots[9] /* temp__1 */ = get__true();
  // 340: !modules(basename)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* basename */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[2])->contents /* modules */;
  func = myself->type;
  frame->cont = cont__66_35;
}
static void cont__66_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* modules */ = arguments->slots[0];
  // 341: $mod_name string(mod_path basename)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* mod_path */;
  arguments->slots[1] = frame->slots[7] /* basename */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__66_36;
}
static void cont__66_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[8] /* mod_name */, arguments->slots[0]);
  // 342: !module_info(mod_name) empty_key_order_table
  frame->slots[9] /* temp__1 */ = get__empty_key_order_table();
  // 342: !module_info(mod_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* mod_name */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = var._module_info;
  func = myself->type;
  frame->cont = cont__66_37;
}
static void cont__66_37(void) {
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
static void entry__66_10(void) {
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
  // 331: ... push &directories name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* directories */;
  arguments->slots[1] = frame->slots[1] /* name */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__66_11;
}
static void cont__66_11(void) {
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
static void entry__66_8(void) {
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
  // 331: ... name .matches. NAME
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = get__NAME();
  result_count = 1;
  myself = get__matches();
  func = myself->type;
  frame->cont = cont__66_9;
}
static void cont__66_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 331: ... : push &directories name
  frame->slots[3] /* temp__2 */ = create_closure(entry__66_10, 0);
  // 331: ... if name .matches. NAME: push &directories name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__66_6(void) {
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
  // 331: ... entry.is_a_directory
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* entry */;
  result_count = 1;
  myself = get__is_a_directory();
  func = myself->type;
  frame->cont = cont__66_7;
}
static void cont__66_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 331: ... : if name .matches. NAME: push &directories name
  frame->slots[4] /* temp__2 */ = create_closure(entry__66_8, 0);
  // 331: -> entry.is_a_directory: if name .matches. NAME: push &directories name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__66_12(void) {
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
  // 332: ... name .has_suffix. ".sim"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = string__66_13;
  result_count = 1;
  myself = get__has_suffix();
  func = myself->type;
  frame->cont = cont__66_14;
}
static void cont__66_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 332: ... :
  // 333:   $submodule_name name .without_suffix. (some(".meta"), ".sim")
  // 334:   !filenames(submodule_name) true
  // 335:   $meta_level (length_of(name)-length_of(submodule_name)-4)/5
  // 336:   $stored_level meta_levels(submodule_name)
  // 337:   if stored_level.is_undefined || meta_level > stored_level:
  // 338:     !meta_levels(submodule_name) meta_level
  // 339:   $basename submodule_name .truncate_from. '-'
  // 340:   !modules(basename) true
  // 341:   $mod_name string(mod_path basename)
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__66_15, 0);
  // 332: -> name .has_suffix. ".sim":
  // 333:   $submodule_name name .without_suffix. (some(".meta"), ".sim")
  // 334:   !filenames(submodule_name) true
  // 335:   $meta_level (length_of(name)-length_of(submodule_name)-4)/5
  // 336:   $stored_level meta_levels(submodule_name)
  // 337:   if stored_level.is_undefined || meta_level > stored_level:
  // 338:     !meta_levels(submodule_name) meta_level
  // 339:   $basename submodule_name .truncate_from. '-'
  // 340:   !modules(basename) true
  // 341:   $mod_name string(mod_path basename)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__66_4(void) {
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
  // 329: $name std::filename_of(entry)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* entry */;
  result_count = 1;
  myself = get__std__filename_of();
  func = myself->type;
  frame->cont = cont__66_5;
}
static void cont__66_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* name */, arguments->slots[0]);
  // 331: -> entry.is_a_directory: if name .matches. NAME: push &directories name
  frame->slots[6] /* temp__1 */ = create_closure(entry__66_6, 0);
  // 332: -> name .has_suffix. ".sim":
  // 333:   $submodule_name name .without_suffix. (some(".meta"), ".sim")
  // 334:   !filenames(submodule_name) true
  // 335:   $meta_level (length_of(name)-length_of(submodule_name)-4)/5
  // 336:   $stored_level meta_levels(submodule_name)
  // 337:   if stored_level.is_undefined || meta_level > stored_level:
  // 338:     !meta_levels(submodule_name) meta_level
  // 339:   $basename submodule_name .truncate_from. '-'
  // 340:   !modules(basename) true
  // 341:   $mod_name string(mod_path basename)
  // ...
  frame->slots[7] /* temp__2 */ = create_closure(entry__66_12, 0);
  // 330: cond
  // 331:   -> entry.is_a_directory: if name .matches. NAME: push &directories name
  // 332:   -> name .has_suffix. ".sim":
  // 333:     $submodule_name name .without_suffix. (some(".meta"), ".sim")
  // 334:     !filenames(submodule_name) true
  // 335:     $meta_level (length_of(name)-length_of(submodule_name)-4)/5
  // 336:     $stored_level meta_levels(submodule_name)
  // 337:     if stored_level.is_undefined || meta_level > stored_level:
  // 338:       !meta_levels(submodule_name) meta_level
  // 339:     $basename submodule_name .truncate_from. '-'
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
static void cont__66_38(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 343: ... : (filename)
  // 344:   if filename .contains. '-':
  // 345:     unless filename .has_suffix. "-common":
  // 346:       $maybe_push_common: (plat)
  // 347:         $common_name string(name "-" plat "-common")
  // 348:         if filenames(common_name): push &files common_name
  // 349:       
  // 350:       $name filename .before. '-'
  // 351:       $mod_name string(mod_path name .truncate_from. '-')
  // 352:       $platform filename .behind. '-'
  // ...
  frame->slots[7] /* temp__1 */ = create_closure(entry__66_39, 1);
  // 343: for_each filenames: (filename)
  // 344:   if filename .contains. '-':
  // 345:     unless filename .has_suffix. "-common":
  // 346:       $maybe_push_common: (plat)
  // 347:         $common_name string(name "-" plat "-common")
  // 348:         if filenames(common_name): push &files common_name
  // 349:       
  // 350:       $name filename .before. '-'
  // 351:       $mod_name string(mod_path name .truncate_from. '-')
  // 352:       $platform filename .behind. '-'
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* filenames */;
  arguments->slots[1] = frame->slots[7] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__66_74;
}
static void entry__66_44(void) {
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
  // 346: ... : (plat)
  // 347:   $common_name string(name "-" plat "-common")
  // 348:   if filenames(common_name): push &files common_name
  frame->slots[9] /* temp__1 */ = create_closure(entry__66_45_maybe_push_common, 1);
  // 346: $maybe_push_common: (plat)
  // 347:   $common_name string(name "-" plat "-common")
  // 348:   if filenames(common_name): push &files common_name
  initialize_future(frame->slots[3] /* maybe_push_common */, frame->slots[9] /* temp__1 */);
  // 350: $name filename .before. '-'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* filename */;
  arguments->slots[1] = character__45;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__66_51;
}
static void entry__66_49(void) {
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
  // 348: ... push &files common_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* files */;
  arguments->slots[1] = frame->slots[1] /* common_name */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__66_50;
}
static void cont__66_50(void) {
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
static void entry__66_45_maybe_push_common(void) {
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
  // 347: $common_name string(name "-" plat "-common")
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* name */;
  arguments->slots[1] = string__66_46;
  arguments->slots[2] = frame->slots[0] /* plat */;
  arguments->slots[3] = string__66_42;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__66_47;
}
static void cont__66_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* common_name */, arguments->slots[0]);
  // 348: ... filenames(common_name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* common_name */;
  result_count = 1;
  myself = ((CELL *)frame->slots[2])->contents /* filenames */;
  func = myself->type;
  frame->cont = cont__66_48;
}
static void cont__66_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 348: ... : push &files common_name
  frame->slots[6] /* temp__2 */ = create_closure(entry__66_49, 0);
  // 348: if filenames(common_name): push &files common_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__66_51(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* name */, arguments->slots[0]);
  // 351: ... name .truncate_from. '-'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* name */;
  arguments->slots[1] = character__45;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__66_52;
}
static void cont__66_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 351: $mod_name string(mod_path name .truncate_from. '-')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* mod_path */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__66_53;
}
static void cont__66_53(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* mod_name */, arguments->slots[0]);
  // 352: $platform filename .behind. '-'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* filename */;
  arguments->slots[1] = character__45;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__66_54;
}
static void cont__66_54(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* platform */, arguments->slots[0]);
  // 353: $$parent supported_platforms(platform)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* platform */;
  result_count = 1;
  myself = var._supported_platforms;
  func = myself->type;
  frame->cont = cont__66_55;
}
static void cont__66_55(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[7])->contents /* parent */ = arguments->slots[0];
  // 354: ... parent.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[7])->contents /* parent */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__66_56;
}
static void cont__66_56(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 354: ... :
  // 355:   Error "
  // 356:     The platform "@(platform)" is not supported!@
  frame->slots[10] /* temp__2 */ = create_closure(entry__66_57, 0);
  // 354: unless parent.is_defined:
  // 355:   Error "
  // 356:     The platform "@(platform)" is not supported!@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__66_61;
}
static void entry__66_57(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // platform: 0
  frame->slots[0] = myself->closure.frame->slots[6]; /* platform */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 355: ... "
  // 356:   The platform "@(platform)" is not supported!@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__66_58;
  arguments->slots[1] = frame->slots[0] /* platform */;
  arguments->slots[2] = string__66_59;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__66_60;
}
static void cont__66_60(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 355: Error "
  // 356:   The platform "@(platform)" is not supported!@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__66_61(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 357: $$files list(filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* filename */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__66_62;
}
static void cont__66_62(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[8])->contents /* files */ = arguments->slots[0];
  // 358: maybe_push_common platform
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* platform */;
  result_count = 0;
  myself = frame->slots[3] /* maybe_push_common */;
  func = myself->type;
  frame->cont = cont__66_63;
}
static void cont__66_63(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 359: ... -> parent != NONE:
  // 360:   maybe_push_common parent
  // 361:   !parent supported_platforms(parent)
  frame->slots[9] /* temp__1 */ = create_closure(entry__66_64, 0);
  // 359: while -> parent != NONE:
  // 360:   maybe_push_common parent
  // 361:   !parent supported_platforms(parent)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  result_count = 0;
  myself = get__while();
  func = myself->type;
  frame->cont = cont__66_70;
}
static void entry__66_67(void) {
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
  // 360: maybe_push_common parent
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* parent */;
  result_count = 0;
  myself = frame->slots[0] /* maybe_push_common */;
  func = myself->type;
  frame->cont = cont__66_68;
}
static void cont__66_68(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 361: !parent supported_platforms(parent)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* parent */;
  result_count = 1;
  myself = var._supported_platforms;
  func = myself->type;
  frame->cont = cont__66_69;
}
static void cont__66_69(void) {
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
static void entry__66_64(void) {
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
  // 359: ... parent != NONE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parent */;
  arguments->slots[1] = var._NONE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__66_65;
}
static void cont__66_65(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 359: ... parent != NONE
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__66_66;
}
static void cont__66_66(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 359: ... :
  // 360:   maybe_push_common parent
  // 361:   !parent supported_platforms(parent)
  frame->slots[4] /* temp__3 */ = create_closure(entry__66_67, 0);
  // 359: ... -> parent != NONE:
  // 360:   maybe_push_common parent
  // 361:   !parent supported_platforms(parent)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__66_70(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 362: !module_info(mod_name)(platform) files
  frame->slots[9] /* temp__1 */ = ((CELL *)frame->slots[8])->contents /* files */;
  // 362: ... module_info(mod_name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* mod_name */;
  result_count = 1;
  myself = var._module_info;
  func = myself->type;
  frame->cont = cont__66_71;
}
static void cont__66_71(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__2 */ = arguments->slots[0];
  // 362: !module_info(mod_name)(platform)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* platform */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = frame->slots[10] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__66_72;
}
static void cont__66_72(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__2 */ = arguments->slots[0];
  // 362: !module_info(mod_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* mod_name */;
  arguments->slots[1] = frame->slots[10] /* temp__2 */;
  result_count = 1;
  myself = var._module_info;
  func = myself->type;
  frame->cont = cont__66_73;
}
static void cont__66_73(void) {
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
static void entry__66_41(void) {
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
  // 345: ... filename .has_suffix. "-common"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  arguments->slots[1] = string__66_42;
  result_count = 1;
  myself = get__has_suffix();
  func = myself->type;
  frame->cont = cont__66_43;
}
static void cont__66_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 345: ... :
  // 346:   $maybe_push_common: (plat)
  // 347:     $common_name string(name "-" plat "-common")
  // 348:     if filenames(common_name): push &files common_name
  // 349:   
  // 350:   $name filename .before. '-'
  // 351:   $mod_name string(mod_path name .truncate_from. '-')
  // 352:   $platform filename .behind. '-'
  // 353:   $$parent supported_platforms(platform)
  // 354:   unless parent.is_defined:
  // ...
  frame->slots[4] /* temp__2 */ = create_closure(entry__66_44, 0);
  // 345: unless filename .has_suffix. "-common":
  // 346:   $maybe_push_common: (plat)
  // 347:     $common_name string(name "-" plat "-common")
  // 348:     if filenames(common_name): push &files common_name
  // 349:   
  // 350:   $name filename .before. '-'
  // 351:   $mod_name string(mod_path name .truncate_from. '-')
  // 352:   $platform filename .behind. '-'
  // 353:   $$parent supported_platforms(platform)
  // 354:   unless parent.is_defined:
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
static void entry__66_39(void) {
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
  // 344: ... filename .contains. '-'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  arguments->slots[1] = character__45;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__66_40;
}
static void cont__66_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 344: ... :
  // 345:   unless filename .has_suffix. "-common":
  // 346:     $maybe_push_common: (plat)
  // 347:       $common_name string(name "-" plat "-common")
  // 348:       if filenames(common_name): push &files common_name
  // 349:     
  // 350:     $name filename .before. '-'
  // 351:     $mod_name string(mod_path name .truncate_from. '-')
  // 352:     $platform filename .behind. '-'
  // 353:     $$parent supported_platforms(platform)
  // ...
  frame->slots[4] /* temp__2 */ = create_closure(entry__66_41, 0);
  // 344: if filename .contains. '-':
  // 345:   unless filename .has_suffix. "-common":
  // 346:     $maybe_push_common: (plat)
  // 347:       $common_name string(name "-" plat "-common")
  // 348:       if filenames(common_name): push &files common_name
  // 349:     
  // 350:     $name filename .before. '-'
  // 351:     $mod_name string(mod_path name .truncate_from. '-')
  // 352:     $platform filename .behind. '-'
  // 353:     $$parent supported_platforms(platform)
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
static void cont__66_74(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 363: ... parameter_count_of(return)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* return */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__66_75;
}
static void cont__66_75(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 363: ... parameter_count_of(return) == 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__2 */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__66_76;
}
static void cont__66_76(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 363: ... : return directories modules
  frame->slots[9] /* temp__3 */ = create_closure(entry__66_77, 0);
  // 363: if parameter_count_of(return) == 2: return directories modules
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__66_78;
}
static void entry__66_77(void) {
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
  // 363: ... return directories modules
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* directories */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* modules */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__66_78(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__67_4(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // info: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 374: ... -> info
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__67_5(void) {
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
  // 375: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__67_6;
}
static void cont__67_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 375: ... before(mod_filename '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__67_7;
}
static void cont__67_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 375: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__67_8;
}
static void cont__67_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 375: ... until(mod_name '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* mod_name */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = get__until();
  func = myself->type;
  frame->cont = cont__67_9;
}
static void cont__67_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 375: add_module_infos before(mod_filename '/' -1) until(mod_name '/' -1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 0;
  myself = var._add_module_infos;
  func = myself->type;
  frame->cont = cont__67_10;
}
static void cont__67_10(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 376: ... module_info(mod_name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* mod_name */;
  result_count = 1;
  myself = var._module_info;
  func = myself->type;
  frame->cont = cont__67_11;
}
static void cont__67_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 376: -> module_info(mod_name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__67_1_lookup(void) {
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
  // 373: $info module_info(mod_name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* mod_name */;
  result_count = 1;
  myself = var._module_info;
  func = myself->type;
  frame->cont = cont__67_2;
}
static void cont__67_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* info */, arguments->slots[0]);
  // 374: ... info.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* info */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__67_3;
}
static void cont__67_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 374: ... -> info
  frame->slots[4] /* temp__2 */ = create_closure(entry__67_4, 0);
  // 374: ... :
  // 375:   add_module_infos before(mod_filename '/' -1) until(mod_name '/' -1)
  // 376:   -> module_info(mod_name)
  frame->slots[5] /* temp__3 */ = create_closure(entry__67_5, 0);
  // 374: if info.is_defined (-> info):
  // 375:   add_module_infos before(mod_filename '/' -1) until(mod_name '/' -1)
  // 376:   -> module_info(mod_name)
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
static void entry__68_1_Gcc(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // args: 0
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 379: ... : ewriteln "gcc " join(args)
  frame->slots[1] /* temp__1 */ = create_closure(entry__68_2, 0);
  // 379: if do_show_debug_infos: ewriteln "gcc " join(args)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_show_debug_infos();
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__68_5;
}
static void entry__68_2(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // args: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* args */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 379: ... join(args)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* args */;
  result_count = 1;
  myself = get__join();
  func = myself->type;
  frame->cont = cont__68_3;
}
static void cont__68_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 379: ... ewriteln "gcc " join(args)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__68_4;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__68_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 380: gcc args*
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = frame->caller_result_count;
  myself = var._gcc;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__69_4(void) {
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
  // 384: Gcc $_out $err $success gcc_options* "-c" c_filename "-o" o_filename
  argument_count = 0;
  arguments = node_p;
  unfold(var._gcc_options);
  arguments->slots[argument_count++] = string__69_5;
  arguments->slots[argument_count++] = frame->slots[0] /* c_filename */;
  arguments->slots[argument_count++] = string__69_6;
  arguments->slots[argument_count++] = frame->slots[1] /* o_filename */;
  result_count = 3;
  myself = var._Gcc;
  func = myself->type;
  frame->cont = cont__69_7;
}
static void cont__69_7(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  frame->slots[6] /* temp__2 */ = arguments->slots[1];
  frame->slots[7] /* temp__3 */ = arguments->slots[2];
  // 384: ... _out
  initialize_future(frame->slots[2] /* out */, frame->slots[5] /* temp__1 */);
  // 384: ... err
  initialize_future(frame->slots[3] /* err */, frame->slots[6] /* temp__2 */);
  // 384: ... success
  initialize_future(frame->slots[4] /* success */, frame->slots[7] /* temp__3 */);
  // 385: ... :
  // 386:   Error "
  // 387:     Failed to compile @(c_filename)
  // 388:     @(err.from_utf8)
  frame->slots[5] /* temp__1 */ = create_closure(entry__69_8, 0);
  // 385: unless success:
  // 386:   Error "
  // 387:     Failed to compile @(c_filename)
  // 388:     @(err.from_utf8)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* success */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__69_13;
}
static void entry__69_8(void) {
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
  // 388: ... err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* err */;
  result_count = 1;
  myself = get__from_utf8();
  func = myself->type;
  frame->cont = cont__69_9;
}
static void cont__69_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 386: ... "
  // 387:   Failed to compile @(c_filename)
  // 388:   @(err.from_utf8)
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__69_10;
  arguments->slots[1] = frame->slots[0] /* c_filename */;
  arguments->slots[2] = string__69_11;
  arguments->slots[3] = frame->slots[3] /* temp__2 */;
  arguments->slots[4] = string__69_11;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__69_12;
}
static void cont__69_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 386: Error "
  // 387:   Failed to compile @(c_filename)
  // 388:   @(err.from_utf8)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__69_13(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 389: !do_link true
  set__do_link(get__true());
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__69_1_compile_c(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // c_filename: 0
  // o_filename: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 383: ... do_build_codeblocks_project || do_list_dependencies
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_build_codeblocks_project;
  arguments->slots[1] = func__69_2;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__69_3;
}
static void entry__69_2(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 383: ... do_list_dependencies
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._do_list_dependencies;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__69_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 383: ... :
  // 384:   Gcc $_out $err $success gcc_options* "-c" c_filename "-o" o_filename
  // 385:   unless success:
  // 386:     Error "
  // 387:       Failed to compile @(c_filename)
  // 388:       @(err.from_utf8)
  // 389:   !do_link true
  frame->slots[3] /* temp__2 */ = create_closure(entry__69_4, 0);
  // 383: unless do_build_codeblocks_project || do_list_dependencies:
  // 384:   Gcc $_out $err $success gcc_options* "-c" c_filename "-o" o_filename
  // 385:   unless success:
  // 386:     Error "
  // 387:       Failed to compile @(c_filename)
  // 388:       @(err.from_utf8)
  // 389:   !do_link true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__70_2(void) {
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
  // 401: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__70_3;
}
static void cont__70_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 401: $meta_path truncate_from(mod_filename '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[11] /* temp__1 */;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__70_4;
}
static void cont__70_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* meta_path */, arguments->slots[0]);
  // 402: ... dup(".meta" meta_level)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__66_16;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* meta_level */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__70_5;
}
static void cont__70_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 402: $filename string(mod_filename dup(".meta" meta_level))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = frame->slots[11] /* temp__1 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__70_6;
}
static void cont__70_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* filename */, arguments->slots[0]);
  // 403: $meta_filename string(filename ".sim")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* filename */;
  arguments->slots[1] = string__66_13;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__70_7;
}
static void cont__70_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* meta_filename */, arguments->slots[0]);
  // 404: ... dup(".meta" meta_level)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__66_16;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* meta_level */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__70_8;
}
static void cont__70_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 404: $meta_c_filename string(mod_filename dup(".meta" meta_level) ".c")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = frame->slots[11] /* temp__1 */;
  arguments->slots[2] = string__70_9;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__70_10;
}
static void cont__70_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* meta_c_filename */, arguments->slots[0]);
  // 405: ... meta_level-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* meta_level */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__70_11;
}
static void cont__70_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__2 */ = arguments->slots[0];
  // 405: ... dup(".meta" meta_level-1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__66_16;
  arguments->slots[1] = frame->slots[12] /* temp__2 */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__70_12;
}
static void cont__70_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 405: $sim_filename string(mod_filename dup(".meta" meta_level-1) ".sim")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = frame->slots[11] /* temp__1 */;
  arguments->slots[2] = string__66_13;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__70_13;
}
static void cont__70_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* sim_filename */, arguments->slots[0]);
  // 406: $meta_info stat(meta_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* meta_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__70_14;
}
static void cont__70_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[7] /* meta_info */, arguments->slots[0]);
  // 407: $sim_info stat(sim_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* sim_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__70_15;
}
static void cont__70_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[8] /* sim_info */, arguments->slots[0]);
  // 408: $meta_c_info stat(meta_c_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* meta_c_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__70_16;
}
static void cont__70_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[9] /* meta_c_info */, arguments->slots[0]);
  frame->slots[11] /* temp__1 */ = create_closure(entry__70_17, 0);
  // 410: $$force_rebuild
  // 411:   ||
  // 412:     do_rebuild
  // 413:     sim_info.is_undefined
  // 414:     meta_c_info.is_undefined
  // 415:     modification_time_of(meta_info) > modification_time_of(meta_c_info)
  // 416:     modification_time_of(meta_c_info) > modification_time_of(sim_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_rebuild;
  arguments->slots[1] = frame->slots[11] /* temp__1 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__70_32;
}
static void entry__70_17(void) {
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
  // 413: sim_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* sim_info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__70_18;
}
static void cont__70_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  frame->slots[5] /* temp__3 */ = create_closure(entry__70_19, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__70_31;
}
static void entry__70_19(void) {
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
  // 414: meta_c_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* meta_c_info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__70_20;
}
static void cont__70_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  frame->slots[5] /* temp__3 */ = create_closure(entry__70_21, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__70_30;
}
static void entry__70_21(void) {
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
  // 415: ... modification_time_of(meta_c_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* meta_c_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__70_22;
}
static void cont__70_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 415: modification_time_of(meta_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* meta_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__70_23;
}
static void cont__70_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__4 */ = arguments->slots[0];
  // 415: modification_time_of(meta_info) > modification_time_of(meta_c_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__70_24;
}
static void cont__70_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 416: modification_time_of(meta_c_info) > modification_time_of(sim_info)
  frame->slots[7] /* temp__5 */ = create_closure(entry__70_25, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__5 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__70_29;
}
static void entry__70_25(void) {
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
  // 416: ... modification_time_of(sim_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* sim_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__70_26;
}
static void cont__70_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 416: modification_time_of(meta_c_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* meta_c_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__70_27;
}
static void cont__70_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 416: modification_time_of(meta_c_info) > modification_time_of(sim_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__70_28;
}
static void cont__70_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 416: modification_time_of(meta_c_info) > modification_time_of(sim_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__70_29(void) {
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
static void cont__70_30(void) {
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
static void cont__70_31(void) {
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
static void cont__70_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[10])->contents /* force_rebuild */ = arguments->slots[0];
  // 418: ... :
  // 419:   $modification_time modification_time_of(sim_info)
  // 420:   load $meta_c_buf meta_c_filename
  // 421:   do: (-> break)
  // 422:     for_each_line meta_c_buf: ($line)
  // 423:       $check: (data_filename)
  // 424:         $data_info stat(data_filename)
  // 425:         if
  // 426:           ||
  // 427:             data_info.is_undefined
  // ...
  frame->slots[11] /* temp__1 */ = create_closure(entry__70_33, 0);
  // 418: unless force_rebuild:
  // 419:   $modification_time modification_time_of(sim_info)
  // 420:   load $meta_c_buf meta_c_filename
  // 421:   do: (-> break)
  // 422:     for_each_line meta_c_buf: ($line)
  // 423:       $check: (data_filename)
  // 424:         $data_info stat(data_filename)
  // 425:         if
  // 426:           ||
  // 427:             data_info.is_undefined
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[10])->contents /* force_rebuild */;
  arguments->slots[1] = frame->slots[11] /* temp__1 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__70_66;
}
static void entry__70_36(void) {
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
  // 422: ... : ($line)
  // 423:   $check: (data_filename)
  // 424:     $data_info stat(data_filename)
  // 425:     if
  // 426:       ||
  // 427:         data_info.is_undefined
  // 428:         modification_time_of(data_info) > modification_time
  // 429:       :
  // 430:         !force_rebuild true
  // 431:         break
  // ...
  frame->slots[5] /* temp__1 */ = create_closure(entry__70_37, 1);
  // 422: for_each_line meta_c_buf: ($line)
  // 423:   $check: (data_filename)
  // 424:     $data_info stat(data_filename)
  // 425:     if
  // 426:       ||
  // 427:         data_info.is_undefined
  // 428:         modification_time_of(data_info) > modification_time
  // 429:       :
  // 430:         !force_rebuild true
  // 431:         break
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* meta_c_buf */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each_line();
  func = myself->type;
  frame->cont = cont__70_65;
}
static void entry__70_63(void) {
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
  // 443: ... string(path '/' argument)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* path */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[2] /* argument */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__70_64;
}
static void cont__70_64(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 443: ... check string(path '/' argument)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* check */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__70_58(void) {
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
  // 441: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__70_59;
}
static void cont__70_59(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 441: ... range(argument 2 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* argument */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__70_60;
}
static void cont__70_60(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 441: ... string(meta_path range(argument 2 -1))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* meta_path */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__70_61;
}
static void cont__70_61(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 441: check string(meta_path range(argument 2 -1))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* check */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__70_62(void) {
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
  // 443: ... : (path) check string(path '/' argument)
  frame->slots[2] /* temp__1 */ = create_closure(entry__70_63, 1);
  // 443: for_each simdatapaths: (path) check string(path '/' argument)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._simdatapaths;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__70_55(void) {
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
  // 440: argument .has_prefix. "./"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* argument */;
  arguments->slots[1] = string__70_56;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__70_57;
}
static void cont__70_57(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 440: ... :
  // 441:   check string(meta_path range(argument 2 -1))
  frame->slots[4] /* temp__2 */ = create_closure(entry__70_58, 0);
  // 442: :
  // 443:   for_each simdatapaths: (path) check string(path '/' argument)
  frame->slots[5] /* temp__3 */ = create_closure(entry__70_62, 0);
  // 439: if
  // 440:   argument .has_prefix. "./":
  // 441:     check string(meta_path range(argument 2 -1))
  // 442:   :
  // 443:     for_each simdatapaths: (path) check string(path '/' argument)
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
static void entry__70_37(void) {
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
  // 423: ... : (data_filename)
  // 424:   $data_info stat(data_filename)
  // 425:   if
  // 426:     ||
  // 427:       data_info.is_undefined
  // 428:       modification_time_of(data_info) > modification_time
  // 429:     :
  // 430:       !force_rebuild true
  // 431:       break
  frame->slots[8] /* temp__1 */ = create_closure(entry__70_38_check, 1);
  // 423: $check: (data_filename)
  // 424:   $data_info stat(data_filename)
  // 425:   if
  // 426:     ||
  // 427:       data_info.is_undefined
  // 428:       modification_time_of(data_info) > modification_time
  // 429:     :
  // 430:       !force_rebuild true
  // 431:       break
  initialize_future(frame->slots[5] /* check */, frame->slots[8] /* temp__1 */);
  // 433: ... line .has_prefix. "/// "
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  arguments->slots[1] = string__70_46;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__70_47;
}
static void entry__70_45(void) {
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
  // 430: !force_rebuild true
  ((CELL *)frame->slots[0])->contents /* force_rebuild */ = get__true();
  // 431: break
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* break */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__70_38_check(void) {
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
  // 424: $data_info stat(data_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* data_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__70_39;
}
static void cont__70_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* data_info */, arguments->slots[0]);
  // 427: data_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* data_info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__70_40;
}
static void cont__70_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 428: modification_time_of(data_info) > modification_time
  frame->slots[7] /* temp__3 */ = create_closure(entry__70_41, 0);
  // 426: ||
  // 427:   data_info.is_undefined
  // 428:   modification_time_of(data_info) > modification_time
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__70_44;
}
static void entry__70_41(void) {
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
  // 428: modification_time_of(data_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* data_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__70_42;
}
static void cont__70_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 428: modification_time_of(data_info) > modification_time
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* modification_time */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__70_43;
}
static void cont__70_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 428: modification_time_of(data_info) > modification_time
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__70_44(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 429: :
  // 430:   !force_rebuild true
  // 431:   break
  frame->slots[8] /* temp__4 */ = create_closure(entry__70_45, 0);
  // 425: if
  // 426:   ||
  // 427:     data_info.is_undefined
  // 428:     modification_time_of(data_info) > modification_time
  // 429:   :
  // 430:     !force_rebuild true
  // 431:     break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__70_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 433: unless line .has_prefix. "/// " break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* break */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__70_48;
}
static void cont__70_48(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 434: behind &line ' '
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  arguments->slots[1] = character__32;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__70_49;
}
static void cont__70_49(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* line */ = arguments->slots[0];
  // 435: trim &line
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__70_50;
}
static void cont__70_50(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* line */ = arguments->slots[0];
  // 436: $command line .truncate_from. WHITESPACE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  arguments->slots[1] = var._WHITESPACE;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__70_51;
}
static void cont__70_51(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* command */, arguments->slots[0]);
  // 437: $argument line .behind. WHITESPACE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  arguments->slots[1] = var._WHITESPACE;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__70_52;
}
static void cont__70_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[7] /* argument */, arguments->slots[0]);
  // 438: ... command == "data"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* command */;
  arguments->slots[1] = string__70_53;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__70_54;
}
static void cont__70_54(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 438: ... :
  // 439:   if
  // 440:     argument .has_prefix. "./":
  // 441:       check string(meta_path range(argument 2 -1))
  // 442:     :
  // 443:       for_each simdatapaths: (path) check string(path '/' argument)
  frame->slots[9] /* temp__2 */ = create_closure(entry__70_55, 0);
  // 438: if command == "data":
  // 439:   if
  // 440:     argument .has_prefix. "./":
  // 441:       check string(meta_path range(argument 2 -1))
  // 442:     :
  // 443:       for_each simdatapaths: (path) check string(path '/' argument)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__70_65(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__70_33(void) {
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
  // 419: $modification_time modification_time_of(sim_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* sim_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__70_34;
}
static void cont__70_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* modification_time */, arguments->slots[0]);
  // 420: load $meta_c_buf meta_c_filename
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* meta_c_filename */;
  result_count = 1;
  myself = get__load();
  func = myself->type;
  frame->cont = cont__70_35;
}
static void cont__70_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* meta_c_buf */, arguments->slots[0]);
  // 421: ... : (-> break)
  // 422:   for_each_line meta_c_buf: ($line)
  // 423:     $check: (data_filename)
  // 424:       $data_info stat(data_filename)
  // 425:       if
  // 426:         ||
  // 427:           data_info.is_undefined
  // 428:           modification_time_of(data_info) > modification_time
  // 429:         :
  // 430:           !force_rebuild true
  // ...
  frame->slots[6] /* temp__1 */ = create_closure(entry__70_36, 0);
  // 421: do: (-> break)
  // 422:   for_each_line meta_c_buf: ($line)
  // 423:     $check: (data_filename)
  // 424:       $data_info stat(data_filename)
  // 425:       if
  // 426:         ||
  // 427:           data_info.is_undefined
  // 428:           modification_time_of(data_info) > modification_time
  // 429:         :
  // 430:           !force_rebuild true
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__do();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__70_66(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 444: ... :
  // 445:   %on_top_level false
  // 446:   %%objects empty_insert_order_set
  // 447:   %%libraries empty_insert_order_set
  // 448:   %%do_link false
  // 449:   %%last_modification_time undefined
  // 450:   %do_build_static_executable false
  // 451:   %main_filename meta_filename
  // 452:   %main_info stat(main_filename)
  // 453:   build_executable
  // ...
  frame->slots[11] /* temp__1 */ = create_closure(entry__70_67, 0);
  // 444: if force_rebuild:
  // 445:   %on_top_level false
  // 446:   %%objects empty_insert_order_set
  // 447:   %%libraries empty_insert_order_set
  // 448:   %%do_link false
  // 449:   %%last_modification_time undefined
  // 450:   %do_build_static_executable false
  // 451:   %main_filename meta_filename
  // 452:   %main_info stat(main_filename)
  // 453:   build_executable
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[10])->contents /* force_rebuild */;
  arguments->slots[1] = frame->slots[11] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__70_79;
}
static void entry__70_67(void) {
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
  // 445: %on_top_level false
  initialize_maybe_future(get__on_top_level(), get__false());
  // 446: %%objects empty_insert_order_set
  set__objects(get__empty_insert_order_set());
  // 447: %%libraries empty_insert_order_set
  set__libraries(get__empty_insert_order_set());
  // 448: %%do_link false
  set__do_link(get__false());
  // 449: %%last_modification_time undefined
  set__last_modification_time(get__undefined());
  // 450: %do_build_static_executable false
  initialize_maybe_future(get__do_build_static_executable(), get__false());
  // 451: %main_filename meta_filename
  initialize_maybe_future(get__main_filename(), frame->slots[1] /* meta_filename */);
  // 452: %main_info stat(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__70_68;
}
static void cont__70_68(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(get__main_info(), arguments->slots[0]);
  // 453: build_executable
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._build_executable;
  func = myself->type;
  frame->cont = cont__70_69;
}
static void cont__70_69(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 454: $orig_path current_path()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__current_path();
  func = myself->type;
  frame->cont = cont__70_70;
}
static void cont__70_70(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* orig_path */, arguments->slots[0]);
  // 455: change_directory meta_path
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* meta_path */;
  result_count = 0;
  myself = get__change_directory();
  func = myself->type;
  frame->cont = cont__70_71;
}
static void cont__70_71(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 456: std::call $out $err $success filename
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* filename */;
  result_count = 3;
  myself = get__std__call();
  func = myself->type;
  frame->cont = cont__70_72;
}
static void cont__70_72(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  frame->slots[10] /* temp__2 */ = arguments->slots[1];
  frame->slots[11] /* temp__3 */ = arguments->slots[2];
  // 456: ... out
  initialize_future(frame->slots[6] /* out */, frame->slots[9] /* temp__1 */);
  // 456: ... err
  initialize_future(frame->slots[7] /* err */, frame->slots[10] /* temp__2 */);
  // 456: ... success
  initialize_future(frame->slots[8] /* success */, frame->slots[11] /* temp__3 */);
  // 457: change_directory orig_path
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* orig_path */;
  result_count = 0;
  myself = get__change_directory();
  func = myself->type;
  frame->cont = cont__70_73;
}
static void cont__70_73(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 458: ... : Error err.from_utf8
  frame->slots[9] /* temp__1 */ = create_closure(entry__70_74, 0);
  // 458: unless success: Error err.from_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* success */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__70_76;
}
static void entry__70_74(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // err: 0
  frame->slots[0] = myself->closure.frame->slots[7]; /* err */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 458: ... err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* err */;
  result_count = 1;
  myself = get__from_utf8();
  func = myself->type;
  frame->cont = cont__70_75;
}
static void cont__70_75(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 458: ... Error err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__70_76(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 459: ... out.to_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* out */;
  result_count = 1;
  myself = get__to_utf8();
  func = myself->type;
  frame->cont = cont__70_77;
}
static void cont__70_77(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 459: save sim_filename out.to_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* sim_filename */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__save();
  func = myself->type;
  frame->cont = cont__70_78;
}
static void cont__70_78(void) {
  myself = frame->slots[0] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__70_79(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 460: dec &meta_level
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* meta_level */;
  result_count = 1;
  myself = get__dec();
  func = myself->type;
  frame->cont = cont__70_80;
}
static void cont__70_80(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* meta_level */ = arguments->slots[0];
  // 461: ... meta_level > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* meta_level */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__70_81;
}
static void cont__70_81(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 461: -> meta_level > 0
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__70_1_compile_meta_module(void) {
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
  // 400: ... :
  // 401:   $meta_path truncate_from(mod_filename '/' -1)
  // 402:   $filename string(mod_filename dup(".meta" meta_level))
  // 403:   $meta_filename string(filename ".sim")
  // 404:   $meta_c_filename string(mod_filename dup(".meta" meta_level) ".c")
  // 405:   $sim_filename string(mod_filename dup(".meta" meta_level-1) ".sim")
  // 406:   $meta_info stat(meta_filename)
  // 407:   $sim_info stat(sim_filename)
  // 408:   $meta_c_info stat(meta_c_filename)
  // 409:   
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__70_2, 0);
  // 400: do_while:
  // 401:   $meta_path truncate_from(mod_filename '/' -1)
  // 402:   $filename string(mod_filename dup(".meta" meta_level))
  // 403:   $meta_filename string(filename ".sim")
  // 404:   $meta_c_filename string(mod_filename dup(".meta" meta_level) ".c")
  // 405:   $sim_filename string(mod_filename dup(".meta" meta_level-1) ".sim")
  // 406:   $meta_info stat(meta_filename)
  // 407:   $sim_info stat(sim_filename)
  // 408:   $meta_c_info stat(meta_c_filename)
  // 409:   
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__do_while();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__71_1_build_dependencies(void) {
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
  // 474: ... : ($line)
  // 475:   unless line .has_prefix. "/// " return
  // 476:   behind &line ' '
  // 477:   trim &line
  // 478:   $command line .truncate_from. WHITESPACE
  // 479:   $argument line .behind. WHITESPACE
  // 480:   case
  // 481:     command
  // 482:     "require":
  // 483:       if
  // ...
  frame->slots[5] /* temp__1 */ = create_closure(entry__71_2, 1);
  // 474: for_each_line c_buf: ($line)
  // 475:   unless line .has_prefix. "/// " return
  // 476:   behind &line ' '
  // 477:   trim &line
  // 478:   $command line .truncate_from. WHITESPACE
  // 479:   $argument line .behind. WHITESPACE
  // 480:   case
  // 481:     command
  // 482:     "require":
  // 483:       if
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* c_buf */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each_line();
  func = myself->type;
  frame->cont = cont__71_41;
}
static void entry__71_36(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // argument: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 502: ... !libraries(argument .truncate_from. '/') true
  frame->slots[1] /* temp__1 */ = get__true();
  // 502: ... argument .truncate_from. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* argument */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__71_37;
}
static void cont__71_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 502: ... !libraries(argument .truncate_from. '/')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__libraries();
  func = myself->type;
  frame->cont = cont__71_38;
}
static void cont__71_38(void) {
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
static void entry__71_30(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // argument: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 500: !libraries(string("sim-" argument .truncate_from. '/')) true
  frame->slots[1] /* temp__1 */ = get__true();
  // 500: ... argument .truncate_from. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* argument */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__71_31;
}
static void cont__71_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 500: ... string("sim-" argument .truncate_from. '/')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__71_32;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__71_33;
}
static void cont__71_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 500: !libraries(string("sim-" argument .truncate_from. '/'))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__libraries();
  func = myself->type;
  frame->cont = cont__71_34;
}
static void cont__71_34(void) {
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
static void entry__71_27(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // argument: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 497: ... resolve_filename(argument)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* argument */;
  result_count = 1;
  myself = var._resolve_filename;
  func = myself->type;
  frame->cont = cont__71_28;
}
static void cont__71_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 497: compile_module resolve_filename(argument) argument
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[0] /* argument */;
  result_count = frame->caller_result_count;
  myself = var._compile_module;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__71_29(void) {
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
  // 499: ... :
  // 500:   !libraries(string("sim-" argument .truncate_from. '/')) true
  frame->slots[2] /* temp__1 */ = create_closure(entry__71_30, 0);
  // 499: if do_compile_c:
  // 500:   !libraries(string("sim-" argument .truncate_from. '/')) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* do_compile_c */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__71_13(void) {
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
  // 486: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__71_14;
}
static void cont__71_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 486: $req_name range(argument 3 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* argument */;
  arguments->slots[1] = number__3;
  arguments->slots[2] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__71_15;
}
static void cont__71_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* req_name */, arguments->slots[0]);
  // 488: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__71_16;
}
static void cont__71_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 488: ... until(mod_filename '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* mod_filename */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count = 1;
  myself = get__until();
  func = myself->type;
  frame->cont = cont__71_17;
}
static void cont__71_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 488: string(until(mod_filename '/' -1) req_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* req_name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__71_18;
}
static void cont__71_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 489: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__71_19;
}
static void cont__71_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__6 */ = arguments->slots[0];
  // 489: ... until(mod_name '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* mod_name */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[9] /* temp__6 */;
  result_count = 1;
  myself = get__until();
  func = myself->type;
  frame->cont = cont__71_20;
}
static void cont__71_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__5 */ = arguments->slots[0];
  // 489: string(until(mod_name '/' -1) req_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__5 */;
  arguments->slots[1] = frame->slots[3] /* req_name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__71_21;
}
static void cont__71_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__4 */ = arguments->slots[0];
  // 487: compile_module
  // 488:   string(until(mod_filename '/' -1) req_name)
  // 489:   string(until(mod_name '/' -1) req_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = var._compile_module;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__71_11(void) {
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
  // 485: ... mode == EXE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__mode();
  arguments->slots[1] = var._EXE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__71_12;
}
static void cont__71_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 485: ... :
  // 486:   $req_name range(argument 3 -1)
  // 487:   compile_module
  // 488:     string(until(mod_filename '/' -1) req_name)
  // 489:     string(until(mod_name '/' -1) req_name)
  frame->slots[4] /* temp__2 */ = create_closure(entry__71_13, 0);
  // 485: if mode == EXE:
  // 486:   $req_name range(argument 3 -1)
  // 487:   compile_module
  // 488:     string(until(mod_filename '/' -1) req_name)
  // 489:     string(until(mod_name '/' -1) req_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__71_22(void) {
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
  arguments->slots[1] = func__71_23;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__71_26;
}
static void entry__71_23(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_build_codeblocks_project;
  arguments->slots[1] = func__71_24;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__71_25;
}
static void entry__71_24(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 495: do_list_dependencies
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._do_list_dependencies;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__71_25(void) {
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
static void cont__71_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 496: :
  // 497:   compile_module resolve_filename(argument) argument
  frame->slots[3] /* temp__2 */ = create_closure(entry__71_27, 0);
  // 498: :
  // 499:   if do_compile_c:
  // 500:     !libraries(string("sim-" argument .truncate_from. '/')) true
  frame->slots[4] /* temp__3 */ = create_closure(entry__71_29, 0);
  // 491: if
  // 492:   ||
  // 493:     do_build_static_executable
  // 494:     do_build_codeblocks_project
  // 495:     do_list_dependencies
  // 496:   :
  // 497:     compile_module resolve_filename(argument) argument
  // 498:   :
  // 499:     if do_compile_c:
  // 500:       !libraries(string("sim-" argument .truncate_from. '/')) true
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
static void entry__71_9(void) {
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
  // 484: argument .has_prefix. "./"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* argument */;
  arguments->slots[1] = string__70_56;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__71_10;
}
static void cont__71_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 484: ... :
  // 485:   if mode == EXE:
  // 486:     $req_name range(argument 3 -1)
  // 487:     compile_module
  // 488:       string(until(mod_filename '/' -1) req_name)
  // 489:       string(until(mod_name '/' -1) req_name)
  frame->slots[5] /* temp__2 */ = create_closure(entry__71_11, 0);
  // 490: :
  // 491:   if
  // 492:     ||
  // 493:       do_build_static_executable
  // 494:       do_build_codeblocks_project
  // 495:       do_list_dependencies
  // 496:     :
  // 497:       compile_module resolve_filename(argument) argument
  // 498:     :
  // 499:       if do_compile_c:
  // ...
  frame->slots[6] /* temp__3 */ = create_closure(entry__71_22, 0);
  // 483: if
  // 484:   argument .has_prefix. "./":
  // 485:     if mode == EXE:
  // 486:       $req_name range(argument 3 -1)
  // 487:       compile_module
  // 488:         string(until(mod_filename '/' -1) req_name)
  // 489:         string(until(mod_name '/' -1) req_name)
  // 490:   :
  // 491:     if
  // 492:       ||
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
static void entry__71_35(void) {
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
  // 502: ... : !libraries(argument .truncate_from. '/') true
  frame->slots[2] /* temp__1 */ = create_closure(entry__71_36, 0);
  // 502: if do_compile_c: !libraries(argument .truncate_from. '/') true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* do_compile_c */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__71_2(void) {
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
  // 475: ... line .has_prefix. "/// "
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  arguments->slots[1] = string__70_46;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__71_3;
}
static void cont__71_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 475: unless line .has_prefix. "/// " return
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* return */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__71_4;
}
static void cont__71_4(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 476: behind &line ' '
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  arguments->slots[1] = character__32;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__71_5;
}
static void cont__71_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* line */ = arguments->slots[0];
  // 477: trim &line
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__71_6;
}
static void cont__71_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* line */ = arguments->slots[0];
  // 478: $command line .truncate_from. WHITESPACE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  arguments->slots[1] = var._WHITESPACE;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__71_7;
}
static void cont__71_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* command */, arguments->slots[0]);
  // 479: $argument line .behind. WHITESPACE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  arguments->slots[1] = var._WHITESPACE;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__71_8;
}
static void cont__71_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* argument */, arguments->slots[0]);
  // 482: ... :
  // 483:   if
  // 484:     argument .has_prefix. "./":
  // 485:       if mode == EXE:
  // 486:         $req_name range(argument 3 -1)
  // 487:         compile_module
  // 488:           string(until(mod_filename '/' -1) req_name)
  // 489:           string(until(mod_name '/' -1) req_name)
  // 490:     :
  // 491:       if
  // ...
  frame->slots[7] /* temp__1 */ = create_closure(entry__71_9, 0);
  // 501: ... :
  // 502:   if do_compile_c: !libraries(argument .truncate_from. '/') true
  frame->slots[8] /* temp__2 */ = create_closure(entry__71_35, 0);
  // 480: case
  // 481:   command
  // 482:   "require":
  // 483:     if
  // 484:       argument .has_prefix. "./":
  // 485:         if mode == EXE:
  // 486:           $req_name range(argument 3 -1)
  // 487:           compile_module
  // 488:             string(until(mod_filename '/' -1) req_name)
  // 489:             string(until(mod_name '/' -1) req_name)
  // ...
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* command */;
  arguments->slots[1] = string__71_39;
  arguments->slots[2] = frame->slots[7] /* temp__1 */;
  arguments->slots[3] = string__71_40;
  arguments->slots[4] = frame->slots[8] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__71_41(void) {
  myself = frame->slots[4] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__72_1_compile_module(void) {
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
  // 513: ... :
  // 514:   (
  // 515:     submodule_names # no paths; no extensions
  // 516:     do_compile_c = true
  // 517:     suffix = "" # a hyphen followed by the platform name
  // 518:   )
  // 519:   $$modification_time undefined
  // 520:   $$sim_filenames empty_list
  // 521:   for_each submodule_names: (submodule_name)
  // 522:     $meta_level meta_levels(submodule_name)
  // ...
  frame->slots[6] /* temp__1 */ = create_closure(entry__72_2_compile_submodule, -1);
  // 513: $compile_submodule:
  // 514:   (
  // 515:     submodule_names # no paths; no extensions
  // 516:     do_compile_c = true
  // 517:     suffix = "" # a hyphen followed by the platform name
  // 518:   )
  // 519:   $$modification_time undefined
  // 520:   $$sim_filenames empty_list
  // 521:   for_each submodule_names: (submodule_name)
  // 522:     $meta_level meta_levels(submodule_name)
  // ...
  initialize_future(frame->slots[3] /* compile_submodule */, frame->slots[6] /* temp__1 */);
  // 569: lookup $mod_info mod_filename mod_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = frame->slots[1] /* mod_name */;
  result_count = 1;
  myself = var._lookup;
  func = myself->type;
  frame->cont = cont__72_73;
}
static void entry__72_2_compile_submodule(void) {
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
  // 519: $$modification_time undefined
  ((CELL *)frame->slots[6])->contents /* modification_time */ = get__undefined();
  // 520: $$sim_filenames empty_list
  ((CELL *)frame->slots[7])->contents /* sim_filenames */ = get__empty_list();
  // 521: ... : (submodule_name)
  // 522:   $meta_level meta_levels(submodule_name)
  // 523:   $submodule_filename string(until(mod_filename '/' -1) submodule_name)
  // 524:   if meta_level > 0 && not(do_omit_meta):
  // 525:     compile_meta_module submodule_filename submodule_name meta_level
  // 526:   $sim_filename string(submodule_filename ".sim")
  // 527:   push &sim_filenames sim_filename
  // 528:   $sim_info stat(sim_filename)
  // 529:   if
  // 530:     ||
  // ...
  frame->slots[11] /* temp__1 */ = create_closure(entry__72_3, 1);
  // 521: for_each submodule_names: (submodule_name)
  // 522:   $meta_level meta_levels(submodule_name)
  // 523:   $submodule_filename string(until(mod_filename '/' -1) submodule_name)
  // 524:   if meta_level > 0 && not(do_omit_meta):
  // 525:     compile_meta_module submodule_filename submodule_name meta_level
  // 526:   $sim_filename string(submodule_filename ".sim")
  // 527:   push &sim_filenames sim_filename
  // 528:   $sim_info stat(sim_filename)
  // 529:   if
  // 530:     ||
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* submodule_names */;
  arguments->slots[1] = frame->slots[11] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__72_24;
}
static void entry__72_22(void) {
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
  // 534: !modification_time modification_time_of(sim_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* sim_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__72_23;
}
static void cont__72_23(void) {
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
static void entry__72_3(void) {
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
  // 522: $meta_level meta_levels(submodule_name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* submodule_name */;
  result_count = 1;
  myself = var._meta_levels;
  func = myself->type;
  frame->cont = cont__72_4;
}
static void cont__72_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* meta_level */, arguments->slots[0]);
  // 523: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__72_5;
}
static void cont__72_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__2 */ = arguments->slots[0];
  // 523: ... until(mod_filename '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* mod_filename */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[9] /* temp__2 */;
  result_count = 1;
  myself = get__until();
  func = myself->type;
  frame->cont = cont__72_6;
}
static void cont__72_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 523: $submodule_filename string(until(mod_filename '/' -1) submodule_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = frame->slots[0] /* submodule_name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__72_7;
}
static void cont__72_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* submodule_filename */, arguments->slots[0]);
  // 524: ... meta_level > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = frame->slots[4] /* meta_level */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__72_8;
}
static void cont__72_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__2 */ = arguments->slots[0];
  // 524: ... meta_level > 0 && not(do_omit_meta)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__2 */;
  arguments->slots[1] = func__72_9;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__72_11;
}
static void entry__72_9(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 524: ... not(do_omit_meta)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._do_omit_meta;
  result_count = 1;
  myself = get__not();
  func = myself->type;
  frame->cont = cont__72_10;
}
static void cont__72_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 524: ... not(do_omit_meta)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__72_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 524: ... :
  // 525:   compile_meta_module submodule_filename submodule_name meta_level
  frame->slots[10] /* temp__3 */ = create_closure(entry__72_12, 0);
  // 524: if meta_level > 0 && not(do_omit_meta):
  // 525:   compile_meta_module submodule_filename submodule_name meta_level
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__72_13;
}
static void entry__72_12(void) {
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
  // 525: compile_meta_module submodule_filename submodule_name meta_level
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
static void cont__72_13(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 526: $sim_filename string(submodule_filename ".sim")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* submodule_filename */;
  arguments->slots[1] = string__66_13;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__72_14;
}
static void cont__72_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* sim_filename */, arguments->slots[0]);
  // 527: push &sim_filenames sim_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* sim_filenames */;
  arguments->slots[1] = frame->slots[6] /* sim_filename */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__72_15;
}
static void cont__72_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* sim_filenames */ = arguments->slots[0];
  // 528: $sim_info stat(sim_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* sim_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__72_16;
}
static void cont__72_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[7] /* sim_info */, arguments->slots[0]);
  // 531: modification_time.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* modification_time */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__72_17;
}
static void cont__72_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__2 */ = arguments->slots[0];
  // 532: modification_time_of(sim_info) > modification_time
  frame->slots[10] /* temp__3 */ = create_closure(entry__72_18, 0);
  // 530: ||
  // 531:   modification_time.is_undefined
  // 532:   modification_time_of(sim_info) > modification_time
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__2 */;
  arguments->slots[1] = frame->slots[10] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__72_21;
}
static void entry__72_18(void) {
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
  // 532: modification_time_of(sim_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* sim_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__72_19;
}
static void cont__72_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 532: modification_time_of(sim_info) > modification_time
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* modification_time */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__72_20;
}
static void cont__72_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 532: modification_time_of(sim_info) > modification_time
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__72_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 533: :
  // 534:   !modification_time modification_time_of(sim_info)
  frame->slots[11] /* temp__4 */ = create_closure(entry__72_22, 0);
  // 529: if
  // 530:   ||
  // 531:     modification_time.is_undefined
  // 532:     modification_time_of(sim_info) > modification_time
  // 533:   :
  // 534:     !modification_time modification_time_of(sim_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = frame->slots[11] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__72_24(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 535: $c_filename string(mod_filename suffix ".c")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* mod_filename */;
  arguments->slots[1] = frame->slots[2] /* suffix */;
  arguments->slots[2] = string__70_9;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__72_25;
}
static void cont__72_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[8] /* c_filename */, arguments->slots[0]);
  // 536: $c_info stat(c_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* c_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__72_26;
}
static void cont__72_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[9] /* c_info */, arguments->slots[0]);
  // 537: ... : !c_sources(c_filename) true
  frame->slots[11] /* temp__1 */ = create_closure(entry__72_27, 0);
  // 537: if do_compile_c: !c_sources(c_filename) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* do_compile_c */;
  arguments->slots[1] = frame->slots[11] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__72_29;
}
static void entry__72_27(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // c_filename: 0
  frame->slots[0] = myself->closure.frame->slots[8]; /* c_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 537: ... !c_sources(c_filename) true
  frame->slots[1] /* temp__1 */ = get__true();
  // 537: ... !c_sources(c_filename)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_filename */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = var._c_sources;
  func = myself->type;
  frame->cont = cont__72_28;
}
static void cont__72_28(void) {
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
static void cont__72_29(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 538: $$c_buf undefined
  ((CELL *)frame->slots[10])->contents /* c_buf */ = get__undefined();
  frame->slots[12] /* temp__2 */ = create_closure(entry__72_30, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_rebuild;
  arguments->slots[1] = frame->slots[12] /* temp__2 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__72_36;
}
static void entry__72_30(void) {
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
  // 542: c_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__72_31;
}
static void cont__72_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 543: modification_time > modification_time_of(c_info)
  frame->slots[4] /* temp__3 */ = create_closure(entry__72_32, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__72_35;
}
static void entry__72_32(void) {
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
  // 543: ... modification_time_of(c_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__72_33;
}
static void cont__72_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 543: modification_time > modification_time_of(c_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* modification_time */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__72_34;
}
static void cont__72_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 543: modification_time > modification_time_of(c_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__72_35(void) {
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
static void cont__72_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 544: :
  // 545:   %sim2c::module_name replace_all(mod_name '/' = "__" '.' = "__")
  // 546:   if verbose: ewriteln "build module " module_name suffix
  // 547:   collect_output $c_source: sim2c sim_filenames
  // 548:   collect_output !c_buf: create_imports c_source
  // 549:   save c_filename c_buf.to_utf8
  // 550:   if do_compile_c: compile_c c_filename o_filename
  frame->slots[13] /* temp__3 */ = create_closure(entry__72_37, 0);
  // 551: :
  // 552:   load !c_buf c_filename
  // 553:   $o_info stat(o_filename)
  // 554:   if
  // 555:     ||
  // 556:       o_info.is_undefined
  // 557:       modification_time_of(c_info) > modification_time_of(o_info)
  // 558:     :
  // 559:       if do_compile_c: compile_c c_filename o_filename
  // 560:     :
  // ...
  frame->slots[14] /* temp__4 */ = create_closure(entry__72_53, 0);
  // 539: if
  // 540:   ||
  // 541:     do_rebuild
  // 542:     c_info.is_undefined
  // 543:     modification_time > modification_time_of(c_info)
  // 544:   :
  // 545:     %sim2c::module_name replace_all(mod_name '/' = "__" '.' = "__")
  // 546:     if verbose: ewriteln "build module " module_name suffix
  // 547:     collect_output $c_source: sim2c sim_filenames
  // 548:     collect_output !c_buf: create_imports c_source
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  arguments->slots[1] = frame->slots[13] /* temp__3 */;
  arguments->slots[2] = frame->slots[14] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__72_72;
}
static void entry__72_70(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // o_info: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* o_info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 566: !last_modification_time modification_time_of(o_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* o_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__72_71;
}
static void cont__72_71(void) {
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
static void entry__72_63(void) {
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
  // 559: ... compile_c c_filename o_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_filename */;
  arguments->slots[1] = frame->slots[1] /* o_filename */;
  result_count = frame->caller_result_count;
  myself = var._compile_c;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__72_62(void) {
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
  // 559: ... : compile_c c_filename o_filename
  frame->slots[3] /* temp__1 */ = create_closure(entry__72_63, 0);
  // 559: if do_compile_c: compile_c c_filename o_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* do_compile_c */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__72_64(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // o_info: 0
  frame->slots[0] = myself->closure.frame->slots[5]; /* o_info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 563: last_modification_time.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__last_modification_time();
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__72_65;
}
static void cont__72_65(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 564: modification_time_of(o_info) > last_modification_time
  frame->slots[3] /* temp__3 */ = create_closure(entry__72_66, 0);
  // 562: ||
  // 563:   last_modification_time.is_undefined
  // 564:   modification_time_of(o_info) > last_modification_time
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__72_69;
}
static void entry__72_66(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // o_info: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* o_info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 564: modification_time_of(o_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* o_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__72_67;
}
static void cont__72_67(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 564: modification_time_of(o_info) > last_modification_time
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__last_modification_time();
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__72_68;
}
static void cont__72_68(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 564: modification_time_of(o_info) > last_modification_time
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__72_69(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 565: :
  // 566:   !last_modification_time modification_time_of(o_info)
  frame->slots[4] /* temp__4 */ = create_closure(entry__72_70, 0);
  // 561: if
  // 562:   ||
  // 563:     last_modification_time.is_undefined
  // 564:     modification_time_of(o_info) > last_modification_time
  // 565:   :
  // 566:     !last_modification_time modification_time_of(o_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__72_37(void) {
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
  // 545: ... '/' = "__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = string__72_38;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__72_39;
}
static void cont__72_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 545: ... '.' = "__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__46;
  arguments->slots[1] = string__72_38;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__72_40;
}
static void cont__72_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__2 */ = arguments->slots[0];
  // 545: %sim2c::module_name replace_all(mod_name '/' = "__" '.' = "__")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* mod_name */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  arguments->slots[2] = frame->slots[10] /* temp__2 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__72_41;
}
static void cont__72_41(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(get__sim2c__module_name(), arguments->slots[0]);
  // 546: ... : ewriteln "build module " module_name suffix
  frame->slots[9] /* temp__1 */ = create_closure(entry__72_42, 0);
  // 546: if verbose: ewriteln "build module " module_name suffix
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__72_44;
}
static void entry__72_42(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // suffix: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* suffix */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 546: ... ewriteln "build module " module_name suffix
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__72_43;
  arguments->slots[1] = get__module_name();
  arguments->slots[2] = frame->slots[0] /* suffix */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__72_44(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 547: ... : sim2c sim_filenames
  frame->slots[9] /* temp__1 */ = create_closure(entry__72_45, 0);
  // 547: collect_output $c_source: sim2c sim_filenames
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__72_46;
}
static void entry__72_45(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // sim_filenames: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* sim_filenames */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 547: ... sim2c sim_filenames
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* sim_filenames */;
  result_count = frame->caller_result_count;
  myself = get__sim2c();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__72_46(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[8] /* c_source */, arguments->slots[0]);
  // 548: ... : create_imports c_source
  frame->slots[9] /* temp__1 */ = create_closure(entry__72_47, 0);
  // 548: collect_output !c_buf: create_imports c_source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__72_48;
}
static void entry__72_47(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // c_source: 0
  frame->slots[0] = myself->closure.frame->slots[8]; /* c_source */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 548: ... create_imports c_source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_source */;
  result_count = frame->caller_result_count;
  myself = var._create_imports;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__72_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* c_buf */ = arguments->slots[0];
  // 549: ... c_buf.to_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* c_buf */;
  result_count = 1;
  myself = get__to_utf8();
  func = myself->type;
  frame->cont = cont__72_49;
}
static void cont__72_49(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 549: save c_filename c_buf.to_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* c_filename */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 0;
  myself = get__save();
  func = myself->type;
  frame->cont = cont__72_50;
}
static void cont__72_50(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 550: ... : compile_c c_filename o_filename
  frame->slots[9] /* temp__1 */ = create_closure(entry__72_51, 0);
  // 550: if do_compile_c: compile_c c_filename o_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* do_compile_c */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__72_52;
}
static void entry__72_51(void) {
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
  // 550: ... compile_c c_filename o_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_filename */;
  arguments->slots[1] = frame->slots[1] /* o_filename */;
  result_count = frame->caller_result_count;
  myself = var._compile_c;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__72_52(void) {
  myself = frame->slots[0] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__72_53(void) {
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
  // 552: load !c_buf c_filename
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* c_filename */;
  result_count = 1;
  myself = get__load();
  func = myself->type;
  frame->cont = cont__72_54;
}
static void cont__72_54(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* c_buf */ = arguments->slots[0];
  // 553: $o_info stat(o_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* o_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__72_55;
}
static void cont__72_55(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* o_info */, arguments->slots[0]);
  // 556: o_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* o_info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__72_56;
}
static void cont__72_56(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 557: modification_time_of(c_info) > modification_time_of(o_info)
  frame->slots[8] /* temp__3 */ = create_closure(entry__72_57, 0);
  // 555: ||
  // 556:   o_info.is_undefined
  // 557:   modification_time_of(c_info) > modification_time_of(o_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  arguments->slots[1] = frame->slots[8] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__72_61;
}
static void entry__72_57(void) {
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
  // 557: ... modification_time_of(o_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* o_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__72_58;
}
static void cont__72_58(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 557: modification_time_of(c_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* c_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__72_59;
}
static void cont__72_59(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 557: modification_time_of(c_info) > modification_time_of(o_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__72_60;
}
static void cont__72_60(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 557: modification_time_of(c_info) > modification_time_of(o_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__72_61(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 558: :
  // 559:   if do_compile_c: compile_c c_filename o_filename
  frame->slots[9] /* temp__4 */ = create_closure(entry__72_62, 0);
  // 560: :
  // 561:   if
  // 562:     ||
  // 563:       last_modification_time.is_undefined
  // 564:       modification_time_of(o_info) > last_modification_time
  // 565:     :
  // 566:       !last_modification_time modification_time_of(o_info)
  frame->slots[10] /* temp__5 */ = create_closure(entry__72_64, 0);
  // 554: if
  // 555:   ||
  // 556:     o_info.is_undefined
  // 557:     modification_time_of(c_info) > modification_time_of(o_info)
  // 558:   :
  // 559:     if do_compile_c: compile_c c_filename o_filename
  // 560:   :
  // 561:     if
  // 562:       ||
  // 563:         last_modification_time.is_undefined
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
static void cont__72_72(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 567: build_dependencies mod_filename mod_name c_buf do_compile_c
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
static void cont__72_73(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* mod_info */, arguments->slots[0]);
  // 570: ... mod_info.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* mod_info */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__72_74;
}
static void cont__72_74(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 570: ... :
  // 571:   Error "
  // 572:     No source file(s) for module "@(mod_name)" found!@
  frame->slots[7] /* temp__2 */ = create_closure(entry__72_75, 0);
  // 570: unless mod_info.is_defined:
  // 571:   Error "
  // 572:     No source file(s) for module "@(mod_name)" found!@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__72_79;
}
static void entry__72_75(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // mod_name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* mod_name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 571: ... "
  // 572:   No source file(s) for module "@(mod_name)" found!@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__72_76;
  arguments->slots[1] = frame->slots[0] /* mod_name */;
  arguments->slots[2] = string__72_77;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__72_78;
}
static void cont__72_78(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 571: Error "
  // 572:   No source file(s) for module "@(mod_name)" found!@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__72_79(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 573: $o_filename append(mod_filename ".o")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = string__72_80;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__72_81;
}
static void cont__72_81(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* o_filename */, arguments->slots[0]);
  // 574: ... objects(o_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* o_filename */;
  result_count = 1;
  myself = get__objects();
  func = myself->type;
  frame->cont = cont__72_82;
}
static void cont__72_82(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 574: if objects(o_filename) return
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* return */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__72_83;
}
static void cont__72_83(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 575: !objects(o_filename) true
  frame->slots[6] /* temp__1 */ = get__true();
  // 575: !objects(o_filename)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* o_filename */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = get__objects();
  func = myself->type;
  frame->cont = cont__72_84;
}
static void cont__72_84(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__objects(arguments->slots[0]);
  // 577: mod_info.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* mod_info */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__72_85;
}
static void cont__72_85(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 577: ... :
  // 578:   compile_submodule list(truncate_until(mod_name '/' -1))
  // 579:   if do_list_dependencies: push &dependencies string(mod_filename ".c")
  frame->slots[7] /* temp__2 */ = create_closure(entry__72_86, 0);
  // 580: :
  // 581:   do:
  // 582:     $$best_platform undefined
  // 583:     $$best_priority 999
  // 584:     for_each mod_info: (platform _filenames)
  // 585:       $priority platform_priority(platform)
  // 586:       if priority.is_defined && priority < best_priority:
  // 587:         !best_platform platform
  // 588:         !best_priority priority
  // 589:     for_each mod_info: (platform filenames)
  // ...
  frame->slots[8] /* temp__3 */ = create_closure(entry__72_94, 0);
  // 576: if
  // 577:   mod_info.is_empty:
  // 578:     compile_submodule list(truncate_until(mod_name '/' -1))
  // 579:     if do_list_dependencies: push &dependencies string(mod_filename ".c")
  // 580:   :
  // 581:     do:
  // 582:       $$best_platform undefined
  // 583:       $$best_priority 999
  // 584:       for_each mod_info: (platform _filenames)
  // 585:         $priority platform_priority(platform)
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  arguments->slots[2] = frame->slots[8] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__72_135;
}
static void entry__72_125(void) {
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
  // 609: $$dependency string(mod_filename "-" platform ".c")
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* mod_filename */;
  arguments->slots[1] = string__66_46;
  arguments->slots[2] = frame->slots[0] /* platform */;
  arguments->slots[3] = string__70_9;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__72_126;
}
static void cont__72_126(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* dependency */ = arguments->slots[0];
  // 610: $platforms used_by(platform)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* platform */;
  result_count = 1;
  myself = ((CELL *)frame->slots[3])->contents /* used_by */;
  func = myself->type;
  frame->cont = cont__72_127;
}
static void cont__72_127(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* platforms */, arguments->slots[0]);
  // 611: ... platforms.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* platforms */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__72_128;
}
static void cont__72_128(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 611: ... :
  // 612:   for_each platforms: (plat) write_to &dependency " #" plat
  frame->slots[7] /* temp__2 */ = create_closure(entry__72_129, 0);
  // 611: if platforms.is_defined:
  // 612:   for_each platforms: (plat) write_to &dependency " #" plat
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__72_133;
}
static void entry__72_130(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // plat: 0
  // dependency: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* dependency */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 612: ... write_to &dependency " #" plat
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* dependency */;
  arguments->slots[1] = string__72_131;
  arguments->slots[2] = frame->slots[0] /* plat */;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__72_132;
}
static void cont__72_132(void) {
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
static void entry__72_129(void) {
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
  // 612: ... : (plat) write_to &dependency " #" plat
  frame->slots[2] /* temp__1 */ = create_closure(entry__72_130, 1);
  // 612: for_each platforms: (plat) write_to &dependency " #" plat
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* platforms */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__72_133(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 613: push &dependencies dependency
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._dependencies;
  arguments->slots[1] = ((CELL *)frame->slots[4])->contents /* dependency */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__72_134;
}
static void cont__72_134(void) {
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
static void entry__72_108(void) {
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
  // 595: $$used_by empty_table
  ((CELL *)frame->slots[2])->contents /* used_by */ = get__empty_table();
  // 596: ... : (supported_platform _parent_platform)
  // 597:   $$best_platform undefined
  // 598:   $$best_priority 999
  // 599:   for_each mod_info: (platform _filenames)
  // 600:     $priority platform_specific_priority(supported_platform platform)
  // 601:     if priority.is_defined && priority < best_priority:
  // 602:       !best_platform platform
  // 603:       !best_priority priority
  // 604:   if best_platform.is_defined:
  // 605:     $$ub default_value(used_by(best_platform) empty_list)
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__72_109, 2);
  // 596: for_each supported_platforms: (supported_platform _parent_platform)
  // 597:   $$best_platform undefined
  // 598:   $$best_priority 999
  // 599:   for_each mod_info: (platform _filenames)
  // 600:     $priority platform_specific_priority(supported_platform platform)
  // 601:     if priority.is_defined && priority < best_priority:
  // 602:       !best_platform platform
  // 603:       !best_priority priority
  // 604:   if best_platform.is_defined:
  // 605:     $$ub default_value(used_by(best_platform) empty_list)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._supported_platforms;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__72_124;
}
static void entry__72_119(void) {
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
  // 605: ... used_by(best_platform)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* best_platform */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* used_by */;
  func = myself->type;
  frame->cont = cont__72_120;
}
static void cont__72_120(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 605: $$ub default_value(used_by(best_platform) empty_list)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = get__empty_list();
  result_count = 1;
  myself = get__default_value();
  func = myself->type;
  frame->cont = cont__72_121;
}
static void cont__72_121(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* ub */ = arguments->slots[0];
  // 606: push &ub supported_platform
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* ub */;
  arguments->slots[1] = frame->slots[2] /* supported_platform */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__72_122;
}
static void cont__72_122(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* ub */ = arguments->slots[0];
  // 607: !used_by(best_platform) ub
  frame->slots[4] /* temp__1 */ = ((CELL *)frame->slots[3])->contents /* ub */;
  // 607: !used_by(best_platform)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* best_platform */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* used_by */;
  func = myself->type;
  frame->cont = cont__72_123;
}
static void cont__72_123(void) {
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
static void entry__72_109(void) {
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
  // 597: $$best_platform undefined
  ((CELL *)frame->slots[4])->contents /* best_platform */ = get__undefined();
  // 598: $$best_priority 999
  ((CELL *)frame->slots[5])->contents /* best_priority */ = number__999;
  // 599: ... : (platform _filenames)
  // 600:   $priority platform_specific_priority(supported_platform platform)
  // 601:   if priority.is_defined && priority < best_priority:
  // 602:     !best_platform platform
  // 603:     !best_priority priority
  frame->slots[6] /* temp__1 */ = create_closure(entry__72_110, 2);
  // 599: for_each mod_info: (platform _filenames)
  // 600:   $priority platform_specific_priority(supported_platform platform)
  // 601:   if priority.is_defined && priority < best_priority:
  // 602:     !best_platform platform
  // 603:     !best_priority priority
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* mod_info */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__72_117;
}
static void entry__72_116(void) {
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
  // 602: !best_platform platform
  ((CELL *)frame->slots[0])->contents /* best_platform */ = frame->slots[1] /* platform */;
  // 603: !best_priority priority
  ((CELL *)frame->slots[2])->contents /* best_priority */ = frame->slots[3] /* priority */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__72_110(void) {
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
  // 600: $priority platform_specific_priority(supported_platform platform)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* supported_platform */;
  arguments->slots[1] = frame->slots[0] /* platform */;
  result_count = 1;
  myself = var._platform_specific_priority;
  func = myself->type;
  frame->cont = cont__72_111;
}
static void cont__72_111(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* priority */, arguments->slots[0]);
  // 601: ... priority.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* priority */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__72_112;
}
static void cont__72_112(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 601: ... priority < best_priority
  frame->slots[8] /* temp__3 */ = create_closure(entry__72_113, 0);
  // 601: ... priority.is_defined && priority < best_priority
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  arguments->slots[1] = frame->slots[8] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__72_115;
}
static void entry__72_113(void) {
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
  // 601: ... priority < best_priority
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* priority */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* best_priority */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__72_114;
}
static void cont__72_114(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 601: ... priority < best_priority
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__72_115(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 601: ... :
  // 602:   !best_platform platform
  // 603:   !best_priority priority
  frame->slots[9] /* temp__4 */ = create_closure(entry__72_116, 0);
  // 601: if priority.is_defined && priority < best_priority:
  // 602:   !best_platform platform
  // 603:   !best_priority priority
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__72_117(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 604: ... best_platform.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* best_platform */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__72_118;
}
static void cont__72_118(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 604: ... :
  // 605:   $$ub default_value(used_by(best_platform) empty_list)
  // 606:   push &ub supported_platform
  // 607:   !used_by(best_platform) ub
  frame->slots[7] /* temp__2 */ = create_closure(entry__72_119, 0);
  // 604: if best_platform.is_defined:
  // 605:   $$ub default_value(used_by(best_platform) empty_list)
  // 606:   push &ub supported_platform
  // 607:   !used_by(best_platform) ub
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__72_124(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 608: ... : (platform _filenames)
  // 609:   $$dependency string(mod_filename "-" platform ".c")
  // 610:   $platforms used_by(platform)
  // 611:   if platforms.is_defined:
  // 612:     for_each platforms: (plat) write_to &dependency " #" plat
  // 613:   push &dependencies dependency
  frame->slots[3] /* temp__1 */ = create_closure(entry__72_125, 2);
  // 608: for_each mod_info: (platform _filenames)
  // 609:   $$dependency string(mod_filename "-" platform ".c")
  // 610:   $platforms used_by(platform)
  // 611:   if platforms.is_defined:
  // 612:     for_each platforms: (plat) write_to &dependency " #" plat
  // 613:   push &dependencies dependency
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_info */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__72_91(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // mod_filename: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* mod_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 579: ... string(mod_filename ".c")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = string__70_9;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__72_92;
}
static void cont__72_92(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 579: ... push &dependencies string(mod_filename ".c")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._dependencies;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__72_93;
}
static void cont__72_93(void) {
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
static void entry__72_86(void) {
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
  // 578: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__72_87;
}
static void cont__72_87(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 578: ... truncate_until(mod_name '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* mod_name */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__72_88;
}
static void cont__72_88(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 578: ... list(truncate_until(mod_name '/' -1))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__72_89;
}
static void cont__72_89(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 578: compile_submodule list(truncate_until(mod_name '/' -1))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = frame->slots[0] /* compile_submodule */;
  func = myself->type;
  frame->cont = cont__72_90;
}
static void cont__72_90(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 579: ... : push &dependencies string(mod_filename ".c")
  frame->slots[3] /* temp__1 */ = create_closure(entry__72_91, 0);
  // 579: if do_list_dependencies: push &dependencies string(mod_filename ".c")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_list_dependencies;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__72_94(void) {
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
  // 581: ... :
  // 582:   $$best_platform undefined
  // 583:   $$best_priority 999
  // 584:   for_each mod_info: (platform _filenames)
  // 585:     $priority platform_priority(platform)
  // 586:     if priority.is_defined && priority < best_priority:
  // 587:       !best_platform platform
  // 588:       !best_priority priority
  // 589:   for_each mod_info: (platform filenames)
  // 590:     compile_submodule
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__72_95, 0);
  // 581: do:
  // 582:   $$best_platform undefined
  // 583:   $$best_priority 999
  // 584:   for_each mod_info: (platform _filenames)
  // 585:     $priority platform_priority(platform)
  // 586:     if priority.is_defined && priority < best_priority:
  // 587:       !best_platform platform
  // 588:       !best_priority priority
  // 589:   for_each mod_info: (platform filenames)
  // 590:     compile_submodule
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__72_107;
}
static void entry__72_104(void) {
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
  // 592: platform == best_platform
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* platform */;
  arguments->slots[1] = ((CELL *)frame->slots[3])->contents /* best_platform */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__72_105;
}
static void cont__72_105(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 593: string("-" platform)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__66_46;
  arguments->slots[1] = frame->slots[0] /* platform */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__72_106;
}
static void cont__72_106(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 590: compile_submodule
  // 591:   filenames
  // 592:   platform == best_platform
  // 593:   string("-" platform)
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
static void entry__72_95(void) {
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
  // 582: $$best_platform undefined
  ((CELL *)frame->slots[2])->contents /* best_platform */ = get__undefined();
  // 583: $$best_priority 999
  ((CELL *)frame->slots[3])->contents /* best_priority */ = number__999;
  // 584: ... : (platform _filenames)
  // 585:   $priority platform_priority(platform)
  // 586:   if priority.is_defined && priority < best_priority:
  // 587:     !best_platform platform
  // 588:     !best_priority priority
  frame->slots[4] /* temp__1 */ = create_closure(entry__72_96, 2);
  // 584: for_each mod_info: (platform _filenames)
  // 585:   $priority platform_priority(platform)
  // 586:   if priority.is_defined && priority < best_priority:
  // 587:     !best_platform platform
  // 588:     !best_priority priority
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_info */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__72_103;
}
static void entry__72_102(void) {
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
  // 587: !best_platform platform
  ((CELL *)frame->slots[0])->contents /* best_platform */ = frame->slots[1] /* platform */;
  // 588: !best_priority priority
  ((CELL *)frame->slots[2])->contents /* best_priority */ = frame->slots[3] /* priority */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__72_96(void) {
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
  // 585: $priority platform_priority(platform)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* platform */;
  result_count = 1;
  myself = var._platform_priority;
  func = myself->type;
  frame->cont = cont__72_97;
}
static void cont__72_97(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* priority */, arguments->slots[0]);
  // 586: ... priority.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* priority */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__72_98;
}
static void cont__72_98(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 586: ... priority < best_priority
  frame->slots[7] /* temp__3 */ = create_closure(entry__72_99, 0);
  // 586: ... priority.is_defined && priority < best_priority
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__72_101;
}
static void entry__72_99(void) {
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
  // 586: ... priority < best_priority
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* priority */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* best_priority */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__72_100;
}
static void cont__72_100(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 586: ... priority < best_priority
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__72_101(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 586: ... :
  // 587:   !best_platform platform
  // 588:   !best_priority priority
  frame->slots[8] /* temp__4 */ = create_closure(entry__72_102, 0);
  // 586: if priority.is_defined && priority < best_priority:
  // 587:   !best_platform platform
  // 588:   !best_priority priority
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__72_103(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 589: ... : (platform filenames)
  // 590:   compile_submodule
  // 591:     filenames
  // 592:     platform == best_platform
  // 593:     string("-" platform)
  frame->slots[4] /* temp__1 */ = create_closure(entry__72_104, 2);
  // 589: for_each mod_info: (platform filenames)
  // 590:   compile_submodule
  // 591:     filenames
  // 592:     platform == best_platform
  // 593:     string("-" platform)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_info */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__72_107(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 594: ... :
  // 595:   $$used_by empty_table
  // 596:   for_each supported_platforms: (supported_platform _parent_platform)
  // 597:     $$best_platform undefined
  // 598:     $$best_priority 999
  // 599:     for_each mod_info: (platform _filenames)
  // 600:       $priority platform_specific_priority(supported_platform platform)
  // 601:       if priority.is_defined && priority < best_priority:
  // 602:         !best_platform platform
  // 603:         !best_priority priority
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__72_108, 0);
  // 594: if do_list_dependencies:
  // 595:   $$used_by empty_table
  // 596:   for_each supported_platforms: (supported_platform _parent_platform)
  // 597:     $$best_platform undefined
  // 598:     $$best_priority 999
  // 599:     for_each mod_info: (platform _filenames)
  // 600:       $priority platform_specific_priority(supported_platform platform)
  // 601:       if priority.is_defined && priority < best_priority:
  // 602:         !best_platform platform
  // 603:         !best_priority priority
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
static void cont__72_135(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__73_8(void) {
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
  // 624: ... string(path '/' name)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* path */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__73_9;
}
static void cont__73_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 624: ... string(mod_path '/' name)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* mod_path */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__73_10;
}
static void cont__73_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 624: compile_module string(path '/' name) string(mod_path '/' name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = var._compile_module;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__73_1_compile_modules(void) {
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
  // 620: ... string(mod_path '/')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* mod_path */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__73_2;
}
static void cont__73_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 620: add_module_infos $directories $modules path string(mod_path '/')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* path */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 2;
  myself = var._add_module_infos;
  func = myself->type;
  frame->cont = cont__73_3;
}
static void cont__73_3(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  frame->slots[6] /* temp__3 */ = arguments->slots[1];
  // 620: ... directories
  initialize_future(frame->slots[2] /* directories */, frame->slots[5] /* temp__2 */);
  // 620: ... modules
  initialize_future(frame->slots[3] /* modules */, frame->slots[6] /* temp__3 */);
  // 621: ... : (name)
  // 622:   compile_modules string(path '/' name) string(mod_path '/' name)
  frame->slots[4] /* temp__1 */ = create_closure(entry__73_4, 1);
  // 621: for_each directories: (name)
  // 622:   compile_modules string(path '/' name) string(mod_path '/' name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* directories */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__73_7;
}
static void entry__73_4(void) {
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
  // 622: ... string(path '/' name)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* path */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__73_5;
}
static void cont__73_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 622: ... string(mod_path '/' name)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* mod_path */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__73_6;
}
static void cont__73_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 622: compile_modules string(path '/' name) string(mod_path '/' name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = var._compile_modules;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__73_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 623: ... : (name)
  // 624:   compile_module string(path '/' name) string(mod_path '/' name)
  frame->slots[4] /* temp__1 */ = create_closure(entry__73_8, 1);
  // 623: for_each modules: (name)
  // 624:   compile_module string(path '/' name) string(mod_path '/' name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* modules */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__75_2(void) {
  allocate_initialized_frame_gc(0, 3);
  // slot allocations:
  // path: 0
  frame->slots[0] /* path */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 632: $path environment("LD_LIBRARY_PATH")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__75_3;
  result_count = 1;
  myself = get__environment();
  func = myself->type;
  frame->cont = cont__75_4;
}
static void cont__75_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[0] /* path */, arguments->slots[0]);
  // 633: ... path.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* path */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__75_5;
}
static void cont__75_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 633: ... : ewriteln "LD_LIBRARY_PATH=@(path)"
  frame->slots[2] /* temp__2 */ = create_closure(entry__75_6, 0);
  // 633: if path.is_defined: ewriteln "LD_LIBRARY_PATH=@(path)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__75_9;
}
static void entry__75_6(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // path: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* path */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 633: ... "LD_LIBRARY_PATH=@(path)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__75_7;
  arguments->slots[1] = frame->slots[0] /* path */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__75_8;
}
static void cont__75_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 633: ... ewriteln "LD_LIBRARY_PATH=@(path)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__75_9(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 634: ... serialize(objects)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__objects();
  result_count = 1;
  myself = get__serialize();
  func = myself->type;
  frame->cont = cont__75_10;
}
static void cont__75_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 634: ewriteln "included object files: " serialize(objects)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__75_11;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 0;
  myself = get__ewriteln();
  func = myself->type;
  frame->cont = cont__75_12;
}
static void cont__75_12(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 635: ... serialize(libraries)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__libraries();
  result_count = 1;
  myself = get__serialize();
  func = myself->type;
  frame->cont = cont__75_13;
}
static void cont__75_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 635: ewriteln "needed libraries: " serialize(libraries)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__75_14;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__75_1_show_file_list(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 631: if do_show_debug_infos:
  // 632:   $path environment("LD_LIBRARY_PATH")
  // 633:   if path.is_defined: ewriteln "LD_LIBRARY_PATH=@(path)"
  // 634:   ewriteln "included object files: " serialize(objects)
  // 635:   ewriteln "needed libraries: " serialize(libraries)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_show_debug_infos();
  arguments->slots[1] = func__75_2;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__76_1_library_paths_and_file_list(void) {
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
  // 638: show_file_list
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._show_file_list;
  func = myself->type;
  frame->cont = cont__76_2;
}
static void cont__76_2(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 639: $$library_paths empty_list
  ((CELL *)frame->slots[0])->contents /* library_paths */ = get__empty_list();
  // 640: $$object_files empty_list
  ((CELL *)frame->slots[1])->contents /* object_files */ = get__empty_list();
  // 641: $$library_files empty_list
  ((CELL *)frame->slots[2])->contents /* library_files */ = get__empty_list();
  // 642: $paths environment("LD_LIBRARY_PATH")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__75_3;
  result_count = 1;
  myself = get__environment();
  func = myself->type;
  frame->cont = cont__76_3;
}
static void cont__76_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* paths */, arguments->slots[0]);
  // 643: ... paths.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* paths */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__76_4;
}
static void cont__76_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 643: ... :
  // 644:   for_each paths .split. ':': (path) push &library_paths "-L@(path)"
  frame->slots[5] /* temp__2 */ = create_closure(entry__76_5, 0);
  // 643: if paths.is_defined:
  // 644:   for_each paths .split. ':': (path) push &library_paths "-L@(path)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__76_11;
}
static void entry__76_7(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // path: 0
  // library_paths: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* library_paths */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 644: ... "-L@(path)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__76_8;
  arguments->slots[1] = frame->slots[0] /* path */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__76_9;
}
static void cont__76_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 644: ... push &library_paths "-L@(path)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* library_paths */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__76_10;
}
static void cont__76_10(void) {
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
static void entry__76_5(void) {
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
  // 644: ... paths .split. ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* paths */;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__split();
  func = myself->type;
  frame->cont = cont__76_6;
}
static void cont__76_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 644: ... : (path) push &library_paths "-L@(path)"
  frame->slots[3] /* temp__2 */ = create_closure(entry__76_7, 1);
  // 644: for_each paths .split. ':': (path) push &library_paths "-L@(path)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__76_11(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 645: ... : ewriteln "library paths: " serialize(library_paths)
  frame->slots[4] /* temp__1 */ = create_closure(entry__76_12, 0);
  // 645: if do_show_debug_infos: ewriteln "library paths: " serialize(library_paths)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_show_debug_infos();
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__76_15;
}
static void entry__76_12(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // library_paths: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* library_paths */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 645: ... serialize(library_paths)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* library_paths */;
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
  // 645: ... ewriteln "library paths: " serialize(library_paths)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__76_14;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__76_15(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 646: ... : (object) push &object_files object
  frame->slots[4] /* temp__1 */ = create_closure(entry__76_16, 1);
  // 646: for_each objects: (object) push &object_files object
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__objects();
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__76_18;
}
static void entry__76_16(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // object: 0
  // object_files: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* object_files */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 646: ... push &object_files object
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* object_files */;
  arguments->slots[1] = frame->slots[0] /* object */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__76_17;
}
static void cont__76_17(void) {
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
static void cont__76_18(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 647: ... : (library)
  // 648:   push
  // 649:     &library_files
  // 650:     if
  // 651:       library .has_prefix. "sim-"
  // 652:       ->
  // 653:         if
  // 654:           operating_system() == "linux"
  // 655:           -> "-l:lib@(library).so.@(MAJOR)"
  // 656:           -> "-l@(library)-@(MAJOR)"
  // ...
  frame->slots[4] /* temp__1 */ = create_closure(entry__76_19, 1);
  // 647: for_each libraries: (library)
  // 648:   push
  // 649:     &library_files
  // 650:     if
  // 651:       library .has_prefix. "sim-"
  // 652:       ->
  // 653:         if
  // 654:           operating_system() == "linux"
  // 655:           -> "-l:lib@(library).so.@(MAJOR)"
  // 656:           -> "-l@(library)-@(MAJOR)"
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__libraries();
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__76_44;
}
static void entry__76_19(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // library: 0
  // library_files: 1
  frame->slots[1] = myself->closure.frame->slots[2]; /* library_files */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 651: library .has_prefix. "sim-"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* library */;
  arguments->slots[1] = string__71_32;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__76_20;
}
static void cont__76_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 652: ->
  // 653:   if
  // 654:     operating_system() == "linux"
  // 655:     -> "-l:lib@(library).so.@(MAJOR)"
  // 656:     -> "-l@(library)-@(MAJOR)"
  frame->slots[4] /* temp__3 */ = create_closure(entry__76_21, 0);
  // 657: ->
  // 658:   if
  // 659:     library .contains. '.'
  // 660:     -> "-l:lib@(library .before. '.').so.@(library .behind. '.')"
  // 661:       # Linux only
  // 662:     -> "-l@(library)"
  frame->slots[5] /* temp__4 */ = create_closure(entry__76_33, 0);
  // 650: if
  // 651:   library .has_prefix. "sim-"
  // 652:   ->
  // 653:     if
  // 654:       operating_system() == "linux"
  // 655:       -> "-l:lib@(library).so.@(MAJOR)"
  // 656:       -> "-l@(library)-@(MAJOR)"
  // 657:   ->
  // 658:     if
  // 659:       library .contains. '.'
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  arguments->slots[2] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__76_42;
}
static void entry__76_21(void) {
  allocate_initialized_frame_gc(1, 6);
  // slot allocations:
  // library: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* library */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 654: operating_system()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__operating_system();
  func = myself->type;
  frame->cont = cont__76_22;
}
static void cont__76_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 654: operating_system() == "linux"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = string__76_23;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__76_24;
}
static void cont__76_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 655: -> "-l:lib@(library).so.@(MAJOR)"
  frame->slots[4] /* temp__4 */ = create_closure(entry__76_25, 0);
  // 656: -> "-l@(library)-@(MAJOR)"
  frame->slots[5] /* temp__5 */ = create_closure(entry__76_29, 0);
  // 653: if
  // 654:   operating_system() == "linux"
  // 655:   -> "-l:lib@(library).so.@(MAJOR)"
  // 656:   -> "-l@(library)-@(MAJOR)"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  arguments->slots[2] = frame->slots[5] /* temp__5 */;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__76_32;
}
static void entry__76_25(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // library: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* library */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 655: ... "-l:lib@(library).so.@(MAJOR)"
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__76_26;
  arguments->slots[1] = frame->slots[0] /* library */;
  arguments->slots[2] = string__76_27;
  arguments->slots[3] = var._MAJOR;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__76_28;
}
static void cont__76_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 655: -> "-l:lib@(library).so.@(MAJOR)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__76_29(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // library: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* library */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 656: ... "-l@(library)-@(MAJOR)"
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__76_30;
  arguments->slots[1] = frame->slots[0] /* library */;
  arguments->slots[2] = string__66_46;
  arguments->slots[3] = var._MAJOR;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__76_31;
}
static void cont__76_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 656: -> "-l@(library)-@(MAJOR)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__76_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 652: ->
  // 653:   if
  // 654:     operating_system() == "linux"
  // 655:     -> "-l:lib@(library).so.@(MAJOR)"
  // 656:     -> "-l@(library)-@(MAJOR)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__76_33(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // library: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* library */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 659: library .contains. '.'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* library */;
  arguments->slots[1] = character__46;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__76_34;
}
static void cont__76_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 660: -> "-l:lib@(library .before. '.').so.@(library .behind. '.')"
  // 661:   # Linux only
  frame->slots[3] /* temp__3 */ = create_closure(entry__76_35, 0);
  // 662: -> "-l@(library)"
  frame->slots[4] /* temp__4 */ = create_closure(entry__76_39, 0);
  // 658: if
  // 659:   library .contains. '.'
  // 660:   -> "-l:lib@(library .before. '.').so.@(library .behind. '.')"
  // 661:     # Linux only
  // 662:   -> "-l@(library)"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  arguments->slots[2] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__76_41;
}
static void entry__76_35(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // library: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* library */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 660: ... library .before. '.'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* library */;
  arguments->slots[1] = character__46;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__76_36;
}
static void cont__76_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 660: ... library .behind. '.'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* library */;
  arguments->slots[1] = character__46;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__76_37;
}
static void cont__76_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 660: ... "-l:lib@(library .before. '.').so.@(library .behind. '.')"
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__76_26;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  arguments->slots[2] = string__76_27;
  arguments->slots[3] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__76_38;
}
static void cont__76_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 660: -> "-l:lib@(library .before. '.').so.@(library .behind. '.')"
  // 661:   # Linux only
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__76_39(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // library: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* library */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 662: ... "-l@(library)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__76_30;
  arguments->slots[1] = frame->slots[0] /* library */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__76_40;
}
static void cont__76_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 662: -> "-l@(library)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__76_41(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 657: ->
  // 658:   if
  // 659:     library .contains. '.'
  // 660:     -> "-l:lib@(library .before. '.').so.@(library .behind. '.')"
  // 661:       # Linux only
  // 662:     -> "-l@(library)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__76_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 648: push
  // 649:   &library_files
  // 650:   if
  // 651:     library .has_prefix. "sim-"
  // 652:     ->
  // 653:       if
  // 654:         operating_system() == "linux"
  // 655:         -> "-l:lib@(library).so.@(MAJOR)"
  // 656:         -> "-l@(library)-@(MAJOR)"
  // 657:     ->
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* library_files */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__76_43;
}
static void cont__76_43(void) {
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
static void cont__76_44(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 663: ... append(object_files library_files)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* object_files */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* library_files */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__76_45;
}
static void cont__76_45(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 663: append library_paths append(object_files library_files)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* library_paths */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__append();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__77_74(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 706: ... write_timing_info "collecting imports"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__77_75;
  result_count = frame->caller_result_count;
  myself = get__write_timing_info();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__77_1_create_imports(void) {
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
  // 668: ... : (buf)
  // 669:   $$s undefined
  // 670:   for_each buf: (idx chr)
  // 671:     if
  // 672:       s.is_defined:
  // 673:         unless chr.is_a_letter || chr == '_' || chr.is_a_digit:
  // 674:           $symbol range(buf s idx-1)
  // 675:           !s undefined
  // 676:           unless already_checked(symbol):
  // 677:             !already_checked(symbol) true
  // ...
  frame->slots[5] /* temp__1 */ = create_closure(entry__77_2_collect_declarations, 1);
  // 668: $collect_declarations: (buf)
  // 669:   $$s undefined
  // 670:   for_each buf: (idx chr)
  // 671:     if
  // 672:       s.is_defined:
  // 673:         unless chr.is_a_letter || chr == '_' || chr.is_a_digit:
  // 674:           $symbol range(buf s idx-1)
  // 675:           !s undefined
  // 676:           unless already_checked(symbol):
  // 677:             !already_checked(symbol) true
  // ...
  initialize_future(frame->slots[2] /* collect_declarations */, frame->slots[5] /* temp__1 */);
  // 666: $$already_checked empty_set
  ((CELL *)frame->slots[1])->contents /* already_checked */ = get__empty_set();
  // 701: ... : collect_declarations source
  frame->slots[5] /* temp__1 */ = create_closure(entry__77_63, 0);
  // 701: collect_output $imports: collect_declarations source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__77_64;
}
static void entry__77_62(void) {
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
  // 699: ... !s idx
  ((CELL *)frame->slots[0])->contents /* s */ = frame->slots[1] /* idx */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__77_21(void) {
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
  // 682: declaration(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* declaration */;
  func = myself->type;
  frame->cont = cont__77_22;
}
static void cont__77_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 682: declaration(1) != '#'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  arguments->slots[1] = character__35;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__77_23;
}
static void cont__77_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 682: declaration(1) != '#'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__77_24;
}
static void cont__77_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  frame->slots[6] /* temp__4 */ = create_closure(entry__77_25, 0);
  // 680: $do_import
  // 681:   &&
  // 682:     declaration(1) != '#'
  // 683:     not(declaration .has_prefix. "typedef")
  // 684:     not(declaration .has_prefix. "REGISTER")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__77_34;
}
static void entry__77_25(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // declaration: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* declaration */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 683: ... declaration .has_prefix. "typedef"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* declaration */;
  arguments->slots[1] = string__77_26;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__77_27;
}
static void cont__77_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 683: not(declaration .has_prefix. "typedef")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__not();
  func = myself->type;
  frame->cont = cont__77_28;
}
static void cont__77_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 684: not(declaration .has_prefix. "REGISTER")
  frame->slots[4] /* temp__4 */ = create_closure(entry__77_29, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__77_33;
}
static void entry__77_29(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // declaration: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* declaration */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 684: ... declaration .has_prefix. "REGISTER"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* declaration */;
  arguments->slots[1] = string__77_30;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__77_31;
}
static void cont__77_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 684: not(declaration .has_prefix. "REGISTER")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__not();
  func = myself->type;
  frame->cont = cont__77_32;
}
static void cont__77_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 684: not(declaration .has_prefix. "REGISTER")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__77_33(void) {
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
static void cont__77_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* do_import */, arguments->slots[0]);
  // 687: ->
  // 688:   declaration(1) == '#' || declaration .has_prefix. "REGISTER"
  // 689:   :
  // 690:     collect_declarations declaration .truncate_from. '{'
  frame->slots[3] /* temp__1 */ = create_closure(entry__77_35, 0);
  // 691: -> declaration .has_prefix. "typedef struct":
  // 692:   for_each_line between(declaration '{' '}').trim: (line)
  // 693:     collect_declarations until(line ' ' -1)
  frame->slots[4] /* temp__2 */ = create_closure(entry__77_43, 0);
  // 694: :
  // 695:   collect_declarations declaration
  frame->slots[5] /* temp__3 */ = create_closure(entry__77_52, 0);
  // 686: cond
  // 687:   ->
  // 688:     declaration(1) == '#' || declaration .has_prefix. "REGISTER"
  // 689:     :
  // 690:       collect_declarations declaration .truncate_from. '{'
  // 691:   -> declaration .has_prefix. "typedef struct":
  // 692:     for_each_line between(declaration '{' '}').trim: (line)
  // 693:       collect_declarations until(line ' ' -1)
  // 694:   :
  // 695:     collect_declarations declaration
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = frame->slots[5] /* temp__3 */;
  result_count = 0;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__77_53;
}
static void entry__77_49(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // line: 0
  // collect_declarations: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* collect_declarations */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 693: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__77_50;
}
static void cont__77_50(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 693: ... until(line ' ' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* line */;
  arguments->slots[1] = character__32;
  arguments->slots[2] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__until();
  func = myself->type;
  frame->cont = cont__77_51;
}
static void cont__77_51(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 693: collect_declarations until(line ' ' -1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* collect_declarations */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__77_46(void) {
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
  // 692: ... between(declaration '{' '}')
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* declaration */;
  arguments->slots[1] = character__123;
  arguments->slots[2] = character__125;
  result_count = 1;
  myself = get__between();
  func = myself->type;
  frame->cont = cont__77_47;
}
static void cont__77_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 692: ... between(declaration '{' '}').trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__77_48;
}
static void cont__77_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 692: ... : (line)
  // 693:   collect_declarations until(line ' ' -1)
  frame->slots[4] /* temp__3 */ = create_closure(entry__77_49, 1);
  // 692: for_each_line between(declaration '{' '}').trim: (line)
  // 693:   collect_declarations until(line ' ' -1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__for_each_line();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__77_41(void) {
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
  // 690: ... declaration .truncate_from. '{'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* declaration */;
  arguments->slots[1] = character__123;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__77_42;
}
static void cont__77_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 690: collect_declarations declaration .truncate_from. '{'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* collect_declarations */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__77_35(void) {
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
  // 688: declaration(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* declaration */;
  func = myself->type;
  frame->cont = cont__77_36;
}
static void cont__77_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 688: declaration(1) == '#'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  arguments->slots[1] = character__35;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__77_37;
}
static void cont__77_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 688: ... declaration .has_prefix. "REGISTER"
  frame->slots[5] /* temp__4 */ = create_closure(entry__77_38, 0);
  // 688: declaration(1) == '#' || declaration .has_prefix. "REGISTER"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__77_40;
}
static void entry__77_38(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // declaration: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* declaration */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 688: ... declaration .has_prefix. "REGISTER"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* declaration */;
  arguments->slots[1] = string__77_30;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__77_39;
}
static void cont__77_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 688: ... declaration .has_prefix. "REGISTER"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__77_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 689: :
  // 690:   collect_declarations declaration .truncate_from. '{'
  frame->slots[6] /* temp__5 */ = create_closure(entry__77_41, 0);
  // 687: ->
  // 688:   declaration(1) == '#' || declaration .has_prefix. "REGISTER"
  // 689:   :
  // 690:     collect_declarations declaration .truncate_from. '{'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__5 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__77_43(void) {
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
  // 691: ... declaration .has_prefix. "typedef struct"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* declaration */;
  arguments->slots[1] = string__77_44;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__77_45;
}
static void cont__77_45(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 691: ... :
  // 692:   for_each_line between(declaration '{' '}').trim: (line)
  // 693:     collect_declarations until(line ' ' -1)
  frame->slots[3] /* temp__2 */ = create_closure(entry__77_46, 0);
  // 691: -> declaration .has_prefix. "typedef struct":
  // 692:   for_each_line between(declaration '{' '}').trim: (line)
  // 693:     collect_declarations until(line ' ' -1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__77_52(void) {
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
  // 695: collect_declarations declaration
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* declaration */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* collect_declarations */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__77_53(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 696: if do_import: write "IMPORT "
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* do_import */;
  arguments->slots[1] = func__77_54;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__77_56;
}
static void entry__77_54(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 696: ... write "IMPORT "
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__77_55;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__77_56(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 697: write declaration
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* declaration */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__77_17(void) {
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
  // 677: !already_checked(symbol) true
  frame->slots[4] /* temp__1 */ = get__true();
  // 677: !already_checked(symbol)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* symbol */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* already_checked */;
  func = myself->type;
  frame->cont = cont__77_18;
}
static void cont__77_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* already_checked */ = arguments->slots[0];
  // 678: $declaration runtime_symbols(symbol)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* symbol */;
  result_count = 1;
  myself = get__runtime_symbols();
  func = myself->type;
  frame->cont = cont__77_19;
}
static void cont__77_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* declaration */, arguments->slots[0]);
  // 679: ... declaration.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* declaration */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__77_20;
}
static void cont__77_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 679: ... :
  // 680:   $do_import
  // 681:     &&
  // 682:       declaration(1) != '#'
  // 683:       not(declaration .has_prefix. "typedef")
  // 684:       not(declaration .has_prefix. "REGISTER")
  // 685:   
  // 686:   cond
  // 687:     ->
  // 688:       declaration(1) == '#' || declaration .has_prefix. "REGISTER"
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__77_21, 0);
  // 679: if declaration.is_defined:
  // 680:   $do_import
  // 681:     &&
  // 682:       declaration(1) != '#'
  // 683:       not(declaration .has_prefix. "typedef")
  // 684:       not(declaration .has_prefix. "REGISTER")
  // 685:   
  // 686:   cond
  // 687:     ->
  // 688:       declaration(1) == '#' || declaration .has_prefix. "REGISTER"
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
static void entry__77_13(void) {
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
  // 674: ... idx-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* idx */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__77_14;
}
static void cont__77_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 674: $symbol range(buf s idx-1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* buf */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* s */;
  arguments->slots[2] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__77_15;
}
static void cont__77_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* symbol */, arguments->slots[0]);
  // 675: !s undefined
  ((CELL *)frame->slots[1])->contents /* s */ = get__undefined();
  // 676: ... already_checked(symbol)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* symbol */;
  result_count = 1;
  myself = ((CELL *)frame->slots[3])->contents /* already_checked */;
  func = myself->type;
  frame->cont = cont__77_16;
}
static void cont__77_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 676: ... :
  // 677:   !already_checked(symbol) true
  // 678:   $declaration runtime_symbols(symbol)
  // 679:   if declaration.is_defined:
  // 680:     $do_import
  // 681:       &&
  // 682:         declaration(1) != '#'
  // 683:         not(declaration .has_prefix. "typedef")
  // 684:         not(declaration .has_prefix. "REGISTER")
  // 685:     
  // ...
  frame->slots[7] /* temp__2 */ = create_closure(entry__77_17, 0);
  // 676: unless already_checked(symbol):
  // 677:   !already_checked(symbol) true
  // 678:   $declaration runtime_symbols(symbol)
  // 679:   if declaration.is_defined:
  // 680:     $do_import
  // 681:       &&
  // 682:         declaration(1) != '#'
  // 683:         not(declaration .has_prefix. "typedef")
  // 684:         not(declaration .has_prefix. "REGISTER")
  // 685:     
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
static void entry__77_5(void) {
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
  // 673: ... chr.is_a_letter
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  result_count = 1;
  myself = get__is_a_letter();
  func = myself->type;
  frame->cont = cont__77_6;
}
static void cont__77_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 673: ... chr == '_' || chr.is_a_digit
  frame->slots[8] /* temp__3 */ = create_closure(entry__77_7, 0);
  // 673: ... chr.is_a_letter || chr == '_' || chr.is_a_digit
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  arguments->slots[1] = frame->slots[8] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__77_12;
}
static void entry__77_7(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 673: ... chr == '_'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__95;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__77_8;
}
static void cont__77_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 673: ... chr.is_a_digit
  frame->slots[3] /* temp__3 */ = create_closure(entry__77_9, 0);
  // 673: ... chr == '_' || chr.is_a_digit
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__77_11;
}
static void entry__77_9(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 673: ... chr.is_a_digit
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  result_count = 1;
  myself = get__is_a_digit();
  func = myself->type;
  frame->cont = cont__77_10;
}
static void cont__77_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 673: ... chr.is_a_digit
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__77_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 673: ... chr == '_' || chr.is_a_digit
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__77_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 673: ... :
  // 674:   $symbol range(buf s idx-1)
  // 675:   !s undefined
  // 676:   unless already_checked(symbol):
  // 677:     !already_checked(symbol) true
  // 678:     $declaration runtime_symbols(symbol)
  // 679:     if declaration.is_defined:
  // 680:       $do_import
  // 681:         &&
  // 682:           declaration(1) != '#'
  // ...
  frame->slots[9] /* temp__4 */ = create_closure(entry__77_13, 0);
  // 673: unless chr.is_a_letter || chr == '_' || chr.is_a_digit:
  // 674:   $symbol range(buf s idx-1)
  // 675:   !s undefined
  // 676:   unless already_checked(symbol):
  // 677:     !already_checked(symbol) true
  // 678:     $declaration runtime_symbols(symbol)
  // 679:     if declaration.is_defined:
  // 680:       $do_import
  // 681:         &&
  // 682:           declaration(1) != '#'
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
static void entry__77_57(void) {
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
  // 699: ... chr.is_a_letter
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  result_count = 1;
  myself = get__is_a_letter();
  func = myself->type;
  frame->cont = cont__77_58;
}
static void cont__77_58(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 699: ... chr == '_'
  frame->slots[5] /* temp__3 */ = create_closure(entry__77_59, 0);
  // 699: ... chr.is_a_letter || chr == '_'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__77_61;
}
static void entry__77_59(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 699: ... chr == '_'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__95;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__77_60;
}
static void cont__77_60(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 699: ... chr == '_'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__77_61(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 699: ... : !s idx
  frame->slots[6] /* temp__4 */ = create_closure(entry__77_62, 0);
  // 699: if chr.is_a_letter || chr == '_': !s idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__77_3(void) {
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
  // 672: s.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* s */;
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
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 672: ... :
  // 673:   unless chr.is_a_letter || chr == '_' || chr.is_a_digit:
  // 674:     $symbol range(buf s idx-1)
  // 675:     !s undefined
  // 676:     unless already_checked(symbol):
  // 677:       !already_checked(symbol) true
  // 678:       $declaration runtime_symbols(symbol)
  // 679:       if declaration.is_defined:
  // 680:         $do_import
  // 681:           &&
  // ...
  frame->slots[7] /* temp__2 */ = create_closure(entry__77_5, 0);
  // 698: :
  // 699:   if chr.is_a_letter || chr == '_': !s idx
  frame->slots[8] /* temp__3 */ = create_closure(entry__77_57, 0);
  // 671: if
  // 672:   s.is_defined:
  // 673:     unless chr.is_a_letter || chr == '_' || chr.is_a_digit:
  // 674:       $symbol range(buf s idx-1)
  // 675:       !s undefined
  // 676:       unless already_checked(symbol):
  // 677:         !already_checked(symbol) true
  // 678:         $declaration runtime_symbols(symbol)
  // 679:         if declaration.is_defined:
  // 680:           $do_import
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
static void entry__77_2_collect_declarations(void) {
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
  // 669: $$s undefined
  ((CELL *)frame->slots[3])->contents /* s */ = get__undefined();
  // 670: ... : (idx chr)
  // 671:   if
  // 672:     s.is_defined:
  // 673:       unless chr.is_a_letter || chr == '_' || chr.is_a_digit:
  // 674:         $symbol range(buf s idx-1)
  // 675:         !s undefined
  // 676:         unless already_checked(symbol):
  // 677:           !already_checked(symbol) true
  // 678:           $declaration runtime_symbols(symbol)
  // 679:           if declaration.is_defined:
  // ...
  frame->slots[4] /* temp__1 */ = create_closure(entry__77_3, 2);
  // 670: for_each buf: (idx chr)
  // 671:   if
  // 672:     s.is_defined:
  // 673:       unless chr.is_a_letter || chr == '_' || chr.is_a_digit:
  // 674:         $symbol range(buf s idx-1)
  // 675:         !s undefined
  // 676:         unless already_checked(symbol):
  // 677:           !already_checked(symbol) true
  // 678:           $declaration runtime_symbols(symbol)
  // 679:           if declaration.is_defined:
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
static void entry__77_63(void) {
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
  // 701: ... collect_declarations source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* source */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* collect_declarations */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__77_64(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* imports */, arguments->slots[0]);
  // 702: $first_part source .before. "// INSERT HERE //"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  arguments->slots[1] = string__77_65;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__77_66;
}
static void cont__77_66(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* first_part */, arguments->slots[0]);
  // 703: write first_part
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* first_part */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__77_67;
}
static void cont__77_67(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 704: write imports
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* imports */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__77_68;
}
static void cont__77_68(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 705: ... length_of(first_part)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* first_part */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__77_69;
}
static void cont__77_69(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__3 */ = arguments->slots[0];
  // 705: ... length_of(first_part)+18
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__3 */;
  arguments->slots[1] = number__18;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__77_70;
}
static void cont__77_70(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 705: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__77_71;
}
static void cont__77_71(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__4 */ = arguments->slots[0];
  // 705: ... range(source length_of(first_part)+18 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  arguments->slots[2] = frame->slots[8] /* temp__4 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__77_72;
}
static void cont__77_72(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 705: write range(source length_of(first_part)+18 -1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__77_73;
}
static void cont__77_73(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 706: if do_time_passes: write_timing_info "collecting imports"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = func__77_74;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__78_1_compile_exe(void) {
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
  // 709: ... main_info.is_a_directory
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_info();
  result_count = 1;
  myself = get__is_a_directory();
  func = myself->type;
  frame->cont = cont__78_2;
}
static void cont__78_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 709: if main_info.is_a_directory: Error "Expected a source code file!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = func__78_3;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__78_5;
}
static void entry__78_3(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 709: ... Error "Expected a source code file!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__78_4;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__78_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 710: ... main_filename .has_suffix. ".sim"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  arguments->slots[1] = string__66_13;
  result_count = 1;
  myself = get__has_suffix();
  func = myself->type;
  frame->cont = cont__78_6;
}
static void cont__78_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 710: unless main_filename .has_suffix. ".sim":
  // 711:   Error "
  // 712:     Expected ".sim" file extension in source filename!@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = func__78_7;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__78_9;
}
static void entry__78_7(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 711: Error "
  // 712:   Expected ".sim" file extension in source filename!@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__78_8;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__78_9(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 714: $mod_filename main_filename .without_suffix. ".sim"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  arguments->slots[1] = string__66_13;
  result_count = 1;
  myself = get__without_suffix();
  func = myself->type;
  frame->cont = cont__78_10;
}
static void cont__78_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* mod_filename */, arguments->slots[0]);
  // 715: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__78_11;
}
static void cont__78_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 715: $mod_name truncate_until(mod_filename '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* mod_filename */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__78_12;
}
static void cont__78_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* mod_name */, arguments->slots[0]);
  // 716: body mod_filename mod_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* mod_filename */;
  arguments->slots[1] = frame->slots[3] /* mod_name */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame->cont = cont__78_13;
}
static void cont__78_13(void) {
  myself = frame->slots[1] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__79_2(void) {
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
  // 720: %sim2c::module_name mod_name
  initialize_maybe_future(get__sim2c__module_name(), frame->slots[1] /* mod_name */);
  // 721: ... list(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__79_3;
}
static void cont__79_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 721: sim2c list(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__sim2c();
  func = myself->type;
  frame->cont = cont__79_4;
}
static void cont__79_4(void) {
  myself = frame->slots[2] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__79_1_dump_source_or_check(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 719: compile_exe: (_mod_filename mod_name)
  // 720:   %sim2c::module_name mod_name
  // 721:   sim2c list(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__79_2;
  result_count = frame->caller_result_count;
  myself = var._compile_exe;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__80_18(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 731: ... write_timing_info "writing C-source"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__80_19;
  result_count = frame->caller_result_count;
  myself = get__write_timing_info();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__80_2(void) {
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
  // 725: ... module_prefix.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._module_prefix;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__80_3;
}
static void cont__80_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 725: ... : append string(module_prefix '/') &mod_name
  frame->slots[5] /* temp__2 */ = create_closure(entry__80_4, 0);
  // 725: if module_prefix.is_defined: append string(module_prefix '/') &mod_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__80_7;
}
static void entry__80_4(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // mod_name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* mod_name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 725: ... string(module_prefix '/')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._module_prefix;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__80_5;
}
static void cont__80_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 725: ... append string(module_prefix '/') &mod_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* mod_name */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__80_6;
}
static void cont__80_6(void) {
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
static void cont__80_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 726: ... :
  // 727:   %sim2c::module_name replace_all(mod_name '/' = "__" '.' = "__")
  // 728:   sim2c list(main_filename)
  frame->slots[4] /* temp__1 */ = create_closure(entry__80_8, 0);
  // 726: collect_output $c_source:
  // 727:   %sim2c::module_name replace_all(mod_name '/' = "__" '.' = "__")
  // 728:   sim2c list(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__80_14;
}
static void entry__80_8(void) {
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
  // 727: ... '/' = "__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = string__72_38;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__80_9;
}
static void cont__80_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 727: ... '.' = "__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__46;
  arguments->slots[1] = string__72_38;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__80_10;
}
static void cont__80_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 727: %sim2c::module_name replace_all(mod_name '/' = "__" '.' = "__")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* mod_name */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  arguments->slots[2] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__80_11;
}
static void cont__80_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(get__sim2c__module_name(), arguments->slots[0]);
  // 728: ... list(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__80_12;
}
static void cont__80_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 728: sim2c list(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__sim2c();
  func = myself->type;
  frame->cont = cont__80_13;
}
static void cont__80_13(void) {
  myself = frame->slots[0] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__80_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* c_source */, arguments->slots[0]);
  // 729: ... : create_imports c_source
  frame->slots[4] /* temp__1 */ = create_closure(entry__80_15, 0);
  // 729: collect_output $c_buf: create_imports c_source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__80_16;
}
static void entry__80_15(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // c_source: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* c_source */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 729: ... create_imports c_source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_source */;
  result_count = frame->caller_result_count;
  myself = var._create_imports;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__80_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* c_buf */, arguments->slots[0]);
  // 730: write c_buf
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* c_buf */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__80_17;
}
static void cont__80_17(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 731: if do_time_passes: write_timing_info "writing C-source"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = func__80_18;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__80_1_print_c(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 724: compile_exe: (_mod_filename $mod_name)
  // 725:   if module_prefix.is_defined: append string(module_prefix '/') &mod_name
  // 726:   collect_output $c_source:
  // 727:     %sim2c::module_name replace_all(mod_name '/' = "__" '.' = "__")
  // 728:     sim2c list(main_filename)
  // 729:   collect_output $c_buf: create_imports c_source
  // 730:   write c_buf
  // 731:   if do_time_passes: write_timing_info "writing C-source"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__80_2;
  result_count = frame->caller_result_count;
  myself = var._compile_exe;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__81_35(void) {
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
  // 760: without_prefix &filename prefix_path
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* filename */;
  arguments->slots[1] = frame->slots[1] /* prefix_path */;
  result_count = 1;
  myself = get__without_prefix();
  func = myself->type;
  frame->cont = cont__81_36;
}
static void cont__81_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* filename */ = arguments->slots[0];
  // 761: without_prefix &filename '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* filename */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__without_prefix();
  func = myself->type;
  frame->cont = cont__81_37;
}
static void cont__81_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* filename */ = arguments->slots[0];
  // 762: writeln filename
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* filename */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__81_1_list_dependencies(void) {
  allocate_initialized_frame_gc(0, 2);
  // slot allocations:
  // prefix_path: 0
  frame->slots[0] /* prefix_path */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 734: !platform_specific_priority multi_dimensional_table(types::table types::table)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__types__table();
  arguments->slots[1] = get__types__table();
  result_count = 1;
  myself = get__multi_dimensional_table();
  func = myself->type;
  frame->cont = cont__81_2;
}
static void cont__81_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._platform_specific_priority = arguments->slots[0];
  // 735: for_each supported_platforms: (supported_platform _parent_platform)
  // 736:   $$platform supported_platform
  // 737:   $$priority 0
  // 738:   do: (-> break)
  // 739:     forever:
  // 740:       $plat supported_platforms(platform)
  // 741:       if plat.is_undefined break
  // 742:       inc &priority
  // 743:       !platform_specific_priority(supported_platform platform) priority
  // 744:       if plat == NONE break
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._supported_platforms;
  arguments->slots[1] = func__81_3;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__81_14;
}
static void entry__81_4(void) {
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
  // 739: ... :
  // 740:   $plat supported_platforms(platform)
  // 741:   if plat.is_undefined break
  // 742:   inc &priority
  // 743:   !platform_specific_priority(supported_platform platform) priority
  // 744:   if plat == NONE break
  // 745:   !platform plat
  frame->slots[4] /* temp__1 */ = create_closure(entry__81_5, 0);
  // 739: forever:
  // 740:   $plat supported_platforms(platform)
  // 741:   if plat.is_undefined break
  // 742:   inc &priority
  // 743:   !platform_specific_priority(supported_platform platform) priority
  // 744:   if plat == NONE break
  // 745:   !platform plat
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame->cont = cont__81_13;
}
static void entry__81_5(void) {
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
  // 740: $plat supported_platforms(platform)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* platform */;
  result_count = 1;
  myself = var._supported_platforms;
  func = myself->type;
  frame->cont = cont__81_6;
}
static void cont__81_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* plat */, arguments->slots[0]);
  // 741: ... plat.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* plat */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__81_7;
}
static void cont__81_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 741: if plat.is_undefined break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* break */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__81_8;
}
static void cont__81_8(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 742: inc &priority
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* priority */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__81_9;
}
static void cont__81_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* priority */ = arguments->slots[0];
  // 743: !platform_specific_priority(supported_platform platform) priority
  frame->slots[5] /* temp__1 */ = ((CELL *)frame->slots[2])->contents /* priority */;
  // 743: !platform_specific_priority(supported_platform platform)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* supported_platform */;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* platform */;
  arguments->slots[2] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = var._platform_specific_priority;
  func = myself->type;
  frame->cont = cont__81_10;
}
static void cont__81_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._platform_specific_priority = arguments->slots[0];
  // 744: ... plat == NONE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* plat */;
  arguments->slots[1] = var._NONE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__81_11;
}
static void cont__81_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 744: if plat == NONE break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* break */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__81_12;
}
static void cont__81_12(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 745: !platform plat
  ((CELL *)frame->slots[0])->contents /* platform */ = frame->slots[4] /* plat */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__81_13(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__81_3(void) {
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
  // 736: $$platform supported_platform
  ((CELL *)frame->slots[2])->contents /* platform */ = frame->slots[0] /* supported_platform */;
  // 737: $$priority 0
  ((CELL *)frame->slots[3])->contents /* priority */ = number__0;
  // 738: ... : (-> break)
  // 739:   forever:
  // 740:     $plat supported_platforms(platform)
  // 741:     if plat.is_undefined break
  // 742:     inc &priority
  // 743:     !platform_specific_priority(supported_platform platform) priority
  // 744:     if plat == NONE break
  // 745:     !platform plat
  frame->slots[4] /* temp__1 */ = create_closure(entry__81_4, 0);
  // 738: do: (-> break)
  // 739:   forever:
  // 740:     $plat supported_platforms(platform)
  // 741:     if plat.is_undefined break
  // 742:     inc &priority
  // 743:     !platform_specific_priority(supported_platform platform) priority
  // 744:     if plat == NONE break
  // 745:     !platform plat
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__do();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__81_14(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 747: main_info.is_a_directory
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_info();
  result_count = 1;
  myself = get__is_a_directory();
  func = myself->type;
  frame->cont = cont__81_15;
}
static void cont__81_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 746: if
  // 747:   main_info.is_a_directory:
  // 748:     %mode LIB
  // 749:     if verbose: ewriteln "list dependencies for " main_filename
  // 750:     compile_modules main_filename behind(main_filename '/' -1)
  // 751:   :
  // 752:     compile_exe: (mod_filename mod_name)
  // 753:       if verbose: ewriteln "list dependencies for " mod_filename
  // 754:       compile_module mod_filename mod_name
  // 755:     writeln "runtime/linker.c"
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__81_16;
  arguments->slots[2] = func__81_23;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__81_33;
}
static void entry__81_16(void) {
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
  // 749: if verbose: ewriteln "list dependencies for " main_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = func__81_17;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__81_19;
}
static void entry__81_17(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 749: ... ewriteln "list dependencies for " main_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__81_18;
  arguments->slots[1] = get__main_filename();
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__81_19(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 750: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__81_20;
}
static void cont__81_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 750: ... behind(main_filename '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__81_21;
}
static void cont__81_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 750: compile_modules main_filename behind(main_filename '/' -1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = var._compile_modules;
  func = myself->type;
  frame->cont = cont__81_22;
}
static void cont__81_22(void) {
  myself = frame->slots[0] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__81_23(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 752: compile_exe: (mod_filename mod_name)
  // 753:   if verbose: ewriteln "list dependencies for " mod_filename
  // 754:   compile_module mod_filename mod_name
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__81_24;
  result_count = 0;
  myself = var._compile_exe;
  func = myself->type;
  frame->cont = cont__81_27;
}
static void entry__81_24(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // mod_filename: 0
  // mod_name: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 753: ... : ewriteln "list dependencies for " mod_filename
  frame->slots[2] /* temp__1 */ = create_closure(entry__81_25, 0);
  // 753: if verbose: ewriteln "list dependencies for " mod_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__81_26;
}
static void entry__81_25(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // mod_filename: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* mod_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 753: ... ewriteln "list dependencies for " mod_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__81_18;
  arguments->slots[1] = frame->slots[0] /* mod_filename */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__81_26(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 754: compile_module mod_filename mod_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = frame->slots[1] /* mod_name */;
  result_count = frame->caller_result_count;
  myself = var._compile_module;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__81_27(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 755: writeln "runtime/linker.c"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__81_28;
  result_count = 0;
  myself = get__writeln();
  func = myself->type;
  frame->cont = cont__81_29;
}
static void cont__81_29(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 756: writeln "runtime/memory.c"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__81_30;
  result_count = 0;
  myself = get__writeln();
  func = myself->type;
  frame->cont = cont__81_31;
}
static void cont__81_31(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 757: writeln "runtime/debugger.c"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__81_32;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__81_33(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 758: $prefix_path current_path()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__current_path();
  func = myself->type;
  frame->cont = cont__81_34;
}
static void cont__81_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[0] /* prefix_path */, arguments->slots[0]);
  // 759: ... : ($filename)
  // 760:   without_prefix &filename prefix_path
  // 761:   without_prefix &filename '/'
  // 762:   writeln filename
  frame->slots[1] /* temp__1 */ = create_closure(entry__81_35, 1);
  // 759: for_each dependencies: ($filename)
  // 760:   without_prefix &filename prefix_path
  // 761:   without_prefix &filename '/'
  // 762:   writeln filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._dependencies;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__82_2(void) {
  allocate_initialized_frame_gc(2, 12);
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
  // 766: $codeblocks_path string(mod_filename ".codeblocks")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = string__82_3;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__82_4;
}
static void cont__82_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* codeblocks_path */, arguments->slots[0]);
  // 767: $info stat(codeblocks_path)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* codeblocks_path */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__82_5;
}
static void cont__82_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* info */, arguments->slots[0]);
  // 768: ... info.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* info */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__82_6;
}
static void cont__82_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 768: ... :
  // 769:   ewrite "
  // 770:     The directory "@(codeblocks_path)" already exists!
  frame->slots[11] /* temp__2 */ = create_closure(entry__82_7, 0);
  // 768: if info.is_defined:
  // 769:   ewrite "
  // 770:     The directory "@(codeblocks_path)" already exists!
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__1 */;
  arguments->slots[1] = frame->slots[11] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__82_11;
}
static void entry__82_7(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // codeblocks_path: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* codeblocks_path */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 769: ... "
  // 770:   The directory "@(codeblocks_path)" already exists!
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__82_8;
  arguments->slots[1] = frame->slots[0] /* codeblocks_path */;
  arguments->slots[2] = string__82_9;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__82_10;
}
static void cont__82_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 769: ewrite "
  // 770:   The directory "@(codeblocks_path)" already exists!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewrite();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__82_11(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 771: ... : ewriteln "build Code::Blocks project in " codeblocks_path
  frame->slots[10] /* temp__1 */ = create_closure(entry__82_12, 0);
  // 771: if verbose: ewriteln "build Code::Blocks project in " codeblocks_path
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = frame->slots[10] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__82_14;
}
static void entry__82_12(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // codeblocks_path: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* codeblocks_path */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 771: ... ewriteln "build Code::Blocks project in " codeblocks_path
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__82_13;
  arguments->slots[1] = frame->slots[0] /* codeblocks_path */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__82_14(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 772: compile_module mod_filename mod_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = frame->slots[1] /* mod_name */;
  result_count = 0;
  myself = var._compile_module;
  func = myself->type;
  frame->cont = cont__82_15;
}
static void cont__82_15(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 773: show_file_list
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._show_file_list;
  func = myself->type;
  frame->cont = cont__82_16;
}
static void cont__82_16(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 774: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__82_17;
}
static void cont__82_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__2 */ = arguments->slots[0];
  // 774: ... truncate_until(main_filename '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[11] /* temp__2 */;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__82_18;
}
static void cont__82_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 774: $basename truncate_until(main_filename '/' -1) .without_suffix. ".sim"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__1 */;
  arguments->slots[1] = string__66_13;
  result_count = 1;
  myself = get__without_suffix();
  func = myself->type;
  frame->cont = cont__82_19;
}
static void cont__82_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* basename */, arguments->slots[0]);
  // 775: $prefix_path current_path()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__current_path();
  func = myself->type;
  frame->cont = cont__82_20;
}
static void cont__82_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* prefix_path */, arguments->slots[0]);
  // 776: ... codeblocks_path .without_prefix. prefix_path
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* codeblocks_path */;
  arguments->slots[1] = frame->slots[5] /* prefix_path */;
  result_count = 1;
  myself = get__without_prefix();
  func = myself->type;
  frame->cont = cont__82_21;
}
static void cont__82_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 776: $depth count_occurrences(codeblocks_path .without_prefix. prefix_path '/')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__1 */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__count_occurrences();
  func = myself->type;
  frame->cont = cont__82_22;
}
static void cont__82_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* depth */, arguments->slots[0]);
  // 777: $path_prefix dup("../" depth)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__82_23;
  arguments->slots[1] = frame->slots[6] /* depth */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__82_24;
}
static void cont__82_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[7] /* path_prefix */, arguments->slots[0]);
  // 778: $cbp_filename string(codeblocks_path "/" basename ".cbp")
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* codeblocks_path */;
  arguments->slots[1] = string__82_25;
  arguments->slots[2] = frame->slots[4] /* basename */;
  arguments->slots[3] = string__82_26;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__82_27;
}
static void cont__82_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[8] /* cbp_filename */, arguments->slots[0]);
  // 779: mkdir codeblocks_path
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* codeblocks_path */;
  result_count = 0;
  myself = var._mkdir;
  func = myself->type;
  frame->cont = cont__82_28;
}
static void cont__82_28(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 780: $$buf ""
  ((CELL *)frame->slots[9])->contents /* buf */ = empty_string;
  // 781: ... "
  // 782:   <?xml version="1.0" encoding="UTF-8" standalone="yes" ?>
  // 783:   <CodeBlocks_project_file>
  // 784:     <FileVersion major="1" minor="6" />
  // 785:     <Project>
  // 786:       <Option title="@(basename)" />
  // 787:       <Option pch_mode="2" />
  // 788:       <Option compiler="gcc" />
  // 789:       <Build>
  // 790:         <Target title="debug">
  // ...
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__82_29;
  arguments->slots[1] = frame->slots[4] /* basename */;
  arguments->slots[2] = string__82_30;
  arguments->slots[3] = frame->slots[4] /* basename */;
  arguments->slots[4] = string__82_31;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__82_32;
}
static void cont__82_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 781: write_to &buf "
  // 782:   <?xml version="1.0" encoding="UTF-8" standalone="yes" ?>
  // 783:   <CodeBlocks_project_file>
  // 784:     <FileVersion major="1" minor="6" />
  // 785:     <Project>
  // 786:       <Option title="@(basename)" />
  // 787:       <Option pch_mode="2" />
  // 788:       <Option compiler="gcc" />
  // 789:       <Build>
  // 790:         <Target title="debug">
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[9])->contents /* buf */;
  arguments->slots[1] = frame->slots[10] /* temp__1 */;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__82_33;
}
static void cont__82_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[9])->contents /* buf */ = arguments->slots[0];
  // 802: ... : (filename)
  // 803:   write_to &buf "
  // 804:     @
  // 805:           <Add library="@(filename)" />
  frame->slots[10] /* temp__1 */ = create_closure(entry__82_34, 1);
  // 802: for_each libraries: (filename)
  // 803:   write_to &buf "
  // 804:     @
  // 805:           <Add library="@(filename)" />
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__libraries();
  arguments->slots[1] = frame->slots[10] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__82_39;
}
static void entry__82_34(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // filename: 0
  // buf: 1
  frame->slots[1] = myself->closure.frame->slots[9]; /* buf */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 803: ... "
  // 804:   @
  // 805:         <Add library="@(filename)" />
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__82_35;
  arguments->slots[1] = frame->slots[0] /* filename */;
  arguments->slots[2] = string__82_36;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__82_37;
}
static void cont__82_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 803: write_to &buf "
  // 804:   @
  // 805:         <Add library="@(filename)" />
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* buf */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__82_38;
}
static void cont__82_38(void) {
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
static void cont__82_39(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 806: ... "
  // 807:   @
  // 808:   
  // 809:       </Linker>
  // 810:       <Compiler>
  // 811:         <Add option="-Wall" />
  // 812:       </Compiler>
  // 813:       <Unit filename="@(path_prefix)runtime/common.h" />
  // 814:       <Unit filename="@(path_prefix)runtime/linker.h" />
  // 815:       <Unit filename="@(path_prefix)runtime/memory.c">
  // ...
  argument_count = 11;
  arguments = node_p;
  arguments->slots[0] = string__82_40;
  arguments->slots[1] = frame->slots[7] /* path_prefix */;
  arguments->slots[2] = string__82_41;
  arguments->slots[3] = frame->slots[7] /* path_prefix */;
  arguments->slots[4] = string__82_42;
  arguments->slots[5] = frame->slots[7] /* path_prefix */;
  arguments->slots[6] = string__82_43;
  arguments->slots[7] = frame->slots[7] /* path_prefix */;
  arguments->slots[8] = string__82_44;
  arguments->slots[9] = frame->slots[7] /* path_prefix */;
  arguments->slots[10] = string__82_45;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__82_46;
}
static void cont__82_46(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 806: write_to &buf "
  // 807:   @
  // 808:   
  // 809:       </Linker>
  // 810:       <Compiler>
  // 811:         <Add option="-Wall" />
  // 812:       </Compiler>
  // 813:       <Unit filename="@(path_prefix)runtime/common.h" />
  // 814:       <Unit filename="@(path_prefix)runtime/linker.h" />
  // 815:       <Unit filename="@(path_prefix)runtime/memory.c">
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[9])->contents /* buf */;
  arguments->slots[1] = frame->slots[10] /* temp__1 */;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__82_47;
}
static void cont__82_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[9])->contents /* buf */ = arguments->slots[0];
  // 824: ... : ($filename)
  // 825:   without_prefix &filename prefix_path
  // 826:   without_prefix &filename '/'
  // 827:   write_to &buf "
  // 828:     @
  // 829:     
  // 830:         <Unit filename="@(path_prefix)@(filename)">
  // 831:           <Option compilerVar="CC" />
  // 832:         </Unit>
  frame->slots[10] /* temp__1 */ = create_closure(entry__82_48, 1);
  // 824: for_each c_sources: ($filename)
  // 825:   without_prefix &filename prefix_path
  // 826:   without_prefix &filename '/'
  // 827:   write_to &buf "
  // 828:     @
  // 829:     
  // 830:         <Unit filename="@(path_prefix)@(filename)">
  // 831:           <Option compilerVar="CC" />
  // 832:         </Unit>
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._c_sources;
  arguments->slots[1] = frame->slots[10] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__82_55;
}
static void entry__82_48(void) {
  allocate_initialized_frame_gc(4, 5);
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
  // 825: without_prefix &filename prefix_path
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* filename */;
  arguments->slots[1] = frame->slots[1] /* prefix_path */;
  result_count = 1;
  myself = get__without_prefix();
  func = myself->type;
  frame->cont = cont__82_49;
}
static void cont__82_49(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* filename */ = arguments->slots[0];
  // 826: without_prefix &filename '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* filename */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__without_prefix();
  func = myself->type;
  frame->cont = cont__82_50;
}
static void cont__82_50(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* filename */ = arguments->slots[0];
  // 827: ... "
  // 828:   @
  // 829:   
  // 830:       <Unit filename="@(path_prefix)@(filename)">
  // 831:         <Option compilerVar="CC" />
  // 832:       </Unit>
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__82_51;
  arguments->slots[1] = frame->slots[3] /* path_prefix */;
  arguments->slots[2] = ((CELL *)frame->slots[0])->contents /* filename */;
  arguments->slots[3] = string__82_52;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__82_53;
}
static void cont__82_53(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 827: write_to &buf "
  // 828:   @
  // 829:   
  // 830:       <Unit filename="@(path_prefix)@(filename)">
  // 831:         <Option compilerVar="CC" />
  // 832:       </Unit>
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* buf */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__82_54;
}
static void cont__82_54(void) {
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
static void cont__82_55(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 833: write_to &buf "
  // 834:       <Extensions>
  // 835:         <code_completion />
  // 836:         <debugger />
  // 837:       </Extensions>
  // 838:     </Project>
  // 839:   </CodeBlocks_project_file>
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[9])->contents /* buf */;
  arguments->slots[1] = string__82_56;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__82_57;
}
static void cont__82_57(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[9])->contents /* buf */ = arguments->slots[0];
  // 840: save cbp_filename buf
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* cbp_filename */;
  arguments->slots[1] = ((CELL *)frame->slots[9])->contents /* buf */;
  result_count = frame->caller_result_count;
  myself = get__save();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__82_1_build_codeblocks_project(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 765: compile_exe: (mod_filename mod_name)
  // 766:   $codeblocks_path string(mod_filename ".codeblocks")
  // 767:   $info stat(codeblocks_path)
  // 768:   if info.is_defined:
  // 769:     ewrite "
  // 770:       The directory "@(codeblocks_path)" already exists!
  // 771:   if verbose: ewriteln "build Code::Blocks project in " codeblocks_path
  // 772:   compile_module mod_filename mod_name
  // 773:   show_file_list
  // 774:   $basename truncate_until(main_filename '/' -1) .without_suffix. ".sim"
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__82_2;
  result_count = frame->caller_result_count;
  myself = var._compile_exe;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__83_1_build_library(void) {
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
  // 843: ... action == "simrun"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._action;
  arguments->slots[1] = string__83_2;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__83_3;
}
static void cont__83_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 843: if action == "simrun": Error "Cannot run a directory!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__83_4;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__83_6;
}
static void entry__83_4(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 843: ... Error "Cannot run a directory!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__83_5;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__83_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 845: if
  // 846:   do_extract_documentation:
  // 847:     extract_documentation main_filename
  // 848:   :
  // 849:     $$version ""
  // 850:     $$so_version ""
  // 851:     $version_filename string(main_filename "/VERSION")
  // 852:     if file_exists(version_filename):
  // 853:       !version string('-' load(version_filename).trim)
  // 854:       !so_version version .truncate_from. '.'
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__do_extract_documentation();
  arguments->slots[1] = func__83_7;
  arguments->slots[2] = func__83_8;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__83_88;
}
static void entry__83_86(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // err: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* err */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 915: ... err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* err */;
  result_count = 1;
  myself = get__from_utf8();
  func = myself->type;
  frame->cont = cont__83_87;
}
static void cont__83_87(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 915: ... Error err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__83_81(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // err: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* err */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 908: ... err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* err */;
  result_count = 1;
  myself = get__from_utf8();
  func = myself->type;
  frame->cont = cont__83_82;
}
static void cont__83_82(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 908: ... Error err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__83_72(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // err: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* err */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 897: ... err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* err */;
  result_count = 1;
  myself = get__from_utf8();
  func = myself->type;
  frame->cont = cont__83_73;
}
static void cont__83_73(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 897: ... Error err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__83_65(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // err: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* err */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 889: ... err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* err */;
  result_count = 1;
  myself = get__from_utf8();
  func = myself->type;
  frame->cont = cont__83_66;
}
static void cont__83_66(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 889: ... Error err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__83_59(void) {
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
  // 885: "-Wl,-soname,libsim-@(base_filename)@(so_version).so.@(MAJOR)"
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__83_60;
  arguments->slots[1] = frame->slots[0] /* base_filename */;
  arguments->slots[2] = ((CELL *)frame->slots[1])->contents /* so_version */;
  arguments->slots[3] = string__76_27;
  arguments->slots[4] = var._MAJOR;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__83_61;
}
static void cont__83_61(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 886: library_paths_and_file_list()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = var._library_paths_and_file_list;
  func = myself->type;
  frame->cont = cont__83_62;
}
static void cont__83_62(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 883: Gcc $_out $err $success
  // 884:   "-shared"
  // 885:   "-Wl,-soname,libsim-@(base_filename)@(so_version).so.@(MAJOR)"
  // 886:   library_paths_and_file_list()*
  // 887:   "-o"
  // 888:   lib_filename
  argument_count = 0;
  arguments = node_p;
  arguments->slots[argument_count++] = string__83_63;
  arguments->slots[argument_count++] = frame->slots[6] /* temp__1 */;
  unfold(frame->slots[7] /* temp__2 */);
  arguments->slots[argument_count++] = string__69_6;
  arguments->slots[argument_count++] = frame->slots[2] /* lib_filename */;
  result_count = 3;
  myself = var._Gcc;
  func = myself->type;
  frame->cont = cont__83_64;
}
static void cont__83_64(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__3 */ = arguments->slots[0];
  frame->slots[9] /* temp__4 */ = arguments->slots[1];
  frame->slots[10] /* temp__5 */ = arguments->slots[2];
  // 883: ... _out
  initialize_future(frame->slots[3] /* out */, frame->slots[8] /* temp__3 */);
  // 883: ... err
  initialize_future(frame->slots[4] /* err */, frame->slots[9] /* temp__4 */);
  // 883: ... success
  initialize_future(frame->slots[5] /* success */, frame->slots[10] /* temp__5 */);
  // 889: ... : Error err.from_utf8
  frame->slots[6] /* temp__1 */ = create_closure(entry__83_65, 0);
  // 889: unless success: Error err.from_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* success */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__83_67(void) {
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
  // 893: library_paths_and_file_list()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = var._library_paths_and_file_list;
  func = myself->type;
  frame->cont = cont__83_68;
}
static void cont__83_68(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 894: "-lsim-@(MAJOR)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__83_69;
  arguments->slots[1] = var._MAJOR;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__83_70;
}
static void cont__83_70(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 891: Gcc $_out $err $success
  // 892:   "-shared"
  // 893:   library_paths_and_file_list()*
  // 894:   "-lsim-@(MAJOR)"
  // 895:   "-o"
  // 896:   lib_filename
  argument_count = 0;
  arguments = node_p;
  arguments->slots[argument_count++] = string__83_63;
  unfold(frame->slots[4] /* temp__1 */);
  arguments->slots[argument_count++] = frame->slots[5] /* temp__2 */;
  arguments->slots[argument_count++] = string__69_6;
  arguments->slots[argument_count++] = frame->slots[0] /* lib_filename */;
  result_count = 3;
  myself = var._Gcc;
  func = myself->type;
  frame->cont = cont__83_71;
}
static void cont__83_71(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  frame->slots[7] /* temp__4 */ = arguments->slots[1];
  frame->slots[8] /* temp__5 */ = arguments->slots[2];
  // 891: ... _out
  initialize_future(frame->slots[1] /* out */, frame->slots[6] /* temp__3 */);
  // 891: ... err
  initialize_future(frame->slots[2] /* err */, frame->slots[7] /* temp__4 */);
  // 891: ... success
  initialize_future(frame->slots[3] /* success */, frame->slots[8] /* temp__5 */);
  // 897: ... : Error err.from_utf8
  frame->slots[4] /* temp__1 */ = create_closure(entry__83_72, 0);
  // 897: unless success: Error err.from_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* success */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__83_74(void) {
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
  // 901: "
  // 902:   -Wl,-install_name,libsim-@(base_filename)@(so_version)-@(MAJOR)@
  // 903:   .dylib@
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = string__83_75;
  arguments->slots[1] = frame->slots[0] /* base_filename */;
  arguments->slots[2] = ((CELL *)frame->slots[1])->contents /* so_version */;
  arguments->slots[3] = string__66_46;
  arguments->slots[4] = var._MAJOR;
  arguments->slots[5] = string__83_30;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__83_76;
}
static void cont__83_76(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 904: library_paths_and_file_list()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = var._library_paths_and_file_list;
  func = myself->type;
  frame->cont = cont__83_77;
}
static void cont__83_77(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 905: "-lsim-@(MAJOR)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__83_69;
  arguments->slots[1] = var._MAJOR;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__83_78;
}
static void cont__83_78(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__3 */ = arguments->slots[0];
  // 899: Gcc $_out $err $success
  // 900:   "-dynamiclib"
  // 901:   "
  // 902:     -Wl,-install_name,libsim-@(base_filename)@(so_version)-@(MAJOR)@
  // 903:     .dylib@
  // 904:   library_paths_and_file_list()*
  // 905:   "-lsim-@(MAJOR)"
  // 906:   "-o"
  // 907:   lib_filename
  argument_count = 0;
  arguments = node_p;
  arguments->slots[argument_count++] = string__83_79;
  arguments->slots[argument_count++] = frame->slots[6] /* temp__1 */;
  unfold(frame->slots[7] /* temp__2 */);
  arguments->slots[argument_count++] = frame->slots[8] /* temp__3 */;
  arguments->slots[argument_count++] = string__69_6;
  arguments->slots[argument_count++] = frame->slots[2] /* lib_filename */;
  result_count = 3;
  myself = var._Gcc;
  func = myself->type;
  frame->cont = cont__83_80;
}
static void cont__83_80(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__4 */ = arguments->slots[0];
  frame->slots[10] /* temp__5 */ = arguments->slots[1];
  frame->slots[11] /* temp__6 */ = arguments->slots[2];
  // 899: ... _out
  initialize_future(frame->slots[3] /* out */, frame->slots[9] /* temp__4 */);
  // 899: ... err
  initialize_future(frame->slots[4] /* err */, frame->slots[10] /* temp__5 */);
  // 899: ... success
  initialize_future(frame->slots[5] /* success */, frame->slots[11] /* temp__6 */);
  // 908: ... : Error err.from_utf8
  frame->slots[6] /* temp__1 */ = create_closure(entry__83_81, 0);
  // 908: unless success: Error err.from_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* success */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__83_83(void) {
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
  // 912: library_paths_and_file_list()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = var._library_paths_and_file_list;
  func = myself->type;
  frame->cont = cont__83_84;
}
static void cont__83_84(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 910: Gcc $_out $err $success
  // 911:   "-shared"
  // 912:   library_paths_and_file_list()*
  // 913:   "-o"
  // 914:   lib_filename
  argument_count = 0;
  arguments = node_p;
  arguments->slots[argument_count++] = string__83_63;
  unfold(frame->slots[4] /* temp__1 */);
  arguments->slots[argument_count++] = string__69_6;
  arguments->slots[argument_count++] = frame->slots[0] /* lib_filename */;
  result_count = 3;
  myself = var._Gcc;
  func = myself->type;
  frame->cont = cont__83_85;
}
static void cont__83_85(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  frame->slots[6] /* temp__3 */ = arguments->slots[1];
  frame->slots[7] /* temp__4 */ = arguments->slots[2];
  // 910: ... _out
  initialize_future(frame->slots[1] /* out */, frame->slots[5] /* temp__2 */);
  // 910: ... err
  initialize_future(frame->slots[2] /* err */, frame->slots[6] /* temp__3 */);
  // 910: ... success
  initialize_future(frame->slots[3] /* success */, frame->slots[7] /* temp__4 */);
  // 915: ... : Error err.from_utf8
  frame->slots[4] /* temp__1 */ = create_closure(entry__83_86, 0);
  // 915: unless success: Error err.from_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* success */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__83_54(void) {
  allocate_initialized_frame_gc(3, 8);
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
  // 879: if verbose: ewriteln "linking dynamic library"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = func__83_55;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__83_57;
}
static void entry__83_55(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 879: ... ewriteln "linking dynamic library"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__83_56;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__83_57(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 881: operating_system()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__operating_system();
  func = myself->type;
  frame->cont = cont__83_58;
}
static void cont__83_58(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 882: ... :
  // 883:   Gcc $_out $err $success
  // 884:     "-shared"
  // 885:     "-Wl,-soname,libsim-@(base_filename)@(so_version).so.@(MAJOR)"
  // 886:     library_paths_and_file_list()*
  // 887:     "-o"
  // 888:     lib_filename
  // 889:   unless success: Error err.from_utf8
  frame->slots[4] /* temp__2 */ = create_closure(entry__83_59, 0);
  // 890: ... :
  // 891:   Gcc $_out $err $success
  // 892:     "-shared"
  // 893:     library_paths_and_file_list()*
  // 894:     "-lsim-@(MAJOR)"
  // 895:     "-o"
  // 896:     lib_filename
  // 897:   unless success: Error err.from_utf8
  frame->slots[5] /* temp__3 */ = create_closure(entry__83_67, 0);
  // 898: ... :
  // 899:   Gcc $_out $err $success
  // 900:     "-dynamiclib"
  // 901:     "
  // 902:       -Wl,-install_name,libsim-@(base_filename)@(so_version)-@(MAJOR)@
  // 903:       .dylib@
  // 904:     library_paths_and_file_list()*
  // 905:     "-lsim-@(MAJOR)"
  // 906:     "-o"
  // 907:     lib_filename
  // ...
  frame->slots[6] /* temp__4 */ = create_closure(entry__83_74, 0);
  // 909: :
  // 910:   Gcc $_out $err $success
  // 911:     "-shared"
  // 912:     library_paths_and_file_list()*
  // 913:     "-o"
  // 914:     lib_filename
  // 915:   unless success: Error err.from_utf8
  frame->slots[7] /* temp__5 */ = create_closure(entry__83_83, 0);
  // 880: case
  // 881:   operating_system()
  // 882:   "linux":
  // 883:     Gcc $_out $err $success
  // 884:       "-shared"
  // 885:       "-Wl,-soname,libsim-@(base_filename)@(so_version).so.@(MAJOR)"
  // 886:       library_paths_and_file_list()*
  // 887:       "-o"
  // 888:       lib_filename
  // 889:     unless success: Error err.from_utf8
  // ...
  argument_count = 8;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = string__76_23;
  arguments->slots[2] = frame->slots[4] /* temp__2 */;
  arguments->slots[3] = string__83_36;
  arguments->slots[4] = frame->slots[5] /* temp__3 */;
  arguments->slots[5] = string__83_37;
  arguments->slots[6] = frame->slots[6] /* temp__4 */;
  arguments->slots[7] = frame->slots[7] /* temp__5 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__83_7(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 847: extract_documentation main_filename
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  result_count = frame->caller_result_count;
  myself = get__extract_documentation();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__83_8(void) {
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
  // 849: $$version ""
  ((CELL *)frame->slots[0])->contents /* version */ = empty_string;
  // 850: $$so_version ""
  ((CELL *)frame->slots[1])->contents /* so_version */ = empty_string;
  // 851: $version_filename string(main_filename "/VERSION")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  arguments->slots[1] = string__83_9;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__83_10;
}
static void cont__83_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* version_filename */, arguments->slots[0]);
  // 852: ... file_exists(version_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* version_filename */;
  result_count = 1;
  myself = get__file_exists();
  func = myself->type;
  frame->cont = cont__83_11;
}
static void cont__83_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 852: ... :
  // 853:   !version string('-' load(version_filename).trim)
  // 854:   !so_version version .truncate_from. '.'
  frame->slots[6] /* temp__2 */ = create_closure(entry__83_12, 0);
  // 852: if file_exists(version_filename):
  // 853:   !version string('-' load(version_filename).trim)
  // 854:   !so_version version .truncate_from. '.'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__83_17;
}
static void entry__83_12(void) {
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
  // 853: ... load(version_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* version_filename */;
  result_count = 1;
  myself = get__load();
  func = myself->type;
  frame->cont = cont__83_13;
}
static void cont__83_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 853: ... load(version_filename).trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__83_14;
}
static void cont__83_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 853: !version string('-' load(version_filename).trim)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__45;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__83_15;
}
static void cont__83_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* version */ = arguments->slots[0];
  // 854: !so_version version .truncate_from. '.'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* version */;
  arguments->slots[1] = character__46;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__83_16;
}
static void cont__83_16(void) {
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
static void cont__83_17(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 855: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__83_18;
}
static void cont__83_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 855: $base_filename truncate_until(main_filename '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__83_19;
}
static void cont__83_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* base_filename */, arguments->slots[0]);
  // 859: operating_system()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__operating_system();
  func = myself->type;
  frame->cont = cont__83_20;
}
static void cont__83_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 861: -> string("libsim-" base_filename version ".so.@(MAJOR)")
  frame->slots[6] /* temp__2 */ = create_closure(entry__83_21, 0);
  // 863: -> string("libsim-" base_filename version "-@(MAJOR).dll")
  frame->slots[7] /* temp__3 */ = create_closure(entry__83_25, 0);
  // 865: -> string("libsim-" base_filename version "-@(MAJOR).dylib")
  frame->slots[8] /* temp__4 */ = create_closure(entry__83_29, 0);
  // 866: -> string("libsim-" base_filename ".so")
  frame->slots[9] /* temp__5 */ = create_closure(entry__83_33, 0);
  // 857: $lib_filename
  // 858:   case
  // 859:     operating_system()
  // 860:     "linux"
  // 861:     -> string("libsim-" base_filename version ".so.@(MAJOR)")
  // 862:     "cygwin"
  // 863:     -> string("libsim-" base_filename version "-@(MAJOR).dll")
  // 864:     "darwin"
  // 865:     -> string("libsim-" base_filename version "-@(MAJOR).dylib")
  // 866:     -> string("libsim-" base_filename ".so")
  argument_count = 8;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = string__76_23;
  arguments->slots[2] = frame->slots[6] /* temp__2 */;
  arguments->slots[3] = string__83_36;
  arguments->slots[4] = frame->slots[7] /* temp__3 */;
  arguments->slots[5] = string__83_37;
  arguments->slots[6] = frame->slots[8] /* temp__4 */;
  arguments->slots[7] = frame->slots[9] /* temp__5 */;
  result_count = 1;
  myself = get__case();
  func = myself->type;
  frame->cont = cont__83_38;
}
static void entry__83_21(void) {
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
  // 861: ... ".so.@(MAJOR)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__76_27;
  arguments->slots[1] = var._MAJOR;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__83_22;
}
static void cont__83_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 861: ... string("libsim-" base_filename version ".so.@(MAJOR)")
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__83_23;
  arguments->slots[1] = frame->slots[0] /* base_filename */;
  arguments->slots[2] = ((CELL *)frame->slots[1])->contents /* version */;
  arguments->slots[3] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__83_24;
}
static void cont__83_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 861: -> string("libsim-" base_filename version ".so.@(MAJOR)")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__83_25(void) {
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
  // 863: ... "-@(MAJOR).dll"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__66_46;
  arguments->slots[1] = var._MAJOR;
  arguments->slots[2] = string__83_26;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__83_27;
}
static void cont__83_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 863: ... string("libsim-" base_filename version "-@(MAJOR).dll")
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__83_23;
  arguments->slots[1] = frame->slots[0] /* base_filename */;
  arguments->slots[2] = ((CELL *)frame->slots[1])->contents /* version */;
  arguments->slots[3] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__83_28;
}
static void cont__83_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 863: -> string("libsim-" base_filename version "-@(MAJOR).dll")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__83_29(void) {
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
  // 865: ... "-@(MAJOR).dylib"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__66_46;
  arguments->slots[1] = var._MAJOR;
  arguments->slots[2] = string__83_30;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__83_31;
}
static void cont__83_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 865: ... string("libsim-" base_filename version "-@(MAJOR).dylib")
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__83_23;
  arguments->slots[1] = frame->slots[0] /* base_filename */;
  arguments->slots[2] = ((CELL *)frame->slots[1])->contents /* version */;
  arguments->slots[3] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__83_32;
}
static void cont__83_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 865: -> string("libsim-" base_filename version "-@(MAJOR).dylib")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__83_33(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // base_filename: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* base_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 866: ... string("libsim-" base_filename ".so")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__83_23;
  arguments->slots[1] = frame->slots[0] /* base_filename */;
  arguments->slots[2] = string__83_34;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__83_35;
}
static void cont__83_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 866: -> string("libsim-" base_filename ".so")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__83_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* lib_filename */, arguments->slots[0]);
  // 868: ... : ewriteln "build library " lib_filename
  frame->slots[5] /* temp__1 */ = create_closure(entry__83_39, 0);
  // 868: if verbose: ewriteln "build library " lib_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__83_41;
}
static void entry__83_39(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // lib_filename: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* lib_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 868: ... ewriteln "build library " lib_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__83_40;
  arguments->slots[1] = frame->slots[0] /* lib_filename */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__83_41(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 869: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__83_42;
}
static void cont__83_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 869: ... behind(main_filename '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__83_43;
}
static void cont__83_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 869: compile_modules main_filename behind(main_filename '/' -1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = var._compile_modules;
  func = myself->type;
  frame->cont = cont__83_44;
}
static void cont__83_44(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 870: ... :
  // 871:   $info stat(lib_filename)
  // 872:   if
  // 873:     ||
  // 874:       info.is_undefined
  // 875:       last_modification_time > modification_time_of(info)
  // 876:     :
  // 877:       !do_link true
  frame->slots[5] /* temp__1 */ = create_closure(entry__83_45, 0);
  // 870: unless do_link:
  // 871:   $info stat(lib_filename)
  // 872:   if
  // 873:     ||
  // 874:       info.is_undefined
  // 875:       last_modification_time > modification_time_of(info)
  // 876:     :
  // 877:       !do_link true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_link();
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__83_53;
}
static void entry__83_52(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 877: !do_link true
  set__do_link(get__true());
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__83_45(void) {
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
  // 871: $info stat(lib_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* lib_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__83_46;
}
static void cont__83_46(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* info */, arguments->slots[0]);
  // 874: info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__83_47;
}
static void cont__83_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 875: last_modification_time > modification_time_of(info)
  frame->slots[4] /* temp__3 */ = create_closure(entry__83_48, 0);
  // 873: ||
  // 874:   info.is_undefined
  // 875:   last_modification_time > modification_time_of(info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__83_51;
}
static void entry__83_48(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // info: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 875: ... modification_time_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__83_49;
}
static void cont__83_49(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 875: last_modification_time > modification_time_of(info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = get__last_modification_time();
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__83_50;
}
static void cont__83_50(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 875: last_modification_time > modification_time_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__83_51(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 872: if
  // 873:   ||
  // 874:     info.is_undefined
  // 875:     last_modification_time > modification_time_of(info)
  // 876:   :
  // 877:     !do_link true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = func__83_52;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__83_53(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 878: ... :
  // 879:   if verbose: ewriteln "linking dynamic library"
  // 880:   case
  // 881:     operating_system()
  // 882:     "linux":
  // 883:       Gcc $_out $err $success
  // 884:         "-shared"
  // 885:         "-Wl,-soname,libsim-@(base_filename)@(so_version).so.@(MAJOR)"
  // 886:         library_paths_and_file_list()*
  // 887:         "-o"
  // ...
  frame->slots[5] /* temp__1 */ = create_closure(entry__83_54, 0);
  // 878: if do_link:
  // 879:   if verbose: ewriteln "linking dynamic library"
  // 880:   case
  // 881:     operating_system()
  // 882:     "linux":
  // 883:       Gcc $_out $err $success
  // 884:         "-shared"
  // 885:         "-Wl,-soname,libsim-@(base_filename)@(so_version).so.@(MAJOR)"
  // 886:         library_paths_and_file_list()*
  // 887:         "-o"
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
static void cont__83_88(void) {
  myself = frame->slots[0] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__84_18(void) {
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
  // 930: ... : ewriteln "compiling runtime module @(filename)"
  frame->slots[3] /* temp__1 */ = create_closure(entry__84_19, 0);
  // 930: if verbose: ewriteln "compiling runtime module @(filename)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__84_22;
}
static void entry__84_19(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // filename: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 930: ... "compiling runtime module @(filename)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__84_20;
  arguments->slots[1] = frame->slots[0] /* filename */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__84_21;
}
static void cont__84_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 930: ... ewriteln "compiling runtime module @(filename)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__84_22(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 931: compile_c c_filename o_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* c_filename */;
  arguments->slots[1] = frame->slots[2] /* o_filename */;
  result_count = frame->caller_result_count;
  myself = var._compile_c;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__84_1_maybe_compile_c_file(void) {
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
  // 918: $c_filename string(filename ".c")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  arguments->slots[1] = string__70_9;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__84_2;
}
static void cont__84_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* c_filename */, arguments->slots[0]);
  // 919: $o_filename string(filename ".o")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  arguments->slots[1] = string__72_80;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__84_3;
}
static void cont__84_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* o_filename */, arguments->slots[0]);
  // 920: $c_info stat(c_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* c_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__84_4;
}
static void cont__84_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* c_info */, arguments->slots[0]);
  // 921: ... c_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* c_info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__84_5;
}
static void cont__84_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 921: ... :
  // 922:   Error "
  // 923:     @quot;@(c_filename)" does not exist!
  frame->slots[6] /* temp__2 */ = create_closure(entry__84_6, 0);
  // 921: if c_info.is_undefined:
  // 922:   Error "
  // 923:     @quot;@(c_filename)" does not exist!
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__84_10;
}
static void entry__84_6(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // c_filename: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* c_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 922: ... "
  // 923:   @quot;@(c_filename)" does not exist!
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__84_7;
  arguments->slots[1] = frame->slots[0] /* c_filename */;
  arguments->slots[2] = string__84_8;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__84_9;
}
static void cont__84_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 922: Error "
  // 923:   @quot;@(c_filename)" does not exist!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__84_10(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 924: $o_info stat(o_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* o_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__84_11;
}
static void cont__84_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* o_info */, arguments->slots[0]);
  // 927: o_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* o_info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__84_12;
}
static void cont__84_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 928: modification_time_of(c_info) > modification_time_of(o_info)
  frame->slots[7] /* temp__3 */ = create_closure(entry__84_13, 0);
  // 926: ||
  // 927:   o_info.is_undefined
  // 928:   modification_time_of(c_info) > modification_time_of(o_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__84_17;
}
static void entry__84_13(void) {
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
  // 928: ... modification_time_of(o_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* o_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__84_14;
}
static void cont__84_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 928: modification_time_of(c_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* c_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__84_15;
}
static void cont__84_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 928: modification_time_of(c_info) > modification_time_of(o_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__84_16;
}
static void cont__84_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 928: modification_time_of(c_info) > modification_time_of(o_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__84_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 929: :
  // 930:   if verbose: ewriteln "compiling runtime module @(filename)"
  // 931:   compile_c c_filename o_filename
  frame->slots[8] /* temp__4 */ = create_closure(entry__84_18, 0);
  // 925: if
  // 926:   ||
  // 927:     o_info.is_undefined
  // 928:     modification_time_of(c_info) > modification_time_of(o_info)
  // 929:   :
  // 930:     if verbose: ewriteln "compiling runtime module @(filename)"
  // 931:     compile_c c_filename o_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__86_1_format_number(void) {
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
  // 941: to_string &val
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* val */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__86_2;
}
static void cont__86_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* val */ = arguments->slots[0];
  // 942: $$ac 0
  ((CELL *)frame->slots[3])->contents /* ac */ = number__0;
  // 943: ... : (-> break)
  // 944:   for_each val: (i chr)
  // 945:     if chr == '.':
  // 946:       !ac length_of(val)-i
  // 947:       if n > i-1: append dup(" " n-(i-1)) &val
  // 948:       break
  frame->slots[4] /* temp__1 */ = create_closure(entry__86_3, 0);
  // 943: do: (-> break)
  // 944:   for_each val: (i chr)
  // 945:     if chr == '.':
  // 946:       !ac length_of(val)-i
  // 947:       if n > i-1: append dup(" " n-(i-1)) &val
  // 948:       break
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__86_19;
}
static void entry__86_3(void) {
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
  // 944: ... : (i chr)
  // 945:   if chr == '.':
  // 946:     !ac length_of(val)-i
  // 947:     if n > i-1: append dup(" " n-(i-1)) &val
  // 948:     break
  frame->slots[4] /* temp__1 */ = create_closure(entry__86_4, 2);
  // 944: for_each val: (i chr)
  // 945:   if chr == '.':
  // 946:     !ac length_of(val)-i
  // 947:     if n > i-1: append dup(" " n-(i-1)) &val
  // 948:     break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* val */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__86_18;
}
static void entry__86_6(void) {
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
  // 946: ... length_of(val)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* val */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__86_7;
}
static void cont__86_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 946: !ac length_of(val)-i
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* i */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__86_8;
}
static void cont__86_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* ac */ = arguments->slots[0];
  // 947: ... i-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* i */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__86_9;
}
static void cont__86_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 947: ... n > i-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* n */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__86_10;
}
static void cont__86_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 947: ... : append dup(" " n-(i-1)) &val
  frame->slots[7] /* temp__3 */ = create_closure(entry__86_11, 0);
  // 947: if n > i-1: append dup(" " n-(i-1)) &val
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__86_17;
}
static void entry__86_11(void) {
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
  // 947: ... i-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* i */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__86_12;
}
static void cont__86_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 947: ... n-(i-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* n */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__86_13;
}
static void cont__86_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 947: ... dup(" " n-(i-1))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__86_14;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__86_15;
}
static void cont__86_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 947: ... append dup(" " n-(i-1)) &val
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* val */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__86_16;
}
static void cont__86_16(void) {
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
static void cont__86_17(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 948: break
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[4] /* break */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__86_4(void) {
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
  // 945: ... chr == '.'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* chr */;
  arguments->slots[1] = character__46;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__86_5;
}
static void cont__86_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 945: ... :
  // 946:   !ac length_of(val)-i
  // 947:   if n > i-1: append dup(" " n-(i-1)) &val
  // 948:   break
  frame->slots[7] /* temp__2 */ = create_closure(entry__86_6, 0);
  // 945: if chr == '.':
  // 946:   !ac length_of(val)-i
  // 947:   if n > i-1: append dup(" " n-(i-1)) &val
  // 948:   break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__86_18(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__86_19(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 950: m > ac
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* ac */;
  arguments->slots[1] = frame->slots[2] /* m */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__86_20;
}
static void cont__86_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 950: ... :
  // 951:   append &val dup("0" m-ac)
  frame->slots[5] /* temp__2 */ = create_closure(entry__86_21, 0);
  // 952: :
  // 953:   if ac > m: range &val 1 -(ac-m+1)
  frame->slots[6] /* temp__3 */ = create_closure(entry__86_26, 0);
  // 949: if
  // 950:   m > ac:
  // 951:     append &val dup("0" m-ac)
  // 952:   :
  // 953:     if ac > m: range &val 1 -(ac-m+1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__86_33;
}
static void entry__86_28(void) {
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
  // 953: ... ac-m
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* ac */;
  arguments->slots[1] = frame->slots[2] /* m */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__86_29;
}
static void cont__86_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 953: ... ac-m+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__86_30;
}
static void cont__86_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 953: ... ac-m+1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__86_31;
}
static void cont__86_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 953: ... range &val 1 -(ac-m+1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* val */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__86_32;
}
static void cont__86_32(void) {
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
static void entry__86_21(void) {
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
  // 951: ... m-ac
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* m */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* ac */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__86_22;
}
static void cont__86_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 951: ... dup("0" m-ac)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__86_23;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__86_24;
}
static void cont__86_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 951: append &val dup("0" m-ac)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* val */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__86_25;
}
static void cont__86_25(void) {
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
static void entry__86_26(void) {
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
  // 953: ... ac > m
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* m */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* ac */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__86_27;
}
static void cont__86_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 953: ... : range &val 1 -(ac-m+1)
  frame->slots[4] /* temp__2 */ = create_closure(entry__86_28, 0);
  // 953: if ac > m: range &val 1 -(ac-m+1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__86_33(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 954: -> val
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* val */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__87_1_sim2c__write_timing_info(void) {
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
  // 957: $new_t current_time()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__current_time();
  func = myself->type;
  frame->cont = cont__87_2;
}
static void cont__87_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* new_t */, arguments->slots[0]);
  // 959: filename.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* filename */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__87_3;
}
static void cont__87_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 959: ... :
  // 960:   truncate_until &filename '/' -1
  // 961:   ewriteln
  // 962:     description
  // 963:     ' '
  // 964:     filename
  // 965:     ':'
  // 966:     dup(" " 12-length_of(description))
  // 967:     format_number(new_t-t 2 3)
  // 968:     " s"
  frame->slots[4] /* temp__2 */ = create_closure(entry__87_4, 0);
  // 969: :
  // 970:   ewriteln description ": " format_number(new_t-t 0 3) " s"
  frame->slots[5] /* temp__3 */ = create_closure(entry__87_13, 0);
  // 958: if
  // 959:   filename.is_defined:
  // 960:     truncate_until &filename '/' -1
  // 961:     ewriteln
  // 962:       description
  // 963:       ' '
  // 964:       filename
  // 965:       ':'
  // 966:       dup(" " 12-length_of(description))
  // 967:       format_number(new_t-t 2 3)
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = frame->slots[5] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__87_17;
}
static void entry__87_4(void) {
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
  // 960: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__87_5;
}
static void cont__87_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 960: truncate_until &filename '/' -1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* filename */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__87_6;
}
static void cont__87_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* filename */ = arguments->slots[0];
  // 966: ... length_of(description)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* description */;
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
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 966: ... 12-length_of(description)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__12;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
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
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 966: dup(" " 12-length_of(description))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__86_14;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__87_9;
}
static void cont__87_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 967: ... new_t-t
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* new_t */;
  arguments->slots[1] = var._t;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__87_10;
}
static void cont__87_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__5 */ = arguments->slots[0];
  // 967: format_number(new_t-t 2 3)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__5 */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = number__3;
  result_count = 1;
  myself = var._format_number;
  func = myself->type;
  frame->cont = cont__87_11;
}
static void cont__87_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__4 */ = arguments->slots[0];
  // 961: ewriteln
  // 962:   description
  // 963:   ' '
  // 964:   filename
  // 965:   ':'
  // 966:   dup(" " 12-length_of(description))
  // 967:   format_number(new_t-t 2 3)
  // 968:   " s"
  argument_count = 7;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* description */;
  arguments->slots[1] = character__32;
  arguments->slots[2] = ((CELL *)frame->slots[0])->contents /* filename */;
  arguments->slots[3] = character__58;
  arguments->slots[4] = frame->slots[3] /* temp__1 */;
  arguments->slots[5] = frame->slots[6] /* temp__4 */;
  arguments->slots[6] = string__87_12;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__87_13(void) {
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
  // 970: ... new_t-t
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* new_t */;
  arguments->slots[1] = var._t;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__87_14;
}
static void cont__87_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 970: ... format_number(new_t-t 0 3)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = number__0;
  arguments->slots[2] = number__3;
  result_count = 1;
  myself = var._format_number;
  func = myself->type;
  frame->cont = cont__87_15;
}
static void cont__87_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 970: ewriteln description ": " format_number(new_t-t 0 3) " s"
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* description */;
  arguments->slots[1] = string__87_16;
  arguments->slots[2] = frame->slots[2] /* temp__1 */;
  arguments->slots[3] = string__87_12;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__87_17(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 971: !t current_time()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__current_time();
  func = myself->type;
  frame->cont = cont__87_18;
}
static void cont__87_18(void) {
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
static void entry__88_116(void) {
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
  // 1066: exe_filename .has_prefix. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* exe_filename */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__88_117;
}
static void cont__88_117(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 1067: -> exe_filename
  frame->slots[4] /* temp__3 */ = create_closure(entry__88_118, 0);
  // 1068: -> string("./" exe_filename)
  frame->slots[5] /* temp__4 */ = create_closure(entry__88_119, 0);
  // 1065: if
  // 1066:   exe_filename .has_prefix. '/'
  // 1067:   -> exe_filename
  // 1068:   -> string("./" exe_filename)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  arguments->slots[2] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__88_121;
}
static void entry__88_118(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // exe_filename: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* exe_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1067: -> exe_filename
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* exe_filename */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__88_119(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // exe_filename: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* exe_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1068: ... string("./" exe_filename)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__70_56;
  arguments->slots[1] = frame->slots[0] /* exe_filename */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__88_120;
}
static void cont__88_120(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1068: -> string("./" exe_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__88_121(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1064: exec
  // 1065:   if
  // 1066:     exe_filename .has_prefix. '/'
  // 1067:     -> exe_filename
  // 1068:     -> string("./" exe_filename)
  // 1069:   zz*
  // 1070:   
  // 1071:   #range(command_line_arguments 2 -1)*
  argument_count = 0;
  arguments = node_p;
  arguments->slots[argument_count++] = frame->slots[2] /* temp__1 */;
  unfold(frame->slots[1] /* zz */);
  result_count = frame->caller_result_count;
  myself = get__exec();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__88_2(void) {
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
  // 986: operating_system()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__operating_system();
  func = myself->type;
  frame->cont = cont__88_3;
}
static void cont__88_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__2 */ = arguments->slots[0];
  // 986: operating_system() == "cygwin"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__2 */;
  arguments->slots[1] = string__83_36;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__88_4;
}
static void cont__88_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 987: -> string(mod_filename ".exe")
  frame->slots[11] /* temp__3 */ = create_closure(entry__88_5, 0);
  // 988: -> mod_filename
  frame->slots[12] /* temp__4 */ = create_closure(entry__88_8, 0);
  // 984: $exe_filename
  // 985:   if
  // 986:     operating_system() == "cygwin"
  // 987:     -> string(mod_filename ".exe")
  // 988:     -> mod_filename
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = frame->slots[11] /* temp__3 */;
  arguments->slots[2] = frame->slots[12] /* temp__4 */;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__88_9;
}
static void entry__88_5(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // mod_filename: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* mod_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 987: ... string(mod_filename ".exe")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = string__88_6;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__88_7;
}
static void cont__88_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 987: -> string(mod_filename ".exe")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__88_8(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // mod_filename: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* mod_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 988: -> mod_filename
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__88_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* exe_filename */, arguments->slots[0]);
  // 990: ... : ewriteln "build executable " exe_filename
  frame->slots[9] /* temp__1 */ = create_closure(entry__88_10, 0);
  // 990: if verbose: ewriteln "build executable " exe_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__88_12;
}
static void entry__88_10(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // exe_filename: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* exe_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 990: ... ewriteln "build executable " exe_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__88_11;
  arguments->slots[1] = frame->slots[0] /* exe_filename */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__88_12(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 991: $c_filename string(mod_filename ".c")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = string__70_9;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__88_13;
}
static void cont__88_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* c_filename */, arguments->slots[0]);
  // 992: $o_filename string(mod_filename ".o")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = string__72_80;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__88_14;
}
static void cont__88_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* o_filename */, arguments->slots[0]);
  // 993: $sim_info stat(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__88_15;
}
static void cont__88_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* sim_info */, arguments->slots[0]);
  // 994: $c_info stat(c_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* c_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__88_16;
}
static void cont__88_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* c_info */, arguments->slots[0]);
  // 995: $$c_buf undefined
  ((CELL *)frame->slots[7])->contents /* c_buf */ = get__undefined();
  // 996: !objects(o_filename) true
  frame->slots[9] /* temp__1 */ = get__true();
  // 996: !objects(o_filename)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* o_filename */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = get__objects();
  func = myself->type;
  frame->cont = cont__88_17;
}
static void cont__88_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__objects(arguments->slots[0]);
  frame->slots[10] /* temp__2 */ = create_closure(entry__88_18, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_rebuild;
  arguments->slots[1] = frame->slots[10] /* temp__2 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__88_25;
}
static void entry__88_18(void) {
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
  // 1000: c_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__88_19;
}
static void cont__88_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 1001: modification_time_of(sim_info) > modification_time_of(c_info)
  frame->slots[4] /* temp__3 */ = create_closure(entry__88_20, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__88_24;
}
static void entry__88_20(void) {
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
  // 1001: ... modification_time_of(c_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__88_21;
}
static void cont__88_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 1001: modification_time_of(sim_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* sim_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__88_22;
}
static void cont__88_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 1001: modification_time_of(sim_info) > modification_time_of(c_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__88_23;
}
static void cont__88_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1001: modification_time_of(sim_info) > modification_time_of(c_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__88_24(void) {
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
static void cont__88_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 1002: :
  // 1003:   %sim2c::module_name mod_name .without_suffix. some(".meta")
  // 1004:   if verbose: ewriteln "build main module " module_name
  // 1005:   collect_output $c_source: sim2c list(main_filename) true
  // 1006:   collect_output !c_buf: create_imports c_source
  // 1007:   save c_filename c_buf.to_utf8
  // 1008:   if do_time_passes: write_timing_info "saving" c_filename
  // 1009:   compile_c c_filename o_filename
  // 1010:   if do_time_passes: write_timing_info "compiling" c_filename
  frame->slots[11] /* temp__3 */ = create_closure(entry__88_26, 0);
  // 1011: :
  // 1012:   load !c_buf c_filename
  // 1013:   $o_info stat(o_filename)
  // 1014:   if
  // 1015:     ||
  // 1016:       o_info.is_undefined
  // 1017:       modification_time_of(c_info) > modification_time_of(o_info)
  // 1018:     :
  // 1019:       compile_c c_filename o_filename
  // 1020:     :
  // ...
  frame->slots[12] /* temp__4 */ = create_closure(entry__88_46, 0);
  //  997: if
  //  998:   ||
  //  999:     do_rebuild
  // 1000:     c_info.is_undefined
  // 1001:     modification_time_of(sim_info) > modification_time_of(c_info)
  // 1002:   :
  // 1003:     %sim2c::module_name mod_name .without_suffix. some(".meta")
  // 1004:     if verbose: ewriteln "build main module " module_name
  // 1005:     collect_output $c_source: sim2c list(main_filename) true
  // 1006:     collect_output !c_buf: create_imports c_source
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = frame->slots[11] /* temp__3 */;
  arguments->slots[2] = frame->slots[12] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__88_58;
}
static void entry__88_55(void) {
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
  // 1019: compile_c c_filename o_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_filename */;
  arguments->slots[1] = frame->slots[1] /* o_filename */;
  result_count = frame->caller_result_count;
  myself = var._compile_c;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__88_56(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // o_info: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* o_info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1021: !last_modification_time modification_time_of(o_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* o_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__88_57;
}
static void cont__88_57(void) {
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
static void entry__88_26(void) {
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
  // 1003: ... some(".meta")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__66_16;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__88_27;
}
static void cont__88_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 1003: %sim2c::module_name mod_name .without_suffix. some(".meta")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* mod_name */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = get__without_suffix();
  func = myself->type;
  frame->cont = cont__88_28;
}
static void cont__88_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(get__sim2c__module_name(), arguments->slots[0]);
  // 1004: if verbose: ewriteln "build main module " module_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = func__88_29;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__88_31;
}
static void entry__88_29(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1004: ... ewriteln "build main module " module_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__88_30;
  arguments->slots[1] = get__module_name();
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__88_31(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1005: collect_output $c_source: sim2c list(main_filename) true
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__88_32;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__88_34;
}
static void entry__88_32(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1005: ... list(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__88_33;
}
static void cont__88_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1005: ... sim2c list(main_filename) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = get__true();
  result_count = frame->caller_result_count;
  myself = get__sim2c();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__88_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* c_source */, arguments->slots[0]);
  // 1006: ... : create_imports c_source
  frame->slots[6] /* temp__1 */ = create_closure(entry__88_35, 0);
  // 1006: collect_output !c_buf: create_imports c_source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__88_36;
}
static void entry__88_35(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // c_source: 0
  frame->slots[0] = myself->closure.frame->slots[5]; /* c_source */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1006: ... create_imports c_source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_source */;
  result_count = frame->caller_result_count;
  myself = var._create_imports;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__88_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* c_buf */ = arguments->slots[0];
  // 1007: ... c_buf.to_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* c_buf */;
  result_count = 1;
  myself = get__to_utf8();
  func = myself->type;
  frame->cont = cont__88_37;
}
static void cont__88_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 1007: save c_filename c_buf.to_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* c_filename */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 0;
  myself = get__save();
  func = myself->type;
  frame->cont = cont__88_38;
}
static void cont__88_38(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1008: ... : write_timing_info "saving" c_filename
  frame->slots[6] /* temp__1 */ = create_closure(entry__88_39, 0);
  // 1008: if do_time_passes: write_timing_info "saving" c_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__88_41;
}
static void entry__88_39(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // c_filename: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* c_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1008: ... write_timing_info "saving" c_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__88_40;
  arguments->slots[1] = frame->slots[0] /* c_filename */;
  result_count = frame->caller_result_count;
  myself = get__write_timing_info();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__88_41(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1009: compile_c c_filename o_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* c_filename */;
  arguments->slots[1] = frame->slots[4] /* o_filename */;
  result_count = 0;
  myself = var._compile_c;
  func = myself->type;
  frame->cont = cont__88_42;
}
static void cont__88_42(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1010: ... : write_timing_info "compiling" c_filename
  frame->slots[6] /* temp__1 */ = create_closure(entry__88_43, 0);
  // 1010: if do_time_passes: write_timing_info "compiling" c_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__88_45;
}
static void entry__88_43(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // c_filename: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* c_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1010: ... write_timing_info "compiling" c_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__88_44;
  arguments->slots[1] = frame->slots[0] /* c_filename */;
  result_count = frame->caller_result_count;
  myself = get__write_timing_info();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__88_45(void) {
  myself = frame->slots[0] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__88_46(void) {
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
  // 1012: load !c_buf c_filename
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* c_filename */;
  result_count = 1;
  myself = get__load();
  func = myself->type;
  frame->cont = cont__88_47;
}
static void cont__88_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* c_buf */ = arguments->slots[0];
  // 1013: $o_info stat(o_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* o_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__88_48;
}
static void cont__88_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* o_info */, arguments->slots[0]);
  // 1016: o_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* o_info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__88_49;
}
static void cont__88_49(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 1017: modification_time_of(c_info) > modification_time_of(o_info)
  frame->slots[7] /* temp__3 */ = create_closure(entry__88_50, 0);
  // 1015: ||
  // 1016:   o_info.is_undefined
  // 1017:   modification_time_of(c_info) > modification_time_of(o_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__88_54;
}
static void entry__88_50(void) {
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
  // 1017: ... modification_time_of(o_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* o_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__88_51;
}
static void cont__88_51(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 1017: modification_time_of(c_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* c_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__88_52;
}
static void cont__88_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 1017: modification_time_of(c_info) > modification_time_of(o_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__88_53;
}
static void cont__88_53(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1017: modification_time_of(c_info) > modification_time_of(o_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__88_54(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 1018: :
  // 1019:   compile_c c_filename o_filename
  frame->slots[8] /* temp__4 */ = create_closure(entry__88_55, 0);
  // 1020: :
  // 1021:   !last_modification_time modification_time_of(o_info)
  frame->slots[9] /* temp__5 */ = create_closure(entry__88_56, 0);
  // 1014: if
  // 1015:   ||
  // 1016:     o_info.is_undefined
  // 1017:     modification_time_of(c_info) > modification_time_of(o_info)
  // 1018:   :
  // 1019:     compile_c c_filename o_filename
  // 1020:   :
  // 1021:     !last_modification_time modification_time_of(o_info)
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
static void cont__88_58(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1022: build_dependencies mod_filename mod_name c_buf
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = frame->slots[1] /* mod_name */;
  arguments->slots[2] = ((CELL *)frame->slots[7])->contents /* c_buf */;
  result_count = 0;
  myself = var._build_dependencies;
  func = myself->type;
  frame->cont = cont__88_59;
}
static void cont__88_59(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1023: if do_build_static_executable:
  // 1024:   for_each
  // 1025:     "runtime/linker", "runtime/memory", "runtime/debugger": (filename)
  // 1026:       maybe_compile_c_file filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_build_static_executable();
  arguments->slots[1] = func__88_60;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__88_66;
}
static void entry__88_65(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // filename: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 1026: maybe_compile_c_file filename
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  result_count = frame->caller_result_count;
  myself = var._maybe_compile_c_file;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__88_60(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1025: "runtime/linker", "runtime/memory", "runtime/debugger"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__88_61;
  arguments->slots[1] = string__88_62;
  arguments->slots[2] = string__88_63;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__88_64;
}
static void cont__88_64(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1024: for_each
  // 1025:   "runtime/linker", "runtime/memory", "runtime/debugger": (filename)
  // 1026:     maybe_compile_c_file filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__88_65;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__88_66(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1027: ... :
  // 1028:   $info stat(exe_filename)
  // 1029:   if
  // 1030:     ||
  // 1031:       info.is_undefined
  // 1032:       &&
  // 1033:         last_modification_time.is_defined
  // 1034:         last_modification_time > modification_time_of(info)
  // 1035:     :
  // 1036:       !do_link true
  frame->slots[9] /* temp__1 */ = create_closure(entry__88_67, 0);
  // 1027: unless do_link:
  // 1028:   $info stat(exe_filename)
  // 1029:   if
  // 1030:     ||
  // 1031:       info.is_undefined
  // 1032:       &&
  // 1033:         last_modification_time.is_defined
  // 1034:         last_modification_time > modification_time_of(info)
  // 1035:     :
  // 1036:       !do_link true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_link();
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__88_78;
}
static void entry__88_77(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1036: !do_link true
  set__do_link(get__true());
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__88_67(void) {
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
  // 1028: $info stat(exe_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* exe_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__88_68;
}
static void cont__88_68(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* info */, arguments->slots[0]);
  // 1031: info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__88_69;
}
static void cont__88_69(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 1032: &&
  // 1033:   last_modification_time.is_defined
  // 1034:   last_modification_time > modification_time_of(info)
  frame->slots[4] /* temp__3 */ = create_closure(entry__88_70, 0);
  // 1030: ||
  // 1031:   info.is_undefined
  // 1032:   &&
  // 1033:     last_modification_time.is_defined
  // 1034:     last_modification_time > modification_time_of(info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__88_76;
}
static void entry__88_70(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // info: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1033: last_modification_time.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__last_modification_time();
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__88_71;
}
static void cont__88_71(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 1034: last_modification_time > modification_time_of(info)
  frame->slots[3] /* temp__3 */ = create_closure(entry__88_72, 0);
  // 1032: &&
  // 1033:   last_modification_time.is_defined
  // 1034:   last_modification_time > modification_time_of(info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__88_75;
}
static void entry__88_72(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // info: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1034: ... modification_time_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__88_73;
}
static void cont__88_73(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 1034: last_modification_time > modification_time_of(info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = get__last_modification_time();
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__88_74;
}
static void cont__88_74(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1034: last_modification_time > modification_time_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__88_75(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1032: &&
  // 1033:   last_modification_time.is_defined
  // 1034:   last_modification_time > modification_time_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__88_76(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1029: if
  // 1030:   ||
  // 1031:     info.is_undefined
  // 1032:     &&
  // 1033:       last_modification_time.is_defined
  // 1034:       last_modification_time > modification_time_of(info)
  // 1035:   :
  // 1036:     !do_link true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = func__88_77;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__88_78(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1037: ... :
  // 1038:   $$libs_and_files library_paths_and_file_list()
  // 1039:   if do_link_profiler: push &libs_and_files "/usr/lib/libprofiler.so.0"
  // 1040:   if
  // 1041:     do_build_static_executable:
  // 1042:       if verbose: ewriteln "linking static executable"
  // 1043:       Gcc $_out $err $success
  // 1044:         "runtime/linker.o"
  // 1045:         "runtime/memory.o"
  // 1046:         "runtime/debugger.o"
  // ...
  frame->slots[9] /* temp__1 */ = create_closure(entry__88_79, 0);
  // 1037: if do_link:
  // 1038:   $$libs_and_files library_paths_and_file_list()
  // 1039:   if do_link_profiler: push &libs_and_files "/usr/lib/libprofiler.so.0"
  // 1040:   if
  // 1041:     do_build_static_executable:
  // 1042:       if verbose: ewriteln "linking static executable"
  // 1043:       Gcc $_out $err $success
  // 1044:         "runtime/linker.o"
  // 1045:         "runtime/memory.o"
  // 1046:         "runtime/debugger.o"
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_link();
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__88_110;
}
static void entry__88_108(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // err: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* err */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1061: ... err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* err */;
  result_count = 1;
  myself = get__from_utf8();
  func = myself->type;
  frame->cont = cont__88_109;
}
static void cont__88_109(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1061: ... Error err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__88_93(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // err: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* err */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1050: ... err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* err */;
  result_count = 1;
  myself = get__from_utf8();
  func = myself->type;
  frame->cont = cont__88_94;
}
static void cont__88_94(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1050: ... Error err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__88_85(void) {
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
  // 1042: if verbose: ewriteln "linking static executable"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = func__88_86;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__88_88;
}
static void entry__88_86(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1042: ... ewriteln "linking static executable"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__88_87;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__88_88(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1043: Gcc $_out $err $success
  // 1044:   "runtime/linker.o"
  // 1045:   "runtime/memory.o"
  // 1046:   "runtime/debugger.o"
  // 1047:   libs_and_files*
  // 1048:   "-o"
  // 1049:   exe_filename
  argument_count = 0;
  arguments = node_p;
  arguments->slots[argument_count++] = string__88_89;
  arguments->slots[argument_count++] = string__88_90;
  arguments->slots[argument_count++] = string__88_91;
  unfold(((CELL *)frame->slots[0])->contents /* libs_and_files */);
  arguments->slots[argument_count++] = string__69_6;
  arguments->slots[argument_count++] = frame->slots[1] /* exe_filename */;
  result_count = 3;
  myself = var._Gcc;
  func = myself->type;
  frame->cont = cont__88_92;
}
static void cont__88_92(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  frame->slots[6] /* temp__2 */ = arguments->slots[1];
  frame->slots[7] /* temp__3 */ = arguments->slots[2];
  // 1043: ... _out
  initialize_future(frame->slots[2] /* out */, frame->slots[5] /* temp__1 */);
  // 1043: ... err
  initialize_future(frame->slots[3] /* err */, frame->slots[6] /* temp__2 */);
  // 1043: ... success
  initialize_future(frame->slots[4] /* success */, frame->slots[7] /* temp__3 */);
  // 1050: ... : Error err.from_utf8
  frame->slots[5] /* temp__1 */ = create_closure(entry__88_93, 0);
  // 1050: unless success: Error err.from_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* success */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__88_95(void) {
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
  // 1052: if verbose: ewriteln "linking executable"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = func__88_96;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__88_98;
}
static void entry__88_96(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1052: ... ewriteln "linking executable"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__88_97;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__88_98(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1056: operating_system()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__operating_system();
  func = myself->type;
  frame->cont = cont__88_99;
}
static void cont__88_99(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__3 */ = arguments->slots[0];
  // 1056: operating_system() == "linux"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__3 */;
  arguments->slots[1] = string__76_23;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__88_100;
}
static void cont__88_100(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 1055: if
  // 1056:   operating_system() == "linux"
  // 1057:   -> "-l:libsim.so.@(MAJOR)"
  // 1058:   -> "-lsim-@(MAJOR)"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = func__88_101;
  arguments->slots[2] = func__88_104;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__88_106;
}
static void entry__88_101(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1057: ... "-l:libsim.so.@(MAJOR)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__88_102;
  arguments->slots[1] = var._MAJOR;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__88_103;
}
static void cont__88_103(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1057: -> "-l:libsim.so.@(MAJOR)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__88_104(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1058: ... "-lsim-@(MAJOR)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__83_69;
  arguments->slots[1] = var._MAJOR;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__88_105;
}
static void cont__88_105(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1058: -> "-lsim-@(MAJOR)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__88_106(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 1053: Gcc $_out $err $success
  // 1054:   libs_and_files*
  // 1055:   if
  // 1056:     operating_system() == "linux"
  // 1057:     -> "-l:libsim.so.@(MAJOR)"
  // 1058:     -> "-lsim-@(MAJOR)"
  // 1059:   "-o"
  // 1060:   exe_filename
  argument_count = 0;
  arguments = node_p;
  unfold(((CELL *)frame->slots[0])->contents /* libs_and_files */);
  arguments->slots[argument_count++] = frame->slots[5] /* temp__1 */;
  arguments->slots[argument_count++] = string__69_6;
  arguments->slots[argument_count++] = frame->slots[1] /* exe_filename */;
  result_count = 3;
  myself = var._Gcc;
  func = myself->type;
  frame->cont = cont__88_107;
}
static void cont__88_107(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__4 */ = arguments->slots[0];
  frame->slots[9] /* temp__5 */ = arguments->slots[1];
  frame->slots[10] /* temp__6 */ = arguments->slots[2];
  // 1053: ... _out
  initialize_future(frame->slots[2] /* out */, frame->slots[8] /* temp__4 */);
  // 1053: ... err
  initialize_future(frame->slots[3] /* err */, frame->slots[9] /* temp__5 */);
  // 1053: ... success
  initialize_future(frame->slots[4] /* success */, frame->slots[10] /* temp__6 */);
  // 1061: ... : Error err.from_utf8
  frame->slots[5] /* temp__1 */ = create_closure(entry__88_108, 0);
  // 1061: unless success: Error err.from_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* success */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__88_79(void) {
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
  // 1038: $$libs_and_files library_paths_and_file_list()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = var._library_paths_and_file_list;
  func = myself->type;
  frame->cont = cont__88_80;
}
static void cont__88_80(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* libs_and_files */ = arguments->slots[0];
  // 1039: ... : push &libs_and_files "/usr/lib/libprofiler.so.0"
  frame->slots[2] /* temp__1 */ = create_closure(entry__88_81, 0);
  // 1039: if do_link_profiler: push &libs_and_files "/usr/lib/libprofiler.so.0"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_link_profiler;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__88_84;
}
static void entry__88_81(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // libs_and_files: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* libs_and_files */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1039: ... push &libs_and_files "/usr/lib/libprofiler.so.0"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* libs_and_files */;
  arguments->slots[1] = string__88_82;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__88_83;
}
static void cont__88_83(void) {
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
static void cont__88_84(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1041: ... :
  // 1042:   if verbose: ewriteln "linking static executable"
  // 1043:   Gcc $_out $err $success
  // 1044:     "runtime/linker.o"
  // 1045:     "runtime/memory.o"
  // 1046:     "runtime/debugger.o"
  // 1047:     libs_and_files*
  // 1048:     "-o"
  // 1049:     exe_filename
  // 1050:   unless success: Error err.from_utf8
  frame->slots[2] /* temp__1 */ = create_closure(entry__88_85, 0);
  // 1051: :
  // 1052:   if verbose: ewriteln "linking executable"
  // 1053:   Gcc $_out $err $success
  // 1054:     libs_and_files*
  // 1055:     if
  // 1056:       operating_system() == "linux"
  // 1057:       -> "-l:libsim.so.@(MAJOR)"
  // 1058:       -> "-lsim-@(MAJOR)"
  // 1059:     "-o"
  // 1060:     exe_filename
  // ...
  frame->slots[3] /* temp__2 */ = create_closure(entry__88_95, 0);
  // 1040: if
  // 1041:   do_build_static_executable:
  // 1042:     if verbose: ewriteln "linking static executable"
  // 1043:     Gcc $_out $err $success
  // 1044:       "runtime/linker.o"
  // 1045:       "runtime/memory.o"
  // 1046:       "runtime/debugger.o"
  // 1047:       libs_and_files*
  // 1048:       "-o"
  // 1049:       exe_filename
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
static void cont__88_110(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1062: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__88_111;
}
static void cont__88_111(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 1062: $zz range(command_line_arguments 2 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__command_line_arguments();
  arguments->slots[1] = number__2;
  arguments->slots[2] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__88_112;
}
static void cont__88_112(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[8] /* zz */, arguments->slots[0]);
  // 1063: ... on_top_level && action == "simrun"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__on_top_level();
  arguments->slots[1] = func__88_113;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__88_115;
}
static void entry__88_113(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1063: ... action == "simrun"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._action;
  arguments->slots[1] = string__83_2;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__88_114;
}
static void cont__88_114(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1063: ... action == "simrun"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__88_115(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 1063: ... :
  // 1064:   exec
  // 1065:     if
  // 1066:       exe_filename .has_prefix. '/'
  // 1067:       -> exe_filename
  // 1068:       -> string("./" exe_filename)
  // 1069:     zz*
  // 1070:     
  // 1071:     #range(command_line_arguments 2 -1)*
  frame->slots[10] /* temp__2 */ = create_closure(entry__88_116, 0);
  // 1063: if on_top_level && action == "simrun":
  // 1064:   exec
  // 1065:     if
  // 1066:       exe_filename .has_prefix. '/'
  // 1067:       -> exe_filename
  // 1068:       -> string("./" exe_filename)
  // 1069:     zz*
  // 1070:     
  // 1071:     #range(command_line_arguments 2 -1)*
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__88_1_build_executable(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 983: compile_exe: (mod_filename mod_name)
  // 984:   $exe_filename
  // 985:     if
  // 986:       operating_system() == "cygwin"
  // 987:       -> string(mod_filename ".exe")
  // 988:       -> mod_filename
  // 989:   
  // 990:   if verbose: ewriteln "build executable " exe_filename
  // 991:   $c_filename string(mod_filename ".c")
  // 992:   $o_filename string(mod_filename ".o")
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__88_2;
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
  var._gcc = collect_node(var._gcc);
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
  var._gcc_basic_options = collect_node(var._gcc_basic_options);
  var._gcc_hardware_specific_options = collect_node(var._gcc_hardware_specific_options);
  var._gcc_include_options = collect_node(var._gcc_include_options);
  var._gcc_options = collect_node(var._gcc_options);
  var._c_sources = collect_node(var._c_sources);
  var._dependencies = collect_node(var._dependencies);
  var._resolved_libraries = collect_node(var._resolved_libraries);
  var._resolve_filename = collect_node(var._resolve_filename);
  var._add_module_infos = collect_node(var._add_module_infos);
  var._lookup = collect_node(var._lookup);
  var._Gcc = collect_node(var._Gcc);
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
  func__65_8 = create_function(entry__65_8, 1);
  func__65_4 = create_function(entry__65_4, 1);
  func__65_3 = create_function(entry__65_3, 0);
  string__65_21 = from_latin_1_string("Cannot resolve required library \042", 33);
  string__65_22 = from_latin_1_string("\042!", 2);
  func__65_1_resolve_filename = create_function(entry__65_1_resolve_filename, 1);
  string__66_13 = from_latin_1_string(".sim", 4);
  string__66_16 = from_latin_1_string(".meta", 5);
  string__66_42 = from_latin_1_string("-common", 7);
  string__66_46 = from_latin_1_string("-", 1);
  string__66_58 = from_latin_1_string("The platform \042", 14);
  string__66_59 = from_latin_1_string("\042 is not supported!", 19);
  func__66_1_add_module_infos = create_function(entry__66_1_add_module_infos, 2);
  func__67_1_lookup = create_function(entry__67_1_lookup, 2);
  string__68_4 = from_latin_1_string("gcc ", 4);
  func__68_1_Gcc = create_function(entry__68_1_Gcc, -1);
  func__69_2 = create_function(entry__69_2, 0);
  string__69_5 = from_latin_1_string("-c", 2);
  string__69_6 = from_latin_1_string("-o", 2);
  string__69_10 = from_latin_1_string("Failed to compile ", 18);
  string__69_11 = from_latin_1_string("\012", 1);
  func__69_1_compile_c = create_function(entry__69_1_compile_c, 2);
  string__70_9 = from_latin_1_string(".c", 2);
  string__70_46 = from_latin_1_string("/// ", 4);
  string__70_53 = from_latin_1_string("data", 4);
  string__70_56 = from_latin_1_string("./", 2);
  func__70_1_compile_meta_module = create_function(entry__70_1_compile_meta_module, 3);
  func__71_24 = create_function(entry__71_24, 0);
  func__71_23 = create_function(entry__71_23, 0);
  string__71_32 = from_latin_1_string("sim-", 4);
  string__71_39 = from_latin_1_string("require", 7);
  string__71_40 = from_latin_1_string("link", 4);
  func__71_1_build_dependencies = create_function(entry__71_1_build_dependencies, -1);
  func__72_9 = create_function(entry__72_9, 0);
  string__72_38 = from_latin_1_string("__", 2);
  string__72_43 = from_latin_1_string("build module ", 13);
  string__72_76 = from_latin_1_string("No source file(s) for module \042", 30);
  string__72_77 = from_latin_1_string("\042 found!", 8);
  string__72_80 = from_latin_1_string(".o", 2);
  string__72_131 = from_latin_1_string(" #", 2);
  func__72_1_compile_module = create_function(entry__72_1_compile_module, 2);
  func__73_1_compile_modules = create_function(entry__73_1_compile_modules, 2);
  string__75_3 = from_latin_1_string("LD_LIBRARY_PATH", 15);
  string__75_7 = from_latin_1_string("LD_LIBRARY_PATH=", 16);
  string__75_11 = from_latin_1_string("included object files: ", 23);
  string__75_14 = from_latin_1_string("needed libraries: ", 18);
  func__75_2 = create_function(entry__75_2, 0);
  func__75_1_show_file_list = create_function(entry__75_1_show_file_list, 0);
  string__76_8 = from_latin_1_string("-L", 2);
  string__76_14 = from_latin_1_string("library paths: ", 15);
  string__76_23 = from_latin_1_string("linux", 5);
  string__76_26 = from_latin_1_string("-l:lib", 6);
  string__76_27 = from_latin_1_string(".so.", 4);
  string__76_30 = from_latin_1_string("-l", 2);
  func__76_1_library_paths_and_file_list = create_function(entry__76_1_library_paths_and_file_list, 0);
  string__77_26 = from_latin_1_string("typedef", 7);
  string__77_30 = from_latin_1_string("REGISTER", 8);
  string__77_44 = from_latin_1_string("typedef struct", 14);
  string__77_55 = from_latin_1_string("IMPORT ", 7);
  func__77_54 = create_function(entry__77_54, 0);
  string__77_65 = from_latin_1_string("// INSERT HERE //", 17);
  string__77_75 = from_latin_1_string("collecting imports", 18);
  func__77_74 = create_function(entry__77_74, 0);
  func__77_1_create_imports = create_function(entry__77_1_create_imports, 1);
  string__78_4 = from_latin_1_string("Expected a source code file!", 28);
  func__78_3 = create_function(entry__78_3, 0);
  string__78_8 = from_latin_1_string("Expected \042.sim\042 file extension in source filename!", 50);
  func__78_7 = create_function(entry__78_7, 0);
  func__78_1_compile_exe = create_function(entry__78_1_compile_exe, 1);
  func__79_2 = create_function(entry__79_2, 2);
  func__79_1_dump_source_or_check = create_function(entry__79_1_dump_source_or_check, 0);
  string__80_19 = from_latin_1_string("writing C-source", 16);
  func__80_18 = create_function(entry__80_18, 0);
  func__80_2 = create_function(entry__80_2, 2);
  func__80_1_print_c = create_function(entry__80_1_print_c, 0);
  func__81_3 = create_function(entry__81_3, 2);
  string__81_18 = from_latin_1_string("list dependencies for ", 22);
  func__81_17 = create_function(entry__81_17, 0);
  func__81_16 = create_function(entry__81_16, 0);
  func__81_24 = create_function(entry__81_24, 2);
  string__81_28 = from_latin_1_string("runtime/linker.c", 16);
  string__81_30 = from_latin_1_string("runtime/memory.c", 16);
  string__81_32 = from_latin_1_string("runtime/debugger.c", 18);
  func__81_23 = create_function(entry__81_23, 0);
  func__81_1_list_dependencies = create_function(entry__81_1_list_dependencies, 0);
  string__82_3 = from_latin_1_string(".codeblocks", 11);
  string__82_8 = from_latin_1_string("The directory \042", 15);
  string__82_9 = from_latin_1_string("\042 already exists!\012", 18);
  string__82_13 = from_latin_1_string("build Code::Blocks project in ", 30);
  string__82_23 = from_latin_1_string("../", 3);
  string__82_25 = from_latin_1_string("/", 1);
  string__82_26 = from_latin_1_string(".cbp", 4);
  string__82_29 = from_latin_1_string("<?xml version=\0421.0\042 encoding=\042UTF-8\042 standalone=\042yes\042 ?>\012<CodeBlocks_project_file>\012  <FileVersion major=\0421\042 minor=\0426\042 />\012  <Project>\012    <Option title=\042", 152);
  string__82_30 = from_latin_1_string("\042 />\012    <Option pch_mode=\0422\042 />\012    <Option compiler=\042gcc\042 />\012    <Build>\012      <Target title=\042debug\042>\012        <Option output=\042bin/debug/", 138);
  string__82_31 = from_latin_1_string("\042 prefix_auto=\0421\042 extension_auto=\0421\042 />\012        <Option object_output=\042obj/debug/\042 />\012        <Option type=\0421\042 />\012        <Option compiler=\042gcc\042 />\012        <Compiler>\012          <Add option=\042-g\042 />\012        </Compiler>\012      </Target>\012    </Build>\012    <Linker>\012", 259);
  string__82_35 = from_latin_1_string("      <Add library=\042", 20);
  string__82_36 = from_latin_1_string("\042 />\012", 5);
  string__82_40 = from_latin_1_string("\012    </Linker>\012    <Compiler>\012      <Add option=\042-Wall\042 />\012    </Compiler>\012    <Unit filename=\042", 95);
  string__82_41 = from_latin_1_string("runtime/common.h\042 />\012    <Unit filename=\042", 41);
  string__82_42 = from_latin_1_string("runtime/linker.h\042 />\012    <Unit filename=\042", 41);
  string__82_43 = from_latin_1_string("runtime/memory.c\042>\012      <Option compilerVar=\042CC\042 />\012    </Unit>\012    <Unit filename=\042", 85);
  string__82_44 = from_latin_1_string("runtime/debugger.c\042>\012      <Option compilerVar=\042CC\042 />\012    </Unit>\012    <Unit filename=\042", 87);
  string__82_45 = from_latin_1_string("runtime/linker.c\042>\012      <Option compilerVar=\042CC\042 />\012    </Unit>\012", 65);
  string__82_51 = from_latin_1_string("\012    <Unit filename=\042", 21);
  string__82_52 = from_latin_1_string("\042>\012      <Option compilerVar=\042CC\042 />\012    </Unit>\012", 49);
  string__82_56 = from_latin_1_string("    <Extensions>\012      <code_completion />\012      <debugger />\012    </Extensions>\012  </Project>\012</CodeBlocks_project_file>\012", 120);
  func__82_2 = create_function(entry__82_2, 2);
  func__82_1_build_codeblocks_project = create_function(entry__82_1_build_codeblocks_project, 0);
  string__83_2 = from_latin_1_string("simrun", 6);
  string__83_5 = from_latin_1_string("Cannot run a directory!", 23);
  func__83_4 = create_function(entry__83_4, 0);
  func__83_7 = create_function(entry__83_7, 0);
  string__83_9 = from_latin_1_string("/VERSION", 8);
  string__83_23 = from_latin_1_string("libsim-", 7);
  string__83_26 = from_latin_1_string(".dll", 4);
  string__83_30 = from_latin_1_string(".dylib", 6);
  string__83_34 = from_latin_1_string(".so", 3);
  string__83_36 = from_latin_1_string("cygwin", 6);
  string__83_37 = from_latin_1_string("darwin", 6);
  string__83_40 = from_latin_1_string("build library ", 14);
  func__83_52 = create_function(entry__83_52, 0);
  string__83_56 = from_latin_1_string("linking dynamic library", 23);
  func__83_55 = create_function(entry__83_55, 0);
  string__83_60 = from_latin_1_string("-Wl,-soname,libsim-", 19);
  string__83_63 = from_latin_1_string("-shared", 7);
  string__83_69 = from_latin_1_string("-lsim-", 6);
  string__83_75 = from_latin_1_string("-Wl,-install_name,libsim-", 25);
  string__83_79 = from_latin_1_string("-dynamiclib", 11);
  func__83_8 = create_function(entry__83_8, 0);
  func__83_1_build_library = create_function(entry__83_1_build_library, 0);
  string__84_7 = from_latin_1_string("\042", 1);
  string__84_8 = from_latin_1_string("\042 does not exist!\012", 18);
  string__84_20 = from_latin_1_string("compiling runtime module ", 25);
  func__84_1_maybe_compile_c_file = create_function(entry__84_1_maybe_compile_c_file, 1);
  string__86_14 = from_latin_1_string(" ", 1);
  string__86_23 = from_latin_1_string("0", 1);
  func__86_1_format_number = create_function(entry__86_1_format_number, -1);
  string__87_12 = from_latin_1_string(" s", 2);
  string__87_16 = from_latin_1_string(": ", 2);
  func__87_1_sim2c__write_timing_info = create_function(entry__87_1_sim2c__write_timing_info, -1);
  string__88_6 = from_latin_1_string(".exe", 4);
  string__88_11 = from_latin_1_string("build executable ", 17);
  string__88_30 = from_latin_1_string("build main module ", 18);
  func__88_29 = create_function(entry__88_29, 0);
  func__88_32 = create_function(entry__88_32, 0);
  string__88_40 = from_latin_1_string("saving", 6);
  string__88_44 = from_latin_1_string("compiling", 9);
  string__88_61 = from_latin_1_string("runtime/linker", 14);
  string__88_62 = from_latin_1_string("runtime/memory", 14);
  string__88_63 = from_latin_1_string("runtime/debugger", 16);
  func__88_65 = create_function(entry__88_65, 1);
  func__88_60 = create_function(entry__88_60, 0);
  func__88_77 = create_function(entry__88_77, 0);
  string__88_82 = from_latin_1_string("/usr/lib/libprofiler.so.0", 25);
  string__88_87 = from_latin_1_string("linking static executable", 25);
  func__88_86 = create_function(entry__88_86, 0);
  string__88_89 = from_latin_1_string("runtime/linker.o", 16);
  string__88_90 = from_latin_1_string("runtime/memory.o", 16);
  string__88_91 = from_latin_1_string("runtime/debugger.o", 18);
  string__88_97 = from_latin_1_string("linking executable", 18);
  func__88_96 = create_function(entry__88_96, 0);
  string__88_102 = from_latin_1_string("-l:libsim.so.", 13);
  func__88_101 = create_function(entry__88_101, 0);
  func__88_104 = create_function(entry__88_104, 0);
  func__88_113 = create_function(entry__88_113, 0);
  func__88_2 = create_function(entry__88_2, 2);
  func__88_1_build_executable = create_function(entry__88_1_build_executable, 0);
  string__92_1 = from_latin_1_string("Copyright (C) 2020 by\012Dipl.-Ing. Michael Niederle\012\012This program is free software; you can redistribute it and/or modify\012it under the terms of the GNU General Public License, version 2, or\012(at your option) version 3.\012\012This program is distributed in the hope that it will be useful,\012but WITHOUT ANY WARRANTY; without even the implied warranty of\012MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the\012GNU General Public License for more details.\012\012For details of the GNU General Public License see the accompanying\012files GPLv2.txt and GLPv3.txt or\012http://www.gnu.org/licenses/gpl-2.0.html\012http://www.gnu.org/licenses/gpl-3.0.html\012or write to the\012Free Software Foundation, Inc.,\01251 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.\012", 742);
  string__97_1 = from_latin_1_string(".", 1);
  string__99_1 = from_latin_1_string("gcc", 3);
  string__100_1 = from_latin_1_string("mkdir", 5);
  string__101_1 = from_latin_1_string("SIMLIBPATH", 10);
  string__102_1 = from_latin_1_string("SIMDATAPATH", 11);
  func__103_2 = create_function(entry__103_2, 0);
  string__103_5 = from_latin_1_string("/usr/local/share/simplicity-", 28);
  string__103_7 = from_latin_1_string("/usr/share/simplicity-", 22);
  func__103_4 = create_function(entry__103_4, 0);
  func__104_2 = create_function(entry__104_2, 0);
  func__104_4 = create_function(entry__104_4, 0);
  string__106_1 = from_latin_1_string("bsd", 3);
  string__106_2 = from_latin_1_string("posix", 5);
  string__106_7 = from_latin_1_string("all", 3);
  string__106_9 = from_latin_1_string("win", 3);
  func__108_1 = create_function(entry__108_1, 0);
  string__133_5 = from_latin_1_string("Missing command line arguments!", 31);
  func__133_4 = create_function(entry__133_4, 0);
  func__133_2 = create_function(entry__133_2, 0);
  string__133_10 = from_latin_1_string("check-only", 10);
  string__133_11 = from_latin_1_string("do not compile; just check for syntax errors\012", 45);
  func__133_9 = create_function(entry__133_9, 0);
  string__133_13 = from_latin_1_string("dump-trees", 10);
  string__133_14 = from_latin_1_string("dump abstract syntax trees\012", 27);
  func__133_12 = create_function(entry__133_12, 0);
  string__133_16 = from_latin_1_string("pretty-print", 12);
  string__133_17 = from_latin_1_string("do not compile; just pretty print the source file\012", 50);
  func__133_15 = create_function(entry__133_15, 0);
  string__133_19 = from_latin_1_string("print-simplified-source", 23);
  string__133_20 = from_latin_1_string("do not generate a C-file; just print the simplified source text\012", 64);
  func__133_18 = create_function(entry__133_18, 0);
  string__133_22 = from_latin_1_string("print-c", 7);
  string__133_23 = from_latin_1_string("print C source code for a single module\012", 40);
  func__133_21 = create_function(entry__133_21, 0);
  string__133_25 = from_latin_1_string("time-passes", 11);
  string__133_26 = from_latin_1_string("print running time for the individual compiler passes\012", 54);
  func__133_24 = create_function(entry__133_24, 0);
  string__133_28 = from_latin_1_string("module-prefix", 13);
  string__133_29 = from_latin_1_string("needed to compile a single file within a subdirectory;\012if the subdirectories are nested use slashes to separate\012the directory names\012", 132);
  func__133_27 = create_function(entry__133_27, 0);
  string__133_31 = from_latin_1_string("brief", 5);
  string__133_32 = from_latin_1_string("show brief error messages\012", 26);
  func__133_30 = create_function(entry__133_30, 0);
  string__133_34 = from_latin_1_string("warnings", 8);
  string__133_35 = from_latin_1_string("show warning messages\012", 22);
  func__133_33 = create_function(entry__133_33, 0);
  string__133_37 = from_latin_1_string("verbose", 7);
  string__133_38 = from_latin_1_string("output verbose informations\012", 28);
  func__133_36 = create_function(entry__133_36, 0);
  string__133_40 = from_latin_1_string("debug", 5);
  string__133_41 = from_latin_1_string("show C-compiler and linker calls\012", 33);
  func__133_39 = create_function(entry__133_39, 0);
  string__133_43 = from_latin_1_string("debug_compiler", 14);
  string__133_44 = from_latin_1_string("show internal debug messages of the Simplicity compiler\012", 56);
  func__133_42 = create_function(entry__133_42, 0);
  string__133_46 = from_latin_1_string("codeblocks", 10);
  string__133_47 = from_latin_1_string("create Code::Blocks project\012", 28);
  func__133_45 = create_function(entry__133_45, 0);
  string__133_49 = from_latin_1_string("extract-documentation", 21);
  string__133_50 = from_latin_1_string("extract documentation encoded as HTML\012", 38);
  func__133_48 = create_function(entry__133_48, 0);
  string__133_52 = from_latin_1_string("list-dependencies", 17);
  string__133_53 = from_latin_1_string("list all dependencies\012", 22);
  func__133_51 = create_function(entry__133_51, 0);
  string__133_55 = from_latin_1_string("rebuild", 7);
  string__133_56 = from_latin_1_string("rebuild all source files\012", 25);
  func__133_54 = create_function(entry__133_54, 0);
  string__133_58 = from_latin_1_string("omit-meta", 9);
  string__133_59 = from_latin_1_string("do not rebuild meta files\012", 26);
  func__133_57 = create_function(entry__133_57, 0);
  string__133_61 = from_latin_1_string("static", 6);
  string__133_62 = from_latin_1_string("create statically linked executable\012", 36);
  func__133_60 = create_function(entry__133_60, 0);
  string__133_64 = from_latin_1_string("profile", 7);
  string__133_65 = from_latin_1_string("link with libprofiler\012", 22);
  func__133_63 = create_function(entry__133_63, 0);
  string__133_67 = from_latin_1_string("filename", 8);
  string__133_68 = from_latin_1_string("the name of the source file to compile\012", 39);
  func__133_66 = create_function(entry__133_66, 0);
  func__133_8 = create_function(entry__133_8, 0);
  func__137_1 = create_function(entry__137_1, 0);
  string__143_1 = from_latin_1_string("-Wall", 5);
  string__143_2 = from_latin_1_string("-Wno-unused-function", 20);
  string__143_3 = from_latin_1_string("-Wno-unused-variable", 20);
  string__143_4 = from_latin_1_string("-Wno-parentheses", 16);
  string__143_5 = from_latin_1_string("-Wno-switch", 11);
  string__143_6 = from_latin_1_string("-Wno-maybe-uninitialized", 24);
  string__143_7 = from_latin_1_string("-Wno-trigraphs", 14);
  string__143_8 = from_latin_1_string("-O1", 3);
  string__143_9 = from_latin_1_string("-fPIC", 5);
  string__143_10 = from_latin_1_string("-fno-stack-protector", 20);
  string__143_11 = from_latin_1_string("-falign-functions=16", 20);
  string__144_1 = from_latin_1_string("-msse2", 6);
  string__144_2 = from_latin_1_string("-mfpmath=sse", 12);
  string__144_4 = from_latin_1_string("x86_32", 6);
  string__144_7 = from_latin_1_string("x86_64", 6);
  string__146_2 = from_latin_1_string("-I", 2);
  func__146_1 = create_function(entry__146_1, 1);
  string__165_3 = from_latin_1_string("Source file \042", 13);
  string__165_4 = from_latin_1_string("\042 does not exist!", 17);
  func__165_2 = create_function(entry__165_2, 0);
  func__180_1 = create_function(entry__180_1, 0);
  func__181_4 = create_function(entry__181_4, 0);
  func__181_3 = create_function(entry__181_3, 0);
  func__181_2 = create_function(entry__181_2, 0);
  func__181_1 = create_function(entry__181_1, 0);
  func__181_8 = create_function(entry__181_8, 0);
  func__181_9 = create_function(entry__181_9, 0);
  func__181_10 = create_function(entry__181_10, 0);
  func__181_11 = create_function(entry__181_11, 0);

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
  var._gcc = create_future();
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
  var._gcc_basic_options = create_future();
  var._gcc_hardware_specific_options = create_future();
  var._gcc_options = create_future();
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
  assign_variable(&var._resolve_filename, &func__65_1_resolve_filename);
  assign_variable(&var._add_module_infos, &func__66_1_add_module_infos);
  assign_variable(&var._lookup, &func__67_1_lookup);
  assign_variable(&var._Gcc, &func__68_1_Gcc);
  assign_variable(&var._compile_c, &func__69_1_compile_c);
  assign_variable(&var._compile_meta_module, &func__70_1_compile_meta_module);
  assign_variable(&var._build_dependencies, &func__71_1_build_dependencies);
  assign_variable(&var._compile_module, &func__72_1_compile_module);
  assign_variable(&var._compile_modules, &func__73_1_compile_modules);
  assign_variable(&var._show_file_list, &func__75_1_show_file_list);
  assign_variable(&var._library_paths_and_file_list, &func__76_1_library_paths_and_file_list);
  assign_variable(&var._create_imports, &func__77_1_create_imports);
  assign_variable(&var._compile_exe, &func__78_1_compile_exe);
  assign_variable(&var._dump_source_or_check, &func__79_1_dump_source_or_check);
  assign_variable(&var._print_c, &func__80_1_print_c);
  assign_variable(&var._list_dependencies, &func__81_1_list_dependencies);
  assign_variable(&var._build_codeblocks_project, &func__82_1_build_codeblocks_project);
  assign_variable(&var._build_library, &func__83_1_build_library);
  assign_variable(&var._maybe_compile_c_file, &func__84_1_maybe_compile_c_file);
  assign_variable(&var._format_number, &func__86_1_format_number);
  assign_variable(&var.sim2c__write_timing_info, &func__87_1_sim2c__write_timing_info);
  assign_variable(&var._build_executable, &func__88_1_build_executable);
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
