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
static NODE_GETTER get__do_use_goto;
static NODE_SETTER set__do_use_goto;
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
  NODE *sim2c__do_use_goto;
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
static NODE *get__sim2c__do_use_goto(void) {
  return var.sim2c__do_use_goto;
}
static void set__sim2c__do_use_goto(NODE *val) {
  var.sim2c__do_use_goto = val;
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
static NODE *func__48_1_sim2c__show_compiler_debug_info;
static void entry__48_1_sim2c__show_compiler_debug_info(void);
static FRAME_INFO frame__48_1_sim2c__show_compiler_debug_info = {1, {"args"}};
static NODE *func__48_2;
static void entry__48_2(void);
static FRAME_INFO frame__48_2 = {1, {"args"}};
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
static NODE *func__64_1_resolve_filename;
static void entry__64_1_resolve_filename(void);
static FRAME_INFO frame__64_1_resolve_filename = {3, {"filename", "libname", "libpath"}};
static void cont__64_2(void);
static NODE *func__64_3;
static void entry__64_3(void);
static FRAME_INFO frame__64_3 = {0, {}};
static NODE *func__64_4;
static void entry__64_4(void);
static FRAME_INFO frame__64_4 = {1, {"path"}};
static void cont__64_5(void);
static NODE *func__64_6;
static void entry__64_6(void);
static FRAME_INFO frame__64_6 = {1, {"path"}};
static void cont__64_7(void);
static NODE *func__64_8;
static void entry__64_8(void);
static FRAME_INFO frame__64_8 = {1, {"entry"}};
static void cont__64_9(void);
static NODE *func__64_10;
static void entry__64_10(void);
static FRAME_INFO frame__64_10 = {2, {"entry", "name"}};
static void cont__64_11(void);
static void cont__64_12(void);
static NODE *func__64_13;
static void entry__64_13(void);
static FRAME_INFO frame__64_13 = {2, {"name", "entry"}};
static void cont__64_14(void);
static void cont__64_15(void);
static void cont__64_16(void);
static void cont__64_17(void);
static void cont__64_18(void);
static void cont__64_19(void);
static NODE *func__64_20;
static void entry__64_20(void);
static FRAME_INFO frame__64_20 = {1, {"libname"}};
static NODE *string__64_21;
static NODE *string__64_22;
static void cont__64_23(void);
static void cont__64_24(void);
static void cont__64_25(void);
static void cont__64_26(void);
static NODE *func__65_1_add_module_infos;
static void entry__65_1_add_module_infos(void);
static FRAME_INFO frame__65_1_add_module_infos = {7, {"path", "mod_path", "return", "entries", "filenames", "directories", "modules"}};
static void cont__65_2(void);
static void cont__65_3(void);
static NODE *func__65_4;
static void entry__65_4(void);
static FRAME_INFO frame__65_4 = {6, {"entry", "directories", "filenames", "modules", "mod_path", "name"}};
static void cont__65_5(void);
static NODE *func__65_6;
static void entry__65_6(void);
static FRAME_INFO frame__65_6 = {3, {"entry", "name", "directories"}};
static void cont__65_7(void);
static NODE *func__65_8;
static void entry__65_8(void);
static FRAME_INFO frame__65_8 = {2, {"name", "directories"}};
static void cont__65_9(void);
static NODE *func__65_10;
static void entry__65_10(void);
static FRAME_INFO frame__65_10 = {2, {"directories", "name"}};
static void cont__65_11(void);
static NODE *func__65_12;
static void entry__65_12(void);
static FRAME_INFO frame__65_12 = {4, {"name", "filenames", "modules", "mod_path"}};
static NODE *string__65_13;
static void cont__65_14(void);
static NODE *func__65_15;
static void entry__65_15(void);
static FRAME_INFO frame__65_15 = {9, {"name", "filenames", "modules", "mod_path", "submodule_name", "meta_level", "stored_level", "basename", "mod_name"}};
static NODE *string__65_16;
static void cont__65_17(void);
static void cont__65_18(void);
static void cont__65_19(void);
static void cont__65_20(void);
static void cont__65_21(void);
static void cont__65_22(void);
static void cont__65_23(void);
static void cont__65_24(void);
static void cont__65_25(void);
static void cont__65_26(void);
static void cont__65_27(void);
static NODE *func__65_28;
static void entry__65_28(void);
static FRAME_INFO frame__65_28 = {2, {"stored_level", "meta_level"}};
static void cont__65_29(void);
static void cont__65_30(void);
static NODE *func__65_31;
static void entry__65_31(void);
static FRAME_INFO frame__65_31 = {2, {"submodule_name", "meta_level"}};
static void cont__65_32(void);
static void cont__65_33(void);
static void cont__65_34(void);
static void cont__65_35(void);
static void cont__65_36(void);
static void cont__65_37(void);
static void cont__65_38(void);
static NODE *func__65_39;
static void entry__65_39(void);
static FRAME_INFO frame__65_39 = {3, {"filename", "filenames", "mod_path"}};
static void cont__65_40(void);
static NODE *func__65_41;
static void entry__65_41(void);
static FRAME_INFO frame__65_41 = {3, {"filename", "filenames", "mod_path"}};
static NODE *string__65_42;
static void cont__65_43(void);
static NODE *func__65_44;
static void entry__65_44(void);
static FRAME_INFO frame__65_44 = {9, {"filenames", "filename", "mod_path", "maybe_push_common", "name", "mod_name", "platform", "parent", "files"}};
static NODE *func__65_45_maybe_push_common;
static void entry__65_45_maybe_push_common(void);
static FRAME_INFO frame__65_45_maybe_push_common = {5, {"plat", "name", "filenames", "files", "common_name"}};
static NODE *string__65_46;
static void cont__65_47(void);
static void cont__65_48(void);
static NODE *func__65_49;
static void entry__65_49(void);
static FRAME_INFO frame__65_49 = {2, {"files", "common_name"}};
static void cont__65_50(void);
static void cont__65_51(void);
static void cont__65_52(void);
static void cont__65_53(void);
static void cont__65_54(void);
static void cont__65_55(void);
static void cont__65_56(void);
static NODE *func__65_57;
static void entry__65_57(void);
static FRAME_INFO frame__65_57 = {1, {"platform"}};
static NODE *string__65_58;
static NODE *string__65_59;
static void cont__65_60(void);
static void cont__65_61(void);
static void cont__65_62(void);
static void cont__65_63(void);
static NODE *func__65_64;
static void entry__65_64(void);
static FRAME_INFO frame__65_64 = {2, {"parent", "maybe_push_common"}};
static void cont__65_65(void);
static void cont__65_66(void);
static NODE *func__65_67;
static void entry__65_67(void);
static FRAME_INFO frame__65_67 = {2, {"maybe_push_common", "parent"}};
static void cont__65_68(void);
static void cont__65_69(void);
static void cont__65_70(void);
static void cont__65_71(void);
static void cont__65_72(void);
static void cont__65_73(void);
static void cont__65_74(void);
static void cont__65_75(void);
static void cont__65_76(void);
static NODE *func__65_77;
static void entry__65_77(void);
static FRAME_INFO frame__65_77 = {3, {"return", "directories", "modules"}};
static void cont__65_78(void);
static NODE *func__66_1_lookup;
static void entry__66_1_lookup(void);
static FRAME_INFO frame__66_1_lookup = {3, {"mod_filename", "mod_name", "info"}};
static void cont__66_2(void);
static void cont__66_3(void);
static NODE *func__66_4;
static void entry__66_4(void);
static FRAME_INFO frame__66_4 = {1, {"info"}};
static NODE *func__66_5;
static void entry__66_5(void);
static FRAME_INFO frame__66_5 = {2, {"mod_filename", "mod_name"}};
static void cont__66_6(void);
static void cont__66_7(void);
static void cont__66_8(void);
static void cont__66_9(void);
static void cont__66_10(void);
static void cont__66_11(void);
static NODE *func__67_1_Gcc;
static void entry__67_1_Gcc(void);
static FRAME_INFO frame__67_1_Gcc = {1, {"args"}};
static NODE *func__67_2;
static void entry__67_2(void);
static FRAME_INFO frame__67_2 = {1, {"args"}};
static void cont__67_3(void);
static NODE *string__67_4;
static void cont__67_5(void);
static NODE *func__68_1_compile_c;
static void entry__68_1_compile_c(void);
static FRAME_INFO frame__68_1_compile_c = {2, {"c_filename", "o_filename"}};
static NODE *func__68_2;
static void entry__68_2(void);
static FRAME_INFO frame__68_2 = {0, {}};
static void cont__68_3(void);
static NODE *func__68_4;
static void entry__68_4(void);
static FRAME_INFO frame__68_4 = {5, {"c_filename", "o_filename", "out", "err", "success"}};
static NODE *string__68_5;
static NODE *string__68_6;
static void cont__68_7(void);
static NODE *func__68_8;
static void entry__68_8(void);
static FRAME_INFO frame__68_8 = {1, {"err"}};
static void cont__68_9(void);
static void cont__68_10(void);
static NODE *func__69_1_compile_meta_module;
static void entry__69_1_compile_meta_module(void);
static FRAME_INFO frame__69_1_compile_meta_module = {3, {"mod_filename", "mod_name", "meta_level"}};
static NODE *func__69_2;
static void entry__69_2(void);
static FRAME_INFO frame__69_2 = {11, {"mod_filename", "meta_level", "meta_path", "filename", "meta_filename", "meta_c_filename", "sim_filename", "meta_info", "sim_info", "meta_c_info", "force_rebuild"}};
static void cont__69_3(void);
static void cont__69_4(void);
static void cont__69_5(void);
static void cont__69_6(void);
static void cont__69_7(void);
static void cont__69_8(void);
static NODE *string__69_9;
static void cont__69_10(void);
static void cont__69_11(void);
static void cont__69_12(void);
static void cont__69_13(void);
static void cont__69_14(void);
static void cont__69_15(void);
static void cont__69_16(void);
static NODE *func__69_17;
static void entry__69_17(void);
static FRAME_INFO frame__69_17 = {3, {"sim_info", "meta_c_info", "meta_info"}};
static void cont__69_18(void);
static NODE *func__69_19;
static void entry__69_19(void);
static FRAME_INFO frame__69_19 = {3, {"meta_c_info", "meta_info", "sim_info"}};
static void cont__69_20(void);
static NODE *func__69_21;
static void entry__69_21(void);
static FRAME_INFO frame__69_21 = {3, {"meta_c_info", "meta_info", "sim_info"}};
static void cont__69_22(void);
static void cont__69_23(void);
static void cont__69_24(void);
static NODE *func__69_25;
static void entry__69_25(void);
static FRAME_INFO frame__69_25 = {2, {"sim_info", "meta_c_info"}};
static void cont__69_26(void);
static void cont__69_27(void);
static void cont__69_28(void);
static void cont__69_29(void);
static void cont__69_30(void);
static void cont__69_31(void);
static void cont__69_32(void);
static NODE *func__69_33;
static void entry__69_33(void);
static FRAME_INFO frame__69_33 = {6, {"sim_info", "meta_c_filename", "force_rebuild", "meta_path", "modification_time", "meta_c_buf"}};
static void cont__69_34(void);
static void cont__69_35(void);
static NODE *func__69_36;
static void entry__69_36(void);
static FRAME_INFO frame__69_36 = {5, {"break", "meta_c_buf", "modification_time", "force_rebuild", "meta_path"}};
static NODE *func__69_37;
static void entry__69_37(void);
static FRAME_INFO frame__69_37 = {8, {"line", "modification_time", "force_rebuild", "break", "meta_path", "check", "command", "argument"}};
static NODE *func__69_38_check;
static void entry__69_38_check(void);
static FRAME_INFO frame__69_38_check = {5, {"data_filename", "modification_time", "force_rebuild", "break", "data_info"}};
static void cont__69_39(void);
static void cont__69_40(void);
static NODE *func__69_41;
static void entry__69_41(void);
static FRAME_INFO frame__69_41 = {2, {"modification_time", "data_info"}};
static void cont__69_42(void);
static void cont__69_43(void);
static void cont__69_44(void);
static NODE *func__69_45;
static void entry__69_45(void);
static FRAME_INFO frame__69_45 = {2, {"force_rebuild", "break"}};
static NODE *string__69_46;
static void cont__69_47(void);
static void cont__69_48(void);
static void cont__69_49(void);
static void cont__69_50(void);
static void cont__69_51(void);
static void cont__69_52(void);
static NODE *string__69_53;
static void cont__69_54(void);
static NODE *func__69_55;
static void entry__69_55(void);
static FRAME_INFO frame__69_55 = {3, {"argument", "check", "meta_path"}};
static NODE *string__69_56;
static void cont__69_57(void);
static NODE *func__69_58;
static void entry__69_58(void);
static FRAME_INFO frame__69_58 = {3, {"check", "meta_path", "argument"}};
static void cont__69_59(void);
static void cont__69_60(void);
static void cont__69_61(void);
static NODE *func__69_62;
static void entry__69_62(void);
static FRAME_INFO frame__69_62 = {2, {"check", "argument"}};
static NODE *func__69_63;
static void entry__69_63(void);
static FRAME_INFO frame__69_63 = {3, {"path", "check", "argument"}};
static void cont__69_64(void);
static void cont__69_65(void);
static void cont__69_66(void);
static NODE *func__69_67;
static void entry__69_67(void);
static FRAME_INFO frame__69_67 = {9, {"return__1", "meta_filename", "meta_path", "filename", "sim_filename", "orig_path", "out", "err", "success"}};
static void cont__69_68(void);
static void cont__69_69(void);
static void cont__69_70(void);
static void cont__69_71(void);
static void cont__69_72(void);
static void cont__69_73(void);
static NODE *func__69_74;
static void entry__69_74(void);
static FRAME_INFO frame__69_74 = {1, {"err"}};
static void cont__69_75(void);
static void cont__69_76(void);
static void cont__69_77(void);
static void cont__69_78(void);
static void cont__69_79(void);
static void cont__69_80(void);
static void cont__69_81(void);
static NODE *func__70_1_build_dependencies;
static void entry__70_1_build_dependencies(void);
static FRAME_INFO frame__70_1_build_dependencies = {5, {"mod_filename", "mod_name", "c_buf", "do_compile_c", "return"}};
static NODE *func__70_2;
static void entry__70_2(void);
static FRAME_INFO frame__70_2 = {7, {"line", "return", "mod_filename", "mod_name", "do_compile_c", "command", "argument"}};
static void cont__70_3(void);
static void cont__70_4(void);
static void cont__70_5(void);
static void cont__70_6(void);
static void cont__70_7(void);
static void cont__70_8(void);
static NODE *func__70_9;
static void entry__70_9(void);
static FRAME_INFO frame__70_9 = {4, {"argument", "mod_filename", "mod_name", "do_compile_c"}};
static void cont__70_10(void);
static NODE *func__70_11;
static void entry__70_11(void);
static FRAME_INFO frame__70_11 = {3, {"argument", "mod_filename", "mod_name"}};
static void cont__70_12(void);
static NODE *func__70_13;
static void entry__70_13(void);
static FRAME_INFO frame__70_13 = {4, {"argument", "mod_filename", "mod_name", "req_name"}};
static void cont__70_14(void);
static void cont__70_15(void);
static void cont__70_16(void);
static void cont__70_17(void);
static void cont__70_18(void);
static void cont__70_19(void);
static void cont__70_20(void);
static void cont__70_21(void);
static NODE *func__70_22;
static void entry__70_22(void);
static FRAME_INFO frame__70_22 = {2, {"argument", "do_compile_c"}};
static NODE *func__70_23;
static void entry__70_23(void);
static FRAME_INFO frame__70_23 = {0, {}};
static NODE *func__70_24;
static void entry__70_24(void);
static FRAME_INFO frame__70_24 = {0, {}};
static void cont__70_25(void);
static void cont__70_26(void);
static NODE *func__70_27;
static void entry__70_27(void);
static FRAME_INFO frame__70_27 = {1, {"argument"}};
static void cont__70_28(void);
static NODE *func__70_29;
static void entry__70_29(void);
static FRAME_INFO frame__70_29 = {2, {"do_compile_c", "argument"}};
static NODE *func__70_30;
static void entry__70_30(void);
static FRAME_INFO frame__70_30 = {1, {"argument"}};
static void cont__70_31(void);
static NODE *string__70_32;
static void cont__70_33(void);
static void cont__70_34(void);
static NODE *func__70_35;
static void entry__70_35(void);
static FRAME_INFO frame__70_35 = {2, {"do_compile_c", "argument"}};
static NODE *func__70_36;
static void entry__70_36(void);
static FRAME_INFO frame__70_36 = {1, {"argument"}};
static void cont__70_37(void);
static void cont__70_38(void);
static NODE *string__70_39;
static NODE *string__70_40;
static void cont__70_41(void);
static NODE *func__71_1_compile_module;
static void entry__71_1_compile_module(void);
static FRAME_INFO frame__71_1_compile_module = {6, {"mod_filename", "mod_name", "return", "compile_submodule", "mod_info", "o_filename"}};
static NODE *func__71_2_compile_submodule;
static void entry__71_2_compile_submodule(void);
static FRAME_INFO frame__71_2_compile_submodule = {11, {"submodule_names", "do_compile_c", "suffix", "mod_filename", "mod_name", "o_filename", "modification_time", "sim_filenames", "c_filename", "c_info", "c_buf"}};
static NODE *func__71_3;
static void entry__71_3(void);
static FRAME_INFO frame__71_3 = {8, {"submodule_name", "mod_filename", "sim_filenames", "modification_time", "meta_level", "submodule_filename", "sim_filename", "sim_info"}};
static void cont__71_4(void);
static void cont__71_5(void);
static void cont__71_6(void);
static void cont__71_7(void);
static void cont__71_8(void);
static NODE *func__71_9;
static void entry__71_9(void);
static FRAME_INFO frame__71_9 = {0, {}};
static void cont__71_10(void);
static void cont__71_11(void);
static NODE *func__71_12;
static void entry__71_12(void);
static FRAME_INFO frame__71_12 = {3, {"submodule_filename", "submodule_name", "meta_level"}};
static void cont__71_13(void);
static void cont__71_14(void);
static void cont__71_15(void);
static void cont__71_16(void);
static void cont__71_17(void);
static NODE *func__71_18;
static void entry__71_18(void);
static FRAME_INFO frame__71_18 = {2, {"modification_time", "sim_info"}};
static void cont__71_19(void);
static void cont__71_20(void);
static void cont__71_21(void);
static NODE *func__71_22;
static void entry__71_22(void);
static FRAME_INFO frame__71_22 = {2, {"modification_time", "sim_info"}};
static void cont__71_23(void);
static void cont__71_24(void);
static void cont__71_25(void);
static void cont__71_26(void);
static NODE *func__71_27;
static void entry__71_27(void);
static FRAME_INFO frame__71_27 = {1, {"c_filename"}};
static void cont__71_28(void);
static void cont__71_29(void);
static NODE *func__71_30;
static void entry__71_30(void);
static FRAME_INFO frame__71_30 = {2, {"c_info", "modification_time"}};
static void cont__71_31(void);
static NODE *func__71_32;
static void entry__71_32(void);
static FRAME_INFO frame__71_32 = {2, {"c_info", "modification_time"}};
static void cont__71_33(void);
static void cont__71_34(void);
static void cont__71_35(void);
static void cont__71_36(void);
static NODE *func__71_37;
static void entry__71_37(void);
static FRAME_INFO frame__71_37 = {9, {"return__1", "mod_name", "suffix", "sim_filenames", "c_buf", "c_filename", "do_compile_c", "o_filename", "c_source"}};
static NODE *string__71_38;
static void cont__71_39(void);
static void cont__71_40(void);
static void cont__71_41(void);
static NODE *func__71_42;
static void entry__71_42(void);
static FRAME_INFO frame__71_42 = {1, {"suffix"}};
static NODE *string__71_43;
static void cont__71_44(void);
static NODE *func__71_45;
static void entry__71_45(void);
static FRAME_INFO frame__71_45 = {1, {"sim_filenames"}};
static void cont__71_46(void);
static NODE *func__71_47;
static void entry__71_47(void);
static FRAME_INFO frame__71_47 = {1, {"c_source"}};
static void cont__71_48(void);
static void cont__71_49(void);
static void cont__71_50(void);
static NODE *func__71_51;
static void entry__71_51(void);
static FRAME_INFO frame__71_51 = {2, {"c_filename", "o_filename"}};
static void cont__71_52(void);
static NODE *func__71_53;
static void entry__71_53(void);
static FRAME_INFO frame__71_53 = {6, {"c_buf", "c_filename", "o_filename", "c_info", "do_compile_c", "o_info"}};
static void cont__71_54(void);
static void cont__71_55(void);
static void cont__71_56(void);
static NODE *func__71_57;
static void entry__71_57(void);
static FRAME_INFO frame__71_57 = {2, {"o_info", "c_info"}};
static void cont__71_58(void);
static void cont__71_59(void);
static void cont__71_60(void);
static void cont__71_61(void);
static NODE *func__71_62;
static void entry__71_62(void);
static FRAME_INFO frame__71_62 = {3, {"do_compile_c", "c_filename", "o_filename"}};
static NODE *func__71_63;
static void entry__71_63(void);
static FRAME_INFO frame__71_63 = {2, {"c_filename", "o_filename"}};
static NODE *func__71_64;
static void entry__71_64(void);
static FRAME_INFO frame__71_64 = {1, {"o_info"}};
static void cont__71_65(void);
static NODE *func__71_66;
static void entry__71_66(void);
static FRAME_INFO frame__71_66 = {1, {"o_info"}};
static void cont__71_67(void);
static void cont__71_68(void);
static void cont__71_69(void);
static NODE *func__71_70;
static void entry__71_70(void);
static FRAME_INFO frame__71_70 = {1, {"o_info"}};
static void cont__71_71(void);
static void cont__71_72(void);
static void cont__71_73(void);
static void cont__71_74(void);
static NODE *func__71_75;
static void entry__71_75(void);
static FRAME_INFO frame__71_75 = {1, {"mod_name"}};
static NODE *string__71_76;
static NODE *string__71_77;
static void cont__71_78(void);
static void cont__71_79(void);
static NODE *string__71_80;
static void cont__71_81(void);
static void cont__71_82(void);
static void cont__71_83(void);
static void cont__71_84(void);
static void cont__71_85(void);
static NODE *func__71_86;
static void entry__71_86(void);
static FRAME_INFO frame__71_86 = {3, {"compile_submodule", "mod_name", "mod_filename"}};
static void cont__71_87(void);
static void cont__71_88(void);
static void cont__71_89(void);
static void cont__71_90(void);
static NODE *func__71_91;
static void entry__71_91(void);
static FRAME_INFO frame__71_91 = {1, {"mod_filename"}};
static void cont__71_92(void);
static void cont__71_93(void);
static NODE *func__71_94;
static void entry__71_94(void);
static FRAME_INFO frame__71_94 = {3, {"mod_info", "compile_submodule", "mod_filename"}};
static NODE *func__71_95;
static void entry__71_95(void);
static FRAME_INFO frame__71_95 = {4, {"mod_info", "compile_submodule", "best_platform", "best_priority"}};
static NODE *func__71_96;
static void entry__71_96(void);
static FRAME_INFO frame__71_96 = {5, {"platform", "filenames", "best_priority", "best_platform", "priority"}};
static void cont__71_97(void);
static void cont__71_98(void);
static NODE *func__71_99;
static void entry__71_99(void);
static FRAME_INFO frame__71_99 = {2, {"priority", "best_priority"}};
static void cont__71_100(void);
static void cont__71_101(void);
static NODE *func__71_102;
static void entry__71_102(void);
static FRAME_INFO frame__71_102 = {4, {"best_platform", "platform", "best_priority", "priority"}};
static void cont__71_103(void);
static NODE *func__71_104;
static void entry__71_104(void);
static FRAME_INFO frame__71_104 = {4, {"platform", "filenames", "compile_submodule", "best_platform"}};
static void cont__71_105(void);
static void cont__71_106(void);
static void cont__71_107(void);
static NODE *func__71_108;
static void entry__71_108(void);
static FRAME_INFO frame__71_108 = {3, {"mod_info", "mod_filename", "used_by"}};
static NODE *func__71_109;
static void entry__71_109(void);
static FRAME_INFO frame__71_109 = {6, {"supported_platform", "parent_platform", "mod_info", "used_by", "best_platform", "best_priority"}};
static NODE *func__71_110;
static void entry__71_110(void);
static FRAME_INFO frame__71_110 = {6, {"platform", "filenames", "supported_platform", "best_priority", "best_platform", "priority"}};
static void cont__71_111(void);
static void cont__71_112(void);
static NODE *func__71_113;
static void entry__71_113(void);
static FRAME_INFO frame__71_113 = {2, {"priority", "best_priority"}};
static void cont__71_114(void);
static void cont__71_115(void);
static NODE *func__71_116;
static void entry__71_116(void);
static FRAME_INFO frame__71_116 = {4, {"best_platform", "platform", "best_priority", "priority"}};
static void cont__71_117(void);
static void cont__71_118(void);
static NODE *func__71_119;
static void entry__71_119(void);
static FRAME_INFO frame__71_119 = {4, {"used_by", "best_platform", "supported_platform", "ub"}};
static void cont__71_120(void);
static void cont__71_121(void);
static void cont__71_122(void);
static void cont__71_123(void);
static void cont__71_124(void);
static NODE *func__71_125;
static void entry__71_125(void);
static FRAME_INFO frame__71_125 = {6, {"platform", "filenames", "mod_filename", "used_by", "dependency", "platforms"}};
static void cont__71_126(void);
static void cont__71_127(void);
static void cont__71_128(void);
static NODE *func__71_129;
static void entry__71_129(void);
static FRAME_INFO frame__71_129 = {2, {"platforms", "dependency"}};
static NODE *func__71_130;
static void entry__71_130(void);
static FRAME_INFO frame__71_130 = {2, {"plat", "dependency"}};
static NODE *string__71_131;
static void cont__71_132(void);
static void cont__71_133(void);
static void cont__71_134(void);
static void cont__71_135(void);
static NODE *func__72_1_compile_modules;
static void entry__72_1_compile_modules(void);
static FRAME_INFO frame__72_1_compile_modules = {4, {"path", "mod_path", "directories", "modules"}};
static void cont__72_2(void);
static void cont__72_3(void);
static NODE *func__72_4;
static void entry__72_4(void);
static FRAME_INFO frame__72_4 = {3, {"name", "path", "mod_path"}};
static void cont__72_5(void);
static void cont__72_6(void);
static void cont__72_7(void);
static NODE *func__72_8;
static void entry__72_8(void);
static FRAME_INFO frame__72_8 = {3, {"name", "path", "mod_path"}};
static void cont__72_9(void);
static void cont__72_10(void);
static NODE *func__74_1_show_file_list;
static void entry__74_1_show_file_list(void);
static FRAME_INFO frame__74_1_show_file_list = {0, {}};
static NODE *func__74_2;
static void entry__74_2(void);
static FRAME_INFO frame__74_2 = {1, {"path"}};
static NODE *string__74_3;
static void cont__74_4(void);
static void cont__74_5(void);
static NODE *func__74_6;
static void entry__74_6(void);
static FRAME_INFO frame__74_6 = {1, {"path"}};
static NODE *string__74_7;
static void cont__74_8(void);
static void cont__74_9(void);
static void cont__74_10(void);
static NODE *string__74_11;
static void cont__74_12(void);
static void cont__74_13(void);
static NODE *string__74_14;
static NODE *func__75_1_library_paths_and_file_list;
static void entry__75_1_library_paths_and_file_list(void);
static FRAME_INFO frame__75_1_library_paths_and_file_list = {4, {"library_paths", "object_files", "library_files", "paths"}};
static void cont__75_2(void);
static void cont__75_3(void);
static void cont__75_4(void);
static NODE *func__75_5;
static void entry__75_5(void);
static FRAME_INFO frame__75_5 = {2, {"paths", "library_paths"}};
static void cont__75_6(void);
static NODE *func__75_7;
static void entry__75_7(void);
static FRAME_INFO frame__75_7 = {2, {"path", "library_paths"}};
static NODE *string__75_8;
static void cont__75_9(void);
static void cont__75_10(void);
static void cont__75_11(void);
static NODE *func__75_12;
static void entry__75_12(void);
static FRAME_INFO frame__75_12 = {1, {"library_paths"}};
static void cont__75_13(void);
static NODE *string__75_14;
static void cont__75_15(void);
static NODE *func__75_16;
static void entry__75_16(void);
static FRAME_INFO frame__75_16 = {2, {"object", "object_files"}};
static void cont__75_17(void);
static void cont__75_18(void);
static NODE *func__75_19;
static void entry__75_19(void);
static FRAME_INFO frame__75_19 = {2, {"library", "library_files"}};
static void cont__75_20(void);
static NODE *func__75_21;
static void entry__75_21(void);
static FRAME_INFO frame__75_21 = {1, {"library"}};
static NODE *string__75_22;
static void cont__75_23(void);
static NODE *func__75_24;
static void entry__75_24(void);
static FRAME_INFO frame__75_24 = {1, {"library"}};
static NODE *string__75_25;
static NODE *string__75_26;
static void cont__75_27(void);
static NODE *func__75_28;
static void entry__75_28(void);
static FRAME_INFO frame__75_28 = {1, {"library"}};
static NODE *string__75_29;
static void cont__75_30(void);
static void cont__75_31(void);
static NODE *func__75_32;
static void entry__75_32(void);
static FRAME_INFO frame__75_32 = {1, {"library"}};
static void cont__75_33(void);
static NODE *func__75_34;
static void entry__75_34(void);
static FRAME_INFO frame__75_34 = {1, {"library"}};
static void cont__75_35(void);
static void cont__75_36(void);
static void cont__75_37(void);
static NODE *func__75_38;
static void entry__75_38(void);
static FRAME_INFO frame__75_38 = {1, {"library"}};
static void cont__75_39(void);
static void cont__75_40(void);
static void cont__75_41(void);
static void cont__75_42(void);
static void cont__75_43(void);
static void cont__75_44(void);
static NODE *func__76_1_create_imports;
static void entry__76_1_create_imports(void);
static FRAME_INFO frame__76_1_create_imports = {5, {"source", "already_checked", "collect_declarations", "imports", "first_part"}};
static NODE *func__76_2_collect_declarations;
static void entry__76_2_collect_declarations(void);
static FRAME_INFO frame__76_2_collect_declarations = {4, {"buf", "already_checked", "collect_declarations", "s"}};
static NODE *func__76_3;
static void entry__76_3(void);
static FRAME_INFO frame__76_3 = {6, {"idx", "chr", "s", "buf", "already_checked", "collect_declarations"}};
static void cont__76_4(void);
static NODE *func__76_5;
static void entry__76_5(void);
static FRAME_INFO frame__76_5 = {6, {"chr", "buf", "s", "idx", "already_checked", "collect_declarations"}};
static void cont__76_6(void);
static NODE *func__76_7;
static void entry__76_7(void);
static FRAME_INFO frame__76_7 = {1, {"chr"}};
static void cont__76_8(void);
static NODE *func__76_9;
static void entry__76_9(void);
static FRAME_INFO frame__76_9 = {1, {"chr"}};
static void cont__76_10(void);
static void cont__76_11(void);
static void cont__76_12(void);
static NODE *func__76_13;
static void entry__76_13(void);
static FRAME_INFO frame__76_13 = {6, {"buf", "s", "idx", "already_checked", "collect_declarations", "symbol"}};
static void cont__76_14(void);
static void cont__76_15(void);
static void cont__76_16(void);
static NODE *func__76_17;
static void entry__76_17(void);
static FRAME_INFO frame__76_17 = {4, {"already_checked", "symbol", "collect_declarations", "declaration"}};
static void cont__76_18(void);
static void cont__76_19(void);
static void cont__76_20(void);
static NODE *func__76_21;
static void entry__76_21(void);
static FRAME_INFO frame__76_21 = {3, {"declaration", "collect_declarations", "do_import"}};
static void cont__76_22(void);
static void cont__76_23(void);
static void cont__76_24(void);
static NODE *func__76_25;
static void entry__76_25(void);
static FRAME_INFO frame__76_25 = {1, {"declaration"}};
static NODE *string__76_26;
static void cont__76_27(void);
static void cont__76_28(void);
static NODE *func__76_29;
static void entry__76_29(void);
static FRAME_INFO frame__76_29 = {1, {"declaration"}};
static NODE *string__76_30;
static void cont__76_31(void);
static void cont__76_32(void);
static void cont__76_33(void);
static void cont__76_34(void);
static NODE *func__76_35;
static void entry__76_35(void);
static FRAME_INFO frame__76_35 = {2, {"declaration", "collect_declarations"}};
static void cont__76_36(void);
static void cont__76_37(void);
static NODE *func__76_38;
static void entry__76_38(void);
static FRAME_INFO frame__76_38 = {1, {"declaration"}};
static void cont__76_39(void);
static void cont__76_40(void);
static NODE *func__76_41;
static void entry__76_41(void);
static FRAME_INFO frame__76_41 = {2, {"collect_declarations", "declaration"}};
static void cont__76_42(void);
static NODE *func__76_43;
static void entry__76_43(void);
static FRAME_INFO frame__76_43 = {2, {"declaration", "collect_declarations"}};
static NODE *string__76_44;
static void cont__76_45(void);
static NODE *func__76_46;
static void entry__76_46(void);
static FRAME_INFO frame__76_46 = {2, {"declaration", "collect_declarations"}};
static void cont__76_47(void);
static void cont__76_48(void);
static NODE *func__76_49;
static void entry__76_49(void);
static FRAME_INFO frame__76_49 = {2, {"line", "collect_declarations"}};
static void cont__76_50(void);
static void cont__76_51(void);
static NODE *func__76_52;
static void entry__76_52(void);
static FRAME_INFO frame__76_52 = {2, {"collect_declarations", "declaration"}};
static void cont__76_53(void);
static NODE *func__76_54;
static void entry__76_54(void);
static FRAME_INFO frame__76_54 = {0, {}};
static NODE *string__76_55;
static void cont__76_56(void);
static NODE *func__76_57;
static void entry__76_57(void);
static FRAME_INFO frame__76_57 = {3, {"chr", "s", "idx"}};
static void cont__76_58(void);
static NODE *func__76_59;
static void entry__76_59(void);
static FRAME_INFO frame__76_59 = {1, {"chr"}};
static void cont__76_60(void);
static void cont__76_61(void);
static NODE *func__76_62;
static void entry__76_62(void);
static FRAME_INFO frame__76_62 = {2, {"s", "idx"}};
static NODE *func__76_63;
static void entry__76_63(void);
static FRAME_INFO frame__76_63 = {2, {"collect_declarations", "source"}};
static void cont__76_64(void);
static NODE *string__76_65;
static void cont__76_66(void);
static void cont__76_67(void);
static void cont__76_68(void);
static void cont__76_69(void);
static void cont__76_70(void);
static void cont__76_71(void);
static void cont__76_72(void);
static void cont__76_73(void);
static NODE *func__76_74;
static void entry__76_74(void);
static FRAME_INFO frame__76_74 = {0, {}};
static NODE *string__76_75;
static NODE *func__77_1_compile_exe;
static void entry__77_1_compile_exe(void);
static FRAME_INFO frame__77_1_compile_exe = {4, {"body", "return__1", "mod_filename", "mod_name"}};
static void cont__77_2(void);
static NODE *func__77_3;
static void entry__77_3(void);
static FRAME_INFO frame__77_3 = {0, {}};
static NODE *string__77_4;
static void cont__77_5(void);
static void cont__77_6(void);
static NODE *func__77_7;
static void entry__77_7(void);
static FRAME_INFO frame__77_7 = {0, {}};
static NODE *string__77_8;
static void cont__77_9(void);
static void cont__77_10(void);
static void cont__77_11(void);
static void cont__77_12(void);
static void cont__77_13(void);
static NODE *func__78_1_dump_source_or_check;
static void entry__78_1_dump_source_or_check(void);
static FRAME_INFO frame__78_1_dump_source_or_check = {0, {}};
static NODE *func__78_2;
static void entry__78_2(void);
static FRAME_INFO frame__78_2 = {3, {"mod_filename", "mod_name", "return__1"}};
static void cont__78_3(void);
static void cont__78_4(void);
static NODE *func__79_1_print_c;
static void entry__79_1_print_c(void);
static FRAME_INFO frame__79_1_print_c = {0, {}};
static NODE *func__79_2;
static void entry__79_2(void);
static FRAME_INFO frame__79_2 = {4, {"mod_filename", "mod_name", "c_source", "c_buf"}};
static void cont__79_3(void);
static NODE *func__79_4;
static void entry__79_4(void);
static FRAME_INFO frame__79_4 = {1, {"mod_name"}};
static void cont__79_5(void);
static void cont__79_6(void);
static void cont__79_7(void);
static NODE *func__79_8;
static void entry__79_8(void);
static FRAME_INFO frame__79_8 = {2, {"return__1", "mod_name"}};
static void cont__79_9(void);
static void cont__79_10(void);
static void cont__79_11(void);
static void cont__79_12(void);
static void cont__79_13(void);
static void cont__79_14(void);
static NODE *func__79_15;
static void entry__79_15(void);
static FRAME_INFO frame__79_15 = {1, {"c_source"}};
static void cont__79_16(void);
static void cont__79_17(void);
static NODE *func__79_18;
static void entry__79_18(void);
static FRAME_INFO frame__79_18 = {0, {}};
static NODE *string__79_19;
static NODE *func__80_1_list_dependencies;
static void entry__80_1_list_dependencies(void);
static FRAME_INFO frame__80_1_list_dependencies = {1, {"prefix_path"}};
static void cont__80_2(void);
static NODE *func__80_3;
static void entry__80_3(void);
static FRAME_INFO frame__80_3 = {4, {"supported_platform", "parent_platform", "platform", "priority"}};
static NODE *func__80_4;
static void entry__80_4(void);
static FRAME_INFO frame__80_4 = {4, {"break", "platform", "priority", "supported_platform"}};
static NODE *func__80_5;
static void entry__80_5(void);
static FRAME_INFO frame__80_5 = {5, {"platform", "break", "priority", "supported_platform", "plat"}};
static void cont__80_6(void);
static void cont__80_7(void);
static void cont__80_8(void);
static void cont__80_9(void);
static void cont__80_10(void);
static void cont__80_11(void);
static void cont__80_12(void);
static void cont__80_13(void);
static void cont__80_14(void);
static void cont__80_15(void);
static NODE *func__80_16;
static void entry__80_16(void);
static FRAME_INFO frame__80_16 = {1, {"return__1"}};
static NODE *func__80_17;
static void entry__80_17(void);
static FRAME_INFO frame__80_17 = {0, {}};
static NODE *string__80_18;
static void cont__80_19(void);
static void cont__80_20(void);
static void cont__80_21(void);
static void cont__80_22(void);
static NODE *func__80_23;
static void entry__80_23(void);
static FRAME_INFO frame__80_23 = {0, {}};
static NODE *func__80_24;
static void entry__80_24(void);
static FRAME_INFO frame__80_24 = {2, {"mod_filename", "mod_name"}};
static NODE *func__80_25;
static void entry__80_25(void);
static FRAME_INFO frame__80_25 = {1, {"mod_filename"}};
static void cont__80_26(void);
static void cont__80_27(void);
static NODE *string__80_28;
static void cont__80_29(void);
static NODE *string__80_30;
static void cont__80_31(void);
static NODE *string__80_32;
static void cont__80_33(void);
static void cont__80_34(void);
static NODE *func__80_35;
static void entry__80_35(void);
static FRAME_INFO frame__80_35 = {2, {"filename", "prefix_path"}};
static void cont__80_36(void);
static void cont__80_37(void);
static NODE *func__81_1_build_codeblocks_project;
static void entry__81_1_build_codeblocks_project(void);
static FRAME_INFO frame__81_1_build_codeblocks_project = {0, {}};
static NODE *func__81_2;
static void entry__81_2(void);
static FRAME_INFO frame__81_2 = {10, {"mod_filename", "mod_name", "codeblocks_path", "info", "basename", "prefix_path", "depth", "path_prefix", "cbp_filename", "buf"}};
static NODE *string__81_3;
static void cont__81_4(void);
static void cont__81_5(void);
static void cont__81_6(void);
static NODE *func__81_7;
static void entry__81_7(void);
static FRAME_INFO frame__81_7 = {1, {"codeblocks_path"}};
static NODE *string__81_8;
static NODE *string__81_9;
static void cont__81_10(void);
static void cont__81_11(void);
static NODE *func__81_12;
static void entry__81_12(void);
static FRAME_INFO frame__81_12 = {1, {"codeblocks_path"}};
static NODE *string__81_13;
static void cont__81_14(void);
static void cont__81_15(void);
static void cont__81_16(void);
static void cont__81_17(void);
static void cont__81_18(void);
static void cont__81_19(void);
static void cont__81_20(void);
static void cont__81_21(void);
static void cont__81_22(void);
static NODE *string__81_23;
static void cont__81_24(void);
static NODE *string__81_25;
static NODE *string__81_26;
static void cont__81_27(void);
static void cont__81_28(void);
static NODE *string__81_29;
static NODE *string__81_30;
static NODE *string__81_31;
static void cont__81_32(void);
static void cont__81_33(void);
static NODE *func__81_34;
static void entry__81_34(void);
static FRAME_INFO frame__81_34 = {2, {"filename", "buf"}};
static NODE *string__81_35;
static NODE *string__81_36;
static void cont__81_37(void);
static void cont__81_38(void);
static void cont__81_39(void);
static NODE *string__81_40;
static NODE *string__81_41;
static NODE *string__81_42;
static NODE *string__81_43;
static NODE *string__81_44;
static NODE *string__81_45;
static void cont__81_46(void);
static void cont__81_47(void);
static NODE *func__81_48;
static void entry__81_48(void);
static FRAME_INFO frame__81_48 = {4, {"filename", "prefix_path", "buf", "path_prefix"}};
static void cont__81_49(void);
static void cont__81_50(void);
static NODE *string__81_51;
static NODE *string__81_52;
static void cont__81_53(void);
static void cont__81_54(void);
static void cont__81_55(void);
static NODE *string__81_56;
static void cont__81_57(void);
static NODE *func__82_1_build_library;
static void entry__82_1_build_library(void);
static FRAME_INFO frame__82_1_build_library = {1, {"return__1"}};
static NODE *string__82_2;
static void cont__82_3(void);
static NODE *func__82_4;
static void entry__82_4(void);
static FRAME_INFO frame__82_4 = {0, {}};
static NODE *string__82_5;
static void cont__82_6(void);
static NODE *func__82_7;
static void entry__82_7(void);
static FRAME_INFO frame__82_7 = {0, {}};
static NODE *func__82_8;
static void entry__82_8(void);
static FRAME_INFO frame__82_8 = {5, {"version", "so_version", "version_filename", "base_filename", "lib_filename"}};
static NODE *string__82_9;
static void cont__82_10(void);
static void cont__82_11(void);
static NODE *func__82_12;
static void entry__82_12(void);
static FRAME_INFO frame__82_12 = {3, {"version", "version_filename", "so_version"}};
static void cont__82_13(void);
static void cont__82_14(void);
static void cont__82_15(void);
static void cont__82_16(void);
static void cont__82_17(void);
static void cont__82_18(void);
static void cont__82_19(void);
static NODE *func__82_20;
static void entry__82_20(void);
static FRAME_INFO frame__82_20 = {2, {"base_filename", "version"}};
static void cont__82_21(void);
static NODE *string__82_22;
static void cont__82_23(void);
static NODE *func__82_24;
static void entry__82_24(void);
static FRAME_INFO frame__82_24 = {2, {"base_filename", "version"}};
static NODE *string__82_25;
static void cont__82_26(void);
static void cont__82_27(void);
static NODE *func__82_28;
static void entry__82_28(void);
static FRAME_INFO frame__82_28 = {2, {"base_filename", "version"}};
static NODE *string__82_29;
static void cont__82_30(void);
static void cont__82_31(void);
static NODE *func__82_32;
static void entry__82_32(void);
static FRAME_INFO frame__82_32 = {1, {"base_filename"}};
static NODE *string__82_33;
static void cont__82_34(void);
static NODE *string__82_35;
static NODE *string__82_36;
static void cont__82_37(void);
static NODE *func__82_38;
static void entry__82_38(void);
static FRAME_INFO frame__82_38 = {1, {"lib_filename"}};
static NODE *string__82_39;
static void cont__82_40(void);
static void cont__82_41(void);
static void cont__82_42(void);
static void cont__82_43(void);
static NODE *func__82_44;
static void entry__82_44(void);
static FRAME_INFO frame__82_44 = {2, {"lib_filename", "info"}};
static void cont__82_45(void);
static void cont__82_46(void);
static NODE *func__82_47;
static void entry__82_47(void);
static FRAME_INFO frame__82_47 = {1, {"info"}};
static void cont__82_48(void);
static void cont__82_49(void);
static void cont__82_50(void);
static NODE *func__82_51;
static void entry__82_51(void);
static FRAME_INFO frame__82_51 = {0, {}};
static void cont__82_52(void);
static NODE *func__82_53;
static void entry__82_53(void);
static FRAME_INFO frame__82_53 = {3, {"base_filename", "so_version", "lib_filename"}};
static NODE *func__82_54;
static void entry__82_54(void);
static FRAME_INFO frame__82_54 = {0, {}};
static NODE *string__82_55;
static void cont__82_56(void);
static NODE *func__82_57;
static void entry__82_57(void);
static FRAME_INFO frame__82_57 = {6, {"base_filename", "so_version", "lib_filename", "out", "err", "success"}};
static NODE *string__82_58;
static void cont__82_59(void);
static void cont__82_60(void);
static NODE *string__82_61;
static void cont__82_62(void);
static NODE *func__82_63;
static void entry__82_63(void);
static FRAME_INFO frame__82_63 = {1, {"err"}};
static void cont__82_64(void);
static NODE *func__82_65;
static void entry__82_65(void);
static FRAME_INFO frame__82_65 = {4, {"lib_filename", "out", "err", "success"}};
static void cont__82_66(void);
static NODE *string__82_67;
static void cont__82_68(void);
static void cont__82_69(void);
static NODE *func__82_70;
static void entry__82_70(void);
static FRAME_INFO frame__82_70 = {1, {"err"}};
static void cont__82_71(void);
static NODE *func__82_72;
static void entry__82_72(void);
static FRAME_INFO frame__82_72 = {6, {"base_filename", "so_version", "lib_filename", "out", "err", "success"}};
static NODE *string__82_73;
static void cont__82_74(void);
static void cont__82_75(void);
static void cont__82_76(void);
static NODE *string__82_77;
static void cont__82_78(void);
static NODE *func__82_79;
static void entry__82_79(void);
static FRAME_INFO frame__82_79 = {1, {"err"}};
static void cont__82_80(void);
static NODE *func__82_81;
static void entry__82_81(void);
static FRAME_INFO frame__82_81 = {4, {"lib_filename", "out", "err", "success"}};
static void cont__82_82(void);
static void cont__82_83(void);
static NODE *func__82_84;
static void entry__82_84(void);
static FRAME_INFO frame__82_84 = {1, {"err"}};
static void cont__82_85(void);
static void cont__82_86(void);
static NODE *func__83_1_maybe_compile_c_file;
static void entry__83_1_maybe_compile_c_file(void);
static FRAME_INFO frame__83_1_maybe_compile_c_file = {5, {"filename", "c_filename", "o_filename", "c_info", "o_info"}};
static void cont__83_2(void);
static void cont__83_3(void);
static void cont__83_4(void);
static void cont__83_5(void);
static NODE *func__83_6;
static void entry__83_6(void);
static FRAME_INFO frame__83_6 = {1, {"c_filename"}};
static NODE *string__83_7;
static NODE *string__83_8;
static void cont__83_9(void);
static void cont__83_10(void);
static void cont__83_11(void);
static void cont__83_12(void);
static NODE *func__83_13;
static void entry__83_13(void);
static FRAME_INFO frame__83_13 = {2, {"o_info", "c_info"}};
static void cont__83_14(void);
static void cont__83_15(void);
static void cont__83_16(void);
static void cont__83_17(void);
static NODE *func__83_18;
static void entry__83_18(void);
static FRAME_INFO frame__83_18 = {3, {"filename", "c_filename", "o_filename"}};
static NODE *func__83_19;
static void entry__83_19(void);
static FRAME_INFO frame__83_19 = {1, {"filename"}};
static NODE *string__83_20;
static void cont__83_21(void);
static void cont__83_22(void);
static NODE *func__85_1_format_number;
static void entry__85_1_format_number(void);
static FRAME_INFO frame__85_1_format_number = {4, {"val", "n", "m", "ac"}};
static void cont__85_2(void);
static NODE *func__85_3;
static void entry__85_3(void);
static FRAME_INFO frame__85_3 = {4, {"break", "val", "ac", "n"}};
static NODE *func__85_4;
static void entry__85_4(void);
static FRAME_INFO frame__85_4 = {6, {"i", "chr", "ac", "val", "n", "break"}};
static void cont__85_5(void);
static NODE *func__85_6;
static void entry__85_6(void);
static FRAME_INFO frame__85_6 = {5, {"ac", "val", "i", "n", "break"}};
static void cont__85_7(void);
static void cont__85_8(void);
static void cont__85_9(void);
static void cont__85_10(void);
static NODE *func__85_11;
static void entry__85_11(void);
static FRAME_INFO frame__85_11 = {3, {"val", "n", "i"}};
static void cont__85_12(void);
static void cont__85_13(void);
static NODE *string__85_14;
static void cont__85_15(void);
static void cont__85_16(void);
static void cont__85_17(void);
static void cont__85_18(void);
static void cont__85_19(void);
static void cont__85_20(void);
static NODE *func__85_21;
static void entry__85_21(void);
static FRAME_INFO frame__85_21 = {3, {"val", "m", "ac"}};
static void cont__85_22(void);
static NODE *string__85_23;
static void cont__85_24(void);
static void cont__85_25(void);
static NODE *func__85_26;
static void entry__85_26(void);
static FRAME_INFO frame__85_26 = {3, {"m", "ac", "val"}};
static void cont__85_27(void);
static NODE *func__85_28;
static void entry__85_28(void);
static FRAME_INFO frame__85_28 = {3, {"val", "ac", "m"}};
static void cont__85_29(void);
static void cont__85_30(void);
static void cont__85_31(void);
static void cont__85_32(void);
static void cont__85_33(void);
static NODE *func__86_1_sim2c__write_timing_info;
static void entry__86_1_sim2c__write_timing_info(void);
static FRAME_INFO frame__86_1_sim2c__write_timing_info = {3, {"description", "filename", "new_t"}};
static void cont__86_2(void);
static void cont__86_3(void);
static NODE *func__86_4;
static void entry__86_4(void);
static FRAME_INFO frame__86_4 = {3, {"filename", "description", "new_t"}};
static void cont__86_5(void);
static void cont__86_6(void);
static void cont__86_7(void);
static void cont__86_8(void);
static void cont__86_9(void);
static void cont__86_10(void);
static void cont__86_11(void);
static NODE *string__86_12;
static NODE *func__86_13;
static void entry__86_13(void);
static FRAME_INFO frame__86_13 = {2, {"description", "new_t"}};
static void cont__86_14(void);
static void cont__86_15(void);
static NODE *string__86_16;
static void cont__86_17(void);
static void cont__86_18(void);
static NODE *get__sim2c__write_timing_info(void) {
  return var.sim2c__write_timing_info;
}
static NODE *func__87_1_build_executable;
static void entry__87_1_build_executable(void);
static FRAME_INFO frame__87_1_build_executable = {0, {}};
static NODE *func__87_2;
static void entry__87_2(void);
static FRAME_INFO frame__87_2 = {9, {"mod_filename", "mod_name", "exe_filename", "c_filename", "o_filename", "sim_info", "c_info", "c_buf", "zz"}};
static void cont__87_3(void);
static NODE *func__87_4;
static void entry__87_4(void);
static FRAME_INFO frame__87_4 = {1, {"mod_filename"}};
static NODE *string__87_5;
static void cont__87_6(void);
static NODE *func__87_7;
static void entry__87_7(void);
static FRAME_INFO frame__87_7 = {1, {"mod_filename"}};
static void cont__87_8(void);
static NODE *func__87_9;
static void entry__87_9(void);
static FRAME_INFO frame__87_9 = {1, {"exe_filename"}};
static NODE *string__87_10;
static void cont__87_11(void);
static void cont__87_12(void);
static void cont__87_13(void);
static void cont__87_14(void);
static void cont__87_15(void);
static void cont__87_16(void);
static NODE *func__87_17;
static void entry__87_17(void);
static FRAME_INFO frame__87_17 = {2, {"c_info", "sim_info"}};
static void cont__87_18(void);
static NODE *func__87_19;
static void entry__87_19(void);
static FRAME_INFO frame__87_19 = {2, {"c_info", "sim_info"}};
static void cont__87_20(void);
static void cont__87_21(void);
static void cont__87_22(void);
static void cont__87_23(void);
static void cont__87_24(void);
static NODE *func__87_25;
static void entry__87_25(void);
static FRAME_INFO frame__87_25 = {6, {"return__1", "mod_name", "c_buf", "c_filename", "o_filename", "c_source"}};
static void cont__87_26(void);
static void cont__87_27(void);
static NODE *func__87_28;
static void entry__87_28(void);
static FRAME_INFO frame__87_28 = {0, {}};
static NODE *string__87_29;
static void cont__87_30(void);
static NODE *func__87_31;
static void entry__87_31(void);
static FRAME_INFO frame__87_31 = {0, {}};
static void cont__87_32(void);
static void cont__87_33(void);
static NODE *func__87_34;
static void entry__87_34(void);
static FRAME_INFO frame__87_34 = {1, {"c_source"}};
static void cont__87_35(void);
static void cont__87_36(void);
static void cont__87_37(void);
static NODE *func__87_38;
static void entry__87_38(void);
static FRAME_INFO frame__87_38 = {1, {"c_filename"}};
static NODE *string__87_39;
static void cont__87_40(void);
static void cont__87_41(void);
static NODE *func__87_42;
static void entry__87_42(void);
static FRAME_INFO frame__87_42 = {1, {"c_filename"}};
static NODE *string__87_43;
static void cont__87_44(void);
static NODE *func__87_45;
static void entry__87_45(void);
static FRAME_INFO frame__87_45 = {5, {"c_buf", "c_filename", "o_filename", "c_info", "o_info"}};
static void cont__87_46(void);
static void cont__87_47(void);
static void cont__87_48(void);
static NODE *func__87_49;
static void entry__87_49(void);
static FRAME_INFO frame__87_49 = {2, {"o_info", "c_info"}};
static void cont__87_50(void);
static void cont__87_51(void);
static void cont__87_52(void);
static void cont__87_53(void);
static NODE *func__87_54;
static void entry__87_54(void);
static FRAME_INFO frame__87_54 = {2, {"c_filename", "o_filename"}};
static NODE *func__87_55;
static void entry__87_55(void);
static FRAME_INFO frame__87_55 = {1, {"o_info"}};
static void cont__87_56(void);
static void cont__87_57(void);
static void cont__87_58(void);
static NODE *func__87_59;
static void entry__87_59(void);
static FRAME_INFO frame__87_59 = {0, {}};
static NODE *string__87_60;
static NODE *string__87_61;
static NODE *string__87_62;
static void cont__87_63(void);
static NODE *func__87_64;
static void entry__87_64(void);
static FRAME_INFO frame__87_64 = {1, {"filename"}};
static void cont__87_65(void);
static NODE *func__87_66;
static void entry__87_66(void);
static FRAME_INFO frame__87_66 = {2, {"exe_filename", "info"}};
static void cont__87_67(void);
static void cont__87_68(void);
static NODE *func__87_69;
static void entry__87_69(void);
static FRAME_INFO frame__87_69 = {1, {"info"}};
static void cont__87_70(void);
static NODE *func__87_71;
static void entry__87_71(void);
static FRAME_INFO frame__87_71 = {1, {"info"}};
static void cont__87_72(void);
static void cont__87_73(void);
static void cont__87_74(void);
static void cont__87_75(void);
static NODE *func__87_76;
static void entry__87_76(void);
static FRAME_INFO frame__87_76 = {0, {}};
static void cont__87_77(void);
static NODE *func__87_78;
static void entry__87_78(void);
static FRAME_INFO frame__87_78 = {2, {"exe_filename", "libs_and_files"}};
static void cont__87_79(void);
static NODE *func__87_80;
static void entry__87_80(void);
static FRAME_INFO frame__87_80 = {1, {"libs_and_files"}};
static NODE *string__87_81;
static void cont__87_82(void);
static void cont__87_83(void);
static NODE *func__87_84;
static void entry__87_84(void);
static FRAME_INFO frame__87_84 = {5, {"libs_and_files", "exe_filename", "out", "err", "success"}};
static NODE *func__87_85;
static void entry__87_85(void);
static FRAME_INFO frame__87_85 = {0, {}};
static NODE *string__87_86;
static void cont__87_87(void);
static NODE *string__87_88;
static NODE *string__87_89;
static NODE *string__87_90;
static void cont__87_91(void);
static NODE *func__87_92;
static void entry__87_92(void);
static FRAME_INFO frame__87_92 = {1, {"err"}};
static void cont__87_93(void);
static NODE *func__87_94;
static void entry__87_94(void);
static FRAME_INFO frame__87_94 = {5, {"libs_and_files", "exe_filename", "out", "err", "success"}};
static NODE *func__87_95;
static void entry__87_95(void);
static FRAME_INFO frame__87_95 = {0, {}};
static NODE *string__87_96;
static void cont__87_97(void);
static void cont__87_98(void);
static NODE *func__87_99;
static void entry__87_99(void);
static FRAME_INFO frame__87_99 = {0, {}};
static NODE *string__87_100;
static void cont__87_101(void);
static NODE *func__87_102;
static void entry__87_102(void);
static FRAME_INFO frame__87_102 = {0, {}};
static void cont__87_103(void);
static void cont__87_104(void);
static void cont__87_105(void);
static NODE *func__87_106;
static void entry__87_106(void);
static FRAME_INFO frame__87_106 = {1, {"err"}};
static void cont__87_107(void);
static void cont__87_108(void);
static void cont__87_109(void);
static void cont__87_110(void);
static NODE *func__87_111;
static void entry__87_111(void);
static FRAME_INFO frame__87_111 = {0, {}};
static void cont__87_112(void);
static void cont__87_113(void);
static NODE *func__87_114;
static void entry__87_114(void);
static FRAME_INFO frame__87_114 = {2, {"exe_filename", "zz"}};
static void cont__87_115(void);
static NODE *func__87_116;
static void entry__87_116(void);
static FRAME_INFO frame__87_116 = {1, {"exe_filename"}};
static NODE *func__87_117;
static void entry__87_117(void);
static FRAME_INFO frame__87_117 = {1, {"exe_filename"}};
static void cont__87_118(void);
static void cont__87_119(void);
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
static NODE *string__91_1;
static void cont__91_2(void);
static void cont__92_1(void);
static void cont__93_1(void);
static void cont__94_1(void);
static NODE *string__96_1;
static void cont__96_2(void);
static void cont__97_1(void);
static NODE *string__98_1;
static void cont__98_2(void);
static NODE *string__99_1;
static void cont__99_2(void);
static NODE *string__100_1;
static void cont__100_2(void);
static NODE *string__101_1;
static void cont__101_2(void);
static void cont__102_1(void);
static NODE *func__102_2;
static void entry__102_2(void);
static FRAME_INFO frame__102_2 = {0, {}};
static void cont__102_3(void);
static NODE *func__102_4;
static void entry__102_4(void);
static FRAME_INFO frame__102_4 = {0, {}};
static NODE *string__102_5;
static void cont__102_6(void);
static NODE *string__102_7;
static void cont__102_8(void);
static void cont__102_9(void);
static void cont__102_10(void);
static void cont__103_1(void);
static NODE *func__103_2;
static void entry__103_2(void);
static FRAME_INFO frame__103_2 = {0, {}};
static void cont__103_3(void);
static NODE *func__103_4;
static void entry__103_4(void);
static FRAME_INFO frame__103_4 = {0, {}};
static void cont__103_5(void);
static void cont__103_6(void);
static void cont__103_7(void);
static void cont__103_8(void);
static NODE *string__105_1;
static NODE *string__105_2;
static void cont__105_3(void);
static void cont__105_4(void);
static void cont__105_5(void);
static void cont__105_6(void);
static NODE *string__105_7;
static void cont__105_8(void);
static NODE *string__105_9;
static void cont__105_10(void);
static void cont__105_11(void);
static void cont__105_12(void);
static NODE *func__107_1;
static void entry__107_1(void);
static FRAME_INFO frame__107_1 = {2, {"platform", "priority"}};
static NODE *func__107_2;
static void entry__107_2(void);
static FRAME_INFO frame__107_2 = {3, {"break", "platform", "priority"}};
static NODE *func__107_3;
static void entry__107_3(void);
static FRAME_INFO frame__107_3 = {4, {"platform", "break", "priority", "plat"}};
static void cont__107_4(void);
static void cont__107_5(void);
static void cont__107_6(void);
static void cont__107_7(void);
static void cont__107_8(void);
static void cont__107_9(void);
static void cont__107_10(void);
static void cont__107_11(void);
static void cont__107_12(void);
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
static NODE *func__133_69;
static void entry__133_69(void);
static FRAME_INFO frame__133_69 = {0, {}};
static NODE *string__133_70;
static NODE *string__133_71;
static void cont__133_72(void);
static void cont__133_73(void);
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
static void cont__145_1(void);
static void cont__145_2(void);
static void cont__145_3(void);
static void cont__145_4(void);
static void cont__163_1(void);
static NODE *func__163_2;
static void entry__163_2(void);
static FRAME_INFO frame__163_2 = {0, {}};
static NODE *string__163_3;
static NODE *string__163_4;
static void cont__163_5(void);
static void cont__163_6(void);
static NODE *func__178_1;
static void entry__178_1(void);
static FRAME_INFO frame__178_1 = {0, {}};
static void cont__178_2(void);
static void cont__178_3(void);
static NODE *func__179_1;
static void entry__179_1(void);
static FRAME_INFO frame__179_1 = {0, {}};
static NODE *func__179_2;
static void entry__179_2(void);
static FRAME_INFO frame__179_2 = {0, {}};
static NODE *func__179_3;
static void entry__179_3(void);
static FRAME_INFO frame__179_3 = {0, {}};
static NODE *func__179_4;
static void entry__179_4(void);
static FRAME_INFO frame__179_4 = {0, {}};
static void cont__179_5(void);
static void cont__179_6(void);
static void cont__179_7(void);
static NODE *func__179_8;
static void entry__179_8(void);
static FRAME_INFO frame__179_8 = {0, {}};
static NODE *func__179_9;
static void entry__179_9(void);
static FRAME_INFO frame__179_9 = {0, {}};
static NODE *func__179_10;
static void entry__179_10(void);
static FRAME_INFO frame__179_10 = {0, {}};
static NODE *func__179_11;
static void entry__179_11(void);
static FRAME_INFO frame__179_11 = {0, {}};
static void cont__179_12(void);
static void cont__179_13(void);
static void cont__180_1(void);
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
  {cont__91_2, NULL, 92, 92, 1, 30},
  {cont__92_1, NULL, 93, 93, 1, 30},
  {cont__93_1, NULL, 94, 94, 1, 28},
  {cont__94_1, NULL, 96, 96, 1, 49},
  {cont__96_2, NULL, 97, 97, 1, 15},
  {cont__97_1, NULL, 98, 98, 1, 17},
  {cont__98_2, NULL, 99, 99, 1, 72},
  {cont__99_2, NULL, 100, 100, 1, 37},
  {cont__100_2, NULL, 101, 101, 1, 39},
  {cont__101_2, NULL, 105, 105, 5, 25},
  {cont__102_1, NULL, 103, 110, 1, 45},
  {cont__102_10, NULL, 114, 114, 5, 26},
  {cont__103_1, NULL, 112, 119, 1, 45},
  {cont__103_8, NULL, 125, 125, 5, 19},
  {cont__105_3, NULL, 126, 126, 5, 22},
  {cont__105_4, NULL, 127, 127, 5, 22},
  {cont__105_5, NULL, 128, 128, 5, 21},
  {cont__105_6, NULL, 129, 129, 5, 19},
  {cont__105_8, NULL, 130, 130, 5, 17},
  {cont__105_10, NULL, 131, 131, 5, 16},
  {cont__105_11, NULL, 123, 131, 1, 17},
  {cont__105_12, NULL, 134, 144, 1, 22},
  {cont__107_12, NULL, 169, 169, 42, 42},
  {cont__132_1, NULL, 169, 169, 1, 43},
  {cont__132_2, NULL, 171, 171, 3, 20},
  {cont__133_1, NULL, 170, 250, 1, 49},
  {cont__133_73, NULL, 251, 251, 1, 39},
  {cont__134_1, NULL, 252, 252, 1, 30},
  {cont__135_1, NULL, 254, 254, 1, 37},
  {cont__137_2, NULL, 263, 263, 1, 21},
  {cont__142_1, NULL, 265, 277, 1, 27},
  {cont__143_12, NULL, 281, 281, 16, 44},
  {cont__144_3, NULL, 281, 281, 5, 44},
  {cont__144_5, NULL, 282, 282, 16, 44},
  {cont__144_6, NULL, 282, 282, 5, 44},
  {cont__144_8, NULL, 279, 282, 1, 45},
  {cont__144_9, NULL, 288, 288, 37, 59},
  {cont__145_1, NULL, 288, 288, 7, 60},
  {cont__145_2, NULL, 287, 289, 5, 15},
  {cont__145_3, NULL, 284, 289, 1, 18},
  {cont__145_4, NULL, 624, 624, 4, 25},
  {cont__163_1, NULL, 624, 626, 1, 52},
  {cont__163_6, NULL, 1071, 1071, 1, 36},
  {cont__178_3, NULL, 1072, 1084, 1, 18},
  {cont__179_13, NULL, },
  {cont__180_1, NULL, },
  {entry__48_2, NULL, 257, 257, 36, 49},
  {entry__48_1_sim2c__show_compiler_debug_info, NULL, 257, 257, 3, 49},
  {entry__64_13, NULL, 308, 308, 37, 80},
  {cont__64_14, &frame__64_13, 308, 308, 37, 61},
  {cont__64_15, &frame__64_13, 308, 308, 80, 80},
  {entry__64_10, NULL, 307, 307, 13, 41},
  {cont__64_11, &frame__64_10, 308, 308, 16, 34},
  {cont__64_12, &frame__64_10, 308, 308, 13, 80},
  {entry__64_8, NULL, 306, 306, 14, 33},
  {cont__64_9, &frame__64_8, 306, 308, 11, 80},
  {entry__64_6, NULL, 305, 305, 18, 32},
  {cont__64_7, &frame__64_6, 305, 308, 9, 81},
  {entry__64_4, NULL, 304, 304, 10, 26},
  {cont__64_5, &frame__64_4, 304, 308, 7, 82},
  {entry__64_3, NULL, 303, 308, 5, 83},
  {entry__64_20, NULL, 312, 313, 11, 57},
  {cont__64_23, &frame__64_20, 312, 313, 5, 57},
  {entry__64_1_resolve_filename, NULL, 301, 301, 6, 36},
  {cont__64_2, &frame__64_1_resolve_filename, 301, 308, 3, 84},
  {cont__64_16, &frame__64_1_resolve_filename, 309, 309, 3, 32},
  {cont__64_17, &frame__64_1_resolve_filename, 310, 310, 3, 38},
  {cont__64_18, &frame__64_1_resolve_filename, 311, 311, 6, 25},
  {cont__64_19, &frame__64_1_resolve_filename, 311, 313, 3, 58},
  {cont__64_24, &frame__64_1_resolve_filename, 314, 314, 21, 39},
  {cont__64_25, &frame__64_1_resolve_filename, 314, 314, 6, 40},
  {cont__64_26, &frame__64_1_resolve_filename, 314, 314, 3, 40},
  {entry__65_10, NULL, 332, 332, 56, 77},
  {cont__65_11, &frame__65_10, 332, 332, 77, 77},
  {entry__65_8, NULL, 332, 332, 35, 53},
  {cont__65_9, &frame__65_8, 332, 332, 32, 77},
  {entry__65_6, NULL, 332, 332, 10, 29},
  {cont__65_7, &frame__65_6, 332, 332, 7, 77},
  {entry__65_28, NULL, 338, 338, 41, 65},
  {cont__65_29, &frame__65_28, 338, 338, 41, 65},
  {entry__65_31, NULL, 339, 339, 11, 38},
  {cont__65_32, &frame__65_31, 339, 339, 49, 49},
  {entry__65_15, NULL, 334, 334, 48, 60},
  {cont__65_17, &frame__65_15, 334, 334, 48, 68},
  {cont__65_18, &frame__65_15, 334, 334, 9, 69},
  {cont__65_19, &frame__65_15, 335, 335, 9, 34},
  {cont__65_20, &frame__65_15, 336, 336, 22, 36},
  {cont__65_21, &frame__65_15, 336, 336, 38, 62},
  {cont__65_22, &frame__65_15, 336, 336, 22, 62},
  {cont__65_23, &frame__65_15, 336, 336, 22, 64},
  {cont__65_24, &frame__65_15, 336, 336, 9, 67},
  {cont__65_25, &frame__65_15, 337, 337, 9, 49},
  {cont__65_26, &frame__65_15, 338, 338, 12, 36},
  {cont__65_27, &frame__65_15, 338, 338, 12, 65},
  {cont__65_30, &frame__65_15, 338, 339, 9, 49},
  {cont__65_33, &frame__65_15, 340, 340, 9, 52},
  {cont__65_34, &frame__65_15, 341, 341, 9, 26},
  {cont__65_35, &frame__65_15, 342, 342, 9, 43},
  {cont__65_36, &frame__65_15, 343, 343, 9, 30},
  {cont__65_37, &frame__65_15, 343, 343, 52, 52},
  {entry__65_12, NULL, 333, 333, 10, 33},
  {cont__65_14, &frame__65_12, 333, 343, 7, 52},
  {entry__65_4, NULL, 330, 330, 5, 33},
  {cont__65_5, &frame__65_4, 331, 343, 5, 53},
  {entry__65_49, NULL, 349, 349, 38, 60},
  {cont__65_50, &frame__65_49, 349, 349, 60, 60},
  {entry__65_45_maybe_push_common, NULL, 348, 348, 11, 54},
  {cont__65_47, &frame__65_45_maybe_push_common, 349, 349, 14, 35},
  {cont__65_48, &frame__65_45_maybe_push_common, 349, 349, 11, 60},
  {entry__65_57, NULL, 356, 357, 17, 57},
  {cont__65_60, &frame__65_57, 356, 357, 11, 57},
  {entry__65_67, NULL, 361, 361, 11, 34},
  {cont__65_68, &frame__65_67, 362, 362, 11, 45},
  {cont__65_69, &frame__65_67, 362, 362, 45, 45},
  {entry__65_64, NULL, 360, 360, 18, 31},
  {cont__65_65, &frame__65_64, 360, 360, 18, 31},
  {cont__65_66, &frame__65_64, 360, 362, 15, 45},
  {entry__65_44, NULL, 351, 351, 9, 35},
  {cont__65_51, &frame__65_44, 352, 352, 35, 58},
  {cont__65_52, &frame__65_44, 352, 352, 9, 59},
  {cont__65_53, &frame__65_44, 353, 353, 9, 39},
  {cont__65_54, &frame__65_44, 354, 354, 9, 46},
  {cont__65_55, &frame__65_44, 355, 355, 16, 32},
  {cont__65_56, &frame__65_44, 355, 357, 9, 58},
  {cont__65_61, &frame__65_44, 358, 358, 9, 30},
  {cont__65_62, &frame__65_44, 359, 359, 9, 34},
  {cont__65_63, &frame__65_44, 360, 362, 9, 45},
  {cont__65_70, &frame__65_44, 363, 363, 10, 30},
  {cont__65_71, &frame__65_44, 363, 363, 9, 40},
  {cont__65_72, &frame__65_44, 363, 363, 9, 30},
  {cont__65_73, &frame__65_44, 363, 363, 46, 46},
  {entry__65_41, NULL, 346, 346, 14, 44},
  {cont__65_43, &frame__65_41, 346, 363, 7, 46},
  {entry__65_39, NULL, 345, 345, 8, 30},
  {cont__65_40, &frame__65_39, 345, 363, 5, 47},
  {entry__65_77, NULL, 364, 364, 39, 64},
  {entry__65_1_add_module_infos, NULL, 325, 325, 22, 27},
  {cont__65_2, &frame__65_1_add_module_infos, 325, 325, 3, 33},
  {cont__65_3, &frame__65_1_add_module_infos, 329, 343, 3, 54},
  {cont__65_38, &frame__65_1_add_module_infos, 344, 363, 3, 48},
  {cont__65_74, &frame__65_1_add_module_infos, 364, 364, 6, 31},
  {cont__65_75, &frame__65_1_add_module_infos, 364, 364, 6, 36},
  {cont__65_76, &frame__65_1_add_module_infos, 364, 364, 3, 64},
  {cont__65_78, &frame__65_1_add_module_infos, 364, 364, 64, 64},
  {entry__66_4, NULL, 375, 375, 23, 29},
  {entry__66_5, NULL, 376, 376, 47, 47},
  {cont__66_6, &frame__66_5, 376, 376, 22, 48},
  {cont__66_7, &frame__66_5, 376, 376, 70, 70},
  {cont__66_8, &frame__66_5, 376, 376, 50, 71},
  {cont__66_9, &frame__66_5, 376, 376, 5, 71},
  {cont__66_10, &frame__66_5, 377, 377, 8, 28},
  {cont__66_11, &frame__66_5, 377, 377, 5, 28},
  {entry__66_1_lookup, NULL, 374, 374, 3, 29},
  {cont__66_2, &frame__66_1_lookup, 375, 375, 6, 20},
  {cont__66_3, &frame__66_1_lookup, 375, 377, 3, 28},
  {entry__67_2, NULL, 380, 380, 43, 52},
  {cont__67_3, &frame__67_2, 380, 380, 27, 52},
  {entry__67_1_Gcc, NULL, 380, 380, 3, 52},
  {cont__67_5, &frame__67_1_Gcc, 381, 381, 3, 11},
  {entry__68_2, NULL, 384, 384, 41, 60},
  {entry__68_8, NULL, 386, 386, 27, 39},
  {cont__68_9, &frame__68_8, 386, 386, 21, 39},
  {entry__68_4, NULL, 385, 385, 5, 72},
  {cont__68_7, &frame__68_4, 386, 386, 5, 39},
  {cont__68_10, &frame__68_4, 387, 387, 17, 17},
  {entry__68_1_compile_c, NULL, 384, 384, 10, 60},
  {cont__68_3, &frame__68_1_compile_c, 384, 387, 3, 17},
  {entry__69_25, NULL, 414, 414, 45, 74},
  {cont__69_26, &frame__69_25, 414, 414, 9, 41},
  {cont__69_27, &frame__69_25, 414, 414, 9, 74},
  {cont__69_28, &frame__69_25, 414, 414, 9, 74},
  {entry__69_21, NULL, 413, 413, 43, 75},
  {cont__69_22, &frame__69_21, 413, 413, 9, 39},
  {cont__69_23, &frame__69_21, 413, 413, 9, 75},
  {cont__69_24, &frame__69_21, 414, 414, 9, 74},
  {cont__69_29, &frame__69_21, },
  {entry__69_19, NULL, 412, 412, 9, 32},
  {cont__69_20, &frame__69_19, },
  {cont__69_30, &frame__69_19, },
  {entry__69_17, NULL, 411, 411, 9, 29},
  {cont__69_18, &frame__69_17, },
  {cont__69_31, &frame__69_17, },
  {entry__69_41, NULL, 426, 426, 17, 47},
  {cont__69_42, &frame__69_41, 426, 426, 17, 67},
  {cont__69_43, &frame__69_41, 426, 426, 17, 67},
  {entry__69_45, NULL, 429, 429, 17, 21},
  {entry__69_38_check, NULL, 422, 422, 13, 42},
  {cont__69_39, &frame__69_38_check, 425, 425, 17, 38},
  {cont__69_40, &frame__69_38_check, 424, 426, 15, 66},
  {cont__69_44, &frame__69_38_check, 423, 429, 13, 22},
  {entry__69_58, NULL, 439, 439, 58, 58},
  {cont__69_59, &frame__69_58, 439, 439, 40, 59},
  {cont__69_60, &frame__69_58, 439, 439, 23, 60},
  {cont__69_61, &frame__69_58, 439, 439, 17, 60},
  {entry__69_63, NULL, 441, 441, 53, 77},
  {cont__69_64, &frame__69_63, 441, 441, 47, 77},
  {entry__69_62, NULL, 441, 441, 17, 77},
  {entry__69_55, NULL, 438, 438, 15, 40},
  {cont__69_57, &frame__69_55, 437, 441, 13, 78},
  {entry__69_37, NULL, 431, 431, 18, 41},
  {cont__69_47, &frame__69_37, 431, 431, 11, 47},
  {cont__69_48, &frame__69_37, 432, 432, 11, 26},
  {cont__69_49, &frame__69_37, 433, 433, 11, 20},
  {cont__69_50, &frame__69_37, 434, 434, 11, 50},
  {cont__69_51, &frame__69_37, 435, 435, 11, 44},
  {cont__69_52, &frame__69_37, 436, 436, 14, 30},
  {cont__69_54, &frame__69_37, 436, 441, 11, 79},
  {entry__69_36, NULL, 420, 441, 9, 80},
  {cont__69_65, &frame__69_36, 441, 441, 80, 80},
  {entry__69_33, NULL, 417, 417, 7, 55},
  {cont__69_34, &frame__69_33, 418, 418, 7, 38},
  {cont__69_35, &frame__69_33, 419, 441, 7, 81},
  {entry__69_74, NULL, 456, 456, 29, 41},
  {cont__69_75, &frame__69_74, 456, 456, 23, 41},
  {entry__69_67, NULL, 450, 450, 7, 36},
  {cont__69_68, &frame__69_67, 451, 451, 7, 22},
  {cont__69_69, &frame__69_67, 452, 452, 7, 31},
  {cont__69_70, &frame__69_67, 453, 453, 7, 32},
  {cont__69_71, &frame__69_67, 454, 454, 7, 43},
  {cont__69_72, &frame__69_67, 455, 455, 7, 32},
  {cont__69_73, &frame__69_67, 456, 456, 7, 41},
  {cont__69_76, &frame__69_67, 457, 457, 25, 35},
  {cont__69_77, &frame__69_67, 457, 457, 7, 35},
  {cont__69_78, &frame__69_67, 457, 457, 35, 35},
  {entry__69_2, NULL, 399, 399, 48, 48},
  {cont__69_3, &frame__69_2, 399, 399, 5, 49},
  {cont__69_4, &frame__69_2, 400, 400, 35, 57},
  {cont__69_5, &frame__69_2, 400, 400, 5, 58},
  {cont__69_6, &frame__69_2, 401, 401, 5, 42},
  {cont__69_7, &frame__69_2, 402, 402, 42, 64},
  {cont__69_8, &frame__69_2, 402, 402, 5, 70},
  {cont__69_10, &frame__69_2, 403, 403, 51, 62},
  {cont__69_11, &frame__69_2, 403, 403, 39, 63},
  {cont__69_12, &frame__69_2, 403, 403, 5, 71},
  {cont__69_13, &frame__69_2, 404, 404, 5, 34},
  {cont__69_14, &frame__69_2, 405, 405, 5, 32},
  {cont__69_15, &frame__69_2, 406, 406, 5, 38},
  {cont__69_16, &frame__69_2, 408, 414, 5, 75},
  {cont__69_32, &frame__69_2, 416, 441, 5, 82},
  {cont__69_66, &frame__69_2, 442, 457, 5, 35},
  {cont__69_79, &frame__69_2, 458, 458, 5, 19},
  {cont__69_80, &frame__69_2, 459, 459, 8, 21},
  {cont__69_81, &frame__69_2, 459, 459, 5, 21},
  {entry__69_1_compile_meta_module, NULL, 398, 459, 3, 21},
  {entry__70_13, NULL, 484, 484, 43, 43},
  {cont__70_14, &frame__70_13, 484, 484, 15, 44},
  {cont__70_15, &frame__70_13, 486, 486, 48, 48},
  {cont__70_16, &frame__70_13, 486, 486, 24, 49},
  {cont__70_17, &frame__70_13, 486, 486, 17, 59},
  {cont__70_18, &frame__70_13, 487, 487, 44, 44},
  {cont__70_19, &frame__70_13, 487, 487, 24, 45},
  {cont__70_20, &frame__70_13, 487, 487, 17, 55},
  {cont__70_21, &frame__70_13, 485, 487, 15, 55},
  {entry__70_11, NULL, 483, 483, 16, 26},
  {cont__70_12, &frame__70_11, 483, 487, 13, 56},
  {entry__70_24, NULL, 493, 493, 17, 36},
  {entry__70_23, NULL, },
  {cont__70_25, &frame__70_23, },
  {entry__70_27, NULL, 495, 495, 32, 57},
  {cont__70_28, &frame__70_27, 495, 495, 17, 66},
  {entry__70_30, NULL, 498, 498, 44, 71},
  {cont__70_31, &frame__70_30, 498, 498, 30, 72},
  {cont__70_33, &frame__70_30, 498, 498, 19, 73},
  {cont__70_34, &frame__70_30, 498, 498, 78, 78},
  {entry__70_29, NULL, 497, 498, 17, 78},
  {entry__70_22, NULL, },
  {cont__70_26, &frame__70_22, 489, 498, 13, 80},
  {entry__70_9, NULL, 482, 482, 11, 36},
  {cont__70_10, &frame__70_9, 481, 498, 9, 82},
  {entry__70_36, NULL, 500, 500, 37, 64},
  {cont__70_37, &frame__70_36, 500, 500, 26, 65},
  {cont__70_38, &frame__70_36, 500, 500, 70, 70},
  {entry__70_35, NULL, 500, 500, 9, 70},
  {entry__70_2, NULL, 473, 473, 12, 35},
  {cont__70_3, &frame__70_2, 473, 473, 5, 42},
  {cont__70_4, &frame__70_2, 474, 474, 5, 20},
  {cont__70_5, &frame__70_2, 475, 475, 5, 14},
  {cont__70_6, &frame__70_2, 476, 476, 5, 44},
  {cont__70_7, &frame__70_2, 477, 477, 5, 38},
  {cont__70_8, &frame__70_2, 478, 500, 5, 71},
  {entry__70_1_build_dependencies, NULL, 472, 500, 3, 72},
  {cont__70_41, &frame__70_1_build_dependencies, 500, 500, 72, 72},
  {entry__71_9, NULL, 522, 522, 28, 44},
  {cont__71_10, &frame__71_9, 522, 522, 28, 44},
  {entry__71_12, NULL, 523, 523, 9, 72},
  {entry__71_18, NULL, 530, 530, 11, 40},
  {cont__71_19, &frame__71_18, 530, 530, 11, 60},
  {cont__71_20, &frame__71_18, 530, 530, 11, 60},
  {entry__71_22, NULL, 532, 532, 11, 59},
  {cont__71_23, &frame__71_22, 532, 532, 59, 59},
  {entry__71_3, NULL, 520, 520, 7, 45},
  {cont__71_4, &frame__71_3, 521, 521, 58, 58},
  {cont__71_5, &frame__71_3, 521, 521, 34, 59},
  {cont__71_6, &frame__71_3, 521, 521, 7, 75},
  {cont__71_7, &frame__71_3, 522, 522, 10, 23},
  {cont__71_8, &frame__71_3, 522, 522, 10, 44},
  {cont__71_11, &frame__71_3, 522, 523, 7, 72},
  {cont__71_13, &frame__71_3, 524, 524, 7, 53},
  {cont__71_14, &frame__71_3, 525, 525, 7, 38},
  {cont__71_15, &frame__71_3, 526, 526, 7, 34},
  {cont__71_16, &frame__71_3, 529, 529, 11, 40},
  {cont__71_17, &frame__71_3, 528, 530, 9, 59},
  {cont__71_21, &frame__71_3, 527, 532, 7, 60},
  {entry__71_27, NULL, 535, 535, 22, 43},
  {cont__71_28, &frame__71_27, 535, 535, 48, 48},
  {entry__71_32, NULL, 541, 541, 29, 56},
  {cont__71_33, &frame__71_32, 541, 541, 9, 56},
  {cont__71_34, &frame__71_32, 541, 541, 9, 56},
  {entry__71_30, NULL, 540, 540, 9, 27},
  {cont__71_31, &frame__71_30, 541, 541, 9, 56},
  {cont__71_35, &frame__71_30, },
  {entry__71_42, NULL, 544, 544, 21, 63},
  {entry__71_45, NULL, 545, 545, 35, 53},
  {entry__71_47, NULL, 546, 546, 32, 54},
  {entry__71_51, NULL, 548, 548, 26, 56},
  {entry__71_37, NULL, 543, 543, 50, 59},
  {cont__71_39, &frame__71_37, 543, 543, 61, 70},
  {cont__71_40, &frame__71_37, 543, 543, 9, 71},
  {cont__71_41, &frame__71_37, 544, 544, 9, 63},
  {cont__71_44, &frame__71_37, 545, 545, 9, 53},
  {cont__71_46, &frame__71_37, 546, 546, 9, 54},
  {cont__71_48, &frame__71_37, 547, 547, 25, 37},
  {cont__71_49, &frame__71_37, 547, 547, 9, 37},
  {cont__71_50, &frame__71_37, 548, 548, 9, 56},
  {cont__71_52, &frame__71_37, 548, 548, 56, 56},
  {entry__71_57, NULL, 555, 555, 44, 71},
  {cont__71_58, &frame__71_57, 555, 555, 13, 40},
  {cont__71_59, &frame__71_57, 555, 555, 13, 71},
  {cont__71_60, &frame__71_57, 555, 555, 13, 71},
  {entry__71_63, NULL, 557, 557, 30, 60},
  {entry__71_62, NULL, 557, 557, 13, 60},
  {entry__71_66, NULL, 562, 562, 17, 44},
  {cont__71_67, &frame__71_66, 562, 562, 17, 69},
  {cont__71_68, &frame__71_66, 562, 562, 17, 69},
  {entry__71_70, NULL, 564, 564, 17, 68},
  {cont__71_71, &frame__71_70, 564, 564, 68, 68},
  {entry__71_64, NULL, 561, 561, 17, 51},
  {cont__71_65, &frame__71_64, 560, 562, 15, 68},
  {cont__71_69, &frame__71_64, 559, 564, 13, 69},
  {entry__71_53, NULL, 550, 550, 9, 30},
  {cont__71_54, &frame__71_53, 551, 551, 9, 32},
  {cont__71_55, &frame__71_53, 554, 554, 13, 31},
  {cont__71_56, &frame__71_53, 553, 555, 11, 70},
  {cont__71_61, &frame__71_53, 552, 564, 9, 71},
  {entry__71_2_compile_submodule, NULL, 519, 532, 5, 61},
  {cont__71_24, &frame__71_2_compile_submodule, 533, 533, 5, 48},
  {cont__71_25, &frame__71_2_compile_submodule, 534, 534, 5, 28},
  {cont__71_26, &frame__71_2_compile_submodule, 535, 535, 5, 48},
  {cont__71_29, &frame__71_2_compile_submodule, 536, 536, 5, 21},
  {cont__71_36, &frame__71_2_compile_submodule, 537, 564, 5, 73},
  {cont__71_72, &frame__71_2_compile_submodule, 565, 565, 5, 63},
  {entry__71_75, NULL, 569, 570, 11, 56},
  {cont__71_78, &frame__71_75, 569, 570, 5, 56},
  {entry__71_91, NULL, 577, 577, 51, 75},
  {cont__71_92, &frame__71_91, 577, 577, 32, 75},
  {cont__71_93, &frame__71_91, 577, 577, 75, 75},
  {entry__71_86, NULL, 576, 576, 59, 59},
  {cont__71_87, &frame__71_86, 576, 576, 30, 60},
  {cont__71_88, &frame__71_86, 576, 576, 25, 61},
  {cont__71_89, &frame__71_86, 576, 576, 7, 61},
  {cont__71_90, &frame__71_86, 577, 577, 7, 75},
  {entry__71_99, NULL, 584, 584, 37, 60},
  {cont__71_100, &frame__71_99, 584, 584, 37, 60},
  {entry__71_102, NULL, 586, 586, 35, 35},
  {entry__71_96, NULL, 583, 583, 11, 47},
  {cont__71_97, &frame__71_96, 584, 584, 14, 32},
  {cont__71_98, &frame__71_96, 584, 584, 14, 60},
  {cont__71_101, &frame__71_96, 584, 586, 11, 35},
  {entry__71_104, NULL, 590, 590, 13, 37},
  {cont__71_105, &frame__71_104, 591, 591, 13, 32},
  {cont__71_106, &frame__71_104, 588, 591, 11, 32},
  {entry__71_95, NULL, 582, 586, 9, 36},
  {cont__71_103, &frame__71_95, 587, 591, 9, 33},
  {entry__71_113, NULL, 599, 599, 39, 62},
  {cont__71_114, &frame__71_113, 599, 599, 39, 62},
  {entry__71_116, NULL, 601, 601, 37, 37},
  {entry__71_110, NULL, 598, 598, 13, 77},
  {cont__71_111, &frame__71_110, 599, 599, 16, 34},
  {cont__71_112, &frame__71_110, 599, 599, 16, 62},
  {cont__71_115, &frame__71_110, 599, 601, 13, 37},
  {entry__71_119, NULL, 603, 603, 32, 53},
  {cont__71_120, &frame__71_119, 603, 603, 13, 65},
  {cont__71_121, &frame__71_119, 604, 604, 13, 39},
  {cont__71_122, &frame__71_119, 605, 605, 13, 35},
  {cont__71_123, &frame__71_119, 605, 605, 38, 38},
  {entry__71_109, NULL, 597, 601, 11, 38},
  {cont__71_117, &frame__71_109, 602, 602, 14, 37},
  {cont__71_118, &frame__71_109, 602, 605, 11, 38},
  {entry__71_130, NULL, 610, 610, 40, 69},
  {cont__71_132, &frame__71_130, 610, 610, 69, 69},
  {entry__71_129, NULL, 610, 610, 13, 69},
  {entry__71_125, NULL, 607, 607, 11, 61},
  {cont__71_126, &frame__71_125, 608, 608, 11, 38},
  {cont__71_127, &frame__71_125, 609, 609, 14, 33},
  {cont__71_128, &frame__71_125, 609, 610, 11, 69},
  {cont__71_133, &frame__71_125, 611, 611, 11, 39},
  {cont__71_134, &frame__71_125, 611, 611, 39, 39},
  {entry__71_108, NULL, 594, 605, 9, 39},
  {cont__71_124, &frame__71_108, 606, 611, 9, 39},
  {entry__71_94, NULL, 579, 591, 7, 34},
  {cont__71_107, &frame__71_94, 592, 611, 7, 40},
  {entry__71_1_compile_module, NULL, 567, 567, 3, 40},
  {cont__71_73, &frame__71_1_compile_module, 568, 568, 10, 28},
  {cont__71_74, &frame__71_1_compile_module, 568, 570, 3, 57},
  {cont__71_79, &frame__71_1_compile_module, 571, 571, 3, 39},
  {cont__71_81, &frame__71_1_compile_module, 572, 572, 6, 24},
  {cont__71_82, &frame__71_1_compile_module, 572, 572, 3, 31},
  {cont__71_83, &frame__71_1_compile_module, 573, 573, 3, 22},
  {cont__71_84, &frame__71_1_compile_module, 575, 575, 5, 21},
  {cont__71_85, &frame__71_1_compile_module, 574, 611, 3, 42},
  {cont__71_135, &frame__71_1_compile_module, 611, 611, 42, 42},
  {entry__72_4, NULL, 620, 620, 21, 41},
  {cont__72_5, &frame__72_4, 620, 620, 43, 67},
  {cont__72_6, &frame__72_4, 620, 620, 5, 67},
  {entry__72_8, NULL, 622, 622, 20, 40},
  {cont__72_9, &frame__72_8, 622, 622, 42, 66},
  {cont__72_10, &frame__72_8, 622, 622, 5, 66},
  {entry__72_1_compile_modules, NULL, 618, 618, 47, 66},
  {cont__72_2, &frame__72_1_compile_modules, 618, 618, 3, 66},
  {cont__72_3, &frame__72_1_compile_modules, 619, 620, 3, 67},
  {cont__72_7, &frame__72_1_compile_modules, 621, 622, 3, 66},
  {entry__74_6, NULL, 631, 631, 34, 58},
  {cont__74_8, &frame__74_6, 631, 631, 25, 58},
  {entry__74_2, NULL, 630, 630, 5, 40},
  {cont__74_4, &frame__74_2, 631, 631, 8, 22},
  {cont__74_5, &frame__74_2, 631, 631, 5, 58},
  {cont__74_9, &frame__74_2, 632, 632, 40, 57},
  {cont__74_10, &frame__74_2, 632, 632, 5, 57},
  {cont__74_12, &frame__74_2, 633, 633, 35, 54},
  {cont__74_13, &frame__74_2, 633, 633, 5, 54},
  {entry__74_1_show_file_list, NULL, 629, 633, 3, 54},
  {entry__75_7, NULL, 642, 642, 60, 70},
  {cont__75_9, &frame__75_7, 642, 642, 40, 70},
  {cont__75_10, &frame__75_7, 642, 642, 70, 70},
  {entry__75_5, NULL, 642, 642, 14, 30},
  {cont__75_6, &frame__75_5, 642, 642, 5, 70},
  {entry__75_12, NULL, 643, 643, 54, 77},
  {cont__75_13, &frame__75_12, 643, 643, 27, 77},
  {entry__75_16, NULL, 644, 644, 30, 54},
  {cont__75_17, &frame__75_16, 644, 644, 54, 54},
  {entry__75_24, NULL, 653, 653, 16, 45},
  {cont__75_27, &frame__75_24, 653, 653, 13, 45},
  {entry__75_28, NULL, 654, 654, 16, 38},
  {cont__75_30, &frame__75_28, 654, 654, 13, 38},
  {entry__75_21, NULL, 652, 652, 13, 39},
  {cont__75_23, &frame__75_21, 651, 654, 11, 37},
  {cont__75_31, &frame__75_21, 650, 654, 9, 39},
  {entry__75_34, NULL, 658, 658, 25, 44},
  {cont__75_35, &frame__75_34, 658, 658, 52, 71},
  {cont__75_36, &frame__75_34, 658, 658, 16, 73},
  {cont__75_37, &frame__75_34, 658, 659, 13, 26},
  {entry__75_38, NULL, 660, 660, 16, 29},
  {cont__75_39, &frame__75_38, 660, 660, 13, 29},
  {entry__75_32, NULL, 657, 657, 13, 34},
  {cont__75_33, &frame__75_32, 656, 660, 11, 28},
  {cont__75_40, &frame__75_32, 655, 660, 9, 30},
  {entry__75_19, NULL, 649, 649, 9, 35},
  {cont__75_20, &frame__75_19, 648, 660, 7, 30},
  {cont__75_41, &frame__75_19, 646, 660, 5, 32},
  {cont__75_42, &frame__75_19, 660, 660, 33, 33},
  {entry__75_1_library_paths_and_file_list, NULL, 636, 636, 3, 16},
  {cont__75_2, &frame__75_1_library_paths_and_file_list, 640, 640, 3, 39},
  {cont__75_3, &frame__75_1_library_paths_and_file_list, 641, 641, 6, 21},
  {cont__75_4, &frame__75_1_library_paths_and_file_list, 641, 642, 3, 70},
  {cont__75_11, &frame__75_1_library_paths_and_file_list, 643, 643, 3, 77},
  {cont__75_15, &frame__75_1_library_paths_and_file_list, 644, 644, 3, 54},
  {cont__75_18, &frame__75_1_library_paths_and_file_list, 645, 660, 3, 33},
  {cont__75_43, &frame__75_1_library_paths_and_file_list, 661, 661, 24, 57},
  {cont__75_44, &frame__75_1_library_paths_and_file_list, 661, 661, 3, 57},
  {entry__76_9, NULL, 671, 671, 51, 64},
  {cont__76_10, &frame__76_9, 671, 671, 51, 64},
  {entry__76_7, NULL, 671, 671, 37, 46},
  {cont__76_8, &frame__76_7, 671, 671, 37, 64},
  {cont__76_11, &frame__76_7, 671, 671, 37, 64},
  {entry__76_29, NULL, 682, 682, 25, 59},
  {cont__76_31, &frame__76_29, 682, 682, 21, 60},
  {cont__76_32, &frame__76_29, 682, 682, 21, 60},
  {entry__76_25, NULL, 681, 681, 25, 58},
  {cont__76_27, &frame__76_25, 681, 681, 21, 59},
  {cont__76_28, &frame__76_25, 682, 682, 21, 60},
  {cont__76_33, &frame__76_25, },
  {entry__76_38, NULL, 686, 686, 46, 80},
  {cont__76_39, &frame__76_38, 686, 686, 46, 80},
  {entry__76_41, NULL, 688, 688, 44, 74},
  {cont__76_42, &frame__76_41, 688, 688, 23, 74},
  {entry__76_35, NULL, 686, 686, 21, 34},
  {cont__76_36, &frame__76_35, 686, 686, 21, 41},
  {cont__76_37, &frame__76_35, 686, 686, 21, 80},
  {cont__76_40, &frame__76_35, 685, 688, 19, 75},
  {entry__76_49, NULL, 691, 691, 60, 60},
  {cont__76_50, &frame__76_49, 691, 691, 44, 61},
  {cont__76_51, &frame__76_49, 691, 691, 23, 61},
  {entry__76_46, NULL, 690, 690, 35, 62},
  {cont__76_47, &frame__76_46, 690, 690, 35, 67},
  {cont__76_48, &frame__76_46, 690, 691, 21, 61},
  {entry__76_43, NULL, 689, 689, 22, 62},
  {cont__76_45, &frame__76_43, 689, 691, 19, 62},
  {entry__76_52, NULL, 693, 693, 21, 52},
  {entry__76_54, NULL, 694, 694, 31, 45},
  {entry__76_21, NULL, 680, 680, 21, 34},
  {cont__76_22, &frame__76_21, 680, 680, 21, 41},
  {cont__76_23, &frame__76_21, 680, 680, 21, 41},
  {cont__76_24, &frame__76_21, 678, 682, 17, 61},
  {cont__76_34, &frame__76_21, 684, 693, 17, 53},
  {cont__76_53, &frame__76_21, 694, 694, 17, 45},
  {cont__76_56, &frame__76_21, 695, 695, 17, 33},
  {entry__76_17, NULL, 675, 675, 15, 38},
  {cont__76_18, &frame__76_17, 676, 676, 15, 50},
  {cont__76_19, &frame__76_17, 677, 677, 18, 39},
  {cont__76_20, &frame__76_17, 677, 695, 15, 33},
  {entry__76_13, NULL, 672, 672, 33, 37},
  {cont__76_14, &frame__76_13, 672, 672, 13, 38},
  {cont__76_15, &frame__76_13, 674, 674, 20, 42},
  {cont__76_16, &frame__76_13, 674, 695, 13, 34},
  {entry__76_5, NULL, 671, 671, 18, 32},
  {cont__76_6, &frame__76_5, 671, 671, 18, 64},
  {cont__76_12, &frame__76_5, 671, 695, 11, 35},
  {entry__76_59, NULL, 697, 697, 33, 42},
  {cont__76_60, &frame__76_59, 697, 697, 33, 42},
  {entry__76_62, NULL, 697, 697, 50, 50},
  {entry__76_57, NULL, 697, 697, 14, 28},
  {cont__76_58, &frame__76_57, 697, 697, 14, 42},
  {cont__76_61, &frame__76_57, 697, 697, 11, 50},
  {entry__76_3, NULL, 670, 670, 9, 20},
  {cont__76_4, &frame__76_3, 669, 697, 7, 51},
  {entry__76_2_collect_declarations, NULL, 668, 697, 5, 52},
  {entry__76_63, NULL, 699, 699, 28, 54},
  {entry__76_74, NULL, 704, 704, 22, 59},
  {entry__76_1_create_imports, NULL, 699, 699, 3, 54},
  {cont__76_64, &frame__76_1_create_imports, 700, 700, 3, 49},
  {cont__76_66, &frame__76_1_create_imports, 701, 701, 3, 18},
  {cont__76_67, &frame__76_1_create_imports, 702, 702, 3, 15},
  {cont__76_68, &frame__76_1_create_imports, 703, 703, 22, 42},
  {cont__76_69, &frame__76_1_create_imports, 703, 703, 22, 45},
  {cont__76_70, &frame__76_1_create_imports, 703, 703, 48, 48},
  {cont__76_71, &frame__76_1_create_imports, 703, 703, 9, 49},
  {cont__76_72, &frame__76_1_create_imports, 703, 703, 3, 49},
  {cont__76_73, &frame__76_1_create_imports, 704, 704, 3, 59},
  {entry__77_3, NULL, 707, 707, 32, 67},
  {entry__77_7, NULL, 709, 710, 5, 57},
  {entry__77_1_compile_exe, NULL, 707, 707, 6, 29},
  {cont__77_2, &frame__77_1_compile_exe, 707, 707, 3, 67},
  {cont__77_5, &frame__77_1_compile_exe, 708, 708, 10, 42},
  {cont__77_6, &frame__77_1_compile_exe, 708, 710, 3, 58},
  {cont__77_9, &frame__77_1_compile_exe, 712, 712, 3, 53},
  {cont__77_10, &frame__77_1_compile_exe, 713, 713, 46, 46},
  {cont__77_11, &frame__77_1_compile_exe, 713, 713, 3, 47},
  {cont__77_12, &frame__77_1_compile_exe, 714, 714, 3, 28},
  {cont__77_13, &frame__77_1_compile_exe, 714, 714, 28, 28},
  {entry__78_2, NULL, 719, 719, 11, 29},
  {cont__78_3, &frame__78_2, 719, 719, 5, 29},
  {cont__78_4, &frame__78_2, 719, 719, 29, 29},
  {entry__78_1_dump_source_or_check, NULL, 717, 719, 3, 29},
  {entry__79_4, NULL, 723, 723, 41, 65},
  {cont__79_5, &frame__79_4, 723, 723, 34, 75},
  {cont__79_6, &frame__79_4, 723, 723, 75, 75},
  {entry__79_8, NULL, 725, 725, 48, 57},
  {cont__79_9, &frame__79_8, 725, 725, 59, 68},
  {cont__79_10, &frame__79_8, 725, 725, 7, 69},
  {cont__79_11, &frame__79_8, 726, 726, 13, 31},
  {cont__79_12, &frame__79_8, 726, 726, 7, 31},
  {cont__79_13, &frame__79_8, 726, 726, 31, 31},
  {entry__79_15, NULL, 727, 727, 28, 50},
  {entry__79_18, NULL, 729, 729, 24, 59},
  {entry__79_2, NULL, 723, 723, 8, 31},
  {cont__79_3, &frame__79_2, 723, 723, 5, 75},
  {cont__79_7, &frame__79_2, 724, 726, 5, 31},
  {cont__79_14, &frame__79_2, 727, 727, 5, 50},
  {cont__79_16, &frame__79_2, 728, 728, 5, 15},
  {cont__79_17, &frame__79_2, 729, 729, 5, 59},
  {entry__79_1_print_c, NULL, 722, 729, 3, 59},
  {entry__80_5, NULL, 738, 738, 9, 43},
  {cont__80_6, &frame__80_5, 739, 739, 12, 28},
  {cont__80_7, &frame__80_5, 739, 739, 9, 34},
  {cont__80_8, &frame__80_5, 740, 740, 9, 21},
  {cont__80_9, &frame__80_5, 741, 741, 9, 64},
  {cont__80_10, &frame__80_5, 742, 742, 12, 23},
  {cont__80_11, &frame__80_5, 742, 742, 9, 29},
  {cont__80_12, &frame__80_5, 743, 743, 22, 22},
  {entry__80_4, NULL, 737, 743, 7, 22},
  {cont__80_13, &frame__80_4, 743, 743, 22, 22},
  {entry__80_3, NULL, 736, 743, 5, 23},
  {entry__80_17, NULL, 747, 747, 19, 65},
  {entry__80_16, NULL, 747, 747, 7, 65},
  {cont__80_19, &frame__80_16, 748, 748, 63, 63},
  {cont__80_20, &frame__80_16, 748, 748, 37, 64},
  {cont__80_21, &frame__80_16, 748, 748, 7, 64},
  {cont__80_22, &frame__80_16, 748, 748, 64, 64},
  {entry__80_25, NULL, 751, 751, 21, 66},
  {entry__80_24, NULL, 751, 751, 9, 66},
  {cont__80_26, &frame__80_24, 752, 752, 9, 44},
  {entry__80_23, NULL, 750, 752, 7, 44},
  {cont__80_27, &frame__80_23, 753, 753, 7, 32},
  {cont__80_29, &frame__80_23, 754, 754, 7, 32},
  {cont__80_31, &frame__80_23, 755, 755, 7, 34},
  {entry__80_35, NULL, 758, 758, 5, 40},
  {cont__80_36, &frame__80_35, 759, 759, 5, 32},
  {cont__80_37, &frame__80_35, 760, 760, 5, 20},
  {entry__80_1_list_dependencies, NULL, 732, 732, 3, 80},
  {cont__80_2, &frame__80_1_list_dependencies, 733, 743, 3, 24},
  {cont__80_14, &frame__80_1_list_dependencies, 745, 745, 5, 28},
  {cont__80_15, &frame__80_1_list_dependencies, 744, 755, 3, 35},
  {cont__80_33, &frame__80_1_list_dependencies, 756, 756, 3, 29},
  {cont__80_34, &frame__80_1_list_dependencies, 757, 760, 3, 20},
  {entry__81_7, NULL, 767, 768, 14, 58},
  {cont__81_10, &frame__81_7, 767, 768, 7, 58},
  {entry__81_12, NULL, 769, 769, 17, 73},
  {entry__81_34, NULL, 801, 803, 21, 49},
  {cont__81_37, &frame__81_34, 801, 803, 7, 49},
  {cont__81_38, &frame__81_34, 803, 803, 50, 50},
  {entry__81_48, NULL, 823, 823, 7, 42},
  {cont__81_49, &frame__81_48, 824, 824, 7, 34},
  {cont__81_50, &frame__81_48, 825, 830, 21, 23},
  {cont__81_53, &frame__81_48, 825, 830, 7, 23},
  {cont__81_54, &frame__81_48, 830, 830, 24, 24},
  {entry__81_2, NULL, 764, 764, 5, 55},
  {cont__81_4, &frame__81_2, 765, 765, 5, 31},
  {cont__81_5, &frame__81_2, 766, 766, 8, 22},
  {cont__81_6, &frame__81_2, 766, 768, 5, 59},
  {cont__81_11, &frame__81_2, 769, 769, 5, 73},
  {cont__81_14, &frame__81_2, 770, 770, 5, 40},
  {cont__81_15, &frame__81_2, 771, 771, 5, 18},
  {cont__81_16, &frame__81_2, 772, 772, 49, 49},
  {cont__81_17, &frame__81_2, 772, 772, 15, 50},
  {cont__81_18, &frame__81_2, 772, 772, 5, 74},
  {cont__81_19, &frame__81_2, 773, 773, 5, 31},
  {cont__81_20, &frame__81_2, 774, 774, 30, 73},
  {cont__81_21, &frame__81_2, 774, 774, 5, 78},
  {cont__81_22, &frame__81_2, 775, 775, 5, 33},
  {cont__81_24, &frame__81_2, 776, 776, 5, 61},
  {cont__81_27, &frame__81_2, 777, 777, 5, 25},
  {cont__81_28, &frame__81_2, 779, 799, 19, 22},
  {cont__81_32, &frame__81_2, 779, 799, 5, 22},
  {cont__81_33, &frame__81_2, 800, 803, 5, 50},
  {cont__81_39, &frame__81_2, 804, 821, 19, 21},
  {cont__81_46, &frame__81_2, 804, 821, 5, 21},
  {cont__81_47, &frame__81_2, 822, 830, 5, 24},
  {cont__81_55, &frame__81_2, 831, 837, 5, 32},
  {cont__81_57, &frame__81_2, 838, 838, 5, 25},
  {entry__81_1_build_codeblocks_project, NULL, 763, 838, 3, 25},
  {entry__82_4, NULL, 841, 841, 26, 56},
  {entry__82_7, NULL, 845, 845, 7, 41},
  {entry__82_12, NULL, 851, 851, 29, 50},
  {cont__82_13, &frame__82_12, 851, 851, 29, 55},
  {cont__82_14, &frame__82_12, 851, 851, 9, 56},
  {cont__82_15, &frame__82_12, 852, 852, 9, 47},
  {cont__82_16, &frame__82_12, 852, 852, 47, 47},
  {entry__82_20, NULL, 859, 859, 53, 66},
  {cont__82_21, &frame__82_20, 859, 859, 14, 67},
  {cont__82_23, &frame__82_20, 859, 859, 11, 67},
  {entry__82_24, NULL, 861, 861, 53, 67},
  {cont__82_26, &frame__82_24, 861, 861, 14, 68},
  {cont__82_27, &frame__82_24, 861, 861, 11, 68},
  {entry__82_28, NULL, 863, 863, 53, 69},
  {cont__82_30, &frame__82_28, 863, 863, 14, 70},
  {cont__82_31, &frame__82_28, 863, 863, 11, 70},
  {entry__82_32, NULL, 864, 864, 14, 50},
  {cont__82_34, &frame__82_32, 864, 864, 11, 50},
  {entry__82_38, NULL, 866, 866, 19, 56},
  {entry__82_47, NULL, 873, 873, 38, 63},
  {cont__82_48, &frame__82_47, 873, 873, 13, 63},
  {cont__82_49, &frame__82_47, 873, 873, 13, 63},
  {entry__82_51, NULL, 875, 875, 25, 25},
  {entry__82_44, NULL, 869, 869, 9, 32},
  {cont__82_45, &frame__82_44, 872, 872, 13, 29},
  {cont__82_46, &frame__82_44, 871, 873, 11, 62},
  {cont__82_50, &frame__82_44, 870, 875, 9, 26},
  {entry__82_54, NULL, 877, 877, 21, 54},
  {entry__82_63, NULL, 887, 887, 35, 47},
  {cont__82_64, &frame__82_63, 887, 887, 29, 47},
  {entry__82_57, NULL, 883, 883, 15, 76},
  {cont__82_59, &frame__82_57, 884, 884, 15, 43},
  {cont__82_60, &frame__82_57, 881, 886, 13, 26},
  {cont__82_62, &frame__82_57, 887, 887, 13, 47},
  {entry__82_70, NULL, 895, 895, 35, 47},
  {cont__82_71, &frame__82_70, 895, 895, 29, 47},
  {entry__82_65, NULL, 891, 891, 15, 43},
  {cont__82_66, &frame__82_65, 892, 892, 15, 30},
  {cont__82_68, &frame__82_65, 889, 894, 13, 26},
  {cont__82_69, &frame__82_65, 895, 895, 13, 47},
  {entry__82_79, NULL, 906, 906, 35, 47},
  {cont__82_80, &frame__82_79, 906, 906, 29, 47},
  {entry__82_72, NULL, 899, 901, 15, 23},
  {cont__82_74, &frame__82_72, 902, 902, 15, 43},
  {cont__82_75, &frame__82_72, 903, 903, 15, 30},
  {cont__82_76, &frame__82_72, 897, 905, 13, 26},
  {cont__82_78, &frame__82_72, 906, 906, 13, 47},
  {entry__82_84, NULL, 913, 913, 35, 47},
  {cont__82_85, &frame__82_84, 913, 913, 29, 47},
  {entry__82_81, NULL, 910, 910, 15, 43},
  {cont__82_82, &frame__82_81, 908, 912, 13, 26},
  {cont__82_83, &frame__82_81, 913, 913, 13, 47},
  {entry__82_53, NULL, 877, 877, 9, 54},
  {cont__82_56, &frame__82_53, 878, 913, 9, 48},
  {entry__82_8, NULL, 849, 849, 7, 56},
  {cont__82_10, &frame__82_8, 850, 850, 10, 38},
  {cont__82_11, &frame__82_8, 850, 852, 7, 47},
  {cont__82_17, &frame__82_8, 853, 853, 56, 56},
  {cont__82_18, &frame__82_8, 853, 853, 7, 57},
  {cont__82_19, &frame__82_8, 855, 864, 7, 51},
  {cont__82_37, &frame__82_8, 866, 866, 7, 56},
  {cont__82_40, &frame__82_8, 867, 867, 63, 63},
  {cont__82_41, &frame__82_8, 867, 867, 37, 64},
  {cont__82_42, &frame__82_8, 867, 867, 7, 64},
  {cont__82_43, &frame__82_8, 868, 875, 7, 27},
  {cont__82_52, &frame__82_8, 876, 913, 7, 49},
  {entry__82_1_build_library, NULL, 841, 841, 6, 23},
  {cont__82_3, &frame__82_1_build_library, 841, 841, 3, 56},
  {cont__82_6, &frame__82_1_build_library, 843, 913, 3, 51},
  {cont__82_86, &frame__82_1_build_library, 913, 913, 51, 51},
  {entry__83_6, NULL, 920, 921, 11, 42},
  {cont__83_9, &frame__83_6, 920, 921, 5, 42},
  {entry__83_13, NULL, 926, 926, 38, 65},
  {cont__83_14, &frame__83_13, 926, 926, 7, 34},
  {cont__83_15, &frame__83_13, 926, 926, 7, 65},
  {cont__83_16, &frame__83_13, 926, 926, 7, 65},
  {entry__83_19, NULL, 928, 928, 28, 65},
  {cont__83_21, &frame__83_19, 928, 928, 19, 65},
  {entry__83_18, NULL, 928, 928, 7, 65},
  {cont__83_22, &frame__83_18, 929, 929, 7, 37},
  {entry__83_1_maybe_compile_c_file, NULL, 916, 916, 3, 35},
  {cont__83_2, &frame__83_1_maybe_compile_c_file, 917, 917, 3, 35},
  {cont__83_3, &frame__83_1_maybe_compile_c_file, 918, 918, 3, 26},
  {cont__83_4, &frame__83_1_maybe_compile_c_file, 919, 919, 6, 24},
  {cont__83_5, &frame__83_1_maybe_compile_c_file, 919, 921, 3, 43},
  {cont__83_10, &frame__83_1_maybe_compile_c_file, 922, 922, 3, 26},
  {cont__83_11, &frame__83_1_maybe_compile_c_file, 925, 925, 7, 25},
  {cont__83_12, &frame__83_1_maybe_compile_c_file, 924, 926, 5, 64},
  {cont__83_17, &frame__83_1_maybe_compile_c_file, 923, 929, 3, 38},
  {entry__85_11, NULL, 945, 945, 39, 41},
  {cont__85_12, &frame__85_11, 945, 945, 36, 41},
  {cont__85_13, &frame__85_11, 945, 945, 28, 43},
  {cont__85_15, &frame__85_11, 945, 945, 21, 48},
  {cont__85_16, &frame__85_11, 945, 945, 48, 48},
  {entry__85_6, NULL, 944, 944, 13, 26},
  {cont__85_7, &frame__85_6, 944, 944, 9, 28},
  {cont__85_8, &frame__85_6, 945, 945, 16, 18},
  {cont__85_9, &frame__85_6, 945, 945, 12, 18},
  {cont__85_10, &frame__85_6, 945, 945, 9, 48},
  {cont__85_17, &frame__85_6, 946, 946, 9, 13},
  {entry__85_4, NULL, 943, 943, 10, 19},
  {cont__85_5, &frame__85_4, 943, 946, 7, 13},
  {entry__85_3, NULL, 942, 946, 5, 14},
  {cont__85_18, &frame__85_3, 946, 946, 14, 14},
  {entry__85_21, NULL, 949, 949, 27, 30},
  {cont__85_22, &frame__85_21, 949, 949, 19, 31},
  {cont__85_24, &frame__85_21, 949, 949, 7, 31},
  {cont__85_25, &frame__85_21, 949, 949, 31, 31},
  {entry__85_28, NULL, 951, 951, 33, 36},
  {cont__85_29, &frame__85_28, 951, 951, 33, 38},
  {cont__85_30, &frame__85_28, 951, 951, 33, 39},
  {cont__85_31, &frame__85_28, 951, 951, 18, 39},
  {cont__85_32, &frame__85_28, 951, 951, 39, 39},
  {entry__85_26, NULL, 951, 951, 10, 15},
  {cont__85_27, &frame__85_26, 951, 951, 7, 39},
  {entry__85_1_format_number, NULL, 939, 939, 3, 16},
  {cont__85_2, &frame__85_1_format_number, 941, 946, 3, 15},
  {cont__85_19, &frame__85_1_format_number, 948, 948, 5, 10},
  {cont__85_20, &frame__85_1_format_number, 947, 951, 3, 40},
  {cont__85_33, &frame__85_1_format_number, 952, 952, 3, 8},
  {entry__86_4, NULL, 958, 958, 37, 37},
  {cont__86_5, &frame__86_4, 958, 958, 7, 37},
  {cont__86_6, &frame__86_4, 964, 964, 20, 41},
  {cont__86_7, &frame__86_4, 964, 964, 17, 41},
  {cont__86_8, &frame__86_4, 964, 964, 9, 42},
  {cont__86_9, &frame__86_4, 965, 965, 23, 29},
  {cont__86_10, &frame__86_4, 965, 965, 9, 34},
  {cont__86_11, &frame__86_4, 959, 966, 7, 12},
  {entry__86_13, NULL, 968, 968, 47, 53},
  {cont__86_14, &frame__86_13, 968, 968, 33, 58},
  {cont__86_15, &frame__86_13, 968, 968, 7, 63},
  {entry__86_1_sim2c__write_timing_info, NULL, 955, 955, 3, 23},
  {cont__86_2, &frame__86_1_sim2c__write_timing_info, 957, 957, 5, 23},
  {cont__86_3, &frame__86_1_sim2c__write_timing_info, 956, 968, 3, 64},
  {cont__86_17, &frame__86_1_sim2c__write_timing_info, 969, 969, 3, 19},
  {cont__86_18, &frame__86_1_sim2c__write_timing_info, 969, 969, 19, 19},
  {entry__87_4, NULL, 985, 985, 12, 38},
  {cont__87_6, &frame__87_4, 985, 985, 9, 38},
  {entry__87_7, NULL, 986, 986, 9, 23},
  {entry__87_9, NULL, 988, 988, 17, 57},
  {entry__87_19, NULL, 999, 999, 42, 69},
  {cont__87_20, &frame__87_19, 999, 999, 9, 38},
  {cont__87_21, &frame__87_19, 999, 999, 9, 69},
  {cont__87_22, &frame__87_19, 999, 999, 9, 69},
  {entry__87_17, NULL, 998, 998, 9, 27},
  {cont__87_18, &frame__87_17, 999, 999, 9, 69},
  {cont__87_23, &frame__87_17, },
  {entry__87_28, NULL, 1002, 1002, 21, 61},
  {entry__87_31, NULL, 1003, 1003, 41, 59},
  {cont__87_32, &frame__87_31, 1003, 1003, 35, 64},
  {entry__87_34, NULL, 1004, 1004, 32, 54},
  {entry__87_38, NULL, 1006, 1006, 28, 64},
  {entry__87_42, NULL, 1008, 1008, 28, 67},
  {entry__87_25, NULL, 1001, 1001, 55, 67},
  {cont__87_26, &frame__87_25, 1001, 1001, 9, 67},
  {cont__87_27, &frame__87_25, 1002, 1002, 9, 61},
  {cont__87_30, &frame__87_25, 1003, 1003, 9, 64},
  {cont__87_33, &frame__87_25, 1004, 1004, 9, 54},
  {cont__87_35, &frame__87_25, 1005, 1005, 25, 37},
  {cont__87_36, &frame__87_25, 1005, 1005, 9, 37},
  {cont__87_37, &frame__87_25, 1006, 1006, 9, 64},
  {cont__87_40, &frame__87_25, 1007, 1007, 9, 39},
  {cont__87_41, &frame__87_25, 1008, 1008, 9, 67},
  {cont__87_44, &frame__87_25, 1008, 1008, 67, 67},
  {entry__87_49, NULL, 1015, 1015, 44, 71},
  {cont__87_50, &frame__87_49, 1015, 1015, 13, 40},
  {cont__87_51, &frame__87_49, 1015, 1015, 13, 71},
  {cont__87_52, &frame__87_49, 1015, 1015, 13, 71},
  {entry__87_54, NULL, 1017, 1017, 13, 43},
  {entry__87_55, NULL, 1019, 1019, 13, 64},
  {cont__87_56, &frame__87_55, 1019, 1019, 64, 64},
  {entry__87_45, NULL, 1010, 1010, 9, 30},
  {cont__87_46, &frame__87_45, 1011, 1011, 9, 32},
  {cont__87_47, &frame__87_45, 1014, 1014, 13, 31},
  {cont__87_48, &frame__87_45, 1013, 1015, 11, 70},
  {cont__87_53, &frame__87_45, 1012, 1019, 9, 65},
  {entry__87_64, NULL, 1024, 1024, 11, 39},
  {entry__87_59, NULL, 1023, 1023, 9, 62},
  {cont__87_63, &frame__87_59, 1022, 1024, 7, 40},
  {entry__87_71, NULL, 1032, 1032, 38, 63},
  {cont__87_72, &frame__87_71, 1032, 1032, 13, 63},
  {cont__87_73, &frame__87_71, 1032, 1032, 13, 63},
  {entry__87_69, NULL, 1031, 1031, 13, 45},
  {cont__87_70, &frame__87_69, 1030, 1032, 11, 62},
  {cont__87_74, &frame__87_69, 1030, 1032, 11, 62},
  {entry__87_76, NULL, 1034, 1034, 23, 23},
  {entry__87_66, NULL, 1026, 1026, 7, 30},
  {cont__87_67, &frame__87_66, 1029, 1029, 11, 27},
  {cont__87_68, &frame__87_66, 1028, 1032, 9, 63},
  {cont__87_75, &frame__87_66, 1027, 1034, 7, 24},
  {entry__87_80, NULL, 1037, 1037, 28, 75},
  {cont__87_82, &frame__87_80, 1037, 1037, 75, 75},
  {entry__87_85, NULL, 1040, 1040, 23, 58},
  {entry__87_92, NULL, 1048, 1048, 33, 45},
  {cont__87_93, &frame__87_92, 1048, 1048, 27, 45},
  {entry__87_84, NULL, 1040, 1040, 11, 58},
  {cont__87_87, &frame__87_84, 1041, 1047, 11, 24},
  {cont__87_91, &frame__87_84, 1048, 1048, 11, 45},
  {entry__87_95, NULL, 1050, 1050, 23, 51},
  {entry__87_99, NULL, 1055, 1055, 18, 40},
  {cont__87_101, &frame__87_99, 1055, 1055, 15, 40},
  {entry__87_102, NULL, 1056, 1056, 18, 33},
  {cont__87_103, &frame__87_102, 1056, 1056, 15, 33},
  {entry__87_106, NULL, 1059, 1059, 33, 45},
  {cont__87_107, &frame__87_106, 1059, 1059, 27, 45},
  {entry__87_94, NULL, 1050, 1050, 11, 51},
  {cont__87_97, &frame__87_94, 1054, 1054, 15, 41},
  {cont__87_98, &frame__87_94, 1053, 1056, 13, 32},
  {cont__87_104, &frame__87_94, 1051, 1058, 11, 24},
  {cont__87_105, &frame__87_94, 1059, 1059, 11, 45},
  {entry__87_78, NULL, 1036, 1036, 7, 52},
  {cont__87_79, &frame__87_78, 1037, 1037, 7, 75},
  {cont__87_83, &frame__87_78, 1038, 1059, 7, 46},
  {entry__87_111, NULL, 1061, 1061, 24, 41},
  {cont__87_112, &frame__87_111, 1061, 1061, 24, 41},
  {entry__87_116, NULL, 1065, 1065, 11, 25},
  {entry__87_117, NULL, 1066, 1066, 14, 38},
  {cont__87_118, &frame__87_117, 1066, 1066, 11, 38},
  {entry__87_114, NULL, 1064, 1064, 11, 39},
  {cont__87_115, &frame__87_114, 1063, 1066, 9, 37},
  {cont__87_119, &frame__87_114, 1062, 1069, 7, 44},
  {entry__87_2, NULL, 984, 984, 9, 36},
  {cont__87_3, &frame__87_2, 982, 986, 5, 24},
  {cont__87_8, &frame__87_2, 988, 988, 5, 57},
  {cont__87_11, &frame__87_2, 989, 989, 5, 41},
  {cont__87_12, &frame__87_2, 990, 990, 5, 41},
  {cont__87_13, &frame__87_2, 991, 991, 5, 33},
  {cont__87_14, &frame__87_2, 992, 992, 5, 28},
  {cont__87_15, &frame__87_2, 994, 994, 5, 24},
  {cont__87_16, &frame__87_2, },
  {cont__87_24, &frame__87_2, 995, 1019, 5, 67},
  {cont__87_57, &frame__87_2, 1020, 1020, 5, 50},
  {cont__87_58, &frame__87_2, 1021, 1024, 5, 41},
  {cont__87_65, &frame__87_2, 1025, 1034, 5, 25},
  {cont__87_77, &frame__87_2, 1035, 1059, 5, 47},
  {cont__87_108, &frame__87_2, 1060, 1060, 41, 41},
  {cont__87_109, &frame__87_2, 1060, 1060, 5, 42},
  {cont__87_110, &frame__87_2, 1061, 1061, 8, 41},
  {cont__87_113, &frame__87_2, 1061, 1069, 5, 45},
  {entry__87_1_build_executable, NULL, 981, 1069, 3, 46},
  {entry__102_2, NULL, 106, 106, 8, 28},
  {cont__102_3, &frame__102_2, 106, 106, 5, 28},
  {entry__102_4, NULL, 109, 109, 9, 48},
  {cont__102_6, &frame__102_4, 110, 110, 9, 42},
  {cont__102_8, &frame__102_4, 108, 110, 7, 41},
  {cont__102_9, &frame__102_4, 107, 110, 5, 43},
  {entry__103_2, NULL, 115, 115, 8, 29},
  {cont__103_3, &frame__103_2, 115, 115, 5, 29},
  {entry__103_4, NULL, 118, 118, 9, 48},
  {cont__103_5, &frame__103_4, 119, 119, 9, 42},
  {cont__103_6, &frame__103_4, 117, 119, 7, 41},
  {cont__103_7, &frame__103_4, 116, 119, 5, 43},
  {entry__107_3, NULL, 139, 139, 7, 41},
  {cont__107_4, &frame__107_3, 140, 140, 10, 26},
  {cont__107_5, &frame__107_3, 140, 140, 7, 32},
  {cont__107_6, &frame__107_3, 141, 141, 7, 19},
  {cont__107_7, &frame__107_3, 142, 142, 7, 34},
  {cont__107_8, &frame__107_3, 143, 143, 10, 21},
  {cont__107_9, &frame__107_3, 143, 143, 7, 27},
  {cont__107_10, &frame__107_3, 144, 144, 20, 20},
  {entry__107_2, NULL, 138, 144, 5, 20},
  {cont__107_11, &frame__107_2, 144, 144, 20, 20},
  {entry__107_1, NULL, 137, 144, 3, 21},
  {entry__133_4, NULL, 172, 172, 41, 79},
  {entry__133_2, NULL, 172, 172, 8, 38},
  {cont__133_3, &frame__133_2, 172, 172, 5, 79},
  {cont__133_6, &frame__133_2, 173, 173, 5, 45},
  {cont__133_7, &frame__133_2, 173, 173, 45, 45},
  {entry__133_9, NULL, 179, 180, 7, 52},
  {entry__133_12, NULL, 182, 183, 7, 34},
  {entry__133_15, NULL, 185, 186, 7, 57},
  {entry__133_18, NULL, 188, 189, 7, 71},
  {entry__133_21, NULL, 191, 192, 7, 47},
  {entry__133_24, NULL, 194, 195, 7, 61},
  {entry__133_27, NULL, 197, 200, 9, 29},
  {entry__133_30, NULL, 204, 205, 7, 33},
  {entry__133_33, NULL, 207, 208, 7, 29},
  {entry__133_36, NULL, 210, 211, 7, 35},
  {entry__133_39, NULL, 213, 214, 7, 40},
  {entry__133_42, NULL, 216, 217, 9, 65},
  {entry__133_45, NULL, 221, 222, 7, 35},
  {entry__133_48, NULL, 224, 225, 7, 45},
  {entry__133_51, NULL, 227, 228, 9, 31},
  {entry__133_54, NULL, 232, 233, 9, 65},
  {entry__133_57, NULL, 237, 238, 7, 32},
  {entry__133_60, NULL, 240, 241, 7, 33},
  {entry__133_63, NULL, 243, 244, 7, 43},
  {entry__133_66, NULL, 246, 247, 7, 29},
  {entry__133_69, NULL, 249, 250, 7, 46},
  {entry__133_8, NULL, 175, 250, 5, 47},
  {cont__133_72, &frame__133_8, 250, 250, 48, 48},
  {entry__137_1, NULL, 254, 254, 37, 37},
  {entry__163_2, NULL, 625, 626, 9, 51},
  {cont__163_5, &frame__163_2, 625, 626, 3, 51},
  {entry__178_1, NULL, 1071, 1071, 20, 36},
  {cont__178_2, &frame__178_1, 1071, 1071, 36, 36},
  {entry__179_4, NULL, 1078, 1078, 7, 32},
  {entry__179_3, NULL, },
  {cont__179_5, &frame__179_3, },
  {entry__179_2, NULL, },
  {cont__179_6, &frame__179_2, },
  {entry__179_1, NULL, },
  {cont__179_7, &frame__179_1, 1073, 1079, 3, 24},
  {entry__179_8, NULL, 1080, 1080, 3, 23},
  {entry__179_9, NULL, 1081, 1081, 3, 43},
  {entry__179_10, NULL, 1082, 1082, 3, 57},
  {entry__179_11, NULL, 1083, 1083, 6, 29},
  {cont__179_12, &frame__179_11, 1083, 1083, 3, 43}
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
  arguments->slots[0] = string__91_1;
  result_count = 0;
  myself = get__copyright();
  func = myself->type;
  frame->cont = cont__91_2;
}
static void cont__91_2(void) {
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
  frame->cont = cont__92_1;
}
static void cont__92_1(void) {
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
  frame->cont = cont__93_1;
}
static void cont__93_1(void) {
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
  frame->cont = cont__94_1;
}
static void cont__94_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._REVISION, arguments->slots[0]);
  // 96: $VERSION "@(MAJOR).@(MINOR).@(REVISION).@(BUILD)"
  argument_count = 7;
  arguments = node_p;
  arguments->slots[0] = var._MAJOR;
  arguments->slots[1] = string__96_1;
  arguments->slots[2] = var._MINOR;
  arguments->slots[3] = string__96_1;
  arguments->slots[4] = var._REVISION;
  arguments->slots[5] = string__96_1;
  arguments->slots[6] = var._BUILD;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__96_2;
}
static void cont__96_2(void) {
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
  frame->cont = cont__97_1;
}
static void cont__97_1(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 98: extern $gcc "gcc"
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
  initialize_future(var._gcc, arguments->slots[0]);
  // 99: extern $mkdir "mkdir" # would be nice to have one in the system library!
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
  initialize_future(var._mkdir, arguments->slots[0]);
  // 100: $SIMLIBPATH environment("SIMLIBPATH")
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
  initialize_future(var._SIMLIBPATH, arguments->slots[0]);
  // 101: $SIMDATAPATH environment("SIMDATAPATH")
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
  initialize_future(var._SIMDATAPATH, arguments->slots[0]);
  // 105: SIMLIBPATH.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._SIMLIBPATH;
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
  arguments->slots[1] = func__102_2;
  arguments->slots[2] = func__102_4;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__102_10;
}
static void entry__102_2(void) {
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
  frame->cont = cont__102_3;
}
static void cont__102_3(void) {
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
static void entry__102_4(void) {
  allocate_initialized_frame_gc(0, 3);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 109: "/usr/local/share/simplicity-@(VERSION)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__102_5;
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
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 110: "/usr/share/simplicity-@(VERSION)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__102_7;
  arguments->slots[1] = var._VERSION;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__102_8;
}
static void cont__102_8(void) {
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
  frame->cont = cont__102_9;
}
static void cont__102_9(void) {
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
static void cont__102_10(void) {
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
  frame->cont = cont__103_1;
}
static void cont__103_1(void) {
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
  arguments->slots[1] = func__103_2;
  arguments->slots[2] = func__103_4;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__103_8;
}
static void entry__103_2(void) {
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
  frame->cont = cont__103_3;
}
static void cont__103_3(void) {
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
static void entry__103_4(void) {
  allocate_initialized_frame_gc(0, 3);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 118: "/usr/local/share/simplicity-@(VERSION)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__102_5;
  arguments->slots[1] = var._VERSION;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__103_5;
}
static void cont__103_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 119: "/usr/share/simplicity-@(VERSION)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__102_7;
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
  frame->cont = cont__103_7;
}
static void cont__103_7(void) {
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
static void cont__103_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._simdatapaths, arguments->slots[0]);
  // 125: "bsd" = "posix"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__105_1;
  arguments->slots[1] = string__105_2;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__105_3;
}
static void cont__105_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 126: "cygwin" = "posix"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__82_35;
  arguments->slots[1] = string__105_2;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__105_4;
}
static void cont__105_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 127: "darwin" = "posix"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__82_36;
  arguments->slots[1] = string__105_2;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__105_5;
}
static void cont__105_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 128: "linux" = "posix"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__75_22;
  arguments->slots[1] = string__105_2;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__105_6;
}
static void cont__105_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 129: "posix" = "all"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__105_2;
  arguments->slots[1] = string__105_7;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__105_8;
}
static void cont__105_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 130: "win" = "all"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__105_9;
  arguments->slots[1] = string__105_7;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__105_10;
}
static void cont__105_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 131: "all" = NONE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__105_7;
  arguments->slots[1] = var._NONE;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__105_11;
}
static void cont__105_11(void) {
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
  frame->cont = cont__105_12;
}
static void cont__105_12(void) {
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
  arguments->slots[0] = func__107_1;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__107_12;
}
static void entry__107_2(void) {
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
  frame->slots[3] /* temp__1 */ = create_closure(entry__107_3, 0);
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
  frame->cont = cont__107_11;
}
static void entry__107_3(void) {
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
  frame->cont = cont__107_4;
}
static void cont__107_4(void) {
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
  frame->cont = cont__107_5;
}
static void cont__107_5(void) {
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
  frame->cont = cont__107_6;
}
static void cont__107_6(void) {
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
  frame->cont = cont__107_7;
}
static void cont__107_7(void) {
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
  frame->cont = cont__107_8;
}
static void cont__107_8(void) {
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
  frame->cont = cont__107_9;
}
static void cont__107_9(void) {
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
  frame->cont = cont__107_10;
}
static void cont__107_10(void) {
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
static void cont__107_11(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__107_1(void) {
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
  frame->slots[2] /* temp__1 */ = create_closure(entry__107_2, 0);
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
static void cont__107_12(void) {
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
  // 166: $$sim2c::do_use_goto false
  var.sim2c__do_use_goto = get__false();
  // 167: $$module_prefix undefined
  var._module_prefix = get__undefined();
  // 168: $$input_filename undefined
  var._input_filename = get__undefined();
  // 169: ... 1
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
  // 169: $action truncate_until(program_name '/' -1)
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
  // 171: action == "simrun"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._action;
  arguments->slots[1] = string__82_2;
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
  // 170: if
  // 171:   action == "simrun":
  // 172:     if command_line_arguments.is_empty: Error "Missing command line arguments!"
  // 173:     !input_filename command_line_arguments(1)
  // 174:   :
  // 175:     program_parameters
  // 176:       # the following options act on a single file only
  // 177:       
  // 178:       !sim2c::do_check_only
  // 179:       -> "check-only" "
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__133_2;
  arguments->slots[2] = func__133_8;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__133_73;
}
static void entry__133_2(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 172: ... command_line_arguments.is_empty
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
  // 172: if command_line_arguments.is_empty: Error "Missing command line arguments!"
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
  // 172: ... Error "Missing command line arguments!"
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
  // 173: !input_filename command_line_arguments(1)
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
  // 175: program_parameters
  // 176:   # the following options act on a single file only
  // 177:   
  // 178:   !sim2c::do_check_only
  // 179:   -> "check-only" "
  // 180:     do not compile; just check for syntax errors
  // 181:   !sim2c::do_dump_trees
  // 182:   -> "dump-trees" "
  // 183:     dump abstract syntax trees
  // 184:   !sim2c::do_pretty_print
  // ...
  argument_count = 21;
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
  arguments->slots[20] = func__133_69;
  result_count = 21;
  myself = get__program_parameters();
  func = myself->type;
  frame->cont = cont__133_72;
}
static void entry__133_9(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 179: -> "check-only" "
  // 180:   do not compile; just check for syntax errors
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
  // 182: -> "dump-trees" "
  // 183:   dump abstract syntax trees
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
  // 185: -> "pretty-print" "
  // 186:   do not compile; just pretty print the source file
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
  // 188: -> "print-simplified-source" "
  // 189:   do not generate a C-file; just print the simplified source text
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
  // 191: -> "print-c" "
  // 192:   print C source code for a single module
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
  // 194: -> "time-passes" "
  // 195:   print running time for the individual compiler passes
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
  // 197: -> VALUED_OPTION "module-prefix" "
  // 198:   needed to compile a single file within a subdirectory;
  // 199:   if the subdirectories are nested use slashes to separate
  // 200:   the directory names
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
  // 204: -> "brief" "
  // 205:   show brief error messages
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
  // 207: -> "warnings" "
  // 208:   show warning messages
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
  // 210: -> "verbose" "
  // 211:   output verbose informations
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
  // 213: -> "debug" "
  // 214:   show C-compiler and linker calls
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
  // 216: -> "debug_compiler" "
  // 217:   show internal debug messages of the Simplicity compiler
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
  // 221: -> "codeblocks" "
  // 222:   create Code::Blocks project
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
  // 224: -> "extract-documentation" "
  // 225:   extract documentation encoded as HTML
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
  // 227: -> "list-dependencies" "
  // 228:   list all dependencies
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
  // 232: -> "goto" "
  // 233:   the compiler uses goto-statements to link continuations
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
  // 237: -> "rebuild" "
  // 238:   rebuild all source files
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
  // 240: -> "omit-meta" "
  // 241:   do not rebuild meta files
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
  // 243: -> "static" "
  // 244:   create statically linked executable
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
  // 246: -> "profile" "
  // 247:   link with libprofiler
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__133_67;
  arguments->slots[1] = string__133_68;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__133_69(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 249: -> std::MANDATORY_PARAMETER "filename" "
  // 250:   the name of the source file to compile
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__std__MANDATORY_PARAMETER();
  arguments->slots[1] = string__133_70;
  arguments->slots[2] = string__133_71;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__133_72(void) {
  if (argument_count != 21) {
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
  set__do_use_goto(arguments->slots[15]);
  var._do_rebuild = arguments->slots[16];
  var._do_omit_meta = arguments->slots[17];
  var._do_build_static = arguments->slots[18];
  var._do_link_profiler = arguments->slots[19];
  var._input_filename = arguments->slots[20];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__133_73(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 251: %main_filename fullname(input_filename)
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
  // 252: %main_info stat(main_filename)
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
  // 253: %do_build_static_executable do_build_static
  initialize_future(get__do_build_static_executable(), var._do_build_static);
  // 254: if do_show_debug_infos: !verbose true
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
  // 254: ... !verbose true
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
  // 262: %mode undefined # EXE or LIB
  initialize_maybe_future(get__mode(), get__undefined());
  // 263: $WHITESPACE many(' ')
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
  // 265: $gcc_basic_options
  // 266:   list
  // 267:     "-Wall"
  // 268:     "-Wno-unused-function"
  // 269:     "-Wno-unused-variable"
  // 270:     "-Wno-parentheses"
  // 271:     "-Wno-switch"
  // 272:     "-Wno-maybe-uninitialized"
  // 273:     "-Wno-trigraphs"
  // 274:     "-O1"
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
  // 281: ... list("-msse2" "-mfpmath=sse")
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
  // 281: "x86_32" = list("-msse2" "-mfpmath=sse")
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
  // 282: ... list("-msse2" "-mfpmath=sse")
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
  // 282: "x86_64" = list("-msse2" "-mfpmath=sse")
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
  // 279: $gcc_hardware_specific_options
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
  frame->cont = cont__144_9;
}
static void cont__144_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._gcc_hardware_specific_options, arguments->slots[0]);
  // 288: ... hardware_architecture()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__hardware_architecture();
  func = myself->type;
  frame->cont = cont__145_1;
}
static void cont__145_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 288: gcc_hardware_specific_options(hardware_architecture())
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = var._gcc_hardware_specific_options;
  func = myself->type;
  frame->cont = cont__145_2;
}
static void cont__145_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 287: default_value
  // 288:   gcc_hardware_specific_options(hardware_architecture())
  // 289:   empty_list
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  arguments->slots[1] = get__empty_list();
  result_count = 1;
  myself = get__default_value();
  func = myself->type;
  frame->cont = cont__145_3;
}
static void cont__145_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 284: $gcc_options
  // 285:   append
  // 286:     gcc_basic_options
  // 287:     default_value
  // 288:       gcc_hardware_specific_options(hardware_architecture())
  // 289:       empty_list
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._gcc_basic_options;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__145_4;
}
static void cont__145_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._gcc_options, arguments->slots[0]);
  // 291: %on_top_level true # set to false while building meta-files
  initialize_maybe_future(get__on_top_level(), get__true());
  // 292: %%objects empty_insert_order_set
  set__objects(get__empty_insert_order_set());
  // 293: %%libraries empty_insert_order_set # contains "-lsim-..."-entries
  set__libraries(get__empty_insert_order_set());
  // 294: %%do_link false
  set__do_link(get__false());
  // 295: %%last_modification_time undefined
  set__last_modification_time(get__undefined());
  // 296: $$c_sources empty_insert_order_set
  var._c_sources = get__empty_insert_order_set();
  // 297: $$dependencies empty_list
  var._dependencies = get__empty_list();
  // 298: $$resolved_libraries undefined
  var._resolved_libraries = get__undefined();
  // 624: ... main_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_info();
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__163_1;
}
static void cont__163_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 624: if main_info.is_undefined:
  // 625:   Error "
  // 626:     Source file "@(main_filename)" does not exist!@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__163_2;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__163_6;
}
static void entry__163_2(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 625: ... "
  // 626:   Source file "@(main_filename)" does not exist!@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__163_3;
  arguments->slots[1] = get__main_filename();
  arguments->slots[2] = string__163_4;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__163_5;
}
static void cont__163_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 625: Error "
  // 626:   Source file "@(main_filename)" does not exist!@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__163_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 931: $$t undefined
  var._t = get__undefined();
  // 1071: if do_time_passes: !t current_time()
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = func__178_1;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__178_3;
}
static void entry__178_1(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1071: ... !t current_time()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__current_time();
  func = myself->type;
  frame->cont = cont__178_2;
}
static void cont__178_2(void) {
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
static void cont__178_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1072: cond
  // 1073:   ->
  // 1074:     ||
  // 1075:       do_check_only
  // 1076:       do_dump_trees
  // 1077:       do_pretty_print
  // 1078:       do_print_simplified_source
  // 1079:     dump_source_or_check
  // 1080:   -> do_print_c print_c
  // 1081:   -> do_list_dependencies list_dependencies
  // ...
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = func__179_1;
  arguments->slots[1] = func__179_8;
  arguments->slots[2] = func__179_9;
  arguments->slots[3] = func__179_10;
  arguments->slots[4] = func__179_11;
  arguments->slots[5] = var._build_executable;
  result_count = 0;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__179_13;
}
static void entry__179_1(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_check_only();
  arguments->slots[1] = func__179_2;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__179_7;
}
static void entry__179_2(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_dump_trees();
  arguments->slots[1] = func__179_3;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__179_6;
}
static void entry__179_3(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_pretty_print();
  arguments->slots[1] = func__179_4;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__179_5;
}
static void entry__179_4(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1078: do_print_simplified_source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__do_print_simplified_source();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__179_5(void) {
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
static void cont__179_6(void) {
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
static void cont__179_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1073: ->
  // 1074:   ||
  // 1075:     do_check_only
  // 1076:     do_dump_trees
  // 1077:     do_pretty_print
  // 1078:     do_print_simplified_source
  // 1079:   dump_source_or_check
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = var._dump_source_or_check;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__179_8(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1080: -> do_print_c print_c
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_print_c;
  arguments->slots[1] = var._print_c;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__179_9(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1081: -> do_list_dependencies list_dependencies
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_list_dependencies;
  arguments->slots[1] = var._list_dependencies;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__179_10(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1082: -> do_build_codeblocks_project build_codeblocks_project
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_build_codeblocks_project;
  arguments->slots[1] = var._build_codeblocks_project;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__179_11(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1083: ... main_info.is_a_directory
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_info();
  result_count = 1;
  myself = get__is_a_directory();
  func = myself->type;
  frame->cont = cont__179_12;
}
static void cont__179_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1083: -> main_info.is_a_directory build_library
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = var._build_library;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__179_13(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = get__std__terminate();
  func = myself->type;
  frame->cont = cont__180_1;
}
static void cont__180_1(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  terminate(0); // should never be reached
}
static void entry__48_2(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // args: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* args */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 257: ... ewriteln args*
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__48_1_sim2c__show_compiler_debug_info(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // args: 0
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 257: ... : ewriteln args*
  frame->slots[1] /* temp__1 */ = create_closure(entry__48_2, 0);
  // 257: if do_show_compiler_debug_infos: ewriteln args*
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_show_compiler_debug_infos();
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__64_1_resolve_filename(void) {
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
  // 301: ... resolved_libraries.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._resolved_libraries;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__64_2;
}
static void cont__64_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 301: if resolved_libraries.is_undefined:
  // 302:   !resolved_libraries empty_table
  // 303:   for_each simlibpaths: (path)
  // 304:     if file_exists(path):
  // 305:       for_each directory(path): (entry)
  // 306:         if entry.is_a_directory:
  // 307:           $name std::filename_of(entry)
  // 308:           if name .matches. NAME: !resolved_libraries(name) fullname_of(entry)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = func__64_3;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__64_16;
}
static void entry__64_13(void) {
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
  // 308: ... !resolved_libraries(name) fullname_of(entry)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* entry */;
  result_count = 1;
  myself = get__fullname_of();
  func = myself->type;
  frame->cont = cont__64_14;
}
static void cont__64_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 308: ... !resolved_libraries(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = var._resolved_libraries;
  func = myself->type;
  frame->cont = cont__64_15;
}
static void cont__64_15(void) {
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
static void entry__64_10(void) {
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
  // 307: $name std::filename_of(entry)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* entry */;
  result_count = 1;
  myself = get__std__filename_of();
  func = myself->type;
  frame->cont = cont__64_11;
}
static void cont__64_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* name */, arguments->slots[0]);
  // 308: ... name .matches. NAME
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* name */;
  arguments->slots[1] = get__NAME();
  result_count = 1;
  myself = get__matches();
  func = myself->type;
  frame->cont = cont__64_12;
}
static void cont__64_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 308: ... : !resolved_libraries(name) fullname_of(entry)
  frame->slots[3] /* temp__2 */ = create_closure(entry__64_13, 0);
  // 308: if name .matches. NAME: !resolved_libraries(name) fullname_of(entry)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__64_8(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // entry: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 306: ... entry.is_a_directory
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* entry */;
  result_count = 1;
  myself = get__is_a_directory();
  func = myself->type;
  frame->cont = cont__64_9;
}
static void cont__64_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 306: ... :
  // 307:   $name std::filename_of(entry)
  // 308:   if name .matches. NAME: !resolved_libraries(name) fullname_of(entry)
  frame->slots[2] /* temp__2 */ = create_closure(entry__64_10, 0);
  // 306: if entry.is_a_directory:
  // 307:   $name std::filename_of(entry)
  // 308:   if name .matches. NAME: !resolved_libraries(name) fullname_of(entry)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__64_6(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // path: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* path */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 305: ... directory(path)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* path */;
  result_count = 1;
  myself = get__directory();
  func = myself->type;
  frame->cont = cont__64_7;
}
static void cont__64_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 305: for_each directory(path): (entry)
  // 306:   if entry.is_a_directory:
  // 307:     $name std::filename_of(entry)
  // 308:     if name .matches. NAME: !resolved_libraries(name) fullname_of(entry)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__64_8;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__64_4(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // path: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 304: ... file_exists(path)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* path */;
  result_count = 1;
  myself = get__file_exists();
  func = myself->type;
  frame->cont = cont__64_5;
}
static void cont__64_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 304: ... :
  // 305:   for_each directory(path): (entry)
  // 306:     if entry.is_a_directory:
  // 307:       $name std::filename_of(entry)
  // 308:       if name .matches. NAME: !resolved_libraries(name) fullname_of(entry)
  frame->slots[2] /* temp__2 */ = create_closure(entry__64_6, 0);
  // 304: if file_exists(path):
  // 305:   for_each directory(path): (entry)
  // 306:     if entry.is_a_directory:
  // 307:       $name std::filename_of(entry)
  // 308:       if name .matches. NAME: !resolved_libraries(name) fullname_of(entry)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__64_3(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 302: !resolved_libraries empty_table
  var._resolved_libraries = get__empty_table();
  // 303: for_each simlibpaths: (path)
  // 304:   if file_exists(path):
  // 305:     for_each directory(path): (entry)
  // 306:       if entry.is_a_directory:
  // 307:         $name std::filename_of(entry)
  // 308:         if name .matches. NAME: !resolved_libraries(name) fullname_of(entry)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._simlibpaths;
  arguments->slots[1] = func__64_4;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__64_16(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 309: $libname filename .before. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__64_17;
}
static void cont__64_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* libname */, arguments->slots[0]);
  // 310: $libpath resolved_libraries(libname)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* libname */;
  result_count = 1;
  myself = var._resolved_libraries;
  func = myself->type;
  frame->cont = cont__64_18;
}
static void cont__64_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* libpath */, arguments->slots[0]);
  // 311: ... libpath.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* libpath */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__64_19;
}
static void cont__64_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 311: ... :
  // 312:   Error "
  // 313:     Cannot resolve required library "@(libname)@quot;!@
  frame->slots[4] /* temp__2 */ = create_closure(entry__64_20, 0);
  // 311: if libpath.is_undefined:
  // 312:   Error "
  // 313:     Cannot resolve required library "@(libname)@quot;!@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__64_24;
}
static void entry__64_20(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // libname: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* libname */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 312: ... "
  // 313:   Cannot resolve required library "@(libname)@quot;!@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__64_21;
  arguments->slots[1] = frame->slots[0] /* libname */;
  arguments->slots[2] = string__64_22;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__64_23;
}
static void cont__64_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 312: Error "
  // 313:   Cannot resolve required library "@(libname)@quot;!@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__64_24(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 314: ... filename .from. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__from();
  func = myself->type;
  frame->cont = cont__64_25;
}
static void cont__64_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 314: ... string(libpath filename .from. '/')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* libpath */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__64_26;
}
static void cont__64_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 314: -> string(libpath filename .from. '/')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__65_1_add_module_infos(void) {
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
  // 325: ... --SORT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__SORT();
  arguments->slots[1] = get__std__true();
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__65_2;
}
static void cont__65_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 325: $entries directory(--SORT path)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[0] /* path */;
  result_count = 1;
  myself = get__directory();
  func = myself->type;
  frame->cont = cont__65_3;
}
static void cont__65_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* entries */, arguments->slots[0]);
  // 326: $$filenames empty_set
  ((CELL *)frame->slots[4])->contents /* filenames */ = get__empty_set();
  // 327: $$directories empty_list
  ((CELL *)frame->slots[5])->contents /* directories */ = get__empty_list();
  // 328: $$modules empty_key_order_set
  ((CELL *)frame->slots[6])->contents /* modules */ = get__empty_key_order_set();
  // 329: ... : (entry)
  // 330:   $name std::filename_of(entry)
  // 331:   cond
  // 332:     -> entry.is_a_directory: if name .matches. NAME: push &directories name
  // 333:     -> name .has_suffix. ".sim":
  // 334:       $submodule_name name .without_suffix. (some(".meta"), ".sim")
  // 335:       !filenames(submodule_name) true
  // 336:       $meta_level (length_of(name)-length_of(submodule_name)-4)/5
  // 337:       $stored_level meta_levels(submodule_name)
  // 338:       if stored_level.is_undefined || meta_level > stored_level:
  // ...
  frame->slots[7] /* temp__1 */ = create_closure(entry__65_4, 1);
  // 329: for_each entries: (entry)
  // 330:   $name std::filename_of(entry)
  // 331:   cond
  // 332:     -> entry.is_a_directory: if name .matches. NAME: push &directories name
  // 333:     -> name .has_suffix. ".sim":
  // 334:       $submodule_name name .without_suffix. (some(".meta"), ".sim")
  // 335:       !filenames(submodule_name) true
  // 336:       $meta_level (length_of(name)-length_of(submodule_name)-4)/5
  // 337:       $stored_level meta_levels(submodule_name)
  // 338:       if stored_level.is_undefined || meta_level > stored_level:
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* entries */;
  arguments->slots[1] = frame->slots[7] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__65_38;
}
static void entry__65_15(void) {
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
  // 334: ... some(".meta")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__65_16;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__65_17;
}
static void cont__65_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__2 */ = arguments->slots[0];
  // 334: ... some(".meta"), ".sim"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__2 */;
  arguments->slots[1] = string__65_13;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__65_18;
}
static void cont__65_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 334: $submodule_name name .without_suffix. (some(".meta"), ".sim")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = get__without_suffix();
  func = myself->type;
  frame->cont = cont__65_19;
}
static void cont__65_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* submodule_name */, arguments->slots[0]);
  // 335: !filenames(submodule_name) true
  frame->slots[9] /* temp__1 */ = get__true();
  // 335: !filenames(submodule_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* submodule_name */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* filenames */;
  func = myself->type;
  frame->cont = cont__65_20;
}
static void cont__65_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* filenames */ = arguments->slots[0];
  // 336: ... length_of(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__65_21;
}
static void cont__65_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__3 */ = arguments->slots[0];
  // 336: ... length_of(submodule_name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* submodule_name */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__65_22;
}
static void cont__65_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__4 */ = arguments->slots[0];
  // 336: ... length_of(name)-length_of(submodule_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__3 */;
  arguments->slots[1] = frame->slots[12] /* temp__4 */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__65_23;
}
static void cont__65_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__2 */ = arguments->slots[0];
  // 336: ... length_of(name)-length_of(submodule_name)-4
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__2 */;
  arguments->slots[1] = number__4;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__65_24;
}
static void cont__65_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 336: $meta_level (length_of(name)-length_of(submodule_name)-4)/5
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__std__over();
  func = myself->type;
  frame->cont = cont__65_25;
}
static void cont__65_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* meta_level */, arguments->slots[0]);
  // 337: $stored_level meta_levels(submodule_name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* submodule_name */;
  result_count = 1;
  myself = var._meta_levels;
  func = myself->type;
  frame->cont = cont__65_26;
}
static void cont__65_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* stored_level */, arguments->slots[0]);
  // 338: ... stored_level.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* stored_level */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__65_27;
}
static void cont__65_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__2 */ = arguments->slots[0];
  // 338: ... meta_level > stored_level
  frame->slots[11] /* temp__3 */ = create_closure(entry__65_28, 0);
  // 338: ... stored_level.is_undefined || meta_level > stored_level
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__2 */;
  arguments->slots[1] = frame->slots[11] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__65_30;
}
static void entry__65_28(void) {
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
  // 338: ... meta_level > stored_level
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stored_level */;
  arguments->slots[1] = frame->slots[1] /* meta_level */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__65_29;
}
static void cont__65_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 338: ... meta_level > stored_level
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__65_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 338: ... :
  // 339:   !meta_levels(submodule_name) meta_level
  frame->slots[12] /* temp__4 */ = create_closure(entry__65_31, 0);
  // 338: if stored_level.is_undefined || meta_level > stored_level:
  // 339:   !meta_levels(submodule_name) meta_level
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = frame->slots[12] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__65_33;
}
static void entry__65_31(void) {
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
  // 339: !meta_levels(submodule_name) meta_level
  frame->slots[2] /* temp__1 */ = frame->slots[1] /* meta_level */;
  // 339: !meta_levels(submodule_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* submodule_name */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = var._meta_levels;
  func = myself->type;
  frame->cont = cont__65_32;
}
static void cont__65_32(void) {
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
static void cont__65_33(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 340: $basename submodule_name .truncate_from. '-'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* submodule_name */;
  arguments->slots[1] = character__45;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__65_34;
}
static void cont__65_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[7] /* basename */, arguments->slots[0]);
  // 341: !modules(basename) true
  frame->slots[9] /* temp__1 */ = get__true();
  // 341: !modules(basename)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* basename */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[2])->contents /* modules */;
  func = myself->type;
  frame->cont = cont__65_35;
}
static void cont__65_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* modules */ = arguments->slots[0];
  // 342: $mod_name string(mod_path basename)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* mod_path */;
  arguments->slots[1] = frame->slots[7] /* basename */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__65_36;
}
static void cont__65_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[8] /* mod_name */, arguments->slots[0]);
  // 343: !module_info(mod_name) empty_key_order_table
  frame->slots[9] /* temp__1 */ = get__empty_key_order_table();
  // 343: !module_info(mod_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* mod_name */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = var._module_info;
  func = myself->type;
  frame->cont = cont__65_37;
}
static void cont__65_37(void) {
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
static void entry__65_10(void) {
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
  // 332: ... push &directories name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* directories */;
  arguments->slots[1] = frame->slots[1] /* name */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__65_11;
}
static void cont__65_11(void) {
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
static void entry__65_8(void) {
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
  // 332: ... name .matches. NAME
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = get__NAME();
  result_count = 1;
  myself = get__matches();
  func = myself->type;
  frame->cont = cont__65_9;
}
static void cont__65_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 332: ... : push &directories name
  frame->slots[3] /* temp__2 */ = create_closure(entry__65_10, 0);
  // 332: ... if name .matches. NAME: push &directories name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__65_6(void) {
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
  // 332: ... entry.is_a_directory
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* entry */;
  result_count = 1;
  myself = get__is_a_directory();
  func = myself->type;
  frame->cont = cont__65_7;
}
static void cont__65_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 332: ... : if name .matches. NAME: push &directories name
  frame->slots[4] /* temp__2 */ = create_closure(entry__65_8, 0);
  // 332: -> entry.is_a_directory: if name .matches. NAME: push &directories name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__65_12(void) {
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
  // 333: ... name .has_suffix. ".sim"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = string__65_13;
  result_count = 1;
  myself = get__has_suffix();
  func = myself->type;
  frame->cont = cont__65_14;
}
static void cont__65_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 333: ... :
  // 334:   $submodule_name name .without_suffix. (some(".meta"), ".sim")
  // 335:   !filenames(submodule_name) true
  // 336:   $meta_level (length_of(name)-length_of(submodule_name)-4)/5
  // 337:   $stored_level meta_levels(submodule_name)
  // 338:   if stored_level.is_undefined || meta_level > stored_level:
  // 339:     !meta_levels(submodule_name) meta_level
  // 340:   $basename submodule_name .truncate_from. '-'
  // 341:   !modules(basename) true
  // 342:   $mod_name string(mod_path basename)
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__65_15, 0);
  // 333: -> name .has_suffix. ".sim":
  // 334:   $submodule_name name .without_suffix. (some(".meta"), ".sim")
  // 335:   !filenames(submodule_name) true
  // 336:   $meta_level (length_of(name)-length_of(submodule_name)-4)/5
  // 337:   $stored_level meta_levels(submodule_name)
  // 338:   if stored_level.is_undefined || meta_level > stored_level:
  // 339:     !meta_levels(submodule_name) meta_level
  // 340:   $basename submodule_name .truncate_from. '-'
  // 341:   !modules(basename) true
  // 342:   $mod_name string(mod_path basename)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__65_4(void) {
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
  // 330: $name std::filename_of(entry)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* entry */;
  result_count = 1;
  myself = get__std__filename_of();
  func = myself->type;
  frame->cont = cont__65_5;
}
static void cont__65_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* name */, arguments->slots[0]);
  // 332: -> entry.is_a_directory: if name .matches. NAME: push &directories name
  frame->slots[6] /* temp__1 */ = create_closure(entry__65_6, 0);
  // 333: -> name .has_suffix. ".sim":
  // 334:   $submodule_name name .without_suffix. (some(".meta"), ".sim")
  // 335:   !filenames(submodule_name) true
  // 336:   $meta_level (length_of(name)-length_of(submodule_name)-4)/5
  // 337:   $stored_level meta_levels(submodule_name)
  // 338:   if stored_level.is_undefined || meta_level > stored_level:
  // 339:     !meta_levels(submodule_name) meta_level
  // 340:   $basename submodule_name .truncate_from. '-'
  // 341:   !modules(basename) true
  // 342:   $mod_name string(mod_path basename)
  // ...
  frame->slots[7] /* temp__2 */ = create_closure(entry__65_12, 0);
  // 331: cond
  // 332:   -> entry.is_a_directory: if name .matches. NAME: push &directories name
  // 333:   -> name .has_suffix. ".sim":
  // 334:     $submodule_name name .without_suffix. (some(".meta"), ".sim")
  // 335:     !filenames(submodule_name) true
  // 336:     $meta_level (length_of(name)-length_of(submodule_name)-4)/5
  // 337:     $stored_level meta_levels(submodule_name)
  // 338:     if stored_level.is_undefined || meta_level > stored_level:
  // 339:       !meta_levels(submodule_name) meta_level
  // 340:     $basename submodule_name .truncate_from. '-'
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
static void cont__65_38(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 344: ... : (filename)
  // 345:   if filename .contains. '-':
  // 346:     unless filename .has_suffix. "-common":
  // 347:       $maybe_push_common: (plat)
  // 348:         $common_name string(name "-" plat "-common")
  // 349:         if filenames(common_name): push &files common_name
  // 350:       
  // 351:       $name filename .before. '-'
  // 352:       $mod_name string(mod_path name .truncate_from. '-')
  // 353:       $platform filename .behind. '-'
  // ...
  frame->slots[7] /* temp__1 */ = create_closure(entry__65_39, 1);
  // 344: for_each filenames: (filename)
  // 345:   if filename .contains. '-':
  // 346:     unless filename .has_suffix. "-common":
  // 347:       $maybe_push_common: (plat)
  // 348:         $common_name string(name "-" plat "-common")
  // 349:         if filenames(common_name): push &files common_name
  // 350:       
  // 351:       $name filename .before. '-'
  // 352:       $mod_name string(mod_path name .truncate_from. '-')
  // 353:       $platform filename .behind. '-'
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* filenames */;
  arguments->slots[1] = frame->slots[7] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__65_74;
}
static void entry__65_44(void) {
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
  // 347: ... : (plat)
  // 348:   $common_name string(name "-" plat "-common")
  // 349:   if filenames(common_name): push &files common_name
  frame->slots[9] /* temp__1 */ = create_closure(entry__65_45_maybe_push_common, 1);
  // 347: $maybe_push_common: (plat)
  // 348:   $common_name string(name "-" plat "-common")
  // 349:   if filenames(common_name): push &files common_name
  initialize_future(frame->slots[3] /* maybe_push_common */, frame->slots[9] /* temp__1 */);
  // 351: $name filename .before. '-'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* filename */;
  arguments->slots[1] = character__45;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__65_51;
}
static void entry__65_49(void) {
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
  // 349: ... push &files common_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* files */;
  arguments->slots[1] = frame->slots[1] /* common_name */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__65_50;
}
static void cont__65_50(void) {
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
static void entry__65_45_maybe_push_common(void) {
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
  // 348: $common_name string(name "-" plat "-common")
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* name */;
  arguments->slots[1] = string__65_46;
  arguments->slots[2] = frame->slots[0] /* plat */;
  arguments->slots[3] = string__65_42;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__65_47;
}
static void cont__65_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* common_name */, arguments->slots[0]);
  // 349: ... filenames(common_name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* common_name */;
  result_count = 1;
  myself = ((CELL *)frame->slots[2])->contents /* filenames */;
  func = myself->type;
  frame->cont = cont__65_48;
}
static void cont__65_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 349: ... : push &files common_name
  frame->slots[6] /* temp__2 */ = create_closure(entry__65_49, 0);
  // 349: if filenames(common_name): push &files common_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__65_51(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* name */, arguments->slots[0]);
  // 352: ... name .truncate_from. '-'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* name */;
  arguments->slots[1] = character__45;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__65_52;
}
static void cont__65_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 352: $mod_name string(mod_path name .truncate_from. '-')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* mod_path */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__65_53;
}
static void cont__65_53(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* mod_name */, arguments->slots[0]);
  // 353: $platform filename .behind. '-'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* filename */;
  arguments->slots[1] = character__45;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__65_54;
}
static void cont__65_54(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* platform */, arguments->slots[0]);
  // 354: $$parent supported_platforms(platform)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* platform */;
  result_count = 1;
  myself = var._supported_platforms;
  func = myself->type;
  frame->cont = cont__65_55;
}
static void cont__65_55(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[7])->contents /* parent */ = arguments->slots[0];
  // 355: ... parent.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[7])->contents /* parent */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__65_56;
}
static void cont__65_56(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 355: ... :
  // 356:   Error "
  // 357:     The platform "@(platform)" is not supported!@
  frame->slots[10] /* temp__2 */ = create_closure(entry__65_57, 0);
  // 355: unless parent.is_defined:
  // 356:   Error "
  // 357:     The platform "@(platform)" is not supported!@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__65_61;
}
static void entry__65_57(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // platform: 0
  frame->slots[0] = myself->closure.frame->slots[6]; /* platform */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 356: ... "
  // 357:   The platform "@(platform)" is not supported!@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__65_58;
  arguments->slots[1] = frame->slots[0] /* platform */;
  arguments->slots[2] = string__65_59;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__65_60;
}
static void cont__65_60(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 356: Error "
  // 357:   The platform "@(platform)" is not supported!@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__65_61(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 358: $$files list(filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* filename */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__65_62;
}
static void cont__65_62(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[8])->contents /* files */ = arguments->slots[0];
  // 359: maybe_push_common platform
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* platform */;
  result_count = 0;
  myself = frame->slots[3] /* maybe_push_common */;
  func = myself->type;
  frame->cont = cont__65_63;
}
static void cont__65_63(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 360: ... -> parent != NONE:
  // 361:   maybe_push_common parent
  // 362:   !parent supported_platforms(parent)
  frame->slots[9] /* temp__1 */ = create_closure(entry__65_64, 0);
  // 360: while -> parent != NONE:
  // 361:   maybe_push_common parent
  // 362:   !parent supported_platforms(parent)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  result_count = 0;
  myself = get__while();
  func = myself->type;
  frame->cont = cont__65_70;
}
static void entry__65_67(void) {
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
  // 361: maybe_push_common parent
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* parent */;
  result_count = 0;
  myself = frame->slots[0] /* maybe_push_common */;
  func = myself->type;
  frame->cont = cont__65_68;
}
static void cont__65_68(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 362: !parent supported_platforms(parent)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* parent */;
  result_count = 1;
  myself = var._supported_platforms;
  func = myself->type;
  frame->cont = cont__65_69;
}
static void cont__65_69(void) {
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
static void entry__65_64(void) {
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
  // 360: ... parent != NONE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parent */;
  arguments->slots[1] = var._NONE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__65_65;
}
static void cont__65_65(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 360: ... parent != NONE
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__65_66;
}
static void cont__65_66(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 360: ... :
  // 361:   maybe_push_common parent
  // 362:   !parent supported_platforms(parent)
  frame->slots[4] /* temp__3 */ = create_closure(entry__65_67, 0);
  // 360: ... -> parent != NONE:
  // 361:   maybe_push_common parent
  // 362:   !parent supported_platforms(parent)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__65_70(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 363: !module_info(mod_name)(platform) files
  frame->slots[9] /* temp__1 */ = ((CELL *)frame->slots[8])->contents /* files */;
  // 363: ... module_info(mod_name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* mod_name */;
  result_count = 1;
  myself = var._module_info;
  func = myself->type;
  frame->cont = cont__65_71;
}
static void cont__65_71(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__2 */ = arguments->slots[0];
  // 363: !module_info(mod_name)(platform)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* platform */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = frame->slots[10] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__65_72;
}
static void cont__65_72(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__2 */ = arguments->slots[0];
  // 363: !module_info(mod_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* mod_name */;
  arguments->slots[1] = frame->slots[10] /* temp__2 */;
  result_count = 1;
  myself = var._module_info;
  func = myself->type;
  frame->cont = cont__65_73;
}
static void cont__65_73(void) {
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
static void entry__65_41(void) {
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
  // 346: ... filename .has_suffix. "-common"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  arguments->slots[1] = string__65_42;
  result_count = 1;
  myself = get__has_suffix();
  func = myself->type;
  frame->cont = cont__65_43;
}
static void cont__65_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 346: ... :
  // 347:   $maybe_push_common: (plat)
  // 348:     $common_name string(name "-" plat "-common")
  // 349:     if filenames(common_name): push &files common_name
  // 350:   
  // 351:   $name filename .before. '-'
  // 352:   $mod_name string(mod_path name .truncate_from. '-')
  // 353:   $platform filename .behind. '-'
  // 354:   $$parent supported_platforms(platform)
  // 355:   unless parent.is_defined:
  // ...
  frame->slots[4] /* temp__2 */ = create_closure(entry__65_44, 0);
  // 346: unless filename .has_suffix. "-common":
  // 347:   $maybe_push_common: (plat)
  // 348:     $common_name string(name "-" plat "-common")
  // 349:     if filenames(common_name): push &files common_name
  // 350:   
  // 351:   $name filename .before. '-'
  // 352:   $mod_name string(mod_path name .truncate_from. '-')
  // 353:   $platform filename .behind. '-'
  // 354:   $$parent supported_platforms(platform)
  // 355:   unless parent.is_defined:
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
static void entry__65_39(void) {
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
  // 345: ... filename .contains. '-'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  arguments->slots[1] = character__45;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__65_40;
}
static void cont__65_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 345: ... :
  // 346:   unless filename .has_suffix. "-common":
  // 347:     $maybe_push_common: (plat)
  // 348:       $common_name string(name "-" plat "-common")
  // 349:       if filenames(common_name): push &files common_name
  // 350:     
  // 351:     $name filename .before. '-'
  // 352:     $mod_name string(mod_path name .truncate_from. '-')
  // 353:     $platform filename .behind. '-'
  // 354:     $$parent supported_platforms(platform)
  // ...
  frame->slots[4] /* temp__2 */ = create_closure(entry__65_41, 0);
  // 345: if filename .contains. '-':
  // 346:   unless filename .has_suffix. "-common":
  // 347:     $maybe_push_common: (plat)
  // 348:       $common_name string(name "-" plat "-common")
  // 349:       if filenames(common_name): push &files common_name
  // 350:     
  // 351:     $name filename .before. '-'
  // 352:     $mod_name string(mod_path name .truncate_from. '-')
  // 353:     $platform filename .behind. '-'
  // 354:     $$parent supported_platforms(platform)
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
static void cont__65_74(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 364: ... parameter_count_of(return)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* return */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__65_75;
}
static void cont__65_75(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 364: ... parameter_count_of(return) == 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__2 */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__65_76;
}
static void cont__65_76(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 364: ... : return directories modules
  frame->slots[9] /* temp__3 */ = create_closure(entry__65_77, 0);
  // 364: if parameter_count_of(return) == 2: return directories modules
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__65_78;
}
static void entry__65_77(void) {
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
  // 364: ... return directories modules
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* directories */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* modules */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__65_78(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__66_4(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // info: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 375: ... -> info
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__66_5(void) {
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
  // 376: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__66_6;
}
static void cont__66_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 376: ... before(mod_filename '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__66_7;
}
static void cont__66_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 376: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__66_8;
}
static void cont__66_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 376: ... until(mod_name '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* mod_name */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = get__until();
  func = myself->type;
  frame->cont = cont__66_9;
}
static void cont__66_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 376: add_module_infos before(mod_filename '/' -1) until(mod_name '/' -1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 0;
  myself = var._add_module_infos;
  func = myself->type;
  frame->cont = cont__66_10;
}
static void cont__66_10(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 377: ... module_info(mod_name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* mod_name */;
  result_count = 1;
  myself = var._module_info;
  func = myself->type;
  frame->cont = cont__66_11;
}
static void cont__66_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 377: -> module_info(mod_name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__66_1_lookup(void) {
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
  // 374: $info module_info(mod_name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* mod_name */;
  result_count = 1;
  myself = var._module_info;
  func = myself->type;
  frame->cont = cont__66_2;
}
static void cont__66_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* info */, arguments->slots[0]);
  // 375: ... info.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* info */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__66_3;
}
static void cont__66_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 375: ... -> info
  frame->slots[4] /* temp__2 */ = create_closure(entry__66_4, 0);
  // 375: ... :
  // 376:   add_module_infos before(mod_filename '/' -1) until(mod_name '/' -1)
  // 377:   -> module_info(mod_name)
  frame->slots[5] /* temp__3 */ = create_closure(entry__66_5, 0);
  // 375: if info.is_defined (-> info):
  // 376:   add_module_infos before(mod_filename '/' -1) until(mod_name '/' -1)
  // 377:   -> module_info(mod_name)
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
static void entry__67_1_Gcc(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // args: 0
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 380: ... : ewriteln "gcc " join(args)
  frame->slots[1] /* temp__1 */ = create_closure(entry__67_2, 0);
  // 380: if do_show_debug_infos: ewriteln "gcc " join(args)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_show_debug_infos();
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__67_5;
}
static void entry__67_2(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // args: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* args */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 380: ... join(args)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* args */;
  result_count = 1;
  myself = get__join();
  func = myself->type;
  frame->cont = cont__67_3;
}
static void cont__67_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 380: ... ewriteln "gcc " join(args)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__67_4;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__67_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 381: gcc args*
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = frame->caller_result_count;
  myself = var._gcc;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__68_4(void) {
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
  // 385: Gcc $_out $err $success gcc_options* "-c" c_filename "-o" o_filename
  argument_count = 0;
  arguments = node_p;
  unfold(var._gcc_options);
  arguments->slots[argument_count++] = string__68_5;
  arguments->slots[argument_count++] = frame->slots[0] /* c_filename */;
  arguments->slots[argument_count++] = string__68_6;
  arguments->slots[argument_count++] = frame->slots[1] /* o_filename */;
  result_count = 3;
  myself = var._Gcc;
  func = myself->type;
  frame->cont = cont__68_7;
}
static void cont__68_7(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  frame->slots[6] /* temp__2 */ = arguments->slots[1];
  frame->slots[7] /* temp__3 */ = arguments->slots[2];
  // 385: ... _out
  initialize_future(frame->slots[2] /* out */, frame->slots[5] /* temp__1 */);
  // 385: ... err
  initialize_future(frame->slots[3] /* err */, frame->slots[6] /* temp__2 */);
  // 385: ... success
  initialize_future(frame->slots[4] /* success */, frame->slots[7] /* temp__3 */);
  // 386: ... : Error err.from_utf8
  frame->slots[5] /* temp__1 */ = create_closure(entry__68_8, 0);
  // 386: unless success: Error err.from_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* success */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__68_10;
}
static void entry__68_8(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // err: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* err */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 386: ... err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* err */;
  result_count = 1;
  myself = get__from_utf8();
  func = myself->type;
  frame->cont = cont__68_9;
}
static void cont__68_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 386: ... Error err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__68_10(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 387: !do_link true
  set__do_link(get__true());
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__68_1_compile_c(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // c_filename: 0
  // o_filename: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 384: ... do_build_codeblocks_project || do_list_dependencies
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_build_codeblocks_project;
  arguments->slots[1] = func__68_2;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__68_3;
}
static void entry__68_2(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 384: ... do_list_dependencies
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._do_list_dependencies;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__68_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 384: ... :
  // 385:   Gcc $_out $err $success gcc_options* "-c" c_filename "-o" o_filename
  // 386:   unless success: Error err.from_utf8
  // 387:   !do_link true
  frame->slots[3] /* temp__2 */ = create_closure(entry__68_4, 0);
  // 384: unless do_build_codeblocks_project || do_list_dependencies:
  // 385:   Gcc $_out $err $success gcc_options* "-c" c_filename "-o" o_filename
  // 386:   unless success: Error err.from_utf8
  // 387:   !do_link true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__69_2(void) {
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
  // 399: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__69_3;
}
static void cont__69_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 399: $meta_path truncate_from(mod_filename '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[11] /* temp__1 */;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__69_4;
}
static void cont__69_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* meta_path */, arguments->slots[0]);
  // 400: ... dup(".meta" meta_level)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__65_16;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* meta_level */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__69_5;
}
static void cont__69_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 400: $filename string(mod_filename dup(".meta" meta_level))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = frame->slots[11] /* temp__1 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__69_6;
}
static void cont__69_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* filename */, arguments->slots[0]);
  // 401: $meta_filename string(filename ".sim")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* filename */;
  arguments->slots[1] = string__65_13;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__69_7;
}
static void cont__69_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* meta_filename */, arguments->slots[0]);
  // 402: ... dup(".meta" meta_level)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__65_16;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* meta_level */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__69_8;
}
static void cont__69_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 402: $meta_c_filename string(mod_filename dup(".meta" meta_level) ".c")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = frame->slots[11] /* temp__1 */;
  arguments->slots[2] = string__69_9;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__69_10;
}
static void cont__69_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* meta_c_filename */, arguments->slots[0]);
  // 403: ... meta_level-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* meta_level */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__69_11;
}
static void cont__69_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__2 */ = arguments->slots[0];
  // 403: ... dup(".meta" meta_level-1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__65_16;
  arguments->slots[1] = frame->slots[12] /* temp__2 */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__69_12;
}
static void cont__69_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 403: $sim_filename string(mod_filename dup(".meta" meta_level-1) ".sim")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = frame->slots[11] /* temp__1 */;
  arguments->slots[2] = string__65_13;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__69_13;
}
static void cont__69_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* sim_filename */, arguments->slots[0]);
  // 404: $meta_info stat(meta_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* meta_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__69_14;
}
static void cont__69_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[7] /* meta_info */, arguments->slots[0]);
  // 405: $sim_info stat(sim_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* sim_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__69_15;
}
static void cont__69_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[8] /* sim_info */, arguments->slots[0]);
  // 406: $meta_c_info stat(meta_c_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* meta_c_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__69_16;
}
static void cont__69_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[9] /* meta_c_info */, arguments->slots[0]);
  frame->slots[11] /* temp__1 */ = create_closure(entry__69_17, 0);
  // 408: $$force_rebuild
  // 409:   ||
  // 410:     do_rebuild
  // 411:     sim_info.is_undefined
  // 412:     meta_c_info.is_undefined
  // 413:     modification_time_of(meta_info) > modification_time_of(meta_c_info)
  // 414:     modification_time_of(meta_c_info) > modification_time_of(sim_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_rebuild;
  arguments->slots[1] = frame->slots[11] /* temp__1 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__69_32;
}
static void entry__69_17(void) {
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
  // 411: sim_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* sim_info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__69_18;
}
static void cont__69_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  frame->slots[5] /* temp__3 */ = create_closure(entry__69_19, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__69_31;
}
static void entry__69_19(void) {
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
  // 412: meta_c_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* meta_c_info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__69_20;
}
static void cont__69_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  frame->slots[5] /* temp__3 */ = create_closure(entry__69_21, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__69_30;
}
static void entry__69_21(void) {
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
  // 413: ... modification_time_of(meta_c_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* meta_c_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__69_22;
}
static void cont__69_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 413: modification_time_of(meta_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* meta_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__69_23;
}
static void cont__69_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__4 */ = arguments->slots[0];
  // 413: modification_time_of(meta_info) > modification_time_of(meta_c_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__69_24;
}
static void cont__69_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 414: modification_time_of(meta_c_info) > modification_time_of(sim_info)
  frame->slots[7] /* temp__5 */ = create_closure(entry__69_25, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__5 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__69_29;
}
static void entry__69_25(void) {
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
  // 414: ... modification_time_of(sim_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* sim_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__69_26;
}
static void cont__69_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 414: modification_time_of(meta_c_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* meta_c_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__69_27;
}
static void cont__69_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 414: modification_time_of(meta_c_info) > modification_time_of(sim_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__69_28;
}
static void cont__69_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 414: modification_time_of(meta_c_info) > modification_time_of(sim_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__69_29(void) {
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
static void cont__69_30(void) {
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
static void cont__69_31(void) {
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
static void cont__69_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[10])->contents /* force_rebuild */ = arguments->slots[0];
  // 416: ... :
  // 417:   $modification_time modification_time_of(sim_info)
  // 418:   load $meta_c_buf meta_c_filename
  // 419:   do: (-> break)
  // 420:     for_each_line meta_c_buf: ($line)
  // 421:       $check: (data_filename)
  // 422:         $data_info stat(data_filename)
  // 423:         if
  // 424:           ||
  // 425:             data_info.is_undefined
  // ...
  frame->slots[11] /* temp__1 */ = create_closure(entry__69_33, 0);
  // 416: unless force_rebuild:
  // 417:   $modification_time modification_time_of(sim_info)
  // 418:   load $meta_c_buf meta_c_filename
  // 419:   do: (-> break)
  // 420:     for_each_line meta_c_buf: ($line)
  // 421:       $check: (data_filename)
  // 422:         $data_info stat(data_filename)
  // 423:         if
  // 424:           ||
  // 425:             data_info.is_undefined
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[10])->contents /* force_rebuild */;
  arguments->slots[1] = frame->slots[11] /* temp__1 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__69_66;
}
static void entry__69_36(void) {
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
  // 420: ... : ($line)
  // 421:   $check: (data_filename)
  // 422:     $data_info stat(data_filename)
  // 423:     if
  // 424:       ||
  // 425:         data_info.is_undefined
  // 426:         modification_time_of(data_info) > modification_time
  // 427:       :
  // 428:         !force_rebuild true
  // 429:         break
  // ...
  frame->slots[5] /* temp__1 */ = create_closure(entry__69_37, 1);
  // 420: for_each_line meta_c_buf: ($line)
  // 421:   $check: (data_filename)
  // 422:     $data_info stat(data_filename)
  // 423:     if
  // 424:       ||
  // 425:         data_info.is_undefined
  // 426:         modification_time_of(data_info) > modification_time
  // 427:       :
  // 428:         !force_rebuild true
  // 429:         break
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* meta_c_buf */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each_line();
  func = myself->type;
  frame->cont = cont__69_65;
}
static void entry__69_63(void) {
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
  // 441: ... string(path '/' argument)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* path */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[2] /* argument */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__69_64;
}
static void cont__69_64(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 441: ... check string(path '/' argument)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* check */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__69_58(void) {
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
  // 439: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__69_59;
}
static void cont__69_59(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 439: ... range(argument 2 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* argument */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__69_60;
}
static void cont__69_60(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 439: ... string(meta_path range(argument 2 -1))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* meta_path */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__69_61;
}
static void cont__69_61(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 439: check string(meta_path range(argument 2 -1))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* check */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__69_62(void) {
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
  // 441: ... : (path) check string(path '/' argument)
  frame->slots[2] /* temp__1 */ = create_closure(entry__69_63, 1);
  // 441: for_each simdatapaths: (path) check string(path '/' argument)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._simdatapaths;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__69_55(void) {
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
  // 438: argument .has_prefix. "./"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* argument */;
  arguments->slots[1] = string__69_56;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__69_57;
}
static void cont__69_57(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 438: ... :
  // 439:   check string(meta_path range(argument 2 -1))
  frame->slots[4] /* temp__2 */ = create_closure(entry__69_58, 0);
  // 440: :
  // 441:   for_each simdatapaths: (path) check string(path '/' argument)
  frame->slots[5] /* temp__3 */ = create_closure(entry__69_62, 0);
  // 437: if
  // 438:   argument .has_prefix. "./":
  // 439:     check string(meta_path range(argument 2 -1))
  // 440:   :
  // 441:     for_each simdatapaths: (path) check string(path '/' argument)
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
static void entry__69_37(void) {
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
  // 421: ... : (data_filename)
  // 422:   $data_info stat(data_filename)
  // 423:   if
  // 424:     ||
  // 425:       data_info.is_undefined
  // 426:       modification_time_of(data_info) > modification_time
  // 427:     :
  // 428:       !force_rebuild true
  // 429:       break
  frame->slots[8] /* temp__1 */ = create_closure(entry__69_38_check, 1);
  // 421: $check: (data_filename)
  // 422:   $data_info stat(data_filename)
  // 423:   if
  // 424:     ||
  // 425:       data_info.is_undefined
  // 426:       modification_time_of(data_info) > modification_time
  // 427:     :
  // 428:       !force_rebuild true
  // 429:       break
  initialize_future(frame->slots[5] /* check */, frame->slots[8] /* temp__1 */);
  // 431: ... line .has_prefix. "/// "
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  arguments->slots[1] = string__69_46;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__69_47;
}
static void entry__69_45(void) {
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
  // 428: !force_rebuild true
  ((CELL *)frame->slots[0])->contents /* force_rebuild */ = get__true();
  // 429: break
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* break */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__69_38_check(void) {
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
  // 422: $data_info stat(data_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* data_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__69_39;
}
static void cont__69_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* data_info */, arguments->slots[0]);
  // 425: data_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* data_info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__69_40;
}
static void cont__69_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 426: modification_time_of(data_info) > modification_time
  frame->slots[7] /* temp__3 */ = create_closure(entry__69_41, 0);
  // 424: ||
  // 425:   data_info.is_undefined
  // 426:   modification_time_of(data_info) > modification_time
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__69_44;
}
static void entry__69_41(void) {
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
  // 426: modification_time_of(data_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* data_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__69_42;
}
static void cont__69_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 426: modification_time_of(data_info) > modification_time
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* modification_time */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__69_43;
}
static void cont__69_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 426: modification_time_of(data_info) > modification_time
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__69_44(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 427: :
  // 428:   !force_rebuild true
  // 429:   break
  frame->slots[8] /* temp__4 */ = create_closure(entry__69_45, 0);
  // 423: if
  // 424:   ||
  // 425:     data_info.is_undefined
  // 426:     modification_time_of(data_info) > modification_time
  // 427:   :
  // 428:     !force_rebuild true
  // 429:     break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__69_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 431: unless line .has_prefix. "/// " break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* break */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__69_48;
}
static void cont__69_48(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 432: behind &line ' '
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  arguments->slots[1] = character__32;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__69_49;
}
static void cont__69_49(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* line */ = arguments->slots[0];
  // 433: trim &line
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__69_50;
}
static void cont__69_50(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* line */ = arguments->slots[0];
  // 434: $command line .truncate_from. WHITESPACE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  arguments->slots[1] = var._WHITESPACE;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__69_51;
}
static void cont__69_51(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* command */, arguments->slots[0]);
  // 435: $argument line .behind. WHITESPACE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  arguments->slots[1] = var._WHITESPACE;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__69_52;
}
static void cont__69_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[7] /* argument */, arguments->slots[0]);
  // 436: ... command == "data"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* command */;
  arguments->slots[1] = string__69_53;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__69_54;
}
static void cont__69_54(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 436: ... :
  // 437:   if
  // 438:     argument .has_prefix. "./":
  // 439:       check string(meta_path range(argument 2 -1))
  // 440:     :
  // 441:       for_each simdatapaths: (path) check string(path '/' argument)
  frame->slots[9] /* temp__2 */ = create_closure(entry__69_55, 0);
  // 436: if command == "data":
  // 437:   if
  // 438:     argument .has_prefix. "./":
  // 439:       check string(meta_path range(argument 2 -1))
  // 440:     :
  // 441:       for_each simdatapaths: (path) check string(path '/' argument)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__69_65(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__69_33(void) {
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
  // 417: $modification_time modification_time_of(sim_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* sim_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__69_34;
}
static void cont__69_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* modification_time */, arguments->slots[0]);
  // 418: load $meta_c_buf meta_c_filename
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* meta_c_filename */;
  result_count = 1;
  myself = get__load();
  func = myself->type;
  frame->cont = cont__69_35;
}
static void cont__69_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* meta_c_buf */, arguments->slots[0]);
  // 419: ... : (-> break)
  // 420:   for_each_line meta_c_buf: ($line)
  // 421:     $check: (data_filename)
  // 422:       $data_info stat(data_filename)
  // 423:       if
  // 424:         ||
  // 425:           data_info.is_undefined
  // 426:           modification_time_of(data_info) > modification_time
  // 427:         :
  // 428:           !force_rebuild true
  // ...
  frame->slots[6] /* temp__1 */ = create_closure(entry__69_36, 0);
  // 419: do: (-> break)
  // 420:   for_each_line meta_c_buf: ($line)
  // 421:     $check: (data_filename)
  // 422:       $data_info stat(data_filename)
  // 423:       if
  // 424:         ||
  // 425:           data_info.is_undefined
  // 426:           modification_time_of(data_info) > modification_time
  // 427:         :
  // 428:           !force_rebuild true
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__do();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__69_66(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 442: ... :
  // 443:   %on_top_level false
  // 444:   %%objects empty_insert_order_set
  // 445:   %%libraries empty_insert_order_set
  // 446:   %%do_link false
  // 447:   %%last_modification_time undefined
  // 448:   %do_build_static_executable false
  // 449:   %main_filename meta_filename
  // 450:   %main_info stat(main_filename)
  // 451:   build_executable
  // ...
  frame->slots[11] /* temp__1 */ = create_closure(entry__69_67, 0);
  // 442: if force_rebuild:
  // 443:   %on_top_level false
  // 444:   %%objects empty_insert_order_set
  // 445:   %%libraries empty_insert_order_set
  // 446:   %%do_link false
  // 447:   %%last_modification_time undefined
  // 448:   %do_build_static_executable false
  // 449:   %main_filename meta_filename
  // 450:   %main_info stat(main_filename)
  // 451:   build_executable
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[10])->contents /* force_rebuild */;
  arguments->slots[1] = frame->slots[11] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__69_79;
}
static void entry__69_67(void) {
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
  // 443: %on_top_level false
  initialize_maybe_future(get__on_top_level(), get__false());
  // 444: %%objects empty_insert_order_set
  set__objects(get__empty_insert_order_set());
  // 445: %%libraries empty_insert_order_set
  set__libraries(get__empty_insert_order_set());
  // 446: %%do_link false
  set__do_link(get__false());
  // 447: %%last_modification_time undefined
  set__last_modification_time(get__undefined());
  // 448: %do_build_static_executable false
  initialize_maybe_future(get__do_build_static_executable(), get__false());
  // 449: %main_filename meta_filename
  initialize_maybe_future(get__main_filename(), frame->slots[1] /* meta_filename */);
  // 450: %main_info stat(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__69_68;
}
static void cont__69_68(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(get__main_info(), arguments->slots[0]);
  // 451: build_executable
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._build_executable;
  func = myself->type;
  frame->cont = cont__69_69;
}
static void cont__69_69(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 452: $orig_path current_path()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__current_path();
  func = myself->type;
  frame->cont = cont__69_70;
}
static void cont__69_70(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* orig_path */, arguments->slots[0]);
  // 453: change_directory meta_path
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* meta_path */;
  result_count = 0;
  myself = get__change_directory();
  func = myself->type;
  frame->cont = cont__69_71;
}
static void cont__69_71(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 454: std::call $out $err $success filename
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* filename */;
  result_count = 3;
  myself = get__std__call();
  func = myself->type;
  frame->cont = cont__69_72;
}
static void cont__69_72(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  frame->slots[10] /* temp__2 */ = arguments->slots[1];
  frame->slots[11] /* temp__3 */ = arguments->slots[2];
  // 454: ... out
  initialize_future(frame->slots[6] /* out */, frame->slots[9] /* temp__1 */);
  // 454: ... err
  initialize_future(frame->slots[7] /* err */, frame->slots[10] /* temp__2 */);
  // 454: ... success
  initialize_future(frame->slots[8] /* success */, frame->slots[11] /* temp__3 */);
  // 455: change_directory orig_path
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* orig_path */;
  result_count = 0;
  myself = get__change_directory();
  func = myself->type;
  frame->cont = cont__69_73;
}
static void cont__69_73(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 456: ... : Error err.from_utf8
  frame->slots[9] /* temp__1 */ = create_closure(entry__69_74, 0);
  // 456: unless success: Error err.from_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* success */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__69_76;
}
static void entry__69_74(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // err: 0
  frame->slots[0] = myself->closure.frame->slots[7]; /* err */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 456: ... err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* err */;
  result_count = 1;
  myself = get__from_utf8();
  func = myself->type;
  frame->cont = cont__69_75;
}
static void cont__69_75(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 456: ... Error err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__69_76(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 457: ... out.to_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* out */;
  result_count = 1;
  myself = get__to_utf8();
  func = myself->type;
  frame->cont = cont__69_77;
}
static void cont__69_77(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 457: save sim_filename out.to_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* sim_filename */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__save();
  func = myself->type;
  frame->cont = cont__69_78;
}
static void cont__69_78(void) {
  myself = frame->slots[0] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__69_79(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 458: dec &meta_level
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* meta_level */;
  result_count = 1;
  myself = get__dec();
  func = myself->type;
  frame->cont = cont__69_80;
}
static void cont__69_80(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* meta_level */ = arguments->slots[0];
  // 459: ... meta_level > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* meta_level */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__69_81;
}
static void cont__69_81(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 459: -> meta_level > 0
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__69_1_compile_meta_module(void) {
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
  // 398: ... :
  // 399:   $meta_path truncate_from(mod_filename '/' -1)
  // 400:   $filename string(mod_filename dup(".meta" meta_level))
  // 401:   $meta_filename string(filename ".sim")
  // 402:   $meta_c_filename string(mod_filename dup(".meta" meta_level) ".c")
  // 403:   $sim_filename string(mod_filename dup(".meta" meta_level-1) ".sim")
  // 404:   $meta_info stat(meta_filename)
  // 405:   $sim_info stat(sim_filename)
  // 406:   $meta_c_info stat(meta_c_filename)
  // 407:   
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__69_2, 0);
  // 398: do_while:
  // 399:   $meta_path truncate_from(mod_filename '/' -1)
  // 400:   $filename string(mod_filename dup(".meta" meta_level))
  // 401:   $meta_filename string(filename ".sim")
  // 402:   $meta_c_filename string(mod_filename dup(".meta" meta_level) ".c")
  // 403:   $sim_filename string(mod_filename dup(".meta" meta_level-1) ".sim")
  // 404:   $meta_info stat(meta_filename)
  // 405:   $sim_info stat(sim_filename)
  // 406:   $meta_c_info stat(meta_c_filename)
  // 407:   
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__do_while();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__70_1_build_dependencies(void) {
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
  // 472: ... : ($line)
  // 473:   unless line .has_prefix. "/// " return
  // 474:   behind &line ' '
  // 475:   trim &line
  // 476:   $command line .truncate_from. WHITESPACE
  // 477:   $argument line .behind. WHITESPACE
  // 478:   case
  // 479:     command
  // 480:     "require":
  // 481:       if
  // ...
  frame->slots[5] /* temp__1 */ = create_closure(entry__70_2, 1);
  // 472: for_each_line c_buf: ($line)
  // 473:   unless line .has_prefix. "/// " return
  // 474:   behind &line ' '
  // 475:   trim &line
  // 476:   $command line .truncate_from. WHITESPACE
  // 477:   $argument line .behind. WHITESPACE
  // 478:   case
  // 479:     command
  // 480:     "require":
  // 481:       if
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* c_buf */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each_line();
  func = myself->type;
  frame->cont = cont__70_41;
}
static void entry__70_36(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // argument: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 500: ... !libraries(argument .truncate_from. '/') true
  frame->slots[1] /* temp__1 */ = get__true();
  // 500: ... argument .truncate_from. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* argument */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__70_37;
}
static void cont__70_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 500: ... !libraries(argument .truncate_from. '/')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__libraries();
  func = myself->type;
  frame->cont = cont__70_38;
}
static void cont__70_38(void) {
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
static void entry__70_30(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // argument: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 498: !libraries(string("sim-" argument .truncate_from. '/')) true
  frame->slots[1] /* temp__1 */ = get__true();
  // 498: ... argument .truncate_from. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* argument */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__70_31;
}
static void cont__70_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 498: ... string("sim-" argument .truncate_from. '/')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__70_32;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__70_33;
}
static void cont__70_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 498: !libraries(string("sim-" argument .truncate_from. '/'))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__libraries();
  func = myself->type;
  frame->cont = cont__70_34;
}
static void cont__70_34(void) {
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
static void entry__70_27(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // argument: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 495: ... resolve_filename(argument)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* argument */;
  result_count = 1;
  myself = var._resolve_filename;
  func = myself->type;
  frame->cont = cont__70_28;
}
static void cont__70_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 495: compile_module resolve_filename(argument) argument
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[0] /* argument */;
  result_count = frame->caller_result_count;
  myself = var._compile_module;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__70_29(void) {
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
  // 497: ... :
  // 498:   !libraries(string("sim-" argument .truncate_from. '/')) true
  frame->slots[2] /* temp__1 */ = create_closure(entry__70_30, 0);
  // 497: if do_compile_c:
  // 498:   !libraries(string("sim-" argument .truncate_from. '/')) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* do_compile_c */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__70_13(void) {
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
  // 484: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__70_14;
}
static void cont__70_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 484: $req_name range(argument 3 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* argument */;
  arguments->slots[1] = number__3;
  arguments->slots[2] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__70_15;
}
static void cont__70_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* req_name */, arguments->slots[0]);
  // 486: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__70_16;
}
static void cont__70_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 486: ... until(mod_filename '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* mod_filename */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count = 1;
  myself = get__until();
  func = myself->type;
  frame->cont = cont__70_17;
}
static void cont__70_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 486: string(until(mod_filename '/' -1) req_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* req_name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__70_18;
}
static void cont__70_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 487: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__70_19;
}
static void cont__70_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__6 */ = arguments->slots[0];
  // 487: ... until(mod_name '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* mod_name */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[9] /* temp__6 */;
  result_count = 1;
  myself = get__until();
  func = myself->type;
  frame->cont = cont__70_20;
}
static void cont__70_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__5 */ = arguments->slots[0];
  // 487: string(until(mod_name '/' -1) req_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__5 */;
  arguments->slots[1] = frame->slots[3] /* req_name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__70_21;
}
static void cont__70_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__4 */ = arguments->slots[0];
  // 485: compile_module
  // 486:   string(until(mod_filename '/' -1) req_name)
  // 487:   string(until(mod_name '/' -1) req_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = var._compile_module;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__70_11(void) {
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
  // 483: ... mode == EXE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__mode();
  arguments->slots[1] = var._EXE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__70_12;
}
static void cont__70_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 483: ... :
  // 484:   $req_name range(argument 3 -1)
  // 485:   compile_module
  // 486:     string(until(mod_filename '/' -1) req_name)
  // 487:     string(until(mod_name '/' -1) req_name)
  frame->slots[4] /* temp__2 */ = create_closure(entry__70_13, 0);
  // 483: if mode == EXE:
  // 484:   $req_name range(argument 3 -1)
  // 485:   compile_module
  // 486:     string(until(mod_filename '/' -1) req_name)
  // 487:     string(until(mod_name '/' -1) req_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__70_22(void) {
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
  arguments->slots[1] = func__70_23;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__70_26;
}
static void entry__70_23(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_build_codeblocks_project;
  arguments->slots[1] = func__70_24;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__70_25;
}
static void entry__70_24(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 493: do_list_dependencies
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._do_list_dependencies;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__70_25(void) {
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
static void cont__70_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 494: :
  // 495:   compile_module resolve_filename(argument) argument
  frame->slots[3] /* temp__2 */ = create_closure(entry__70_27, 0);
  // 496: :
  // 497:   if do_compile_c:
  // 498:     !libraries(string("sim-" argument .truncate_from. '/')) true
  frame->slots[4] /* temp__3 */ = create_closure(entry__70_29, 0);
  // 489: if
  // 490:   ||
  // 491:     do_build_static_executable
  // 492:     do_build_codeblocks_project
  // 493:     do_list_dependencies
  // 494:   :
  // 495:     compile_module resolve_filename(argument) argument
  // 496:   :
  // 497:     if do_compile_c:
  // 498:       !libraries(string("sim-" argument .truncate_from. '/')) true
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
static void entry__70_9(void) {
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
  // 482: argument .has_prefix. "./"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* argument */;
  arguments->slots[1] = string__69_56;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__70_10;
}
static void cont__70_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 482: ... :
  // 483:   if mode == EXE:
  // 484:     $req_name range(argument 3 -1)
  // 485:     compile_module
  // 486:       string(until(mod_filename '/' -1) req_name)
  // 487:       string(until(mod_name '/' -1) req_name)
  frame->slots[5] /* temp__2 */ = create_closure(entry__70_11, 0);
  // 488: :
  // 489:   if
  // 490:     ||
  // 491:       do_build_static_executable
  // 492:       do_build_codeblocks_project
  // 493:       do_list_dependencies
  // 494:     :
  // 495:       compile_module resolve_filename(argument) argument
  // 496:     :
  // 497:       if do_compile_c:
  // ...
  frame->slots[6] /* temp__3 */ = create_closure(entry__70_22, 0);
  // 481: if
  // 482:   argument .has_prefix. "./":
  // 483:     if mode == EXE:
  // 484:       $req_name range(argument 3 -1)
  // 485:       compile_module
  // 486:         string(until(mod_filename '/' -1) req_name)
  // 487:         string(until(mod_name '/' -1) req_name)
  // 488:   :
  // 489:     if
  // 490:       ||
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
static void entry__70_35(void) {
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
  // 500: ... : !libraries(argument .truncate_from. '/') true
  frame->slots[2] /* temp__1 */ = create_closure(entry__70_36, 0);
  // 500: if do_compile_c: !libraries(argument .truncate_from. '/') true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* do_compile_c */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__70_2(void) {
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
  // 473: ... line .has_prefix. "/// "
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  arguments->slots[1] = string__69_46;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__70_3;
}
static void cont__70_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 473: unless line .has_prefix. "/// " return
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* return */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__70_4;
}
static void cont__70_4(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 474: behind &line ' '
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  arguments->slots[1] = character__32;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__70_5;
}
static void cont__70_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* line */ = arguments->slots[0];
  // 475: trim &line
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__70_6;
}
static void cont__70_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* line */ = arguments->slots[0];
  // 476: $command line .truncate_from. WHITESPACE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  arguments->slots[1] = var._WHITESPACE;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__70_7;
}
static void cont__70_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* command */, arguments->slots[0]);
  // 477: $argument line .behind. WHITESPACE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  arguments->slots[1] = var._WHITESPACE;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__70_8;
}
static void cont__70_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* argument */, arguments->slots[0]);
  // 480: ... :
  // 481:   if
  // 482:     argument .has_prefix. "./":
  // 483:       if mode == EXE:
  // 484:         $req_name range(argument 3 -1)
  // 485:         compile_module
  // 486:           string(until(mod_filename '/' -1) req_name)
  // 487:           string(until(mod_name '/' -1) req_name)
  // 488:     :
  // 489:       if
  // ...
  frame->slots[7] /* temp__1 */ = create_closure(entry__70_9, 0);
  // 499: ... :
  // 500:   if do_compile_c: !libraries(argument .truncate_from. '/') true
  frame->slots[8] /* temp__2 */ = create_closure(entry__70_35, 0);
  // 478: case
  // 479:   command
  // 480:   "require":
  // 481:     if
  // 482:       argument .has_prefix. "./":
  // 483:         if mode == EXE:
  // 484:           $req_name range(argument 3 -1)
  // 485:           compile_module
  // 486:             string(until(mod_filename '/' -1) req_name)
  // 487:             string(until(mod_name '/' -1) req_name)
  // ...
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* command */;
  arguments->slots[1] = string__70_39;
  arguments->slots[2] = frame->slots[7] /* temp__1 */;
  arguments->slots[3] = string__70_40;
  arguments->slots[4] = frame->slots[8] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__70_41(void) {
  myself = frame->slots[4] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__71_1_compile_module(void) {
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
  // 511: ... :
  // 512:   (
  // 513:     submodule_names # no paths; no extensions
  // 514:     do_compile_c = true
  // 515:     suffix = "" # a hyphen followed by the platform name
  // 516:   )
  // 517:   $$modification_time undefined
  // 518:   $$sim_filenames empty_list
  // 519:   for_each submodule_names: (submodule_name)
  // 520:     $meta_level meta_levels(submodule_name)
  // ...
  frame->slots[6] /* temp__1 */ = create_closure(entry__71_2_compile_submodule, -1);
  // 511: $compile_submodule:
  // 512:   (
  // 513:     submodule_names # no paths; no extensions
  // 514:     do_compile_c = true
  // 515:     suffix = "" # a hyphen followed by the platform name
  // 516:   )
  // 517:   $$modification_time undefined
  // 518:   $$sim_filenames empty_list
  // 519:   for_each submodule_names: (submodule_name)
  // 520:     $meta_level meta_levels(submodule_name)
  // ...
  initialize_future(frame->slots[3] /* compile_submodule */, frame->slots[6] /* temp__1 */);
  // 567: lookup $mod_info mod_filename mod_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = frame->slots[1] /* mod_name */;
  result_count = 1;
  myself = var._lookup;
  func = myself->type;
  frame->cont = cont__71_73;
}
static void entry__71_2_compile_submodule(void) {
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
  // 517: $$modification_time undefined
  ((CELL *)frame->slots[6])->contents /* modification_time */ = get__undefined();
  // 518: $$sim_filenames empty_list
  ((CELL *)frame->slots[7])->contents /* sim_filenames */ = get__empty_list();
  // 519: ... : (submodule_name)
  // 520:   $meta_level meta_levels(submodule_name)
  // 521:   $submodule_filename string(until(mod_filename '/' -1) submodule_name)
  // 522:   if meta_level > 0 && not(do_omit_meta):
  // 523:     compile_meta_module submodule_filename submodule_name meta_level
  // 524:   $sim_filename string(submodule_filename ".sim")
  // 525:   push &sim_filenames sim_filename
  // 526:   $sim_info stat(sim_filename)
  // 527:   if
  // 528:     ||
  // ...
  frame->slots[11] /* temp__1 */ = create_closure(entry__71_3, 1);
  // 519: for_each submodule_names: (submodule_name)
  // 520:   $meta_level meta_levels(submodule_name)
  // 521:   $submodule_filename string(until(mod_filename '/' -1) submodule_name)
  // 522:   if meta_level > 0 && not(do_omit_meta):
  // 523:     compile_meta_module submodule_filename submodule_name meta_level
  // 524:   $sim_filename string(submodule_filename ".sim")
  // 525:   push &sim_filenames sim_filename
  // 526:   $sim_info stat(sim_filename)
  // 527:   if
  // 528:     ||
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* submodule_names */;
  arguments->slots[1] = frame->slots[11] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__71_24;
}
static void entry__71_22(void) {
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
  // 532: !modification_time modification_time_of(sim_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* sim_info */;
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
  ((CELL *)frame->slots[0])->contents /* modification_time */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__71_3(void) {
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
  // 520: $meta_level meta_levels(submodule_name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* submodule_name */;
  result_count = 1;
  myself = var._meta_levels;
  func = myself->type;
  frame->cont = cont__71_4;
}
static void cont__71_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* meta_level */, arguments->slots[0]);
  // 521: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__71_5;
}
static void cont__71_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__2 */ = arguments->slots[0];
  // 521: ... until(mod_filename '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* mod_filename */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[9] /* temp__2 */;
  result_count = 1;
  myself = get__until();
  func = myself->type;
  frame->cont = cont__71_6;
}
static void cont__71_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 521: $submodule_filename string(until(mod_filename '/' -1) submodule_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = frame->slots[0] /* submodule_name */;
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
  initialize_future(frame->slots[5] /* submodule_filename */, arguments->slots[0]);
  // 522: ... meta_level > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = frame->slots[4] /* meta_level */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__71_8;
}
static void cont__71_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__2 */ = arguments->slots[0];
  // 522: ... meta_level > 0 && not(do_omit_meta)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__2 */;
  arguments->slots[1] = func__71_9;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__71_11;
}
static void entry__71_9(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 522: ... not(do_omit_meta)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._do_omit_meta;
  result_count = 1;
  myself = get__not();
  func = myself->type;
  frame->cont = cont__71_10;
}
static void cont__71_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 522: ... not(do_omit_meta)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__71_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 522: ... :
  // 523:   compile_meta_module submodule_filename submodule_name meta_level
  frame->slots[10] /* temp__3 */ = create_closure(entry__71_12, 0);
  // 522: if meta_level > 0 && not(do_omit_meta):
  // 523:   compile_meta_module submodule_filename submodule_name meta_level
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__71_13;
}
static void entry__71_12(void) {
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
  // 523: compile_meta_module submodule_filename submodule_name meta_level
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
static void cont__71_13(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 524: $sim_filename string(submodule_filename ".sim")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* submodule_filename */;
  arguments->slots[1] = string__65_13;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__71_14;
}
static void cont__71_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* sim_filename */, arguments->slots[0]);
  // 525: push &sim_filenames sim_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* sim_filenames */;
  arguments->slots[1] = frame->slots[6] /* sim_filename */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__71_15;
}
static void cont__71_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* sim_filenames */ = arguments->slots[0];
  // 526: $sim_info stat(sim_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* sim_filename */;
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
  initialize_future(frame->slots[7] /* sim_info */, arguments->slots[0]);
  // 529: modification_time.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* modification_time */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__71_17;
}
static void cont__71_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__2 */ = arguments->slots[0];
  // 530: modification_time_of(sim_info) > modification_time
  frame->slots[10] /* temp__3 */ = create_closure(entry__71_18, 0);
  // 528: ||
  // 529:   modification_time.is_undefined
  // 530:   modification_time_of(sim_info) > modification_time
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__2 */;
  arguments->slots[1] = frame->slots[10] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__71_21;
}
static void entry__71_18(void) {
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
  // 530: modification_time_of(sim_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* sim_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__71_19;
}
static void cont__71_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 530: modification_time_of(sim_info) > modification_time
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* modification_time */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__71_20;
}
static void cont__71_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 530: modification_time_of(sim_info) > modification_time
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__71_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 531: :
  // 532:   !modification_time modification_time_of(sim_info)
  frame->slots[11] /* temp__4 */ = create_closure(entry__71_22, 0);
  // 527: if
  // 528:   ||
  // 529:     modification_time.is_undefined
  // 530:     modification_time_of(sim_info) > modification_time
  // 531:   :
  // 532:     !modification_time modification_time_of(sim_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = frame->slots[11] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__71_24(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 533: $c_filename string(mod_filename suffix ".c")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* mod_filename */;
  arguments->slots[1] = frame->slots[2] /* suffix */;
  arguments->slots[2] = string__69_9;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__71_25;
}
static void cont__71_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[8] /* c_filename */, arguments->slots[0]);
  // 534: $c_info stat(c_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* c_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__71_26;
}
static void cont__71_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[9] /* c_info */, arguments->slots[0]);
  // 535: ... : !c_sources(c_filename) true
  frame->slots[11] /* temp__1 */ = create_closure(entry__71_27, 0);
  // 535: if do_compile_c: !c_sources(c_filename) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* do_compile_c */;
  arguments->slots[1] = frame->slots[11] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__71_29;
}
static void entry__71_27(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // c_filename: 0
  frame->slots[0] = myself->closure.frame->slots[8]; /* c_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 535: ... !c_sources(c_filename) true
  frame->slots[1] /* temp__1 */ = get__true();
  // 535: ... !c_sources(c_filename)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_filename */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = var._c_sources;
  func = myself->type;
  frame->cont = cont__71_28;
}
static void cont__71_28(void) {
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
static void cont__71_29(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 536: $$c_buf undefined
  ((CELL *)frame->slots[10])->contents /* c_buf */ = get__undefined();
  frame->slots[12] /* temp__2 */ = create_closure(entry__71_30, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_rebuild;
  arguments->slots[1] = frame->slots[12] /* temp__2 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__71_36;
}
static void entry__71_30(void) {
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
  // 540: c_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__71_31;
}
static void cont__71_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 541: modification_time > modification_time_of(c_info)
  frame->slots[4] /* temp__3 */ = create_closure(entry__71_32, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__71_35;
}
static void entry__71_32(void) {
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
  // 541: ... modification_time_of(c_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__71_33;
}
static void cont__71_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 541: modification_time > modification_time_of(c_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* modification_time */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__71_34;
}
static void cont__71_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 541: modification_time > modification_time_of(c_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__71_35(void) {
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
static void cont__71_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 542: :
  // 543:   %sim2c::module_name replace_all(mod_name '/' = "__" '.' = "__")
  // 544:   if verbose: ewriteln "build module " module_name suffix
  // 545:   collect_output $c_source: sim2c sim_filenames
  // 546:   collect_output !c_buf: create_imports c_source
  // 547:   save c_filename c_buf.to_utf8
  // 548:   if do_compile_c: compile_c c_filename o_filename
  frame->slots[13] /* temp__3 */ = create_closure(entry__71_37, 0);
  // 549: :
  // 550:   load !c_buf c_filename
  // 551:   $o_info stat(o_filename)
  // 552:   if
  // 553:     ||
  // 554:       o_info.is_undefined
  // 555:       modification_time_of(c_info) > modification_time_of(o_info)
  // 556:     :
  // 557:       if do_compile_c: compile_c c_filename o_filename
  // 558:     :
  // ...
  frame->slots[14] /* temp__4 */ = create_closure(entry__71_53, 0);
  // 537: if
  // 538:   ||
  // 539:     do_rebuild
  // 540:     c_info.is_undefined
  // 541:     modification_time > modification_time_of(c_info)
  // 542:   :
  // 543:     %sim2c::module_name replace_all(mod_name '/' = "__" '.' = "__")
  // 544:     if verbose: ewriteln "build module " module_name suffix
  // 545:     collect_output $c_source: sim2c sim_filenames
  // 546:     collect_output !c_buf: create_imports c_source
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  arguments->slots[1] = frame->slots[13] /* temp__3 */;
  arguments->slots[2] = frame->slots[14] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__71_72;
}
static void entry__71_70(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // o_info: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* o_info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 564: !last_modification_time modification_time_of(o_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* o_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__71_71;
}
static void cont__71_71(void) {
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
static void entry__71_63(void) {
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
  // 557: ... compile_c c_filename o_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_filename */;
  arguments->slots[1] = frame->slots[1] /* o_filename */;
  result_count = frame->caller_result_count;
  myself = var._compile_c;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__71_62(void) {
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
  // 557: ... : compile_c c_filename o_filename
  frame->slots[3] /* temp__1 */ = create_closure(entry__71_63, 0);
  // 557: if do_compile_c: compile_c c_filename o_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* do_compile_c */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__71_64(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // o_info: 0
  frame->slots[0] = myself->closure.frame->slots[5]; /* o_info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 561: last_modification_time.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__last_modification_time();
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__71_65;
}
static void cont__71_65(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 562: modification_time_of(o_info) > last_modification_time
  frame->slots[3] /* temp__3 */ = create_closure(entry__71_66, 0);
  // 560: ||
  // 561:   last_modification_time.is_undefined
  // 562:   modification_time_of(o_info) > last_modification_time
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__71_69;
}
static void entry__71_66(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // o_info: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* o_info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 562: modification_time_of(o_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* o_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__71_67;
}
static void cont__71_67(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 562: modification_time_of(o_info) > last_modification_time
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__last_modification_time();
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__71_68;
}
static void cont__71_68(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 562: modification_time_of(o_info) > last_modification_time
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__71_69(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 563: :
  // 564:   !last_modification_time modification_time_of(o_info)
  frame->slots[4] /* temp__4 */ = create_closure(entry__71_70, 0);
  // 559: if
  // 560:   ||
  // 561:     last_modification_time.is_undefined
  // 562:     modification_time_of(o_info) > last_modification_time
  // 563:   :
  // 564:     !last_modification_time modification_time_of(o_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__71_37(void) {
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
  // 543: ... '/' = "__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = string__71_38;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__71_39;
}
static void cont__71_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 543: ... '.' = "__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__46;
  arguments->slots[1] = string__71_38;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__71_40;
}
static void cont__71_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__2 */ = arguments->slots[0];
  // 543: %sim2c::module_name replace_all(mod_name '/' = "__" '.' = "__")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* mod_name */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  arguments->slots[2] = frame->slots[10] /* temp__2 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__71_41;
}
static void cont__71_41(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(get__sim2c__module_name(), arguments->slots[0]);
  // 544: ... : ewriteln "build module " module_name suffix
  frame->slots[9] /* temp__1 */ = create_closure(entry__71_42, 0);
  // 544: if verbose: ewriteln "build module " module_name suffix
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__71_44;
}
static void entry__71_42(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // suffix: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* suffix */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 544: ... ewriteln "build module " module_name suffix
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__71_43;
  arguments->slots[1] = get__module_name();
  arguments->slots[2] = frame->slots[0] /* suffix */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__71_44(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 545: ... : sim2c sim_filenames
  frame->slots[9] /* temp__1 */ = create_closure(entry__71_45, 0);
  // 545: collect_output $c_source: sim2c sim_filenames
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__71_46;
}
static void entry__71_45(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // sim_filenames: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* sim_filenames */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 545: ... sim2c sim_filenames
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* sim_filenames */;
  result_count = frame->caller_result_count;
  myself = get__sim2c();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__71_46(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[8] /* c_source */, arguments->slots[0]);
  // 546: ... : create_imports c_source
  frame->slots[9] /* temp__1 */ = create_closure(entry__71_47, 0);
  // 546: collect_output !c_buf: create_imports c_source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__71_48;
}
static void entry__71_47(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // c_source: 0
  frame->slots[0] = myself->closure.frame->slots[8]; /* c_source */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 546: ... create_imports c_source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_source */;
  result_count = frame->caller_result_count;
  myself = var._create_imports;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__71_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* c_buf */ = arguments->slots[0];
  // 547: ... c_buf.to_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* c_buf */;
  result_count = 1;
  myself = get__to_utf8();
  func = myself->type;
  frame->cont = cont__71_49;
}
static void cont__71_49(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 547: save c_filename c_buf.to_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* c_filename */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 0;
  myself = get__save();
  func = myself->type;
  frame->cont = cont__71_50;
}
static void cont__71_50(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 548: ... : compile_c c_filename o_filename
  frame->slots[9] /* temp__1 */ = create_closure(entry__71_51, 0);
  // 548: if do_compile_c: compile_c c_filename o_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* do_compile_c */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__71_52;
}
static void entry__71_51(void) {
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
  // 548: ... compile_c c_filename o_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_filename */;
  arguments->slots[1] = frame->slots[1] /* o_filename */;
  result_count = frame->caller_result_count;
  myself = var._compile_c;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__71_52(void) {
  myself = frame->slots[0] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__71_53(void) {
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
  // 550: load !c_buf c_filename
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* c_filename */;
  result_count = 1;
  myself = get__load();
  func = myself->type;
  frame->cont = cont__71_54;
}
static void cont__71_54(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* c_buf */ = arguments->slots[0];
  // 551: $o_info stat(o_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* o_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__71_55;
}
static void cont__71_55(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* o_info */, arguments->slots[0]);
  // 554: o_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* o_info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__71_56;
}
static void cont__71_56(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 555: modification_time_of(c_info) > modification_time_of(o_info)
  frame->slots[8] /* temp__3 */ = create_closure(entry__71_57, 0);
  // 553: ||
  // 554:   o_info.is_undefined
  // 555:   modification_time_of(c_info) > modification_time_of(o_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  arguments->slots[1] = frame->slots[8] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__71_61;
}
static void entry__71_57(void) {
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
  // 555: ... modification_time_of(o_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* o_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__71_58;
}
static void cont__71_58(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 555: modification_time_of(c_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* c_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__71_59;
}
static void cont__71_59(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 555: modification_time_of(c_info) > modification_time_of(o_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__71_60;
}
static void cont__71_60(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 555: modification_time_of(c_info) > modification_time_of(o_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__71_61(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 556: :
  // 557:   if do_compile_c: compile_c c_filename o_filename
  frame->slots[9] /* temp__4 */ = create_closure(entry__71_62, 0);
  // 558: :
  // 559:   if
  // 560:     ||
  // 561:       last_modification_time.is_undefined
  // 562:       modification_time_of(o_info) > last_modification_time
  // 563:     :
  // 564:       !last_modification_time modification_time_of(o_info)
  frame->slots[10] /* temp__5 */ = create_closure(entry__71_64, 0);
  // 552: if
  // 553:   ||
  // 554:     o_info.is_undefined
  // 555:     modification_time_of(c_info) > modification_time_of(o_info)
  // 556:   :
  // 557:     if do_compile_c: compile_c c_filename o_filename
  // 558:   :
  // 559:     if
  // 560:       ||
  // 561:         last_modification_time.is_undefined
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
static void cont__71_72(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 565: build_dependencies mod_filename mod_name c_buf do_compile_c
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
static void cont__71_73(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* mod_info */, arguments->slots[0]);
  // 568: ... mod_info.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* mod_info */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__71_74;
}
static void cont__71_74(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 568: ... :
  // 569:   Error "
  // 570:     No source file(s) for module "@(mod_name)" found!@
  frame->slots[7] /* temp__2 */ = create_closure(entry__71_75, 0);
  // 568: unless mod_info.is_defined:
  // 569:   Error "
  // 570:     No source file(s) for module "@(mod_name)" found!@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__71_79;
}
static void entry__71_75(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // mod_name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* mod_name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 569: ... "
  // 570:   No source file(s) for module "@(mod_name)" found!@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__71_76;
  arguments->slots[1] = frame->slots[0] /* mod_name */;
  arguments->slots[2] = string__71_77;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__71_78;
}
static void cont__71_78(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 569: Error "
  // 570:   No source file(s) for module "@(mod_name)" found!@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__71_79(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 571: $o_filename append(mod_filename ".o")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = string__71_80;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__71_81;
}
static void cont__71_81(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* o_filename */, arguments->slots[0]);
  // 572: ... objects(o_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* o_filename */;
  result_count = 1;
  myself = get__objects();
  func = myself->type;
  frame->cont = cont__71_82;
}
static void cont__71_82(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 572: if objects(o_filename) return
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* return */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__71_83;
}
static void cont__71_83(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 573: !objects(o_filename) true
  frame->slots[6] /* temp__1 */ = get__true();
  // 573: !objects(o_filename)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* o_filename */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = get__objects();
  func = myself->type;
  frame->cont = cont__71_84;
}
static void cont__71_84(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__objects(arguments->slots[0]);
  // 575: mod_info.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* mod_info */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__71_85;
}
static void cont__71_85(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 575: ... :
  // 576:   compile_submodule list(truncate_until(mod_name '/' -1))
  // 577:   if do_list_dependencies: push &dependencies string(mod_filename ".c")
  frame->slots[7] /* temp__2 */ = create_closure(entry__71_86, 0);
  // 578: :
  // 579:   do:
  // 580:     $$best_platform undefined
  // 581:     $$best_priority 999
  // 582:     for_each mod_info: (platform _filenames)
  // 583:       $priority platform_priority(platform)
  // 584:       if priority.is_defined && priority < best_priority:
  // 585:         !best_platform platform
  // 586:         !best_priority priority
  // 587:     for_each mod_info: (platform filenames)
  // ...
  frame->slots[8] /* temp__3 */ = create_closure(entry__71_94, 0);
  // 574: if
  // 575:   mod_info.is_empty:
  // 576:     compile_submodule list(truncate_until(mod_name '/' -1))
  // 577:     if do_list_dependencies: push &dependencies string(mod_filename ".c")
  // 578:   :
  // 579:     do:
  // 580:       $$best_platform undefined
  // 581:       $$best_priority 999
  // 582:       for_each mod_info: (platform _filenames)
  // 583:         $priority platform_priority(platform)
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  arguments->slots[2] = frame->slots[8] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__71_135;
}
static void entry__71_125(void) {
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
  // 607: $$dependency string(mod_filename "-" platform ".c")
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* mod_filename */;
  arguments->slots[1] = string__65_46;
  arguments->slots[2] = frame->slots[0] /* platform */;
  arguments->slots[3] = string__69_9;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__71_126;
}
static void cont__71_126(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* dependency */ = arguments->slots[0];
  // 608: $platforms used_by(platform)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* platform */;
  result_count = 1;
  myself = ((CELL *)frame->slots[3])->contents /* used_by */;
  func = myself->type;
  frame->cont = cont__71_127;
}
static void cont__71_127(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* platforms */, arguments->slots[0]);
  // 609: ... platforms.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* platforms */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__71_128;
}
static void cont__71_128(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 609: ... :
  // 610:   for_each platforms: (plat) write_to &dependency " #" plat
  frame->slots[7] /* temp__2 */ = create_closure(entry__71_129, 0);
  // 609: if platforms.is_defined:
  // 610:   for_each platforms: (plat) write_to &dependency " #" plat
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__71_133;
}
static void entry__71_130(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // plat: 0
  // dependency: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* dependency */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 610: ... write_to &dependency " #" plat
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* dependency */;
  arguments->slots[1] = string__71_131;
  arguments->slots[2] = frame->slots[0] /* plat */;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__71_132;
}
static void cont__71_132(void) {
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
static void entry__71_129(void) {
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
  // 610: ... : (plat) write_to &dependency " #" plat
  frame->slots[2] /* temp__1 */ = create_closure(entry__71_130, 1);
  // 610: for_each platforms: (plat) write_to &dependency " #" plat
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* platforms */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__71_133(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 611: push &dependencies dependency
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._dependencies;
  arguments->slots[1] = ((CELL *)frame->slots[4])->contents /* dependency */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__71_134;
}
static void cont__71_134(void) {
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
static void entry__71_108(void) {
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
  // 593: $$used_by empty_table
  ((CELL *)frame->slots[2])->contents /* used_by */ = get__empty_table();
  // 594: ... : (supported_platform _parent_platform)
  // 595:   $$best_platform undefined
  // 596:   $$best_priority 999
  // 597:   for_each mod_info: (platform _filenames)
  // 598:     $priority platform_specific_priority(supported_platform platform)
  // 599:     if priority.is_defined && priority < best_priority:
  // 600:       !best_platform platform
  // 601:       !best_priority priority
  // 602:   if best_platform.is_defined:
  // 603:     $$ub default_value(used_by(best_platform) empty_list)
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__71_109, 2);
  // 594: for_each supported_platforms: (supported_platform _parent_platform)
  // 595:   $$best_platform undefined
  // 596:   $$best_priority 999
  // 597:   for_each mod_info: (platform _filenames)
  // 598:     $priority platform_specific_priority(supported_platform platform)
  // 599:     if priority.is_defined && priority < best_priority:
  // 600:       !best_platform platform
  // 601:       !best_priority priority
  // 602:   if best_platform.is_defined:
  // 603:     $$ub default_value(used_by(best_platform) empty_list)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._supported_platforms;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__71_124;
}
static void entry__71_119(void) {
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
  // 603: ... used_by(best_platform)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* best_platform */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* used_by */;
  func = myself->type;
  frame->cont = cont__71_120;
}
static void cont__71_120(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 603: $$ub default_value(used_by(best_platform) empty_list)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = get__empty_list();
  result_count = 1;
  myself = get__default_value();
  func = myself->type;
  frame->cont = cont__71_121;
}
static void cont__71_121(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* ub */ = arguments->slots[0];
  // 604: push &ub supported_platform
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* ub */;
  arguments->slots[1] = frame->slots[2] /* supported_platform */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__71_122;
}
static void cont__71_122(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* ub */ = arguments->slots[0];
  // 605: !used_by(best_platform) ub
  frame->slots[4] /* temp__1 */ = ((CELL *)frame->slots[3])->contents /* ub */;
  // 605: !used_by(best_platform)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* best_platform */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* used_by */;
  func = myself->type;
  frame->cont = cont__71_123;
}
static void cont__71_123(void) {
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
static void entry__71_109(void) {
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
  // 595: $$best_platform undefined
  ((CELL *)frame->slots[4])->contents /* best_platform */ = get__undefined();
  // 596: $$best_priority 999
  ((CELL *)frame->slots[5])->contents /* best_priority */ = number__999;
  // 597: ... : (platform _filenames)
  // 598:   $priority platform_specific_priority(supported_platform platform)
  // 599:   if priority.is_defined && priority < best_priority:
  // 600:     !best_platform platform
  // 601:     !best_priority priority
  frame->slots[6] /* temp__1 */ = create_closure(entry__71_110, 2);
  // 597: for_each mod_info: (platform _filenames)
  // 598:   $priority platform_specific_priority(supported_platform platform)
  // 599:   if priority.is_defined && priority < best_priority:
  // 600:     !best_platform platform
  // 601:     !best_priority priority
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* mod_info */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__71_117;
}
static void entry__71_116(void) {
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
  // 600: !best_platform platform
  ((CELL *)frame->slots[0])->contents /* best_platform */ = frame->slots[1] /* platform */;
  // 601: !best_priority priority
  ((CELL *)frame->slots[2])->contents /* best_priority */ = frame->slots[3] /* priority */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__71_110(void) {
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
  // 598: $priority platform_specific_priority(supported_platform platform)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* supported_platform */;
  arguments->slots[1] = frame->slots[0] /* platform */;
  result_count = 1;
  myself = var._platform_specific_priority;
  func = myself->type;
  frame->cont = cont__71_111;
}
static void cont__71_111(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* priority */, arguments->slots[0]);
  // 599: ... priority.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* priority */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__71_112;
}
static void cont__71_112(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 599: ... priority < best_priority
  frame->slots[8] /* temp__3 */ = create_closure(entry__71_113, 0);
  // 599: ... priority.is_defined && priority < best_priority
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  arguments->slots[1] = frame->slots[8] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__71_115;
}
static void entry__71_113(void) {
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
  // 599: ... priority < best_priority
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* priority */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* best_priority */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__71_114;
}
static void cont__71_114(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 599: ... priority < best_priority
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__71_115(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 599: ... :
  // 600:   !best_platform platform
  // 601:   !best_priority priority
  frame->slots[9] /* temp__4 */ = create_closure(entry__71_116, 0);
  // 599: if priority.is_defined && priority < best_priority:
  // 600:   !best_platform platform
  // 601:   !best_priority priority
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__71_117(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 602: ... best_platform.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* best_platform */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__71_118;
}
static void cont__71_118(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 602: ... :
  // 603:   $$ub default_value(used_by(best_platform) empty_list)
  // 604:   push &ub supported_platform
  // 605:   !used_by(best_platform) ub
  frame->slots[7] /* temp__2 */ = create_closure(entry__71_119, 0);
  // 602: if best_platform.is_defined:
  // 603:   $$ub default_value(used_by(best_platform) empty_list)
  // 604:   push &ub supported_platform
  // 605:   !used_by(best_platform) ub
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__71_124(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 606: ... : (platform _filenames)
  // 607:   $$dependency string(mod_filename "-" platform ".c")
  // 608:   $platforms used_by(platform)
  // 609:   if platforms.is_defined:
  // 610:     for_each platforms: (plat) write_to &dependency " #" plat
  // 611:   push &dependencies dependency
  frame->slots[3] /* temp__1 */ = create_closure(entry__71_125, 2);
  // 606: for_each mod_info: (platform _filenames)
  // 607:   $$dependency string(mod_filename "-" platform ".c")
  // 608:   $platforms used_by(platform)
  // 609:   if platforms.is_defined:
  // 610:     for_each platforms: (plat) write_to &dependency " #" plat
  // 611:   push &dependencies dependency
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_info */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__71_91(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // mod_filename: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* mod_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 577: ... string(mod_filename ".c")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = string__69_9;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__71_92;
}
static void cont__71_92(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 577: ... push &dependencies string(mod_filename ".c")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._dependencies;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__71_93;
}
static void cont__71_93(void) {
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
static void entry__71_86(void) {
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
  // 576: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__71_87;
}
static void cont__71_87(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 576: ... truncate_until(mod_name '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* mod_name */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__71_88;
}
static void cont__71_88(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 576: ... list(truncate_until(mod_name '/' -1))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__71_89;
}
static void cont__71_89(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 576: compile_submodule list(truncate_until(mod_name '/' -1))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = frame->slots[0] /* compile_submodule */;
  func = myself->type;
  frame->cont = cont__71_90;
}
static void cont__71_90(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 577: ... : push &dependencies string(mod_filename ".c")
  frame->slots[3] /* temp__1 */ = create_closure(entry__71_91, 0);
  // 577: if do_list_dependencies: push &dependencies string(mod_filename ".c")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_list_dependencies;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__71_94(void) {
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
  // 579: ... :
  // 580:   $$best_platform undefined
  // 581:   $$best_priority 999
  // 582:   for_each mod_info: (platform _filenames)
  // 583:     $priority platform_priority(platform)
  // 584:     if priority.is_defined && priority < best_priority:
  // 585:       !best_platform platform
  // 586:       !best_priority priority
  // 587:   for_each mod_info: (platform filenames)
  // 588:     compile_submodule
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__71_95, 0);
  // 579: do:
  // 580:   $$best_platform undefined
  // 581:   $$best_priority 999
  // 582:   for_each mod_info: (platform _filenames)
  // 583:     $priority platform_priority(platform)
  // 584:     if priority.is_defined && priority < best_priority:
  // 585:       !best_platform platform
  // 586:       !best_priority priority
  // 587:   for_each mod_info: (platform filenames)
  // 588:     compile_submodule
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__71_107;
}
static void entry__71_104(void) {
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
  // 590: platform == best_platform
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* platform */;
  arguments->slots[1] = ((CELL *)frame->slots[3])->contents /* best_platform */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__71_105;
}
static void cont__71_105(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 591: string("-" platform)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__65_46;
  arguments->slots[1] = frame->slots[0] /* platform */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__71_106;
}
static void cont__71_106(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 588: compile_submodule
  // 589:   filenames
  // 590:   platform == best_platform
  // 591:   string("-" platform)
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
static void entry__71_95(void) {
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
  // 580: $$best_platform undefined
  ((CELL *)frame->slots[2])->contents /* best_platform */ = get__undefined();
  // 581: $$best_priority 999
  ((CELL *)frame->slots[3])->contents /* best_priority */ = number__999;
  // 582: ... : (platform _filenames)
  // 583:   $priority platform_priority(platform)
  // 584:   if priority.is_defined && priority < best_priority:
  // 585:     !best_platform platform
  // 586:     !best_priority priority
  frame->slots[4] /* temp__1 */ = create_closure(entry__71_96, 2);
  // 582: for_each mod_info: (platform _filenames)
  // 583:   $priority platform_priority(platform)
  // 584:   if priority.is_defined && priority < best_priority:
  // 585:     !best_platform platform
  // 586:     !best_priority priority
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_info */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__71_103;
}
static void entry__71_102(void) {
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
  // 585: !best_platform platform
  ((CELL *)frame->slots[0])->contents /* best_platform */ = frame->slots[1] /* platform */;
  // 586: !best_priority priority
  ((CELL *)frame->slots[2])->contents /* best_priority */ = frame->slots[3] /* priority */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__71_96(void) {
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
  // 583: $priority platform_priority(platform)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* platform */;
  result_count = 1;
  myself = var._platform_priority;
  func = myself->type;
  frame->cont = cont__71_97;
}
static void cont__71_97(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* priority */, arguments->slots[0]);
  // 584: ... priority.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* priority */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__71_98;
}
static void cont__71_98(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 584: ... priority < best_priority
  frame->slots[7] /* temp__3 */ = create_closure(entry__71_99, 0);
  // 584: ... priority.is_defined && priority < best_priority
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__71_101;
}
static void entry__71_99(void) {
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
  // 584: ... priority < best_priority
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* priority */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* best_priority */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__71_100;
}
static void cont__71_100(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 584: ... priority < best_priority
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__71_101(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 584: ... :
  // 585:   !best_platform platform
  // 586:   !best_priority priority
  frame->slots[8] /* temp__4 */ = create_closure(entry__71_102, 0);
  // 584: if priority.is_defined && priority < best_priority:
  // 585:   !best_platform platform
  // 586:   !best_priority priority
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__71_103(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 587: ... : (platform filenames)
  // 588:   compile_submodule
  // 589:     filenames
  // 590:     platform == best_platform
  // 591:     string("-" platform)
  frame->slots[4] /* temp__1 */ = create_closure(entry__71_104, 2);
  // 587: for_each mod_info: (platform filenames)
  // 588:   compile_submodule
  // 589:     filenames
  // 590:     platform == best_platform
  // 591:     string("-" platform)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_info */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__71_107(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 592: ... :
  // 593:   $$used_by empty_table
  // 594:   for_each supported_platforms: (supported_platform _parent_platform)
  // 595:     $$best_platform undefined
  // 596:     $$best_priority 999
  // 597:     for_each mod_info: (platform _filenames)
  // 598:       $priority platform_specific_priority(supported_platform platform)
  // 599:       if priority.is_defined && priority < best_priority:
  // 600:         !best_platform platform
  // 601:         !best_priority priority
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__71_108, 0);
  // 592: if do_list_dependencies:
  // 593:   $$used_by empty_table
  // 594:   for_each supported_platforms: (supported_platform _parent_platform)
  // 595:     $$best_platform undefined
  // 596:     $$best_priority 999
  // 597:     for_each mod_info: (platform _filenames)
  // 598:       $priority platform_specific_priority(supported_platform platform)
  // 599:       if priority.is_defined && priority < best_priority:
  // 600:         !best_platform platform
  // 601:         !best_priority priority
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
static void cont__71_135(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__72_8(void) {
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
  frame->cont = cont__72_9;
}
static void cont__72_9(void) {
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
  frame->cont = cont__72_10;
}
static void cont__72_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 622: compile_module string(path '/' name) string(mod_path '/' name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = var._compile_module;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__72_1_compile_modules(void) {
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
  // 618: ... string(mod_path '/')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* mod_path */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__72_2;
}
static void cont__72_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 618: add_module_infos $directories $modules path string(mod_path '/')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* path */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 2;
  myself = var._add_module_infos;
  func = myself->type;
  frame->cont = cont__72_3;
}
static void cont__72_3(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  frame->slots[6] /* temp__3 */ = arguments->slots[1];
  // 618: ... directories
  initialize_future(frame->slots[2] /* directories */, frame->slots[5] /* temp__2 */);
  // 618: ... modules
  initialize_future(frame->slots[3] /* modules */, frame->slots[6] /* temp__3 */);
  // 619: ... : (name)
  // 620:   compile_modules string(path '/' name) string(mod_path '/' name)
  frame->slots[4] /* temp__1 */ = create_closure(entry__72_4, 1);
  // 619: for_each directories: (name)
  // 620:   compile_modules string(path '/' name) string(mod_path '/' name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* directories */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__72_7;
}
static void entry__72_4(void) {
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
  // 620: ... string(path '/' name)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* path */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__72_5;
}
static void cont__72_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 620: ... string(mod_path '/' name)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* mod_path */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__72_6;
}
static void cont__72_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 620: compile_modules string(path '/' name) string(mod_path '/' name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = var._compile_modules;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__72_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 621: ... : (name)
  // 622:   compile_module string(path '/' name) string(mod_path '/' name)
  frame->slots[4] /* temp__1 */ = create_closure(entry__72_8, 1);
  // 621: for_each modules: (name)
  // 622:   compile_module string(path '/' name) string(mod_path '/' name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* modules */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__74_2(void) {
  allocate_initialized_frame_gc(0, 3);
  // slot allocations:
  // path: 0
  frame->slots[0] /* path */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 630: $path environment("LD_LIBRARY_PATH")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__74_3;
  result_count = 1;
  myself = get__environment();
  func = myself->type;
  frame->cont = cont__74_4;
}
static void cont__74_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[0] /* path */, arguments->slots[0]);
  // 631: ... path.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* path */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__74_5;
}
static void cont__74_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 631: ... : ewriteln "LD_LIBRARY_PATH=@(path)"
  frame->slots[2] /* temp__2 */ = create_closure(entry__74_6, 0);
  // 631: if path.is_defined: ewriteln "LD_LIBRARY_PATH=@(path)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__74_9;
}
static void entry__74_6(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // path: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* path */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 631: ... "LD_LIBRARY_PATH=@(path)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__74_7;
  arguments->slots[1] = frame->slots[0] /* path */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__74_8;
}
static void cont__74_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 631: ... ewriteln "LD_LIBRARY_PATH=@(path)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__74_9(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 632: ... serialize(objects)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__objects();
  result_count = 1;
  myself = get__serialize();
  func = myself->type;
  frame->cont = cont__74_10;
}
static void cont__74_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 632: ewriteln "included object files: " serialize(objects)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__74_11;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 0;
  myself = get__ewriteln();
  func = myself->type;
  frame->cont = cont__74_12;
}
static void cont__74_12(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 633: ... serialize(libraries)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__libraries();
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
  // 633: ewriteln "needed libraries: " serialize(libraries)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__74_14;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__74_1_show_file_list(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 629: if do_show_debug_infos:
  // 630:   $path environment("LD_LIBRARY_PATH")
  // 631:   if path.is_defined: ewriteln "LD_LIBRARY_PATH=@(path)"
  // 632:   ewriteln "included object files: " serialize(objects)
  // 633:   ewriteln "needed libraries: " serialize(libraries)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_show_debug_infos();
  arguments->slots[1] = func__74_2;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__75_1_library_paths_and_file_list(void) {
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
  // 636: show_file_list
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._show_file_list;
  func = myself->type;
  frame->cont = cont__75_2;
}
static void cont__75_2(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 637: $$library_paths empty_list
  ((CELL *)frame->slots[0])->contents /* library_paths */ = get__empty_list();
  // 638: $$object_files empty_list
  ((CELL *)frame->slots[1])->contents /* object_files */ = get__empty_list();
  // 639: $$library_files empty_list
  ((CELL *)frame->slots[2])->contents /* library_files */ = get__empty_list();
  // 640: $paths environment("LD_LIBRARY_PATH")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__74_3;
  result_count = 1;
  myself = get__environment();
  func = myself->type;
  frame->cont = cont__75_3;
}
static void cont__75_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* paths */, arguments->slots[0]);
  // 641: ... paths.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* paths */;
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
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 641: ... :
  // 642:   for_each paths .split. ':': (path) push &library_paths "-L@(path)"
  frame->slots[5] /* temp__2 */ = create_closure(entry__75_5, 0);
  // 641: if paths.is_defined:
  // 642:   for_each paths .split. ':': (path) push &library_paths "-L@(path)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__75_11;
}
static void entry__75_7(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // path: 0
  // library_paths: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* library_paths */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 642: ... "-L@(path)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__75_8;
  arguments->slots[1] = frame->slots[0] /* path */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__75_9;
}
static void cont__75_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 642: ... push &library_paths "-L@(path)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* library_paths */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__75_10;
}
static void cont__75_10(void) {
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
static void entry__75_5(void) {
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
  // 642: ... paths .split. ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* paths */;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__split();
  func = myself->type;
  frame->cont = cont__75_6;
}
static void cont__75_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 642: ... : (path) push &library_paths "-L@(path)"
  frame->slots[3] /* temp__2 */ = create_closure(entry__75_7, 1);
  // 642: for_each paths .split. ':': (path) push &library_paths "-L@(path)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__75_11(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 643: ... : ewriteln "library paths: " serialize(library_paths)
  frame->slots[4] /* temp__1 */ = create_closure(entry__75_12, 0);
  // 643: if do_show_debug_infos: ewriteln "library paths: " serialize(library_paths)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_show_debug_infos();
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__75_15;
}
static void entry__75_12(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // library_paths: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* library_paths */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 643: ... serialize(library_paths)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* library_paths */;
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
  // 643: ... ewriteln "library paths: " serialize(library_paths)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__75_14;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__75_15(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 644: ... : (object) push &object_files object
  frame->slots[4] /* temp__1 */ = create_closure(entry__75_16, 1);
  // 644: for_each objects: (object) push &object_files object
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__objects();
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__75_18;
}
static void entry__75_16(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // object: 0
  // object_files: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* object_files */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 644: ... push &object_files object
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* object_files */;
  arguments->slots[1] = frame->slots[0] /* object */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__75_17;
}
static void cont__75_17(void) {
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
static void cont__75_18(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 645: ... : (library)
  // 646:   push
  // 647:     &library_files
  // 648:     if
  // 649:       library .has_prefix. "sim-"
  // 650:       ->
  // 651:         if
  // 652:           current_platform == "linux"
  // 653:           -> "-l:lib@(library).so.@(MAJOR)"
  // 654:           -> "-l@(library)-@(MAJOR)"
  // ...
  frame->slots[4] /* temp__1 */ = create_closure(entry__75_19, 1);
  // 645: for_each libraries: (library)
  // 646:   push
  // 647:     &library_files
  // 648:     if
  // 649:       library .has_prefix. "sim-"
  // 650:       ->
  // 651:         if
  // 652:           current_platform == "linux"
  // 653:           -> "-l:lib@(library).so.@(MAJOR)"
  // 654:           -> "-l@(library)-@(MAJOR)"
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__libraries();
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__75_43;
}
static void entry__75_19(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // library: 0
  // library_files: 1
  frame->slots[1] = myself->closure.frame->slots[2]; /* library_files */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 649: library .has_prefix. "sim-"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* library */;
  arguments->slots[1] = string__70_32;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__75_20;
}
static void cont__75_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 650: ->
  // 651:   if
  // 652:     current_platform == "linux"
  // 653:     -> "-l:lib@(library).so.@(MAJOR)"
  // 654:     -> "-l@(library)-@(MAJOR)"
  frame->slots[4] /* temp__3 */ = create_closure(entry__75_21, 0);
  // 655: ->
  // 656:   if
  // 657:     library .contains. '.'
  // 658:     -> "-l:lib@(library .before. '.').so.@(library .behind. '.')"
  // 659:       # Linux only
  // 660:     -> "-l@(library)"
  frame->slots[5] /* temp__4 */ = create_closure(entry__75_32, 0);
  // 648: if
  // 649:   library .has_prefix. "sim-"
  // 650:   ->
  // 651:     if
  // 652:       current_platform == "linux"
  // 653:       -> "-l:lib@(library).so.@(MAJOR)"
  // 654:       -> "-l@(library)-@(MAJOR)"
  // 655:   ->
  // 656:     if
  // 657:       library .contains. '.'
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  arguments->slots[2] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__75_41;
}
static void entry__75_21(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // library: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* library */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 652: current_platform == "linux"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__current_platform();
  arguments->slots[1] = string__75_22;
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
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 653: -> "-l:lib@(library).so.@(MAJOR)"
  frame->slots[3] /* temp__3 */ = create_closure(entry__75_24, 0);
  // 654: -> "-l@(library)-@(MAJOR)"
  frame->slots[4] /* temp__4 */ = create_closure(entry__75_28, 0);
  // 651: if
  // 652:   current_platform == "linux"
  // 653:   -> "-l:lib@(library).so.@(MAJOR)"
  // 654:   -> "-l@(library)-@(MAJOR)"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  arguments->slots[2] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__75_31;
}
static void entry__75_24(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // library: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* library */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 653: ... "-l:lib@(library).so.@(MAJOR)"
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__75_25;
  arguments->slots[1] = frame->slots[0] /* library */;
  arguments->slots[2] = string__75_26;
  arguments->slots[3] = var._MAJOR;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__75_27;
}
static void cont__75_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 653: -> "-l:lib@(library).so.@(MAJOR)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__75_28(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // library: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* library */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 654: ... "-l@(library)-@(MAJOR)"
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__75_29;
  arguments->slots[1] = frame->slots[0] /* library */;
  arguments->slots[2] = string__65_46;
  arguments->slots[3] = var._MAJOR;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__75_30;
}
static void cont__75_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 654: -> "-l@(library)-@(MAJOR)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__75_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 650: ->
  // 651:   if
  // 652:     current_platform == "linux"
  // 653:     -> "-l:lib@(library).so.@(MAJOR)"
  // 654:     -> "-l@(library)-@(MAJOR)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__75_32(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // library: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* library */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 657: library .contains. '.'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* library */;
  arguments->slots[1] = character__46;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__75_33;
}
static void cont__75_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 658: -> "-l:lib@(library .before. '.').so.@(library .behind. '.')"
  // 659:   # Linux only
  frame->slots[3] /* temp__3 */ = create_closure(entry__75_34, 0);
  // 660: -> "-l@(library)"
  frame->slots[4] /* temp__4 */ = create_closure(entry__75_38, 0);
  // 656: if
  // 657:   library .contains. '.'
  // 658:   -> "-l:lib@(library .before. '.').so.@(library .behind. '.')"
  // 659:     # Linux only
  // 660:   -> "-l@(library)"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  arguments->slots[2] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__75_40;
}
static void entry__75_34(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // library: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* library */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 658: ... library .before. '.'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* library */;
  arguments->slots[1] = character__46;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__75_35;
}
static void cont__75_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 658: ... library .behind. '.'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* library */;
  arguments->slots[1] = character__46;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__75_36;
}
static void cont__75_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 658: ... "-l:lib@(library .before. '.').so.@(library .behind. '.')"
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__75_25;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  arguments->slots[2] = string__75_26;
  arguments->slots[3] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__75_37;
}
static void cont__75_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 658: -> "-l:lib@(library .before. '.').so.@(library .behind. '.')"
  // 659:   # Linux only
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__75_38(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // library: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* library */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 660: ... "-l@(library)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__75_29;
  arguments->slots[1] = frame->slots[0] /* library */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__75_39;
}
static void cont__75_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 660: -> "-l@(library)"
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
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 655: ->
  // 656:   if
  // 657:     library .contains. '.'
  // 658:     -> "-l:lib@(library .before. '.').so.@(library .behind. '.')"
  // 659:       # Linux only
  // 660:     -> "-l@(library)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__75_41(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 646: push
  // 647:   &library_files
  // 648:   if
  // 649:     library .has_prefix. "sim-"
  // 650:     ->
  // 651:       if
  // 652:         current_platform == "linux"
  // 653:         -> "-l:lib@(library).so.@(MAJOR)"
  // 654:         -> "-l@(library)-@(MAJOR)"
  // 655:     ->
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* library_files */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__75_42;
}
static void cont__75_42(void) {
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
static void cont__75_43(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 661: ... append(object_files library_files)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* object_files */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* library_files */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__75_44;
}
static void cont__75_44(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 661: append library_paths append(object_files library_files)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* library_paths */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__append();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__76_74(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 704: ... write_timing_info "collecting imports"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__76_75;
  result_count = frame->caller_result_count;
  myself = get__write_timing_info();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__76_1_create_imports(void) {
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
  // 666: ... : (buf)
  // 667:   $$s undefined
  // 668:   for_each buf: (idx chr)
  // 669:     if
  // 670:       s.is_defined:
  // 671:         unless chr.is_a_letter || chr == '_' || chr.is_a_digit:
  // 672:           $symbol range(buf s idx-1)
  // 673:           !s undefined
  // 674:           unless already_checked(symbol):
  // 675:             !already_checked(symbol) true
  // ...
  frame->slots[5] /* temp__1 */ = create_closure(entry__76_2_collect_declarations, 1);
  // 666: $collect_declarations: (buf)
  // 667:   $$s undefined
  // 668:   for_each buf: (idx chr)
  // 669:     if
  // 670:       s.is_defined:
  // 671:         unless chr.is_a_letter || chr == '_' || chr.is_a_digit:
  // 672:           $symbol range(buf s idx-1)
  // 673:           !s undefined
  // 674:           unless already_checked(symbol):
  // 675:             !already_checked(symbol) true
  // ...
  initialize_future(frame->slots[2] /* collect_declarations */, frame->slots[5] /* temp__1 */);
  // 664: $$already_checked empty_set
  ((CELL *)frame->slots[1])->contents /* already_checked */ = get__empty_set();
  // 699: ... : collect_declarations source
  frame->slots[5] /* temp__1 */ = create_closure(entry__76_63, 0);
  // 699: collect_output $imports: collect_declarations source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__76_64;
}
static void entry__76_62(void) {
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
  // 697: ... !s idx
  ((CELL *)frame->slots[0])->contents /* s */ = frame->slots[1] /* idx */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__76_21(void) {
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
  // 680: declaration(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* declaration */;
  func = myself->type;
  frame->cont = cont__76_22;
}
static void cont__76_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 680: declaration(1) != '#'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  arguments->slots[1] = character__35;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__76_23;
}
static void cont__76_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 680: declaration(1) != '#'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__76_24;
}
static void cont__76_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  frame->slots[6] /* temp__4 */ = create_closure(entry__76_25, 0);
  // 678: $do_import
  // 679:   &&
  // 680:     declaration(1) != '#'
  // 681:     not(declaration .has_prefix. "typedef")
  // 682:     not(declaration .has_prefix. "REGISTER")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__76_34;
}
static void entry__76_25(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // declaration: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* declaration */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 681: ... declaration .has_prefix. "typedef"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* declaration */;
  arguments->slots[1] = string__76_26;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__76_27;
}
static void cont__76_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 681: not(declaration .has_prefix. "typedef")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__not();
  func = myself->type;
  frame->cont = cont__76_28;
}
static void cont__76_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 682: not(declaration .has_prefix. "REGISTER")
  frame->slots[4] /* temp__4 */ = create_closure(entry__76_29, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__76_33;
}
static void entry__76_29(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // declaration: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* declaration */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 682: ... declaration .has_prefix. "REGISTER"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* declaration */;
  arguments->slots[1] = string__76_30;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__76_31;
}
static void cont__76_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 682: not(declaration .has_prefix. "REGISTER")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__not();
  func = myself->type;
  frame->cont = cont__76_32;
}
static void cont__76_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 682: not(declaration .has_prefix. "REGISTER")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__76_33(void) {
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
static void cont__76_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* do_import */, arguments->slots[0]);
  // 685: ->
  // 686:   declaration(1) == '#' || declaration .has_prefix. "REGISTER"
  // 687:   :
  // 688:     collect_declarations declaration .truncate_from. '{'
  frame->slots[3] /* temp__1 */ = create_closure(entry__76_35, 0);
  // 689: -> declaration .has_prefix. "typedef struct":
  // 690:   for_each_line between(declaration '{' '}').trim: (line)
  // 691:     collect_declarations until(line ' ' -1)
  frame->slots[4] /* temp__2 */ = create_closure(entry__76_43, 0);
  // 692: :
  // 693:   collect_declarations declaration
  frame->slots[5] /* temp__3 */ = create_closure(entry__76_52, 0);
  // 684: cond
  // 685:   ->
  // 686:     declaration(1) == '#' || declaration .has_prefix. "REGISTER"
  // 687:     :
  // 688:       collect_declarations declaration .truncate_from. '{'
  // 689:   -> declaration .has_prefix. "typedef struct":
  // 690:     for_each_line between(declaration '{' '}').trim: (line)
  // 691:       collect_declarations until(line ' ' -1)
  // 692:   :
  // 693:     collect_declarations declaration
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = frame->slots[5] /* temp__3 */;
  result_count = 0;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__76_53;
}
static void entry__76_49(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // line: 0
  // collect_declarations: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* collect_declarations */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 691: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__76_50;
}
static void cont__76_50(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 691: ... until(line ' ' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* line */;
  arguments->slots[1] = character__32;
  arguments->slots[2] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__until();
  func = myself->type;
  frame->cont = cont__76_51;
}
static void cont__76_51(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 691: collect_declarations until(line ' ' -1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* collect_declarations */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__76_46(void) {
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
  // 690: ... between(declaration '{' '}')
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* declaration */;
  arguments->slots[1] = character__123;
  arguments->slots[2] = character__125;
  result_count = 1;
  myself = get__between();
  func = myself->type;
  frame->cont = cont__76_47;
}
static void cont__76_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 690: ... between(declaration '{' '}').trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__76_48;
}
static void cont__76_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 690: ... : (line)
  // 691:   collect_declarations until(line ' ' -1)
  frame->slots[4] /* temp__3 */ = create_closure(entry__76_49, 1);
  // 690: for_each_line between(declaration '{' '}').trim: (line)
  // 691:   collect_declarations until(line ' ' -1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__for_each_line();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__76_41(void) {
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
  // 688: ... declaration .truncate_from. '{'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* declaration */;
  arguments->slots[1] = character__123;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__76_42;
}
static void cont__76_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 688: collect_declarations declaration .truncate_from. '{'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* collect_declarations */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__76_35(void) {
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
  // 686: declaration(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* declaration */;
  func = myself->type;
  frame->cont = cont__76_36;
}
static void cont__76_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 686: declaration(1) == '#'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  arguments->slots[1] = character__35;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__76_37;
}
static void cont__76_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 686: ... declaration .has_prefix. "REGISTER"
  frame->slots[5] /* temp__4 */ = create_closure(entry__76_38, 0);
  // 686: declaration(1) == '#' || declaration .has_prefix. "REGISTER"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__76_40;
}
static void entry__76_38(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // declaration: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* declaration */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 686: ... declaration .has_prefix. "REGISTER"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* declaration */;
  arguments->slots[1] = string__76_30;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__76_39;
}
static void cont__76_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 686: ... declaration .has_prefix. "REGISTER"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__76_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 687: :
  // 688:   collect_declarations declaration .truncate_from. '{'
  frame->slots[6] /* temp__5 */ = create_closure(entry__76_41, 0);
  // 685: ->
  // 686:   declaration(1) == '#' || declaration .has_prefix. "REGISTER"
  // 687:   :
  // 688:     collect_declarations declaration .truncate_from. '{'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__5 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__76_43(void) {
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
  // 689: ... declaration .has_prefix. "typedef struct"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* declaration */;
  arguments->slots[1] = string__76_44;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__76_45;
}
static void cont__76_45(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 689: ... :
  // 690:   for_each_line between(declaration '{' '}').trim: (line)
  // 691:     collect_declarations until(line ' ' -1)
  frame->slots[3] /* temp__2 */ = create_closure(entry__76_46, 0);
  // 689: -> declaration .has_prefix. "typedef struct":
  // 690:   for_each_line between(declaration '{' '}').trim: (line)
  // 691:     collect_declarations until(line ' ' -1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__76_52(void) {
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
  // 693: collect_declarations declaration
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* declaration */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* collect_declarations */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__76_53(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 694: if do_import: write "IMPORT "
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* do_import */;
  arguments->slots[1] = func__76_54;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__76_56;
}
static void entry__76_54(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 694: ... write "IMPORT "
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__76_55;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__76_56(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 695: write declaration
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* declaration */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__76_17(void) {
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
  // 675: !already_checked(symbol) true
  frame->slots[4] /* temp__1 */ = get__true();
  // 675: !already_checked(symbol)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* symbol */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* already_checked */;
  func = myself->type;
  frame->cont = cont__76_18;
}
static void cont__76_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* already_checked */ = arguments->slots[0];
  // 676: $declaration runtime_symbols(symbol)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* symbol */;
  result_count = 1;
  myself = get__runtime_symbols();
  func = myself->type;
  frame->cont = cont__76_19;
}
static void cont__76_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* declaration */, arguments->slots[0]);
  // 677: ... declaration.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* declaration */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__76_20;
}
static void cont__76_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 677: ... :
  // 678:   $do_import
  // 679:     &&
  // 680:       declaration(1) != '#'
  // 681:       not(declaration .has_prefix. "typedef")
  // 682:       not(declaration .has_prefix. "REGISTER")
  // 683:   
  // 684:   cond
  // 685:     ->
  // 686:       declaration(1) == '#' || declaration .has_prefix. "REGISTER"
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__76_21, 0);
  // 677: if declaration.is_defined:
  // 678:   $do_import
  // 679:     &&
  // 680:       declaration(1) != '#'
  // 681:       not(declaration .has_prefix. "typedef")
  // 682:       not(declaration .has_prefix. "REGISTER")
  // 683:   
  // 684:   cond
  // 685:     ->
  // 686:       declaration(1) == '#' || declaration .has_prefix. "REGISTER"
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
static void entry__76_13(void) {
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
  // 672: ... idx-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* idx */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__76_14;
}
static void cont__76_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 672: $symbol range(buf s idx-1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* buf */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* s */;
  arguments->slots[2] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__76_15;
}
static void cont__76_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* symbol */, arguments->slots[0]);
  // 673: !s undefined
  ((CELL *)frame->slots[1])->contents /* s */ = get__undefined();
  // 674: ... already_checked(symbol)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* symbol */;
  result_count = 1;
  myself = ((CELL *)frame->slots[3])->contents /* already_checked */;
  func = myself->type;
  frame->cont = cont__76_16;
}
static void cont__76_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 674: ... :
  // 675:   !already_checked(symbol) true
  // 676:   $declaration runtime_symbols(symbol)
  // 677:   if declaration.is_defined:
  // 678:     $do_import
  // 679:       &&
  // 680:         declaration(1) != '#'
  // 681:         not(declaration .has_prefix. "typedef")
  // 682:         not(declaration .has_prefix. "REGISTER")
  // 683:     
  // ...
  frame->slots[7] /* temp__2 */ = create_closure(entry__76_17, 0);
  // 674: unless already_checked(symbol):
  // 675:   !already_checked(symbol) true
  // 676:   $declaration runtime_symbols(symbol)
  // 677:   if declaration.is_defined:
  // 678:     $do_import
  // 679:       &&
  // 680:         declaration(1) != '#'
  // 681:         not(declaration .has_prefix. "typedef")
  // 682:         not(declaration .has_prefix. "REGISTER")
  // 683:     
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
static void entry__76_5(void) {
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
  // 671: ... chr.is_a_letter
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  result_count = 1;
  myself = get__is_a_letter();
  func = myself->type;
  frame->cont = cont__76_6;
}
static void cont__76_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 671: ... chr == '_' || chr.is_a_digit
  frame->slots[8] /* temp__3 */ = create_closure(entry__76_7, 0);
  // 671: ... chr.is_a_letter || chr == '_' || chr.is_a_digit
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  arguments->slots[1] = frame->slots[8] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__76_12;
}
static void entry__76_7(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 671: ... chr == '_'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__95;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__76_8;
}
static void cont__76_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 671: ... chr.is_a_digit
  frame->slots[3] /* temp__3 */ = create_closure(entry__76_9, 0);
  // 671: ... chr == '_' || chr.is_a_digit
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__76_11;
}
static void entry__76_9(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 671: ... chr.is_a_digit
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  result_count = 1;
  myself = get__is_a_digit();
  func = myself->type;
  frame->cont = cont__76_10;
}
static void cont__76_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 671: ... chr.is_a_digit
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__76_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 671: ... chr == '_' || chr.is_a_digit
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__76_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 671: ... :
  // 672:   $symbol range(buf s idx-1)
  // 673:   !s undefined
  // 674:   unless already_checked(symbol):
  // 675:     !already_checked(symbol) true
  // 676:     $declaration runtime_symbols(symbol)
  // 677:     if declaration.is_defined:
  // 678:       $do_import
  // 679:         &&
  // 680:           declaration(1) != '#'
  // ...
  frame->slots[9] /* temp__4 */ = create_closure(entry__76_13, 0);
  // 671: unless chr.is_a_letter || chr == '_' || chr.is_a_digit:
  // 672:   $symbol range(buf s idx-1)
  // 673:   !s undefined
  // 674:   unless already_checked(symbol):
  // 675:     !already_checked(symbol) true
  // 676:     $declaration runtime_symbols(symbol)
  // 677:     if declaration.is_defined:
  // 678:       $do_import
  // 679:         &&
  // 680:           declaration(1) != '#'
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
static void entry__76_57(void) {
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
  // 697: ... chr.is_a_letter
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  result_count = 1;
  myself = get__is_a_letter();
  func = myself->type;
  frame->cont = cont__76_58;
}
static void cont__76_58(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 697: ... chr == '_'
  frame->slots[5] /* temp__3 */ = create_closure(entry__76_59, 0);
  // 697: ... chr.is_a_letter || chr == '_'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__76_61;
}
static void entry__76_59(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 697: ... chr == '_'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__95;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__76_60;
}
static void cont__76_60(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 697: ... chr == '_'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__76_61(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 697: ... : !s idx
  frame->slots[6] /* temp__4 */ = create_closure(entry__76_62, 0);
  // 697: if chr.is_a_letter || chr == '_': !s idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__76_3(void) {
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
  // 670: s.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* s */;
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
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 670: ... :
  // 671:   unless chr.is_a_letter || chr == '_' || chr.is_a_digit:
  // 672:     $symbol range(buf s idx-1)
  // 673:     !s undefined
  // 674:     unless already_checked(symbol):
  // 675:       !already_checked(symbol) true
  // 676:       $declaration runtime_symbols(symbol)
  // 677:       if declaration.is_defined:
  // 678:         $do_import
  // 679:           &&
  // ...
  frame->slots[7] /* temp__2 */ = create_closure(entry__76_5, 0);
  // 696: :
  // 697:   if chr.is_a_letter || chr == '_': !s idx
  frame->slots[8] /* temp__3 */ = create_closure(entry__76_57, 0);
  // 669: if
  // 670:   s.is_defined:
  // 671:     unless chr.is_a_letter || chr == '_' || chr.is_a_digit:
  // 672:       $symbol range(buf s idx-1)
  // 673:       !s undefined
  // 674:       unless already_checked(symbol):
  // 675:         !already_checked(symbol) true
  // 676:         $declaration runtime_symbols(symbol)
  // 677:         if declaration.is_defined:
  // 678:           $do_import
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
static void entry__76_2_collect_declarations(void) {
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
  // 667: $$s undefined
  ((CELL *)frame->slots[3])->contents /* s */ = get__undefined();
  // 668: ... : (idx chr)
  // 669:   if
  // 670:     s.is_defined:
  // 671:       unless chr.is_a_letter || chr == '_' || chr.is_a_digit:
  // 672:         $symbol range(buf s idx-1)
  // 673:         !s undefined
  // 674:         unless already_checked(symbol):
  // 675:           !already_checked(symbol) true
  // 676:           $declaration runtime_symbols(symbol)
  // 677:           if declaration.is_defined:
  // ...
  frame->slots[4] /* temp__1 */ = create_closure(entry__76_3, 2);
  // 668: for_each buf: (idx chr)
  // 669:   if
  // 670:     s.is_defined:
  // 671:       unless chr.is_a_letter || chr == '_' || chr.is_a_digit:
  // 672:         $symbol range(buf s idx-1)
  // 673:         !s undefined
  // 674:         unless already_checked(symbol):
  // 675:           !already_checked(symbol) true
  // 676:           $declaration runtime_symbols(symbol)
  // 677:           if declaration.is_defined:
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
static void entry__76_63(void) {
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
  // 699: ... collect_declarations source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* source */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* collect_declarations */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__76_64(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* imports */, arguments->slots[0]);
  // 700: $first_part source .before. "// INSERT HERE //"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  arguments->slots[1] = string__76_65;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__76_66;
}
static void cont__76_66(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* first_part */, arguments->slots[0]);
  // 701: write first_part
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* first_part */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__76_67;
}
static void cont__76_67(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 702: write imports
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* imports */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__76_68;
}
static void cont__76_68(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 703: ... length_of(first_part)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* first_part */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__76_69;
}
static void cont__76_69(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__3 */ = arguments->slots[0];
  // 703: ... length_of(first_part)+18
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__3 */;
  arguments->slots[1] = number__18;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__76_70;
}
static void cont__76_70(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 703: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__76_71;
}
static void cont__76_71(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__4 */ = arguments->slots[0];
  // 703: ... range(source length_of(first_part)+18 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  arguments->slots[2] = frame->slots[8] /* temp__4 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__76_72;
}
static void cont__76_72(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 703: write range(source length_of(first_part)+18 -1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__76_73;
}
static void cont__76_73(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 704: if do_time_passes: write_timing_info "collecting imports"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = func__76_74;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__77_1_compile_exe(void) {
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
  // 707: ... main_info.is_a_directory
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_info();
  result_count = 1;
  myself = get__is_a_directory();
  func = myself->type;
  frame->cont = cont__77_2;
}
static void cont__77_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 707: if main_info.is_a_directory: Error "Expected a source code file!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = func__77_3;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__77_5;
}
static void entry__77_3(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 707: ... Error "Expected a source code file!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__77_4;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__77_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 708: ... main_filename .has_suffix. ".sim"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  arguments->slots[1] = string__65_13;
  result_count = 1;
  myself = get__has_suffix();
  func = myself->type;
  frame->cont = cont__77_6;
}
static void cont__77_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 708: unless main_filename .has_suffix. ".sim":
  // 709:   Error "
  // 710:     Expected ".sim" file extension in source filename!@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = func__77_7;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__77_9;
}
static void entry__77_7(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 709: Error "
  // 710:   Expected ".sim" file extension in source filename!@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__77_8;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__77_9(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 712: $mod_filename main_filename .without_suffix. ".sim"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  arguments->slots[1] = string__65_13;
  result_count = 1;
  myself = get__without_suffix();
  func = myself->type;
  frame->cont = cont__77_10;
}
static void cont__77_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* mod_filename */, arguments->slots[0]);
  // 713: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__77_11;
}
static void cont__77_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 713: $mod_name truncate_until(mod_filename '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* mod_filename */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__77_12;
}
static void cont__77_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* mod_name */, arguments->slots[0]);
  // 714: body mod_filename mod_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* mod_filename */;
  arguments->slots[1] = frame->slots[3] /* mod_name */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame->cont = cont__77_13;
}
static void cont__77_13(void) {
  myself = frame->slots[1] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__78_2(void) {
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
  // 718: %sim2c::module_name mod_name
  initialize_maybe_future(get__sim2c__module_name(), frame->slots[1] /* mod_name */);
  // 719: ... list(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__78_3;
}
static void cont__78_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 719: sim2c list(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__sim2c();
  func = myself->type;
  frame->cont = cont__78_4;
}
static void cont__78_4(void) {
  myself = frame->slots[2] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__78_1_dump_source_or_check(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 717: compile_exe: (_mod_filename mod_name)
  // 718:   %sim2c::module_name mod_name
  // 719:   sim2c list(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__78_2;
  result_count = frame->caller_result_count;
  myself = var._compile_exe;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__79_18(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 729: ... write_timing_info "writing C-source"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__79_19;
  result_count = frame->caller_result_count;
  myself = get__write_timing_info();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__79_2(void) {
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
  // 723: ... module_prefix.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._module_prefix;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__79_3;
}
static void cont__79_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 723: ... : append string(module_prefix '/') &mod_name
  frame->slots[5] /* temp__2 */ = create_closure(entry__79_4, 0);
  // 723: if module_prefix.is_defined: append string(module_prefix '/') &mod_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__79_7;
}
static void entry__79_4(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // mod_name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* mod_name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 723: ... string(module_prefix '/')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._module_prefix;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__79_5;
}
static void cont__79_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 723: ... append string(module_prefix '/') &mod_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* mod_name */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__79_6;
}
static void cont__79_6(void) {
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
static void cont__79_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 724: ... :
  // 725:   %sim2c::module_name replace_all(mod_name '/' = "__" '.' = "__")
  // 726:   sim2c list(main_filename)
  frame->slots[4] /* temp__1 */ = create_closure(entry__79_8, 0);
  // 724: collect_output $c_source:
  // 725:   %sim2c::module_name replace_all(mod_name '/' = "__" '.' = "__")
  // 726:   sim2c list(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__79_14;
}
static void entry__79_8(void) {
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
  // 725: ... '/' = "__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = string__71_38;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__79_9;
}
static void cont__79_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 725: ... '.' = "__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__46;
  arguments->slots[1] = string__71_38;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__79_10;
}
static void cont__79_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 725: %sim2c::module_name replace_all(mod_name '/' = "__" '.' = "__")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* mod_name */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  arguments->slots[2] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__79_11;
}
static void cont__79_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(get__sim2c__module_name(), arguments->slots[0]);
  // 726: ... list(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__79_12;
}
static void cont__79_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 726: sim2c list(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__sim2c();
  func = myself->type;
  frame->cont = cont__79_13;
}
static void cont__79_13(void) {
  myself = frame->slots[0] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__79_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* c_source */, arguments->slots[0]);
  // 727: ... : create_imports c_source
  frame->slots[4] /* temp__1 */ = create_closure(entry__79_15, 0);
  // 727: collect_output $c_buf: create_imports c_source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__79_16;
}
static void entry__79_15(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // c_source: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* c_source */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 727: ... create_imports c_source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_source */;
  result_count = frame->caller_result_count;
  myself = var._create_imports;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__79_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* c_buf */, arguments->slots[0]);
  // 728: write c_buf
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* c_buf */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__79_17;
}
static void cont__79_17(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 729: if do_time_passes: write_timing_info "writing C-source"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = func__79_18;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__79_1_print_c(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 722: compile_exe: (_mod_filename $mod_name)
  // 723:   if module_prefix.is_defined: append string(module_prefix '/') &mod_name
  // 724:   collect_output $c_source:
  // 725:     %sim2c::module_name replace_all(mod_name '/' = "__" '.' = "__")
  // 726:     sim2c list(main_filename)
  // 727:   collect_output $c_buf: create_imports c_source
  // 728:   write c_buf
  // 729:   if do_time_passes: write_timing_info "writing C-source"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__79_2;
  result_count = frame->caller_result_count;
  myself = var._compile_exe;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__80_35(void) {
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
  // 758: without_prefix &filename prefix_path
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* filename */;
  arguments->slots[1] = frame->slots[1] /* prefix_path */;
  result_count = 1;
  myself = get__without_prefix();
  func = myself->type;
  frame->cont = cont__80_36;
}
static void cont__80_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* filename */ = arguments->slots[0];
  // 759: without_prefix &filename '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* filename */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__without_prefix();
  func = myself->type;
  frame->cont = cont__80_37;
}
static void cont__80_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* filename */ = arguments->slots[0];
  // 760: writeln filename
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* filename */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__80_1_list_dependencies(void) {
  allocate_initialized_frame_gc(0, 2);
  // slot allocations:
  // prefix_path: 0
  frame->slots[0] /* prefix_path */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 732: !platform_specific_priority multi_dimensional_table(types::table types::table)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__types__table();
  arguments->slots[1] = get__types__table();
  result_count = 1;
  myself = get__multi_dimensional_table();
  func = myself->type;
  frame->cont = cont__80_2;
}
static void cont__80_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._platform_specific_priority = arguments->slots[0];
  // 733: for_each supported_platforms: (supported_platform _parent_platform)
  // 734:   $$platform supported_platform
  // 735:   $$priority 0
  // 736:   do: (-> break)
  // 737:     forever:
  // 738:       $plat supported_platforms(platform)
  // 739:       if plat.is_undefined break
  // 740:       inc &priority
  // 741:       !platform_specific_priority(supported_platform platform) priority
  // 742:       if plat == NONE break
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._supported_platforms;
  arguments->slots[1] = func__80_3;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__80_14;
}
static void entry__80_4(void) {
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
  // 737: ... :
  // 738:   $plat supported_platforms(platform)
  // 739:   if plat.is_undefined break
  // 740:   inc &priority
  // 741:   !platform_specific_priority(supported_platform platform) priority
  // 742:   if plat == NONE break
  // 743:   !platform plat
  frame->slots[4] /* temp__1 */ = create_closure(entry__80_5, 0);
  // 737: forever:
  // 738:   $plat supported_platforms(platform)
  // 739:   if plat.is_undefined break
  // 740:   inc &priority
  // 741:   !platform_specific_priority(supported_platform platform) priority
  // 742:   if plat == NONE break
  // 743:   !platform plat
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame->cont = cont__80_13;
}
static void entry__80_5(void) {
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
  // 738: $plat supported_platforms(platform)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* platform */;
  result_count = 1;
  myself = var._supported_platforms;
  func = myself->type;
  frame->cont = cont__80_6;
}
static void cont__80_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* plat */, arguments->slots[0]);
  // 739: ... plat.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* plat */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__80_7;
}
static void cont__80_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 739: if plat.is_undefined break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* break */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__80_8;
}
static void cont__80_8(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 740: inc &priority
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* priority */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__80_9;
}
static void cont__80_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* priority */ = arguments->slots[0];
  // 741: !platform_specific_priority(supported_platform platform) priority
  frame->slots[5] /* temp__1 */ = ((CELL *)frame->slots[2])->contents /* priority */;
  // 741: !platform_specific_priority(supported_platform platform)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* supported_platform */;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* platform */;
  arguments->slots[2] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = var._platform_specific_priority;
  func = myself->type;
  frame->cont = cont__80_10;
}
static void cont__80_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._platform_specific_priority = arguments->slots[0];
  // 742: ... plat == NONE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* plat */;
  arguments->slots[1] = var._NONE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__80_11;
}
static void cont__80_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 742: if plat == NONE break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* break */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__80_12;
}
static void cont__80_12(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 743: !platform plat
  ((CELL *)frame->slots[0])->contents /* platform */ = frame->slots[4] /* plat */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__80_13(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__80_3(void) {
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
  // 734: $$platform supported_platform
  ((CELL *)frame->slots[2])->contents /* platform */ = frame->slots[0] /* supported_platform */;
  // 735: $$priority 0
  ((CELL *)frame->slots[3])->contents /* priority */ = number__0;
  // 736: ... : (-> break)
  // 737:   forever:
  // 738:     $plat supported_platforms(platform)
  // 739:     if plat.is_undefined break
  // 740:     inc &priority
  // 741:     !platform_specific_priority(supported_platform platform) priority
  // 742:     if plat == NONE break
  // 743:     !platform plat
  frame->slots[4] /* temp__1 */ = create_closure(entry__80_4, 0);
  // 736: do: (-> break)
  // 737:   forever:
  // 738:     $plat supported_platforms(platform)
  // 739:     if plat.is_undefined break
  // 740:     inc &priority
  // 741:     !platform_specific_priority(supported_platform platform) priority
  // 742:     if plat == NONE break
  // 743:     !platform plat
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__do();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__80_14(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 745: main_info.is_a_directory
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_info();
  result_count = 1;
  myself = get__is_a_directory();
  func = myself->type;
  frame->cont = cont__80_15;
}
static void cont__80_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 744: if
  // 745:   main_info.is_a_directory:
  // 746:     %mode LIB
  // 747:     if verbose: ewriteln "list dependencies for " main_filename
  // 748:     compile_modules main_filename behind(main_filename '/' -1)
  // 749:   :
  // 750:     compile_exe: (mod_filename mod_name)
  // 751:       if verbose: ewriteln "list dependencies for " mod_filename
  // 752:       compile_module mod_filename mod_name
  // 753:     writeln "runtime/linker.c"
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__80_16;
  arguments->slots[2] = func__80_23;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__80_33;
}
static void entry__80_16(void) {
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
  // 747: if verbose: ewriteln "list dependencies for " main_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = func__80_17;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__80_19;
}
static void entry__80_17(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 747: ... ewriteln "list dependencies for " main_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__80_18;
  arguments->slots[1] = get__main_filename();
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__80_19(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 748: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__80_20;
}
static void cont__80_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 748: ... behind(main_filename '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__80_21;
}
static void cont__80_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 748: compile_modules main_filename behind(main_filename '/' -1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = var._compile_modules;
  func = myself->type;
  frame->cont = cont__80_22;
}
static void cont__80_22(void) {
  myself = frame->slots[0] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__80_23(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 750: compile_exe: (mod_filename mod_name)
  // 751:   if verbose: ewriteln "list dependencies for " mod_filename
  // 752:   compile_module mod_filename mod_name
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__80_24;
  result_count = 0;
  myself = var._compile_exe;
  func = myself->type;
  frame->cont = cont__80_27;
}
static void entry__80_24(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // mod_filename: 0
  // mod_name: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 751: ... : ewriteln "list dependencies for " mod_filename
  frame->slots[2] /* temp__1 */ = create_closure(entry__80_25, 0);
  // 751: if verbose: ewriteln "list dependencies for " mod_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__80_26;
}
static void entry__80_25(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // mod_filename: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* mod_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 751: ... ewriteln "list dependencies for " mod_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__80_18;
  arguments->slots[1] = frame->slots[0] /* mod_filename */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__80_26(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 752: compile_module mod_filename mod_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = frame->slots[1] /* mod_name */;
  result_count = frame->caller_result_count;
  myself = var._compile_module;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__80_27(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 753: writeln "runtime/linker.c"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__80_28;
  result_count = 0;
  myself = get__writeln();
  func = myself->type;
  frame->cont = cont__80_29;
}
static void cont__80_29(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 754: writeln "runtime/memory.c"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__80_30;
  result_count = 0;
  myself = get__writeln();
  func = myself->type;
  frame->cont = cont__80_31;
}
static void cont__80_31(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 755: writeln "runtime/debugger.c"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__80_32;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__80_33(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 756: $prefix_path current_path()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__current_path();
  func = myself->type;
  frame->cont = cont__80_34;
}
static void cont__80_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[0] /* prefix_path */, arguments->slots[0]);
  // 757: ... : ($filename)
  // 758:   without_prefix &filename prefix_path
  // 759:   without_prefix &filename '/'
  // 760:   writeln filename
  frame->slots[1] /* temp__1 */ = create_closure(entry__80_35, 1);
  // 757: for_each dependencies: ($filename)
  // 758:   without_prefix &filename prefix_path
  // 759:   without_prefix &filename '/'
  // 760:   writeln filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._dependencies;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__81_2(void) {
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
  // 764: $codeblocks_path string(mod_filename ".codeblocks")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = string__81_3;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__81_4;
}
static void cont__81_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* codeblocks_path */, arguments->slots[0]);
  // 765: $info stat(codeblocks_path)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* codeblocks_path */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__81_5;
}
static void cont__81_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* info */, arguments->slots[0]);
  // 766: ... info.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* info */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__81_6;
}
static void cont__81_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 766: ... :
  // 767:   ewrite "
  // 768:     The directory "@(codeblocks_path)" already exists!
  frame->slots[11] /* temp__2 */ = create_closure(entry__81_7, 0);
  // 766: if info.is_defined:
  // 767:   ewrite "
  // 768:     The directory "@(codeblocks_path)" already exists!
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__1 */;
  arguments->slots[1] = frame->slots[11] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__81_11;
}
static void entry__81_7(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // codeblocks_path: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* codeblocks_path */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 767: ... "
  // 768:   The directory "@(codeblocks_path)" already exists!
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__81_8;
  arguments->slots[1] = frame->slots[0] /* codeblocks_path */;
  arguments->slots[2] = string__81_9;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__81_10;
}
static void cont__81_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 767: ewrite "
  // 768:   The directory "@(codeblocks_path)" already exists!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewrite();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__81_11(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 769: ... : ewriteln "build Code::Blocks project in " codeblocks_path
  frame->slots[10] /* temp__1 */ = create_closure(entry__81_12, 0);
  // 769: if verbose: ewriteln "build Code::Blocks project in " codeblocks_path
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = frame->slots[10] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__81_14;
}
static void entry__81_12(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // codeblocks_path: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* codeblocks_path */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 769: ... ewriteln "build Code::Blocks project in " codeblocks_path
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__81_13;
  arguments->slots[1] = frame->slots[0] /* codeblocks_path */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__81_14(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 770: compile_module mod_filename mod_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = frame->slots[1] /* mod_name */;
  result_count = 0;
  myself = var._compile_module;
  func = myself->type;
  frame->cont = cont__81_15;
}
static void cont__81_15(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 771: show_file_list
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._show_file_list;
  func = myself->type;
  frame->cont = cont__81_16;
}
static void cont__81_16(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 772: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__81_17;
}
static void cont__81_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__2 */ = arguments->slots[0];
  // 772: ... truncate_until(main_filename '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[11] /* temp__2 */;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__81_18;
}
static void cont__81_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 772: $basename truncate_until(main_filename '/' -1) .without_suffix. ".sim"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__1 */;
  arguments->slots[1] = string__65_13;
  result_count = 1;
  myself = get__without_suffix();
  func = myself->type;
  frame->cont = cont__81_19;
}
static void cont__81_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* basename */, arguments->slots[0]);
  // 773: $prefix_path current_path()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__current_path();
  func = myself->type;
  frame->cont = cont__81_20;
}
static void cont__81_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* prefix_path */, arguments->slots[0]);
  // 774: ... codeblocks_path .without_prefix. prefix_path
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* codeblocks_path */;
  arguments->slots[1] = frame->slots[5] /* prefix_path */;
  result_count = 1;
  myself = get__without_prefix();
  func = myself->type;
  frame->cont = cont__81_21;
}
static void cont__81_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 774: $depth count_occurrences(codeblocks_path .without_prefix. prefix_path '/')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__1 */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__count_occurrences();
  func = myself->type;
  frame->cont = cont__81_22;
}
static void cont__81_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* depth */, arguments->slots[0]);
  // 775: $path_prefix dup("../" depth)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__81_23;
  arguments->slots[1] = frame->slots[6] /* depth */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__81_24;
}
static void cont__81_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[7] /* path_prefix */, arguments->slots[0]);
  // 776: $cbp_filename string(codeblocks_path "/" basename ".cbp")
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* codeblocks_path */;
  arguments->slots[1] = string__81_25;
  arguments->slots[2] = frame->slots[4] /* basename */;
  arguments->slots[3] = string__81_26;
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
  initialize_future(frame->slots[8] /* cbp_filename */, arguments->slots[0]);
  // 777: mkdir codeblocks_path
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* codeblocks_path */;
  result_count = 0;
  myself = var._mkdir;
  func = myself->type;
  frame->cont = cont__81_28;
}
static void cont__81_28(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 778: $$buf ""
  ((CELL *)frame->slots[9])->contents /* buf */ = empty_string;
  // 779: ... "
  // 780:   <?xml version="1.0" encoding="UTF-8" standalone="yes" ?>
  // 781:   <CodeBlocks_project_file>
  // 782:     <FileVersion major="1" minor="6" />
  // 783:     <Project>
  // 784:       <Option title="@(basename)" />
  // 785:       <Option pch_mode="2" />
  // 786:       <Option compiler="gcc" />
  // 787:       <Build>
  // 788:         <Target title="debug">
  // ...
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__81_29;
  arguments->slots[1] = frame->slots[4] /* basename */;
  arguments->slots[2] = string__81_30;
  arguments->slots[3] = frame->slots[4] /* basename */;
  arguments->slots[4] = string__81_31;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__81_32;
}
static void cont__81_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 779: write_to &buf "
  // 780:   <?xml version="1.0" encoding="UTF-8" standalone="yes" ?>
  // 781:   <CodeBlocks_project_file>
  // 782:     <FileVersion major="1" minor="6" />
  // 783:     <Project>
  // 784:       <Option title="@(basename)" />
  // 785:       <Option pch_mode="2" />
  // 786:       <Option compiler="gcc" />
  // 787:       <Build>
  // 788:         <Target title="debug">
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[9])->contents /* buf */;
  arguments->slots[1] = frame->slots[10] /* temp__1 */;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__81_33;
}
static void cont__81_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[9])->contents /* buf */ = arguments->slots[0];
  // 800: ... : (filename)
  // 801:   write_to &buf "
  // 802:     @
  // 803:           <Add library="@(filename)" />
  frame->slots[10] /* temp__1 */ = create_closure(entry__81_34, 1);
  // 800: for_each libraries: (filename)
  // 801:   write_to &buf "
  // 802:     @
  // 803:           <Add library="@(filename)" />
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__libraries();
  arguments->slots[1] = frame->slots[10] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__81_39;
}
static void entry__81_34(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // filename: 0
  // buf: 1
  frame->slots[1] = myself->closure.frame->slots[9]; /* buf */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 801: ... "
  // 802:   @
  // 803:         <Add library="@(filename)" />
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__81_35;
  arguments->slots[1] = frame->slots[0] /* filename */;
  arguments->slots[2] = string__81_36;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__81_37;
}
static void cont__81_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 801: write_to &buf "
  // 802:   @
  // 803:         <Add library="@(filename)" />
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* buf */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__81_38;
}
static void cont__81_38(void) {
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
static void cont__81_39(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 804: ... "
  // 805:   @
  // 806:   
  // 807:       </Linker>
  // 808:       <Compiler>
  // 809:         <Add option="-Wall" />
  // 810:       </Compiler>
  // 811:       <Unit filename="@(path_prefix)runtime/common.h" />
  // 812:       <Unit filename="@(path_prefix)runtime/linker.h" />
  // 813:       <Unit filename="@(path_prefix)runtime/memory.c">
  // ...
  argument_count = 11;
  arguments = node_p;
  arguments->slots[0] = string__81_40;
  arguments->slots[1] = frame->slots[7] /* path_prefix */;
  arguments->slots[2] = string__81_41;
  arguments->slots[3] = frame->slots[7] /* path_prefix */;
  arguments->slots[4] = string__81_42;
  arguments->slots[5] = frame->slots[7] /* path_prefix */;
  arguments->slots[6] = string__81_43;
  arguments->slots[7] = frame->slots[7] /* path_prefix */;
  arguments->slots[8] = string__81_44;
  arguments->slots[9] = frame->slots[7] /* path_prefix */;
  arguments->slots[10] = string__81_45;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__81_46;
}
static void cont__81_46(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 804: write_to &buf "
  // 805:   @
  // 806:   
  // 807:       </Linker>
  // 808:       <Compiler>
  // 809:         <Add option="-Wall" />
  // 810:       </Compiler>
  // 811:       <Unit filename="@(path_prefix)runtime/common.h" />
  // 812:       <Unit filename="@(path_prefix)runtime/linker.h" />
  // 813:       <Unit filename="@(path_prefix)runtime/memory.c">
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[9])->contents /* buf */;
  arguments->slots[1] = frame->slots[10] /* temp__1 */;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__81_47;
}
static void cont__81_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[9])->contents /* buf */ = arguments->slots[0];
  // 822: ... : ($filename)
  // 823:   without_prefix &filename prefix_path
  // 824:   without_prefix &filename '/'
  // 825:   write_to &buf "
  // 826:     @
  // 827:     
  // 828:         <Unit filename="@(path_prefix)@(filename)">
  // 829:           <Option compilerVar="CC" />
  // 830:         </Unit>
  frame->slots[10] /* temp__1 */ = create_closure(entry__81_48, 1);
  // 822: for_each c_sources: ($filename)
  // 823:   without_prefix &filename prefix_path
  // 824:   without_prefix &filename '/'
  // 825:   write_to &buf "
  // 826:     @
  // 827:     
  // 828:         <Unit filename="@(path_prefix)@(filename)">
  // 829:           <Option compilerVar="CC" />
  // 830:         </Unit>
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._c_sources;
  arguments->slots[1] = frame->slots[10] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__81_55;
}
static void entry__81_48(void) {
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
  // 823: without_prefix &filename prefix_path
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* filename */;
  arguments->slots[1] = frame->slots[1] /* prefix_path */;
  result_count = 1;
  myself = get__without_prefix();
  func = myself->type;
  frame->cont = cont__81_49;
}
static void cont__81_49(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* filename */ = arguments->slots[0];
  // 824: without_prefix &filename '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* filename */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__without_prefix();
  func = myself->type;
  frame->cont = cont__81_50;
}
static void cont__81_50(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* filename */ = arguments->slots[0];
  // 825: ... "
  // 826:   @
  // 827:   
  // 828:       <Unit filename="@(path_prefix)@(filename)">
  // 829:         <Option compilerVar="CC" />
  // 830:       </Unit>
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__81_51;
  arguments->slots[1] = frame->slots[3] /* path_prefix */;
  arguments->slots[2] = ((CELL *)frame->slots[0])->contents /* filename */;
  arguments->slots[3] = string__81_52;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__81_53;
}
static void cont__81_53(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 825: write_to &buf "
  // 826:   @
  // 827:   
  // 828:       <Unit filename="@(path_prefix)@(filename)">
  // 829:         <Option compilerVar="CC" />
  // 830:       </Unit>
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* buf */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__81_54;
}
static void cont__81_54(void) {
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
static void cont__81_55(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 831: write_to &buf "
  // 832:       <Extensions>
  // 833:         <code_completion />
  // 834:         <debugger />
  // 835:       </Extensions>
  // 836:     </Project>
  // 837:   </CodeBlocks_project_file>
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[9])->contents /* buf */;
  arguments->slots[1] = string__81_56;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__81_57;
}
static void cont__81_57(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[9])->contents /* buf */ = arguments->slots[0];
  // 838: save cbp_filename buf
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* cbp_filename */;
  arguments->slots[1] = ((CELL *)frame->slots[9])->contents /* buf */;
  result_count = frame->caller_result_count;
  myself = get__save();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__81_1_build_codeblocks_project(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 763: compile_exe: (mod_filename mod_name)
  // 764:   $codeblocks_path string(mod_filename ".codeblocks")
  // 765:   $info stat(codeblocks_path)
  // 766:   if info.is_defined:
  // 767:     ewrite "
  // 768:       The directory "@(codeblocks_path)" already exists!
  // 769:   if verbose: ewriteln "build Code::Blocks project in " codeblocks_path
  // 770:   compile_module mod_filename mod_name
  // 771:   show_file_list
  // 772:   $basename truncate_until(main_filename '/' -1) .without_suffix. ".sim"
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__81_2;
  result_count = frame->caller_result_count;
  myself = var._compile_exe;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__82_1_build_library(void) {
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
  // 841: ... action == "simrun"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._action;
  arguments->slots[1] = string__82_2;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__82_3;
}
static void cont__82_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 841: if action == "simrun": Error "Cannot run a directory!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__82_4;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__82_6;
}
static void entry__82_4(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 841: ... Error "Cannot run a directory!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__82_5;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__82_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 843: if
  // 844:   do_extract_documentation:
  // 845:     extract_documentation main_filename
  // 846:   :
  // 847:     $$version ""
  // 848:     $$so_version ""
  // 849:     $version_filename string(main_filename "/VERSION")
  // 850:     if file_exists(version_filename):
  // 851:       !version string('-' load(version_filename).trim)
  // 852:       !so_version version .truncate_from. '.'
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__do_extract_documentation();
  arguments->slots[1] = func__82_7;
  arguments->slots[2] = func__82_8;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__82_86;
}
static void entry__82_84(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // err: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* err */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 913: ... err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* err */;
  result_count = 1;
  myself = get__from_utf8();
  func = myself->type;
  frame->cont = cont__82_85;
}
static void cont__82_85(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 913: ... Error err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__82_79(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // err: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* err */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 906: ... err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* err */;
  result_count = 1;
  myself = get__from_utf8();
  func = myself->type;
  frame->cont = cont__82_80;
}
static void cont__82_80(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 906: ... Error err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__82_70(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // err: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* err */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 895: ... err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* err */;
  result_count = 1;
  myself = get__from_utf8();
  func = myself->type;
  frame->cont = cont__82_71;
}
static void cont__82_71(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 895: ... Error err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__82_63(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // err: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* err */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 887: ... err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* err */;
  result_count = 1;
  myself = get__from_utf8();
  func = myself->type;
  frame->cont = cont__82_64;
}
static void cont__82_64(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 887: ... Error err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__82_57(void) {
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
  // 883: "-Wl,-soname,libsim-@(base_filename)@(so_version).so.@(MAJOR)"
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__82_58;
  arguments->slots[1] = frame->slots[0] /* base_filename */;
  arguments->slots[2] = ((CELL *)frame->slots[1])->contents /* so_version */;
  arguments->slots[3] = string__75_26;
  arguments->slots[4] = var._MAJOR;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__82_59;
}
static void cont__82_59(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 884: library_paths_and_file_list()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = var._library_paths_and_file_list;
  func = myself->type;
  frame->cont = cont__82_60;
}
static void cont__82_60(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 881: Gcc $_out $err $success
  // 882:   "-shared"
  // 883:   "-Wl,-soname,libsim-@(base_filename)@(so_version).so.@(MAJOR)"
  // 884:   library_paths_and_file_list()*
  // 885:   "-o"
  // 886:   lib_filename
  argument_count = 0;
  arguments = node_p;
  arguments->slots[argument_count++] = string__82_61;
  arguments->slots[argument_count++] = frame->slots[6] /* temp__1 */;
  unfold(frame->slots[7] /* temp__2 */);
  arguments->slots[argument_count++] = string__68_6;
  arguments->slots[argument_count++] = frame->slots[2] /* lib_filename */;
  result_count = 3;
  myself = var._Gcc;
  func = myself->type;
  frame->cont = cont__82_62;
}
static void cont__82_62(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__3 */ = arguments->slots[0];
  frame->slots[9] /* temp__4 */ = arguments->slots[1];
  frame->slots[10] /* temp__5 */ = arguments->slots[2];
  // 881: ... _out
  initialize_future(frame->slots[3] /* out */, frame->slots[8] /* temp__3 */);
  // 881: ... err
  initialize_future(frame->slots[4] /* err */, frame->slots[9] /* temp__4 */);
  // 881: ... success
  initialize_future(frame->slots[5] /* success */, frame->slots[10] /* temp__5 */);
  // 887: ... : Error err.from_utf8
  frame->slots[6] /* temp__1 */ = create_closure(entry__82_63, 0);
  // 887: unless success: Error err.from_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* success */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__82_65(void) {
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
  // 891: library_paths_and_file_list()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = var._library_paths_and_file_list;
  func = myself->type;
  frame->cont = cont__82_66;
}
static void cont__82_66(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 892: "-lsim-@(MAJOR)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__82_67;
  arguments->slots[1] = var._MAJOR;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__82_68;
}
static void cont__82_68(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 889: Gcc $_out $err $success
  // 890:   "-shared"
  // 891:   library_paths_and_file_list()*
  // 892:   "-lsim-@(MAJOR)"
  // 893:   "-o"
  // 894:   lib_filename
  argument_count = 0;
  arguments = node_p;
  arguments->slots[argument_count++] = string__82_61;
  unfold(frame->slots[4] /* temp__1 */);
  arguments->slots[argument_count++] = frame->slots[5] /* temp__2 */;
  arguments->slots[argument_count++] = string__68_6;
  arguments->slots[argument_count++] = frame->slots[0] /* lib_filename */;
  result_count = 3;
  myself = var._Gcc;
  func = myself->type;
  frame->cont = cont__82_69;
}
static void cont__82_69(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  frame->slots[7] /* temp__4 */ = arguments->slots[1];
  frame->slots[8] /* temp__5 */ = arguments->slots[2];
  // 889: ... _out
  initialize_future(frame->slots[1] /* out */, frame->slots[6] /* temp__3 */);
  // 889: ... err
  initialize_future(frame->slots[2] /* err */, frame->slots[7] /* temp__4 */);
  // 889: ... success
  initialize_future(frame->slots[3] /* success */, frame->slots[8] /* temp__5 */);
  // 895: ... : Error err.from_utf8
  frame->slots[4] /* temp__1 */ = create_closure(entry__82_70, 0);
  // 895: unless success: Error err.from_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* success */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__82_72(void) {
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
  // 899: "
  // 900:   -Wl,-install_name,libsim-@(base_filename)@(so_version)-@(MAJOR)@
  // 901:   .dylib@
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = string__82_73;
  arguments->slots[1] = frame->slots[0] /* base_filename */;
  arguments->slots[2] = ((CELL *)frame->slots[1])->contents /* so_version */;
  arguments->slots[3] = string__65_46;
  arguments->slots[4] = var._MAJOR;
  arguments->slots[5] = string__82_29;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__82_74;
}
static void cont__82_74(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 902: library_paths_and_file_list()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = var._library_paths_and_file_list;
  func = myself->type;
  frame->cont = cont__82_75;
}
static void cont__82_75(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 903: "-lsim-@(MAJOR)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__82_67;
  arguments->slots[1] = var._MAJOR;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__82_76;
}
static void cont__82_76(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__3 */ = arguments->slots[0];
  // 897: Gcc $_out $err $success
  // 898:   "-dynamiclib"
  // 899:   "
  // 900:     -Wl,-install_name,libsim-@(base_filename)@(so_version)-@(MAJOR)@
  // 901:     .dylib@
  // 902:   library_paths_and_file_list()*
  // 903:   "-lsim-@(MAJOR)"
  // 904:   "-o"
  // 905:   lib_filename
  argument_count = 0;
  arguments = node_p;
  arguments->slots[argument_count++] = string__82_77;
  arguments->slots[argument_count++] = frame->slots[6] /* temp__1 */;
  unfold(frame->slots[7] /* temp__2 */);
  arguments->slots[argument_count++] = frame->slots[8] /* temp__3 */;
  arguments->slots[argument_count++] = string__68_6;
  arguments->slots[argument_count++] = frame->slots[2] /* lib_filename */;
  result_count = 3;
  myself = var._Gcc;
  func = myself->type;
  frame->cont = cont__82_78;
}
static void cont__82_78(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__4 */ = arguments->slots[0];
  frame->slots[10] /* temp__5 */ = arguments->slots[1];
  frame->slots[11] /* temp__6 */ = arguments->slots[2];
  // 897: ... _out
  initialize_future(frame->slots[3] /* out */, frame->slots[9] /* temp__4 */);
  // 897: ... err
  initialize_future(frame->slots[4] /* err */, frame->slots[10] /* temp__5 */);
  // 897: ... success
  initialize_future(frame->slots[5] /* success */, frame->slots[11] /* temp__6 */);
  // 906: ... : Error err.from_utf8
  frame->slots[6] /* temp__1 */ = create_closure(entry__82_79, 0);
  // 906: unless success: Error err.from_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* success */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__82_81(void) {
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
  // 910: library_paths_and_file_list()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = var._library_paths_and_file_list;
  func = myself->type;
  frame->cont = cont__82_82;
}
static void cont__82_82(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 908: Gcc $_out $err $success
  // 909:   "-shared"
  // 910:   library_paths_and_file_list()*
  // 911:   "-o"
  // 912:   lib_filename
  argument_count = 0;
  arguments = node_p;
  arguments->slots[argument_count++] = string__82_61;
  unfold(frame->slots[4] /* temp__1 */);
  arguments->slots[argument_count++] = string__68_6;
  arguments->slots[argument_count++] = frame->slots[0] /* lib_filename */;
  result_count = 3;
  myself = var._Gcc;
  func = myself->type;
  frame->cont = cont__82_83;
}
static void cont__82_83(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  frame->slots[6] /* temp__3 */ = arguments->slots[1];
  frame->slots[7] /* temp__4 */ = arguments->slots[2];
  // 908: ... _out
  initialize_future(frame->slots[1] /* out */, frame->slots[5] /* temp__2 */);
  // 908: ... err
  initialize_future(frame->slots[2] /* err */, frame->slots[6] /* temp__3 */);
  // 908: ... success
  initialize_future(frame->slots[3] /* success */, frame->slots[7] /* temp__4 */);
  // 913: ... : Error err.from_utf8
  frame->slots[4] /* temp__1 */ = create_closure(entry__82_84, 0);
  // 913: unless success: Error err.from_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* success */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__82_53(void) {
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
  // 877: if verbose: ewriteln "linking dynamic library"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = func__82_54;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__82_56;
}
static void entry__82_54(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 877: ... ewriteln "linking dynamic library"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__82_55;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__82_56(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 880: ... :
  // 881:   Gcc $_out $err $success
  // 882:     "-shared"
  // 883:     "-Wl,-soname,libsim-@(base_filename)@(so_version).so.@(MAJOR)"
  // 884:     library_paths_and_file_list()*
  // 885:     "-o"
  // 886:     lib_filename
  // 887:   unless success: Error err.from_utf8
  frame->slots[3] /* temp__1 */ = create_closure(entry__82_57, 0);
  // 888: ... :
  // 889:   Gcc $_out $err $success
  // 890:     "-shared"
  // 891:     library_paths_and_file_list()*
  // 892:     "-lsim-@(MAJOR)"
  // 893:     "-o"
  // 894:     lib_filename
  // 895:   unless success: Error err.from_utf8
  frame->slots[4] /* temp__2 */ = create_closure(entry__82_65, 0);
  // 896: ... :
  // 897:   Gcc $_out $err $success
  // 898:     "-dynamiclib"
  // 899:     "
  // 900:       -Wl,-install_name,libsim-@(base_filename)@(so_version)-@(MAJOR)@
  // 901:       .dylib@
  // 902:     library_paths_and_file_list()*
  // 903:     "-lsim-@(MAJOR)"
  // 904:     "-o"
  // 905:     lib_filename
  // ...
  frame->slots[5] /* temp__3 */ = create_closure(entry__82_72, 0);
  // 907: :
  // 908:   Gcc $_out $err $success
  // 909:     "-shared"
  // 910:     library_paths_and_file_list()*
  // 911:     "-o"
  // 912:     lib_filename
  // 913:   unless success: Error err.from_utf8
  frame->slots[6] /* temp__4 */ = create_closure(entry__82_81, 0);
  // 878: case
  // 879:   current_platform
  // 880:   "linux":
  // 881:     Gcc $_out $err $success
  // 882:       "-shared"
  // 883:       "-Wl,-soname,libsim-@(base_filename)@(so_version).so.@(MAJOR)"
  // 884:       library_paths_and_file_list()*
  // 885:       "-o"
  // 886:       lib_filename
  // 887:     unless success: Error err.from_utf8
  // ...
  argument_count = 8;
  arguments = node_p;
  arguments->slots[0] = get__current_platform();
  arguments->slots[1] = string__75_22;
  arguments->slots[2] = frame->slots[3] /* temp__1 */;
  arguments->slots[3] = string__82_35;
  arguments->slots[4] = frame->slots[4] /* temp__2 */;
  arguments->slots[5] = string__82_36;
  arguments->slots[6] = frame->slots[5] /* temp__3 */;
  arguments->slots[7] = frame->slots[6] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__82_7(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 845: extract_documentation main_filename
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  result_count = frame->caller_result_count;
  myself = get__extract_documentation();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__82_8(void) {
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
  // 847: $$version ""
  ((CELL *)frame->slots[0])->contents /* version */ = empty_string;
  // 848: $$so_version ""
  ((CELL *)frame->slots[1])->contents /* so_version */ = empty_string;
  // 849: $version_filename string(main_filename "/VERSION")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  arguments->slots[1] = string__82_9;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__82_10;
}
static void cont__82_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* version_filename */, arguments->slots[0]);
  // 850: ... file_exists(version_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* version_filename */;
  result_count = 1;
  myself = get__file_exists();
  func = myself->type;
  frame->cont = cont__82_11;
}
static void cont__82_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 850: ... :
  // 851:   !version string('-' load(version_filename).trim)
  // 852:   !so_version version .truncate_from. '.'
  frame->slots[6] /* temp__2 */ = create_closure(entry__82_12, 0);
  // 850: if file_exists(version_filename):
  // 851:   !version string('-' load(version_filename).trim)
  // 852:   !so_version version .truncate_from. '.'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__82_17;
}
static void entry__82_12(void) {
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
  // 851: ... load(version_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* version_filename */;
  result_count = 1;
  myself = get__load();
  func = myself->type;
  frame->cont = cont__82_13;
}
static void cont__82_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 851: ... load(version_filename).trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__82_14;
}
static void cont__82_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 851: !version string('-' load(version_filename).trim)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__45;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__82_15;
}
static void cont__82_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* version */ = arguments->slots[0];
  // 852: !so_version version .truncate_from. '.'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* version */;
  arguments->slots[1] = character__46;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__82_16;
}
static void cont__82_16(void) {
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
static void cont__82_17(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 853: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__82_18;
}
static void cont__82_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 853: $base_filename truncate_until(main_filename '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__82_19;
}
static void cont__82_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* base_filename */, arguments->slots[0]);
  // 859: -> string("libsim-" base_filename version ".so.@(MAJOR)")
  frame->slots[5] /* temp__1 */ = create_closure(entry__82_20, 0);
  // 861: -> string("libsim-" base_filename version "-@(MAJOR).dll")
  frame->slots[6] /* temp__2 */ = create_closure(entry__82_24, 0);
  // 863: -> string("libsim-" base_filename version "-@(MAJOR).dylib")
  frame->slots[7] /* temp__3 */ = create_closure(entry__82_28, 0);
  // 864: -> string("libsim-" base_filename ".so")
  frame->slots[8] /* temp__4 */ = create_closure(entry__82_32, 0);
  // 855: $lib_filename
  // 856:   case
  // 857:     current_platform
  // 858:     "linux"
  // 859:     -> string("libsim-" base_filename version ".so.@(MAJOR)")
  // 860:     "cygwin"
  // 861:     -> string("libsim-" base_filename version "-@(MAJOR).dll")
  // 862:     "darwin"
  // 863:     -> string("libsim-" base_filename version "-@(MAJOR).dylib")
  // 864:     -> string("libsim-" base_filename ".so")
  argument_count = 8;
  arguments = node_p;
  arguments->slots[0] = get__current_platform();
  arguments->slots[1] = string__75_22;
  arguments->slots[2] = frame->slots[5] /* temp__1 */;
  arguments->slots[3] = string__82_35;
  arguments->slots[4] = frame->slots[6] /* temp__2 */;
  arguments->slots[5] = string__82_36;
  arguments->slots[6] = frame->slots[7] /* temp__3 */;
  arguments->slots[7] = frame->slots[8] /* temp__4 */;
  result_count = 1;
  myself = get__case();
  func = myself->type;
  frame->cont = cont__82_37;
}
static void entry__82_20(void) {
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
  // 859: ... ".so.@(MAJOR)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__75_26;
  arguments->slots[1] = var._MAJOR;
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
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 859: ... string("libsim-" base_filename version ".so.@(MAJOR)")
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__82_22;
  arguments->slots[1] = frame->slots[0] /* base_filename */;
  arguments->slots[2] = ((CELL *)frame->slots[1])->contents /* version */;
  arguments->slots[3] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__82_23;
}
static void cont__82_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 859: -> string("libsim-" base_filename version ".so.@(MAJOR)")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__82_24(void) {
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
  // 861: ... "-@(MAJOR).dll"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__65_46;
  arguments->slots[1] = var._MAJOR;
  arguments->slots[2] = string__82_25;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__82_26;
}
static void cont__82_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 861: ... string("libsim-" base_filename version "-@(MAJOR).dll")
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__82_22;
  arguments->slots[1] = frame->slots[0] /* base_filename */;
  arguments->slots[2] = ((CELL *)frame->slots[1])->contents /* version */;
  arguments->slots[3] = frame->slots[3] /* temp__2 */;
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
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 861: -> string("libsim-" base_filename version "-@(MAJOR).dll")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__82_28(void) {
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
  // 863: ... "-@(MAJOR).dylib"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__65_46;
  arguments->slots[1] = var._MAJOR;
  arguments->slots[2] = string__82_29;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__82_30;
}
static void cont__82_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 863: ... string("libsim-" base_filename version "-@(MAJOR).dylib")
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__82_22;
  arguments->slots[1] = frame->slots[0] /* base_filename */;
  arguments->slots[2] = ((CELL *)frame->slots[1])->contents /* version */;
  arguments->slots[3] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__82_31;
}
static void cont__82_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 863: -> string("libsim-" base_filename version "-@(MAJOR).dylib")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__82_32(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // base_filename: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* base_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 864: ... string("libsim-" base_filename ".so")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__82_22;
  arguments->slots[1] = frame->slots[0] /* base_filename */;
  arguments->slots[2] = string__82_33;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__82_34;
}
static void cont__82_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 864: -> string("libsim-" base_filename ".so")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__82_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* lib_filename */, arguments->slots[0]);
  // 866: ... : ewriteln "build library " lib_filename
  frame->slots[5] /* temp__1 */ = create_closure(entry__82_38, 0);
  // 866: if verbose: ewriteln "build library " lib_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__82_40;
}
static void entry__82_38(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // lib_filename: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* lib_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 866: ... ewriteln "build library " lib_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__82_39;
  arguments->slots[1] = frame->slots[0] /* lib_filename */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__82_40(void) {
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
  frame->cont = cont__82_41;
}
static void cont__82_41(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 867: ... behind(main_filename '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__82_42;
}
static void cont__82_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 867: compile_modules main_filename behind(main_filename '/' -1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = var._compile_modules;
  func = myself->type;
  frame->cont = cont__82_43;
}
static void cont__82_43(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 868: ... :
  // 869:   $info stat(lib_filename)
  // 870:   if
  // 871:     ||
  // 872:       info.is_undefined
  // 873:       last_modification_time > modification_time_of(info)
  // 874:     :
  // 875:       !do_link true
  frame->slots[5] /* temp__1 */ = create_closure(entry__82_44, 0);
  // 868: unless do_link:
  // 869:   $info stat(lib_filename)
  // 870:   if
  // 871:     ||
  // 872:       info.is_undefined
  // 873:       last_modification_time > modification_time_of(info)
  // 874:     :
  // 875:       !do_link true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_link();
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__82_52;
}
static void entry__82_51(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 875: !do_link true
  set__do_link(get__true());
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__82_44(void) {
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
  // 869: $info stat(lib_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* lib_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__82_45;
}
static void cont__82_45(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* info */, arguments->slots[0]);
  // 872: info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__82_46;
}
static void cont__82_46(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 873: last_modification_time > modification_time_of(info)
  frame->slots[4] /* temp__3 */ = create_closure(entry__82_47, 0);
  // 871: ||
  // 872:   info.is_undefined
  // 873:   last_modification_time > modification_time_of(info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__82_50;
}
static void entry__82_47(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // info: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 873: ... modification_time_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__82_48;
}
static void cont__82_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 873: last_modification_time > modification_time_of(info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = get__last_modification_time();
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__82_49;
}
static void cont__82_49(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 873: last_modification_time > modification_time_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__82_50(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 870: if
  // 871:   ||
  // 872:     info.is_undefined
  // 873:     last_modification_time > modification_time_of(info)
  // 874:   :
  // 875:     !do_link true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = func__82_51;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__82_52(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 876: ... :
  // 877:   if verbose: ewriteln "linking dynamic library"
  // 878:   case
  // 879:     current_platform
  // 880:     "linux":
  // 881:       Gcc $_out $err $success
  // 882:         "-shared"
  // 883:         "-Wl,-soname,libsim-@(base_filename)@(so_version).so.@(MAJOR)"
  // 884:         library_paths_and_file_list()*
  // 885:         "-o"
  // ...
  frame->slots[5] /* temp__1 */ = create_closure(entry__82_53, 0);
  // 876: if do_link:
  // 877:   if verbose: ewriteln "linking dynamic library"
  // 878:   case
  // 879:     current_platform
  // 880:     "linux":
  // 881:       Gcc $_out $err $success
  // 882:         "-shared"
  // 883:         "-Wl,-soname,libsim-@(base_filename)@(so_version).so.@(MAJOR)"
  // 884:         library_paths_and_file_list()*
  // 885:         "-o"
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
static void cont__82_86(void) {
  myself = frame->slots[0] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__83_18(void) {
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
  // 928: ... : ewriteln "compiling runtime module @(filename)"
  frame->slots[3] /* temp__1 */ = create_closure(entry__83_19, 0);
  // 928: if verbose: ewriteln "compiling runtime module @(filename)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__83_22;
}
static void entry__83_19(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // filename: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 928: ... "compiling runtime module @(filename)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__83_20;
  arguments->slots[1] = frame->slots[0] /* filename */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__83_21;
}
static void cont__83_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 928: ... ewriteln "compiling runtime module @(filename)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__83_22(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 929: compile_c c_filename o_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* c_filename */;
  arguments->slots[1] = frame->slots[2] /* o_filename */;
  result_count = frame->caller_result_count;
  myself = var._compile_c;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__83_1_maybe_compile_c_file(void) {
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
  // 916: $c_filename string(filename ".c")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  arguments->slots[1] = string__69_9;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__83_2;
}
static void cont__83_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* c_filename */, arguments->slots[0]);
  // 917: $o_filename string(filename ".o")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  arguments->slots[1] = string__71_80;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__83_3;
}
static void cont__83_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* o_filename */, arguments->slots[0]);
  // 918: $c_info stat(c_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* c_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__83_4;
}
static void cont__83_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* c_info */, arguments->slots[0]);
  // 919: ... c_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* c_info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__83_5;
}
static void cont__83_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 919: ... :
  // 920:   Error "
  // 921:     @quot;@(c_filename)" does not exist!
  frame->slots[6] /* temp__2 */ = create_closure(entry__83_6, 0);
  // 919: if c_info.is_undefined:
  // 920:   Error "
  // 921:     @quot;@(c_filename)" does not exist!
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__83_10;
}
static void entry__83_6(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // c_filename: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* c_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 920: ... "
  // 921:   @quot;@(c_filename)" does not exist!
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__83_7;
  arguments->slots[1] = frame->slots[0] /* c_filename */;
  arguments->slots[2] = string__83_8;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__83_9;
}
static void cont__83_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 920: Error "
  // 921:   @quot;@(c_filename)" does not exist!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__83_10(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 922: $o_info stat(o_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* o_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__83_11;
}
static void cont__83_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* o_info */, arguments->slots[0]);
  // 925: o_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* o_info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__83_12;
}
static void cont__83_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 926: modification_time_of(c_info) > modification_time_of(o_info)
  frame->slots[7] /* temp__3 */ = create_closure(entry__83_13, 0);
  // 924: ||
  // 925:   o_info.is_undefined
  // 926:   modification_time_of(c_info) > modification_time_of(o_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__83_17;
}
static void entry__83_13(void) {
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
  // 926: ... modification_time_of(o_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* o_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__83_14;
}
static void cont__83_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 926: modification_time_of(c_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* c_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__83_15;
}
static void cont__83_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 926: modification_time_of(c_info) > modification_time_of(o_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__83_16;
}
static void cont__83_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 926: modification_time_of(c_info) > modification_time_of(o_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__83_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 927: :
  // 928:   if verbose: ewriteln "compiling runtime module @(filename)"
  // 929:   compile_c c_filename o_filename
  frame->slots[8] /* temp__4 */ = create_closure(entry__83_18, 0);
  // 923: if
  // 924:   ||
  // 925:     o_info.is_undefined
  // 926:     modification_time_of(c_info) > modification_time_of(o_info)
  // 927:   :
  // 928:     if verbose: ewriteln "compiling runtime module @(filename)"
  // 929:     compile_c c_filename o_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__85_1_format_number(void) {
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
  // 939: to_string &val
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* val */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__85_2;
}
static void cont__85_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* val */ = arguments->slots[0];
  // 940: $$ac 0
  ((CELL *)frame->slots[3])->contents /* ac */ = number__0;
  // 941: ... : (-> break)
  // 942:   for_each val: (i chr)
  // 943:     if chr == '.':
  // 944:       !ac length_of(val)-i
  // 945:       if n > i-1: append dup(" " n-(i-1)) &val
  // 946:       break
  frame->slots[4] /* temp__1 */ = create_closure(entry__85_3, 0);
  // 941: do: (-> break)
  // 942:   for_each val: (i chr)
  // 943:     if chr == '.':
  // 944:       !ac length_of(val)-i
  // 945:       if n > i-1: append dup(" " n-(i-1)) &val
  // 946:       break
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__85_19;
}
static void entry__85_3(void) {
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
  // 942: ... : (i chr)
  // 943:   if chr == '.':
  // 944:     !ac length_of(val)-i
  // 945:     if n > i-1: append dup(" " n-(i-1)) &val
  // 946:     break
  frame->slots[4] /* temp__1 */ = create_closure(entry__85_4, 2);
  // 942: for_each val: (i chr)
  // 943:   if chr == '.':
  // 944:     !ac length_of(val)-i
  // 945:     if n > i-1: append dup(" " n-(i-1)) &val
  // 946:     break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* val */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__85_18;
}
static void entry__85_6(void) {
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
  // 944: ... length_of(val)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* val */;
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
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 944: !ac length_of(val)-i
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* i */;
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
  ((CELL *)frame->slots[0])->contents /* ac */ = arguments->slots[0];
  // 945: ... i-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* i */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__85_9;
}
static void cont__85_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 945: ... n > i-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* n */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__85_10;
}
static void cont__85_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 945: ... : append dup(" " n-(i-1)) &val
  frame->slots[7] /* temp__3 */ = create_closure(entry__85_11, 0);
  // 945: if n > i-1: append dup(" " n-(i-1)) &val
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__85_17;
}
static void entry__85_11(void) {
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
  // 945: ... i-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* i */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__85_12;
}
static void cont__85_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 945: ... n-(i-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* n */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__85_13;
}
static void cont__85_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 945: ... dup(" " n-(i-1))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__85_14;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__85_15;
}
static void cont__85_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 945: ... append dup(" " n-(i-1)) &val
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* val */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__85_16;
}
static void cont__85_16(void) {
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
static void cont__85_17(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 946: break
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[4] /* break */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__85_4(void) {
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
  // 943: ... chr == '.'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* chr */;
  arguments->slots[1] = character__46;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__85_5;
}
static void cont__85_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 943: ... :
  // 944:   !ac length_of(val)-i
  // 945:   if n > i-1: append dup(" " n-(i-1)) &val
  // 946:   break
  frame->slots[7] /* temp__2 */ = create_closure(entry__85_6, 0);
  // 943: if chr == '.':
  // 944:   !ac length_of(val)-i
  // 945:   if n > i-1: append dup(" " n-(i-1)) &val
  // 946:   break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__85_18(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__85_19(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 948: m > ac
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* ac */;
  arguments->slots[1] = frame->slots[2] /* m */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__85_20;
}
static void cont__85_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 948: ... :
  // 949:   append &val dup("0" m-ac)
  frame->slots[5] /* temp__2 */ = create_closure(entry__85_21, 0);
  // 950: :
  // 951:   if ac > m: range &val 1 -(ac-m+1)
  frame->slots[6] /* temp__3 */ = create_closure(entry__85_26, 0);
  // 947: if
  // 948:   m > ac:
  // 949:     append &val dup("0" m-ac)
  // 950:   :
  // 951:     if ac > m: range &val 1 -(ac-m+1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__85_33;
}
static void entry__85_28(void) {
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
  // 951: ... ac-m
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* ac */;
  arguments->slots[1] = frame->slots[2] /* m */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__85_29;
}
static void cont__85_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 951: ... ac-m+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__85_30;
}
static void cont__85_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 951: ... ac-m+1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__85_31;
}
static void cont__85_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 951: ... range &val 1 -(ac-m+1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* val */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__85_32;
}
static void cont__85_32(void) {
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
static void entry__85_21(void) {
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
  // 949: ... m-ac
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* m */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* ac */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__85_22;
}
static void cont__85_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 949: ... dup("0" m-ac)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__85_23;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__85_24;
}
static void cont__85_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 949: append &val dup("0" m-ac)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* val */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__85_25;
}
static void cont__85_25(void) {
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
static void entry__85_26(void) {
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
  // 951: ... ac > m
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* m */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* ac */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__85_27;
}
static void cont__85_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 951: ... : range &val 1 -(ac-m+1)
  frame->slots[4] /* temp__2 */ = create_closure(entry__85_28, 0);
  // 951: if ac > m: range &val 1 -(ac-m+1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__85_33(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 952: -> val
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* val */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__86_1_sim2c__write_timing_info(void) {
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
  // 955: $new_t current_time()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__current_time();
  func = myself->type;
  frame->cont = cont__86_2;
}
static void cont__86_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* new_t */, arguments->slots[0]);
  // 957: filename.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* filename */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__86_3;
}
static void cont__86_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 957: ... :
  // 958:   truncate_until &filename '/' -1
  // 959:   ewriteln
  // 960:     description
  // 961:     ' '
  // 962:     filename
  // 963:     ':'
  // 964:     dup(" " 12-length_of(description))
  // 965:     format_number(new_t-t 2 3)
  // 966:     " s"
  frame->slots[4] /* temp__2 */ = create_closure(entry__86_4, 0);
  // 967: :
  // 968:   ewriteln description ": " format_number(new_t-t 0 3) " s"
  frame->slots[5] /* temp__3 */ = create_closure(entry__86_13, 0);
  // 956: if
  // 957:   filename.is_defined:
  // 958:     truncate_until &filename '/' -1
  // 959:     ewriteln
  // 960:       description
  // 961:       ' '
  // 962:       filename
  // 963:       ':'
  // 964:       dup(" " 12-length_of(description))
  // 965:       format_number(new_t-t 2 3)
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = frame->slots[5] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__86_17;
}
static void entry__86_4(void) {
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
  // 958: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__86_5;
}
static void cont__86_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 958: truncate_until &filename '/' -1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* filename */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__86_6;
}
static void cont__86_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* filename */ = arguments->slots[0];
  // 964: ... length_of(description)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* description */;
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
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 964: ... 12-length_of(description)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__12;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
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
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 964: dup(" " 12-length_of(description))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__85_14;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__86_9;
}
static void cont__86_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 965: ... new_t-t
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* new_t */;
  arguments->slots[1] = var._t;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__86_10;
}
static void cont__86_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__5 */ = arguments->slots[0];
  // 965: format_number(new_t-t 2 3)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__5 */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = number__3;
  result_count = 1;
  myself = var._format_number;
  func = myself->type;
  frame->cont = cont__86_11;
}
static void cont__86_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__4 */ = arguments->slots[0];
  // 959: ewriteln
  // 960:   description
  // 961:   ' '
  // 962:   filename
  // 963:   ':'
  // 964:   dup(" " 12-length_of(description))
  // 965:   format_number(new_t-t 2 3)
  // 966:   " s"
  argument_count = 7;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* description */;
  arguments->slots[1] = character__32;
  arguments->slots[2] = ((CELL *)frame->slots[0])->contents /* filename */;
  arguments->slots[3] = character__58;
  arguments->slots[4] = frame->slots[3] /* temp__1 */;
  arguments->slots[5] = frame->slots[6] /* temp__4 */;
  arguments->slots[6] = string__86_12;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__86_13(void) {
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
  // 968: ... new_t-t
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* new_t */;
  arguments->slots[1] = var._t;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__86_14;
}
static void cont__86_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 968: ... format_number(new_t-t 0 3)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = number__0;
  arguments->slots[2] = number__3;
  result_count = 1;
  myself = var._format_number;
  func = myself->type;
  frame->cont = cont__86_15;
}
static void cont__86_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 968: ewriteln description ": " format_number(new_t-t 0 3) " s"
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* description */;
  arguments->slots[1] = string__86_16;
  arguments->slots[2] = frame->slots[2] /* temp__1 */;
  arguments->slots[3] = string__86_12;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__86_17(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 969: !t current_time()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__current_time();
  func = myself->type;
  frame->cont = cont__86_18;
}
static void cont__86_18(void) {
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
static void entry__87_114(void) {
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
  // 1064: exe_filename .has_prefix. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* exe_filename */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__87_115;
}
static void cont__87_115(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 1065: -> exe_filename
  frame->slots[4] /* temp__3 */ = create_closure(entry__87_116, 0);
  // 1066: -> string("./" exe_filename)
  frame->slots[5] /* temp__4 */ = create_closure(entry__87_117, 0);
  // 1063: if
  // 1064:   exe_filename .has_prefix. '/'
  // 1065:   -> exe_filename
  // 1066:   -> string("./" exe_filename)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  arguments->slots[2] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__87_119;
}
static void entry__87_116(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // exe_filename: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* exe_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1065: -> exe_filename
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* exe_filename */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__87_117(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // exe_filename: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* exe_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1066: ... string("./" exe_filename)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__69_56;
  arguments->slots[1] = frame->slots[0] /* exe_filename */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__87_118;
}
static void cont__87_118(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1066: -> string("./" exe_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__87_119(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1062: exec
  // 1063:   if
  // 1064:     exe_filename .has_prefix. '/'
  // 1065:     -> exe_filename
  // 1066:     -> string("./" exe_filename)
  // 1067:   zz*
  // 1068:   
  // 1069:   #range(command_line_arguments 2 -1)*
  argument_count = 0;
  arguments = node_p;
  arguments->slots[argument_count++] = frame->slots[2] /* temp__1 */;
  unfold(frame->slots[1] /* zz */);
  result_count = frame->caller_result_count;
  myself = get__exec();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__87_2(void) {
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
  // 984: current_platform == "cygwin"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__current_platform();
  arguments->slots[1] = string__82_35;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__87_3;
}
static void cont__87_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 985: -> string(mod_filename ".exe")
  frame->slots[10] /* temp__2 */ = create_closure(entry__87_4, 0);
  // 986: -> mod_filename
  frame->slots[11] /* temp__3 */ = create_closure(entry__87_7, 0);
  // 982: $exe_filename
  // 983:   if
  // 984:     current_platform == "cygwin"
  // 985:     -> string(mod_filename ".exe")
  // 986:     -> mod_filename
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__2 */;
  arguments->slots[2] = frame->slots[11] /* temp__3 */;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__87_8;
}
static void entry__87_4(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // mod_filename: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* mod_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 985: ... string(mod_filename ".exe")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = string__87_5;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__87_6;
}
static void cont__87_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 985: -> string(mod_filename ".exe")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__87_7(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // mod_filename: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* mod_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 986: -> mod_filename
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__87_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* exe_filename */, arguments->slots[0]);
  // 988: ... : ewriteln "build executable " exe_filename
  frame->slots[9] /* temp__1 */ = create_closure(entry__87_9, 0);
  // 988: if verbose: ewriteln "build executable " exe_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__87_11;
}
static void entry__87_9(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // exe_filename: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* exe_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 988: ... ewriteln "build executable " exe_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__87_10;
  arguments->slots[1] = frame->slots[0] /* exe_filename */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__87_11(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 989: $c_filename string(mod_filename ".c")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = string__69_9;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__87_12;
}
static void cont__87_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* c_filename */, arguments->slots[0]);
  // 990: $o_filename string(mod_filename ".o")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = string__71_80;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__87_13;
}
static void cont__87_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* o_filename */, arguments->slots[0]);
  // 991: $sim_info stat(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__87_14;
}
static void cont__87_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* sim_info */, arguments->slots[0]);
  // 992: $c_info stat(c_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* c_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__87_15;
}
static void cont__87_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* c_info */, arguments->slots[0]);
  // 993: $$c_buf undefined
  ((CELL *)frame->slots[7])->contents /* c_buf */ = get__undefined();
  // 994: !objects(o_filename) true
  frame->slots[9] /* temp__1 */ = get__true();
  // 994: !objects(o_filename)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* o_filename */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = get__objects();
  func = myself->type;
  frame->cont = cont__87_16;
}
static void cont__87_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__objects(arguments->slots[0]);
  frame->slots[10] /* temp__2 */ = create_closure(entry__87_17, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_rebuild;
  arguments->slots[1] = frame->slots[10] /* temp__2 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__87_24;
}
static void entry__87_17(void) {
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
  // 998: c_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__87_18;
}
static void cont__87_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 999: modification_time_of(sim_info) > modification_time_of(c_info)
  frame->slots[4] /* temp__3 */ = create_closure(entry__87_19, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__87_23;
}
static void entry__87_19(void) {
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
  // 999: ... modification_time_of(c_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__87_20;
}
static void cont__87_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 999: modification_time_of(sim_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* sim_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__87_21;
}
static void cont__87_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 999: modification_time_of(sim_info) > modification_time_of(c_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__87_22;
}
static void cont__87_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 999: modification_time_of(sim_info) > modification_time_of(c_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__87_23(void) {
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
static void cont__87_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 1000: :
  // 1001:   %sim2c::module_name mod_name .without_suffix. some(".meta")
  // 1002:   if verbose: ewriteln "build main module " module_name
  // 1003:   collect_output $c_source: sim2c list(main_filename) true
  // 1004:   collect_output !c_buf: create_imports c_source
  // 1005:   save c_filename c_buf.to_utf8
  // 1006:   if do_time_passes: write_timing_info "saving" c_filename
  // 1007:   compile_c c_filename o_filename
  // 1008:   if do_time_passes: write_timing_info "compiling" c_filename
  frame->slots[11] /* temp__3 */ = create_closure(entry__87_25, 0);
  // 1009: :
  // 1010:   load !c_buf c_filename
  // 1011:   $o_info stat(o_filename)
  // 1012:   if
  // 1013:     ||
  // 1014:       o_info.is_undefined
  // 1015:       modification_time_of(c_info) > modification_time_of(o_info)
  // 1016:     :
  // 1017:       compile_c c_filename o_filename
  // 1018:     :
  // ...
  frame->slots[12] /* temp__4 */ = create_closure(entry__87_45, 0);
  //  995: if
  //  996:   ||
  //  997:     do_rebuild
  //  998:     c_info.is_undefined
  //  999:     modification_time_of(sim_info) > modification_time_of(c_info)
  // 1000:   :
  // 1001:     %sim2c::module_name mod_name .without_suffix. some(".meta")
  // 1002:     if verbose: ewriteln "build main module " module_name
  // 1003:     collect_output $c_source: sim2c list(main_filename) true
  // 1004:     collect_output !c_buf: create_imports c_source
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = frame->slots[11] /* temp__3 */;
  arguments->slots[2] = frame->slots[12] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__87_57;
}
static void entry__87_54(void) {
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
  // 1017: compile_c c_filename o_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_filename */;
  arguments->slots[1] = frame->slots[1] /* o_filename */;
  result_count = frame->caller_result_count;
  myself = var._compile_c;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__87_55(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // o_info: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* o_info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1019: !last_modification_time modification_time_of(o_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* o_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__87_56;
}
static void cont__87_56(void) {
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
static void entry__87_25(void) {
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
  // 1001: ... some(".meta")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__65_16;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__87_26;
}
static void cont__87_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 1001: %sim2c::module_name mod_name .without_suffix. some(".meta")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* mod_name */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = get__without_suffix();
  func = myself->type;
  frame->cont = cont__87_27;
}
static void cont__87_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(get__sim2c__module_name(), arguments->slots[0]);
  // 1002: if verbose: ewriteln "build main module " module_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = func__87_28;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__87_30;
}
static void entry__87_28(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1002: ... ewriteln "build main module " module_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__87_29;
  arguments->slots[1] = get__module_name();
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__87_30(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1003: collect_output $c_source: sim2c list(main_filename) true
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__87_31;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__87_33;
}
static void entry__87_31(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1003: ... list(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__87_32;
}
static void cont__87_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1003: ... sim2c list(main_filename) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = get__true();
  result_count = frame->caller_result_count;
  myself = get__sim2c();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__87_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* c_source */, arguments->slots[0]);
  // 1004: ... : create_imports c_source
  frame->slots[6] /* temp__1 */ = create_closure(entry__87_34, 0);
  // 1004: collect_output !c_buf: create_imports c_source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__87_35;
}
static void entry__87_34(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // c_source: 0
  frame->slots[0] = myself->closure.frame->slots[5]; /* c_source */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1004: ... create_imports c_source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_source */;
  result_count = frame->caller_result_count;
  myself = var._create_imports;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__87_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* c_buf */ = arguments->slots[0];
  // 1005: ... c_buf.to_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* c_buf */;
  result_count = 1;
  myself = get__to_utf8();
  func = myself->type;
  frame->cont = cont__87_36;
}
static void cont__87_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 1005: save c_filename c_buf.to_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* c_filename */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 0;
  myself = get__save();
  func = myself->type;
  frame->cont = cont__87_37;
}
static void cont__87_37(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1006: ... : write_timing_info "saving" c_filename
  frame->slots[6] /* temp__1 */ = create_closure(entry__87_38, 0);
  // 1006: if do_time_passes: write_timing_info "saving" c_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__87_40;
}
static void entry__87_38(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // c_filename: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* c_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1006: ... write_timing_info "saving" c_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__87_39;
  arguments->slots[1] = frame->slots[0] /* c_filename */;
  result_count = frame->caller_result_count;
  myself = get__write_timing_info();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__87_40(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1007: compile_c c_filename o_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* c_filename */;
  arguments->slots[1] = frame->slots[4] /* o_filename */;
  result_count = 0;
  myself = var._compile_c;
  func = myself->type;
  frame->cont = cont__87_41;
}
static void cont__87_41(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1008: ... : write_timing_info "compiling" c_filename
  frame->slots[6] /* temp__1 */ = create_closure(entry__87_42, 0);
  // 1008: if do_time_passes: write_timing_info "compiling" c_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__87_44;
}
static void entry__87_42(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // c_filename: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* c_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1008: ... write_timing_info "compiling" c_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__87_43;
  arguments->slots[1] = frame->slots[0] /* c_filename */;
  result_count = frame->caller_result_count;
  myself = get__write_timing_info();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__87_44(void) {
  myself = frame->slots[0] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__87_45(void) {
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
  // 1010: load !c_buf c_filename
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* c_filename */;
  result_count = 1;
  myself = get__load();
  func = myself->type;
  frame->cont = cont__87_46;
}
static void cont__87_46(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* c_buf */ = arguments->slots[0];
  // 1011: $o_info stat(o_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* o_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__87_47;
}
static void cont__87_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* o_info */, arguments->slots[0]);
  // 1014: o_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* o_info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__87_48;
}
static void cont__87_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 1015: modification_time_of(c_info) > modification_time_of(o_info)
  frame->slots[7] /* temp__3 */ = create_closure(entry__87_49, 0);
  // 1013: ||
  // 1014:   o_info.is_undefined
  // 1015:   modification_time_of(c_info) > modification_time_of(o_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__87_53;
}
static void entry__87_49(void) {
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
  // 1015: ... modification_time_of(o_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* o_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__87_50;
}
static void cont__87_50(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 1015: modification_time_of(c_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* c_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__87_51;
}
static void cont__87_51(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 1015: modification_time_of(c_info) > modification_time_of(o_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__87_52;
}
static void cont__87_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1015: modification_time_of(c_info) > modification_time_of(o_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__87_53(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 1016: :
  // 1017:   compile_c c_filename o_filename
  frame->slots[8] /* temp__4 */ = create_closure(entry__87_54, 0);
  // 1018: :
  // 1019:   !last_modification_time modification_time_of(o_info)
  frame->slots[9] /* temp__5 */ = create_closure(entry__87_55, 0);
  // 1012: if
  // 1013:   ||
  // 1014:     o_info.is_undefined
  // 1015:     modification_time_of(c_info) > modification_time_of(o_info)
  // 1016:   :
  // 1017:     compile_c c_filename o_filename
  // 1018:   :
  // 1019:     !last_modification_time modification_time_of(o_info)
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
static void cont__87_57(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1020: build_dependencies mod_filename mod_name c_buf
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = frame->slots[1] /* mod_name */;
  arguments->slots[2] = ((CELL *)frame->slots[7])->contents /* c_buf */;
  result_count = 0;
  myself = var._build_dependencies;
  func = myself->type;
  frame->cont = cont__87_58;
}
static void cont__87_58(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1021: if do_build_static_executable:
  // 1022:   for_each
  // 1023:     "runtime/linker", "runtime/memory", "runtime/debugger": (filename)
  // 1024:       maybe_compile_c_file filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_build_static_executable();
  arguments->slots[1] = func__87_59;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__87_65;
}
static void entry__87_64(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // filename: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 1024: maybe_compile_c_file filename
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  result_count = frame->caller_result_count;
  myself = var._maybe_compile_c_file;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__87_59(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1023: "runtime/linker", "runtime/memory", "runtime/debugger"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__87_60;
  arguments->slots[1] = string__87_61;
  arguments->slots[2] = string__87_62;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__87_63;
}
static void cont__87_63(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1022: for_each
  // 1023:   "runtime/linker", "runtime/memory", "runtime/debugger": (filename)
  // 1024:     maybe_compile_c_file filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__87_64;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__87_65(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1025: ... :
  // 1026:   $info stat(exe_filename)
  // 1027:   if
  // 1028:     ||
  // 1029:       info.is_undefined
  // 1030:       &&
  // 1031:         last_modification_time.is_defined
  // 1032:         last_modification_time > modification_time_of(info)
  // 1033:     :
  // 1034:       !do_link true
  frame->slots[9] /* temp__1 */ = create_closure(entry__87_66, 0);
  // 1025: unless do_link:
  // 1026:   $info stat(exe_filename)
  // 1027:   if
  // 1028:     ||
  // 1029:       info.is_undefined
  // 1030:       &&
  // 1031:         last_modification_time.is_defined
  // 1032:         last_modification_time > modification_time_of(info)
  // 1033:     :
  // 1034:       !do_link true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_link();
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__87_77;
}
static void entry__87_76(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1034: !do_link true
  set__do_link(get__true());
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__87_66(void) {
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
  // 1026: $info stat(exe_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* exe_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__87_67;
}
static void cont__87_67(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* info */, arguments->slots[0]);
  // 1029: info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__87_68;
}
static void cont__87_68(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 1030: &&
  // 1031:   last_modification_time.is_defined
  // 1032:   last_modification_time > modification_time_of(info)
  frame->slots[4] /* temp__3 */ = create_closure(entry__87_69, 0);
  // 1028: ||
  // 1029:   info.is_undefined
  // 1030:   &&
  // 1031:     last_modification_time.is_defined
  // 1032:     last_modification_time > modification_time_of(info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__87_75;
}
static void entry__87_69(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // info: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1031: last_modification_time.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__last_modification_time();
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__87_70;
}
static void cont__87_70(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 1032: last_modification_time > modification_time_of(info)
  frame->slots[3] /* temp__3 */ = create_closure(entry__87_71, 0);
  // 1030: &&
  // 1031:   last_modification_time.is_defined
  // 1032:   last_modification_time > modification_time_of(info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__87_74;
}
static void entry__87_71(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // info: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1032: ... modification_time_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__87_72;
}
static void cont__87_72(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 1032: last_modification_time > modification_time_of(info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = get__last_modification_time();
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__87_73;
}
static void cont__87_73(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1032: last_modification_time > modification_time_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__87_74(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1030: &&
  // 1031:   last_modification_time.is_defined
  // 1032:   last_modification_time > modification_time_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__87_75(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1027: if
  // 1028:   ||
  // 1029:     info.is_undefined
  // 1030:     &&
  // 1031:       last_modification_time.is_defined
  // 1032:       last_modification_time > modification_time_of(info)
  // 1033:   :
  // 1034:     !do_link true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = func__87_76;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__87_77(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1035: ... :
  // 1036:   $$libs_and_files library_paths_and_file_list()
  // 1037:   if do_link_profiler: push &libs_and_files "/usr/lib/libprofiler.so.0"
  // 1038:   if
  // 1039:     do_build_static_executable:
  // 1040:       if verbose: ewriteln "linking static executable"
  // 1041:       Gcc $_out $err $success
  // 1042:         "runtime/linker.o"
  // 1043:         "runtime/memory.o"
  // 1044:         "runtime/debugger.o"
  // ...
  frame->slots[9] /* temp__1 */ = create_closure(entry__87_78, 0);
  // 1035: if do_link:
  // 1036:   $$libs_and_files library_paths_and_file_list()
  // 1037:   if do_link_profiler: push &libs_and_files "/usr/lib/libprofiler.so.0"
  // 1038:   if
  // 1039:     do_build_static_executable:
  // 1040:       if verbose: ewriteln "linking static executable"
  // 1041:       Gcc $_out $err $success
  // 1042:         "runtime/linker.o"
  // 1043:         "runtime/memory.o"
  // 1044:         "runtime/debugger.o"
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_link();
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__87_108;
}
static void entry__87_106(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // err: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* err */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1059: ... err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* err */;
  result_count = 1;
  myself = get__from_utf8();
  func = myself->type;
  frame->cont = cont__87_107;
}
static void cont__87_107(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1059: ... Error err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__87_92(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // err: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* err */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1048: ... err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* err */;
  result_count = 1;
  myself = get__from_utf8();
  func = myself->type;
  frame->cont = cont__87_93;
}
static void cont__87_93(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1048: ... Error err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__87_84(void) {
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
  // 1040: if verbose: ewriteln "linking static executable"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = func__87_85;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__87_87;
}
static void entry__87_85(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1040: ... ewriteln "linking static executable"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__87_86;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__87_87(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1041: Gcc $_out $err $success
  // 1042:   "runtime/linker.o"
  // 1043:   "runtime/memory.o"
  // 1044:   "runtime/debugger.o"
  // 1045:   libs_and_files*
  // 1046:   "-o"
  // 1047:   exe_filename
  argument_count = 0;
  arguments = node_p;
  arguments->slots[argument_count++] = string__87_88;
  arguments->slots[argument_count++] = string__87_89;
  arguments->slots[argument_count++] = string__87_90;
  unfold(((CELL *)frame->slots[0])->contents /* libs_and_files */);
  arguments->slots[argument_count++] = string__68_6;
  arguments->slots[argument_count++] = frame->slots[1] /* exe_filename */;
  result_count = 3;
  myself = var._Gcc;
  func = myself->type;
  frame->cont = cont__87_91;
}
static void cont__87_91(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  frame->slots[6] /* temp__2 */ = arguments->slots[1];
  frame->slots[7] /* temp__3 */ = arguments->slots[2];
  // 1041: ... _out
  initialize_future(frame->slots[2] /* out */, frame->slots[5] /* temp__1 */);
  // 1041: ... err
  initialize_future(frame->slots[3] /* err */, frame->slots[6] /* temp__2 */);
  // 1041: ... success
  initialize_future(frame->slots[4] /* success */, frame->slots[7] /* temp__3 */);
  // 1048: ... : Error err.from_utf8
  frame->slots[5] /* temp__1 */ = create_closure(entry__87_92, 0);
  // 1048: unless success: Error err.from_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* success */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__87_94(void) {
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
  // 1050: if verbose: ewriteln "linking executable"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = func__87_95;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__87_97;
}
static void entry__87_95(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1050: ... ewriteln "linking executable"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__87_96;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__87_97(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1054: current_platform == "linux"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__current_platform();
  arguments->slots[1] = string__75_22;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__87_98;
}
static void cont__87_98(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 1053: if
  // 1054:   current_platform == "linux"
  // 1055:   -> "-l:libsim.so.@(MAJOR)"
  // 1056:   -> "-lsim-@(MAJOR)"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = func__87_99;
  arguments->slots[2] = func__87_102;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__87_104;
}
static void entry__87_99(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1055: ... "-l:libsim.so.@(MAJOR)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__87_100;
  arguments->slots[1] = var._MAJOR;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__87_101;
}
static void cont__87_101(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1055: -> "-l:libsim.so.@(MAJOR)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__87_102(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1056: ... "-lsim-@(MAJOR)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__82_67;
  arguments->slots[1] = var._MAJOR;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__87_103;
}
static void cont__87_103(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1056: -> "-lsim-@(MAJOR)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__87_104(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 1051: Gcc $_out $err $success
  // 1052:   libs_and_files*
  // 1053:   if
  // 1054:     current_platform == "linux"
  // 1055:     -> "-l:libsim.so.@(MAJOR)"
  // 1056:     -> "-lsim-@(MAJOR)"
  // 1057:   "-o"
  // 1058:   exe_filename
  argument_count = 0;
  arguments = node_p;
  unfold(((CELL *)frame->slots[0])->contents /* libs_and_files */);
  arguments->slots[argument_count++] = frame->slots[5] /* temp__1 */;
  arguments->slots[argument_count++] = string__68_6;
  arguments->slots[argument_count++] = frame->slots[1] /* exe_filename */;
  result_count = 3;
  myself = var._Gcc;
  func = myself->type;
  frame->cont = cont__87_105;
}
static void cont__87_105(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__3 */ = arguments->slots[0];
  frame->slots[8] /* temp__4 */ = arguments->slots[1];
  frame->slots[9] /* temp__5 */ = arguments->slots[2];
  // 1051: ... _out
  initialize_future(frame->slots[2] /* out */, frame->slots[7] /* temp__3 */);
  // 1051: ... err
  initialize_future(frame->slots[3] /* err */, frame->slots[8] /* temp__4 */);
  // 1051: ... success
  initialize_future(frame->slots[4] /* success */, frame->slots[9] /* temp__5 */);
  // 1059: ... : Error err.from_utf8
  frame->slots[5] /* temp__1 */ = create_closure(entry__87_106, 0);
  // 1059: unless success: Error err.from_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* success */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__87_78(void) {
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
  // 1036: $$libs_and_files library_paths_and_file_list()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = var._library_paths_and_file_list;
  func = myself->type;
  frame->cont = cont__87_79;
}
static void cont__87_79(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* libs_and_files */ = arguments->slots[0];
  // 1037: ... : push &libs_and_files "/usr/lib/libprofiler.so.0"
  frame->slots[2] /* temp__1 */ = create_closure(entry__87_80, 0);
  // 1037: if do_link_profiler: push &libs_and_files "/usr/lib/libprofiler.so.0"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_link_profiler;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__87_83;
}
static void entry__87_80(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // libs_and_files: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* libs_and_files */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1037: ... push &libs_and_files "/usr/lib/libprofiler.so.0"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* libs_and_files */;
  arguments->slots[1] = string__87_81;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__87_82;
}
static void cont__87_82(void) {
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
static void cont__87_83(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1039: ... :
  // 1040:   if verbose: ewriteln "linking static executable"
  // 1041:   Gcc $_out $err $success
  // 1042:     "runtime/linker.o"
  // 1043:     "runtime/memory.o"
  // 1044:     "runtime/debugger.o"
  // 1045:     libs_and_files*
  // 1046:     "-o"
  // 1047:     exe_filename
  // 1048:   unless success: Error err.from_utf8
  frame->slots[2] /* temp__1 */ = create_closure(entry__87_84, 0);
  // 1049: :
  // 1050:   if verbose: ewriteln "linking executable"
  // 1051:   Gcc $_out $err $success
  // 1052:     libs_and_files*
  // 1053:     if
  // 1054:       current_platform == "linux"
  // 1055:       -> "-l:libsim.so.@(MAJOR)"
  // 1056:       -> "-lsim-@(MAJOR)"
  // 1057:     "-o"
  // 1058:     exe_filename
  // ...
  frame->slots[3] /* temp__2 */ = create_closure(entry__87_94, 0);
  // 1038: if
  // 1039:   do_build_static_executable:
  // 1040:     if verbose: ewriteln "linking static executable"
  // 1041:     Gcc $_out $err $success
  // 1042:       "runtime/linker.o"
  // 1043:       "runtime/memory.o"
  // 1044:       "runtime/debugger.o"
  // 1045:       libs_and_files*
  // 1046:       "-o"
  // 1047:       exe_filename
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
static void cont__87_108(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1060: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__87_109;
}
static void cont__87_109(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 1060: $zz range(command_line_arguments 2 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__command_line_arguments();
  arguments->slots[1] = number__2;
  arguments->slots[2] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__87_110;
}
static void cont__87_110(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[8] /* zz */, arguments->slots[0]);
  // 1061: ... on_top_level && action == "simrun"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__on_top_level();
  arguments->slots[1] = func__87_111;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__87_113;
}
static void entry__87_111(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1061: ... action == "simrun"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._action;
  arguments->slots[1] = string__82_2;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__87_112;
}
static void cont__87_112(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1061: ... action == "simrun"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__87_113(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 1061: ... :
  // 1062:   exec
  // 1063:     if
  // 1064:       exe_filename .has_prefix. '/'
  // 1065:       -> exe_filename
  // 1066:       -> string("./" exe_filename)
  // 1067:     zz*
  // 1068:     
  // 1069:     #range(command_line_arguments 2 -1)*
  frame->slots[10] /* temp__2 */ = create_closure(entry__87_114, 0);
  // 1061: if on_top_level && action == "simrun":
  // 1062:   exec
  // 1063:     if
  // 1064:       exe_filename .has_prefix. '/'
  // 1065:       -> exe_filename
  // 1066:       -> string("./" exe_filename)
  // 1067:     zz*
  // 1068:     
  // 1069:     #range(command_line_arguments 2 -1)*
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__87_1_build_executable(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 981: compile_exe: (mod_filename mod_name)
  // 982:   $exe_filename
  // 983:     if
  // 984:       current_platform == "cygwin"
  // 985:       -> string(mod_filename ".exe")
  // 986:       -> mod_filename
  // 987:   
  // 988:   if verbose: ewriteln "build executable " exe_filename
  // 989:   $c_filename string(mod_filename ".c")
  // 990:   $o_filename string(mod_filename ".o")
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__87_2;
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
  var.sim2c__do_use_goto = collect_node(var.sim2c__do_use_goto);
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
  func__48_1_sim2c__show_compiler_debug_info = create_function(entry__48_1_sim2c__show_compiler_debug_info, -1);
  unique__EXE = register_unique_item("EXE");
  unique__LIB = register_unique_item("LIB");
  func__64_8 = create_function(entry__64_8, 1);
  func__64_4 = create_function(entry__64_4, 1);
  func__64_3 = create_function(entry__64_3, 0);
  string__64_21 = from_latin_1_string("Cannot resolve required library \042", 33);
  string__64_22 = from_latin_1_string("\042!", 2);
  func__64_1_resolve_filename = create_function(entry__64_1_resolve_filename, 1);
  string__65_13 = from_latin_1_string(".sim", 4);
  string__65_16 = from_latin_1_string(".meta", 5);
  string__65_42 = from_latin_1_string("-common", 7);
  string__65_46 = from_latin_1_string("-", 1);
  string__65_58 = from_latin_1_string("The platform \042", 14);
  string__65_59 = from_latin_1_string("\042 is not supported!", 19);
  func__65_1_add_module_infos = create_function(entry__65_1_add_module_infos, 2);
  func__66_1_lookup = create_function(entry__66_1_lookup, 2);
  string__67_4 = from_latin_1_string("gcc ", 4);
  func__67_1_Gcc = create_function(entry__67_1_Gcc, -1);
  func__68_2 = create_function(entry__68_2, 0);
  string__68_5 = from_latin_1_string("-c", 2);
  string__68_6 = from_latin_1_string("-o", 2);
  func__68_1_compile_c = create_function(entry__68_1_compile_c, 2);
  string__69_9 = from_latin_1_string(".c", 2);
  string__69_46 = from_latin_1_string("/// ", 4);
  string__69_53 = from_latin_1_string("data", 4);
  string__69_56 = from_latin_1_string("./", 2);
  func__69_1_compile_meta_module = create_function(entry__69_1_compile_meta_module, 3);
  func__70_24 = create_function(entry__70_24, 0);
  func__70_23 = create_function(entry__70_23, 0);
  string__70_32 = from_latin_1_string("sim-", 4);
  string__70_39 = from_latin_1_string("require", 7);
  string__70_40 = from_latin_1_string("link", 4);
  func__70_1_build_dependencies = create_function(entry__70_1_build_dependencies, -1);
  func__71_9 = create_function(entry__71_9, 0);
  string__71_38 = from_latin_1_string("__", 2);
  string__71_43 = from_latin_1_string("build module ", 13);
  string__71_76 = from_latin_1_string("No source file(s) for module \042", 30);
  string__71_77 = from_latin_1_string("\042 found!", 8);
  string__71_80 = from_latin_1_string(".o", 2);
  string__71_131 = from_latin_1_string(" #", 2);
  func__71_1_compile_module = create_function(entry__71_1_compile_module, 2);
  func__72_1_compile_modules = create_function(entry__72_1_compile_modules, 2);
  string__74_3 = from_latin_1_string("LD_LIBRARY_PATH", 15);
  string__74_7 = from_latin_1_string("LD_LIBRARY_PATH=", 16);
  string__74_11 = from_latin_1_string("included object files: ", 23);
  string__74_14 = from_latin_1_string("needed libraries: ", 18);
  func__74_2 = create_function(entry__74_2, 0);
  func__74_1_show_file_list = create_function(entry__74_1_show_file_list, 0);
  string__75_8 = from_latin_1_string("-L", 2);
  string__75_14 = from_latin_1_string("library paths: ", 15);
  string__75_22 = from_latin_1_string("linux", 5);
  string__75_25 = from_latin_1_string("-l:lib", 6);
  string__75_26 = from_latin_1_string(".so.", 4);
  string__75_29 = from_latin_1_string("-l", 2);
  func__75_1_library_paths_and_file_list = create_function(entry__75_1_library_paths_and_file_list, 0);
  string__76_26 = from_latin_1_string("typedef", 7);
  string__76_30 = from_latin_1_string("REGISTER", 8);
  string__76_44 = from_latin_1_string("typedef struct", 14);
  string__76_55 = from_latin_1_string("IMPORT ", 7);
  func__76_54 = create_function(entry__76_54, 0);
  string__76_65 = from_latin_1_string("// INSERT HERE //", 17);
  string__76_75 = from_latin_1_string("collecting imports", 18);
  func__76_74 = create_function(entry__76_74, 0);
  func__76_1_create_imports = create_function(entry__76_1_create_imports, 1);
  string__77_4 = from_latin_1_string("Expected a source code file!", 28);
  func__77_3 = create_function(entry__77_3, 0);
  string__77_8 = from_latin_1_string("Expected \042.sim\042 file extension in source filename!", 50);
  func__77_7 = create_function(entry__77_7, 0);
  func__77_1_compile_exe = create_function(entry__77_1_compile_exe, 1);
  func__78_2 = create_function(entry__78_2, 2);
  func__78_1_dump_source_or_check = create_function(entry__78_1_dump_source_or_check, 0);
  string__79_19 = from_latin_1_string("writing C-source", 16);
  func__79_18 = create_function(entry__79_18, 0);
  func__79_2 = create_function(entry__79_2, 2);
  func__79_1_print_c = create_function(entry__79_1_print_c, 0);
  func__80_3 = create_function(entry__80_3, 2);
  string__80_18 = from_latin_1_string("list dependencies for ", 22);
  func__80_17 = create_function(entry__80_17, 0);
  func__80_16 = create_function(entry__80_16, 0);
  func__80_24 = create_function(entry__80_24, 2);
  string__80_28 = from_latin_1_string("runtime/linker.c", 16);
  string__80_30 = from_latin_1_string("runtime/memory.c", 16);
  string__80_32 = from_latin_1_string("runtime/debugger.c", 18);
  func__80_23 = create_function(entry__80_23, 0);
  func__80_1_list_dependencies = create_function(entry__80_1_list_dependencies, 0);
  string__81_3 = from_latin_1_string(".codeblocks", 11);
  string__81_8 = from_latin_1_string("The directory \042", 15);
  string__81_9 = from_latin_1_string("\042 already exists!\012", 18);
  string__81_13 = from_latin_1_string("build Code::Blocks project in ", 30);
  string__81_23 = from_latin_1_string("../", 3);
  string__81_25 = from_latin_1_string("/", 1);
  string__81_26 = from_latin_1_string(".cbp", 4);
  string__81_29 = from_latin_1_string("<?xml version=\0421.0\042 encoding=\042UTF-8\042 standalone=\042yes\042 ?>\012<CodeBlocks_project_file>\012  <FileVersion major=\0421\042 minor=\0426\042 />\012  <Project>\012    <Option title=\042", 152);
  string__81_30 = from_latin_1_string("\042 />\012    <Option pch_mode=\0422\042 />\012    <Option compiler=\042gcc\042 />\012    <Build>\012      <Target title=\042debug\042>\012        <Option output=\042bin/debug/", 138);
  string__81_31 = from_latin_1_string("\042 prefix_auto=\0421\042 extension_auto=\0421\042 />\012        <Option object_output=\042obj/debug/\042 />\012        <Option type=\0421\042 />\012        <Option compiler=\042gcc\042 />\012        <Compiler>\012          <Add option=\042-g\042 />\012        </Compiler>\012      </Target>\012    </Build>\012    <Linker>\012", 259);
  string__81_35 = from_latin_1_string("      <Add library=\042", 20);
  string__81_36 = from_latin_1_string("\042 />\012", 5);
  string__81_40 = from_latin_1_string("\012    </Linker>\012    <Compiler>\012      <Add option=\042-Wall\042 />\012    </Compiler>\012    <Unit filename=\042", 95);
  string__81_41 = from_latin_1_string("runtime/common.h\042 />\012    <Unit filename=\042", 41);
  string__81_42 = from_latin_1_string("runtime/linker.h\042 />\012    <Unit filename=\042", 41);
  string__81_43 = from_latin_1_string("runtime/memory.c\042>\012      <Option compilerVar=\042CC\042 />\012    </Unit>\012    <Unit filename=\042", 85);
  string__81_44 = from_latin_1_string("runtime/debugger.c\042>\012      <Option compilerVar=\042CC\042 />\012    </Unit>\012    <Unit filename=\042", 87);
  string__81_45 = from_latin_1_string("runtime/linker.c\042>\012      <Option compilerVar=\042CC\042 />\012    </Unit>\012", 65);
  string__81_51 = from_latin_1_string("\012    <Unit filename=\042", 21);
  string__81_52 = from_latin_1_string("\042>\012      <Option compilerVar=\042CC\042 />\012    </Unit>\012", 49);
  string__81_56 = from_latin_1_string("    <Extensions>\012      <code_completion />\012      <debugger />\012    </Extensions>\012  </Project>\012</CodeBlocks_project_file>\012", 120);
  func__81_2 = create_function(entry__81_2, 2);
  func__81_1_build_codeblocks_project = create_function(entry__81_1_build_codeblocks_project, 0);
  string__82_2 = from_latin_1_string("simrun", 6);
  string__82_5 = from_latin_1_string("Cannot run a directory!", 23);
  func__82_4 = create_function(entry__82_4, 0);
  func__82_7 = create_function(entry__82_7, 0);
  string__82_9 = from_latin_1_string("/VERSION", 8);
  string__82_22 = from_latin_1_string("libsim-", 7);
  string__82_25 = from_latin_1_string(".dll", 4);
  string__82_29 = from_latin_1_string(".dylib", 6);
  string__82_33 = from_latin_1_string(".so", 3);
  string__82_35 = from_latin_1_string("cygwin", 6);
  string__82_36 = from_latin_1_string("darwin", 6);
  string__82_39 = from_latin_1_string("build library ", 14);
  func__82_51 = create_function(entry__82_51, 0);
  string__82_55 = from_latin_1_string("linking dynamic library", 23);
  func__82_54 = create_function(entry__82_54, 0);
  string__82_58 = from_latin_1_string("-Wl,-soname,libsim-", 19);
  string__82_61 = from_latin_1_string("-shared", 7);
  string__82_67 = from_latin_1_string("-lsim-", 6);
  string__82_73 = from_latin_1_string("-Wl,-install_name,libsim-", 25);
  string__82_77 = from_latin_1_string("-dynamiclib", 11);
  func__82_8 = create_function(entry__82_8, 0);
  func__82_1_build_library = create_function(entry__82_1_build_library, 0);
  string__83_7 = from_latin_1_string("\042", 1);
  string__83_8 = from_latin_1_string("\042 does not exist!\012", 18);
  string__83_20 = from_latin_1_string("compiling runtime module ", 25);
  func__83_1_maybe_compile_c_file = create_function(entry__83_1_maybe_compile_c_file, 1);
  string__85_14 = from_latin_1_string(" ", 1);
  string__85_23 = from_latin_1_string("0", 1);
  func__85_1_format_number = create_function(entry__85_1_format_number, -1);
  string__86_12 = from_latin_1_string(" s", 2);
  string__86_16 = from_latin_1_string(": ", 2);
  func__86_1_sim2c__write_timing_info = create_function(entry__86_1_sim2c__write_timing_info, -1);
  string__87_5 = from_latin_1_string(".exe", 4);
  string__87_10 = from_latin_1_string("build executable ", 17);
  string__87_29 = from_latin_1_string("build main module ", 18);
  func__87_28 = create_function(entry__87_28, 0);
  func__87_31 = create_function(entry__87_31, 0);
  string__87_39 = from_latin_1_string("saving", 6);
  string__87_43 = from_latin_1_string("compiling", 9);
  string__87_60 = from_latin_1_string("runtime/linker", 14);
  string__87_61 = from_latin_1_string("runtime/memory", 14);
  string__87_62 = from_latin_1_string("runtime/debugger", 16);
  func__87_64 = create_function(entry__87_64, 1);
  func__87_59 = create_function(entry__87_59, 0);
  func__87_76 = create_function(entry__87_76, 0);
  string__87_81 = from_latin_1_string("/usr/lib/libprofiler.so.0", 25);
  string__87_86 = from_latin_1_string("linking static executable", 25);
  func__87_85 = create_function(entry__87_85, 0);
  string__87_88 = from_latin_1_string("runtime/linker.o", 16);
  string__87_89 = from_latin_1_string("runtime/memory.o", 16);
  string__87_90 = from_latin_1_string("runtime/debugger.o", 18);
  string__87_96 = from_latin_1_string("linking executable", 18);
  func__87_95 = create_function(entry__87_95, 0);
  string__87_100 = from_latin_1_string("-l:libsim.so.", 13);
  func__87_99 = create_function(entry__87_99, 0);
  func__87_102 = create_function(entry__87_102, 0);
  func__87_111 = create_function(entry__87_111, 0);
  func__87_2 = create_function(entry__87_2, 2);
  func__87_1_build_executable = create_function(entry__87_1_build_executable, 0);
  string__91_1 = from_latin_1_string("Copyright (C) 2020 by\012Dipl.-Ing. Michael Niederle\012\012This program is free software; you can redistribute it and/or modify\012it under the terms of the GNU General Public License, version 2, or\012(at your option) version 3.\012\012This program is distributed in the hope that it will be useful,\012but WITHOUT ANY WARRANTY; without even the implied warranty of\012MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the\012GNU General Public License for more details.\012\012For details of the GNU General Public License see the accompanying\012files GPLv2.txt and GLPv3.txt or\012http://www.gnu.org/licenses/gpl-2.0.html\012http://www.gnu.org/licenses/gpl-3.0.html\012or write to the\012Free Software Foundation, Inc.,\01251 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.\012", 742);
  string__96_1 = from_latin_1_string(".", 1);
  string__98_1 = from_latin_1_string("gcc", 3);
  string__99_1 = from_latin_1_string("mkdir", 5);
  string__100_1 = from_latin_1_string("SIMLIBPATH", 10);
  string__101_1 = from_latin_1_string("SIMDATAPATH", 11);
  func__102_2 = create_function(entry__102_2, 0);
  string__102_5 = from_latin_1_string("/usr/local/share/simplicity-", 28);
  string__102_7 = from_latin_1_string("/usr/share/simplicity-", 22);
  func__102_4 = create_function(entry__102_4, 0);
  func__103_2 = create_function(entry__103_2, 0);
  func__103_4 = create_function(entry__103_4, 0);
  string__105_1 = from_latin_1_string("bsd", 3);
  string__105_2 = from_latin_1_string("posix", 5);
  string__105_7 = from_latin_1_string("all", 3);
  string__105_9 = from_latin_1_string("win", 3);
  func__107_1 = create_function(entry__107_1, 0);
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
  string__133_55 = from_latin_1_string("goto", 4);
  string__133_56 = from_latin_1_string("the compiler uses goto-statements to link continuations\012", 56);
  func__133_54 = create_function(entry__133_54, 0);
  string__133_58 = from_latin_1_string("rebuild", 7);
  string__133_59 = from_latin_1_string("rebuild all source files\012", 25);
  func__133_57 = create_function(entry__133_57, 0);
  string__133_61 = from_latin_1_string("omit-meta", 9);
  string__133_62 = from_latin_1_string("do not rebuild meta files\012", 26);
  func__133_60 = create_function(entry__133_60, 0);
  string__133_64 = from_latin_1_string("static", 6);
  string__133_65 = from_latin_1_string("create statically linked executable\012", 36);
  func__133_63 = create_function(entry__133_63, 0);
  string__133_67 = from_latin_1_string("profile", 7);
  string__133_68 = from_latin_1_string("link with libprofiler\012", 22);
  func__133_66 = create_function(entry__133_66, 0);
  string__133_70 = from_latin_1_string("filename", 8);
  string__133_71 = from_latin_1_string("the name of the source file to compile\012", 39);
  func__133_69 = create_function(entry__133_69, 0);
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
  string__163_3 = from_latin_1_string("Source file \042", 13);
  string__163_4 = from_latin_1_string("\042 does not exist!", 17);
  func__163_2 = create_function(entry__163_2, 0);
  func__178_1 = create_function(entry__178_1, 0);
  func__179_4 = create_function(entry__179_4, 0);
  func__179_3 = create_function(entry__179_3, 0);
  func__179_2 = create_function(entry__179_2, 0);
  func__179_1 = create_function(entry__179_1, 0);
  func__179_8 = create_function(entry__179_8, 0);
  func__179_9 = create_function(entry__179_9, 0);
  func__179_10 = create_function(entry__179_10, 0);
  func__179_11 = create_function(entry__179_11, 0);

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
  define_multi_assign_static("sim2c", "do_use_goto", get__sim2c__do_use_goto, set__sim2c__do_use_goto);
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
  use_read_write(NULL, "do_use_goto", &get__do_use_goto, &set__do_use_goto);
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
  assign_variable(&var.sim2c__show_compiler_debug_info, &func__48_1_sim2c__show_compiler_debug_info);
  maybe_initialize_future(get__mode(), get__undefined());
  maybe_initialize_future(get__on_top_level(), get__true());
  assign_variable(&var._resolve_filename, &func__64_1_resolve_filename);
  assign_variable(&var._add_module_infos, &func__65_1_add_module_infos);
  assign_variable(&var._lookup, &func__66_1_lookup);
  assign_variable(&var._Gcc, &func__67_1_Gcc);
  assign_variable(&var._compile_c, &func__68_1_compile_c);
  assign_variable(&var._compile_meta_module, &func__69_1_compile_meta_module);
  assign_variable(&var._build_dependencies, &func__70_1_build_dependencies);
  assign_variable(&var._compile_module, &func__71_1_compile_module);
  assign_variable(&var._compile_modules, &func__72_1_compile_modules);
  assign_variable(&var._show_file_list, &func__74_1_show_file_list);
  assign_variable(&var._library_paths_and_file_list, &func__75_1_library_paths_and_file_list);
  assign_variable(&var._create_imports, &func__76_1_create_imports);
  assign_variable(&var._compile_exe, &func__77_1_compile_exe);
  assign_variable(&var._dump_source_or_check, &func__78_1_dump_source_or_check);
  assign_variable(&var._print_c, &func__79_1_print_c);
  assign_variable(&var._list_dependencies, &func__80_1_list_dependencies);
  assign_variable(&var._build_codeblocks_project, &func__81_1_build_codeblocks_project);
  assign_variable(&var._build_library, &func__82_1_build_library);
  assign_variable(&var._maybe_compile_c_file, &func__83_1_maybe_compile_c_file);
  assign_variable(&var._format_number, &func__85_1_format_number);
  assign_variable(&var.sim2c__write_timing_info, &func__86_1_sim2c__write_timing_info);
  assign_variable(&var._build_executable, &func__87_1_build_executable);
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
