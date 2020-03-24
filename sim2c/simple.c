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
IMPORT NODE *create_function(FUNC func, int par_count);
IMPORT NODE *from_latin_1_string(const char *str, long len);
IMPORT void initialize_phase_3(void);
IMPORT void resolve_symbols(void);
IMPORT void set_module(const char *name);
IMPORT void set_used_namespaces(const char **namespaces);
IMPORT NODE *register_unique_item(const char *name);
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
static NODE *unique__13_1;
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
static NODE *func__47_1;
static void entry__47_1(void);
static FRAME_INFO frame__47_1 = {1, {"args"}};
static NODE *func__47_2;
static void entry__47_2(void);
static FRAME_INFO frame__47_2 = {1, {"args"}};
static NODE *get__sim2c__show_compiler_debug_info(void) {
  return var.sim2c__show_compiler_debug_info;
}
static NODE *unique__48_1;
static NODE *unique__49_1;
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
static NODE *func__63_1;
static void entry__63_1(void);
static FRAME_INFO frame__63_1 = {3, {"filename", "libname", "libpath"}};
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
static FRAME_INFO frame__63_6 = {1, {"entry"}};
static void cont__63_7(void);
static NODE *func__63_8;
static void entry__63_8(void);
static FRAME_INFO frame__63_8 = {2, {"entry", "name"}};
static void cont__63_9(void);
static void cont__63_10(void);
static NODE *func__63_11;
static void entry__63_11(void);
static FRAME_INFO frame__63_11 = {2, {"name", "entry"}};
static void cont__63_12(void);
static void cont__63_13(void);
static void cont__63_14(void);
static void cont__63_15(void);
static void cont__63_16(void);
static void cont__63_17(void);
static NODE *func__63_18;
static void entry__63_18(void);
static FRAME_INFO frame__63_18 = {1, {"libname"}};
static NODE *string__63_19;
static NODE *string__63_20;
static void cont__63_21(void);
static void cont__63_22(void);
static void cont__63_23(void);
static void cont__63_24(void);
static NODE *func__64_1;
static void entry__64_1(void);
static FRAME_INFO frame__64_1 = {7, {"path", "mod_path", "return", "entries", "filenames", "directories", "modules"}};
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
static NODE *string__64_18;
static void cont__64_19(void);
static void cont__64_20(void);
static void cont__64_21(void);
static void cont__64_22(void);
static void cont__64_23(void);
static void cont__64_24(void);
static void cont__64_25(void);
static void cont__64_26(void);
static void cont__64_27(void);
static void cont__64_28(void);
static NODE *func__64_29;
static void entry__64_29(void);
static FRAME_INFO frame__64_29 = {2, {"stored_level", "meta_level"}};
static void cont__64_30(void);
static void cont__64_31(void);
static NODE *func__64_32;
static void entry__64_32(void);
static FRAME_INFO frame__64_32 = {2, {"submodule_name", "meta_level"}};
static void cont__64_33(void);
static void cont__64_34(void);
static void cont__64_35(void);
static void cont__64_36(void);
static void cont__64_37(void);
static void cont__64_38(void);
static void cont__64_39(void);
static NODE *func__64_40;
static void entry__64_40(void);
static FRAME_INFO frame__64_40 = {3, {"filename", "filenames", "mod_path"}};
static void cont__64_41(void);
static NODE *func__64_42;
static void entry__64_42(void);
static FRAME_INFO frame__64_42 = {3, {"filename", "filenames", "mod_path"}};
static NODE *string__64_43;
static void cont__64_44(void);
static NODE *func__64_45;
static void entry__64_45(void);
static FRAME_INFO frame__64_45 = {9, {"filenames", "filename", "mod_path", "maybe_push_common", "name", "mod_name", "platform", "parent", "files"}};
static NODE *func__64_46;
static void entry__64_46(void);
static FRAME_INFO frame__64_46 = {5, {"plat", "name", "filenames", "files", "common_name"}};
static NODE *string__64_47;
static NODE *string__64_48;
static void cont__64_49(void);
static void cont__64_50(void);
static NODE *func__64_51;
static void entry__64_51(void);
static FRAME_INFO frame__64_51 = {2, {"files", "common_name"}};
static void cont__64_52(void);
static void cont__64_53(void);
static void cont__64_54(void);
static void cont__64_55(void);
static void cont__64_56(void);
static void cont__64_57(void);
static void cont__64_58(void);
static NODE *func__64_59;
static void entry__64_59(void);
static FRAME_INFO frame__64_59 = {1, {"platform"}};
static NODE *string__64_60;
static NODE *string__64_61;
static void cont__64_62(void);
static void cont__64_63(void);
static void cont__64_64(void);
static void cont__64_65(void);
static NODE *func__64_66;
static void entry__64_66(void);
static FRAME_INFO frame__64_66 = {2, {"parent", "maybe_push_common"}};
static void cont__64_67(void);
static void cont__64_68(void);
static NODE *func__64_69;
static void entry__64_69(void);
static FRAME_INFO frame__64_69 = {2, {"maybe_push_common", "parent"}};
static void cont__64_70(void);
static void cont__64_71(void);
static void cont__64_72(void);
static void cont__64_73(void);
static void cont__64_74(void);
static void cont__64_75(void);
static void cont__64_76(void);
static void cont__64_77(void);
static void cont__64_78(void);
static NODE *func__64_79;
static void entry__64_79(void);
static FRAME_INFO frame__64_79 = {3, {"return", "directories", "modules"}};
static void cont__64_80(void);
static NODE *func__65_1;
static void entry__65_1(void);
static FRAME_INFO frame__65_1 = {3, {"mod_filename", "mod_name", "info"}};
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
static NODE *func__66_1;
static void entry__66_1(void);
static FRAME_INFO frame__66_1 = {1, {"args"}};
static NODE *func__66_2;
static void entry__66_2(void);
static FRAME_INFO frame__66_2 = {1, {"args"}};
static void cont__66_3(void);
static NODE *string__66_4;
static void cont__66_5(void);
static NODE *func__67_1;
static void entry__67_1(void);
static FRAME_INFO frame__67_1 = {2, {"c_filename", "o_filename"}};
static NODE *func__67_2;
static void entry__67_2(void);
static FRAME_INFO frame__67_2 = {0, {}};
static void cont__67_3(void);
static NODE *func__67_4;
static void entry__67_4(void);
static FRAME_INFO frame__67_4 = {2, {"c_filename", "o_filename"}};
static NODE *func__67_5;
static void entry__67_5(void);
static FRAME_INFO frame__67_5 = {5, {"c_filename", "o_filename", "out", "err", "success"}};
static NODE *string__67_6;
static NODE *string__67_7;
static void cont__67_8(void);
static NODE *func__67_9;
static void entry__67_9(void);
static FRAME_INFO frame__67_9 = {1, {"err"}};
static void cont__67_10(void);
static NODE *func__67_11;
static void entry__67_11(void);
static FRAME_INFO frame__67_11 = {5, {"c_filename", "o_filename", "out", "err", "success"}};
static NODE *string__67_12;
static NODE *string__67_13;
static NODE *string__67_14;
static NODE *string__67_15;
static void cont__67_16(void);
static NODE *func__67_17;
static void entry__67_17(void);
static FRAME_INFO frame__67_17 = {1, {"err"}};
static void cont__67_18(void);
static void cont__67_19(void);
static NODE *func__68_1;
static void entry__68_1(void);
static FRAME_INFO frame__68_1 = {3, {"mod_filename", "mod_name", "meta_level"}};
static NODE *func__68_2;
static void entry__68_2(void);
static FRAME_INFO frame__68_2 = {11, {"mod_filename", "meta_level", "meta_path", "filename", "meta_filename", "meta_c_filename", "sim_filename", "meta_info", "sim_info", "meta_c_info", "force_rebuild"}};
static void cont__68_3(void);
static void cont__68_4(void);
static NODE *string__68_5;
static void cont__68_6(void);
static void cont__68_7(void);
static NODE *string__68_8;
static void cont__68_9(void);
static NODE *string__68_10;
static void cont__68_11(void);
static NODE *string__68_12;
static void cont__68_13(void);
static void cont__68_14(void);
static NODE *string__68_15;
static void cont__68_16(void);
static NODE *string__68_17;
static void cont__68_18(void);
static void cont__68_19(void);
static void cont__68_20(void);
static void cont__68_21(void);
static NODE *func__68_22;
static void entry__68_22(void);
static FRAME_INFO frame__68_22 = {3, {"sim_info", "meta_c_info", "meta_info"}};
static void cont__68_23(void);
static NODE *func__68_24;
static void entry__68_24(void);
static FRAME_INFO frame__68_24 = {3, {"meta_c_info", "meta_info", "sim_info"}};
static void cont__68_25(void);
static NODE *func__68_26;
static void entry__68_26(void);
static FRAME_INFO frame__68_26 = {3, {"meta_c_info", "meta_info", "sim_info"}};
static void cont__68_27(void);
static void cont__68_28(void);
static void cont__68_29(void);
static NODE *func__68_30;
static void entry__68_30(void);
static FRAME_INFO frame__68_30 = {2, {"sim_info", "meta_c_info"}};
static void cont__68_31(void);
static void cont__68_32(void);
static void cont__68_33(void);
static void cont__68_34(void);
static void cont__68_35(void);
static void cont__68_36(void);
static void cont__68_37(void);
static NODE *func__68_38;
static void entry__68_38(void);
static FRAME_INFO frame__68_38 = {6, {"sim_info", "meta_c_filename", "force_rebuild", "meta_path", "modification_time", "meta_c_buf"}};
static void cont__68_39(void);
static void cont__68_40(void);
static NODE *func__68_41;
static void entry__68_41(void);
static FRAME_INFO frame__68_41 = {5, {"break", "meta_c_buf", "modification_time", "force_rebuild", "meta_path"}};
static NODE *func__68_42;
static void entry__68_42(void);
static FRAME_INFO frame__68_42 = {8, {"line", "modification_time", "force_rebuild", "break", "meta_path", "check", "command", "argument"}};
static NODE *func__68_43;
static void entry__68_43(void);
static FRAME_INFO frame__68_43 = {5, {"data_filename", "modification_time", "force_rebuild", "break", "data_info"}};
static void cont__68_44(void);
static void cont__68_45(void);
static NODE *func__68_46;
static void entry__68_46(void);
static FRAME_INFO frame__68_46 = {2, {"modification_time", "data_info"}};
static void cont__68_47(void);
static void cont__68_48(void);
static void cont__68_49(void);
static NODE *func__68_50;
static void entry__68_50(void);
static FRAME_INFO frame__68_50 = {2, {"force_rebuild", "break"}};
static NODE *string__68_51;
static void cont__68_52(void);
static void cont__68_53(void);
static void cont__68_54(void);
static void cont__68_55(void);
static void cont__68_56(void);
static void cont__68_57(void);
static NODE *string__68_58;
static void cont__68_59(void);
static NODE *func__68_60;
static void entry__68_60(void);
static FRAME_INFO frame__68_60 = {3, {"argument", "check", "meta_path"}};
static NODE *string__68_61;
static void cont__68_62(void);
static NODE *func__68_63;
static void entry__68_63(void);
static FRAME_INFO frame__68_63 = {3, {"check", "meta_path", "argument"}};
static void cont__68_64(void);
static void cont__68_65(void);
static void cont__68_66(void);
static NODE *func__68_67;
static void entry__68_67(void);
static FRAME_INFO frame__68_67 = {2, {"check", "argument"}};
static NODE *func__68_68;
static void entry__68_68(void);
static FRAME_INFO frame__68_68 = {3, {"path", "check", "argument"}};
static void cont__68_69(void);
static void cont__68_70(void);
static void cont__68_71(void);
static NODE *func__68_72;
static void entry__68_72(void);
static FRAME_INFO frame__68_72 = {9, {"return__1", "meta_filename", "meta_path", "filename", "sim_filename", "orig_path", "out", "err", "success"}};
static void cont__68_73(void);
static void cont__68_74(void);
static void cont__68_75(void);
static void cont__68_76(void);
static void cont__68_77(void);
static void cont__68_78(void);
static NODE *func__68_79;
static void entry__68_79(void);
static FRAME_INFO frame__68_79 = {1, {"err"}};
static void cont__68_80(void);
static void cont__68_81(void);
static void cont__68_82(void);
static void cont__68_83(void);
static void cont__68_84(void);
static void cont__68_85(void);
static void cont__68_86(void);
static NODE *func__69_1;
static void entry__69_1(void);
static FRAME_INFO frame__69_1 = {5, {"mod_filename", "mod_name", "c_buf", "do_compile_c", "return"}};
static NODE *func__69_2;
static void entry__69_2(void);
static FRAME_INFO frame__69_2 = {7, {"line", "return", "mod_filename", "mod_name", "do_compile_c", "command", "argument"}};
static NODE *string__69_3;
static void cont__69_4(void);
static void cont__69_5(void);
static void cont__69_6(void);
static void cont__69_7(void);
static void cont__69_8(void);
static void cont__69_9(void);
static NODE *func__69_10;
static void entry__69_10(void);
static FRAME_INFO frame__69_10 = {4, {"argument", "mod_filename", "mod_name", "do_compile_c"}};
static NODE *string__69_11;
static void cont__69_12(void);
static NODE *func__69_13;
static void entry__69_13(void);
static FRAME_INFO frame__69_13 = {3, {"argument", "mod_filename", "mod_name"}};
static void cont__69_14(void);
static NODE *func__69_15;
static void entry__69_15(void);
static FRAME_INFO frame__69_15 = {4, {"argument", "mod_filename", "mod_name", "req_name"}};
static void cont__69_16(void);
static void cont__69_17(void);
static void cont__69_18(void);
static void cont__69_19(void);
static void cont__69_20(void);
static void cont__69_21(void);
static void cont__69_22(void);
static void cont__69_23(void);
static NODE *func__69_24;
static void entry__69_24(void);
static FRAME_INFO frame__69_24 = {2, {"argument", "do_compile_c"}};
static NODE *func__69_25;
static void entry__69_25(void);
static FRAME_INFO frame__69_25 = {0, {}};
static NODE *func__69_26;
static void entry__69_26(void);
static FRAME_INFO frame__69_26 = {0, {}};
static void cont__69_27(void);
static void cont__69_28(void);
static NODE *func__69_29;
static void entry__69_29(void);
static FRAME_INFO frame__69_29 = {1, {"argument"}};
static void cont__69_30(void);
static NODE *func__69_31;
static void entry__69_31(void);
static FRAME_INFO frame__69_31 = {2, {"do_compile_c", "argument"}};
static NODE *func__69_32;
static void entry__69_32(void);
static FRAME_INFO frame__69_32 = {0, {}};
static void cont__69_33(void);
static void cont__69_34(void);
static NODE *func__69_35;
static void entry__69_35(void);
static FRAME_INFO frame__69_35 = {1, {"argument"}};
static void cont__69_36(void);
static NODE *string__69_37;
static void cont__69_38(void);
static void cont__69_39(void);
static NODE *func__69_40;
static void entry__69_40(void);
static FRAME_INFO frame__69_40 = {2, {"do_compile_c", "argument"}};
static NODE *func__69_41;
static void entry__69_41(void);
static FRAME_INFO frame__69_41 = {1, {"argument"}};
static void cont__69_42(void);
static void cont__69_43(void);
static NODE *string__69_44;
static NODE *string__69_45;
static void cont__69_46(void);
static NODE *func__70_1;
static void entry__70_1(void);
static FRAME_INFO frame__70_1 = {6, {"mod_filename", "mod_name", "return", "compile_submodule", "mod_info", "o_filename"}};
static NODE *func__70_2;
static void entry__70_2(void);
static FRAME_INFO frame__70_2 = {11, {"submodule_names", "do_compile_c", "suffix", "mod_filename", "mod_name", "o_filename", "modification_time", "sim_filenames", "c_filename", "c_info", "c_buf"}};
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
static NODE *string__70_14;
static void cont__70_15(void);
static void cont__70_16(void);
static void cont__70_17(void);
static void cont__70_18(void);
static NODE *func__70_19;
static void entry__70_19(void);
static FRAME_INFO frame__70_19 = {2, {"modification_time", "sim_info"}};
static void cont__70_20(void);
static void cont__70_21(void);
static void cont__70_22(void);
static NODE *func__70_23;
static void entry__70_23(void);
static FRAME_INFO frame__70_23 = {2, {"modification_time", "sim_info"}};
static void cont__70_24(void);
static void cont__70_25(void);
static NODE *string__70_26;
static void cont__70_27(void);
static void cont__70_28(void);
static NODE *func__70_29;
static void entry__70_29(void);
static FRAME_INFO frame__70_29 = {1, {"c_filename"}};
static void cont__70_30(void);
static void cont__70_31(void);
static NODE *func__70_32;
static void entry__70_32(void);
static FRAME_INFO frame__70_32 = {2, {"c_info", "modification_time"}};
static void cont__70_33(void);
static NODE *func__70_34;
static void entry__70_34(void);
static FRAME_INFO frame__70_34 = {2, {"c_info", "modification_time"}};
static void cont__70_35(void);
static void cont__70_36(void);
static void cont__70_37(void);
static void cont__70_38(void);
static NODE *func__70_39;
static void entry__70_39(void);
static FRAME_INFO frame__70_39 = {9, {"return__1", "mod_name", "suffix", "sim_filenames", "c_buf", "c_filename", "do_compile_c", "o_filename", "c_source"}};
static NODE *string__70_40;
static void cont__70_41(void);
static NODE *string__70_42;
static void cont__70_43(void);
static void cont__70_44(void);
static NODE *func__70_45;
static void entry__70_45(void);
static FRAME_INFO frame__70_45 = {1, {"suffix"}};
static NODE *func__70_46;
static void entry__70_46(void);
static FRAME_INFO frame__70_46 = {1, {"suffix"}};
static NODE *string__70_47;
static NODE *func__70_48;
static void entry__70_48(void);
static FRAME_INFO frame__70_48 = {1, {"suffix"}};
static NODE *func__70_49;
static void entry__70_49(void);
static FRAME_INFO frame__70_49 = {1, {"suffix"}};
static NODE *string__70_50;
static void cont__70_51(void);
static NODE *func__70_52;
static void entry__70_52(void);
static FRAME_INFO frame__70_52 = {1, {"sim_filenames"}};
static void cont__70_53(void);
static NODE *func__70_54;
static void entry__70_54(void);
static FRAME_INFO frame__70_54 = {1, {"c_source"}};
static void cont__70_55(void);
static void cont__70_56(void);
static void cont__70_57(void);
static NODE *func__70_58;
static void entry__70_58(void);
static FRAME_INFO frame__70_58 = {2, {"c_filename", "o_filename"}};
static void cont__70_59(void);
static NODE *func__70_60;
static void entry__70_60(void);
static FRAME_INFO frame__70_60 = {6, {"c_buf", "c_filename", "o_filename", "c_info", "do_compile_c", "o_info"}};
static void cont__70_61(void);
static void cont__70_62(void);
static void cont__70_63(void);
static NODE *func__70_64;
static void entry__70_64(void);
static FRAME_INFO frame__70_64 = {2, {"o_info", "c_info"}};
static void cont__70_65(void);
static void cont__70_66(void);
static void cont__70_67(void);
static void cont__70_68(void);
static NODE *func__70_69;
static void entry__70_69(void);
static FRAME_INFO frame__70_69 = {3, {"do_compile_c", "c_filename", "o_filename"}};
static NODE *func__70_70;
static void entry__70_70(void);
static FRAME_INFO frame__70_70 = {2, {"c_filename", "o_filename"}};
static NODE *func__70_71;
static void entry__70_71(void);
static FRAME_INFO frame__70_71 = {1, {"o_info"}};
static void cont__70_72(void);
static NODE *func__70_73;
static void entry__70_73(void);
static FRAME_INFO frame__70_73 = {1, {"o_info"}};
static void cont__70_74(void);
static void cont__70_75(void);
static void cont__70_76(void);
static NODE *func__70_77;
static void entry__70_77(void);
static FRAME_INFO frame__70_77 = {1, {"o_info"}};
static void cont__70_78(void);
static void cont__70_79(void);
static void cont__70_80(void);
static void cont__70_81(void);
static NODE *func__70_82;
static void entry__70_82(void);
static FRAME_INFO frame__70_82 = {1, {"mod_name"}};
static NODE *string__70_83;
static NODE *string__70_84;
static void cont__70_85(void);
static void cont__70_86(void);
static void cont__70_87(void);
static NODE *func__70_88;
static void entry__70_88(void);
static FRAME_INFO frame__70_88 = {0, {}};
static NODE *string__70_89;
static NODE *func__70_90;
static void entry__70_90(void);
static FRAME_INFO frame__70_90 = {0, {}};
static NODE *string__70_91;
static void cont__70_92(void);
static void cont__70_93(void);
static void cont__70_94(void);
static void cont__70_95(void);
static void cont__70_96(void);
static void cont__70_97(void);
static NODE *func__70_98;
static void entry__70_98(void);
static FRAME_INFO frame__70_98 = {3, {"compile_submodule", "mod_name", "mod_filename"}};
static void cont__70_99(void);
static void cont__70_100(void);
static void cont__70_101(void);
static void cont__70_102(void);
static NODE *func__70_103;
static void entry__70_103(void);
static FRAME_INFO frame__70_103 = {1, {"mod_filename"}};
static NODE *string__70_104;
static void cont__70_105(void);
static void cont__70_106(void);
static NODE *func__70_107;
static void entry__70_107(void);
static FRAME_INFO frame__70_107 = {3, {"mod_info", "compile_submodule", "mod_filename"}};
static NODE *func__70_108;
static void entry__70_108(void);
static FRAME_INFO frame__70_108 = {4, {"mod_info", "compile_submodule", "best_platform", "best_priority"}};
static NODE *func__70_109;
static void entry__70_109(void);
static FRAME_INFO frame__70_109 = {5, {"platform", "filenames", "best_priority", "best_platform", "priority"}};
static void cont__70_110(void);
static void cont__70_111(void);
static NODE *func__70_112;
static void entry__70_112(void);
static FRAME_INFO frame__70_112 = {2, {"priority", "best_priority"}};
static void cont__70_113(void);
static void cont__70_114(void);
static NODE *func__70_115;
static void entry__70_115(void);
static FRAME_INFO frame__70_115 = {4, {"best_platform", "platform", "best_priority", "priority"}};
static void cont__70_116(void);
static NODE *func__70_117;
static void entry__70_117(void);
static FRAME_INFO frame__70_117 = {4, {"platform", "filenames", "compile_submodule", "best_platform"}};
static void cont__70_118(void);
static NODE *string__70_119;
static void cont__70_120(void);
static void cont__70_121(void);
static NODE *func__70_122;
static void entry__70_122(void);
static FRAME_INFO frame__70_122 = {3, {"mod_info", "mod_filename", "used_by"}};
static NODE *func__70_123;
static void entry__70_123(void);
static FRAME_INFO frame__70_123 = {6, {"supported_platform", "parent_platform", "mod_info", "used_by", "best_platform", "best_priority"}};
static NODE *func__70_124;
static void entry__70_124(void);
static FRAME_INFO frame__70_124 = {6, {"platform", "filenames", "supported_platform", "best_priority", "best_platform", "priority"}};
static void cont__70_125(void);
static void cont__70_126(void);
static NODE *func__70_127;
static void entry__70_127(void);
static FRAME_INFO frame__70_127 = {2, {"priority", "best_priority"}};
static void cont__70_128(void);
static void cont__70_129(void);
static NODE *func__70_130;
static void entry__70_130(void);
static FRAME_INFO frame__70_130 = {4, {"best_platform", "platform", "best_priority", "priority"}};
static void cont__70_131(void);
static void cont__70_132(void);
static NODE *func__70_133;
static void entry__70_133(void);
static FRAME_INFO frame__70_133 = {4, {"used_by", "best_platform", "supported_platform", "ub"}};
static void cont__70_134(void);
static void cont__70_135(void);
static void cont__70_136(void);
static void cont__70_137(void);
static void cont__70_138(void);
static NODE *func__70_139;
static void entry__70_139(void);
static FRAME_INFO frame__70_139 = {6, {"platform", "filenames", "mod_filename", "used_by", "dependency", "platforms"}};
static NODE *string__70_140;
static NODE *string__70_141;
static void cont__70_142(void);
static void cont__70_143(void);
static void cont__70_144(void);
static NODE *func__70_145;
static void entry__70_145(void);
static FRAME_INFO frame__70_145 = {2, {"platforms", "dependency"}};
static NODE *func__70_146;
static void entry__70_146(void);
static FRAME_INFO frame__70_146 = {2, {"plat", "dependency"}};
static NODE *string__70_147;
static void cont__70_148(void);
static void cont__70_149(void);
static void cont__70_150(void);
static void cont__70_151(void);
static NODE *func__71_1;
static void entry__71_1(void);
static FRAME_INFO frame__71_1 = {4, {"path", "mod_path", "directories", "modules"}};
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
static NODE *func__73_1;
static void entry__73_1(void);
static FRAME_INFO frame__73_1 = {0, {}};
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
static NODE *func__74_1;
static void entry__74_1(void);
static FRAME_INFO frame__74_1 = {4, {"library_paths", "object_files", "library_files", "paths"}};
static void cont__74_2(void);
static NODE *string__74_3;
static void cont__74_4(void);
static void cont__74_5(void);
static NODE *func__74_6;
static void entry__74_6(void);
static FRAME_INFO frame__74_6 = {2, {"paths", "library_paths"}};
static void cont__74_7(void);
static NODE *func__74_8;
static void entry__74_8(void);
static FRAME_INFO frame__74_8 = {2, {"path", "library_paths"}};
static NODE *string__74_9;
static void cont__74_10(void);
static void cont__74_11(void);
static void cont__74_12(void);
static NODE *func__74_13;
static void entry__74_13(void);
static FRAME_INFO frame__74_13 = {1, {"library_paths"}};
static void cont__74_14(void);
static NODE *string__74_15;
static void cont__74_16(void);
static NODE *func__74_17;
static void entry__74_17(void);
static FRAME_INFO frame__74_17 = {2, {"object", "object_files"}};
static void cont__74_18(void);
static void cont__74_19(void);
static NODE *func__74_20;
static void entry__74_20(void);
static FRAME_INFO frame__74_20 = {2, {"library", "library_files"}};
static NODE *string__74_21;
static void cont__74_22(void);
static NODE *func__74_23;
static void entry__74_23(void);
static FRAME_INFO frame__74_23 = {1, {"library"}};
static NODE *string__74_24;
static void cont__74_25(void);
static NODE *func__74_26;
static void entry__74_26(void);
static FRAME_INFO frame__74_26 = {1, {"library"}};
static NODE *string__74_27;
static NODE *string__74_28;
static void cont__74_29(void);
static NODE *func__74_30;
static void entry__74_30(void);
static FRAME_INFO frame__74_30 = {1, {"library"}};
static NODE *string__74_31;
static NODE *string__74_32;
static void cont__74_33(void);
static void cont__74_34(void);
static NODE *func__74_35;
static void entry__74_35(void);
static FRAME_INFO frame__74_35 = {1, {"library"}};
static void cont__74_36(void);
static NODE *func__74_37;
static void entry__74_37(void);
static FRAME_INFO frame__74_37 = {1, {"library"}};
static void cont__74_38(void);
static void cont__74_39(void);
static NODE *string__74_40;
static NODE *string__74_41;
static void cont__74_42(void);
static NODE *func__74_43;
static void entry__74_43(void);
static FRAME_INFO frame__74_43 = {1, {"library"}};
static NODE *string__74_44;
static void cont__74_45(void);
static void cont__74_46(void);
static void cont__74_47(void);
static void cont__74_48(void);
static void cont__74_49(void);
static void cont__74_50(void);
static NODE *func__75_1;
static void entry__75_1(void);
static FRAME_INFO frame__75_1 = {5, {"source", "already_checked", "collect_declarations", "imports", "first_part"}};
static NODE *func__75_2;
static void entry__75_2(void);
static FRAME_INFO frame__75_2 = {4, {"buf", "already_checked", "collect_declarations", "s"}};
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
static NODE *string__75_39;
static void cont__75_40(void);
static void cont__75_41(void);
static NODE *func__75_42;
static void entry__75_42(void);
static FRAME_INFO frame__75_42 = {2, {"collect_declarations", "declaration"}};
static void cont__75_43(void);
static NODE *func__75_44;
static void entry__75_44(void);
static FRAME_INFO frame__75_44 = {2, {"declaration", "collect_declarations"}};
static NODE *string__75_45;
static void cont__75_46(void);
static NODE *func__75_47;
static void entry__75_47(void);
static FRAME_INFO frame__75_47 = {2, {"declaration", "collect_declarations"}};
static void cont__75_48(void);
static void cont__75_49(void);
static NODE *func__75_50;
static void entry__75_50(void);
static FRAME_INFO frame__75_50 = {2, {"line", "collect_declarations"}};
static void cont__75_51(void);
static void cont__75_52(void);
static NODE *func__75_53;
static void entry__75_53(void);
static FRAME_INFO frame__75_53 = {2, {"collect_declarations", "declaration"}};
static void cont__75_54(void);
static NODE *func__75_55;
static void entry__75_55(void);
static FRAME_INFO frame__75_55 = {0, {}};
static NODE *string__75_56;
static void cont__75_57(void);
static NODE *func__75_58;
static void entry__75_58(void);
static FRAME_INFO frame__75_58 = {3, {"chr", "s", "idx"}};
static void cont__75_59(void);
static NODE *func__75_60;
static void entry__75_60(void);
static FRAME_INFO frame__75_60 = {1, {"chr"}};
static void cont__75_61(void);
static void cont__75_62(void);
static NODE *func__75_63;
static void entry__75_63(void);
static FRAME_INFO frame__75_63 = {2, {"s", "idx"}};
static NODE *func__75_64;
static void entry__75_64(void);
static FRAME_INFO frame__75_64 = {2, {"collect_declarations", "source"}};
static void cont__75_65(void);
static NODE *string__75_66;
static void cont__75_67(void);
static void cont__75_68(void);
static void cont__75_69(void);
static void cont__75_70(void);
static void cont__75_71(void);
static void cont__75_72(void);
static void cont__75_73(void);
static void cont__75_74(void);
static NODE *func__75_75;
static void entry__75_75(void);
static FRAME_INFO frame__75_75 = {0, {}};
static NODE *string__75_76;
static NODE *func__76_1;
static void entry__76_1(void);
static FRAME_INFO frame__76_1 = {4, {"body", "return__1", "mod_filename", "mod_name"}};
static void cont__76_2(void);
static NODE *func__76_3;
static void entry__76_3(void);
static FRAME_INFO frame__76_3 = {0, {}};
static NODE *string__76_4;
static void cont__76_5(void);
static NODE *string__76_6;
static void cont__76_7(void);
static NODE *func__76_8;
static void entry__76_8(void);
static FRAME_INFO frame__76_8 = {0, {}};
static NODE *string__76_9;
static void cont__76_10(void);
static NODE *string__76_11;
static void cont__76_12(void);
static void cont__76_13(void);
static void cont__76_14(void);
static void cont__76_15(void);
static NODE *func__77_1;
static void entry__77_1(void);
static FRAME_INFO frame__77_1 = {0, {}};
static NODE *func__77_2;
static void entry__77_2(void);
static FRAME_INFO frame__77_2 = {3, {"mod_filename", "mod_name", "return__1"}};
static void cont__77_3(void);
static void cont__77_4(void);
static NODE *func__78_1;
static void entry__78_1(void);
static FRAME_INFO frame__78_1 = {0, {}};
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
static NODE *string__78_9;
static void cont__78_10(void);
static NODE *string__78_11;
static void cont__78_12(void);
static void cont__78_13(void);
static void cont__78_14(void);
static void cont__78_15(void);
static void cont__78_16(void);
static NODE *func__78_17;
static void entry__78_17(void);
static FRAME_INFO frame__78_17 = {1, {"c_source"}};
static void cont__78_18(void);
static void cont__78_19(void);
static NODE *func__78_20;
static void entry__78_20(void);
static FRAME_INFO frame__78_20 = {0, {}};
static NODE *string__78_21;
static NODE *func__79_1;
static void entry__79_1(void);
static FRAME_INFO frame__79_1 = {1, {"prefix_path"}};
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
static NODE *string__79_26;
static void cont__79_27(void);
static void cont__79_28(void);
static NODE *string__79_29;
static void cont__79_30(void);
static NODE *string__79_31;
static void cont__79_32(void);
static NODE *string__79_33;
static void cont__79_34(void);
static void cont__79_35(void);
static NODE *func__79_36;
static void entry__79_36(void);
static FRAME_INFO frame__79_36 = {2, {"filename", "prefix_path"}};
static void cont__79_37(void);
static void cont__79_38(void);
static NODE *func__80_1;
static void entry__80_1(void);
static FRAME_INFO frame__80_1 = {0, {}};
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
static NODE *string__80_19;
static void cont__80_20(void);
static void cont__80_21(void);
static void cont__80_22(void);
static void cont__80_23(void);
static NODE *string__80_24;
static void cont__80_25(void);
static NODE *string__80_26;
static NODE *string__80_27;
static void cont__80_28(void);
static void cont__80_29(void);
static NODE *string__80_30;
static NODE *string__80_31;
static NODE *string__80_32;
static void cont__80_33(void);
static void cont__80_34(void);
static NODE *func__80_35;
static void entry__80_35(void);
static FRAME_INFO frame__80_35 = {2, {"filename", "buf"}};
static NODE *string__80_36;
static NODE *string__80_37;
static void cont__80_38(void);
static void cont__80_39(void);
static void cont__80_40(void);
static NODE *string__80_41;
static NODE *string__80_42;
static NODE *string__80_43;
static NODE *string__80_44;
static NODE *string__80_45;
static NODE *string__80_46;
static void cont__80_47(void);
static void cont__80_48(void);
static NODE *func__80_49;
static void entry__80_49(void);
static FRAME_INFO frame__80_49 = {4, {"filename", "prefix_path", "buf", "path_prefix"}};
static void cont__80_50(void);
static void cont__80_51(void);
static NODE *string__80_52;
static NODE *string__80_53;
static void cont__80_54(void);
static void cont__80_55(void);
static void cont__80_56(void);
static NODE *string__80_57;
static void cont__80_58(void);
static NODE *func__81_1;
static void entry__81_1(void);
static FRAME_INFO frame__81_1 = {1, {"return__1"}};
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
static NODE *string__81_21;
static void cont__81_22(void);
static NODE *string__81_23;
static void cont__81_24(void);
static NODE *func__81_25;
static void entry__81_25(void);
static FRAME_INFO frame__81_25 = {2, {"base_filename", "version"}};
static NODE *string__81_26;
static NODE *string__81_27;
static void cont__81_28(void);
static NODE *string__81_29;
static void cont__81_30(void);
static NODE *func__81_31;
static void entry__81_31(void);
static FRAME_INFO frame__81_31 = {2, {"base_filename", "version"}};
static NODE *string__81_32;
static NODE *string__81_33;
static void cont__81_34(void);
static NODE *string__81_35;
static void cont__81_36(void);
static NODE *func__81_37;
static void entry__81_37(void);
static FRAME_INFO frame__81_37 = {1, {"base_filename"}};
static NODE *string__81_38;
static NODE *string__81_39;
static void cont__81_40(void);
static NODE *string__81_41;
static NODE *string__81_42;
static NODE *string__81_43;
static void cont__81_44(void);
static NODE *func__81_45;
static void entry__81_45(void);
static FRAME_INFO frame__81_45 = {1, {"lib_filename"}};
static NODE *string__81_46;
static void cont__81_47(void);
static void cont__81_48(void);
static void cont__81_49(void);
static void cont__81_50(void);
static NODE *func__81_51;
static void entry__81_51(void);
static FRAME_INFO frame__81_51 = {2, {"lib_filename", "info"}};
static void cont__81_52(void);
static void cont__81_53(void);
static NODE *func__81_54;
static void entry__81_54(void);
static FRAME_INFO frame__81_54 = {1, {"info"}};
static void cont__81_55(void);
static void cont__81_56(void);
static void cont__81_57(void);
static NODE *func__81_58;
static void entry__81_58(void);
static FRAME_INFO frame__81_58 = {0, {}};
static void cont__81_59(void);
static NODE *func__81_60;
static void entry__81_60(void);
static FRAME_INFO frame__81_60 = {3, {"base_filename", "so_version", "lib_filename"}};
static NODE *func__81_61;
static void entry__81_61(void);
static FRAME_INFO frame__81_61 = {0, {}};
static NODE *string__81_62;
static void cont__81_63(void);
static NODE *func__81_64;
static void entry__81_64(void);
static FRAME_INFO frame__81_64 = {6, {"base_filename", "so_version", "lib_filename", "out", "err", "success"}};
static NODE *string__81_65;
static NODE *string__81_66;
static void cont__81_67(void);
static void cont__81_68(void);
static NODE *string__81_69;
static NODE *string__81_70;
static void cont__81_71(void);
static NODE *func__81_72;
static void entry__81_72(void);
static FRAME_INFO frame__81_72 = {1, {"err"}};
static void cont__81_73(void);
static NODE *func__81_74;
static void entry__81_74(void);
static FRAME_INFO frame__81_74 = {4, {"lib_filename", "out", "err", "success"}};
static void cont__81_75(void);
static NODE *string__81_76;
static void cont__81_77(void);
static NODE *string__81_78;
static NODE *string__81_79;
static void cont__81_80(void);
static NODE *func__81_81;
static void entry__81_81(void);
static FRAME_INFO frame__81_81 = {1, {"err"}};
static void cont__81_82(void);
static NODE *func__81_83;
static void entry__81_83(void);
static FRAME_INFO frame__81_83 = {6, {"base_filename", "so_version", "lib_filename", "out", "err", "success"}};
static NODE *string__81_84;
static NODE *string__81_85;
static NODE *string__81_86;
static void cont__81_87(void);
static void cont__81_88(void);
static NODE *string__81_89;
static void cont__81_90(void);
static NODE *string__81_91;
static NODE *string__81_92;
static void cont__81_93(void);
static NODE *func__81_94;
static void entry__81_94(void);
static FRAME_INFO frame__81_94 = {1, {"err"}};
static void cont__81_95(void);
static NODE *func__81_96;
static void entry__81_96(void);
static FRAME_INFO frame__81_96 = {4, {"lib_filename", "out", "err", "success"}};
static void cont__81_97(void);
static NODE *string__81_98;
static NODE *string__81_99;
static void cont__81_100(void);
static NODE *func__81_101;
static void entry__81_101(void);
static FRAME_INFO frame__81_101 = {1, {"err"}};
static void cont__81_102(void);
static NODE *string__81_103;
static NODE *string__81_104;
static NODE *string__81_105;
static void cont__81_106(void);
static NODE *func__82_1;
static void entry__82_1(void);
static FRAME_INFO frame__82_1 = {5, {"filename", "c_filename", "o_filename", "c_info", "o_info"}};
static NODE *string__82_2;
static void cont__82_3(void);
static NODE *string__82_4;
static void cont__82_5(void);
static void cont__82_6(void);
static void cont__82_7(void);
static NODE *func__82_8;
static void entry__82_8(void);
static FRAME_INFO frame__82_8 = {1, {"c_filename"}};
static NODE *string__82_9;
static NODE *string__82_10;
static void cont__82_11(void);
static void cont__82_12(void);
static void cont__82_13(void);
static void cont__82_14(void);
static NODE *func__82_15;
static void entry__82_15(void);
static FRAME_INFO frame__82_15 = {2, {"o_info", "c_info"}};
static void cont__82_16(void);
static void cont__82_17(void);
static void cont__82_18(void);
static void cont__82_19(void);
static NODE *func__82_20;
static void entry__82_20(void);
static FRAME_INFO frame__82_20 = {3, {"filename", "c_filename", "o_filename"}};
static NODE *func__82_21;
static void entry__82_21(void);
static FRAME_INFO frame__82_21 = {1, {"filename"}};
static NODE *string__82_22;
static void cont__82_23(void);
static void cont__82_24(void);
static NODE *func__84_1;
static void entry__84_1(void);
static FRAME_INFO frame__84_1 = {4, {"val", "n", "m", "ac"}};
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
static NODE *func__85_1;
static void entry__85_1(void);
static FRAME_INFO frame__85_1 = {3, {"description", "filename", "new_t"}};
static void cont__85_2(void);
static void cont__85_3(void);
static NODE *func__85_4;
static void entry__85_4(void);
static FRAME_INFO frame__85_4 = {3, {"filename", "description", "new_t"}};
static void cont__85_5(void);
static void cont__85_6(void);
static void cont__85_7(void);
static void cont__85_8(void);
static NODE *string__85_9;
static void cont__85_10(void);
static void cont__85_11(void);
static void cont__85_12(void);
static NODE *string__85_13;
static NODE *func__85_14;
static void entry__85_14(void);
static FRAME_INFO frame__85_14 = {2, {"description", "new_t"}};
static void cont__85_15(void);
static void cont__85_16(void);
static NODE *string__85_17;
static NODE *string__85_18;
static void cont__85_19(void);
static void cont__85_20(void);
static NODE *get__sim2c__write_timing_info(void) {
  return var.sim2c__write_timing_info;
}
static NODE *func__86_1;
static void entry__86_1(void);
static FRAME_INFO frame__86_1 = {0, {}};
static NODE *func__86_2;
static void entry__86_2(void);
static FRAME_INFO frame__86_2 = {9, {"mod_filename", "mod_name", "exe_filename", "c_filename", "o_filename", "sim_info", "c_info", "c_buf", "zz"}};
static NODE *string__86_3;
static void cont__86_4(void);
static NODE *func__86_5;
static void entry__86_5(void);
static FRAME_INFO frame__86_5 = {1, {"mod_filename"}};
static NODE *string__86_6;
static void cont__86_7(void);
static NODE *func__86_8;
static void entry__86_8(void);
static FRAME_INFO frame__86_8 = {1, {"mod_filename"}};
static void cont__86_9(void);
static NODE *func__86_10;
static void entry__86_10(void);
static FRAME_INFO frame__86_10 = {1, {"exe_filename"}};
static NODE *string__86_11;
static void cont__86_12(void);
static NODE *string__86_13;
static void cont__86_14(void);
static NODE *string__86_15;
static void cont__86_16(void);
static void cont__86_17(void);
static void cont__86_18(void);
static void cont__86_19(void);
static NODE *func__86_20;
static void entry__86_20(void);
static FRAME_INFO frame__86_20 = {2, {"c_info", "sim_info"}};
static void cont__86_21(void);
static NODE *func__86_22;
static void entry__86_22(void);
static FRAME_INFO frame__86_22 = {2, {"c_info", "sim_info"}};
static void cont__86_23(void);
static void cont__86_24(void);
static void cont__86_25(void);
static void cont__86_26(void);
static void cont__86_27(void);
static NODE *func__86_28;
static void entry__86_28(void);
static FRAME_INFO frame__86_28 = {6, {"return__1", "mod_name", "c_buf", "c_filename", "o_filename", "c_source"}};
static NODE *string__86_29;
static void cont__86_30(void);
static void cont__86_31(void);
static NODE *func__86_32;
static void entry__86_32(void);
static FRAME_INFO frame__86_32 = {0, {}};
static NODE *string__86_33;
static void cont__86_34(void);
static NODE *func__86_35;
static void entry__86_35(void);
static FRAME_INFO frame__86_35 = {0, {}};
static void cont__86_36(void);
static void cont__86_37(void);
static NODE *func__86_38;
static void entry__86_38(void);
static FRAME_INFO frame__86_38 = {1, {"c_source"}};
static void cont__86_39(void);
static void cont__86_40(void);
static void cont__86_41(void);
static NODE *func__86_42;
static void entry__86_42(void);
static FRAME_INFO frame__86_42 = {1, {"c_filename"}};
static NODE *string__86_43;
static void cont__86_44(void);
static void cont__86_45(void);
static NODE *func__86_46;
static void entry__86_46(void);
static FRAME_INFO frame__86_46 = {1, {"c_filename"}};
static NODE *string__86_47;
static void cont__86_48(void);
static NODE *func__86_49;
static void entry__86_49(void);
static FRAME_INFO frame__86_49 = {5, {"c_buf", "c_filename", "o_filename", "c_info", "o_info"}};
static void cont__86_50(void);
static void cont__86_51(void);
static void cont__86_52(void);
static NODE *func__86_53;
static void entry__86_53(void);
static FRAME_INFO frame__86_53 = {2, {"o_info", "c_info"}};
static void cont__86_54(void);
static void cont__86_55(void);
static void cont__86_56(void);
static void cont__86_57(void);
static NODE *func__86_58;
static void entry__86_58(void);
static FRAME_INFO frame__86_58 = {2, {"c_filename", "o_filename"}};
static NODE *func__86_59;
static void entry__86_59(void);
static FRAME_INFO frame__86_59 = {1, {"o_info"}};
static void cont__86_60(void);
static void cont__86_61(void);
static void cont__86_62(void);
static NODE *func__86_63;
static void entry__86_63(void);
static FRAME_INFO frame__86_63 = {0, {}};
static NODE *string__86_64;
static NODE *string__86_65;
static NODE *string__86_66;
static void cont__86_67(void);
static NODE *func__86_68;
static void entry__86_68(void);
static FRAME_INFO frame__86_68 = {1, {"filename"}};
static void cont__86_69(void);
static NODE *func__86_70;
static void entry__86_70(void);
static FRAME_INFO frame__86_70 = {2, {"exe_filename", "info"}};
static void cont__86_71(void);
static void cont__86_72(void);
static NODE *func__86_73;
static void entry__86_73(void);
static FRAME_INFO frame__86_73 = {1, {"info"}};
static void cont__86_74(void);
static NODE *func__86_75;
static void entry__86_75(void);
static FRAME_INFO frame__86_75 = {1, {"info"}};
static void cont__86_76(void);
static void cont__86_77(void);
static void cont__86_78(void);
static void cont__86_79(void);
static NODE *func__86_80;
static void entry__86_80(void);
static FRAME_INFO frame__86_80 = {0, {}};
static void cont__86_81(void);
static NODE *func__86_82;
static void entry__86_82(void);
static FRAME_INFO frame__86_82 = {2, {"exe_filename", "libs_and_files"}};
static void cont__86_83(void);
static NODE *func__86_84;
static void entry__86_84(void);
static FRAME_INFO frame__86_84 = {1, {"libs_and_files"}};
static NODE *string__86_85;
static void cont__86_86(void);
static void cont__86_87(void);
static NODE *func__86_88;
static void entry__86_88(void);
static FRAME_INFO frame__86_88 = {5, {"libs_and_files", "exe_filename", "out", "err", "success"}};
static NODE *func__86_89;
static void entry__86_89(void);
static FRAME_INFO frame__86_89 = {0, {}};
static NODE *string__86_90;
static void cont__86_91(void);
static NODE *string__86_92;
static NODE *string__86_93;
static NODE *string__86_94;
static NODE *string__86_95;
static void cont__86_96(void);
static NODE *func__86_97;
static void entry__86_97(void);
static FRAME_INFO frame__86_97 = {1, {"err"}};
static void cont__86_98(void);
static NODE *func__86_99;
static void entry__86_99(void);
static FRAME_INFO frame__86_99 = {5, {"libs_and_files", "exe_filename", "out", "err", "success"}};
static NODE *func__86_100;
static void entry__86_100(void);
static FRAME_INFO frame__86_100 = {0, {}};
static NODE *string__86_101;
static void cont__86_102(void);
static NODE *string__86_103;
static void cont__86_104(void);
static NODE *func__86_105;
static void entry__86_105(void);
static FRAME_INFO frame__86_105 = {0, {}};
static NODE *string__86_106;
static void cont__86_107(void);
static NODE *func__86_108;
static void entry__86_108(void);
static FRAME_INFO frame__86_108 = {0, {}};
static NODE *string__86_109;
static void cont__86_110(void);
static void cont__86_111(void);
static NODE *string__86_112;
static void cont__86_113(void);
static NODE *func__86_114;
static void entry__86_114(void);
static FRAME_INFO frame__86_114 = {1, {"err"}};
static void cont__86_115(void);
static void cont__86_116(void);
static void cont__86_117(void);
static void cont__86_118(void);
static NODE *func__86_119;
static void entry__86_119(void);
static FRAME_INFO frame__86_119 = {0, {}};
static NODE *string__86_120;
static void cont__86_121(void);
static void cont__86_122(void);
static NODE *func__86_123;
static void entry__86_123(void);
static FRAME_INFO frame__86_123 = {2, {"exe_filename", "zz"}};
static void cont__86_124(void);
static NODE *func__86_125;
static void entry__86_125(void);
static FRAME_INFO frame__86_125 = {1, {"exe_filename"}};
static NODE *func__86_126;
static void entry__86_126(void);
static FRAME_INFO frame__86_126 = {1, {"exe_filename"}};
static NODE *string__86_127;
static void cont__86_128(void);
static void cont__86_129(void);
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
static NODE *string__95_2;
static NODE *string__95_3;
static void cont__95_4(void);
static void cont__95_5(void);
static NODE *string__96_1;
static void cont__96_2(void);
static NODE *string__97_1;
static void cont__97_2(void);
static NODE *string__98_1;
static void cont__98_2(void);
static NODE *string__99_1;
static void cont__99_2(void);
static void cont__100_1(void);
static NODE *func__100_2;
static void entry__100_2(void);
static FRAME_INFO frame__100_2 = {0, {}};
static void cont__100_3(void);
static NODE *func__100_4;
static void entry__100_4(void);
static FRAME_INFO frame__100_4 = {0, {}};
static NODE *string__100_5;
static NODE *string__100_6;
static void cont__100_7(void);
static void cont__100_8(void);
static void cont__101_1(void);
static NODE *func__101_2;
static void entry__101_2(void);
static FRAME_INFO frame__101_2 = {0, {}};
static void cont__101_3(void);
static NODE *func__101_4;
static void entry__101_4(void);
static FRAME_INFO frame__101_4 = {0, {}};
static NODE *string__101_5;
static NODE *string__101_6;
static void cont__101_7(void);
static void cont__101_8(void);
static NODE *string__103_1;
static NODE *string__103_2;
static void cont__103_3(void);
static NODE *string__103_4;
static NODE *string__103_5;
static void cont__103_6(void);
static NODE *string__103_7;
static NODE *string__103_8;
static void cont__103_9(void);
static NODE *string__103_10;
static NODE *string__103_11;
static void cont__103_12(void);
static NODE *string__103_13;
static NODE *string__103_14;
static void cont__103_15(void);
static NODE *string__103_16;
static NODE *string__103_17;
static void cont__103_18(void);
static NODE *string__103_19;
static void cont__103_20(void);
static void cont__103_21(void);
static NODE *func__105_1;
static void entry__105_1(void);
static FRAME_INFO frame__105_1 = {2, {"platform", "priority"}};
static NODE *func__105_2;
static void entry__105_2(void);
static FRAME_INFO frame__105_2 = {3, {"break", "platform", "priority"}};
static NODE *func__105_3;
static void entry__105_3(void);
static FRAME_INFO frame__105_3 = {4, {"platform", "break", "priority", "plat"}};
static void cont__105_4(void);
static void cont__105_5(void);
static void cont__105_6(void);
static void cont__105_7(void);
static void cont__105_8(void);
static void cont__105_9(void);
static void cont__105_10(void);
static void cont__105_11(void);
static void cont__105_12(void);
static void cont__130_1(void);
static void cont__130_2(void);
static NODE *string__131_1;
static void cont__131_2(void);
static NODE *func__131_3;
static void entry__131_3(void);
static FRAME_INFO frame__131_3 = {0, {}};
static void cont__131_4(void);
static NODE *func__131_5;
static void entry__131_5(void);
static FRAME_INFO frame__131_5 = {0, {}};
static NODE *string__131_6;
static void cont__131_7(void);
static void cont__131_8(void);
static NODE *func__131_9;
static void entry__131_9(void);
static FRAME_INFO frame__131_9 = {0, {}};
static NODE *func__131_10;
static void entry__131_10(void);
static FRAME_INFO frame__131_10 = {0, {}};
static NODE *string__131_11;
static NODE *string__131_12;
static NODE *func__131_13;
static void entry__131_13(void);
static FRAME_INFO frame__131_13 = {0, {}};
static NODE *string__131_14;
static NODE *string__131_15;
static NODE *func__131_16;
static void entry__131_16(void);
static FRAME_INFO frame__131_16 = {0, {}};
static NODE *string__131_17;
static NODE *string__131_18;
static NODE *func__131_19;
static void entry__131_19(void);
static FRAME_INFO frame__131_19 = {0, {}};
static NODE *string__131_20;
static NODE *string__131_21;
static NODE *func__131_22;
static void entry__131_22(void);
static FRAME_INFO frame__131_22 = {0, {}};
static NODE *string__131_23;
static NODE *string__131_24;
static NODE *func__131_25;
static void entry__131_25(void);
static FRAME_INFO frame__131_25 = {0, {}};
static NODE *string__131_26;
static NODE *string__131_27;
static NODE *func__131_28;
static void entry__131_28(void);
static FRAME_INFO frame__131_28 = {0, {}};
static NODE *string__131_29;
static NODE *string__131_30;
static NODE *func__131_31;
static void entry__131_31(void);
static FRAME_INFO frame__131_31 = {0, {}};
static NODE *string__131_32;
static NODE *string__131_33;
static NODE *func__131_34;
static void entry__131_34(void);
static FRAME_INFO frame__131_34 = {0, {}};
static NODE *string__131_35;
static NODE *string__131_36;
static NODE *func__131_37;
static void entry__131_37(void);
static FRAME_INFO frame__131_37 = {0, {}};
static NODE *string__131_38;
static NODE *string__131_39;
static NODE *func__131_40;
static void entry__131_40(void);
static FRAME_INFO frame__131_40 = {0, {}};
static NODE *string__131_41;
static NODE *string__131_42;
static NODE *func__131_43;
static void entry__131_43(void);
static FRAME_INFO frame__131_43 = {0, {}};
static NODE *string__131_44;
static NODE *string__131_45;
static NODE *func__131_46;
static void entry__131_46(void);
static FRAME_INFO frame__131_46 = {0, {}};
static NODE *string__131_47;
static NODE *string__131_48;
static NODE *func__131_49;
static void entry__131_49(void);
static FRAME_INFO frame__131_49 = {0, {}};
static NODE *string__131_50;
static NODE *string__131_51;
static NODE *func__131_52;
static void entry__131_52(void);
static FRAME_INFO frame__131_52 = {0, {}};
static NODE *string__131_53;
static NODE *string__131_54;
static NODE *func__131_55;
static void entry__131_55(void);
static FRAME_INFO frame__131_55 = {0, {}};
static NODE *string__131_56;
static NODE *string__131_57;
static NODE *func__131_58;
static void entry__131_58(void);
static FRAME_INFO frame__131_58 = {0, {}};
static NODE *string__131_59;
static NODE *string__131_60;
static NODE *func__131_61;
static void entry__131_61(void);
static FRAME_INFO frame__131_61 = {0, {}};
static NODE *string__131_62;
static NODE *string__131_63;
static NODE *func__131_64;
static void entry__131_64(void);
static FRAME_INFO frame__131_64 = {0, {}};
static NODE *string__131_65;
static NODE *string__131_66;
static NODE *func__131_67;
static void entry__131_67(void);
static FRAME_INFO frame__131_67 = {0, {}};
static NODE *string__131_68;
static NODE *string__131_69;
static NODE *func__131_70;
static void entry__131_70(void);
static FRAME_INFO frame__131_70 = {0, {}};
static NODE *string__131_71;
static NODE *string__131_72;
static void cont__131_73(void);
static void cont__131_74(void);
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
static void cont__141_11(void);
static NODE *string__142_1;
static NODE *string__142_2;
static void cont__142_3(void);
static NODE *string__142_4;
static void cont__142_5(void);
static NODE *string__142_6;
static NODE *string__142_7;
static void cont__142_8(void);
static NODE *string__142_9;
static void cont__142_10(void);
static void cont__142_11(void);
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
  {cont__93_1, NULL, 96, 96, 9, 48},
  {cont__95_4, NULL, 96, 96, 1, 48},
  {cont__95_5, NULL, 97, 97, 1, 17},
  {cont__96_2, NULL, 98, 98, 1, 72},
  {cont__97_2, NULL, 99, 99, 1, 37},
  {cont__98_2, NULL, 100, 100, 1, 39},
  {cont__99_2, NULL, 104, 104, 5, 25},
  {cont__100_1, NULL, 102, 106, 1, 67},
  {cont__100_8, NULL, 110, 110, 5, 26},
  {cont__101_1, NULL, 108, 112, 1, 67},
  {cont__101_8, NULL, 118, 118, 5, 19},
  {cont__103_3, NULL, 119, 119, 5, 22},
  {cont__103_6, NULL, 120, 120, 5, 22},
  {cont__103_9, NULL, 121, 121, 5, 21},
  {cont__103_12, NULL, 122, 122, 5, 19},
  {cont__103_15, NULL, 123, 123, 5, 17},
  {cont__103_18, NULL, 124, 124, 5, 16},
  {cont__103_20, NULL, 116, 124, 1, 17},
  {cont__103_21, NULL, 127, 137, 1, 22},
  {cont__105_12, NULL, 162, 162, 42, 42},
  {cont__130_1, NULL, 162, 162, 1, 43},
  {cont__130_2, NULL, 164, 164, 3, 20},
  {cont__131_2, NULL, 163, 243, 1, 49},
  {cont__131_74, NULL, 244, 244, 1, 39},
  {cont__132_1, NULL, 245, 245, 1, 30},
  {cont__133_1, NULL, 247, 247, 1, 37},
  {cont__135_2, NULL, 256, 256, 1, 21},
  {cont__140_1, NULL, 258, 269, 1, 27},
  {cont__141_11, NULL, 273, 273, 16, 44},
  {cont__142_3, NULL, 273, 273, 5, 44},
  {cont__142_5, NULL, 274, 274, 16, 44},
  {cont__142_8, NULL, 274, 274, 5, 44},
  {cont__142_10, NULL, 271, 274, 1, 45},
  {cont__142_11, NULL, 280, 280, 37, 59},
  {cont__143_1, NULL, 280, 280, 7, 60},
  {cont__143_2, NULL, 279, 281, 5, 15},
  {cont__143_3, NULL, 276, 281, 1, 18},
  {cont__143_4, NULL, 633, 633, 4, 25},
  {cont__161_1, NULL, 633, 635, 1, 52},
  {cont__161_6, NULL, 1071, 1071, 1, 36},
  {cont__176_3, NULL, 1072, 1084, 1, 18},
  {cont__177_13, NULL, },
  {cont__178_1, NULL, },
  {entry__47_2, NULL, 250, 250, 36, 49},
  {entry__47_1, NULL, 250, 250, 3, 49},
  {entry__63_11, NULL, 299, 299, 35, 78},
  {cont__63_12, &frame__63_11, 299, 299, 35, 59},
  {cont__63_13, &frame__63_11, 299, 299, 78, 78},
  {entry__63_8, NULL, 298, 298, 11, 39},
  {cont__63_9, &frame__63_8, 299, 299, 14, 32},
  {cont__63_10, &frame__63_8, 299, 299, 11, 78},
  {entry__63_6, NULL, 297, 297, 12, 31},
  {cont__63_7, &frame__63_6, 297, 299, 9, 78},
  {entry__63_4, NULL, 296, 296, 16, 30},
  {cont__63_5, &frame__63_4, 296, 299, 7, 79},
  {entry__63_3, NULL, 295, 299, 5, 80},
  {entry__63_18, NULL, 303, 304, 11, 57},
  {cont__63_21, &frame__63_18, 303, 304, 5, 57},
  {entry__63_1, NULL, 293, 293, 6, 36},
  {cont__63_2, &frame__63_1, 293, 299, 3, 81},
  {cont__63_14, &frame__63_1, 300, 300, 3, 32},
  {cont__63_15, &frame__63_1, 301, 301, 3, 38},
  {cont__63_16, &frame__63_1, 302, 302, 6, 25},
  {cont__63_17, &frame__63_1, 302, 304, 3, 58},
  {cont__63_22, &frame__63_1, 305, 305, 21, 39},
  {cont__63_23, &frame__63_1, 305, 305, 6, 40},
  {cont__63_24, &frame__63_1, 305, 305, 3, 40},
  {entry__64_10, NULL, 323, 323, 56, 77},
  {cont__64_11, &frame__64_10, 323, 323, 77, 77},
  {entry__64_8, NULL, 323, 323, 35, 53},
  {cont__64_9, &frame__64_8, 323, 323, 32, 77},
  {entry__64_6, NULL, 323, 323, 10, 29},
  {cont__64_7, &frame__64_6, 323, 323, 7, 77},
  {entry__64_29, NULL, 329, 329, 41, 65},
  {cont__64_30, &frame__64_29, 329, 329, 41, 65},
  {entry__64_32, NULL, 330, 330, 11, 38},
  {cont__64_33, &frame__64_32, 330, 330, 49, 49},
  {entry__64_15, NULL, 325, 325, 48, 60},
  {cont__64_17, &frame__64_15, 325, 325, 48, 68},
  {cont__64_19, &frame__64_15, 325, 325, 9, 69},
  {cont__64_20, &frame__64_15, 326, 326, 9, 34},
  {cont__64_21, &frame__64_15, 327, 327, 22, 36},
  {cont__64_22, &frame__64_15, 327, 327, 38, 62},
  {cont__64_23, &frame__64_15, 327, 327, 22, 62},
  {cont__64_24, &frame__64_15, 327, 327, 22, 64},
  {cont__64_25, &frame__64_15, 327, 327, 9, 67},
  {cont__64_26, &frame__64_15, 328, 328, 9, 49},
  {cont__64_27, &frame__64_15, 329, 329, 12, 36},
  {cont__64_28, &frame__64_15, 329, 329, 12, 65},
  {cont__64_31, &frame__64_15, 329, 330, 9, 49},
  {cont__64_34, &frame__64_15, 331, 331, 9, 52},
  {cont__64_35, &frame__64_15, 332, 332, 9, 26},
  {cont__64_36, &frame__64_15, 333, 333, 9, 43},
  {cont__64_37, &frame__64_15, 334, 334, 9, 30},
  {cont__64_38, &frame__64_15, 334, 334, 52, 52},
  {entry__64_12, NULL, 324, 324, 10, 33},
  {cont__64_14, &frame__64_12, 324, 334, 7, 52},
  {entry__64_4, NULL, 321, 321, 5, 33},
  {cont__64_5, &frame__64_4, 322, 334, 5, 53},
  {entry__64_51, NULL, 340, 340, 38, 60},
  {cont__64_52, &frame__64_51, 340, 340, 60, 60},
  {entry__64_46, NULL, 339, 339, 11, 54},
  {cont__64_49, &frame__64_46, 340, 340, 14, 35},
  {cont__64_50, &frame__64_46, 340, 340, 11, 60},
  {entry__64_59, NULL, 347, 348, 17, 57},
  {cont__64_62, &frame__64_59, 347, 348, 11, 57},
  {entry__64_69, NULL, 352, 352, 11, 34},
  {cont__64_70, &frame__64_69, 353, 353, 11, 45},
  {cont__64_71, &frame__64_69, 353, 353, 45, 45},
  {entry__64_66, NULL, 351, 351, 18, 31},
  {cont__64_67, &frame__64_66, 351, 351, 18, 31},
  {cont__64_68, &frame__64_66, 351, 353, 15, 45},
  {entry__64_45, NULL, 342, 342, 9, 35},
  {cont__64_53, &frame__64_45, 343, 343, 35, 58},
  {cont__64_54, &frame__64_45, 343, 343, 9, 59},
  {cont__64_55, &frame__64_45, 344, 344, 9, 39},
  {cont__64_56, &frame__64_45, 345, 345, 9, 46},
  {cont__64_57, &frame__64_45, 346, 346, 16, 32},
  {cont__64_58, &frame__64_45, 346, 348, 9, 58},
  {cont__64_63, &frame__64_45, 349, 349, 9, 30},
  {cont__64_64, &frame__64_45, 350, 350, 9, 34},
  {cont__64_65, &frame__64_45, 351, 353, 9, 45},
  {cont__64_72, &frame__64_45, 354, 354, 10, 30},
  {cont__64_73, &frame__64_45, 354, 354, 9, 40},
  {cont__64_74, &frame__64_45, 354, 354, 9, 30},
  {cont__64_75, &frame__64_45, 354, 354, 46, 46},
  {entry__64_42, NULL, 337, 337, 14, 44},
  {cont__64_44, &frame__64_42, 337, 354, 7, 46},
  {entry__64_40, NULL, 336, 336, 8, 30},
  {cont__64_41, &frame__64_40, 336, 354, 5, 47},
  {entry__64_79, NULL, 355, 355, 39, 64},
  {entry__64_1, NULL, 316, 316, 22, 27},
  {cont__64_2, &frame__64_1, 316, 316, 3, 33},
  {cont__64_3, &frame__64_1, 320, 334, 3, 54},
  {cont__64_39, &frame__64_1, 335, 354, 3, 48},
  {cont__64_76, &frame__64_1, 355, 355, 6, 31},
  {cont__64_77, &frame__64_1, 355, 355, 6, 36},
  {cont__64_78, &frame__64_1, 355, 355, 3, 64},
  {cont__64_80, &frame__64_1, 355, 355, 64, 64},
  {entry__65_4, NULL, 366, 366, 23, 29},
  {entry__65_5, NULL, 367, 367, 47, 47},
  {cont__65_6, &frame__65_5, 367, 367, 22, 48},
  {cont__65_7, &frame__65_5, 367, 367, 70, 70},
  {cont__65_8, &frame__65_5, 367, 367, 50, 71},
  {cont__65_9, &frame__65_5, 367, 367, 5, 71},
  {cont__65_10, &frame__65_5, 368, 368, 8, 28},
  {cont__65_11, &frame__65_5, 368, 368, 5, 28},
  {entry__65_1, NULL, 365, 365, 3, 29},
  {cont__65_2, &frame__65_1, 366, 366, 6, 20},
  {cont__65_3, &frame__65_1, 366, 368, 3, 28},
  {entry__66_2, NULL, 371, 371, 43, 52},
  {cont__66_3, &frame__66_2, 371, 371, 27, 52},
  {entry__66_1, NULL, 371, 371, 3, 52},
  {cont__66_5, &frame__66_1, 372, 372, 3, 11},
  {entry__67_2, NULL, 375, 375, 41, 60},
  {entry__67_9, NULL, 380, 380, 31, 43},
  {cont__67_10, &frame__67_9, 380, 380, 25, 43},
  {entry__67_5, NULL, 379, 379, 9, 76},
  {cont__67_8, &frame__67_5, 380, 380, 9, 43},
  {entry__67_17, NULL, 390, 390, 31, 43},
  {cont__67_18, &frame__67_17, 390, 390, 25, 43},
  {entry__67_11, NULL, 382, 389, 9, 20},
  {cont__67_16, &frame__67_11, 390, 390, 9, 43},
  {entry__67_4, NULL, 376, 390, 5, 44},
  {cont__67_19, &frame__67_4, 391, 391, 17, 17},
  {entry__67_1, NULL, 375, 375, 10, 60},
  {cont__67_3, &frame__67_1, 375, 391, 3, 17},
  {entry__68_30, NULL, 418, 418, 45, 74},
  {cont__68_31, &frame__68_30, 418, 418, 9, 41},
  {cont__68_32, &frame__68_30, 418, 418, 9, 74},
  {cont__68_33, &frame__68_30, 418, 418, 9, 74},
  {entry__68_26, NULL, 417, 417, 43, 75},
  {cont__68_27, &frame__68_26, 417, 417, 9, 39},
  {cont__68_28, &frame__68_26, 417, 417, 9, 75},
  {cont__68_29, &frame__68_26, 418, 418, 9, 74},
  {cont__68_34, &frame__68_26, },
  {entry__68_24, NULL, 416, 416, 9, 32},
  {cont__68_25, &frame__68_24, },
  {cont__68_35, &frame__68_24, },
  {entry__68_22, NULL, 415, 415, 9, 29},
  {cont__68_23, &frame__68_22, },
  {cont__68_36, &frame__68_22, },
  {entry__68_46, NULL, 430, 430, 17, 47},
  {cont__68_47, &frame__68_46, 430, 430, 17, 67},
  {cont__68_48, &frame__68_46, 430, 430, 17, 67},
  {entry__68_50, NULL, 433, 433, 17, 21},
  {entry__68_43, NULL, 426, 426, 13, 42},
  {cont__68_44, &frame__68_43, 429, 429, 17, 38},
  {cont__68_45, &frame__68_43, 428, 430, 15, 66},
  {cont__68_49, &frame__68_43, 427, 433, 13, 22},
  {entry__68_63, NULL, 443, 443, 58, 58},
  {cont__68_64, &frame__68_63, 443, 443, 40, 59},
  {cont__68_65, &frame__68_63, 443, 443, 23, 60},
  {cont__68_66, &frame__68_63, 443, 443, 17, 60},
  {entry__68_68, NULL, 445, 445, 53, 77},
  {cont__68_69, &frame__68_68, 445, 445, 47, 77},
  {entry__68_67, NULL, 445, 445, 17, 77},
  {entry__68_60, NULL, 442, 442, 15, 40},
  {cont__68_62, &frame__68_60, 441, 445, 13, 78},
  {entry__68_42, NULL, 435, 435, 18, 41},
  {cont__68_52, &frame__68_42, 435, 435, 11, 47},
  {cont__68_53, &frame__68_42, 436, 436, 11, 26},
  {cont__68_54, &frame__68_42, 437, 437, 11, 20},
  {cont__68_55, &frame__68_42, 438, 438, 11, 50},
  {cont__68_56, &frame__68_42, 439, 439, 11, 44},
  {cont__68_57, &frame__68_42, 440, 440, 14, 30},
  {cont__68_59, &frame__68_42, 440, 445, 11, 79},
  {entry__68_41, NULL, 424, 445, 9, 80},
  {cont__68_70, &frame__68_41, 445, 445, 80, 80},
  {entry__68_38, NULL, 421, 421, 7, 55},
  {cont__68_39, &frame__68_38, 422, 422, 7, 38},
  {cont__68_40, &frame__68_38, 423, 445, 7, 81},
  {entry__68_79, NULL, 460, 460, 29, 41},
  {cont__68_80, &frame__68_79, 460, 460, 23, 41},
  {entry__68_72, NULL, 454, 454, 7, 36},
  {cont__68_73, &frame__68_72, 455, 455, 7, 22},
  {cont__68_74, &frame__68_72, 456, 456, 7, 31},
  {cont__68_75, &frame__68_72, 457, 457, 7, 32},
  {cont__68_76, &frame__68_72, 458, 458, 7, 43},
  {cont__68_77, &frame__68_72, 459, 459, 7, 32},
  {cont__68_78, &frame__68_72, 460, 460, 7, 41},
  {cont__68_81, &frame__68_72, 461, 461, 25, 35},
  {cont__68_82, &frame__68_72, 461, 461, 7, 35},
  {cont__68_83, &frame__68_72, 461, 461, 35, 35},
  {entry__68_2, NULL, 403, 403, 48, 48},
  {cont__68_3, &frame__68_2, 403, 403, 5, 49},
  {cont__68_4, &frame__68_2, 404, 404, 35, 57},
  {cont__68_6, &frame__68_2, 404, 404, 5, 58},
  {cont__68_7, &frame__68_2, 405, 405, 5, 42},
  {cont__68_9, &frame__68_2, 406, 406, 42, 64},
  {cont__68_11, &frame__68_2, 406, 406, 5, 70},
  {cont__68_13, &frame__68_2, 407, 407, 51, 62},
  {cont__68_14, &frame__68_2, 407, 407, 39, 63},
  {cont__68_16, &frame__68_2, 407, 407, 5, 71},
  {cont__68_18, &frame__68_2, 408, 408, 5, 34},
  {cont__68_19, &frame__68_2, 409, 409, 5, 32},
  {cont__68_20, &frame__68_2, 410, 410, 5, 38},
  {cont__68_21, &frame__68_2, 412, 418, 5, 75},
  {cont__68_37, &frame__68_2, 420, 445, 5, 82},
  {cont__68_71, &frame__68_2, 446, 461, 5, 35},
  {cont__68_84, &frame__68_2, 462, 462, 5, 19},
  {cont__68_85, &frame__68_2, 463, 463, 8, 21},
  {cont__68_86, &frame__68_2, 463, 463, 5, 21},
  {entry__68_1, NULL, 402, 463, 3, 21},
  {entry__69_15, NULL, 488, 488, 43, 43},
  {cont__69_16, &frame__69_15, 488, 488, 15, 44},
  {cont__69_17, &frame__69_15, 490, 490, 48, 48},
  {cont__69_18, &frame__69_15, 490, 490, 24, 49},
  {cont__69_19, &frame__69_15, 490, 490, 17, 59},
  {cont__69_20, &frame__69_15, 491, 491, 44, 44},
  {cont__69_21, &frame__69_15, 491, 491, 24, 45},
  {cont__69_22, &frame__69_15, 491, 491, 17, 55},
  {cont__69_23, &frame__69_15, 489, 491, 15, 55},
  {entry__69_13, NULL, 487, 487, 16, 26},
  {cont__69_14, &frame__69_13, 487, 491, 13, 56},
  {entry__69_26, NULL, 497, 497, 17, 36},
  {entry__69_25, NULL, },
  {cont__69_27, &frame__69_25, },
  {entry__69_29, NULL, 499, 499, 32, 57},
  {cont__69_30, &frame__69_29, 499, 499, 17, 66},
  {entry__69_32, NULL, 501, 501, 36, 66},
  {cont__69_33, &frame__69_32, 501, 501, 36, 66},
  {entry__69_35, NULL, 502, 502, 44, 71},
  {cont__69_36, &frame__69_35, 502, 502, 30, 72},
  {cont__69_38, &frame__69_35, 502, 502, 19, 73},
  {cont__69_39, &frame__69_35, 502, 502, 78, 78},
  {entry__69_31, NULL, 501, 501, 20, 66},
  {cont__69_34, &frame__69_31, 501, 502, 17, 78},
  {entry__69_24, NULL, },
  {cont__69_28, &frame__69_24, 493, 502, 13, 80},
  {entry__69_10, NULL, 486, 486, 11, 36},
  {cont__69_12, &frame__69_10, 485, 502, 9, 82},
  {entry__69_41, NULL, 504, 504, 37, 64},
  {cont__69_42, &frame__69_41, 504, 504, 26, 65},
  {cont__69_43, &frame__69_41, 504, 504, 70, 70},
  {entry__69_40, NULL, 504, 504, 9, 70},
  {entry__69_2, NULL, 477, 477, 12, 35},
  {cont__69_4, &frame__69_2, 477, 477, 5, 42},
  {cont__69_5, &frame__69_2, 478, 478, 5, 20},
  {cont__69_6, &frame__69_2, 479, 479, 5, 14},
  {cont__69_7, &frame__69_2, 480, 480, 5, 44},
  {cont__69_8, &frame__69_2, 481, 481, 5, 38},
  {cont__69_9, &frame__69_2, 482, 504, 5, 71},
  {entry__69_1, NULL, 476, 504, 3, 72},
  {cont__69_46, &frame__69_1, 504, 504, 72, 72},
  {entry__70_9, NULL, 526, 526, 28, 44},
  {cont__70_10, &frame__70_9, 526, 526, 28, 44},
  {entry__70_12, NULL, 527, 527, 9, 72},
  {entry__70_19, NULL, 534, 534, 11, 40},
  {cont__70_20, &frame__70_19, 534, 534, 11, 60},
  {cont__70_21, &frame__70_19, 534, 534, 11, 60},
  {entry__70_23, NULL, 536, 536, 11, 59},
  {cont__70_24, &frame__70_23, 536, 536, 59, 59},
  {entry__70_3, NULL, 524, 524, 7, 45},
  {cont__70_4, &frame__70_3, 525, 525, 58, 58},
  {cont__70_5, &frame__70_3, 525, 525, 34, 59},
  {cont__70_6, &frame__70_3, 525, 525, 7, 75},
  {cont__70_7, &frame__70_3, 526, 526, 10, 23},
  {cont__70_8, &frame__70_3, 526, 526, 10, 44},
  {cont__70_11, &frame__70_3, 526, 527, 7, 72},
  {cont__70_13, &frame__70_3, 528, 528, 7, 53},
  {cont__70_15, &frame__70_3, 529, 529, 7, 38},
  {cont__70_16, &frame__70_3, 530, 530, 7, 34},
  {cont__70_17, &frame__70_3, 533, 533, 11, 40},
  {cont__70_18, &frame__70_3, 532, 534, 9, 59},
  {cont__70_22, &frame__70_3, 531, 536, 7, 60},
  {entry__70_29, NULL, 539, 539, 22, 43},
  {cont__70_30, &frame__70_29, 539, 539, 48, 48},
  {entry__70_34, NULL, 545, 545, 29, 56},
  {cont__70_35, &frame__70_34, 545, 545, 9, 56},
  {cont__70_36, &frame__70_34, 545, 545, 9, 56},
  {entry__70_32, NULL, 544, 544, 9, 27},
  {cont__70_33, &frame__70_32, 545, 545, 9, 56},
  {cont__70_37, &frame__70_32, },
  {entry__70_46, NULL, 551, 551, 25, 79},
  {entry__70_45, NULL, 551, 551, 13, 79},
  {entry__70_49, NULL, 553, 553, 25, 75},
  {entry__70_48, NULL, 553, 553, 13, 75},
  {entry__70_52, NULL, 554, 554, 35, 53},
  {entry__70_54, NULL, 555, 555, 32, 54},
  {entry__70_58, NULL, 557, 557, 26, 56},
  {entry__70_39, NULL, 547, 547, 50, 59},
  {cont__70_41, &frame__70_39, 547, 547, 61, 70},
  {cont__70_43, &frame__70_39, 547, 547, 9, 71},
  {cont__70_44, &frame__70_39, 548, 553, 9, 76},
  {cont__70_51, &frame__70_39, 554, 554, 9, 53},
  {cont__70_53, &frame__70_39, 555, 555, 9, 54},
  {cont__70_55, &frame__70_39, 556, 556, 25, 37},
  {cont__70_56, &frame__70_39, 556, 556, 9, 37},
  {cont__70_57, &frame__70_39, 557, 557, 9, 56},
  {cont__70_59, &frame__70_39, 557, 557, 56, 56},
  {entry__70_64, NULL, 564, 564, 44, 71},
  {cont__70_65, &frame__70_64, 564, 564, 13, 40},
  {cont__70_66, &frame__70_64, 564, 564, 13, 71},
  {cont__70_67, &frame__70_64, 564, 564, 13, 71},
  {entry__70_70, NULL, 566, 566, 30, 60},
  {entry__70_69, NULL, 566, 566, 13, 60},
  {entry__70_73, NULL, 571, 571, 17, 44},
  {cont__70_74, &frame__70_73, 571, 571, 17, 69},
  {cont__70_75, &frame__70_73, 571, 571, 17, 69},
  {entry__70_77, NULL, 573, 573, 17, 68},
  {cont__70_78, &frame__70_77, 573, 573, 68, 68},
  {entry__70_71, NULL, 570, 570, 17, 51},
  {cont__70_72, &frame__70_71, 569, 571, 15, 68},
  {cont__70_76, &frame__70_71, 568, 573, 13, 69},
  {entry__70_60, NULL, 559, 559, 9, 30},
  {cont__70_61, &frame__70_60, 560, 560, 9, 32},
  {cont__70_62, &frame__70_60, 563, 563, 13, 31},
  {cont__70_63, &frame__70_60, 562, 564, 11, 70},
  {cont__70_68, &frame__70_60, 561, 573, 9, 71},
  {entry__70_2, NULL, 523, 536, 5, 61},
  {cont__70_25, &frame__70_2, 537, 537, 5, 48},
  {cont__70_27, &frame__70_2, 538, 538, 5, 28},
  {cont__70_28, &frame__70_2, 539, 539, 5, 48},
  {cont__70_31, &frame__70_2, 540, 540, 5, 21},
  {cont__70_38, &frame__70_2, 541, 573, 5, 73},
  {cont__70_79, &frame__70_2, 574, 574, 5, 63},
  {entry__70_82, NULL, 578, 579, 11, 56},
  {cont__70_85, &frame__70_82, 578, 579, 5, 56},
  {entry__70_88, NULL, 580, 580, 51, 61},
  {entry__70_90, NULL, 580, 580, 64, 70},
  {entry__70_103, NULL, 586, 586, 51, 75},
  {cont__70_105, &frame__70_103, 586, 586, 32, 75},
  {cont__70_106, &frame__70_103, 586, 586, 75, 75},
  {entry__70_98, NULL, 585, 585, 59, 59},
  {cont__70_99, &frame__70_98, 585, 585, 30, 60},
  {cont__70_100, &frame__70_98, 585, 585, 25, 61},
  {cont__70_101, &frame__70_98, 585, 585, 7, 61},
  {cont__70_102, &frame__70_98, 586, 586, 7, 75},
  {entry__70_112, NULL, 593, 593, 37, 60},
  {cont__70_113, &frame__70_112, 593, 593, 37, 60},
  {entry__70_115, NULL, 595, 595, 35, 35},
  {entry__70_109, NULL, 592, 592, 11, 47},
  {cont__70_110, &frame__70_109, 593, 593, 14, 32},
  {cont__70_111, &frame__70_109, 593, 593, 14, 60},
  {cont__70_114, &frame__70_109, 593, 595, 11, 35},
  {entry__70_117, NULL, 599, 599, 13, 37},
  {cont__70_118, &frame__70_117, 600, 600, 13, 32},
  {cont__70_120, &frame__70_117, 597, 600, 11, 32},
  {entry__70_108, NULL, 591, 595, 9, 36},
  {cont__70_116, &frame__70_108, 596, 600, 9, 33},
  {entry__70_127, NULL, 608, 608, 39, 62},
  {cont__70_128, &frame__70_127, 608, 608, 39, 62},
  {entry__70_130, NULL, 610, 610, 37, 37},
  {entry__70_124, NULL, 607, 607, 13, 77},
  {cont__70_125, &frame__70_124, 608, 608, 16, 34},
  {cont__70_126, &frame__70_124, 608, 608, 16, 62},
  {cont__70_129, &frame__70_124, 608, 610, 13, 37},
  {entry__70_133, NULL, 612, 612, 32, 53},
  {cont__70_134, &frame__70_133, 612, 612, 13, 65},
  {cont__70_135, &frame__70_133, 613, 613, 13, 39},
  {cont__70_136, &frame__70_133, 614, 614, 13, 35},
  {cont__70_137, &frame__70_133, 614, 614, 38, 38},
  {entry__70_123, NULL, 606, 610, 11, 38},
  {cont__70_131, &frame__70_123, 611, 611, 14, 37},
  {cont__70_132, &frame__70_123, 611, 614, 11, 38},
  {entry__70_146, NULL, 619, 619, 40, 69},
  {cont__70_148, &frame__70_146, 619, 619, 69, 69},
  {entry__70_145, NULL, 619, 619, 13, 69},
  {entry__70_139, NULL, 616, 616, 11, 61},
  {cont__70_142, &frame__70_139, 617, 617, 11, 38},
  {cont__70_143, &frame__70_139, 618, 618, 14, 33},
  {cont__70_144, &frame__70_139, 618, 619, 11, 69},
  {cont__70_149, &frame__70_139, 620, 620, 11, 39},
  {cont__70_150, &frame__70_139, 620, 620, 39, 39},
  {entry__70_122, NULL, 603, 614, 9, 39},
  {cont__70_138, &frame__70_122, 615, 620, 9, 39},
  {entry__70_107, NULL, 588, 600, 7, 34},
  {cont__70_121, &frame__70_107, 601, 620, 7, 40},
  {entry__70_1, NULL, 576, 576, 3, 40},
  {cont__70_80, &frame__70_1, 577, 577, 10, 28},
  {cont__70_81, &frame__70_1, 577, 579, 3, 57},
  {cont__70_86, &frame__70_1, 580, 580, 38, 48},
  {cont__70_87, &frame__70_1, 580, 580, 35, 71},
  {cont__70_92, &frame__70_1, 580, 580, 3, 72},
  {cont__70_93, &frame__70_1, 581, 581, 6, 24},
  {cont__70_94, &frame__70_1, 581, 581, 3, 31},
  {cont__70_95, &frame__70_1, 582, 582, 3, 22},
  {cont__70_96, &frame__70_1, 584, 584, 5, 21},
  {cont__70_97, &frame__70_1, 583, 620, 3, 42},
  {cont__70_151, &frame__70_1, 620, 620, 42, 42},
  {entry__71_4, NULL, 629, 629, 21, 41},
  {cont__71_5, &frame__71_4, 629, 629, 43, 67},
  {cont__71_6, &frame__71_4, 629, 629, 5, 67},
  {entry__71_8, NULL, 631, 631, 20, 40},
  {cont__71_9, &frame__71_8, 631, 631, 42, 66},
  {cont__71_10, &frame__71_8, 631, 631, 5, 66},
  {entry__71_1, NULL, 627, 627, 47, 66},
  {cont__71_2, &frame__71_1, 627, 627, 3, 66},
  {cont__71_3, &frame__71_1, 628, 629, 3, 67},
  {cont__71_7, &frame__71_1, 630, 631, 3, 66},
  {entry__73_6, NULL, 640, 640, 34, 58},
  {cont__73_8, &frame__73_6, 640, 640, 25, 58},
  {entry__73_2, NULL, 639, 639, 5, 40},
  {cont__73_4, &frame__73_2, 640, 640, 8, 22},
  {cont__73_5, &frame__73_2, 640, 640, 5, 58},
  {cont__73_9, &frame__73_2, 641, 641, 40, 57},
  {cont__73_10, &frame__73_2, 641, 641, 5, 57},
  {cont__73_12, &frame__73_2, 642, 642, 35, 54},
  {cont__73_13, &frame__73_2, 642, 642, 5, 54},
  {entry__73_1, NULL, 638, 642, 3, 54},
  {entry__74_8, NULL, 651, 651, 60, 70},
  {cont__74_10, &frame__74_8, 651, 651, 40, 70},
  {cont__74_11, &frame__74_8, 651, 651, 70, 70},
  {entry__74_6, NULL, 651, 651, 14, 30},
  {cont__74_7, &frame__74_6, 651, 651, 5, 70},
  {entry__74_13, NULL, 652, 652, 54, 77},
  {cont__74_14, &frame__74_13, 652, 652, 27, 77},
  {entry__74_17, NULL, 653, 653, 30, 54},
  {cont__74_18, &frame__74_17, 653, 653, 54, 54},
  {entry__74_26, NULL, 662, 662, 16, 45},
  {cont__74_29, &frame__74_26, 662, 662, 13, 45},
  {entry__74_30, NULL, 663, 663, 16, 38},
  {cont__74_33, &frame__74_30, 663, 663, 13, 38},
  {entry__74_23, NULL, 661, 661, 13, 39},
  {cont__74_25, &frame__74_23, 660, 663, 11, 37},
  {cont__74_34, &frame__74_23, 659, 663, 9, 39},
  {entry__74_37, NULL, 667, 667, 25, 44},
  {cont__74_38, &frame__74_37, 667, 667, 52, 71},
  {cont__74_39, &frame__74_37, 667, 667, 16, 73},
  {cont__74_42, &frame__74_37, 667, 668, 13, 26},
  {entry__74_43, NULL, 669, 669, 16, 29},
  {cont__74_45, &frame__74_43, 669, 669, 13, 29},
  {entry__74_35, NULL, 666, 666, 13, 34},
  {cont__74_36, &frame__74_35, 665, 669, 11, 28},
  {cont__74_46, &frame__74_35, 664, 669, 9, 30},
  {entry__74_20, NULL, 658, 658, 9, 35},
  {cont__74_22, &frame__74_20, 657, 669, 7, 30},
  {cont__74_47, &frame__74_20, 655, 669, 5, 32},
  {cont__74_48, &frame__74_20, 669, 669, 33, 33},
  {entry__74_1, NULL, 645, 645, 3, 16},
  {cont__74_2, &frame__74_1, 649, 649, 3, 39},
  {cont__74_4, &frame__74_1, 650, 650, 6, 21},
  {cont__74_5, &frame__74_1, 650, 651, 3, 70},
  {cont__74_12, &frame__74_1, 652, 652, 3, 77},
  {cont__74_16, &frame__74_1, 653, 653, 3, 54},
  {cont__74_19, &frame__74_1, 654, 669, 3, 33},
  {cont__74_49, &frame__74_1, 670, 670, 24, 57},
  {cont__74_50, &frame__74_1, 670, 670, 3, 57},
  {entry__75_9, NULL, 680, 680, 51, 64},
  {cont__75_10, &frame__75_9, 680, 680, 51, 64},
  {entry__75_7, NULL, 680, 680, 37, 46},
  {cont__75_8, &frame__75_7, 680, 680, 37, 64},
  {cont__75_11, &frame__75_7, 680, 680, 37, 64},
  {entry__75_29, NULL, 691, 691, 25, 59},
  {cont__75_31, &frame__75_29, 691, 691, 21, 60},
  {cont__75_32, &frame__75_29, 691, 691, 21, 60},
  {entry__75_25, NULL, 690, 690, 25, 58},
  {cont__75_27, &frame__75_25, 690, 690, 21, 59},
  {cont__75_28, &frame__75_25, 691, 691, 21, 60},
  {cont__75_33, &frame__75_25, },
  {entry__75_38, NULL, 695, 695, 46, 80},
  {cont__75_40, &frame__75_38, 695, 695, 46, 80},
  {entry__75_42, NULL, 697, 697, 44, 74},
  {cont__75_43, &frame__75_42, 697, 697, 23, 74},
  {entry__75_35, NULL, 695, 695, 21, 34},
  {cont__75_36, &frame__75_35, 695, 695, 21, 41},
  {cont__75_37, &frame__75_35, 695, 695, 21, 80},
  {cont__75_41, &frame__75_35, 694, 697, 19, 75},
  {entry__75_50, NULL, 700, 700, 60, 60},
  {cont__75_51, &frame__75_50, 700, 700, 44, 61},
  {cont__75_52, &frame__75_50, 700, 700, 23, 61},
  {entry__75_47, NULL, 699, 699, 35, 62},
  {cont__75_48, &frame__75_47, 699, 699, 35, 67},
  {cont__75_49, &frame__75_47, 699, 700, 21, 61},
  {entry__75_44, NULL, 698, 698, 22, 62},
  {cont__75_46, &frame__75_44, 698, 700, 19, 62},
  {entry__75_53, NULL, 702, 702, 21, 52},
  {entry__75_55, NULL, 703, 703, 31, 45},
  {entry__75_21, NULL, 689, 689, 21, 34},
  {cont__75_22, &frame__75_21, 689, 689, 21, 41},
  {cont__75_23, &frame__75_21, 689, 689, 21, 41},
  {cont__75_24, &frame__75_21, 687, 691, 17, 61},
  {cont__75_34, &frame__75_21, 693, 702, 17, 53},
  {cont__75_54, &frame__75_21, 703, 703, 17, 45},
  {cont__75_57, &frame__75_21, 704, 704, 17, 33},
  {entry__75_17, NULL, 684, 684, 15, 38},
  {cont__75_18, &frame__75_17, 685, 685, 15, 50},
  {cont__75_19, &frame__75_17, 686, 686, 18, 39},
  {cont__75_20, &frame__75_17, 686, 704, 15, 33},
  {entry__75_13, NULL, 681, 681, 33, 37},
  {cont__75_14, &frame__75_13, 681, 681, 13, 38},
  {cont__75_15, &frame__75_13, 683, 683, 20, 42},
  {cont__75_16, &frame__75_13, 683, 704, 13, 34},
  {entry__75_5, NULL, 680, 680, 18, 32},
  {cont__75_6, &frame__75_5, 680, 680, 18, 64},
  {cont__75_12, &frame__75_5, 680, 704, 11, 35},
  {entry__75_60, NULL, 706, 706, 33, 42},
  {cont__75_61, &frame__75_60, 706, 706, 33, 42},
  {entry__75_63, NULL, 706, 706, 50, 50},
  {entry__75_58, NULL, 706, 706, 14, 28},
  {cont__75_59, &frame__75_58, 706, 706, 14, 42},
  {cont__75_62, &frame__75_58, 706, 706, 11, 50},
  {entry__75_3, NULL, 679, 679, 9, 20},
  {cont__75_4, &frame__75_3, 678, 706, 7, 51},
  {entry__75_2, NULL, 677, 706, 5, 52},
  {entry__75_64, NULL, 708, 708, 28, 54},
  {entry__75_75, NULL, 713, 713, 22, 59},
  {entry__75_1, NULL, 708, 708, 3, 54},
  {cont__75_65, &frame__75_1, 709, 709, 3, 49},
  {cont__75_67, &frame__75_1, 710, 710, 3, 18},
  {cont__75_68, &frame__75_1, 711, 711, 3, 15},
  {cont__75_69, &frame__75_1, 712, 712, 22, 42},
  {cont__75_70, &frame__75_1, 712, 712, 22, 45},
  {cont__75_71, &frame__75_1, 712, 712, 48, 48},
  {cont__75_72, &frame__75_1, 712, 712, 9, 49},
  {cont__75_73, &frame__75_1, 712, 712, 3, 49},
  {cont__75_74, &frame__75_1, 713, 713, 3, 59},
  {entry__76_3, NULL, 716, 716, 32, 67},
  {entry__76_8, NULL, 718, 719, 5, 57},
  {entry__76_1, NULL, 716, 716, 6, 29},
  {cont__76_2, &frame__76_1, 716, 716, 3, 67},
  {cont__76_5, &frame__76_1, 717, 717, 10, 42},
  {cont__76_7, &frame__76_1, 717, 719, 3, 58},
  {cont__76_10, &frame__76_1, 721, 721, 3, 53},
  {cont__76_12, &frame__76_1, 722, 722, 46, 46},
  {cont__76_13, &frame__76_1, 722, 722, 3, 47},
  {cont__76_14, &frame__76_1, 723, 723, 3, 28},
  {cont__76_15, &frame__76_1, 723, 723, 28, 28},
  {entry__77_2, NULL, 728, 728, 11, 29},
  {cont__77_3, &frame__77_2, 728, 728, 5, 29},
  {cont__77_4, &frame__77_2, 728, 728, 29, 29},
  {entry__77_1, NULL, 726, 728, 3, 29},
  {entry__78_4, NULL, 732, 732, 41, 65},
  {cont__78_5, &frame__78_4, 732, 732, 34, 75},
  {cont__78_6, &frame__78_4, 732, 732, 75, 75},
  {entry__78_8, NULL, 734, 734, 48, 57},
  {cont__78_10, &frame__78_8, 734, 734, 59, 68},
  {cont__78_12, &frame__78_8, 734, 734, 7, 69},
  {cont__78_13, &frame__78_8, 735, 735, 13, 31},
  {cont__78_14, &frame__78_8, 735, 735, 7, 31},
  {cont__78_15, &frame__78_8, 735, 735, 31, 31},
  {entry__78_17, NULL, 736, 736, 28, 50},
  {entry__78_20, NULL, 738, 738, 24, 59},
  {entry__78_2, NULL, 732, 732, 8, 31},
  {cont__78_3, &frame__78_2, 732, 732, 5, 75},
  {cont__78_7, &frame__78_2, 733, 735, 5, 31},
  {cont__78_16, &frame__78_2, 736, 736, 5, 50},
  {cont__78_18, &frame__78_2, 737, 737, 5, 15},
  {cont__78_19, &frame__78_2, 738, 738, 5, 59},
  {entry__78_1, NULL, 731, 738, 3, 59},
  {entry__79_5, NULL, 747, 747, 9, 43},
  {cont__79_6, &frame__79_5, 748, 748, 12, 28},
  {cont__79_7, &frame__79_5, 748, 748, 9, 34},
  {cont__79_8, &frame__79_5, 749, 749, 9, 21},
  {cont__79_9, &frame__79_5, 750, 750, 9, 64},
  {cont__79_10, &frame__79_5, 751, 751, 12, 23},
  {cont__79_11, &frame__79_5, 751, 751, 9, 29},
  {cont__79_12, &frame__79_5, 752, 752, 22, 22},
  {entry__79_4, NULL, 746, 752, 7, 22},
  {cont__79_13, &frame__79_4, 752, 752, 22, 22},
  {entry__79_3, NULL, 745, 752, 5, 23},
  {entry__79_17, NULL, 756, 756, 19, 65},
  {entry__79_16, NULL, 756, 756, 7, 65},
  {cont__79_19, &frame__79_16, 757, 757, 63, 63},
  {cont__79_20, &frame__79_16, 757, 757, 37, 64},
  {cont__79_21, &frame__79_16, 757, 757, 7, 64},
  {cont__79_22, &frame__79_16, 757, 757, 64, 64},
  {entry__79_25, NULL, 760, 760, 21, 66},
  {entry__79_24, NULL, 760, 760, 9, 66},
  {cont__79_27, &frame__79_24, 761, 761, 9, 44},
  {entry__79_23, NULL, 759, 761, 7, 44},
  {cont__79_28, &frame__79_23, 762, 762, 7, 32},
  {cont__79_30, &frame__79_23, 763, 763, 7, 32},
  {cont__79_32, &frame__79_23, 764, 764, 7, 34},
  {entry__79_36, NULL, 767, 767, 5, 40},
  {cont__79_37, &frame__79_36, 768, 768, 5, 32},
  {cont__79_38, &frame__79_36, 769, 769, 5, 20},
  {entry__79_1, NULL, 741, 741, 3, 80},
  {cont__79_2, &frame__79_1, 742, 752, 3, 24},
  {cont__79_14, &frame__79_1, 754, 754, 5, 28},
  {cont__79_15, &frame__79_1, 753, 764, 3, 35},
  {cont__79_34, &frame__79_1, 765, 765, 3, 29},
  {cont__79_35, &frame__79_1, 766, 769, 3, 20},
  {entry__80_7, NULL, 776, 777, 14, 58},
  {cont__80_10, &frame__80_7, 776, 777, 7, 58},
  {entry__80_12, NULL, 778, 778, 17, 73},
  {entry__80_35, NULL, 810, 812, 21, 49},
  {cont__80_38, &frame__80_35, 810, 812, 7, 49},
  {cont__80_39, &frame__80_35, 812, 812, 50, 50},
  {entry__80_49, NULL, 832, 832, 7, 42},
  {cont__80_50, &frame__80_49, 833, 833, 7, 34},
  {cont__80_51, &frame__80_49, 834, 839, 21, 23},
  {cont__80_54, &frame__80_49, 834, 839, 7, 23},
  {cont__80_55, &frame__80_49, 839, 839, 24, 24},
  {entry__80_2, NULL, 773, 773, 5, 55},
  {cont__80_4, &frame__80_2, 774, 774, 5, 31},
  {cont__80_5, &frame__80_2, 775, 775, 8, 22},
  {cont__80_6, &frame__80_2, 775, 777, 5, 59},
  {cont__80_11, &frame__80_2, 778, 778, 5, 73},
  {cont__80_14, &frame__80_2, 779, 779, 5, 40},
  {cont__80_15, &frame__80_2, 780, 780, 5, 18},
  {cont__80_16, &frame__80_2, 781, 781, 49, 49},
  {cont__80_17, &frame__80_2, 781, 781, 15, 50},
  {cont__80_18, &frame__80_2, 781, 781, 5, 74},
  {cont__80_20, &frame__80_2, 782, 782, 5, 31},
  {cont__80_21, &frame__80_2, 783, 783, 30, 73},
  {cont__80_22, &frame__80_2, 783, 783, 5, 78},
  {cont__80_23, &frame__80_2, 784, 784, 5, 33},
  {cont__80_25, &frame__80_2, 785, 785, 5, 61},
  {cont__80_28, &frame__80_2, 786, 786, 5, 25},
  {cont__80_29, &frame__80_2, 788, 808, 19, 22},
  {cont__80_33, &frame__80_2, 788, 808, 5, 22},
  {cont__80_34, &frame__80_2, 809, 812, 5, 50},
  {cont__80_40, &frame__80_2, 813, 830, 19, 21},
  {cont__80_47, &frame__80_2, 813, 830, 5, 21},
  {cont__80_48, &frame__80_2, 831, 839, 5, 24},
  {cont__80_56, &frame__80_2, 840, 846, 5, 32},
  {cont__80_58, &frame__80_2, 847, 847, 5, 25},
  {entry__80_1, NULL, 772, 847, 3, 25},
  {entry__81_4, NULL, 850, 850, 26, 56},
  {entry__81_7, NULL, 854, 854, 7, 41},
  {entry__81_12, NULL, 860, 860, 29, 50},
  {cont__81_13, &frame__81_12, 860, 860, 29, 55},
  {cont__81_14, &frame__81_12, 860, 860, 9, 56},
  {cont__81_15, &frame__81_12, 861, 861, 9, 47},
  {cont__81_16, &frame__81_12, 861, 861, 47, 47},
  {entry__81_20, NULL, 868, 868, 53, 66},
  {cont__81_22, &frame__81_20, 868, 868, 14, 67},
  {cont__81_24, &frame__81_20, 868, 868, 11, 67},
  {entry__81_25, NULL, 870, 870, 53, 67},
  {cont__81_28, &frame__81_25, 870, 870, 14, 68},
  {cont__81_30, &frame__81_25, 870, 870, 11, 68},
  {entry__81_31, NULL, 872, 872, 53, 69},
  {cont__81_34, &frame__81_31, 872, 872, 14, 70},
  {cont__81_36, &frame__81_31, 872, 872, 11, 70},
  {entry__81_37, NULL, 873, 873, 14, 50},
  {cont__81_40, &frame__81_37, 873, 873, 11, 50},
  {entry__81_45, NULL, 875, 875, 19, 56},
  {entry__81_54, NULL, 882, 882, 38, 63},
  {cont__81_55, &frame__81_54, 882, 882, 13, 63},
  {cont__81_56, &frame__81_54, 882, 882, 13, 63},
  {entry__81_58, NULL, 884, 884, 25, 25},
  {entry__81_51, NULL, 878, 878, 9, 32},
  {cont__81_52, &frame__81_51, 881, 881, 13, 29},
  {cont__81_53, &frame__81_51, 880, 882, 11, 62},
  {cont__81_57, &frame__81_51, 879, 884, 9, 26},
  {entry__81_61, NULL, 886, 886, 21, 54},
  {entry__81_72, NULL, 896, 896, 35, 47},
  {cont__81_73, &frame__81_72, 896, 896, 29, 47},
  {entry__81_64, NULL, 892, 892, 15, 76},
  {cont__81_67, &frame__81_64, 893, 893, 15, 43},
  {cont__81_68, &frame__81_64, 890, 895, 13, 26},
  {cont__81_71, &frame__81_64, 896, 896, 13, 47},
  {entry__81_81, NULL, 904, 904, 35, 47},
  {cont__81_82, &frame__81_81, 904, 904, 29, 47},
  {entry__81_74, NULL, 900, 900, 15, 43},
  {cont__81_75, &frame__81_74, 901, 901, 15, 30},
  {cont__81_77, &frame__81_74, 898, 903, 13, 26},
  {cont__81_80, &frame__81_74, 904, 904, 13, 47},
  {entry__81_94, NULL, 915, 915, 35, 47},
  {cont__81_95, &frame__81_94, 915, 915, 29, 47},
  {entry__81_83, NULL, 908, 910, 15, 23},
  {cont__81_87, &frame__81_83, 911, 911, 15, 43},
  {cont__81_88, &frame__81_83, 912, 912, 15, 30},
  {cont__81_90, &frame__81_83, 906, 914, 13, 26},
  {cont__81_93, &frame__81_83, 915, 915, 13, 47},
  {entry__81_101, NULL, 922, 922, 35, 47},
  {cont__81_102, &frame__81_101, 922, 922, 29, 47},
  {entry__81_96, NULL, 919, 919, 15, 43},
  {cont__81_97, &frame__81_96, 917, 921, 13, 26},
  {cont__81_100, &frame__81_96, 922, 922, 13, 47},
  {entry__81_60, NULL, 886, 886, 9, 54},
  {cont__81_63, &frame__81_60, 887, 922, 9, 48},
  {entry__81_8, NULL, 858, 858, 7, 56},
  {cont__81_10, &frame__81_8, 859, 859, 10, 38},
  {cont__81_11, &frame__81_8, 859, 861, 7, 47},
  {cont__81_17, &frame__81_8, 862, 862, 56, 56},
  {cont__81_18, &frame__81_8, 862, 862, 7, 57},
  {cont__81_19, &frame__81_8, 864, 873, 7, 51},
  {cont__81_44, &frame__81_8, 875, 875, 7, 56},
  {cont__81_47, &frame__81_8, 876, 876, 63, 63},
  {cont__81_48, &frame__81_8, 876, 876, 37, 64},
  {cont__81_49, &frame__81_8, 876, 876, 7, 64},
  {cont__81_50, &frame__81_8, 877, 884, 7, 27},
  {cont__81_59, &frame__81_8, 885, 922, 7, 49},
  {entry__81_1, NULL, 850, 850, 6, 23},
  {cont__81_3, &frame__81_1, 850, 850, 3, 56},
  {cont__81_6, &frame__81_1, 852, 922, 3, 51},
  {cont__81_106, &frame__81_1, 922, 922, 51, 51},
  {entry__82_8, NULL, 929, 930, 11, 42},
  {cont__82_11, &frame__82_8, 929, 930, 5, 42},
  {entry__82_15, NULL, 935, 935, 38, 65},
  {cont__82_16, &frame__82_15, 935, 935, 7, 34},
  {cont__82_17, &frame__82_15, 935, 935, 7, 65},
  {cont__82_18, &frame__82_15, 935, 935, 7, 65},
  {entry__82_21, NULL, 937, 937, 28, 65},
  {cont__82_23, &frame__82_21, 937, 937, 19, 65},
  {entry__82_20, NULL, 937, 937, 7, 65},
  {cont__82_24, &frame__82_20, 938, 938, 7, 37},
  {entry__82_1, NULL, 925, 925, 3, 35},
  {cont__82_3, &frame__82_1, 926, 926, 3, 35},
  {cont__82_5, &frame__82_1, 927, 927, 3, 26},
  {cont__82_6, &frame__82_1, 928, 928, 6, 24},
  {cont__82_7, &frame__82_1, 928, 930, 3, 43},
  {cont__82_12, &frame__82_1, 931, 931, 3, 26},
  {cont__82_13, &frame__82_1, 934, 934, 7, 25},
  {cont__82_14, &frame__82_1, 933, 935, 5, 64},
  {cont__82_19, &frame__82_1, 932, 938, 3, 38},
  {entry__84_11, NULL, 954, 954, 39, 41},
  {cont__84_12, &frame__84_11, 954, 954, 36, 41},
  {cont__84_13, &frame__84_11, 954, 954, 28, 43},
  {cont__84_15, &frame__84_11, 954, 954, 21, 48},
  {cont__84_16, &frame__84_11, 954, 954, 48, 48},
  {entry__84_6, NULL, 953, 953, 13, 26},
  {cont__84_7, &frame__84_6, 953, 953, 9, 28},
  {cont__84_8, &frame__84_6, 954, 954, 16, 18},
  {cont__84_9, &frame__84_6, 954, 954, 12, 18},
  {cont__84_10, &frame__84_6, 954, 954, 9, 48},
  {cont__84_17, &frame__84_6, 955, 955, 9, 13},
  {entry__84_4, NULL, 952, 952, 10, 19},
  {cont__84_5, &frame__84_4, 952, 955, 7, 13},
  {entry__84_3, NULL, 951, 955, 5, 14},
  {cont__84_18, &frame__84_3, 955, 955, 14, 14},
  {entry__84_21, NULL, 958, 958, 27, 30},
  {cont__84_22, &frame__84_21, 958, 958, 19, 31},
  {cont__84_24, &frame__84_21, 958, 958, 7, 31},
  {cont__84_25, &frame__84_21, 958, 958, 31, 31},
  {entry__84_28, NULL, 960, 960, 33, 36},
  {cont__84_29, &frame__84_28, 960, 960, 33, 38},
  {cont__84_30, &frame__84_28, 960, 960, 33, 39},
  {cont__84_31, &frame__84_28, 960, 960, 18, 39},
  {cont__84_32, &frame__84_28, 960, 960, 39, 39},
  {entry__84_26, NULL, 960, 960, 10, 15},
  {cont__84_27, &frame__84_26, 960, 960, 7, 39},
  {entry__84_1, NULL, 948, 948, 3, 16},
  {cont__84_2, &frame__84_1, 950, 955, 3, 15},
  {cont__84_19, &frame__84_1, 957, 957, 5, 10},
  {cont__84_20, &frame__84_1, 956, 960, 3, 40},
  {cont__84_33, &frame__84_1, 961, 961, 3, 8},
  {entry__85_4, NULL, 967, 967, 37, 37},
  {cont__85_5, &frame__85_4, 967, 967, 7, 37},
  {cont__85_6, &frame__85_4, 973, 973, 20, 41},
  {cont__85_7, &frame__85_4, 973, 973, 17, 41},
  {cont__85_8, &frame__85_4, 973, 973, 9, 42},
  {cont__85_10, &frame__85_4, 974, 974, 23, 29},
  {cont__85_11, &frame__85_4, 974, 974, 9, 34},
  {cont__85_12, &frame__85_4, 968, 975, 7, 12},
  {entry__85_14, NULL, 977, 977, 47, 53},
  {cont__85_15, &frame__85_14, 977, 977, 33, 58},
  {cont__85_16, &frame__85_14, 977, 977, 7, 63},
  {entry__85_1, NULL, 964, 964, 3, 23},
  {cont__85_2, &frame__85_1, 966, 966, 5, 23},
  {cont__85_3, &frame__85_1, 965, 977, 3, 64},
  {cont__85_19, &frame__85_1, 978, 978, 3, 19},
  {cont__85_20, &frame__85_1, 978, 978, 19, 19},
  {entry__86_5, NULL, 985, 985, 12, 38},
  {cont__86_7, &frame__86_5, 985, 985, 9, 38},
  {entry__86_8, NULL, 986, 986, 9, 23},
  {entry__86_10, NULL, 988, 988, 17, 57},
  {entry__86_22, NULL, 999, 999, 42, 69},
  {cont__86_23, &frame__86_22, 999, 999, 9, 38},
  {cont__86_24, &frame__86_22, 999, 999, 9, 69},
  {cont__86_25, &frame__86_22, 999, 999, 9, 69},
  {entry__86_20, NULL, 998, 998, 9, 27},
  {cont__86_21, &frame__86_20, 999, 999, 9, 69},
  {cont__86_26, &frame__86_20, },
  {entry__86_32, NULL, 1002, 1002, 21, 61},
  {entry__86_35, NULL, 1003, 1003, 41, 59},
  {cont__86_36, &frame__86_35, 1003, 1003, 35, 64},
  {entry__86_38, NULL, 1004, 1004, 32, 54},
  {entry__86_42, NULL, 1006, 1006, 28, 64},
  {entry__86_46, NULL, 1008, 1008, 28, 67},
  {entry__86_28, NULL, 1001, 1001, 55, 67},
  {cont__86_30, &frame__86_28, 1001, 1001, 9, 67},
  {cont__86_31, &frame__86_28, 1002, 1002, 9, 61},
  {cont__86_34, &frame__86_28, 1003, 1003, 9, 64},
  {cont__86_37, &frame__86_28, 1004, 1004, 9, 54},
  {cont__86_39, &frame__86_28, 1005, 1005, 25, 37},
  {cont__86_40, &frame__86_28, 1005, 1005, 9, 37},
  {cont__86_41, &frame__86_28, 1006, 1006, 9, 64},
  {cont__86_44, &frame__86_28, 1007, 1007, 9, 39},
  {cont__86_45, &frame__86_28, 1008, 1008, 9, 67},
  {cont__86_48, &frame__86_28, 1008, 1008, 67, 67},
  {entry__86_53, NULL, 1015, 1015, 44, 71},
  {cont__86_54, &frame__86_53, 1015, 1015, 13, 40},
  {cont__86_55, &frame__86_53, 1015, 1015, 13, 71},
  {cont__86_56, &frame__86_53, 1015, 1015, 13, 71},
  {entry__86_58, NULL, 1017, 1017, 13, 43},
  {entry__86_59, NULL, 1019, 1019, 13, 64},
  {cont__86_60, &frame__86_59, 1019, 1019, 64, 64},
  {entry__86_49, NULL, 1010, 1010, 9, 30},
  {cont__86_50, &frame__86_49, 1011, 1011, 9, 32},
  {cont__86_51, &frame__86_49, 1014, 1014, 13, 31},
  {cont__86_52, &frame__86_49, 1013, 1015, 11, 70},
  {cont__86_57, &frame__86_49, 1012, 1019, 9, 65},
  {entry__86_68, NULL, 1024, 1024, 11, 39},
  {entry__86_63, NULL, 1023, 1023, 9, 62},
  {cont__86_67, &frame__86_63, 1022, 1024, 7, 40},
  {entry__86_75, NULL, 1032, 1032, 38, 63},
  {cont__86_76, &frame__86_75, 1032, 1032, 13, 63},
  {cont__86_77, &frame__86_75, 1032, 1032, 13, 63},
  {entry__86_73, NULL, 1031, 1031, 13, 45},
  {cont__86_74, &frame__86_73, 1030, 1032, 11, 62},
  {cont__86_78, &frame__86_73, 1030, 1032, 11, 62},
  {entry__86_80, NULL, 1034, 1034, 23, 23},
  {entry__86_70, NULL, 1026, 1026, 7, 30},
  {cont__86_71, &frame__86_70, 1029, 1029, 11, 27},
  {cont__86_72, &frame__86_70, 1028, 1032, 9, 63},
  {cont__86_79, &frame__86_70, 1027, 1034, 7, 24},
  {entry__86_84, NULL, 1037, 1037, 28, 75},
  {cont__86_86, &frame__86_84, 1037, 1037, 75, 75},
  {entry__86_89, NULL, 1040, 1040, 23, 58},
  {entry__86_97, NULL, 1048, 1048, 33, 45},
  {cont__86_98, &frame__86_97, 1048, 1048, 27, 45},
  {entry__86_88, NULL, 1040, 1040, 11, 58},
  {cont__86_91, &frame__86_88, 1041, 1047, 11, 24},
  {cont__86_96, &frame__86_88, 1048, 1048, 11, 45},
  {entry__86_100, NULL, 1050, 1050, 23, 51},
  {entry__86_105, NULL, 1055, 1055, 18, 40},
  {cont__86_107, &frame__86_105, 1055, 1055, 15, 40},
  {entry__86_108, NULL, 1056, 1056, 18, 33},
  {cont__86_110, &frame__86_108, 1056, 1056, 15, 33},
  {entry__86_114, NULL, 1059, 1059, 33, 45},
  {cont__86_115, &frame__86_114, 1059, 1059, 27, 45},
  {entry__86_99, NULL, 1050, 1050, 11, 51},
  {cont__86_102, &frame__86_99, 1054, 1054, 15, 41},
  {cont__86_104, &frame__86_99, 1053, 1056, 13, 32},
  {cont__86_111, &frame__86_99, 1051, 1058, 11, 24},
  {cont__86_113, &frame__86_99, 1059, 1059, 11, 45},
  {entry__86_82, NULL, 1036, 1036, 7, 52},
  {cont__86_83, &frame__86_82, 1037, 1037, 7, 75},
  {cont__86_87, &frame__86_82, 1038, 1059, 7, 46},
  {entry__86_119, NULL, 1061, 1061, 24, 41},
  {cont__86_121, &frame__86_119, 1061, 1061, 24, 41},
  {entry__86_125, NULL, 1065, 1065, 11, 25},
  {entry__86_126, NULL, 1066, 1066, 14, 38},
  {cont__86_128, &frame__86_126, 1066, 1066, 11, 38},
  {entry__86_123, NULL, 1064, 1064, 11, 39},
  {cont__86_124, &frame__86_123, 1063, 1066, 9, 37},
  {cont__86_129, &frame__86_123, 1062, 1069, 7, 44},
  {entry__86_2, NULL, 984, 984, 9, 36},
  {cont__86_4, &frame__86_2, 982, 986, 5, 24},
  {cont__86_9, &frame__86_2, 988, 988, 5, 57},
  {cont__86_12, &frame__86_2, 989, 989, 5, 41},
  {cont__86_14, &frame__86_2, 990, 990, 5, 41},
  {cont__86_16, &frame__86_2, 991, 991, 5, 33},
  {cont__86_17, &frame__86_2, 992, 992, 5, 28},
  {cont__86_18, &frame__86_2, 994, 994, 5, 24},
  {cont__86_19, &frame__86_2, },
  {cont__86_27, &frame__86_2, 995, 1019, 5, 67},
  {cont__86_61, &frame__86_2, 1020, 1020, 5, 50},
  {cont__86_62, &frame__86_2, 1021, 1024, 5, 41},
  {cont__86_69, &frame__86_2, 1025, 1034, 5, 25},
  {cont__86_81, &frame__86_2, 1035, 1059, 5, 47},
  {cont__86_116, &frame__86_2, 1060, 1060, 41, 41},
  {cont__86_117, &frame__86_2, 1060, 1060, 5, 42},
  {cont__86_118, &frame__86_2, 1061, 1061, 8, 41},
  {cont__86_122, &frame__86_2, 1061, 1069, 5, 45},
  {entry__86_1, NULL, 981, 1069, 3, 46},
  {entry__100_2, NULL, 105, 105, 8, 28},
  {cont__100_3, &frame__100_2, 105, 105, 5, 28},
  {entry__100_4, NULL, 106, 106, 8, 66},
  {cont__100_7, &frame__100_4, 106, 106, 5, 66},
  {entry__101_2, NULL, 111, 111, 8, 29},
  {cont__101_3, &frame__101_2, 111, 111, 5, 29},
  {entry__101_4, NULL, 112, 112, 8, 66},
  {cont__101_7, &frame__101_4, 112, 112, 5, 66},
  {entry__105_3, NULL, 132, 132, 7, 41},
  {cont__105_4, &frame__105_3, 133, 133, 10, 26},
  {cont__105_5, &frame__105_3, 133, 133, 7, 32},
  {cont__105_6, &frame__105_3, 134, 134, 7, 19},
  {cont__105_7, &frame__105_3, 135, 135, 7, 34},
  {cont__105_8, &frame__105_3, 136, 136, 10, 21},
  {cont__105_9, &frame__105_3, 136, 136, 7, 27},
  {cont__105_10, &frame__105_3, 137, 137, 20, 20},
  {entry__105_2, NULL, 131, 137, 5, 20},
  {cont__105_11, &frame__105_2, 137, 137, 20, 20},
  {entry__105_1, NULL, 130, 137, 3, 21},
  {entry__131_5, NULL, 165, 165, 41, 79},
  {entry__131_3, NULL, 165, 165, 8, 38},
  {cont__131_4, &frame__131_3, 165, 165, 5, 79},
  {cont__131_7, &frame__131_3, 166, 166, 5, 45},
  {cont__131_8, &frame__131_3, 166, 166, 45, 45},
  {entry__131_10, NULL, 172, 173, 7, 52},
  {entry__131_13, NULL, 175, 176, 7, 34},
  {entry__131_16, NULL, 178, 179, 7, 57},
  {entry__131_19, NULL, 181, 182, 7, 71},
  {entry__131_22, NULL, 184, 185, 7, 47},
  {entry__131_25, NULL, 187, 188, 7, 61},
  {entry__131_28, NULL, 190, 193, 9, 29},
  {entry__131_31, NULL, 197, 198, 7, 33},
  {entry__131_34, NULL, 200, 201, 7, 29},
  {entry__131_37, NULL, 203, 204, 7, 35},
  {entry__131_40, NULL, 206, 207, 7, 40},
  {entry__131_43, NULL, 209, 210, 9, 65},
  {entry__131_46, NULL, 214, 215, 7, 35},
  {entry__131_49, NULL, 217, 218, 7, 45},
  {entry__131_52, NULL, 220, 221, 9, 31},
  {entry__131_55, NULL, 225, 226, 9, 65},
  {entry__131_58, NULL, 230, 231, 7, 32},
  {entry__131_61, NULL, 233, 234, 7, 33},
  {entry__131_64, NULL, 236, 237, 7, 43},
  {entry__131_67, NULL, 239, 240, 7, 29},
  {entry__131_70, NULL, 242, 243, 7, 46},
  {entry__131_9, NULL, 168, 243, 5, 47},
  {cont__131_73, &frame__131_9, 243, 243, 48, 48},
  {entry__135_1, NULL, 247, 247, 37, 37},
  {entry__161_2, NULL, 634, 635, 9, 51},
  {cont__161_5, &frame__161_2, 634, 635, 3, 51},
  {entry__176_1, NULL, 1071, 1071, 20, 36},
  {cont__176_2, &frame__176_1, 1071, 1071, 36, 36},
  {entry__177_4, NULL, 1078, 1078, 7, 32},
  {entry__177_3, NULL, },
  {cont__177_5, &frame__177_3, },
  {entry__177_2, NULL, },
  {cont__177_6, &frame__177_2, },
  {entry__177_1, NULL, },
  {cont__177_7, &frame__177_1, 1073, 1079, 3, 24},
  {entry__177_8, NULL, 1080, 1080, 3, 23},
  {entry__177_9, NULL, 1081, 1081, 3, 43},
  {entry__177_10, NULL, 1082, 1082, 3, 57},
  {entry__177_11, NULL, 1083, 1083, 6, 29},
  {cont__177_12, &frame__177_11, 1083, 1083, 3, 43}
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
  // 96: ... "@(MAJOR).@(MINOR).@(REVISION).@(BUILD)"
  argument_count = 7;
  arguments = node_p;
  arguments->slots[0] = var._MAJOR;
  arguments->slots[1] = string__95_1;
  arguments->slots[2] = var._MINOR;
  arguments->slots[3] = string__95_2;
  arguments->slots[4] = var._REVISION;
  arguments->slots[5] = string__95_3;
  arguments->slots[6] = var._BUILD;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__95_4;
}
static void cont__95_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 96: version "@(MAJOR).@(MINOR).@(REVISION).@(BUILD)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = 0;
  myself = get__version();
  func = myself->type;
  frame->cont = cont__95_5;
}
static void cont__95_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 97: extern $gcc "gcc"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__96_1;
  result_count = 1;
  myself = get__extern();
  func = myself->type;
  frame->cont = cont__96_2;
}
static void cont__96_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._gcc, arguments->slots[0]);
  // 98: extern $mkdir "mkdir" # would be nice to have one in the system library!
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
  initialize_future(var._mkdir, arguments->slots[0]);
  // 99: $SIMLIBPATH environment("SIMLIBPATH")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__98_1;
  result_count = 1;
  myself = get__environment();
  func = myself->type;
  frame->cont = cont__98_2;
}
static void cont__98_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._SIMLIBPATH, arguments->slots[0]);
  // 100: $SIMDATAPATH environment("SIMDATAPATH")
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
  initialize_future(var._SIMDATAPATH, arguments->slots[0]);
  // 104: SIMLIBPATH.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._SIMLIBPATH;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__100_1;
}
static void cont__100_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 102: $simlibpaths
  // 103:   if
  // 104:     SIMLIBPATH.is_defined
  // 105:     -> split(SIMLIBPATH ':')
  // 106:     -> list("/usr/local/share/simplicity" "/usr/share/simplicity")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__100_2;
  arguments->slots[2] = func__100_4;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__100_8;
}
static void entry__100_2(void) {
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
  frame->cont = cont__100_3;
}
static void cont__100_3(void) {
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
static void entry__100_4(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 106: ... list("/usr/local/share/simplicity" "/usr/share/simplicity")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__100_5;
  arguments->slots[1] = string__100_6;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__100_7;
}
static void cont__100_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 106: -> list("/usr/local/share/simplicity" "/usr/share/simplicity")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__100_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._simlibpaths, arguments->slots[0]);
  // 110: SIMDATAPATH.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._SIMDATAPATH;
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
  // 108: $simdatapaths
  // 109:   if
  // 110:     SIMDATAPATH.is_defined
  // 111:     -> split(SIMDATAPATH ':')
  // 112:     -> list("/usr/local/share/simplicity" "/usr/share/simplicity")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__101_2;
  arguments->slots[2] = func__101_4;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__101_8;
}
static void entry__101_2(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 111: ... split(SIMDATAPATH ':')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._SIMDATAPATH;
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
  // 111: -> split(SIMDATAPATH ':')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__101_4(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 112: ... list("/usr/local/share/simplicity" "/usr/share/simplicity")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__101_5;
  arguments->slots[1] = string__101_6;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__101_7;
}
static void cont__101_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 112: -> list("/usr/local/share/simplicity" "/usr/share/simplicity")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__101_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._simdatapaths, arguments->slots[0]);
  // 118: "bsd" = "posix"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__103_1;
  arguments->slots[1] = string__103_2;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__103_3;
}
static void cont__103_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 119: "cygwin" = "posix"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__103_4;
  arguments->slots[1] = string__103_5;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__103_6;
}
static void cont__103_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 120: "darwin" = "posix"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__103_7;
  arguments->slots[1] = string__103_8;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__103_9;
}
static void cont__103_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 121: "linux" = "posix"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__103_10;
  arguments->slots[1] = string__103_11;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__103_12;
}
static void cont__103_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 122: "posix" = "all"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__103_13;
  arguments->slots[1] = string__103_14;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__103_15;
}
static void cont__103_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 123: "win" = "all"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__103_16;
  arguments->slots[1] = string__103_17;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__103_18;
}
static void cont__103_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 124: "all" = NONE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__103_19;
  arguments->slots[1] = var._NONE;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__103_20;
}
static void cont__103_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__7 */ = arguments->slots[0];
  // 116: $supported_platforms
  // 117:   key_order_table
  // 118:     "bsd" = "posix"
  // 119:     "cygwin" = "posix"
  // 120:     "darwin" = "posix"
  // 121:     "linux" = "posix"
  // 122:     "posix" = "all"
  // 123:     "win" = "all"
  // 124:     "all" = NONE
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
  frame->cont = cont__103_21;
}
static void cont__103_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._supported_platforms, arguments->slots[0]);
  // 126: $$platform_priority empty_table
  var._platform_priority = get__empty_table();
  // 127: do:
  // 128:   $$platform current_platform
  // 129:   $$priority 0
  // 130:   do: (-> break)
  // 131:     forever:
  // 132:       $plat supported_platforms(platform)
  // 133:       if plat.is_undefined break
  // 134:       inc &priority
  // 135:       !platform_priority(platform) priority
  // 136:       if plat == NONE break
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__105_1;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__105_12;
}
static void entry__105_2(void) {
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
  // 131: ... :
  // 132:   $plat supported_platforms(platform)
  // 133:   if plat.is_undefined break
  // 134:   inc &priority
  // 135:   !platform_priority(platform) priority
  // 136:   if plat == NONE break
  // 137:   !platform plat
  frame->slots[3] /* temp__1 */ = create_closure(entry__105_3, 0);
  // 131: forever:
  // 132:   $plat supported_platforms(platform)
  // 133:   if plat.is_undefined break
  // 134:   inc &priority
  // 135:   !platform_priority(platform) priority
  // 136:   if plat == NONE break
  // 137:   !platform plat
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame->cont = cont__105_11;
}
static void entry__105_3(void) {
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
  // 132: $plat supported_platforms(platform)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* platform */;
  result_count = 1;
  myself = var._supported_platforms;
  func = myself->type;
  frame->cont = cont__105_4;
}
static void cont__105_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* plat */, arguments->slots[0]);
  // 133: ... plat.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* plat */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__105_5;
}
static void cont__105_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 133: if plat.is_undefined break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* break */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__105_6;
}
static void cont__105_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 134: inc &priority
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* priority */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__105_7;
}
static void cont__105_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* priority */ = arguments->slots[0];
  // 135: !platform_priority(platform) priority
  frame->slots[4] /* temp__1 */ = ((CELL *)frame->slots[2])->contents /* priority */;
  // 135: !platform_priority(platform)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* platform */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = var._platform_priority;
  func = myself->type;
  frame->cont = cont__105_8;
}
static void cont__105_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._platform_priority = arguments->slots[0];
  // 136: ... plat == NONE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* plat */;
  arguments->slots[1] = var._NONE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__105_9;
}
static void cont__105_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 136: if plat == NONE break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* break */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__105_10;
}
static void cont__105_10(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 137: !platform plat
  ((CELL *)frame->slots[0])->contents /* platform */ = frame->slots[3] /* plat */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__105_11(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__105_1(void) {
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
  // 128: $$platform current_platform
  ((CELL *)frame->slots[0])->contents /* platform */ = get__current_platform();
  // 129: $$priority 0
  ((CELL *)frame->slots[1])->contents /* priority */ = number__0;
  // 130: ... : (-> break)
  // 131:   forever:
  // 132:     $plat supported_platforms(platform)
  // 133:     if plat.is_undefined break
  // 134:     inc &priority
  // 135:     !platform_priority(platform) priority
  // 136:     if plat == NONE break
  // 137:     !platform plat
  frame->slots[2] /* temp__1 */ = create_closure(entry__105_2, 0);
  // 130: do: (-> break)
  // 131:   forever:
  // 132:     $plat supported_platforms(platform)
  // 133:     if plat.is_undefined break
  // 134:     inc &priority
  // 135:     !platform_priority(platform) priority
  // 136:     if plat == NONE break
  // 137:     !platform plat
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__do();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__105_12(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 138: $$platform_specific_priority undefined
  var._platform_specific_priority = get__undefined();
  // 139: $$module_info empty_table
  var._module_info = get__empty_table();
  // 140: $$meta_levels empty_table # 0 -> no meta files
  var._meta_levels = get__empty_table();
  // 141: $$do_rebuild false
  var._do_rebuild = get__false();
  // 142: $$do_omit_meta false
  var._do_omit_meta = get__false();
  // 143: $$sim2c::do_dump_trees false
  var.sim2c__do_dump_trees = get__false();
  // 144: $$sim2c::do_pretty_print false
  var.sim2c__do_pretty_print = get__false();
  // 145: $$sim2c::do_print_simplified_source false
  var.sim2c__do_print_simplified_source = get__false();
  // 146: $$sim2c::do_show_debug_infos false
  var.sim2c__do_show_debug_infos = get__false();
  // 147: $$sim2c::do_show_compiler_debug_infos false
  var.sim2c__do_show_compiler_debug_infos = get__false();
  // 148: $$sim2c::do_check_only false
  var.sim2c__do_check_only = get__false();
  // 149: $$sim2c::do_show_brief_messages false
  var.sim2c__do_show_brief_messages = get__false();
  // 150: $$sim2c::do_print_warnings false
  var.sim2c__do_print_warnings = get__false();
  // 151: $$sim2c::verbose false
  var.sim2c__verbose = get__false();
  // 152: $$do_print_c false
  var._do_print_c = get__false();
  // 153: $$sim2c::do_extract_documentation false
  var.sim2c__do_extract_documentation = get__false();
  // 154: $$do_build_codeblocks_project false
  var._do_build_codeblocks_project = get__false();
  // 155: $$do_list_dependencies false
  var._do_list_dependencies = get__false();
  // 156: $$do_build_static false
  var._do_build_static = get__false();
  // 157: $$do_link_profiler false
  var._do_link_profiler = get__false();
  // 158: $$sim2c::do_time_passes false
  var.sim2c__do_time_passes = get__false();
  // 159: $$sim2c::do_use_goto false
  var.sim2c__do_use_goto = get__false();
  // 160: $$module_prefix undefined
  var._module_prefix = get__undefined();
  // 161: $$input_filename undefined
  var._input_filename = get__undefined();
  // 162: ... 1
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
  // 162: $action truncate_until(program_name '/' -1)
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
  // 164: action == "simrun"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._action;
  arguments->slots[1] = string__131_1;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__131_2;
}
static void cont__131_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 163: if
  // 164:   action == "simrun":
  // 165:     if command_line_arguments.is_empty: Error "Missing command line arguments!"
  // 166:     !input_filename command_line_arguments(1)
  // 167:   :
  // 168:     program_parameters
  // 169:       # the following options act on a single file only
  // 170:       
  // 171:       !sim2c::do_check_only
  // 172:       -> "check-only" "
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__131_3;
  arguments->slots[2] = func__131_9;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__131_74;
}
static void entry__131_3(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 165: ... command_line_arguments.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__command_line_arguments();
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__131_4;
}
static void cont__131_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 165: if command_line_arguments.is_empty: Error "Missing command line arguments!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__131_5;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__131_7;
}
static void entry__131_5(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 165: ... Error "Missing command line arguments!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__131_6;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__131_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 166: !input_filename command_line_arguments(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__command_line_arguments();
  func = myself->type;
  frame->cont = cont__131_8;
}
static void cont__131_8(void) {
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
static void entry__131_9(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 168: program_parameters
  // 169:   # the following options act on a single file only
  // 170:   
  // 171:   !sim2c::do_check_only
  // 172:   -> "check-only" "
  // 173:     do not compile; just check for syntax errors
  // 174:   !sim2c::do_dump_trees
  // 175:   -> "dump-trees" "
  // 176:     dump abstract syntax trees
  // 177:   !sim2c::do_pretty_print
  // ...
  argument_count = 21;
  arguments = node_p;
  arguments->slots[0] = func__131_10;
  arguments->slots[1] = func__131_13;
  arguments->slots[2] = func__131_16;
  arguments->slots[3] = func__131_19;
  arguments->slots[4] = func__131_22;
  arguments->slots[5] = func__131_25;
  arguments->slots[6] = func__131_28;
  arguments->slots[7] = func__131_31;
  arguments->slots[8] = func__131_34;
  arguments->slots[9] = func__131_37;
  arguments->slots[10] = func__131_40;
  arguments->slots[11] = func__131_43;
  arguments->slots[12] = func__131_46;
  arguments->slots[13] = func__131_49;
  arguments->slots[14] = func__131_52;
  arguments->slots[15] = func__131_55;
  arguments->slots[16] = func__131_58;
  arguments->slots[17] = func__131_61;
  arguments->slots[18] = func__131_64;
  arguments->slots[19] = func__131_67;
  arguments->slots[20] = func__131_70;
  result_count = 21;
  myself = get__program_parameters();
  func = myself->type;
  frame->cont = cont__131_73;
}
static void entry__131_10(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 172: -> "check-only" "
  // 173:   do not compile; just check for syntax errors
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__131_11;
  arguments->slots[1] = string__131_12;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__131_13(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 175: -> "dump-trees" "
  // 176:   dump abstract syntax trees
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__131_14;
  arguments->slots[1] = string__131_15;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__131_16(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 178: -> "pretty-print" "
  // 179:   do not compile; just pretty print the source file
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__131_17;
  arguments->slots[1] = string__131_18;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__131_19(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 181: -> "print-simplified-source" "
  // 182:   do not generate a C-file; just print the simplified source text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__131_20;
  arguments->slots[1] = string__131_21;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__131_22(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 184: -> "print-c" "
  // 185:   print C source code for a single module
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__131_23;
  arguments->slots[1] = string__131_24;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__131_25(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 187: -> "time-passes" "
  // 188:   print running time for the individual compiler passes
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__131_26;
  arguments->slots[1] = string__131_27;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__131_28(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 190: -> VALUED_OPTION "module-prefix" "
  // 191:   needed to compile a single file within a subdirectory;
  // 192:   if the subdirectories are nested use slashes to separate
  // 193:   the directory names
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__VALUED_OPTION();
  arguments->slots[1] = string__131_29;
  arguments->slots[2] = string__131_30;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__131_31(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 197: -> "brief" "
  // 198:   show brief error messages
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__131_32;
  arguments->slots[1] = string__131_33;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__131_34(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 200: -> "warnings" "
  // 201:   show warning messages
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__131_35;
  arguments->slots[1] = string__131_36;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__131_37(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 203: -> "verbose" "
  // 204:   output verbose informations
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__131_38;
  arguments->slots[1] = string__131_39;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__131_40(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 206: -> "debug" "
  // 207:   show C-compiler and linker calls
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__131_41;
  arguments->slots[1] = string__131_42;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__131_43(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 209: -> "debug_compiler" "
  // 210:   show internal debug messages of the Simplicity compiler
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__131_44;
  arguments->slots[1] = string__131_45;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__131_46(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 214: -> "codeblocks" "
  // 215:   create Code::Blocks project
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__131_47;
  arguments->slots[1] = string__131_48;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__131_49(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 217: -> "extract-documentation" "
  // 218:   extract documentation encoded as HTML
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__131_50;
  arguments->slots[1] = string__131_51;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__131_52(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 220: -> "list-dependencies" "
  // 221:   list all dependencies
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__131_53;
  arguments->slots[1] = string__131_54;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__131_55(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 225: -> "goto" "
  // 226:   the compiler uses goto-statements to link continuations
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__131_56;
  arguments->slots[1] = string__131_57;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__131_58(void) {
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
  arguments->slots[0] = string__131_59;
  arguments->slots[1] = string__131_60;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__131_61(void) {
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
  arguments->slots[0] = string__131_62;
  arguments->slots[1] = string__131_63;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__131_64(void) {
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
  arguments->slots[0] = string__131_65;
  arguments->slots[1] = string__131_66;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__131_67(void) {
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
  arguments->slots[0] = string__131_68;
  arguments->slots[1] = string__131_69;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__131_70(void) {
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
  arguments->slots[1] = string__131_71;
  arguments->slots[2] = string__131_72;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__131_73(void) {
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
static void cont__131_74(void) {
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
  frame->cont = cont__132_1;
}
static void cont__132_1(void) {
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
  frame->cont = cont__133_1;
}
static void cont__133_1(void) {
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
  // 247: ... !verbose true
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
  // 255: %mode undefined # EXE or LIB
  initialize_maybe_future(get__mode(), get__undefined());
  // 256: $WHITESPACE many(' ')
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
  argument_count = 10;
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
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__141_11;
}
static void cont__141_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._gcc_basic_options, arguments->slots[0]);
  // 273: ... list("-msse2" "-mfpmath=sse")
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
  // 273: "x86_32" = list("-msse2" "-mfpmath=sse")
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
  // 274: ... list("-msse2" "-mfpmath=sse")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__142_6;
  arguments->slots[1] = string__142_7;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__142_8;
}
static void cont__142_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 274: "x86_64" = list("-msse2" "-mfpmath=sse")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__142_9;
  arguments->slots[1] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__142_10;
}
static void cont__142_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 271: $gcc_hardware_specific_options
  // 272:   table
  // 273:     "x86_32" = list("-msse2" "-mfpmath=sse")
  // 274:     "x86_64" = list("-msse2" "-mfpmath=sse")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__table();
  func = myself->type;
  frame->cont = cont__142_11;
}
static void cont__142_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._gcc_hardware_specific_options, arguments->slots[0]);
  // 280: ... hardware_architecture()
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
  // 280: gcc_hardware_specific_options(hardware_architecture())
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
  // 279: default_value
  // 280:   gcc_hardware_specific_options(hardware_architecture())
  // 281:   empty_list
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
  // 276: $gcc_options
  // 277:   append
  // 278:     gcc_basic_options
  // 279:     default_value
  // 280:       gcc_hardware_specific_options(hardware_architecture())
  // 281:       empty_list
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
  // 283: %on_top_level true # set to false while building meta-files
  initialize_maybe_future(get__on_top_level(), get__true());
  // 284: %%objects empty_insert_order_set
  set__objects(get__empty_insert_order_set());
  // 285: %%libraries empty_insert_order_set # contains "-lsim-..."-entries
  set__libraries(get__empty_insert_order_set());
  // 286: %%do_link false
  set__do_link(get__false());
  // 287: %%last_modification_time undefined
  set__last_modification_time(get__undefined());
  // 288: $$c_sources empty_insert_order_set
  var._c_sources = get__empty_insert_order_set();
  // 289: $$dependencies empty_list
  var._dependencies = get__empty_list();
  // 290: $$resolved_libraries undefined
  var._resolved_libraries = get__undefined();
  // 633: ... main_info.is_undefined
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
  // 633: if main_info.is_undefined:
  // 634:   Error "
  // 635:     Source file "@(main_filename)" does not exist!@
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
  // 634: ... "
  // 635:   Source file "@(main_filename)" does not exist!@
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
  // 634: Error "
  // 635:   Source file "@(main_filename)" does not exist!@
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
  // 940: $$t undefined
  var._t = get__undefined();
  // 1071: if do_time_passes: !t current_time()
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
  // 1071: ... !t current_time()
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
  // 1078: do_print_simplified_source
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
static void entry__177_8(void) {
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
static void entry__177_9(void) {
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
static void entry__177_10(void) {
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
static void entry__177_11(void) {
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
  frame->cont = cont__177_12;
}
static void cont__177_12(void) {
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
  // 250: ... ewriteln args*
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__47_1(void) {
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
static void entry__63_1(void) {
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
  // 293: ... resolved_libraries.is_undefined
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
  // 293: if resolved_libraries.is_undefined:
  // 294:   !resolved_libraries empty_table
  // 295:   for_each simlibpaths: (path)
  // 296:     for_each directory(path): (entry)
  // 297:       if entry.is_a_directory:
  // 298:         $name std::filename_of(entry)
  // 299:         if name .matches. NAME: !resolved_libraries(name) fullname_of(entry)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = func__63_3;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__63_14;
}
static void entry__63_11(void) {
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
  // 299: ... !resolved_libraries(name) fullname_of(entry)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* entry */;
  result_count = 1;
  myself = get__fullname_of();
  func = myself->type;
  frame->cont = cont__63_12;
}
static void cont__63_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 299: ... !resolved_libraries(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = var._resolved_libraries;
  func = myself->type;
  frame->cont = cont__63_13;
}
static void cont__63_13(void) {
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
static void entry__63_8(void) {
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
  // 298: $name std::filename_of(entry)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* entry */;
  result_count = 1;
  myself = get__std__filename_of();
  func = myself->type;
  frame->cont = cont__63_9;
}
static void cont__63_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* name */, arguments->slots[0]);
  // 299: ... name .matches. NAME
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* name */;
  arguments->slots[1] = get__NAME();
  result_count = 1;
  myself = get__matches();
  func = myself->type;
  frame->cont = cont__63_10;
}
static void cont__63_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 299: ... : !resolved_libraries(name) fullname_of(entry)
  frame->slots[3] /* temp__2 */ = create_closure(entry__63_11, 0);
  // 299: if name .matches. NAME: !resolved_libraries(name) fullname_of(entry)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__63_6(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // entry: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 297: ... entry.is_a_directory
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* entry */;
  result_count = 1;
  myself = get__is_a_directory();
  func = myself->type;
  frame->cont = cont__63_7;
}
static void cont__63_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 297: ... :
  // 298:   $name std::filename_of(entry)
  // 299:   if name .matches. NAME: !resolved_libraries(name) fullname_of(entry)
  frame->slots[2] /* temp__2 */ = create_closure(entry__63_8, 0);
  // 297: if entry.is_a_directory:
  // 298:   $name std::filename_of(entry)
  // 299:   if name .matches. NAME: !resolved_libraries(name) fullname_of(entry)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__63_4(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // path: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 296: ... directory(path)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* path */;
  result_count = 1;
  myself = get__directory();
  func = myself->type;
  frame->cont = cont__63_5;
}
static void cont__63_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 296: for_each directory(path): (entry)
  // 297:   if entry.is_a_directory:
  // 298:     $name std::filename_of(entry)
  // 299:     if name .matches. NAME: !resolved_libraries(name) fullname_of(entry)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__63_6;
  result_count = frame->caller_result_count;
  myself = get__for_each();
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
  // 294: !resolved_libraries empty_table
  var._resolved_libraries = get__empty_table();
  // 295: for_each simlibpaths: (path)
  // 296:   for_each directory(path): (entry)
  // 297:     if entry.is_a_directory:
  // 298:       $name std::filename_of(entry)
  // 299:       if name .matches. NAME: !resolved_libraries(name) fullname_of(entry)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._simlibpaths;
  arguments->slots[1] = func__63_4;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__63_14(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 300: $libname filename .before. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__63_15;
}
static void cont__63_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* libname */, arguments->slots[0]);
  // 301: $libpath resolved_libraries(libname)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* libname */;
  result_count = 1;
  myself = var._resolved_libraries;
  func = myself->type;
  frame->cont = cont__63_16;
}
static void cont__63_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* libpath */, arguments->slots[0]);
  // 302: ... libpath.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* libpath */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__63_17;
}
static void cont__63_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 302: ... :
  // 303:   Error "
  // 304:     Cannot resolve required library "@(libname)@quot;!@
  frame->slots[4] /* temp__2 */ = create_closure(entry__63_18, 0);
  // 302: if libpath.is_undefined:
  // 303:   Error "
  // 304:     Cannot resolve required library "@(libname)@quot;!@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__63_22;
}
static void entry__63_18(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // libname: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* libname */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 303: ... "
  // 304:   Cannot resolve required library "@(libname)@quot;!@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__63_19;
  arguments->slots[1] = frame->slots[0] /* libname */;
  arguments->slots[2] = string__63_20;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__63_21;
}
static void cont__63_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 303: Error "
  // 304:   Cannot resolve required library "@(libname)@quot;!@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__63_22(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 305: ... filename .from. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__from();
  func = myself->type;
  frame->cont = cont__63_23;
}
static void cont__63_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 305: ... string(libpath filename .from. '/')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* libpath */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__63_24;
}
static void cont__63_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 305: -> string(libpath filename .from. '/')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__64_1(void) {
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
  // 316: ... --SORT
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
  // 316: $entries directory(--SORT path)
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
  // 317: $$filenames empty_set
  ((CELL *)frame->slots[4])->contents /* filenames */ = get__empty_set();
  // 318: $$directories empty_list
  ((CELL *)frame->slots[5])->contents /* directories */ = get__empty_list();
  // 319: $$modules empty_key_order_set
  ((CELL *)frame->slots[6])->contents /* modules */ = get__empty_key_order_set();
  // 320: ... : (entry)
  // 321:   $name std::filename_of(entry)
  // 322:   cond
  // 323:     -> entry.is_a_directory: if name .matches. NAME: push &directories name
  // 324:     -> name .has_suffix. ".sim":
  // 325:       $submodule_name name .without_suffix. (some(".meta"), ".sim")
  // 326:       !filenames(submodule_name) true
  // 327:       $meta_level (length_of(name)-length_of(submodule_name)-4)/5
  // 328:       $stored_level meta_levels(submodule_name)
  // 329:       if stored_level.is_undefined || meta_level > stored_level:
  // ...
  frame->slots[7] /* temp__1 */ = create_closure(entry__64_4, 1);
  // 320: for_each entries: (entry)
  // 321:   $name std::filename_of(entry)
  // 322:   cond
  // 323:     -> entry.is_a_directory: if name .matches. NAME: push &directories name
  // 324:     -> name .has_suffix. ".sim":
  // 325:       $submodule_name name .without_suffix. (some(".meta"), ".sim")
  // 326:       !filenames(submodule_name) true
  // 327:       $meta_level (length_of(name)-length_of(submodule_name)-4)/5
  // 328:       $stored_level meta_levels(submodule_name)
  // 329:       if stored_level.is_undefined || meta_level > stored_level:
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* entries */;
  arguments->slots[1] = frame->slots[7] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__64_39;
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
  // 325: ... some(".meta")
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
  // 325: ... some(".meta"), ".sim"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__2 */;
  arguments->slots[1] = string__64_18;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__64_19;
}
static void cont__64_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 325: $submodule_name name .without_suffix. (some(".meta"), ".sim")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = get__without_suffix();
  func = myself->type;
  frame->cont = cont__64_20;
}
static void cont__64_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* submodule_name */, arguments->slots[0]);
  // 326: !filenames(submodule_name) true
  frame->slots[9] /* temp__1 */ = get__true();
  // 326: !filenames(submodule_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* submodule_name */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* filenames */;
  func = myself->type;
  frame->cont = cont__64_21;
}
static void cont__64_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* filenames */ = arguments->slots[0];
  // 327: ... length_of(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
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
  frame->slots[11] /* temp__3 */ = arguments->slots[0];
  // 327: ... length_of(submodule_name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* submodule_name */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__64_23;
}
static void cont__64_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__4 */ = arguments->slots[0];
  // 327: ... length_of(name)-length_of(submodule_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__3 */;
  arguments->slots[1] = frame->slots[12] /* temp__4 */;
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
  frame->slots[10] /* temp__2 */ = arguments->slots[0];
  // 327: ... length_of(name)-length_of(submodule_name)-4
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__2 */;
  arguments->slots[1] = number__4;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__64_25;
}
static void cont__64_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 327: $meta_level (length_of(name)-length_of(submodule_name)-4)/5
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__std__over();
  func = myself->type;
  frame->cont = cont__64_26;
}
static void cont__64_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* meta_level */, arguments->slots[0]);
  // 328: $stored_level meta_levels(submodule_name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* submodule_name */;
  result_count = 1;
  myself = var._meta_levels;
  func = myself->type;
  frame->cont = cont__64_27;
}
static void cont__64_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* stored_level */, arguments->slots[0]);
  // 329: ... stored_level.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* stored_level */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__64_28;
}
static void cont__64_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__2 */ = arguments->slots[0];
  // 329: ... meta_level > stored_level
  frame->slots[11] /* temp__3 */ = create_closure(entry__64_29, 0);
  // 329: ... stored_level.is_undefined || meta_level > stored_level
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__2 */;
  arguments->slots[1] = frame->slots[11] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__64_31;
}
static void entry__64_29(void) {
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
  // 329: ... meta_level > stored_level
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stored_level */;
  arguments->slots[1] = frame->slots[1] /* meta_level */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__64_30;
}
static void cont__64_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 329: ... meta_level > stored_level
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__64_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 329: ... :
  // 330:   !meta_levels(submodule_name) meta_level
  frame->slots[12] /* temp__4 */ = create_closure(entry__64_32, 0);
  // 329: if stored_level.is_undefined || meta_level > stored_level:
  // 330:   !meta_levels(submodule_name) meta_level
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = frame->slots[12] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__64_34;
}
static void entry__64_32(void) {
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
  // 330: !meta_levels(submodule_name) meta_level
  frame->slots[2] /* temp__1 */ = frame->slots[1] /* meta_level */;
  // 330: !meta_levels(submodule_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* submodule_name */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = var._meta_levels;
  func = myself->type;
  frame->cont = cont__64_33;
}
static void cont__64_33(void) {
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
static void cont__64_34(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 331: $basename submodule_name .truncate_from. '-'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* submodule_name */;
  arguments->slots[1] = character__45;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__64_35;
}
static void cont__64_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[7] /* basename */, arguments->slots[0]);
  // 332: !modules(basename) true
  frame->slots[9] /* temp__1 */ = get__true();
  // 332: !modules(basename)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* basename */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[2])->contents /* modules */;
  func = myself->type;
  frame->cont = cont__64_36;
}
static void cont__64_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* modules */ = arguments->slots[0];
  // 333: $mod_name string(mod_path basename)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* mod_path */;
  arguments->slots[1] = frame->slots[7] /* basename */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__64_37;
}
static void cont__64_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[8] /* mod_name */, arguments->slots[0]);
  // 334: !module_info(mod_name) empty_key_order_table
  frame->slots[9] /* temp__1 */ = get__empty_key_order_table();
  // 334: !module_info(mod_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* mod_name */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = var._module_info;
  func = myself->type;
  frame->cont = cont__64_38;
}
static void cont__64_38(void) {
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
  // 323: ... push &directories name
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
  // 323: ... name .matches. NAME
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
  // 323: ... : push &directories name
  frame->slots[3] /* temp__2 */ = create_closure(entry__64_10, 0);
  // 323: ... if name .matches. NAME: push &directories name
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
  // 323: ... entry.is_a_directory
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
  // 323: ... : if name .matches. NAME: push &directories name
  frame->slots[4] /* temp__2 */ = create_closure(entry__64_8, 0);
  // 323: -> entry.is_a_directory: if name .matches. NAME: push &directories name
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
  // 324: ... name .has_suffix. ".sim"
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
  // 324: ... :
  // 325:   $submodule_name name .without_suffix. (some(".meta"), ".sim")
  // 326:   !filenames(submodule_name) true
  // 327:   $meta_level (length_of(name)-length_of(submodule_name)-4)/5
  // 328:   $stored_level meta_levels(submodule_name)
  // 329:   if stored_level.is_undefined || meta_level > stored_level:
  // 330:     !meta_levels(submodule_name) meta_level
  // 331:   $basename submodule_name .truncate_from. '-'
  // 332:   !modules(basename) true
  // 333:   $mod_name string(mod_path basename)
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__64_15, 0);
  // 324: -> name .has_suffix. ".sim":
  // 325:   $submodule_name name .without_suffix. (some(".meta"), ".sim")
  // 326:   !filenames(submodule_name) true
  // 327:   $meta_level (length_of(name)-length_of(submodule_name)-4)/5
  // 328:   $stored_level meta_levels(submodule_name)
  // 329:   if stored_level.is_undefined || meta_level > stored_level:
  // 330:     !meta_levels(submodule_name) meta_level
  // 331:   $basename submodule_name .truncate_from. '-'
  // 332:   !modules(basename) true
  // 333:   $mod_name string(mod_path basename)
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
  // 321: $name std::filename_of(entry)
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
  // 323: -> entry.is_a_directory: if name .matches. NAME: push &directories name
  frame->slots[6] /* temp__1 */ = create_closure(entry__64_6, 0);
  // 324: -> name .has_suffix. ".sim":
  // 325:   $submodule_name name .without_suffix. (some(".meta"), ".sim")
  // 326:   !filenames(submodule_name) true
  // 327:   $meta_level (length_of(name)-length_of(submodule_name)-4)/5
  // 328:   $stored_level meta_levels(submodule_name)
  // 329:   if stored_level.is_undefined || meta_level > stored_level:
  // 330:     !meta_levels(submodule_name) meta_level
  // 331:   $basename submodule_name .truncate_from. '-'
  // 332:   !modules(basename) true
  // 333:   $mod_name string(mod_path basename)
  // ...
  frame->slots[7] /* temp__2 */ = create_closure(entry__64_12, 0);
  // 322: cond
  // 323:   -> entry.is_a_directory: if name .matches. NAME: push &directories name
  // 324:   -> name .has_suffix. ".sim":
  // 325:     $submodule_name name .without_suffix. (some(".meta"), ".sim")
  // 326:     !filenames(submodule_name) true
  // 327:     $meta_level (length_of(name)-length_of(submodule_name)-4)/5
  // 328:     $stored_level meta_levels(submodule_name)
  // 329:     if stored_level.is_undefined || meta_level > stored_level:
  // 330:       !meta_levels(submodule_name) meta_level
  // 331:     $basename submodule_name .truncate_from. '-'
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
static void cont__64_39(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 335: ... : (filename)
  // 336:   if filename .contains. '-':
  // 337:     unless filename .has_suffix. "-common":
  // 338:       $maybe_push_common: (plat)
  // 339:         $common_name string(name "-" plat "-common")
  // 340:         if filenames(common_name): push &files common_name
  // 341:       
  // 342:       $name filename .before. '-'
  // 343:       $mod_name string(mod_path name .truncate_from. '-')
  // 344:       $platform filename .behind. '-'
  // ...
  frame->slots[7] /* temp__1 */ = create_closure(entry__64_40, 1);
  // 335: for_each filenames: (filename)
  // 336:   if filename .contains. '-':
  // 337:     unless filename .has_suffix. "-common":
  // 338:       $maybe_push_common: (plat)
  // 339:         $common_name string(name "-" plat "-common")
  // 340:         if filenames(common_name): push &files common_name
  // 341:       
  // 342:       $name filename .before. '-'
  // 343:       $mod_name string(mod_path name .truncate_from. '-')
  // 344:       $platform filename .behind. '-'
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* filenames */;
  arguments->slots[1] = frame->slots[7] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__64_76;
}
static void entry__64_45(void) {
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
  // 338: ... : (plat)
  // 339:   $common_name string(name "-" plat "-common")
  // 340:   if filenames(common_name): push &files common_name
  frame->slots[9] /* temp__1 */ = create_closure(entry__64_46, 1);
  // 338: $maybe_push_common: (plat)
  // 339:   $common_name string(name "-" plat "-common")
  // 340:   if filenames(common_name): push &files common_name
  initialize_future(frame->slots[3] /* maybe_push_common */, frame->slots[9] /* temp__1 */);
  // 342: $name filename .before. '-'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* filename */;
  arguments->slots[1] = character__45;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__64_53;
}
static void entry__64_51(void) {
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
  // 340: ... push &files common_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* files */;
  arguments->slots[1] = frame->slots[1] /* common_name */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__64_52;
}
static void cont__64_52(void) {
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
static void entry__64_46(void) {
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
  // 339: $common_name string(name "-" plat "-common")
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* name */;
  arguments->slots[1] = string__64_47;
  arguments->slots[2] = frame->slots[0] /* plat */;
  arguments->slots[3] = string__64_48;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__64_49;
}
static void cont__64_49(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* common_name */, arguments->slots[0]);
  // 340: ... filenames(common_name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* common_name */;
  result_count = 1;
  myself = ((CELL *)frame->slots[2])->contents /* filenames */;
  func = myself->type;
  frame->cont = cont__64_50;
}
static void cont__64_50(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 340: ... : push &files common_name
  frame->slots[6] /* temp__2 */ = create_closure(entry__64_51, 0);
  // 340: if filenames(common_name): push &files common_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__64_53(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* name */, arguments->slots[0]);
  // 343: ... name .truncate_from. '-'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* name */;
  arguments->slots[1] = character__45;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__64_54;
}
static void cont__64_54(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 343: $mod_name string(mod_path name .truncate_from. '-')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* mod_path */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__64_55;
}
static void cont__64_55(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* mod_name */, arguments->slots[0]);
  // 344: $platform filename .behind. '-'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* filename */;
  arguments->slots[1] = character__45;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__64_56;
}
static void cont__64_56(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* platform */, arguments->slots[0]);
  // 345: $$parent supported_platforms(platform)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* platform */;
  result_count = 1;
  myself = var._supported_platforms;
  func = myself->type;
  frame->cont = cont__64_57;
}
static void cont__64_57(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[7])->contents /* parent */ = arguments->slots[0];
  // 346: ... parent.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[7])->contents /* parent */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__64_58;
}
static void cont__64_58(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 346: ... :
  // 347:   Error "
  // 348:     The platform "@(platform)" is not supported!@
  frame->slots[10] /* temp__2 */ = create_closure(entry__64_59, 0);
  // 346: unless parent.is_defined:
  // 347:   Error "
  // 348:     The platform "@(platform)" is not supported!@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__64_63;
}
static void entry__64_59(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // platform: 0
  frame->slots[0] = myself->closure.frame->slots[6]; /* platform */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 347: ... "
  // 348:   The platform "@(platform)" is not supported!@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__64_60;
  arguments->slots[1] = frame->slots[0] /* platform */;
  arguments->slots[2] = string__64_61;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__64_62;
}
static void cont__64_62(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 347: Error "
  // 348:   The platform "@(platform)" is not supported!@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__64_63(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 349: $$files list(filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* filename */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__64_64;
}
static void cont__64_64(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[8])->contents /* files */ = arguments->slots[0];
  // 350: maybe_push_common platform
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* platform */;
  result_count = 0;
  myself = frame->slots[3] /* maybe_push_common */;
  func = myself->type;
  frame->cont = cont__64_65;
}
static void cont__64_65(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 351: ... -> parent != NONE:
  // 352:   maybe_push_common parent
  // 353:   !parent supported_platforms(parent)
  frame->slots[9] /* temp__1 */ = create_closure(entry__64_66, 0);
  // 351: while -> parent != NONE:
  // 352:   maybe_push_common parent
  // 353:   !parent supported_platforms(parent)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  result_count = 0;
  myself = get__while();
  func = myself->type;
  frame->cont = cont__64_72;
}
static void entry__64_69(void) {
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
  // 352: maybe_push_common parent
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* parent */;
  result_count = 0;
  myself = frame->slots[0] /* maybe_push_common */;
  func = myself->type;
  frame->cont = cont__64_70;
}
static void cont__64_70(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 353: !parent supported_platforms(parent)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* parent */;
  result_count = 1;
  myself = var._supported_platforms;
  func = myself->type;
  frame->cont = cont__64_71;
}
static void cont__64_71(void) {
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
static void entry__64_66(void) {
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
  // 351: ... parent != NONE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parent */;
  arguments->slots[1] = var._NONE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__64_67;
}
static void cont__64_67(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 351: ... parent != NONE
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__64_68;
}
static void cont__64_68(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 351: ... :
  // 352:   maybe_push_common parent
  // 353:   !parent supported_platforms(parent)
  frame->slots[4] /* temp__3 */ = create_closure(entry__64_69, 0);
  // 351: ... -> parent != NONE:
  // 352:   maybe_push_common parent
  // 353:   !parent supported_platforms(parent)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__64_72(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 354: !module_info(mod_name)(platform) files
  frame->slots[9] /* temp__1 */ = ((CELL *)frame->slots[8])->contents /* files */;
  // 354: ... module_info(mod_name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* mod_name */;
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
  frame->slots[10] /* temp__2 */ = arguments->slots[0];
  // 354: !module_info(mod_name)(platform)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* platform */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = frame->slots[10] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__64_74;
}
static void cont__64_74(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__2 */ = arguments->slots[0];
  // 354: !module_info(mod_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* mod_name */;
  arguments->slots[1] = frame->slots[10] /* temp__2 */;
  result_count = 1;
  myself = var._module_info;
  func = myself->type;
  frame->cont = cont__64_75;
}
static void cont__64_75(void) {
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
static void entry__64_42(void) {
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
  // 337: ... filename .has_suffix. "-common"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  arguments->slots[1] = string__64_43;
  result_count = 1;
  myself = get__has_suffix();
  func = myself->type;
  frame->cont = cont__64_44;
}
static void cont__64_44(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 337: ... :
  // 338:   $maybe_push_common: (plat)
  // 339:     $common_name string(name "-" plat "-common")
  // 340:     if filenames(common_name): push &files common_name
  // 341:   
  // 342:   $name filename .before. '-'
  // 343:   $mod_name string(mod_path name .truncate_from. '-')
  // 344:   $platform filename .behind. '-'
  // 345:   $$parent supported_platforms(platform)
  // 346:   unless parent.is_defined:
  // ...
  frame->slots[4] /* temp__2 */ = create_closure(entry__64_45, 0);
  // 337: unless filename .has_suffix. "-common":
  // 338:   $maybe_push_common: (plat)
  // 339:     $common_name string(name "-" plat "-common")
  // 340:     if filenames(common_name): push &files common_name
  // 341:   
  // 342:   $name filename .before. '-'
  // 343:   $mod_name string(mod_path name .truncate_from. '-')
  // 344:   $platform filename .behind. '-'
  // 345:   $$parent supported_platforms(platform)
  // 346:   unless parent.is_defined:
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
static void entry__64_40(void) {
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
  // 336: ... filename .contains. '-'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  arguments->slots[1] = character__45;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__64_41;
}
static void cont__64_41(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 336: ... :
  // 337:   unless filename .has_suffix. "-common":
  // 338:     $maybe_push_common: (plat)
  // 339:       $common_name string(name "-" plat "-common")
  // 340:       if filenames(common_name): push &files common_name
  // 341:     
  // 342:     $name filename .before. '-'
  // 343:     $mod_name string(mod_path name .truncate_from. '-')
  // 344:     $platform filename .behind. '-'
  // 345:     $$parent supported_platforms(platform)
  // ...
  frame->slots[4] /* temp__2 */ = create_closure(entry__64_42, 0);
  // 336: if filename .contains. '-':
  // 337:   unless filename .has_suffix. "-common":
  // 338:     $maybe_push_common: (plat)
  // 339:       $common_name string(name "-" plat "-common")
  // 340:       if filenames(common_name): push &files common_name
  // 341:     
  // 342:     $name filename .before. '-'
  // 343:     $mod_name string(mod_path name .truncate_from. '-')
  // 344:     $platform filename .behind. '-'
  // 345:     $$parent supported_platforms(platform)
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
static void cont__64_76(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 355: ... parameter_count_of(return)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* return */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__64_77;
}
static void cont__64_77(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 355: ... parameter_count_of(return) == 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__2 */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__64_78;
}
static void cont__64_78(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 355: ... : return directories modules
  frame->slots[9] /* temp__3 */ = create_closure(entry__64_79, 0);
  // 355: if parameter_count_of(return) == 2: return directories modules
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__64_80;
}
static void entry__64_79(void) {
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
  // 355: ... return directories modules
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* directories */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* modules */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__64_80(void) {
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
  // 366: ... -> info
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
  // 367: ... 1
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
  // 367: ... before(mod_filename '/' -1)
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
  // 367: ... 1
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
  // 367: ... until(mod_name '/' -1)
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
  // 367: add_module_infos before(mod_filename '/' -1) until(mod_name '/' -1)
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
  // 368: ... module_info(mod_name)
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
  // 368: -> module_info(mod_name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__65_1(void) {
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
  // 365: $info module_info(mod_name)
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
  // 366: ... info.is_defined
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
  // 366: ... -> info
  frame->slots[4] /* temp__2 */ = create_closure(entry__65_4, 0);
  // 366: ... :
  // 367:   add_module_infos before(mod_filename '/' -1) until(mod_name '/' -1)
  // 368:   -> module_info(mod_name)
  frame->slots[5] /* temp__3 */ = create_closure(entry__65_5, 0);
  // 366: if info.is_defined (-> info):
  // 367:   add_module_infos before(mod_filename '/' -1) until(mod_name '/' -1)
  // 368:   -> module_info(mod_name)
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
static void entry__66_1(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // args: 0
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 371: ... : ewriteln "gcc " join(args)
  frame->slots[1] /* temp__1 */ = create_closure(entry__66_2, 0);
  // 371: if do_show_debug_infos: ewriteln "gcc " join(args)
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
  // 371: ... join(args)
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
  // 371: ... ewriteln "gcc " join(args)
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
  // 372: gcc args*
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = frame->caller_result_count;
  myself = var._gcc;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__67_4(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // c_filename: 0
  // o_filename: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* c_filename */
  frame->slots[1] = myself->closure.frame->slots[1]; /* o_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 378: ... :
  // 379:   Gcc $_out $err $success gcc_options* "-c" c_filename "-o" o_filename
  // 380:   unless success: Error err.from_utf8
  frame->slots[2] /* temp__1 */ = create_closure(entry__67_5, 0);
  // 381: ... :
  // 382:   Gcc $_out $err $success
  // 383:     "-DWITHIN_LIBRARY"
  // 384:     gcc_options*
  // 385:     "-fPIC"
  // 386:     "-c"
  // 387:     c_filename
  // 388:     "-o"
  // 389:     o_filename
  // 390:   unless success: Error err.from_utf8
  frame->slots[3] /* temp__2 */ = create_closure(entry__67_11, 0);
  // 376: case
  // 377:   mode
  // 378:   EXE:
  // 379:     Gcc $_out $err $success gcc_options* "-c" c_filename "-o" o_filename
  // 380:     unless success: Error err.from_utf8
  // 381:   LIB:
  // 382:     Gcc $_out $err $success
  // 383:       "-DWITHIN_LIBRARY"
  // 384:       gcc_options*
  // 385:       "-fPIC"
  // ...
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = get__mode();
  arguments->slots[1] = var._EXE;
  arguments->slots[2] = frame->slots[2] /* temp__1 */;
  arguments->slots[3] = var._LIB;
  arguments->slots[4] = frame->slots[3] /* temp__2 */;
  result_count = 0;
  myself = get__case();
  func = myself->type;
  frame->cont = cont__67_19;
}
static void entry__67_17(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // err: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* err */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 390: ... err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* err */;
  result_count = 1;
  myself = get__from_utf8();
  func = myself->type;
  frame->cont = cont__67_18;
}
static void cont__67_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 390: ... Error err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__67_9(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // err: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* err */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 380: ... err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* err */;
  result_count = 1;
  myself = get__from_utf8();
  func = myself->type;
  frame->cont = cont__67_10;
}
static void cont__67_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 380: ... Error err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__67_5(void) {
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
  arguments->slots[argument_count++] = string__67_6;
  arguments->slots[argument_count++] = frame->slots[0] /* c_filename */;
  arguments->slots[argument_count++] = string__67_7;
  arguments->slots[argument_count++] = frame->slots[1] /* o_filename */;
  result_count = 3;
  myself = var._Gcc;
  func = myself->type;
  frame->cont = cont__67_8;
}
static void cont__67_8(void) {
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
  // 380: ... : Error err.from_utf8
  frame->slots[5] /* temp__1 */ = create_closure(entry__67_9, 0);
  // 380: unless success: Error err.from_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* success */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__67_11(void) {
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
  // 382: Gcc $_out $err $success
  // 383:   "-DWITHIN_LIBRARY"
  // 384:   gcc_options*
  // 385:   "-fPIC"
  // 386:   "-c"
  // 387:   c_filename
  // 388:   "-o"
  // 389:   o_filename
  argument_count = 0;
  arguments = node_p;
  arguments->slots[argument_count++] = string__67_12;
  unfold(var._gcc_options);
  arguments->slots[argument_count++] = string__67_13;
  arguments->slots[argument_count++] = string__67_14;
  arguments->slots[argument_count++] = frame->slots[0] /* c_filename */;
  arguments->slots[argument_count++] = string__67_15;
  arguments->slots[argument_count++] = frame->slots[1] /* o_filename */;
  result_count = 3;
  myself = var._Gcc;
  func = myself->type;
  frame->cont = cont__67_16;
}
static void cont__67_16(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  frame->slots[6] /* temp__2 */ = arguments->slots[1];
  frame->slots[7] /* temp__3 */ = arguments->slots[2];
  // 382: ... _out
  initialize_future(frame->slots[2] /* out */, frame->slots[5] /* temp__1 */);
  // 382: ... err
  initialize_future(frame->slots[3] /* err */, frame->slots[6] /* temp__2 */);
  // 382: ... success
  initialize_future(frame->slots[4] /* success */, frame->slots[7] /* temp__3 */);
  // 390: ... : Error err.from_utf8
  frame->slots[5] /* temp__1 */ = create_closure(entry__67_17, 0);
  // 390: unless success: Error err.from_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* success */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__67_19(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 391: !do_link true
  set__do_link(get__true());
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__67_1(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // c_filename: 0
  // o_filename: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 375: ... do_build_codeblocks_project || do_list_dependencies
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
  // 375: ... do_list_dependencies
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
  // 375: ... :
  // 376:   case
  // 377:     mode
  // 378:     EXE:
  // 379:       Gcc $_out $err $success gcc_options* "-c" c_filename "-o" o_filename
  // 380:       unless success: Error err.from_utf8
  // 381:     LIB:
  // 382:       Gcc $_out $err $success
  // 383:         "-DWITHIN_LIBRARY"
  // 384:         gcc_options*
  // ...
  frame->slots[3] /* temp__2 */ = create_closure(entry__67_4, 0);
  // 375: unless do_build_codeblocks_project || do_list_dependencies:
  // 376:   case
  // 377:     mode
  // 378:     EXE:
  // 379:       Gcc $_out $err $success gcc_options* "-c" c_filename "-o" o_filename
  // 380:       unless success: Error err.from_utf8
  // 381:     LIB:
  // 382:       Gcc $_out $err $success
  // 383:         "-DWITHIN_LIBRARY"
  // 384:         gcc_options*
  // ...
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
  // 403: ... 1
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
  // 403: $meta_path truncate_from(mod_filename '/' -1)
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
  // 404: ... dup(".meta" meta_level)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__68_5;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* meta_level */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__68_6;
}
static void cont__68_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 404: $filename string(mod_filename dup(".meta" meta_level))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = frame->slots[11] /* temp__1 */;
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
  initialize_future(frame->slots[3] /* filename */, arguments->slots[0]);
  // 405: $meta_filename string(filename ".sim")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* filename */;
  arguments->slots[1] = string__68_8;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__68_9;
}
static void cont__68_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* meta_filename */, arguments->slots[0]);
  // 406: ... dup(".meta" meta_level)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__68_10;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* meta_level */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__68_11;
}
static void cont__68_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 406: $meta_c_filename string(mod_filename dup(".meta" meta_level) ".c")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = frame->slots[11] /* temp__1 */;
  arguments->slots[2] = string__68_12;
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
  initialize_future(frame->slots[5] /* meta_c_filename */, arguments->slots[0]);
  // 407: ... meta_level-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* meta_level */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__68_14;
}
static void cont__68_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__2 */ = arguments->slots[0];
  // 407: ... dup(".meta" meta_level-1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__68_15;
  arguments->slots[1] = frame->slots[12] /* temp__2 */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__68_16;
}
static void cont__68_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 407: $sim_filename string(mod_filename dup(".meta" meta_level-1) ".sim")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = frame->slots[11] /* temp__1 */;
  arguments->slots[2] = string__68_17;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__68_18;
}
static void cont__68_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* sim_filename */, arguments->slots[0]);
  // 408: $meta_info stat(meta_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* meta_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__68_19;
}
static void cont__68_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[7] /* meta_info */, arguments->slots[0]);
  // 409: $sim_info stat(sim_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* sim_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__68_20;
}
static void cont__68_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[8] /* sim_info */, arguments->slots[0]);
  // 410: $meta_c_info stat(meta_c_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* meta_c_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__68_21;
}
static void cont__68_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[9] /* meta_c_info */, arguments->slots[0]);
  frame->slots[11] /* temp__1 */ = create_closure(entry__68_22, 0);
  // 412: $$force_rebuild
  // 413:   ||
  // 414:     do_rebuild
  // 415:     sim_info.is_undefined
  // 416:     meta_c_info.is_undefined
  // 417:     modification_time_of(meta_info) > modification_time_of(meta_c_info)
  // 418:     modification_time_of(meta_c_info) > modification_time_of(sim_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_rebuild;
  arguments->slots[1] = frame->slots[11] /* temp__1 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__68_37;
}
static void entry__68_22(void) {
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
  // 415: sim_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* sim_info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__68_23;
}
static void cont__68_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  frame->slots[5] /* temp__3 */ = create_closure(entry__68_24, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__68_36;
}
static void entry__68_24(void) {
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
  // 416: meta_c_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* meta_c_info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__68_25;
}
static void cont__68_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  frame->slots[5] /* temp__3 */ = create_closure(entry__68_26, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__68_35;
}
static void entry__68_26(void) {
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
  // 417: ... modification_time_of(meta_c_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* meta_c_info */;
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
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 417: modification_time_of(meta_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* meta_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__68_28;
}
static void cont__68_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__4 */ = arguments->slots[0];
  // 417: modification_time_of(meta_info) > modification_time_of(meta_c_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__68_29;
}
static void cont__68_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 418: modification_time_of(meta_c_info) > modification_time_of(sim_info)
  frame->slots[7] /* temp__5 */ = create_closure(entry__68_30, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__5 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__68_34;
}
static void entry__68_30(void) {
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
  // 418: ... modification_time_of(sim_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* sim_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__68_31;
}
static void cont__68_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 418: modification_time_of(meta_c_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* meta_c_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__68_32;
}
static void cont__68_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 418: modification_time_of(meta_c_info) > modification_time_of(sim_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__68_33;
}
static void cont__68_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 418: modification_time_of(meta_c_info) > modification_time_of(sim_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__68_34(void) {
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
static void cont__68_35(void) {
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
static void cont__68_36(void) {
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
static void cont__68_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[10])->contents /* force_rebuild */ = arguments->slots[0];
  // 420: ... :
  // 421:   $modification_time modification_time_of(sim_info)
  // 422:   load $meta_c_buf meta_c_filename
  // 423:   do: (-> break)
  // 424:     for_each_line meta_c_buf: ($line)
  // 425:       $check: (data_filename)
  // 426:         $data_info stat(data_filename)
  // 427:         if
  // 428:           ||
  // 429:             data_info.is_undefined
  // ...
  frame->slots[11] /* temp__1 */ = create_closure(entry__68_38, 0);
  // 420: unless force_rebuild:
  // 421:   $modification_time modification_time_of(sim_info)
  // 422:   load $meta_c_buf meta_c_filename
  // 423:   do: (-> break)
  // 424:     for_each_line meta_c_buf: ($line)
  // 425:       $check: (data_filename)
  // 426:         $data_info stat(data_filename)
  // 427:         if
  // 428:           ||
  // 429:             data_info.is_undefined
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[10])->contents /* force_rebuild */;
  arguments->slots[1] = frame->slots[11] /* temp__1 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__68_71;
}
static void entry__68_41(void) {
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
  // 424: ... : ($line)
  // 425:   $check: (data_filename)
  // 426:     $data_info stat(data_filename)
  // 427:     if
  // 428:       ||
  // 429:         data_info.is_undefined
  // 430:         modification_time_of(data_info) > modification_time
  // 431:       :
  // 432:         !force_rebuild true
  // 433:         break
  // ...
  frame->slots[5] /* temp__1 */ = create_closure(entry__68_42, 1);
  // 424: for_each_line meta_c_buf: ($line)
  // 425:   $check: (data_filename)
  // 426:     $data_info stat(data_filename)
  // 427:     if
  // 428:       ||
  // 429:         data_info.is_undefined
  // 430:         modification_time_of(data_info) > modification_time
  // 431:       :
  // 432:         !force_rebuild true
  // 433:         break
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* meta_c_buf */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each_line();
  func = myself->type;
  frame->cont = cont__68_70;
}
static void entry__68_68(void) {
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
  // 445: ... string(path '/' argument)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* path */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[2] /* argument */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__68_69;
}
static void cont__68_69(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 445: ... check string(path '/' argument)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* check */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__68_63(void) {
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
  // 443: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__68_64;
}
static void cont__68_64(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 443: ... range(argument 2 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* argument */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__68_65;
}
static void cont__68_65(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 443: ... string(meta_path range(argument 2 -1))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* meta_path */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__68_66;
}
static void cont__68_66(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 443: check string(meta_path range(argument 2 -1))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* check */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__68_67(void) {
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
  // 445: ... : (path) check string(path '/' argument)
  frame->slots[2] /* temp__1 */ = create_closure(entry__68_68, 1);
  // 445: for_each simdatapaths: (path) check string(path '/' argument)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._simdatapaths;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__68_60(void) {
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
  // 442: argument .has_prefix. "./"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* argument */;
  arguments->slots[1] = string__68_61;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__68_62;
}
static void cont__68_62(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 442: ... :
  // 443:   check string(meta_path range(argument 2 -1))
  frame->slots[4] /* temp__2 */ = create_closure(entry__68_63, 0);
  // 444: :
  // 445:   for_each simdatapaths: (path) check string(path '/' argument)
  frame->slots[5] /* temp__3 */ = create_closure(entry__68_67, 0);
  // 441: if
  // 442:   argument .has_prefix. "./":
  // 443:     check string(meta_path range(argument 2 -1))
  // 444:   :
  // 445:     for_each simdatapaths: (path) check string(path '/' argument)
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
static void entry__68_42(void) {
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
  // 425: ... : (data_filename)
  // 426:   $data_info stat(data_filename)
  // 427:   if
  // 428:     ||
  // 429:       data_info.is_undefined
  // 430:       modification_time_of(data_info) > modification_time
  // 431:     :
  // 432:       !force_rebuild true
  // 433:       break
  frame->slots[8] /* temp__1 */ = create_closure(entry__68_43, 1);
  // 425: $check: (data_filename)
  // 426:   $data_info stat(data_filename)
  // 427:   if
  // 428:     ||
  // 429:       data_info.is_undefined
  // 430:       modification_time_of(data_info) > modification_time
  // 431:     :
  // 432:       !force_rebuild true
  // 433:       break
  initialize_future(frame->slots[5] /* check */, frame->slots[8] /* temp__1 */);
  // 435: ... line .has_prefix. "/// "
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  arguments->slots[1] = string__68_51;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__68_52;
}
static void entry__68_50(void) {
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
  // 432: !force_rebuild true
  ((CELL *)frame->slots[0])->contents /* force_rebuild */ = get__true();
  // 433: break
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* break */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__68_43(void) {
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
  // 426: $data_info stat(data_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* data_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__68_44;
}
static void cont__68_44(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* data_info */, arguments->slots[0]);
  // 429: data_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* data_info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__68_45;
}
static void cont__68_45(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 430: modification_time_of(data_info) > modification_time
  frame->slots[7] /* temp__3 */ = create_closure(entry__68_46, 0);
  // 428: ||
  // 429:   data_info.is_undefined
  // 430:   modification_time_of(data_info) > modification_time
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__68_49;
}
static void entry__68_46(void) {
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
  // 430: modification_time_of(data_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* data_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__68_47;
}
static void cont__68_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 430: modification_time_of(data_info) > modification_time
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* modification_time */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__68_48;
}
static void cont__68_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 430: modification_time_of(data_info) > modification_time
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__68_49(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 431: :
  // 432:   !force_rebuild true
  // 433:   break
  frame->slots[8] /* temp__4 */ = create_closure(entry__68_50, 0);
  // 427: if
  // 428:   ||
  // 429:     data_info.is_undefined
  // 430:     modification_time_of(data_info) > modification_time
  // 431:   :
  // 432:     !force_rebuild true
  // 433:     break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__68_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 435: unless line .has_prefix. "/// " break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* break */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__68_53;
}
static void cont__68_53(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 436: behind &line ' '
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  arguments->slots[1] = character__32;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__68_54;
}
static void cont__68_54(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* line */ = arguments->slots[0];
  // 437: trim &line
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__68_55;
}
static void cont__68_55(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* line */ = arguments->slots[0];
  // 438: $command line .truncate_from. WHITESPACE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  arguments->slots[1] = var._WHITESPACE;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__68_56;
}
static void cont__68_56(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* command */, arguments->slots[0]);
  // 439: $argument line .behind. WHITESPACE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  arguments->slots[1] = var._WHITESPACE;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__68_57;
}
static void cont__68_57(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[7] /* argument */, arguments->slots[0]);
  // 440: ... command == "data"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* command */;
  arguments->slots[1] = string__68_58;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__68_59;
}
static void cont__68_59(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 440: ... :
  // 441:   if
  // 442:     argument .has_prefix. "./":
  // 443:       check string(meta_path range(argument 2 -1))
  // 444:     :
  // 445:       for_each simdatapaths: (path) check string(path '/' argument)
  frame->slots[9] /* temp__2 */ = create_closure(entry__68_60, 0);
  // 440: if command == "data":
  // 441:   if
  // 442:     argument .has_prefix. "./":
  // 443:       check string(meta_path range(argument 2 -1))
  // 444:     :
  // 445:       for_each simdatapaths: (path) check string(path '/' argument)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__68_70(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__68_38(void) {
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
  // 421: $modification_time modification_time_of(sim_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* sim_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__68_39;
}
static void cont__68_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* modification_time */, arguments->slots[0]);
  // 422: load $meta_c_buf meta_c_filename
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* meta_c_filename */;
  result_count = 1;
  myself = get__load();
  func = myself->type;
  frame->cont = cont__68_40;
}
static void cont__68_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* meta_c_buf */, arguments->slots[0]);
  // 423: ... : (-> break)
  // 424:   for_each_line meta_c_buf: ($line)
  // 425:     $check: (data_filename)
  // 426:       $data_info stat(data_filename)
  // 427:       if
  // 428:         ||
  // 429:           data_info.is_undefined
  // 430:           modification_time_of(data_info) > modification_time
  // 431:         :
  // 432:           !force_rebuild true
  // ...
  frame->slots[6] /* temp__1 */ = create_closure(entry__68_41, 0);
  // 423: do: (-> break)
  // 424:   for_each_line meta_c_buf: ($line)
  // 425:     $check: (data_filename)
  // 426:       $data_info stat(data_filename)
  // 427:       if
  // 428:         ||
  // 429:           data_info.is_undefined
  // 430:           modification_time_of(data_info) > modification_time
  // 431:         :
  // 432:           !force_rebuild true
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__do();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__68_71(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 446: ... :
  // 447:   %on_top_level false
  // 448:   %%objects empty_insert_order_set
  // 449:   %%libraries empty_insert_order_set
  // 450:   %%do_link false
  // 451:   %%last_modification_time undefined
  // 452:   %do_build_static_executable false
  // 453:   %main_filename meta_filename
  // 454:   %main_info stat(main_filename)
  // 455:   build_executable
  // ...
  frame->slots[11] /* temp__1 */ = create_closure(entry__68_72, 0);
  // 446: if force_rebuild:
  // 447:   %on_top_level false
  // 448:   %%objects empty_insert_order_set
  // 449:   %%libraries empty_insert_order_set
  // 450:   %%do_link false
  // 451:   %%last_modification_time undefined
  // 452:   %do_build_static_executable false
  // 453:   %main_filename meta_filename
  // 454:   %main_info stat(main_filename)
  // 455:   build_executable
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[10])->contents /* force_rebuild */;
  arguments->slots[1] = frame->slots[11] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__68_84;
}
static void entry__68_72(void) {
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
  // 447: %on_top_level false
  initialize_maybe_future(get__on_top_level(), get__false());
  // 448: %%objects empty_insert_order_set
  set__objects(get__empty_insert_order_set());
  // 449: %%libraries empty_insert_order_set
  set__libraries(get__empty_insert_order_set());
  // 450: %%do_link false
  set__do_link(get__false());
  // 451: %%last_modification_time undefined
  set__last_modification_time(get__undefined());
  // 452: %do_build_static_executable false
  initialize_maybe_future(get__do_build_static_executable(), get__false());
  // 453: %main_filename meta_filename
  initialize_maybe_future(get__main_filename(), frame->slots[1] /* meta_filename */);
  // 454: %main_info stat(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__68_73;
}
static void cont__68_73(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(get__main_info(), arguments->slots[0]);
  // 455: build_executable
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._build_executable;
  func = myself->type;
  frame->cont = cont__68_74;
}
static void cont__68_74(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 456: $orig_path current_path()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__current_path();
  func = myself->type;
  frame->cont = cont__68_75;
}
static void cont__68_75(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* orig_path */, arguments->slots[0]);
  // 457: change_directory meta_path
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* meta_path */;
  result_count = 0;
  myself = get__change_directory();
  func = myself->type;
  frame->cont = cont__68_76;
}
static void cont__68_76(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 458: std::call $out $err $success filename
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* filename */;
  result_count = 3;
  myself = get__std__call();
  func = myself->type;
  frame->cont = cont__68_77;
}
static void cont__68_77(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  frame->slots[10] /* temp__2 */ = arguments->slots[1];
  frame->slots[11] /* temp__3 */ = arguments->slots[2];
  // 458: ... out
  initialize_future(frame->slots[6] /* out */, frame->slots[9] /* temp__1 */);
  // 458: ... err
  initialize_future(frame->slots[7] /* err */, frame->slots[10] /* temp__2 */);
  // 458: ... success
  initialize_future(frame->slots[8] /* success */, frame->slots[11] /* temp__3 */);
  // 459: change_directory orig_path
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* orig_path */;
  result_count = 0;
  myself = get__change_directory();
  func = myself->type;
  frame->cont = cont__68_78;
}
static void cont__68_78(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 460: ... : Error err.from_utf8
  frame->slots[9] /* temp__1 */ = create_closure(entry__68_79, 0);
  // 460: unless success: Error err.from_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* success */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__68_81;
}
static void entry__68_79(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // err: 0
  frame->slots[0] = myself->closure.frame->slots[7]; /* err */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 460: ... err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* err */;
  result_count = 1;
  myself = get__from_utf8();
  func = myself->type;
  frame->cont = cont__68_80;
}
static void cont__68_80(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 460: ... Error err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__68_81(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 461: ... out.to_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* out */;
  result_count = 1;
  myself = get__to_utf8();
  func = myself->type;
  frame->cont = cont__68_82;
}
static void cont__68_82(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 461: save sim_filename out.to_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* sim_filename */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__save();
  func = myself->type;
  frame->cont = cont__68_83;
}
static void cont__68_83(void) {
  myself = frame->slots[0] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__68_84(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 462: dec &meta_level
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* meta_level */;
  result_count = 1;
  myself = get__dec();
  func = myself->type;
  frame->cont = cont__68_85;
}
static void cont__68_85(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* meta_level */ = arguments->slots[0];
  // 463: ... meta_level > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* meta_level */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__68_86;
}
static void cont__68_86(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 463: -> meta_level > 0
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__68_1(void) {
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
  // 402: ... :
  // 403:   $meta_path truncate_from(mod_filename '/' -1)
  // 404:   $filename string(mod_filename dup(".meta" meta_level))
  // 405:   $meta_filename string(filename ".sim")
  // 406:   $meta_c_filename string(mod_filename dup(".meta" meta_level) ".c")
  // 407:   $sim_filename string(mod_filename dup(".meta" meta_level-1) ".sim")
  // 408:   $meta_info stat(meta_filename)
  // 409:   $sim_info stat(sim_filename)
  // 410:   $meta_c_info stat(meta_c_filename)
  // 411:   
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__68_2, 0);
  // 402: do_while:
  // 403:   $meta_path truncate_from(mod_filename '/' -1)
  // 404:   $filename string(mod_filename dup(".meta" meta_level))
  // 405:   $meta_filename string(filename ".sim")
  // 406:   $meta_c_filename string(mod_filename dup(".meta" meta_level) ".c")
  // 407:   $sim_filename string(mod_filename dup(".meta" meta_level-1) ".sim")
  // 408:   $meta_info stat(meta_filename)
  // 409:   $sim_info stat(sim_filename)
  // 410:   $meta_c_info stat(meta_c_filename)
  // 411:   
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__do_while();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__69_1(void) {
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
  // 476: ... : ($line)
  // 477:   unless line .has_prefix. "/// " return
  // 478:   behind &line ' '
  // 479:   trim &line
  // 480:   $command line .truncate_from. WHITESPACE
  // 481:   $argument line .behind. WHITESPACE
  // 482:   case
  // 483:     command
  // 484:     "require":
  // 485:       if
  // ...
  frame->slots[5] /* temp__1 */ = create_closure(entry__69_2, 1);
  // 476: for_each_line c_buf: ($line)
  // 477:   unless line .has_prefix. "/// " return
  // 478:   behind &line ' '
  // 479:   trim &line
  // 480:   $command line .truncate_from. WHITESPACE
  // 481:   $argument line .behind. WHITESPACE
  // 482:   case
  // 483:     command
  // 484:     "require":
  // 485:       if
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* c_buf */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each_line();
  func = myself->type;
  frame->cont = cont__69_46;
}
static void entry__69_41(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // argument: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 504: ... !libraries(argument .truncate_from. '/') true
  frame->slots[1] /* temp__1 */ = get__true();
  // 504: ... argument .truncate_from. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* argument */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__69_42;
}
static void cont__69_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 504: ... !libraries(argument .truncate_from. '/')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__libraries();
  func = myself->type;
  frame->cont = cont__69_43;
}
static void cont__69_43(void) {
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
static void entry__69_35(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // argument: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 502: !libraries(string("sim-" argument .truncate_from. '/')) true
  frame->slots[1] /* temp__1 */ = get__true();
  // 502: ... argument .truncate_from. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* argument */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__69_36;
}
static void cont__69_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 502: ... string("sim-" argument .truncate_from. '/')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__69_37;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__69_38;
}
static void cont__69_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 502: !libraries(string("sim-" argument .truncate_from. '/'))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__libraries();
  func = myself->type;
  frame->cont = cont__69_39;
}
static void cont__69_39(void) {
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
static void entry__69_29(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // argument: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 499: ... resolve_filename(argument)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* argument */;
  result_count = 1;
  myself = var._resolve_filename;
  func = myself->type;
  frame->cont = cont__69_30;
}
static void cont__69_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 499: compile_module resolve_filename(argument) argument
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[0] /* argument */;
  result_count = frame->caller_result_count;
  myself = var._compile_module;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__69_31(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // do_compile_c: 0
  // argument: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* do_compile_c */
  frame->slots[1] = myself->closure.frame->slots[0]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 501: ... do_compile_c && not(do_build_static_executable)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* do_compile_c */;
  arguments->slots[1] = func__69_32;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__69_34;
}
static void entry__69_32(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 501: ... not(do_build_static_executable)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__do_build_static_executable();
  result_count = 1;
  myself = get__not();
  func = myself->type;
  frame->cont = cont__69_33;
}
static void cont__69_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 501: ... not(do_build_static_executable)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__69_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 501: ... :
  // 502:   !libraries(string("sim-" argument .truncate_from. '/')) true
  frame->slots[3] /* temp__2 */ = create_closure(entry__69_35, 0);
  // 501: if do_compile_c && not(do_build_static_executable):
  // 502:   !libraries(string("sim-" argument .truncate_from. '/')) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__69_15(void) {
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
  // 488: ... 1
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
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 488: $req_name range(argument 3 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* argument */;
  arguments->slots[1] = number__3;
  arguments->slots[2] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__69_17;
}
static void cont__69_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* req_name */, arguments->slots[0]);
  // 490: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__69_18;
}
static void cont__69_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 490: ... until(mod_filename '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* mod_filename */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count = 1;
  myself = get__until();
  func = myself->type;
  frame->cont = cont__69_19;
}
static void cont__69_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 490: string(until(mod_filename '/' -1) req_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* req_name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__69_20;
}
static void cont__69_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 491: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__69_21;
}
static void cont__69_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__6 */ = arguments->slots[0];
  // 491: ... until(mod_name '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* mod_name */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[9] /* temp__6 */;
  result_count = 1;
  myself = get__until();
  func = myself->type;
  frame->cont = cont__69_22;
}
static void cont__69_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__5 */ = arguments->slots[0];
  // 491: string(until(mod_name '/' -1) req_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__5 */;
  arguments->slots[1] = frame->slots[3] /* req_name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__69_23;
}
static void cont__69_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__4 */ = arguments->slots[0];
  // 489: compile_module
  // 490:   string(until(mod_filename '/' -1) req_name)
  // 491:   string(until(mod_name '/' -1) req_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = var._compile_module;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__69_13(void) {
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
  // 487: ... mode == EXE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__mode();
  arguments->slots[1] = var._EXE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__69_14;
}
static void cont__69_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 487: ... :
  // 488:   $req_name range(argument 3 -1)
  // 489:   compile_module
  // 490:     string(until(mod_filename '/' -1) req_name)
  // 491:     string(until(mod_name '/' -1) req_name)
  frame->slots[4] /* temp__2 */ = create_closure(entry__69_15, 0);
  // 487: if mode == EXE:
  // 488:   $req_name range(argument 3 -1)
  // 489:   compile_module
  // 490:     string(until(mod_filename '/' -1) req_name)
  // 491:     string(until(mod_name '/' -1) req_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__69_24(void) {
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
  arguments->slots[1] = func__69_25;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__69_28;
}
static void entry__69_25(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_build_codeblocks_project;
  arguments->slots[1] = func__69_26;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__69_27;
}
static void entry__69_26(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 497: do_list_dependencies
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._do_list_dependencies;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__69_27(void) {
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
static void cont__69_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 498: :
  // 499:   compile_module resolve_filename(argument) argument
  frame->slots[3] /* temp__2 */ = create_closure(entry__69_29, 0);
  // 500: :
  // 501:   if do_compile_c && not(do_build_static_executable):
  // 502:     !libraries(string("sim-" argument .truncate_from. '/')) true
  frame->slots[4] /* temp__3 */ = create_closure(entry__69_31, 0);
  // 493: if
  // 494:   ||
  // 495:     do_build_static_executable
  // 496:     do_build_codeblocks_project
  // 497:     do_list_dependencies
  // 498:   :
  // 499:     compile_module resolve_filename(argument) argument
  // 500:   :
  // 501:     if do_compile_c && not(do_build_static_executable):
  // 502:       !libraries(string("sim-" argument .truncate_from. '/')) true
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
static void entry__69_10(void) {
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
  // 486: argument .has_prefix. "./"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* argument */;
  arguments->slots[1] = string__69_11;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__69_12;
}
static void cont__69_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 486: ... :
  // 487:   if mode == EXE:
  // 488:     $req_name range(argument 3 -1)
  // 489:     compile_module
  // 490:       string(until(mod_filename '/' -1) req_name)
  // 491:       string(until(mod_name '/' -1) req_name)
  frame->slots[5] /* temp__2 */ = create_closure(entry__69_13, 0);
  // 492: :
  // 493:   if
  // 494:     ||
  // 495:       do_build_static_executable
  // 496:       do_build_codeblocks_project
  // 497:       do_list_dependencies
  // 498:     :
  // 499:       compile_module resolve_filename(argument) argument
  // 500:     :
  // 501:       if do_compile_c && not(do_build_static_executable):
  // ...
  frame->slots[6] /* temp__3 */ = create_closure(entry__69_24, 0);
  // 485: if
  // 486:   argument .has_prefix. "./":
  // 487:     if mode == EXE:
  // 488:       $req_name range(argument 3 -1)
  // 489:       compile_module
  // 490:         string(until(mod_filename '/' -1) req_name)
  // 491:         string(until(mod_name '/' -1) req_name)
  // 492:   :
  // 493:     if
  // 494:       ||
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
static void entry__69_40(void) {
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
  // 504: ... : !libraries(argument .truncate_from. '/') true
  frame->slots[2] /* temp__1 */ = create_closure(entry__69_41, 0);
  // 504: if do_compile_c: !libraries(argument .truncate_from. '/') true
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
  // 477: ... line .has_prefix. "/// "
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  arguments->slots[1] = string__69_3;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__69_4;
}
static void cont__69_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 477: unless line .has_prefix. "/// " return
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* return */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__69_5;
}
static void cont__69_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 478: behind &line ' '
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  arguments->slots[1] = character__32;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__69_6;
}
static void cont__69_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* line */ = arguments->slots[0];
  // 479: trim &line
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__69_7;
}
static void cont__69_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* line */ = arguments->slots[0];
  // 480: $command line .truncate_from. WHITESPACE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  arguments->slots[1] = var._WHITESPACE;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__69_8;
}
static void cont__69_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* command */, arguments->slots[0]);
  // 481: $argument line .behind. WHITESPACE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  arguments->slots[1] = var._WHITESPACE;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__69_9;
}
static void cont__69_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* argument */, arguments->slots[0]);
  // 484: ... :
  // 485:   if
  // 486:     argument .has_prefix. "./":
  // 487:       if mode == EXE:
  // 488:         $req_name range(argument 3 -1)
  // 489:         compile_module
  // 490:           string(until(mod_filename '/' -1) req_name)
  // 491:           string(until(mod_name '/' -1) req_name)
  // 492:     :
  // 493:       if
  // ...
  frame->slots[7] /* temp__1 */ = create_closure(entry__69_10, 0);
  // 503: ... :
  // 504:   if do_compile_c: !libraries(argument .truncate_from. '/') true
  frame->slots[8] /* temp__2 */ = create_closure(entry__69_40, 0);
  // 482: case
  // 483:   command
  // 484:   "require":
  // 485:     if
  // 486:       argument .has_prefix. "./":
  // 487:         if mode == EXE:
  // 488:           $req_name range(argument 3 -1)
  // 489:           compile_module
  // 490:             string(until(mod_filename '/' -1) req_name)
  // 491:             string(until(mod_name '/' -1) req_name)
  // ...
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* command */;
  arguments->slots[1] = string__69_44;
  arguments->slots[2] = frame->slots[7] /* temp__1 */;
  arguments->slots[3] = string__69_45;
  arguments->slots[4] = frame->slots[8] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__69_46(void) {
  myself = frame->slots[4] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__70_1(void) {
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
  // 515: ... :
  // 516:   (
  // 517:     submodule_names # no paths; no extensions
  // 518:     do_compile_c = true
  // 519:     suffix = "" # a hyphen followed by the platform name
  // 520:   )
  // 521:   $$modification_time undefined
  // 522:   $$sim_filenames empty_list
  // 523:   for_each submodule_names: (submodule_name)
  // 524:     $meta_level meta_levels(submodule_name)
  // ...
  frame->slots[6] /* temp__1 */ = create_closure(entry__70_2, -1);
  // 515: $compile_submodule:
  // 516:   (
  // 517:     submodule_names # no paths; no extensions
  // 518:     do_compile_c = true
  // 519:     suffix = "" # a hyphen followed by the platform name
  // 520:   )
  // 521:   $$modification_time undefined
  // 522:   $$sim_filenames empty_list
  // 523:   for_each submodule_names: (submodule_name)
  // 524:     $meta_level meta_levels(submodule_name)
  // ...
  initialize_future(frame->slots[3] /* compile_submodule */, frame->slots[6] /* temp__1 */);
  // 576: lookup $mod_info mod_filename mod_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = frame->slots[1] /* mod_name */;
  result_count = 1;
  myself = var._lookup;
  func = myself->type;
  frame->cont = cont__70_80;
}
static void entry__70_2(void) {
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
  // 521: $$modification_time undefined
  ((CELL *)frame->slots[6])->contents /* modification_time */ = get__undefined();
  // 522: $$sim_filenames empty_list
  ((CELL *)frame->slots[7])->contents /* sim_filenames */ = get__empty_list();
  // 523: ... : (submodule_name)
  // 524:   $meta_level meta_levels(submodule_name)
  // 525:   $submodule_filename string(until(mod_filename '/' -1) submodule_name)
  // 526:   if meta_level > 0 && not(do_omit_meta):
  // 527:     compile_meta_module submodule_filename submodule_name meta_level
  // 528:   $sim_filename string(submodule_filename ".sim")
  // 529:   push &sim_filenames sim_filename
  // 530:   $sim_info stat(sim_filename)
  // 531:   if
  // 532:     ||
  // ...
  frame->slots[11] /* temp__1 */ = create_closure(entry__70_3, 1);
  // 523: for_each submodule_names: (submodule_name)
  // 524:   $meta_level meta_levels(submodule_name)
  // 525:   $submodule_filename string(until(mod_filename '/' -1) submodule_name)
  // 526:   if meta_level > 0 && not(do_omit_meta):
  // 527:     compile_meta_module submodule_filename submodule_name meta_level
  // 528:   $sim_filename string(submodule_filename ".sim")
  // 529:   push &sim_filenames sim_filename
  // 530:   $sim_info stat(sim_filename)
  // 531:   if
  // 532:     ||
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* submodule_names */;
  arguments->slots[1] = frame->slots[11] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__70_25;
}
static void entry__70_23(void) {
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
  // 536: !modification_time modification_time_of(sim_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* sim_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__70_24;
}
static void cont__70_24(void) {
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
  // 524: $meta_level meta_levels(submodule_name)
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
  // 525: ... 1
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
  // 525: ... until(mod_filename '/' -1)
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
  // 525: $submodule_filename string(until(mod_filename '/' -1) submodule_name)
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
  // 526: ... meta_level > 0
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
  // 526: ... meta_level > 0 && not(do_omit_meta)
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
  // 526: ... not(do_omit_meta)
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
  // 526: ... not(do_omit_meta)
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
  // 526: ... :
  // 527:   compile_meta_module submodule_filename submodule_name meta_level
  frame->slots[10] /* temp__3 */ = create_closure(entry__70_12, 0);
  // 526: if meta_level > 0 && not(do_omit_meta):
  // 527:   compile_meta_module submodule_filename submodule_name meta_level
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
  // 527: compile_meta_module submodule_filename submodule_name meta_level
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
  // 528: $sim_filename string(submodule_filename ".sim")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* submodule_filename */;
  arguments->slots[1] = string__70_14;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__70_15;
}
static void cont__70_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* sim_filename */, arguments->slots[0]);
  // 529: push &sim_filenames sim_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* sim_filenames */;
  arguments->slots[1] = frame->slots[6] /* sim_filename */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__70_16;
}
static void cont__70_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* sim_filenames */ = arguments->slots[0];
  // 530: $sim_info stat(sim_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* sim_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__70_17;
}
static void cont__70_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[7] /* sim_info */, arguments->slots[0]);
  // 533: modification_time.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* modification_time */;
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
  frame->slots[9] /* temp__2 */ = arguments->slots[0];
  // 534: modification_time_of(sim_info) > modification_time
  frame->slots[10] /* temp__3 */ = create_closure(entry__70_19, 0);
  // 532: ||
  // 533:   modification_time.is_undefined
  // 534:   modification_time_of(sim_info) > modification_time
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__2 */;
  arguments->slots[1] = frame->slots[10] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__70_22;
}
static void entry__70_19(void) {
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
  // 534: modification_time_of(sim_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* sim_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__70_20;
}
static void cont__70_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 534: modification_time_of(sim_info) > modification_time
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* modification_time */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__70_21;
}
static void cont__70_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 534: modification_time_of(sim_info) > modification_time
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__70_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 535: :
  // 536:   !modification_time modification_time_of(sim_info)
  frame->slots[11] /* temp__4 */ = create_closure(entry__70_23, 0);
  // 531: if
  // 532:   ||
  // 533:     modification_time.is_undefined
  // 534:     modification_time_of(sim_info) > modification_time
  // 535:   :
  // 536:     !modification_time modification_time_of(sim_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = frame->slots[11] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__70_25(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 537: $c_filename string(mod_filename suffix ".c")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* mod_filename */;
  arguments->slots[1] = frame->slots[2] /* suffix */;
  arguments->slots[2] = string__70_26;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__70_27;
}
static void cont__70_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[8] /* c_filename */, arguments->slots[0]);
  // 538: $c_info stat(c_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* c_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__70_28;
}
static void cont__70_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[9] /* c_info */, arguments->slots[0]);
  // 539: ... : !c_sources(c_filename) true
  frame->slots[11] /* temp__1 */ = create_closure(entry__70_29, 0);
  // 539: if do_compile_c: !c_sources(c_filename) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* do_compile_c */;
  arguments->slots[1] = frame->slots[11] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__70_31;
}
static void entry__70_29(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // c_filename: 0
  frame->slots[0] = myself->closure.frame->slots[8]; /* c_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 539: ... !c_sources(c_filename) true
  frame->slots[1] /* temp__1 */ = get__true();
  // 539: ... !c_sources(c_filename)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_filename */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = var._c_sources;
  func = myself->type;
  frame->cont = cont__70_30;
}
static void cont__70_30(void) {
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
static void cont__70_31(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 540: $$c_buf undefined
  ((CELL *)frame->slots[10])->contents /* c_buf */ = get__undefined();
  frame->slots[12] /* temp__2 */ = create_closure(entry__70_32, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_rebuild;
  arguments->slots[1] = frame->slots[12] /* temp__2 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__70_38;
}
static void entry__70_32(void) {
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
  // 544: c_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__70_33;
}
static void cont__70_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 545: modification_time > modification_time_of(c_info)
  frame->slots[4] /* temp__3 */ = create_closure(entry__70_34, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__70_37;
}
static void entry__70_34(void) {
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
  // 545: ... modification_time_of(c_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__70_35;
}
static void cont__70_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 545: modification_time > modification_time_of(c_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* modification_time */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__70_36;
}
static void cont__70_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 545: modification_time > modification_time_of(c_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__70_37(void) {
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
static void cont__70_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 546: :
  // 547:   %sim2c::module_name replace_all(mod_name '/' = "__" '.' = "__")
  // 548:   case
  // 549:     mode
  // 550:     EXE:
  // 551:       if verbose: ewriteln "build application module " module_name suffix
  // 552:     LIB:
  // 553:       if verbose: ewriteln "build library module " module_name suffix
  // 554:   collect_output $c_source: sim2c sim_filenames
  // 555:   collect_output !c_buf: create_imports c_source
  // ...
  frame->slots[13] /* temp__3 */ = create_closure(entry__70_39, 0);
  // 558: :
  // 559:   load !c_buf c_filename
  // 560:   $o_info stat(o_filename)
  // 561:   if
  // 562:     ||
  // 563:       o_info.is_undefined
  // 564:       modification_time_of(c_info) > modification_time_of(o_info)
  // 565:     :
  // 566:       if do_compile_c: compile_c c_filename o_filename
  // 567:     :
  // ...
  frame->slots[14] /* temp__4 */ = create_closure(entry__70_60, 0);
  // 541: if
  // 542:   ||
  // 543:     do_rebuild
  // 544:     c_info.is_undefined
  // 545:     modification_time > modification_time_of(c_info)
  // 546:   :
  // 547:     %sim2c::module_name replace_all(mod_name '/' = "__" '.' = "__")
  // 548:     case
  // 549:       mode
  // 550:       EXE:
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  arguments->slots[1] = frame->slots[13] /* temp__3 */;
  arguments->slots[2] = frame->slots[14] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__70_79;
}
static void entry__70_77(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // o_info: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* o_info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 573: !last_modification_time modification_time_of(o_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* o_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__70_78;
}
static void cont__70_78(void) {
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
static void entry__70_70(void) {
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
  // 566: ... compile_c c_filename o_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_filename */;
  arguments->slots[1] = frame->slots[1] /* o_filename */;
  result_count = frame->caller_result_count;
  myself = var._compile_c;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__70_69(void) {
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
  // 566: ... : compile_c c_filename o_filename
  frame->slots[3] /* temp__1 */ = create_closure(entry__70_70, 0);
  // 566: if do_compile_c: compile_c c_filename o_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* do_compile_c */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__70_71(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // o_info: 0
  frame->slots[0] = myself->closure.frame->slots[5]; /* o_info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 570: last_modification_time.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__last_modification_time();
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__70_72;
}
static void cont__70_72(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 571: modification_time_of(o_info) > last_modification_time
  frame->slots[3] /* temp__3 */ = create_closure(entry__70_73, 0);
  // 569: ||
  // 570:   last_modification_time.is_undefined
  // 571:   modification_time_of(o_info) > last_modification_time
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__70_76;
}
static void entry__70_73(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // o_info: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* o_info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 571: modification_time_of(o_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* o_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__70_74;
}
static void cont__70_74(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 571: modification_time_of(o_info) > last_modification_time
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__last_modification_time();
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__70_75;
}
static void cont__70_75(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 571: modification_time_of(o_info) > last_modification_time
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__70_76(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 572: :
  // 573:   !last_modification_time modification_time_of(o_info)
  frame->slots[4] /* temp__4 */ = create_closure(entry__70_77, 0);
  // 568: if
  // 569:   ||
  // 570:     last_modification_time.is_undefined
  // 571:     modification_time_of(o_info) > last_modification_time
  // 572:   :
  // 573:     !last_modification_time modification_time_of(o_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__70_39(void) {
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
  // 547: ... '/' = "__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = string__70_40;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__70_41;
}
static void cont__70_41(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 547: ... '.' = "__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__46;
  arguments->slots[1] = string__70_42;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__70_43;
}
static void cont__70_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__2 */ = arguments->slots[0];
  // 547: %sim2c::module_name replace_all(mod_name '/' = "__" '.' = "__")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* mod_name */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  arguments->slots[2] = frame->slots[10] /* temp__2 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__70_44;
}
static void cont__70_44(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(get__sim2c__module_name(), arguments->slots[0]);
  // 550: ... :
  // 551:   if verbose: ewriteln "build application module " module_name suffix
  frame->slots[9] /* temp__1 */ = create_closure(entry__70_45, 0);
  // 552: ... :
  // 553:   if verbose: ewriteln "build library module " module_name suffix
  frame->slots[10] /* temp__2 */ = create_closure(entry__70_48, 0);
  // 548: case
  // 549:   mode
  // 550:   EXE:
  // 551:     if verbose: ewriteln "build application module " module_name suffix
  // 552:   LIB:
  // 553:     if verbose: ewriteln "build library module " module_name suffix
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = get__mode();
  arguments->slots[1] = var._EXE;
  arguments->slots[2] = frame->slots[9] /* temp__1 */;
  arguments->slots[3] = var._LIB;
  arguments->slots[4] = frame->slots[10] /* temp__2 */;
  result_count = 0;
  myself = get__case();
  func = myself->type;
  frame->cont = cont__70_51;
}
static void entry__70_49(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // suffix: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* suffix */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 553: ... ewriteln "build library module " module_name suffix
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__70_50;
  arguments->slots[1] = get__module_name();
  arguments->slots[2] = frame->slots[0] /* suffix */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__70_46(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // suffix: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* suffix */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 551: ... ewriteln "build application module " module_name suffix
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__70_47;
  arguments->slots[1] = get__module_name();
  arguments->slots[2] = frame->slots[0] /* suffix */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__70_45(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // suffix: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* suffix */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 551: ... : ewriteln "build application module " module_name suffix
  frame->slots[1] /* temp__1 */ = create_closure(entry__70_46, 0);
  // 551: if verbose: ewriteln "build application module " module_name suffix
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__70_48(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // suffix: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* suffix */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 553: ... : ewriteln "build library module " module_name suffix
  frame->slots[1] /* temp__1 */ = create_closure(entry__70_49, 0);
  // 553: if verbose: ewriteln "build library module " module_name suffix
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__70_51(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 554: ... : sim2c sim_filenames
  frame->slots[9] /* temp__1 */ = create_closure(entry__70_52, 0);
  // 554: collect_output $c_source: sim2c sim_filenames
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__70_53;
}
static void entry__70_52(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // sim_filenames: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* sim_filenames */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 554: ... sim2c sim_filenames
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* sim_filenames */;
  result_count = frame->caller_result_count;
  myself = get__sim2c();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__70_53(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[8] /* c_source */, arguments->slots[0]);
  // 555: ... : create_imports c_source
  frame->slots[9] /* temp__1 */ = create_closure(entry__70_54, 0);
  // 555: collect_output !c_buf: create_imports c_source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__70_55;
}
static void entry__70_54(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // c_source: 0
  frame->slots[0] = myself->closure.frame->slots[8]; /* c_source */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 555: ... create_imports c_source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_source */;
  result_count = frame->caller_result_count;
  myself = var._create_imports;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__70_55(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* c_buf */ = arguments->slots[0];
  // 556: ... c_buf.to_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* c_buf */;
  result_count = 1;
  myself = get__to_utf8();
  func = myself->type;
  frame->cont = cont__70_56;
}
static void cont__70_56(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 556: save c_filename c_buf.to_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* c_filename */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 0;
  myself = get__save();
  func = myself->type;
  frame->cont = cont__70_57;
}
static void cont__70_57(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 557: ... : compile_c c_filename o_filename
  frame->slots[9] /* temp__1 */ = create_closure(entry__70_58, 0);
  // 557: if do_compile_c: compile_c c_filename o_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* do_compile_c */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__70_59;
}
static void entry__70_58(void) {
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
static void cont__70_59(void) {
  myself = frame->slots[0] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__70_60(void) {
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
  // 559: load !c_buf c_filename
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* c_filename */;
  result_count = 1;
  myself = get__load();
  func = myself->type;
  frame->cont = cont__70_61;
}
static void cont__70_61(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* c_buf */ = arguments->slots[0];
  // 560: $o_info stat(o_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* o_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__70_62;
}
static void cont__70_62(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* o_info */, arguments->slots[0]);
  // 563: o_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* o_info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__70_63;
}
static void cont__70_63(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 564: modification_time_of(c_info) > modification_time_of(o_info)
  frame->slots[8] /* temp__3 */ = create_closure(entry__70_64, 0);
  // 562: ||
  // 563:   o_info.is_undefined
  // 564:   modification_time_of(c_info) > modification_time_of(o_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  arguments->slots[1] = frame->slots[8] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__70_68;
}
static void entry__70_64(void) {
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
  // 564: ... modification_time_of(o_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* o_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__70_65;
}
static void cont__70_65(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 564: modification_time_of(c_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* c_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__70_66;
}
static void cont__70_66(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 564: modification_time_of(c_info) > modification_time_of(o_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__70_67;
}
static void cont__70_67(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 564: modification_time_of(c_info) > modification_time_of(o_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__70_68(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 565: :
  // 566:   if do_compile_c: compile_c c_filename o_filename
  frame->slots[9] /* temp__4 */ = create_closure(entry__70_69, 0);
  // 567: :
  // 568:   if
  // 569:     ||
  // 570:       last_modification_time.is_undefined
  // 571:       modification_time_of(o_info) > last_modification_time
  // 572:     :
  // 573:       !last_modification_time modification_time_of(o_info)
  frame->slots[10] /* temp__5 */ = create_closure(entry__70_71, 0);
  // 561: if
  // 562:   ||
  // 563:     o_info.is_undefined
  // 564:     modification_time_of(c_info) > modification_time_of(o_info)
  // 565:   :
  // 566:     if do_compile_c: compile_c c_filename o_filename
  // 567:   :
  // 568:     if
  // 569:       ||
  // 570:         last_modification_time.is_undefined
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
static void cont__70_79(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 574: build_dependencies mod_filename mod_name c_buf do_compile_c
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
static void cont__70_80(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* mod_info */, arguments->slots[0]);
  // 577: ... mod_info.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* mod_info */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__70_81;
}
static void cont__70_81(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 577: ... :
  // 578:   Error "
  // 579:     No source file(s) for module "@(mod_name)" found!@
  frame->slots[7] /* temp__2 */ = create_closure(entry__70_82, 0);
  // 577: unless mod_info.is_defined:
  // 578:   Error "
  // 579:     No source file(s) for module "@(mod_name)" found!@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__70_86;
}
static void entry__70_82(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // mod_name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* mod_name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 578: ... "
  // 579:   No source file(s) for module "@(mod_name)" found!@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__70_83;
  arguments->slots[1] = frame->slots[0] /* mod_name */;
  arguments->slots[2] = string__70_84;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__70_85;
}
static void cont__70_85(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 578: Error "
  // 579:   No source file(s) for module "@(mod_name)" found!@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__70_86(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 580: ... mode == LIB
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__mode();
  arguments->slots[1] = var._LIB;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__70_87;
}
static void cont__70_87(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 580: ... if(mode == LIB (-> ".lib.o") -> ".o")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  arguments->slots[1] = func__70_88;
  arguments->slots[2] = func__70_90;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__70_92;
}
static void entry__70_88(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 580: ... -> ".lib.o"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__70_89;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__70_90(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 580: ... -> ".o"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__70_91;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__70_92(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 580: $o_filename append(mod_filename if(mode == LIB (-> ".lib.o") -> ".o"))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__70_93;
}
static void cont__70_93(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* o_filename */, arguments->slots[0]);
  // 581: ... objects(o_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* o_filename */;
  result_count = 1;
  myself = get__objects();
  func = myself->type;
  frame->cont = cont__70_94;
}
static void cont__70_94(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 581: if objects(o_filename) return
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* return */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__70_95;
}
static void cont__70_95(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 582: !objects(o_filename) true
  frame->slots[6] /* temp__1 */ = get__true();
  // 582: !objects(o_filename)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* o_filename */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = get__objects();
  func = myself->type;
  frame->cont = cont__70_96;
}
static void cont__70_96(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__objects(arguments->slots[0]);
  // 584: mod_info.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* mod_info */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__70_97;
}
static void cont__70_97(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 584: ... :
  // 585:   compile_submodule list(truncate_until(mod_name '/' -1))
  // 586:   if do_list_dependencies: push &dependencies string(mod_filename ".c")
  frame->slots[7] /* temp__2 */ = create_closure(entry__70_98, 0);
  // 587: :
  // 588:   do:
  // 589:     $$best_platform undefined
  // 590:     $$best_priority 999
  // 591:     for_each mod_info: (platform _filenames)
  // 592:       $priority platform_priority(platform)
  // 593:       if priority.is_defined && priority < best_priority:
  // 594:         !best_platform platform
  // 595:         !best_priority priority
  // 596:     for_each mod_info: (platform filenames)
  // ...
  frame->slots[8] /* temp__3 */ = create_closure(entry__70_107, 0);
  // 583: if
  // 584:   mod_info.is_empty:
  // 585:     compile_submodule list(truncate_until(mod_name '/' -1))
  // 586:     if do_list_dependencies: push &dependencies string(mod_filename ".c")
  // 587:   :
  // 588:     do:
  // 589:       $$best_platform undefined
  // 590:       $$best_priority 999
  // 591:       for_each mod_info: (platform _filenames)
  // 592:         $priority platform_priority(platform)
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  arguments->slots[2] = frame->slots[8] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__70_151;
}
static void entry__70_139(void) {
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
  // 616: $$dependency string(mod_filename "-" platform ".c")
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* mod_filename */;
  arguments->slots[1] = string__70_140;
  arguments->slots[2] = frame->slots[0] /* platform */;
  arguments->slots[3] = string__70_141;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__70_142;
}
static void cont__70_142(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* dependency */ = arguments->slots[0];
  // 617: $platforms used_by(platform)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* platform */;
  result_count = 1;
  myself = ((CELL *)frame->slots[3])->contents /* used_by */;
  func = myself->type;
  frame->cont = cont__70_143;
}
static void cont__70_143(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* platforms */, arguments->slots[0]);
  // 618: ... platforms.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* platforms */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__70_144;
}
static void cont__70_144(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 618: ... :
  // 619:   for_each platforms: (plat) write_to &dependency " #" plat
  frame->slots[7] /* temp__2 */ = create_closure(entry__70_145, 0);
  // 618: if platforms.is_defined:
  // 619:   for_each platforms: (plat) write_to &dependency " #" plat
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__70_149;
}
static void entry__70_146(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // plat: 0
  // dependency: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* dependency */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 619: ... write_to &dependency " #" plat
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* dependency */;
  arguments->slots[1] = string__70_147;
  arguments->slots[2] = frame->slots[0] /* plat */;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__70_148;
}
static void cont__70_148(void) {
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
static void entry__70_145(void) {
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
  // 619: ... : (plat) write_to &dependency " #" plat
  frame->slots[2] /* temp__1 */ = create_closure(entry__70_146, 1);
  // 619: for_each platforms: (plat) write_to &dependency " #" plat
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* platforms */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__70_149(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 620: push &dependencies dependency
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._dependencies;
  arguments->slots[1] = ((CELL *)frame->slots[4])->contents /* dependency */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__70_150;
}
static void cont__70_150(void) {
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
static void entry__70_122(void) {
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
  // 602: $$used_by empty_table
  ((CELL *)frame->slots[2])->contents /* used_by */ = get__empty_table();
  // 603: ... : (supported_platform _parent_platform)
  // 604:   $$best_platform undefined
  // 605:   $$best_priority 999
  // 606:   for_each mod_info: (platform _filenames)
  // 607:     $priority platform_specific_priority(supported_platform platform)
  // 608:     if priority.is_defined && priority < best_priority:
  // 609:       !best_platform platform
  // 610:       !best_priority priority
  // 611:   if best_platform.is_defined:
  // 612:     $$ub default_value(used_by(best_platform) empty_list)
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__70_123, 2);
  // 603: for_each supported_platforms: (supported_platform _parent_platform)
  // 604:   $$best_platform undefined
  // 605:   $$best_priority 999
  // 606:   for_each mod_info: (platform _filenames)
  // 607:     $priority platform_specific_priority(supported_platform platform)
  // 608:     if priority.is_defined && priority < best_priority:
  // 609:       !best_platform platform
  // 610:       !best_priority priority
  // 611:   if best_platform.is_defined:
  // 612:     $$ub default_value(used_by(best_platform) empty_list)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._supported_platforms;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__70_138;
}
static void entry__70_133(void) {
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
  // 612: ... used_by(best_platform)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* best_platform */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* used_by */;
  func = myself->type;
  frame->cont = cont__70_134;
}
static void cont__70_134(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 612: $$ub default_value(used_by(best_platform) empty_list)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = get__empty_list();
  result_count = 1;
  myself = get__default_value();
  func = myself->type;
  frame->cont = cont__70_135;
}
static void cont__70_135(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* ub */ = arguments->slots[0];
  // 613: push &ub supported_platform
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* ub */;
  arguments->slots[1] = frame->slots[2] /* supported_platform */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__70_136;
}
static void cont__70_136(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* ub */ = arguments->slots[0];
  // 614: !used_by(best_platform) ub
  frame->slots[4] /* temp__1 */ = ((CELL *)frame->slots[3])->contents /* ub */;
  // 614: !used_by(best_platform)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* best_platform */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* used_by */;
  func = myself->type;
  frame->cont = cont__70_137;
}
static void cont__70_137(void) {
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
static void entry__70_123(void) {
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
  // 604: $$best_platform undefined
  ((CELL *)frame->slots[4])->contents /* best_platform */ = get__undefined();
  // 605: $$best_priority 999
  ((CELL *)frame->slots[5])->contents /* best_priority */ = number__999;
  // 606: ... : (platform _filenames)
  // 607:   $priority platform_specific_priority(supported_platform platform)
  // 608:   if priority.is_defined && priority < best_priority:
  // 609:     !best_platform platform
  // 610:     !best_priority priority
  frame->slots[6] /* temp__1 */ = create_closure(entry__70_124, 2);
  // 606: for_each mod_info: (platform _filenames)
  // 607:   $priority platform_specific_priority(supported_platform platform)
  // 608:   if priority.is_defined && priority < best_priority:
  // 609:     !best_platform platform
  // 610:     !best_priority priority
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* mod_info */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__70_131;
}
static void entry__70_130(void) {
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
  // 609: !best_platform platform
  ((CELL *)frame->slots[0])->contents /* best_platform */ = frame->slots[1] /* platform */;
  // 610: !best_priority priority
  ((CELL *)frame->slots[2])->contents /* best_priority */ = frame->slots[3] /* priority */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__70_124(void) {
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
  // 607: $priority platform_specific_priority(supported_platform platform)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* supported_platform */;
  arguments->slots[1] = frame->slots[0] /* platform */;
  result_count = 1;
  myself = var._platform_specific_priority;
  func = myself->type;
  frame->cont = cont__70_125;
}
static void cont__70_125(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* priority */, arguments->slots[0]);
  // 608: ... priority.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* priority */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__70_126;
}
static void cont__70_126(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 608: ... priority < best_priority
  frame->slots[8] /* temp__3 */ = create_closure(entry__70_127, 0);
  // 608: ... priority.is_defined && priority < best_priority
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  arguments->slots[1] = frame->slots[8] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__70_129;
}
static void entry__70_127(void) {
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
  // 608: ... priority < best_priority
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* priority */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* best_priority */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__70_128;
}
static void cont__70_128(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 608: ... priority < best_priority
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__70_129(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 608: ... :
  // 609:   !best_platform platform
  // 610:   !best_priority priority
  frame->slots[9] /* temp__4 */ = create_closure(entry__70_130, 0);
  // 608: if priority.is_defined && priority < best_priority:
  // 609:   !best_platform platform
  // 610:   !best_priority priority
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__70_131(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 611: ... best_platform.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* best_platform */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__70_132;
}
static void cont__70_132(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 611: ... :
  // 612:   $$ub default_value(used_by(best_platform) empty_list)
  // 613:   push &ub supported_platform
  // 614:   !used_by(best_platform) ub
  frame->slots[7] /* temp__2 */ = create_closure(entry__70_133, 0);
  // 611: if best_platform.is_defined:
  // 612:   $$ub default_value(used_by(best_platform) empty_list)
  // 613:   push &ub supported_platform
  // 614:   !used_by(best_platform) ub
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__70_138(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 615: ... : (platform _filenames)
  // 616:   $$dependency string(mod_filename "-" platform ".c")
  // 617:   $platforms used_by(platform)
  // 618:   if platforms.is_defined:
  // 619:     for_each platforms: (plat) write_to &dependency " #" plat
  // 620:   push &dependencies dependency
  frame->slots[3] /* temp__1 */ = create_closure(entry__70_139, 2);
  // 615: for_each mod_info: (platform _filenames)
  // 616:   $$dependency string(mod_filename "-" platform ".c")
  // 617:   $platforms used_by(platform)
  // 618:   if platforms.is_defined:
  // 619:     for_each platforms: (plat) write_to &dependency " #" plat
  // 620:   push &dependencies dependency
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_info */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__70_103(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // mod_filename: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* mod_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 586: ... string(mod_filename ".c")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = string__70_104;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__70_105;
}
static void cont__70_105(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 586: ... push &dependencies string(mod_filename ".c")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._dependencies;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__70_106;
}
static void cont__70_106(void) {
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
static void entry__70_98(void) {
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
  // 585: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__70_99;
}
static void cont__70_99(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 585: ... truncate_until(mod_name '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* mod_name */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__70_100;
}
static void cont__70_100(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 585: ... list(truncate_until(mod_name '/' -1))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__70_101;
}
static void cont__70_101(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 585: compile_submodule list(truncate_until(mod_name '/' -1))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = frame->slots[0] /* compile_submodule */;
  func = myself->type;
  frame->cont = cont__70_102;
}
static void cont__70_102(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 586: ... : push &dependencies string(mod_filename ".c")
  frame->slots[3] /* temp__1 */ = create_closure(entry__70_103, 0);
  // 586: if do_list_dependencies: push &dependencies string(mod_filename ".c")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_list_dependencies;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__70_107(void) {
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
  // 588: ... :
  // 589:   $$best_platform undefined
  // 590:   $$best_priority 999
  // 591:   for_each mod_info: (platform _filenames)
  // 592:     $priority platform_priority(platform)
  // 593:     if priority.is_defined && priority < best_priority:
  // 594:       !best_platform platform
  // 595:       !best_priority priority
  // 596:   for_each mod_info: (platform filenames)
  // 597:     compile_submodule
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__70_108, 0);
  // 588: do:
  // 589:   $$best_platform undefined
  // 590:   $$best_priority 999
  // 591:   for_each mod_info: (platform _filenames)
  // 592:     $priority platform_priority(platform)
  // 593:     if priority.is_defined && priority < best_priority:
  // 594:       !best_platform platform
  // 595:       !best_priority priority
  // 596:   for_each mod_info: (platform filenames)
  // 597:     compile_submodule
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__70_121;
}
static void entry__70_117(void) {
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
  // 599: platform == best_platform
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* platform */;
  arguments->slots[1] = ((CELL *)frame->slots[3])->contents /* best_platform */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__70_118;
}
static void cont__70_118(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 600: string("-" platform)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__70_119;
  arguments->slots[1] = frame->slots[0] /* platform */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__70_120;
}
static void cont__70_120(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 597: compile_submodule
  // 598:   filenames
  // 599:   platform == best_platform
  // 600:   string("-" platform)
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
static void entry__70_108(void) {
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
  // 589: $$best_platform undefined
  ((CELL *)frame->slots[2])->contents /* best_platform */ = get__undefined();
  // 590: $$best_priority 999
  ((CELL *)frame->slots[3])->contents /* best_priority */ = number__999;
  // 591: ... : (platform _filenames)
  // 592:   $priority platform_priority(platform)
  // 593:   if priority.is_defined && priority < best_priority:
  // 594:     !best_platform platform
  // 595:     !best_priority priority
  frame->slots[4] /* temp__1 */ = create_closure(entry__70_109, 2);
  // 591: for_each mod_info: (platform _filenames)
  // 592:   $priority platform_priority(platform)
  // 593:   if priority.is_defined && priority < best_priority:
  // 594:     !best_platform platform
  // 595:     !best_priority priority
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_info */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__70_116;
}
static void entry__70_115(void) {
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
  // 594: !best_platform platform
  ((CELL *)frame->slots[0])->contents /* best_platform */ = frame->slots[1] /* platform */;
  // 595: !best_priority priority
  ((CELL *)frame->slots[2])->contents /* best_priority */ = frame->slots[3] /* priority */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__70_109(void) {
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
  // 592: $priority platform_priority(platform)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* platform */;
  result_count = 1;
  myself = var._platform_priority;
  func = myself->type;
  frame->cont = cont__70_110;
}
static void cont__70_110(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* priority */, arguments->slots[0]);
  // 593: ... priority.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* priority */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__70_111;
}
static void cont__70_111(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 593: ... priority < best_priority
  frame->slots[7] /* temp__3 */ = create_closure(entry__70_112, 0);
  // 593: ... priority.is_defined && priority < best_priority
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__70_114;
}
static void entry__70_112(void) {
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
  // 593: ... priority < best_priority
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* priority */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* best_priority */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__70_113;
}
static void cont__70_113(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 593: ... priority < best_priority
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__70_114(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 593: ... :
  // 594:   !best_platform platform
  // 595:   !best_priority priority
  frame->slots[8] /* temp__4 */ = create_closure(entry__70_115, 0);
  // 593: if priority.is_defined && priority < best_priority:
  // 594:   !best_platform platform
  // 595:   !best_priority priority
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__70_116(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 596: ... : (platform filenames)
  // 597:   compile_submodule
  // 598:     filenames
  // 599:     platform == best_platform
  // 600:     string("-" platform)
  frame->slots[4] /* temp__1 */ = create_closure(entry__70_117, 2);
  // 596: for_each mod_info: (platform filenames)
  // 597:   compile_submodule
  // 598:     filenames
  // 599:     platform == best_platform
  // 600:     string("-" platform)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_info */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__70_121(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 601: ... :
  // 602:   $$used_by empty_table
  // 603:   for_each supported_platforms: (supported_platform _parent_platform)
  // 604:     $$best_platform undefined
  // 605:     $$best_priority 999
  // 606:     for_each mod_info: (platform _filenames)
  // 607:       $priority platform_specific_priority(supported_platform platform)
  // 608:       if priority.is_defined && priority < best_priority:
  // 609:         !best_platform platform
  // 610:         !best_priority priority
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__70_122, 0);
  // 601: if do_list_dependencies:
  // 602:   $$used_by empty_table
  // 603:   for_each supported_platforms: (supported_platform _parent_platform)
  // 604:     $$best_platform undefined
  // 605:     $$best_priority 999
  // 606:     for_each mod_info: (platform _filenames)
  // 607:       $priority platform_specific_priority(supported_platform platform)
  // 608:       if priority.is_defined && priority < best_priority:
  // 609:         !best_platform platform
  // 610:         !best_priority priority
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
static void cont__70_151(void) {
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
  // 631: ... string(path '/' name)
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
  // 631: ... string(mod_path '/' name)
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
  // 631: compile_module string(path '/' name) string(mod_path '/' name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = var._compile_module;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__71_1(void) {
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
  // 627: ... string(mod_path '/')
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
  // 627: add_module_infos $directories $modules path string(mod_path '/')
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
  // 627: ... directories
  initialize_future(frame->slots[2] /* directories */, frame->slots[5] /* temp__2 */);
  // 627: ... modules
  initialize_future(frame->slots[3] /* modules */, frame->slots[6] /* temp__3 */);
  // 628: ... : (name)
  // 629:   compile_modules string(path '/' name) string(mod_path '/' name)
  frame->slots[4] /* temp__1 */ = create_closure(entry__71_4, 1);
  // 628: for_each directories: (name)
  // 629:   compile_modules string(path '/' name) string(mod_path '/' name)
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
  // 629: ... string(path '/' name)
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
  // 629: ... string(mod_path '/' name)
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
  // 629: compile_modules string(path '/' name) string(mod_path '/' name)
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
  // 630: ... : (name)
  // 631:   compile_module string(path '/' name) string(mod_path '/' name)
  frame->slots[4] /* temp__1 */ = create_closure(entry__71_8, 1);
  // 630: for_each modules: (name)
  // 631:   compile_module string(path '/' name) string(mod_path '/' name)
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
  // 639: $path environment("LD_LIBRARY_PATH")
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
  // 640: ... path.is_defined
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
  // 640: ... : ewriteln "LD_LIBRARY_PATH=@(path)"
  frame->slots[2] /* temp__2 */ = create_closure(entry__73_6, 0);
  // 640: if path.is_defined: ewriteln "LD_LIBRARY_PATH=@(path)"
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
  // 640: ... "LD_LIBRARY_PATH=@(path)"
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
  // 640: ... ewriteln "LD_LIBRARY_PATH=@(path)"
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
  // 641: ... serialize(objects)
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
  // 641: ewriteln "included object files: " serialize(objects)
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
  // 642: ... serialize(libraries)
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
  // 642: ewriteln "needed libraries: " serialize(libraries)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__73_14;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__73_1(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 638: if do_show_debug_infos:
  // 639:   $path environment("LD_LIBRARY_PATH")
  // 640:   if path.is_defined: ewriteln "LD_LIBRARY_PATH=@(path)"
  // 641:   ewriteln "included object files: " serialize(objects)
  // 642:   ewriteln "needed libraries: " serialize(libraries)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_show_debug_infos();
  arguments->slots[1] = func__73_2;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__74_1(void) {
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
  // 645: show_file_list
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
  // 646: $$library_paths empty_list
  ((CELL *)frame->slots[0])->contents /* library_paths */ = get__empty_list();
  // 647: $$object_files empty_list
  ((CELL *)frame->slots[1])->contents /* object_files */ = get__empty_list();
  // 648: $$library_files empty_list
  ((CELL *)frame->slots[2])->contents /* library_files */ = get__empty_list();
  // 649: $paths environment("LD_LIBRARY_PATH")
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
  initialize_future(frame->slots[3] /* paths */, arguments->slots[0]);
  // 650: ... paths.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* paths */;
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
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 650: ... :
  // 651:   for_each paths .split. ':': (path) push &library_paths "-L@(path)"
  frame->slots[5] /* temp__2 */ = create_closure(entry__74_6, 0);
  // 650: if paths.is_defined:
  // 651:   for_each paths .split. ':': (path) push &library_paths "-L@(path)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__74_12;
}
static void entry__74_8(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // path: 0
  // library_paths: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* library_paths */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 651: ... "-L@(path)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__74_9;
  arguments->slots[1] = frame->slots[0] /* path */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__74_10;
}
static void cont__74_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 651: ... push &library_paths "-L@(path)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* library_paths */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__74_11;
}
static void cont__74_11(void) {
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
static void entry__74_6(void) {
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
  // 651: ... paths .split. ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* paths */;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__split();
  func = myself->type;
  frame->cont = cont__74_7;
}
static void cont__74_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 651: ... : (path) push &library_paths "-L@(path)"
  frame->slots[3] /* temp__2 */ = create_closure(entry__74_8, 1);
  // 651: for_each paths .split. ':': (path) push &library_paths "-L@(path)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__74_12(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 652: ... : ewriteln "library paths: " serialize(library_paths)
  frame->slots[4] /* temp__1 */ = create_closure(entry__74_13, 0);
  // 652: if do_show_debug_infos: ewriteln "library paths: " serialize(library_paths)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_show_debug_infos();
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__74_16;
}
static void entry__74_13(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // library_paths: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* library_paths */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 652: ... serialize(library_paths)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* library_paths */;
  result_count = 1;
  myself = get__serialize();
  func = myself->type;
  frame->cont = cont__74_14;
}
static void cont__74_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 652: ... ewriteln "library paths: " serialize(library_paths)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__74_15;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__74_16(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 653: ... : (object) push &object_files object
  frame->slots[4] /* temp__1 */ = create_closure(entry__74_17, 1);
  // 653: for_each objects: (object) push &object_files object
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__objects();
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__74_19;
}
static void entry__74_17(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // object: 0
  // object_files: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* object_files */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 653: ... push &object_files object
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* object_files */;
  arguments->slots[1] = frame->slots[0] /* object */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__74_18;
}
static void cont__74_18(void) {
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
static void cont__74_19(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 654: ... : (library)
  // 655:   push
  // 656:     &library_files
  // 657:     if
  // 658:       library .has_prefix. "sim-"
  // 659:       ->
  // 660:         if
  // 661:           current_platform == "linux"
  // 662:           -> "-l:lib@(library).so.@(MAJOR)"
  // 663:           -> "-l@(library)-@(MAJOR)"
  // ...
  frame->slots[4] /* temp__1 */ = create_closure(entry__74_20, 1);
  // 654: for_each libraries: (library)
  // 655:   push
  // 656:     &library_files
  // 657:     if
  // 658:       library .has_prefix. "sim-"
  // 659:       ->
  // 660:         if
  // 661:           current_platform == "linux"
  // 662:           -> "-l:lib@(library).so.@(MAJOR)"
  // 663:           -> "-l@(library)-@(MAJOR)"
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__libraries();
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__74_49;
}
static void entry__74_20(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // library: 0
  // library_files: 1
  frame->slots[1] = myself->closure.frame->slots[2]; /* library_files */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 658: library .has_prefix. "sim-"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* library */;
  arguments->slots[1] = string__74_21;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__74_22;
}
static void cont__74_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 659: ->
  // 660:   if
  // 661:     current_platform == "linux"
  // 662:     -> "-l:lib@(library).so.@(MAJOR)"
  // 663:     -> "-l@(library)-@(MAJOR)"
  frame->slots[4] /* temp__3 */ = create_closure(entry__74_23, 0);
  // 664: ->
  // 665:   if
  // 666:     library .contains. '.'
  // 667:     -> "-l:lib@(library .before. '.').so.@(library .behind. '.')"
  // 668:       # Linux only
  // 669:     -> "-l@(library)"
  frame->slots[5] /* temp__4 */ = create_closure(entry__74_35, 0);
  // 657: if
  // 658:   library .has_prefix. "sim-"
  // 659:   ->
  // 660:     if
  // 661:       current_platform == "linux"
  // 662:       -> "-l:lib@(library).so.@(MAJOR)"
  // 663:       -> "-l@(library)-@(MAJOR)"
  // 664:   ->
  // 665:     if
  // 666:       library .contains. '.'
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  arguments->slots[2] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__74_47;
}
static void entry__74_23(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // library: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* library */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 661: current_platform == "linux"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__current_platform();
  arguments->slots[1] = string__74_24;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__74_25;
}
static void cont__74_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 662: -> "-l:lib@(library).so.@(MAJOR)"
  frame->slots[3] /* temp__3 */ = create_closure(entry__74_26, 0);
  // 663: -> "-l@(library)-@(MAJOR)"
  frame->slots[4] /* temp__4 */ = create_closure(entry__74_30, 0);
  // 660: if
  // 661:   current_platform == "linux"
  // 662:   -> "-l:lib@(library).so.@(MAJOR)"
  // 663:   -> "-l@(library)-@(MAJOR)"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  arguments->slots[2] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__74_34;
}
static void entry__74_26(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // library: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* library */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 662: ... "-l:lib@(library).so.@(MAJOR)"
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__74_27;
  arguments->slots[1] = frame->slots[0] /* library */;
  arguments->slots[2] = string__74_28;
  arguments->slots[3] = var._MAJOR;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__74_29;
}
static void cont__74_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 662: -> "-l:lib@(library).so.@(MAJOR)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__74_30(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // library: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* library */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 663: ... "-l@(library)-@(MAJOR)"
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__74_31;
  arguments->slots[1] = frame->slots[0] /* library */;
  arguments->slots[2] = string__74_32;
  arguments->slots[3] = var._MAJOR;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__74_33;
}
static void cont__74_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 663: -> "-l@(library)-@(MAJOR)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__74_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 659: ->
  // 660:   if
  // 661:     current_platform == "linux"
  // 662:     -> "-l:lib@(library).so.@(MAJOR)"
  // 663:     -> "-l@(library)-@(MAJOR)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__74_35(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // library: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* library */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 666: library .contains. '.'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* library */;
  arguments->slots[1] = character__46;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__74_36;
}
static void cont__74_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 667: -> "-l:lib@(library .before. '.').so.@(library .behind. '.')"
  // 668:   # Linux only
  frame->slots[3] /* temp__3 */ = create_closure(entry__74_37, 0);
  // 669: -> "-l@(library)"
  frame->slots[4] /* temp__4 */ = create_closure(entry__74_43, 0);
  // 665: if
  // 666:   library .contains. '.'
  // 667:   -> "-l:lib@(library .before. '.').so.@(library .behind. '.')"
  // 668:     # Linux only
  // 669:   -> "-l@(library)"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  arguments->slots[2] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__74_46;
}
static void entry__74_37(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // library: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* library */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 667: ... library .before. '.'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* library */;
  arguments->slots[1] = character__46;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__74_38;
}
static void cont__74_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 667: ... library .behind. '.'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* library */;
  arguments->slots[1] = character__46;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__74_39;
}
static void cont__74_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 667: ... "-l:lib@(library .before. '.').so.@(library .behind. '.')"
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__74_40;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  arguments->slots[2] = string__74_41;
  arguments->slots[3] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__74_42;
}
static void cont__74_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 667: -> "-l:lib@(library .before. '.').so.@(library .behind. '.')"
  // 668:   # Linux only
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__74_43(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // library: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* library */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 669: ... "-l@(library)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__74_44;
  arguments->slots[1] = frame->slots[0] /* library */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__74_45;
}
static void cont__74_45(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 669: -> "-l@(library)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__74_46(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 664: ->
  // 665:   if
  // 666:     library .contains. '.'
  // 667:     -> "-l:lib@(library .before. '.').so.@(library .behind. '.')"
  // 668:       # Linux only
  // 669:     -> "-l@(library)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__74_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 655: push
  // 656:   &library_files
  // 657:   if
  // 658:     library .has_prefix. "sim-"
  // 659:     ->
  // 660:       if
  // 661:         current_platform == "linux"
  // 662:         -> "-l:lib@(library).so.@(MAJOR)"
  // 663:         -> "-l@(library)-@(MAJOR)"
  // 664:     ->
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* library_files */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__74_48;
}
static void cont__74_48(void) {
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
static void cont__74_49(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 670: ... append(object_files library_files)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* object_files */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* library_files */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__74_50;
}
static void cont__74_50(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 670: append library_paths append(object_files library_files)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* library_paths */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__append();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__75_75(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 713: ... write_timing_info "collecting imports"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__75_76;
  result_count = frame->caller_result_count;
  myself = get__write_timing_info();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__75_1(void) {
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
  // 675: ... : (buf)
  // 676:   $$s undefined
  // 677:   for_each buf: (idx chr)
  // 678:     if
  // 679:       s.is_defined:
  // 680:         unless chr.is_a_letter || chr == '_' || chr.is_a_digit:
  // 681:           $symbol range(buf s idx-1)
  // 682:           !s undefined
  // 683:           unless already_checked(symbol):
  // 684:             !already_checked(symbol) true
  // ...
  frame->slots[5] /* temp__1 */ = create_closure(entry__75_2, 1);
  // 675: $collect_declarations: (buf)
  // 676:   $$s undefined
  // 677:   for_each buf: (idx chr)
  // 678:     if
  // 679:       s.is_defined:
  // 680:         unless chr.is_a_letter || chr == '_' || chr.is_a_digit:
  // 681:           $symbol range(buf s idx-1)
  // 682:           !s undefined
  // 683:           unless already_checked(symbol):
  // 684:             !already_checked(symbol) true
  // ...
  initialize_future(frame->slots[2] /* collect_declarations */, frame->slots[5] /* temp__1 */);
  // 673: $$already_checked empty_set
  ((CELL *)frame->slots[1])->contents /* already_checked */ = get__empty_set();
  // 708: ... : collect_declarations source
  frame->slots[5] /* temp__1 */ = create_closure(entry__75_64, 0);
  // 708: collect_output $imports: collect_declarations source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__75_65;
}
static void entry__75_63(void) {
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
  // 706: ... !s idx
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
  // 689: declaration(1)
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
  // 689: declaration(1) != '#'
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
  // 689: declaration(1) != '#'
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
  // 687: $do_import
  // 688:   &&
  // 689:     declaration(1) != '#'
  // 690:     not(declaration .has_prefix. "typedef")
  // 691:     not(declaration .has_prefix. "REGISTER")
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
  // 690: ... declaration .has_prefix. "typedef"
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
  // 690: not(declaration .has_prefix. "typedef")
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
  // 691: not(declaration .has_prefix. "REGISTER")
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
  // 691: ... declaration .has_prefix. "REGISTER"
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
  // 691: not(declaration .has_prefix. "REGISTER")
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
  // 691: not(declaration .has_prefix. "REGISTER")
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
  // 694: ->
  // 695:   declaration(1) == '#' || declaration .has_prefix. "REGISTER"
  // 696:   :
  // 697:     collect_declarations declaration .truncate_from. '{'
  frame->slots[3] /* temp__1 */ = create_closure(entry__75_35, 0);
  // 698: -> declaration .has_prefix. "typedef struct":
  // 699:   for_each_line between(declaration '{' '}').trim: (line)
  // 700:     collect_declarations until(line ' ' -1)
  frame->slots[4] /* temp__2 */ = create_closure(entry__75_44, 0);
  // 701: :
  // 702:   collect_declarations declaration
  frame->slots[5] /* temp__3 */ = create_closure(entry__75_53, 0);
  // 693: cond
  // 694:   ->
  // 695:     declaration(1) == '#' || declaration .has_prefix. "REGISTER"
  // 696:     :
  // 697:       collect_declarations declaration .truncate_from. '{'
  // 698:   -> declaration .has_prefix. "typedef struct":
  // 699:     for_each_line between(declaration '{' '}').trim: (line)
  // 700:       collect_declarations until(line ' ' -1)
  // 701:   :
  // 702:     collect_declarations declaration
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = frame->slots[5] /* temp__3 */;
  result_count = 0;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__75_54;
}
static void entry__75_50(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // line: 0
  // collect_declarations: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* collect_declarations */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 700: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__75_51;
}
static void cont__75_51(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 700: ... until(line ' ' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* line */;
  arguments->slots[1] = character__32;
  arguments->slots[2] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__until();
  func = myself->type;
  frame->cont = cont__75_52;
}
static void cont__75_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 700: collect_declarations until(line ' ' -1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* collect_declarations */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__75_47(void) {
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
  // 699: ... between(declaration '{' '}')
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* declaration */;
  arguments->slots[1] = character__123;
  arguments->slots[2] = character__125;
  result_count = 1;
  myself = get__between();
  func = myself->type;
  frame->cont = cont__75_48;
}
static void cont__75_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 699: ... between(declaration '{' '}').trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__75_49;
}
static void cont__75_49(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 699: ... : (line)
  // 700:   collect_declarations until(line ' ' -1)
  frame->slots[4] /* temp__3 */ = create_closure(entry__75_50, 1);
  // 699: for_each_line between(declaration '{' '}').trim: (line)
  // 700:   collect_declarations until(line ' ' -1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__for_each_line();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__75_42(void) {
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
  // 697: ... declaration .truncate_from. '{'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* declaration */;
  arguments->slots[1] = character__123;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__75_43;
}
static void cont__75_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 697: collect_declarations declaration .truncate_from. '{'
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
  // 695: declaration(1)
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
  // 695: declaration(1) == '#'
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
  // 695: ... declaration .has_prefix. "REGISTER"
  frame->slots[5] /* temp__4 */ = create_closure(entry__75_38, 0);
  // 695: declaration(1) == '#' || declaration .has_prefix. "REGISTER"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__75_41;
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
  // 695: ... declaration .has_prefix. "REGISTER"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* declaration */;
  arguments->slots[1] = string__75_39;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__75_40;
}
static void cont__75_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 695: ... declaration .has_prefix. "REGISTER"
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
  // 696: :
  // 697:   collect_declarations declaration .truncate_from. '{'
  frame->slots[6] /* temp__5 */ = create_closure(entry__75_42, 0);
  // 694: ->
  // 695:   declaration(1) == '#' || declaration .has_prefix. "REGISTER"
  // 696:   :
  // 697:     collect_declarations declaration .truncate_from. '{'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__5 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__75_44(void) {
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
  // 698: ... declaration .has_prefix. "typedef struct"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* declaration */;
  arguments->slots[1] = string__75_45;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__75_46;
}
static void cont__75_46(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 698: ... :
  // 699:   for_each_line between(declaration '{' '}').trim: (line)
  // 700:     collect_declarations until(line ' ' -1)
  frame->slots[3] /* temp__2 */ = create_closure(entry__75_47, 0);
  // 698: -> declaration .has_prefix. "typedef struct":
  // 699:   for_each_line between(declaration '{' '}').trim: (line)
  // 700:     collect_declarations until(line ' ' -1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__75_53(void) {
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
  // 702: collect_declarations declaration
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* declaration */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* collect_declarations */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__75_54(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 703: if do_import: write "IMPORT "
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* do_import */;
  arguments->slots[1] = func__75_55;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__75_57;
}
static void entry__75_55(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 703: ... write "IMPORT "
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__75_56;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__75_57(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 704: write declaration
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
  // 684: !already_checked(symbol) true
  frame->slots[4] /* temp__1 */ = get__true();
  // 684: !already_checked(symbol)
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
  // 685: $declaration runtime_symbols(symbol)
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
  // 686: ... declaration.is_defined
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
  // 686: ... :
  // 687:   $do_import
  // 688:     &&
  // 689:       declaration(1) != '#'
  // 690:       not(declaration .has_prefix. "typedef")
  // 691:       not(declaration .has_prefix. "REGISTER")
  // 692:   
  // 693:   cond
  // 694:     ->
  // 695:       declaration(1) == '#' || declaration .has_prefix. "REGISTER"
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__75_21, 0);
  // 686: if declaration.is_defined:
  // 687:   $do_import
  // 688:     &&
  // 689:       declaration(1) != '#'
  // 690:       not(declaration .has_prefix. "typedef")
  // 691:       not(declaration .has_prefix. "REGISTER")
  // 692:   
  // 693:   cond
  // 694:     ->
  // 695:       declaration(1) == '#' || declaration .has_prefix. "REGISTER"
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
  // 681: ... idx-1
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
  // 681: $symbol range(buf s idx-1)
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
  // 682: !s undefined
  ((CELL *)frame->slots[1])->contents /* s */ = get__undefined();
  // 683: ... already_checked(symbol)
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
  // 683: ... :
  // 684:   !already_checked(symbol) true
  // 685:   $declaration runtime_symbols(symbol)
  // 686:   if declaration.is_defined:
  // 687:     $do_import
  // 688:       &&
  // 689:         declaration(1) != '#'
  // 690:         not(declaration .has_prefix. "typedef")
  // 691:         not(declaration .has_prefix. "REGISTER")
  // 692:     
  // ...
  frame->slots[7] /* temp__2 */ = create_closure(entry__75_17, 0);
  // 683: unless already_checked(symbol):
  // 684:   !already_checked(symbol) true
  // 685:   $declaration runtime_symbols(symbol)
  // 686:   if declaration.is_defined:
  // 687:     $do_import
  // 688:       &&
  // 689:         declaration(1) != '#'
  // 690:         not(declaration .has_prefix. "typedef")
  // 691:         not(declaration .has_prefix. "REGISTER")
  // 692:     
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
  // 680: ... chr.is_a_letter
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
  // 680: ... chr == '_' || chr.is_a_digit
  frame->slots[8] /* temp__3 */ = create_closure(entry__75_7, 0);
  // 680: ... chr.is_a_letter || chr == '_' || chr.is_a_digit
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
  // 680: ... chr == '_'
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
  // 680: ... chr.is_a_digit
  frame->slots[3] /* temp__3 */ = create_closure(entry__75_9, 0);
  // 680: ... chr == '_' || chr.is_a_digit
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
  // 680: ... chr.is_a_digit
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
  // 680: ... chr.is_a_digit
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
  // 680: ... chr == '_' || chr.is_a_digit
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
  // 680: ... :
  // 681:   $symbol range(buf s idx-1)
  // 682:   !s undefined
  // 683:   unless already_checked(symbol):
  // 684:     !already_checked(symbol) true
  // 685:     $declaration runtime_symbols(symbol)
  // 686:     if declaration.is_defined:
  // 687:       $do_import
  // 688:         &&
  // 689:           declaration(1) != '#'
  // ...
  frame->slots[9] /* temp__4 */ = create_closure(entry__75_13, 0);
  // 680: unless chr.is_a_letter || chr == '_' || chr.is_a_digit:
  // 681:   $symbol range(buf s idx-1)
  // 682:   !s undefined
  // 683:   unless already_checked(symbol):
  // 684:     !already_checked(symbol) true
  // 685:     $declaration runtime_symbols(symbol)
  // 686:     if declaration.is_defined:
  // 687:       $do_import
  // 688:         &&
  // 689:           declaration(1) != '#'
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
static void entry__75_58(void) {
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
  // 706: ... chr.is_a_letter
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  result_count = 1;
  myself = get__is_a_letter();
  func = myself->type;
  frame->cont = cont__75_59;
}
static void cont__75_59(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 706: ... chr == '_'
  frame->slots[5] /* temp__3 */ = create_closure(entry__75_60, 0);
  // 706: ... chr.is_a_letter || chr == '_'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__75_62;
}
static void entry__75_60(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 706: ... chr == '_'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__95;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__75_61;
}
static void cont__75_61(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 706: ... chr == '_'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__75_62(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 706: ... : !s idx
  frame->slots[6] /* temp__4 */ = create_closure(entry__75_63, 0);
  // 706: if chr.is_a_letter || chr == '_': !s idx
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
  // 679: s.is_defined
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
  // 679: ... :
  // 680:   unless chr.is_a_letter || chr == '_' || chr.is_a_digit:
  // 681:     $symbol range(buf s idx-1)
  // 682:     !s undefined
  // 683:     unless already_checked(symbol):
  // 684:       !already_checked(symbol) true
  // 685:       $declaration runtime_symbols(symbol)
  // 686:       if declaration.is_defined:
  // 687:         $do_import
  // 688:           &&
  // ...
  frame->slots[7] /* temp__2 */ = create_closure(entry__75_5, 0);
  // 705: :
  // 706:   if chr.is_a_letter || chr == '_': !s idx
  frame->slots[8] /* temp__3 */ = create_closure(entry__75_58, 0);
  // 678: if
  // 679:   s.is_defined:
  // 680:     unless chr.is_a_letter || chr == '_' || chr.is_a_digit:
  // 681:       $symbol range(buf s idx-1)
  // 682:       !s undefined
  // 683:       unless already_checked(symbol):
  // 684:         !already_checked(symbol) true
  // 685:         $declaration runtime_symbols(symbol)
  // 686:         if declaration.is_defined:
  // 687:           $do_import
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
static void entry__75_2(void) {
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
  // 676: $$s undefined
  ((CELL *)frame->slots[3])->contents /* s */ = get__undefined();
  // 677: ... : (idx chr)
  // 678:   if
  // 679:     s.is_defined:
  // 680:       unless chr.is_a_letter || chr == '_' || chr.is_a_digit:
  // 681:         $symbol range(buf s idx-1)
  // 682:         !s undefined
  // 683:         unless already_checked(symbol):
  // 684:           !already_checked(symbol) true
  // 685:           $declaration runtime_symbols(symbol)
  // 686:           if declaration.is_defined:
  // ...
  frame->slots[4] /* temp__1 */ = create_closure(entry__75_3, 2);
  // 677: for_each buf: (idx chr)
  // 678:   if
  // 679:     s.is_defined:
  // 680:       unless chr.is_a_letter || chr == '_' || chr.is_a_digit:
  // 681:         $symbol range(buf s idx-1)
  // 682:         !s undefined
  // 683:         unless already_checked(symbol):
  // 684:           !already_checked(symbol) true
  // 685:           $declaration runtime_symbols(symbol)
  // 686:           if declaration.is_defined:
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
static void entry__75_64(void) {
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
  // 708: ... collect_declarations source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* source */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* collect_declarations */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__75_65(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* imports */, arguments->slots[0]);
  // 709: $first_part source .before. "// INSERT HERE //"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  arguments->slots[1] = string__75_66;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__75_67;
}
static void cont__75_67(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* first_part */, arguments->slots[0]);
  // 710: write first_part
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* first_part */;
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
  // 711: write imports
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* imports */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__75_69;
}
static void cont__75_69(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 712: ... length_of(first_part)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* first_part */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__75_70;
}
static void cont__75_70(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__3 */ = arguments->slots[0];
  // 712: ... length_of(first_part)+18
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__3 */;
  arguments->slots[1] = number__18;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__75_71;
}
static void cont__75_71(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 712: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__75_72;
}
static void cont__75_72(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__4 */ = arguments->slots[0];
  // 712: ... range(source length_of(first_part)+18 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  arguments->slots[2] = frame->slots[8] /* temp__4 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__75_73;
}
static void cont__75_73(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 712: write range(source length_of(first_part)+18 -1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__75_74;
}
static void cont__75_74(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 713: if do_time_passes: write_timing_info "collecting imports"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = func__75_75;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__76_1(void) {
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
  // 716: ... main_info.is_a_directory
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
  // 716: if main_info.is_a_directory: Error "Expected a source code file!"
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
  // 716: ... Error "Expected a source code file!"
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
  // 717: ... main_filename .has_suffix. ".sim"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  arguments->slots[1] = string__76_6;
  result_count = 1;
  myself = get__has_suffix();
  func = myself->type;
  frame->cont = cont__76_7;
}
static void cont__76_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 717: unless main_filename .has_suffix. ".sim":
  // 718:   Error "
  // 719:     Expected ".sim" file extension in source filename!@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = func__76_8;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__76_10;
}
static void entry__76_8(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 718: Error "
  // 719:   Expected ".sim" file extension in source filename!@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__76_9;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__76_10(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 721: $mod_filename main_filename .without_suffix. ".sim"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  arguments->slots[1] = string__76_11;
  result_count = 1;
  myself = get__without_suffix();
  func = myself->type;
  frame->cont = cont__76_12;
}
static void cont__76_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* mod_filename */, arguments->slots[0]);
  // 722: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__76_13;
}
static void cont__76_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 722: $mod_name truncate_until(mod_filename '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* mod_filename */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__76_14;
}
static void cont__76_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* mod_name */, arguments->slots[0]);
  // 723: body mod_filename mod_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* mod_filename */;
  arguments->slots[1] = frame->slots[3] /* mod_name */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame->cont = cont__76_15;
}
static void cont__76_15(void) {
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
  // 727: %sim2c::module_name mod_name
  initialize_maybe_future(get__sim2c__module_name(), frame->slots[1] /* mod_name */);
  // 728: ... list(main_filename)
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
  // 728: sim2c list(main_filename)
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
static void entry__77_1(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 726: compile_exe: (_mod_filename mod_name)
  // 727:   %sim2c::module_name mod_name
  // 728:   sim2c list(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__77_2;
  result_count = frame->caller_result_count;
  myself = var._compile_exe;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__78_20(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 738: ... write_timing_info "writing C-source"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__78_21;
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
  // 732: ... module_prefix.is_defined
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
  // 732: ... : append string(module_prefix '/') &mod_name
  frame->slots[5] /* temp__2 */ = create_closure(entry__78_4, 0);
  // 732: if module_prefix.is_defined: append string(module_prefix '/') &mod_name
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
  // 732: ... string(module_prefix '/')
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
  // 732: ... append string(module_prefix '/') &mod_name
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
  // 733: ... :
  // 734:   %sim2c::module_name replace_all(mod_name '/' = "__" '.' = "__")
  // 735:   sim2c list(main_filename)
  frame->slots[4] /* temp__1 */ = create_closure(entry__78_8, 0);
  // 733: collect_output $c_source:
  // 734:   %sim2c::module_name replace_all(mod_name '/' = "__" '.' = "__")
  // 735:   sim2c list(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__78_16;
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
  // 734: ... '/' = "__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = string__78_9;
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
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 734: ... '.' = "__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__46;
  arguments->slots[1] = string__78_11;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__78_12;
}
static void cont__78_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 734: %sim2c::module_name replace_all(mod_name '/' = "__" '.' = "__")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* mod_name */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  arguments->slots[2] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__78_13;
}
static void cont__78_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(get__sim2c__module_name(), arguments->slots[0]);
  // 735: ... list(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__78_14;
}
static void cont__78_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 735: sim2c list(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__sim2c();
  func = myself->type;
  frame->cont = cont__78_15;
}
static void cont__78_15(void) {
  myself = frame->slots[0] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__78_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* c_source */, arguments->slots[0]);
  // 736: ... : create_imports c_source
  frame->slots[4] /* temp__1 */ = create_closure(entry__78_17, 0);
  // 736: collect_output $c_buf: create_imports c_source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__78_18;
}
static void entry__78_17(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // c_source: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* c_source */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 736: ... create_imports c_source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_source */;
  result_count = frame->caller_result_count;
  myself = var._create_imports;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__78_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* c_buf */, arguments->slots[0]);
  // 737: write c_buf
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* c_buf */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__78_19;
}
static void cont__78_19(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 738: if do_time_passes: write_timing_info "writing C-source"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = func__78_20;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__78_1(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 731: compile_exe: (_mod_filename $mod_name)
  // 732:   if module_prefix.is_defined: append string(module_prefix '/') &mod_name
  // 733:   collect_output $c_source:
  // 734:     %sim2c::module_name replace_all(mod_name '/' = "__" '.' = "__")
  // 735:     sim2c list(main_filename)
  // 736:   collect_output $c_buf: create_imports c_source
  // 737:   write c_buf
  // 738:   if do_time_passes: write_timing_info "writing C-source"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__78_2;
  result_count = frame->caller_result_count;
  myself = var._compile_exe;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__79_36(void) {
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
  // 767: without_prefix &filename prefix_path
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* filename */;
  arguments->slots[1] = frame->slots[1] /* prefix_path */;
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
  // 768: without_prefix &filename '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* filename */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__without_prefix();
  func = myself->type;
  frame->cont = cont__79_38;
}
static void cont__79_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* filename */ = arguments->slots[0];
  // 769: writeln filename
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* filename */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__79_1(void) {
  allocate_initialized_frame_gc(0, 2);
  // slot allocations:
  // prefix_path: 0
  frame->slots[0] /* prefix_path */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 741: !platform_specific_priority multi_dimensional_table(types::table types::table)
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
  // 742: for_each supported_platforms: (supported_platform _parent_platform)
  // 743:   $$platform supported_platform
  // 744:   $$priority 0
  // 745:   do: (-> break)
  // 746:     forever:
  // 747:       $plat supported_platforms(platform)
  // 748:       if plat.is_undefined break
  // 749:       inc &priority
  // 750:       !platform_specific_priority(supported_platform platform) priority
  // 751:       if plat == NONE break
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
  // 746: ... :
  // 747:   $plat supported_platforms(platform)
  // 748:   if plat.is_undefined break
  // 749:   inc &priority
  // 750:   !platform_specific_priority(supported_platform platform) priority
  // 751:   if plat == NONE break
  // 752:   !platform plat
  frame->slots[4] /* temp__1 */ = create_closure(entry__79_5, 0);
  // 746: forever:
  // 747:   $plat supported_platforms(platform)
  // 748:   if plat.is_undefined break
  // 749:   inc &priority
  // 750:   !platform_specific_priority(supported_platform platform) priority
  // 751:   if plat == NONE break
  // 752:   !platform plat
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
  // 747: $plat supported_platforms(platform)
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
  // 748: ... plat.is_undefined
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
  // 748: if plat.is_undefined break
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
  // 749: inc &priority
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
  // 750: !platform_specific_priority(supported_platform platform) priority
  frame->slots[5] /* temp__1 */ = ((CELL *)frame->slots[2])->contents /* priority */;
  // 750: !platform_specific_priority(supported_platform platform)
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
  // 751: ... plat == NONE
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
  // 751: if plat == NONE break
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
  // 752: !platform plat
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
  // 743: $$platform supported_platform
  ((CELL *)frame->slots[2])->contents /* platform */ = frame->slots[0] /* supported_platform */;
  // 744: $$priority 0
  ((CELL *)frame->slots[3])->contents /* priority */ = number__0;
  // 745: ... : (-> break)
  // 746:   forever:
  // 747:     $plat supported_platforms(platform)
  // 748:     if plat.is_undefined break
  // 749:     inc &priority
  // 750:     !platform_specific_priority(supported_platform platform) priority
  // 751:     if plat == NONE break
  // 752:     !platform plat
  frame->slots[4] /* temp__1 */ = create_closure(entry__79_4, 0);
  // 745: do: (-> break)
  // 746:   forever:
  // 747:     $plat supported_platforms(platform)
  // 748:     if plat.is_undefined break
  // 749:     inc &priority
  // 750:     !platform_specific_priority(supported_platform platform) priority
  // 751:     if plat == NONE break
  // 752:     !platform plat
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
  // 754: main_info.is_a_directory
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
  // 753: if
  // 754:   main_info.is_a_directory:
  // 755:     %mode LIB
  // 756:     if verbose: ewriteln "list dependencies for " main_filename
  // 757:     compile_modules main_filename behind(main_filename '/' -1)
  // 758:   :
  // 759:     compile_exe: (mod_filename mod_name)
  // 760:       if verbose: ewriteln "list dependencies for " mod_filename
  // 761:       compile_module mod_filename mod_name
  // 762:     writeln "runtime/linker.c"
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__79_16;
  arguments->slots[2] = func__79_23;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__79_34;
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
  // 756: if verbose: ewriteln "list dependencies for " main_filename
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
  // 756: ... ewriteln "list dependencies for " main_filename
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
  // 757: ... 1
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
  // 757: ... behind(main_filename '/' -1)
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
  // 757: compile_modules main_filename behind(main_filename '/' -1)
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
  // 759: compile_exe: (mod_filename mod_name)
  // 760:   if verbose: ewriteln "list dependencies for " mod_filename
  // 761:   compile_module mod_filename mod_name
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__79_24;
  result_count = 0;
  myself = var._compile_exe;
  func = myself->type;
  frame->cont = cont__79_28;
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
  // 760: ... : ewriteln "list dependencies for " mod_filename
  frame->slots[2] /* temp__1 */ = create_closure(entry__79_25, 0);
  // 760: if verbose: ewriteln "list dependencies for " mod_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__79_27;
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
  // 760: ... ewriteln "list dependencies for " mod_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__79_26;
  arguments->slots[1] = frame->slots[0] /* mod_filename */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__79_27(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 761: compile_module mod_filename mod_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = frame->slots[1] /* mod_name */;
  result_count = frame->caller_result_count;
  myself = var._compile_module;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__79_28(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 762: writeln "runtime/linker.c"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__79_29;
  result_count = 0;
  myself = get__writeln();
  func = myself->type;
  frame->cont = cont__79_30;
}
static void cont__79_30(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 763: writeln "runtime/memory.c"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__79_31;
  result_count = 0;
  myself = get__writeln();
  func = myself->type;
  frame->cont = cont__79_32;
}
static void cont__79_32(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 764: writeln "runtime/debugger.c"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__79_33;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__79_34(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 765: $prefix_path current_path()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__current_path();
  func = myself->type;
  frame->cont = cont__79_35;
}
static void cont__79_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[0] /* prefix_path */, arguments->slots[0]);
  // 766: ... : ($filename)
  // 767:   without_prefix &filename prefix_path
  // 768:   without_prefix &filename '/'
  // 769:   writeln filename
  frame->slots[1] /* temp__1 */ = create_closure(entry__79_36, 1);
  // 766: for_each dependencies: ($filename)
  // 767:   without_prefix &filename prefix_path
  // 768:   without_prefix &filename '/'
  // 769:   writeln filename
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
  // 773: $codeblocks_path string(mod_filename ".codeblocks")
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
  // 774: $info stat(codeblocks_path)
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
  // 775: ... info.is_defined
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
  // 775: ... :
  // 776:   ewrite "
  // 777:     The directory "@(codeblocks_path)" already exists!
  frame->slots[11] /* temp__2 */ = create_closure(entry__80_7, 0);
  // 775: if info.is_defined:
  // 776:   ewrite "
  // 777:     The directory "@(codeblocks_path)" already exists!
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
  // 776: ... "
  // 777:   The directory "@(codeblocks_path)" already exists!
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
  // 776: ewrite "
  // 777:   The directory "@(codeblocks_path)" already exists!
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
  // 778: ... : ewriteln "build Code::Blocks project in " codeblocks_path
  frame->slots[10] /* temp__1 */ = create_closure(entry__80_12, 0);
  // 778: if verbose: ewriteln "build Code::Blocks project in " codeblocks_path
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
  // 778: ... ewriteln "build Code::Blocks project in " codeblocks_path
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
  // 779: compile_module mod_filename mod_name
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
  // 780: show_file_list
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
  // 781: ... 1
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
  // 781: ... truncate_until(main_filename '/' -1)
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
  // 781: $basename truncate_until(main_filename '/' -1) .without_suffix. ".sim"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__1 */;
  arguments->slots[1] = string__80_19;
  result_count = 1;
  myself = get__without_suffix();
  func = myself->type;
  frame->cont = cont__80_20;
}
static void cont__80_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* basename */, arguments->slots[0]);
  // 782: $prefix_path current_path()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__current_path();
  func = myself->type;
  frame->cont = cont__80_21;
}
static void cont__80_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* prefix_path */, arguments->slots[0]);
  // 783: ... codeblocks_path .without_prefix. prefix_path
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* codeblocks_path */;
  arguments->slots[1] = frame->slots[5] /* prefix_path */;
  result_count = 1;
  myself = get__without_prefix();
  func = myself->type;
  frame->cont = cont__80_22;
}
static void cont__80_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 783: $depth count_occurrences(codeblocks_path .without_prefix. prefix_path '/')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__1 */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__count_occurrences();
  func = myself->type;
  frame->cont = cont__80_23;
}
static void cont__80_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* depth */, arguments->slots[0]);
  // 784: $path_prefix dup("../" depth)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__80_24;
  arguments->slots[1] = frame->slots[6] /* depth */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__80_25;
}
static void cont__80_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[7] /* path_prefix */, arguments->slots[0]);
  // 785: $cbp_filename string(codeblocks_path "/" basename ".cbp")
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* codeblocks_path */;
  arguments->slots[1] = string__80_26;
  arguments->slots[2] = frame->slots[4] /* basename */;
  arguments->slots[3] = string__80_27;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__80_28;
}
static void cont__80_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[8] /* cbp_filename */, arguments->slots[0]);
  // 786: mkdir codeblocks_path
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* codeblocks_path */;
  result_count = 0;
  myself = var._mkdir;
  func = myself->type;
  frame->cont = cont__80_29;
}
static void cont__80_29(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 787: $$buf ""
  ((CELL *)frame->slots[9])->contents /* buf */ = empty_string;
  // 788: ... "
  // 789:   <?xml version="1.0" encoding="UTF-8" standalone="yes" ?>
  // 790:   <CodeBlocks_project_file>
  // 791:     <FileVersion major="1" minor="6" />
  // 792:     <Project>
  // 793:       <Option title="@(basename)" />
  // 794:       <Option pch_mode="2" />
  // 795:       <Option compiler="gcc" />
  // 796:       <Build>
  // 797:         <Target title="debug">
  // ...
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__80_30;
  arguments->slots[1] = frame->slots[4] /* basename */;
  arguments->slots[2] = string__80_31;
  arguments->slots[3] = frame->slots[4] /* basename */;
  arguments->slots[4] = string__80_32;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__80_33;
}
static void cont__80_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 788: write_to &buf "
  // 789:   <?xml version="1.0" encoding="UTF-8" standalone="yes" ?>
  // 790:   <CodeBlocks_project_file>
  // 791:     <FileVersion major="1" minor="6" />
  // 792:     <Project>
  // 793:       <Option title="@(basename)" />
  // 794:       <Option pch_mode="2" />
  // 795:       <Option compiler="gcc" />
  // 796:       <Build>
  // 797:         <Target title="debug">
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[9])->contents /* buf */;
  arguments->slots[1] = frame->slots[10] /* temp__1 */;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__80_34;
}
static void cont__80_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[9])->contents /* buf */ = arguments->slots[0];
  // 809: ... : (filename)
  // 810:   write_to &buf "
  // 811:     @
  // 812:           <Add library="@(filename)" />
  frame->slots[10] /* temp__1 */ = create_closure(entry__80_35, 1);
  // 809: for_each libraries: (filename)
  // 810:   write_to &buf "
  // 811:     @
  // 812:           <Add library="@(filename)" />
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__libraries();
  arguments->slots[1] = frame->slots[10] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__80_40;
}
static void entry__80_35(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // filename: 0
  // buf: 1
  frame->slots[1] = myself->closure.frame->slots[9]; /* buf */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 810: ... "
  // 811:   @
  // 812:         <Add library="@(filename)" />
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__80_36;
  arguments->slots[1] = frame->slots[0] /* filename */;
  arguments->slots[2] = string__80_37;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__80_38;
}
static void cont__80_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 810: write_to &buf "
  // 811:   @
  // 812:         <Add library="@(filename)" />
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* buf */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__80_39;
}
static void cont__80_39(void) {
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
static void cont__80_40(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 813: ... "
  // 814:   @
  // 815:   
  // 816:       </Linker>
  // 817:       <Compiler>
  // 818:         <Add option="-Wall" />
  // 819:       </Compiler>
  // 820:       <Unit filename="@(path_prefix)runtime/common.h" />
  // 821:       <Unit filename="@(path_prefix)runtime/linker.h" />
  // 822:       <Unit filename="@(path_prefix)runtime/memory.c">
  // ...
  argument_count = 11;
  arguments = node_p;
  arguments->slots[0] = string__80_41;
  arguments->slots[1] = frame->slots[7] /* path_prefix */;
  arguments->slots[2] = string__80_42;
  arguments->slots[3] = frame->slots[7] /* path_prefix */;
  arguments->slots[4] = string__80_43;
  arguments->slots[5] = frame->slots[7] /* path_prefix */;
  arguments->slots[6] = string__80_44;
  arguments->slots[7] = frame->slots[7] /* path_prefix */;
  arguments->slots[8] = string__80_45;
  arguments->slots[9] = frame->slots[7] /* path_prefix */;
  arguments->slots[10] = string__80_46;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__80_47;
}
static void cont__80_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 813: write_to &buf "
  // 814:   @
  // 815:   
  // 816:       </Linker>
  // 817:       <Compiler>
  // 818:         <Add option="-Wall" />
  // 819:       </Compiler>
  // 820:       <Unit filename="@(path_prefix)runtime/common.h" />
  // 821:       <Unit filename="@(path_prefix)runtime/linker.h" />
  // 822:       <Unit filename="@(path_prefix)runtime/memory.c">
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[9])->contents /* buf */;
  arguments->slots[1] = frame->slots[10] /* temp__1 */;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__80_48;
}
static void cont__80_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[9])->contents /* buf */ = arguments->slots[0];
  // 831: ... : ($filename)
  // 832:   without_prefix &filename prefix_path
  // 833:   without_prefix &filename '/'
  // 834:   write_to &buf "
  // 835:     @
  // 836:     
  // 837:         <Unit filename="@(path_prefix)@(filename)">
  // 838:           <Option compilerVar="CC" />
  // 839:         </Unit>
  frame->slots[10] /* temp__1 */ = create_closure(entry__80_49, 1);
  // 831: for_each c_sources: ($filename)
  // 832:   without_prefix &filename prefix_path
  // 833:   without_prefix &filename '/'
  // 834:   write_to &buf "
  // 835:     @
  // 836:     
  // 837:         <Unit filename="@(path_prefix)@(filename)">
  // 838:           <Option compilerVar="CC" />
  // 839:         </Unit>
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._c_sources;
  arguments->slots[1] = frame->slots[10] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__80_56;
}
static void entry__80_49(void) {
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
  // 832: without_prefix &filename prefix_path
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* filename */;
  arguments->slots[1] = frame->slots[1] /* prefix_path */;
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
  // 833: without_prefix &filename '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* filename */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__without_prefix();
  func = myself->type;
  frame->cont = cont__80_51;
}
static void cont__80_51(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* filename */ = arguments->slots[0];
  // 834: ... "
  // 835:   @
  // 836:   
  // 837:       <Unit filename="@(path_prefix)@(filename)">
  // 838:         <Option compilerVar="CC" />
  // 839:       </Unit>
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__80_52;
  arguments->slots[1] = frame->slots[3] /* path_prefix */;
  arguments->slots[2] = ((CELL *)frame->slots[0])->contents /* filename */;
  arguments->slots[3] = string__80_53;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__80_54;
}
static void cont__80_54(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 834: write_to &buf "
  // 835:   @
  // 836:   
  // 837:       <Unit filename="@(path_prefix)@(filename)">
  // 838:         <Option compilerVar="CC" />
  // 839:       </Unit>
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* buf */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__80_55;
}
static void cont__80_55(void) {
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
static void cont__80_56(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 840: write_to &buf "
  // 841:       <Extensions>
  // 842:         <code_completion />
  // 843:         <debugger />
  // 844:       </Extensions>
  // 845:     </Project>
  // 846:   </CodeBlocks_project_file>
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[9])->contents /* buf */;
  arguments->slots[1] = string__80_57;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__80_58;
}
static void cont__80_58(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[9])->contents /* buf */ = arguments->slots[0];
  // 847: save cbp_filename buf
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* cbp_filename */;
  arguments->slots[1] = ((CELL *)frame->slots[9])->contents /* buf */;
  result_count = frame->caller_result_count;
  myself = get__save();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__80_1(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 772: compile_exe: (mod_filename mod_name)
  // 773:   $codeblocks_path string(mod_filename ".codeblocks")
  // 774:   $info stat(codeblocks_path)
  // 775:   if info.is_defined:
  // 776:     ewrite "
  // 777:       The directory "@(codeblocks_path)" already exists!
  // 778:   if verbose: ewriteln "build Code::Blocks project in " codeblocks_path
  // 779:   compile_module mod_filename mod_name
  // 780:   show_file_list
  // 781:   $basename truncate_until(main_filename '/' -1) .without_suffix. ".sim"
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__80_2;
  result_count = frame->caller_result_count;
  myself = var._compile_exe;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__81_1(void) {
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
  // 850: ... action == "simrun"
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
  // 850: if action == "simrun": Error "Cannot run a directory!"
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
  // 850: ... Error "Cannot run a directory!"
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
  // 852: if
  // 853:   do_extract_documentation:
  // 854:     extract_documentation main_filename
  // 855:   :
  // 856:     $$version ""
  // 857:     $$so_version ""
  // 858:     $version_filename string(main_filename "/VERSION")
  // 859:     if file_exists(version_filename):
  // 860:       !version string('-' load(version_filename).trim)
  // 861:       !so_version version .truncate_from. '.'
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__do_extract_documentation();
  arguments->slots[1] = func__81_7;
  arguments->slots[2] = func__81_8;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__81_106;
}
static void entry__81_101(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // err: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* err */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 922: ... err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* err */;
  result_count = 1;
  myself = get__from_utf8();
  func = myself->type;
  frame->cont = cont__81_102;
}
static void cont__81_102(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 922: ... Error err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__81_94(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // err: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* err */
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
  frame->cont = cont__81_95;
}
static void cont__81_95(void) {
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
static void entry__81_81(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // err: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* err */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 904: ... err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* err */;
  result_count = 1;
  myself = get__from_utf8();
  func = myself->type;
  frame->cont = cont__81_82;
}
static void cont__81_82(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 904: ... Error err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__81_72(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // err: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* err */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 896: ... err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* err */;
  result_count = 1;
  myself = get__from_utf8();
  func = myself->type;
  frame->cont = cont__81_73;
}
static void cont__81_73(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 896: ... Error err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__81_64(void) {
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
  // 892: "-Wl,-soname,libsim-@(base_filename)@(so_version).so.@(MAJOR)"
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__81_65;
  arguments->slots[1] = frame->slots[0] /* base_filename */;
  arguments->slots[2] = ((CELL *)frame->slots[1])->contents /* so_version */;
  arguments->slots[3] = string__81_66;
  arguments->slots[4] = var._MAJOR;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__81_67;
}
static void cont__81_67(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 893: library_paths_and_file_list()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = var._library_paths_and_file_list;
  func = myself->type;
  frame->cont = cont__81_68;
}
static void cont__81_68(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 890: Gcc $_out $err $success
  // 891:   "-shared"
  // 892:   "-Wl,-soname,libsim-@(base_filename)@(so_version).so.@(MAJOR)"
  // 893:   library_paths_and_file_list()*
  // 894:   "-o"
  // 895:   lib_filename
  argument_count = 0;
  arguments = node_p;
  arguments->slots[argument_count++] = string__81_69;
  arguments->slots[argument_count++] = frame->slots[6] /* temp__1 */;
  unfold(frame->slots[7] /* temp__2 */);
  arguments->slots[argument_count++] = string__81_70;
  arguments->slots[argument_count++] = frame->slots[2] /* lib_filename */;
  result_count = 3;
  myself = var._Gcc;
  func = myself->type;
  frame->cont = cont__81_71;
}
static void cont__81_71(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__3 */ = arguments->slots[0];
  frame->slots[9] /* temp__4 */ = arguments->slots[1];
  frame->slots[10] /* temp__5 */ = arguments->slots[2];
  // 890: ... _out
  initialize_future(frame->slots[3] /* out */, frame->slots[8] /* temp__3 */);
  // 890: ... err
  initialize_future(frame->slots[4] /* err */, frame->slots[9] /* temp__4 */);
  // 890: ... success
  initialize_future(frame->slots[5] /* success */, frame->slots[10] /* temp__5 */);
  // 896: ... : Error err.from_utf8
  frame->slots[6] /* temp__1 */ = create_closure(entry__81_72, 0);
  // 896: unless success: Error err.from_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* success */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__81_74(void) {
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
  // 900: library_paths_and_file_list()
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
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 901: "-lsim-@(MAJOR)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__81_76;
  arguments->slots[1] = var._MAJOR;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__81_77;
}
static void cont__81_77(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 898: Gcc $_out $err $success
  // 899:   "-shared"
  // 900:   library_paths_and_file_list()*
  // 901:   "-lsim-@(MAJOR)"
  // 902:   "-o"
  // 903:   lib_filename
  argument_count = 0;
  arguments = node_p;
  arguments->slots[argument_count++] = string__81_78;
  unfold(frame->slots[4] /* temp__1 */);
  arguments->slots[argument_count++] = frame->slots[5] /* temp__2 */;
  arguments->slots[argument_count++] = string__81_79;
  arguments->slots[argument_count++] = frame->slots[0] /* lib_filename */;
  result_count = 3;
  myself = var._Gcc;
  func = myself->type;
  frame->cont = cont__81_80;
}
static void cont__81_80(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  frame->slots[7] /* temp__4 */ = arguments->slots[1];
  frame->slots[8] /* temp__5 */ = arguments->slots[2];
  // 898: ... _out
  initialize_future(frame->slots[1] /* out */, frame->slots[6] /* temp__3 */);
  // 898: ... err
  initialize_future(frame->slots[2] /* err */, frame->slots[7] /* temp__4 */);
  // 898: ... success
  initialize_future(frame->slots[3] /* success */, frame->slots[8] /* temp__5 */);
  // 904: ... : Error err.from_utf8
  frame->slots[4] /* temp__1 */ = create_closure(entry__81_81, 0);
  // 904: unless success: Error err.from_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* success */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__81_83(void) {
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
  // 908: "
  // 909:   -Wl,-install_name,libsim-@(base_filename)@(so_version)-@(MAJOR)@
  // 910:   .dylib@
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = string__81_84;
  arguments->slots[1] = frame->slots[0] /* base_filename */;
  arguments->slots[2] = ((CELL *)frame->slots[1])->contents /* so_version */;
  arguments->slots[3] = string__81_85;
  arguments->slots[4] = var._MAJOR;
  arguments->slots[5] = string__81_86;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__81_87;
}
static void cont__81_87(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 911: library_paths_and_file_list()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = var._library_paths_and_file_list;
  func = myself->type;
  frame->cont = cont__81_88;
}
static void cont__81_88(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 912: "-lsim-@(MAJOR)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__81_89;
  arguments->slots[1] = var._MAJOR;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__81_90;
}
static void cont__81_90(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__3 */ = arguments->slots[0];
  // 906: Gcc $_out $err $success
  // 907:   "-dynamiclib"
  // 908:   "
  // 909:     -Wl,-install_name,libsim-@(base_filename)@(so_version)-@(MAJOR)@
  // 910:     .dylib@
  // 911:   library_paths_and_file_list()*
  // 912:   "-lsim-@(MAJOR)"
  // 913:   "-o"
  // 914:   lib_filename
  argument_count = 0;
  arguments = node_p;
  arguments->slots[argument_count++] = string__81_91;
  arguments->slots[argument_count++] = frame->slots[6] /* temp__1 */;
  unfold(frame->slots[7] /* temp__2 */);
  arguments->slots[argument_count++] = frame->slots[8] /* temp__3 */;
  arguments->slots[argument_count++] = string__81_92;
  arguments->slots[argument_count++] = frame->slots[2] /* lib_filename */;
  result_count = 3;
  myself = var._Gcc;
  func = myself->type;
  frame->cont = cont__81_93;
}
static void cont__81_93(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__4 */ = arguments->slots[0];
  frame->slots[10] /* temp__5 */ = arguments->slots[1];
  frame->slots[11] /* temp__6 */ = arguments->slots[2];
  // 906: ... _out
  initialize_future(frame->slots[3] /* out */, frame->slots[9] /* temp__4 */);
  // 906: ... err
  initialize_future(frame->slots[4] /* err */, frame->slots[10] /* temp__5 */);
  // 906: ... success
  initialize_future(frame->slots[5] /* success */, frame->slots[11] /* temp__6 */);
  // 915: ... : Error err.from_utf8
  frame->slots[6] /* temp__1 */ = create_closure(entry__81_94, 0);
  // 915: unless success: Error err.from_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* success */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__81_96(void) {
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
  // 919: library_paths_and_file_list()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = var._library_paths_and_file_list;
  func = myself->type;
  frame->cont = cont__81_97;
}
static void cont__81_97(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 917: Gcc $_out $err $success
  // 918:   "-shared"
  // 919:   library_paths_and_file_list()*
  // 920:   "-o"
  // 921:   lib_filename
  argument_count = 0;
  arguments = node_p;
  arguments->slots[argument_count++] = string__81_98;
  unfold(frame->slots[4] /* temp__1 */);
  arguments->slots[argument_count++] = string__81_99;
  arguments->slots[argument_count++] = frame->slots[0] /* lib_filename */;
  result_count = 3;
  myself = var._Gcc;
  func = myself->type;
  frame->cont = cont__81_100;
}
static void cont__81_100(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  frame->slots[6] /* temp__3 */ = arguments->slots[1];
  frame->slots[7] /* temp__4 */ = arguments->slots[2];
  // 917: ... _out
  initialize_future(frame->slots[1] /* out */, frame->slots[5] /* temp__2 */);
  // 917: ... err
  initialize_future(frame->slots[2] /* err */, frame->slots[6] /* temp__3 */);
  // 917: ... success
  initialize_future(frame->slots[3] /* success */, frame->slots[7] /* temp__4 */);
  // 922: ... : Error err.from_utf8
  frame->slots[4] /* temp__1 */ = create_closure(entry__81_101, 0);
  // 922: unless success: Error err.from_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* success */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__81_60(void) {
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
  // 886: if verbose: ewriteln "linking dynamic library"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = func__81_61;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__81_63;
}
static void entry__81_61(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 886: ... ewriteln "linking dynamic library"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__81_62;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__81_63(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 889: ... :
  // 890:   Gcc $_out $err $success
  // 891:     "-shared"
  // 892:     "-Wl,-soname,libsim-@(base_filename)@(so_version).so.@(MAJOR)"
  // 893:     library_paths_and_file_list()*
  // 894:     "-o"
  // 895:     lib_filename
  // 896:   unless success: Error err.from_utf8
  frame->slots[3] /* temp__1 */ = create_closure(entry__81_64, 0);
  // 897: ... :
  // 898:   Gcc $_out $err $success
  // 899:     "-shared"
  // 900:     library_paths_and_file_list()*
  // 901:     "-lsim-@(MAJOR)"
  // 902:     "-o"
  // 903:     lib_filename
  // 904:   unless success: Error err.from_utf8
  frame->slots[4] /* temp__2 */ = create_closure(entry__81_74, 0);
  // 905: ... :
  // 906:   Gcc $_out $err $success
  // 907:     "-dynamiclib"
  // 908:     "
  // 909:       -Wl,-install_name,libsim-@(base_filename)@(so_version)-@(MAJOR)@
  // 910:       .dylib@
  // 911:     library_paths_and_file_list()*
  // 912:     "-lsim-@(MAJOR)"
  // 913:     "-o"
  // 914:     lib_filename
  // ...
  frame->slots[5] /* temp__3 */ = create_closure(entry__81_83, 0);
  // 916: :
  // 917:   Gcc $_out $err $success
  // 918:     "-shared"
  // 919:     library_paths_and_file_list()*
  // 920:     "-o"
  // 921:     lib_filename
  // 922:   unless success: Error err.from_utf8
  frame->slots[6] /* temp__4 */ = create_closure(entry__81_96, 0);
  // 887: case
  // 888:   current_platform
  // 889:   "linux":
  // 890:     Gcc $_out $err $success
  // 891:       "-shared"
  // 892:       "-Wl,-soname,libsim-@(base_filename)@(so_version).so.@(MAJOR)"
  // 893:       library_paths_and_file_list()*
  // 894:       "-o"
  // 895:       lib_filename
  // 896:     unless success: Error err.from_utf8
  // ...
  argument_count = 8;
  arguments = node_p;
  arguments->slots[0] = get__current_platform();
  arguments->slots[1] = string__81_103;
  arguments->slots[2] = frame->slots[3] /* temp__1 */;
  arguments->slots[3] = string__81_104;
  arguments->slots[4] = frame->slots[4] /* temp__2 */;
  arguments->slots[5] = string__81_105;
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
  // 854: extract_documentation main_filename
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
  // 856: $$version ""
  ((CELL *)frame->slots[0])->contents /* version */ = empty_string;
  // 857: $$so_version ""
  ((CELL *)frame->slots[1])->contents /* so_version */ = empty_string;
  // 858: $version_filename string(main_filename "/VERSION")
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
  // 859: ... file_exists(version_filename)
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
  // 859: ... :
  // 860:   !version string('-' load(version_filename).trim)
  // 861:   !so_version version .truncate_from. '.'
  frame->slots[6] /* temp__2 */ = create_closure(entry__81_12, 0);
  // 859: if file_exists(version_filename):
  // 860:   !version string('-' load(version_filename).trim)
  // 861:   !so_version version .truncate_from. '.'
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
  // 860: ... load(version_filename)
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
  // 860: ... load(version_filename).trim
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
  // 860: !version string('-' load(version_filename).trim)
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
  // 861: !so_version version .truncate_from. '.'
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
  // 862: ... 1
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
  // 862: $base_filename truncate_until(main_filename '/' -1)
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
  // 868: -> string("libsim-" base_filename version ".so.@(MAJOR)")
  frame->slots[5] /* temp__1 */ = create_closure(entry__81_20, 0);
  // 870: -> string("libsim-" base_filename version "-@(MAJOR).dll")
  frame->slots[6] /* temp__2 */ = create_closure(entry__81_25, 0);
  // 872: -> string("libsim-" base_filename version "-@(MAJOR).dylib")
  frame->slots[7] /* temp__3 */ = create_closure(entry__81_31, 0);
  // 873: -> string("libsim-" base_filename ".so")
  frame->slots[8] /* temp__4 */ = create_closure(entry__81_37, 0);
  // 864: $lib_filename
  // 865:   case
  // 866:     current_platform
  // 867:     "linux"
  // 868:     -> string("libsim-" base_filename version ".so.@(MAJOR)")
  // 869:     "cygwin"
  // 870:     -> string("libsim-" base_filename version "-@(MAJOR).dll")
  // 871:     "darwin"
  // 872:     -> string("libsim-" base_filename version "-@(MAJOR).dylib")
  // 873:     -> string("libsim-" base_filename ".so")
  argument_count = 8;
  arguments = node_p;
  arguments->slots[0] = get__current_platform();
  arguments->slots[1] = string__81_41;
  arguments->slots[2] = frame->slots[5] /* temp__1 */;
  arguments->slots[3] = string__81_42;
  arguments->slots[4] = frame->slots[6] /* temp__2 */;
  arguments->slots[5] = string__81_43;
  arguments->slots[6] = frame->slots[7] /* temp__3 */;
  arguments->slots[7] = frame->slots[8] /* temp__4 */;
  result_count = 1;
  myself = get__case();
  func = myself->type;
  frame->cont = cont__81_44;
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
  // 868: ... ".so.@(MAJOR)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__81_21;
  arguments->slots[1] = var._MAJOR;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__81_22;
}
static void cont__81_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 868: ... string("libsim-" base_filename version ".so.@(MAJOR)")
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__81_23;
  arguments->slots[1] = frame->slots[0] /* base_filename */;
  arguments->slots[2] = ((CELL *)frame->slots[1])->contents /* version */;
  arguments->slots[3] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__81_24;
}
static void cont__81_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 868: -> string("libsim-" base_filename version ".so.@(MAJOR)")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__81_25(void) {
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
  // 870: ... "-@(MAJOR).dll"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__81_26;
  arguments->slots[1] = var._MAJOR;
  arguments->slots[2] = string__81_27;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__81_28;
}
static void cont__81_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 870: ... string("libsim-" base_filename version "-@(MAJOR).dll")
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__81_29;
  arguments->slots[1] = frame->slots[0] /* base_filename */;
  arguments->slots[2] = ((CELL *)frame->slots[1])->contents /* version */;
  arguments->slots[3] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__81_30;
}
static void cont__81_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 870: -> string("libsim-" base_filename version "-@(MAJOR).dll")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__81_31(void) {
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
  // 872: ... "-@(MAJOR).dylib"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__81_32;
  arguments->slots[1] = var._MAJOR;
  arguments->slots[2] = string__81_33;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__81_34;
}
static void cont__81_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 872: ... string("libsim-" base_filename version "-@(MAJOR).dylib")
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__81_35;
  arguments->slots[1] = frame->slots[0] /* base_filename */;
  arguments->slots[2] = ((CELL *)frame->slots[1])->contents /* version */;
  arguments->slots[3] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__81_36;
}
static void cont__81_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 872: -> string("libsim-" base_filename version "-@(MAJOR).dylib")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__81_37(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // base_filename: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* base_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 873: ... string("libsim-" base_filename ".so")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__81_38;
  arguments->slots[1] = frame->slots[0] /* base_filename */;
  arguments->slots[2] = string__81_39;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__81_40;
}
static void cont__81_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 873: -> string("libsim-" base_filename ".so")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__81_44(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* lib_filename */, arguments->slots[0]);
  // 875: ... : ewriteln "build library " lib_filename
  frame->slots[5] /* temp__1 */ = create_closure(entry__81_45, 0);
  // 875: if verbose: ewriteln "build library " lib_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__81_47;
}
static void entry__81_45(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // lib_filename: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* lib_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 875: ... ewriteln "build library " lib_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__81_46;
  arguments->slots[1] = frame->slots[0] /* lib_filename */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__81_47(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 876: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__81_48;
}
static void cont__81_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 876: ... behind(main_filename '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__81_49;
}
static void cont__81_49(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 876: compile_modules main_filename behind(main_filename '/' -1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = var._compile_modules;
  func = myself->type;
  frame->cont = cont__81_50;
}
static void cont__81_50(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 877: ... :
  // 878:   $info stat(lib_filename)
  // 879:   if
  // 880:     ||
  // 881:       info.is_undefined
  // 882:       last_modification_time > modification_time_of(info)
  // 883:     :
  // 884:       !do_link true
  frame->slots[5] /* temp__1 */ = create_closure(entry__81_51, 0);
  // 877: unless do_link:
  // 878:   $info stat(lib_filename)
  // 879:   if
  // 880:     ||
  // 881:       info.is_undefined
  // 882:       last_modification_time > modification_time_of(info)
  // 883:     :
  // 884:       !do_link true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_link();
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__81_59;
}
static void entry__81_58(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 884: !do_link true
  set__do_link(get__true());
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__81_51(void) {
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
  // 878: $info stat(lib_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* lib_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__81_52;
}
static void cont__81_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* info */, arguments->slots[0]);
  // 881: info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__81_53;
}
static void cont__81_53(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 882: last_modification_time > modification_time_of(info)
  frame->slots[4] /* temp__3 */ = create_closure(entry__81_54, 0);
  // 880: ||
  // 881:   info.is_undefined
  // 882:   last_modification_time > modification_time_of(info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__81_57;
}
static void entry__81_54(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // info: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 882: ... modification_time_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__81_55;
}
static void cont__81_55(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 882: last_modification_time > modification_time_of(info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = get__last_modification_time();
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__81_56;
}
static void cont__81_56(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 882: last_modification_time > modification_time_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__81_57(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 879: if
  // 880:   ||
  // 881:     info.is_undefined
  // 882:     last_modification_time > modification_time_of(info)
  // 883:   :
  // 884:     !do_link true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = func__81_58;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__81_59(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 885: ... :
  // 886:   if verbose: ewriteln "linking dynamic library"
  // 887:   case
  // 888:     current_platform
  // 889:     "linux":
  // 890:       Gcc $_out $err $success
  // 891:         "-shared"
  // 892:         "-Wl,-soname,libsim-@(base_filename)@(so_version).so.@(MAJOR)"
  // 893:         library_paths_and_file_list()*
  // 894:         "-o"
  // ...
  frame->slots[5] /* temp__1 */ = create_closure(entry__81_60, 0);
  // 885: if do_link:
  // 886:   if verbose: ewriteln "linking dynamic library"
  // 887:   case
  // 888:     current_platform
  // 889:     "linux":
  // 890:       Gcc $_out $err $success
  // 891:         "-shared"
  // 892:         "-Wl,-soname,libsim-@(base_filename)@(so_version).so.@(MAJOR)"
  // 893:         library_paths_and_file_list()*
  // 894:         "-o"
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
static void cont__81_106(void) {
  myself = frame->slots[0] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__82_20(void) {
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
  // 937: ... : ewriteln "compiling runtime module @(filename)"
  frame->slots[3] /* temp__1 */ = create_closure(entry__82_21, 0);
  // 937: if verbose: ewriteln "compiling runtime module @(filename)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__82_24;
}
static void entry__82_21(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // filename: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 937: ... "compiling runtime module @(filename)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__82_22;
  arguments->slots[1] = frame->slots[0] /* filename */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__82_23;
}
static void cont__82_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 937: ... ewriteln "compiling runtime module @(filename)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__82_24(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 938: compile_c c_filename o_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* c_filename */;
  arguments->slots[1] = frame->slots[2] /* o_filename */;
  result_count = frame->caller_result_count;
  myself = var._compile_c;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__82_1(void) {
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
  // 925: $c_filename string(filename ".c")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  arguments->slots[1] = string__82_2;
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
  initialize_future(frame->slots[1] /* c_filename */, arguments->slots[0]);
  // 926: $o_filename string(filename ".o")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  arguments->slots[1] = string__82_4;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__82_5;
}
static void cont__82_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* o_filename */, arguments->slots[0]);
  // 927: $c_info stat(c_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* c_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__82_6;
}
static void cont__82_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* c_info */, arguments->slots[0]);
  // 928: ... c_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* c_info */;
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
  // 928: ... :
  // 929:   Error "
  // 930:     @quot;@(c_filename)" does not exist!
  frame->slots[6] /* temp__2 */ = create_closure(entry__82_8, 0);
  // 928: if c_info.is_undefined:
  // 929:   Error "
  // 930:     @quot;@(c_filename)" does not exist!
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__82_12;
}
static void entry__82_8(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // c_filename: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* c_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 929: ... "
  // 930:   @quot;@(c_filename)" does not exist!
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__82_9;
  arguments->slots[1] = frame->slots[0] /* c_filename */;
  arguments->slots[2] = string__82_10;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__82_11;
}
static void cont__82_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 929: Error "
  // 930:   @quot;@(c_filename)" does not exist!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__82_12(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 931: $o_info stat(o_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* o_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__82_13;
}
static void cont__82_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* o_info */, arguments->slots[0]);
  // 934: o_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* o_info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__82_14;
}
static void cont__82_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 935: modification_time_of(c_info) > modification_time_of(o_info)
  frame->slots[7] /* temp__3 */ = create_closure(entry__82_15, 0);
  // 933: ||
  // 934:   o_info.is_undefined
  // 935:   modification_time_of(c_info) > modification_time_of(o_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__82_19;
}
static void entry__82_15(void) {
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
  // 935: ... modification_time_of(o_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* o_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__82_16;
}
static void cont__82_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 935: modification_time_of(c_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* c_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__82_17;
}
static void cont__82_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 935: modification_time_of(c_info) > modification_time_of(o_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__82_18;
}
static void cont__82_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 935: modification_time_of(c_info) > modification_time_of(o_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__82_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 936: :
  // 937:   if verbose: ewriteln "compiling runtime module @(filename)"
  // 938:   compile_c c_filename o_filename
  frame->slots[8] /* temp__4 */ = create_closure(entry__82_20, 0);
  // 932: if
  // 933:   ||
  // 934:     o_info.is_undefined
  // 935:     modification_time_of(c_info) > modification_time_of(o_info)
  // 936:   :
  // 937:     if verbose: ewriteln "compiling runtime module @(filename)"
  // 938:     compile_c c_filename o_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__84_1(void) {
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
  // 948: to_string &val
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
  // 949: $$ac 0
  ((CELL *)frame->slots[3])->contents /* ac */ = number__0;
  // 950: ... : (-> break)
  // 951:   for_each val: (i chr)
  // 952:     if chr == '.':
  // 953:       !ac length_of(val)-i
  // 954:       if n > i-1: append dup(" " n-(i-1)) &val
  // 955:       break
  frame->slots[4] /* temp__1 */ = create_closure(entry__84_3, 0);
  // 950: do: (-> break)
  // 951:   for_each val: (i chr)
  // 952:     if chr == '.':
  // 953:       !ac length_of(val)-i
  // 954:       if n > i-1: append dup(" " n-(i-1)) &val
  // 955:       break
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
  // 951: ... : (i chr)
  // 952:   if chr == '.':
  // 953:     !ac length_of(val)-i
  // 954:     if n > i-1: append dup(" " n-(i-1)) &val
  // 955:     break
  frame->slots[4] /* temp__1 */ = create_closure(entry__84_4, 2);
  // 951: for_each val: (i chr)
  // 952:   if chr == '.':
  // 953:     !ac length_of(val)-i
  // 954:     if n > i-1: append dup(" " n-(i-1)) &val
  // 955:     break
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
  // 953: ... length_of(val)
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
  // 953: !ac length_of(val)-i
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
  // 954: ... i-1
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
  // 954: ... n > i-1
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
  // 954: ... : append dup(" " n-(i-1)) &val
  frame->slots[7] /* temp__3 */ = create_closure(entry__84_11, 0);
  // 954: if n > i-1: append dup(" " n-(i-1)) &val
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
  // 954: ... i-1
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
  // 954: ... n-(i-1
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
  // 954: ... dup(" " n-(i-1))
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
  // 954: ... append dup(" " n-(i-1)) &val
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
  // 955: break
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
  // 952: ... chr == '.'
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
  // 952: ... :
  // 953:   !ac length_of(val)-i
  // 954:   if n > i-1: append dup(" " n-(i-1)) &val
  // 955:   break
  frame->slots[7] /* temp__2 */ = create_closure(entry__84_6, 0);
  // 952: if chr == '.':
  // 953:   !ac length_of(val)-i
  // 954:   if n > i-1: append dup(" " n-(i-1)) &val
  // 955:   break
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
  // 957: m > ac
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
  // 957: ... :
  // 958:   append &val dup("0" m-ac)
  frame->slots[5] /* temp__2 */ = create_closure(entry__84_21, 0);
  // 959: :
  // 960:   if ac > m: range &val 1 -(ac-m+1)
  frame->slots[6] /* temp__3 */ = create_closure(entry__84_26, 0);
  // 956: if
  // 957:   m > ac:
  // 958:     append &val dup("0" m-ac)
  // 959:   :
  // 960:     if ac > m: range &val 1 -(ac-m+1)
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
  // 960: ... ac-m
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
  // 960: ... ac-m+1
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
  // 960: ... ac-m+1)
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
  // 960: ... range &val 1 -(ac-m+1)
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
  // 958: ... m-ac
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
  // 958: ... dup("0" m-ac)
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
  // 958: append &val dup("0" m-ac)
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
  // 960: ... ac > m
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
  // 960: ... : range &val 1 -(ac-m+1)
  frame->slots[4] /* temp__2 */ = create_closure(entry__84_28, 0);
  // 960: if ac > m: range &val 1 -(ac-m+1)
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
  // 961: -> val
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* val */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__85_1(void) {
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
  // 964: $new_t current_time()
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
  // 966: filename.is_defined
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
  // 966: ... :
  // 967:   truncate_until &filename '/' -1
  // 968:   ewriteln
  // 969:     description
  // 970:     ' '
  // 971:     filename
  // 972:     ':'
  // 973:     dup(" " 12-length_of(description))
  // 974:     format_number(new_t-t 2 3)
  // 975:     " s"
  frame->slots[4] /* temp__2 */ = create_closure(entry__85_4, 0);
  // 976: :
  // 977:   ewriteln description ": " format_number(new_t-t 0 3) " s"
  frame->slots[5] /* temp__3 */ = create_closure(entry__85_14, 0);
  // 965: if
  // 966:   filename.is_defined:
  // 967:     truncate_until &filename '/' -1
  // 968:     ewriteln
  // 969:       description
  // 970:       ' '
  // 971:       filename
  // 972:       ':'
  // 973:       dup(" " 12-length_of(description))
  // 974:       format_number(new_t-t 2 3)
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = frame->slots[5] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__85_19;
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
  // 967: ... 1
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
  // 967: truncate_until &filename '/' -1
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
  // 973: ... length_of(description)
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
  // 973: ... 12-length_of(description)
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
  // 973: dup(" " 12-length_of(description))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__85_9;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__85_10;
}
static void cont__85_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 974: ... new_t-t
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* new_t */;
  arguments->slots[1] = var._t;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__85_11;
}
static void cont__85_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__5 */ = arguments->slots[0];
  // 974: format_number(new_t-t 2 3)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__5 */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = number__3;
  result_count = 1;
  myself = var._format_number;
  func = myself->type;
  frame->cont = cont__85_12;
}
static void cont__85_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__4 */ = arguments->slots[0];
  // 968: ewriteln
  // 969:   description
  // 970:   ' '
  // 971:   filename
  // 972:   ':'
  // 973:   dup(" " 12-length_of(description))
  // 974:   format_number(new_t-t 2 3)
  // 975:   " s"
  argument_count = 7;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* description */;
  arguments->slots[1] = character__32;
  arguments->slots[2] = ((CELL *)frame->slots[0])->contents /* filename */;
  arguments->slots[3] = character__58;
  arguments->slots[4] = frame->slots[3] /* temp__1 */;
  arguments->slots[5] = frame->slots[6] /* temp__4 */;
  arguments->slots[6] = string__85_13;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__85_14(void) {
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
  // 977: ... new_t-t
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* new_t */;
  arguments->slots[1] = var._t;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__85_15;
}
static void cont__85_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 977: ... format_number(new_t-t 0 3)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = number__0;
  arguments->slots[2] = number__3;
  result_count = 1;
  myself = var._format_number;
  func = myself->type;
  frame->cont = cont__85_16;
}
static void cont__85_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 977: ewriteln description ": " format_number(new_t-t 0 3) " s"
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* description */;
  arguments->slots[1] = string__85_17;
  arguments->slots[2] = frame->slots[2] /* temp__1 */;
  arguments->slots[3] = string__85_18;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__85_19(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 978: !t current_time()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__current_time();
  func = myself->type;
  frame->cont = cont__85_20;
}
static void cont__85_20(void) {
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
static void entry__86_123(void) {
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
  frame->cont = cont__86_124;
}
static void cont__86_124(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 1065: -> exe_filename
  frame->slots[4] /* temp__3 */ = create_closure(entry__86_125, 0);
  // 1066: -> string("./" exe_filename)
  frame->slots[5] /* temp__4 */ = create_closure(entry__86_126, 0);
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
  frame->cont = cont__86_129;
}
static void entry__86_125(void) {
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
static void entry__86_126(void) {
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
  arguments->slots[0] = string__86_127;
  arguments->slots[1] = frame->slots[0] /* exe_filename */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__86_128;
}
static void cont__86_128(void) {
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
static void cont__86_129(void) {
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
  // 984: current_platform == "cygwin"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__current_platform();
  arguments->slots[1] = string__86_3;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__86_4;
}
static void cont__86_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 985: -> string(mod_filename ".exe")
  frame->slots[10] /* temp__2 */ = create_closure(entry__86_5, 0);
  // 986: -> mod_filename
  frame->slots[11] /* temp__3 */ = create_closure(entry__86_8, 0);
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
  frame->cont = cont__86_9;
}
static void entry__86_5(void) {
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
  arguments->slots[1] = string__86_6;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__86_7;
}
static void cont__86_7(void) {
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
static void entry__86_8(void) {
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
static void cont__86_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* exe_filename */, arguments->slots[0]);
  // 988: ... : ewriteln "build executable " exe_filename
  frame->slots[9] /* temp__1 */ = create_closure(entry__86_10, 0);
  // 988: if verbose: ewriteln "build executable " exe_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__86_12;
}
static void entry__86_10(void) {
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
  arguments->slots[0] = string__86_11;
  arguments->slots[1] = frame->slots[0] /* exe_filename */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__86_12(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 989: $c_filename string(mod_filename ".c")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = string__86_13;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__86_14;
}
static void cont__86_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* c_filename */, arguments->slots[0]);
  // 990: $o_filename string(mod_filename ".o")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = string__86_15;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__86_16;
}
static void cont__86_16(void) {
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
  frame->cont = cont__86_17;
}
static void cont__86_17(void) {
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
  frame->cont = cont__86_18;
}
static void cont__86_18(void) {
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
  frame->cont = cont__86_19;
}
static void cont__86_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__objects(arguments->slots[0]);
  frame->slots[10] /* temp__2 */ = create_closure(entry__86_20, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_rebuild;
  arguments->slots[1] = frame->slots[10] /* temp__2 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__86_27;
}
static void entry__86_20(void) {
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
  frame->cont = cont__86_21;
}
static void cont__86_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 999: modification_time_of(sim_info) > modification_time_of(c_info)
  frame->slots[4] /* temp__3 */ = create_closure(entry__86_22, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__86_26;
}
static void entry__86_22(void) {
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
  frame->cont = cont__86_23;
}
static void cont__86_23(void) {
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
  frame->cont = cont__86_24;
}
static void cont__86_24(void) {
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
  frame->cont = cont__86_25;
}
static void cont__86_25(void) {
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
static void cont__86_26(void) {
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
static void cont__86_27(void) {
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
  frame->slots[11] /* temp__3 */ = create_closure(entry__86_28, 0);
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
  frame->slots[12] /* temp__4 */ = create_closure(entry__86_49, 0);
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
  frame->cont = cont__86_61;
}
static void entry__86_58(void) {
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
static void entry__86_59(void) {
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
  frame->cont = cont__86_60;
}
static void cont__86_60(void) {
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
static void entry__86_28(void) {
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
  arguments->slots[0] = string__86_29;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__86_30;
}
static void cont__86_30(void) {
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
  frame->cont = cont__86_31;
}
static void cont__86_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(get__sim2c__module_name(), arguments->slots[0]);
  // 1002: if verbose: ewriteln "build main module " module_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = func__86_32;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__86_34;
}
static void entry__86_32(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1002: ... ewriteln "build main module " module_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__86_33;
  arguments->slots[1] = get__module_name();
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__86_34(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1003: collect_output $c_source: sim2c list(main_filename) true
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__86_35;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__86_37;
}
static void entry__86_35(void) {
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
  frame->cont = cont__86_36;
}
static void cont__86_36(void) {
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
static void cont__86_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* c_source */, arguments->slots[0]);
  // 1004: ... : create_imports c_source
  frame->slots[6] /* temp__1 */ = create_closure(entry__86_38, 0);
  // 1004: collect_output !c_buf: create_imports c_source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__86_39;
}
static void entry__86_38(void) {
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
static void cont__86_39(void) {
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
  frame->cont = cont__86_40;
}
static void cont__86_40(void) {
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
  frame->cont = cont__86_41;
}
static void cont__86_41(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1006: ... : write_timing_info "saving" c_filename
  frame->slots[6] /* temp__1 */ = create_closure(entry__86_42, 0);
  // 1006: if do_time_passes: write_timing_info "saving" c_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 0;
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
  // 1006: ... write_timing_info "saving" c_filename
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
  frame->cont = cont__86_45;
}
static void cont__86_45(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1008: ... : write_timing_info "compiling" c_filename
  frame->slots[6] /* temp__1 */ = create_closure(entry__86_46, 0);
  // 1008: if do_time_passes: write_timing_info "compiling" c_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__86_48;
}
static void entry__86_46(void) {
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
  arguments->slots[0] = string__86_47;
  arguments->slots[1] = frame->slots[0] /* c_filename */;
  result_count = frame->caller_result_count;
  myself = get__write_timing_info();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__86_48(void) {
  myself = frame->slots[0] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__86_49(void) {
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
  frame->cont = cont__86_50;
}
static void cont__86_50(void) {
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
  frame->cont = cont__86_51;
}
static void cont__86_51(void) {
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
  frame->cont = cont__86_52;
}
static void cont__86_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 1015: modification_time_of(c_info) > modification_time_of(o_info)
  frame->slots[7] /* temp__3 */ = create_closure(entry__86_53, 0);
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
  frame->cont = cont__86_57;
}
static void entry__86_53(void) {
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
  frame->cont = cont__86_54;
}
static void cont__86_54(void) {
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
  frame->cont = cont__86_55;
}
static void cont__86_55(void) {
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
  frame->cont = cont__86_56;
}
static void cont__86_56(void) {
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
static void cont__86_57(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 1016: :
  // 1017:   compile_c c_filename o_filename
  frame->slots[8] /* temp__4 */ = create_closure(entry__86_58, 0);
  // 1018: :
  // 1019:   !last_modification_time modification_time_of(o_info)
  frame->slots[9] /* temp__5 */ = create_closure(entry__86_59, 0);
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
static void cont__86_61(void) {
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
  frame->cont = cont__86_62;
}
static void cont__86_62(void) {
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
  arguments->slots[1] = func__86_63;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__86_69;
}
static void entry__86_68(void) {
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
static void entry__86_63(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1023: "runtime/linker", "runtime/memory", "runtime/debugger"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__86_64;
  arguments->slots[1] = string__86_65;
  arguments->slots[2] = string__86_66;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__86_67;
}
static void cont__86_67(void) {
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
  arguments->slots[1] = func__86_68;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__86_69(void) {
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
  frame->slots[9] /* temp__1 */ = create_closure(entry__86_70, 0);
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
  frame->cont = cont__86_81;
}
static void entry__86_80(void) {
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
static void entry__86_70(void) {
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
  frame->cont = cont__86_71;
}
static void cont__86_71(void) {
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
  frame->cont = cont__86_72;
}
static void cont__86_72(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 1030: &&
  // 1031:   last_modification_time.is_defined
  // 1032:   last_modification_time > modification_time_of(info)
  frame->slots[4] /* temp__3 */ = create_closure(entry__86_73, 0);
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
  frame->cont = cont__86_79;
}
static void entry__86_73(void) {
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
  frame->cont = cont__86_74;
}
static void cont__86_74(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 1032: last_modification_time > modification_time_of(info)
  frame->slots[3] /* temp__3 */ = create_closure(entry__86_75, 0);
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
  frame->cont = cont__86_78;
}
static void entry__86_75(void) {
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
  frame->cont = cont__86_76;
}
static void cont__86_76(void) {
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
  frame->cont = cont__86_77;
}
static void cont__86_77(void) {
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
static void cont__86_78(void) {
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
static void cont__86_79(void) {
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
  arguments->slots[1] = func__86_80;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__86_81(void) {
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
  frame->slots[9] /* temp__1 */ = create_closure(entry__86_82, 0);
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
  frame->cont = cont__86_116;
}
static void entry__86_114(void) {
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
  frame->cont = cont__86_115;
}
static void cont__86_115(void) {
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
static void entry__86_97(void) {
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
  frame->cont = cont__86_98;
}
static void cont__86_98(void) {
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
static void entry__86_88(void) {
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
  arguments->slots[1] = func__86_89;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__86_91;
}
static void entry__86_89(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1040: ... ewriteln "linking static executable"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__86_90;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__86_91(void) {
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
  arguments->slots[argument_count++] = string__86_92;
  arguments->slots[argument_count++] = string__86_93;
  arguments->slots[argument_count++] = string__86_94;
  unfold(((CELL *)frame->slots[0])->contents /* libs_and_files */);
  arguments->slots[argument_count++] = string__86_95;
  arguments->slots[argument_count++] = frame->slots[1] /* exe_filename */;
  result_count = 3;
  myself = var._Gcc;
  func = myself->type;
  frame->cont = cont__86_96;
}
static void cont__86_96(void) {
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
  frame->slots[5] /* temp__1 */ = create_closure(entry__86_97, 0);
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
static void entry__86_99(void) {
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
  arguments->slots[1] = func__86_100;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__86_102;
}
static void entry__86_100(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1050: ... ewriteln "linking executable"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__86_101;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__86_102(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1054: current_platform == "linux"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__current_platform();
  arguments->slots[1] = string__86_103;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__86_104;
}
static void cont__86_104(void) {
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
  arguments->slots[1] = func__86_105;
  arguments->slots[2] = func__86_108;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__86_111;
}
static void entry__86_105(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1055: ... "-l:libsim.so.@(MAJOR)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__86_106;
  arguments->slots[1] = var._MAJOR;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__86_107;
}
static void cont__86_107(void) {
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
static void entry__86_108(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1056: ... "-lsim-@(MAJOR)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__86_109;
  arguments->slots[1] = var._MAJOR;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__86_110;
}
static void cont__86_110(void) {
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
static void cont__86_111(void) {
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
  arguments->slots[argument_count++] = string__86_112;
  arguments->slots[argument_count++] = frame->slots[1] /* exe_filename */;
  result_count = 3;
  myself = var._Gcc;
  func = myself->type;
  frame->cont = cont__86_113;
}
static void cont__86_113(void) {
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
  frame->slots[5] /* temp__1 */ = create_closure(entry__86_114, 0);
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
static void entry__86_82(void) {
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
  frame->cont = cont__86_83;
}
static void cont__86_83(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* libs_and_files */ = arguments->slots[0];
  // 1037: ... : push &libs_and_files "/usr/lib/libprofiler.so.0"
  frame->slots[2] /* temp__1 */ = create_closure(entry__86_84, 0);
  // 1037: if do_link_profiler: push &libs_and_files "/usr/lib/libprofiler.so.0"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_link_profiler;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__86_87;
}
static void entry__86_84(void) {
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
  arguments->slots[1] = string__86_85;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__86_86;
}
static void cont__86_86(void) {
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
static void cont__86_87(void) {
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
  frame->slots[2] /* temp__1 */ = create_closure(entry__86_88, 0);
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
  frame->slots[3] /* temp__2 */ = create_closure(entry__86_99, 0);
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
static void cont__86_116(void) {
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
  frame->cont = cont__86_117;
}
static void cont__86_117(void) {
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
  frame->cont = cont__86_118;
}
static void cont__86_118(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[8] /* zz */, arguments->slots[0]);
  // 1061: ... on_top_level && action == "simrun"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__on_top_level();
  arguments->slots[1] = func__86_119;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__86_122;
}
static void entry__86_119(void) {
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
  arguments->slots[1] = string__86_120;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__86_121;
}
static void cont__86_121(void) {
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
static void cont__86_122(void) {
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
  frame->slots[10] /* temp__2 */ = create_closure(entry__86_123, 0);
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
static void entry__86_1(void) {
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
  var._gcc = collect_node(var._gcc);
  var._mkdir = collect_node(var._mkdir);
  var._SIMLIBPATH = collect_node(var._SIMLIBPATH);
  var._SIMDATAPATH = collect_node(var._SIMDATAPATH);
  var._simlibpaths = collect_node(var._simlibpaths);
  var._simdatapaths = collect_node(var._simdatapaths);
  var._NONE = collect_node(var._NONE);
  unique__13_1 = collect_node(unique__13_1);
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
  unique__48_1 = collect_node(unique__48_1);
  var._LIB = collect_node(var._LIB);
  unique__49_1 = collect_node(unique__49_1);
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
  func__47_1 = create_function(entry__47_1, -1);
  func__63_6 = create_function(entry__63_6, 1);
  func__63_4 = create_function(entry__63_4, 1);
  func__63_3 = create_function(entry__63_3, 0);
  string__63_19 = from_latin_1_string("Cannot resolve required library \042", 33);
  string__63_20 = from_latin_1_string("\042!", 2);
  func__63_1 = create_function(entry__63_1, 1);
  string__64_13 = from_latin_1_string(".sim", 4);
  string__64_16 = from_latin_1_string(".meta", 5);
  string__64_18 = from_latin_1_string(".sim", 4);
  string__64_43 = from_latin_1_string("-common", 7);
  string__64_47 = from_latin_1_string("-", 1);
  string__64_48 = from_latin_1_string("-common", 7);
  string__64_60 = from_latin_1_string("The platform \042", 14);
  string__64_61 = from_latin_1_string("\042 is not supported!", 19);
  func__64_1 = create_function(entry__64_1, 2);
  func__65_1 = create_function(entry__65_1, 2);
  string__66_4 = from_latin_1_string("gcc ", 4);
  func__66_1 = create_function(entry__66_1, -1);
  func__67_2 = create_function(entry__67_2, 0);
  string__67_6 = from_latin_1_string("-c", 2);
  string__67_7 = from_latin_1_string("-o", 2);
  string__67_12 = from_latin_1_string("-DWITHIN_LIBRARY", 16);
  string__67_13 = from_latin_1_string("-fPIC", 5);
  string__67_14 = from_latin_1_string("-c", 2);
  string__67_15 = from_latin_1_string("-o", 2);
  func__67_1 = create_function(entry__67_1, 2);
  string__68_5 = from_latin_1_string(".meta", 5);
  string__68_8 = from_latin_1_string(".sim", 4);
  string__68_10 = from_latin_1_string(".meta", 5);
  string__68_12 = from_latin_1_string(".c", 2);
  string__68_15 = from_latin_1_string(".meta", 5);
  string__68_17 = from_latin_1_string(".sim", 4);
  string__68_51 = from_latin_1_string("/// ", 4);
  string__68_58 = from_latin_1_string("data", 4);
  string__68_61 = from_latin_1_string("./", 2);
  func__68_1 = create_function(entry__68_1, 3);
  string__69_3 = from_latin_1_string("/// ", 4);
  string__69_11 = from_latin_1_string("./", 2);
  func__69_26 = create_function(entry__69_26, 0);
  func__69_25 = create_function(entry__69_25, 0);
  func__69_32 = create_function(entry__69_32, 0);
  string__69_37 = from_latin_1_string("sim-", 4);
  string__69_44 = from_latin_1_string("require", 7);
  string__69_45 = from_latin_1_string("link", 4);
  func__69_1 = create_function(entry__69_1, -1);
  func__70_9 = create_function(entry__70_9, 0);
  string__70_14 = from_latin_1_string(".sim", 4);
  string__70_26 = from_latin_1_string(".c", 2);
  string__70_40 = from_latin_1_string("__", 2);
  string__70_42 = from_latin_1_string("__", 2);
  string__70_47 = from_latin_1_string("build application module ", 25);
  string__70_50 = from_latin_1_string("build library module ", 21);
  string__70_83 = from_latin_1_string("No source file(s) for module \042", 30);
  string__70_84 = from_latin_1_string("\042 found!", 8);
  string__70_89 = from_latin_1_string(".lib.o", 6);
  func__70_88 = create_function(entry__70_88, 0);
  string__70_91 = from_latin_1_string(".o", 2);
  func__70_90 = create_function(entry__70_90, 0);
  string__70_104 = from_latin_1_string(".c", 2);
  string__70_119 = from_latin_1_string("-", 1);
  string__70_140 = from_latin_1_string("-", 1);
  string__70_141 = from_latin_1_string(".c", 2);
  string__70_147 = from_latin_1_string(" #", 2);
  func__70_1 = create_function(entry__70_1, 2);
  func__71_1 = create_function(entry__71_1, 2);
  string__73_3 = from_latin_1_string("LD_LIBRARY_PATH", 15);
  string__73_7 = from_latin_1_string("LD_LIBRARY_PATH=", 16);
  string__73_11 = from_latin_1_string("included object files: ", 23);
  string__73_14 = from_latin_1_string("needed libraries: ", 18);
  func__73_2 = create_function(entry__73_2, 0);
  func__73_1 = create_function(entry__73_1, 0);
  string__74_3 = from_latin_1_string("LD_LIBRARY_PATH", 15);
  string__74_9 = from_latin_1_string("-L", 2);
  string__74_15 = from_latin_1_string("library paths: ", 15);
  string__74_21 = from_latin_1_string("sim-", 4);
  string__74_24 = from_latin_1_string("linux", 5);
  string__74_27 = from_latin_1_string("-l:lib", 6);
  string__74_28 = from_latin_1_string(".so.", 4);
  string__74_31 = from_latin_1_string("-l", 2);
  string__74_32 = from_latin_1_string("-", 1);
  string__74_40 = from_latin_1_string("-l:lib", 6);
  string__74_41 = from_latin_1_string(".so.", 4);
  string__74_44 = from_latin_1_string("-l", 2);
  func__74_1 = create_function(entry__74_1, 0);
  string__75_26 = from_latin_1_string("typedef", 7);
  string__75_30 = from_latin_1_string("REGISTER", 8);
  string__75_39 = from_latin_1_string("REGISTER", 8);
  string__75_45 = from_latin_1_string("typedef struct", 14);
  string__75_56 = from_latin_1_string("IMPORT ", 7);
  func__75_55 = create_function(entry__75_55, 0);
  string__75_66 = from_latin_1_string("// INSERT HERE //", 17);
  string__75_76 = from_latin_1_string("collecting imports", 18);
  func__75_75 = create_function(entry__75_75, 0);
  func__75_1 = create_function(entry__75_1, 1);
  string__76_4 = from_latin_1_string("Expected a source code file!", 28);
  func__76_3 = create_function(entry__76_3, 0);
  string__76_6 = from_latin_1_string(".sim", 4);
  string__76_9 = from_latin_1_string("Expected \042.sim\042 file extension in source filename!", 50);
  func__76_8 = create_function(entry__76_8, 0);
  string__76_11 = from_latin_1_string(".sim", 4);
  func__76_1 = create_function(entry__76_1, 1);
  func__77_2 = create_function(entry__77_2, 2);
  func__77_1 = create_function(entry__77_1, 0);
  string__78_9 = from_latin_1_string("__", 2);
  string__78_11 = from_latin_1_string("__", 2);
  string__78_21 = from_latin_1_string("writing C-source", 16);
  func__78_20 = create_function(entry__78_20, 0);
  func__78_2 = create_function(entry__78_2, 2);
  func__78_1 = create_function(entry__78_1, 0);
  func__79_3 = create_function(entry__79_3, 2);
  string__79_18 = from_latin_1_string("list dependencies for ", 22);
  func__79_17 = create_function(entry__79_17, 0);
  func__79_16 = create_function(entry__79_16, 0);
  string__79_26 = from_latin_1_string("list dependencies for ", 22);
  func__79_24 = create_function(entry__79_24, 2);
  string__79_29 = from_latin_1_string("runtime/linker.c", 16);
  string__79_31 = from_latin_1_string("runtime/memory.c", 16);
  string__79_33 = from_latin_1_string("runtime/debugger.c", 18);
  func__79_23 = create_function(entry__79_23, 0);
  func__79_1 = create_function(entry__79_1, 0);
  string__80_3 = from_latin_1_string(".codeblocks", 11);
  string__80_8 = from_latin_1_string("The directory \042", 15);
  string__80_9 = from_latin_1_string("\042 already exists!\012", 18);
  string__80_13 = from_latin_1_string("build Code::Blocks project in ", 30);
  string__80_19 = from_latin_1_string(".sim", 4);
  string__80_24 = from_latin_1_string("../", 3);
  string__80_26 = from_latin_1_string("/", 1);
  string__80_27 = from_latin_1_string(".cbp", 4);
  string__80_30 = from_latin_1_string("<?xml version=\0421.0\042 encoding=\042UTF-8\042 standalone=\042yes\042 ?>\012<CodeBlocks_project_file>\012  <FileVersion major=\0421\042 minor=\0426\042 />\012  <Project>\012    <Option title=\042", 152);
  string__80_31 = from_latin_1_string("\042 />\012    <Option pch_mode=\0422\042 />\012    <Option compiler=\042gcc\042 />\012    <Build>\012      <Target title=\042debug\042>\012        <Option output=\042bin/debug/", 138);
  string__80_32 = from_latin_1_string("\042 prefix_auto=\0421\042 extension_auto=\0421\042 />\012        <Option object_output=\042obj/debug/\042 />\012        <Option type=\0421\042 />\012        <Option compiler=\042gcc\042 />\012        <Compiler>\012          <Add option=\042-g\042 />\012        </Compiler>\012      </Target>\012    </Build>\012    <Linker>\012", 259);
  string__80_36 = from_latin_1_string("      <Add library=\042", 20);
  string__80_37 = from_latin_1_string("\042 />\012", 5);
  string__80_41 = from_latin_1_string("\012    </Linker>\012    <Compiler>\012      <Add option=\042-Wall\042 />\012    </Compiler>\012    <Unit filename=\042", 95);
  string__80_42 = from_latin_1_string("runtime/common.h\042 />\012    <Unit filename=\042", 41);
  string__80_43 = from_latin_1_string("runtime/linker.h\042 />\012    <Unit filename=\042", 41);
  string__80_44 = from_latin_1_string("runtime/memory.c\042>\012      <Option compilerVar=\042CC\042 />\012    </Unit>\012    <Unit filename=\042", 85);
  string__80_45 = from_latin_1_string("runtime/debugger.c\042>\012      <Option compilerVar=\042CC\042 />\012    </Unit>\012    <Unit filename=\042", 87);
  string__80_46 = from_latin_1_string("runtime/linker.c\042>\012      <Option compilerVar=\042CC\042 />\012    </Unit>\012", 65);
  string__80_52 = from_latin_1_string("\012    <Unit filename=\042", 21);
  string__80_53 = from_latin_1_string("\042>\012      <Option compilerVar=\042CC\042 />\012    </Unit>\012", 49);
  string__80_57 = from_latin_1_string("    <Extensions>\012      <code_completion />\012      <debugger />\012    </Extensions>\012  </Project>\012</CodeBlocks_project_file>\012", 120);
  func__80_2 = create_function(entry__80_2, 2);
  func__80_1 = create_function(entry__80_1, 0);
  string__81_2 = from_latin_1_string("simrun", 6);
  string__81_5 = from_latin_1_string("Cannot run a directory!", 23);
  func__81_4 = create_function(entry__81_4, 0);
  func__81_7 = create_function(entry__81_7, 0);
  string__81_9 = from_latin_1_string("/VERSION", 8);
  string__81_21 = from_latin_1_string(".so.", 4);
  string__81_23 = from_latin_1_string("libsim-", 7);
  string__81_26 = from_latin_1_string("-", 1);
  string__81_27 = from_latin_1_string(".dll", 4);
  string__81_29 = from_latin_1_string("libsim-", 7);
  string__81_32 = from_latin_1_string("-", 1);
  string__81_33 = from_latin_1_string(".dylib", 6);
  string__81_35 = from_latin_1_string("libsim-", 7);
  string__81_38 = from_latin_1_string("libsim-", 7);
  string__81_39 = from_latin_1_string(".so", 3);
  string__81_41 = from_latin_1_string("linux", 5);
  string__81_42 = from_latin_1_string("cygwin", 6);
  string__81_43 = from_latin_1_string("darwin", 6);
  string__81_46 = from_latin_1_string("build library ", 14);
  func__81_58 = create_function(entry__81_58, 0);
  string__81_62 = from_latin_1_string("linking dynamic library", 23);
  func__81_61 = create_function(entry__81_61, 0);
  string__81_65 = from_latin_1_string("-Wl,-soname,libsim-", 19);
  string__81_66 = from_latin_1_string(".so.", 4);
  string__81_69 = from_latin_1_string("-shared", 7);
  string__81_70 = from_latin_1_string("-o", 2);
  string__81_76 = from_latin_1_string("-lsim-", 6);
  string__81_78 = from_latin_1_string("-shared", 7);
  string__81_79 = from_latin_1_string("-o", 2);
  string__81_84 = from_latin_1_string("-Wl,-install_name,libsim-", 25);
  string__81_85 = from_latin_1_string("-", 1);
  string__81_86 = from_latin_1_string(".dylib", 6);
  string__81_89 = from_latin_1_string("-lsim-", 6);
  string__81_91 = from_latin_1_string("-dynamiclib", 11);
  string__81_92 = from_latin_1_string("-o", 2);
  string__81_98 = from_latin_1_string("-shared", 7);
  string__81_99 = from_latin_1_string("-o", 2);
  string__81_103 = from_latin_1_string("linux", 5);
  string__81_104 = from_latin_1_string("cygwin", 6);
  string__81_105 = from_latin_1_string("darwin", 6);
  func__81_8 = create_function(entry__81_8, 0);
  func__81_1 = create_function(entry__81_1, 0);
  string__82_2 = from_latin_1_string(".c", 2);
  string__82_4 = from_latin_1_string(".o", 2);
  string__82_9 = from_latin_1_string("\042", 1);
  string__82_10 = from_latin_1_string("\042 does not exist!\012", 18);
  string__82_22 = from_latin_1_string("compiling runtime module ", 25);
  func__82_1 = create_function(entry__82_1, 1);
  string__84_14 = from_latin_1_string(" ", 1);
  string__84_23 = from_latin_1_string("0", 1);
  func__84_1 = create_function(entry__84_1, -1);
  string__85_9 = from_latin_1_string(" ", 1);
  string__85_13 = from_latin_1_string(" s", 2);
  string__85_17 = from_latin_1_string(": ", 2);
  string__85_18 = from_latin_1_string(" s", 2);
  func__85_1 = create_function(entry__85_1, -1);
  string__86_3 = from_latin_1_string("cygwin", 6);
  string__86_6 = from_latin_1_string(".exe", 4);
  string__86_11 = from_latin_1_string("build executable ", 17);
  string__86_13 = from_latin_1_string(".c", 2);
  string__86_15 = from_latin_1_string(".o", 2);
  string__86_29 = from_latin_1_string(".meta", 5);
  string__86_33 = from_latin_1_string("build main module ", 18);
  func__86_32 = create_function(entry__86_32, 0);
  func__86_35 = create_function(entry__86_35, 0);
  string__86_43 = from_latin_1_string("saving", 6);
  string__86_47 = from_latin_1_string("compiling", 9);
  string__86_64 = from_latin_1_string("runtime/linker", 14);
  string__86_65 = from_latin_1_string("runtime/memory", 14);
  string__86_66 = from_latin_1_string("runtime/debugger", 16);
  func__86_68 = create_function(entry__86_68, 1);
  func__86_63 = create_function(entry__86_63, 0);
  func__86_80 = create_function(entry__86_80, 0);
  string__86_85 = from_latin_1_string("/usr/lib/libprofiler.so.0", 25);
  string__86_90 = from_latin_1_string("linking static executable", 25);
  func__86_89 = create_function(entry__86_89, 0);
  string__86_92 = from_latin_1_string("runtime/linker.o", 16);
  string__86_93 = from_latin_1_string("runtime/memory.o", 16);
  string__86_94 = from_latin_1_string("runtime/debugger.o", 18);
  string__86_95 = from_latin_1_string("-o", 2);
  string__86_101 = from_latin_1_string("linking executable", 18);
  func__86_100 = create_function(entry__86_100, 0);
  string__86_103 = from_latin_1_string("linux", 5);
  string__86_106 = from_latin_1_string("-l:libsim.so.", 13);
  func__86_105 = create_function(entry__86_105, 0);
  string__86_109 = from_latin_1_string("-lsim-", 6);
  func__86_108 = create_function(entry__86_108, 0);
  string__86_112 = from_latin_1_string("-o", 2);
  string__86_120 = from_latin_1_string("simrun", 6);
  func__86_119 = create_function(entry__86_119, 0);
  string__86_127 = from_latin_1_string("./", 2);
  func__86_2 = create_function(entry__86_2, 2);
  func__86_1 = create_function(entry__86_1, 0);
  string__90_1 = from_latin_1_string("Copyright (C) 2020 by\012Dipl.-Ing. Michael Niederle\012\012This program is free software; you can redistribute it and/or modify\012it under the terms of the GNU General Public License, version 2, or\012(at your option) version 3.\012\012This program is distributed in the hope that it will be useful,\012but WITHOUT ANY WARRANTY; without even the implied warranty of\012MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the\012GNU General Public License for more details.\012\012For details of the GNU General Public License see the accompanying\012files GPLv2.txt and GLPv3.txt or\012http://www.gnu.org/licenses/gpl-2.0.html\012http://www.gnu.org/licenses/gpl-3.0.html\012or write to the\012Free Software Foundation, Inc.,\01251 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.\012", 742);
  string__95_1 = from_latin_1_string(".", 1);
  string__95_2 = from_latin_1_string(".", 1);
  string__95_3 = from_latin_1_string(".", 1);
  string__96_1 = from_latin_1_string("gcc", 3);
  string__97_1 = from_latin_1_string("mkdir", 5);
  string__98_1 = from_latin_1_string("SIMLIBPATH", 10);
  string__99_1 = from_latin_1_string("SIMDATAPATH", 11);
  func__100_2 = create_function(entry__100_2, 0);
  string__100_5 = from_latin_1_string("/usr/local/share/simplicity", 27);
  string__100_6 = from_latin_1_string("/usr/share/simplicity", 21);
  func__100_4 = create_function(entry__100_4, 0);
  func__101_2 = create_function(entry__101_2, 0);
  string__101_5 = from_latin_1_string("/usr/local/share/simplicity", 27);
  string__101_6 = from_latin_1_string("/usr/share/simplicity", 21);
  func__101_4 = create_function(entry__101_4, 0);
  string__103_1 = from_latin_1_string("bsd", 3);
  string__103_2 = from_latin_1_string("posix", 5);
  string__103_4 = from_latin_1_string("cygwin", 6);
  string__103_5 = from_latin_1_string("posix", 5);
  string__103_7 = from_latin_1_string("darwin", 6);
  string__103_8 = from_latin_1_string("posix", 5);
  string__103_10 = from_latin_1_string("linux", 5);
  string__103_11 = from_latin_1_string("posix", 5);
  string__103_13 = from_latin_1_string("posix", 5);
  string__103_14 = from_latin_1_string("all", 3);
  string__103_16 = from_latin_1_string("win", 3);
  string__103_17 = from_latin_1_string("all", 3);
  string__103_19 = from_latin_1_string("all", 3);
  func__105_1 = create_function(entry__105_1, 0);
  string__131_1 = from_latin_1_string("simrun", 6);
  string__131_6 = from_latin_1_string("Missing command line arguments!", 31);
  func__131_5 = create_function(entry__131_5, 0);
  func__131_3 = create_function(entry__131_3, 0);
  string__131_11 = from_latin_1_string("check-only", 10);
  string__131_12 = from_latin_1_string("do not compile; just check for syntax errors\012", 45);
  func__131_10 = create_function(entry__131_10, 0);
  string__131_14 = from_latin_1_string("dump-trees", 10);
  string__131_15 = from_latin_1_string("dump abstract syntax trees\012", 27);
  func__131_13 = create_function(entry__131_13, 0);
  string__131_17 = from_latin_1_string("pretty-print", 12);
  string__131_18 = from_latin_1_string("do not compile; just pretty print the source file\012", 50);
  func__131_16 = create_function(entry__131_16, 0);
  string__131_20 = from_latin_1_string("print-simplified-source", 23);
  string__131_21 = from_latin_1_string("do not generate a C-file; just print the simplified source text\012", 64);
  func__131_19 = create_function(entry__131_19, 0);
  string__131_23 = from_latin_1_string("print-c", 7);
  string__131_24 = from_latin_1_string("print C source code for a single module\012", 40);
  func__131_22 = create_function(entry__131_22, 0);
  string__131_26 = from_latin_1_string("time-passes", 11);
  string__131_27 = from_latin_1_string("print running time for the individual compiler passes\012", 54);
  func__131_25 = create_function(entry__131_25, 0);
  string__131_29 = from_latin_1_string("module-prefix", 13);
  string__131_30 = from_latin_1_string("needed to compile a single file within a subdirectory;\012if the subdirectories are nested use slashes to separate\012the directory names\012", 132);
  func__131_28 = create_function(entry__131_28, 0);
  string__131_32 = from_latin_1_string("brief", 5);
  string__131_33 = from_latin_1_string("show brief error messages\012", 26);
  func__131_31 = create_function(entry__131_31, 0);
  string__131_35 = from_latin_1_string("warnings", 8);
  string__131_36 = from_latin_1_string("show warning messages\012", 22);
  func__131_34 = create_function(entry__131_34, 0);
  string__131_38 = from_latin_1_string("verbose", 7);
  string__131_39 = from_latin_1_string("output verbose informations\012", 28);
  func__131_37 = create_function(entry__131_37, 0);
  string__131_41 = from_latin_1_string("debug", 5);
  string__131_42 = from_latin_1_string("show C-compiler and linker calls\012", 33);
  func__131_40 = create_function(entry__131_40, 0);
  string__131_44 = from_latin_1_string("debug_compiler", 14);
  string__131_45 = from_latin_1_string("show internal debug messages of the Simplicity compiler\012", 56);
  func__131_43 = create_function(entry__131_43, 0);
  string__131_47 = from_latin_1_string("codeblocks", 10);
  string__131_48 = from_latin_1_string("create Code::Blocks project\012", 28);
  func__131_46 = create_function(entry__131_46, 0);
  string__131_50 = from_latin_1_string("extract-documentation", 21);
  string__131_51 = from_latin_1_string("extract documentation encoded as HTML\012", 38);
  func__131_49 = create_function(entry__131_49, 0);
  string__131_53 = from_latin_1_string("list-dependencies", 17);
  string__131_54 = from_latin_1_string("list all dependencies\012", 22);
  func__131_52 = create_function(entry__131_52, 0);
  string__131_56 = from_latin_1_string("goto", 4);
  string__131_57 = from_latin_1_string("the compiler uses goto-statements to link continuations\012", 56);
  func__131_55 = create_function(entry__131_55, 0);
  string__131_59 = from_latin_1_string("rebuild", 7);
  string__131_60 = from_latin_1_string("rebuild all source files\012", 25);
  func__131_58 = create_function(entry__131_58, 0);
  string__131_62 = from_latin_1_string("omit-meta", 9);
  string__131_63 = from_latin_1_string("do not rebuild meta files\012", 26);
  func__131_61 = create_function(entry__131_61, 0);
  string__131_65 = from_latin_1_string("static", 6);
  string__131_66 = from_latin_1_string("create statically linked executable\012", 36);
  func__131_64 = create_function(entry__131_64, 0);
  string__131_68 = from_latin_1_string("profile", 7);
  string__131_69 = from_latin_1_string("link with libprofiler\012", 22);
  func__131_67 = create_function(entry__131_67, 0);
  string__131_71 = from_latin_1_string("filename", 8);
  string__131_72 = from_latin_1_string("the name of the source file to compile\012", 39);
  func__131_70 = create_function(entry__131_70, 0);
  func__131_9 = create_function(entry__131_9, 0);
  func__135_1 = create_function(entry__135_1, 0);
  string__141_1 = from_latin_1_string("-Wall", 5);
  string__141_2 = from_latin_1_string("-Wno-unused-function", 20);
  string__141_3 = from_latin_1_string("-Wno-unused-variable", 20);
  string__141_4 = from_latin_1_string("-Wno-parentheses", 16);
  string__141_5 = from_latin_1_string("-Wno-switch", 11);
  string__141_6 = from_latin_1_string("-Wno-maybe-uninitialized", 24);
  string__141_7 = from_latin_1_string("-Wno-trigraphs", 14);
  string__141_8 = from_latin_1_string("-O1", 3);
  string__141_9 = from_latin_1_string("-fno-stack-protector", 20);
  string__141_10 = from_latin_1_string("-falign-functions=16", 20);
  string__142_1 = from_latin_1_string("-msse2", 6);
  string__142_2 = from_latin_1_string("-mfpmath=sse", 12);
  string__142_4 = from_latin_1_string("x86_32", 6);
  string__142_6 = from_latin_1_string("-msse2", 6);
  string__142_7 = from_latin_1_string("-mfpmath=sse", 12);
  string__142_9 = from_latin_1_string("x86_64", 6);
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
  var._gcc = create_future();
  var._mkdir = create_future();
  var._SIMLIBPATH = create_future();
  var._SIMDATAPATH = create_future();
  var._simlibpaths = create_future();
  var._simdatapaths = create_future();
  unique__13_1 = register_unique_item("NONE");
  assign_value(&var._NONE, unique__13_1);
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
  unique__48_1 = register_unique_item("EXE");
  assign_value(&var._EXE, unique__48_1);
  unique__49_1 = register_unique_item("LIB");
  assign_value(&var._LIB, unique__49_1);
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
  assign_variable(&var.sim2c__show_compiler_debug_info, &func__47_1);
  maybe_initialize_future(get__mode(), get__undefined());
  maybe_initialize_future(get__on_top_level(), get__true());
  assign_variable(&var._resolve_filename, &func__63_1);
  assign_variable(&var._add_module_infos, &func__64_1);
  assign_variable(&var._lookup, &func__65_1);
  assign_variable(&var._Gcc, &func__66_1);
  assign_variable(&var._compile_c, &func__67_1);
  assign_variable(&var._compile_meta_module, &func__68_1);
  assign_variable(&var._build_dependencies, &func__69_1);
  assign_variable(&var._compile_module, &func__70_1);
  assign_variable(&var._compile_modules, &func__71_1);
  assign_variable(&var._show_file_list, &func__73_1);
  assign_variable(&var._library_paths_and_file_list, &func__74_1);
  assign_variable(&var._create_imports, &func__75_1);
  assign_variable(&var._compile_exe, &func__76_1);
  assign_variable(&var._dump_source_or_check, &func__77_1);
  assign_variable(&var._print_c, &func__78_1);
  assign_variable(&var._list_dependencies, &func__79_1);
  assign_variable(&var._build_codeblocks_project, &func__80_1);
  assign_variable(&var._build_library, &func__81_1);
  assign_variable(&var._maybe_compile_c_file, &func__82_1);
  assign_variable(&var._format_number, &func__84_1);
  assign_variable(&var.sim2c__write_timing_info, &func__85_1);
  assign_variable(&var._build_executable, &func__86_1);
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
