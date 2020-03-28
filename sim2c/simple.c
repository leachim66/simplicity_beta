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
/// require platform/platform
/// require platform/hardware_architecture
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
static NODE_GETTER get__current_platform;
static NODE_GETTER get_value_or_future__current_platform;
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
static NODE *func__63_1_resolve_filename;
static void entry__63_1_resolve_filename(void);
static FRAME_INFO frame__63_1_resolve_filename = {3, {"filename", "libname", "libpath"}};
static void cont__63_2(void);
static NODE *func__63_3;
static void entry__63_3(void);
static FRAME_INFO frame__63_3 = {0, {}};
static NODE *func__63_4;
static void entry__63_4(void);
static FRAME_INFO frame__63_4 = {1, {"path"}};
static void cont__63_5(void);
static NODE *func__63_6;
static void entry__63_6(void);
static FRAME_INFO frame__63_6 = {1, {"path"}};
static void cont__63_7(void);
static NODE *func__63_8;
static void entry__63_8(void);
static FRAME_INFO frame__63_8 = {1, {"entry"}};
static void cont__63_9(void);
static NODE *func__63_10;
static void entry__63_10(void);
static FRAME_INFO frame__63_10 = {2, {"entry", "name"}};
static void cont__63_11(void);
static void cont__63_12(void);
static NODE *func__63_13;
static void entry__63_13(void);
static FRAME_INFO frame__63_13 = {2, {"name", "entry"}};
static void cont__63_14(void);
static void cont__63_15(void);
static void cont__63_16(void);
static void cont__63_17(void);
static void cont__63_18(void);
static void cont__63_19(void);
static NODE *func__63_20;
static void entry__63_20(void);
static FRAME_INFO frame__63_20 = {1, {"libname"}};
static NODE *string__63_21;
static NODE *string__63_22;
static void cont__63_23(void);
static void cont__63_24(void);
static void cont__63_25(void);
static void cont__63_26(void);
static NODE *func__64_1_add_module_infos;
static void entry__64_1_add_module_infos(void);
static FRAME_INFO frame__64_1_add_module_infos = {7, {"path", "mod_path", "return", "entries", "filenames", "directories", "modules"}};
static void cont__64_2(void);
static void cont__64_3(void);
static NODE *func__64_4;
static void entry__64_4(void);
static FRAME_INFO frame__64_4 = {6, {"entry", "directories", "filenames", "modules", "mod_path", "name"}};
static void cont__64_5(void);
static NODE *func__64_6;
static void entry__64_6(void);
static FRAME_INFO frame__64_6 = {3, {"entry", "name", "directories"}};
static void cont__64_7(void);
static NODE *func__64_8;
static void entry__64_8(void);
static FRAME_INFO frame__64_8 = {2, {"name", "directories"}};
static void cont__64_9(void);
static NODE *func__64_10;
static void entry__64_10(void);
static FRAME_INFO frame__64_10 = {2, {"directories", "name"}};
static void cont__64_11(void);
static NODE *func__64_12;
static void entry__64_12(void);
static FRAME_INFO frame__64_12 = {4, {"name", "filenames", "modules", "mod_path"}};
static NODE *string__64_13;
static void cont__64_14(void);
static NODE *func__64_15;
static void entry__64_15(void);
static FRAME_INFO frame__64_15 = {9, {"name", "filenames", "modules", "mod_path", "submodule_name", "meta_level", "stored_level", "basename", "mod_name"}};
static NODE *string__64_16;
static void cont__64_17(void);
static void cont__64_18(void);
static void cont__64_19(void);
static void cont__64_20(void);
static void cont__64_21(void);
static void cont__64_22(void);
static void cont__64_23(void);
static void cont__64_24(void);
static void cont__64_25(void);
static void cont__64_26(void);
static void cont__64_27(void);
static NODE *func__64_28;
static void entry__64_28(void);
static FRAME_INFO frame__64_28 = {2, {"stored_level", "meta_level"}};
static void cont__64_29(void);
static void cont__64_30(void);
static NODE *func__64_31;
static void entry__64_31(void);
static FRAME_INFO frame__64_31 = {2, {"submodule_name", "meta_level"}};
static void cont__64_32(void);
static void cont__64_33(void);
static void cont__64_34(void);
static void cont__64_35(void);
static void cont__64_36(void);
static void cont__64_37(void);
static void cont__64_38(void);
static NODE *func__64_39;
static void entry__64_39(void);
static FRAME_INFO frame__64_39 = {3, {"filename", "filenames", "mod_path"}};
static void cont__64_40(void);
static NODE *func__64_41;
static void entry__64_41(void);
static FRAME_INFO frame__64_41 = {3, {"filename", "filenames", "mod_path"}};
static NODE *string__64_42;
static void cont__64_43(void);
static NODE *func__64_44;
static void entry__64_44(void);
static FRAME_INFO frame__64_44 = {9, {"filenames", "filename", "mod_path", "maybe_push_common", "name", "mod_name", "platform", "parent", "files"}};
static NODE *func__64_45_maybe_push_common;
static void entry__64_45_maybe_push_common(void);
static FRAME_INFO frame__64_45_maybe_push_common = {5, {"plat", "name", "filenames", "files", "common_name"}};
static NODE *string__64_46;
static void cont__64_47(void);
static void cont__64_48(void);
static NODE *func__64_49;
static void entry__64_49(void);
static FRAME_INFO frame__64_49 = {2, {"files", "common_name"}};
static void cont__64_50(void);
static void cont__64_51(void);
static void cont__64_52(void);
static void cont__64_53(void);
static void cont__64_54(void);
static void cont__64_55(void);
static void cont__64_56(void);
static NODE *func__64_57;
static void entry__64_57(void);
static FRAME_INFO frame__64_57 = {1, {"platform"}};
static NODE *string__64_58;
static NODE *string__64_59;
static void cont__64_60(void);
static void cont__64_61(void);
static void cont__64_62(void);
static void cont__64_63(void);
static NODE *func__64_64;
static void entry__64_64(void);
static FRAME_INFO frame__64_64 = {2, {"parent", "maybe_push_common"}};
static void cont__64_65(void);
static void cont__64_66(void);
static NODE *func__64_67;
static void entry__64_67(void);
static FRAME_INFO frame__64_67 = {2, {"maybe_push_common", "parent"}};
static void cont__64_68(void);
static void cont__64_69(void);
static void cont__64_70(void);
static void cont__64_71(void);
static void cont__64_72(void);
static void cont__64_73(void);
static void cont__64_74(void);
static void cont__64_75(void);
static void cont__64_76(void);
static NODE *func__64_77;
static void entry__64_77(void);
static FRAME_INFO frame__64_77 = {3, {"return", "directories", "modules"}};
static void cont__64_78(void);
static NODE *func__65_1_lookup;
static void entry__65_1_lookup(void);
static FRAME_INFO frame__65_1_lookup = {3, {"mod_filename", "mod_name", "info"}};
static void cont__65_2(void);
static void cont__65_3(void);
static NODE *func__65_4;
static void entry__65_4(void);
static FRAME_INFO frame__65_4 = {1, {"info"}};
static NODE *func__65_5;
static void entry__65_5(void);
static FRAME_INFO frame__65_5 = {2, {"mod_filename", "mod_name"}};
static void cont__65_6(void);
static void cont__65_7(void);
static void cont__65_8(void);
static void cont__65_9(void);
static void cont__65_10(void);
static void cont__65_11(void);
static NODE *func__66_1_Gcc;
static void entry__66_1_Gcc(void);
static FRAME_INFO frame__66_1_Gcc = {1, {"args"}};
static NODE *func__66_2;
static void entry__66_2(void);
static FRAME_INFO frame__66_2 = {1, {"args"}};
static void cont__66_3(void);
static NODE *string__66_4;
static void cont__66_5(void);
static NODE *func__67_1_compile_c;
static void entry__67_1_compile_c(void);
static FRAME_INFO frame__67_1_compile_c = {2, {"c_filename", "o_filename"}};
static NODE *func__67_2;
static void entry__67_2(void);
static FRAME_INFO frame__67_2 = {0, {}};
static void cont__67_3(void);
static NODE *func__67_4;
static void entry__67_4(void);
static FRAME_INFO frame__67_4 = {5, {"c_filename", "o_filename", "out", "err", "success"}};
static NODE *string__67_5;
static NODE *string__67_6;
static void cont__67_7(void);
static NODE *func__67_8;
static void entry__67_8(void);
static FRAME_INFO frame__67_8 = {2, {"c_filename", "err"}};
static void cont__67_9(void);
static NODE *string__67_10;
static NODE *string__67_11;
static void cont__67_12(void);
static void cont__67_13(void);
static NODE *func__68_1_compile_meta_module;
static void entry__68_1_compile_meta_module(void);
static FRAME_INFO frame__68_1_compile_meta_module = {3, {"mod_filename", "mod_name", "meta_level"}};
static NODE *func__68_2;
static void entry__68_2(void);
static FRAME_INFO frame__68_2 = {11, {"mod_filename", "meta_level", "meta_path", "filename", "meta_filename", "meta_c_filename", "sim_filename", "meta_info", "sim_info", "meta_c_info", "force_rebuild"}};
static void cont__68_3(void);
static void cont__68_4(void);
static void cont__68_5(void);
static void cont__68_6(void);
static void cont__68_7(void);
static void cont__68_8(void);
static NODE *string__68_9;
static void cont__68_10(void);
static void cont__68_11(void);
static void cont__68_12(void);
static void cont__68_13(void);
static void cont__68_14(void);
static void cont__68_15(void);
static void cont__68_16(void);
static NODE *func__68_17;
static void entry__68_17(void);
static FRAME_INFO frame__68_17 = {3, {"sim_info", "meta_c_info", "meta_info"}};
static void cont__68_18(void);
static NODE *func__68_19;
static void entry__68_19(void);
static FRAME_INFO frame__68_19 = {3, {"meta_c_info", "meta_info", "sim_info"}};
static void cont__68_20(void);
static NODE *func__68_21;
static void entry__68_21(void);
static FRAME_INFO frame__68_21 = {3, {"meta_c_info", "meta_info", "sim_info"}};
static void cont__68_22(void);
static void cont__68_23(void);
static void cont__68_24(void);
static NODE *func__68_25;
static void entry__68_25(void);
static FRAME_INFO frame__68_25 = {2, {"sim_info", "meta_c_info"}};
static void cont__68_26(void);
static void cont__68_27(void);
static void cont__68_28(void);
static void cont__68_29(void);
static void cont__68_30(void);
static void cont__68_31(void);
static void cont__68_32(void);
static NODE *func__68_33;
static void entry__68_33(void);
static FRAME_INFO frame__68_33 = {6, {"sim_info", "meta_c_filename", "force_rebuild", "meta_path", "modification_time", "meta_c_buf"}};
static void cont__68_34(void);
static void cont__68_35(void);
static NODE *func__68_36;
static void entry__68_36(void);
static FRAME_INFO frame__68_36 = {5, {"break", "meta_c_buf", "modification_time", "force_rebuild", "meta_path"}};
static NODE *func__68_37;
static void entry__68_37(void);
static FRAME_INFO frame__68_37 = {8, {"line", "modification_time", "force_rebuild", "break", "meta_path", "check", "command", "argument"}};
static NODE *func__68_38_check;
static void entry__68_38_check(void);
static FRAME_INFO frame__68_38_check = {5, {"data_filename", "modification_time", "force_rebuild", "break", "data_info"}};
static void cont__68_39(void);
static void cont__68_40(void);
static NODE *func__68_41;
static void entry__68_41(void);
static FRAME_INFO frame__68_41 = {2, {"modification_time", "data_info"}};
static void cont__68_42(void);
static void cont__68_43(void);
static void cont__68_44(void);
static NODE *func__68_45;
static void entry__68_45(void);
static FRAME_INFO frame__68_45 = {2, {"force_rebuild", "break"}};
static NODE *string__68_46;
static void cont__68_47(void);
static void cont__68_48(void);
static void cont__68_49(void);
static void cont__68_50(void);
static void cont__68_51(void);
static void cont__68_52(void);
static NODE *string__68_53;
static void cont__68_54(void);
static NODE *func__68_55;
static void entry__68_55(void);
static FRAME_INFO frame__68_55 = {3, {"argument", "check", "meta_path"}};
static NODE *string__68_56;
static void cont__68_57(void);
static NODE *func__68_58;
static void entry__68_58(void);
static FRAME_INFO frame__68_58 = {3, {"check", "meta_path", "argument"}};
static void cont__68_59(void);
static void cont__68_60(void);
static void cont__68_61(void);
static NODE *func__68_62;
static void entry__68_62(void);
static FRAME_INFO frame__68_62 = {2, {"check", "argument"}};
static NODE *func__68_63;
static void entry__68_63(void);
static FRAME_INFO frame__68_63 = {3, {"path", "check", "argument"}};
static void cont__68_64(void);
static void cont__68_65(void);
static void cont__68_66(void);
static NODE *func__68_67;
static void entry__68_67(void);
static FRAME_INFO frame__68_67 = {9, {"return__1", "meta_filename", "meta_path", "filename", "sim_filename", "orig_path", "out", "err", "success"}};
static void cont__68_68(void);
static void cont__68_69(void);
static void cont__68_70(void);
static void cont__68_71(void);
static void cont__68_72(void);
static void cont__68_73(void);
static NODE *func__68_74;
static void entry__68_74(void);
static FRAME_INFO frame__68_74 = {1, {"err"}};
static void cont__68_75(void);
static void cont__68_76(void);
static void cont__68_77(void);
static void cont__68_78(void);
static void cont__68_79(void);
static void cont__68_80(void);
static void cont__68_81(void);
static NODE *func__69_1_build_dependencies;
static void entry__69_1_build_dependencies(void);
static FRAME_INFO frame__69_1_build_dependencies = {5, {"mod_filename", "mod_name", "c_buf", "do_compile_c", "return"}};
static NODE *func__69_2;
static void entry__69_2(void);
static FRAME_INFO frame__69_2 = {7, {"line", "return", "mod_filename", "mod_name", "do_compile_c", "command", "argument"}};
static void cont__69_3(void);
static void cont__69_4(void);
static void cont__69_5(void);
static void cont__69_6(void);
static void cont__69_7(void);
static void cont__69_8(void);
static NODE *func__69_9;
static void entry__69_9(void);
static FRAME_INFO frame__69_9 = {4, {"argument", "mod_filename", "mod_name", "do_compile_c"}};
static void cont__69_10(void);
static NODE *func__69_11;
static void entry__69_11(void);
static FRAME_INFO frame__69_11 = {3, {"argument", "mod_filename", "mod_name"}};
static void cont__69_12(void);
static NODE *func__69_13;
static void entry__69_13(void);
static FRAME_INFO frame__69_13 = {4, {"argument", "mod_filename", "mod_name", "req_name"}};
static void cont__69_14(void);
static void cont__69_15(void);
static void cont__69_16(void);
static void cont__69_17(void);
static void cont__69_18(void);
static void cont__69_19(void);
static void cont__69_20(void);
static void cont__69_21(void);
static NODE *func__69_22;
static void entry__69_22(void);
static FRAME_INFO frame__69_22 = {2, {"argument", "do_compile_c"}};
static NODE *func__69_23;
static void entry__69_23(void);
static FRAME_INFO frame__69_23 = {0, {}};
static NODE *func__69_24;
static void entry__69_24(void);
static FRAME_INFO frame__69_24 = {0, {}};
static void cont__69_25(void);
static void cont__69_26(void);
static NODE *func__69_27;
static void entry__69_27(void);
static FRAME_INFO frame__69_27 = {1, {"argument"}};
static void cont__69_28(void);
static NODE *func__69_29;
static void entry__69_29(void);
static FRAME_INFO frame__69_29 = {2, {"do_compile_c", "argument"}};
static NODE *func__69_30;
static void entry__69_30(void);
static FRAME_INFO frame__69_30 = {1, {"argument"}};
static void cont__69_31(void);
static NODE *string__69_32;
static void cont__69_33(void);
static void cont__69_34(void);
static NODE *func__69_35;
static void entry__69_35(void);
static FRAME_INFO frame__69_35 = {2, {"do_compile_c", "argument"}};
static NODE *func__69_36;
static void entry__69_36(void);
static FRAME_INFO frame__69_36 = {1, {"argument"}};
static void cont__69_37(void);
static void cont__69_38(void);
static NODE *string__69_39;
static NODE *string__69_40;
static void cont__69_41(void);
static NODE *func__70_1_compile_module;
static void entry__70_1_compile_module(void);
static FRAME_INFO frame__70_1_compile_module = {6, {"mod_filename", "mod_name", "return", "compile_submodule", "mod_info", "o_filename"}};
static NODE *func__70_2_compile_submodule;
static void entry__70_2_compile_submodule(void);
static FRAME_INFO frame__70_2_compile_submodule = {11, {"submodule_names", "do_compile_c", "suffix", "mod_filename", "mod_name", "o_filename", "modification_time", "sim_filenames", "c_filename", "c_info", "c_buf"}};
static NODE *func__70_3;
static void entry__70_3(void);
static FRAME_INFO frame__70_3 = {8, {"submodule_name", "mod_filename", "sim_filenames", "modification_time", "meta_level", "submodule_filename", "sim_filename", "sim_info"}};
static void cont__70_4(void);
static void cont__70_5(void);
static void cont__70_6(void);
static void cont__70_7(void);
static void cont__70_8(void);
static NODE *func__70_9;
static void entry__70_9(void);
static FRAME_INFO frame__70_9 = {0, {}};
static void cont__70_10(void);
static void cont__70_11(void);
static NODE *func__70_12;
static void entry__70_12(void);
static FRAME_INFO frame__70_12 = {3, {"submodule_filename", "submodule_name", "meta_level"}};
static void cont__70_13(void);
static void cont__70_14(void);
static void cont__70_15(void);
static void cont__70_16(void);
static void cont__70_17(void);
static NODE *func__70_18;
static void entry__70_18(void);
static FRAME_INFO frame__70_18 = {2, {"modification_time", "sim_info"}};
static void cont__70_19(void);
static void cont__70_20(void);
static void cont__70_21(void);
static NODE *func__70_22;
static void entry__70_22(void);
static FRAME_INFO frame__70_22 = {2, {"modification_time", "sim_info"}};
static void cont__70_23(void);
static void cont__70_24(void);
static void cont__70_25(void);
static void cont__70_26(void);
static NODE *func__70_27;
static void entry__70_27(void);
static FRAME_INFO frame__70_27 = {1, {"c_filename"}};
static void cont__70_28(void);
static void cont__70_29(void);
static NODE *func__70_30;
static void entry__70_30(void);
static FRAME_INFO frame__70_30 = {2, {"c_info", "modification_time"}};
static void cont__70_31(void);
static NODE *func__70_32;
static void entry__70_32(void);
static FRAME_INFO frame__70_32 = {2, {"c_info", "modification_time"}};
static void cont__70_33(void);
static void cont__70_34(void);
static void cont__70_35(void);
static void cont__70_36(void);
static NODE *func__70_37;
static void entry__70_37(void);
static FRAME_INFO frame__70_37 = {9, {"return__1", "mod_name", "suffix", "sim_filenames", "c_buf", "c_filename", "do_compile_c", "o_filename", "c_source"}};
static NODE *string__70_38;
static void cont__70_39(void);
static void cont__70_40(void);
static void cont__70_41(void);
static NODE *func__70_42;
static void entry__70_42(void);
static FRAME_INFO frame__70_42 = {1, {"suffix"}};
static NODE *string__70_43;
static void cont__70_44(void);
static NODE *func__70_45;
static void entry__70_45(void);
static FRAME_INFO frame__70_45 = {1, {"sim_filenames"}};
static void cont__70_46(void);
static NODE *func__70_47;
static void entry__70_47(void);
static FRAME_INFO frame__70_47 = {1, {"c_source"}};
static void cont__70_48(void);
static void cont__70_49(void);
static void cont__70_50(void);
static NODE *func__70_51;
static void entry__70_51(void);
static FRAME_INFO frame__70_51 = {2, {"c_filename", "o_filename"}};
static void cont__70_52(void);
static NODE *func__70_53;
static void entry__70_53(void);
static FRAME_INFO frame__70_53 = {6, {"c_buf", "c_filename", "o_filename", "c_info", "do_compile_c", "o_info"}};
static void cont__70_54(void);
static void cont__70_55(void);
static void cont__70_56(void);
static NODE *func__70_57;
static void entry__70_57(void);
static FRAME_INFO frame__70_57 = {2, {"o_info", "c_info"}};
static void cont__70_58(void);
static void cont__70_59(void);
static void cont__70_60(void);
static void cont__70_61(void);
static NODE *func__70_62;
static void entry__70_62(void);
static FRAME_INFO frame__70_62 = {3, {"do_compile_c", "c_filename", "o_filename"}};
static NODE *func__70_63;
static void entry__70_63(void);
static FRAME_INFO frame__70_63 = {2, {"c_filename", "o_filename"}};
static NODE *func__70_64;
static void entry__70_64(void);
static FRAME_INFO frame__70_64 = {1, {"o_info"}};
static void cont__70_65(void);
static NODE *func__70_66;
static void entry__70_66(void);
static FRAME_INFO frame__70_66 = {1, {"o_info"}};
static void cont__70_67(void);
static void cont__70_68(void);
static void cont__70_69(void);
static NODE *func__70_70;
static void entry__70_70(void);
static FRAME_INFO frame__70_70 = {1, {"o_info"}};
static void cont__70_71(void);
static void cont__70_72(void);
static void cont__70_73(void);
static void cont__70_74(void);
static NODE *func__70_75;
static void entry__70_75(void);
static FRAME_INFO frame__70_75 = {1, {"mod_name"}};
static NODE *string__70_76;
static NODE *string__70_77;
static void cont__70_78(void);
static void cont__70_79(void);
static NODE *string__70_80;
static void cont__70_81(void);
static void cont__70_82(void);
static void cont__70_83(void);
static void cont__70_84(void);
static void cont__70_85(void);
static NODE *func__70_86;
static void entry__70_86(void);
static FRAME_INFO frame__70_86 = {3, {"compile_submodule", "mod_name", "mod_filename"}};
static void cont__70_87(void);
static void cont__70_88(void);
static void cont__70_89(void);
static void cont__70_90(void);
static NODE *func__70_91;
static void entry__70_91(void);
static FRAME_INFO frame__70_91 = {1, {"mod_filename"}};
static void cont__70_92(void);
static void cont__70_93(void);
static NODE *func__70_94;
static void entry__70_94(void);
static FRAME_INFO frame__70_94 = {3, {"mod_info", "compile_submodule", "mod_filename"}};
static NODE *func__70_95;
static void entry__70_95(void);
static FRAME_INFO frame__70_95 = {4, {"mod_info", "compile_submodule", "best_platform", "best_priority"}};
static NODE *func__70_96;
static void entry__70_96(void);
static FRAME_INFO frame__70_96 = {5, {"platform", "filenames", "best_priority", "best_platform", "priority"}};
static void cont__70_97(void);
static void cont__70_98(void);
static NODE *func__70_99;
static void entry__70_99(void);
static FRAME_INFO frame__70_99 = {2, {"priority", "best_priority"}};
static void cont__70_100(void);
static void cont__70_101(void);
static NODE *func__70_102;
static void entry__70_102(void);
static FRAME_INFO frame__70_102 = {4, {"best_platform", "platform", "best_priority", "priority"}};
static void cont__70_103(void);
static NODE *func__70_104;
static void entry__70_104(void);
static FRAME_INFO frame__70_104 = {4, {"platform", "filenames", "compile_submodule", "best_platform"}};
static void cont__70_105(void);
static void cont__70_106(void);
static void cont__70_107(void);
static NODE *func__70_108;
static void entry__70_108(void);
static FRAME_INFO frame__70_108 = {3, {"mod_info", "mod_filename", "used_by"}};
static NODE *func__70_109;
static void entry__70_109(void);
static FRAME_INFO frame__70_109 = {6, {"supported_platform", "parent_platform", "mod_info", "used_by", "best_platform", "best_priority"}};
static NODE *func__70_110;
static void entry__70_110(void);
static FRAME_INFO frame__70_110 = {6, {"platform", "filenames", "supported_platform", "best_priority", "best_platform", "priority"}};
static void cont__70_111(void);
static void cont__70_112(void);
static NODE *func__70_113;
static void entry__70_113(void);
static FRAME_INFO frame__70_113 = {2, {"priority", "best_priority"}};
static void cont__70_114(void);
static void cont__70_115(void);
static NODE *func__70_116;
static void entry__70_116(void);
static FRAME_INFO frame__70_116 = {4, {"best_platform", "platform", "best_priority", "priority"}};
static void cont__70_117(void);
static void cont__70_118(void);
static NODE *func__70_119;
static void entry__70_119(void);
static FRAME_INFO frame__70_119 = {4, {"used_by", "best_platform", "supported_platform", "ub"}};
static void cont__70_120(void);
static void cont__70_121(void);
static void cont__70_122(void);
static void cont__70_123(void);
static void cont__70_124(void);
static NODE *func__70_125;
static void entry__70_125(void);
static FRAME_INFO frame__70_125 = {6, {"platform", "filenames", "mod_filename", "used_by", "dependency", "platforms"}};
static void cont__70_126(void);
static void cont__70_127(void);
static void cont__70_128(void);
static NODE *func__70_129;
static void entry__70_129(void);
static FRAME_INFO frame__70_129 = {2, {"platforms", "dependency"}};
static NODE *func__70_130;
static void entry__70_130(void);
static FRAME_INFO frame__70_130 = {2, {"plat", "dependency"}};
static NODE *string__70_131;
static void cont__70_132(void);
static void cont__70_133(void);
static void cont__70_134(void);
static void cont__70_135(void);
static NODE *func__71_1_compile_modules;
static void entry__71_1_compile_modules(void);
static FRAME_INFO frame__71_1_compile_modules = {4, {"path", "mod_path", "directories", "modules"}};
static void cont__71_2(void);
static void cont__71_3(void);
static NODE *func__71_4;
static void entry__71_4(void);
static FRAME_INFO frame__71_4 = {3, {"name", "path", "mod_path"}};
static void cont__71_5(void);
static void cont__71_6(void);
static void cont__71_7(void);
static NODE *func__71_8;
static void entry__71_8(void);
static FRAME_INFO frame__71_8 = {3, {"name", "path", "mod_path"}};
static void cont__71_9(void);
static void cont__71_10(void);
static NODE *func__73_1_show_file_list;
static void entry__73_1_show_file_list(void);
static FRAME_INFO frame__73_1_show_file_list = {0, {}};
static NODE *func__73_2;
static void entry__73_2(void);
static FRAME_INFO frame__73_2 = {1, {"path"}};
static NODE *string__73_3;
static void cont__73_4(void);
static void cont__73_5(void);
static NODE *func__73_6;
static void entry__73_6(void);
static FRAME_INFO frame__73_6 = {1, {"path"}};
static NODE *string__73_7;
static void cont__73_8(void);
static void cont__73_9(void);
static void cont__73_10(void);
static NODE *string__73_11;
static void cont__73_12(void);
static void cont__73_13(void);
static NODE *string__73_14;
static NODE *func__74_1_library_paths_and_file_list;
static void entry__74_1_library_paths_and_file_list(void);
static FRAME_INFO frame__74_1_library_paths_and_file_list = {4, {"library_paths", "object_files", "library_files", "paths"}};
static void cont__74_2(void);
static void cont__74_3(void);
static void cont__74_4(void);
static NODE *func__74_5;
static void entry__74_5(void);
static FRAME_INFO frame__74_5 = {2, {"paths", "library_paths"}};
static void cont__74_6(void);
static NODE *func__74_7;
static void entry__74_7(void);
static FRAME_INFO frame__74_7 = {2, {"path", "library_paths"}};
static NODE *string__74_8;
static void cont__74_9(void);
static void cont__74_10(void);
static void cont__74_11(void);
static NODE *func__74_12;
static void entry__74_12(void);
static FRAME_INFO frame__74_12 = {1, {"library_paths"}};
static void cont__74_13(void);
static NODE *string__74_14;
static void cont__74_15(void);
static NODE *func__74_16;
static void entry__74_16(void);
static FRAME_INFO frame__74_16 = {2, {"object", "object_files"}};
static void cont__74_17(void);
static void cont__74_18(void);
static NODE *func__74_19;
static void entry__74_19(void);
static FRAME_INFO frame__74_19 = {2, {"library", "library_files"}};
static void cont__74_20(void);
static NODE *func__74_21;
static void entry__74_21(void);
static FRAME_INFO frame__74_21 = {1, {"library"}};
static NODE *string__74_22;
static void cont__74_23(void);
static NODE *func__74_24;
static void entry__74_24(void);
static FRAME_INFO frame__74_24 = {1, {"library"}};
static NODE *string__74_25;
static NODE *string__74_26;
static void cont__74_27(void);
static NODE *func__74_28;
static void entry__74_28(void);
static FRAME_INFO frame__74_28 = {1, {"library"}};
static NODE *string__74_29;
static void cont__74_30(void);
static void cont__74_31(void);
static NODE *func__74_32;
static void entry__74_32(void);
static FRAME_INFO frame__74_32 = {1, {"library"}};
static void cont__74_33(void);
static NODE *func__74_34;
static void entry__74_34(void);
static FRAME_INFO frame__74_34 = {1, {"library"}};
static void cont__74_35(void);
static void cont__74_36(void);
static void cont__74_37(void);
static NODE *func__74_38;
static void entry__74_38(void);
static FRAME_INFO frame__74_38 = {1, {"library"}};
static void cont__74_39(void);
static void cont__74_40(void);
static void cont__74_41(void);
static void cont__74_42(void);
static void cont__74_43(void);
static void cont__74_44(void);
static NODE *func__75_1_create_imports;
static void entry__75_1_create_imports(void);
static FRAME_INFO frame__75_1_create_imports = {5, {"source", "already_checked", "collect_declarations", "imports", "first_part"}};
static NODE *func__75_2_collect_declarations;
static void entry__75_2_collect_declarations(void);
static FRAME_INFO frame__75_2_collect_declarations = {4, {"buf", "already_checked", "collect_declarations", "s"}};
static NODE *func__75_3;
static void entry__75_3(void);
static FRAME_INFO frame__75_3 = {6, {"idx", "chr", "s", "buf", "already_checked", "collect_declarations"}};
static void cont__75_4(void);
static NODE *func__75_5;
static void entry__75_5(void);
static FRAME_INFO frame__75_5 = {6, {"chr", "buf", "s", "idx", "already_checked", "collect_declarations"}};
static void cont__75_6(void);
static NODE *func__75_7;
static void entry__75_7(void);
static FRAME_INFO frame__75_7 = {1, {"chr"}};
static void cont__75_8(void);
static NODE *func__75_9;
static void entry__75_9(void);
static FRAME_INFO frame__75_9 = {1, {"chr"}};
static void cont__75_10(void);
static void cont__75_11(void);
static void cont__75_12(void);
static NODE *func__75_13;
static void entry__75_13(void);
static FRAME_INFO frame__75_13 = {6, {"buf", "s", "idx", "already_checked", "collect_declarations", "symbol"}};
static void cont__75_14(void);
static void cont__75_15(void);
static void cont__75_16(void);
static NODE *func__75_17;
static void entry__75_17(void);
static FRAME_INFO frame__75_17 = {4, {"already_checked", "symbol", "collect_declarations", "declaration"}};
static void cont__75_18(void);
static void cont__75_19(void);
static void cont__75_20(void);
static NODE *func__75_21;
static void entry__75_21(void);
static FRAME_INFO frame__75_21 = {3, {"declaration", "collect_declarations", "do_import"}};
static void cont__75_22(void);
static void cont__75_23(void);
static void cont__75_24(void);
static NODE *func__75_25;
static void entry__75_25(void);
static FRAME_INFO frame__75_25 = {1, {"declaration"}};
static NODE *string__75_26;
static void cont__75_27(void);
static void cont__75_28(void);
static NODE *func__75_29;
static void entry__75_29(void);
static FRAME_INFO frame__75_29 = {1, {"declaration"}};
static NODE *string__75_30;
static void cont__75_31(void);
static void cont__75_32(void);
static void cont__75_33(void);
static void cont__75_34(void);
static NODE *func__75_35;
static void entry__75_35(void);
static FRAME_INFO frame__75_35 = {2, {"declaration", "collect_declarations"}};
static void cont__75_36(void);
static void cont__75_37(void);
static NODE *func__75_38;
static void entry__75_38(void);
static FRAME_INFO frame__75_38 = {1, {"declaration"}};
static void cont__75_39(void);
static void cont__75_40(void);
static NODE *func__75_41;
static void entry__75_41(void);
static FRAME_INFO frame__75_41 = {2, {"collect_declarations", "declaration"}};
static void cont__75_42(void);
static NODE *func__75_43;
static void entry__75_43(void);
static FRAME_INFO frame__75_43 = {2, {"declaration", "collect_declarations"}};
static NODE *string__75_44;
static void cont__75_45(void);
static NODE *func__75_46;
static void entry__75_46(void);
static FRAME_INFO frame__75_46 = {2, {"declaration", "collect_declarations"}};
static void cont__75_47(void);
static void cont__75_48(void);
static NODE *func__75_49;
static void entry__75_49(void);
static FRAME_INFO frame__75_49 = {2, {"line", "collect_declarations"}};
static void cont__75_50(void);
static void cont__75_51(void);
static NODE *func__75_52;
static void entry__75_52(void);
static FRAME_INFO frame__75_52 = {2, {"collect_declarations", "declaration"}};
static void cont__75_53(void);
static NODE *func__75_54;
static void entry__75_54(void);
static FRAME_INFO frame__75_54 = {0, {}};
static NODE *string__75_55;
static void cont__75_56(void);
static NODE *func__75_57;
static void entry__75_57(void);
static FRAME_INFO frame__75_57 = {3, {"chr", "s", "idx"}};
static void cont__75_58(void);
static NODE *func__75_59;
static void entry__75_59(void);
static FRAME_INFO frame__75_59 = {1, {"chr"}};
static void cont__75_60(void);
static void cont__75_61(void);
static NODE *func__75_62;
static void entry__75_62(void);
static FRAME_INFO frame__75_62 = {2, {"s", "idx"}};
static NODE *func__75_63;
static void entry__75_63(void);
static FRAME_INFO frame__75_63 = {2, {"collect_declarations", "source"}};
static void cont__75_64(void);
static NODE *string__75_65;
static void cont__75_66(void);
static void cont__75_67(void);
static void cont__75_68(void);
static void cont__75_69(void);
static void cont__75_70(void);
static void cont__75_71(void);
static void cont__75_72(void);
static void cont__75_73(void);
static NODE *func__75_74;
static void entry__75_74(void);
static FRAME_INFO frame__75_74 = {0, {}};
static NODE *string__75_75;
static NODE *func__76_1_compile_exe;
static void entry__76_1_compile_exe(void);
static FRAME_INFO frame__76_1_compile_exe = {4, {"body", "return__1", "mod_filename", "mod_name"}};
static void cont__76_2(void);
static NODE *func__76_3;
static void entry__76_3(void);
static FRAME_INFO frame__76_3 = {0, {}};
static NODE *string__76_4;
static void cont__76_5(void);
static void cont__76_6(void);
static NODE *func__76_7;
static void entry__76_7(void);
static FRAME_INFO frame__76_7 = {0, {}};
static NODE *string__76_8;
static void cont__76_9(void);
static void cont__76_10(void);
static void cont__76_11(void);
static void cont__76_12(void);
static void cont__76_13(void);
static NODE *func__77_1_dump_source_or_check;
static void entry__77_1_dump_source_or_check(void);
static FRAME_INFO frame__77_1_dump_source_or_check = {0, {}};
static NODE *func__77_2;
static void entry__77_2(void);
static FRAME_INFO frame__77_2 = {3, {"mod_filename", "mod_name", "return__1"}};
static void cont__77_3(void);
static void cont__77_4(void);
static NODE *func__78_1_print_c;
static void entry__78_1_print_c(void);
static FRAME_INFO frame__78_1_print_c = {0, {}};
static NODE *func__78_2;
static void entry__78_2(void);
static FRAME_INFO frame__78_2 = {4, {"mod_filename", "mod_name", "c_source", "c_buf"}};
static void cont__78_3(void);
static NODE *func__78_4;
static void entry__78_4(void);
static FRAME_INFO frame__78_4 = {1, {"mod_name"}};
static void cont__78_5(void);
static void cont__78_6(void);
static void cont__78_7(void);
static NODE *func__78_8;
static void entry__78_8(void);
static FRAME_INFO frame__78_8 = {2, {"return__1", "mod_name"}};
static void cont__78_9(void);
static void cont__78_10(void);
static void cont__78_11(void);
static void cont__78_12(void);
static void cont__78_13(void);
static void cont__78_14(void);
static NODE *func__78_15;
static void entry__78_15(void);
static FRAME_INFO frame__78_15 = {1, {"c_source"}};
static void cont__78_16(void);
static void cont__78_17(void);
static NODE *func__78_18;
static void entry__78_18(void);
static FRAME_INFO frame__78_18 = {0, {}};
static NODE *string__78_19;
static NODE *func__79_1_list_dependencies;
static void entry__79_1_list_dependencies(void);
static FRAME_INFO frame__79_1_list_dependencies = {1, {"prefix_path"}};
static void cont__79_2(void);
static NODE *func__79_3;
static void entry__79_3(void);
static FRAME_INFO frame__79_3 = {4, {"supported_platform", "parent_platform", "platform", "priority"}};
static NODE *func__79_4;
static void entry__79_4(void);
static FRAME_INFO frame__79_4 = {4, {"break", "platform", "priority", "supported_platform"}};
static NODE *func__79_5;
static void entry__79_5(void);
static FRAME_INFO frame__79_5 = {5, {"platform", "break", "priority", "supported_platform", "plat"}};
static void cont__79_6(void);
static void cont__79_7(void);
static void cont__79_8(void);
static void cont__79_9(void);
static void cont__79_10(void);
static void cont__79_11(void);
static void cont__79_12(void);
static void cont__79_13(void);
static void cont__79_14(void);
static void cont__79_15(void);
static NODE *func__79_16;
static void entry__79_16(void);
static FRAME_INFO frame__79_16 = {1, {"return__1"}};
static NODE *func__79_17;
static void entry__79_17(void);
static FRAME_INFO frame__79_17 = {0, {}};
static NODE *string__79_18;
static void cont__79_19(void);
static void cont__79_20(void);
static void cont__79_21(void);
static void cont__79_22(void);
static NODE *func__79_23;
static void entry__79_23(void);
static FRAME_INFO frame__79_23 = {0, {}};
static NODE *func__79_24;
static void entry__79_24(void);
static FRAME_INFO frame__79_24 = {2, {"mod_filename", "mod_name"}};
static NODE *func__79_25;
static void entry__79_25(void);
static FRAME_INFO frame__79_25 = {1, {"mod_filename"}};
static void cont__79_26(void);
static void cont__79_27(void);
static NODE *string__79_28;
static void cont__79_29(void);
static NODE *string__79_30;
static void cont__79_31(void);
static NODE *string__79_32;
static void cont__79_33(void);
static void cont__79_34(void);
static NODE *func__79_35;
static void entry__79_35(void);
static FRAME_INFO frame__79_35 = {2, {"filename", "prefix_path"}};
static void cont__79_36(void);
static void cont__79_37(void);
static NODE *func__80_1_build_codeblocks_project;
static void entry__80_1_build_codeblocks_project(void);
static FRAME_INFO frame__80_1_build_codeblocks_project = {0, {}};
static NODE *func__80_2;
static void entry__80_2(void);
static FRAME_INFO frame__80_2 = {10, {"mod_filename", "mod_name", "codeblocks_path", "info", "basename", "prefix_path", "depth", "path_prefix", "cbp_filename", "buf"}};
static NODE *string__80_3;
static void cont__80_4(void);
static void cont__80_5(void);
static void cont__80_6(void);
static NODE *func__80_7;
static void entry__80_7(void);
static FRAME_INFO frame__80_7 = {1, {"codeblocks_path"}};
static NODE *string__80_8;
static NODE *string__80_9;
static void cont__80_10(void);
static void cont__80_11(void);
static NODE *func__80_12;
static void entry__80_12(void);
static FRAME_INFO frame__80_12 = {1, {"codeblocks_path"}};
static NODE *string__80_13;
static void cont__80_14(void);
static void cont__80_15(void);
static void cont__80_16(void);
static void cont__80_17(void);
static void cont__80_18(void);
static void cont__80_19(void);
static void cont__80_20(void);
static void cont__80_21(void);
static void cont__80_22(void);
static NODE *string__80_23;
static void cont__80_24(void);
static NODE *string__80_25;
static NODE *string__80_26;
static void cont__80_27(void);
static void cont__80_28(void);
static NODE *string__80_29;
static NODE *string__80_30;
static NODE *string__80_31;
static void cont__80_32(void);
static void cont__80_33(void);
static NODE *func__80_34;
static void entry__80_34(void);
static FRAME_INFO frame__80_34 = {2, {"filename", "buf"}};
static NODE *string__80_35;
static NODE *string__80_36;
static void cont__80_37(void);
static void cont__80_38(void);
static void cont__80_39(void);
static NODE *string__80_40;
static NODE *string__80_41;
static NODE *string__80_42;
static NODE *string__80_43;
static NODE *string__80_44;
static NODE *string__80_45;
static void cont__80_46(void);
static void cont__80_47(void);
static NODE *func__80_48;
static void entry__80_48(void);
static FRAME_INFO frame__80_48 = {4, {"filename", "prefix_path", "buf", "path_prefix"}};
static void cont__80_49(void);
static void cont__80_50(void);
static NODE *string__80_51;
static NODE *string__80_52;
static void cont__80_53(void);
static void cont__80_54(void);
static void cont__80_55(void);
static NODE *string__80_56;
static void cont__80_57(void);
static NODE *func__81_1_build_library;
static void entry__81_1_build_library(void);
static FRAME_INFO frame__81_1_build_library = {1, {"return__1"}};
static NODE *string__81_2;
static void cont__81_3(void);
static NODE *func__81_4;
static void entry__81_4(void);
static FRAME_INFO frame__81_4 = {0, {}};
static NODE *string__81_5;
static void cont__81_6(void);
static NODE *func__81_7;
static void entry__81_7(void);
static FRAME_INFO frame__81_7 = {0, {}};
static NODE *func__81_8;
static void entry__81_8(void);
static FRAME_INFO frame__81_8 = {5, {"version", "so_version", "version_filename", "base_filename", "lib_filename"}};
static NODE *string__81_9;
static void cont__81_10(void);
static void cont__81_11(void);
static NODE *func__81_12;
static void entry__81_12(void);
static FRAME_INFO frame__81_12 = {3, {"version", "version_filename", "so_version"}};
static void cont__81_13(void);
static void cont__81_14(void);
static void cont__81_15(void);
static void cont__81_16(void);
static void cont__81_17(void);
static void cont__81_18(void);
static void cont__81_19(void);
static NODE *func__81_20;
static void entry__81_20(void);
static FRAME_INFO frame__81_20 = {2, {"base_filename", "version"}};
static void cont__81_21(void);
static NODE *string__81_22;
static void cont__81_23(void);
static NODE *func__81_24;
static void entry__81_24(void);
static FRAME_INFO frame__81_24 = {2, {"base_filename", "version"}};
static NODE *string__81_25;
static void cont__81_26(void);
static void cont__81_27(void);
static NODE *func__81_28;
static void entry__81_28(void);
static FRAME_INFO frame__81_28 = {2, {"base_filename", "version"}};
static NODE *string__81_29;
static void cont__81_30(void);
static void cont__81_31(void);
static NODE *func__81_32;
static void entry__81_32(void);
static FRAME_INFO frame__81_32 = {1, {"base_filename"}};
static NODE *string__81_33;
static void cont__81_34(void);
static NODE *string__81_35;
static NODE *string__81_36;
static void cont__81_37(void);
static NODE *func__81_38;
static void entry__81_38(void);
static FRAME_INFO frame__81_38 = {1, {"lib_filename"}};
static NODE *string__81_39;
static void cont__81_40(void);
static void cont__81_41(void);
static void cont__81_42(void);
static void cont__81_43(void);
static NODE *func__81_44;
static void entry__81_44(void);
static FRAME_INFO frame__81_44 = {2, {"lib_filename", "info"}};
static void cont__81_45(void);
static void cont__81_46(void);
static NODE *func__81_47;
static void entry__81_47(void);
static FRAME_INFO frame__81_47 = {1, {"info"}};
static void cont__81_48(void);
static void cont__81_49(void);
static void cont__81_50(void);
static NODE *func__81_51;
static void entry__81_51(void);
static FRAME_INFO frame__81_51 = {0, {}};
static void cont__81_52(void);
static NODE *func__81_53;
static void entry__81_53(void);
static FRAME_INFO frame__81_53 = {3, {"base_filename", "so_version", "lib_filename"}};
static NODE *func__81_54;
static void entry__81_54(void);
static FRAME_INFO frame__81_54 = {0, {}};
static NODE *string__81_55;
static void cont__81_56(void);
static NODE *func__81_57;
static void entry__81_57(void);
static FRAME_INFO frame__81_57 = {6, {"base_filename", "so_version", "lib_filename", "out", "err", "success"}};
static NODE *string__81_58;
static void cont__81_59(void);
static void cont__81_60(void);
static NODE *string__81_61;
static void cont__81_62(void);
static NODE *func__81_63;
static void entry__81_63(void);
static FRAME_INFO frame__81_63 = {1, {"err"}};
static void cont__81_64(void);
static NODE *func__81_65;
static void entry__81_65(void);
static FRAME_INFO frame__81_65 = {4, {"lib_filename", "out", "err", "success"}};
static void cont__81_66(void);
static NODE *string__81_67;
static void cont__81_68(void);
static void cont__81_69(void);
static NODE *func__81_70;
static void entry__81_70(void);
static FRAME_INFO frame__81_70 = {1, {"err"}};
static void cont__81_71(void);
static NODE *func__81_72;
static void entry__81_72(void);
static FRAME_INFO frame__81_72 = {6, {"base_filename", "so_version", "lib_filename", "out", "err", "success"}};
static NODE *string__81_73;
static void cont__81_74(void);
static void cont__81_75(void);
static void cont__81_76(void);
static NODE *string__81_77;
static void cont__81_78(void);
static NODE *func__81_79;
static void entry__81_79(void);
static FRAME_INFO frame__81_79 = {1, {"err"}};
static void cont__81_80(void);
static NODE *func__81_81;
static void entry__81_81(void);
static FRAME_INFO frame__81_81 = {4, {"lib_filename", "out", "err", "success"}};
static void cont__81_82(void);
static void cont__81_83(void);
static NODE *func__81_84;
static void entry__81_84(void);
static FRAME_INFO frame__81_84 = {1, {"err"}};
static void cont__81_85(void);
static void cont__81_86(void);
static NODE *func__82_1_maybe_compile_c_file;
static void entry__82_1_maybe_compile_c_file(void);
static FRAME_INFO frame__82_1_maybe_compile_c_file = {5, {"filename", "c_filename", "o_filename", "c_info", "o_info"}};
static void cont__82_2(void);
static void cont__82_3(void);
static void cont__82_4(void);
static void cont__82_5(void);
static NODE *func__82_6;
static void entry__82_6(void);
static FRAME_INFO frame__82_6 = {1, {"c_filename"}};
static NODE *string__82_7;
static NODE *string__82_8;
static void cont__82_9(void);
static void cont__82_10(void);
static void cont__82_11(void);
static void cont__82_12(void);
static NODE *func__82_13;
static void entry__82_13(void);
static FRAME_INFO frame__82_13 = {2, {"o_info", "c_info"}};
static void cont__82_14(void);
static void cont__82_15(void);
static void cont__82_16(void);
static void cont__82_17(void);
static NODE *func__82_18;
static void entry__82_18(void);
static FRAME_INFO frame__82_18 = {3, {"filename", "c_filename", "o_filename"}};
static NODE *func__82_19;
static void entry__82_19(void);
static FRAME_INFO frame__82_19 = {1, {"filename"}};
static NODE *string__82_20;
static void cont__82_21(void);
static void cont__82_22(void);
static NODE *func__84_1_format_number;
static void entry__84_1_format_number(void);
static FRAME_INFO frame__84_1_format_number = {4, {"val", "n", "m", "ac"}};
static void cont__84_2(void);
static NODE *func__84_3;
static void entry__84_3(void);
static FRAME_INFO frame__84_3 = {4, {"break", "val", "ac", "n"}};
static NODE *func__84_4;
static void entry__84_4(void);
static FRAME_INFO frame__84_4 = {6, {"i", "chr", "ac", "val", "n", "break"}};
static void cont__84_5(void);
static NODE *func__84_6;
static void entry__84_6(void);
static FRAME_INFO frame__84_6 = {5, {"ac", "val", "i", "n", "break"}};
static void cont__84_7(void);
static void cont__84_8(void);
static void cont__84_9(void);
static void cont__84_10(void);
static NODE *func__84_11;
static void entry__84_11(void);
static FRAME_INFO frame__84_11 = {3, {"val", "n", "i"}};
static void cont__84_12(void);
static void cont__84_13(void);
static NODE *string__84_14;
static void cont__84_15(void);
static void cont__84_16(void);
static void cont__84_17(void);
static void cont__84_18(void);
static void cont__84_19(void);
static void cont__84_20(void);
static NODE *func__84_21;
static void entry__84_21(void);
static FRAME_INFO frame__84_21 = {3, {"val", "m", "ac"}};
static void cont__84_22(void);
static NODE *string__84_23;
static void cont__84_24(void);
static void cont__84_25(void);
static NODE *func__84_26;
static void entry__84_26(void);
static FRAME_INFO frame__84_26 = {3, {"m", "ac", "val"}};
static void cont__84_27(void);
static NODE *func__84_28;
static void entry__84_28(void);
static FRAME_INFO frame__84_28 = {3, {"val", "ac", "m"}};
static void cont__84_29(void);
static void cont__84_30(void);
static void cont__84_31(void);
static void cont__84_32(void);
static void cont__84_33(void);
static NODE *func__85_1_sim2c__write_timing_info;
static void entry__85_1_sim2c__write_timing_info(void);
static FRAME_INFO frame__85_1_sim2c__write_timing_info = {3, {"description", "filename", "new_t"}};
static void cont__85_2(void);
static void cont__85_3(void);
static NODE *func__85_4;
static void entry__85_4(void);
static FRAME_INFO frame__85_4 = {3, {"filename", "description", "new_t"}};
static void cont__85_5(void);
static void cont__85_6(void);
static void cont__85_7(void);
static void cont__85_8(void);
static void cont__85_9(void);
static void cont__85_10(void);
static void cont__85_11(void);
static NODE *string__85_12;
static NODE *func__85_13;
static void entry__85_13(void);
static FRAME_INFO frame__85_13 = {2, {"description", "new_t"}};
static void cont__85_14(void);
static void cont__85_15(void);
static NODE *string__85_16;
static void cont__85_17(void);
static void cont__85_18(void);
static NODE *get__sim2c__write_timing_info(void) {
  return var.sim2c__write_timing_info;
}
static NODE *func__86_1_build_executable;
static void entry__86_1_build_executable(void);
static FRAME_INFO frame__86_1_build_executable = {0, {}};
static NODE *func__86_2;
static void entry__86_2(void);
static FRAME_INFO frame__86_2 = {9, {"mod_filename", "mod_name", "exe_filename", "c_filename", "o_filename", "sim_info", "c_info", "c_buf", "zz"}};
static void cont__86_3(void);
static NODE *func__86_4;
static void entry__86_4(void);
static FRAME_INFO frame__86_4 = {1, {"mod_filename"}};
static NODE *string__86_5;
static void cont__86_6(void);
static NODE *func__86_7;
static void entry__86_7(void);
static FRAME_INFO frame__86_7 = {1, {"mod_filename"}};
static void cont__86_8(void);
static NODE *func__86_9;
static void entry__86_9(void);
static FRAME_INFO frame__86_9 = {1, {"exe_filename"}};
static NODE *string__86_10;
static void cont__86_11(void);
static void cont__86_12(void);
static void cont__86_13(void);
static void cont__86_14(void);
static void cont__86_15(void);
static void cont__86_16(void);
static NODE *func__86_17;
static void entry__86_17(void);
static FRAME_INFO frame__86_17 = {2, {"c_info", "sim_info"}};
static void cont__86_18(void);
static NODE *func__86_19;
static void entry__86_19(void);
static FRAME_INFO frame__86_19 = {2, {"c_info", "sim_info"}};
static void cont__86_20(void);
static void cont__86_21(void);
static void cont__86_22(void);
static void cont__86_23(void);
static void cont__86_24(void);
static NODE *func__86_25;
static void entry__86_25(void);
static FRAME_INFO frame__86_25 = {6, {"return__1", "mod_name", "c_buf", "c_filename", "o_filename", "c_source"}};
static void cont__86_26(void);
static void cont__86_27(void);
static NODE *func__86_28;
static void entry__86_28(void);
static FRAME_INFO frame__86_28 = {0, {}};
static NODE *string__86_29;
static void cont__86_30(void);
static NODE *func__86_31;
static void entry__86_31(void);
static FRAME_INFO frame__86_31 = {0, {}};
static void cont__86_32(void);
static void cont__86_33(void);
static NODE *func__86_34;
static void entry__86_34(void);
static FRAME_INFO frame__86_34 = {1, {"c_source"}};
static void cont__86_35(void);
static void cont__86_36(void);
static void cont__86_37(void);
static NODE *func__86_38;
static void entry__86_38(void);
static FRAME_INFO frame__86_38 = {1, {"c_filename"}};
static NODE *string__86_39;
static void cont__86_40(void);
static void cont__86_41(void);
static NODE *func__86_42;
static void entry__86_42(void);
static FRAME_INFO frame__86_42 = {1, {"c_filename"}};
static NODE *string__86_43;
static void cont__86_44(void);
static NODE *func__86_45;
static void entry__86_45(void);
static FRAME_INFO frame__86_45 = {5, {"c_buf", "c_filename", "o_filename", "c_info", "o_info"}};
static void cont__86_46(void);
static void cont__86_47(void);
static void cont__86_48(void);
static NODE *func__86_49;
static void entry__86_49(void);
static FRAME_INFO frame__86_49 = {2, {"o_info", "c_info"}};
static void cont__86_50(void);
static void cont__86_51(void);
static void cont__86_52(void);
static void cont__86_53(void);
static NODE *func__86_54;
static void entry__86_54(void);
static FRAME_INFO frame__86_54 = {2, {"c_filename", "o_filename"}};
static NODE *func__86_55;
static void entry__86_55(void);
static FRAME_INFO frame__86_55 = {1, {"o_info"}};
static void cont__86_56(void);
static void cont__86_57(void);
static void cont__86_58(void);
static NODE *func__86_59;
static void entry__86_59(void);
static FRAME_INFO frame__86_59 = {0, {}};
static NODE *string__86_60;
static NODE *string__86_61;
static NODE *string__86_62;
static void cont__86_63(void);
static NODE *func__86_64;
static void entry__86_64(void);
static FRAME_INFO frame__86_64 = {1, {"filename"}};
static void cont__86_65(void);
static NODE *func__86_66;
static void entry__86_66(void);
static FRAME_INFO frame__86_66 = {2, {"exe_filename", "info"}};
static void cont__86_67(void);
static void cont__86_68(void);
static NODE *func__86_69;
static void entry__86_69(void);
static FRAME_INFO frame__86_69 = {1, {"info"}};
static void cont__86_70(void);
static NODE *func__86_71;
static void entry__86_71(void);
static FRAME_INFO frame__86_71 = {1, {"info"}};
static void cont__86_72(void);
static void cont__86_73(void);
static void cont__86_74(void);
static void cont__86_75(void);
static NODE *func__86_76;
static void entry__86_76(void);
static FRAME_INFO frame__86_76 = {0, {}};
static void cont__86_77(void);
static NODE *func__86_78;
static void entry__86_78(void);
static FRAME_INFO frame__86_78 = {2, {"exe_filename", "libs_and_files"}};
static void cont__86_79(void);
static NODE *func__86_80;
static void entry__86_80(void);
static FRAME_INFO frame__86_80 = {1, {"libs_and_files"}};
static NODE *string__86_81;
static void cont__86_82(void);
static void cont__86_83(void);
static NODE *func__86_84;
static void entry__86_84(void);
static FRAME_INFO frame__86_84 = {5, {"libs_and_files", "exe_filename", "out", "err", "success"}};
static NODE *func__86_85;
static void entry__86_85(void);
static FRAME_INFO frame__86_85 = {0, {}};
static NODE *string__86_86;
static void cont__86_87(void);
static NODE *string__86_88;
static NODE *string__86_89;
static NODE *string__86_90;
static void cont__86_91(void);
static NODE *func__86_92;
static void entry__86_92(void);
static FRAME_INFO frame__86_92 = {1, {"err"}};
static void cont__86_93(void);
static NODE *func__86_94;
static void entry__86_94(void);
static FRAME_INFO frame__86_94 = {5, {"libs_and_files", "exe_filename", "out", "err", "success"}};
static NODE *func__86_95;
static void entry__86_95(void);
static FRAME_INFO frame__86_95 = {0, {}};
static NODE *string__86_96;
static void cont__86_97(void);
static void cont__86_98(void);
static NODE *func__86_99;
static void entry__86_99(void);
static FRAME_INFO frame__86_99 = {0, {}};
static NODE *string__86_100;
static void cont__86_101(void);
static NODE *func__86_102;
static void entry__86_102(void);
static FRAME_INFO frame__86_102 = {0, {}};
static void cont__86_103(void);
static void cont__86_104(void);
static void cont__86_105(void);
static NODE *func__86_106;
static void entry__86_106(void);
static FRAME_INFO frame__86_106 = {1, {"err"}};
static void cont__86_107(void);
static void cont__86_108(void);
static void cont__86_109(void);
static void cont__86_110(void);
static NODE *func__86_111;
static void entry__86_111(void);
static FRAME_INFO frame__86_111 = {0, {}};
static void cont__86_112(void);
static void cont__86_113(void);
static NODE *func__86_114;
static void entry__86_114(void);
static FRAME_INFO frame__86_114 = {2, {"exe_filename", "zz"}};
static void cont__86_115(void);
static NODE *func__86_116;
static void entry__86_116(void);
static FRAME_INFO frame__86_116 = {1, {"exe_filename"}};
static NODE *func__86_117;
static void entry__86_117(void);
static FRAME_INFO frame__86_117 = {1, {"exe_filename"}};
static void cont__86_118(void);
static void cont__86_119(void);
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
static void cont__run__platform__platform(void);
static void cont__run__platform__hardware_architecture(void);
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
static NODE *string__90_1;
static void cont__90_2(void);
static void cont__91_1(void);
static void cont__92_1(void);
static void cont__93_1(void);
static NODE *string__95_1;
static void cont__95_2(void);
static void cont__96_1(void);
static NODE *string__97_1;
static void cont__97_2(void);
static NODE *string__98_1;
static void cont__98_2(void);
static NODE *string__99_1;
static void cont__99_2(void);
static NODE *string__100_1;
static void cont__100_2(void);
static void cont__101_1(void);
static NODE *func__101_2;
static void entry__101_2(void);
static FRAME_INFO frame__101_2 = {0, {}};
static void cont__101_3(void);
static NODE *func__101_4;
static void entry__101_4(void);
static FRAME_INFO frame__101_4 = {0, {}};
static NODE *string__101_5;
static void cont__101_6(void);
static NODE *string__101_7;
static void cont__101_8(void);
static void cont__101_9(void);
static void cont__101_10(void);
static void cont__102_1(void);
static NODE *func__102_2;
static void entry__102_2(void);
static FRAME_INFO frame__102_2 = {0, {}};
static void cont__102_3(void);
static NODE *func__102_4;
static void entry__102_4(void);
static FRAME_INFO frame__102_4 = {0, {}};
static void cont__102_5(void);
static void cont__102_6(void);
static void cont__102_7(void);
static void cont__102_8(void);
static NODE *string__104_1;
static NODE *string__104_2;
static void cont__104_3(void);
static void cont__104_4(void);
static void cont__104_5(void);
static void cont__104_6(void);
static NODE *string__104_7;
static void cont__104_8(void);
static NODE *string__104_9;
static void cont__104_10(void);
static void cont__104_11(void);
static void cont__104_12(void);
static NODE *func__106_1;
static void entry__106_1(void);
static FRAME_INFO frame__106_1 = {2, {"platform", "priority"}};
static NODE *func__106_2;
static void entry__106_2(void);
static FRAME_INFO frame__106_2 = {3, {"break", "platform", "priority"}};
static NODE *func__106_3;
static void entry__106_3(void);
static FRAME_INFO frame__106_3 = {4, {"platform", "break", "priority", "plat"}};
static void cont__106_4(void);
static void cont__106_5(void);
static void cont__106_6(void);
static void cont__106_7(void);
static void cont__106_8(void);
static void cont__106_9(void);
static void cont__106_10(void);
static void cont__106_11(void);
static void cont__106_12(void);
static void cont__130_1(void);
static void cont__130_2(void);
static void cont__131_1(void);
static NODE *func__131_2;
static void entry__131_2(void);
static FRAME_INFO frame__131_2 = {0, {}};
static void cont__131_3(void);
static NODE *func__131_4;
static void entry__131_4(void);
static FRAME_INFO frame__131_4 = {0, {}};
static NODE *string__131_5;
static void cont__131_6(void);
static void cont__131_7(void);
static NODE *func__131_8;
static void entry__131_8(void);
static FRAME_INFO frame__131_8 = {0, {}};
static NODE *func__131_9;
static void entry__131_9(void);
static FRAME_INFO frame__131_9 = {0, {}};
static NODE *string__131_10;
static NODE *string__131_11;
static NODE *func__131_12;
static void entry__131_12(void);
static FRAME_INFO frame__131_12 = {0, {}};
static NODE *string__131_13;
static NODE *string__131_14;
static NODE *func__131_15;
static void entry__131_15(void);
static FRAME_INFO frame__131_15 = {0, {}};
static NODE *string__131_16;
static NODE *string__131_17;
static NODE *func__131_18;
static void entry__131_18(void);
static FRAME_INFO frame__131_18 = {0, {}};
static NODE *string__131_19;
static NODE *string__131_20;
static NODE *func__131_21;
static void entry__131_21(void);
static FRAME_INFO frame__131_21 = {0, {}};
static NODE *string__131_22;
static NODE *string__131_23;
static NODE *func__131_24;
static void entry__131_24(void);
static FRAME_INFO frame__131_24 = {0, {}};
static NODE *string__131_25;
static NODE *string__131_26;
static NODE *func__131_27;
static void entry__131_27(void);
static FRAME_INFO frame__131_27 = {0, {}};
static NODE *string__131_28;
static NODE *string__131_29;
static NODE *func__131_30;
static void entry__131_30(void);
static FRAME_INFO frame__131_30 = {0, {}};
static NODE *string__131_31;
static NODE *string__131_32;
static NODE *func__131_33;
static void entry__131_33(void);
static FRAME_INFO frame__131_33 = {0, {}};
static NODE *string__131_34;
static NODE *string__131_35;
static NODE *func__131_36;
static void entry__131_36(void);
static FRAME_INFO frame__131_36 = {0, {}};
static NODE *string__131_37;
static NODE *string__131_38;
static NODE *func__131_39;
static void entry__131_39(void);
static FRAME_INFO frame__131_39 = {0, {}};
static NODE *string__131_40;
static NODE *string__131_41;
static NODE *func__131_42;
static void entry__131_42(void);
static FRAME_INFO frame__131_42 = {0, {}};
static NODE *string__131_43;
static NODE *string__131_44;
static NODE *func__131_45;
static void entry__131_45(void);
static FRAME_INFO frame__131_45 = {0, {}};
static NODE *string__131_46;
static NODE *string__131_47;
static NODE *func__131_48;
static void entry__131_48(void);
static FRAME_INFO frame__131_48 = {0, {}};
static NODE *string__131_49;
static NODE *string__131_50;
static NODE *func__131_51;
static void entry__131_51(void);
static FRAME_INFO frame__131_51 = {0, {}};
static NODE *string__131_52;
static NODE *string__131_53;
static NODE *func__131_54;
static void entry__131_54(void);
static FRAME_INFO frame__131_54 = {0, {}};
static NODE *string__131_55;
static NODE *string__131_56;
static NODE *func__131_57;
static void entry__131_57(void);
static FRAME_INFO frame__131_57 = {0, {}};
static NODE *string__131_58;
static NODE *string__131_59;
static NODE *func__131_60;
static void entry__131_60(void);
static FRAME_INFO frame__131_60 = {0, {}};
static NODE *string__131_61;
static NODE *string__131_62;
static NODE *func__131_63;
static void entry__131_63(void);
static FRAME_INFO frame__131_63 = {0, {}};
static NODE *string__131_64;
static NODE *string__131_65;
static NODE *func__131_66;
static void entry__131_66(void);
static FRAME_INFO frame__131_66 = {0, {}};
static NODE *string__131_67;
static NODE *string__131_68;
static void cont__131_69(void);
static void cont__131_70(void);
static void cont__132_1(void);
static void cont__133_1(void);
static NODE *func__135_1;
static void entry__135_1(void);
static FRAME_INFO frame__135_1 = {0, {}};
static void cont__135_2(void);
static void cont__140_1(void);
static NODE *string__141_1;
static NODE *string__141_2;
static NODE *string__141_3;
static NODE *string__141_4;
static NODE *string__141_5;
static NODE *string__141_6;
static NODE *string__141_7;
static NODE *string__141_8;
static NODE *string__141_9;
static NODE *string__141_10;
static NODE *string__141_11;
static void cont__141_12(void);
static NODE *string__142_1;
static NODE *string__142_2;
static void cont__142_3(void);
static NODE *string__142_4;
static void cont__142_5(void);
static void cont__142_6(void);
static NODE *string__142_7;
static void cont__142_8(void);
static void cont__142_9(void);
static void cont__143_1(void);
static void cont__143_2(void);
static void cont__143_3(void);
static void cont__143_4(void);
static void cont__161_1(void);
static NODE *func__161_2;
static void entry__161_2(void);
static FRAME_INFO frame__161_2 = {0, {}};
static NODE *string__161_3;
static NODE *string__161_4;
static void cont__161_5(void);
static void cont__161_6(void);
static NODE *func__176_1;
static void entry__176_1(void);
static FRAME_INFO frame__176_1 = {0, {}};
static void cont__176_2(void);
static void cont__176_3(void);
static NODE *func__177_1;
static void entry__177_1(void);
static FRAME_INFO frame__177_1 = {0, {}};
static NODE *func__177_2;
static void entry__177_2(void);
static FRAME_INFO frame__177_2 = {0, {}};
static NODE *func__177_3;
static void entry__177_3(void);
static FRAME_INFO frame__177_3 = {0, {}};
static NODE *func__177_4;
static void entry__177_4(void);
static FRAME_INFO frame__177_4 = {0, {}};
static void cont__177_5(void);
static void cont__177_6(void);
static void cont__177_7(void);
static NODE *func__177_8;
static void entry__177_8(void);
static FRAME_INFO frame__177_8 = {0, {}};
static NODE *func__177_9;
static void entry__177_9(void);
static FRAME_INFO frame__177_9 = {0, {}};
static NODE *func__177_10;
static void entry__177_10(void);
static FRAME_INFO frame__177_10 = {0, {}};
static NODE *func__177_11;
static void entry__177_11(void);
static FRAME_INFO frame__177_11 = {0, {}};
static void cont__177_12(void);
static void cont__177_13(void);
static void cont__178_1(void);
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
  {cont__run__basic__parameters, NULL, 22, 22, 9, 37},
  {cont__run__basic__polymorphic_functions, NULL, 23, 23, 9, 26},
  {cont__run__basic__primitives, NULL, 24, 24, 9, 23},
  {cont__run__basic__runtime, NULL, 25, 25, 9, 29},
  {cont__run__basic__types__boolean, NULL, 26, 26, 9, 31},
  {cont__run__basic__types__character, NULL, 27, 27, 9, 34},
  {cont__run__basic__types__continuation, NULL, 28, 28, 9, 35},
  {cont__run__basic__types__date_and_time, NULL, 29, 29, 9, 30},
  {cont__run__basic__types__function, NULL, 30, 30, 9, 38},
  {cont__run__basic__types__insert_order_set, NULL, 31, 31, 9, 40},
  {cont__run__basic__types__insert_order_table, NULL, 32, 32, 9, 26},
  {cont__run__basic__types__list, NULL, 33, 33, 9, 43},
  {cont__run__basic__types__multi_dimensional_set, NULL, 34, 34, 9, 45},
  {cont__run__basic__types__multi_dimensional_table, NULL, 35, 35, 9, 28},
  {cont__run__basic__types__number, NULL, 36, 36, 9, 28},
  {cont__run__basic__types__object, NULL, 37, 37, 9, 37},
  {cont__run__basic__types__key_order_table, NULL, 38, 38, 9, 36},
  {cont__run__basic__types__key_value_pair, NULL, 39, 39, 9, 25},
  {cont__run__basic__types__set, NULL, 40, 40, 9, 35},
  {cont__run__basic__types__key_order_set, NULL, 41, 41, 9, 39},
  {cont__run__basic__types__string_primitives, NULL, 42, 42, 9, 28},
  {cont__run__basic__types__string, NULL, 43, 43, 9, 27},
  {cont__run__basic__types__table, NULL, 44, 44, 9, 31},
  {cont__run__basic__types__undefined, NULL, 45, 45, 9, 33},
  {cont__run__basic__types__unique_item, NULL, 46, 46, 9, 35},
  {cont__run__basic__types__unordered_set, NULL, 47, 47, 9, 37},
  {cont__run__basic__types__unordered_table, NULL, 48, 48, 9, 33},
  {cont__run__basic__types__value_range, NULL, 49, 49, 9, 28},
  {cont__run__system__export__html, NULL, 50, 50, 9, 27},
  {cont__run__platform__platform, NULL, 51, 51, 9, 40},
  {cont__run__platform__hardware_architecture, NULL, 52, 52, 9, 27},
  {cont__run__character_names, NULL, 53, 53, 9, 21},
  {cont__run__fragments, NULL, 54, 54, 9, 21},
  {cont__run__tokenizer, NULL, 55, 55, 9, 28},
  {cont__run__shared_variables, NULL, 56, 56, 9, 17},
  {cont__run__nodes, NULL, 57, 57, 9, 18},
  {cont__run__parser, NULL, 58, 58, 9, 20},
  {cont__run__expander, NULL, 59, 59, 9, 21},
  {cont__run__annotator, NULL, 60, 60, 9, 22},
  {cont__run__simplifier, NULL, 61, 61, 9, 18},
  {cont__run__macros, NULL, 62, 62, 9, 28},
  {cont__run__c_code_generator, NULL, 63, 63, 9, 26},
  {cont__run__pretty_printer, NULL, 64, 64, 9, 17},
  {cont__run__sim2c, NULL, 65, 65, 9, 21},
  {cont__run__extractor, NULL, 66, 66, 9, 31},
  {cont__run__runtime_definitions, NULL, 72, 91, 1, 62},
  {cont__90_2, NULL, 92, 92, 1, 30},
  {cont__91_1, NULL, 93, 93, 1, 30},
  {cont__92_1, NULL, 94, 94, 1, 28},
  {cont__93_1, NULL, 96, 96, 1, 49},
  {cont__95_2, NULL, 97, 97, 1, 15},
  {cont__96_1, NULL, 98, 98, 1, 17},
  {cont__97_2, NULL, 99, 99, 1, 72},
  {cont__98_2, NULL, 100, 100, 1, 37},
  {cont__99_2, NULL, 101, 101, 1, 39},
  {cont__100_2, NULL, 105, 105, 5, 25},
  {cont__101_1, NULL, 103, 110, 1, 45},
  {cont__101_10, NULL, 114, 114, 5, 26},
  {cont__102_1, NULL, 112, 119, 1, 45},
  {cont__102_8, NULL, 125, 125, 5, 19},
  {cont__104_3, NULL, 126, 126, 5, 22},
  {cont__104_4, NULL, 127, 127, 5, 22},
  {cont__104_5, NULL, 128, 128, 5, 21},
  {cont__104_6, NULL, 129, 129, 5, 19},
  {cont__104_8, NULL, 130, 130, 5, 17},
  {cont__104_10, NULL, 131, 131, 5, 16},
  {cont__104_11, NULL, 123, 131, 1, 17},
  {cont__104_12, NULL, 134, 144, 1, 22},
  {cont__106_12, NULL, 168, 168, 42, 42},
  {cont__130_1, NULL, 168, 168, 1, 43},
  {cont__130_2, NULL, 170, 170, 3, 20},
  {cont__131_1, NULL, 169, 244, 1, 49},
  {cont__131_70, NULL, 245, 245, 1, 39},
  {cont__132_1, NULL, 246, 246, 1, 30},
  {cont__133_1, NULL, 248, 248, 1, 37},
  {cont__135_2, NULL, 257, 257, 1, 21},
  {cont__140_1, NULL, 259, 271, 1, 27},
  {cont__141_12, NULL, 275, 275, 16, 44},
  {cont__142_3, NULL, 275, 275, 5, 44},
  {cont__142_5, NULL, 276, 276, 16, 44},
  {cont__142_6, NULL, 276, 276, 5, 44},
  {cont__142_8, NULL, 273, 276, 1, 45},
  {cont__142_9, NULL, 282, 282, 37, 59},
  {cont__143_1, NULL, 282, 282, 7, 60},
  {cont__143_2, NULL, 281, 283, 5, 15},
  {cont__143_3, NULL, 278, 283, 1, 18},
  {cont__143_4, NULL, 621, 621, 4, 25},
  {cont__161_1, NULL, 621, 623, 1, 52},
  {cont__161_6, NULL, 1068, 1068, 1, 36},
  {cont__176_3, NULL, 1069, 1081, 1, 18},
  {cont__177_13, NULL, },
  {cont__178_1, NULL, },
  {entry__47_2, NULL, 251, 251, 36, 49},
  {entry__47_1_sim2c__show_compiler_debug_info, NULL, 251, 251, 3, 49},
  {entry__63_13, NULL, 302, 302, 37, 80},
  {cont__63_14, &frame__63_13, 302, 302, 37, 61},
  {cont__63_15, &frame__63_13, 302, 302, 80, 80},
  {entry__63_10, NULL, 301, 301, 13, 41},
  {cont__63_11, &frame__63_10, 302, 302, 16, 34},
  {cont__63_12, &frame__63_10, 302, 302, 13, 80},
  {entry__63_8, NULL, 300, 300, 14, 33},
  {cont__63_9, &frame__63_8, 300, 302, 11, 80},
  {entry__63_6, NULL, 299, 299, 18, 32},
  {cont__63_7, &frame__63_6, 299, 302, 9, 81},
  {entry__63_4, NULL, 298, 298, 10, 26},
  {cont__63_5, &frame__63_4, 298, 302, 7, 82},
  {entry__63_3, NULL, 297, 302, 5, 83},
  {entry__63_20, NULL, 306, 307, 11, 57},
  {cont__63_23, &frame__63_20, 306, 307, 5, 57},
  {entry__63_1_resolve_filename, NULL, 295, 295, 6, 36},
  {cont__63_2, &frame__63_1_resolve_filename, 295, 302, 3, 84},
  {cont__63_16, &frame__63_1_resolve_filename, 303, 303, 3, 32},
  {cont__63_17, &frame__63_1_resolve_filename, 304, 304, 3, 38},
  {cont__63_18, &frame__63_1_resolve_filename, 305, 305, 6, 25},
  {cont__63_19, &frame__63_1_resolve_filename, 305, 307, 3, 58},
  {cont__63_24, &frame__63_1_resolve_filename, 308, 308, 21, 39},
  {cont__63_25, &frame__63_1_resolve_filename, 308, 308, 6, 40},
  {cont__63_26, &frame__63_1_resolve_filename, 308, 308, 3, 40},
  {entry__64_10, NULL, 326, 326, 56, 77},
  {cont__64_11, &frame__64_10, 326, 326, 77, 77},
  {entry__64_8, NULL, 326, 326, 35, 53},
  {cont__64_9, &frame__64_8, 326, 326, 32, 77},
  {entry__64_6, NULL, 326, 326, 10, 29},
  {cont__64_7, &frame__64_6, 326, 326, 7, 77},
  {entry__64_28, NULL, 332, 332, 41, 65},
  {cont__64_29, &frame__64_28, 332, 332, 41, 65},
  {entry__64_31, NULL, 333, 333, 11, 38},
  {cont__64_32, &frame__64_31, 333, 333, 49, 49},
  {entry__64_15, NULL, 328, 328, 48, 60},
  {cont__64_17, &frame__64_15, 328, 328, 48, 68},
  {cont__64_18, &frame__64_15, 328, 328, 9, 69},
  {cont__64_19, &frame__64_15, 329, 329, 9, 34},
  {cont__64_20, &frame__64_15, 330, 330, 22, 36},
  {cont__64_21, &frame__64_15, 330, 330, 38, 62},
  {cont__64_22, &frame__64_15, 330, 330, 22, 62},
  {cont__64_23, &frame__64_15, 330, 330, 22, 64},
  {cont__64_24, &frame__64_15, 330, 330, 9, 67},
  {cont__64_25, &frame__64_15, 331, 331, 9, 49},
  {cont__64_26, &frame__64_15, 332, 332, 12, 36},
  {cont__64_27, &frame__64_15, 332, 332, 12, 65},
  {cont__64_30, &frame__64_15, 332, 333, 9, 49},
  {cont__64_33, &frame__64_15, 334, 334, 9, 52},
  {cont__64_34, &frame__64_15, 335, 335, 9, 26},
  {cont__64_35, &frame__64_15, 336, 336, 9, 43},
  {cont__64_36, &frame__64_15, 337, 337, 9, 30},
  {cont__64_37, &frame__64_15, 337, 337, 52, 52},
  {entry__64_12, NULL, 327, 327, 10, 33},
  {cont__64_14, &frame__64_12, 327, 337, 7, 52},
  {entry__64_4, NULL, 324, 324, 5, 33},
  {cont__64_5, &frame__64_4, 325, 337, 5, 53},
  {entry__64_49, NULL, 343, 343, 38, 60},
  {cont__64_50, &frame__64_49, 343, 343, 60, 60},
  {entry__64_45_maybe_push_common, NULL, 342, 342, 11, 54},
  {cont__64_47, &frame__64_45_maybe_push_common, 343, 343, 14, 35},
  {cont__64_48, &frame__64_45_maybe_push_common, 343, 343, 11, 60},
  {entry__64_57, NULL, 350, 351, 17, 57},
  {cont__64_60, &frame__64_57, 350, 351, 11, 57},
  {entry__64_67, NULL, 355, 355, 11, 34},
  {cont__64_68, &frame__64_67, 356, 356, 11, 45},
  {cont__64_69, &frame__64_67, 356, 356, 45, 45},
  {entry__64_64, NULL, 354, 354, 18, 31},
  {cont__64_65, &frame__64_64, 354, 354, 18, 31},
  {cont__64_66, &frame__64_64, 354, 356, 15, 45},
  {entry__64_44, NULL, 345, 345, 9, 35},
  {cont__64_51, &frame__64_44, 346, 346, 35, 58},
  {cont__64_52, &frame__64_44, 346, 346, 9, 59},
  {cont__64_53, &frame__64_44, 347, 347, 9, 39},
  {cont__64_54, &frame__64_44, 348, 348, 9, 46},
  {cont__64_55, &frame__64_44, 349, 349, 16, 32},
  {cont__64_56, &frame__64_44, 349, 351, 9, 58},
  {cont__64_61, &frame__64_44, 352, 352, 9, 30},
  {cont__64_62, &frame__64_44, 353, 353, 9, 34},
  {cont__64_63, &frame__64_44, 354, 356, 9, 45},
  {cont__64_70, &frame__64_44, 357, 357, 10, 30},
  {cont__64_71, &frame__64_44, 357, 357, 9, 40},
  {cont__64_72, &frame__64_44, 357, 357, 9, 30},
  {cont__64_73, &frame__64_44, 357, 357, 46, 46},
  {entry__64_41, NULL, 340, 340, 14, 44},
  {cont__64_43, &frame__64_41, 340, 357, 7, 46},
  {entry__64_39, NULL, 339, 339, 8, 30},
  {cont__64_40, &frame__64_39, 339, 357, 5, 47},
  {entry__64_77, NULL, 358, 358, 39, 64},
  {entry__64_1_add_module_infos, NULL, 319, 319, 22, 27},
  {cont__64_2, &frame__64_1_add_module_infos, 319, 319, 3, 33},
  {cont__64_3, &frame__64_1_add_module_infos, 323, 337, 3, 54},
  {cont__64_38, &frame__64_1_add_module_infos, 338, 357, 3, 48},
  {cont__64_74, &frame__64_1_add_module_infos, 358, 358, 6, 31},
  {cont__64_75, &frame__64_1_add_module_infos, 358, 358, 6, 36},
  {cont__64_76, &frame__64_1_add_module_infos, 358, 358, 3, 64},
  {cont__64_78, &frame__64_1_add_module_infos, 358, 358, 64, 64},
  {entry__65_4, NULL, 369, 369, 23, 29},
  {entry__65_5, NULL, 370, 370, 47, 47},
  {cont__65_6, &frame__65_5, 370, 370, 22, 48},
  {cont__65_7, &frame__65_5, 370, 370, 70, 70},
  {cont__65_8, &frame__65_5, 370, 370, 50, 71},
  {cont__65_9, &frame__65_5, 370, 370, 5, 71},
  {cont__65_10, &frame__65_5, 371, 371, 8, 28},
  {cont__65_11, &frame__65_5, 371, 371, 5, 28},
  {entry__65_1_lookup, NULL, 368, 368, 3, 29},
  {cont__65_2, &frame__65_1_lookup, 369, 369, 6, 20},
  {cont__65_3, &frame__65_1_lookup, 369, 371, 3, 28},
  {entry__66_2, NULL, 374, 374, 43, 52},
  {cont__66_3, &frame__66_2, 374, 374, 27, 52},
  {entry__66_1_Gcc, NULL, 374, 374, 3, 52},
  {cont__66_5, &frame__66_1_Gcc, 375, 375, 3, 11},
  {entry__67_2, NULL, 378, 378, 41, 60},
  {entry__67_8, NULL, 383, 383, 11, 23},
  {cont__67_9, &frame__67_8, 381, 383, 13, 24},
  {cont__67_12, &frame__67_8, 381, 383, 7, 24},
  {entry__67_4, NULL, 379, 379, 5, 72},
  {cont__67_7, &frame__67_4, 380, 383, 5, 25},
  {cont__67_13, &frame__67_4, 384, 384, 17, 17},
  {entry__67_1_compile_c, NULL, 378, 378, 10, 60},
  {cont__67_3, &frame__67_1_compile_c, 378, 384, 3, 17},
  {entry__68_25, NULL, 411, 411, 45, 74},
  {cont__68_26, &frame__68_25, 411, 411, 9, 41},
  {cont__68_27, &frame__68_25, 411, 411, 9, 74},
  {cont__68_28, &frame__68_25, 411, 411, 9, 74},
  {entry__68_21, NULL, 410, 410, 43, 75},
  {cont__68_22, &frame__68_21, 410, 410, 9, 39},
  {cont__68_23, &frame__68_21, 410, 410, 9, 75},
  {cont__68_24, &frame__68_21, 411, 411, 9, 74},
  {cont__68_29, &frame__68_21, },
  {entry__68_19, NULL, 409, 409, 9, 32},
  {cont__68_20, &frame__68_19, },
  {cont__68_30, &frame__68_19, },
  {entry__68_17, NULL, 408, 408, 9, 29},
  {cont__68_18, &frame__68_17, },
  {cont__68_31, &frame__68_17, },
  {entry__68_41, NULL, 423, 423, 17, 47},
  {cont__68_42, &frame__68_41, 423, 423, 17, 67},
  {cont__68_43, &frame__68_41, 423, 423, 17, 67},
  {entry__68_45, NULL, 426, 426, 17, 21},
  {entry__68_38_check, NULL, 419, 419, 13, 42},
  {cont__68_39, &frame__68_38_check, 422, 422, 17, 38},
  {cont__68_40, &frame__68_38_check, 421, 423, 15, 66},
  {cont__68_44, &frame__68_38_check, 420, 426, 13, 22},
  {entry__68_58, NULL, 436, 436, 58, 58},
  {cont__68_59, &frame__68_58, 436, 436, 40, 59},
  {cont__68_60, &frame__68_58, 436, 436, 23, 60},
  {cont__68_61, &frame__68_58, 436, 436, 17, 60},
  {entry__68_63, NULL, 438, 438, 53, 77},
  {cont__68_64, &frame__68_63, 438, 438, 47, 77},
  {entry__68_62, NULL, 438, 438, 17, 77},
  {entry__68_55, NULL, 435, 435, 15, 40},
  {cont__68_57, &frame__68_55, 434, 438, 13, 78},
  {entry__68_37, NULL, 428, 428, 18, 41},
  {cont__68_47, &frame__68_37, 428, 428, 11, 47},
  {cont__68_48, &frame__68_37, 429, 429, 11, 26},
  {cont__68_49, &frame__68_37, 430, 430, 11, 20},
  {cont__68_50, &frame__68_37, 431, 431, 11, 50},
  {cont__68_51, &frame__68_37, 432, 432, 11, 44},
  {cont__68_52, &frame__68_37, 433, 433, 14, 30},
  {cont__68_54, &frame__68_37, 433, 438, 11, 79},
  {entry__68_36, NULL, 417, 438, 9, 80},
  {cont__68_65, &frame__68_36, 438, 438, 80, 80},
  {entry__68_33, NULL, 414, 414, 7, 55},
  {cont__68_34, &frame__68_33, 415, 415, 7, 38},
  {cont__68_35, &frame__68_33, 416, 438, 7, 81},
  {entry__68_74, NULL, 453, 453, 29, 41},
  {cont__68_75, &frame__68_74, 453, 453, 23, 41},
  {entry__68_67, NULL, 447, 447, 7, 36},
  {cont__68_68, &frame__68_67, 448, 448, 7, 22},
  {cont__68_69, &frame__68_67, 449, 449, 7, 31},
  {cont__68_70, &frame__68_67, 450, 450, 7, 32},
  {cont__68_71, &frame__68_67, 451, 451, 7, 43},
  {cont__68_72, &frame__68_67, 452, 452, 7, 32},
  {cont__68_73, &frame__68_67, 453, 453, 7, 41},
  {cont__68_76, &frame__68_67, 454, 454, 25, 35},
  {cont__68_77, &frame__68_67, 454, 454, 7, 35},
  {cont__68_78, &frame__68_67, 454, 454, 35, 35},
  {entry__68_2, NULL, 396, 396, 48, 48},
  {cont__68_3, &frame__68_2, 396, 396, 5, 49},
  {cont__68_4, &frame__68_2, 397, 397, 35, 57},
  {cont__68_5, &frame__68_2, 397, 397, 5, 58},
  {cont__68_6, &frame__68_2, 398, 398, 5, 42},
  {cont__68_7, &frame__68_2, 399, 399, 42, 64},
  {cont__68_8, &frame__68_2, 399, 399, 5, 70},
  {cont__68_10, &frame__68_2, 400, 400, 51, 62},
  {cont__68_11, &frame__68_2, 400, 400, 39, 63},
  {cont__68_12, &frame__68_2, 400, 400, 5, 71},
  {cont__68_13, &frame__68_2, 401, 401, 5, 34},
  {cont__68_14, &frame__68_2, 402, 402, 5, 32},
  {cont__68_15, &frame__68_2, 403, 403, 5, 38},
  {cont__68_16, &frame__68_2, 405, 411, 5, 75},
  {cont__68_32, &frame__68_2, 413, 438, 5, 82},
  {cont__68_66, &frame__68_2, 439, 454, 5, 35},
  {cont__68_79, &frame__68_2, 455, 455, 5, 19},
  {cont__68_80, &frame__68_2, 456, 456, 8, 21},
  {cont__68_81, &frame__68_2, 456, 456, 5, 21},
  {entry__68_1_compile_meta_module, NULL, 395, 456, 3, 21},
  {entry__69_13, NULL, 481, 481, 43, 43},
  {cont__69_14, &frame__69_13, 481, 481, 15, 44},
  {cont__69_15, &frame__69_13, 483, 483, 48, 48},
  {cont__69_16, &frame__69_13, 483, 483, 24, 49},
  {cont__69_17, &frame__69_13, 483, 483, 17, 59},
  {cont__69_18, &frame__69_13, 484, 484, 44, 44},
  {cont__69_19, &frame__69_13, 484, 484, 24, 45},
  {cont__69_20, &frame__69_13, 484, 484, 17, 55},
  {cont__69_21, &frame__69_13, 482, 484, 15, 55},
  {entry__69_11, NULL, 480, 480, 16, 26},
  {cont__69_12, &frame__69_11, 480, 484, 13, 56},
  {entry__69_24, NULL, 490, 490, 17, 36},
  {entry__69_23, NULL, },
  {cont__69_25, &frame__69_23, },
  {entry__69_27, NULL, 492, 492, 32, 57},
  {cont__69_28, &frame__69_27, 492, 492, 17, 66},
  {entry__69_30, NULL, 495, 495, 44, 71},
  {cont__69_31, &frame__69_30, 495, 495, 30, 72},
  {cont__69_33, &frame__69_30, 495, 495, 19, 73},
  {cont__69_34, &frame__69_30, 495, 495, 78, 78},
  {entry__69_29, NULL, 494, 495, 17, 78},
  {entry__69_22, NULL, },
  {cont__69_26, &frame__69_22, 486, 495, 13, 80},
  {entry__69_9, NULL, 479, 479, 11, 36},
  {cont__69_10, &frame__69_9, 478, 495, 9, 82},
  {entry__69_36, NULL, 497, 497, 37, 64},
  {cont__69_37, &frame__69_36, 497, 497, 26, 65},
  {cont__69_38, &frame__69_36, 497, 497, 70, 70},
  {entry__69_35, NULL, 497, 497, 9, 70},
  {entry__69_2, NULL, 470, 470, 12, 35},
  {cont__69_3, &frame__69_2, 470, 470, 5, 42},
  {cont__69_4, &frame__69_2, 471, 471, 5, 20},
  {cont__69_5, &frame__69_2, 472, 472, 5, 14},
  {cont__69_6, &frame__69_2, 473, 473, 5, 44},
  {cont__69_7, &frame__69_2, 474, 474, 5, 38},
  {cont__69_8, &frame__69_2, 475, 497, 5, 71},
  {entry__69_1_build_dependencies, NULL, 469, 497, 3, 72},
  {cont__69_41, &frame__69_1_build_dependencies, 497, 497, 72, 72},
  {entry__70_9, NULL, 519, 519, 28, 44},
  {cont__70_10, &frame__70_9, 519, 519, 28, 44},
  {entry__70_12, NULL, 520, 520, 9, 72},
  {entry__70_18, NULL, 527, 527, 11, 40},
  {cont__70_19, &frame__70_18, 527, 527, 11, 60},
  {cont__70_20, &frame__70_18, 527, 527, 11, 60},
  {entry__70_22, NULL, 529, 529, 11, 59},
  {cont__70_23, &frame__70_22, 529, 529, 59, 59},
  {entry__70_3, NULL, 517, 517, 7, 45},
  {cont__70_4, &frame__70_3, 518, 518, 58, 58},
  {cont__70_5, &frame__70_3, 518, 518, 34, 59},
  {cont__70_6, &frame__70_3, 518, 518, 7, 75},
  {cont__70_7, &frame__70_3, 519, 519, 10, 23},
  {cont__70_8, &frame__70_3, 519, 519, 10, 44},
  {cont__70_11, &frame__70_3, 519, 520, 7, 72},
  {cont__70_13, &frame__70_3, 521, 521, 7, 53},
  {cont__70_14, &frame__70_3, 522, 522, 7, 38},
  {cont__70_15, &frame__70_3, 523, 523, 7, 34},
  {cont__70_16, &frame__70_3, 526, 526, 11, 40},
  {cont__70_17, &frame__70_3, 525, 527, 9, 59},
  {cont__70_21, &frame__70_3, 524, 529, 7, 60},
  {entry__70_27, NULL, 532, 532, 22, 43},
  {cont__70_28, &frame__70_27, 532, 532, 48, 48},
  {entry__70_32, NULL, 538, 538, 29, 56},
  {cont__70_33, &frame__70_32, 538, 538, 9, 56},
  {cont__70_34, &frame__70_32, 538, 538, 9, 56},
  {entry__70_30, NULL, 537, 537, 9, 27},
  {cont__70_31, &frame__70_30, 538, 538, 9, 56},
  {cont__70_35, &frame__70_30, },
  {entry__70_42, NULL, 541, 541, 21, 63},
  {entry__70_45, NULL, 542, 542, 35, 53},
  {entry__70_47, NULL, 543, 543, 32, 54},
  {entry__70_51, NULL, 545, 545, 26, 56},
  {entry__70_37, NULL, 540, 540, 50, 59},
  {cont__70_39, &frame__70_37, 540, 540, 61, 70},
  {cont__70_40, &frame__70_37, 540, 540, 9, 71},
  {cont__70_41, &frame__70_37, 541, 541, 9, 63},
  {cont__70_44, &frame__70_37, 542, 542, 9, 53},
  {cont__70_46, &frame__70_37, 543, 543, 9, 54},
  {cont__70_48, &frame__70_37, 544, 544, 25, 37},
  {cont__70_49, &frame__70_37, 544, 544, 9, 37},
  {cont__70_50, &frame__70_37, 545, 545, 9, 56},
  {cont__70_52, &frame__70_37, 545, 545, 56, 56},
  {entry__70_57, NULL, 552, 552, 44, 71},
  {cont__70_58, &frame__70_57, 552, 552, 13, 40},
  {cont__70_59, &frame__70_57, 552, 552, 13, 71},
  {cont__70_60, &frame__70_57, 552, 552, 13, 71},
  {entry__70_63, NULL, 554, 554, 30, 60},
  {entry__70_62, NULL, 554, 554, 13, 60},
  {entry__70_66, NULL, 559, 559, 17, 44},
  {cont__70_67, &frame__70_66, 559, 559, 17, 69},
  {cont__70_68, &frame__70_66, 559, 559, 17, 69},
  {entry__70_70, NULL, 561, 561, 17, 68},
  {cont__70_71, &frame__70_70, 561, 561, 68, 68},
  {entry__70_64, NULL, 558, 558, 17, 51},
  {cont__70_65, &frame__70_64, 557, 559, 15, 68},
  {cont__70_69, &frame__70_64, 556, 561, 13, 69},
  {entry__70_53, NULL, 547, 547, 9, 30},
  {cont__70_54, &frame__70_53, 548, 548, 9, 32},
  {cont__70_55, &frame__70_53, 551, 551, 13, 31},
  {cont__70_56, &frame__70_53, 550, 552, 11, 70},
  {cont__70_61, &frame__70_53, 549, 561, 9, 71},
  {entry__70_2_compile_submodule, NULL, 516, 529, 5, 61},
  {cont__70_24, &frame__70_2_compile_submodule, 530, 530, 5, 48},
  {cont__70_25, &frame__70_2_compile_submodule, 531, 531, 5, 28},
  {cont__70_26, &frame__70_2_compile_submodule, 532, 532, 5, 48},
  {cont__70_29, &frame__70_2_compile_submodule, 533, 533, 5, 21},
  {cont__70_36, &frame__70_2_compile_submodule, 534, 561, 5, 73},
  {cont__70_72, &frame__70_2_compile_submodule, 562, 562, 5, 63},
  {entry__70_75, NULL, 566, 567, 11, 56},
  {cont__70_78, &frame__70_75, 566, 567, 5, 56},
  {entry__70_91, NULL, 574, 574, 51, 75},
  {cont__70_92, &frame__70_91, 574, 574, 32, 75},
  {cont__70_93, &frame__70_91, 574, 574, 75, 75},
  {entry__70_86, NULL, 573, 573, 59, 59},
  {cont__70_87, &frame__70_86, 573, 573, 30, 60},
  {cont__70_88, &frame__70_86, 573, 573, 25, 61},
  {cont__70_89, &frame__70_86, 573, 573, 7, 61},
  {cont__70_90, &frame__70_86, 574, 574, 7, 75},
  {entry__70_99, NULL, 581, 581, 37, 60},
  {cont__70_100, &frame__70_99, 581, 581, 37, 60},
  {entry__70_102, NULL, 583, 583, 35, 35},
  {entry__70_96, NULL, 580, 580, 11, 47},
  {cont__70_97, &frame__70_96, 581, 581, 14, 32},
  {cont__70_98, &frame__70_96, 581, 581, 14, 60},
  {cont__70_101, &frame__70_96, 581, 583, 11, 35},
  {entry__70_104, NULL, 587, 587, 13, 37},
  {cont__70_105, &frame__70_104, 588, 588, 13, 32},
  {cont__70_106, &frame__70_104, 585, 588, 11, 32},
  {entry__70_95, NULL, 579, 583, 9, 36},
  {cont__70_103, &frame__70_95, 584, 588, 9, 33},
  {entry__70_113, NULL, 596, 596, 39, 62},
  {cont__70_114, &frame__70_113, 596, 596, 39, 62},
  {entry__70_116, NULL, 598, 598, 37, 37},
  {entry__70_110, NULL, 595, 595, 13, 77},
  {cont__70_111, &frame__70_110, 596, 596, 16, 34},
  {cont__70_112, &frame__70_110, 596, 596, 16, 62},
  {cont__70_115, &frame__70_110, 596, 598, 13, 37},
  {entry__70_119, NULL, 600, 600, 32, 53},
  {cont__70_120, &frame__70_119, 600, 600, 13, 65},
  {cont__70_121, &frame__70_119, 601, 601, 13, 39},
  {cont__70_122, &frame__70_119, 602, 602, 13, 35},
  {cont__70_123, &frame__70_119, 602, 602, 38, 38},
  {entry__70_109, NULL, 594, 598, 11, 38},
  {cont__70_117, &frame__70_109, 599, 599, 14, 37},
  {cont__70_118, &frame__70_109, 599, 602, 11, 38},
  {entry__70_130, NULL, 607, 607, 40, 69},
  {cont__70_132, &frame__70_130, 607, 607, 69, 69},
  {entry__70_129, NULL, 607, 607, 13, 69},
  {entry__70_125, NULL, 604, 604, 11, 61},
  {cont__70_126, &frame__70_125, 605, 605, 11, 38},
  {cont__70_127, &frame__70_125, 606, 606, 14, 33},
  {cont__70_128, &frame__70_125, 606, 607, 11, 69},
  {cont__70_133, &frame__70_125, 608, 608, 11, 39},
  {cont__70_134, &frame__70_125, 608, 608, 39, 39},
  {entry__70_108, NULL, 591, 602, 9, 39},
  {cont__70_124, &frame__70_108, 603, 608, 9, 39},
  {entry__70_94, NULL, 576, 588, 7, 34},
  {cont__70_107, &frame__70_94, 589, 608, 7, 40},
  {entry__70_1_compile_module, NULL, 564, 564, 3, 40},
  {cont__70_73, &frame__70_1_compile_module, 565, 565, 10, 28},
  {cont__70_74, &frame__70_1_compile_module, 565, 567, 3, 57},
  {cont__70_79, &frame__70_1_compile_module, 568, 568, 3, 39},
  {cont__70_81, &frame__70_1_compile_module, 569, 569, 6, 24},
  {cont__70_82, &frame__70_1_compile_module, 569, 569, 3, 31},
  {cont__70_83, &frame__70_1_compile_module, 570, 570, 3, 22},
  {cont__70_84, &frame__70_1_compile_module, 572, 572, 5, 21},
  {cont__70_85, &frame__70_1_compile_module, 571, 608, 3, 42},
  {cont__70_135, &frame__70_1_compile_module, 608, 608, 42, 42},
  {entry__71_4, NULL, 617, 617, 21, 41},
  {cont__71_5, &frame__71_4, 617, 617, 43, 67},
  {cont__71_6, &frame__71_4, 617, 617, 5, 67},
  {entry__71_8, NULL, 619, 619, 20, 40},
  {cont__71_9, &frame__71_8, 619, 619, 42, 66},
  {cont__71_10, &frame__71_8, 619, 619, 5, 66},
  {entry__71_1_compile_modules, NULL, 615, 615, 47, 66},
  {cont__71_2, &frame__71_1_compile_modules, 615, 615, 3, 66},
  {cont__71_3, &frame__71_1_compile_modules, 616, 617, 3, 67},
  {cont__71_7, &frame__71_1_compile_modules, 618, 619, 3, 66},
  {entry__73_6, NULL, 628, 628, 34, 58},
  {cont__73_8, &frame__73_6, 628, 628, 25, 58},
  {entry__73_2, NULL, 627, 627, 5, 40},
  {cont__73_4, &frame__73_2, 628, 628, 8, 22},
  {cont__73_5, &frame__73_2, 628, 628, 5, 58},
  {cont__73_9, &frame__73_2, 629, 629, 40, 57},
  {cont__73_10, &frame__73_2, 629, 629, 5, 57},
  {cont__73_12, &frame__73_2, 630, 630, 35, 54},
  {cont__73_13, &frame__73_2, 630, 630, 5, 54},
  {entry__73_1_show_file_list, NULL, 626, 630, 3, 54},
  {entry__74_7, NULL, 639, 639, 60, 70},
  {cont__74_9, &frame__74_7, 639, 639, 40, 70},
  {cont__74_10, &frame__74_7, 639, 639, 70, 70},
  {entry__74_5, NULL, 639, 639, 14, 30},
  {cont__74_6, &frame__74_5, 639, 639, 5, 70},
  {entry__74_12, NULL, 640, 640, 54, 77},
  {cont__74_13, &frame__74_12, 640, 640, 27, 77},
  {entry__74_16, NULL, 641, 641, 30, 54},
  {cont__74_17, &frame__74_16, 641, 641, 54, 54},
  {entry__74_24, NULL, 650, 650, 16, 45},
  {cont__74_27, &frame__74_24, 650, 650, 13, 45},
  {entry__74_28, NULL, 651, 651, 16, 38},
  {cont__74_30, &frame__74_28, 651, 651, 13, 38},
  {entry__74_21, NULL, 649, 649, 13, 39},
  {cont__74_23, &frame__74_21, 648, 651, 11, 37},
  {cont__74_31, &frame__74_21, 647, 651, 9, 39},
  {entry__74_34, NULL, 655, 655, 25, 44},
  {cont__74_35, &frame__74_34, 655, 655, 52, 71},
  {cont__74_36, &frame__74_34, 655, 655, 16, 73},
  {cont__74_37, &frame__74_34, 655, 656, 13, 26},
  {entry__74_38, NULL, 657, 657, 16, 29},
  {cont__74_39, &frame__74_38, 657, 657, 13, 29},
  {entry__74_32, NULL, 654, 654, 13, 34},
  {cont__74_33, &frame__74_32, 653, 657, 11, 28},
  {cont__74_40, &frame__74_32, 652, 657, 9, 30},
  {entry__74_19, NULL, 646, 646, 9, 35},
  {cont__74_20, &frame__74_19, 645, 657, 7, 30},
  {cont__74_41, &frame__74_19, 643, 657, 5, 32},
  {cont__74_42, &frame__74_19, 657, 657, 33, 33},
  {entry__74_1_library_paths_and_file_list, NULL, 633, 633, 3, 16},
  {cont__74_2, &frame__74_1_library_paths_and_file_list, 637, 637, 3, 39},
  {cont__74_3, &frame__74_1_library_paths_and_file_list, 638, 638, 6, 21},
  {cont__74_4, &frame__74_1_library_paths_and_file_list, 638, 639, 3, 70},
  {cont__74_11, &frame__74_1_library_paths_and_file_list, 640, 640, 3, 77},
  {cont__74_15, &frame__74_1_library_paths_and_file_list, 641, 641, 3, 54},
  {cont__74_18, &frame__74_1_library_paths_and_file_list, 642, 657, 3, 33},
  {cont__74_43, &frame__74_1_library_paths_and_file_list, 658, 658, 24, 57},
  {cont__74_44, &frame__74_1_library_paths_and_file_list, 658, 658, 3, 57},
  {entry__75_9, NULL, 668, 668, 51, 64},
  {cont__75_10, &frame__75_9, 668, 668, 51, 64},
  {entry__75_7, NULL, 668, 668, 37, 46},
  {cont__75_8, &frame__75_7, 668, 668, 37, 64},
  {cont__75_11, &frame__75_7, 668, 668, 37, 64},
  {entry__75_29, NULL, 679, 679, 25, 59},
  {cont__75_31, &frame__75_29, 679, 679, 21, 60},
  {cont__75_32, &frame__75_29, 679, 679, 21, 60},
  {entry__75_25, NULL, 678, 678, 25, 58},
  {cont__75_27, &frame__75_25, 678, 678, 21, 59},
  {cont__75_28, &frame__75_25, 679, 679, 21, 60},
  {cont__75_33, &frame__75_25, },
  {entry__75_38, NULL, 683, 683, 46, 80},
  {cont__75_39, &frame__75_38, 683, 683, 46, 80},
  {entry__75_41, NULL, 685, 685, 44, 74},
  {cont__75_42, &frame__75_41, 685, 685, 23, 74},
  {entry__75_35, NULL, 683, 683, 21, 34},
  {cont__75_36, &frame__75_35, 683, 683, 21, 41},
  {cont__75_37, &frame__75_35, 683, 683, 21, 80},
  {cont__75_40, &frame__75_35, 682, 685, 19, 75},
  {entry__75_49, NULL, 688, 688, 60, 60},
  {cont__75_50, &frame__75_49, 688, 688, 44, 61},
  {cont__75_51, &frame__75_49, 688, 688, 23, 61},
  {entry__75_46, NULL, 687, 687, 35, 62},
  {cont__75_47, &frame__75_46, 687, 687, 35, 67},
  {cont__75_48, &frame__75_46, 687, 688, 21, 61},
  {entry__75_43, NULL, 686, 686, 22, 62},
  {cont__75_45, &frame__75_43, 686, 688, 19, 62},
  {entry__75_52, NULL, 690, 690, 21, 52},
  {entry__75_54, NULL, 691, 691, 31, 45},
  {entry__75_21, NULL, 677, 677, 21, 34},
  {cont__75_22, &frame__75_21, 677, 677, 21, 41},
  {cont__75_23, &frame__75_21, 677, 677, 21, 41},
  {cont__75_24, &frame__75_21, 675, 679, 17, 61},
  {cont__75_34, &frame__75_21, 681, 690, 17, 53},
  {cont__75_53, &frame__75_21, 691, 691, 17, 45},
  {cont__75_56, &frame__75_21, 692, 692, 17, 33},
  {entry__75_17, NULL, 672, 672, 15, 38},
  {cont__75_18, &frame__75_17, 673, 673, 15, 50},
  {cont__75_19, &frame__75_17, 674, 674, 18, 39},
  {cont__75_20, &frame__75_17, 674, 692, 15, 33},
  {entry__75_13, NULL, 669, 669, 33, 37},
  {cont__75_14, &frame__75_13, 669, 669, 13, 38},
  {cont__75_15, &frame__75_13, 671, 671, 20, 42},
  {cont__75_16, &frame__75_13, 671, 692, 13, 34},
  {entry__75_5, NULL, 668, 668, 18, 32},
  {cont__75_6, &frame__75_5, 668, 668, 18, 64},
  {cont__75_12, &frame__75_5, 668, 692, 11, 35},
  {entry__75_59, NULL, 694, 694, 33, 42},
  {cont__75_60, &frame__75_59, 694, 694, 33, 42},
  {entry__75_62, NULL, 694, 694, 50, 50},
  {entry__75_57, NULL, 694, 694, 14, 28},
  {cont__75_58, &frame__75_57, 694, 694, 14, 42},
  {cont__75_61, &frame__75_57, 694, 694, 11, 50},
  {entry__75_3, NULL, 667, 667, 9, 20},
  {cont__75_4, &frame__75_3, 666, 694, 7, 51},
  {entry__75_2_collect_declarations, NULL, 665, 694, 5, 52},
  {entry__75_63, NULL, 696, 696, 28, 54},
  {entry__75_74, NULL, 701, 701, 22, 59},
  {entry__75_1_create_imports, NULL, 696, 696, 3, 54},
  {cont__75_64, &frame__75_1_create_imports, 697, 697, 3, 49},
  {cont__75_66, &frame__75_1_create_imports, 698, 698, 3, 18},
  {cont__75_67, &frame__75_1_create_imports, 699, 699, 3, 15},
  {cont__75_68, &frame__75_1_create_imports, 700, 700, 22, 42},
  {cont__75_69, &frame__75_1_create_imports, 700, 700, 22, 45},
  {cont__75_70, &frame__75_1_create_imports, 700, 700, 48, 48},
  {cont__75_71, &frame__75_1_create_imports, 700, 700, 9, 49},
  {cont__75_72, &frame__75_1_create_imports, 700, 700, 3, 49},
  {cont__75_73, &frame__75_1_create_imports, 701, 701, 3, 59},
  {entry__76_3, NULL, 704, 704, 32, 67},
  {entry__76_7, NULL, 706, 707, 5, 57},
  {entry__76_1_compile_exe, NULL, 704, 704, 6, 29},
  {cont__76_2, &frame__76_1_compile_exe, 704, 704, 3, 67},
  {cont__76_5, &frame__76_1_compile_exe, 705, 705, 10, 42},
  {cont__76_6, &frame__76_1_compile_exe, 705, 707, 3, 58},
  {cont__76_9, &frame__76_1_compile_exe, 709, 709, 3, 53},
  {cont__76_10, &frame__76_1_compile_exe, 710, 710, 46, 46},
  {cont__76_11, &frame__76_1_compile_exe, 710, 710, 3, 47},
  {cont__76_12, &frame__76_1_compile_exe, 711, 711, 3, 28},
  {cont__76_13, &frame__76_1_compile_exe, 711, 711, 28, 28},
  {entry__77_2, NULL, 716, 716, 11, 29},
  {cont__77_3, &frame__77_2, 716, 716, 5, 29},
  {cont__77_4, &frame__77_2, 716, 716, 29, 29},
  {entry__77_1_dump_source_or_check, NULL, 714, 716, 3, 29},
  {entry__78_4, NULL, 720, 720, 41, 65},
  {cont__78_5, &frame__78_4, 720, 720, 34, 75},
  {cont__78_6, &frame__78_4, 720, 720, 75, 75},
  {entry__78_8, NULL, 722, 722, 48, 57},
  {cont__78_9, &frame__78_8, 722, 722, 59, 68},
  {cont__78_10, &frame__78_8, 722, 722, 7, 69},
  {cont__78_11, &frame__78_8, 723, 723, 13, 31},
  {cont__78_12, &frame__78_8, 723, 723, 7, 31},
  {cont__78_13, &frame__78_8, 723, 723, 31, 31},
  {entry__78_15, NULL, 724, 724, 28, 50},
  {entry__78_18, NULL, 726, 726, 24, 59},
  {entry__78_2, NULL, 720, 720, 8, 31},
  {cont__78_3, &frame__78_2, 720, 720, 5, 75},
  {cont__78_7, &frame__78_2, 721, 723, 5, 31},
  {cont__78_14, &frame__78_2, 724, 724, 5, 50},
  {cont__78_16, &frame__78_2, 725, 725, 5, 15},
  {cont__78_17, &frame__78_2, 726, 726, 5, 59},
  {entry__78_1_print_c, NULL, 719, 726, 3, 59},
  {entry__79_5, NULL, 735, 735, 9, 43},
  {cont__79_6, &frame__79_5, 736, 736, 12, 28},
  {cont__79_7, &frame__79_5, 736, 736, 9, 34},
  {cont__79_8, &frame__79_5, 737, 737, 9, 21},
  {cont__79_9, &frame__79_5, 738, 738, 9, 64},
  {cont__79_10, &frame__79_5, 739, 739, 12, 23},
  {cont__79_11, &frame__79_5, 739, 739, 9, 29},
  {cont__79_12, &frame__79_5, 740, 740, 22, 22},
  {entry__79_4, NULL, 734, 740, 7, 22},
  {cont__79_13, &frame__79_4, 740, 740, 22, 22},
  {entry__79_3, NULL, 733, 740, 5, 23},
  {entry__79_17, NULL, 744, 744, 19, 65},
  {entry__79_16, NULL, 744, 744, 7, 65},
  {cont__79_19, &frame__79_16, 745, 745, 63, 63},
  {cont__79_20, &frame__79_16, 745, 745, 37, 64},
  {cont__79_21, &frame__79_16, 745, 745, 7, 64},
  {cont__79_22, &frame__79_16, 745, 745, 64, 64},
  {entry__79_25, NULL, 748, 748, 21, 66},
  {entry__79_24, NULL, 748, 748, 9, 66},
  {cont__79_26, &frame__79_24, 749, 749, 9, 44},
  {entry__79_23, NULL, 747, 749, 7, 44},
  {cont__79_27, &frame__79_23, 750, 750, 7, 32},
  {cont__79_29, &frame__79_23, 751, 751, 7, 32},
  {cont__79_31, &frame__79_23, 752, 752, 7, 34},
  {entry__79_35, NULL, 755, 755, 5, 40},
  {cont__79_36, &frame__79_35, 756, 756, 5, 32},
  {cont__79_37, &frame__79_35, 757, 757, 5, 20},
  {entry__79_1_list_dependencies, NULL, 729, 729, 3, 80},
  {cont__79_2, &frame__79_1_list_dependencies, 730, 740, 3, 24},
  {cont__79_14, &frame__79_1_list_dependencies, 742, 742, 5, 28},
  {cont__79_15, &frame__79_1_list_dependencies, 741, 752, 3, 35},
  {cont__79_33, &frame__79_1_list_dependencies, 753, 753, 3, 29},
  {cont__79_34, &frame__79_1_list_dependencies, 754, 757, 3, 20},
  {entry__80_7, NULL, 764, 765, 14, 58},
  {cont__80_10, &frame__80_7, 764, 765, 7, 58},
  {entry__80_12, NULL, 766, 766, 17, 73},
  {entry__80_34, NULL, 798, 800, 21, 49},
  {cont__80_37, &frame__80_34, 798, 800, 7, 49},
  {cont__80_38, &frame__80_34, 800, 800, 50, 50},
  {entry__80_48, NULL, 820, 820, 7, 42},
  {cont__80_49, &frame__80_48, 821, 821, 7, 34},
  {cont__80_50, &frame__80_48, 822, 827, 21, 23},
  {cont__80_53, &frame__80_48, 822, 827, 7, 23},
  {cont__80_54, &frame__80_48, 827, 827, 24, 24},
  {entry__80_2, NULL, 761, 761, 5, 55},
  {cont__80_4, &frame__80_2, 762, 762, 5, 31},
  {cont__80_5, &frame__80_2, 763, 763, 8, 22},
  {cont__80_6, &frame__80_2, 763, 765, 5, 59},
  {cont__80_11, &frame__80_2, 766, 766, 5, 73},
  {cont__80_14, &frame__80_2, 767, 767, 5, 40},
  {cont__80_15, &frame__80_2, 768, 768, 5, 18},
  {cont__80_16, &frame__80_2, 769, 769, 49, 49},
  {cont__80_17, &frame__80_2, 769, 769, 15, 50},
  {cont__80_18, &frame__80_2, 769, 769, 5, 74},
  {cont__80_19, &frame__80_2, 770, 770, 5, 31},
  {cont__80_20, &frame__80_2, 771, 771, 30, 73},
  {cont__80_21, &frame__80_2, 771, 771, 5, 78},
  {cont__80_22, &frame__80_2, 772, 772, 5, 33},
  {cont__80_24, &frame__80_2, 773, 773, 5, 61},
  {cont__80_27, &frame__80_2, 774, 774, 5, 25},
  {cont__80_28, &frame__80_2, 776, 796, 19, 22},
  {cont__80_32, &frame__80_2, 776, 796, 5, 22},
  {cont__80_33, &frame__80_2, 797, 800, 5, 50},
  {cont__80_39, &frame__80_2, 801, 818, 19, 21},
  {cont__80_46, &frame__80_2, 801, 818, 5, 21},
  {cont__80_47, &frame__80_2, 819, 827, 5, 24},
  {cont__80_55, &frame__80_2, 828, 834, 5, 32},
  {cont__80_57, &frame__80_2, 835, 835, 5, 25},
  {entry__80_1_build_codeblocks_project, NULL, 760, 835, 3, 25},
  {entry__81_4, NULL, 838, 838, 26, 56},
  {entry__81_7, NULL, 842, 842, 7, 41},
  {entry__81_12, NULL, 848, 848, 29, 50},
  {cont__81_13, &frame__81_12, 848, 848, 29, 55},
  {cont__81_14, &frame__81_12, 848, 848, 9, 56},
  {cont__81_15, &frame__81_12, 849, 849, 9, 47},
  {cont__81_16, &frame__81_12, 849, 849, 47, 47},
  {entry__81_20, NULL, 856, 856, 53, 66},
  {cont__81_21, &frame__81_20, 856, 856, 14, 67},
  {cont__81_23, &frame__81_20, 856, 856, 11, 67},
  {entry__81_24, NULL, 858, 858, 53, 67},
  {cont__81_26, &frame__81_24, 858, 858, 14, 68},
  {cont__81_27, &frame__81_24, 858, 858, 11, 68},
  {entry__81_28, NULL, 860, 860, 53, 69},
  {cont__81_30, &frame__81_28, 860, 860, 14, 70},
  {cont__81_31, &frame__81_28, 860, 860, 11, 70},
  {entry__81_32, NULL, 861, 861, 14, 50},
  {cont__81_34, &frame__81_32, 861, 861, 11, 50},
  {entry__81_38, NULL, 863, 863, 19, 56},
  {entry__81_47, NULL, 870, 870, 38, 63},
  {cont__81_48, &frame__81_47, 870, 870, 13, 63},
  {cont__81_49, &frame__81_47, 870, 870, 13, 63},
  {entry__81_51, NULL, 872, 872, 25, 25},
  {entry__81_44, NULL, 866, 866, 9, 32},
  {cont__81_45, &frame__81_44, 869, 869, 13, 29},
  {cont__81_46, &frame__81_44, 868, 870, 11, 62},
  {cont__81_50, &frame__81_44, 867, 872, 9, 26},
  {entry__81_54, NULL, 874, 874, 21, 54},
  {entry__81_63, NULL, 884, 884, 35, 47},
  {cont__81_64, &frame__81_63, 884, 884, 29, 47},
  {entry__81_57, NULL, 880, 880, 15, 76},
  {cont__81_59, &frame__81_57, 881, 881, 15, 43},
  {cont__81_60, &frame__81_57, 878, 883, 13, 26},
  {cont__81_62, &frame__81_57, 884, 884, 13, 47},
  {entry__81_70, NULL, 892, 892, 35, 47},
  {cont__81_71, &frame__81_70, 892, 892, 29, 47},
  {entry__81_65, NULL, 888, 888, 15, 43},
  {cont__81_66, &frame__81_65, 889, 889, 15, 30},
  {cont__81_68, &frame__81_65, 886, 891, 13, 26},
  {cont__81_69, &frame__81_65, 892, 892, 13, 47},
  {entry__81_79, NULL, 903, 903, 35, 47},
  {cont__81_80, &frame__81_79, 903, 903, 29, 47},
  {entry__81_72, NULL, 896, 898, 15, 23},
  {cont__81_74, &frame__81_72, 899, 899, 15, 43},
  {cont__81_75, &frame__81_72, 900, 900, 15, 30},
  {cont__81_76, &frame__81_72, 894, 902, 13, 26},
  {cont__81_78, &frame__81_72, 903, 903, 13, 47},
  {entry__81_84, NULL, 910, 910, 35, 47},
  {cont__81_85, &frame__81_84, 910, 910, 29, 47},
  {entry__81_81, NULL, 907, 907, 15, 43},
  {cont__81_82, &frame__81_81, 905, 909, 13, 26},
  {cont__81_83, &frame__81_81, 910, 910, 13, 47},
  {entry__81_53, NULL, 874, 874, 9, 54},
  {cont__81_56, &frame__81_53, 875, 910, 9, 48},
  {entry__81_8, NULL, 846, 846, 7, 56},
  {cont__81_10, &frame__81_8, 847, 847, 10, 38},
  {cont__81_11, &frame__81_8, 847, 849, 7, 47},
  {cont__81_17, &frame__81_8, 850, 850, 56, 56},
  {cont__81_18, &frame__81_8, 850, 850, 7, 57},
  {cont__81_19, &frame__81_8, 852, 861, 7, 51},
  {cont__81_37, &frame__81_8, 863, 863, 7, 56},
  {cont__81_40, &frame__81_8, 864, 864, 63, 63},
  {cont__81_41, &frame__81_8, 864, 864, 37, 64},
  {cont__81_42, &frame__81_8, 864, 864, 7, 64},
  {cont__81_43, &frame__81_8, 865, 872, 7, 27},
  {cont__81_52, &frame__81_8, 873, 910, 7, 49},
  {entry__81_1_build_library, NULL, 838, 838, 6, 23},
  {cont__81_3, &frame__81_1_build_library, 838, 838, 3, 56},
  {cont__81_6, &frame__81_1_build_library, 840, 910, 3, 51},
  {cont__81_86, &frame__81_1_build_library, 910, 910, 51, 51},
  {entry__82_6, NULL, 917, 918, 11, 42},
  {cont__82_9, &frame__82_6, 917, 918, 5, 42},
  {entry__82_13, NULL, 923, 923, 38, 65},
  {cont__82_14, &frame__82_13, 923, 923, 7, 34},
  {cont__82_15, &frame__82_13, 923, 923, 7, 65},
  {cont__82_16, &frame__82_13, 923, 923, 7, 65},
  {entry__82_19, NULL, 925, 925, 28, 65},
  {cont__82_21, &frame__82_19, 925, 925, 19, 65},
  {entry__82_18, NULL, 925, 925, 7, 65},
  {cont__82_22, &frame__82_18, 926, 926, 7, 37},
  {entry__82_1_maybe_compile_c_file, NULL, 913, 913, 3, 35},
  {cont__82_2, &frame__82_1_maybe_compile_c_file, 914, 914, 3, 35},
  {cont__82_3, &frame__82_1_maybe_compile_c_file, 915, 915, 3, 26},
  {cont__82_4, &frame__82_1_maybe_compile_c_file, 916, 916, 6, 24},
  {cont__82_5, &frame__82_1_maybe_compile_c_file, 916, 918, 3, 43},
  {cont__82_10, &frame__82_1_maybe_compile_c_file, 919, 919, 3, 26},
  {cont__82_11, &frame__82_1_maybe_compile_c_file, 922, 922, 7, 25},
  {cont__82_12, &frame__82_1_maybe_compile_c_file, 921, 923, 5, 64},
  {cont__82_17, &frame__82_1_maybe_compile_c_file, 920, 926, 3, 38},
  {entry__84_11, NULL, 942, 942, 39, 41},
  {cont__84_12, &frame__84_11, 942, 942, 36, 41},
  {cont__84_13, &frame__84_11, 942, 942, 28, 43},
  {cont__84_15, &frame__84_11, 942, 942, 21, 48},
  {cont__84_16, &frame__84_11, 942, 942, 48, 48},
  {entry__84_6, NULL, 941, 941, 13, 26},
  {cont__84_7, &frame__84_6, 941, 941, 9, 28},
  {cont__84_8, &frame__84_6, 942, 942, 16, 18},
  {cont__84_9, &frame__84_6, 942, 942, 12, 18},
  {cont__84_10, &frame__84_6, 942, 942, 9, 48},
  {cont__84_17, &frame__84_6, 943, 943, 9, 13},
  {entry__84_4, NULL, 940, 940, 10, 19},
  {cont__84_5, &frame__84_4, 940, 943, 7, 13},
  {entry__84_3, NULL, 939, 943, 5, 14},
  {cont__84_18, &frame__84_3, 943, 943, 14, 14},
  {entry__84_21, NULL, 946, 946, 27, 30},
  {cont__84_22, &frame__84_21, 946, 946, 19, 31},
  {cont__84_24, &frame__84_21, 946, 946, 7, 31},
  {cont__84_25, &frame__84_21, 946, 946, 31, 31},
  {entry__84_28, NULL, 948, 948, 33, 36},
  {cont__84_29, &frame__84_28, 948, 948, 33, 38},
  {cont__84_30, &frame__84_28, 948, 948, 33, 39},
  {cont__84_31, &frame__84_28, 948, 948, 18, 39},
  {cont__84_32, &frame__84_28, 948, 948, 39, 39},
  {entry__84_26, NULL, 948, 948, 10, 15},
  {cont__84_27, &frame__84_26, 948, 948, 7, 39},
  {entry__84_1_format_number, NULL, 936, 936, 3, 16},
  {cont__84_2, &frame__84_1_format_number, 938, 943, 3, 15},
  {cont__84_19, &frame__84_1_format_number, 945, 945, 5, 10},
  {cont__84_20, &frame__84_1_format_number, 944, 948, 3, 40},
  {cont__84_33, &frame__84_1_format_number, 949, 949, 3, 8},
  {entry__85_4, NULL, 955, 955, 37, 37},
  {cont__85_5, &frame__85_4, 955, 955, 7, 37},
  {cont__85_6, &frame__85_4, 961, 961, 20, 41},
  {cont__85_7, &frame__85_4, 961, 961, 17, 41},
  {cont__85_8, &frame__85_4, 961, 961, 9, 42},
  {cont__85_9, &frame__85_4, 962, 962, 23, 29},
  {cont__85_10, &frame__85_4, 962, 962, 9, 34},
  {cont__85_11, &frame__85_4, 956, 963, 7, 12},
  {entry__85_13, NULL, 965, 965, 47, 53},
  {cont__85_14, &frame__85_13, 965, 965, 33, 58},
  {cont__85_15, &frame__85_13, 965, 965, 7, 63},
  {entry__85_1_sim2c__write_timing_info, NULL, 952, 952, 3, 23},
  {cont__85_2, &frame__85_1_sim2c__write_timing_info, 954, 954, 5, 23},
  {cont__85_3, &frame__85_1_sim2c__write_timing_info, 953, 965, 3, 64},
  {cont__85_17, &frame__85_1_sim2c__write_timing_info, 966, 966, 3, 19},
  {cont__85_18, &frame__85_1_sim2c__write_timing_info, 966, 966, 19, 19},
  {entry__86_4, NULL, 982, 982, 12, 38},
  {cont__86_6, &frame__86_4, 982, 982, 9, 38},
  {entry__86_7, NULL, 983, 983, 9, 23},
  {entry__86_9, NULL, 985, 985, 17, 57},
  {entry__86_19, NULL, 996, 996, 42, 69},
  {cont__86_20, &frame__86_19, 996, 996, 9, 38},
  {cont__86_21, &frame__86_19, 996, 996, 9, 69},
  {cont__86_22, &frame__86_19, 996, 996, 9, 69},
  {entry__86_17, NULL, 995, 995, 9, 27},
  {cont__86_18, &frame__86_17, 996, 996, 9, 69},
  {cont__86_23, &frame__86_17, },
  {entry__86_28, NULL, 999, 999, 21, 61},
  {entry__86_31, NULL, 1000, 1000, 41, 59},
  {cont__86_32, &frame__86_31, 1000, 1000, 35, 64},
  {entry__86_34, NULL, 1001, 1001, 32, 54},
  {entry__86_38, NULL, 1003, 1003, 28, 64},
  {entry__86_42, NULL, 1005, 1005, 28, 67},
  {entry__86_25, NULL, 998, 998, 55, 67},
  {cont__86_26, &frame__86_25, 998, 998, 9, 67},
  {cont__86_27, &frame__86_25, 999, 999, 9, 61},
  {cont__86_30, &frame__86_25, 1000, 1000, 9, 64},
  {cont__86_33, &frame__86_25, 1001, 1001, 9, 54},
  {cont__86_35, &frame__86_25, 1002, 1002, 25, 37},
  {cont__86_36, &frame__86_25, 1002, 1002, 9, 37},
  {cont__86_37, &frame__86_25, 1003, 1003, 9, 64},
  {cont__86_40, &frame__86_25, 1004, 1004, 9, 39},
  {cont__86_41, &frame__86_25, 1005, 1005, 9, 67},
  {cont__86_44, &frame__86_25, 1005, 1005, 67, 67},
  {entry__86_49, NULL, 1012, 1012, 44, 71},
  {cont__86_50, &frame__86_49, 1012, 1012, 13, 40},
  {cont__86_51, &frame__86_49, 1012, 1012, 13, 71},
  {cont__86_52, &frame__86_49, 1012, 1012, 13, 71},
  {entry__86_54, NULL, 1014, 1014, 13, 43},
  {entry__86_55, NULL, 1016, 1016, 13, 64},
  {cont__86_56, &frame__86_55, 1016, 1016, 64, 64},
  {entry__86_45, NULL, 1007, 1007, 9, 30},
  {cont__86_46, &frame__86_45, 1008, 1008, 9, 32},
  {cont__86_47, &frame__86_45, 1011, 1011, 13, 31},
  {cont__86_48, &frame__86_45, 1010, 1012, 11, 70},
  {cont__86_53, &frame__86_45, 1009, 1016, 9, 65},
  {entry__86_64, NULL, 1021, 1021, 11, 39},
  {entry__86_59, NULL, 1020, 1020, 9, 62},
  {cont__86_63, &frame__86_59, 1019, 1021, 7, 40},
  {entry__86_71, NULL, 1029, 1029, 38, 63},
  {cont__86_72, &frame__86_71, 1029, 1029, 13, 63},
  {cont__86_73, &frame__86_71, 1029, 1029, 13, 63},
  {entry__86_69, NULL, 1028, 1028, 13, 45},
  {cont__86_70, &frame__86_69, 1027, 1029, 11, 62},
  {cont__86_74, &frame__86_69, 1027, 1029, 11, 62},
  {entry__86_76, NULL, 1031, 1031, 23, 23},
  {entry__86_66, NULL, 1023, 1023, 7, 30},
  {cont__86_67, &frame__86_66, 1026, 1026, 11, 27},
  {cont__86_68, &frame__86_66, 1025, 1029, 9, 63},
  {cont__86_75, &frame__86_66, 1024, 1031, 7, 24},
  {entry__86_80, NULL, 1034, 1034, 28, 75},
  {cont__86_82, &frame__86_80, 1034, 1034, 75, 75},
  {entry__86_85, NULL, 1037, 1037, 23, 58},
  {entry__86_92, NULL, 1045, 1045, 33, 45},
  {cont__86_93, &frame__86_92, 1045, 1045, 27, 45},
  {entry__86_84, NULL, 1037, 1037, 11, 58},
  {cont__86_87, &frame__86_84, 1038, 1044, 11, 24},
  {cont__86_91, &frame__86_84, 1045, 1045, 11, 45},
  {entry__86_95, NULL, 1047, 1047, 23, 51},
  {entry__86_99, NULL, 1052, 1052, 18, 40},
  {cont__86_101, &frame__86_99, 1052, 1052, 15, 40},
  {entry__86_102, NULL, 1053, 1053, 18, 33},
  {cont__86_103, &frame__86_102, 1053, 1053, 15, 33},
  {entry__86_106, NULL, 1056, 1056, 33, 45},
  {cont__86_107, &frame__86_106, 1056, 1056, 27, 45},
  {entry__86_94, NULL, 1047, 1047, 11, 51},
  {cont__86_97, &frame__86_94, 1051, 1051, 15, 41},
  {cont__86_98, &frame__86_94, 1050, 1053, 13, 32},
  {cont__86_104, &frame__86_94, 1048, 1055, 11, 24},
  {cont__86_105, &frame__86_94, 1056, 1056, 11, 45},
  {entry__86_78, NULL, 1033, 1033, 7, 52},
  {cont__86_79, &frame__86_78, 1034, 1034, 7, 75},
  {cont__86_83, &frame__86_78, 1035, 1056, 7, 46},
  {entry__86_111, NULL, 1058, 1058, 24, 41},
  {cont__86_112, &frame__86_111, 1058, 1058, 24, 41},
  {entry__86_116, NULL, 1062, 1062, 11, 25},
  {entry__86_117, NULL, 1063, 1063, 14, 38},
  {cont__86_118, &frame__86_117, 1063, 1063, 11, 38},
  {entry__86_114, NULL, 1061, 1061, 11, 39},
  {cont__86_115, &frame__86_114, 1060, 1063, 9, 37},
  {cont__86_119, &frame__86_114, 1059, 1066, 7, 44},
  {entry__86_2, NULL, 981, 981, 9, 36},
  {cont__86_3, &frame__86_2, 979, 983, 5, 24},
  {cont__86_8, &frame__86_2, 985, 985, 5, 57},
  {cont__86_11, &frame__86_2, 986, 986, 5, 41},
  {cont__86_12, &frame__86_2, 987, 987, 5, 41},
  {cont__86_13, &frame__86_2, 988, 988, 5, 33},
  {cont__86_14, &frame__86_2, 989, 989, 5, 28},
  {cont__86_15, &frame__86_2, 991, 991, 5, 24},
  {cont__86_16, &frame__86_2, },
  {cont__86_24, &frame__86_2, 992, 1016, 5, 67},
  {cont__86_57, &frame__86_2, 1017, 1017, 5, 50},
  {cont__86_58, &frame__86_2, 1018, 1021, 5, 41},
  {cont__86_65, &frame__86_2, 1022, 1031, 5, 25},
  {cont__86_77, &frame__86_2, 1032, 1056, 5, 47},
  {cont__86_108, &frame__86_2, 1057, 1057, 41, 41},
  {cont__86_109, &frame__86_2, 1057, 1057, 5, 42},
  {cont__86_110, &frame__86_2, 1058, 1058, 8, 41},
  {cont__86_113, &frame__86_2, 1058, 1066, 5, 45},
  {entry__86_1_build_executable, NULL, 978, 1066, 3, 46},
  {entry__101_2, NULL, 106, 106, 8, 28},
  {cont__101_3, &frame__101_2, 106, 106, 5, 28},
  {entry__101_4, NULL, 109, 109, 9, 48},
  {cont__101_6, &frame__101_4, 110, 110, 9, 42},
  {cont__101_8, &frame__101_4, 108, 110, 7, 41},
  {cont__101_9, &frame__101_4, 107, 110, 5, 43},
  {entry__102_2, NULL, 115, 115, 8, 29},
  {cont__102_3, &frame__102_2, 115, 115, 5, 29},
  {entry__102_4, NULL, 118, 118, 9, 48},
  {cont__102_5, &frame__102_4, 119, 119, 9, 42},
  {cont__102_6, &frame__102_4, 117, 119, 7, 41},
  {cont__102_7, &frame__102_4, 116, 119, 5, 43},
  {entry__106_3, NULL, 139, 139, 7, 41},
  {cont__106_4, &frame__106_3, 140, 140, 10, 26},
  {cont__106_5, &frame__106_3, 140, 140, 7, 32},
  {cont__106_6, &frame__106_3, 141, 141, 7, 19},
  {cont__106_7, &frame__106_3, 142, 142, 7, 34},
  {cont__106_8, &frame__106_3, 143, 143, 10, 21},
  {cont__106_9, &frame__106_3, 143, 143, 7, 27},
  {cont__106_10, &frame__106_3, 144, 144, 20, 20},
  {entry__106_2, NULL, 138, 144, 5, 20},
  {cont__106_11, &frame__106_2, 144, 144, 20, 20},
  {entry__106_1, NULL, 137, 144, 3, 21},
  {entry__131_4, NULL, 171, 171, 41, 79},
  {entry__131_2, NULL, 171, 171, 8, 38},
  {cont__131_3, &frame__131_2, 171, 171, 5, 79},
  {cont__131_6, &frame__131_2, 172, 172, 5, 45},
  {cont__131_7, &frame__131_2, 172, 172, 45, 45},
  {entry__131_9, NULL, 178, 179, 7, 52},
  {entry__131_12, NULL, 181, 182, 7, 34},
  {entry__131_15, NULL, 184, 185, 7, 57},
  {entry__131_18, NULL, 187, 188, 7, 71},
  {entry__131_21, NULL, 190, 191, 7, 47},
  {entry__131_24, NULL, 193, 194, 7, 61},
  {entry__131_27, NULL, 196, 199, 9, 29},
  {entry__131_30, NULL, 203, 204, 7, 33},
  {entry__131_33, NULL, 206, 207, 7, 29},
  {entry__131_36, NULL, 209, 210, 7, 35},
  {entry__131_39, NULL, 212, 213, 7, 40},
  {entry__131_42, NULL, 215, 216, 9, 65},
  {entry__131_45, NULL, 220, 221, 7, 35},
  {entry__131_48, NULL, 223, 224, 7, 45},
  {entry__131_51, NULL, 226, 227, 9, 31},
  {entry__131_54, NULL, 231, 232, 7, 32},
  {entry__131_57, NULL, 234, 235, 7, 33},
  {entry__131_60, NULL, 237, 238, 7, 43},
  {entry__131_63, NULL, 240, 241, 7, 29},
  {entry__131_66, NULL, 243, 244, 7, 46},
  {entry__131_8, NULL, 174, 244, 5, 47},
  {cont__131_69, &frame__131_8, 244, 244, 48, 48},
  {entry__135_1, NULL, 248, 248, 37, 37},
  {entry__161_2, NULL, 622, 623, 9, 51},
  {cont__161_5, &frame__161_2, 622, 623, 3, 51},
  {entry__176_1, NULL, 1068, 1068, 20, 36},
  {cont__176_2, &frame__176_1, 1068, 1068, 36, 36},
  {entry__177_4, NULL, 1075, 1075, 7, 32},
  {entry__177_3, NULL, },
  {cont__177_5, &frame__177_3, },
  {entry__177_2, NULL, },
  {cont__177_6, &frame__177_2, },
  {entry__177_1, NULL, },
  {cont__177_7, &frame__177_1, 1070, 1076, 3, 24},
  {entry__177_8, NULL, 1077, 1077, 3, 23},
  {entry__177_9, NULL, 1078, 1078, 3, 43},
  {entry__177_10, NULL, 1079, 1079, 3, 57},
  {entry__177_11, NULL, 1080, 1080, 6, 29},
  {cont__177_12, &frame__177_11, 1080, 1080, 3, 43}
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
IMPORT void collect__platform__platform(void);
IMPORT void phase_1__platform__platform(void);
IMPORT void phase_2__platform__platform(void);
IMPORT void phase_3__platform__platform(void);
IMPORT void phase_4__platform__platform(void);
IMPORT void phase_5__platform__platform(void);
IMPORT void phase_6__platform__platform(void);
IMPORT void run__platform__platform(void);
IMPORT void collect__platform__hardware_architecture(void);
IMPORT void phase_1__platform__hardware_architecture(void);
IMPORT void phase_2__platform__hardware_architecture(void);
IMPORT void phase_3__platform__hardware_architecture(void);
IMPORT void phase_4__platform__hardware_architecture(void);
IMPORT void phase_5__platform__hardware_architecture(void);
IMPORT void phase_6__platform__hardware_architecture(void);
IMPORT void run__platform__hardware_architecture(void);
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
  // 22: ...  basic/polymorphic_functions>
  func = run__basic__polymorphic_functions;
  frame->cont = cont__run__basic__polymorphic_functions;
}
static void cont__run__basic__polymorphic_functions(void) {
  // 23: ...  basic/primitives>
  func = run__basic__primitives;
  frame->cont = cont__run__basic__primitives;
}
static void cont__run__basic__primitives(void) {
  // 24: ...  basic/runtime>
  func = run__basic__runtime;
  frame->cont = cont__run__basic__runtime;
}
static void cont__run__basic__runtime(void) {
  // 25: ...  basic/types/boolean>
  func = run__basic__types__boolean;
  frame->cont = cont__run__basic__types__boolean;
}
static void cont__run__basic__types__boolean(void) {
  // 26: ...  basic/types/character>
  func = run__basic__types__character;
  frame->cont = cont__run__basic__types__character;
}
static void cont__run__basic__types__character(void) {
  // 27: ...  basic/types/continuation>
  func = run__basic__types__continuation;
  frame->cont = cont__run__basic__types__continuation;
}
static void cont__run__basic__types__continuation(void) {
  // 28: ...  basic/types/date_and_time>
  func = run__basic__types__date_and_time;
  frame->cont = cont__run__basic__types__date_and_time;
}
static void cont__run__basic__types__date_and_time(void) {
  // 29: ...  basic/types/function>
  func = run__basic__types__function;
  frame->cont = cont__run__basic__types__function;
}
static void cont__run__basic__types__function(void) {
  // 30: ...  basic/types/insert_order_set>
  func = run__basic__types__insert_order_set;
  frame->cont = cont__run__basic__types__insert_order_set;
}
static void cont__run__basic__types__insert_order_set(void) {
  // 31: ...  basic/types/insert_order_table>
  func = run__basic__types__insert_order_table;
  frame->cont = cont__run__basic__types__insert_order_table;
}
static void cont__run__basic__types__insert_order_table(void) {
  // 32: ...  basic/types/list>
  func = run__basic__types__list;
  frame->cont = cont__run__basic__types__list;
}
static void cont__run__basic__types__list(void) {
  // 33: ...  basic/types/multi_dimensional_set>
  func = run__basic__types__multi_dimensional_set;
  frame->cont = cont__run__basic__types__multi_dimensional_set;
}
static void cont__run__basic__types__multi_dimensional_set(void) {
  // 34: ...  basic/types/multi_dimensional_table>
  func = run__basic__types__multi_dimensional_table;
  frame->cont = cont__run__basic__types__multi_dimensional_table;
}
static void cont__run__basic__types__multi_dimensional_table(void) {
  // 35: ...  basic/types/number>
  func = run__basic__types__number;
  frame->cont = cont__run__basic__types__number;
}
static void cont__run__basic__types__number(void) {
  // 36: ...  basic/types/object>
  func = run__basic__types__object;
  frame->cont = cont__run__basic__types__object;
}
static void cont__run__basic__types__object(void) {
  // 37: ...  basic/types/key_order_table>
  func = run__basic__types__key_order_table;
  frame->cont = cont__run__basic__types__key_order_table;
}
static void cont__run__basic__types__key_order_table(void) {
  // 38: ...  basic/types/key_value_pair>
  func = run__basic__types__key_value_pair;
  frame->cont = cont__run__basic__types__key_value_pair;
}
static void cont__run__basic__types__key_value_pair(void) {
  // 39: ...  basic/types/set>
  func = run__basic__types__set;
  frame->cont = cont__run__basic__types__set;
}
static void cont__run__basic__types__set(void) {
  // 40: ...  basic/types/key_order_set>
  func = run__basic__types__key_order_set;
  frame->cont = cont__run__basic__types__key_order_set;
}
static void cont__run__basic__types__key_order_set(void) {
  // 41: ...  basic/types/string_primitives>
  func = run__basic__types__string_primitives;
  frame->cont = cont__run__basic__types__string_primitives;
}
static void cont__run__basic__types__string_primitives(void) {
  // 42: ...  basic/types/string>
  func = run__basic__types__string;
  frame->cont = cont__run__basic__types__string;
}
static void cont__run__basic__types__string(void) {
  // 43: ...  basic/types/table>
  func = run__basic__types__table;
  frame->cont = cont__run__basic__types__table;
}
static void cont__run__basic__types__table(void) {
  // 44: ...  basic/types/undefined>
  func = run__basic__types__undefined;
  frame->cont = cont__run__basic__types__undefined;
}
static void cont__run__basic__types__undefined(void) {
  // 45: ...  basic/types/unique_item>
  func = run__basic__types__unique_item;
  frame->cont = cont__run__basic__types__unique_item;
}
static void cont__run__basic__types__unique_item(void) {
  // 46: ...  basic/types/unordered_set>
  func = run__basic__types__unordered_set;
  frame->cont = cont__run__basic__types__unordered_set;
}
static void cont__run__basic__types__unordered_set(void) {
  // 47: ...  basic/types/unordered_table>
  func = run__basic__types__unordered_table;
  frame->cont = cont__run__basic__types__unordered_table;
}
static void cont__run__basic__types__unordered_table(void) {
  // 48: ...  basic/types/value_range>
  func = run__basic__types__value_range;
  frame->cont = cont__run__basic__types__value_range;
}
static void cont__run__basic__types__value_range(void) {
  // 49: ...  system/export/html>
  func = run__system__export__html;
  frame->cont = cont__run__system__export__html;
}
static void cont__run__system__export__html(void) {
  // 50: ...  platform/platform>
  func = run__platform__platform;
  frame->cont = cont__run__platform__platform;
}
static void cont__run__platform__platform(void) {
  // 51: ...  platform/hardware_architecture>
  func = run__platform__hardware_architecture;
  frame->cont = cont__run__platform__hardware_architecture;
}
static void cont__run__platform__hardware_architecture(void) {
  // 52: ...  ./character_names>
  func = run__character_names;
  frame->cont = cont__run__character_names;
}
static void cont__run__character_names(void) {
  // 53: ...  ./fragments>
  func = run__fragments;
  frame->cont = cont__run__fragments;
}
static void cont__run__fragments(void) {
  // 54: ...  ./tokenizer>
  func = run__tokenizer;
  frame->cont = cont__run__tokenizer;
}
static void cont__run__tokenizer(void) {
  // 55: ...  ./shared_variables>
  func = run__shared_variables;
  frame->cont = cont__run__shared_variables;
}
static void cont__run__shared_variables(void) {
  // 56: ...  ./nodes>
  func = run__nodes;
  frame->cont = cont__run__nodes;
}
static void cont__run__nodes(void) {
  // 57: ...  ./parser>
  func = run__parser;
  frame->cont = cont__run__parser;
}
static void cont__run__parser(void) {
  // 58: ...  ./expander>
  func = run__expander;
  frame->cont = cont__run__expander;
}
static void cont__run__expander(void) {
  // 59: ...  ./annotator>
  func = run__annotator;
  frame->cont = cont__run__annotator;
}
static void cont__run__annotator(void) {
  // 60: ...  ./simplifier>
  func = run__simplifier;
  frame->cont = cont__run__simplifier;
}
static void cont__run__simplifier(void) {
  // 61: ...  ./macros>
  func = run__macros;
  frame->cont = cont__run__macros;
}
static void cont__run__macros(void) {
  // 62: ...  ./c_code_generator>
  func = run__c_code_generator;
  frame->cont = cont__run__c_code_generator;
}
static void cont__run__c_code_generator(void) {
  // 63: ...  ./pretty_printer>
  func = run__pretty_printer;
  frame->cont = cont__run__pretty_printer;
}
static void cont__run__pretty_printer(void) {
  // 64: ...  ./sim2c>
  func = run__sim2c;
  frame->cont = cont__run__sim2c;
}
static void cont__run__sim2c(void) {
  // 65: ...  ./extractor>
  func = run__extractor;
  frame->cont = cont__run__extractor;
}
static void cont__run__extractor(void) {
  // 66: ...  ./runtime_definitions>
  func = run__runtime_definitions;
  frame->cont = cont__run__runtime_definitions;
}
static void cont__run__runtime_definitions(void) {
  // 72: copyright "
  // 73:   Copyright (C) 2020 by
  // 74:   Dipl.-Ing. Michael Niederle
  // 75:   
  // 76:   This program is free software; you can redistribute it and/or modify
  // 77:   it under the terms of the GNU General Public License, version 2, or
  // 78:   (at your option) version 3.
  // 79:   
  // 80:   This program is distributed in the hope that it will be useful,
  // 81:   but WITHOUT ANY WARRANTY; without even the implied warranty of
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__90_1;
  result_count = 0;
  myself = get__copyright();
  func = myself->type;
  frame->cont = cont__90_2;
}
static void cont__90_2(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 92: $MAJOR runtime_major_version()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__runtime_major_version();
  func = myself->type;
  frame->cont = cont__91_1;
}
static void cont__91_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._MAJOR, arguments->slots[0]);
  // 93: $MINOR runtime_minor_version()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__runtime_minor_version();
  func = myself->type;
  frame->cont = cont__92_1;
}
static void cont__92_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._MINOR, arguments->slots[0]);
  // 94: $REVISION runtime_revision()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__runtime_revision();
  func = myself->type;
  frame->cont = cont__93_1;
}
static void cont__93_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._REVISION, arguments->slots[0]);
  // 96: $VERSION "@(MAJOR).@(MINOR).@(REVISION).@(BUILD)"
  argument_count = 7;
  arguments = node_p;
  arguments->slots[0] = var._MAJOR;
  arguments->slots[1] = string__95_1;
  arguments->slots[2] = var._MINOR;
  arguments->slots[3] = string__95_1;
  arguments->slots[4] = var._REVISION;
  arguments->slots[5] = string__95_1;
  arguments->slots[6] = var._BUILD;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__95_2;
}
static void cont__95_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._VERSION, arguments->slots[0]);
  // 97: version VERSION
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._VERSION;
  result_count = 0;
  myself = get__version();
  func = myself->type;
  frame->cont = cont__96_1;
}
static void cont__96_1(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 98: extern $gcc "gcc"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__97_1;
  result_count = 1;
  myself = get__extern();
  func = myself->type;
  frame->cont = cont__97_2;
}
static void cont__97_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._gcc, arguments->slots[0]);
  // 99: extern $mkdir "mkdir" # would be nice to have one in the system library!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__98_1;
  result_count = 1;
  myself = get__extern();
  func = myself->type;
  frame->cont = cont__98_2;
}
static void cont__98_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._mkdir, arguments->slots[0]);
  // 100: $SIMLIBPATH environment("SIMLIBPATH")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__99_1;
  result_count = 1;
  myself = get__environment();
  func = myself->type;
  frame->cont = cont__99_2;
}
static void cont__99_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._SIMLIBPATH, arguments->slots[0]);
  // 101: $SIMDATAPATH environment("SIMDATAPATH")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__100_1;
  result_count = 1;
  myself = get__environment();
  func = myself->type;
  frame->cont = cont__100_2;
}
static void cont__100_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._SIMDATAPATH, arguments->slots[0]);
  // 105: SIMLIBPATH.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._SIMLIBPATH;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__101_1;
}
static void cont__101_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 103: $simlibpaths
  // 104:   if
  // 105:     SIMLIBPATH.is_defined
  // 106:     -> split(SIMLIBPATH ':')
  // 107:     ->
  // 108:       list
  // 109:         "/usr/local/share/simplicity-@(VERSION)"
  // 110:         "/usr/share/simplicity-@(VERSION)"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__101_2;
  arguments->slots[2] = func__101_4;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__101_10;
}
static void entry__101_2(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 106: ... split(SIMLIBPATH ':')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._SIMLIBPATH;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__split();
  func = myself->type;
  frame->cont = cont__101_3;
}
static void cont__101_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 106: -> split(SIMLIBPATH ':')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__101_4(void) {
  allocate_initialized_frame_gc(0, 3);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 109: "/usr/local/share/simplicity-@(VERSION)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__101_5;
  arguments->slots[1] = var._VERSION;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__101_6;
}
static void cont__101_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 110: "/usr/share/simplicity-@(VERSION)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__101_7;
  arguments->slots[1] = var._VERSION;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__101_8;
}
static void cont__101_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 108: list
  // 109:   "/usr/local/share/simplicity-@(VERSION)"
  // 110:   "/usr/share/simplicity-@(VERSION)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  arguments->slots[1] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__101_9;
}
static void cont__101_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 107: ->
  // 108:   list
  // 109:     "/usr/local/share/simplicity-@(VERSION)"
  // 110:     "/usr/share/simplicity-@(VERSION)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__101_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._simlibpaths, arguments->slots[0]);
  // 114: SIMDATAPATH.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._SIMDATAPATH;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__102_1;
}
static void cont__102_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 112: $simdatapaths
  // 113:   if
  // 114:     SIMDATAPATH.is_defined
  // 115:     -> split(SIMDATAPATH ':')
  // 116:     ->
  // 117:       list
  // 118:         "/usr/local/share/simplicity-@(VERSION)"
  // 119:         "/usr/share/simplicity-@(VERSION)"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__102_2;
  arguments->slots[2] = func__102_4;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__102_8;
}
static void entry__102_2(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 115: ... split(SIMDATAPATH ':')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._SIMDATAPATH;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__split();
  func = myself->type;
  frame->cont = cont__102_3;
}
static void cont__102_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 115: -> split(SIMDATAPATH ':')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__102_4(void) {
  allocate_initialized_frame_gc(0, 3);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 118: "/usr/local/share/simplicity-@(VERSION)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__101_5;
  arguments->slots[1] = var._VERSION;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__102_5;
}
static void cont__102_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 119: "/usr/share/simplicity-@(VERSION)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__101_7;
  arguments->slots[1] = var._VERSION;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__102_6;
}
static void cont__102_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 117: list
  // 118:   "/usr/local/share/simplicity-@(VERSION)"
  // 119:   "/usr/share/simplicity-@(VERSION)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  arguments->slots[1] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__102_7;
}
static void cont__102_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 116: ->
  // 117:   list
  // 118:     "/usr/local/share/simplicity-@(VERSION)"
  // 119:     "/usr/share/simplicity-@(VERSION)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__102_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._simdatapaths, arguments->slots[0]);
  // 125: "bsd" = "posix"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__104_1;
  arguments->slots[1] = string__104_2;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__104_3;
}
static void cont__104_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 126: "cygwin" = "posix"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__81_35;
  arguments->slots[1] = string__104_2;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__104_4;
}
static void cont__104_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 127: "darwin" = "posix"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__81_36;
  arguments->slots[1] = string__104_2;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__104_5;
}
static void cont__104_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 128: "linux" = "posix"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__74_22;
  arguments->slots[1] = string__104_2;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__104_6;
}
static void cont__104_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 129: "posix" = "all"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__104_2;
  arguments->slots[1] = string__104_7;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__104_8;
}
static void cont__104_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 130: "win" = "all"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__104_9;
  arguments->slots[1] = string__104_7;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__104_10;
}
static void cont__104_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 131: "all" = NONE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__104_7;
  arguments->slots[1] = var._NONE;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__104_11;
}
static void cont__104_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__7 */ = arguments->slots[0];
  // 123: $supported_platforms
  // 124:   key_order_table
  // 125:     "bsd" = "posix"
  // 126:     "cygwin" = "posix"
  // 127:     "darwin" = "posix"
  // 128:     "linux" = "posix"
  // 129:     "posix" = "all"
  // 130:     "win" = "all"
  // 131:     "all" = NONE
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
  frame->cont = cont__104_12;
}
static void cont__104_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._supported_platforms, arguments->slots[0]);
  // 133: $$platform_priority empty_table
  var._platform_priority = get__empty_table();
  // 134: do:
  // 135:   $$platform current_platform
  // 136:   $$priority 0
  // 137:   do: (-> break)
  // 138:     forever:
  // 139:       $plat supported_platforms(platform)
  // 140:       if plat.is_undefined break
  // 141:       inc &priority
  // 142:       !platform_priority(platform) priority
  // 143:       if plat == NONE break
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__106_1;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__106_12;
}
static void entry__106_2(void) {
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
  // 138: ... :
  // 139:   $plat supported_platforms(platform)
  // 140:   if plat.is_undefined break
  // 141:   inc &priority
  // 142:   !platform_priority(platform) priority
  // 143:   if plat == NONE break
  // 144:   !platform plat
  frame->slots[3] /* temp__1 */ = create_closure(entry__106_3, 0);
  // 138: forever:
  // 139:   $plat supported_platforms(platform)
  // 140:   if plat.is_undefined break
  // 141:   inc &priority
  // 142:   !platform_priority(platform) priority
  // 143:   if plat == NONE break
  // 144:   !platform plat
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame->cont = cont__106_11;
}
static void entry__106_3(void) {
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
  // 139: $plat supported_platforms(platform)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* platform */;
  result_count = 1;
  myself = var._supported_platforms;
  func = myself->type;
  frame->cont = cont__106_4;
}
static void cont__106_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* plat */, arguments->slots[0]);
  // 140: ... plat.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* plat */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__106_5;
}
static void cont__106_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 140: if plat.is_undefined break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* break */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__106_6;
}
static void cont__106_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 141: inc &priority
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* priority */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__106_7;
}
static void cont__106_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* priority */ = arguments->slots[0];
  // 142: !platform_priority(platform) priority
  frame->slots[4] /* temp__1 */ = ((CELL *)frame->slots[2])->contents /* priority */;
  // 142: !platform_priority(platform)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* platform */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = var._platform_priority;
  func = myself->type;
  frame->cont = cont__106_8;
}
static void cont__106_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._platform_priority = arguments->slots[0];
  // 143: ... plat == NONE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* plat */;
  arguments->slots[1] = var._NONE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__106_9;
}
static void cont__106_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 143: if plat == NONE break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* break */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__106_10;
}
static void cont__106_10(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 144: !platform plat
  ((CELL *)frame->slots[0])->contents /* platform */ = frame->slots[3] /* plat */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__106_11(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__106_1(void) {
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
  // 135: $$platform current_platform
  ((CELL *)frame->slots[0])->contents /* platform */ = get__current_platform();
  // 136: $$priority 0
  ((CELL *)frame->slots[1])->contents /* priority */ = number__0;
  // 137: ... : (-> break)
  // 138:   forever:
  // 139:     $plat supported_platforms(platform)
  // 140:     if plat.is_undefined break
  // 141:     inc &priority
  // 142:     !platform_priority(platform) priority
  // 143:     if plat == NONE break
  // 144:     !platform plat
  frame->slots[2] /* temp__1 */ = create_closure(entry__106_2, 0);
  // 137: do: (-> break)
  // 138:   forever:
  // 139:     $plat supported_platforms(platform)
  // 140:     if plat.is_undefined break
  // 141:     inc &priority
  // 142:     !platform_priority(platform) priority
  // 143:     if plat == NONE break
  // 144:     !platform plat
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__do();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__106_12(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 145: $$platform_specific_priority undefined
  var._platform_specific_priority = get__undefined();
  // 146: $$module_info empty_table
  var._module_info = get__empty_table();
  // 147: $$meta_levels empty_table # 0 -> no meta files
  var._meta_levels = get__empty_table();
  // 148: $$do_rebuild false
  var._do_rebuild = get__false();
  // 149: $$do_omit_meta false
  var._do_omit_meta = get__false();
  // 150: $$sim2c::do_dump_trees false
  var.sim2c__do_dump_trees = get__false();
  // 151: $$sim2c::do_pretty_print false
  var.sim2c__do_pretty_print = get__false();
  // 152: $$sim2c::do_print_simplified_source false
  var.sim2c__do_print_simplified_source = get__false();
  // 153: $$sim2c::do_show_debug_infos false
  var.sim2c__do_show_debug_infos = get__false();
  // 154: $$sim2c::do_show_compiler_debug_infos false
  var.sim2c__do_show_compiler_debug_infos = get__false();
  // 155: $$sim2c::do_check_only false
  var.sim2c__do_check_only = get__false();
  // 156: $$sim2c::do_show_brief_messages false
  var.sim2c__do_show_brief_messages = get__false();
  // 157: $$sim2c::do_print_warnings false
  var.sim2c__do_print_warnings = get__false();
  // 158: $$sim2c::verbose false
  var.sim2c__verbose = get__false();
  // 159: $$do_print_c false
  var._do_print_c = get__false();
  // 160: $$sim2c::do_extract_documentation false
  var.sim2c__do_extract_documentation = get__false();
  // 161: $$do_build_codeblocks_project false
  var._do_build_codeblocks_project = get__false();
  // 162: $$do_list_dependencies false
  var._do_list_dependencies = get__false();
  // 163: $$do_build_static false
  var._do_build_static = get__false();
  // 164: $$do_link_profiler false
  var._do_link_profiler = get__false();
  // 165: $$sim2c::do_time_passes false
  var.sim2c__do_time_passes = get__false();
  // 166: $$module_prefix undefined
  var._module_prefix = get__undefined();
  // 167: $$input_filename undefined
  var._input_filename = get__undefined();
  // 168: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__130_1;
}
static void cont__130_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 168: $action truncate_until(program_name '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__program_name();
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__130_2;
}
static void cont__130_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._action, arguments->slots[0]);
  // 170: action == "simrun"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._action;
  arguments->slots[1] = string__81_2;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__131_1;
}
static void cont__131_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 169: if
  // 170:   action == "simrun":
  // 171:     if command_line_arguments.is_empty: Error "Missing command line arguments!"
  // 172:     !input_filename command_line_arguments(1)
  // 173:   :
  // 174:     program_parameters
  // 175:       # the following options act on a single file only
  // 176:       
  // 177:       !sim2c::do_check_only
  // 178:       -> "check-only" "
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__131_2;
  arguments->slots[2] = func__131_8;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__131_70;
}
static void entry__131_2(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 171: ... command_line_arguments.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__command_line_arguments();
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__131_3;
}
static void cont__131_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 171: if command_line_arguments.is_empty: Error "Missing command line arguments!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__131_4;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__131_6;
}
static void entry__131_4(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 171: ... Error "Missing command line arguments!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__131_5;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__131_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 172: !input_filename command_line_arguments(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__command_line_arguments();
  func = myself->type;
  frame->cont = cont__131_7;
}
static void cont__131_7(void) {
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
static void entry__131_8(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 174: program_parameters
  // 175:   # the following options act on a single file only
  // 176:   
  // 177:   !sim2c::do_check_only
  // 178:   -> "check-only" "
  // 179:     do not compile; just check for syntax errors
  // 180:   !sim2c::do_dump_trees
  // 181:   -> "dump-trees" "
  // 182:     dump abstract syntax trees
  // 183:   !sim2c::do_pretty_print
  // ...
  argument_count = 20;
  arguments = node_p;
  arguments->slots[0] = func__131_9;
  arguments->slots[1] = func__131_12;
  arguments->slots[2] = func__131_15;
  arguments->slots[3] = func__131_18;
  arguments->slots[4] = func__131_21;
  arguments->slots[5] = func__131_24;
  arguments->slots[6] = func__131_27;
  arguments->slots[7] = func__131_30;
  arguments->slots[8] = func__131_33;
  arguments->slots[9] = func__131_36;
  arguments->slots[10] = func__131_39;
  arguments->slots[11] = func__131_42;
  arguments->slots[12] = func__131_45;
  arguments->slots[13] = func__131_48;
  arguments->slots[14] = func__131_51;
  arguments->slots[15] = func__131_54;
  arguments->slots[16] = func__131_57;
  arguments->slots[17] = func__131_60;
  arguments->slots[18] = func__131_63;
  arguments->slots[19] = func__131_66;
  result_count = 20;
  myself = get__program_parameters();
  func = myself->type;
  frame->cont = cont__131_69;
}
static void entry__131_9(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 178: -> "check-only" "
  // 179:   do not compile; just check for syntax errors
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__131_10;
  arguments->slots[1] = string__131_11;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__131_12(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 181: -> "dump-trees" "
  // 182:   dump abstract syntax trees
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__131_13;
  arguments->slots[1] = string__131_14;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__131_15(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 184: -> "pretty-print" "
  // 185:   do not compile; just pretty print the source file
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__131_16;
  arguments->slots[1] = string__131_17;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__131_18(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 187: -> "print-simplified-source" "
  // 188:   do not generate a C-file; just print the simplified source text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__131_19;
  arguments->slots[1] = string__131_20;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__131_21(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 190: -> "print-c" "
  // 191:   print C source code for a single module
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__131_22;
  arguments->slots[1] = string__131_23;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__131_24(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 193: -> "time-passes" "
  // 194:   print running time for the individual compiler passes
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__131_25;
  arguments->slots[1] = string__131_26;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__131_27(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 196: -> VALUED_OPTION "module-prefix" "
  // 197:   needed to compile a single file within a subdirectory;
  // 198:   if the subdirectories are nested use slashes to separate
  // 199:   the directory names
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__VALUED_OPTION();
  arguments->slots[1] = string__131_28;
  arguments->slots[2] = string__131_29;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__131_30(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 203: -> "brief" "
  // 204:   show brief error messages
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__131_31;
  arguments->slots[1] = string__131_32;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__131_33(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 206: -> "warnings" "
  // 207:   show warning messages
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__131_34;
  arguments->slots[1] = string__131_35;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__131_36(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 209: -> "verbose" "
  // 210:   output verbose informations
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__131_37;
  arguments->slots[1] = string__131_38;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__131_39(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 212: -> "debug" "
  // 213:   show C-compiler and linker calls
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__131_40;
  arguments->slots[1] = string__131_41;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__131_42(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 215: -> "debug_compiler" "
  // 216:   show internal debug messages of the Simplicity compiler
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__131_43;
  arguments->slots[1] = string__131_44;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__131_45(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 220: -> "codeblocks" "
  // 221:   create Code::Blocks project
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__131_46;
  arguments->slots[1] = string__131_47;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__131_48(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 223: -> "extract-documentation" "
  // 224:   extract documentation encoded as HTML
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__131_49;
  arguments->slots[1] = string__131_50;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__131_51(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 226: -> "list-dependencies" "
  // 227:   list all dependencies
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__131_52;
  arguments->slots[1] = string__131_53;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__131_54(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 231: -> "rebuild" "
  // 232:   rebuild all source files
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__131_55;
  arguments->slots[1] = string__131_56;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__131_57(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 234: -> "omit-meta" "
  // 235:   do not rebuild meta files
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__131_58;
  arguments->slots[1] = string__131_59;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__131_60(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 237: -> "static" "
  // 238:   create statically linked executable
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__131_61;
  arguments->slots[1] = string__131_62;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__131_63(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 240: -> "profile" "
  // 241:   link with libprofiler
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__131_64;
  arguments->slots[1] = string__131_65;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__131_66(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 243: -> std::MANDATORY_PARAMETER "filename" "
  // 244:   the name of the source file to compile
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__std__MANDATORY_PARAMETER();
  arguments->slots[1] = string__131_67;
  arguments->slots[2] = string__131_68;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__131_69(void) {
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
static void cont__131_70(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 245: %main_filename fullname(input_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._input_filename;
  result_count = 1;
  myself = get__fullname();
  func = myself->type;
  frame->cont = cont__132_1;
}
static void cont__132_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(get__main_filename(), arguments->slots[0]);
  // 246: %main_info stat(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__133_1;
}
static void cont__133_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(get__main_info(), arguments->slots[0]);
  // 247: %do_build_static_executable do_build_static
  initialize_future(get__do_build_static_executable(), var._do_build_static);
  // 248: if do_show_debug_infos: !verbose true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_show_debug_infos();
  arguments->slots[1] = func__135_1;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__135_2;
}
static void entry__135_1(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 248: ... !verbose true
  set__verbose(get__true());
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__135_2(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 256: %mode undefined # EXE or LIB
  initialize_maybe_future(get__mode(), get__undefined());
  // 257: $WHITESPACE many(' ')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__32;
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__140_1;
}
static void cont__140_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._WHITESPACE, arguments->slots[0]);
  // 259: $gcc_basic_options
  // 260:   list
  // 261:     "-Wall"
  // 262:     "-Wno-unused-function"
  // 263:     "-Wno-unused-variable"
  // 264:     "-Wno-parentheses"
  // 265:     "-Wno-switch"
  // 266:     "-Wno-maybe-uninitialized"
  // 267:     "-Wno-trigraphs"
  // 268:     "-O1"
  // ...
  argument_count = 11;
  arguments = node_p;
  arguments->slots[0] = string__141_1;
  arguments->slots[1] = string__141_2;
  arguments->slots[2] = string__141_3;
  arguments->slots[3] = string__141_4;
  arguments->slots[4] = string__141_5;
  arguments->slots[5] = string__141_6;
  arguments->slots[6] = string__141_7;
  arguments->slots[7] = string__141_8;
  arguments->slots[8] = string__141_9;
  arguments->slots[9] = string__141_10;
  arguments->slots[10] = string__141_11;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__141_12;
}
static void cont__141_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._gcc_basic_options, arguments->slots[0]);
  // 275: ... list("-msse2" "-mfpmath=sse")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__142_1;
  arguments->slots[1] = string__142_2;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__142_3;
}
static void cont__142_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 275: "x86_32" = list("-msse2" "-mfpmath=sse")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__142_4;
  arguments->slots[1] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__142_5;
}
static void cont__142_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 276: ... list("-msse2" "-mfpmath=sse")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__142_1;
  arguments->slots[1] = string__142_2;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__142_6;
}
static void cont__142_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 276: "x86_64" = list("-msse2" "-mfpmath=sse")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__142_7;
  arguments->slots[1] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__142_8;
}
static void cont__142_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 273: $gcc_hardware_specific_options
  // 274:   table
  // 275:     "x86_32" = list("-msse2" "-mfpmath=sse")
  // 276:     "x86_64" = list("-msse2" "-mfpmath=sse")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__table();
  func = myself->type;
  frame->cont = cont__142_9;
}
static void cont__142_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._gcc_hardware_specific_options, arguments->slots[0]);
  // 282: ... hardware_architecture()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__hardware_architecture();
  func = myself->type;
  frame->cont = cont__143_1;
}
static void cont__143_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 282: gcc_hardware_specific_options(hardware_architecture())
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = var._gcc_hardware_specific_options;
  func = myself->type;
  frame->cont = cont__143_2;
}
static void cont__143_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 281: default_value
  // 282:   gcc_hardware_specific_options(hardware_architecture())
  // 283:   empty_list
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  arguments->slots[1] = get__empty_list();
  result_count = 1;
  myself = get__default_value();
  func = myself->type;
  frame->cont = cont__143_3;
}
static void cont__143_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 278: $gcc_options
  // 279:   append
  // 280:     gcc_basic_options
  // 281:     default_value
  // 282:       gcc_hardware_specific_options(hardware_architecture())
  // 283:       empty_list
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._gcc_basic_options;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__143_4;
}
static void cont__143_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._gcc_options, arguments->slots[0]);
  // 285: %on_top_level true # set to false while building meta-files
  initialize_maybe_future(get__on_top_level(), get__true());
  // 286: %%objects empty_insert_order_set
  set__objects(get__empty_insert_order_set());
  // 287: %%libraries empty_insert_order_set # contains "-lsim-..."-entries
  set__libraries(get__empty_insert_order_set());
  // 288: %%do_link false
  set__do_link(get__false());
  // 289: %%last_modification_time undefined
  set__last_modification_time(get__undefined());
  // 290: $$c_sources empty_insert_order_set
  var._c_sources = get__empty_insert_order_set();
  // 291: $$dependencies empty_list
  var._dependencies = get__empty_list();
  // 292: $$resolved_libraries undefined
  var._resolved_libraries = get__undefined();
  // 621: ... main_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_info();
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__161_1;
}
static void cont__161_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 621: if main_info.is_undefined:
  // 622:   Error "
  // 623:     Source file "@(main_filename)" does not exist!@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__161_2;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__161_6;
}
static void entry__161_2(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 622: ... "
  // 623:   Source file "@(main_filename)" does not exist!@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__161_3;
  arguments->slots[1] = get__main_filename();
  arguments->slots[2] = string__161_4;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__161_5;
}
static void cont__161_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 622: Error "
  // 623:   Source file "@(main_filename)" does not exist!@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__161_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 928: $$t undefined
  var._t = get__undefined();
  // 1068: if do_time_passes: !t current_time()
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = func__176_1;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__176_3;
}
static void entry__176_1(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1068: ... !t current_time()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__current_time();
  func = myself->type;
  frame->cont = cont__176_2;
}
static void cont__176_2(void) {
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
static void cont__176_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1069: cond
  // 1070:   ->
  // 1071:     ||
  // 1072:       do_check_only
  // 1073:       do_dump_trees
  // 1074:       do_pretty_print
  // 1075:       do_print_simplified_source
  // 1076:     dump_source_or_check
  // 1077:   -> do_print_c print_c
  // 1078:   -> do_list_dependencies list_dependencies
  // ...
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = func__177_1;
  arguments->slots[1] = func__177_8;
  arguments->slots[2] = func__177_9;
  arguments->slots[3] = func__177_10;
  arguments->slots[4] = func__177_11;
  arguments->slots[5] = var._build_executable;
  result_count = 0;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__177_13;
}
static void entry__177_1(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_check_only();
  arguments->slots[1] = func__177_2;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__177_7;
}
static void entry__177_2(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_dump_trees();
  arguments->slots[1] = func__177_3;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__177_6;
}
static void entry__177_3(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_pretty_print();
  arguments->slots[1] = func__177_4;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__177_5;
}
static void entry__177_4(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1075: do_print_simplified_source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__do_print_simplified_source();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__177_5(void) {
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
static void cont__177_6(void) {
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
static void cont__177_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1070: ->
  // 1071:   ||
  // 1072:     do_check_only
  // 1073:     do_dump_trees
  // 1074:     do_pretty_print
  // 1075:     do_print_simplified_source
  // 1076:   dump_source_or_check
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = var._dump_source_or_check;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__177_8(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1077: -> do_print_c print_c
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_print_c;
  arguments->slots[1] = var._print_c;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__177_9(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1078: -> do_list_dependencies list_dependencies
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_list_dependencies;
  arguments->slots[1] = var._list_dependencies;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__177_10(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1079: -> do_build_codeblocks_project build_codeblocks_project
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_build_codeblocks_project;
  arguments->slots[1] = var._build_codeblocks_project;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__177_11(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1080: ... main_info.is_a_directory
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_info();
  result_count = 1;
  myself = get__is_a_directory();
  func = myself->type;
  frame->cont = cont__177_12;
}
static void cont__177_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1080: -> main_info.is_a_directory build_library
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = var._build_library;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__177_13(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = get__std__terminate();
  func = myself->type;
  frame->cont = cont__178_1;
}
static void cont__178_1(void) {
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
  // 251: ... ewriteln args*
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
  // 251: ... : ewriteln args*
  frame->slots[1] /* temp__1 */ = create_closure(entry__47_2, 0);
  // 251: if do_show_compiler_debug_infos: ewriteln args*
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_show_compiler_debug_infos();
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__63_1_resolve_filename(void) {
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
  // 295: ... resolved_libraries.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._resolved_libraries;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__63_2;
}
static void cont__63_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 295: if resolved_libraries.is_undefined:
  // 296:   !resolved_libraries empty_table
  // 297:   for_each simlibpaths: (path)
  // 298:     if file_exists(path):
  // 299:       for_each directory(path): (entry)
  // 300:         if entry.is_a_directory:
  // 301:           $name std::filename_of(entry)
  // 302:           if name .matches. NAME: !resolved_libraries(name) fullname_of(entry)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = func__63_3;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__63_16;
}
static void entry__63_13(void) {
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
  // 302: ... !resolved_libraries(name) fullname_of(entry)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* entry */;
  result_count = 1;
  myself = get__fullname_of();
  func = myself->type;
  frame->cont = cont__63_14;
}
static void cont__63_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 302: ... !resolved_libraries(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = var._resolved_libraries;
  func = myself->type;
  frame->cont = cont__63_15;
}
static void cont__63_15(void) {
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
static void entry__63_10(void) {
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
  // 301: $name std::filename_of(entry)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* entry */;
  result_count = 1;
  myself = get__std__filename_of();
  func = myself->type;
  frame->cont = cont__63_11;
}
static void cont__63_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* name */, arguments->slots[0]);
  // 302: ... name .matches. NAME
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* name */;
  arguments->slots[1] = get__NAME();
  result_count = 1;
  myself = get__matches();
  func = myself->type;
  frame->cont = cont__63_12;
}
static void cont__63_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 302: ... : !resolved_libraries(name) fullname_of(entry)
  frame->slots[3] /* temp__2 */ = create_closure(entry__63_13, 0);
  // 302: if name .matches. NAME: !resolved_libraries(name) fullname_of(entry)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__63_8(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // entry: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 300: ... entry.is_a_directory
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* entry */;
  result_count = 1;
  myself = get__is_a_directory();
  func = myself->type;
  frame->cont = cont__63_9;
}
static void cont__63_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 300: ... :
  // 301:   $name std::filename_of(entry)
  // 302:   if name .matches. NAME: !resolved_libraries(name) fullname_of(entry)
  frame->slots[2] /* temp__2 */ = create_closure(entry__63_10, 0);
  // 300: if entry.is_a_directory:
  // 301:   $name std::filename_of(entry)
  // 302:   if name .matches. NAME: !resolved_libraries(name) fullname_of(entry)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__63_6(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // path: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* path */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 299: ... directory(path)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* path */;
  result_count = 1;
  myself = get__directory();
  func = myself->type;
  frame->cont = cont__63_7;
}
static void cont__63_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 299: for_each directory(path): (entry)
  // 300:   if entry.is_a_directory:
  // 301:     $name std::filename_of(entry)
  // 302:     if name .matches. NAME: !resolved_libraries(name) fullname_of(entry)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__63_8;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__63_4(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // path: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 298: ... file_exists(path)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* path */;
  result_count = 1;
  myself = get__file_exists();
  func = myself->type;
  frame->cont = cont__63_5;
}
static void cont__63_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 298: ... :
  // 299:   for_each directory(path): (entry)
  // 300:     if entry.is_a_directory:
  // 301:       $name std::filename_of(entry)
  // 302:       if name .matches. NAME: !resolved_libraries(name) fullname_of(entry)
  frame->slots[2] /* temp__2 */ = create_closure(entry__63_6, 0);
  // 298: if file_exists(path):
  // 299:   for_each directory(path): (entry)
  // 300:     if entry.is_a_directory:
  // 301:       $name std::filename_of(entry)
  // 302:       if name .matches. NAME: !resolved_libraries(name) fullname_of(entry)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__63_3(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 296: !resolved_libraries empty_table
  var._resolved_libraries = get__empty_table();
  // 297: for_each simlibpaths: (path)
  // 298:   if file_exists(path):
  // 299:     for_each directory(path): (entry)
  // 300:       if entry.is_a_directory:
  // 301:         $name std::filename_of(entry)
  // 302:         if name .matches. NAME: !resolved_libraries(name) fullname_of(entry)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._simlibpaths;
  arguments->slots[1] = func__63_4;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__63_16(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 303: $libname filename .before. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__63_17;
}
static void cont__63_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* libname */, arguments->slots[0]);
  // 304: $libpath resolved_libraries(libname)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* libname */;
  result_count = 1;
  myself = var._resolved_libraries;
  func = myself->type;
  frame->cont = cont__63_18;
}
static void cont__63_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* libpath */, arguments->slots[0]);
  // 305: ... libpath.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* libpath */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__63_19;
}
static void cont__63_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 305: ... :
  // 306:   Error "
  // 307:     Cannot resolve required library "@(libname)@quot;!@
  frame->slots[4] /* temp__2 */ = create_closure(entry__63_20, 0);
  // 305: if libpath.is_undefined:
  // 306:   Error "
  // 307:     Cannot resolve required library "@(libname)@quot;!@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__63_24;
}
static void entry__63_20(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // libname: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* libname */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 306: ... "
  // 307:   Cannot resolve required library "@(libname)@quot;!@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__63_21;
  arguments->slots[1] = frame->slots[0] /* libname */;
  arguments->slots[2] = string__63_22;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__63_23;
}
static void cont__63_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 306: Error "
  // 307:   Cannot resolve required library "@(libname)@quot;!@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__63_24(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 308: ... filename .from. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__from();
  func = myself->type;
  frame->cont = cont__63_25;
}
static void cont__63_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 308: ... string(libpath filename .from. '/')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* libpath */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__63_26;
}
static void cont__63_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 308: -> string(libpath filename .from. '/')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__64_1_add_module_infos(void) {
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
  // 319: ... --SORT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__SORT();
  arguments->slots[1] = get__std__true();
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__64_2;
}
static void cont__64_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 319: $entries directory(--SORT path)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[0] /* path */;
  result_count = 1;
  myself = get__directory();
  func = myself->type;
  frame->cont = cont__64_3;
}
static void cont__64_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* entries */, arguments->slots[0]);
  // 320: $$filenames empty_set
  ((CELL *)frame->slots[4])->contents /* filenames */ = get__empty_set();
  // 321: $$directories empty_list
  ((CELL *)frame->slots[5])->contents /* directories */ = get__empty_list();
  // 322: $$modules empty_key_order_set
  ((CELL *)frame->slots[6])->contents /* modules */ = get__empty_key_order_set();
  // 323: ... : (entry)
  // 324:   $name std::filename_of(entry)
  // 325:   cond
  // 326:     -> entry.is_a_directory: if name .matches. NAME: push &directories name
  // 327:     -> name .has_suffix. ".sim":
  // 328:       $submodule_name name .without_suffix. (some(".meta"), ".sim")
  // 329:       !filenames(submodule_name) true
  // 330:       $meta_level (length_of(name)-length_of(submodule_name)-4)/5
  // 331:       $stored_level meta_levels(submodule_name)
  // 332:       if stored_level.is_undefined || meta_level > stored_level:
  // ...
  frame->slots[7] /* temp__1 */ = create_closure(entry__64_4, 1);
  // 323: for_each entries: (entry)
  // 324:   $name std::filename_of(entry)
  // 325:   cond
  // 326:     -> entry.is_a_directory: if name .matches. NAME: push &directories name
  // 327:     -> name .has_suffix. ".sim":
  // 328:       $submodule_name name .without_suffix. (some(".meta"), ".sim")
  // 329:       !filenames(submodule_name) true
  // 330:       $meta_level (length_of(name)-length_of(submodule_name)-4)/5
  // 331:       $stored_level meta_levels(submodule_name)
  // 332:       if stored_level.is_undefined || meta_level > stored_level:
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* entries */;
  arguments->slots[1] = frame->slots[7] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__64_38;
}
static void entry__64_15(void) {
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
  // 328: ... some(".meta")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__64_16;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__64_17;
}
static void cont__64_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__2 */ = arguments->slots[0];
  // 328: ... some(".meta"), ".sim"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__2 */;
  arguments->slots[1] = string__64_13;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__64_18;
}
static void cont__64_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 328: $submodule_name name .without_suffix. (some(".meta"), ".sim")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = get__without_suffix();
  func = myself->type;
  frame->cont = cont__64_19;
}
static void cont__64_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* submodule_name */, arguments->slots[0]);
  // 329: !filenames(submodule_name) true
  frame->slots[9] /* temp__1 */ = get__true();
  // 329: !filenames(submodule_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* submodule_name */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* filenames */;
  func = myself->type;
  frame->cont = cont__64_20;
}
static void cont__64_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* filenames */ = arguments->slots[0];
  // 330: ... length_of(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__64_21;
}
static void cont__64_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__3 */ = arguments->slots[0];
  // 330: ... length_of(submodule_name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* submodule_name */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__64_22;
}
static void cont__64_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__4 */ = arguments->slots[0];
  // 330: ... length_of(name)-length_of(submodule_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__3 */;
  arguments->slots[1] = frame->slots[12] /* temp__4 */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__64_23;
}
static void cont__64_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__2 */ = arguments->slots[0];
  // 330: ... length_of(name)-length_of(submodule_name)-4
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__2 */;
  arguments->slots[1] = number__4;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__64_24;
}
static void cont__64_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 330: $meta_level (length_of(name)-length_of(submodule_name)-4)/5
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__std__over();
  func = myself->type;
  frame->cont = cont__64_25;
}
static void cont__64_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* meta_level */, arguments->slots[0]);
  // 331: $stored_level meta_levels(submodule_name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* submodule_name */;
  result_count = 1;
  myself = var._meta_levels;
  func = myself->type;
  frame->cont = cont__64_26;
}
static void cont__64_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* stored_level */, arguments->slots[0]);
  // 332: ... stored_level.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* stored_level */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__64_27;
}
static void cont__64_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__2 */ = arguments->slots[0];
  // 332: ... meta_level > stored_level
  frame->slots[11] /* temp__3 */ = create_closure(entry__64_28, 0);
  // 332: ... stored_level.is_undefined || meta_level > stored_level
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__2 */;
  arguments->slots[1] = frame->slots[11] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__64_30;
}
static void entry__64_28(void) {
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
  // 332: ... meta_level > stored_level
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stored_level */;
  arguments->slots[1] = frame->slots[1] /* meta_level */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__64_29;
}
static void cont__64_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 332: ... meta_level > stored_level
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__64_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 332: ... :
  // 333:   !meta_levels(submodule_name) meta_level
  frame->slots[12] /* temp__4 */ = create_closure(entry__64_31, 0);
  // 332: if stored_level.is_undefined || meta_level > stored_level:
  // 333:   !meta_levels(submodule_name) meta_level
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = frame->slots[12] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__64_33;
}
static void entry__64_31(void) {
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
  // 333: !meta_levels(submodule_name) meta_level
  frame->slots[2] /* temp__1 */ = frame->slots[1] /* meta_level */;
  // 333: !meta_levels(submodule_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* submodule_name */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = var._meta_levels;
  func = myself->type;
  frame->cont = cont__64_32;
}
static void cont__64_32(void) {
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
static void cont__64_33(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 334: $basename submodule_name .truncate_from. '-'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* submodule_name */;
  arguments->slots[1] = character__45;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__64_34;
}
static void cont__64_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[7] /* basename */, arguments->slots[0]);
  // 335: !modules(basename) true
  frame->slots[9] /* temp__1 */ = get__true();
  // 335: !modules(basename)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* basename */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[2])->contents /* modules */;
  func = myself->type;
  frame->cont = cont__64_35;
}
static void cont__64_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* modules */ = arguments->slots[0];
  // 336: $mod_name string(mod_path basename)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* mod_path */;
  arguments->slots[1] = frame->slots[7] /* basename */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__64_36;
}
static void cont__64_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[8] /* mod_name */, arguments->slots[0]);
  // 337: !module_info(mod_name) empty_key_order_table
  frame->slots[9] /* temp__1 */ = get__empty_key_order_table();
  // 337: !module_info(mod_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* mod_name */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = var._module_info;
  func = myself->type;
  frame->cont = cont__64_37;
}
static void cont__64_37(void) {
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
static void entry__64_10(void) {
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
  // 326: ... push &directories name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* directories */;
  arguments->slots[1] = frame->slots[1] /* name */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__64_11;
}
static void cont__64_11(void) {
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
static void entry__64_8(void) {
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
  // 326: ... name .matches. NAME
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = get__NAME();
  result_count = 1;
  myself = get__matches();
  func = myself->type;
  frame->cont = cont__64_9;
}
static void cont__64_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 326: ... : push &directories name
  frame->slots[3] /* temp__2 */ = create_closure(entry__64_10, 0);
  // 326: ... if name .matches. NAME: push &directories name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__64_6(void) {
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
  // 326: ... entry.is_a_directory
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* entry */;
  result_count = 1;
  myself = get__is_a_directory();
  func = myself->type;
  frame->cont = cont__64_7;
}
static void cont__64_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 326: ... : if name .matches. NAME: push &directories name
  frame->slots[4] /* temp__2 */ = create_closure(entry__64_8, 0);
  // 326: -> entry.is_a_directory: if name .matches. NAME: push &directories name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__64_12(void) {
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
  // 327: ... name .has_suffix. ".sim"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = string__64_13;
  result_count = 1;
  myself = get__has_suffix();
  func = myself->type;
  frame->cont = cont__64_14;
}
static void cont__64_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 327: ... :
  // 328:   $submodule_name name .without_suffix. (some(".meta"), ".sim")
  // 329:   !filenames(submodule_name) true
  // 330:   $meta_level (length_of(name)-length_of(submodule_name)-4)/5
  // 331:   $stored_level meta_levels(submodule_name)
  // 332:   if stored_level.is_undefined || meta_level > stored_level:
  // 333:     !meta_levels(submodule_name) meta_level
  // 334:   $basename submodule_name .truncate_from. '-'
  // 335:   !modules(basename) true
  // 336:   $mod_name string(mod_path basename)
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__64_15, 0);
  // 327: -> name .has_suffix. ".sim":
  // 328:   $submodule_name name .without_suffix. (some(".meta"), ".sim")
  // 329:   !filenames(submodule_name) true
  // 330:   $meta_level (length_of(name)-length_of(submodule_name)-4)/5
  // 331:   $stored_level meta_levels(submodule_name)
  // 332:   if stored_level.is_undefined || meta_level > stored_level:
  // 333:     !meta_levels(submodule_name) meta_level
  // 334:   $basename submodule_name .truncate_from. '-'
  // 335:   !modules(basename) true
  // 336:   $mod_name string(mod_path basename)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__64_4(void) {
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
  // 324: $name std::filename_of(entry)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* entry */;
  result_count = 1;
  myself = get__std__filename_of();
  func = myself->type;
  frame->cont = cont__64_5;
}
static void cont__64_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* name */, arguments->slots[0]);
  // 326: -> entry.is_a_directory: if name .matches. NAME: push &directories name
  frame->slots[6] /* temp__1 */ = create_closure(entry__64_6, 0);
  // 327: -> name .has_suffix. ".sim":
  // 328:   $submodule_name name .without_suffix. (some(".meta"), ".sim")
  // 329:   !filenames(submodule_name) true
  // 330:   $meta_level (length_of(name)-length_of(submodule_name)-4)/5
  // 331:   $stored_level meta_levels(submodule_name)
  // 332:   if stored_level.is_undefined || meta_level > stored_level:
  // 333:     !meta_levels(submodule_name) meta_level
  // 334:   $basename submodule_name .truncate_from. '-'
  // 335:   !modules(basename) true
  // 336:   $mod_name string(mod_path basename)
  // ...
  frame->slots[7] /* temp__2 */ = create_closure(entry__64_12, 0);
  // 325: cond
  // 326:   -> entry.is_a_directory: if name .matches. NAME: push &directories name
  // 327:   -> name .has_suffix. ".sim":
  // 328:     $submodule_name name .without_suffix. (some(".meta"), ".sim")
  // 329:     !filenames(submodule_name) true
  // 330:     $meta_level (length_of(name)-length_of(submodule_name)-4)/5
  // 331:     $stored_level meta_levels(submodule_name)
  // 332:     if stored_level.is_undefined || meta_level > stored_level:
  // 333:       !meta_levels(submodule_name) meta_level
  // 334:     $basename submodule_name .truncate_from. '-'
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
static void cont__64_38(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 338: ... : (filename)
  // 339:   if filename .contains. '-':
  // 340:     unless filename .has_suffix. "-common":
  // 341:       $maybe_push_common: (plat)
  // 342:         $common_name string(name "-" plat "-common")
  // 343:         if filenames(common_name): push &files common_name
  // 344:       
  // 345:       $name filename .before. '-'
  // 346:       $mod_name string(mod_path name .truncate_from. '-')
  // 347:       $platform filename .behind. '-'
  // ...
  frame->slots[7] /* temp__1 */ = create_closure(entry__64_39, 1);
  // 338: for_each filenames: (filename)
  // 339:   if filename .contains. '-':
  // 340:     unless filename .has_suffix. "-common":
  // 341:       $maybe_push_common: (plat)
  // 342:         $common_name string(name "-" plat "-common")
  // 343:         if filenames(common_name): push &files common_name
  // 344:       
  // 345:       $name filename .before. '-'
  // 346:       $mod_name string(mod_path name .truncate_from. '-')
  // 347:       $platform filename .behind. '-'
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* filenames */;
  arguments->slots[1] = frame->slots[7] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__64_74;
}
static void entry__64_44(void) {
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
  // 341: ... : (plat)
  // 342:   $common_name string(name "-" plat "-common")
  // 343:   if filenames(common_name): push &files common_name
  frame->slots[9] /* temp__1 */ = create_closure(entry__64_45_maybe_push_common, 1);
  // 341: $maybe_push_common: (plat)
  // 342:   $common_name string(name "-" plat "-common")
  // 343:   if filenames(common_name): push &files common_name
  initialize_future(frame->slots[3] /* maybe_push_common */, frame->slots[9] /* temp__1 */);
  // 345: $name filename .before. '-'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* filename */;
  arguments->slots[1] = character__45;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__64_51;
}
static void entry__64_49(void) {
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
  // 343: ... push &files common_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* files */;
  arguments->slots[1] = frame->slots[1] /* common_name */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__64_50;
}
static void cont__64_50(void) {
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
static void entry__64_45_maybe_push_common(void) {
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
  // 342: $common_name string(name "-" plat "-common")
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* name */;
  arguments->slots[1] = string__64_46;
  arguments->slots[2] = frame->slots[0] /* plat */;
  arguments->slots[3] = string__64_42;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__64_47;
}
static void cont__64_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* common_name */, arguments->slots[0]);
  // 343: ... filenames(common_name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* common_name */;
  result_count = 1;
  myself = ((CELL *)frame->slots[2])->contents /* filenames */;
  func = myself->type;
  frame->cont = cont__64_48;
}
static void cont__64_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 343: ... : push &files common_name
  frame->slots[6] /* temp__2 */ = create_closure(entry__64_49, 0);
  // 343: if filenames(common_name): push &files common_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__64_51(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* name */, arguments->slots[0]);
  // 346: ... name .truncate_from. '-'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* name */;
  arguments->slots[1] = character__45;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__64_52;
}
static void cont__64_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 346: $mod_name string(mod_path name .truncate_from. '-')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* mod_path */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__64_53;
}
static void cont__64_53(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* mod_name */, arguments->slots[0]);
  // 347: $platform filename .behind. '-'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* filename */;
  arguments->slots[1] = character__45;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__64_54;
}
static void cont__64_54(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* platform */, arguments->slots[0]);
  // 348: $$parent supported_platforms(platform)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* platform */;
  result_count = 1;
  myself = var._supported_platforms;
  func = myself->type;
  frame->cont = cont__64_55;
}
static void cont__64_55(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[7])->contents /* parent */ = arguments->slots[0];
  // 349: ... parent.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[7])->contents /* parent */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__64_56;
}
static void cont__64_56(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 349: ... :
  // 350:   Error "
  // 351:     The platform "@(platform)" is not supported!@
  frame->slots[10] /* temp__2 */ = create_closure(entry__64_57, 0);
  // 349: unless parent.is_defined:
  // 350:   Error "
  // 351:     The platform "@(platform)" is not supported!@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__64_61;
}
static void entry__64_57(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // platform: 0
  frame->slots[0] = myself->closure.frame->slots[6]; /* platform */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 350: ... "
  // 351:   The platform "@(platform)" is not supported!@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__64_58;
  arguments->slots[1] = frame->slots[0] /* platform */;
  arguments->slots[2] = string__64_59;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__64_60;
}
static void cont__64_60(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 350: Error "
  // 351:   The platform "@(platform)" is not supported!@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__64_61(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 352: $$files list(filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* filename */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__64_62;
}
static void cont__64_62(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[8])->contents /* files */ = arguments->slots[0];
  // 353: maybe_push_common platform
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* platform */;
  result_count = 0;
  myself = frame->slots[3] /* maybe_push_common */;
  func = myself->type;
  frame->cont = cont__64_63;
}
static void cont__64_63(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 354: ... -> parent != NONE:
  // 355:   maybe_push_common parent
  // 356:   !parent supported_platforms(parent)
  frame->slots[9] /* temp__1 */ = create_closure(entry__64_64, 0);
  // 354: while -> parent != NONE:
  // 355:   maybe_push_common parent
  // 356:   !parent supported_platforms(parent)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  result_count = 0;
  myself = get__while();
  func = myself->type;
  frame->cont = cont__64_70;
}
static void entry__64_67(void) {
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
  // 355: maybe_push_common parent
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* parent */;
  result_count = 0;
  myself = frame->slots[0] /* maybe_push_common */;
  func = myself->type;
  frame->cont = cont__64_68;
}
static void cont__64_68(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 356: !parent supported_platforms(parent)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* parent */;
  result_count = 1;
  myself = var._supported_platforms;
  func = myself->type;
  frame->cont = cont__64_69;
}
static void cont__64_69(void) {
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
static void entry__64_64(void) {
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
  // 354: ... parent != NONE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parent */;
  arguments->slots[1] = var._NONE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__64_65;
}
static void cont__64_65(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 354: ... parent != NONE
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__64_66;
}
static void cont__64_66(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 354: ... :
  // 355:   maybe_push_common parent
  // 356:   !parent supported_platforms(parent)
  frame->slots[4] /* temp__3 */ = create_closure(entry__64_67, 0);
  // 354: ... -> parent != NONE:
  // 355:   maybe_push_common parent
  // 356:   !parent supported_platforms(parent)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__64_70(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 357: !module_info(mod_name)(platform) files
  frame->slots[9] /* temp__1 */ = ((CELL *)frame->slots[8])->contents /* files */;
  // 357: ... module_info(mod_name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* mod_name */;
  result_count = 1;
  myself = var._module_info;
  func = myself->type;
  frame->cont = cont__64_71;
}
static void cont__64_71(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__2 */ = arguments->slots[0];
  // 357: !module_info(mod_name)(platform)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* platform */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = frame->slots[10] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__64_72;
}
static void cont__64_72(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__2 */ = arguments->slots[0];
  // 357: !module_info(mod_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* mod_name */;
  arguments->slots[1] = frame->slots[10] /* temp__2 */;
  result_count = 1;
  myself = var._module_info;
  func = myself->type;
  frame->cont = cont__64_73;
}
static void cont__64_73(void) {
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
static void entry__64_41(void) {
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
  // 340: ... filename .has_suffix. "-common"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  arguments->slots[1] = string__64_42;
  result_count = 1;
  myself = get__has_suffix();
  func = myself->type;
  frame->cont = cont__64_43;
}
static void cont__64_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 340: ... :
  // 341:   $maybe_push_common: (plat)
  // 342:     $common_name string(name "-" plat "-common")
  // 343:     if filenames(common_name): push &files common_name
  // 344:   
  // 345:   $name filename .before. '-'
  // 346:   $mod_name string(mod_path name .truncate_from. '-')
  // 347:   $platform filename .behind. '-'
  // 348:   $$parent supported_platforms(platform)
  // 349:   unless parent.is_defined:
  // ...
  frame->slots[4] /* temp__2 */ = create_closure(entry__64_44, 0);
  // 340: unless filename .has_suffix. "-common":
  // 341:   $maybe_push_common: (plat)
  // 342:     $common_name string(name "-" plat "-common")
  // 343:     if filenames(common_name): push &files common_name
  // 344:   
  // 345:   $name filename .before. '-'
  // 346:   $mod_name string(mod_path name .truncate_from. '-')
  // 347:   $platform filename .behind. '-'
  // 348:   $$parent supported_platforms(platform)
  // 349:   unless parent.is_defined:
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
static void entry__64_39(void) {
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
  // 339: ... filename .contains. '-'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  arguments->slots[1] = character__45;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__64_40;
}
static void cont__64_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 339: ... :
  // 340:   unless filename .has_suffix. "-common":
  // 341:     $maybe_push_common: (plat)
  // 342:       $common_name string(name "-" plat "-common")
  // 343:       if filenames(common_name): push &files common_name
  // 344:     
  // 345:     $name filename .before. '-'
  // 346:     $mod_name string(mod_path name .truncate_from. '-')
  // 347:     $platform filename .behind. '-'
  // 348:     $$parent supported_platforms(platform)
  // ...
  frame->slots[4] /* temp__2 */ = create_closure(entry__64_41, 0);
  // 339: if filename .contains. '-':
  // 340:   unless filename .has_suffix. "-common":
  // 341:     $maybe_push_common: (plat)
  // 342:       $common_name string(name "-" plat "-common")
  // 343:       if filenames(common_name): push &files common_name
  // 344:     
  // 345:     $name filename .before. '-'
  // 346:     $mod_name string(mod_path name .truncate_from. '-')
  // 347:     $platform filename .behind. '-'
  // 348:     $$parent supported_platforms(platform)
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
static void cont__64_74(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 358: ... parameter_count_of(return)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* return */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__64_75;
}
static void cont__64_75(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 358: ... parameter_count_of(return) == 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__2 */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__64_76;
}
static void cont__64_76(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 358: ... : return directories modules
  frame->slots[9] /* temp__3 */ = create_closure(entry__64_77, 0);
  // 358: if parameter_count_of(return) == 2: return directories modules
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__64_78;
}
static void entry__64_77(void) {
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
  // 358: ... return directories modules
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* directories */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* modules */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__64_78(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__65_4(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // info: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 369: ... -> info
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__65_5(void) {
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
  // 370: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__65_6;
}
static void cont__65_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 370: ... before(mod_filename '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__65_7;
}
static void cont__65_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 370: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__65_8;
}
static void cont__65_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 370: ... until(mod_name '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* mod_name */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = get__until();
  func = myself->type;
  frame->cont = cont__65_9;
}
static void cont__65_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 370: add_module_infos before(mod_filename '/' -1) until(mod_name '/' -1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 0;
  myself = var._add_module_infos;
  func = myself->type;
  frame->cont = cont__65_10;
}
static void cont__65_10(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 371: ... module_info(mod_name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* mod_name */;
  result_count = 1;
  myself = var._module_info;
  func = myself->type;
  frame->cont = cont__65_11;
}
static void cont__65_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 371: -> module_info(mod_name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__65_1_lookup(void) {
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
  // 368: $info module_info(mod_name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* mod_name */;
  result_count = 1;
  myself = var._module_info;
  func = myself->type;
  frame->cont = cont__65_2;
}
static void cont__65_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* info */, arguments->slots[0]);
  // 369: ... info.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* info */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__65_3;
}
static void cont__65_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 369: ... -> info
  frame->slots[4] /* temp__2 */ = create_closure(entry__65_4, 0);
  // 369: ... :
  // 370:   add_module_infos before(mod_filename '/' -1) until(mod_name '/' -1)
  // 371:   -> module_info(mod_name)
  frame->slots[5] /* temp__3 */ = create_closure(entry__65_5, 0);
  // 369: if info.is_defined (-> info):
  // 370:   add_module_infos before(mod_filename '/' -1) until(mod_name '/' -1)
  // 371:   -> module_info(mod_name)
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
static void entry__66_1_Gcc(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // args: 0
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 374: ... : ewriteln "gcc " join(args)
  frame->slots[1] /* temp__1 */ = create_closure(entry__66_2, 0);
  // 374: if do_show_debug_infos: ewriteln "gcc " join(args)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_show_debug_infos();
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__66_5;
}
static void entry__66_2(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // args: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* args */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 374: ... join(args)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* args */;
  result_count = 1;
  myself = get__join();
  func = myself->type;
  frame->cont = cont__66_3;
}
static void cont__66_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 374: ... ewriteln "gcc " join(args)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__66_4;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__66_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 375: gcc args*
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = frame->caller_result_count;
  myself = var._gcc;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__67_4(void) {
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
  // 379: Gcc $_out $err $success gcc_options* "-c" c_filename "-o" o_filename
  argument_count = 0;
  arguments = node_p;
  unfold(var._gcc_options);
  arguments->slots[argument_count++] = string__67_5;
  arguments->slots[argument_count++] = frame->slots[0] /* c_filename */;
  arguments->slots[argument_count++] = string__67_6;
  arguments->slots[argument_count++] = frame->slots[1] /* o_filename */;
  result_count = 3;
  myself = var._Gcc;
  func = myself->type;
  frame->cont = cont__67_7;
}
static void cont__67_7(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  frame->slots[6] /* temp__2 */ = arguments->slots[1];
  frame->slots[7] /* temp__3 */ = arguments->slots[2];
  // 379: ... _out
  initialize_future(frame->slots[2] /* out */, frame->slots[5] /* temp__1 */);
  // 379: ... err
  initialize_future(frame->slots[3] /* err */, frame->slots[6] /* temp__2 */);
  // 379: ... success
  initialize_future(frame->slots[4] /* success */, frame->slots[7] /* temp__3 */);
  // 380: ... :
  // 381:   Error "
  // 382:     Failed to compile @(c_filename)
  // 383:     @(err.from_utf8)
  frame->slots[5] /* temp__1 */ = create_closure(entry__67_8, 0);
  // 380: unless success:
  // 381:   Error "
  // 382:     Failed to compile @(c_filename)
  // 383:     @(err.from_utf8)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* success */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__67_13;
}
static void entry__67_8(void) {
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
  // 383: ... err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* err */;
  result_count = 1;
  myself = get__from_utf8();
  func = myself->type;
  frame->cont = cont__67_9;
}
static void cont__67_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 381: ... "
  // 382:   Failed to compile @(c_filename)
  // 383:   @(err.from_utf8)
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__67_10;
  arguments->slots[1] = frame->slots[0] /* c_filename */;
  arguments->slots[2] = string__67_11;
  arguments->slots[3] = frame->slots[3] /* temp__2 */;
  arguments->slots[4] = string__67_11;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__67_12;
}
static void cont__67_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 381: Error "
  // 382:   Failed to compile @(c_filename)
  // 383:   @(err.from_utf8)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__67_13(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 384: !do_link true
  set__do_link(get__true());
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__67_1_compile_c(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // c_filename: 0
  // o_filename: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 378: ... do_build_codeblocks_project || do_list_dependencies
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_build_codeblocks_project;
  arguments->slots[1] = func__67_2;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__67_3;
}
static void entry__67_2(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 378: ... do_list_dependencies
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._do_list_dependencies;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__67_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 378: ... :
  // 379:   Gcc $_out $err $success gcc_options* "-c" c_filename "-o" o_filename
  // 380:   unless success:
  // 381:     Error "
  // 382:       Failed to compile @(c_filename)
  // 383:       @(err.from_utf8)
  // 384:   !do_link true
  frame->slots[3] /* temp__2 */ = create_closure(entry__67_4, 0);
  // 378: unless do_build_codeblocks_project || do_list_dependencies:
  // 379:   Gcc $_out $err $success gcc_options* "-c" c_filename "-o" o_filename
  // 380:   unless success:
  // 381:     Error "
  // 382:       Failed to compile @(c_filename)
  // 383:       @(err.from_utf8)
  // 384:   !do_link true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__68_2(void) {
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
  // 396: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__68_3;
}
static void cont__68_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 396: $meta_path truncate_from(mod_filename '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[11] /* temp__1 */;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__68_4;
}
static void cont__68_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* meta_path */, arguments->slots[0]);
  // 397: ... dup(".meta" meta_level)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__64_16;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* meta_level */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__68_5;
}
static void cont__68_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 397: $filename string(mod_filename dup(".meta" meta_level))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = frame->slots[11] /* temp__1 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__68_6;
}
static void cont__68_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* filename */, arguments->slots[0]);
  // 398: $meta_filename string(filename ".sim")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* filename */;
  arguments->slots[1] = string__64_13;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__68_7;
}
static void cont__68_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* meta_filename */, arguments->slots[0]);
  // 399: ... dup(".meta" meta_level)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__64_16;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* meta_level */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__68_8;
}
static void cont__68_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 399: $meta_c_filename string(mod_filename dup(".meta" meta_level) ".c")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = frame->slots[11] /* temp__1 */;
  arguments->slots[2] = string__68_9;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__68_10;
}
static void cont__68_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* meta_c_filename */, arguments->slots[0]);
  // 400: ... meta_level-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* meta_level */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__68_11;
}
static void cont__68_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__2 */ = arguments->slots[0];
  // 400: ... dup(".meta" meta_level-1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__64_16;
  arguments->slots[1] = frame->slots[12] /* temp__2 */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__68_12;
}
static void cont__68_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 400: $sim_filename string(mod_filename dup(".meta" meta_level-1) ".sim")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = frame->slots[11] /* temp__1 */;
  arguments->slots[2] = string__64_13;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__68_13;
}
static void cont__68_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* sim_filename */, arguments->slots[0]);
  // 401: $meta_info stat(meta_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* meta_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__68_14;
}
static void cont__68_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[7] /* meta_info */, arguments->slots[0]);
  // 402: $sim_info stat(sim_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* sim_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__68_15;
}
static void cont__68_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[8] /* sim_info */, arguments->slots[0]);
  // 403: $meta_c_info stat(meta_c_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* meta_c_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__68_16;
}
static void cont__68_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[9] /* meta_c_info */, arguments->slots[0]);
  frame->slots[11] /* temp__1 */ = create_closure(entry__68_17, 0);
  // 405: $$force_rebuild
  // 406:   ||
  // 407:     do_rebuild
  // 408:     sim_info.is_undefined
  // 409:     meta_c_info.is_undefined
  // 410:     modification_time_of(meta_info) > modification_time_of(meta_c_info)
  // 411:     modification_time_of(meta_c_info) > modification_time_of(sim_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_rebuild;
  arguments->slots[1] = frame->slots[11] /* temp__1 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__68_32;
}
static void entry__68_17(void) {
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
  // 408: sim_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* sim_info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__68_18;
}
static void cont__68_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  frame->slots[5] /* temp__3 */ = create_closure(entry__68_19, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__68_31;
}
static void entry__68_19(void) {
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
  // 409: meta_c_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* meta_c_info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__68_20;
}
static void cont__68_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  frame->slots[5] /* temp__3 */ = create_closure(entry__68_21, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__68_30;
}
static void entry__68_21(void) {
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
  // 410: ... modification_time_of(meta_c_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* meta_c_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__68_22;
}
static void cont__68_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 410: modification_time_of(meta_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* meta_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__68_23;
}
static void cont__68_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__4 */ = arguments->slots[0];
  // 410: modification_time_of(meta_info) > modification_time_of(meta_c_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__68_24;
}
static void cont__68_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 411: modification_time_of(meta_c_info) > modification_time_of(sim_info)
  frame->slots[7] /* temp__5 */ = create_closure(entry__68_25, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__5 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__68_29;
}
static void entry__68_25(void) {
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
  // 411: ... modification_time_of(sim_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* sim_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__68_26;
}
static void cont__68_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 411: modification_time_of(meta_c_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* meta_c_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__68_27;
}
static void cont__68_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 411: modification_time_of(meta_c_info) > modification_time_of(sim_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__68_28;
}
static void cont__68_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 411: modification_time_of(meta_c_info) > modification_time_of(sim_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__68_29(void) {
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
static void cont__68_30(void) {
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
static void cont__68_31(void) {
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
static void cont__68_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[10])->contents /* force_rebuild */ = arguments->slots[0];
  // 413: ... :
  // 414:   $modification_time modification_time_of(sim_info)
  // 415:   load $meta_c_buf meta_c_filename
  // 416:   do: (-> break)
  // 417:     for_each_line meta_c_buf: ($line)
  // 418:       $check: (data_filename)
  // 419:         $data_info stat(data_filename)
  // 420:         if
  // 421:           ||
  // 422:             data_info.is_undefined
  // ...
  frame->slots[11] /* temp__1 */ = create_closure(entry__68_33, 0);
  // 413: unless force_rebuild:
  // 414:   $modification_time modification_time_of(sim_info)
  // 415:   load $meta_c_buf meta_c_filename
  // 416:   do: (-> break)
  // 417:     for_each_line meta_c_buf: ($line)
  // 418:       $check: (data_filename)
  // 419:         $data_info stat(data_filename)
  // 420:         if
  // 421:           ||
  // 422:             data_info.is_undefined
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[10])->contents /* force_rebuild */;
  arguments->slots[1] = frame->slots[11] /* temp__1 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__68_66;
}
static void entry__68_36(void) {
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
  // 417: ... : ($line)
  // 418:   $check: (data_filename)
  // 419:     $data_info stat(data_filename)
  // 420:     if
  // 421:       ||
  // 422:         data_info.is_undefined
  // 423:         modification_time_of(data_info) > modification_time
  // 424:       :
  // 425:         !force_rebuild true
  // 426:         break
  // ...
  frame->slots[5] /* temp__1 */ = create_closure(entry__68_37, 1);
  // 417: for_each_line meta_c_buf: ($line)
  // 418:   $check: (data_filename)
  // 419:     $data_info stat(data_filename)
  // 420:     if
  // 421:       ||
  // 422:         data_info.is_undefined
  // 423:         modification_time_of(data_info) > modification_time
  // 424:       :
  // 425:         !force_rebuild true
  // 426:         break
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* meta_c_buf */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each_line();
  func = myself->type;
  frame->cont = cont__68_65;
}
static void entry__68_63(void) {
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
  // 438: ... string(path '/' argument)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* path */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[2] /* argument */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__68_64;
}
static void cont__68_64(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 438: ... check string(path '/' argument)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* check */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__68_58(void) {
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
  // 436: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__68_59;
}
static void cont__68_59(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 436: ... range(argument 2 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* argument */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__68_60;
}
static void cont__68_60(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 436: ... string(meta_path range(argument 2 -1))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* meta_path */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__68_61;
}
static void cont__68_61(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 436: check string(meta_path range(argument 2 -1))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* check */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__68_62(void) {
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
  // 438: ... : (path) check string(path '/' argument)
  frame->slots[2] /* temp__1 */ = create_closure(entry__68_63, 1);
  // 438: for_each simdatapaths: (path) check string(path '/' argument)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._simdatapaths;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__68_55(void) {
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
  // 435: argument .has_prefix. "./"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* argument */;
  arguments->slots[1] = string__68_56;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__68_57;
}
static void cont__68_57(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 435: ... :
  // 436:   check string(meta_path range(argument 2 -1))
  frame->slots[4] /* temp__2 */ = create_closure(entry__68_58, 0);
  // 437: :
  // 438:   for_each simdatapaths: (path) check string(path '/' argument)
  frame->slots[5] /* temp__3 */ = create_closure(entry__68_62, 0);
  // 434: if
  // 435:   argument .has_prefix. "./":
  // 436:     check string(meta_path range(argument 2 -1))
  // 437:   :
  // 438:     for_each simdatapaths: (path) check string(path '/' argument)
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
static void entry__68_37(void) {
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
  // 418: ... : (data_filename)
  // 419:   $data_info stat(data_filename)
  // 420:   if
  // 421:     ||
  // 422:       data_info.is_undefined
  // 423:       modification_time_of(data_info) > modification_time
  // 424:     :
  // 425:       !force_rebuild true
  // 426:       break
  frame->slots[8] /* temp__1 */ = create_closure(entry__68_38_check, 1);
  // 418: $check: (data_filename)
  // 419:   $data_info stat(data_filename)
  // 420:   if
  // 421:     ||
  // 422:       data_info.is_undefined
  // 423:       modification_time_of(data_info) > modification_time
  // 424:     :
  // 425:       !force_rebuild true
  // 426:       break
  initialize_future(frame->slots[5] /* check */, frame->slots[8] /* temp__1 */);
  // 428: ... line .has_prefix. "/// "
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  arguments->slots[1] = string__68_46;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__68_47;
}
static void entry__68_45(void) {
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
  // 425: !force_rebuild true
  ((CELL *)frame->slots[0])->contents /* force_rebuild */ = get__true();
  // 426: break
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* break */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__68_38_check(void) {
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
  // 419: $data_info stat(data_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* data_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__68_39;
}
static void cont__68_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* data_info */, arguments->slots[0]);
  // 422: data_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* data_info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__68_40;
}
static void cont__68_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 423: modification_time_of(data_info) > modification_time
  frame->slots[7] /* temp__3 */ = create_closure(entry__68_41, 0);
  // 421: ||
  // 422:   data_info.is_undefined
  // 423:   modification_time_of(data_info) > modification_time
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__68_44;
}
static void entry__68_41(void) {
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
  // 423: modification_time_of(data_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* data_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__68_42;
}
static void cont__68_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 423: modification_time_of(data_info) > modification_time
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* modification_time */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__68_43;
}
static void cont__68_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 423: modification_time_of(data_info) > modification_time
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__68_44(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 424: :
  // 425:   !force_rebuild true
  // 426:   break
  frame->slots[8] /* temp__4 */ = create_closure(entry__68_45, 0);
  // 420: if
  // 421:   ||
  // 422:     data_info.is_undefined
  // 423:     modification_time_of(data_info) > modification_time
  // 424:   :
  // 425:     !force_rebuild true
  // 426:     break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__68_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 428: unless line .has_prefix. "/// " break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* break */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__68_48;
}
static void cont__68_48(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 429: behind &line ' '
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  arguments->slots[1] = character__32;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__68_49;
}
static void cont__68_49(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* line */ = arguments->slots[0];
  // 430: trim &line
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__68_50;
}
static void cont__68_50(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* line */ = arguments->slots[0];
  // 431: $command line .truncate_from. WHITESPACE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  arguments->slots[1] = var._WHITESPACE;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__68_51;
}
static void cont__68_51(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* command */, arguments->slots[0]);
  // 432: $argument line .behind. WHITESPACE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  arguments->slots[1] = var._WHITESPACE;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__68_52;
}
static void cont__68_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[7] /* argument */, arguments->slots[0]);
  // 433: ... command == "data"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* command */;
  arguments->slots[1] = string__68_53;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__68_54;
}
static void cont__68_54(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 433: ... :
  // 434:   if
  // 435:     argument .has_prefix. "./":
  // 436:       check string(meta_path range(argument 2 -1))
  // 437:     :
  // 438:       for_each simdatapaths: (path) check string(path '/' argument)
  frame->slots[9] /* temp__2 */ = create_closure(entry__68_55, 0);
  // 433: if command == "data":
  // 434:   if
  // 435:     argument .has_prefix. "./":
  // 436:       check string(meta_path range(argument 2 -1))
  // 437:     :
  // 438:       for_each simdatapaths: (path) check string(path '/' argument)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__68_65(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__68_33(void) {
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
  // 414: $modification_time modification_time_of(sim_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* sim_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__68_34;
}
static void cont__68_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* modification_time */, arguments->slots[0]);
  // 415: load $meta_c_buf meta_c_filename
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* meta_c_filename */;
  result_count = 1;
  myself = get__load();
  func = myself->type;
  frame->cont = cont__68_35;
}
static void cont__68_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* meta_c_buf */, arguments->slots[0]);
  // 416: ... : (-> break)
  // 417:   for_each_line meta_c_buf: ($line)
  // 418:     $check: (data_filename)
  // 419:       $data_info stat(data_filename)
  // 420:       if
  // 421:         ||
  // 422:           data_info.is_undefined
  // 423:           modification_time_of(data_info) > modification_time
  // 424:         :
  // 425:           !force_rebuild true
  // ...
  frame->slots[6] /* temp__1 */ = create_closure(entry__68_36, 0);
  // 416: do: (-> break)
  // 417:   for_each_line meta_c_buf: ($line)
  // 418:     $check: (data_filename)
  // 419:       $data_info stat(data_filename)
  // 420:       if
  // 421:         ||
  // 422:           data_info.is_undefined
  // 423:           modification_time_of(data_info) > modification_time
  // 424:         :
  // 425:           !force_rebuild true
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__do();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__68_66(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 439: ... :
  // 440:   %on_top_level false
  // 441:   %%objects empty_insert_order_set
  // 442:   %%libraries empty_insert_order_set
  // 443:   %%do_link false
  // 444:   %%last_modification_time undefined
  // 445:   %do_build_static_executable false
  // 446:   %main_filename meta_filename
  // 447:   %main_info stat(main_filename)
  // 448:   build_executable
  // ...
  frame->slots[11] /* temp__1 */ = create_closure(entry__68_67, 0);
  // 439: if force_rebuild:
  // 440:   %on_top_level false
  // 441:   %%objects empty_insert_order_set
  // 442:   %%libraries empty_insert_order_set
  // 443:   %%do_link false
  // 444:   %%last_modification_time undefined
  // 445:   %do_build_static_executable false
  // 446:   %main_filename meta_filename
  // 447:   %main_info stat(main_filename)
  // 448:   build_executable
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[10])->contents /* force_rebuild */;
  arguments->slots[1] = frame->slots[11] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__68_79;
}
static void entry__68_67(void) {
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
  // 440: %on_top_level false
  initialize_maybe_future(get__on_top_level(), get__false());
  // 441: %%objects empty_insert_order_set
  set__objects(get__empty_insert_order_set());
  // 442: %%libraries empty_insert_order_set
  set__libraries(get__empty_insert_order_set());
  // 443: %%do_link false
  set__do_link(get__false());
  // 444: %%last_modification_time undefined
  set__last_modification_time(get__undefined());
  // 445: %do_build_static_executable false
  initialize_maybe_future(get__do_build_static_executable(), get__false());
  // 446: %main_filename meta_filename
  initialize_maybe_future(get__main_filename(), frame->slots[1] /* meta_filename */);
  // 447: %main_info stat(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__68_68;
}
static void cont__68_68(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(get__main_info(), arguments->slots[0]);
  // 448: build_executable
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._build_executable;
  func = myself->type;
  frame->cont = cont__68_69;
}
static void cont__68_69(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 449: $orig_path current_path()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__current_path();
  func = myself->type;
  frame->cont = cont__68_70;
}
static void cont__68_70(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* orig_path */, arguments->slots[0]);
  // 450: change_directory meta_path
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* meta_path */;
  result_count = 0;
  myself = get__change_directory();
  func = myself->type;
  frame->cont = cont__68_71;
}
static void cont__68_71(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 451: std::call $out $err $success filename
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* filename */;
  result_count = 3;
  myself = get__std__call();
  func = myself->type;
  frame->cont = cont__68_72;
}
static void cont__68_72(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  frame->slots[10] /* temp__2 */ = arguments->slots[1];
  frame->slots[11] /* temp__3 */ = arguments->slots[2];
  // 451: ... out
  initialize_future(frame->slots[6] /* out */, frame->slots[9] /* temp__1 */);
  // 451: ... err
  initialize_future(frame->slots[7] /* err */, frame->slots[10] /* temp__2 */);
  // 451: ... success
  initialize_future(frame->slots[8] /* success */, frame->slots[11] /* temp__3 */);
  // 452: change_directory orig_path
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* orig_path */;
  result_count = 0;
  myself = get__change_directory();
  func = myself->type;
  frame->cont = cont__68_73;
}
static void cont__68_73(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 453: ... : Error err.from_utf8
  frame->slots[9] /* temp__1 */ = create_closure(entry__68_74, 0);
  // 453: unless success: Error err.from_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* success */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__68_76;
}
static void entry__68_74(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // err: 0
  frame->slots[0] = myself->closure.frame->slots[7]; /* err */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 453: ... err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* err */;
  result_count = 1;
  myself = get__from_utf8();
  func = myself->type;
  frame->cont = cont__68_75;
}
static void cont__68_75(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 453: ... Error err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__68_76(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 454: ... out.to_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* out */;
  result_count = 1;
  myself = get__to_utf8();
  func = myself->type;
  frame->cont = cont__68_77;
}
static void cont__68_77(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 454: save sim_filename out.to_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* sim_filename */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__save();
  func = myself->type;
  frame->cont = cont__68_78;
}
static void cont__68_78(void) {
  myself = frame->slots[0] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__68_79(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 455: dec &meta_level
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* meta_level */;
  result_count = 1;
  myself = get__dec();
  func = myself->type;
  frame->cont = cont__68_80;
}
static void cont__68_80(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* meta_level */ = arguments->slots[0];
  // 456: ... meta_level > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* meta_level */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__68_81;
}
static void cont__68_81(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 456: -> meta_level > 0
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__68_1_compile_meta_module(void) {
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
  // 395: ... :
  // 396:   $meta_path truncate_from(mod_filename '/' -1)
  // 397:   $filename string(mod_filename dup(".meta" meta_level))
  // 398:   $meta_filename string(filename ".sim")
  // 399:   $meta_c_filename string(mod_filename dup(".meta" meta_level) ".c")
  // 400:   $sim_filename string(mod_filename dup(".meta" meta_level-1) ".sim")
  // 401:   $meta_info stat(meta_filename)
  // 402:   $sim_info stat(sim_filename)
  // 403:   $meta_c_info stat(meta_c_filename)
  // 404:   
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__68_2, 0);
  // 395: do_while:
  // 396:   $meta_path truncate_from(mod_filename '/' -1)
  // 397:   $filename string(mod_filename dup(".meta" meta_level))
  // 398:   $meta_filename string(filename ".sim")
  // 399:   $meta_c_filename string(mod_filename dup(".meta" meta_level) ".c")
  // 400:   $sim_filename string(mod_filename dup(".meta" meta_level-1) ".sim")
  // 401:   $meta_info stat(meta_filename)
  // 402:   $sim_info stat(sim_filename)
  // 403:   $meta_c_info stat(meta_c_filename)
  // 404:   
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__do_while();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__69_1_build_dependencies(void) {
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
  // 469: ... : ($line)
  // 470:   unless line .has_prefix. "/// " return
  // 471:   behind &line ' '
  // 472:   trim &line
  // 473:   $command line .truncate_from. WHITESPACE
  // 474:   $argument line .behind. WHITESPACE
  // 475:   case
  // 476:     command
  // 477:     "require":
  // 478:       if
  // ...
  frame->slots[5] /* temp__1 */ = create_closure(entry__69_2, 1);
  // 469: for_each_line c_buf: ($line)
  // 470:   unless line .has_prefix. "/// " return
  // 471:   behind &line ' '
  // 472:   trim &line
  // 473:   $command line .truncate_from. WHITESPACE
  // 474:   $argument line .behind. WHITESPACE
  // 475:   case
  // 476:     command
  // 477:     "require":
  // 478:       if
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* c_buf */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each_line();
  func = myself->type;
  frame->cont = cont__69_41;
}
static void entry__69_36(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // argument: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 497: ... !libraries(argument .truncate_from. '/') true
  frame->slots[1] /* temp__1 */ = get__true();
  // 497: ... argument .truncate_from. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* argument */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__69_37;
}
static void cont__69_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 497: ... !libraries(argument .truncate_from. '/')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__libraries();
  func = myself->type;
  frame->cont = cont__69_38;
}
static void cont__69_38(void) {
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
static void entry__69_30(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // argument: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 495: !libraries(string("sim-" argument .truncate_from. '/')) true
  frame->slots[1] /* temp__1 */ = get__true();
  // 495: ... argument .truncate_from. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* argument */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__69_31;
}
static void cont__69_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 495: ... string("sim-" argument .truncate_from. '/')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__69_32;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__69_33;
}
static void cont__69_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 495: !libraries(string("sim-" argument .truncate_from. '/'))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__libraries();
  func = myself->type;
  frame->cont = cont__69_34;
}
static void cont__69_34(void) {
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
static void entry__69_27(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // argument: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 492: ... resolve_filename(argument)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* argument */;
  result_count = 1;
  myself = var._resolve_filename;
  func = myself->type;
  frame->cont = cont__69_28;
}
static void cont__69_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 492: compile_module resolve_filename(argument) argument
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[0] /* argument */;
  result_count = frame->caller_result_count;
  myself = var._compile_module;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__69_29(void) {
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
  // 494: ... :
  // 495:   !libraries(string("sim-" argument .truncate_from. '/')) true
  frame->slots[2] /* temp__1 */ = create_closure(entry__69_30, 0);
  // 494: if do_compile_c:
  // 495:   !libraries(string("sim-" argument .truncate_from. '/')) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* do_compile_c */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__69_13(void) {
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
  // 481: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__69_14;
}
static void cont__69_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 481: $req_name range(argument 3 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* argument */;
  arguments->slots[1] = number__3;
  arguments->slots[2] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__69_15;
}
static void cont__69_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* req_name */, arguments->slots[0]);
  // 483: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__69_16;
}
static void cont__69_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 483: ... until(mod_filename '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* mod_filename */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count = 1;
  myself = get__until();
  func = myself->type;
  frame->cont = cont__69_17;
}
static void cont__69_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 483: string(until(mod_filename '/' -1) req_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* req_name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__69_18;
}
static void cont__69_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 484: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__69_19;
}
static void cont__69_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__6 */ = arguments->slots[0];
  // 484: ... until(mod_name '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* mod_name */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[9] /* temp__6 */;
  result_count = 1;
  myself = get__until();
  func = myself->type;
  frame->cont = cont__69_20;
}
static void cont__69_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__5 */ = arguments->slots[0];
  // 484: string(until(mod_name '/' -1) req_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__5 */;
  arguments->slots[1] = frame->slots[3] /* req_name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__69_21;
}
static void cont__69_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__4 */ = arguments->slots[0];
  // 482: compile_module
  // 483:   string(until(mod_filename '/' -1) req_name)
  // 484:   string(until(mod_name '/' -1) req_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = var._compile_module;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__69_11(void) {
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
  // 480: ... mode == EXE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__mode();
  arguments->slots[1] = var._EXE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__69_12;
}
static void cont__69_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 480: ... :
  // 481:   $req_name range(argument 3 -1)
  // 482:   compile_module
  // 483:     string(until(mod_filename '/' -1) req_name)
  // 484:     string(until(mod_name '/' -1) req_name)
  frame->slots[4] /* temp__2 */ = create_closure(entry__69_13, 0);
  // 480: if mode == EXE:
  // 481:   $req_name range(argument 3 -1)
  // 482:   compile_module
  // 483:     string(until(mod_filename '/' -1) req_name)
  // 484:     string(until(mod_name '/' -1) req_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__69_22(void) {
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
  arguments->slots[1] = func__69_23;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__69_26;
}
static void entry__69_23(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_build_codeblocks_project;
  arguments->slots[1] = func__69_24;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__69_25;
}
static void entry__69_24(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 490: do_list_dependencies
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._do_list_dependencies;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__69_25(void) {
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
static void cont__69_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 491: :
  // 492:   compile_module resolve_filename(argument) argument
  frame->slots[3] /* temp__2 */ = create_closure(entry__69_27, 0);
  // 493: :
  // 494:   if do_compile_c:
  // 495:     !libraries(string("sim-" argument .truncate_from. '/')) true
  frame->slots[4] /* temp__3 */ = create_closure(entry__69_29, 0);
  // 486: if
  // 487:   ||
  // 488:     do_build_static_executable
  // 489:     do_build_codeblocks_project
  // 490:     do_list_dependencies
  // 491:   :
  // 492:     compile_module resolve_filename(argument) argument
  // 493:   :
  // 494:     if do_compile_c:
  // 495:       !libraries(string("sim-" argument .truncate_from. '/')) true
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
static void entry__69_9(void) {
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
  // 479: argument .has_prefix. "./"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* argument */;
  arguments->slots[1] = string__68_56;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__69_10;
}
static void cont__69_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 479: ... :
  // 480:   if mode == EXE:
  // 481:     $req_name range(argument 3 -1)
  // 482:     compile_module
  // 483:       string(until(mod_filename '/' -1) req_name)
  // 484:       string(until(mod_name '/' -1) req_name)
  frame->slots[5] /* temp__2 */ = create_closure(entry__69_11, 0);
  // 485: :
  // 486:   if
  // 487:     ||
  // 488:       do_build_static_executable
  // 489:       do_build_codeblocks_project
  // 490:       do_list_dependencies
  // 491:     :
  // 492:       compile_module resolve_filename(argument) argument
  // 493:     :
  // 494:       if do_compile_c:
  // ...
  frame->slots[6] /* temp__3 */ = create_closure(entry__69_22, 0);
  // 478: if
  // 479:   argument .has_prefix. "./":
  // 480:     if mode == EXE:
  // 481:       $req_name range(argument 3 -1)
  // 482:       compile_module
  // 483:         string(until(mod_filename '/' -1) req_name)
  // 484:         string(until(mod_name '/' -1) req_name)
  // 485:   :
  // 486:     if
  // 487:       ||
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
static void entry__69_35(void) {
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
  // 497: ... : !libraries(argument .truncate_from. '/') true
  frame->slots[2] /* temp__1 */ = create_closure(entry__69_36, 0);
  // 497: if do_compile_c: !libraries(argument .truncate_from. '/') true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* do_compile_c */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__69_2(void) {
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
  // 470: ... line .has_prefix. "/// "
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  arguments->slots[1] = string__68_46;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__69_3;
}
static void cont__69_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 470: unless line .has_prefix. "/// " return
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* return */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__69_4;
}
static void cont__69_4(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 471: behind &line ' '
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  arguments->slots[1] = character__32;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__69_5;
}
static void cont__69_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* line */ = arguments->slots[0];
  // 472: trim &line
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__69_6;
}
static void cont__69_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* line */ = arguments->slots[0];
  // 473: $command line .truncate_from. WHITESPACE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  arguments->slots[1] = var._WHITESPACE;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__69_7;
}
static void cont__69_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* command */, arguments->slots[0]);
  // 474: $argument line .behind. WHITESPACE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  arguments->slots[1] = var._WHITESPACE;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__69_8;
}
static void cont__69_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* argument */, arguments->slots[0]);
  // 477: ... :
  // 478:   if
  // 479:     argument .has_prefix. "./":
  // 480:       if mode == EXE:
  // 481:         $req_name range(argument 3 -1)
  // 482:         compile_module
  // 483:           string(until(mod_filename '/' -1) req_name)
  // 484:           string(until(mod_name '/' -1) req_name)
  // 485:     :
  // 486:       if
  // ...
  frame->slots[7] /* temp__1 */ = create_closure(entry__69_9, 0);
  // 496: ... :
  // 497:   if do_compile_c: !libraries(argument .truncate_from. '/') true
  frame->slots[8] /* temp__2 */ = create_closure(entry__69_35, 0);
  // 475: case
  // 476:   command
  // 477:   "require":
  // 478:     if
  // 479:       argument .has_prefix. "./":
  // 480:         if mode == EXE:
  // 481:           $req_name range(argument 3 -1)
  // 482:           compile_module
  // 483:             string(until(mod_filename '/' -1) req_name)
  // 484:             string(until(mod_name '/' -1) req_name)
  // ...
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* command */;
  arguments->slots[1] = string__69_39;
  arguments->slots[2] = frame->slots[7] /* temp__1 */;
  arguments->slots[3] = string__69_40;
  arguments->slots[4] = frame->slots[8] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__69_41(void) {
  myself = frame->slots[4] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__70_1_compile_module(void) {
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
  // 508: ... :
  // 509:   (
  // 510:     submodule_names # no paths; no extensions
  // 511:     do_compile_c = true
  // 512:     suffix = "" # a hyphen followed by the platform name
  // 513:   )
  // 514:   $$modification_time undefined
  // 515:   $$sim_filenames empty_list
  // 516:   for_each submodule_names: (submodule_name)
  // 517:     $meta_level meta_levels(submodule_name)
  // ...
  frame->slots[6] /* temp__1 */ = create_closure(entry__70_2_compile_submodule, -1);
  // 508: $compile_submodule:
  // 509:   (
  // 510:     submodule_names # no paths; no extensions
  // 511:     do_compile_c = true
  // 512:     suffix = "" # a hyphen followed by the platform name
  // 513:   )
  // 514:   $$modification_time undefined
  // 515:   $$sim_filenames empty_list
  // 516:   for_each submodule_names: (submodule_name)
  // 517:     $meta_level meta_levels(submodule_name)
  // ...
  initialize_future(frame->slots[3] /* compile_submodule */, frame->slots[6] /* temp__1 */);
  // 564: lookup $mod_info mod_filename mod_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = frame->slots[1] /* mod_name */;
  result_count = 1;
  myself = var._lookup;
  func = myself->type;
  frame->cont = cont__70_73;
}
static void entry__70_2_compile_submodule(void) {
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
  // 514: $$modification_time undefined
  ((CELL *)frame->slots[6])->contents /* modification_time */ = get__undefined();
  // 515: $$sim_filenames empty_list
  ((CELL *)frame->slots[7])->contents /* sim_filenames */ = get__empty_list();
  // 516: ... : (submodule_name)
  // 517:   $meta_level meta_levels(submodule_name)
  // 518:   $submodule_filename string(until(mod_filename '/' -1) submodule_name)
  // 519:   if meta_level > 0 && not(do_omit_meta):
  // 520:     compile_meta_module submodule_filename submodule_name meta_level
  // 521:   $sim_filename string(submodule_filename ".sim")
  // 522:   push &sim_filenames sim_filename
  // 523:   $sim_info stat(sim_filename)
  // 524:   if
  // 525:     ||
  // ...
  frame->slots[11] /* temp__1 */ = create_closure(entry__70_3, 1);
  // 516: for_each submodule_names: (submodule_name)
  // 517:   $meta_level meta_levels(submodule_name)
  // 518:   $submodule_filename string(until(mod_filename '/' -1) submodule_name)
  // 519:   if meta_level > 0 && not(do_omit_meta):
  // 520:     compile_meta_module submodule_filename submodule_name meta_level
  // 521:   $sim_filename string(submodule_filename ".sim")
  // 522:   push &sim_filenames sim_filename
  // 523:   $sim_info stat(sim_filename)
  // 524:   if
  // 525:     ||
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* submodule_names */;
  arguments->slots[1] = frame->slots[11] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__70_24;
}
static void entry__70_22(void) {
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
  // 529: !modification_time modification_time_of(sim_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* sim_info */;
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
  ((CELL *)frame->slots[0])->contents /* modification_time */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__70_3(void) {
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
  // 517: $meta_level meta_levels(submodule_name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* submodule_name */;
  result_count = 1;
  myself = var._meta_levels;
  func = myself->type;
  frame->cont = cont__70_4;
}
static void cont__70_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* meta_level */, arguments->slots[0]);
  // 518: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__70_5;
}
static void cont__70_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__2 */ = arguments->slots[0];
  // 518: ... until(mod_filename '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* mod_filename */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[9] /* temp__2 */;
  result_count = 1;
  myself = get__until();
  func = myself->type;
  frame->cont = cont__70_6;
}
static void cont__70_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 518: $submodule_filename string(until(mod_filename '/' -1) submodule_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = frame->slots[0] /* submodule_name */;
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
  initialize_future(frame->slots[5] /* submodule_filename */, arguments->slots[0]);
  // 519: ... meta_level > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = frame->slots[4] /* meta_level */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__70_8;
}
static void cont__70_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__2 */ = arguments->slots[0];
  // 519: ... meta_level > 0 && not(do_omit_meta)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__2 */;
  arguments->slots[1] = func__70_9;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__70_11;
}
static void entry__70_9(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 519: ... not(do_omit_meta)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._do_omit_meta;
  result_count = 1;
  myself = get__not();
  func = myself->type;
  frame->cont = cont__70_10;
}
static void cont__70_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 519: ... not(do_omit_meta)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__70_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 519: ... :
  // 520:   compile_meta_module submodule_filename submodule_name meta_level
  frame->slots[10] /* temp__3 */ = create_closure(entry__70_12, 0);
  // 519: if meta_level > 0 && not(do_omit_meta):
  // 520:   compile_meta_module submodule_filename submodule_name meta_level
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__70_13;
}
static void entry__70_12(void) {
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
  // 520: compile_meta_module submodule_filename submodule_name meta_level
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
static void cont__70_13(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 521: $sim_filename string(submodule_filename ".sim")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* submodule_filename */;
  arguments->slots[1] = string__64_13;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__70_14;
}
static void cont__70_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* sim_filename */, arguments->slots[0]);
  // 522: push &sim_filenames sim_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* sim_filenames */;
  arguments->slots[1] = frame->slots[6] /* sim_filename */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__70_15;
}
static void cont__70_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* sim_filenames */ = arguments->slots[0];
  // 523: $sim_info stat(sim_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* sim_filename */;
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
  initialize_future(frame->slots[7] /* sim_info */, arguments->slots[0]);
  // 526: modification_time.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* modification_time */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__70_17;
}
static void cont__70_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__2 */ = arguments->slots[0];
  // 527: modification_time_of(sim_info) > modification_time
  frame->slots[10] /* temp__3 */ = create_closure(entry__70_18, 0);
  // 525: ||
  // 526:   modification_time.is_undefined
  // 527:   modification_time_of(sim_info) > modification_time
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__2 */;
  arguments->slots[1] = frame->slots[10] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__70_21;
}
static void entry__70_18(void) {
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
  // 527: modification_time_of(sim_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* sim_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__70_19;
}
static void cont__70_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 527: modification_time_of(sim_info) > modification_time
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* modification_time */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__70_20;
}
static void cont__70_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 527: modification_time_of(sim_info) > modification_time
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__70_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 528: :
  // 529:   !modification_time modification_time_of(sim_info)
  frame->slots[11] /* temp__4 */ = create_closure(entry__70_22, 0);
  // 524: if
  // 525:   ||
  // 526:     modification_time.is_undefined
  // 527:     modification_time_of(sim_info) > modification_time
  // 528:   :
  // 529:     !modification_time modification_time_of(sim_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = frame->slots[11] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__70_24(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 530: $c_filename string(mod_filename suffix ".c")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* mod_filename */;
  arguments->slots[1] = frame->slots[2] /* suffix */;
  arguments->slots[2] = string__68_9;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__70_25;
}
static void cont__70_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[8] /* c_filename */, arguments->slots[0]);
  // 531: $c_info stat(c_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* c_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__70_26;
}
static void cont__70_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[9] /* c_info */, arguments->slots[0]);
  // 532: ... : !c_sources(c_filename) true
  frame->slots[11] /* temp__1 */ = create_closure(entry__70_27, 0);
  // 532: if do_compile_c: !c_sources(c_filename) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* do_compile_c */;
  arguments->slots[1] = frame->slots[11] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__70_29;
}
static void entry__70_27(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // c_filename: 0
  frame->slots[0] = myself->closure.frame->slots[8]; /* c_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 532: ... !c_sources(c_filename) true
  frame->slots[1] /* temp__1 */ = get__true();
  // 532: ... !c_sources(c_filename)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_filename */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = var._c_sources;
  func = myself->type;
  frame->cont = cont__70_28;
}
static void cont__70_28(void) {
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
static void cont__70_29(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 533: $$c_buf undefined
  ((CELL *)frame->slots[10])->contents /* c_buf */ = get__undefined();
  frame->slots[12] /* temp__2 */ = create_closure(entry__70_30, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_rebuild;
  arguments->slots[1] = frame->slots[12] /* temp__2 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__70_36;
}
static void entry__70_30(void) {
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
  // 537: c_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__70_31;
}
static void cont__70_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 538: modification_time > modification_time_of(c_info)
  frame->slots[4] /* temp__3 */ = create_closure(entry__70_32, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__70_35;
}
static void entry__70_32(void) {
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
  // 538: ... modification_time_of(c_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__70_33;
}
static void cont__70_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 538: modification_time > modification_time_of(c_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* modification_time */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__70_34;
}
static void cont__70_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 538: modification_time > modification_time_of(c_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__70_35(void) {
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
static void cont__70_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 539: :
  // 540:   %sim2c::module_name replace_all(mod_name '/' = "__" '.' = "__")
  // 541:   if verbose: ewriteln "build module " module_name suffix
  // 542:   collect_output $c_source: sim2c sim_filenames
  // 543:   collect_output !c_buf: create_imports c_source
  // 544:   save c_filename c_buf.to_utf8
  // 545:   if do_compile_c: compile_c c_filename o_filename
  frame->slots[13] /* temp__3 */ = create_closure(entry__70_37, 0);
  // 546: :
  // 547:   load !c_buf c_filename
  // 548:   $o_info stat(o_filename)
  // 549:   if
  // 550:     ||
  // 551:       o_info.is_undefined
  // 552:       modification_time_of(c_info) > modification_time_of(o_info)
  // 553:     :
  // 554:       if do_compile_c: compile_c c_filename o_filename
  // 555:     :
  // ...
  frame->slots[14] /* temp__4 */ = create_closure(entry__70_53, 0);
  // 534: if
  // 535:   ||
  // 536:     do_rebuild
  // 537:     c_info.is_undefined
  // 538:     modification_time > modification_time_of(c_info)
  // 539:   :
  // 540:     %sim2c::module_name replace_all(mod_name '/' = "__" '.' = "__")
  // 541:     if verbose: ewriteln "build module " module_name suffix
  // 542:     collect_output $c_source: sim2c sim_filenames
  // 543:     collect_output !c_buf: create_imports c_source
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  arguments->slots[1] = frame->slots[13] /* temp__3 */;
  arguments->slots[2] = frame->slots[14] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__70_72;
}
static void entry__70_70(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // o_info: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* o_info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 561: !last_modification_time modification_time_of(o_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* o_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__70_71;
}
static void cont__70_71(void) {
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
static void entry__70_63(void) {
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
  // 554: ... compile_c c_filename o_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_filename */;
  arguments->slots[1] = frame->slots[1] /* o_filename */;
  result_count = frame->caller_result_count;
  myself = var._compile_c;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__70_62(void) {
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
  // 554: ... : compile_c c_filename o_filename
  frame->slots[3] /* temp__1 */ = create_closure(entry__70_63, 0);
  // 554: if do_compile_c: compile_c c_filename o_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* do_compile_c */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__70_64(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // o_info: 0
  frame->slots[0] = myself->closure.frame->slots[5]; /* o_info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 558: last_modification_time.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__last_modification_time();
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__70_65;
}
static void cont__70_65(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 559: modification_time_of(o_info) > last_modification_time
  frame->slots[3] /* temp__3 */ = create_closure(entry__70_66, 0);
  // 557: ||
  // 558:   last_modification_time.is_undefined
  // 559:   modification_time_of(o_info) > last_modification_time
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__70_69;
}
static void entry__70_66(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // o_info: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* o_info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 559: modification_time_of(o_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* o_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__70_67;
}
static void cont__70_67(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 559: modification_time_of(o_info) > last_modification_time
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__last_modification_time();
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__70_68;
}
static void cont__70_68(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 559: modification_time_of(o_info) > last_modification_time
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__70_69(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 560: :
  // 561:   !last_modification_time modification_time_of(o_info)
  frame->slots[4] /* temp__4 */ = create_closure(entry__70_70, 0);
  // 556: if
  // 557:   ||
  // 558:     last_modification_time.is_undefined
  // 559:     modification_time_of(o_info) > last_modification_time
  // 560:   :
  // 561:     !last_modification_time modification_time_of(o_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__70_37(void) {
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
  // 540: ... '/' = "__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = string__70_38;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__70_39;
}
static void cont__70_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 540: ... '.' = "__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__46;
  arguments->slots[1] = string__70_38;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__70_40;
}
static void cont__70_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__2 */ = arguments->slots[0];
  // 540: %sim2c::module_name replace_all(mod_name '/' = "__" '.' = "__")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* mod_name */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  arguments->slots[2] = frame->slots[10] /* temp__2 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__70_41;
}
static void cont__70_41(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(get__sim2c__module_name(), arguments->slots[0]);
  // 541: ... : ewriteln "build module " module_name suffix
  frame->slots[9] /* temp__1 */ = create_closure(entry__70_42, 0);
  // 541: if verbose: ewriteln "build module " module_name suffix
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__70_44;
}
static void entry__70_42(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // suffix: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* suffix */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 541: ... ewriteln "build module " module_name suffix
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__70_43;
  arguments->slots[1] = get__module_name();
  arguments->slots[2] = frame->slots[0] /* suffix */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__70_44(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 542: ... : sim2c sim_filenames
  frame->slots[9] /* temp__1 */ = create_closure(entry__70_45, 0);
  // 542: collect_output $c_source: sim2c sim_filenames
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__70_46;
}
static void entry__70_45(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // sim_filenames: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* sim_filenames */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 542: ... sim2c sim_filenames
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* sim_filenames */;
  result_count = frame->caller_result_count;
  myself = get__sim2c();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__70_46(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[8] /* c_source */, arguments->slots[0]);
  // 543: ... : create_imports c_source
  frame->slots[9] /* temp__1 */ = create_closure(entry__70_47, 0);
  // 543: collect_output !c_buf: create_imports c_source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__70_48;
}
static void entry__70_47(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // c_source: 0
  frame->slots[0] = myself->closure.frame->slots[8]; /* c_source */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 543: ... create_imports c_source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_source */;
  result_count = frame->caller_result_count;
  myself = var._create_imports;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__70_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* c_buf */ = arguments->slots[0];
  // 544: ... c_buf.to_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* c_buf */;
  result_count = 1;
  myself = get__to_utf8();
  func = myself->type;
  frame->cont = cont__70_49;
}
static void cont__70_49(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 544: save c_filename c_buf.to_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* c_filename */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 0;
  myself = get__save();
  func = myself->type;
  frame->cont = cont__70_50;
}
static void cont__70_50(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 545: ... : compile_c c_filename o_filename
  frame->slots[9] /* temp__1 */ = create_closure(entry__70_51, 0);
  // 545: if do_compile_c: compile_c c_filename o_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* do_compile_c */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__70_52;
}
static void entry__70_51(void) {
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
  // 545: ... compile_c c_filename o_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_filename */;
  arguments->slots[1] = frame->slots[1] /* o_filename */;
  result_count = frame->caller_result_count;
  myself = var._compile_c;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__70_52(void) {
  myself = frame->slots[0] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__70_53(void) {
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
  // 547: load !c_buf c_filename
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* c_filename */;
  result_count = 1;
  myself = get__load();
  func = myself->type;
  frame->cont = cont__70_54;
}
static void cont__70_54(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* c_buf */ = arguments->slots[0];
  // 548: $o_info stat(o_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* o_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__70_55;
}
static void cont__70_55(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* o_info */, arguments->slots[0]);
  // 551: o_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* o_info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__70_56;
}
static void cont__70_56(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 552: modification_time_of(c_info) > modification_time_of(o_info)
  frame->slots[8] /* temp__3 */ = create_closure(entry__70_57, 0);
  // 550: ||
  // 551:   o_info.is_undefined
  // 552:   modification_time_of(c_info) > modification_time_of(o_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  arguments->slots[1] = frame->slots[8] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__70_61;
}
static void entry__70_57(void) {
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
  // 552: ... modification_time_of(o_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* o_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__70_58;
}
static void cont__70_58(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 552: modification_time_of(c_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* c_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__70_59;
}
static void cont__70_59(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 552: modification_time_of(c_info) > modification_time_of(o_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__70_60;
}
static void cont__70_60(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 552: modification_time_of(c_info) > modification_time_of(o_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__70_61(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 553: :
  // 554:   if do_compile_c: compile_c c_filename o_filename
  frame->slots[9] /* temp__4 */ = create_closure(entry__70_62, 0);
  // 555: :
  // 556:   if
  // 557:     ||
  // 558:       last_modification_time.is_undefined
  // 559:       modification_time_of(o_info) > last_modification_time
  // 560:     :
  // 561:       !last_modification_time modification_time_of(o_info)
  frame->slots[10] /* temp__5 */ = create_closure(entry__70_64, 0);
  // 549: if
  // 550:   ||
  // 551:     o_info.is_undefined
  // 552:     modification_time_of(c_info) > modification_time_of(o_info)
  // 553:   :
  // 554:     if do_compile_c: compile_c c_filename o_filename
  // 555:   :
  // 556:     if
  // 557:       ||
  // 558:         last_modification_time.is_undefined
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
static void cont__70_72(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 562: build_dependencies mod_filename mod_name c_buf do_compile_c
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
static void cont__70_73(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* mod_info */, arguments->slots[0]);
  // 565: ... mod_info.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* mod_info */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__70_74;
}
static void cont__70_74(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 565: ... :
  // 566:   Error "
  // 567:     No source file(s) for module "@(mod_name)" found!@
  frame->slots[7] /* temp__2 */ = create_closure(entry__70_75, 0);
  // 565: unless mod_info.is_defined:
  // 566:   Error "
  // 567:     No source file(s) for module "@(mod_name)" found!@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__70_79;
}
static void entry__70_75(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // mod_name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* mod_name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 566: ... "
  // 567:   No source file(s) for module "@(mod_name)" found!@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__70_76;
  arguments->slots[1] = frame->slots[0] /* mod_name */;
  arguments->slots[2] = string__70_77;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__70_78;
}
static void cont__70_78(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 566: Error "
  // 567:   No source file(s) for module "@(mod_name)" found!@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__70_79(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 568: $o_filename append(mod_filename ".o")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = string__70_80;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__70_81;
}
static void cont__70_81(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* o_filename */, arguments->slots[0]);
  // 569: ... objects(o_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* o_filename */;
  result_count = 1;
  myself = get__objects();
  func = myself->type;
  frame->cont = cont__70_82;
}
static void cont__70_82(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 569: if objects(o_filename) return
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* return */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__70_83;
}
static void cont__70_83(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 570: !objects(o_filename) true
  frame->slots[6] /* temp__1 */ = get__true();
  // 570: !objects(o_filename)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* o_filename */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = get__objects();
  func = myself->type;
  frame->cont = cont__70_84;
}
static void cont__70_84(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__objects(arguments->slots[0]);
  // 572: mod_info.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* mod_info */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__70_85;
}
static void cont__70_85(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 572: ... :
  // 573:   compile_submodule list(truncate_until(mod_name '/' -1))
  // 574:   if do_list_dependencies: push &dependencies string(mod_filename ".c")
  frame->slots[7] /* temp__2 */ = create_closure(entry__70_86, 0);
  // 575: :
  // 576:   do:
  // 577:     $$best_platform undefined
  // 578:     $$best_priority 999
  // 579:     for_each mod_info: (platform _filenames)
  // 580:       $priority platform_priority(platform)
  // 581:       if priority.is_defined && priority < best_priority:
  // 582:         !best_platform platform
  // 583:         !best_priority priority
  // 584:     for_each mod_info: (platform filenames)
  // ...
  frame->slots[8] /* temp__3 */ = create_closure(entry__70_94, 0);
  // 571: if
  // 572:   mod_info.is_empty:
  // 573:     compile_submodule list(truncate_until(mod_name '/' -1))
  // 574:     if do_list_dependencies: push &dependencies string(mod_filename ".c")
  // 575:   :
  // 576:     do:
  // 577:       $$best_platform undefined
  // 578:       $$best_priority 999
  // 579:       for_each mod_info: (platform _filenames)
  // 580:         $priority platform_priority(platform)
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  arguments->slots[2] = frame->slots[8] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__70_135;
}
static void entry__70_125(void) {
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
  // 604: $$dependency string(mod_filename "-" platform ".c")
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* mod_filename */;
  arguments->slots[1] = string__64_46;
  arguments->slots[2] = frame->slots[0] /* platform */;
  arguments->slots[3] = string__68_9;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__70_126;
}
static void cont__70_126(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* dependency */ = arguments->slots[0];
  // 605: $platforms used_by(platform)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* platform */;
  result_count = 1;
  myself = ((CELL *)frame->slots[3])->contents /* used_by */;
  func = myself->type;
  frame->cont = cont__70_127;
}
static void cont__70_127(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* platforms */, arguments->slots[0]);
  // 606: ... platforms.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* platforms */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__70_128;
}
static void cont__70_128(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 606: ... :
  // 607:   for_each platforms: (plat) write_to &dependency " #" plat
  frame->slots[7] /* temp__2 */ = create_closure(entry__70_129, 0);
  // 606: if platforms.is_defined:
  // 607:   for_each platforms: (plat) write_to &dependency " #" plat
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__70_133;
}
static void entry__70_130(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // plat: 0
  // dependency: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* dependency */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 607: ... write_to &dependency " #" plat
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* dependency */;
  arguments->slots[1] = string__70_131;
  arguments->slots[2] = frame->slots[0] /* plat */;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__70_132;
}
static void cont__70_132(void) {
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
static void entry__70_129(void) {
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
  // 607: ... : (plat) write_to &dependency " #" plat
  frame->slots[2] /* temp__1 */ = create_closure(entry__70_130, 1);
  // 607: for_each platforms: (plat) write_to &dependency " #" plat
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* platforms */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__70_133(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 608: push &dependencies dependency
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._dependencies;
  arguments->slots[1] = ((CELL *)frame->slots[4])->contents /* dependency */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__70_134;
}
static void cont__70_134(void) {
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
static void entry__70_108(void) {
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
  // 590: $$used_by empty_table
  ((CELL *)frame->slots[2])->contents /* used_by */ = get__empty_table();
  // 591: ... : (supported_platform _parent_platform)
  // 592:   $$best_platform undefined
  // 593:   $$best_priority 999
  // 594:   for_each mod_info: (platform _filenames)
  // 595:     $priority platform_specific_priority(supported_platform platform)
  // 596:     if priority.is_defined && priority < best_priority:
  // 597:       !best_platform platform
  // 598:       !best_priority priority
  // 599:   if best_platform.is_defined:
  // 600:     $$ub default_value(used_by(best_platform) empty_list)
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__70_109, 2);
  // 591: for_each supported_platforms: (supported_platform _parent_platform)
  // 592:   $$best_platform undefined
  // 593:   $$best_priority 999
  // 594:   for_each mod_info: (platform _filenames)
  // 595:     $priority platform_specific_priority(supported_platform platform)
  // 596:     if priority.is_defined && priority < best_priority:
  // 597:       !best_platform platform
  // 598:       !best_priority priority
  // 599:   if best_platform.is_defined:
  // 600:     $$ub default_value(used_by(best_platform) empty_list)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._supported_platforms;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__70_124;
}
static void entry__70_119(void) {
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
  // 600: ... used_by(best_platform)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* best_platform */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* used_by */;
  func = myself->type;
  frame->cont = cont__70_120;
}
static void cont__70_120(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 600: $$ub default_value(used_by(best_platform) empty_list)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = get__empty_list();
  result_count = 1;
  myself = get__default_value();
  func = myself->type;
  frame->cont = cont__70_121;
}
static void cont__70_121(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* ub */ = arguments->slots[0];
  // 601: push &ub supported_platform
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* ub */;
  arguments->slots[1] = frame->slots[2] /* supported_platform */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__70_122;
}
static void cont__70_122(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* ub */ = arguments->slots[0];
  // 602: !used_by(best_platform) ub
  frame->slots[4] /* temp__1 */ = ((CELL *)frame->slots[3])->contents /* ub */;
  // 602: !used_by(best_platform)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* best_platform */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* used_by */;
  func = myself->type;
  frame->cont = cont__70_123;
}
static void cont__70_123(void) {
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
static void entry__70_109(void) {
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
  // 592: $$best_platform undefined
  ((CELL *)frame->slots[4])->contents /* best_platform */ = get__undefined();
  // 593: $$best_priority 999
  ((CELL *)frame->slots[5])->contents /* best_priority */ = number__999;
  // 594: ... : (platform _filenames)
  // 595:   $priority platform_specific_priority(supported_platform platform)
  // 596:   if priority.is_defined && priority < best_priority:
  // 597:     !best_platform platform
  // 598:     !best_priority priority
  frame->slots[6] /* temp__1 */ = create_closure(entry__70_110, 2);
  // 594: for_each mod_info: (platform _filenames)
  // 595:   $priority platform_specific_priority(supported_platform platform)
  // 596:   if priority.is_defined && priority < best_priority:
  // 597:     !best_platform platform
  // 598:     !best_priority priority
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* mod_info */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__70_117;
}
static void entry__70_116(void) {
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
  // 597: !best_platform platform
  ((CELL *)frame->slots[0])->contents /* best_platform */ = frame->slots[1] /* platform */;
  // 598: !best_priority priority
  ((CELL *)frame->slots[2])->contents /* best_priority */ = frame->slots[3] /* priority */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__70_110(void) {
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
  // 595: $priority platform_specific_priority(supported_platform platform)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* supported_platform */;
  arguments->slots[1] = frame->slots[0] /* platform */;
  result_count = 1;
  myself = var._platform_specific_priority;
  func = myself->type;
  frame->cont = cont__70_111;
}
static void cont__70_111(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* priority */, arguments->slots[0]);
  // 596: ... priority.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* priority */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__70_112;
}
static void cont__70_112(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 596: ... priority < best_priority
  frame->slots[8] /* temp__3 */ = create_closure(entry__70_113, 0);
  // 596: ... priority.is_defined && priority < best_priority
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  arguments->slots[1] = frame->slots[8] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__70_115;
}
static void entry__70_113(void) {
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
  // 596: ... priority < best_priority
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* priority */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* best_priority */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__70_114;
}
static void cont__70_114(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 596: ... priority < best_priority
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__70_115(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 596: ... :
  // 597:   !best_platform platform
  // 598:   !best_priority priority
  frame->slots[9] /* temp__4 */ = create_closure(entry__70_116, 0);
  // 596: if priority.is_defined && priority < best_priority:
  // 597:   !best_platform platform
  // 598:   !best_priority priority
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__70_117(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 599: ... best_platform.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* best_platform */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__70_118;
}
static void cont__70_118(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 599: ... :
  // 600:   $$ub default_value(used_by(best_platform) empty_list)
  // 601:   push &ub supported_platform
  // 602:   !used_by(best_platform) ub
  frame->slots[7] /* temp__2 */ = create_closure(entry__70_119, 0);
  // 599: if best_platform.is_defined:
  // 600:   $$ub default_value(used_by(best_platform) empty_list)
  // 601:   push &ub supported_platform
  // 602:   !used_by(best_platform) ub
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__70_124(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 603: ... : (platform _filenames)
  // 604:   $$dependency string(mod_filename "-" platform ".c")
  // 605:   $platforms used_by(platform)
  // 606:   if platforms.is_defined:
  // 607:     for_each platforms: (plat) write_to &dependency " #" plat
  // 608:   push &dependencies dependency
  frame->slots[3] /* temp__1 */ = create_closure(entry__70_125, 2);
  // 603: for_each mod_info: (platform _filenames)
  // 604:   $$dependency string(mod_filename "-" platform ".c")
  // 605:   $platforms used_by(platform)
  // 606:   if platforms.is_defined:
  // 607:     for_each platforms: (plat) write_to &dependency " #" plat
  // 608:   push &dependencies dependency
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_info */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__70_91(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // mod_filename: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* mod_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 574: ... string(mod_filename ".c")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = string__68_9;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__70_92;
}
static void cont__70_92(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 574: ... push &dependencies string(mod_filename ".c")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._dependencies;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__70_93;
}
static void cont__70_93(void) {
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
static void entry__70_86(void) {
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
  // 573: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__70_87;
}
static void cont__70_87(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 573: ... truncate_until(mod_name '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* mod_name */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__70_88;
}
static void cont__70_88(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 573: ... list(truncate_until(mod_name '/' -1))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__70_89;
}
static void cont__70_89(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 573: compile_submodule list(truncate_until(mod_name '/' -1))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = frame->slots[0] /* compile_submodule */;
  func = myself->type;
  frame->cont = cont__70_90;
}
static void cont__70_90(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 574: ... : push &dependencies string(mod_filename ".c")
  frame->slots[3] /* temp__1 */ = create_closure(entry__70_91, 0);
  // 574: if do_list_dependencies: push &dependencies string(mod_filename ".c")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_list_dependencies;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__70_94(void) {
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
  // 576: ... :
  // 577:   $$best_platform undefined
  // 578:   $$best_priority 999
  // 579:   for_each mod_info: (platform _filenames)
  // 580:     $priority platform_priority(platform)
  // 581:     if priority.is_defined && priority < best_priority:
  // 582:       !best_platform platform
  // 583:       !best_priority priority
  // 584:   for_each mod_info: (platform filenames)
  // 585:     compile_submodule
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__70_95, 0);
  // 576: do:
  // 577:   $$best_platform undefined
  // 578:   $$best_priority 999
  // 579:   for_each mod_info: (platform _filenames)
  // 580:     $priority platform_priority(platform)
  // 581:     if priority.is_defined && priority < best_priority:
  // 582:       !best_platform platform
  // 583:       !best_priority priority
  // 584:   for_each mod_info: (platform filenames)
  // 585:     compile_submodule
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__70_107;
}
static void entry__70_104(void) {
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
  // 587: platform == best_platform
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* platform */;
  arguments->slots[1] = ((CELL *)frame->slots[3])->contents /* best_platform */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__70_105;
}
static void cont__70_105(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 588: string("-" platform)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__64_46;
  arguments->slots[1] = frame->slots[0] /* platform */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__70_106;
}
static void cont__70_106(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 585: compile_submodule
  // 586:   filenames
  // 587:   platform == best_platform
  // 588:   string("-" platform)
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
static void entry__70_95(void) {
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
  // 577: $$best_platform undefined
  ((CELL *)frame->slots[2])->contents /* best_platform */ = get__undefined();
  // 578: $$best_priority 999
  ((CELL *)frame->slots[3])->contents /* best_priority */ = number__999;
  // 579: ... : (platform _filenames)
  // 580:   $priority platform_priority(platform)
  // 581:   if priority.is_defined && priority < best_priority:
  // 582:     !best_platform platform
  // 583:     !best_priority priority
  frame->slots[4] /* temp__1 */ = create_closure(entry__70_96, 2);
  // 579: for_each mod_info: (platform _filenames)
  // 580:   $priority platform_priority(platform)
  // 581:   if priority.is_defined && priority < best_priority:
  // 582:     !best_platform platform
  // 583:     !best_priority priority
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_info */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__70_103;
}
static void entry__70_102(void) {
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
  // 582: !best_platform platform
  ((CELL *)frame->slots[0])->contents /* best_platform */ = frame->slots[1] /* platform */;
  // 583: !best_priority priority
  ((CELL *)frame->slots[2])->contents /* best_priority */ = frame->slots[3] /* priority */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__70_96(void) {
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
  // 580: $priority platform_priority(platform)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* platform */;
  result_count = 1;
  myself = var._platform_priority;
  func = myself->type;
  frame->cont = cont__70_97;
}
static void cont__70_97(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* priority */, arguments->slots[0]);
  // 581: ... priority.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* priority */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__70_98;
}
static void cont__70_98(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 581: ... priority < best_priority
  frame->slots[7] /* temp__3 */ = create_closure(entry__70_99, 0);
  // 581: ... priority.is_defined && priority < best_priority
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__70_101;
}
static void entry__70_99(void) {
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
  // 581: ... priority < best_priority
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* priority */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* best_priority */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__70_100;
}
static void cont__70_100(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 581: ... priority < best_priority
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__70_101(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 581: ... :
  // 582:   !best_platform platform
  // 583:   !best_priority priority
  frame->slots[8] /* temp__4 */ = create_closure(entry__70_102, 0);
  // 581: if priority.is_defined && priority < best_priority:
  // 582:   !best_platform platform
  // 583:   !best_priority priority
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__70_103(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 584: ... : (platform filenames)
  // 585:   compile_submodule
  // 586:     filenames
  // 587:     platform == best_platform
  // 588:     string("-" platform)
  frame->slots[4] /* temp__1 */ = create_closure(entry__70_104, 2);
  // 584: for_each mod_info: (platform filenames)
  // 585:   compile_submodule
  // 586:     filenames
  // 587:     platform == best_platform
  // 588:     string("-" platform)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_info */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__70_107(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 589: ... :
  // 590:   $$used_by empty_table
  // 591:   for_each supported_platforms: (supported_platform _parent_platform)
  // 592:     $$best_platform undefined
  // 593:     $$best_priority 999
  // 594:     for_each mod_info: (platform _filenames)
  // 595:       $priority platform_specific_priority(supported_platform platform)
  // 596:       if priority.is_defined && priority < best_priority:
  // 597:         !best_platform platform
  // 598:         !best_priority priority
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__70_108, 0);
  // 589: if do_list_dependencies:
  // 590:   $$used_by empty_table
  // 591:   for_each supported_platforms: (supported_platform _parent_platform)
  // 592:     $$best_platform undefined
  // 593:     $$best_priority 999
  // 594:     for_each mod_info: (platform _filenames)
  // 595:       $priority platform_specific_priority(supported_platform platform)
  // 596:       if priority.is_defined && priority < best_priority:
  // 597:         !best_platform platform
  // 598:         !best_priority priority
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
static void cont__70_135(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__71_8(void) {
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
  // 619: ... string(path '/' name)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* path */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__71_9;
}
static void cont__71_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 619: ... string(mod_path '/' name)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* mod_path */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[0] /* name */;
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
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 619: compile_module string(path '/' name) string(mod_path '/' name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = var._compile_module;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__71_1_compile_modules(void) {
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
  // 615: ... string(mod_path '/')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* mod_path */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__71_2;
}
static void cont__71_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 615: add_module_infos $directories $modules path string(mod_path '/')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* path */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 2;
  myself = var._add_module_infos;
  func = myself->type;
  frame->cont = cont__71_3;
}
static void cont__71_3(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  frame->slots[6] /* temp__3 */ = arguments->slots[1];
  // 615: ... directories
  initialize_future(frame->slots[2] /* directories */, frame->slots[5] /* temp__2 */);
  // 615: ... modules
  initialize_future(frame->slots[3] /* modules */, frame->slots[6] /* temp__3 */);
  // 616: ... : (name)
  // 617:   compile_modules string(path '/' name) string(mod_path '/' name)
  frame->slots[4] /* temp__1 */ = create_closure(entry__71_4, 1);
  // 616: for_each directories: (name)
  // 617:   compile_modules string(path '/' name) string(mod_path '/' name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* directories */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__71_7;
}
static void entry__71_4(void) {
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
  // 617: ... string(path '/' name)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* path */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__71_5;
}
static void cont__71_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 617: ... string(mod_path '/' name)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* mod_path */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[0] /* name */;
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
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 617: compile_modules string(path '/' name) string(mod_path '/' name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = var._compile_modules;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__71_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 618: ... : (name)
  // 619:   compile_module string(path '/' name) string(mod_path '/' name)
  frame->slots[4] /* temp__1 */ = create_closure(entry__71_8, 1);
  // 618: for_each modules: (name)
  // 619:   compile_module string(path '/' name) string(mod_path '/' name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* modules */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__73_2(void) {
  allocate_initialized_frame_gc(0, 3);
  // slot allocations:
  // path: 0
  frame->slots[0] /* path */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 627: $path environment("LD_LIBRARY_PATH")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__73_3;
  result_count = 1;
  myself = get__environment();
  func = myself->type;
  frame->cont = cont__73_4;
}
static void cont__73_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[0] /* path */, arguments->slots[0]);
  // 628: ... path.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* path */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__73_5;
}
static void cont__73_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 628: ... : ewriteln "LD_LIBRARY_PATH=@(path)"
  frame->slots[2] /* temp__2 */ = create_closure(entry__73_6, 0);
  // 628: if path.is_defined: ewriteln "LD_LIBRARY_PATH=@(path)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__73_9;
}
static void entry__73_6(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // path: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* path */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 628: ... "LD_LIBRARY_PATH=@(path)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__73_7;
  arguments->slots[1] = frame->slots[0] /* path */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__73_8;
}
static void cont__73_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 628: ... ewriteln "LD_LIBRARY_PATH=@(path)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__73_9(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 629: ... serialize(objects)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__objects();
  result_count = 1;
  myself = get__serialize();
  func = myself->type;
  frame->cont = cont__73_10;
}
static void cont__73_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 629: ewriteln "included object files: " serialize(objects)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__73_11;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 0;
  myself = get__ewriteln();
  func = myself->type;
  frame->cont = cont__73_12;
}
static void cont__73_12(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 630: ... serialize(libraries)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__libraries();
  result_count = 1;
  myself = get__serialize();
  func = myself->type;
  frame->cont = cont__73_13;
}
static void cont__73_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 630: ewriteln "needed libraries: " serialize(libraries)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__73_14;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__73_1_show_file_list(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 626: if do_show_debug_infos:
  // 627:   $path environment("LD_LIBRARY_PATH")
  // 628:   if path.is_defined: ewriteln "LD_LIBRARY_PATH=@(path)"
  // 629:   ewriteln "included object files: " serialize(objects)
  // 630:   ewriteln "needed libraries: " serialize(libraries)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_show_debug_infos();
  arguments->slots[1] = func__73_2;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__74_1_library_paths_and_file_list(void) {
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
  // 633: show_file_list
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._show_file_list;
  func = myself->type;
  frame->cont = cont__74_2;
}
static void cont__74_2(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 634: $$library_paths empty_list
  ((CELL *)frame->slots[0])->contents /* library_paths */ = get__empty_list();
  // 635: $$object_files empty_list
  ((CELL *)frame->slots[1])->contents /* object_files */ = get__empty_list();
  // 636: $$library_files empty_list
  ((CELL *)frame->slots[2])->contents /* library_files */ = get__empty_list();
  // 637: $paths environment("LD_LIBRARY_PATH")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__73_3;
  result_count = 1;
  myself = get__environment();
  func = myself->type;
  frame->cont = cont__74_3;
}
static void cont__74_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* paths */, arguments->slots[0]);
  // 638: ... paths.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* paths */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__74_4;
}
static void cont__74_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 638: ... :
  // 639:   for_each paths .split. ':': (path) push &library_paths "-L@(path)"
  frame->slots[5] /* temp__2 */ = create_closure(entry__74_5, 0);
  // 638: if paths.is_defined:
  // 639:   for_each paths .split. ':': (path) push &library_paths "-L@(path)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__74_11;
}
static void entry__74_7(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // path: 0
  // library_paths: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* library_paths */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 639: ... "-L@(path)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__74_8;
  arguments->slots[1] = frame->slots[0] /* path */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__74_9;
}
static void cont__74_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 639: ... push &library_paths "-L@(path)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* library_paths */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__74_10;
}
static void cont__74_10(void) {
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
static void entry__74_5(void) {
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
  // 639: ... paths .split. ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* paths */;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__split();
  func = myself->type;
  frame->cont = cont__74_6;
}
static void cont__74_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 639: ... : (path) push &library_paths "-L@(path)"
  frame->slots[3] /* temp__2 */ = create_closure(entry__74_7, 1);
  // 639: for_each paths .split. ':': (path) push &library_paths "-L@(path)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__74_11(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 640: ... : ewriteln "library paths: " serialize(library_paths)
  frame->slots[4] /* temp__1 */ = create_closure(entry__74_12, 0);
  // 640: if do_show_debug_infos: ewriteln "library paths: " serialize(library_paths)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_show_debug_infos();
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__74_15;
}
static void entry__74_12(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // library_paths: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* library_paths */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 640: ... serialize(library_paths)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* library_paths */;
  result_count = 1;
  myself = get__serialize();
  func = myself->type;
  frame->cont = cont__74_13;
}
static void cont__74_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 640: ... ewriteln "library paths: " serialize(library_paths)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__74_14;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__74_15(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 641: ... : (object) push &object_files object
  frame->slots[4] /* temp__1 */ = create_closure(entry__74_16, 1);
  // 641: for_each objects: (object) push &object_files object
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__objects();
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__74_18;
}
static void entry__74_16(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // object: 0
  // object_files: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* object_files */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 641: ... push &object_files object
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* object_files */;
  arguments->slots[1] = frame->slots[0] /* object */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__74_17;
}
static void cont__74_17(void) {
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
static void cont__74_18(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 642: ... : (library)
  // 643:   push
  // 644:     &library_files
  // 645:     if
  // 646:       library .has_prefix. "sim-"
  // 647:       ->
  // 648:         if
  // 649:           current_platform == "linux"
  // 650:           -> "-l:lib@(library).so.@(MAJOR)"
  // 651:           -> "-l@(library)-@(MAJOR)"
  // ...
  frame->slots[4] /* temp__1 */ = create_closure(entry__74_19, 1);
  // 642: for_each libraries: (library)
  // 643:   push
  // 644:     &library_files
  // 645:     if
  // 646:       library .has_prefix. "sim-"
  // 647:       ->
  // 648:         if
  // 649:           current_platform == "linux"
  // 650:           -> "-l:lib@(library).so.@(MAJOR)"
  // 651:           -> "-l@(library)-@(MAJOR)"
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__libraries();
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__74_43;
}
static void entry__74_19(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // library: 0
  // library_files: 1
  frame->slots[1] = myself->closure.frame->slots[2]; /* library_files */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 646: library .has_prefix. "sim-"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* library */;
  arguments->slots[1] = string__69_32;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__74_20;
}
static void cont__74_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 647: ->
  // 648:   if
  // 649:     current_platform == "linux"
  // 650:     -> "-l:lib@(library).so.@(MAJOR)"
  // 651:     -> "-l@(library)-@(MAJOR)"
  frame->slots[4] /* temp__3 */ = create_closure(entry__74_21, 0);
  // 652: ->
  // 653:   if
  // 654:     library .contains. '.'
  // 655:     -> "-l:lib@(library .before. '.').so.@(library .behind. '.')"
  // 656:       # Linux only
  // 657:     -> "-l@(library)"
  frame->slots[5] /* temp__4 */ = create_closure(entry__74_32, 0);
  // 645: if
  // 646:   library .has_prefix. "sim-"
  // 647:   ->
  // 648:     if
  // 649:       current_platform == "linux"
  // 650:       -> "-l:lib@(library).so.@(MAJOR)"
  // 651:       -> "-l@(library)-@(MAJOR)"
  // 652:   ->
  // 653:     if
  // 654:       library .contains. '.'
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  arguments->slots[2] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__74_41;
}
static void entry__74_21(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // library: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* library */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 649: current_platform == "linux"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__current_platform();
  arguments->slots[1] = string__74_22;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__74_23;
}
static void cont__74_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 650: -> "-l:lib@(library).so.@(MAJOR)"
  frame->slots[3] /* temp__3 */ = create_closure(entry__74_24, 0);
  // 651: -> "-l@(library)-@(MAJOR)"
  frame->slots[4] /* temp__4 */ = create_closure(entry__74_28, 0);
  // 648: if
  // 649:   current_platform == "linux"
  // 650:   -> "-l:lib@(library).so.@(MAJOR)"
  // 651:   -> "-l@(library)-@(MAJOR)"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  arguments->slots[2] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__74_31;
}
static void entry__74_24(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // library: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* library */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 650: ... "-l:lib@(library).so.@(MAJOR)"
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__74_25;
  arguments->slots[1] = frame->slots[0] /* library */;
  arguments->slots[2] = string__74_26;
  arguments->slots[3] = var._MAJOR;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__74_27;
}
static void cont__74_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 650: -> "-l:lib@(library).so.@(MAJOR)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__74_28(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // library: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* library */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 651: ... "-l@(library)-@(MAJOR)"
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__74_29;
  arguments->slots[1] = frame->slots[0] /* library */;
  arguments->slots[2] = string__64_46;
  arguments->slots[3] = var._MAJOR;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__74_30;
}
static void cont__74_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 651: -> "-l@(library)-@(MAJOR)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__74_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 647: ->
  // 648:   if
  // 649:     current_platform == "linux"
  // 650:     -> "-l:lib@(library).so.@(MAJOR)"
  // 651:     -> "-l@(library)-@(MAJOR)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__74_32(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // library: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* library */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 654: library .contains. '.'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* library */;
  arguments->slots[1] = character__46;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__74_33;
}
static void cont__74_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 655: -> "-l:lib@(library .before. '.').so.@(library .behind. '.')"
  // 656:   # Linux only
  frame->slots[3] /* temp__3 */ = create_closure(entry__74_34, 0);
  // 657: -> "-l@(library)"
  frame->slots[4] /* temp__4 */ = create_closure(entry__74_38, 0);
  // 653: if
  // 654:   library .contains. '.'
  // 655:   -> "-l:lib@(library .before. '.').so.@(library .behind. '.')"
  // 656:     # Linux only
  // 657:   -> "-l@(library)"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  arguments->slots[2] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__74_40;
}
static void entry__74_34(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // library: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* library */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 655: ... library .before. '.'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* library */;
  arguments->slots[1] = character__46;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__74_35;
}
static void cont__74_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 655: ... library .behind. '.'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* library */;
  arguments->slots[1] = character__46;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__74_36;
}
static void cont__74_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 655: ... "-l:lib@(library .before. '.').so.@(library .behind. '.')"
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__74_25;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  arguments->slots[2] = string__74_26;
  arguments->slots[3] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__74_37;
}
static void cont__74_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 655: -> "-l:lib@(library .before. '.').so.@(library .behind. '.')"
  // 656:   # Linux only
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__74_38(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // library: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* library */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 657: ... "-l@(library)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__74_29;
  arguments->slots[1] = frame->slots[0] /* library */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__74_39;
}
static void cont__74_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 657: -> "-l@(library)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__74_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 652: ->
  // 653:   if
  // 654:     library .contains. '.'
  // 655:     -> "-l:lib@(library .before. '.').so.@(library .behind. '.')"
  // 656:       # Linux only
  // 657:     -> "-l@(library)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__74_41(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 643: push
  // 644:   &library_files
  // 645:   if
  // 646:     library .has_prefix. "sim-"
  // 647:     ->
  // 648:       if
  // 649:         current_platform == "linux"
  // 650:         -> "-l:lib@(library).so.@(MAJOR)"
  // 651:         -> "-l@(library)-@(MAJOR)"
  // 652:     ->
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* library_files */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__74_42;
}
static void cont__74_42(void) {
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
static void cont__74_43(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 658: ... append(object_files library_files)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* object_files */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* library_files */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__74_44;
}
static void cont__74_44(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 658: append library_paths append(object_files library_files)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* library_paths */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__append();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__75_74(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 701: ... write_timing_info "collecting imports"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__75_75;
  result_count = frame->caller_result_count;
  myself = get__write_timing_info();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__75_1_create_imports(void) {
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
  // 663: ... : (buf)
  // 664:   $$s undefined
  // 665:   for_each buf: (idx chr)
  // 666:     if
  // 667:       s.is_defined:
  // 668:         unless chr.is_a_letter || chr == '_' || chr.is_a_digit:
  // 669:           $symbol range(buf s idx-1)
  // 670:           !s undefined
  // 671:           unless already_checked(symbol):
  // 672:             !already_checked(symbol) true
  // ...
  frame->slots[5] /* temp__1 */ = create_closure(entry__75_2_collect_declarations, 1);
  // 663: $collect_declarations: (buf)
  // 664:   $$s undefined
  // 665:   for_each buf: (idx chr)
  // 666:     if
  // 667:       s.is_defined:
  // 668:         unless chr.is_a_letter || chr == '_' || chr.is_a_digit:
  // 669:           $symbol range(buf s idx-1)
  // 670:           !s undefined
  // 671:           unless already_checked(symbol):
  // 672:             !already_checked(symbol) true
  // ...
  initialize_future(frame->slots[2] /* collect_declarations */, frame->slots[5] /* temp__1 */);
  // 661: $$already_checked empty_set
  ((CELL *)frame->slots[1])->contents /* already_checked */ = get__empty_set();
  // 696: ... : collect_declarations source
  frame->slots[5] /* temp__1 */ = create_closure(entry__75_63, 0);
  // 696: collect_output $imports: collect_declarations source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__75_64;
}
static void entry__75_62(void) {
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
  // 694: ... !s idx
  ((CELL *)frame->slots[0])->contents /* s */ = frame->slots[1] /* idx */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__75_21(void) {
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
  // 677: declaration(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* declaration */;
  func = myself->type;
  frame->cont = cont__75_22;
}
static void cont__75_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 677: declaration(1) != '#'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  arguments->slots[1] = character__35;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__75_23;
}
static void cont__75_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 677: declaration(1) != '#'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__75_24;
}
static void cont__75_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  frame->slots[6] /* temp__4 */ = create_closure(entry__75_25, 0);
  // 675: $do_import
  // 676:   &&
  // 677:     declaration(1) != '#'
  // 678:     not(declaration .has_prefix. "typedef")
  // 679:     not(declaration .has_prefix. "REGISTER")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__75_34;
}
static void entry__75_25(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // declaration: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* declaration */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 678: ... declaration .has_prefix. "typedef"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* declaration */;
  arguments->slots[1] = string__75_26;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__75_27;
}
static void cont__75_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 678: not(declaration .has_prefix. "typedef")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__not();
  func = myself->type;
  frame->cont = cont__75_28;
}
static void cont__75_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 679: not(declaration .has_prefix. "REGISTER")
  frame->slots[4] /* temp__4 */ = create_closure(entry__75_29, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__75_33;
}
static void entry__75_29(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // declaration: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* declaration */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 679: ... declaration .has_prefix. "REGISTER"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* declaration */;
  arguments->slots[1] = string__75_30;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__75_31;
}
static void cont__75_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 679: not(declaration .has_prefix. "REGISTER")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__not();
  func = myself->type;
  frame->cont = cont__75_32;
}
static void cont__75_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 679: not(declaration .has_prefix. "REGISTER")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__75_33(void) {
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
static void cont__75_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* do_import */, arguments->slots[0]);
  // 682: ->
  // 683:   declaration(1) == '#' || declaration .has_prefix. "REGISTER"
  // 684:   :
  // 685:     collect_declarations declaration .truncate_from. '{'
  frame->slots[3] /* temp__1 */ = create_closure(entry__75_35, 0);
  // 686: -> declaration .has_prefix. "typedef struct":
  // 687:   for_each_line between(declaration '{' '}').trim: (line)
  // 688:     collect_declarations until(line ' ' -1)
  frame->slots[4] /* temp__2 */ = create_closure(entry__75_43, 0);
  // 689: :
  // 690:   collect_declarations declaration
  frame->slots[5] /* temp__3 */ = create_closure(entry__75_52, 0);
  // 681: cond
  // 682:   ->
  // 683:     declaration(1) == '#' || declaration .has_prefix. "REGISTER"
  // 684:     :
  // 685:       collect_declarations declaration .truncate_from. '{'
  // 686:   -> declaration .has_prefix. "typedef struct":
  // 687:     for_each_line between(declaration '{' '}').trim: (line)
  // 688:       collect_declarations until(line ' ' -1)
  // 689:   :
  // 690:     collect_declarations declaration
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = frame->slots[5] /* temp__3 */;
  result_count = 0;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__75_53;
}
static void entry__75_49(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // line: 0
  // collect_declarations: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* collect_declarations */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 688: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__75_50;
}
static void cont__75_50(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 688: ... until(line ' ' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* line */;
  arguments->slots[1] = character__32;
  arguments->slots[2] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__until();
  func = myself->type;
  frame->cont = cont__75_51;
}
static void cont__75_51(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 688: collect_declarations until(line ' ' -1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* collect_declarations */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__75_46(void) {
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
  // 687: ... between(declaration '{' '}')
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* declaration */;
  arguments->slots[1] = character__123;
  arguments->slots[2] = character__125;
  result_count = 1;
  myself = get__between();
  func = myself->type;
  frame->cont = cont__75_47;
}
static void cont__75_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 687: ... between(declaration '{' '}').trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__75_48;
}
static void cont__75_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 687: ... : (line)
  // 688:   collect_declarations until(line ' ' -1)
  frame->slots[4] /* temp__3 */ = create_closure(entry__75_49, 1);
  // 687: for_each_line between(declaration '{' '}').trim: (line)
  // 688:   collect_declarations until(line ' ' -1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__for_each_line();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__75_41(void) {
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
  // 685: ... declaration .truncate_from. '{'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* declaration */;
  arguments->slots[1] = character__123;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__75_42;
}
static void cont__75_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 685: collect_declarations declaration .truncate_from. '{'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* collect_declarations */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__75_35(void) {
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
  // 683: declaration(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* declaration */;
  func = myself->type;
  frame->cont = cont__75_36;
}
static void cont__75_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 683: declaration(1) == '#'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  arguments->slots[1] = character__35;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__75_37;
}
static void cont__75_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 683: ... declaration .has_prefix. "REGISTER"
  frame->slots[5] /* temp__4 */ = create_closure(entry__75_38, 0);
  // 683: declaration(1) == '#' || declaration .has_prefix. "REGISTER"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__75_40;
}
static void entry__75_38(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // declaration: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* declaration */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 683: ... declaration .has_prefix. "REGISTER"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* declaration */;
  arguments->slots[1] = string__75_30;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__75_39;
}
static void cont__75_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 683: ... declaration .has_prefix. "REGISTER"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__75_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 684: :
  // 685:   collect_declarations declaration .truncate_from. '{'
  frame->slots[6] /* temp__5 */ = create_closure(entry__75_41, 0);
  // 682: ->
  // 683:   declaration(1) == '#' || declaration .has_prefix. "REGISTER"
  // 684:   :
  // 685:     collect_declarations declaration .truncate_from. '{'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__5 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__75_43(void) {
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
  // 686: ... declaration .has_prefix. "typedef struct"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* declaration */;
  arguments->slots[1] = string__75_44;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__75_45;
}
static void cont__75_45(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 686: ... :
  // 687:   for_each_line between(declaration '{' '}').trim: (line)
  // 688:     collect_declarations until(line ' ' -1)
  frame->slots[3] /* temp__2 */ = create_closure(entry__75_46, 0);
  // 686: -> declaration .has_prefix. "typedef struct":
  // 687:   for_each_line between(declaration '{' '}').trim: (line)
  // 688:     collect_declarations until(line ' ' -1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__75_52(void) {
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
  // 690: collect_declarations declaration
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* declaration */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* collect_declarations */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__75_53(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 691: if do_import: write "IMPORT "
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* do_import */;
  arguments->slots[1] = func__75_54;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__75_56;
}
static void entry__75_54(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 691: ... write "IMPORT "
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__75_55;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__75_56(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 692: write declaration
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* declaration */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__75_17(void) {
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
  // 672: !already_checked(symbol) true
  frame->slots[4] /* temp__1 */ = get__true();
  // 672: !already_checked(symbol)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* symbol */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* already_checked */;
  func = myself->type;
  frame->cont = cont__75_18;
}
static void cont__75_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* already_checked */ = arguments->slots[0];
  // 673: $declaration runtime_symbols(symbol)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* symbol */;
  result_count = 1;
  myself = get__runtime_symbols();
  func = myself->type;
  frame->cont = cont__75_19;
}
static void cont__75_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* declaration */, arguments->slots[0]);
  // 674: ... declaration.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* declaration */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__75_20;
}
static void cont__75_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 674: ... :
  // 675:   $do_import
  // 676:     &&
  // 677:       declaration(1) != '#'
  // 678:       not(declaration .has_prefix. "typedef")
  // 679:       not(declaration .has_prefix. "REGISTER")
  // 680:   
  // 681:   cond
  // 682:     ->
  // 683:       declaration(1) == '#' || declaration .has_prefix. "REGISTER"
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__75_21, 0);
  // 674: if declaration.is_defined:
  // 675:   $do_import
  // 676:     &&
  // 677:       declaration(1) != '#'
  // 678:       not(declaration .has_prefix. "typedef")
  // 679:       not(declaration .has_prefix. "REGISTER")
  // 680:   
  // 681:   cond
  // 682:     ->
  // 683:       declaration(1) == '#' || declaration .has_prefix. "REGISTER"
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
static void entry__75_13(void) {
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
  // 669: ... idx-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* idx */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__75_14;
}
static void cont__75_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 669: $symbol range(buf s idx-1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* buf */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* s */;
  arguments->slots[2] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__75_15;
}
static void cont__75_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* symbol */, arguments->slots[0]);
  // 670: !s undefined
  ((CELL *)frame->slots[1])->contents /* s */ = get__undefined();
  // 671: ... already_checked(symbol)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* symbol */;
  result_count = 1;
  myself = ((CELL *)frame->slots[3])->contents /* already_checked */;
  func = myself->type;
  frame->cont = cont__75_16;
}
static void cont__75_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 671: ... :
  // 672:   !already_checked(symbol) true
  // 673:   $declaration runtime_symbols(symbol)
  // 674:   if declaration.is_defined:
  // 675:     $do_import
  // 676:       &&
  // 677:         declaration(1) != '#'
  // 678:         not(declaration .has_prefix. "typedef")
  // 679:         not(declaration .has_prefix. "REGISTER")
  // 680:     
  // ...
  frame->slots[7] /* temp__2 */ = create_closure(entry__75_17, 0);
  // 671: unless already_checked(symbol):
  // 672:   !already_checked(symbol) true
  // 673:   $declaration runtime_symbols(symbol)
  // 674:   if declaration.is_defined:
  // 675:     $do_import
  // 676:       &&
  // 677:         declaration(1) != '#'
  // 678:         not(declaration .has_prefix. "typedef")
  // 679:         not(declaration .has_prefix. "REGISTER")
  // 680:     
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
static void entry__75_5(void) {
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
  // 668: ... chr.is_a_letter
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  result_count = 1;
  myself = get__is_a_letter();
  func = myself->type;
  frame->cont = cont__75_6;
}
static void cont__75_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 668: ... chr == '_' || chr.is_a_digit
  frame->slots[8] /* temp__3 */ = create_closure(entry__75_7, 0);
  // 668: ... chr.is_a_letter || chr == '_' || chr.is_a_digit
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  arguments->slots[1] = frame->slots[8] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__75_12;
}
static void entry__75_7(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 668: ... chr == '_'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__95;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__75_8;
}
static void cont__75_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 668: ... chr.is_a_digit
  frame->slots[3] /* temp__3 */ = create_closure(entry__75_9, 0);
  // 668: ... chr == '_' || chr.is_a_digit
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__75_11;
}
static void entry__75_9(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 668: ... chr.is_a_digit
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  result_count = 1;
  myself = get__is_a_digit();
  func = myself->type;
  frame->cont = cont__75_10;
}
static void cont__75_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 668: ... chr.is_a_digit
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__75_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 668: ... chr == '_' || chr.is_a_digit
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__75_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 668: ... :
  // 669:   $symbol range(buf s idx-1)
  // 670:   !s undefined
  // 671:   unless already_checked(symbol):
  // 672:     !already_checked(symbol) true
  // 673:     $declaration runtime_symbols(symbol)
  // 674:     if declaration.is_defined:
  // 675:       $do_import
  // 676:         &&
  // 677:           declaration(1) != '#'
  // ...
  frame->slots[9] /* temp__4 */ = create_closure(entry__75_13, 0);
  // 668: unless chr.is_a_letter || chr == '_' || chr.is_a_digit:
  // 669:   $symbol range(buf s idx-1)
  // 670:   !s undefined
  // 671:   unless already_checked(symbol):
  // 672:     !already_checked(symbol) true
  // 673:     $declaration runtime_symbols(symbol)
  // 674:     if declaration.is_defined:
  // 675:       $do_import
  // 676:         &&
  // 677:           declaration(1) != '#'
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
static void entry__75_57(void) {
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
  // 694: ... chr.is_a_letter
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  result_count = 1;
  myself = get__is_a_letter();
  func = myself->type;
  frame->cont = cont__75_58;
}
static void cont__75_58(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 694: ... chr == '_'
  frame->slots[5] /* temp__3 */ = create_closure(entry__75_59, 0);
  // 694: ... chr.is_a_letter || chr == '_'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__75_61;
}
static void entry__75_59(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 694: ... chr == '_'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__95;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__75_60;
}
static void cont__75_60(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 694: ... chr == '_'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__75_61(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 694: ... : !s idx
  frame->slots[6] /* temp__4 */ = create_closure(entry__75_62, 0);
  // 694: if chr.is_a_letter || chr == '_': !s idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__75_3(void) {
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
  // 667: s.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* s */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__75_4;
}
static void cont__75_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 667: ... :
  // 668:   unless chr.is_a_letter || chr == '_' || chr.is_a_digit:
  // 669:     $symbol range(buf s idx-1)
  // 670:     !s undefined
  // 671:     unless already_checked(symbol):
  // 672:       !already_checked(symbol) true
  // 673:       $declaration runtime_symbols(symbol)
  // 674:       if declaration.is_defined:
  // 675:         $do_import
  // 676:           &&
  // ...
  frame->slots[7] /* temp__2 */ = create_closure(entry__75_5, 0);
  // 693: :
  // 694:   if chr.is_a_letter || chr == '_': !s idx
  frame->slots[8] /* temp__3 */ = create_closure(entry__75_57, 0);
  // 666: if
  // 667:   s.is_defined:
  // 668:     unless chr.is_a_letter || chr == '_' || chr.is_a_digit:
  // 669:       $symbol range(buf s idx-1)
  // 670:       !s undefined
  // 671:       unless already_checked(symbol):
  // 672:         !already_checked(symbol) true
  // 673:         $declaration runtime_symbols(symbol)
  // 674:         if declaration.is_defined:
  // 675:           $do_import
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
static void entry__75_2_collect_declarations(void) {
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
  // 664: $$s undefined
  ((CELL *)frame->slots[3])->contents /* s */ = get__undefined();
  // 665: ... : (idx chr)
  // 666:   if
  // 667:     s.is_defined:
  // 668:       unless chr.is_a_letter || chr == '_' || chr.is_a_digit:
  // 669:         $symbol range(buf s idx-1)
  // 670:         !s undefined
  // 671:         unless already_checked(symbol):
  // 672:           !already_checked(symbol) true
  // 673:           $declaration runtime_symbols(symbol)
  // 674:           if declaration.is_defined:
  // ...
  frame->slots[4] /* temp__1 */ = create_closure(entry__75_3, 2);
  // 665: for_each buf: (idx chr)
  // 666:   if
  // 667:     s.is_defined:
  // 668:       unless chr.is_a_letter || chr == '_' || chr.is_a_digit:
  // 669:         $symbol range(buf s idx-1)
  // 670:         !s undefined
  // 671:         unless already_checked(symbol):
  // 672:           !already_checked(symbol) true
  // 673:           $declaration runtime_symbols(symbol)
  // 674:           if declaration.is_defined:
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
static void entry__75_63(void) {
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
  // 696: ... collect_declarations source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* source */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* collect_declarations */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__75_64(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* imports */, arguments->slots[0]);
  // 697: $first_part source .before. "// INSERT HERE //"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  arguments->slots[1] = string__75_65;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__75_66;
}
static void cont__75_66(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* first_part */, arguments->slots[0]);
  // 698: write first_part
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* first_part */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__75_67;
}
static void cont__75_67(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 699: write imports
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* imports */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__75_68;
}
static void cont__75_68(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 700: ... length_of(first_part)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* first_part */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__75_69;
}
static void cont__75_69(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__3 */ = arguments->slots[0];
  // 700: ... length_of(first_part)+18
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__3 */;
  arguments->slots[1] = number__18;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__75_70;
}
static void cont__75_70(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 700: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__75_71;
}
static void cont__75_71(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__4 */ = arguments->slots[0];
  // 700: ... range(source length_of(first_part)+18 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  arguments->slots[2] = frame->slots[8] /* temp__4 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__75_72;
}
static void cont__75_72(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 700: write range(source length_of(first_part)+18 -1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__75_73;
}
static void cont__75_73(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 701: if do_time_passes: write_timing_info "collecting imports"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = func__75_74;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__76_1_compile_exe(void) {
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
  // 704: ... main_info.is_a_directory
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_info();
  result_count = 1;
  myself = get__is_a_directory();
  func = myself->type;
  frame->cont = cont__76_2;
}
static void cont__76_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 704: if main_info.is_a_directory: Error "Expected a source code file!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = func__76_3;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__76_5;
}
static void entry__76_3(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 704: ... Error "Expected a source code file!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__76_4;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__76_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 705: ... main_filename .has_suffix. ".sim"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  arguments->slots[1] = string__64_13;
  result_count = 1;
  myself = get__has_suffix();
  func = myself->type;
  frame->cont = cont__76_6;
}
static void cont__76_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 705: unless main_filename .has_suffix. ".sim":
  // 706:   Error "
  // 707:     Expected ".sim" file extension in source filename!@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = func__76_7;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__76_9;
}
static void entry__76_7(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 706: Error "
  // 707:   Expected ".sim" file extension in source filename!@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__76_8;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__76_9(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 709: $mod_filename main_filename .without_suffix. ".sim"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  arguments->slots[1] = string__64_13;
  result_count = 1;
  myself = get__without_suffix();
  func = myself->type;
  frame->cont = cont__76_10;
}
static void cont__76_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* mod_filename */, arguments->slots[0]);
  // 710: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__76_11;
}
static void cont__76_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 710: $mod_name truncate_until(mod_filename '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* mod_filename */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__76_12;
}
static void cont__76_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* mod_name */, arguments->slots[0]);
  // 711: body mod_filename mod_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* mod_filename */;
  arguments->slots[1] = frame->slots[3] /* mod_name */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame->cont = cont__76_13;
}
static void cont__76_13(void) {
  myself = frame->slots[1] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__77_2(void) {
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
  // 715: %sim2c::module_name mod_name
  initialize_maybe_future(get__sim2c__module_name(), frame->slots[1] /* mod_name */);
  // 716: ... list(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__77_3;
}
static void cont__77_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 716: sim2c list(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__sim2c();
  func = myself->type;
  frame->cont = cont__77_4;
}
static void cont__77_4(void) {
  myself = frame->slots[2] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__77_1_dump_source_or_check(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 714: compile_exe: (_mod_filename mod_name)
  // 715:   %sim2c::module_name mod_name
  // 716:   sim2c list(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__77_2;
  result_count = frame->caller_result_count;
  myself = var._compile_exe;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__78_18(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 726: ... write_timing_info "writing C-source"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__78_19;
  result_count = frame->caller_result_count;
  myself = get__write_timing_info();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__78_2(void) {
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
  // 720: ... module_prefix.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._module_prefix;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__78_3;
}
static void cont__78_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 720: ... : append string(module_prefix '/') &mod_name
  frame->slots[5] /* temp__2 */ = create_closure(entry__78_4, 0);
  // 720: if module_prefix.is_defined: append string(module_prefix '/') &mod_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__78_7;
}
static void entry__78_4(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // mod_name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* mod_name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 720: ... string(module_prefix '/')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._module_prefix;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__78_5;
}
static void cont__78_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 720: ... append string(module_prefix '/') &mod_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* mod_name */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__78_6;
}
static void cont__78_6(void) {
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
static void cont__78_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 721: ... :
  // 722:   %sim2c::module_name replace_all(mod_name '/' = "__" '.' = "__")
  // 723:   sim2c list(main_filename)
  frame->slots[4] /* temp__1 */ = create_closure(entry__78_8, 0);
  // 721: collect_output $c_source:
  // 722:   %sim2c::module_name replace_all(mod_name '/' = "__" '.' = "__")
  // 723:   sim2c list(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__78_14;
}
static void entry__78_8(void) {
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
  // 722: ... '/' = "__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = string__70_38;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__78_9;
}
static void cont__78_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 722: ... '.' = "__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__46;
  arguments->slots[1] = string__70_38;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__78_10;
}
static void cont__78_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 722: %sim2c::module_name replace_all(mod_name '/' = "__" '.' = "__")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* mod_name */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  arguments->slots[2] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__78_11;
}
static void cont__78_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(get__sim2c__module_name(), arguments->slots[0]);
  // 723: ... list(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__78_12;
}
static void cont__78_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 723: sim2c list(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__sim2c();
  func = myself->type;
  frame->cont = cont__78_13;
}
static void cont__78_13(void) {
  myself = frame->slots[0] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__78_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* c_source */, arguments->slots[0]);
  // 724: ... : create_imports c_source
  frame->slots[4] /* temp__1 */ = create_closure(entry__78_15, 0);
  // 724: collect_output $c_buf: create_imports c_source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__78_16;
}
static void entry__78_15(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // c_source: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* c_source */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 724: ... create_imports c_source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_source */;
  result_count = frame->caller_result_count;
  myself = var._create_imports;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__78_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* c_buf */, arguments->slots[0]);
  // 725: write c_buf
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* c_buf */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__78_17;
}
static void cont__78_17(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 726: if do_time_passes: write_timing_info "writing C-source"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = func__78_18;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__78_1_print_c(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 719: compile_exe: (_mod_filename $mod_name)
  // 720:   if module_prefix.is_defined: append string(module_prefix '/') &mod_name
  // 721:   collect_output $c_source:
  // 722:     %sim2c::module_name replace_all(mod_name '/' = "__" '.' = "__")
  // 723:     sim2c list(main_filename)
  // 724:   collect_output $c_buf: create_imports c_source
  // 725:   write c_buf
  // 726:   if do_time_passes: write_timing_info "writing C-source"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__78_2;
  result_count = frame->caller_result_count;
  myself = var._compile_exe;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__79_35(void) {
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
  // 755: without_prefix &filename prefix_path
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* filename */;
  arguments->slots[1] = frame->slots[1] /* prefix_path */;
  result_count = 1;
  myself = get__without_prefix();
  func = myself->type;
  frame->cont = cont__79_36;
}
static void cont__79_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* filename */ = arguments->slots[0];
  // 756: without_prefix &filename '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* filename */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__without_prefix();
  func = myself->type;
  frame->cont = cont__79_37;
}
static void cont__79_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* filename */ = arguments->slots[0];
  // 757: writeln filename
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* filename */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__79_1_list_dependencies(void) {
  allocate_initialized_frame_gc(0, 2);
  // slot allocations:
  // prefix_path: 0
  frame->slots[0] /* prefix_path */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 729: !platform_specific_priority multi_dimensional_table(types::table types::table)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__types__table();
  arguments->slots[1] = get__types__table();
  result_count = 1;
  myself = get__multi_dimensional_table();
  func = myself->type;
  frame->cont = cont__79_2;
}
static void cont__79_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._platform_specific_priority = arguments->slots[0];
  // 730: for_each supported_platforms: (supported_platform _parent_platform)
  // 731:   $$platform supported_platform
  // 732:   $$priority 0
  // 733:   do: (-> break)
  // 734:     forever:
  // 735:       $plat supported_platforms(platform)
  // 736:       if plat.is_undefined break
  // 737:       inc &priority
  // 738:       !platform_specific_priority(supported_platform platform) priority
  // 739:       if plat == NONE break
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._supported_platforms;
  arguments->slots[1] = func__79_3;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__79_14;
}
static void entry__79_4(void) {
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
  // 734: ... :
  // 735:   $plat supported_platforms(platform)
  // 736:   if plat.is_undefined break
  // 737:   inc &priority
  // 738:   !platform_specific_priority(supported_platform platform) priority
  // 739:   if plat == NONE break
  // 740:   !platform plat
  frame->slots[4] /* temp__1 */ = create_closure(entry__79_5, 0);
  // 734: forever:
  // 735:   $plat supported_platforms(platform)
  // 736:   if plat.is_undefined break
  // 737:   inc &priority
  // 738:   !platform_specific_priority(supported_platform platform) priority
  // 739:   if plat == NONE break
  // 740:   !platform plat
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame->cont = cont__79_13;
}
static void entry__79_5(void) {
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
  // 735: $plat supported_platforms(platform)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* platform */;
  result_count = 1;
  myself = var._supported_platforms;
  func = myself->type;
  frame->cont = cont__79_6;
}
static void cont__79_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* plat */, arguments->slots[0]);
  // 736: ... plat.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* plat */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__79_7;
}
static void cont__79_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 736: if plat.is_undefined break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* break */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__79_8;
}
static void cont__79_8(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 737: inc &priority
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* priority */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__79_9;
}
static void cont__79_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* priority */ = arguments->slots[0];
  // 738: !platform_specific_priority(supported_platform platform) priority
  frame->slots[5] /* temp__1 */ = ((CELL *)frame->slots[2])->contents /* priority */;
  // 738: !platform_specific_priority(supported_platform platform)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* supported_platform */;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* platform */;
  arguments->slots[2] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = var._platform_specific_priority;
  func = myself->type;
  frame->cont = cont__79_10;
}
static void cont__79_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._platform_specific_priority = arguments->slots[0];
  // 739: ... plat == NONE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* plat */;
  arguments->slots[1] = var._NONE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__79_11;
}
static void cont__79_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 739: if plat == NONE break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* break */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__79_12;
}
static void cont__79_12(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 740: !platform plat
  ((CELL *)frame->slots[0])->contents /* platform */ = frame->slots[4] /* plat */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__79_13(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__79_3(void) {
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
  // 731: $$platform supported_platform
  ((CELL *)frame->slots[2])->contents /* platform */ = frame->slots[0] /* supported_platform */;
  // 732: $$priority 0
  ((CELL *)frame->slots[3])->contents /* priority */ = number__0;
  // 733: ... : (-> break)
  // 734:   forever:
  // 735:     $plat supported_platforms(platform)
  // 736:     if plat.is_undefined break
  // 737:     inc &priority
  // 738:     !platform_specific_priority(supported_platform platform) priority
  // 739:     if plat == NONE break
  // 740:     !platform plat
  frame->slots[4] /* temp__1 */ = create_closure(entry__79_4, 0);
  // 733: do: (-> break)
  // 734:   forever:
  // 735:     $plat supported_platforms(platform)
  // 736:     if plat.is_undefined break
  // 737:     inc &priority
  // 738:     !platform_specific_priority(supported_platform platform) priority
  // 739:     if plat == NONE break
  // 740:     !platform plat
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__do();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__79_14(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 742: main_info.is_a_directory
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_info();
  result_count = 1;
  myself = get__is_a_directory();
  func = myself->type;
  frame->cont = cont__79_15;
}
static void cont__79_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 741: if
  // 742:   main_info.is_a_directory:
  // 743:     %mode LIB
  // 744:     if verbose: ewriteln "list dependencies for " main_filename
  // 745:     compile_modules main_filename behind(main_filename '/' -1)
  // 746:   :
  // 747:     compile_exe: (mod_filename mod_name)
  // 748:       if verbose: ewriteln "list dependencies for " mod_filename
  // 749:       compile_module mod_filename mod_name
  // 750:     writeln "runtime/linker.c"
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__79_16;
  arguments->slots[2] = func__79_23;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__79_33;
}
static void entry__79_16(void) {
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
  // 744: if verbose: ewriteln "list dependencies for " main_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = func__79_17;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__79_19;
}
static void entry__79_17(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 744: ... ewriteln "list dependencies for " main_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__79_18;
  arguments->slots[1] = get__main_filename();
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__79_19(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 745: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__79_20;
}
static void cont__79_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 745: ... behind(main_filename '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__79_21;
}
static void cont__79_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 745: compile_modules main_filename behind(main_filename '/' -1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = var._compile_modules;
  func = myself->type;
  frame->cont = cont__79_22;
}
static void cont__79_22(void) {
  myself = frame->slots[0] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__79_23(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 747: compile_exe: (mod_filename mod_name)
  // 748:   if verbose: ewriteln "list dependencies for " mod_filename
  // 749:   compile_module mod_filename mod_name
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__79_24;
  result_count = 0;
  myself = var._compile_exe;
  func = myself->type;
  frame->cont = cont__79_27;
}
static void entry__79_24(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // mod_filename: 0
  // mod_name: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 748: ... : ewriteln "list dependencies for " mod_filename
  frame->slots[2] /* temp__1 */ = create_closure(entry__79_25, 0);
  // 748: if verbose: ewriteln "list dependencies for " mod_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__79_26;
}
static void entry__79_25(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // mod_filename: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* mod_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 748: ... ewriteln "list dependencies for " mod_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__79_18;
  arguments->slots[1] = frame->slots[0] /* mod_filename */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__79_26(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 749: compile_module mod_filename mod_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = frame->slots[1] /* mod_name */;
  result_count = frame->caller_result_count;
  myself = var._compile_module;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__79_27(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 750: writeln "runtime/linker.c"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__79_28;
  result_count = 0;
  myself = get__writeln();
  func = myself->type;
  frame->cont = cont__79_29;
}
static void cont__79_29(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 751: writeln "runtime/memory.c"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__79_30;
  result_count = 0;
  myself = get__writeln();
  func = myself->type;
  frame->cont = cont__79_31;
}
static void cont__79_31(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 752: writeln "runtime/debugger.c"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__79_32;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__79_33(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 753: $prefix_path current_path()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__current_path();
  func = myself->type;
  frame->cont = cont__79_34;
}
static void cont__79_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[0] /* prefix_path */, arguments->slots[0]);
  // 754: ... : ($filename)
  // 755:   without_prefix &filename prefix_path
  // 756:   without_prefix &filename '/'
  // 757:   writeln filename
  frame->slots[1] /* temp__1 */ = create_closure(entry__79_35, 1);
  // 754: for_each dependencies: ($filename)
  // 755:   without_prefix &filename prefix_path
  // 756:   without_prefix &filename '/'
  // 757:   writeln filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._dependencies;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__80_2(void) {
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
  // 761: $codeblocks_path string(mod_filename ".codeblocks")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = string__80_3;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__80_4;
}
static void cont__80_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* codeblocks_path */, arguments->slots[0]);
  // 762: $info stat(codeblocks_path)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* codeblocks_path */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__80_5;
}
static void cont__80_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* info */, arguments->slots[0]);
  // 763: ... info.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* info */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__80_6;
}
static void cont__80_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 763: ... :
  // 764:   ewrite "
  // 765:     The directory "@(codeblocks_path)" already exists!
  frame->slots[11] /* temp__2 */ = create_closure(entry__80_7, 0);
  // 763: if info.is_defined:
  // 764:   ewrite "
  // 765:     The directory "@(codeblocks_path)" already exists!
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__1 */;
  arguments->slots[1] = frame->slots[11] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__80_11;
}
static void entry__80_7(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // codeblocks_path: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* codeblocks_path */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 764: ... "
  // 765:   The directory "@(codeblocks_path)" already exists!
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__80_8;
  arguments->slots[1] = frame->slots[0] /* codeblocks_path */;
  arguments->slots[2] = string__80_9;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__80_10;
}
static void cont__80_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 764: ewrite "
  // 765:   The directory "@(codeblocks_path)" already exists!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewrite();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__80_11(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 766: ... : ewriteln "build Code::Blocks project in " codeblocks_path
  frame->slots[10] /* temp__1 */ = create_closure(entry__80_12, 0);
  // 766: if verbose: ewriteln "build Code::Blocks project in " codeblocks_path
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = frame->slots[10] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__80_14;
}
static void entry__80_12(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // codeblocks_path: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* codeblocks_path */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 766: ... ewriteln "build Code::Blocks project in " codeblocks_path
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__80_13;
  arguments->slots[1] = frame->slots[0] /* codeblocks_path */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__80_14(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 767: compile_module mod_filename mod_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = frame->slots[1] /* mod_name */;
  result_count = 0;
  myself = var._compile_module;
  func = myself->type;
  frame->cont = cont__80_15;
}
static void cont__80_15(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 768: show_file_list
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._show_file_list;
  func = myself->type;
  frame->cont = cont__80_16;
}
static void cont__80_16(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 769: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__80_17;
}
static void cont__80_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__2 */ = arguments->slots[0];
  // 769: ... truncate_until(main_filename '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[11] /* temp__2 */;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__80_18;
}
static void cont__80_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 769: $basename truncate_until(main_filename '/' -1) .without_suffix. ".sim"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__1 */;
  arguments->slots[1] = string__64_13;
  result_count = 1;
  myself = get__without_suffix();
  func = myself->type;
  frame->cont = cont__80_19;
}
static void cont__80_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* basename */, arguments->slots[0]);
  // 770: $prefix_path current_path()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__current_path();
  func = myself->type;
  frame->cont = cont__80_20;
}
static void cont__80_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* prefix_path */, arguments->slots[0]);
  // 771: ... codeblocks_path .without_prefix. prefix_path
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* codeblocks_path */;
  arguments->slots[1] = frame->slots[5] /* prefix_path */;
  result_count = 1;
  myself = get__without_prefix();
  func = myself->type;
  frame->cont = cont__80_21;
}
static void cont__80_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 771: $depth count_occurrences(codeblocks_path .without_prefix. prefix_path '/')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__1 */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__count_occurrences();
  func = myself->type;
  frame->cont = cont__80_22;
}
static void cont__80_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* depth */, arguments->slots[0]);
  // 772: $path_prefix dup("../" depth)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__80_23;
  arguments->slots[1] = frame->slots[6] /* depth */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__80_24;
}
static void cont__80_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[7] /* path_prefix */, arguments->slots[0]);
  // 773: $cbp_filename string(codeblocks_path "/" basename ".cbp")
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* codeblocks_path */;
  arguments->slots[1] = string__80_25;
  arguments->slots[2] = frame->slots[4] /* basename */;
  arguments->slots[3] = string__80_26;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__80_27;
}
static void cont__80_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[8] /* cbp_filename */, arguments->slots[0]);
  // 774: mkdir codeblocks_path
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* codeblocks_path */;
  result_count = 0;
  myself = var._mkdir;
  func = myself->type;
  frame->cont = cont__80_28;
}
static void cont__80_28(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 775: $$buf ""
  ((CELL *)frame->slots[9])->contents /* buf */ = empty_string;
  // 776: ... "
  // 777:   <?xml version="1.0" encoding="UTF-8" standalone="yes" ?>
  // 778:   <CodeBlocks_project_file>
  // 779:     <FileVersion major="1" minor="6" />
  // 780:     <Project>
  // 781:       <Option title="@(basename)" />
  // 782:       <Option pch_mode="2" />
  // 783:       <Option compiler="gcc" />
  // 784:       <Build>
  // 785:         <Target title="debug">
  // ...
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__80_29;
  arguments->slots[1] = frame->slots[4] /* basename */;
  arguments->slots[2] = string__80_30;
  arguments->slots[3] = frame->slots[4] /* basename */;
  arguments->slots[4] = string__80_31;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__80_32;
}
static void cont__80_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 776: write_to &buf "
  // 777:   <?xml version="1.0" encoding="UTF-8" standalone="yes" ?>
  // 778:   <CodeBlocks_project_file>
  // 779:     <FileVersion major="1" minor="6" />
  // 780:     <Project>
  // 781:       <Option title="@(basename)" />
  // 782:       <Option pch_mode="2" />
  // 783:       <Option compiler="gcc" />
  // 784:       <Build>
  // 785:         <Target title="debug">
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[9])->contents /* buf */;
  arguments->slots[1] = frame->slots[10] /* temp__1 */;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__80_33;
}
static void cont__80_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[9])->contents /* buf */ = arguments->slots[0];
  // 797: ... : (filename)
  // 798:   write_to &buf "
  // 799:     @
  // 800:           <Add library="@(filename)" />
  frame->slots[10] /* temp__1 */ = create_closure(entry__80_34, 1);
  // 797: for_each libraries: (filename)
  // 798:   write_to &buf "
  // 799:     @
  // 800:           <Add library="@(filename)" />
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__libraries();
  arguments->slots[1] = frame->slots[10] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__80_39;
}
static void entry__80_34(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // filename: 0
  // buf: 1
  frame->slots[1] = myself->closure.frame->slots[9]; /* buf */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 798: ... "
  // 799:   @
  // 800:         <Add library="@(filename)" />
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__80_35;
  arguments->slots[1] = frame->slots[0] /* filename */;
  arguments->slots[2] = string__80_36;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__80_37;
}
static void cont__80_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 798: write_to &buf "
  // 799:   @
  // 800:         <Add library="@(filename)" />
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* buf */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__80_38;
}
static void cont__80_38(void) {
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
static void cont__80_39(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 801: ... "
  // 802:   @
  // 803:   
  // 804:       </Linker>
  // 805:       <Compiler>
  // 806:         <Add option="-Wall" />
  // 807:       </Compiler>
  // 808:       <Unit filename="@(path_prefix)runtime/common.h" />
  // 809:       <Unit filename="@(path_prefix)runtime/linker.h" />
  // 810:       <Unit filename="@(path_prefix)runtime/memory.c">
  // ...
  argument_count = 11;
  arguments = node_p;
  arguments->slots[0] = string__80_40;
  arguments->slots[1] = frame->slots[7] /* path_prefix */;
  arguments->slots[2] = string__80_41;
  arguments->slots[3] = frame->slots[7] /* path_prefix */;
  arguments->slots[4] = string__80_42;
  arguments->slots[5] = frame->slots[7] /* path_prefix */;
  arguments->slots[6] = string__80_43;
  arguments->slots[7] = frame->slots[7] /* path_prefix */;
  arguments->slots[8] = string__80_44;
  arguments->slots[9] = frame->slots[7] /* path_prefix */;
  arguments->slots[10] = string__80_45;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__80_46;
}
static void cont__80_46(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 801: write_to &buf "
  // 802:   @
  // 803:   
  // 804:       </Linker>
  // 805:       <Compiler>
  // 806:         <Add option="-Wall" />
  // 807:       </Compiler>
  // 808:       <Unit filename="@(path_prefix)runtime/common.h" />
  // 809:       <Unit filename="@(path_prefix)runtime/linker.h" />
  // 810:       <Unit filename="@(path_prefix)runtime/memory.c">
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[9])->contents /* buf */;
  arguments->slots[1] = frame->slots[10] /* temp__1 */;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__80_47;
}
static void cont__80_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[9])->contents /* buf */ = arguments->slots[0];
  // 819: ... : ($filename)
  // 820:   without_prefix &filename prefix_path
  // 821:   without_prefix &filename '/'
  // 822:   write_to &buf "
  // 823:     @
  // 824:     
  // 825:         <Unit filename="@(path_prefix)@(filename)">
  // 826:           <Option compilerVar="CC" />
  // 827:         </Unit>
  frame->slots[10] /* temp__1 */ = create_closure(entry__80_48, 1);
  // 819: for_each c_sources: ($filename)
  // 820:   without_prefix &filename prefix_path
  // 821:   without_prefix &filename '/'
  // 822:   write_to &buf "
  // 823:     @
  // 824:     
  // 825:         <Unit filename="@(path_prefix)@(filename)">
  // 826:           <Option compilerVar="CC" />
  // 827:         </Unit>
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._c_sources;
  arguments->slots[1] = frame->slots[10] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__80_55;
}
static void entry__80_48(void) {
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
  // 820: without_prefix &filename prefix_path
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* filename */;
  arguments->slots[1] = frame->slots[1] /* prefix_path */;
  result_count = 1;
  myself = get__without_prefix();
  func = myself->type;
  frame->cont = cont__80_49;
}
static void cont__80_49(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* filename */ = arguments->slots[0];
  // 821: without_prefix &filename '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* filename */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__without_prefix();
  func = myself->type;
  frame->cont = cont__80_50;
}
static void cont__80_50(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* filename */ = arguments->slots[0];
  // 822: ... "
  // 823:   @
  // 824:   
  // 825:       <Unit filename="@(path_prefix)@(filename)">
  // 826:         <Option compilerVar="CC" />
  // 827:       </Unit>
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__80_51;
  arguments->slots[1] = frame->slots[3] /* path_prefix */;
  arguments->slots[2] = ((CELL *)frame->slots[0])->contents /* filename */;
  arguments->slots[3] = string__80_52;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__80_53;
}
static void cont__80_53(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 822: write_to &buf "
  // 823:   @
  // 824:   
  // 825:       <Unit filename="@(path_prefix)@(filename)">
  // 826:         <Option compilerVar="CC" />
  // 827:       </Unit>
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* buf */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__80_54;
}
static void cont__80_54(void) {
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
static void cont__80_55(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 828: write_to &buf "
  // 829:       <Extensions>
  // 830:         <code_completion />
  // 831:         <debugger />
  // 832:       </Extensions>
  // 833:     </Project>
  // 834:   </CodeBlocks_project_file>
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[9])->contents /* buf */;
  arguments->slots[1] = string__80_56;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__80_57;
}
static void cont__80_57(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[9])->contents /* buf */ = arguments->slots[0];
  // 835: save cbp_filename buf
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* cbp_filename */;
  arguments->slots[1] = ((CELL *)frame->slots[9])->contents /* buf */;
  result_count = frame->caller_result_count;
  myself = get__save();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__80_1_build_codeblocks_project(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 760: compile_exe: (mod_filename mod_name)
  // 761:   $codeblocks_path string(mod_filename ".codeblocks")
  // 762:   $info stat(codeblocks_path)
  // 763:   if info.is_defined:
  // 764:     ewrite "
  // 765:       The directory "@(codeblocks_path)" already exists!
  // 766:   if verbose: ewriteln "build Code::Blocks project in " codeblocks_path
  // 767:   compile_module mod_filename mod_name
  // 768:   show_file_list
  // 769:   $basename truncate_until(main_filename '/' -1) .without_suffix. ".sim"
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__80_2;
  result_count = frame->caller_result_count;
  myself = var._compile_exe;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__81_1_build_library(void) {
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
  // 838: ... action == "simrun"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._action;
  arguments->slots[1] = string__81_2;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__81_3;
}
static void cont__81_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 838: if action == "simrun": Error "Cannot run a directory!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__81_4;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__81_6;
}
static void entry__81_4(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 838: ... Error "Cannot run a directory!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__81_5;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__81_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 840: if
  // 841:   do_extract_documentation:
  // 842:     extract_documentation main_filename
  // 843:   :
  // 844:     $$version ""
  // 845:     $$so_version ""
  // 846:     $version_filename string(main_filename "/VERSION")
  // 847:     if file_exists(version_filename):
  // 848:       !version string('-' load(version_filename).trim)
  // 849:       !so_version version .truncate_from. '.'
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__do_extract_documentation();
  arguments->slots[1] = func__81_7;
  arguments->slots[2] = func__81_8;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__81_86;
}
static void entry__81_84(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // err: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* err */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 910: ... err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* err */;
  result_count = 1;
  myself = get__from_utf8();
  func = myself->type;
  frame->cont = cont__81_85;
}
static void cont__81_85(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 910: ... Error err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__81_79(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // err: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* err */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 903: ... err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* err */;
  result_count = 1;
  myself = get__from_utf8();
  func = myself->type;
  frame->cont = cont__81_80;
}
static void cont__81_80(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 903: ... Error err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__81_70(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // err: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* err */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 892: ... err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* err */;
  result_count = 1;
  myself = get__from_utf8();
  func = myself->type;
  frame->cont = cont__81_71;
}
static void cont__81_71(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 892: ... Error err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__81_63(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // err: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* err */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 884: ... err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* err */;
  result_count = 1;
  myself = get__from_utf8();
  func = myself->type;
  frame->cont = cont__81_64;
}
static void cont__81_64(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 884: ... Error err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__81_57(void) {
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
  // 880: "-Wl,-soname,libsim-@(base_filename)@(so_version).so.@(MAJOR)"
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__81_58;
  arguments->slots[1] = frame->slots[0] /* base_filename */;
  arguments->slots[2] = ((CELL *)frame->slots[1])->contents /* so_version */;
  arguments->slots[3] = string__74_26;
  arguments->slots[4] = var._MAJOR;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__81_59;
}
static void cont__81_59(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 881: library_paths_and_file_list()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = var._library_paths_and_file_list;
  func = myself->type;
  frame->cont = cont__81_60;
}
static void cont__81_60(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 878: Gcc $_out $err $success
  // 879:   "-shared"
  // 880:   "-Wl,-soname,libsim-@(base_filename)@(so_version).so.@(MAJOR)"
  // 881:   library_paths_and_file_list()*
  // 882:   "-o"
  // 883:   lib_filename
  argument_count = 0;
  arguments = node_p;
  arguments->slots[argument_count++] = string__81_61;
  arguments->slots[argument_count++] = frame->slots[6] /* temp__1 */;
  unfold(frame->slots[7] /* temp__2 */);
  arguments->slots[argument_count++] = string__67_6;
  arguments->slots[argument_count++] = frame->slots[2] /* lib_filename */;
  result_count = 3;
  myself = var._Gcc;
  func = myself->type;
  frame->cont = cont__81_62;
}
static void cont__81_62(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__3 */ = arguments->slots[0];
  frame->slots[9] /* temp__4 */ = arguments->slots[1];
  frame->slots[10] /* temp__5 */ = arguments->slots[2];
  // 878: ... _out
  initialize_future(frame->slots[3] /* out */, frame->slots[8] /* temp__3 */);
  // 878: ... err
  initialize_future(frame->slots[4] /* err */, frame->slots[9] /* temp__4 */);
  // 878: ... success
  initialize_future(frame->slots[5] /* success */, frame->slots[10] /* temp__5 */);
  // 884: ... : Error err.from_utf8
  frame->slots[6] /* temp__1 */ = create_closure(entry__81_63, 0);
  // 884: unless success: Error err.from_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* success */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__81_65(void) {
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
  // 888: library_paths_and_file_list()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = var._library_paths_and_file_list;
  func = myself->type;
  frame->cont = cont__81_66;
}
static void cont__81_66(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 889: "-lsim-@(MAJOR)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__81_67;
  arguments->slots[1] = var._MAJOR;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__81_68;
}
static void cont__81_68(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 886: Gcc $_out $err $success
  // 887:   "-shared"
  // 888:   library_paths_and_file_list()*
  // 889:   "-lsim-@(MAJOR)"
  // 890:   "-o"
  // 891:   lib_filename
  argument_count = 0;
  arguments = node_p;
  arguments->slots[argument_count++] = string__81_61;
  unfold(frame->slots[4] /* temp__1 */);
  arguments->slots[argument_count++] = frame->slots[5] /* temp__2 */;
  arguments->slots[argument_count++] = string__67_6;
  arguments->slots[argument_count++] = frame->slots[0] /* lib_filename */;
  result_count = 3;
  myself = var._Gcc;
  func = myself->type;
  frame->cont = cont__81_69;
}
static void cont__81_69(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  frame->slots[7] /* temp__4 */ = arguments->slots[1];
  frame->slots[8] /* temp__5 */ = arguments->slots[2];
  // 886: ... _out
  initialize_future(frame->slots[1] /* out */, frame->slots[6] /* temp__3 */);
  // 886: ... err
  initialize_future(frame->slots[2] /* err */, frame->slots[7] /* temp__4 */);
  // 886: ... success
  initialize_future(frame->slots[3] /* success */, frame->slots[8] /* temp__5 */);
  // 892: ... : Error err.from_utf8
  frame->slots[4] /* temp__1 */ = create_closure(entry__81_70, 0);
  // 892: unless success: Error err.from_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* success */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__81_72(void) {
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
  // 896: "
  // 897:   -Wl,-install_name,libsim-@(base_filename)@(so_version)-@(MAJOR)@
  // 898:   .dylib@
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = string__81_73;
  arguments->slots[1] = frame->slots[0] /* base_filename */;
  arguments->slots[2] = ((CELL *)frame->slots[1])->contents /* so_version */;
  arguments->slots[3] = string__64_46;
  arguments->slots[4] = var._MAJOR;
  arguments->slots[5] = string__81_29;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__81_74;
}
static void cont__81_74(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 899: library_paths_and_file_list()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = var._library_paths_and_file_list;
  func = myself->type;
  frame->cont = cont__81_75;
}
static void cont__81_75(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 900: "-lsim-@(MAJOR)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__81_67;
  arguments->slots[1] = var._MAJOR;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__81_76;
}
static void cont__81_76(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__3 */ = arguments->slots[0];
  // 894: Gcc $_out $err $success
  // 895:   "-dynamiclib"
  // 896:   "
  // 897:     -Wl,-install_name,libsim-@(base_filename)@(so_version)-@(MAJOR)@
  // 898:     .dylib@
  // 899:   library_paths_and_file_list()*
  // 900:   "-lsim-@(MAJOR)"
  // 901:   "-o"
  // 902:   lib_filename
  argument_count = 0;
  arguments = node_p;
  arguments->slots[argument_count++] = string__81_77;
  arguments->slots[argument_count++] = frame->slots[6] /* temp__1 */;
  unfold(frame->slots[7] /* temp__2 */);
  arguments->slots[argument_count++] = frame->slots[8] /* temp__3 */;
  arguments->slots[argument_count++] = string__67_6;
  arguments->slots[argument_count++] = frame->slots[2] /* lib_filename */;
  result_count = 3;
  myself = var._Gcc;
  func = myself->type;
  frame->cont = cont__81_78;
}
static void cont__81_78(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__4 */ = arguments->slots[0];
  frame->slots[10] /* temp__5 */ = arguments->slots[1];
  frame->slots[11] /* temp__6 */ = arguments->slots[2];
  // 894: ... _out
  initialize_future(frame->slots[3] /* out */, frame->slots[9] /* temp__4 */);
  // 894: ... err
  initialize_future(frame->slots[4] /* err */, frame->slots[10] /* temp__5 */);
  // 894: ... success
  initialize_future(frame->slots[5] /* success */, frame->slots[11] /* temp__6 */);
  // 903: ... : Error err.from_utf8
  frame->slots[6] /* temp__1 */ = create_closure(entry__81_79, 0);
  // 903: unless success: Error err.from_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* success */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__81_81(void) {
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
  // 907: library_paths_and_file_list()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = var._library_paths_and_file_list;
  func = myself->type;
  frame->cont = cont__81_82;
}
static void cont__81_82(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 905: Gcc $_out $err $success
  // 906:   "-shared"
  // 907:   library_paths_and_file_list()*
  // 908:   "-o"
  // 909:   lib_filename
  argument_count = 0;
  arguments = node_p;
  arguments->slots[argument_count++] = string__81_61;
  unfold(frame->slots[4] /* temp__1 */);
  arguments->slots[argument_count++] = string__67_6;
  arguments->slots[argument_count++] = frame->slots[0] /* lib_filename */;
  result_count = 3;
  myself = var._Gcc;
  func = myself->type;
  frame->cont = cont__81_83;
}
static void cont__81_83(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  frame->slots[6] /* temp__3 */ = arguments->slots[1];
  frame->slots[7] /* temp__4 */ = arguments->slots[2];
  // 905: ... _out
  initialize_future(frame->slots[1] /* out */, frame->slots[5] /* temp__2 */);
  // 905: ... err
  initialize_future(frame->slots[2] /* err */, frame->slots[6] /* temp__3 */);
  // 905: ... success
  initialize_future(frame->slots[3] /* success */, frame->slots[7] /* temp__4 */);
  // 910: ... : Error err.from_utf8
  frame->slots[4] /* temp__1 */ = create_closure(entry__81_84, 0);
  // 910: unless success: Error err.from_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* success */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__81_53(void) {
  allocate_initialized_frame_gc(3, 7);
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
  // 874: if verbose: ewriteln "linking dynamic library"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = func__81_54;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__81_56;
}
static void entry__81_54(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 874: ... ewriteln "linking dynamic library"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__81_55;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__81_56(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 877: ... :
  // 878:   Gcc $_out $err $success
  // 879:     "-shared"
  // 880:     "-Wl,-soname,libsim-@(base_filename)@(so_version).so.@(MAJOR)"
  // 881:     library_paths_and_file_list()*
  // 882:     "-o"
  // 883:     lib_filename
  // 884:   unless success: Error err.from_utf8
  frame->slots[3] /* temp__1 */ = create_closure(entry__81_57, 0);
  // 885: ... :
  // 886:   Gcc $_out $err $success
  // 887:     "-shared"
  // 888:     library_paths_and_file_list()*
  // 889:     "-lsim-@(MAJOR)"
  // 890:     "-o"
  // 891:     lib_filename
  // 892:   unless success: Error err.from_utf8
  frame->slots[4] /* temp__2 */ = create_closure(entry__81_65, 0);
  // 893: ... :
  // 894:   Gcc $_out $err $success
  // 895:     "-dynamiclib"
  // 896:     "
  // 897:       -Wl,-install_name,libsim-@(base_filename)@(so_version)-@(MAJOR)@
  // 898:       .dylib@
  // 899:     library_paths_and_file_list()*
  // 900:     "-lsim-@(MAJOR)"
  // 901:     "-o"
  // 902:     lib_filename
  // ...
  frame->slots[5] /* temp__3 */ = create_closure(entry__81_72, 0);
  // 904: :
  // 905:   Gcc $_out $err $success
  // 906:     "-shared"
  // 907:     library_paths_and_file_list()*
  // 908:     "-o"
  // 909:     lib_filename
  // 910:   unless success: Error err.from_utf8
  frame->slots[6] /* temp__4 */ = create_closure(entry__81_81, 0);
  // 875: case
  // 876:   current_platform
  // 877:   "linux":
  // 878:     Gcc $_out $err $success
  // 879:       "-shared"
  // 880:       "-Wl,-soname,libsim-@(base_filename)@(so_version).so.@(MAJOR)"
  // 881:       library_paths_and_file_list()*
  // 882:       "-o"
  // 883:       lib_filename
  // 884:     unless success: Error err.from_utf8
  // ...
  argument_count = 8;
  arguments = node_p;
  arguments->slots[0] = get__current_platform();
  arguments->slots[1] = string__74_22;
  arguments->slots[2] = frame->slots[3] /* temp__1 */;
  arguments->slots[3] = string__81_35;
  arguments->slots[4] = frame->slots[4] /* temp__2 */;
  arguments->slots[5] = string__81_36;
  arguments->slots[6] = frame->slots[5] /* temp__3 */;
  arguments->slots[7] = frame->slots[6] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__81_7(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 842: extract_documentation main_filename
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  result_count = frame->caller_result_count;
  myself = get__extract_documentation();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__81_8(void) {
  allocate_initialized_frame_gc(0, 9);
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
  // 844: $$version ""
  ((CELL *)frame->slots[0])->contents /* version */ = empty_string;
  // 845: $$so_version ""
  ((CELL *)frame->slots[1])->contents /* so_version */ = empty_string;
  // 846: $version_filename string(main_filename "/VERSION")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  arguments->slots[1] = string__81_9;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__81_10;
}
static void cont__81_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* version_filename */, arguments->slots[0]);
  // 847: ... file_exists(version_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* version_filename */;
  result_count = 1;
  myself = get__file_exists();
  func = myself->type;
  frame->cont = cont__81_11;
}
static void cont__81_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 847: ... :
  // 848:   !version string('-' load(version_filename).trim)
  // 849:   !so_version version .truncate_from. '.'
  frame->slots[6] /* temp__2 */ = create_closure(entry__81_12, 0);
  // 847: if file_exists(version_filename):
  // 848:   !version string('-' load(version_filename).trim)
  // 849:   !so_version version .truncate_from. '.'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__81_17;
}
static void entry__81_12(void) {
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
  // 848: ... load(version_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* version_filename */;
  result_count = 1;
  myself = get__load();
  func = myself->type;
  frame->cont = cont__81_13;
}
static void cont__81_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 848: ... load(version_filename).trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__81_14;
}
static void cont__81_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 848: !version string('-' load(version_filename).trim)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__45;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__81_15;
}
static void cont__81_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* version */ = arguments->slots[0];
  // 849: !so_version version .truncate_from. '.'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* version */;
  arguments->slots[1] = character__46;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__81_16;
}
static void cont__81_16(void) {
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
static void cont__81_17(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 850: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__81_18;
}
static void cont__81_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 850: $base_filename truncate_until(main_filename '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__81_19;
}
static void cont__81_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* base_filename */, arguments->slots[0]);
  // 856: -> string("libsim-" base_filename version ".so.@(MAJOR)")
  frame->slots[5] /* temp__1 */ = create_closure(entry__81_20, 0);
  // 858: -> string("libsim-" base_filename version "-@(MAJOR).dll")
  frame->slots[6] /* temp__2 */ = create_closure(entry__81_24, 0);
  // 860: -> string("libsim-" base_filename version "-@(MAJOR).dylib")
  frame->slots[7] /* temp__3 */ = create_closure(entry__81_28, 0);
  // 861: -> string("libsim-" base_filename ".so")
  frame->slots[8] /* temp__4 */ = create_closure(entry__81_32, 0);
  // 852: $lib_filename
  // 853:   case
  // 854:     current_platform
  // 855:     "linux"
  // 856:     -> string("libsim-" base_filename version ".so.@(MAJOR)")
  // 857:     "cygwin"
  // 858:     -> string("libsim-" base_filename version "-@(MAJOR).dll")
  // 859:     "darwin"
  // 860:     -> string("libsim-" base_filename version "-@(MAJOR).dylib")
  // 861:     -> string("libsim-" base_filename ".so")
  argument_count = 8;
  arguments = node_p;
  arguments->slots[0] = get__current_platform();
  arguments->slots[1] = string__74_22;
  arguments->slots[2] = frame->slots[5] /* temp__1 */;
  arguments->slots[3] = string__81_35;
  arguments->slots[4] = frame->slots[6] /* temp__2 */;
  arguments->slots[5] = string__81_36;
  arguments->slots[6] = frame->slots[7] /* temp__3 */;
  arguments->slots[7] = frame->slots[8] /* temp__4 */;
  result_count = 1;
  myself = get__case();
  func = myself->type;
  frame->cont = cont__81_37;
}
static void entry__81_20(void) {
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
  // 856: ... ".so.@(MAJOR)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__74_26;
  arguments->slots[1] = var._MAJOR;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__81_21;
}
static void cont__81_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 856: ... string("libsim-" base_filename version ".so.@(MAJOR)")
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__81_22;
  arguments->slots[1] = frame->slots[0] /* base_filename */;
  arguments->slots[2] = ((CELL *)frame->slots[1])->contents /* version */;
  arguments->slots[3] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__81_23;
}
static void cont__81_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 856: -> string("libsim-" base_filename version ".so.@(MAJOR)")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__81_24(void) {
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
  // 858: ... "-@(MAJOR).dll"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__64_46;
  arguments->slots[1] = var._MAJOR;
  arguments->slots[2] = string__81_25;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__81_26;
}
static void cont__81_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 858: ... string("libsim-" base_filename version "-@(MAJOR).dll")
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__81_22;
  arguments->slots[1] = frame->slots[0] /* base_filename */;
  arguments->slots[2] = ((CELL *)frame->slots[1])->contents /* version */;
  arguments->slots[3] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__81_27;
}
static void cont__81_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 858: -> string("libsim-" base_filename version "-@(MAJOR).dll")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__81_28(void) {
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
  // 860: ... "-@(MAJOR).dylib"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__64_46;
  arguments->slots[1] = var._MAJOR;
  arguments->slots[2] = string__81_29;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__81_30;
}
static void cont__81_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 860: ... string("libsim-" base_filename version "-@(MAJOR).dylib")
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__81_22;
  arguments->slots[1] = frame->slots[0] /* base_filename */;
  arguments->slots[2] = ((CELL *)frame->slots[1])->contents /* version */;
  arguments->slots[3] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__81_31;
}
static void cont__81_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 860: -> string("libsim-" base_filename version "-@(MAJOR).dylib")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__81_32(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // base_filename: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* base_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 861: ... string("libsim-" base_filename ".so")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__81_22;
  arguments->slots[1] = frame->slots[0] /* base_filename */;
  arguments->slots[2] = string__81_33;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__81_34;
}
static void cont__81_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 861: -> string("libsim-" base_filename ".so")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__81_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* lib_filename */, arguments->slots[0]);
  // 863: ... : ewriteln "build library " lib_filename
  frame->slots[5] /* temp__1 */ = create_closure(entry__81_38, 0);
  // 863: if verbose: ewriteln "build library " lib_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__81_40;
}
static void entry__81_38(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // lib_filename: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* lib_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 863: ... ewriteln "build library " lib_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__81_39;
  arguments->slots[1] = frame->slots[0] /* lib_filename */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__81_40(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 864: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__81_41;
}
static void cont__81_41(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 864: ... behind(main_filename '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__81_42;
}
static void cont__81_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 864: compile_modules main_filename behind(main_filename '/' -1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = var._compile_modules;
  func = myself->type;
  frame->cont = cont__81_43;
}
static void cont__81_43(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 865: ... :
  // 866:   $info stat(lib_filename)
  // 867:   if
  // 868:     ||
  // 869:       info.is_undefined
  // 870:       last_modification_time > modification_time_of(info)
  // 871:     :
  // 872:       !do_link true
  frame->slots[5] /* temp__1 */ = create_closure(entry__81_44, 0);
  // 865: unless do_link:
  // 866:   $info stat(lib_filename)
  // 867:   if
  // 868:     ||
  // 869:       info.is_undefined
  // 870:       last_modification_time > modification_time_of(info)
  // 871:     :
  // 872:       !do_link true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_link();
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__81_52;
}
static void entry__81_51(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 872: !do_link true
  set__do_link(get__true());
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__81_44(void) {
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
  // 866: $info stat(lib_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* lib_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__81_45;
}
static void cont__81_45(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* info */, arguments->slots[0]);
  // 869: info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__81_46;
}
static void cont__81_46(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 870: last_modification_time > modification_time_of(info)
  frame->slots[4] /* temp__3 */ = create_closure(entry__81_47, 0);
  // 868: ||
  // 869:   info.is_undefined
  // 870:   last_modification_time > modification_time_of(info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__81_50;
}
static void entry__81_47(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // info: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 870: ... modification_time_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__81_48;
}
static void cont__81_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 870: last_modification_time > modification_time_of(info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = get__last_modification_time();
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__81_49;
}
static void cont__81_49(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 870: last_modification_time > modification_time_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__81_50(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 867: if
  // 868:   ||
  // 869:     info.is_undefined
  // 870:     last_modification_time > modification_time_of(info)
  // 871:   :
  // 872:     !do_link true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = func__81_51;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__81_52(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 873: ... :
  // 874:   if verbose: ewriteln "linking dynamic library"
  // 875:   case
  // 876:     current_platform
  // 877:     "linux":
  // 878:       Gcc $_out $err $success
  // 879:         "-shared"
  // 880:         "-Wl,-soname,libsim-@(base_filename)@(so_version).so.@(MAJOR)"
  // 881:         library_paths_and_file_list()*
  // 882:         "-o"
  // ...
  frame->slots[5] /* temp__1 */ = create_closure(entry__81_53, 0);
  // 873: if do_link:
  // 874:   if verbose: ewriteln "linking dynamic library"
  // 875:   case
  // 876:     current_platform
  // 877:     "linux":
  // 878:       Gcc $_out $err $success
  // 879:         "-shared"
  // 880:         "-Wl,-soname,libsim-@(base_filename)@(so_version).so.@(MAJOR)"
  // 881:         library_paths_and_file_list()*
  // 882:         "-o"
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
static void cont__81_86(void) {
  myself = frame->slots[0] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__82_18(void) {
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
  // 925: ... : ewriteln "compiling runtime module @(filename)"
  frame->slots[3] /* temp__1 */ = create_closure(entry__82_19, 0);
  // 925: if verbose: ewriteln "compiling runtime module @(filename)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__82_22;
}
static void entry__82_19(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // filename: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 925: ... "compiling runtime module @(filename)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__82_20;
  arguments->slots[1] = frame->slots[0] /* filename */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__82_21;
}
static void cont__82_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 925: ... ewriteln "compiling runtime module @(filename)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__82_22(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 926: compile_c c_filename o_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* c_filename */;
  arguments->slots[1] = frame->slots[2] /* o_filename */;
  result_count = frame->caller_result_count;
  myself = var._compile_c;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__82_1_maybe_compile_c_file(void) {
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
  // 913: $c_filename string(filename ".c")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  arguments->slots[1] = string__68_9;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__82_2;
}
static void cont__82_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* c_filename */, arguments->slots[0]);
  // 914: $o_filename string(filename ".o")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  arguments->slots[1] = string__70_80;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__82_3;
}
static void cont__82_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* o_filename */, arguments->slots[0]);
  // 915: $c_info stat(c_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* c_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__82_4;
}
static void cont__82_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* c_info */, arguments->slots[0]);
  // 916: ... c_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* c_info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__82_5;
}
static void cont__82_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 916: ... :
  // 917:   Error "
  // 918:     @quot;@(c_filename)" does not exist!
  frame->slots[6] /* temp__2 */ = create_closure(entry__82_6, 0);
  // 916: if c_info.is_undefined:
  // 917:   Error "
  // 918:     @quot;@(c_filename)" does not exist!
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__82_10;
}
static void entry__82_6(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // c_filename: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* c_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 917: ... "
  // 918:   @quot;@(c_filename)" does not exist!
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__82_7;
  arguments->slots[1] = frame->slots[0] /* c_filename */;
  arguments->slots[2] = string__82_8;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__82_9;
}
static void cont__82_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 917: Error "
  // 918:   @quot;@(c_filename)" does not exist!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__82_10(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 919: $o_info stat(o_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* o_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__82_11;
}
static void cont__82_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* o_info */, arguments->slots[0]);
  // 922: o_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* o_info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__82_12;
}
static void cont__82_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 923: modification_time_of(c_info) > modification_time_of(o_info)
  frame->slots[7] /* temp__3 */ = create_closure(entry__82_13, 0);
  // 921: ||
  // 922:   o_info.is_undefined
  // 923:   modification_time_of(c_info) > modification_time_of(o_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__82_17;
}
static void entry__82_13(void) {
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
  // 923: ... modification_time_of(o_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* o_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__82_14;
}
static void cont__82_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 923: modification_time_of(c_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* c_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__82_15;
}
static void cont__82_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 923: modification_time_of(c_info) > modification_time_of(o_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__82_16;
}
static void cont__82_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 923: modification_time_of(c_info) > modification_time_of(o_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__82_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 924: :
  // 925:   if verbose: ewriteln "compiling runtime module @(filename)"
  // 926:   compile_c c_filename o_filename
  frame->slots[8] /* temp__4 */ = create_closure(entry__82_18, 0);
  // 920: if
  // 921:   ||
  // 922:     o_info.is_undefined
  // 923:     modification_time_of(c_info) > modification_time_of(o_info)
  // 924:   :
  // 925:     if verbose: ewriteln "compiling runtime module @(filename)"
  // 926:     compile_c c_filename o_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__84_1_format_number(void) {
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
  // 936: to_string &val
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* val */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__84_2;
}
static void cont__84_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* val */ = arguments->slots[0];
  // 937: $$ac 0
  ((CELL *)frame->slots[3])->contents /* ac */ = number__0;
  // 938: ... : (-> break)
  // 939:   for_each val: (i chr)
  // 940:     if chr == '.':
  // 941:       !ac length_of(val)-i
  // 942:       if n > i-1: append dup(" " n-(i-1)) &val
  // 943:       break
  frame->slots[4] /* temp__1 */ = create_closure(entry__84_3, 0);
  // 938: do: (-> break)
  // 939:   for_each val: (i chr)
  // 940:     if chr == '.':
  // 941:       !ac length_of(val)-i
  // 942:       if n > i-1: append dup(" " n-(i-1)) &val
  // 943:       break
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__84_19;
}
static void entry__84_3(void) {
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
  // 939: ... : (i chr)
  // 940:   if chr == '.':
  // 941:     !ac length_of(val)-i
  // 942:     if n > i-1: append dup(" " n-(i-1)) &val
  // 943:     break
  frame->slots[4] /* temp__1 */ = create_closure(entry__84_4, 2);
  // 939: for_each val: (i chr)
  // 940:   if chr == '.':
  // 941:     !ac length_of(val)-i
  // 942:     if n > i-1: append dup(" " n-(i-1)) &val
  // 943:     break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* val */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__84_18;
}
static void entry__84_6(void) {
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
  // 941: ... length_of(val)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* val */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__84_7;
}
static void cont__84_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 941: !ac length_of(val)-i
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* i */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__84_8;
}
static void cont__84_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* ac */ = arguments->slots[0];
  // 942: ... i-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* i */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__84_9;
}
static void cont__84_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 942: ... n > i-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* n */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__84_10;
}
static void cont__84_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 942: ... : append dup(" " n-(i-1)) &val
  frame->slots[7] /* temp__3 */ = create_closure(entry__84_11, 0);
  // 942: if n > i-1: append dup(" " n-(i-1)) &val
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__84_17;
}
static void entry__84_11(void) {
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
  // 942: ... i-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* i */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__84_12;
}
static void cont__84_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 942: ... n-(i-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* n */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__84_13;
}
static void cont__84_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 942: ... dup(" " n-(i-1))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__84_14;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__84_15;
}
static void cont__84_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 942: ... append dup(" " n-(i-1)) &val
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* val */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__84_16;
}
static void cont__84_16(void) {
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
static void cont__84_17(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 943: break
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[4] /* break */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__84_4(void) {
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
  // 940: ... chr == '.'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* chr */;
  arguments->slots[1] = character__46;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__84_5;
}
static void cont__84_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 940: ... :
  // 941:   !ac length_of(val)-i
  // 942:   if n > i-1: append dup(" " n-(i-1)) &val
  // 943:   break
  frame->slots[7] /* temp__2 */ = create_closure(entry__84_6, 0);
  // 940: if chr == '.':
  // 941:   !ac length_of(val)-i
  // 942:   if n > i-1: append dup(" " n-(i-1)) &val
  // 943:   break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__84_18(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__84_19(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 945: m > ac
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* ac */;
  arguments->slots[1] = frame->slots[2] /* m */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__84_20;
}
static void cont__84_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 945: ... :
  // 946:   append &val dup("0" m-ac)
  frame->slots[5] /* temp__2 */ = create_closure(entry__84_21, 0);
  // 947: :
  // 948:   if ac > m: range &val 1 -(ac-m+1)
  frame->slots[6] /* temp__3 */ = create_closure(entry__84_26, 0);
  // 944: if
  // 945:   m > ac:
  // 946:     append &val dup("0" m-ac)
  // 947:   :
  // 948:     if ac > m: range &val 1 -(ac-m+1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__84_33;
}
static void entry__84_28(void) {
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
  // 948: ... ac-m
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* ac */;
  arguments->slots[1] = frame->slots[2] /* m */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__84_29;
}
static void cont__84_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 948: ... ac-m+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__84_30;
}
static void cont__84_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 948: ... ac-m+1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__84_31;
}
static void cont__84_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 948: ... range &val 1 -(ac-m+1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* val */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__84_32;
}
static void cont__84_32(void) {
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
static void entry__84_21(void) {
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
  // 946: ... m-ac
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* m */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* ac */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__84_22;
}
static void cont__84_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 946: ... dup("0" m-ac)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__84_23;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__84_24;
}
static void cont__84_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 946: append &val dup("0" m-ac)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* val */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__84_25;
}
static void cont__84_25(void) {
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
static void entry__84_26(void) {
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
  // 948: ... ac > m
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* m */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* ac */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__84_27;
}
static void cont__84_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 948: ... : range &val 1 -(ac-m+1)
  frame->slots[4] /* temp__2 */ = create_closure(entry__84_28, 0);
  // 948: if ac > m: range &val 1 -(ac-m+1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__84_33(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 949: -> val
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* val */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__85_1_sim2c__write_timing_info(void) {
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
  // 952: $new_t current_time()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__current_time();
  func = myself->type;
  frame->cont = cont__85_2;
}
static void cont__85_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* new_t */, arguments->slots[0]);
  // 954: filename.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* filename */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__85_3;
}
static void cont__85_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 954: ... :
  // 955:   truncate_until &filename '/' -1
  // 956:   ewriteln
  // 957:     description
  // 958:     ' '
  // 959:     filename
  // 960:     ':'
  // 961:     dup(" " 12-length_of(description))
  // 962:     format_number(new_t-t 2 3)
  // 963:     " s"
  frame->slots[4] /* temp__2 */ = create_closure(entry__85_4, 0);
  // 964: :
  // 965:   ewriteln description ": " format_number(new_t-t 0 3) " s"
  frame->slots[5] /* temp__3 */ = create_closure(entry__85_13, 0);
  // 953: if
  // 954:   filename.is_defined:
  // 955:     truncate_until &filename '/' -1
  // 956:     ewriteln
  // 957:       description
  // 958:       ' '
  // 959:       filename
  // 960:       ':'
  // 961:       dup(" " 12-length_of(description))
  // 962:       format_number(new_t-t 2 3)
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = frame->slots[5] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__85_17;
}
static void entry__85_4(void) {
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
  // 955: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__85_5;
}
static void cont__85_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 955: truncate_until &filename '/' -1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* filename */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__85_6;
}
static void cont__85_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* filename */ = arguments->slots[0];
  // 961: ... length_of(description)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* description */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__85_7;
}
static void cont__85_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 961: ... 12-length_of(description)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__12;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__85_8;
}
static void cont__85_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 961: dup(" " 12-length_of(description))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__84_14;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__85_9;
}
static void cont__85_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 962: ... new_t-t
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* new_t */;
  arguments->slots[1] = var._t;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__85_10;
}
static void cont__85_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__5 */ = arguments->slots[0];
  // 962: format_number(new_t-t 2 3)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__5 */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = number__3;
  result_count = 1;
  myself = var._format_number;
  func = myself->type;
  frame->cont = cont__85_11;
}
static void cont__85_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__4 */ = arguments->slots[0];
  // 956: ewriteln
  // 957:   description
  // 958:   ' '
  // 959:   filename
  // 960:   ':'
  // 961:   dup(" " 12-length_of(description))
  // 962:   format_number(new_t-t 2 3)
  // 963:   " s"
  argument_count = 7;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* description */;
  arguments->slots[1] = character__32;
  arguments->slots[2] = ((CELL *)frame->slots[0])->contents /* filename */;
  arguments->slots[3] = character__58;
  arguments->slots[4] = frame->slots[3] /* temp__1 */;
  arguments->slots[5] = frame->slots[6] /* temp__4 */;
  arguments->slots[6] = string__85_12;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__85_13(void) {
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
  // 965: ... new_t-t
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* new_t */;
  arguments->slots[1] = var._t;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__85_14;
}
static void cont__85_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 965: ... format_number(new_t-t 0 3)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = number__0;
  arguments->slots[2] = number__3;
  result_count = 1;
  myself = var._format_number;
  func = myself->type;
  frame->cont = cont__85_15;
}
static void cont__85_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 965: ewriteln description ": " format_number(new_t-t 0 3) " s"
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* description */;
  arguments->slots[1] = string__85_16;
  arguments->slots[2] = frame->slots[2] /* temp__1 */;
  arguments->slots[3] = string__85_12;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__85_17(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 966: !t current_time()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__current_time();
  func = myself->type;
  frame->cont = cont__85_18;
}
static void cont__85_18(void) {
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
static void entry__86_114(void) {
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
  // 1061: exe_filename .has_prefix. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* exe_filename */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__86_115;
}
static void cont__86_115(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 1062: -> exe_filename
  frame->slots[4] /* temp__3 */ = create_closure(entry__86_116, 0);
  // 1063: -> string("./" exe_filename)
  frame->slots[5] /* temp__4 */ = create_closure(entry__86_117, 0);
  // 1060: if
  // 1061:   exe_filename .has_prefix. '/'
  // 1062:   -> exe_filename
  // 1063:   -> string("./" exe_filename)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  arguments->slots[2] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__86_119;
}
static void entry__86_116(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // exe_filename: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* exe_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1062: -> exe_filename
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* exe_filename */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__86_117(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // exe_filename: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* exe_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1063: ... string("./" exe_filename)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__68_56;
  arguments->slots[1] = frame->slots[0] /* exe_filename */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__86_118;
}
static void cont__86_118(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1063: -> string("./" exe_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__86_119(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1059: exec
  // 1060:   if
  // 1061:     exe_filename .has_prefix. '/'
  // 1062:     -> exe_filename
  // 1063:     -> string("./" exe_filename)
  // 1064:   zz*
  // 1065:   
  // 1066:   #range(command_line_arguments 2 -1)*
  argument_count = 0;
  arguments = node_p;
  arguments->slots[argument_count++] = frame->slots[2] /* temp__1 */;
  unfold(frame->slots[1] /* zz */);
  result_count = frame->caller_result_count;
  myself = get__exec();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__86_2(void) {
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
  // 981: current_platform == "cygwin"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__current_platform();
  arguments->slots[1] = string__81_35;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__86_3;
}
static void cont__86_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 982: -> string(mod_filename ".exe")
  frame->slots[10] /* temp__2 */ = create_closure(entry__86_4, 0);
  // 983: -> mod_filename
  frame->slots[11] /* temp__3 */ = create_closure(entry__86_7, 0);
  // 979: $exe_filename
  // 980:   if
  // 981:     current_platform == "cygwin"
  // 982:     -> string(mod_filename ".exe")
  // 983:     -> mod_filename
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__2 */;
  arguments->slots[2] = frame->slots[11] /* temp__3 */;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__86_8;
}
static void entry__86_4(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // mod_filename: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* mod_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 982: ... string(mod_filename ".exe")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = string__86_5;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__86_6;
}
static void cont__86_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 982: -> string(mod_filename ".exe")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__86_7(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // mod_filename: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* mod_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 983: -> mod_filename
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__86_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* exe_filename */, arguments->slots[0]);
  // 985: ... : ewriteln "build executable " exe_filename
  frame->slots[9] /* temp__1 */ = create_closure(entry__86_9, 0);
  // 985: if verbose: ewriteln "build executable " exe_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__86_11;
}
static void entry__86_9(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // exe_filename: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* exe_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 985: ... ewriteln "build executable " exe_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__86_10;
  arguments->slots[1] = frame->slots[0] /* exe_filename */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__86_11(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 986: $c_filename string(mod_filename ".c")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = string__68_9;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__86_12;
}
static void cont__86_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* c_filename */, arguments->slots[0]);
  // 987: $o_filename string(mod_filename ".o")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = string__70_80;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__86_13;
}
static void cont__86_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* o_filename */, arguments->slots[0]);
  // 988: $sim_info stat(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__86_14;
}
static void cont__86_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* sim_info */, arguments->slots[0]);
  // 989: $c_info stat(c_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* c_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__86_15;
}
static void cont__86_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* c_info */, arguments->slots[0]);
  // 990: $$c_buf undefined
  ((CELL *)frame->slots[7])->contents /* c_buf */ = get__undefined();
  // 991: !objects(o_filename) true
  frame->slots[9] /* temp__1 */ = get__true();
  // 991: !objects(o_filename)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* o_filename */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = get__objects();
  func = myself->type;
  frame->cont = cont__86_16;
}
static void cont__86_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__objects(arguments->slots[0]);
  frame->slots[10] /* temp__2 */ = create_closure(entry__86_17, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_rebuild;
  arguments->slots[1] = frame->slots[10] /* temp__2 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__86_24;
}
static void entry__86_17(void) {
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
  // 995: c_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__86_18;
}
static void cont__86_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 996: modification_time_of(sim_info) > modification_time_of(c_info)
  frame->slots[4] /* temp__3 */ = create_closure(entry__86_19, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__86_23;
}
static void entry__86_19(void) {
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
  // 996: ... modification_time_of(c_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__86_20;
}
static void cont__86_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 996: modification_time_of(sim_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* sim_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__86_21;
}
static void cont__86_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 996: modification_time_of(sim_info) > modification_time_of(c_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__86_22;
}
static void cont__86_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 996: modification_time_of(sim_info) > modification_time_of(c_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__86_23(void) {
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
static void cont__86_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  //  997: :
  //  998:   %sim2c::module_name mod_name .without_suffix. some(".meta")
  //  999:   if verbose: ewriteln "build main module " module_name
  // 1000:   collect_output $c_source: sim2c list(main_filename) true
  // 1001:   collect_output !c_buf: create_imports c_source
  // 1002:   save c_filename c_buf.to_utf8
  // 1003:   if do_time_passes: write_timing_info "saving" c_filename
  // 1004:   compile_c c_filename o_filename
  // 1005:   if do_time_passes: write_timing_info "compiling" c_filename
  frame->slots[11] /* temp__3 */ = create_closure(entry__86_25, 0);
  // 1006: :
  // 1007:   load !c_buf c_filename
  // 1008:   $o_info stat(o_filename)
  // 1009:   if
  // 1010:     ||
  // 1011:       o_info.is_undefined
  // 1012:       modification_time_of(c_info) > modification_time_of(o_info)
  // 1013:     :
  // 1014:       compile_c c_filename o_filename
  // 1015:     :
  // ...
  frame->slots[12] /* temp__4 */ = create_closure(entry__86_45, 0);
  //  992: if
  //  993:   ||
  //  994:     do_rebuild
  //  995:     c_info.is_undefined
  //  996:     modification_time_of(sim_info) > modification_time_of(c_info)
  //  997:   :
  //  998:     %sim2c::module_name mod_name .without_suffix. some(".meta")
  //  999:     if verbose: ewriteln "build main module " module_name
  // 1000:     collect_output $c_source: sim2c list(main_filename) true
  // 1001:     collect_output !c_buf: create_imports c_source
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = frame->slots[11] /* temp__3 */;
  arguments->slots[2] = frame->slots[12] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__86_57;
}
static void entry__86_54(void) {
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
  // 1014: compile_c c_filename o_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_filename */;
  arguments->slots[1] = frame->slots[1] /* o_filename */;
  result_count = frame->caller_result_count;
  myself = var._compile_c;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__86_55(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // o_info: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* o_info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1016: !last_modification_time modification_time_of(o_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* o_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__86_56;
}
static void cont__86_56(void) {
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
static void entry__86_25(void) {
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
  // 998: ... some(".meta")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__64_16;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__86_26;
}
static void cont__86_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 998: %sim2c::module_name mod_name .without_suffix. some(".meta")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* mod_name */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = get__without_suffix();
  func = myself->type;
  frame->cont = cont__86_27;
}
static void cont__86_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(get__sim2c__module_name(), arguments->slots[0]);
  // 999: if verbose: ewriteln "build main module " module_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = func__86_28;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__86_30;
}
static void entry__86_28(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 999: ... ewriteln "build main module " module_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__86_29;
  arguments->slots[1] = get__module_name();
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__86_30(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1000: collect_output $c_source: sim2c list(main_filename) true
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__86_31;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__86_33;
}
static void entry__86_31(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1000: ... list(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__86_32;
}
static void cont__86_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1000: ... sim2c list(main_filename) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = get__true();
  result_count = frame->caller_result_count;
  myself = get__sim2c();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__86_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* c_source */, arguments->slots[0]);
  // 1001: ... : create_imports c_source
  frame->slots[6] /* temp__1 */ = create_closure(entry__86_34, 0);
  // 1001: collect_output !c_buf: create_imports c_source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__86_35;
}
static void entry__86_34(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // c_source: 0
  frame->slots[0] = myself->closure.frame->slots[5]; /* c_source */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1001: ... create_imports c_source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_source */;
  result_count = frame->caller_result_count;
  myself = var._create_imports;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__86_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* c_buf */ = arguments->slots[0];
  // 1002: ... c_buf.to_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* c_buf */;
  result_count = 1;
  myself = get__to_utf8();
  func = myself->type;
  frame->cont = cont__86_36;
}
static void cont__86_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 1002: save c_filename c_buf.to_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* c_filename */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 0;
  myself = get__save();
  func = myself->type;
  frame->cont = cont__86_37;
}
static void cont__86_37(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1003: ... : write_timing_info "saving" c_filename
  frame->slots[6] /* temp__1 */ = create_closure(entry__86_38, 0);
  // 1003: if do_time_passes: write_timing_info "saving" c_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__86_40;
}
static void entry__86_38(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // c_filename: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* c_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1003: ... write_timing_info "saving" c_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__86_39;
  arguments->slots[1] = frame->slots[0] /* c_filename */;
  result_count = frame->caller_result_count;
  myself = get__write_timing_info();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__86_40(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1004: compile_c c_filename o_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* c_filename */;
  arguments->slots[1] = frame->slots[4] /* o_filename */;
  result_count = 0;
  myself = var._compile_c;
  func = myself->type;
  frame->cont = cont__86_41;
}
static void cont__86_41(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1005: ... : write_timing_info "compiling" c_filename
  frame->slots[6] /* temp__1 */ = create_closure(entry__86_42, 0);
  // 1005: if do_time_passes: write_timing_info "compiling" c_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__86_44;
}
static void entry__86_42(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // c_filename: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* c_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1005: ... write_timing_info "compiling" c_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__86_43;
  arguments->slots[1] = frame->slots[0] /* c_filename */;
  result_count = frame->caller_result_count;
  myself = get__write_timing_info();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__86_44(void) {
  myself = frame->slots[0] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__86_45(void) {
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
  // 1007: load !c_buf c_filename
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* c_filename */;
  result_count = 1;
  myself = get__load();
  func = myself->type;
  frame->cont = cont__86_46;
}
static void cont__86_46(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* c_buf */ = arguments->slots[0];
  // 1008: $o_info stat(o_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* o_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__86_47;
}
static void cont__86_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* o_info */, arguments->slots[0]);
  // 1011: o_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* o_info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__86_48;
}
static void cont__86_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 1012: modification_time_of(c_info) > modification_time_of(o_info)
  frame->slots[7] /* temp__3 */ = create_closure(entry__86_49, 0);
  // 1010: ||
  // 1011:   o_info.is_undefined
  // 1012:   modification_time_of(c_info) > modification_time_of(o_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__86_53;
}
static void entry__86_49(void) {
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
  // 1012: ... modification_time_of(o_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* o_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__86_50;
}
static void cont__86_50(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 1012: modification_time_of(c_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* c_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__86_51;
}
static void cont__86_51(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 1012: modification_time_of(c_info) > modification_time_of(o_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__86_52;
}
static void cont__86_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1012: modification_time_of(c_info) > modification_time_of(o_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__86_53(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 1013: :
  // 1014:   compile_c c_filename o_filename
  frame->slots[8] /* temp__4 */ = create_closure(entry__86_54, 0);
  // 1015: :
  // 1016:   !last_modification_time modification_time_of(o_info)
  frame->slots[9] /* temp__5 */ = create_closure(entry__86_55, 0);
  // 1009: if
  // 1010:   ||
  // 1011:     o_info.is_undefined
  // 1012:     modification_time_of(c_info) > modification_time_of(o_info)
  // 1013:   :
  // 1014:     compile_c c_filename o_filename
  // 1015:   :
  // 1016:     !last_modification_time modification_time_of(o_info)
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
static void cont__86_57(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1017: build_dependencies mod_filename mod_name c_buf
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = frame->slots[1] /* mod_name */;
  arguments->slots[2] = ((CELL *)frame->slots[7])->contents /* c_buf */;
  result_count = 0;
  myself = var._build_dependencies;
  func = myself->type;
  frame->cont = cont__86_58;
}
static void cont__86_58(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1018: if do_build_static_executable:
  // 1019:   for_each
  // 1020:     "runtime/linker", "runtime/memory", "runtime/debugger": (filename)
  // 1021:       maybe_compile_c_file filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_build_static_executable();
  arguments->slots[1] = func__86_59;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__86_65;
}
static void entry__86_64(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // filename: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 1021: maybe_compile_c_file filename
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  result_count = frame->caller_result_count;
  myself = var._maybe_compile_c_file;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__86_59(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1020: "runtime/linker", "runtime/memory", "runtime/debugger"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__86_60;
  arguments->slots[1] = string__86_61;
  arguments->slots[2] = string__86_62;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__86_63;
}
static void cont__86_63(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1019: for_each
  // 1020:   "runtime/linker", "runtime/memory", "runtime/debugger": (filename)
  // 1021:     maybe_compile_c_file filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__86_64;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__86_65(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1022: ... :
  // 1023:   $info stat(exe_filename)
  // 1024:   if
  // 1025:     ||
  // 1026:       info.is_undefined
  // 1027:       &&
  // 1028:         last_modification_time.is_defined
  // 1029:         last_modification_time > modification_time_of(info)
  // 1030:     :
  // 1031:       !do_link true
  frame->slots[9] /* temp__1 */ = create_closure(entry__86_66, 0);
  // 1022: unless do_link:
  // 1023:   $info stat(exe_filename)
  // 1024:   if
  // 1025:     ||
  // 1026:       info.is_undefined
  // 1027:       &&
  // 1028:         last_modification_time.is_defined
  // 1029:         last_modification_time > modification_time_of(info)
  // 1030:     :
  // 1031:       !do_link true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_link();
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__86_77;
}
static void entry__86_76(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1031: !do_link true
  set__do_link(get__true());
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__86_66(void) {
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
  // 1023: $info stat(exe_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* exe_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__86_67;
}
static void cont__86_67(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* info */, arguments->slots[0]);
  // 1026: info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__86_68;
}
static void cont__86_68(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 1027: &&
  // 1028:   last_modification_time.is_defined
  // 1029:   last_modification_time > modification_time_of(info)
  frame->slots[4] /* temp__3 */ = create_closure(entry__86_69, 0);
  // 1025: ||
  // 1026:   info.is_undefined
  // 1027:   &&
  // 1028:     last_modification_time.is_defined
  // 1029:     last_modification_time > modification_time_of(info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__86_75;
}
static void entry__86_69(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // info: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1028: last_modification_time.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__last_modification_time();
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__86_70;
}
static void cont__86_70(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 1029: last_modification_time > modification_time_of(info)
  frame->slots[3] /* temp__3 */ = create_closure(entry__86_71, 0);
  // 1027: &&
  // 1028:   last_modification_time.is_defined
  // 1029:   last_modification_time > modification_time_of(info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__86_74;
}
static void entry__86_71(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // info: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1029: ... modification_time_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__86_72;
}
static void cont__86_72(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 1029: last_modification_time > modification_time_of(info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = get__last_modification_time();
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__86_73;
}
static void cont__86_73(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1029: last_modification_time > modification_time_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__86_74(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1027: &&
  // 1028:   last_modification_time.is_defined
  // 1029:   last_modification_time > modification_time_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__86_75(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1024: if
  // 1025:   ||
  // 1026:     info.is_undefined
  // 1027:     &&
  // 1028:       last_modification_time.is_defined
  // 1029:       last_modification_time > modification_time_of(info)
  // 1030:   :
  // 1031:     !do_link true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = func__86_76;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__86_77(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1032: ... :
  // 1033:   $$libs_and_files library_paths_and_file_list()
  // 1034:   if do_link_profiler: push &libs_and_files "/usr/lib/libprofiler.so.0"
  // 1035:   if
  // 1036:     do_build_static_executable:
  // 1037:       if verbose: ewriteln "linking static executable"
  // 1038:       Gcc $_out $err $success
  // 1039:         "runtime/linker.o"
  // 1040:         "runtime/memory.o"
  // 1041:         "runtime/debugger.o"
  // ...
  frame->slots[9] /* temp__1 */ = create_closure(entry__86_78, 0);
  // 1032: if do_link:
  // 1033:   $$libs_and_files library_paths_and_file_list()
  // 1034:   if do_link_profiler: push &libs_and_files "/usr/lib/libprofiler.so.0"
  // 1035:   if
  // 1036:     do_build_static_executable:
  // 1037:       if verbose: ewriteln "linking static executable"
  // 1038:       Gcc $_out $err $success
  // 1039:         "runtime/linker.o"
  // 1040:         "runtime/memory.o"
  // 1041:         "runtime/debugger.o"
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_link();
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__86_108;
}
static void entry__86_106(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // err: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* err */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1056: ... err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* err */;
  result_count = 1;
  myself = get__from_utf8();
  func = myself->type;
  frame->cont = cont__86_107;
}
static void cont__86_107(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1056: ... Error err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__86_92(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // err: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* err */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1045: ... err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* err */;
  result_count = 1;
  myself = get__from_utf8();
  func = myself->type;
  frame->cont = cont__86_93;
}
static void cont__86_93(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1045: ... Error err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__86_84(void) {
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
  // 1037: if verbose: ewriteln "linking static executable"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = func__86_85;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__86_87;
}
static void entry__86_85(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1037: ... ewriteln "linking static executable"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__86_86;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__86_87(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1038: Gcc $_out $err $success
  // 1039:   "runtime/linker.o"
  // 1040:   "runtime/memory.o"
  // 1041:   "runtime/debugger.o"
  // 1042:   libs_and_files*
  // 1043:   "-o"
  // 1044:   exe_filename
  argument_count = 0;
  arguments = node_p;
  arguments->slots[argument_count++] = string__86_88;
  arguments->slots[argument_count++] = string__86_89;
  arguments->slots[argument_count++] = string__86_90;
  unfold(((CELL *)frame->slots[0])->contents /* libs_and_files */);
  arguments->slots[argument_count++] = string__67_6;
  arguments->slots[argument_count++] = frame->slots[1] /* exe_filename */;
  result_count = 3;
  myself = var._Gcc;
  func = myself->type;
  frame->cont = cont__86_91;
}
static void cont__86_91(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  frame->slots[6] /* temp__2 */ = arguments->slots[1];
  frame->slots[7] /* temp__3 */ = arguments->slots[2];
  // 1038: ... _out
  initialize_future(frame->slots[2] /* out */, frame->slots[5] /* temp__1 */);
  // 1038: ... err
  initialize_future(frame->slots[3] /* err */, frame->slots[6] /* temp__2 */);
  // 1038: ... success
  initialize_future(frame->slots[4] /* success */, frame->slots[7] /* temp__3 */);
  // 1045: ... : Error err.from_utf8
  frame->slots[5] /* temp__1 */ = create_closure(entry__86_92, 0);
  // 1045: unless success: Error err.from_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* success */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__86_94(void) {
  allocate_initialized_frame_gc(2, 10);
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
  // 1047: if verbose: ewriteln "linking executable"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = func__86_95;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__86_97;
}
static void entry__86_95(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1047: ... ewriteln "linking executable"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__86_96;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__86_97(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1051: current_platform == "linux"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__current_platform();
  arguments->slots[1] = string__74_22;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__86_98;
}
static void cont__86_98(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 1050: if
  // 1051:   current_platform == "linux"
  // 1052:   -> "-l:libsim.so.@(MAJOR)"
  // 1053:   -> "-lsim-@(MAJOR)"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = func__86_99;
  arguments->slots[2] = func__86_102;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__86_104;
}
static void entry__86_99(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1052: ... "-l:libsim.so.@(MAJOR)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__86_100;
  arguments->slots[1] = var._MAJOR;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__86_101;
}
static void cont__86_101(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1052: -> "-l:libsim.so.@(MAJOR)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__86_102(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1053: ... "-lsim-@(MAJOR)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__81_67;
  arguments->slots[1] = var._MAJOR;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__86_103;
}
static void cont__86_103(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1053: -> "-lsim-@(MAJOR)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__86_104(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 1048: Gcc $_out $err $success
  // 1049:   libs_and_files*
  // 1050:   if
  // 1051:     current_platform == "linux"
  // 1052:     -> "-l:libsim.so.@(MAJOR)"
  // 1053:     -> "-lsim-@(MAJOR)"
  // 1054:   "-o"
  // 1055:   exe_filename
  argument_count = 0;
  arguments = node_p;
  unfold(((CELL *)frame->slots[0])->contents /* libs_and_files */);
  arguments->slots[argument_count++] = frame->slots[5] /* temp__1 */;
  arguments->slots[argument_count++] = string__67_6;
  arguments->slots[argument_count++] = frame->slots[1] /* exe_filename */;
  result_count = 3;
  myself = var._Gcc;
  func = myself->type;
  frame->cont = cont__86_105;
}
static void cont__86_105(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__3 */ = arguments->slots[0];
  frame->slots[8] /* temp__4 */ = arguments->slots[1];
  frame->slots[9] /* temp__5 */ = arguments->slots[2];
  // 1048: ... _out
  initialize_future(frame->slots[2] /* out */, frame->slots[7] /* temp__3 */);
  // 1048: ... err
  initialize_future(frame->slots[3] /* err */, frame->slots[8] /* temp__4 */);
  // 1048: ... success
  initialize_future(frame->slots[4] /* success */, frame->slots[9] /* temp__5 */);
  // 1056: ... : Error err.from_utf8
  frame->slots[5] /* temp__1 */ = create_closure(entry__86_106, 0);
  // 1056: unless success: Error err.from_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* success */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__86_78(void) {
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
  // 1033: $$libs_and_files library_paths_and_file_list()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = var._library_paths_and_file_list;
  func = myself->type;
  frame->cont = cont__86_79;
}
static void cont__86_79(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* libs_and_files */ = arguments->slots[0];
  // 1034: ... : push &libs_and_files "/usr/lib/libprofiler.so.0"
  frame->slots[2] /* temp__1 */ = create_closure(entry__86_80, 0);
  // 1034: if do_link_profiler: push &libs_and_files "/usr/lib/libprofiler.so.0"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_link_profiler;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__86_83;
}
static void entry__86_80(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // libs_and_files: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* libs_and_files */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1034: ... push &libs_and_files "/usr/lib/libprofiler.so.0"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* libs_and_files */;
  arguments->slots[1] = string__86_81;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__86_82;
}
static void cont__86_82(void) {
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
static void cont__86_83(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1036: ... :
  // 1037:   if verbose: ewriteln "linking static executable"
  // 1038:   Gcc $_out $err $success
  // 1039:     "runtime/linker.o"
  // 1040:     "runtime/memory.o"
  // 1041:     "runtime/debugger.o"
  // 1042:     libs_and_files*
  // 1043:     "-o"
  // 1044:     exe_filename
  // 1045:   unless success: Error err.from_utf8
  frame->slots[2] /* temp__1 */ = create_closure(entry__86_84, 0);
  // 1046: :
  // 1047:   if verbose: ewriteln "linking executable"
  // 1048:   Gcc $_out $err $success
  // 1049:     libs_and_files*
  // 1050:     if
  // 1051:       current_platform == "linux"
  // 1052:       -> "-l:libsim.so.@(MAJOR)"
  // 1053:       -> "-lsim-@(MAJOR)"
  // 1054:     "-o"
  // 1055:     exe_filename
  // ...
  frame->slots[3] /* temp__2 */ = create_closure(entry__86_94, 0);
  // 1035: if
  // 1036:   do_build_static_executable:
  // 1037:     if verbose: ewriteln "linking static executable"
  // 1038:     Gcc $_out $err $success
  // 1039:       "runtime/linker.o"
  // 1040:       "runtime/memory.o"
  // 1041:       "runtime/debugger.o"
  // 1042:       libs_and_files*
  // 1043:       "-o"
  // 1044:       exe_filename
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
static void cont__86_108(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1057: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__86_109;
}
static void cont__86_109(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 1057: $zz range(command_line_arguments 2 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__command_line_arguments();
  arguments->slots[1] = number__2;
  arguments->slots[2] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__86_110;
}
static void cont__86_110(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[8] /* zz */, arguments->slots[0]);
  // 1058: ... on_top_level && action == "simrun"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__on_top_level();
  arguments->slots[1] = func__86_111;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__86_113;
}
static void entry__86_111(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1058: ... action == "simrun"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._action;
  arguments->slots[1] = string__81_2;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__86_112;
}
static void cont__86_112(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1058: ... action == "simrun"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__86_113(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 1058: ... :
  // 1059:   exec
  // 1060:     if
  // 1061:       exe_filename .has_prefix. '/'
  // 1062:       -> exe_filename
  // 1063:       -> string("./" exe_filename)
  // 1064:     zz*
  // 1065:     
  // 1066:     #range(command_line_arguments 2 -1)*
  frame->slots[10] /* temp__2 */ = create_closure(entry__86_114, 0);
  // 1058: if on_top_level && action == "simrun":
  // 1059:   exec
  // 1060:     if
  // 1061:       exe_filename .has_prefix. '/'
  // 1062:       -> exe_filename
  // 1063:       -> string("./" exe_filename)
  // 1064:     zz*
  // 1065:     
  // 1066:     #range(command_line_arguments 2 -1)*
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__86_1_build_executable(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 978: compile_exe: (mod_filename mod_name)
  // 979:   $exe_filename
  // 980:     if
  // 981:       current_platform == "cygwin"
  // 982:       -> string(mod_filename ".exe")
  // 983:       -> mod_filename
  // 984:   
  // 985:   if verbose: ewriteln "build executable " exe_filename
  // 986:   $c_filename string(mod_filename ".c")
  // 987:   $o_filename string(mod_filename ".o")
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__86_2;
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
  phase_1__platform__platform();
  phase_1__platform__hardware_architecture();
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
  phase_2__platform__platform();
  phase_2__platform__hardware_architecture();
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
  func__63_8 = create_function(entry__63_8, 1);
  func__63_4 = create_function(entry__63_4, 1);
  func__63_3 = create_function(entry__63_3, 0);
  string__63_21 = from_latin_1_string("Cannot resolve required library \042", 33);
  string__63_22 = from_latin_1_string("\042!", 2);
  func__63_1_resolve_filename = create_function(entry__63_1_resolve_filename, 1);
  string__64_13 = from_latin_1_string(".sim", 4);
  string__64_16 = from_latin_1_string(".meta", 5);
  string__64_42 = from_latin_1_string("-common", 7);
  string__64_46 = from_latin_1_string("-", 1);
  string__64_58 = from_latin_1_string("The platform \042", 14);
  string__64_59 = from_latin_1_string("\042 is not supported!", 19);
  func__64_1_add_module_infos = create_function(entry__64_1_add_module_infos, 2);
  func__65_1_lookup = create_function(entry__65_1_lookup, 2);
  string__66_4 = from_latin_1_string("gcc ", 4);
  func__66_1_Gcc = create_function(entry__66_1_Gcc, -1);
  func__67_2 = create_function(entry__67_2, 0);
  string__67_5 = from_latin_1_string("-c", 2);
  string__67_6 = from_latin_1_string("-o", 2);
  string__67_10 = from_latin_1_string("Failed to compile ", 18);
  string__67_11 = from_latin_1_string("\012", 1);
  func__67_1_compile_c = create_function(entry__67_1_compile_c, 2);
  string__68_9 = from_latin_1_string(".c", 2);
  string__68_46 = from_latin_1_string("/// ", 4);
  string__68_53 = from_latin_1_string("data", 4);
  string__68_56 = from_latin_1_string("./", 2);
  func__68_1_compile_meta_module = create_function(entry__68_1_compile_meta_module, 3);
  func__69_24 = create_function(entry__69_24, 0);
  func__69_23 = create_function(entry__69_23, 0);
  string__69_32 = from_latin_1_string("sim-", 4);
  string__69_39 = from_latin_1_string("require", 7);
  string__69_40 = from_latin_1_string("link", 4);
  func__69_1_build_dependencies = create_function(entry__69_1_build_dependencies, -1);
  func__70_9 = create_function(entry__70_9, 0);
  string__70_38 = from_latin_1_string("__", 2);
  string__70_43 = from_latin_1_string("build module ", 13);
  string__70_76 = from_latin_1_string("No source file(s) for module \042", 30);
  string__70_77 = from_latin_1_string("\042 found!", 8);
  string__70_80 = from_latin_1_string(".o", 2);
  string__70_131 = from_latin_1_string(" #", 2);
  func__70_1_compile_module = create_function(entry__70_1_compile_module, 2);
  func__71_1_compile_modules = create_function(entry__71_1_compile_modules, 2);
  string__73_3 = from_latin_1_string("LD_LIBRARY_PATH", 15);
  string__73_7 = from_latin_1_string("LD_LIBRARY_PATH=", 16);
  string__73_11 = from_latin_1_string("included object files: ", 23);
  string__73_14 = from_latin_1_string("needed libraries: ", 18);
  func__73_2 = create_function(entry__73_2, 0);
  func__73_1_show_file_list = create_function(entry__73_1_show_file_list, 0);
  string__74_8 = from_latin_1_string("-L", 2);
  string__74_14 = from_latin_1_string("library paths: ", 15);
  string__74_22 = from_latin_1_string("linux", 5);
  string__74_25 = from_latin_1_string("-l:lib", 6);
  string__74_26 = from_latin_1_string(".so.", 4);
  string__74_29 = from_latin_1_string("-l", 2);
  func__74_1_library_paths_and_file_list = create_function(entry__74_1_library_paths_and_file_list, 0);
  string__75_26 = from_latin_1_string("typedef", 7);
  string__75_30 = from_latin_1_string("REGISTER", 8);
  string__75_44 = from_latin_1_string("typedef struct", 14);
  string__75_55 = from_latin_1_string("IMPORT ", 7);
  func__75_54 = create_function(entry__75_54, 0);
  string__75_65 = from_latin_1_string("// INSERT HERE //", 17);
  string__75_75 = from_latin_1_string("collecting imports", 18);
  func__75_74 = create_function(entry__75_74, 0);
  func__75_1_create_imports = create_function(entry__75_1_create_imports, 1);
  string__76_4 = from_latin_1_string("Expected a source code file!", 28);
  func__76_3 = create_function(entry__76_3, 0);
  string__76_8 = from_latin_1_string("Expected \042.sim\042 file extension in source filename!", 50);
  func__76_7 = create_function(entry__76_7, 0);
  func__76_1_compile_exe = create_function(entry__76_1_compile_exe, 1);
  func__77_2 = create_function(entry__77_2, 2);
  func__77_1_dump_source_or_check = create_function(entry__77_1_dump_source_or_check, 0);
  string__78_19 = from_latin_1_string("writing C-source", 16);
  func__78_18 = create_function(entry__78_18, 0);
  func__78_2 = create_function(entry__78_2, 2);
  func__78_1_print_c = create_function(entry__78_1_print_c, 0);
  func__79_3 = create_function(entry__79_3, 2);
  string__79_18 = from_latin_1_string("list dependencies for ", 22);
  func__79_17 = create_function(entry__79_17, 0);
  func__79_16 = create_function(entry__79_16, 0);
  func__79_24 = create_function(entry__79_24, 2);
  string__79_28 = from_latin_1_string("runtime/linker.c", 16);
  string__79_30 = from_latin_1_string("runtime/memory.c", 16);
  string__79_32 = from_latin_1_string("runtime/debugger.c", 18);
  func__79_23 = create_function(entry__79_23, 0);
  func__79_1_list_dependencies = create_function(entry__79_1_list_dependencies, 0);
  string__80_3 = from_latin_1_string(".codeblocks", 11);
  string__80_8 = from_latin_1_string("The directory \042", 15);
  string__80_9 = from_latin_1_string("\042 already exists!\012", 18);
  string__80_13 = from_latin_1_string("build Code::Blocks project in ", 30);
  string__80_23 = from_latin_1_string("../", 3);
  string__80_25 = from_latin_1_string("/", 1);
  string__80_26 = from_latin_1_string(".cbp", 4);
  string__80_29 = from_latin_1_string("<?xml version=\0421.0\042 encoding=\042UTF-8\042 standalone=\042yes\042 ?>\012<CodeBlocks_project_file>\012  <FileVersion major=\0421\042 minor=\0426\042 />\012  <Project>\012    <Option title=\042", 152);
  string__80_30 = from_latin_1_string("\042 />\012    <Option pch_mode=\0422\042 />\012    <Option compiler=\042gcc\042 />\012    <Build>\012      <Target title=\042debug\042>\012        <Option output=\042bin/debug/", 138);
  string__80_31 = from_latin_1_string("\042 prefix_auto=\0421\042 extension_auto=\0421\042 />\012        <Option object_output=\042obj/debug/\042 />\012        <Option type=\0421\042 />\012        <Option compiler=\042gcc\042 />\012        <Compiler>\012          <Add option=\042-g\042 />\012        </Compiler>\012      </Target>\012    </Build>\012    <Linker>\012", 259);
  string__80_35 = from_latin_1_string("      <Add library=\042", 20);
  string__80_36 = from_latin_1_string("\042 />\012", 5);
  string__80_40 = from_latin_1_string("\012    </Linker>\012    <Compiler>\012      <Add option=\042-Wall\042 />\012    </Compiler>\012    <Unit filename=\042", 95);
  string__80_41 = from_latin_1_string("runtime/common.h\042 />\012    <Unit filename=\042", 41);
  string__80_42 = from_latin_1_string("runtime/linker.h\042 />\012    <Unit filename=\042", 41);
  string__80_43 = from_latin_1_string("runtime/memory.c\042>\012      <Option compilerVar=\042CC\042 />\012    </Unit>\012    <Unit filename=\042", 85);
  string__80_44 = from_latin_1_string("runtime/debugger.c\042>\012      <Option compilerVar=\042CC\042 />\012    </Unit>\012    <Unit filename=\042", 87);
  string__80_45 = from_latin_1_string("runtime/linker.c\042>\012      <Option compilerVar=\042CC\042 />\012    </Unit>\012", 65);
  string__80_51 = from_latin_1_string("\012    <Unit filename=\042", 21);
  string__80_52 = from_latin_1_string("\042>\012      <Option compilerVar=\042CC\042 />\012    </Unit>\012", 49);
  string__80_56 = from_latin_1_string("    <Extensions>\012      <code_completion />\012      <debugger />\012    </Extensions>\012  </Project>\012</CodeBlocks_project_file>\012", 120);
  func__80_2 = create_function(entry__80_2, 2);
  func__80_1_build_codeblocks_project = create_function(entry__80_1_build_codeblocks_project, 0);
  string__81_2 = from_latin_1_string("simrun", 6);
  string__81_5 = from_latin_1_string("Cannot run a directory!", 23);
  func__81_4 = create_function(entry__81_4, 0);
  func__81_7 = create_function(entry__81_7, 0);
  string__81_9 = from_latin_1_string("/VERSION", 8);
  string__81_22 = from_latin_1_string("libsim-", 7);
  string__81_25 = from_latin_1_string(".dll", 4);
  string__81_29 = from_latin_1_string(".dylib", 6);
  string__81_33 = from_latin_1_string(".so", 3);
  string__81_35 = from_latin_1_string("cygwin", 6);
  string__81_36 = from_latin_1_string("darwin", 6);
  string__81_39 = from_latin_1_string("build library ", 14);
  func__81_51 = create_function(entry__81_51, 0);
  string__81_55 = from_latin_1_string("linking dynamic library", 23);
  func__81_54 = create_function(entry__81_54, 0);
  string__81_58 = from_latin_1_string("-Wl,-soname,libsim-", 19);
  string__81_61 = from_latin_1_string("-shared", 7);
  string__81_67 = from_latin_1_string("-lsim-", 6);
  string__81_73 = from_latin_1_string("-Wl,-install_name,libsim-", 25);
  string__81_77 = from_latin_1_string("-dynamiclib", 11);
  func__81_8 = create_function(entry__81_8, 0);
  func__81_1_build_library = create_function(entry__81_1_build_library, 0);
  string__82_7 = from_latin_1_string("\042", 1);
  string__82_8 = from_latin_1_string("\042 does not exist!\012", 18);
  string__82_20 = from_latin_1_string("compiling runtime module ", 25);
  func__82_1_maybe_compile_c_file = create_function(entry__82_1_maybe_compile_c_file, 1);
  string__84_14 = from_latin_1_string(" ", 1);
  string__84_23 = from_latin_1_string("0", 1);
  func__84_1_format_number = create_function(entry__84_1_format_number, -1);
  string__85_12 = from_latin_1_string(" s", 2);
  string__85_16 = from_latin_1_string(": ", 2);
  func__85_1_sim2c__write_timing_info = create_function(entry__85_1_sim2c__write_timing_info, -1);
  string__86_5 = from_latin_1_string(".exe", 4);
  string__86_10 = from_latin_1_string("build executable ", 17);
  string__86_29 = from_latin_1_string("build main module ", 18);
  func__86_28 = create_function(entry__86_28, 0);
  func__86_31 = create_function(entry__86_31, 0);
  string__86_39 = from_latin_1_string("saving", 6);
  string__86_43 = from_latin_1_string("compiling", 9);
  string__86_60 = from_latin_1_string("runtime/linker", 14);
  string__86_61 = from_latin_1_string("runtime/memory", 14);
  string__86_62 = from_latin_1_string("runtime/debugger", 16);
  func__86_64 = create_function(entry__86_64, 1);
  func__86_59 = create_function(entry__86_59, 0);
  func__86_76 = create_function(entry__86_76, 0);
  string__86_81 = from_latin_1_string("/usr/lib/libprofiler.so.0", 25);
  string__86_86 = from_latin_1_string("linking static executable", 25);
  func__86_85 = create_function(entry__86_85, 0);
  string__86_88 = from_latin_1_string("runtime/linker.o", 16);
  string__86_89 = from_latin_1_string("runtime/memory.o", 16);
  string__86_90 = from_latin_1_string("runtime/debugger.o", 18);
  string__86_96 = from_latin_1_string("linking executable", 18);
  func__86_95 = create_function(entry__86_95, 0);
  string__86_100 = from_latin_1_string("-l:libsim.so.", 13);
  func__86_99 = create_function(entry__86_99, 0);
  func__86_102 = create_function(entry__86_102, 0);
  func__86_111 = create_function(entry__86_111, 0);
  func__86_2 = create_function(entry__86_2, 2);
  func__86_1_build_executable = create_function(entry__86_1_build_executable, 0);
  string__90_1 = from_latin_1_string("Copyright (C) 2020 by\012Dipl.-Ing. Michael Niederle\012\012This program is free software; you can redistribute it and/or modify\012it under the terms of the GNU General Public License, version 2, or\012(at your option) version 3.\012\012This program is distributed in the hope that it will be useful,\012but WITHOUT ANY WARRANTY; without even the implied warranty of\012MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the\012GNU General Public License for more details.\012\012For details of the GNU General Public License see the accompanying\012files GPLv2.txt and GLPv3.txt or\012http://www.gnu.org/licenses/gpl-2.0.html\012http://www.gnu.org/licenses/gpl-3.0.html\012or write to the\012Free Software Foundation, Inc.,\01251 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.\012", 742);
  string__95_1 = from_latin_1_string(".", 1);
  string__97_1 = from_latin_1_string("gcc", 3);
  string__98_1 = from_latin_1_string("mkdir", 5);
  string__99_1 = from_latin_1_string("SIMLIBPATH", 10);
  string__100_1 = from_latin_1_string("SIMDATAPATH", 11);
  func__101_2 = create_function(entry__101_2, 0);
  string__101_5 = from_latin_1_string("/usr/local/share/simplicity-", 28);
  string__101_7 = from_latin_1_string("/usr/share/simplicity-", 22);
  func__101_4 = create_function(entry__101_4, 0);
  func__102_2 = create_function(entry__102_2, 0);
  func__102_4 = create_function(entry__102_4, 0);
  string__104_1 = from_latin_1_string("bsd", 3);
  string__104_2 = from_latin_1_string("posix", 5);
  string__104_7 = from_latin_1_string("all", 3);
  string__104_9 = from_latin_1_string("win", 3);
  func__106_1 = create_function(entry__106_1, 0);
  string__131_5 = from_latin_1_string("Missing command line arguments!", 31);
  func__131_4 = create_function(entry__131_4, 0);
  func__131_2 = create_function(entry__131_2, 0);
  string__131_10 = from_latin_1_string("check-only", 10);
  string__131_11 = from_latin_1_string("do not compile; just check for syntax errors\012", 45);
  func__131_9 = create_function(entry__131_9, 0);
  string__131_13 = from_latin_1_string("dump-trees", 10);
  string__131_14 = from_latin_1_string("dump abstract syntax trees\012", 27);
  func__131_12 = create_function(entry__131_12, 0);
  string__131_16 = from_latin_1_string("pretty-print", 12);
  string__131_17 = from_latin_1_string("do not compile; just pretty print the source file\012", 50);
  func__131_15 = create_function(entry__131_15, 0);
  string__131_19 = from_latin_1_string("print-simplified-source", 23);
  string__131_20 = from_latin_1_string("do not generate a C-file; just print the simplified source text\012", 64);
  func__131_18 = create_function(entry__131_18, 0);
  string__131_22 = from_latin_1_string("print-c", 7);
  string__131_23 = from_latin_1_string("print C source code for a single module\012", 40);
  func__131_21 = create_function(entry__131_21, 0);
  string__131_25 = from_latin_1_string("time-passes", 11);
  string__131_26 = from_latin_1_string("print running time for the individual compiler passes\012", 54);
  func__131_24 = create_function(entry__131_24, 0);
  string__131_28 = from_latin_1_string("module-prefix", 13);
  string__131_29 = from_latin_1_string("needed to compile a single file within a subdirectory;\012if the subdirectories are nested use slashes to separate\012the directory names\012", 132);
  func__131_27 = create_function(entry__131_27, 0);
  string__131_31 = from_latin_1_string("brief", 5);
  string__131_32 = from_latin_1_string("show brief error messages\012", 26);
  func__131_30 = create_function(entry__131_30, 0);
  string__131_34 = from_latin_1_string("warnings", 8);
  string__131_35 = from_latin_1_string("show warning messages\012", 22);
  func__131_33 = create_function(entry__131_33, 0);
  string__131_37 = from_latin_1_string("verbose", 7);
  string__131_38 = from_latin_1_string("output verbose informations\012", 28);
  func__131_36 = create_function(entry__131_36, 0);
  string__131_40 = from_latin_1_string("debug", 5);
  string__131_41 = from_latin_1_string("show C-compiler and linker calls\012", 33);
  func__131_39 = create_function(entry__131_39, 0);
  string__131_43 = from_latin_1_string("debug_compiler", 14);
  string__131_44 = from_latin_1_string("show internal debug messages of the Simplicity compiler\012", 56);
  func__131_42 = create_function(entry__131_42, 0);
  string__131_46 = from_latin_1_string("codeblocks", 10);
  string__131_47 = from_latin_1_string("create Code::Blocks project\012", 28);
  func__131_45 = create_function(entry__131_45, 0);
  string__131_49 = from_latin_1_string("extract-documentation", 21);
  string__131_50 = from_latin_1_string("extract documentation encoded as HTML\012", 38);
  func__131_48 = create_function(entry__131_48, 0);
  string__131_52 = from_latin_1_string("list-dependencies", 17);
  string__131_53 = from_latin_1_string("list all dependencies\012", 22);
  func__131_51 = create_function(entry__131_51, 0);
  string__131_55 = from_latin_1_string("rebuild", 7);
  string__131_56 = from_latin_1_string("rebuild all source files\012", 25);
  func__131_54 = create_function(entry__131_54, 0);
  string__131_58 = from_latin_1_string("omit-meta", 9);
  string__131_59 = from_latin_1_string("do not rebuild meta files\012", 26);
  func__131_57 = create_function(entry__131_57, 0);
  string__131_61 = from_latin_1_string("static", 6);
  string__131_62 = from_latin_1_string("create statically linked executable\012", 36);
  func__131_60 = create_function(entry__131_60, 0);
  string__131_64 = from_latin_1_string("profile", 7);
  string__131_65 = from_latin_1_string("link with libprofiler\012", 22);
  func__131_63 = create_function(entry__131_63, 0);
  string__131_67 = from_latin_1_string("filename", 8);
  string__131_68 = from_latin_1_string("the name of the source file to compile\012", 39);
  func__131_66 = create_function(entry__131_66, 0);
  func__131_8 = create_function(entry__131_8, 0);
  func__135_1 = create_function(entry__135_1, 0);
  string__141_1 = from_latin_1_string("-Wall", 5);
  string__141_2 = from_latin_1_string("-Wno-unused-function", 20);
  string__141_3 = from_latin_1_string("-Wno-unused-variable", 20);
  string__141_4 = from_latin_1_string("-Wno-parentheses", 16);
  string__141_5 = from_latin_1_string("-Wno-switch", 11);
  string__141_6 = from_latin_1_string("-Wno-maybe-uninitialized", 24);
  string__141_7 = from_latin_1_string("-Wno-trigraphs", 14);
  string__141_8 = from_latin_1_string("-O1", 3);
  string__141_9 = from_latin_1_string("-fPIC", 5);
  string__141_10 = from_latin_1_string("-fno-stack-protector", 20);
  string__141_11 = from_latin_1_string("-falign-functions=16", 20);
  string__142_1 = from_latin_1_string("-msse2", 6);
  string__142_2 = from_latin_1_string("-mfpmath=sse", 12);
  string__142_4 = from_latin_1_string("x86_32", 6);
  string__142_7 = from_latin_1_string("x86_64", 6);
  string__161_3 = from_latin_1_string("Source file \042", 13);
  string__161_4 = from_latin_1_string("\042 does not exist!", 17);
  func__161_2 = create_function(entry__161_2, 0);
  func__176_1 = create_function(entry__176_1, 0);
  func__177_4 = create_function(entry__177_4, 0);
  func__177_3 = create_function(entry__177_3, 0);
  func__177_2 = create_function(entry__177_2, 0);
  func__177_1 = create_function(entry__177_1, 0);
  func__177_8 = create_function(entry__177_8, 0);
  func__177_9 = create_function(entry__177_9, 0);
  func__177_10 = create_function(entry__177_10, 0);
  func__177_11 = create_function(entry__177_11, 0);

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
  phase_3__platform__platform();
  phase_3__platform__hardware_architecture();
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
  phase_4__platform__platform();
  phase_4__platform__hardware_architecture();
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
  use_read_only(NULL, "current_platform", &get__current_platform, &get_value_or_future__current_platform);
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
  phase_5__platform__platform();
  phase_5__platform__hardware_architecture();
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
  assign_variable(&var._resolve_filename, &func__63_1_resolve_filename);
  assign_variable(&var._add_module_infos, &func__64_1_add_module_infos);
  assign_variable(&var._lookup, &func__65_1_lookup);
  assign_variable(&var._Gcc, &func__66_1_Gcc);
  assign_variable(&var._compile_c, &func__67_1_compile_c);
  assign_variable(&var._compile_meta_module, &func__68_1_compile_meta_module);
  assign_variable(&var._build_dependencies, &func__69_1_build_dependencies);
  assign_variable(&var._compile_module, &func__70_1_compile_module);
  assign_variable(&var._compile_modules, &func__71_1_compile_modules);
  assign_variable(&var._show_file_list, &func__73_1_show_file_list);
  assign_variable(&var._library_paths_and_file_list, &func__74_1_library_paths_and_file_list);
  assign_variable(&var._create_imports, &func__75_1_create_imports);
  assign_variable(&var._compile_exe, &func__76_1_compile_exe);
  assign_variable(&var._dump_source_or_check, &func__77_1_dump_source_or_check);
  assign_variable(&var._print_c, &func__78_1_print_c);
  assign_variable(&var._list_dependencies, &func__79_1_list_dependencies);
  assign_variable(&var._build_codeblocks_project, &func__80_1_build_codeblocks_project);
  assign_variable(&var._build_library, &func__81_1_build_library);
  assign_variable(&var._maybe_compile_c_file, &func__82_1_maybe_compile_c_file);
  assign_variable(&var._format_number, &func__84_1_format_number);
  assign_variable(&var.sim2c__write_timing_info, &func__85_1_sim2c__write_timing_info);
  assign_variable(&var._build_executable, &func__86_1_build_executable);
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
  phase_6__platform__platform();
  phase_6__platform__hardware_architecture();
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
