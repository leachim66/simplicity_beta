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
static NODE_GETTER get__CPPFLAGS;
static NODE_GETTER get_value_or_future__CPPFLAGS;
static NODE_GETTER get__Error;
static NODE_GETTER get_value_or_future__Error;
static NODE_GETTER get__LDFLAGS;
static NODE_GETTER get_value_or_future__LDFLAGS;
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
  NODE *_cc_options;
  NODE *_cpp_options;
  NODE *_ld_options;
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
  NODE *sim2c__do_print_missing;
  NODE *sim2c__do_print_summary;
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
  "cc_options",
  "cpp_options",
  "ld_options",
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
static NODE *get__sim2c__do_print_missing(void) {
  return var.sim2c__do_print_missing;
}
static void set__sim2c__do_print_missing(NODE *val) {
  var.sim2c__do_print_missing = val;
}
static NODE *get__sim2c__do_print_summary(void) {
  return var.sim2c__do_print_summary;
}
static void set__sim2c__do_print_summary(NODE *val) {
  var.sim2c__do_print_summary = val;
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
static NODE *func__69_1_resolve_filename;
static void entry__69_1_resolve_filename(void);
static FRAME_INFO frame__69_1_resolve_filename = {3, {"filename", "libname", "libpath"}};
static void cont__69_2(void);
static NODE *func__69_3;
static void entry__69_3(void);
static FRAME_INFO frame__69_3 = {0, {}};
static NODE *func__69_4;
static void entry__69_4(void);
static FRAME_INFO frame__69_4 = {1, {"path"}};
static void cont__69_5(void);
static NODE *func__69_6;
static void entry__69_6(void);
static FRAME_INFO frame__69_6 = {1, {"path"}};
static void cont__69_7(void);
static NODE *func__69_8;
static void entry__69_8(void);
static FRAME_INFO frame__69_8 = {1, {"entry"}};
static void cont__69_9(void);
static NODE *func__69_10;
static void entry__69_10(void);
static FRAME_INFO frame__69_10 = {2, {"entry", "name"}};
static void cont__69_11(void);
static void cont__69_12(void);
static NODE *func__69_13;
static void entry__69_13(void);
static FRAME_INFO frame__69_13 = {2, {"name", "entry"}};
static void cont__69_14(void);
static void cont__69_15(void);
static void cont__69_16(void);
static void cont__69_17(void);
static void cont__69_18(void);
static void cont__69_19(void);
static NODE *func__69_20;
static void entry__69_20(void);
static FRAME_INFO frame__69_20 = {1, {"libname"}};
static NODE *string__69_21;
static NODE *string__69_22;
static void cont__69_23(void);
static void cont__69_24(void);
static void cont__69_25(void);
static void cont__69_26(void);
static NODE *func__70_1_add_module_infos;
static void entry__70_1_add_module_infos(void);
static FRAME_INFO frame__70_1_add_module_infos = {7, {"path", "mod_path", "return", "entries", "filenames", "directories", "modules"}};
static void cont__70_2(void);
static void cont__70_3(void);
static NODE *func__70_4;
static void entry__70_4(void);
static FRAME_INFO frame__70_4 = {6, {"entry", "directories", "filenames", "modules", "mod_path", "name"}};
static void cont__70_5(void);
static NODE *func__70_6;
static void entry__70_6(void);
static FRAME_INFO frame__70_6 = {3, {"entry", "name", "directories"}};
static void cont__70_7(void);
static NODE *func__70_8;
static void entry__70_8(void);
static FRAME_INFO frame__70_8 = {2, {"name", "directories"}};
static void cont__70_9(void);
static NODE *func__70_10;
static void entry__70_10(void);
static FRAME_INFO frame__70_10 = {2, {"directories", "name"}};
static void cont__70_11(void);
static NODE *func__70_12;
static void entry__70_12(void);
static FRAME_INFO frame__70_12 = {4, {"name", "filenames", "modules", "mod_path"}};
static NODE *string__70_13;
static void cont__70_14(void);
static NODE *func__70_15;
static void entry__70_15(void);
static FRAME_INFO frame__70_15 = {9, {"name", "filenames", "modules", "mod_path", "submodule_name", "meta_level", "stored_level", "basename", "mod_name"}};
static NODE *string__70_16;
static void cont__70_17(void);
static void cont__70_18(void);
static void cont__70_19(void);
static void cont__70_20(void);
static void cont__70_21(void);
static void cont__70_22(void);
static void cont__70_23(void);
static void cont__70_24(void);
static void cont__70_25(void);
static void cont__70_26(void);
static void cont__70_27(void);
static NODE *func__70_28;
static void entry__70_28(void);
static FRAME_INFO frame__70_28 = {2, {"stored_level", "meta_level"}};
static void cont__70_29(void);
static void cont__70_30(void);
static NODE *func__70_31;
static void entry__70_31(void);
static FRAME_INFO frame__70_31 = {2, {"submodule_name", "meta_level"}};
static void cont__70_32(void);
static void cont__70_33(void);
static void cont__70_34(void);
static void cont__70_35(void);
static void cont__70_36(void);
static void cont__70_37(void);
static void cont__70_38(void);
static NODE *func__70_39;
static void entry__70_39(void);
static FRAME_INFO frame__70_39 = {3, {"filename", "filenames", "mod_path"}};
static void cont__70_40(void);
static NODE *func__70_41;
static void entry__70_41(void);
static FRAME_INFO frame__70_41 = {3, {"filename", "filenames", "mod_path"}};
static NODE *string__70_42;
static void cont__70_43(void);
static NODE *func__70_44;
static void entry__70_44(void);
static FRAME_INFO frame__70_44 = {9, {"filenames", "filename", "mod_path", "maybe_push_common", "name", "mod_name", "platform", "parent", "files"}};
static NODE *func__70_45_maybe_push_common;
static void entry__70_45_maybe_push_common(void);
static FRAME_INFO frame__70_45_maybe_push_common = {5, {"plat", "name", "filenames", "files", "common_name"}};
static NODE *string__70_46;
static void cont__70_47(void);
static void cont__70_48(void);
static NODE *func__70_49;
static void entry__70_49(void);
static FRAME_INFO frame__70_49 = {2, {"files", "common_name"}};
static void cont__70_50(void);
static void cont__70_51(void);
static void cont__70_52(void);
static void cont__70_53(void);
static void cont__70_54(void);
static void cont__70_55(void);
static void cont__70_56(void);
static NODE *func__70_57;
static void entry__70_57(void);
static FRAME_INFO frame__70_57 = {1, {"platform"}};
static NODE *string__70_58;
static NODE *string__70_59;
static void cont__70_60(void);
static void cont__70_61(void);
static void cont__70_62(void);
static void cont__70_63(void);
static NODE *func__70_64;
static void entry__70_64(void);
static FRAME_INFO frame__70_64 = {2, {"parent", "maybe_push_common"}};
static void cont__70_65(void);
static void cont__70_66(void);
static NODE *func__70_67;
static void entry__70_67(void);
static FRAME_INFO frame__70_67 = {2, {"maybe_push_common", "parent"}};
static void cont__70_68(void);
static void cont__70_69(void);
static void cont__70_70(void);
static void cont__70_71(void);
static void cont__70_72(void);
static void cont__70_73(void);
static void cont__70_74(void);
static void cont__70_75(void);
static void cont__70_76(void);
static NODE *func__70_77;
static void entry__70_77(void);
static FRAME_INFO frame__70_77 = {3, {"return", "directories", "modules"}};
static void cont__70_78(void);
static NODE *func__71_1_lookup;
static void entry__71_1_lookup(void);
static FRAME_INFO frame__71_1_lookup = {3, {"mod_filename", "mod_name", "info"}};
static void cont__71_2(void);
static void cont__71_3(void);
static NODE *func__71_4;
static void entry__71_4(void);
static FRAME_INFO frame__71_4 = {1, {"info"}};
static NODE *func__71_5;
static void entry__71_5(void);
static FRAME_INFO frame__71_5 = {2, {"mod_filename", "mod_name"}};
static void cont__71_6(void);
static void cont__71_7(void);
static void cont__71_8(void);
static void cont__71_9(void);
static void cont__71_10(void);
static void cont__71_11(void);
static NODE *func__72_1_CC;
static void entry__72_1_CC(void);
static FRAME_INFO frame__72_1_CC = {1, {"args"}};
static NODE *func__72_2;
static void entry__72_2(void);
static FRAME_INFO frame__72_2 = {1, {"args"}};
static void cont__72_3(void);
static void cont__72_4(void);
static void cont__72_5(void);
static NODE *func__73_1_compile_c;
static void entry__73_1_compile_c(void);
static FRAME_INFO frame__73_1_compile_c = {2, {"c_filename", "o_filename"}};
static NODE *func__73_2;
static void entry__73_2(void);
static FRAME_INFO frame__73_2 = {0, {}};
static void cont__73_3(void);
static NODE *func__73_4;
static void entry__73_4(void);
static FRAME_INFO frame__73_4 = {5, {"c_filename", "o_filename", "out", "err", "success"}};
static NODE *string__73_5;
static NODE *string__73_6;
static void cont__73_7(void);
static NODE *func__73_8;
static void entry__73_8(void);
static FRAME_INFO frame__73_8 = {2, {"c_filename", "err"}};
static void cont__73_9(void);
static NODE *string__73_10;
static NODE *string__73_11;
static void cont__73_12(void);
static void cont__73_13(void);
static NODE *func__74_1_compile_meta_module;
static void entry__74_1_compile_meta_module(void);
static FRAME_INFO frame__74_1_compile_meta_module = {3, {"mod_filename", "mod_name", "meta_level"}};
static NODE *func__74_2;
static void entry__74_2(void);
static FRAME_INFO frame__74_2 = {11, {"mod_filename", "meta_level", "meta_path", "filename", "meta_filename", "meta_c_filename", "sim_filename", "meta_info", "sim_info", "meta_c_info", "force_rebuild"}};
static void cont__74_3(void);
static void cont__74_4(void);
static void cont__74_5(void);
static void cont__74_6(void);
static void cont__74_7(void);
static void cont__74_8(void);
static NODE *string__74_9;
static void cont__74_10(void);
static void cont__74_11(void);
static void cont__74_12(void);
static void cont__74_13(void);
static void cont__74_14(void);
static void cont__74_15(void);
static void cont__74_16(void);
static NODE *func__74_17;
static void entry__74_17(void);
static FRAME_INFO frame__74_17 = {3, {"sim_info", "meta_c_info", "meta_info"}};
static void cont__74_18(void);
static NODE *func__74_19;
static void entry__74_19(void);
static FRAME_INFO frame__74_19 = {3, {"meta_c_info", "meta_info", "sim_info"}};
static void cont__74_20(void);
static NODE *func__74_21;
static void entry__74_21(void);
static FRAME_INFO frame__74_21 = {3, {"meta_c_info", "meta_info", "sim_info"}};
static void cont__74_22(void);
static void cont__74_23(void);
static void cont__74_24(void);
static NODE *func__74_25;
static void entry__74_25(void);
static FRAME_INFO frame__74_25 = {2, {"sim_info", "meta_c_info"}};
static void cont__74_26(void);
static void cont__74_27(void);
static void cont__74_28(void);
static void cont__74_29(void);
static void cont__74_30(void);
static void cont__74_31(void);
static void cont__74_32(void);
static NODE *func__74_33;
static void entry__74_33(void);
static FRAME_INFO frame__74_33 = {6, {"sim_info", "meta_c_filename", "force_rebuild", "meta_path", "modification_time", "meta_c_buf"}};
static void cont__74_34(void);
static void cont__74_35(void);
static NODE *func__74_36;
static void entry__74_36(void);
static FRAME_INFO frame__74_36 = {5, {"break", "meta_c_buf", "modification_time", "force_rebuild", "meta_path"}};
static NODE *func__74_37;
static void entry__74_37(void);
static FRAME_INFO frame__74_37 = {8, {"line", "modification_time", "force_rebuild", "break", "meta_path", "check", "command", "argument"}};
static NODE *func__74_38_check;
static void entry__74_38_check(void);
static FRAME_INFO frame__74_38_check = {5, {"data_filename", "modification_time", "force_rebuild", "break", "data_info"}};
static void cont__74_39(void);
static void cont__74_40(void);
static NODE *func__74_41;
static void entry__74_41(void);
static FRAME_INFO frame__74_41 = {2, {"modification_time", "data_info"}};
static void cont__74_42(void);
static void cont__74_43(void);
static void cont__74_44(void);
static NODE *func__74_45;
static void entry__74_45(void);
static FRAME_INFO frame__74_45 = {2, {"force_rebuild", "break"}};
static NODE *string__74_46;
static void cont__74_47(void);
static void cont__74_48(void);
static void cont__74_49(void);
static void cont__74_50(void);
static void cont__74_51(void);
static void cont__74_52(void);
static NODE *string__74_53;
static void cont__74_54(void);
static NODE *func__74_55;
static void entry__74_55(void);
static FRAME_INFO frame__74_55 = {3, {"argument", "check", "meta_path"}};
static NODE *string__74_56;
static void cont__74_57(void);
static NODE *func__74_58;
static void entry__74_58(void);
static FRAME_INFO frame__74_58 = {3, {"check", "meta_path", "argument"}};
static void cont__74_59(void);
static void cont__74_60(void);
static void cont__74_61(void);
static NODE *func__74_62;
static void entry__74_62(void);
static FRAME_INFO frame__74_62 = {2, {"check", "argument"}};
static NODE *func__74_63;
static void entry__74_63(void);
static FRAME_INFO frame__74_63 = {3, {"path", "check", "argument"}};
static void cont__74_64(void);
static void cont__74_65(void);
static void cont__74_66(void);
static NODE *func__74_67;
static void entry__74_67(void);
static FRAME_INFO frame__74_67 = {9, {"return__1", "meta_filename", "meta_path", "filename", "sim_filename", "orig_path", "out", "err", "success"}};
static void cont__74_68(void);
static void cont__74_69(void);
static void cont__74_70(void);
static void cont__74_71(void);
static void cont__74_72(void);
static void cont__74_73(void);
static NODE *func__74_74;
static void entry__74_74(void);
static FRAME_INFO frame__74_74 = {1, {"err"}};
static void cont__74_75(void);
static void cont__74_76(void);
static void cont__74_77(void);
static void cont__74_78(void);
static void cont__74_79(void);
static void cont__74_80(void);
static void cont__74_81(void);
static NODE *func__75_1_build_dependencies;
static void entry__75_1_build_dependencies(void);
static FRAME_INFO frame__75_1_build_dependencies = {5, {"mod_filename", "mod_name", "c_buf", "do_compile_c", "return"}};
static NODE *func__75_2;
static void entry__75_2(void);
static FRAME_INFO frame__75_2 = {7, {"line", "return", "mod_filename", "mod_name", "do_compile_c", "command", "argument"}};
static void cont__75_3(void);
static void cont__75_4(void);
static void cont__75_5(void);
static void cont__75_6(void);
static void cont__75_7(void);
static void cont__75_8(void);
static NODE *func__75_9;
static void entry__75_9(void);
static FRAME_INFO frame__75_9 = {4, {"argument", "mod_filename", "mod_name", "do_compile_c"}};
static void cont__75_10(void);
static NODE *func__75_11;
static void entry__75_11(void);
static FRAME_INFO frame__75_11 = {3, {"argument", "mod_filename", "mod_name"}};
static void cont__75_12(void);
static NODE *func__75_13;
static void entry__75_13(void);
static FRAME_INFO frame__75_13 = {4, {"argument", "mod_filename", "mod_name", "req_name"}};
static void cont__75_14(void);
static void cont__75_15(void);
static void cont__75_16(void);
static void cont__75_17(void);
static void cont__75_18(void);
static void cont__75_19(void);
static void cont__75_20(void);
static void cont__75_21(void);
static NODE *func__75_22;
static void entry__75_22(void);
static FRAME_INFO frame__75_22 = {2, {"argument", "do_compile_c"}};
static NODE *func__75_23;
static void entry__75_23(void);
static FRAME_INFO frame__75_23 = {0, {}};
static NODE *func__75_24;
static void entry__75_24(void);
static FRAME_INFO frame__75_24 = {0, {}};
static void cont__75_25(void);
static void cont__75_26(void);
static NODE *func__75_27;
static void entry__75_27(void);
static FRAME_INFO frame__75_27 = {1, {"argument"}};
static void cont__75_28(void);
static NODE *func__75_29;
static void entry__75_29(void);
static FRAME_INFO frame__75_29 = {2, {"do_compile_c", "argument"}};
static NODE *func__75_30;
static void entry__75_30(void);
static FRAME_INFO frame__75_30 = {1, {"argument"}};
static void cont__75_31(void);
static NODE *string__75_32;
static void cont__75_33(void);
static void cont__75_34(void);
static NODE *func__75_35;
static void entry__75_35(void);
static FRAME_INFO frame__75_35 = {2, {"do_compile_c", "argument"}};
static NODE *func__75_36;
static void entry__75_36(void);
static FRAME_INFO frame__75_36 = {1, {"argument"}};
static void cont__75_37(void);
static void cont__75_38(void);
static NODE *string__75_39;
static NODE *string__75_40;
static void cont__75_41(void);
static NODE *func__76_1_compile_module;
static void entry__76_1_compile_module(void);
static FRAME_INFO frame__76_1_compile_module = {6, {"mod_filename", "mod_name", "return", "compile_submodule", "mod_info", "o_filename"}};
static NODE *func__76_2_compile_submodule;
static void entry__76_2_compile_submodule(void);
static FRAME_INFO frame__76_2_compile_submodule = {11, {"submodule_names", "do_compile_c", "suffix", "mod_filename", "mod_name", "o_filename", "modification_time", "sim_filenames", "c_filename", "c_info", "c_buf"}};
static NODE *func__76_3;
static void entry__76_3(void);
static FRAME_INFO frame__76_3 = {8, {"submodule_name", "mod_filename", "sim_filenames", "modification_time", "meta_level", "submodule_filename", "sim_filename", "sim_info"}};
static void cont__76_4(void);
static void cont__76_5(void);
static void cont__76_6(void);
static void cont__76_7(void);
static void cont__76_8(void);
static NODE *func__76_9;
static void entry__76_9(void);
static FRAME_INFO frame__76_9 = {0, {}};
static void cont__76_10(void);
static void cont__76_11(void);
static NODE *func__76_12;
static void entry__76_12(void);
static FRAME_INFO frame__76_12 = {3, {"submodule_filename", "submodule_name", "meta_level"}};
static void cont__76_13(void);
static void cont__76_14(void);
static void cont__76_15(void);
static void cont__76_16(void);
static void cont__76_17(void);
static NODE *func__76_18;
static void entry__76_18(void);
static FRAME_INFO frame__76_18 = {1, {"sim_filename"}};
static NODE *string__76_19;
static void cont__76_20(void);
static void cont__76_21(void);
static void cont__76_22(void);
static NODE *func__76_23;
static void entry__76_23(void);
static FRAME_INFO frame__76_23 = {2, {"modification_time", "sim_info"}};
static void cont__76_24(void);
static void cont__76_25(void);
static void cont__76_26(void);
static NODE *func__76_27;
static void entry__76_27(void);
static FRAME_INFO frame__76_27 = {2, {"modification_time", "sim_info"}};
static void cont__76_28(void);
static void cont__76_29(void);
static void cont__76_30(void);
static void cont__76_31(void);
static NODE *func__76_32;
static void entry__76_32(void);
static FRAME_INFO frame__76_32 = {1, {"c_filename"}};
static void cont__76_33(void);
static void cont__76_34(void);
static NODE *func__76_35;
static void entry__76_35(void);
static FRAME_INFO frame__76_35 = {2, {"c_info", "modification_time"}};
static void cont__76_36(void);
static NODE *func__76_37;
static void entry__76_37(void);
static FRAME_INFO frame__76_37 = {2, {"c_info", "modification_time"}};
static void cont__76_38(void);
static void cont__76_39(void);
static void cont__76_40(void);
static void cont__76_41(void);
static NODE *func__76_42;
static void entry__76_42(void);
static FRAME_INFO frame__76_42 = {9, {"return__1", "mod_name", "suffix", "sim_filenames", "c_buf", "c_filename", "do_compile_c", "o_filename", "c_source"}};
static NODE *string__76_43;
static void cont__76_44(void);
static void cont__76_45(void);
static void cont__76_46(void);
static NODE *func__76_47;
static void entry__76_47(void);
static FRAME_INFO frame__76_47 = {1, {"suffix"}};
static NODE *string__76_48;
static void cont__76_49(void);
static NODE *func__76_50;
static void entry__76_50(void);
static FRAME_INFO frame__76_50 = {1, {"sim_filenames"}};
static void cont__76_51(void);
static NODE *func__76_52;
static void entry__76_52(void);
static FRAME_INFO frame__76_52 = {1, {"c_source"}};
static void cont__76_53(void);
static void cont__76_54(void);
static void cont__76_55(void);
static NODE *func__76_56;
static void entry__76_56(void);
static FRAME_INFO frame__76_56 = {2, {"c_filename", "o_filename"}};
static void cont__76_57(void);
static NODE *func__76_58;
static void entry__76_58(void);
static FRAME_INFO frame__76_58 = {6, {"c_buf", "c_filename", "o_filename", "c_info", "do_compile_c", "o_info"}};
static void cont__76_59(void);
static void cont__76_60(void);
static void cont__76_61(void);
static NODE *func__76_62;
static void entry__76_62(void);
static FRAME_INFO frame__76_62 = {2, {"o_info", "c_info"}};
static void cont__76_63(void);
static void cont__76_64(void);
static void cont__76_65(void);
static void cont__76_66(void);
static NODE *func__76_67;
static void entry__76_67(void);
static FRAME_INFO frame__76_67 = {3, {"do_compile_c", "c_filename", "o_filename"}};
static NODE *func__76_68;
static void entry__76_68(void);
static FRAME_INFO frame__76_68 = {2, {"c_filename", "o_filename"}};
static NODE *func__76_69;
static void entry__76_69(void);
static FRAME_INFO frame__76_69 = {1, {"o_info"}};
static void cont__76_70(void);
static NODE *func__76_71;
static void entry__76_71(void);
static FRAME_INFO frame__76_71 = {1, {"o_info"}};
static void cont__76_72(void);
static void cont__76_73(void);
static void cont__76_74(void);
static NODE *func__76_75;
static void entry__76_75(void);
static FRAME_INFO frame__76_75 = {1, {"o_info"}};
static void cont__76_76(void);
static void cont__76_77(void);
static void cont__76_78(void);
static void cont__76_79(void);
static NODE *func__76_80;
static void entry__76_80(void);
static FRAME_INFO frame__76_80 = {1, {"mod_name"}};
static NODE *string__76_81;
static NODE *string__76_82;
static void cont__76_83(void);
static void cont__76_84(void);
static NODE *string__76_85;
static void cont__76_86(void);
static void cont__76_87(void);
static void cont__76_88(void);
static void cont__76_89(void);
static void cont__76_90(void);
static NODE *func__76_91;
static void entry__76_91(void);
static FRAME_INFO frame__76_91 = {3, {"compile_submodule", "mod_name", "mod_filename"}};
static void cont__76_92(void);
static void cont__76_93(void);
static void cont__76_94(void);
static void cont__76_95(void);
static NODE *func__76_96;
static void entry__76_96(void);
static FRAME_INFO frame__76_96 = {1, {"mod_filename"}};
static void cont__76_97(void);
static void cont__76_98(void);
static NODE *func__76_99;
static void entry__76_99(void);
static FRAME_INFO frame__76_99 = {3, {"mod_info", "compile_submodule", "mod_filename"}};
static NODE *func__76_100;
static void entry__76_100(void);
static FRAME_INFO frame__76_100 = {4, {"mod_info", "compile_submodule", "best_platform", "best_priority"}};
static NODE *func__76_101;
static void entry__76_101(void);
static FRAME_INFO frame__76_101 = {5, {"platform", "filenames", "best_priority", "best_platform", "priority"}};
static void cont__76_102(void);
static void cont__76_103(void);
static NODE *func__76_104;
static void entry__76_104(void);
static FRAME_INFO frame__76_104 = {2, {"priority", "best_priority"}};
static void cont__76_105(void);
static void cont__76_106(void);
static NODE *func__76_107;
static void entry__76_107(void);
static FRAME_INFO frame__76_107 = {4, {"best_platform", "platform", "best_priority", "priority"}};
static void cont__76_108(void);
static NODE *func__76_109;
static void entry__76_109(void);
static FRAME_INFO frame__76_109 = {4, {"platform", "filenames", "compile_submodule", "best_platform"}};
static void cont__76_110(void);
static void cont__76_111(void);
static void cont__76_112(void);
static NODE *func__76_113;
static void entry__76_113(void);
static FRAME_INFO frame__76_113 = {3, {"mod_info", "mod_filename", "used_by"}};
static NODE *func__76_114;
static void entry__76_114(void);
static FRAME_INFO frame__76_114 = {6, {"supported_platform", "parent_platform", "mod_info", "used_by", "best_platform", "best_priority"}};
static NODE *func__76_115;
static void entry__76_115(void);
static FRAME_INFO frame__76_115 = {6, {"platform", "filenames", "supported_platform", "best_priority", "best_platform", "priority"}};
static void cont__76_116(void);
static void cont__76_117(void);
static NODE *func__76_118;
static void entry__76_118(void);
static FRAME_INFO frame__76_118 = {2, {"priority", "best_priority"}};
static void cont__76_119(void);
static void cont__76_120(void);
static NODE *func__76_121;
static void entry__76_121(void);
static FRAME_INFO frame__76_121 = {4, {"best_platform", "platform", "best_priority", "priority"}};
static void cont__76_122(void);
static void cont__76_123(void);
static NODE *func__76_124;
static void entry__76_124(void);
static FRAME_INFO frame__76_124 = {4, {"used_by", "best_platform", "supported_platform", "ub"}};
static void cont__76_125(void);
static void cont__76_126(void);
static void cont__76_127(void);
static void cont__76_128(void);
static void cont__76_129(void);
static NODE *func__76_130;
static void entry__76_130(void);
static FRAME_INFO frame__76_130 = {6, {"platform", "filenames", "mod_filename", "used_by", "dependency", "platforms"}};
static void cont__76_131(void);
static void cont__76_132(void);
static void cont__76_133(void);
static NODE *func__76_134;
static void entry__76_134(void);
static FRAME_INFO frame__76_134 = {2, {"platforms", "dependency"}};
static NODE *func__76_135;
static void entry__76_135(void);
static FRAME_INFO frame__76_135 = {2, {"plat", "dependency"}};
static NODE *string__76_136;
static void cont__76_137(void);
static void cont__76_138(void);
static void cont__76_139(void);
static void cont__76_140(void);
static NODE *func__77_1_compile_modules;
static void entry__77_1_compile_modules(void);
static FRAME_INFO frame__77_1_compile_modules = {4, {"path", "mod_path", "directories", "modules"}};
static void cont__77_2(void);
static void cont__77_3(void);
static NODE *func__77_4;
static void entry__77_4(void);
static FRAME_INFO frame__77_4 = {3, {"name", "path", "mod_path"}};
static void cont__77_5(void);
static void cont__77_6(void);
static void cont__77_7(void);
static NODE *func__77_8;
static void entry__77_8(void);
static FRAME_INFO frame__77_8 = {3, {"name", "path", "mod_path"}};
static void cont__77_9(void);
static void cont__77_10(void);
static NODE *func__79_1_show_file_list;
static void entry__79_1_show_file_list(void);
static FRAME_INFO frame__79_1_show_file_list = {0, {}};
static NODE *func__79_2;
static void entry__79_2(void);
static FRAME_INFO frame__79_2 = {1, {"path"}};
static NODE *string__79_3;
static void cont__79_4(void);
static void cont__79_5(void);
static NODE *func__79_6;
static void entry__79_6(void);
static FRAME_INFO frame__79_6 = {1, {"path"}};
static NODE *string__79_7;
static void cont__79_8(void);
static void cont__79_9(void);
static void cont__79_10(void);
static NODE *string__79_11;
static void cont__79_12(void);
static void cont__79_13(void);
static NODE *string__79_14;
static NODE *func__80_1_library_paths_and_file_list;
static void entry__80_1_library_paths_and_file_list(void);
static FRAME_INFO frame__80_1_library_paths_and_file_list = {4, {"library_paths", "object_files", "library_files", "paths"}};
static void cont__80_2(void);
static void cont__80_3(void);
static void cont__80_4(void);
static NODE *func__80_5;
static void entry__80_5(void);
static FRAME_INFO frame__80_5 = {2, {"paths", "library_paths"}};
static void cont__80_6(void);
static NODE *func__80_7;
static void entry__80_7(void);
static FRAME_INFO frame__80_7 = {2, {"path", "library_paths"}};
static NODE *string__80_8;
static void cont__80_9(void);
static void cont__80_10(void);
static void cont__80_11(void);
static NODE *func__80_12;
static void entry__80_12(void);
static FRAME_INFO frame__80_12 = {1, {"library_paths"}};
static void cont__80_13(void);
static NODE *string__80_14;
static void cont__80_15(void);
static NODE *func__80_16;
static void entry__80_16(void);
static FRAME_INFO frame__80_16 = {2, {"object", "object_files"}};
static void cont__80_17(void);
static void cont__80_18(void);
static NODE *func__80_19;
static void entry__80_19(void);
static FRAME_INFO frame__80_19 = {2, {"library", "library_files"}};
static void cont__80_20(void);
static NODE *func__80_21;
static void entry__80_21(void);
static FRAME_INFO frame__80_21 = {1, {"library"}};
static void cont__80_22(void);
static NODE *string__80_23;
static NODE *string__80_24;
static void cont__80_25(void);
static NODE *func__80_26;
static void entry__80_26(void);
static FRAME_INFO frame__80_26 = {1, {"library"}};
static NODE *string__80_27;
static NODE *string__80_28;
static void cont__80_29(void);
static NODE *func__80_30;
static void entry__80_30(void);
static FRAME_INFO frame__80_30 = {1, {"library"}};
static NODE *string__80_31;
static void cont__80_32(void);
static void cont__80_33(void);
static NODE *func__80_34;
static void entry__80_34(void);
static FRAME_INFO frame__80_34 = {1, {"library"}};
static void cont__80_35(void);
static NODE *func__80_36;
static void entry__80_36(void);
static FRAME_INFO frame__80_36 = {1, {"library"}};
static void cont__80_37(void);
static void cont__80_38(void);
static void cont__80_39(void);
static NODE *func__80_40;
static void entry__80_40(void);
static FRAME_INFO frame__80_40 = {1, {"library"}};
static void cont__80_41(void);
static void cont__80_42(void);
static void cont__80_43(void);
static void cont__80_44(void);
static void cont__80_45(void);
static void cont__80_46(void);
static NODE *func__81_1_create_imports;
static void entry__81_1_create_imports(void);
static FRAME_INFO frame__81_1_create_imports = {5, {"source", "already_checked", "collect_declarations", "imports", "first_part"}};
static NODE *func__81_2_collect_declarations;
static void entry__81_2_collect_declarations(void);
static FRAME_INFO frame__81_2_collect_declarations = {4, {"buf", "already_checked", "collect_declarations", "s"}};
static NODE *func__81_3;
static void entry__81_3(void);
static FRAME_INFO frame__81_3 = {6, {"idx", "chr", "s", "buf", "already_checked", "collect_declarations"}};
static void cont__81_4(void);
static NODE *func__81_5;
static void entry__81_5(void);
static FRAME_INFO frame__81_5 = {6, {"chr", "buf", "s", "idx", "already_checked", "collect_declarations"}};
static void cont__81_6(void);
static NODE *func__81_7;
static void entry__81_7(void);
static FRAME_INFO frame__81_7 = {1, {"chr"}};
static void cont__81_8(void);
static NODE *func__81_9;
static void entry__81_9(void);
static FRAME_INFO frame__81_9 = {1, {"chr"}};
static void cont__81_10(void);
static void cont__81_11(void);
static void cont__81_12(void);
static NODE *func__81_13;
static void entry__81_13(void);
static FRAME_INFO frame__81_13 = {6, {"buf", "s", "idx", "already_checked", "collect_declarations", "symbol"}};
static void cont__81_14(void);
static void cont__81_15(void);
static void cont__81_16(void);
static NODE *func__81_17;
static void entry__81_17(void);
static FRAME_INFO frame__81_17 = {4, {"already_checked", "symbol", "collect_declarations", "declaration"}};
static void cont__81_18(void);
static void cont__81_19(void);
static void cont__81_20(void);
static NODE *func__81_21;
static void entry__81_21(void);
static FRAME_INFO frame__81_21 = {3, {"declaration", "collect_declarations", "do_import"}};
static void cont__81_22(void);
static void cont__81_23(void);
static void cont__81_24(void);
static NODE *func__81_25;
static void entry__81_25(void);
static FRAME_INFO frame__81_25 = {1, {"declaration"}};
static NODE *string__81_26;
static void cont__81_27(void);
static void cont__81_28(void);
static NODE *func__81_29;
static void entry__81_29(void);
static FRAME_INFO frame__81_29 = {1, {"declaration"}};
static NODE *string__81_30;
static void cont__81_31(void);
static void cont__81_32(void);
static void cont__81_33(void);
static void cont__81_34(void);
static NODE *func__81_35;
static void entry__81_35(void);
static FRAME_INFO frame__81_35 = {2, {"declaration", "collect_declarations"}};
static void cont__81_36(void);
static void cont__81_37(void);
static NODE *func__81_38;
static void entry__81_38(void);
static FRAME_INFO frame__81_38 = {1, {"declaration"}};
static void cont__81_39(void);
static void cont__81_40(void);
static NODE *func__81_41;
static void entry__81_41(void);
static FRAME_INFO frame__81_41 = {2, {"collect_declarations", "declaration"}};
static void cont__81_42(void);
static NODE *func__81_43;
static void entry__81_43(void);
static FRAME_INFO frame__81_43 = {2, {"declaration", "collect_declarations"}};
static NODE *string__81_44;
static void cont__81_45(void);
static NODE *func__81_46;
static void entry__81_46(void);
static FRAME_INFO frame__81_46 = {2, {"declaration", "collect_declarations"}};
static void cont__81_47(void);
static void cont__81_48(void);
static NODE *func__81_49;
static void entry__81_49(void);
static FRAME_INFO frame__81_49 = {2, {"line", "collect_declarations"}};
static void cont__81_50(void);
static void cont__81_51(void);
static NODE *func__81_52;
static void entry__81_52(void);
static FRAME_INFO frame__81_52 = {2, {"collect_declarations", "declaration"}};
static void cont__81_53(void);
static NODE *func__81_54;
static void entry__81_54(void);
static FRAME_INFO frame__81_54 = {0, {}};
static NODE *string__81_55;
static void cont__81_56(void);
static NODE *func__81_57;
static void entry__81_57(void);
static FRAME_INFO frame__81_57 = {3, {"chr", "s", "idx"}};
static void cont__81_58(void);
static NODE *func__81_59;
static void entry__81_59(void);
static FRAME_INFO frame__81_59 = {1, {"chr"}};
static void cont__81_60(void);
static void cont__81_61(void);
static NODE *func__81_62;
static void entry__81_62(void);
static FRAME_INFO frame__81_62 = {2, {"s", "idx"}};
static NODE *func__81_63;
static void entry__81_63(void);
static FRAME_INFO frame__81_63 = {2, {"collect_declarations", "source"}};
static void cont__81_64(void);
static NODE *string__81_65;
static void cont__81_66(void);
static void cont__81_67(void);
static void cont__81_68(void);
static void cont__81_69(void);
static void cont__81_70(void);
static void cont__81_71(void);
static void cont__81_72(void);
static void cont__81_73(void);
static NODE *func__81_74;
static void entry__81_74(void);
static FRAME_INFO frame__81_74 = {0, {}};
static NODE *string__81_75;
static NODE *func__82_1_compile_exe;
static void entry__82_1_compile_exe(void);
static FRAME_INFO frame__82_1_compile_exe = {4, {"body", "return__1", "mod_filename", "mod_name"}};
static void cont__82_2(void);
static NODE *func__82_3;
static void entry__82_3(void);
static FRAME_INFO frame__82_3 = {0, {}};
static NODE *string__82_4;
static void cont__82_5(void);
static void cont__82_6(void);
static NODE *func__82_7;
static void entry__82_7(void);
static FRAME_INFO frame__82_7 = {0, {}};
static NODE *string__82_8;
static void cont__82_9(void);
static void cont__82_10(void);
static void cont__82_11(void);
static void cont__82_12(void);
static void cont__82_13(void);
static NODE *func__83_1_dump_source_or_check;
static void entry__83_1_dump_source_or_check(void);
static FRAME_INFO frame__83_1_dump_source_or_check = {0, {}};
static NODE *func__83_2;
static void entry__83_2(void);
static FRAME_INFO frame__83_2 = {3, {"mod_filename", "mod_name", "return__1"}};
static void cont__83_3(void);
static void cont__83_4(void);
static NODE *func__84_1_print_c;
static void entry__84_1_print_c(void);
static FRAME_INFO frame__84_1_print_c = {0, {}};
static NODE *func__84_2;
static void entry__84_2(void);
static FRAME_INFO frame__84_2 = {4, {"mod_filename", "mod_name", "c_source", "c_buf"}};
static void cont__84_3(void);
static NODE *func__84_4;
static void entry__84_4(void);
static FRAME_INFO frame__84_4 = {1, {"mod_name"}};
static void cont__84_5(void);
static void cont__84_6(void);
static void cont__84_7(void);
static NODE *func__84_8;
static void entry__84_8(void);
static FRAME_INFO frame__84_8 = {2, {"return__1", "mod_name"}};
static void cont__84_9(void);
static void cont__84_10(void);
static void cont__84_11(void);
static void cont__84_12(void);
static void cont__84_13(void);
static void cont__84_14(void);
static NODE *func__84_15;
static void entry__84_15(void);
static FRAME_INFO frame__84_15 = {1, {"c_source"}};
static void cont__84_16(void);
static void cont__84_17(void);
static NODE *func__84_18;
static void entry__84_18(void);
static FRAME_INFO frame__84_18 = {0, {}};
static NODE *string__84_19;
static NODE *func__85_1_list_dependencies;
static void entry__85_1_list_dependencies(void);
static FRAME_INFO frame__85_1_list_dependencies = {1, {"prefix_path"}};
static void cont__85_2(void);
static NODE *func__85_3;
static void entry__85_3(void);
static FRAME_INFO frame__85_3 = {4, {"supported_platform", "parent_platform", "platform", "priority"}};
static NODE *func__85_4;
static void entry__85_4(void);
static FRAME_INFO frame__85_4 = {4, {"break", "platform", "priority", "supported_platform"}};
static NODE *func__85_5;
static void entry__85_5(void);
static FRAME_INFO frame__85_5 = {5, {"platform", "break", "priority", "supported_platform", "plat"}};
static void cont__85_6(void);
static void cont__85_7(void);
static void cont__85_8(void);
static void cont__85_9(void);
static void cont__85_10(void);
static void cont__85_11(void);
static void cont__85_12(void);
static void cont__85_13(void);
static void cont__85_14(void);
static void cont__85_15(void);
static NODE *func__85_16;
static void entry__85_16(void);
static FRAME_INFO frame__85_16 = {1, {"return__1"}};
static NODE *func__85_17;
static void entry__85_17(void);
static FRAME_INFO frame__85_17 = {0, {}};
static NODE *string__85_18;
static void cont__85_19(void);
static void cont__85_20(void);
static void cont__85_21(void);
static void cont__85_22(void);
static NODE *func__85_23;
static void entry__85_23(void);
static FRAME_INFO frame__85_23 = {0, {}};
static NODE *func__85_24;
static void entry__85_24(void);
static FRAME_INFO frame__85_24 = {2, {"mod_filename", "mod_name"}};
static NODE *func__85_25;
static void entry__85_25(void);
static FRAME_INFO frame__85_25 = {1, {"mod_filename"}};
static void cont__85_26(void);
static void cont__85_27(void);
static NODE *string__85_28;
static void cont__85_29(void);
static NODE *string__85_30;
static void cont__85_31(void);
static NODE *string__85_32;
static void cont__85_33(void);
static void cont__85_34(void);
static NODE *func__85_35;
static void entry__85_35(void);
static FRAME_INFO frame__85_35 = {2, {"filename", "prefix_path"}};
static void cont__85_36(void);
static void cont__85_37(void);
static NODE *func__86_1_build_codeblocks_project;
static void entry__86_1_build_codeblocks_project(void);
static FRAME_INFO frame__86_1_build_codeblocks_project = {0, {}};
static NODE *func__86_2;
static void entry__86_2(void);
static FRAME_INFO frame__86_2 = {10, {"mod_filename", "mod_name", "codeblocks_path", "info", "basename", "prefix_path", "depth", "path_prefix", "cbp_filename", "buf"}};
static NODE *string__86_3;
static void cont__86_4(void);
static void cont__86_5(void);
static void cont__86_6(void);
static NODE *func__86_7;
static void entry__86_7(void);
static FRAME_INFO frame__86_7 = {1, {"codeblocks_path"}};
static NODE *string__86_8;
static NODE *string__86_9;
static void cont__86_10(void);
static void cont__86_11(void);
static NODE *func__86_12;
static void entry__86_12(void);
static FRAME_INFO frame__86_12 = {1, {"codeblocks_path"}};
static NODE *string__86_13;
static void cont__86_14(void);
static void cont__86_15(void);
static void cont__86_16(void);
static void cont__86_17(void);
static void cont__86_18(void);
static void cont__86_19(void);
static void cont__86_20(void);
static void cont__86_21(void);
static void cont__86_22(void);
static NODE *string__86_23;
static void cont__86_24(void);
static NODE *string__86_25;
static NODE *string__86_26;
static void cont__86_27(void);
static void cont__86_28(void);
static NODE *string__86_29;
static NODE *string__86_30;
static NODE *string__86_31;
static void cont__86_32(void);
static void cont__86_33(void);
static NODE *func__86_34;
static void entry__86_34(void);
static FRAME_INFO frame__86_34 = {2, {"filename", "buf"}};
static NODE *string__86_35;
static NODE *string__86_36;
static void cont__86_37(void);
static void cont__86_38(void);
static void cont__86_39(void);
static void cont__86_40(void);
static void cont__86_41(void);
static void cont__86_42(void);
static NODE *string__86_43;
static NODE *string__86_44;
static NODE *string__86_45;
static NODE *string__86_46;
static NODE *string__86_47;
static NODE *string__86_48;
static NODE *string__86_49;
static NODE *string__86_50;
static void cont__86_51(void);
static void cont__86_52(void);
static NODE *func__86_53;
static void entry__86_53(void);
static FRAME_INFO frame__86_53 = {4, {"filename", "prefix_path", "buf", "path_prefix"}};
static void cont__86_54(void);
static void cont__86_55(void);
static void cont__86_56(void);
static NODE *string__86_57;
static NODE *string__86_58;
static void cont__86_59(void);
static void cont__86_60(void);
static void cont__86_61(void);
static NODE *string__86_62;
static void cont__86_63(void);
static NODE *func__87_1_build_library;
static void entry__87_1_build_library(void);
static FRAME_INFO frame__87_1_build_library = {1, {"return__1"}};
static NODE *string__87_2;
static void cont__87_3(void);
static NODE *func__87_4;
static void entry__87_4(void);
static FRAME_INFO frame__87_4 = {0, {}};
static NODE *string__87_5;
static void cont__87_6(void);
static NODE *func__87_7;
static void entry__87_7(void);
static FRAME_INFO frame__87_7 = {0, {}};
static NODE *func__87_8;
static void entry__87_8(void);
static FRAME_INFO frame__87_8 = {5, {"version", "version_filename", "so_version", "base_filename", "lib_filename"}};
static NODE *string__87_9;
static void cont__87_10(void);
static void cont__87_11(void);
static NODE *func__87_12;
static void entry__87_12(void);
static FRAME_INFO frame__87_12 = {2, {"version", "version_filename"}};
static void cont__87_13(void);
static void cont__87_14(void);
static void cont__87_15(void);
static void cont__87_16(void);
static void cont__87_17(void);
static void cont__87_18(void);
static void cont__87_19(void);
static void cont__87_20(void);
static void cont__87_21(void);
static NODE *func__87_22;
static void entry__87_22(void);
static FRAME_INFO frame__87_22 = {2, {"base_filename", "version"}};
static void cont__87_23(void);
static NODE *string__87_24;
static void cont__87_25(void);
static NODE *func__87_26;
static void entry__87_26(void);
static FRAME_INFO frame__87_26 = {2, {"base_filename", "version"}};
static NODE *string__87_27;
static void cont__87_28(void);
static void cont__87_29(void);
static NODE *func__87_30;
static void entry__87_30(void);
static FRAME_INFO frame__87_30 = {2, {"base_filename", "version"}};
static NODE *string__87_31;
static void cont__87_32(void);
static void cont__87_33(void);
static NODE *func__87_34;
static void entry__87_34(void);
static FRAME_INFO frame__87_34 = {2, {"base_filename", "version"}};
static void cont__87_35(void);
static void cont__87_36(void);
static NODE *string__87_37;
static NODE *string__87_38;
static void cont__87_39(void);
static NODE *func__87_40;
static void entry__87_40(void);
static FRAME_INFO frame__87_40 = {1, {"lib_filename"}};
static NODE *string__87_41;
static void cont__87_42(void);
static void cont__87_43(void);
static void cont__87_44(void);
static void cont__87_45(void);
static NODE *func__87_46;
static void entry__87_46(void);
static FRAME_INFO frame__87_46 = {2, {"lib_filename", "info"}};
static void cont__87_47(void);
static void cont__87_48(void);
static NODE *func__87_49;
static void entry__87_49(void);
static FRAME_INFO frame__87_49 = {1, {"info"}};
static void cont__87_50(void);
static void cont__87_51(void);
static void cont__87_52(void);
static NODE *func__87_53;
static void entry__87_53(void);
static FRAME_INFO frame__87_53 = {0, {}};
static void cont__87_54(void);
static NODE *func__87_55;
static void entry__87_55(void);
static FRAME_INFO frame__87_55 = {3, {"base_filename", "so_version", "lib_filename"}};
static NODE *func__87_56;
static void entry__87_56(void);
static FRAME_INFO frame__87_56 = {0, {}};
static NODE *string__87_57;
static void cont__87_58(void);
static void cont__87_59(void);
static void cont__87_60(void);
static NODE *func__87_61;
static void entry__87_61(void);
static FRAME_INFO frame__87_61 = {6, {"base_filename", "so_version", "lib_filename", "out", "err", "success"}};
static NODE *string__87_62;
static void cont__87_63(void);
static void cont__87_64(void);
static NODE *string__87_65;
static void cont__87_66(void);
static NODE *func__87_67;
static void entry__87_67(void);
static FRAME_INFO frame__87_67 = {1, {"err"}};
static void cont__87_68(void);
static NODE *func__87_69;
static void entry__87_69(void);
static FRAME_INFO frame__87_69 = {4, {"lib_filename", "out", "err", "success"}};
static void cont__87_70(void);
static NODE *string__87_71;
static void cont__87_72(void);
static void cont__87_73(void);
static NODE *func__87_74;
static void entry__87_74(void);
static FRAME_INFO frame__87_74 = {1, {"err"}};
static void cont__87_75(void);
static NODE *func__87_76;
static void entry__87_76(void);
static FRAME_INFO frame__87_76 = {6, {"base_filename", "so_version", "lib_filename", "out", "err", "success"}};
static NODE *string__87_77;
static void cont__87_78(void);
static void cont__87_79(void);
static void cont__87_80(void);
static NODE *string__87_81;
static void cont__87_82(void);
static NODE *func__87_83;
static void entry__87_83(void);
static FRAME_INFO frame__87_83 = {1, {"err"}};
static void cont__87_84(void);
static NODE *func__87_85;
static void entry__87_85(void);
static FRAME_INFO frame__87_85 = {4, {"lib_filename", "out", "err", "success"}};
static void cont__87_86(void);
static void cont__87_87(void);
static NODE *func__87_88;
static void entry__87_88(void);
static FRAME_INFO frame__87_88 = {1, {"err"}};
static void cont__87_89(void);
static void cont__87_90(void);
static NODE *func__88_1_maybe_compile_c_file;
static void entry__88_1_maybe_compile_c_file(void);
static FRAME_INFO frame__88_1_maybe_compile_c_file = {5, {"filename", "c_filename", "o_filename", "c_info", "o_info"}};
static void cont__88_2(void);
static void cont__88_3(void);
static void cont__88_4(void);
static void cont__88_5(void);
static NODE *func__88_6;
static void entry__88_6(void);
static FRAME_INFO frame__88_6 = {1, {"c_filename"}};
static NODE *string__88_7;
static NODE *string__88_8;
static void cont__88_9(void);
static void cont__88_10(void);
static void cont__88_11(void);
static void cont__88_12(void);
static NODE *func__88_13;
static void entry__88_13(void);
static FRAME_INFO frame__88_13 = {2, {"o_info", "c_info"}};
static void cont__88_14(void);
static void cont__88_15(void);
static void cont__88_16(void);
static void cont__88_17(void);
static NODE *func__88_18;
static void entry__88_18(void);
static FRAME_INFO frame__88_18 = {3, {"filename", "c_filename", "o_filename"}};
static NODE *func__88_19;
static void entry__88_19(void);
static FRAME_INFO frame__88_19 = {1, {"filename"}};
static NODE *string__88_20;
static void cont__88_21(void);
static void cont__88_22(void);
static NODE *func__90_1_format_number;
static void entry__90_1_format_number(void);
static FRAME_INFO frame__90_1_format_number = {4, {"val", "n", "m", "ac"}};
static void cont__90_2(void);
static NODE *func__90_3;
static void entry__90_3(void);
static FRAME_INFO frame__90_3 = {4, {"break", "val", "ac", "n"}};
static NODE *func__90_4;
static void entry__90_4(void);
static FRAME_INFO frame__90_4 = {6, {"i", "chr", "ac", "val", "n", "break"}};
static void cont__90_5(void);
static NODE *func__90_6;
static void entry__90_6(void);
static FRAME_INFO frame__90_6 = {5, {"ac", "val", "i", "n", "break"}};
static void cont__90_7(void);
static void cont__90_8(void);
static void cont__90_9(void);
static void cont__90_10(void);
static NODE *func__90_11;
static void entry__90_11(void);
static FRAME_INFO frame__90_11 = {3, {"val", "n", "i"}};
static void cont__90_12(void);
static void cont__90_13(void);
static NODE *string__90_14;
static void cont__90_15(void);
static void cont__90_16(void);
static void cont__90_17(void);
static void cont__90_18(void);
static void cont__90_19(void);
static void cont__90_20(void);
static NODE *func__90_21;
static void entry__90_21(void);
static FRAME_INFO frame__90_21 = {3, {"val", "m", "ac"}};
static void cont__90_22(void);
static NODE *string__90_23;
static void cont__90_24(void);
static void cont__90_25(void);
static NODE *func__90_26;
static void entry__90_26(void);
static FRAME_INFO frame__90_26 = {3, {"m", "ac", "val"}};
static void cont__90_27(void);
static NODE *func__90_28;
static void entry__90_28(void);
static FRAME_INFO frame__90_28 = {3, {"val", "ac", "m"}};
static void cont__90_29(void);
static void cont__90_30(void);
static void cont__90_31(void);
static void cont__90_32(void);
static void cont__90_33(void);
static NODE *func__91_1_sim2c__write_timing_info;
static void entry__91_1_sim2c__write_timing_info(void);
static FRAME_INFO frame__91_1_sim2c__write_timing_info = {3, {"description", "filename", "new_t"}};
static void cont__91_2(void);
static void cont__91_3(void);
static NODE *func__91_4;
static void entry__91_4(void);
static FRAME_INFO frame__91_4 = {3, {"filename", "description", "new_t"}};
static void cont__91_5(void);
static void cont__91_6(void);
static void cont__91_7(void);
static void cont__91_8(void);
static void cont__91_9(void);
static void cont__91_10(void);
static void cont__91_11(void);
static NODE *string__91_12;
static NODE *func__91_13;
static void entry__91_13(void);
static FRAME_INFO frame__91_13 = {2, {"description", "new_t"}};
static void cont__91_14(void);
static void cont__91_15(void);
static NODE *string__91_16;
static void cont__91_17(void);
static void cont__91_18(void);
static NODE *get__sim2c__write_timing_info(void) {
  return var.sim2c__write_timing_info;
}
static NODE *func__92_1_build_executable;
static void entry__92_1_build_executable(void);
static FRAME_INFO frame__92_1_build_executable = {0, {}};
static NODE *func__92_2;
static void entry__92_2(void);
static FRAME_INFO frame__92_2 = {9, {"mod_filename", "mod_name", "exe_filename", "c_filename", "o_filename", "sim_info", "c_info", "c_buf", "zz"}};
static void cont__92_3(void);
static void cont__92_4(void);
static NODE *func__92_5;
static void entry__92_5(void);
static FRAME_INFO frame__92_5 = {1, {"mod_filename"}};
static NODE *string__92_6;
static void cont__92_7(void);
static NODE *func__92_8;
static void entry__92_8(void);
static FRAME_INFO frame__92_8 = {1, {"mod_filename"}};
static void cont__92_9(void);
static NODE *func__92_10;
static void entry__92_10(void);
static FRAME_INFO frame__92_10 = {1, {"exe_filename"}};
static NODE *string__92_11;
static void cont__92_12(void);
static void cont__92_13(void);
static void cont__92_14(void);
static void cont__92_15(void);
static void cont__92_16(void);
static void cont__92_17(void);
static NODE *func__92_18;
static void entry__92_18(void);
static FRAME_INFO frame__92_18 = {2, {"c_info", "sim_info"}};
static void cont__92_19(void);
static NODE *func__92_20;
static void entry__92_20(void);
static FRAME_INFO frame__92_20 = {2, {"c_info", "sim_info"}};
static void cont__92_21(void);
static void cont__92_22(void);
static void cont__92_23(void);
static void cont__92_24(void);
static void cont__92_25(void);
static NODE *func__92_26;
static void entry__92_26(void);
static FRAME_INFO frame__92_26 = {6, {"return__1", "mod_name", "c_buf", "c_filename", "o_filename", "c_source"}};
static void cont__92_27(void);
static void cont__92_28(void);
static NODE *func__92_29;
static void entry__92_29(void);
static FRAME_INFO frame__92_29 = {0, {}};
static NODE *string__92_30;
static void cont__92_31(void);
static NODE *func__92_32;
static void entry__92_32(void);
static FRAME_INFO frame__92_32 = {0, {}};
static void cont__92_33(void);
static void cont__92_34(void);
static NODE *func__92_35;
static void entry__92_35(void);
static FRAME_INFO frame__92_35 = {1, {"c_source"}};
static void cont__92_36(void);
static void cont__92_37(void);
static void cont__92_38(void);
static NODE *func__92_39;
static void entry__92_39(void);
static FRAME_INFO frame__92_39 = {1, {"c_filename"}};
static NODE *string__92_40;
static void cont__92_41(void);
static void cont__92_42(void);
static NODE *func__92_43;
static void entry__92_43(void);
static FRAME_INFO frame__92_43 = {1, {"c_filename"}};
static NODE *string__92_44;
static void cont__92_45(void);
static NODE *func__92_46;
static void entry__92_46(void);
static FRAME_INFO frame__92_46 = {5, {"c_buf", "c_filename", "o_filename", "c_info", "o_info"}};
static void cont__92_47(void);
static void cont__92_48(void);
static void cont__92_49(void);
static NODE *func__92_50;
static void entry__92_50(void);
static FRAME_INFO frame__92_50 = {2, {"o_info", "c_info"}};
static void cont__92_51(void);
static void cont__92_52(void);
static void cont__92_53(void);
static void cont__92_54(void);
static NODE *func__92_55;
static void entry__92_55(void);
static FRAME_INFO frame__92_55 = {2, {"c_filename", "o_filename"}};
static NODE *func__92_56;
static void entry__92_56(void);
static FRAME_INFO frame__92_56 = {1, {"o_info"}};
static void cont__92_57(void);
static void cont__92_58(void);
static void cont__92_59(void);
static NODE *func__92_60;
static void entry__92_60(void);
static FRAME_INFO frame__92_60 = {0, {}};
static NODE *string__92_61;
static NODE *string__92_62;
static NODE *string__92_63;
static void cont__92_64(void);
static NODE *func__92_65;
static void entry__92_65(void);
static FRAME_INFO frame__92_65 = {1, {"filename"}};
static void cont__92_66(void);
static NODE *func__92_67;
static void entry__92_67(void);
static FRAME_INFO frame__92_67 = {2, {"exe_filename", "info"}};
static void cont__92_68(void);
static void cont__92_69(void);
static NODE *func__92_70;
static void entry__92_70(void);
static FRAME_INFO frame__92_70 = {1, {"info"}};
static void cont__92_71(void);
static NODE *func__92_72;
static void entry__92_72(void);
static FRAME_INFO frame__92_72 = {1, {"info"}};
static void cont__92_73(void);
static void cont__92_74(void);
static void cont__92_75(void);
static void cont__92_76(void);
static NODE *func__92_77;
static void entry__92_77(void);
static FRAME_INFO frame__92_77 = {0, {}};
static void cont__92_78(void);
static NODE *func__92_79;
static void entry__92_79(void);
static FRAME_INFO frame__92_79 = {2, {"exe_filename", "libs_and_files"}};
static void cont__92_80(void);
static NODE *func__92_81;
static void entry__92_81(void);
static FRAME_INFO frame__92_81 = {1, {"libs_and_files"}};
static NODE *string__92_82;
static void cont__92_83(void);
static void cont__92_84(void);
static NODE *func__92_85;
static void entry__92_85(void);
static FRAME_INFO frame__92_85 = {5, {"libs_and_files", "exe_filename", "out", "err", "success"}};
static NODE *func__92_86;
static void entry__92_86(void);
static FRAME_INFO frame__92_86 = {0, {}};
static NODE *string__92_87;
static void cont__92_88(void);
static NODE *string__92_89;
static NODE *string__92_90;
static NODE *string__92_91;
static void cont__92_92(void);
static NODE *func__92_93;
static void entry__92_93(void);
static FRAME_INFO frame__92_93 = {1, {"err"}};
static void cont__92_94(void);
static NODE *func__92_95;
static void entry__92_95(void);
static FRAME_INFO frame__92_95 = {5, {"libs_and_files", "exe_filename", "out", "err", "success"}};
static NODE *func__92_96;
static void entry__92_96(void);
static FRAME_INFO frame__92_96 = {0, {}};
static NODE *string__92_97;
static void cont__92_98(void);
static void cont__92_99(void);
static void cont__92_100(void);
static NODE *func__92_101;
static void entry__92_101(void);
static FRAME_INFO frame__92_101 = {0, {}};
static NODE *string__92_102;
static void cont__92_103(void);
static NODE *func__92_104;
static void entry__92_104(void);
static FRAME_INFO frame__92_104 = {0, {}};
static void cont__92_105(void);
static void cont__92_106(void);
static void cont__92_107(void);
static NODE *func__92_108;
static void entry__92_108(void);
static FRAME_INFO frame__92_108 = {1, {"err"}};
static void cont__92_109(void);
static void cont__92_110(void);
static void cont__92_111(void);
static void cont__92_112(void);
static NODE *func__92_113;
static void entry__92_113(void);
static FRAME_INFO frame__92_113 = {0, {}};
static void cont__92_114(void);
static void cont__92_115(void);
static NODE *func__92_116;
static void entry__92_116(void);
static FRAME_INFO frame__92_116 = {2, {"exe_filename", "zz"}};
static void cont__92_117(void);
static NODE *func__92_118;
static void entry__92_118(void);
static FRAME_INFO frame__92_118 = {1, {"exe_filename"}};
static NODE *func__92_119;
static void entry__92_119(void);
static FRAME_INFO frame__92_119 = {1, {"exe_filename"}};
static void cont__92_120(void);
static void cont__92_121(void);
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
static NODE *string__96_1;
static void cont__96_2(void);
static void cont__97_1(void);
static void cont__98_1(void);
static void cont__99_1(void);
static NODE *string__100_1;
static void cont__100_2(void);
static void cont__101_1(void);
static void cont__102_1(void);
static void cont__102_2(void);
static NODE *string__103_1;
static void cont__103_2(void);
static NODE *string__104_1;
static void cont__104_2(void);
static NODE *string__105_1;
static void cont__105_2(void);
static void cont__106_1(void);
static NODE *func__106_2;
static void entry__106_2(void);
static FRAME_INFO frame__106_2 = {0, {}};
static void cont__106_3(void);
static NODE *func__106_4;
static void entry__106_4(void);
static FRAME_INFO frame__106_4 = {0, {}};
static NODE *string__106_5;
static void cont__106_6(void);
static NODE *string__106_7;
static void cont__106_8(void);
static void cont__106_9(void);
static void cont__106_10(void);
static void cont__107_1(void);
static NODE *func__107_2;
static void entry__107_2(void);
static FRAME_INFO frame__107_2 = {0, {}};
static void cont__107_3(void);
static NODE *func__107_4;
static void entry__107_4(void);
static FRAME_INFO frame__107_4 = {0, {}};
static void cont__107_5(void);
static void cont__107_6(void);
static void cont__107_7(void);
static void cont__107_8(void);
static NODE *string__109_1;
static void cont__109_2(void);
static void cont__109_3(void);
static void cont__109_4(void);
static void cont__109_5(void);
static NODE *string__109_6;
static void cont__109_7(void);
static NODE *string__109_8;
static void cont__109_9(void);
static void cont__109_10(void);
static void cont__109_11(void);
static NODE *func__111_1;
static void entry__111_1(void);
static FRAME_INFO frame__111_1 = {2, {"platform", "priority"}};
static void cont__111_2(void);
static NODE *func__111_3;
static void entry__111_3(void);
static FRAME_INFO frame__111_3 = {3, {"break", "platform", "priority"}};
static NODE *func__111_4;
static void entry__111_4(void);
static FRAME_INFO frame__111_4 = {4, {"platform", "break", "priority", "plat"}};
static void cont__111_5(void);
static void cont__111_6(void);
static void cont__111_7(void);
static void cont__111_8(void);
static void cont__111_9(void);
static void cont__111_10(void);
static void cont__111_11(void);
static void cont__111_12(void);
static void cont__111_13(void);
static void cont__137_1(void);
static void cont__137_2(void);
static void cont__137_3(void);
static void cont__138_1(void);
static NODE *func__138_2;
static void entry__138_2(void);
static FRAME_INFO frame__138_2 = {0, {}};
static void cont__138_3(void);
static NODE *func__138_4;
static void entry__138_4(void);
static FRAME_INFO frame__138_4 = {0, {}};
static NODE *string__138_5;
static void cont__138_6(void);
static void cont__138_7(void);
static NODE *func__138_8;
static void entry__138_8(void);
static FRAME_INFO frame__138_8 = {0, {}};
static NODE *func__138_9;
static void entry__138_9(void);
static FRAME_INFO frame__138_9 = {0, {}};
static NODE *string__138_10;
static NODE *string__138_11;
static NODE *func__138_12;
static void entry__138_12(void);
static FRAME_INFO frame__138_12 = {0, {}};
static NODE *string__138_13;
static NODE *string__138_14;
static NODE *func__138_15;
static void entry__138_15(void);
static FRAME_INFO frame__138_15 = {0, {}};
static NODE *string__138_16;
static NODE *string__138_17;
static NODE *func__138_18;
static void entry__138_18(void);
static FRAME_INFO frame__138_18 = {0, {}};
static NODE *string__138_19;
static NODE *string__138_20;
static NODE *func__138_21;
static void entry__138_21(void);
static FRAME_INFO frame__138_21 = {0, {}};
static NODE *string__138_22;
static NODE *string__138_23;
static NODE *func__138_24;
static void entry__138_24(void);
static FRAME_INFO frame__138_24 = {0, {}};
static NODE *string__138_25;
static NODE *string__138_26;
static NODE *func__138_27;
static void entry__138_27(void);
static FRAME_INFO frame__138_27 = {0, {}};
static NODE *string__138_28;
static NODE *string__138_29;
static NODE *func__138_30;
static void entry__138_30(void);
static FRAME_INFO frame__138_30 = {0, {}};
static NODE *string__138_31;
static NODE *string__138_32;
static NODE *func__138_33;
static void entry__138_33(void);
static FRAME_INFO frame__138_33 = {0, {}};
static NODE *string__138_34;
static NODE *string__138_35;
static NODE *func__138_36;
static void entry__138_36(void);
static FRAME_INFO frame__138_36 = {0, {}};
static NODE *string__138_37;
static NODE *string__138_38;
static NODE *func__138_39;
static void entry__138_39(void);
static FRAME_INFO frame__138_39 = {0, {}};
static NODE *string__138_40;
static NODE *string__138_41;
static NODE *func__138_42;
static void entry__138_42(void);
static FRAME_INFO frame__138_42 = {0, {}};
static NODE *string__138_43;
static NODE *string__138_44;
static NODE *func__138_45;
static void entry__138_45(void);
static FRAME_INFO frame__138_45 = {0, {}};
static NODE *string__138_46;
static NODE *string__138_47;
static NODE *func__138_48;
static void entry__138_48(void);
static FRAME_INFO frame__138_48 = {0, {}};
static NODE *string__138_49;
static NODE *string__138_50;
static NODE *func__138_51;
static void entry__138_51(void);
static FRAME_INFO frame__138_51 = {0, {}};
static NODE *string__138_52;
static NODE *string__138_53;
static NODE *func__138_54;
static void entry__138_54(void);
static FRAME_INFO frame__138_54 = {0, {}};
static NODE *string__138_55;
static NODE *string__138_56;
static NODE *func__138_57;
static void entry__138_57(void);
static FRAME_INFO frame__138_57 = {0, {}};
static NODE *string__138_58;
static NODE *string__138_59;
static NODE *func__138_60;
static void entry__138_60(void);
static FRAME_INFO frame__138_60 = {0, {}};
static NODE *string__138_61;
static NODE *string__138_62;
static NODE *func__138_63;
static void entry__138_63(void);
static FRAME_INFO frame__138_63 = {0, {}};
static NODE *string__138_64;
static NODE *string__138_65;
static NODE *func__138_66;
static void entry__138_66(void);
static FRAME_INFO frame__138_66 = {0, {}};
static NODE *string__138_67;
static NODE *string__138_68;
static NODE *func__138_69;
static void entry__138_69(void);
static FRAME_INFO frame__138_69 = {0, {}};
static NODE *string__138_70;
static NODE *string__138_71;
static NODE *func__138_72;
static void entry__138_72(void);
static FRAME_INFO frame__138_72 = {0, {}};
static NODE *string__138_73;
static NODE *string__138_74;
static void cont__138_75(void);
static void cont__138_76(void);
static void cont__139_1(void);
static void cont__140_1(void);
static NODE *func__142_1;
static void entry__142_1(void);
static FRAME_INFO frame__142_1 = {0, {}};
static void cont__142_2(void);
static void cont__147_1(void);
static NODE *string__148_1;
static NODE *string__148_2;
static NODE *string__148_3;
static NODE *string__148_4;
static NODE *string__148_5;
static NODE *string__148_6;
static NODE *string__148_7;
static NODE *string__148_8;
static NODE *string__148_9;
static NODE *string__148_10;
static void cont__148_11(void);
static void cont__149_1(void);
static NODE *string__149_2;
static void cont__149_3(void);
static NODE *func__149_4;
static void entry__149_4(void);
static FRAME_INFO frame__149_4 = {0, {}};
static NODE *string__149_5;
static void cont__149_6(void);
static void cont__149_7(void);
static void cont__150_1(void);
static NODE *string__150_2;
static NODE *string__150_3;
static void cont__150_4(void);
static NODE *func__150_5;
static void entry__150_5(void);
static FRAME_INFO frame__150_5 = {0, {}};
static NODE *string__150_6;
static void cont__150_7(void);
static NODE *string__150_8;
static void cont__150_9(void);
static void cont__150_10(void);
static NODE *func__151_1;
static void entry__151_1(void);
static FRAME_INFO frame__151_1 = {1, {"path"}};
static NODE *string__151_2;
static void cont__151_3(void);
static void cont__151_4(void);
static void cont__151_5(void);
static void cont__153_1(void);
static void cont__153_2(void);
static NODE *func__153_3;
static void entry__153_3(void);
static FRAME_INFO frame__153_3 = {1, {"option"}};
static void cont__153_4(void);
static void cont__153_5(void);
static void cont__155_1(void);
static void cont__155_2(void);
static NODE *func__155_3;
static void entry__155_3(void);
static FRAME_INFO frame__155_3 = {1, {"option"}};
static void cont__155_4(void);
static void cont__155_5(void);
static void cont__173_1(void);
static NODE *func__173_2;
static void entry__173_2(void);
static FRAME_INFO frame__173_2 = {0, {}};
static NODE *string__173_3;
static NODE *string__173_4;
static void cont__173_5(void);
static void cont__173_6(void);
static NODE *func__188_1;
static void entry__188_1(void);
static FRAME_INFO frame__188_1 = {0, {}};
static void cont__188_2(void);
static void cont__188_3(void);
static NODE *func__189_1;
static void entry__189_1(void);
static FRAME_INFO frame__189_1 = {0, {}};
static NODE *func__189_2;
static void entry__189_2(void);
static FRAME_INFO frame__189_2 = {0, {}};
static NODE *func__189_3;
static void entry__189_3(void);
static FRAME_INFO frame__189_3 = {0, {}};
static NODE *func__189_4;
static void entry__189_4(void);
static FRAME_INFO frame__189_4 = {0, {}};
static void cont__189_5(void);
static void cont__189_6(void);
static void cont__189_7(void);
static NODE *func__189_8;
static void entry__189_8(void);
static FRAME_INFO frame__189_8 = {0, {}};
static NODE *func__189_9;
static void entry__189_9(void);
static FRAME_INFO frame__189_9 = {0, {}};
static NODE *func__189_10;
static void entry__189_10(void);
static FRAME_INFO frame__189_10 = {0, {}};
static NODE *func__189_11;
static void entry__189_11(void);
static FRAME_INFO frame__189_11 = {0, {}};
static void cont__189_12(void);
static void cont__189_13(void);
static void cont__190_1(void);
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
  {cont__96_2, NULL, 92, 92, 1, 30},
  {cont__97_1, NULL, 93, 93, 1, 30},
  {cont__98_1, NULL, 94, 94, 1, 28},
  {cont__99_1, NULL, 96, 96, 1, 40},
  {cont__100_2, NULL, 98, 98, 1, 15},
  {cont__101_1, NULL, 100, 100, 12, 23},
  {cont__102_1, NULL, 100, 100, 1, 23},
  {cont__102_2, NULL, 101, 101, 1, 72},
  {cont__103_2, NULL, 102, 102, 1, 37},
  {cont__104_2, NULL, 103, 103, 1, 39},
  {cont__105_2, NULL, 107, 107, 5, 25},
  {cont__106_1, NULL, 105, 112, 1, 45},
  {cont__106_10, NULL, 116, 116, 5, 26},
  {cont__107_1, NULL, 114, 121, 1, 45},
  {cont__107_8, NULL, 127, 127, 5, 19},
  {cont__109_2, NULL, 128, 128, 5, 22},
  {cont__109_3, NULL, 129, 129, 5, 22},
  {cont__109_4, NULL, 130, 130, 5, 21},
  {cont__109_5, NULL, 131, 131, 5, 19},
  {cont__109_7, NULL, 132, 132, 5, 17},
  {cont__109_9, NULL, 133, 133, 5, 16},
  {cont__109_10, NULL, 125, 133, 1, 17},
  {cont__109_11, NULL, 136, 146, 1, 22},
  {cont__111_13, NULL, 172, 172, 42, 42},
  {cont__137_1, NULL, 172, 172, 9, 43},
  {cont__137_2, NULL, 172, 172, 1, 63},
  {cont__137_3, NULL, 174, 174, 3, 20},
  {cont__138_1, NULL, 173, 254, 1, 49},
  {cont__138_76, NULL, 255, 255, 1, 39},
  {cont__139_1, NULL, 256, 256, 1, 30},
  {cont__140_1, NULL, 258, 258, 1, 37},
  {cont__142_2, NULL, 267, 267, 1, 21},
  {cont__147_1, NULL, 269, 280, 1, 27},
  {cont__148_11, NULL, 282, 282, 4, 15},
  {cont__149_1, NULL, 282, 282, 4, 24},
  {cont__149_3, NULL, 282, 283, 1, 45},
  {cont__149_7, NULL, 285, 285, 6, 28},
  {cont__150_1, NULL, 286, 286, 3, 20},
  {cont__150_4, NULL, 285, 288, 1, 36},
  {cont__150_10, NULL, 290, 291, 1, 30},
  {cont__151_5, NULL, 294, 294, 16, 25},
  {cont__153_1, NULL, 294, 294, 10, 26},
  {cont__153_2, NULL, 294, 295, 1, 26},
  {cont__153_5, NULL, 298, 298, 16, 24},
  {cont__155_1, NULL, 298, 298, 10, 25},
  {cont__155_2, NULL, 298, 299, 1, 25},
  {cont__155_5, NULL, 640, 640, 4, 25},
  {cont__173_1, NULL, 640, 642, 1, 52},
  {cont__173_6, NULL, 1089, 1089, 1, 36},
  {cont__188_3, NULL, 1090, 1102, 1, 18},
  {cont__189_13, NULL, },
  {cont__190_1, NULL, },
  {entry__48_2, NULL, 261, 261, 36, 49},
  {entry__48_1_sim2c__show_compiler_debug_info, NULL, 261, 261, 3, 49},
  {entry__69_13, NULL, 318, 318, 37, 80},
  {cont__69_14, &frame__69_13, 318, 318, 37, 61},
  {cont__69_15, &frame__69_13, 318, 318, 80, 80},
  {entry__69_10, NULL, 317, 317, 13, 41},
  {cont__69_11, &frame__69_10, 318, 318, 16, 34},
  {cont__69_12, &frame__69_10, 318, 318, 13, 80},
  {entry__69_8, NULL, 316, 316, 14, 33},
  {cont__69_9, &frame__69_8, 316, 318, 11, 80},
  {entry__69_6, NULL, 315, 315, 18, 32},
  {cont__69_7, &frame__69_6, 315, 318, 9, 81},
  {entry__69_4, NULL, 314, 314, 10, 26},
  {cont__69_5, &frame__69_4, 314, 318, 7, 82},
  {entry__69_3, NULL, 313, 318, 5, 83},
  {entry__69_20, NULL, 322, 323, 11, 57},
  {cont__69_23, &frame__69_20, 322, 323, 5, 57},
  {entry__69_1_resolve_filename, NULL, 311, 311, 6, 36},
  {cont__69_2, &frame__69_1_resolve_filename, 311, 318, 3, 84},
  {cont__69_16, &frame__69_1_resolve_filename, 319, 319, 3, 32},
  {cont__69_17, &frame__69_1_resolve_filename, 320, 320, 3, 38},
  {cont__69_18, &frame__69_1_resolve_filename, 321, 321, 6, 25},
  {cont__69_19, &frame__69_1_resolve_filename, 321, 323, 3, 58},
  {cont__69_24, &frame__69_1_resolve_filename, 324, 324, 21, 39},
  {cont__69_25, &frame__69_1_resolve_filename, 324, 324, 6, 40},
  {cont__69_26, &frame__69_1_resolve_filename, 324, 324, 3, 40},
  {entry__70_10, NULL, 342, 342, 56, 77},
  {cont__70_11, &frame__70_10, 342, 342, 77, 77},
  {entry__70_8, NULL, 342, 342, 35, 53},
  {cont__70_9, &frame__70_8, 342, 342, 32, 77},
  {entry__70_6, NULL, 342, 342, 10, 29},
  {cont__70_7, &frame__70_6, 342, 342, 7, 77},
  {entry__70_28, NULL, 348, 348, 41, 65},
  {cont__70_29, &frame__70_28, 348, 348, 41, 65},
  {entry__70_31, NULL, 349, 349, 11, 38},
  {cont__70_32, &frame__70_31, 349, 349, 49, 49},
  {entry__70_15, NULL, 344, 344, 48, 60},
  {cont__70_17, &frame__70_15, 344, 344, 48, 68},
  {cont__70_18, &frame__70_15, 344, 344, 9, 69},
  {cont__70_19, &frame__70_15, 345, 345, 9, 34},
  {cont__70_20, &frame__70_15, 346, 346, 22, 36},
  {cont__70_21, &frame__70_15, 346, 346, 38, 62},
  {cont__70_22, &frame__70_15, 346, 346, 22, 62},
  {cont__70_23, &frame__70_15, 346, 346, 22, 64},
  {cont__70_24, &frame__70_15, 346, 346, 9, 67},
  {cont__70_25, &frame__70_15, 347, 347, 9, 49},
  {cont__70_26, &frame__70_15, 348, 348, 12, 36},
  {cont__70_27, &frame__70_15, 348, 348, 12, 65},
  {cont__70_30, &frame__70_15, 348, 349, 9, 49},
  {cont__70_33, &frame__70_15, 350, 350, 9, 52},
  {cont__70_34, &frame__70_15, 351, 351, 9, 26},
  {cont__70_35, &frame__70_15, 352, 352, 9, 43},
  {cont__70_36, &frame__70_15, 353, 353, 9, 30},
  {cont__70_37, &frame__70_15, 353, 353, 52, 52},
  {entry__70_12, NULL, 343, 343, 10, 33},
  {cont__70_14, &frame__70_12, 343, 353, 7, 52},
  {entry__70_4, NULL, 340, 340, 5, 33},
  {cont__70_5, &frame__70_4, 341, 353, 5, 53},
  {entry__70_49, NULL, 359, 359, 38, 60},
  {cont__70_50, &frame__70_49, 359, 359, 60, 60},
  {entry__70_45_maybe_push_common, NULL, 358, 358, 11, 54},
  {cont__70_47, &frame__70_45_maybe_push_common, 359, 359, 14, 35},
  {cont__70_48, &frame__70_45_maybe_push_common, 359, 359, 11, 60},
  {entry__70_57, NULL, 366, 367, 17, 57},
  {cont__70_60, &frame__70_57, 366, 367, 11, 57},
  {entry__70_67, NULL, 371, 371, 11, 34},
  {cont__70_68, &frame__70_67, 372, 372, 11, 45},
  {cont__70_69, &frame__70_67, 372, 372, 45, 45},
  {entry__70_64, NULL, 370, 370, 18, 31},
  {cont__70_65, &frame__70_64, 370, 370, 18, 31},
  {cont__70_66, &frame__70_64, 370, 372, 15, 45},
  {entry__70_44, NULL, 361, 361, 9, 35},
  {cont__70_51, &frame__70_44, 362, 362, 35, 58},
  {cont__70_52, &frame__70_44, 362, 362, 9, 59},
  {cont__70_53, &frame__70_44, 363, 363, 9, 39},
  {cont__70_54, &frame__70_44, 364, 364, 9, 46},
  {cont__70_55, &frame__70_44, 365, 365, 16, 32},
  {cont__70_56, &frame__70_44, 365, 367, 9, 58},
  {cont__70_61, &frame__70_44, 368, 368, 9, 30},
  {cont__70_62, &frame__70_44, 369, 369, 9, 34},
  {cont__70_63, &frame__70_44, 370, 372, 9, 45},
  {cont__70_70, &frame__70_44, 373, 373, 10, 30},
  {cont__70_71, &frame__70_44, 373, 373, 9, 40},
  {cont__70_72, &frame__70_44, 373, 373, 9, 30},
  {cont__70_73, &frame__70_44, 373, 373, 46, 46},
  {entry__70_41, NULL, 356, 356, 14, 44},
  {cont__70_43, &frame__70_41, 356, 373, 7, 46},
  {entry__70_39, NULL, 355, 355, 8, 30},
  {cont__70_40, &frame__70_39, 355, 373, 5, 47},
  {entry__70_77, NULL, 374, 374, 39, 64},
  {entry__70_1_add_module_infos, NULL, 335, 335, 22, 27},
  {cont__70_2, &frame__70_1_add_module_infos, 335, 335, 3, 33},
  {cont__70_3, &frame__70_1_add_module_infos, 339, 353, 3, 54},
  {cont__70_38, &frame__70_1_add_module_infos, 354, 373, 3, 48},
  {cont__70_74, &frame__70_1_add_module_infos, 374, 374, 6, 31},
  {cont__70_75, &frame__70_1_add_module_infos, 374, 374, 6, 36},
  {cont__70_76, &frame__70_1_add_module_infos, 374, 374, 3, 64},
  {cont__70_78, &frame__70_1_add_module_infos, 374, 374, 64, 64},
  {entry__71_4, NULL, 385, 385, 23, 29},
  {entry__71_5, NULL, 386, 386, 47, 47},
  {cont__71_6, &frame__71_5, 386, 386, 22, 48},
  {cont__71_7, &frame__71_5, 386, 386, 70, 70},
  {cont__71_8, &frame__71_5, 386, 386, 50, 71},
  {cont__71_9, &frame__71_5, 386, 386, 5, 71},
  {cont__71_10, &frame__71_5, 387, 387, 8, 28},
  {cont__71_11, &frame__71_5, 387, 387, 5, 28},
  {entry__71_1_lookup, NULL, 384, 384, 3, 29},
  {cont__71_2, &frame__71_1_lookup, 385, 385, 6, 20},
  {cont__71_3, &frame__71_1_lookup, 385, 387, 3, 28},
  {entry__72_2, NULL, 390, 390, 36, 47},
  {cont__72_3, &frame__72_2, 390, 390, 53, 62},
  {cont__72_4, &frame__72_2, 390, 390, 27, 62},
  {entry__72_1_CC, NULL, 390, 390, 3, 62},
  {cont__72_5, &frame__72_1_CC, 391, 391, 3, 10},
  {entry__73_2, NULL, 394, 394, 41, 60},
  {entry__73_8, NULL, 399, 399, 11, 23},
  {cont__73_9, &frame__73_8, 397, 399, 13, 24},
  {cont__73_12, &frame__73_8, 397, 399, 7, 24},
  {entry__73_4, NULL, 395, 395, 5, 83},
  {cont__73_7, &frame__73_4, 396, 399, 5, 25},
  {cont__73_13, &frame__73_4, 400, 400, 17, 17},
  {entry__73_1_compile_c, NULL, 394, 394, 10, 60},
  {cont__73_3, &frame__73_1_compile_c, 394, 400, 3, 17},
  {entry__74_25, NULL, 427, 427, 45, 74},
  {cont__74_26, &frame__74_25, 427, 427, 9, 41},
  {cont__74_27, &frame__74_25, 427, 427, 9, 74},
  {cont__74_28, &frame__74_25, 427, 427, 9, 74},
  {entry__74_21, NULL, 426, 426, 43, 75},
  {cont__74_22, &frame__74_21, 426, 426, 9, 39},
  {cont__74_23, &frame__74_21, 426, 426, 9, 75},
  {cont__74_24, &frame__74_21, 427, 427, 9, 74},
  {cont__74_29, &frame__74_21, },
  {entry__74_19, NULL, 425, 425, 9, 32},
  {cont__74_20, &frame__74_19, },
  {cont__74_30, &frame__74_19, },
  {entry__74_17, NULL, 424, 424, 9, 29},
  {cont__74_18, &frame__74_17, },
  {cont__74_31, &frame__74_17, },
  {entry__74_41, NULL, 439, 439, 17, 47},
  {cont__74_42, &frame__74_41, 439, 439, 17, 67},
  {cont__74_43, &frame__74_41, 439, 439, 17, 67},
  {entry__74_45, NULL, 442, 442, 17, 21},
  {entry__74_38_check, NULL, 435, 435, 13, 42},
  {cont__74_39, &frame__74_38_check, 438, 438, 17, 38},
  {cont__74_40, &frame__74_38_check, 437, 439, 15, 66},
  {cont__74_44, &frame__74_38_check, 436, 442, 13, 22},
  {entry__74_58, NULL, 452, 452, 58, 58},
  {cont__74_59, &frame__74_58, 452, 452, 40, 59},
  {cont__74_60, &frame__74_58, 452, 452, 23, 60},
  {cont__74_61, &frame__74_58, 452, 452, 17, 60},
  {entry__74_63, NULL, 454, 454, 53, 77},
  {cont__74_64, &frame__74_63, 454, 454, 47, 77},
  {entry__74_62, NULL, 454, 454, 17, 77},
  {entry__74_55, NULL, 451, 451, 15, 40},
  {cont__74_57, &frame__74_55, 450, 454, 13, 78},
  {entry__74_37, NULL, 444, 444, 18, 41},
  {cont__74_47, &frame__74_37, 444, 444, 11, 47},
  {cont__74_48, &frame__74_37, 445, 445, 11, 26},
  {cont__74_49, &frame__74_37, 446, 446, 11, 20},
  {cont__74_50, &frame__74_37, 447, 447, 11, 50},
  {cont__74_51, &frame__74_37, 448, 448, 11, 44},
  {cont__74_52, &frame__74_37, 449, 449, 14, 30},
  {cont__74_54, &frame__74_37, 449, 454, 11, 79},
  {entry__74_36, NULL, 433, 454, 9, 80},
  {cont__74_65, &frame__74_36, 454, 454, 80, 80},
  {entry__74_33, NULL, 430, 430, 7, 55},
  {cont__74_34, &frame__74_33, 431, 431, 7, 38},
  {cont__74_35, &frame__74_33, 432, 454, 7, 81},
  {entry__74_74, NULL, 469, 469, 29, 41},
  {cont__74_75, &frame__74_74, 469, 469, 23, 41},
  {entry__74_67, NULL, 463, 463, 7, 36},
  {cont__74_68, &frame__74_67, 464, 464, 7, 22},
  {cont__74_69, &frame__74_67, 465, 465, 7, 31},
  {cont__74_70, &frame__74_67, 466, 466, 7, 32},
  {cont__74_71, &frame__74_67, 467, 467, 7, 43},
  {cont__74_72, &frame__74_67, 468, 468, 7, 32},
  {cont__74_73, &frame__74_67, 469, 469, 7, 41},
  {cont__74_76, &frame__74_67, 470, 470, 25, 35},
  {cont__74_77, &frame__74_67, 470, 470, 7, 35},
  {cont__74_78, &frame__74_67, 470, 470, 35, 35},
  {entry__74_2, NULL, 412, 412, 48, 48},
  {cont__74_3, &frame__74_2, 412, 412, 5, 49},
  {cont__74_4, &frame__74_2, 413, 413, 35, 57},
  {cont__74_5, &frame__74_2, 413, 413, 5, 58},
  {cont__74_6, &frame__74_2, 414, 414, 5, 42},
  {cont__74_7, &frame__74_2, 415, 415, 42, 64},
  {cont__74_8, &frame__74_2, 415, 415, 5, 70},
  {cont__74_10, &frame__74_2, 416, 416, 51, 62},
  {cont__74_11, &frame__74_2, 416, 416, 39, 63},
  {cont__74_12, &frame__74_2, 416, 416, 5, 71},
  {cont__74_13, &frame__74_2, 417, 417, 5, 34},
  {cont__74_14, &frame__74_2, 418, 418, 5, 32},
  {cont__74_15, &frame__74_2, 419, 419, 5, 38},
  {cont__74_16, &frame__74_2, 421, 427, 5, 75},
  {cont__74_32, &frame__74_2, 429, 454, 5, 82},
  {cont__74_66, &frame__74_2, 455, 470, 5, 35},
  {cont__74_79, &frame__74_2, 471, 471, 5, 19},
  {cont__74_80, &frame__74_2, 472, 472, 8, 21},
  {cont__74_81, &frame__74_2, 472, 472, 5, 21},
  {entry__74_1_compile_meta_module, NULL, 411, 472, 3, 21},
  {entry__75_13, NULL, 497, 497, 43, 43},
  {cont__75_14, &frame__75_13, 497, 497, 15, 44},
  {cont__75_15, &frame__75_13, 499, 499, 48, 48},
  {cont__75_16, &frame__75_13, 499, 499, 24, 49},
  {cont__75_17, &frame__75_13, 499, 499, 17, 59},
  {cont__75_18, &frame__75_13, 500, 500, 44, 44},
  {cont__75_19, &frame__75_13, 500, 500, 24, 45},
  {cont__75_20, &frame__75_13, 500, 500, 17, 55},
  {cont__75_21, &frame__75_13, 498, 500, 15, 55},
  {entry__75_11, NULL, 496, 496, 16, 26},
  {cont__75_12, &frame__75_11, 496, 500, 13, 56},
  {entry__75_24, NULL, 506, 506, 17, 36},
  {entry__75_23, NULL, },
  {cont__75_25, &frame__75_23, },
  {entry__75_27, NULL, 508, 508, 32, 57},
  {cont__75_28, &frame__75_27, 508, 508, 17, 66},
  {entry__75_30, NULL, 511, 511, 44, 71},
  {cont__75_31, &frame__75_30, 511, 511, 30, 72},
  {cont__75_33, &frame__75_30, 511, 511, 19, 73},
  {cont__75_34, &frame__75_30, 511, 511, 78, 78},
  {entry__75_29, NULL, 510, 511, 17, 78},
  {entry__75_22, NULL, },
  {cont__75_26, &frame__75_22, 502, 511, 13, 80},
  {entry__75_9, NULL, 495, 495, 11, 36},
  {cont__75_10, &frame__75_9, 494, 511, 9, 82},
  {entry__75_36, NULL, 513, 513, 37, 64},
  {cont__75_37, &frame__75_36, 513, 513, 26, 65},
  {cont__75_38, &frame__75_36, 513, 513, 70, 70},
  {entry__75_35, NULL, 513, 513, 9, 70},
  {entry__75_2, NULL, 486, 486, 12, 35},
  {cont__75_3, &frame__75_2, 486, 486, 5, 42},
  {cont__75_4, &frame__75_2, 487, 487, 5, 20},
  {cont__75_5, &frame__75_2, 488, 488, 5, 14},
  {cont__75_6, &frame__75_2, 489, 489, 5, 44},
  {cont__75_7, &frame__75_2, 490, 490, 5, 38},
  {cont__75_8, &frame__75_2, 491, 513, 5, 71},
  {entry__75_1_build_dependencies, NULL, 485, 513, 3, 72},
  {cont__75_41, &frame__75_1_build_dependencies, 513, 513, 72, 72},
  {entry__76_9, NULL, 535, 535, 28, 44},
  {cont__76_10, &frame__76_9, 535, 535, 28, 44},
  {entry__76_12, NULL, 536, 536, 9, 72},
  {entry__76_18, NULL, 541, 542, 15, 49},
  {cont__76_20, &frame__76_18, 541, 542, 9, 49},
  {entry__76_23, NULL, 546, 546, 11, 40},
  {cont__76_24, &frame__76_23, 546, 546, 11, 60},
  {cont__76_25, &frame__76_23, 546, 546, 11, 60},
  {entry__76_27, NULL, 548, 548, 11, 59},
  {cont__76_28, &frame__76_27, 548, 548, 59, 59},
  {entry__76_3, NULL, 533, 533, 7, 45},
  {cont__76_4, &frame__76_3, 534, 534, 58, 58},
  {cont__76_5, &frame__76_3, 534, 534, 34, 59},
  {cont__76_6, &frame__76_3, 534, 534, 7, 75},
  {cont__76_7, &frame__76_3, 535, 535, 10, 23},
  {cont__76_8, &frame__76_3, 535, 535, 10, 44},
  {cont__76_11, &frame__76_3, 535, 536, 7, 72},
  {cont__76_13, &frame__76_3, 537, 537, 7, 53},
  {cont__76_14, &frame__76_3, 538, 538, 7, 38},
  {cont__76_15, &frame__76_3, 539, 539, 7, 34},
  {cont__76_16, &frame__76_3, 540, 540, 14, 32},
  {cont__76_17, &frame__76_3, 540, 542, 7, 50},
  {cont__76_21, &frame__76_3, 545, 545, 11, 40},
  {cont__76_22, &frame__76_3, 544, 546, 9, 59},
  {cont__76_26, &frame__76_3, 543, 548, 7, 60},
  {entry__76_32, NULL, 551, 551, 22, 43},
  {cont__76_33, &frame__76_32, 551, 551, 48, 48},
  {entry__76_37, NULL, 557, 557, 29, 56},
  {cont__76_38, &frame__76_37, 557, 557, 9, 56},
  {cont__76_39, &frame__76_37, 557, 557, 9, 56},
  {entry__76_35, NULL, 556, 556, 9, 27},
  {cont__76_36, &frame__76_35, 557, 557, 9, 56},
  {cont__76_40, &frame__76_35, },
  {entry__76_47, NULL, 560, 560, 21, 63},
  {entry__76_50, NULL, 561, 561, 35, 53},
  {entry__76_52, NULL, 562, 562, 32, 54},
  {entry__76_56, NULL, 564, 564, 26, 56},
  {entry__76_42, NULL, 559, 559, 50, 59},
  {cont__76_44, &frame__76_42, 559, 559, 61, 70},
  {cont__76_45, &frame__76_42, 559, 559, 9, 71},
  {cont__76_46, &frame__76_42, 560, 560, 9, 63},
  {cont__76_49, &frame__76_42, 561, 561, 9, 53},
  {cont__76_51, &frame__76_42, 562, 562, 9, 54},
  {cont__76_53, &frame__76_42, 563, 563, 25, 37},
  {cont__76_54, &frame__76_42, 563, 563, 9, 37},
  {cont__76_55, &frame__76_42, 564, 564, 9, 56},
  {cont__76_57, &frame__76_42, 564, 564, 56, 56},
  {entry__76_62, NULL, 571, 571, 44, 71},
  {cont__76_63, &frame__76_62, 571, 571, 13, 40},
  {cont__76_64, &frame__76_62, 571, 571, 13, 71},
  {cont__76_65, &frame__76_62, 571, 571, 13, 71},
  {entry__76_68, NULL, 573, 573, 30, 60},
  {entry__76_67, NULL, 573, 573, 13, 60},
  {entry__76_71, NULL, 578, 578, 17, 44},
  {cont__76_72, &frame__76_71, 578, 578, 17, 69},
  {cont__76_73, &frame__76_71, 578, 578, 17, 69},
  {entry__76_75, NULL, 580, 580, 17, 68},
  {cont__76_76, &frame__76_75, 580, 580, 68, 68},
  {entry__76_69, NULL, 577, 577, 17, 51},
  {cont__76_70, &frame__76_69, 576, 578, 15, 68},
  {cont__76_74, &frame__76_69, 575, 580, 13, 69},
  {entry__76_58, NULL, 566, 566, 9, 30},
  {cont__76_59, &frame__76_58, 567, 567, 9, 32},
  {cont__76_60, &frame__76_58, 570, 570, 13, 31},
  {cont__76_61, &frame__76_58, 569, 571, 11, 70},
  {cont__76_66, &frame__76_58, 568, 580, 9, 71},
  {entry__76_2_compile_submodule, NULL, 532, 548, 5, 61},
  {cont__76_29, &frame__76_2_compile_submodule, 549, 549, 5, 48},
  {cont__76_30, &frame__76_2_compile_submodule, 550, 550, 5, 28},
  {cont__76_31, &frame__76_2_compile_submodule, 551, 551, 5, 48},
  {cont__76_34, &frame__76_2_compile_submodule, 552, 552, 5, 21},
  {cont__76_41, &frame__76_2_compile_submodule, 553, 580, 5, 73},
  {cont__76_77, &frame__76_2_compile_submodule, 581, 581, 5, 63},
  {entry__76_80, NULL, 585, 586, 11, 56},
  {cont__76_83, &frame__76_80, 585, 586, 5, 56},
  {entry__76_96, NULL, 593, 593, 51, 75},
  {cont__76_97, &frame__76_96, 593, 593, 32, 75},
  {cont__76_98, &frame__76_96, 593, 593, 75, 75},
  {entry__76_91, NULL, 592, 592, 59, 59},
  {cont__76_92, &frame__76_91, 592, 592, 30, 60},
  {cont__76_93, &frame__76_91, 592, 592, 25, 61},
  {cont__76_94, &frame__76_91, 592, 592, 7, 61},
  {cont__76_95, &frame__76_91, 593, 593, 7, 75},
  {entry__76_104, NULL, 600, 600, 37, 60},
  {cont__76_105, &frame__76_104, 600, 600, 37, 60},
  {entry__76_107, NULL, 602, 602, 35, 35},
  {entry__76_101, NULL, 599, 599, 11, 47},
  {cont__76_102, &frame__76_101, 600, 600, 14, 32},
  {cont__76_103, &frame__76_101, 600, 600, 14, 60},
  {cont__76_106, &frame__76_101, 600, 602, 11, 35},
  {entry__76_109, NULL, 606, 606, 13, 37},
  {cont__76_110, &frame__76_109, 607, 607, 13, 32},
  {cont__76_111, &frame__76_109, 604, 607, 11, 32},
  {entry__76_100, NULL, 598, 602, 9, 36},
  {cont__76_108, &frame__76_100, 603, 607, 9, 33},
  {entry__76_118, NULL, 615, 615, 39, 62},
  {cont__76_119, &frame__76_118, 615, 615, 39, 62},
  {entry__76_121, NULL, 617, 617, 37, 37},
  {entry__76_115, NULL, 614, 614, 13, 77},
  {cont__76_116, &frame__76_115, 615, 615, 16, 34},
  {cont__76_117, &frame__76_115, 615, 615, 16, 62},
  {cont__76_120, &frame__76_115, 615, 617, 13, 37},
  {entry__76_124, NULL, 619, 619, 32, 53},
  {cont__76_125, &frame__76_124, 619, 619, 13, 65},
  {cont__76_126, &frame__76_124, 620, 620, 13, 39},
  {cont__76_127, &frame__76_124, 621, 621, 13, 35},
  {cont__76_128, &frame__76_124, 621, 621, 38, 38},
  {entry__76_114, NULL, 613, 617, 11, 38},
  {cont__76_122, &frame__76_114, 618, 618, 14, 37},
  {cont__76_123, &frame__76_114, 618, 621, 11, 38},
  {entry__76_135, NULL, 626, 626, 40, 69},
  {cont__76_137, &frame__76_135, 626, 626, 69, 69},
  {entry__76_134, NULL, 626, 626, 13, 69},
  {entry__76_130, NULL, 623, 623, 11, 61},
  {cont__76_131, &frame__76_130, 624, 624, 11, 38},
  {cont__76_132, &frame__76_130, 625, 625, 14, 33},
  {cont__76_133, &frame__76_130, 625, 626, 11, 69},
  {cont__76_138, &frame__76_130, 627, 627, 11, 39},
  {cont__76_139, &frame__76_130, 627, 627, 39, 39},
  {entry__76_113, NULL, 610, 621, 9, 39},
  {cont__76_129, &frame__76_113, 622, 627, 9, 39},
  {entry__76_99, NULL, 595, 607, 7, 34},
  {cont__76_112, &frame__76_99, 608, 627, 7, 40},
  {entry__76_1_compile_module, NULL, 583, 583, 3, 40},
  {cont__76_78, &frame__76_1_compile_module, 584, 584, 10, 28},
  {cont__76_79, &frame__76_1_compile_module, 584, 586, 3, 57},
  {cont__76_84, &frame__76_1_compile_module, 587, 587, 3, 39},
  {cont__76_86, &frame__76_1_compile_module, 588, 588, 6, 24},
  {cont__76_87, &frame__76_1_compile_module, 588, 588, 3, 31},
  {cont__76_88, &frame__76_1_compile_module, 589, 589, 3, 22},
  {cont__76_89, &frame__76_1_compile_module, 591, 591, 5, 21},
  {cont__76_90, &frame__76_1_compile_module, 590, 627, 3, 42},
  {cont__76_140, &frame__76_1_compile_module, 627, 627, 42, 42},
  {entry__77_4, NULL, 636, 636, 21, 41},
  {cont__77_5, &frame__77_4, 636, 636, 43, 67},
  {cont__77_6, &frame__77_4, 636, 636, 5, 67},
  {entry__77_8, NULL, 638, 638, 20, 40},
  {cont__77_9, &frame__77_8, 638, 638, 42, 66},
  {cont__77_10, &frame__77_8, 638, 638, 5, 66},
  {entry__77_1_compile_modules, NULL, 634, 634, 47, 66},
  {cont__77_2, &frame__77_1_compile_modules, 634, 634, 3, 66},
  {cont__77_3, &frame__77_1_compile_modules, 635, 636, 3, 67},
  {cont__77_7, &frame__77_1_compile_modules, 637, 638, 3, 66},
  {entry__79_6, NULL, 647, 647, 34, 58},
  {cont__79_8, &frame__79_6, 647, 647, 25, 58},
  {entry__79_2, NULL, 646, 646, 5, 40},
  {cont__79_4, &frame__79_2, 647, 647, 8, 22},
  {cont__79_5, &frame__79_2, 647, 647, 5, 58},
  {cont__79_9, &frame__79_2, 648, 648, 40, 57},
  {cont__79_10, &frame__79_2, 648, 648, 5, 57},
  {cont__79_12, &frame__79_2, 649, 649, 35, 54},
  {cont__79_13, &frame__79_2, 649, 649, 5, 54},
  {entry__79_1_show_file_list, NULL, 645, 649, 3, 54},
  {entry__80_7, NULL, 658, 658, 60, 70},
  {cont__80_9, &frame__80_7, 658, 658, 40, 70},
  {cont__80_10, &frame__80_7, 658, 658, 70, 70},
  {entry__80_5, NULL, 658, 658, 14, 30},
  {cont__80_6, &frame__80_5, 658, 658, 5, 70},
  {entry__80_12, NULL, 659, 659, 54, 77},
  {cont__80_13, &frame__80_12, 659, 659, 27, 77},
  {entry__80_16, NULL, 660, 660, 30, 54},
  {cont__80_17, &frame__80_16, 660, 660, 54, 54},
  {entry__80_26, NULL, 669, 669, 31, 60},
  {cont__80_29, &frame__80_26, 669, 669, 28, 60},
  {entry__80_30, NULL, 670, 670, 16, 38},
  {cont__80_32, &frame__80_30, 670, 670, 13, 38},
  {entry__80_21, NULL, 668, 668, 13, 30},
  {cont__80_22, &frame__80_21, 669, 669, 13, 26},
  {cont__80_25, &frame__80_21, 667, 670, 11, 37},
  {cont__80_33, &frame__80_21, 666, 670, 9, 39},
  {entry__80_36, NULL, 674, 674, 25, 44},
  {cont__80_37, &frame__80_36, 674, 674, 52, 71},
  {cont__80_38, &frame__80_36, 674, 674, 16, 73},
  {cont__80_39, &frame__80_36, 674, 675, 13, 26},
  {entry__80_40, NULL, 676, 676, 16, 29},
  {cont__80_41, &frame__80_40, 676, 676, 13, 29},
  {entry__80_34, NULL, 673, 673, 13, 34},
  {cont__80_35, &frame__80_34, 672, 676, 11, 28},
  {cont__80_42, &frame__80_34, 671, 676, 9, 30},
  {entry__80_19, NULL, 665, 665, 9, 35},
  {cont__80_20, &frame__80_19, 664, 676, 7, 30},
  {cont__80_43, &frame__80_19, 662, 676, 5, 32},
  {cont__80_44, &frame__80_19, 676, 676, 33, 33},
  {entry__80_1_library_paths_and_file_list, NULL, 652, 652, 3, 16},
  {cont__80_2, &frame__80_1_library_paths_and_file_list, 656, 656, 3, 39},
  {cont__80_3, &frame__80_1_library_paths_and_file_list, 657, 657, 6, 21},
  {cont__80_4, &frame__80_1_library_paths_and_file_list, 657, 658, 3, 70},
  {cont__80_11, &frame__80_1_library_paths_and_file_list, 659, 659, 3, 77},
  {cont__80_15, &frame__80_1_library_paths_and_file_list, 660, 660, 3, 54},
  {cont__80_18, &frame__80_1_library_paths_and_file_list, 661, 676, 3, 33},
  {cont__80_45, &frame__80_1_library_paths_and_file_list, 677, 677, 24, 57},
  {cont__80_46, &frame__80_1_library_paths_and_file_list, 677, 677, 3, 57},
  {entry__81_9, NULL, 687, 687, 51, 64},
  {cont__81_10, &frame__81_9, 687, 687, 51, 64},
  {entry__81_7, NULL, 687, 687, 37, 46},
  {cont__81_8, &frame__81_7, 687, 687, 37, 64},
  {cont__81_11, &frame__81_7, 687, 687, 37, 64},
  {entry__81_29, NULL, 698, 698, 25, 59},
  {cont__81_31, &frame__81_29, 698, 698, 21, 60},
  {cont__81_32, &frame__81_29, 698, 698, 21, 60},
  {entry__81_25, NULL, 697, 697, 25, 58},
  {cont__81_27, &frame__81_25, 697, 697, 21, 59},
  {cont__81_28, &frame__81_25, 698, 698, 21, 60},
  {cont__81_33, &frame__81_25, },
  {entry__81_38, NULL, 702, 702, 46, 80},
  {cont__81_39, &frame__81_38, 702, 702, 46, 80},
  {entry__81_41, NULL, 704, 704, 44, 74},
  {cont__81_42, &frame__81_41, 704, 704, 23, 74},
  {entry__81_35, NULL, 702, 702, 21, 34},
  {cont__81_36, &frame__81_35, 702, 702, 21, 41},
  {cont__81_37, &frame__81_35, 702, 702, 21, 80},
  {cont__81_40, &frame__81_35, 701, 704, 19, 75},
  {entry__81_49, NULL, 707, 707, 60, 60},
  {cont__81_50, &frame__81_49, 707, 707, 44, 61},
  {cont__81_51, &frame__81_49, 707, 707, 23, 61},
  {entry__81_46, NULL, 706, 706, 35, 62},
  {cont__81_47, &frame__81_46, 706, 706, 35, 67},
  {cont__81_48, &frame__81_46, 706, 707, 21, 61},
  {entry__81_43, NULL, 705, 705, 22, 62},
  {cont__81_45, &frame__81_43, 705, 707, 19, 62},
  {entry__81_52, NULL, 709, 709, 21, 52},
  {entry__81_54, NULL, 710, 710, 31, 45},
  {entry__81_21, NULL, 696, 696, 21, 34},
  {cont__81_22, &frame__81_21, 696, 696, 21, 41},
  {cont__81_23, &frame__81_21, 696, 696, 21, 41},
  {cont__81_24, &frame__81_21, 694, 698, 17, 61},
  {cont__81_34, &frame__81_21, 700, 709, 17, 53},
  {cont__81_53, &frame__81_21, 710, 710, 17, 45},
  {cont__81_56, &frame__81_21, 711, 711, 17, 33},
  {entry__81_17, NULL, 691, 691, 15, 38},
  {cont__81_18, &frame__81_17, 692, 692, 15, 50},
  {cont__81_19, &frame__81_17, 693, 693, 18, 39},
  {cont__81_20, &frame__81_17, 693, 711, 15, 33},
  {entry__81_13, NULL, 688, 688, 33, 37},
  {cont__81_14, &frame__81_13, 688, 688, 13, 38},
  {cont__81_15, &frame__81_13, 690, 690, 20, 42},
  {cont__81_16, &frame__81_13, 690, 711, 13, 34},
  {entry__81_5, NULL, 687, 687, 18, 32},
  {cont__81_6, &frame__81_5, 687, 687, 18, 64},
  {cont__81_12, &frame__81_5, 687, 711, 11, 35},
  {entry__81_59, NULL, 713, 713, 33, 42},
  {cont__81_60, &frame__81_59, 713, 713, 33, 42},
  {entry__81_62, NULL, 713, 713, 50, 50},
  {entry__81_57, NULL, 713, 713, 14, 28},
  {cont__81_58, &frame__81_57, 713, 713, 14, 42},
  {cont__81_61, &frame__81_57, 713, 713, 11, 50},
  {entry__81_3, NULL, 686, 686, 9, 20},
  {cont__81_4, &frame__81_3, 685, 713, 7, 51},
  {entry__81_2_collect_declarations, NULL, 684, 713, 5, 52},
  {entry__81_63, NULL, 715, 715, 28, 54},
  {entry__81_74, NULL, 720, 720, 22, 59},
  {entry__81_1_create_imports, NULL, 715, 715, 3, 54},
  {cont__81_64, &frame__81_1_create_imports, 716, 716, 3, 49},
  {cont__81_66, &frame__81_1_create_imports, 717, 717, 3, 18},
  {cont__81_67, &frame__81_1_create_imports, 718, 718, 3, 15},
  {cont__81_68, &frame__81_1_create_imports, 719, 719, 22, 42},
  {cont__81_69, &frame__81_1_create_imports, 719, 719, 22, 45},
  {cont__81_70, &frame__81_1_create_imports, 719, 719, 48, 48},
  {cont__81_71, &frame__81_1_create_imports, 719, 719, 9, 49},
  {cont__81_72, &frame__81_1_create_imports, 719, 719, 3, 49},
  {cont__81_73, &frame__81_1_create_imports, 720, 720, 3, 59},
  {entry__82_3, NULL, 723, 723, 32, 67},
  {entry__82_7, NULL, 725, 726, 5, 57},
  {entry__82_1_compile_exe, NULL, 723, 723, 6, 29},
  {cont__82_2, &frame__82_1_compile_exe, 723, 723, 3, 67},
  {cont__82_5, &frame__82_1_compile_exe, 724, 724, 10, 42},
  {cont__82_6, &frame__82_1_compile_exe, 724, 726, 3, 58},
  {cont__82_9, &frame__82_1_compile_exe, 728, 728, 3, 53},
  {cont__82_10, &frame__82_1_compile_exe, 729, 729, 46, 46},
  {cont__82_11, &frame__82_1_compile_exe, 729, 729, 3, 47},
  {cont__82_12, &frame__82_1_compile_exe, 730, 730, 3, 28},
  {cont__82_13, &frame__82_1_compile_exe, 730, 730, 28, 28},
  {entry__83_2, NULL, 735, 735, 11, 29},
  {cont__83_3, &frame__83_2, 735, 735, 5, 29},
  {cont__83_4, &frame__83_2, 735, 735, 29, 29},
  {entry__83_1_dump_source_or_check, NULL, 733, 735, 3, 29},
  {entry__84_4, NULL, 739, 739, 41, 65},
  {cont__84_5, &frame__84_4, 739, 739, 34, 75},
  {cont__84_6, &frame__84_4, 739, 739, 75, 75},
  {entry__84_8, NULL, 741, 741, 48, 57},
  {cont__84_9, &frame__84_8, 741, 741, 59, 68},
  {cont__84_10, &frame__84_8, 741, 741, 7, 69},
  {cont__84_11, &frame__84_8, 742, 742, 13, 31},
  {cont__84_12, &frame__84_8, 742, 742, 7, 31},
  {cont__84_13, &frame__84_8, 742, 742, 31, 31},
  {entry__84_15, NULL, 743, 743, 28, 50},
  {entry__84_18, NULL, 745, 745, 24, 59},
  {entry__84_2, NULL, 739, 739, 8, 31},
  {cont__84_3, &frame__84_2, 739, 739, 5, 75},
  {cont__84_7, &frame__84_2, 740, 742, 5, 31},
  {cont__84_14, &frame__84_2, 743, 743, 5, 50},
  {cont__84_16, &frame__84_2, 744, 744, 5, 15},
  {cont__84_17, &frame__84_2, 745, 745, 5, 59},
  {entry__84_1_print_c, NULL, 738, 745, 3, 59},
  {entry__85_5, NULL, 754, 754, 9, 43},
  {cont__85_6, &frame__85_5, 755, 755, 12, 28},
  {cont__85_7, &frame__85_5, 755, 755, 9, 34},
  {cont__85_8, &frame__85_5, 756, 756, 9, 21},
  {cont__85_9, &frame__85_5, 757, 757, 9, 64},
  {cont__85_10, &frame__85_5, 758, 758, 12, 23},
  {cont__85_11, &frame__85_5, 758, 758, 9, 29},
  {cont__85_12, &frame__85_5, 759, 759, 22, 22},
  {entry__85_4, NULL, 753, 759, 7, 22},
  {cont__85_13, &frame__85_4, 759, 759, 22, 22},
  {entry__85_3, NULL, 752, 759, 5, 23},
  {entry__85_17, NULL, 763, 763, 19, 65},
  {entry__85_16, NULL, 763, 763, 7, 65},
  {cont__85_19, &frame__85_16, 764, 764, 63, 63},
  {cont__85_20, &frame__85_16, 764, 764, 37, 64},
  {cont__85_21, &frame__85_16, 764, 764, 7, 64},
  {cont__85_22, &frame__85_16, 764, 764, 64, 64},
  {entry__85_25, NULL, 767, 767, 21, 66},
  {entry__85_24, NULL, 767, 767, 9, 66},
  {cont__85_26, &frame__85_24, 768, 768, 9, 44},
  {entry__85_23, NULL, 766, 768, 7, 44},
  {cont__85_27, &frame__85_23, 769, 769, 7, 32},
  {cont__85_29, &frame__85_23, 770, 770, 7, 32},
  {cont__85_31, &frame__85_23, 771, 771, 7, 34},
  {entry__85_35, NULL, 774, 774, 5, 40},
  {cont__85_36, &frame__85_35, 775, 775, 5, 32},
  {cont__85_37, &frame__85_35, 776, 776, 5, 20},
  {entry__85_1_list_dependencies, NULL, 748, 748, 3, 80},
  {cont__85_2, &frame__85_1_list_dependencies, 749, 759, 3, 24},
  {cont__85_14, &frame__85_1_list_dependencies, 761, 761, 5, 28},
  {cont__85_15, &frame__85_1_list_dependencies, 760, 771, 3, 35},
  {cont__85_33, &frame__85_1_list_dependencies, 772, 772, 3, 29},
  {cont__85_34, &frame__85_1_list_dependencies, 773, 776, 3, 20},
  {entry__86_7, NULL, 783, 784, 14, 58},
  {cont__86_10, &frame__86_7, 783, 784, 7, 58},
  {entry__86_12, NULL, 785, 785, 17, 73},
  {entry__86_34, NULL, 817, 819, 21, 49},
  {cont__86_37, &frame__86_34, 817, 819, 7, 49},
  {cont__86_38, &frame__86_34, 819, 819, 50, 50},
  {entry__86_53, NULL, 839, 839, 7, 42},
  {cont__86_54, &frame__86_53, 840, 840, 7, 34},
  {cont__86_55, &frame__86_53, 845, 845, 44, 55},
  {cont__86_56, &frame__86_53, 841, 846, 21, 23},
  {cont__86_59, &frame__86_53, 841, 846, 7, 23},
  {cont__86_60, &frame__86_53, 846, 846, 24, 24},
  {entry__86_2, NULL, 780, 780, 5, 55},
  {cont__86_4, &frame__86_2, 781, 781, 5, 31},
  {cont__86_5, &frame__86_2, 782, 782, 8, 22},
  {cont__86_6, &frame__86_2, 782, 784, 5, 59},
  {cont__86_11, &frame__86_2, 785, 785, 5, 73},
  {cont__86_14, &frame__86_2, 786, 786, 5, 40},
  {cont__86_15, &frame__86_2, 787, 787, 5, 18},
  {cont__86_16, &frame__86_2, 788, 788, 49, 49},
  {cont__86_17, &frame__86_2, 788, 788, 15, 50},
  {cont__86_18, &frame__86_2, 788, 788, 5, 74},
  {cont__86_19, &frame__86_2, 789, 789, 5, 31},
  {cont__86_20, &frame__86_2, 790, 790, 30, 73},
  {cont__86_21, &frame__86_2, 790, 790, 5, 78},
  {cont__86_22, &frame__86_2, 791, 791, 5, 33},
  {cont__86_24, &frame__86_2, 792, 792, 5, 61},
  {cont__86_27, &frame__86_2, 793, 793, 5, 25},
  {cont__86_28, &frame__86_2, 795, 815, 19, 22},
  {cont__86_32, &frame__86_2, 795, 815, 5, 22},
  {cont__86_33, &frame__86_2, 816, 819, 5, 50},
  {cont__86_39, &frame__86_2, 830, 830, 42, 53},
  {cont__86_40, &frame__86_2, 833, 833, 42, 53},
  {cont__86_41, &frame__86_2, 836, 836, 42, 53},
  {cont__86_42, &frame__86_2, 820, 837, 19, 21},
  {cont__86_51, &frame__86_2, 820, 837, 5, 21},
  {cont__86_52, &frame__86_2, 838, 846, 5, 24},
  {cont__86_61, &frame__86_2, 847, 853, 5, 32},
  {cont__86_63, &frame__86_2, 854, 854, 5, 25},
  {entry__86_1_build_codeblocks_project, NULL, 779, 854, 3, 25},
  {entry__87_4, NULL, 857, 857, 26, 56},
  {entry__87_7, NULL, 861, 861, 7, 41},
  {entry__87_12, NULL, 866, 866, 29, 50},
  {cont__87_13, &frame__87_12, 866, 866, 29, 55},
  {cont__87_14, &frame__87_12, 866, 866, 9, 56},
  {cont__87_15, &frame__87_12, 866, 866, 56, 56},
  {entry__87_22, NULL, 874, 874, 53, 66},
  {cont__87_23, &frame__87_22, 874, 874, 14, 67},
  {cont__87_25, &frame__87_22, 874, 874, 11, 67},
  {entry__87_26, NULL, 876, 876, 53, 67},
  {cont__87_28, &frame__87_26, 876, 876, 14, 68},
  {cont__87_29, &frame__87_26, 876, 876, 11, 68},
  {entry__87_30, NULL, 878, 878, 53, 69},
  {cont__87_32, &frame__87_30, 878, 878, 14, 70},
  {cont__87_33, &frame__87_30, 878, 878, 11, 70},
  {entry__87_34, NULL, 879, 879, 53, 66},
  {cont__87_35, &frame__87_34, 879, 879, 14, 67},
  {cont__87_36, &frame__87_34, 879, 879, 11, 67},
  {entry__87_40, NULL, 881, 881, 19, 56},
  {entry__87_49, NULL, 888, 888, 38, 63},
  {cont__87_50, &frame__87_49, 888, 888, 13, 63},
  {cont__87_51, &frame__87_49, 888, 888, 13, 63},
  {entry__87_53, NULL, 890, 890, 25, 25},
  {entry__87_46, NULL, 884, 884, 9, 32},
  {cont__87_47, &frame__87_46, 887, 887, 13, 29},
  {cont__87_48, &frame__87_46, 886, 888, 11, 62},
  {cont__87_52, &frame__87_46, 885, 890, 9, 26},
  {entry__87_56, NULL, 892, 892, 21, 54},
  {entry__87_67, NULL, 903, 903, 35, 47},
  {cont__87_68, &frame__87_67, 903, 903, 29, 47},
  {entry__87_61, NULL, 899, 899, 15, 76},
  {cont__87_63, &frame__87_61, 900, 900, 15, 43},
  {cont__87_64, &frame__87_61, 896, 902, 13, 26},
  {cont__87_66, &frame__87_61, 903, 903, 13, 47},
  {entry__87_74, NULL, 912, 912, 35, 47},
  {cont__87_75, &frame__87_74, 912, 912, 29, 47},
  {entry__87_69, NULL, 908, 908, 15, 43},
  {cont__87_70, &frame__87_69, 909, 909, 15, 30},
  {cont__87_72, &frame__87_69, 905, 911, 13, 26},
  {cont__87_73, &frame__87_69, 912, 912, 13, 47},
  {entry__87_83, NULL, 923, 923, 35, 47},
  {cont__87_84, &frame__87_83, 923, 923, 29, 47},
  {entry__87_76, NULL, 917, 918, 15, 86},
  {cont__87_78, &frame__87_76, 919, 919, 15, 43},
  {cont__87_79, &frame__87_76, 920, 920, 15, 30},
  {cont__87_80, &frame__87_76, 914, 922, 13, 26},
  {cont__87_82, &frame__87_76, 923, 923, 13, 47},
  {entry__87_88, NULL, 931, 931, 35, 47},
  {cont__87_89, &frame__87_88, 931, 931, 29, 47},
  {entry__87_85, NULL, 928, 928, 15, 43},
  {cont__87_86, &frame__87_85, 925, 930, 13, 26},
  {cont__87_87, &frame__87_85, 931, 931, 13, 47},
  {entry__87_55, NULL, 892, 892, 9, 54},
  {cont__87_58, &frame__87_55, 894, 894, 11, 28},
  {cont__87_59, &frame__87_55, 895, 895, 11, 24},
  {cont__87_60, &frame__87_55, 893, 931, 9, 48},
  {entry__87_8, NULL, 864, 864, 7, 56},
  {cont__87_10, &frame__87_8, 865, 865, 10, 38},
  {cont__87_11, &frame__87_8, 865, 866, 7, 56},
  {cont__87_16, &frame__87_8, 867, 867, 7, 45},
  {cont__87_17, &frame__87_8, 868, 868, 56, 56},
  {cont__87_18, &frame__87_8, 868, 868, 7, 57},
  {cont__87_19, &frame__87_8, 872, 872, 11, 28},
  {cont__87_20, &frame__87_8, 873, 873, 11, 24},
  {cont__87_21, &frame__87_8, 870, 879, 7, 68},
  {cont__87_39, &frame__87_8, 881, 881, 7, 56},
  {cont__87_42, &frame__87_8, 882, 882, 63, 63},
  {cont__87_43, &frame__87_8, 882, 882, 37, 64},
  {cont__87_44, &frame__87_8, 882, 882, 7, 64},
  {cont__87_45, &frame__87_8, 883, 890, 7, 27},
  {cont__87_54, &frame__87_8, 891, 931, 7, 49},
  {entry__87_1_build_library, NULL, 857, 857, 6, 23},
  {cont__87_3, &frame__87_1_build_library, 857, 857, 3, 56},
  {cont__87_6, &frame__87_1_build_library, 859, 931, 3, 51},
  {cont__87_90, &frame__87_1_build_library, 931, 931, 51, 51},
  {entry__88_6, NULL, 938, 939, 11, 42},
  {cont__88_9, &frame__88_6, 938, 939, 5, 42},
  {entry__88_13, NULL, 944, 944, 38, 65},
  {cont__88_14, &frame__88_13, 944, 944, 7, 34},
  {cont__88_15, &frame__88_13, 944, 944, 7, 65},
  {cont__88_16, &frame__88_13, 944, 944, 7, 65},
  {entry__88_19, NULL, 946, 946, 28, 65},
  {cont__88_21, &frame__88_19, 946, 946, 19, 65},
  {entry__88_18, NULL, 946, 946, 7, 65},
  {cont__88_22, &frame__88_18, 947, 947, 7, 37},
  {entry__88_1_maybe_compile_c_file, NULL, 934, 934, 3, 35},
  {cont__88_2, &frame__88_1_maybe_compile_c_file, 935, 935, 3, 35},
  {cont__88_3, &frame__88_1_maybe_compile_c_file, 936, 936, 3, 26},
  {cont__88_4, &frame__88_1_maybe_compile_c_file, 937, 937, 6, 24},
  {cont__88_5, &frame__88_1_maybe_compile_c_file, 937, 939, 3, 43},
  {cont__88_10, &frame__88_1_maybe_compile_c_file, 940, 940, 3, 26},
  {cont__88_11, &frame__88_1_maybe_compile_c_file, 943, 943, 7, 25},
  {cont__88_12, &frame__88_1_maybe_compile_c_file, 942, 944, 5, 64},
  {cont__88_17, &frame__88_1_maybe_compile_c_file, 941, 947, 3, 38},
  {entry__90_11, NULL, 963, 963, 39, 41},
  {cont__90_12, &frame__90_11, 963, 963, 36, 41},
  {cont__90_13, &frame__90_11, 963, 963, 28, 43},
  {cont__90_15, &frame__90_11, 963, 963, 21, 48},
  {cont__90_16, &frame__90_11, 963, 963, 48, 48},
  {entry__90_6, NULL, 962, 962, 13, 26},
  {cont__90_7, &frame__90_6, 962, 962, 9, 28},
  {cont__90_8, &frame__90_6, 963, 963, 16, 18},
  {cont__90_9, &frame__90_6, 963, 963, 12, 18},
  {cont__90_10, &frame__90_6, 963, 963, 9, 48},
  {cont__90_17, &frame__90_6, 964, 964, 9, 13},
  {entry__90_4, NULL, 961, 961, 10, 19},
  {cont__90_5, &frame__90_4, 961, 964, 7, 13},
  {entry__90_3, NULL, 960, 964, 5, 14},
  {cont__90_18, &frame__90_3, 964, 964, 14, 14},
  {entry__90_21, NULL, 967, 967, 27, 30},
  {cont__90_22, &frame__90_21, 967, 967, 19, 31},
  {cont__90_24, &frame__90_21, 967, 967, 7, 31},
  {cont__90_25, &frame__90_21, 967, 967, 31, 31},
  {entry__90_28, NULL, 969, 969, 33, 36},
  {cont__90_29, &frame__90_28, 969, 969, 33, 38},
  {cont__90_30, &frame__90_28, 969, 969, 33, 39},
  {cont__90_31, &frame__90_28, 969, 969, 18, 39},
  {cont__90_32, &frame__90_28, 969, 969, 39, 39},
  {entry__90_26, NULL, 969, 969, 10, 15},
  {cont__90_27, &frame__90_26, 969, 969, 7, 39},
  {entry__90_1_format_number, NULL, 957, 957, 3, 16},
  {cont__90_2, &frame__90_1_format_number, 959, 964, 3, 15},
  {cont__90_19, &frame__90_1_format_number, 966, 966, 5, 10},
  {cont__90_20, &frame__90_1_format_number, 965, 969, 3, 40},
  {cont__90_33, &frame__90_1_format_number, 970, 970, 3, 8},
  {entry__91_4, NULL, 976, 976, 37, 37},
  {cont__91_5, &frame__91_4, 976, 976, 7, 37},
  {cont__91_6, &frame__91_4, 982, 982, 20, 41},
  {cont__91_7, &frame__91_4, 982, 982, 17, 41},
  {cont__91_8, &frame__91_4, 982, 982, 9, 42},
  {cont__91_9, &frame__91_4, 983, 983, 23, 29},
  {cont__91_10, &frame__91_4, 983, 983, 9, 34},
  {cont__91_11, &frame__91_4, 977, 984, 7, 12},
  {entry__91_13, NULL, 986, 986, 47, 53},
  {cont__91_14, &frame__91_13, 986, 986, 33, 58},
  {cont__91_15, &frame__91_13, 986, 986, 7, 63},
  {entry__91_1_sim2c__write_timing_info, NULL, 973, 973, 3, 23},
  {cont__91_2, &frame__91_1_sim2c__write_timing_info, 975, 975, 5, 23},
  {cont__91_3, &frame__91_1_sim2c__write_timing_info, 974, 986, 3, 64},
  {cont__91_17, &frame__91_1_sim2c__write_timing_info, 987, 987, 3, 19},
  {cont__91_18, &frame__91_1_sim2c__write_timing_info, 987, 987, 19, 19},
  {entry__92_5, NULL, 1003, 1003, 12, 38},
  {cont__92_7, &frame__92_5, 1003, 1003, 9, 38},
  {entry__92_8, NULL, 1004, 1004, 9, 23},
  {entry__92_10, NULL, 1006, 1006, 17, 57},
  {entry__92_20, NULL, 1017, 1017, 42, 69},
  {cont__92_21, &frame__92_20, 1017, 1017, 9, 38},
  {cont__92_22, &frame__92_20, 1017, 1017, 9, 69},
  {cont__92_23, &frame__92_20, 1017, 1017, 9, 69},
  {entry__92_18, NULL, 1016, 1016, 9, 27},
  {cont__92_19, &frame__92_18, 1017, 1017, 9, 69},
  {cont__92_24, &frame__92_18, },
  {entry__92_29, NULL, 1020, 1020, 21, 61},
  {entry__92_32, NULL, 1021, 1021, 41, 59},
  {cont__92_33, &frame__92_32, 1021, 1021, 35, 64},
  {entry__92_35, NULL, 1022, 1022, 32, 54},
  {entry__92_39, NULL, 1024, 1024, 28, 64},
  {entry__92_43, NULL, 1026, 1026, 28, 67},
  {entry__92_26, NULL, 1019, 1019, 55, 67},
  {cont__92_27, &frame__92_26, 1019, 1019, 9, 67},
  {cont__92_28, &frame__92_26, 1020, 1020, 9, 61},
  {cont__92_31, &frame__92_26, 1021, 1021, 9, 64},
  {cont__92_34, &frame__92_26, 1022, 1022, 9, 54},
  {cont__92_36, &frame__92_26, 1023, 1023, 25, 37},
  {cont__92_37, &frame__92_26, 1023, 1023, 9, 37},
  {cont__92_38, &frame__92_26, 1024, 1024, 9, 64},
  {cont__92_41, &frame__92_26, 1025, 1025, 9, 39},
  {cont__92_42, &frame__92_26, 1026, 1026, 9, 67},
  {cont__92_45, &frame__92_26, 1026, 1026, 67, 67},
  {entry__92_50, NULL, 1033, 1033, 44, 71},
  {cont__92_51, &frame__92_50, 1033, 1033, 13, 40},
  {cont__92_52, &frame__92_50, 1033, 1033, 13, 71},
  {cont__92_53, &frame__92_50, 1033, 1033, 13, 71},
  {entry__92_55, NULL, 1035, 1035, 13, 43},
  {entry__92_56, NULL, 1037, 1037, 13, 64},
  {cont__92_57, &frame__92_56, 1037, 1037, 64, 64},
  {entry__92_46, NULL, 1028, 1028, 9, 30},
  {cont__92_47, &frame__92_46, 1029, 1029, 9, 32},
  {cont__92_48, &frame__92_46, 1032, 1032, 13, 31},
  {cont__92_49, &frame__92_46, 1031, 1033, 11, 70},
  {cont__92_54, &frame__92_46, 1030, 1037, 9, 65},
  {entry__92_65, NULL, 1042, 1042, 11, 39},
  {entry__92_60, NULL, 1041, 1041, 9, 62},
  {cont__92_64, &frame__92_60, 1040, 1042, 7, 40},
  {entry__92_72, NULL, 1050, 1050, 38, 63},
  {cont__92_73, &frame__92_72, 1050, 1050, 13, 63},
  {cont__92_74, &frame__92_72, 1050, 1050, 13, 63},
  {entry__92_70, NULL, 1049, 1049, 13, 45},
  {cont__92_71, &frame__92_70, 1048, 1050, 11, 62},
  {cont__92_75, &frame__92_70, 1048, 1050, 11, 62},
  {entry__92_77, NULL, 1052, 1052, 23, 23},
  {entry__92_67, NULL, 1044, 1044, 7, 30},
  {cont__92_68, &frame__92_67, 1047, 1047, 11, 27},
  {cont__92_69, &frame__92_67, 1046, 1050, 9, 63},
  {cont__92_76, &frame__92_67, 1045, 1052, 7, 24},
  {entry__92_81, NULL, 1055, 1055, 28, 75},
  {cont__92_83, &frame__92_81, 1055, 1055, 75, 75},
  {entry__92_86, NULL, 1058, 1058, 23, 58},
  {entry__92_93, NULL, 1066, 1066, 33, 45},
  {cont__92_94, &frame__92_93, 1066, 1066, 27, 45},
  {entry__92_85, NULL, 1058, 1058, 11, 58},
  {cont__92_88, &frame__92_85, 1059, 1065, 11, 24},
  {cont__92_92, &frame__92_85, 1066, 1066, 11, 45},
  {entry__92_96, NULL, 1068, 1068, 23, 51},
  {entry__92_101, NULL, 1073, 1073, 33, 55},
  {cont__92_103, &frame__92_101, 1073, 1073, 30, 55},
  {entry__92_104, NULL, 1074, 1074, 18, 33},
  {cont__92_105, &frame__92_104, 1074, 1074, 15, 33},
  {entry__92_108, NULL, 1077, 1077, 33, 45},
  {cont__92_109, &frame__92_108, 1077, 1077, 27, 45},
  {entry__92_95, NULL, 1068, 1068, 11, 51},
  {cont__92_98, &frame__92_95, 1072, 1072, 15, 32},
  {cont__92_99, &frame__92_95, 1073, 1073, 15, 28},
  {cont__92_100, &frame__92_95, 1071, 1074, 13, 32},
  {cont__92_106, &frame__92_95, 1069, 1076, 11, 24},
  {cont__92_107, &frame__92_95, 1077, 1077, 11, 45},
  {entry__92_79, NULL, 1054, 1054, 7, 52},
  {cont__92_80, &frame__92_79, 1055, 1055, 7, 75},
  {cont__92_84, &frame__92_79, 1056, 1077, 7, 46},
  {entry__92_113, NULL, 1079, 1079, 24, 41},
  {cont__92_114, &frame__92_113, 1079, 1079, 24, 41},
  {entry__92_118, NULL, 1083, 1083, 11, 25},
  {entry__92_119, NULL, 1084, 1084, 14, 38},
  {cont__92_120, &frame__92_119, 1084, 1084, 11, 38},
  {entry__92_116, NULL, 1082, 1082, 11, 39},
  {cont__92_117, &frame__92_116, 1081, 1084, 9, 37},
  {cont__92_121, &frame__92_116, 1080, 1087, 7, 44},
  {entry__92_2, NULL, 1002, 1002, 9, 26},
  {cont__92_3, &frame__92_2, 1002, 1002, 9, 38},
  {cont__92_4, &frame__92_2, 1000, 1004, 5, 24},
  {cont__92_9, &frame__92_2, 1006, 1006, 5, 57},
  {cont__92_12, &frame__92_2, 1007, 1007, 5, 41},
  {cont__92_13, &frame__92_2, 1008, 1008, 5, 41},
  {cont__92_14, &frame__92_2, 1009, 1009, 5, 33},
  {cont__92_15, &frame__92_2, 1010, 1010, 5, 28},
  {cont__92_16, &frame__92_2, 1012, 1012, 5, 24},
  {cont__92_17, &frame__92_2, },
  {cont__92_25, &frame__92_2, 1013, 1037, 5, 67},
  {cont__92_58, &frame__92_2, 1038, 1038, 5, 50},
  {cont__92_59, &frame__92_2, 1039, 1042, 5, 41},
  {cont__92_66, &frame__92_2, 1043, 1052, 5, 25},
  {cont__92_78, &frame__92_2, 1053, 1077, 5, 47},
  {cont__92_110, &frame__92_2, 1078, 1078, 41, 41},
  {cont__92_111, &frame__92_2, 1078, 1078, 5, 42},
  {cont__92_112, &frame__92_2, 1079, 1079, 8, 41},
  {cont__92_115, &frame__92_2, 1079, 1087, 5, 45},
  {entry__92_1_build_executable, NULL, 999, 1087, 3, 46},
  {entry__106_2, NULL, 108, 108, 8, 28},
  {cont__106_3, &frame__106_2, 108, 108, 5, 28},
  {entry__106_4, NULL, 111, 111, 9, 48},
  {cont__106_6, &frame__106_4, 112, 112, 9, 42},
  {cont__106_8, &frame__106_4, 110, 112, 7, 41},
  {cont__106_9, &frame__106_4, 109, 112, 5, 43},
  {entry__107_2, NULL, 117, 117, 8, 29},
  {cont__107_3, &frame__107_2, 117, 117, 5, 29},
  {entry__107_4, NULL, 120, 120, 9, 48},
  {cont__107_5, &frame__107_4, 121, 121, 9, 42},
  {cont__107_6, &frame__107_4, 119, 121, 7, 41},
  {cont__107_7, &frame__107_4, 118, 121, 5, 43},
  {entry__111_4, NULL, 141, 141, 7, 41},
  {cont__111_5, &frame__111_4, 142, 142, 10, 26},
  {cont__111_6, &frame__111_4, 142, 142, 7, 32},
  {cont__111_7, &frame__111_4, 143, 143, 7, 19},
  {cont__111_8, &frame__111_4, 144, 144, 7, 34},
  {cont__111_9, &frame__111_4, 145, 145, 10, 21},
  {cont__111_10, &frame__111_4, 145, 145, 7, 27},
  {cont__111_11, &frame__111_4, 146, 146, 20, 20},
  {entry__111_3, NULL, 140, 146, 5, 20},
  {cont__111_12, &frame__111_3, 146, 146, 20, 20},
  {entry__111_1, NULL, 137, 137, 3, 31},
  {cont__111_2, &frame__111_1, 139, 146, 3, 21},
  {entry__138_4, NULL, 175, 175, 41, 79},
  {entry__138_2, NULL, 175, 175, 8, 38},
  {cont__138_3, &frame__138_2, 175, 175, 5, 79},
  {cont__138_6, &frame__138_2, 176, 176, 5, 45},
  {cont__138_7, &frame__138_2, 176, 176, 45, 45},
  {entry__138_9, NULL, 182, 183, 7, 52},
  {entry__138_12, NULL, 185, 186, 7, 34},
  {entry__138_15, NULL, 188, 189, 7, 57},
  {entry__138_18, NULL, 191, 192, 7, 71},
  {entry__138_21, NULL, 194, 195, 7, 47},
  {entry__138_24, NULL, 197, 198, 7, 61},
  {entry__138_27, NULL, 200, 203, 9, 29},
  {entry__138_30, NULL, 207, 208, 7, 33},
  {entry__138_33, NULL, 210, 211, 7, 29},
  {entry__138_36, NULL, 213, 214, 7, 42},
  {entry__138_39, NULL, 216, 217, 7, 34},
  {entry__138_42, NULL, 219, 220, 7, 35},
  {entry__138_45, NULL, 222, 223, 7, 40},
  {entry__138_48, NULL, 225, 226, 9, 65},
  {entry__138_51, NULL, 230, 231, 7, 35},
  {entry__138_54, NULL, 233, 234, 7, 45},
  {entry__138_57, NULL, 236, 237, 9, 31},
  {entry__138_60, NULL, 241, 242, 7, 32},
  {entry__138_63, NULL, 244, 245, 7, 33},
  {entry__138_66, NULL, 247, 248, 7, 43},
  {entry__138_69, NULL, 250, 251, 7, 29},
  {entry__138_72, NULL, 253, 254, 7, 46},
  {entry__138_8, NULL, 178, 254, 5, 47},
  {cont__138_75, &frame__138_8, 254, 254, 48, 48},
  {entry__142_1, NULL, 258, 258, 37, 37},
  {entry__149_4, NULL, 283, 283, 3, 45},
  {cont__149_6, &frame__149_4, 283, 283, 45, 45},
  {entry__150_5, NULL, 287, 287, 5, 29},
  {cont__150_7, &frame__150_5, 288, 288, 5, 35},
  {cont__150_9, &frame__150_5, 288, 288, 35, 35},
  {entry__151_1, NULL, 291, 291, 20, 30},
  {cont__151_3, &frame__151_1, 291, 291, 3, 30},
  {cont__151_4, &frame__151_1, 291, 291, 30, 30},
  {entry__153_3, NULL, 295, 295, 3, 26},
  {cont__153_4, &frame__153_3, 295, 295, 26, 26},
  {entry__155_3, NULL, 299, 299, 3, 25},
  {cont__155_4, &frame__155_3, 299, 299, 25, 25},
  {entry__173_2, NULL, 641, 642, 9, 51},
  {cont__173_5, &frame__173_2, 641, 642, 3, 51},
  {entry__188_1, NULL, 1089, 1089, 20, 36},
  {cont__188_2, &frame__188_1, 1089, 1089, 36, 36},
  {entry__189_4, NULL, 1096, 1096, 7, 32},
  {entry__189_3, NULL, },
  {cont__189_5, &frame__189_3, },
  {entry__189_2, NULL, },
  {cont__189_6, &frame__189_2, },
  {entry__189_1, NULL, },
  {cont__189_7, &frame__189_1, 1091, 1097, 3, 24},
  {entry__189_8, NULL, 1098, 1098, 3, 23},
  {entry__189_9, NULL, 1099, 1099, 3, 43},
  {entry__189_10, NULL, 1100, 1100, 3, 57},
  {entry__189_11, NULL, 1101, 1101, 6, 29},
  {cont__189_12, &frame__189_11, 1101, 1101, 3, 43}
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
  arguments->slots[0] = string__96_1;
  result_count = 0;
  myself = get__copyright();
  func = myself->type;
  frame->cont = cont__96_2;
}
static void cont__96_2(void) {
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
  frame->cont = cont__97_1;
}
static void cont__97_1(void) {
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
  frame->cont = cont__98_1;
}
static void cont__98_1(void) {
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
  frame->cont = cont__99_1;
}
static void cont__99_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._REVISION, arguments->slots[0]);
  // 96: $VERSION "@(MAJOR).@(MINOR).@(REVISION)"
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = var._MAJOR;
  arguments->slots[1] = string__100_1;
  arguments->slots[2] = var._MINOR;
  arguments->slots[3] = string__100_1;
  arguments->slots[4] = var._REVISION;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__100_2;
}
static void cont__100_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._VERSION, arguments->slots[0]);
  // 98: version VERSION
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._VERSION;
  result_count = 0;
  myself = get__version();
  func = myself->type;
  frame->cont = cont__101_1;
}
static void cont__101_1(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 100: ... c_compiler()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__c_compiler();
  func = myself->type;
  frame->cont = cont__102_1;
}
static void cont__102_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 100: extern $cc c_compiler()
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__extern();
  func = myself->type;
  frame->cont = cont__102_2;
}
static void cont__102_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._cc, arguments->slots[0]);
  // 101: extern $mkdir "mkdir" # would be nice to have one in the system library!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__103_1;
  result_count = 1;
  myself = get__extern();
  func = myself->type;
  frame->cont = cont__103_2;
}
static void cont__103_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._mkdir, arguments->slots[0]);
  // 102: $SIMLIBPATH environment("SIMLIBPATH")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__104_1;
  result_count = 1;
  myself = get__environment();
  func = myself->type;
  frame->cont = cont__104_2;
}
static void cont__104_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._SIMLIBPATH, arguments->slots[0]);
  // 103: $SIMDATAPATH environment("SIMDATAPATH")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__105_1;
  result_count = 1;
  myself = get__environment();
  func = myself->type;
  frame->cont = cont__105_2;
}
static void cont__105_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._SIMDATAPATH, arguments->slots[0]);
  // 107: SIMLIBPATH.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._SIMLIBPATH;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__106_1;
}
static void cont__106_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 105: $simlibpaths
  // 106:   if
  // 107:     SIMLIBPATH.is_defined
  // 108:     -> split(SIMLIBPATH ':')
  // 109:     ->
  // 110:       list
  // 111:         "/usr/local/share/simplicity-@(VERSION)"
  // 112:         "/usr/share/simplicity-@(VERSION)"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__106_2;
  arguments->slots[2] = func__106_4;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__106_10;
}
static void entry__106_2(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 108: ... split(SIMLIBPATH ':')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._SIMLIBPATH;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__split();
  func = myself->type;
  frame->cont = cont__106_3;
}
static void cont__106_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 108: -> split(SIMLIBPATH ':')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__106_4(void) {
  allocate_initialized_frame_gc(0, 3);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 111: "/usr/local/share/simplicity-@(VERSION)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__106_5;
  arguments->slots[1] = var._VERSION;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__106_6;
}
static void cont__106_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 112: "/usr/share/simplicity-@(VERSION)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__106_7;
  arguments->slots[1] = var._VERSION;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__106_8;
}
static void cont__106_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 110: list
  // 111:   "/usr/local/share/simplicity-@(VERSION)"
  // 112:   "/usr/share/simplicity-@(VERSION)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  arguments->slots[1] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__106_9;
}
static void cont__106_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 109: ->
  // 110:   list
  // 111:     "/usr/local/share/simplicity-@(VERSION)"
  // 112:     "/usr/share/simplicity-@(VERSION)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__106_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._simlibpaths, arguments->slots[0]);
  // 116: SIMDATAPATH.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._SIMDATAPATH;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__107_1;
}
static void cont__107_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 114: $simdatapaths
  // 115:   if
  // 116:     SIMDATAPATH.is_defined
  // 117:     -> split(SIMDATAPATH ':')
  // 118:     ->
  // 119:       list
  // 120:         "/usr/local/share/simplicity-@(VERSION)"
  // 121:         "/usr/share/simplicity-@(VERSION)"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__107_2;
  arguments->slots[2] = func__107_4;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__107_8;
}
static void entry__107_2(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 117: ... split(SIMDATAPATH ':')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._SIMDATAPATH;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__split();
  func = myself->type;
  frame->cont = cont__107_3;
}
static void cont__107_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 117: -> split(SIMDATAPATH ':')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__107_4(void) {
  allocate_initialized_frame_gc(0, 3);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 120: "/usr/local/share/simplicity-@(VERSION)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__106_5;
  arguments->slots[1] = var._VERSION;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__107_5;
}
static void cont__107_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 121: "/usr/share/simplicity-@(VERSION)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__106_7;
  arguments->slots[1] = var._VERSION;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__107_6;
}
static void cont__107_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 119: list
  // 120:   "/usr/local/share/simplicity-@(VERSION)"
  // 121:   "/usr/share/simplicity-@(VERSION)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  arguments->slots[1] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__107_7;
}
static void cont__107_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 118: ->
  // 119:   list
  // 120:     "/usr/local/share/simplicity-@(VERSION)"
  // 121:     "/usr/share/simplicity-@(VERSION)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__107_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._simdatapaths, arguments->slots[0]);
  // 127: "bsd" = "posix"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__80_24;
  arguments->slots[1] = string__109_1;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__109_2;
}
static void cont__109_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 128: "cygwin" = "posix"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__87_37;
  arguments->slots[1] = string__109_1;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__109_3;
}
static void cont__109_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 129: "darwin" = "posix"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__87_38;
  arguments->slots[1] = string__109_1;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__109_4;
}
static void cont__109_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 130: "linux" = "posix"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__80_23;
  arguments->slots[1] = string__109_1;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__109_5;
}
static void cont__109_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 131: "posix" = "all"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__109_1;
  arguments->slots[1] = string__109_6;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__109_7;
}
static void cont__109_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 132: "win" = "all"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__109_8;
  arguments->slots[1] = string__109_6;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__109_9;
}
static void cont__109_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 133: "all" = NONE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__109_6;
  arguments->slots[1] = var._NONE;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__109_10;
}
static void cont__109_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__7 */ = arguments->slots[0];
  // 125: $supported_platforms
  // 126:   key_order_table
  // 127:     "bsd" = "posix"
  // 128:     "cygwin" = "posix"
  // 129:     "darwin" = "posix"
  // 130:     "linux" = "posix"
  // 131:     "posix" = "all"
  // 132:     "win" = "all"
  // 133:     "all" = NONE
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
  frame->cont = cont__109_11;
}
static void cont__109_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._supported_platforms, arguments->slots[0]);
  // 135: $$platform_priority empty_table
  var._platform_priority = get__empty_table();
  // 136: do:
  // 137:   $$platform operating_system()
  // 138:   $$priority 0
  // 139:   do: (-> break)
  // 140:     forever:
  // 141:       $plat supported_platforms(platform)
  // 142:       if plat.is_undefined break
  // 143:       inc &priority
  // 144:       !platform_priority(platform) priority
  // 145:       if plat == NONE break
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__111_1;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__111_13;
}
static void entry__111_3(void) {
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
  // 140: ... :
  // 141:   $plat supported_platforms(platform)
  // 142:   if plat.is_undefined break
  // 143:   inc &priority
  // 144:   !platform_priority(platform) priority
  // 145:   if plat == NONE break
  // 146:   !platform plat
  frame->slots[3] /* temp__1 */ = create_closure(entry__111_4, 0);
  // 140: forever:
  // 141:   $plat supported_platforms(platform)
  // 142:   if plat.is_undefined break
  // 143:   inc &priority
  // 144:   !platform_priority(platform) priority
  // 145:   if plat == NONE break
  // 146:   !platform plat
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame->cont = cont__111_12;
}
static void entry__111_4(void) {
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
  // 141: $plat supported_platforms(platform)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* platform */;
  result_count = 1;
  myself = var._supported_platforms;
  func = myself->type;
  frame->cont = cont__111_5;
}
static void cont__111_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* plat */, arguments->slots[0]);
  // 142: ... plat.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* plat */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__111_6;
}
static void cont__111_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 142: if plat.is_undefined break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* break */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__111_7;
}
static void cont__111_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 143: inc &priority
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* priority */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__111_8;
}
static void cont__111_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* priority */ = arguments->slots[0];
  // 144: !platform_priority(platform) priority
  frame->slots[4] /* temp__1 */ = ((CELL *)frame->slots[2])->contents /* priority */;
  // 144: !platform_priority(platform)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* platform */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = var._platform_priority;
  func = myself->type;
  frame->cont = cont__111_9;
}
static void cont__111_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._platform_priority = arguments->slots[0];
  // 145: ... plat == NONE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* plat */;
  arguments->slots[1] = var._NONE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__111_10;
}
static void cont__111_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 145: if plat == NONE break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* break */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__111_11;
}
static void cont__111_11(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 146: !platform plat
  ((CELL *)frame->slots[0])->contents /* platform */ = frame->slots[3] /* plat */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__111_12(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__111_1(void) {
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
  // 137: $$platform operating_system()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__operating_system();
  func = myself->type;
  frame->cont = cont__111_2;
}
static void cont__111_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* platform */ = arguments->slots[0];
  // 138: $$priority 0
  ((CELL *)frame->slots[1])->contents /* priority */ = number__0;
  // 139: ... : (-> break)
  // 140:   forever:
  // 141:     $plat supported_platforms(platform)
  // 142:     if plat.is_undefined break
  // 143:     inc &priority
  // 144:     !platform_priority(platform) priority
  // 145:     if plat == NONE break
  // 146:     !platform plat
  frame->slots[2] /* temp__1 */ = create_closure(entry__111_3, 0);
  // 139: do: (-> break)
  // 140:   forever:
  // 141:     $plat supported_platforms(platform)
  // 142:     if plat.is_undefined break
  // 143:     inc &priority
  // 144:     !platform_priority(platform) priority
  // 145:     if plat == NONE break
  // 146:     !platform plat
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__do();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__111_13(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 147: $$platform_specific_priority undefined
  var._platform_specific_priority = get__undefined();
  // 148: $$module_info empty_table
  var._module_info = get__empty_table();
  // 149: $$meta_levels empty_table # 0 -> no meta files
  var._meta_levels = get__empty_table();
  // 150: $$do_rebuild false
  var._do_rebuild = get__false();
  // 151: $$do_omit_meta false
  var._do_omit_meta = get__false();
  // 152: $$sim2c::do_dump_trees false
  var.sim2c__do_dump_trees = get__false();
  // 153: $$sim2c::do_pretty_print false
  var.sim2c__do_pretty_print = get__false();
  // 154: $$sim2c::do_print_simplified_source false
  var.sim2c__do_print_simplified_source = get__false();
  // 155: $$sim2c::do_show_debug_infos false
  var.sim2c__do_show_debug_infos = get__false();
  // 156: $$sim2c::do_show_compiler_debug_infos false
  var.sim2c__do_show_compiler_debug_infos = get__false();
  // 157: $$sim2c::do_check_only false
  var.sim2c__do_check_only = get__false();
  // 158: $$sim2c::do_show_brief_messages false
  var.sim2c__do_show_brief_messages = get__false();
  // 159: $$sim2c::do_print_warnings false
  var.sim2c__do_print_warnings = get__false();
  // 160: $$sim2c::do_print_missing false
  var.sim2c__do_print_missing = get__false();
  // 161: $$sim2c::do_print_summary false
  var.sim2c__do_print_summary = get__false();
  // 162: $$sim2c::verbose false
  var.sim2c__verbose = get__false();
  // 163: $$do_print_c false
  var._do_print_c = get__false();
  // 164: $$sim2c::do_extract_documentation false
  var.sim2c__do_extract_documentation = get__false();
  // 165: $$do_build_codeblocks_project false
  var._do_build_codeblocks_project = get__false();
  // 166: $$do_list_dependencies false
  var._do_list_dependencies = get__false();
  // 167: $$do_build_static false
  var._do_build_static = get__false();
  // 168: $$do_link_profiler false
  var._do_link_profiler = get__false();
  // 169: $$sim2c::do_time_passes false
  var.sim2c__do_time_passes = get__false();
  // 170: $$module_prefix undefined
  var._module_prefix = get__undefined();
  // 171: $$input_filename undefined
  var._input_filename = get__undefined();
  // 172: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__137_1;
}
static void cont__137_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 172: ... truncate_until(program_name '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__program_name();
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__137_2;
}
static void cont__137_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 172: $action truncate_until(program_name '/' -1) .truncate_from. '-'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = character__45;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__137_3;
}
static void cont__137_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._action, arguments->slots[0]);
  // 174: action == "simrun"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._action;
  arguments->slots[1] = string__87_2;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__138_1;
}
static void cont__138_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 173: if
  // 174:   action == "simrun":
  // 175:     if command_line_arguments.is_empty: Error "Missing command line arguments!"
  // 176:     !input_filename command_line_arguments(1)
  // 177:   :
  // 178:     program_parameters
  // 179:       # the following options act on a single file only
  // 180:       
  // 181:       !sim2c::do_check_only
  // 182:       -> "check-only" "
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__138_2;
  arguments->slots[2] = func__138_8;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__138_76;
}
static void entry__138_2(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 175: ... command_line_arguments.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__command_line_arguments();
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__138_3;
}
static void cont__138_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 175: if command_line_arguments.is_empty: Error "Missing command line arguments!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__138_4;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__138_6;
}
static void entry__138_4(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 175: ... Error "Missing command line arguments!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__138_5;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__138_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 176: !input_filename command_line_arguments(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__command_line_arguments();
  func = myself->type;
  frame->cont = cont__138_7;
}
static void cont__138_7(void) {
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
static void entry__138_8(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 178: program_parameters
  // 179:   # the following options act on a single file only
  // 180:   
  // 181:   !sim2c::do_check_only
  // 182:   -> "check-only" "
  // 183:     do not compile; just check for syntax errors
  // 184:   !sim2c::do_dump_trees
  // 185:   -> "dump-trees" "
  // 186:     dump abstract syntax trees
  // 187:   !sim2c::do_pretty_print
  // ...
  argument_count = 22;
  arguments = node_p;
  arguments->slots[0] = func__138_9;
  arguments->slots[1] = func__138_12;
  arguments->slots[2] = func__138_15;
  arguments->slots[3] = func__138_18;
  arguments->slots[4] = func__138_21;
  arguments->slots[5] = func__138_24;
  arguments->slots[6] = func__138_27;
  arguments->slots[7] = func__138_30;
  arguments->slots[8] = func__138_33;
  arguments->slots[9] = func__138_36;
  arguments->slots[10] = func__138_39;
  arguments->slots[11] = func__138_42;
  arguments->slots[12] = func__138_45;
  arguments->slots[13] = func__138_48;
  arguments->slots[14] = func__138_51;
  arguments->slots[15] = func__138_54;
  arguments->slots[16] = func__138_57;
  arguments->slots[17] = func__138_60;
  arguments->slots[18] = func__138_63;
  arguments->slots[19] = func__138_66;
  arguments->slots[20] = func__138_69;
  arguments->slots[21] = func__138_72;
  result_count = 22;
  myself = get__program_parameters();
  func = myself->type;
  frame->cont = cont__138_75;
}
static void entry__138_9(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 182: -> "check-only" "
  // 183:   do not compile; just check for syntax errors
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__138_10;
  arguments->slots[1] = string__138_11;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__138_12(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 185: -> "dump-trees" "
  // 186:   dump abstract syntax trees
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__138_13;
  arguments->slots[1] = string__138_14;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__138_15(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 188: -> "pretty-print" "
  // 189:   do not compile; just pretty print the source file
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__138_16;
  arguments->slots[1] = string__138_17;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__138_18(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 191: -> "print-simplified-source" "
  // 192:   do not generate a C-file; just print the simplified source text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__138_19;
  arguments->slots[1] = string__138_20;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__138_21(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 194: -> "print-c" "
  // 195:   print C source code for a single module
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__138_22;
  arguments->slots[1] = string__138_23;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__138_24(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 197: -> "time-passes" "
  // 198:   print running time for the individual compiler passes
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__138_25;
  arguments->slots[1] = string__138_26;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__138_27(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 200: -> VALUED_OPTION "module-prefix" "
  // 201:   needed to compile a single file within a subdirectory;
  // 202:   if the subdirectories are nested use slashes to separate
  // 203:   the directory names
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__VALUED_OPTION();
  arguments->slots[1] = string__138_28;
  arguments->slots[2] = string__138_29;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__138_30(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 207: -> "brief" "
  // 208:   show brief error messages
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__138_31;
  arguments->slots[1] = string__138_32;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__138_33(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 210: -> "warnings" "
  // 211:   show warning messages
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__138_34;
  arguments->slots[1] = string__138_35;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__138_36(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 213: -> "missing" "
  // 214:   inform about missing documentation
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__138_37;
  arguments->slots[1] = string__138_38;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__138_39(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 216: -> "summary" "
  // 217:   show a statistical summary
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__138_40;
  arguments->slots[1] = string__138_41;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__138_42(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 219: -> "verbose" "
  // 220:   output verbose informations
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__138_43;
  arguments->slots[1] = string__138_44;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__138_45(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 222: -> "debug" "
  // 223:   show C-compiler and linker calls
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__138_46;
  arguments->slots[1] = string__138_47;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__138_48(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 225: -> "debug_compiler" "
  // 226:   show internal debug messages of the Simplicity compiler
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__138_49;
  arguments->slots[1] = string__138_50;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__138_51(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 230: -> "codeblocks" "
  // 231:   create Code::Blocks project
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__138_52;
  arguments->slots[1] = string__138_53;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__138_54(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 233: -> "extract-documentation" "
  // 234:   extract documentation encoded as HTML
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__138_55;
  arguments->slots[1] = string__138_56;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__138_57(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 236: -> "list-dependencies" "
  // 237:   list all dependencies
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__138_58;
  arguments->slots[1] = string__138_59;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__138_60(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 241: -> "rebuild" "
  // 242:   rebuild all source files
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__138_61;
  arguments->slots[1] = string__138_62;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__138_63(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 244: -> "omit-meta" "
  // 245:   do not rebuild meta files
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__138_64;
  arguments->slots[1] = string__138_65;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__138_66(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 247: -> "static" "
  // 248:   create statically linked executable
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__138_67;
  arguments->slots[1] = string__138_68;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__138_69(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 250: -> "profile" "
  // 251:   link with libprofiler
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__138_70;
  arguments->slots[1] = string__138_71;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__138_72(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 253: -> std::MANDATORY_PARAMETER "filename" "
  // 254:   the name of the source file to compile
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__std__MANDATORY_PARAMETER();
  arguments->slots[1] = string__138_73;
  arguments->slots[2] = string__138_74;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__138_75(void) {
  if (argument_count != 22) {
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
  var.sim2c__do_print_missing = arguments->slots[9];
  var.sim2c__do_print_summary = arguments->slots[10];
  var.sim2c__verbose = arguments->slots[11];
  var.sim2c__do_show_debug_infos = arguments->slots[12];
  var.sim2c__do_show_compiler_debug_infos = arguments->slots[13];
  var._do_build_codeblocks_project = arguments->slots[14];
  set__do_extract_documentation(arguments->slots[15]);
  var._do_list_dependencies = arguments->slots[16];
  var._do_rebuild = arguments->slots[17];
  var._do_omit_meta = arguments->slots[18];
  var._do_build_static = arguments->slots[19];
  var._do_link_profiler = arguments->slots[20];
  var._input_filename = arguments->slots[21];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__138_76(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 255: %main_filename fullname(input_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._input_filename;
  result_count = 1;
  myself = get__fullname();
  func = myself->type;
  frame->cont = cont__139_1;
}
static void cont__139_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(get__main_filename(), arguments->slots[0]);
  // 256: %main_info stat(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__140_1;
}
static void cont__140_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(get__main_info(), arguments->slots[0]);
  // 257: %do_build_static_executable do_build_static
  initialize_future(get__do_build_static_executable(), var._do_build_static);
  // 258: if do_show_debug_infos: !verbose true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_show_debug_infos();
  arguments->slots[1] = func__142_1;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__142_2;
}
static void entry__142_1(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 258: ... !verbose true
  set__verbose(get__true());
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__142_2(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 266: %mode undefined # EXE or LIB
  initialize_maybe_future(get__mode(), get__undefined());
  // 267: $WHITESPACE many(' ')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__32;
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__147_1;
}
static void cont__147_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._WHITESPACE, arguments->slots[0]);
  // 269: $$cc_options
  // 270:   list
  // 271:     "-Wall"
  // 272:     "-Wno-unused-function"
  // 273:     "-Wno-unused-variable"
  // 274:     "-Wno-parentheses"
  // 275:     "-Wno-switch"
  // 276:     "-Wno-trigraphs"
  // 277:     "-O1"
  // 278:     "-fPIC"
  // ...
  argument_count = 10;
  arguments = node_p;
  arguments->slots[0] = string__148_1;
  arguments->slots[1] = string__148_2;
  arguments->slots[2] = string__148_3;
  arguments->slots[3] = string__148_4;
  arguments->slots[4] = string__148_5;
  arguments->slots[5] = string__148_6;
  arguments->slots[6] = string__148_7;
  arguments->slots[7] = string__148_8;
  arguments->slots[8] = string__148_9;
  arguments->slots[9] = string__148_10;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__148_11;
}
static void cont__148_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._cc_options = arguments->slots[0];
  // 282: ... c_compiler()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__c_compiler();
  func = myself->type;
  frame->cont = cont__149_1;
}
static void cont__149_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 282: ... c_compiler() == "gcc"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  arguments->slots[1] = string__149_2;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__149_3;
}
static void cont__149_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 282: if c_compiler() == "gcc":
  // 283:   push &cc_options "-Wno-maybe-uninitialized"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__149_4;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__149_7;
}
static void entry__149_4(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 283: push &cc_options "-Wno-maybe-uninitialized"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._cc_options;
  arguments->slots[1] = string__149_5;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__149_6;
}
static void cont__149_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._cc_options = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__149_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 285: ... hardware_architecture()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__hardware_architecture();
  func = myself->type;
  frame->cont = cont__150_1;
}
static void cont__150_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 286: "x86_32", "x86_64"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__150_2;
  arguments->slots[1] = string__150_3;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__150_4;
}
static void cont__150_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 285: case hardware_architecture()
  // 286:   "x86_32", "x86_64":
  // 287:     push &cc_options "-msse2"
  // 288:     push &cc_options "-mfpmath=sse"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* temp__2 */;
  arguments->slots[2] = func__150_5;
  result_count = 0;
  myself = get__case();
  func = myself->type;
  frame->cont = cont__150_10;
}
static void entry__150_5(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 287: push &cc_options "-msse2"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._cc_options;
  arguments->slots[1] = string__150_6;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__150_7;
}
static void cont__150_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._cc_options = arguments->slots[0];
  // 288: push &cc_options "-mfpmath=sse"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._cc_options;
  arguments->slots[1] = string__150_8;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__150_9;
}
static void cont__150_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._cc_options = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__150_10(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 290: for_each simdatapaths: (path)
  // 291:   push &cc_options "-I@(path)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._simdatapaths;
  arguments->slots[1] = func__151_1;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__151_5;
}
static void entry__151_1(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // path: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 291: ... "-I@(path)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__151_2;
  arguments->slots[1] = frame->slots[0] /* path */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__151_3;
}
static void cont__151_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 291: push &cc_options "-I@(path)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._cc_options;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__151_4;
}
static void cont__151_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._cc_options = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__151_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 293: $$cpp_options empty_list
  var._cpp_options = get__empty_list();
  // 294: ... CPPFLAGS()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__CPPFLAGS();
  func = myself->type;
  frame->cont = cont__153_1;
}
static void cont__153_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 294: ... split(CPPFLAGS())
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__split();
  func = myself->type;
  frame->cont = cont__153_2;
}
static void cont__153_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 294: for_each split(CPPFLAGS()): (option)
  // 295:   push &cpp_options option
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__153_3;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__153_5;
}
static void entry__153_3(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // option: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 295: push &cpp_options option
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._cpp_options;
  arguments->slots[1] = frame->slots[0] /* option */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__153_4;
}
static void cont__153_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._cpp_options = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__153_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 297: $$ld_options empty_list
  var._ld_options = get__empty_list();
  // 298: ... LDFLAGS()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__LDFLAGS();
  func = myself->type;
  frame->cont = cont__155_1;
}
static void cont__155_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 298: ... split(LDFLAGS())
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__split();
  func = myself->type;
  frame->cont = cont__155_2;
}
static void cont__155_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 298: for_each split(LDFLAGS()): (option)
  // 299:   push &ld_options option
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__155_3;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__155_5;
}
static void entry__155_3(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // option: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 299: push &ld_options option
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._ld_options;
  arguments->slots[1] = frame->slots[0] /* option */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__155_4;
}
static void cont__155_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._ld_options = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__155_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 301: %on_top_level true # set to false while building meta-files
  initialize_maybe_future(get__on_top_level(), get__true());
  // 302: %%objects empty_insert_order_set
  set__objects(get__empty_insert_order_set());
  // 303: %%libraries empty_insert_order_set # contains "-lsim-..."-entries
  set__libraries(get__empty_insert_order_set());
  // 304: %%do_link false
  set__do_link(get__false());
  // 305: %%last_modification_time undefined
  set__last_modification_time(get__undefined());
  // 306: $$c_sources empty_insert_order_set
  var._c_sources = get__empty_insert_order_set();
  // 307: $$dependencies empty_list
  var._dependencies = get__empty_list();
  // 308: $$resolved_libraries undefined
  var._resolved_libraries = get__undefined();
  // 640: ... main_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_info();
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__173_1;
}
static void cont__173_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 640: if main_info.is_undefined:
  // 641:   Error "
  // 642:     Source file "@(main_filename)" does not exist!@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__173_2;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__173_6;
}
static void entry__173_2(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 641: ... "
  // 642:   Source file "@(main_filename)" does not exist!@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__173_3;
  arguments->slots[1] = get__main_filename();
  arguments->slots[2] = string__173_4;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__173_5;
}
static void cont__173_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 641: Error "
  // 642:   Source file "@(main_filename)" does not exist!@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__173_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 949: $$t undefined
  var._t = get__undefined();
  // 1089: if do_time_passes: !t current_time()
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = func__188_1;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__188_3;
}
static void entry__188_1(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1089: ... !t current_time()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__current_time();
  func = myself->type;
  frame->cont = cont__188_2;
}
static void cont__188_2(void) {
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
static void cont__188_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1090: cond
  // 1091:   ->
  // 1092:     ||
  // 1093:       do_check_only
  // 1094:       do_dump_trees
  // 1095:       do_pretty_print
  // 1096:       do_print_simplified_source
  // 1097:     dump_source_or_check
  // 1098:   -> do_print_c print_c
  // 1099:   -> do_list_dependencies list_dependencies
  // ...
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = func__189_1;
  arguments->slots[1] = func__189_8;
  arguments->slots[2] = func__189_9;
  arguments->slots[3] = func__189_10;
  arguments->slots[4] = func__189_11;
  arguments->slots[5] = var._build_executable;
  result_count = 0;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__189_13;
}
static void entry__189_1(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_check_only();
  arguments->slots[1] = func__189_2;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__189_7;
}
static void entry__189_2(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_dump_trees();
  arguments->slots[1] = func__189_3;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__189_6;
}
static void entry__189_3(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_pretty_print();
  arguments->slots[1] = func__189_4;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__189_5;
}
static void entry__189_4(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1096: do_print_simplified_source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__do_print_simplified_source();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__189_5(void) {
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
static void cont__189_6(void) {
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
static void cont__189_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1091: ->
  // 1092:   ||
  // 1093:     do_check_only
  // 1094:     do_dump_trees
  // 1095:     do_pretty_print
  // 1096:     do_print_simplified_source
  // 1097:   dump_source_or_check
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = var._dump_source_or_check;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__189_8(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1098: -> do_print_c print_c
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_print_c;
  arguments->slots[1] = var._print_c;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__189_9(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1099: -> do_list_dependencies list_dependencies
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_list_dependencies;
  arguments->slots[1] = var._list_dependencies;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__189_10(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1100: -> do_build_codeblocks_project build_codeblocks_project
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_build_codeblocks_project;
  arguments->slots[1] = var._build_codeblocks_project;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__189_11(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1101: ... main_info.is_a_directory
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_info();
  result_count = 1;
  myself = get__is_a_directory();
  func = myself->type;
  frame->cont = cont__189_12;
}
static void cont__189_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1101: -> main_info.is_a_directory build_library
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = var._build_library;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__189_13(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = get__std__terminate();
  func = myself->type;
  frame->cont = cont__190_1;
}
static void cont__190_1(void) {
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
  // 261: ... ewriteln args*
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
  // 261: ... : ewriteln args*
  frame->slots[1] /* temp__1 */ = create_closure(entry__48_2, 0);
  // 261: if do_show_compiler_debug_infos: ewriteln args*
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_show_compiler_debug_infos();
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__69_1_resolve_filename(void) {
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
  // 311: ... resolved_libraries.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._resolved_libraries;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__69_2;
}
static void cont__69_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 311: if resolved_libraries.is_undefined:
  // 312:   !resolved_libraries empty_table
  // 313:   for_each simlibpaths: (path)
  // 314:     if file_exists(path):
  // 315:       for_each directory(path): (entry)
  // 316:         if entry.is_a_directory:
  // 317:           $name std::filename_of(entry)
  // 318:           if name .matches. NAME: !resolved_libraries(name) fullname_of(entry)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = func__69_3;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__69_16;
}
static void entry__69_13(void) {
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
  // 318: ... !resolved_libraries(name) fullname_of(entry)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* entry */;
  result_count = 1;
  myself = get__fullname_of();
  func = myself->type;
  frame->cont = cont__69_14;
}
static void cont__69_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 318: ... !resolved_libraries(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = var._resolved_libraries;
  func = myself->type;
  frame->cont = cont__69_15;
}
static void cont__69_15(void) {
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
static void entry__69_10(void) {
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
  // 317: $name std::filename_of(entry)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* entry */;
  result_count = 1;
  myself = get__std__filename_of();
  func = myself->type;
  frame->cont = cont__69_11;
}
static void cont__69_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* name */, arguments->slots[0]);
  // 318: ... name .matches. NAME
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* name */;
  arguments->slots[1] = get__NAME();
  result_count = 1;
  myself = get__matches();
  func = myself->type;
  frame->cont = cont__69_12;
}
static void cont__69_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 318: ... : !resolved_libraries(name) fullname_of(entry)
  frame->slots[3] /* temp__2 */ = create_closure(entry__69_13, 0);
  // 318: if name .matches. NAME: !resolved_libraries(name) fullname_of(entry)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__69_8(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // entry: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 316: ... entry.is_a_directory
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* entry */;
  result_count = 1;
  myself = get__is_a_directory();
  func = myself->type;
  frame->cont = cont__69_9;
}
static void cont__69_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 316: ... :
  // 317:   $name std::filename_of(entry)
  // 318:   if name .matches. NAME: !resolved_libraries(name) fullname_of(entry)
  frame->slots[2] /* temp__2 */ = create_closure(entry__69_10, 0);
  // 316: if entry.is_a_directory:
  // 317:   $name std::filename_of(entry)
  // 318:   if name .matches. NAME: !resolved_libraries(name) fullname_of(entry)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__69_6(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // path: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* path */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 315: ... directory(path)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* path */;
  result_count = 1;
  myself = get__directory();
  func = myself->type;
  frame->cont = cont__69_7;
}
static void cont__69_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 315: for_each directory(path): (entry)
  // 316:   if entry.is_a_directory:
  // 317:     $name std::filename_of(entry)
  // 318:     if name .matches. NAME: !resolved_libraries(name) fullname_of(entry)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__69_8;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__69_4(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // path: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 314: ... file_exists(path)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* path */;
  result_count = 1;
  myself = get__file_exists();
  func = myself->type;
  frame->cont = cont__69_5;
}
static void cont__69_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 314: ... :
  // 315:   for_each directory(path): (entry)
  // 316:     if entry.is_a_directory:
  // 317:       $name std::filename_of(entry)
  // 318:       if name .matches. NAME: !resolved_libraries(name) fullname_of(entry)
  frame->slots[2] /* temp__2 */ = create_closure(entry__69_6, 0);
  // 314: if file_exists(path):
  // 315:   for_each directory(path): (entry)
  // 316:     if entry.is_a_directory:
  // 317:       $name std::filename_of(entry)
  // 318:       if name .matches. NAME: !resolved_libraries(name) fullname_of(entry)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__69_3(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 312: !resolved_libraries empty_table
  var._resolved_libraries = get__empty_table();
  // 313: for_each simlibpaths: (path)
  // 314:   if file_exists(path):
  // 315:     for_each directory(path): (entry)
  // 316:       if entry.is_a_directory:
  // 317:         $name std::filename_of(entry)
  // 318:         if name .matches. NAME: !resolved_libraries(name) fullname_of(entry)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._simlibpaths;
  arguments->slots[1] = func__69_4;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__69_16(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 319: $libname filename .before. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__69_17;
}
static void cont__69_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* libname */, arguments->slots[0]);
  // 320: $libpath resolved_libraries(libname)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* libname */;
  result_count = 1;
  myself = var._resolved_libraries;
  func = myself->type;
  frame->cont = cont__69_18;
}
static void cont__69_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* libpath */, arguments->slots[0]);
  // 321: ... libpath.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* libpath */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__69_19;
}
static void cont__69_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 321: ... :
  // 322:   Error "
  // 323:     Cannot resolve required library "@(libname)@quot;!@
  frame->slots[4] /* temp__2 */ = create_closure(entry__69_20, 0);
  // 321: if libpath.is_undefined:
  // 322:   Error "
  // 323:     Cannot resolve required library "@(libname)@quot;!@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__69_24;
}
static void entry__69_20(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // libname: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* libname */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 322: ... "
  // 323:   Cannot resolve required library "@(libname)@quot;!@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__69_21;
  arguments->slots[1] = frame->slots[0] /* libname */;
  arguments->slots[2] = string__69_22;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__69_23;
}
static void cont__69_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 322: Error "
  // 323:   Cannot resolve required library "@(libname)@quot;!@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__69_24(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 324: ... filename .from. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__from();
  func = myself->type;
  frame->cont = cont__69_25;
}
static void cont__69_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 324: ... string(libpath filename .from. '/')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* libpath */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__69_26;
}
static void cont__69_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 324: -> string(libpath filename .from. '/')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__70_1_add_module_infos(void) {
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
  // 335: ... --SORT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__SORT();
  arguments->slots[1] = get__std__true();
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__70_2;
}
static void cont__70_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 335: $entries directory(--SORT path)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[0] /* path */;
  result_count = 1;
  myself = get__directory();
  func = myself->type;
  frame->cont = cont__70_3;
}
static void cont__70_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* entries */, arguments->slots[0]);
  // 336: $$filenames empty_set
  ((CELL *)frame->slots[4])->contents /* filenames */ = get__empty_set();
  // 337: $$directories empty_list
  ((CELL *)frame->slots[5])->contents /* directories */ = get__empty_list();
  // 338: $$modules empty_key_order_set
  ((CELL *)frame->slots[6])->contents /* modules */ = get__empty_key_order_set();
  // 339: ... : (entry)
  // 340:   $name std::filename_of(entry)
  // 341:   cond
  // 342:     -> entry.is_a_directory: if name .matches. NAME: push &directories name
  // 343:     -> name .has_suffix. ".sim":
  // 344:       $submodule_name name .without_suffix. (some(".meta"), ".sim")
  // 345:       !filenames(submodule_name) true
  // 346:       $meta_level (length_of(name)-length_of(submodule_name)-4)/5
  // 347:       $stored_level meta_levels(submodule_name)
  // 348:       if stored_level.is_undefined || meta_level > stored_level:
  // ...
  frame->slots[7] /* temp__1 */ = create_closure(entry__70_4, 1);
  // 339: for_each entries: (entry)
  // 340:   $name std::filename_of(entry)
  // 341:   cond
  // 342:     -> entry.is_a_directory: if name .matches. NAME: push &directories name
  // 343:     -> name .has_suffix. ".sim":
  // 344:       $submodule_name name .without_suffix. (some(".meta"), ".sim")
  // 345:       !filenames(submodule_name) true
  // 346:       $meta_level (length_of(name)-length_of(submodule_name)-4)/5
  // 347:       $stored_level meta_levels(submodule_name)
  // 348:       if stored_level.is_undefined || meta_level > stored_level:
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* entries */;
  arguments->slots[1] = frame->slots[7] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__70_38;
}
static void entry__70_15(void) {
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
  // 344: ... some(".meta")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__70_16;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__70_17;
}
static void cont__70_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__2 */ = arguments->slots[0];
  // 344: ... some(".meta"), ".sim"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__2 */;
  arguments->slots[1] = string__70_13;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__70_18;
}
static void cont__70_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 344: $submodule_name name .without_suffix. (some(".meta"), ".sim")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = get__without_suffix();
  func = myself->type;
  frame->cont = cont__70_19;
}
static void cont__70_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* submodule_name */, arguments->slots[0]);
  // 345: !filenames(submodule_name) true
  frame->slots[9] /* temp__1 */ = get__true();
  // 345: !filenames(submodule_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* submodule_name */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* filenames */;
  func = myself->type;
  frame->cont = cont__70_20;
}
static void cont__70_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* filenames */ = arguments->slots[0];
  // 346: ... length_of(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__70_21;
}
static void cont__70_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__3 */ = arguments->slots[0];
  // 346: ... length_of(submodule_name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* submodule_name */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__70_22;
}
static void cont__70_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__4 */ = arguments->slots[0];
  // 346: ... length_of(name)-length_of(submodule_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__3 */;
  arguments->slots[1] = frame->slots[12] /* temp__4 */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__70_23;
}
static void cont__70_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__2 */ = arguments->slots[0];
  // 346: ... length_of(name)-length_of(submodule_name)-4
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__2 */;
  arguments->slots[1] = number__4;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__70_24;
}
static void cont__70_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 346: $meta_level (length_of(name)-length_of(submodule_name)-4)/5
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__std__over();
  func = myself->type;
  frame->cont = cont__70_25;
}
static void cont__70_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* meta_level */, arguments->slots[0]);
  // 347: $stored_level meta_levels(submodule_name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* submodule_name */;
  result_count = 1;
  myself = var._meta_levels;
  func = myself->type;
  frame->cont = cont__70_26;
}
static void cont__70_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* stored_level */, arguments->slots[0]);
  // 348: ... stored_level.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* stored_level */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__70_27;
}
static void cont__70_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__2 */ = arguments->slots[0];
  // 348: ... meta_level > stored_level
  frame->slots[11] /* temp__3 */ = create_closure(entry__70_28, 0);
  // 348: ... stored_level.is_undefined || meta_level > stored_level
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__2 */;
  arguments->slots[1] = frame->slots[11] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__70_30;
}
static void entry__70_28(void) {
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
  // 348: ... meta_level > stored_level
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stored_level */;
  arguments->slots[1] = frame->slots[1] /* meta_level */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__70_29;
}
static void cont__70_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 348: ... meta_level > stored_level
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__70_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 348: ... :
  // 349:   !meta_levels(submodule_name) meta_level
  frame->slots[12] /* temp__4 */ = create_closure(entry__70_31, 0);
  // 348: if stored_level.is_undefined || meta_level > stored_level:
  // 349:   !meta_levels(submodule_name) meta_level
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = frame->slots[12] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__70_33;
}
static void entry__70_31(void) {
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
  // 349: !meta_levels(submodule_name) meta_level
  frame->slots[2] /* temp__1 */ = frame->slots[1] /* meta_level */;
  // 349: !meta_levels(submodule_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* submodule_name */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = var._meta_levels;
  func = myself->type;
  frame->cont = cont__70_32;
}
static void cont__70_32(void) {
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
static void cont__70_33(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 350: $basename submodule_name .truncate_from. '-'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* submodule_name */;
  arguments->slots[1] = character__45;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__70_34;
}
static void cont__70_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[7] /* basename */, arguments->slots[0]);
  // 351: !modules(basename) true
  frame->slots[9] /* temp__1 */ = get__true();
  // 351: !modules(basename)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* basename */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[2])->contents /* modules */;
  func = myself->type;
  frame->cont = cont__70_35;
}
static void cont__70_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* modules */ = arguments->slots[0];
  // 352: $mod_name string(mod_path basename)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* mod_path */;
  arguments->slots[1] = frame->slots[7] /* basename */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__70_36;
}
static void cont__70_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[8] /* mod_name */, arguments->slots[0]);
  // 353: !module_info(mod_name) empty_key_order_table
  frame->slots[9] /* temp__1 */ = get__empty_key_order_table();
  // 353: !module_info(mod_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* mod_name */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = var._module_info;
  func = myself->type;
  frame->cont = cont__70_37;
}
static void cont__70_37(void) {
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
static void entry__70_10(void) {
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
  // 342: ... push &directories name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* directories */;
  arguments->slots[1] = frame->slots[1] /* name */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__70_11;
}
static void cont__70_11(void) {
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
static void entry__70_8(void) {
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
  // 342: ... name .matches. NAME
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = get__NAME();
  result_count = 1;
  myself = get__matches();
  func = myself->type;
  frame->cont = cont__70_9;
}
static void cont__70_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 342: ... : push &directories name
  frame->slots[3] /* temp__2 */ = create_closure(entry__70_10, 0);
  // 342: ... if name .matches. NAME: push &directories name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__70_6(void) {
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
  // 342: ... entry.is_a_directory
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* entry */;
  result_count = 1;
  myself = get__is_a_directory();
  func = myself->type;
  frame->cont = cont__70_7;
}
static void cont__70_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 342: ... : if name .matches. NAME: push &directories name
  frame->slots[4] /* temp__2 */ = create_closure(entry__70_8, 0);
  // 342: -> entry.is_a_directory: if name .matches. NAME: push &directories name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__70_12(void) {
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
  // 343: ... name .has_suffix. ".sim"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = string__70_13;
  result_count = 1;
  myself = get__has_suffix();
  func = myself->type;
  frame->cont = cont__70_14;
}
static void cont__70_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 343: ... :
  // 344:   $submodule_name name .without_suffix. (some(".meta"), ".sim")
  // 345:   !filenames(submodule_name) true
  // 346:   $meta_level (length_of(name)-length_of(submodule_name)-4)/5
  // 347:   $stored_level meta_levels(submodule_name)
  // 348:   if stored_level.is_undefined || meta_level > stored_level:
  // 349:     !meta_levels(submodule_name) meta_level
  // 350:   $basename submodule_name .truncate_from. '-'
  // 351:   !modules(basename) true
  // 352:   $mod_name string(mod_path basename)
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__70_15, 0);
  // 343: -> name .has_suffix. ".sim":
  // 344:   $submodule_name name .without_suffix. (some(".meta"), ".sim")
  // 345:   !filenames(submodule_name) true
  // 346:   $meta_level (length_of(name)-length_of(submodule_name)-4)/5
  // 347:   $stored_level meta_levels(submodule_name)
  // 348:   if stored_level.is_undefined || meta_level > stored_level:
  // 349:     !meta_levels(submodule_name) meta_level
  // 350:   $basename submodule_name .truncate_from. '-'
  // 351:   !modules(basename) true
  // 352:   $mod_name string(mod_path basename)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__70_4(void) {
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
  // 340: $name std::filename_of(entry)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* entry */;
  result_count = 1;
  myself = get__std__filename_of();
  func = myself->type;
  frame->cont = cont__70_5;
}
static void cont__70_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* name */, arguments->slots[0]);
  // 342: -> entry.is_a_directory: if name .matches. NAME: push &directories name
  frame->slots[6] /* temp__1 */ = create_closure(entry__70_6, 0);
  // 343: -> name .has_suffix. ".sim":
  // 344:   $submodule_name name .without_suffix. (some(".meta"), ".sim")
  // 345:   !filenames(submodule_name) true
  // 346:   $meta_level (length_of(name)-length_of(submodule_name)-4)/5
  // 347:   $stored_level meta_levels(submodule_name)
  // 348:   if stored_level.is_undefined || meta_level > stored_level:
  // 349:     !meta_levels(submodule_name) meta_level
  // 350:   $basename submodule_name .truncate_from. '-'
  // 351:   !modules(basename) true
  // 352:   $mod_name string(mod_path basename)
  // ...
  frame->slots[7] /* temp__2 */ = create_closure(entry__70_12, 0);
  // 341: cond
  // 342:   -> entry.is_a_directory: if name .matches. NAME: push &directories name
  // 343:   -> name .has_suffix. ".sim":
  // 344:     $submodule_name name .without_suffix. (some(".meta"), ".sim")
  // 345:     !filenames(submodule_name) true
  // 346:     $meta_level (length_of(name)-length_of(submodule_name)-4)/5
  // 347:     $stored_level meta_levels(submodule_name)
  // 348:     if stored_level.is_undefined || meta_level > stored_level:
  // 349:       !meta_levels(submodule_name) meta_level
  // 350:     $basename submodule_name .truncate_from. '-'
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
static void cont__70_38(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 354: ... : (filename)
  // 355:   if filename .contains. '-':
  // 356:     unless filename .has_suffix. "-common":
  // 357:       $maybe_push_common: (plat)
  // 358:         $common_name string(name "-" plat "-common")
  // 359:         if filenames(common_name): push &files common_name
  // 360:       
  // 361:       $name filename .before. '-'
  // 362:       $mod_name string(mod_path name .truncate_from. '-')
  // 363:       $platform filename .behind. '-'
  // ...
  frame->slots[7] /* temp__1 */ = create_closure(entry__70_39, 1);
  // 354: for_each filenames: (filename)
  // 355:   if filename .contains. '-':
  // 356:     unless filename .has_suffix. "-common":
  // 357:       $maybe_push_common: (plat)
  // 358:         $common_name string(name "-" plat "-common")
  // 359:         if filenames(common_name): push &files common_name
  // 360:       
  // 361:       $name filename .before. '-'
  // 362:       $mod_name string(mod_path name .truncate_from. '-')
  // 363:       $platform filename .behind. '-'
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* filenames */;
  arguments->slots[1] = frame->slots[7] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__70_74;
}
static void entry__70_44(void) {
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
  // 357: ... : (plat)
  // 358:   $common_name string(name "-" plat "-common")
  // 359:   if filenames(common_name): push &files common_name
  frame->slots[9] /* temp__1 */ = create_closure(entry__70_45_maybe_push_common, 1);
  // 357: $maybe_push_common: (plat)
  // 358:   $common_name string(name "-" plat "-common")
  // 359:   if filenames(common_name): push &files common_name
  initialize_future(frame->slots[3] /* maybe_push_common */, frame->slots[9] /* temp__1 */);
  // 361: $name filename .before. '-'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* filename */;
  arguments->slots[1] = character__45;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__70_51;
}
static void entry__70_49(void) {
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
  // 359: ... push &files common_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* files */;
  arguments->slots[1] = frame->slots[1] /* common_name */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__70_50;
}
static void cont__70_50(void) {
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
static void entry__70_45_maybe_push_common(void) {
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
  // 358: $common_name string(name "-" plat "-common")
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* name */;
  arguments->slots[1] = string__70_46;
  arguments->slots[2] = frame->slots[0] /* plat */;
  arguments->slots[3] = string__70_42;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__70_47;
}
static void cont__70_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* common_name */, arguments->slots[0]);
  // 359: ... filenames(common_name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* common_name */;
  result_count = 1;
  myself = ((CELL *)frame->slots[2])->contents /* filenames */;
  func = myself->type;
  frame->cont = cont__70_48;
}
static void cont__70_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 359: ... : push &files common_name
  frame->slots[6] /* temp__2 */ = create_closure(entry__70_49, 0);
  // 359: if filenames(common_name): push &files common_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__70_51(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* name */, arguments->slots[0]);
  // 362: ... name .truncate_from. '-'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* name */;
  arguments->slots[1] = character__45;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__70_52;
}
static void cont__70_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 362: $mod_name string(mod_path name .truncate_from. '-')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* mod_path */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__70_53;
}
static void cont__70_53(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* mod_name */, arguments->slots[0]);
  // 363: $platform filename .behind. '-'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* filename */;
  arguments->slots[1] = character__45;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__70_54;
}
static void cont__70_54(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* platform */, arguments->slots[0]);
  // 364: $$parent supported_platforms(platform)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* platform */;
  result_count = 1;
  myself = var._supported_platforms;
  func = myself->type;
  frame->cont = cont__70_55;
}
static void cont__70_55(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[7])->contents /* parent */ = arguments->slots[0];
  // 365: ... parent.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[7])->contents /* parent */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__70_56;
}
static void cont__70_56(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 365: ... :
  // 366:   Error "
  // 367:     The platform "@(platform)" is not supported!@
  frame->slots[10] /* temp__2 */ = create_closure(entry__70_57, 0);
  // 365: unless parent.is_defined:
  // 366:   Error "
  // 367:     The platform "@(platform)" is not supported!@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__70_61;
}
static void entry__70_57(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // platform: 0
  frame->slots[0] = myself->closure.frame->slots[6]; /* platform */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 366: ... "
  // 367:   The platform "@(platform)" is not supported!@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__70_58;
  arguments->slots[1] = frame->slots[0] /* platform */;
  arguments->slots[2] = string__70_59;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__70_60;
}
static void cont__70_60(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 366: Error "
  // 367:   The platform "@(platform)" is not supported!@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__70_61(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 368: $$files list(filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* filename */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__70_62;
}
static void cont__70_62(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[8])->contents /* files */ = arguments->slots[0];
  // 369: maybe_push_common platform
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* platform */;
  result_count = 0;
  myself = frame->slots[3] /* maybe_push_common */;
  func = myself->type;
  frame->cont = cont__70_63;
}
static void cont__70_63(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 370: ... -> parent != NONE:
  // 371:   maybe_push_common parent
  // 372:   !parent supported_platforms(parent)
  frame->slots[9] /* temp__1 */ = create_closure(entry__70_64, 0);
  // 370: while -> parent != NONE:
  // 371:   maybe_push_common parent
  // 372:   !parent supported_platforms(parent)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  result_count = 0;
  myself = get__while();
  func = myself->type;
  frame->cont = cont__70_70;
}
static void entry__70_67(void) {
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
  // 371: maybe_push_common parent
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* parent */;
  result_count = 0;
  myself = frame->slots[0] /* maybe_push_common */;
  func = myself->type;
  frame->cont = cont__70_68;
}
static void cont__70_68(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 372: !parent supported_platforms(parent)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* parent */;
  result_count = 1;
  myself = var._supported_platforms;
  func = myself->type;
  frame->cont = cont__70_69;
}
static void cont__70_69(void) {
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
static void entry__70_64(void) {
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
  // 370: ... parent != NONE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parent */;
  arguments->slots[1] = var._NONE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__70_65;
}
static void cont__70_65(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 370: ... parent != NONE
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__70_66;
}
static void cont__70_66(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 370: ... :
  // 371:   maybe_push_common parent
  // 372:   !parent supported_platforms(parent)
  frame->slots[4] /* temp__3 */ = create_closure(entry__70_67, 0);
  // 370: ... -> parent != NONE:
  // 371:   maybe_push_common parent
  // 372:   !parent supported_platforms(parent)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__70_70(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 373: !module_info(mod_name)(platform) files
  frame->slots[9] /* temp__1 */ = ((CELL *)frame->slots[8])->contents /* files */;
  // 373: ... module_info(mod_name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* mod_name */;
  result_count = 1;
  myself = var._module_info;
  func = myself->type;
  frame->cont = cont__70_71;
}
static void cont__70_71(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__2 */ = arguments->slots[0];
  // 373: !module_info(mod_name)(platform)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* platform */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = frame->slots[10] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__70_72;
}
static void cont__70_72(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__2 */ = arguments->slots[0];
  // 373: !module_info(mod_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* mod_name */;
  arguments->slots[1] = frame->slots[10] /* temp__2 */;
  result_count = 1;
  myself = var._module_info;
  func = myself->type;
  frame->cont = cont__70_73;
}
static void cont__70_73(void) {
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
static void entry__70_41(void) {
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
  // 356: ... filename .has_suffix. "-common"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  arguments->slots[1] = string__70_42;
  result_count = 1;
  myself = get__has_suffix();
  func = myself->type;
  frame->cont = cont__70_43;
}
static void cont__70_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 356: ... :
  // 357:   $maybe_push_common: (plat)
  // 358:     $common_name string(name "-" plat "-common")
  // 359:     if filenames(common_name): push &files common_name
  // 360:   
  // 361:   $name filename .before. '-'
  // 362:   $mod_name string(mod_path name .truncate_from. '-')
  // 363:   $platform filename .behind. '-'
  // 364:   $$parent supported_platforms(platform)
  // 365:   unless parent.is_defined:
  // ...
  frame->slots[4] /* temp__2 */ = create_closure(entry__70_44, 0);
  // 356: unless filename .has_suffix. "-common":
  // 357:   $maybe_push_common: (plat)
  // 358:     $common_name string(name "-" plat "-common")
  // 359:     if filenames(common_name): push &files common_name
  // 360:   
  // 361:   $name filename .before. '-'
  // 362:   $mod_name string(mod_path name .truncate_from. '-')
  // 363:   $platform filename .behind. '-'
  // 364:   $$parent supported_platforms(platform)
  // 365:   unless parent.is_defined:
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
static void entry__70_39(void) {
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
  // 355: ... filename .contains. '-'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  arguments->slots[1] = character__45;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__70_40;
}
static void cont__70_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 355: ... :
  // 356:   unless filename .has_suffix. "-common":
  // 357:     $maybe_push_common: (plat)
  // 358:       $common_name string(name "-" plat "-common")
  // 359:       if filenames(common_name): push &files common_name
  // 360:     
  // 361:     $name filename .before. '-'
  // 362:     $mod_name string(mod_path name .truncate_from. '-')
  // 363:     $platform filename .behind. '-'
  // 364:     $$parent supported_platforms(platform)
  // ...
  frame->slots[4] /* temp__2 */ = create_closure(entry__70_41, 0);
  // 355: if filename .contains. '-':
  // 356:   unless filename .has_suffix. "-common":
  // 357:     $maybe_push_common: (plat)
  // 358:       $common_name string(name "-" plat "-common")
  // 359:       if filenames(common_name): push &files common_name
  // 360:     
  // 361:     $name filename .before. '-'
  // 362:     $mod_name string(mod_path name .truncate_from. '-')
  // 363:     $platform filename .behind. '-'
  // 364:     $$parent supported_platforms(platform)
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
static void cont__70_74(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 374: ... parameter_count_of(return)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* return */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__70_75;
}
static void cont__70_75(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 374: ... parameter_count_of(return) == 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__2 */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__70_76;
}
static void cont__70_76(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 374: ... : return directories modules
  frame->slots[9] /* temp__3 */ = create_closure(entry__70_77, 0);
  // 374: if parameter_count_of(return) == 2: return directories modules
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__70_78;
}
static void entry__70_77(void) {
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
  // 374: ... return directories modules
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* directories */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* modules */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__70_78(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__71_4(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // info: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 385: ... -> info
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__71_5(void) {
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
  // 386: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__71_6;
}
static void cont__71_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 386: ... before(mod_filename '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__71_7;
}
static void cont__71_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 386: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__71_8;
}
static void cont__71_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 386: ... until(mod_name '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* mod_name */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = get__until();
  func = myself->type;
  frame->cont = cont__71_9;
}
static void cont__71_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 386: add_module_infos before(mod_filename '/' -1) until(mod_name '/' -1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 0;
  myself = var._add_module_infos;
  func = myself->type;
  frame->cont = cont__71_10;
}
static void cont__71_10(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 387: ... module_info(mod_name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* mod_name */;
  result_count = 1;
  myself = var._module_info;
  func = myself->type;
  frame->cont = cont__71_11;
}
static void cont__71_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 387: -> module_info(mod_name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__71_1_lookup(void) {
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
  // 384: $info module_info(mod_name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* mod_name */;
  result_count = 1;
  myself = var._module_info;
  func = myself->type;
  frame->cont = cont__71_2;
}
static void cont__71_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* info */, arguments->slots[0]);
  // 385: ... info.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* info */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__71_3;
}
static void cont__71_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 385: ... -> info
  frame->slots[4] /* temp__2 */ = create_closure(entry__71_4, 0);
  // 385: ... :
  // 386:   add_module_infos before(mod_filename '/' -1) until(mod_name '/' -1)
  // 387:   -> module_info(mod_name)
  frame->slots[5] /* temp__3 */ = create_closure(entry__71_5, 0);
  // 385: if info.is_defined (-> info):
  // 386:   add_module_infos before(mod_filename '/' -1) until(mod_name '/' -1)
  // 387:   -> module_info(mod_name)
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
static void entry__72_1_CC(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // args: 0
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 390: ... : ewriteln c_compiler() ' ' join(args)
  frame->slots[1] /* temp__1 */ = create_closure(entry__72_2, 0);
  // 390: if do_show_debug_infos: ewriteln c_compiler() ' ' join(args)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_show_debug_infos();
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__72_5;
}
static void entry__72_2(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // args: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* args */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 390: ... c_compiler()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__c_compiler();
  func = myself->type;
  frame->cont = cont__72_3;
}
static void cont__72_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 390: ... join(args)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* args */;
  result_count = 1;
  myself = get__join();
  func = myself->type;
  frame->cont = cont__72_4;
}
static void cont__72_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 390: ... ewriteln c_compiler() ' ' join(args)
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
static void cont__72_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 391: cc args*
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = frame->caller_result_count;
  myself = var._cc;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__73_4(void) {
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
  // 395: CC $_out $err $success cpp_options* cc_options* "-c" c_filename "-o" o_filename
  argument_count = 0;
  arguments = node_p;
  unfold(var._cpp_options);
  unfold(var._cc_options);
  arguments->slots[argument_count++] = string__73_5;
  arguments->slots[argument_count++] = frame->slots[0] /* c_filename */;
  arguments->slots[argument_count++] = string__73_6;
  arguments->slots[argument_count++] = frame->slots[1] /* o_filename */;
  result_count = 3;
  myself = var._CC;
  func = myself->type;
  frame->cont = cont__73_7;
}
static void cont__73_7(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  frame->slots[6] /* temp__2 */ = arguments->slots[1];
  frame->slots[7] /* temp__3 */ = arguments->slots[2];
  // 395: ... _out
  initialize_future(frame->slots[2] /* out */, frame->slots[5] /* temp__1 */);
  // 395: ... err
  initialize_future(frame->slots[3] /* err */, frame->slots[6] /* temp__2 */);
  // 395: ... success
  initialize_future(frame->slots[4] /* success */, frame->slots[7] /* temp__3 */);
  // 396: ... :
  // 397:   Error "
  // 398:     Failed to compile @(c_filename)
  // 399:     @(err.from_utf8)
  frame->slots[5] /* temp__1 */ = create_closure(entry__73_8, 0);
  // 396: unless success:
  // 397:   Error "
  // 398:     Failed to compile @(c_filename)
  // 399:     @(err.from_utf8)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* success */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__73_13;
}
static void entry__73_8(void) {
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
  // 399: ... err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* err */;
  result_count = 1;
  myself = get__from_utf8();
  func = myself->type;
  frame->cont = cont__73_9;
}
static void cont__73_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 397: ... "
  // 398:   Failed to compile @(c_filename)
  // 399:   @(err.from_utf8)
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__73_10;
  arguments->slots[1] = frame->slots[0] /* c_filename */;
  arguments->slots[2] = string__73_11;
  arguments->slots[3] = frame->slots[3] /* temp__2 */;
  arguments->slots[4] = string__73_11;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__73_12;
}
static void cont__73_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 397: Error "
  // 398:   Failed to compile @(c_filename)
  // 399:   @(err.from_utf8)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__73_13(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 400: !do_link true
  set__do_link(get__true());
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__73_1_compile_c(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // c_filename: 0
  // o_filename: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 394: ... do_build_codeblocks_project || do_list_dependencies
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_build_codeblocks_project;
  arguments->slots[1] = func__73_2;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__73_3;
}
static void entry__73_2(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 394: ... do_list_dependencies
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._do_list_dependencies;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__73_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 394: ... :
  // 395:   CC $_out $err $success cpp_options* cc_options* "-c" c_filename "-o" o_filename
  // 396:   unless success:
  // 397:     Error "
  // 398:       Failed to compile @(c_filename)
  // 399:       @(err.from_utf8)
  // 400:   !do_link true
  frame->slots[3] /* temp__2 */ = create_closure(entry__73_4, 0);
  // 394: unless do_build_codeblocks_project || do_list_dependencies:
  // 395:   CC $_out $err $success cpp_options* cc_options* "-c" c_filename "-o" o_filename
  // 396:   unless success:
  // 397:     Error "
  // 398:       Failed to compile @(c_filename)
  // 399:       @(err.from_utf8)
  // 400:   !do_link true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__74_2(void) {
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
  // 412: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__74_3;
}
static void cont__74_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 412: $meta_path truncate_from(mod_filename '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[11] /* temp__1 */;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__74_4;
}
static void cont__74_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* meta_path */, arguments->slots[0]);
  // 413: ... dup(".meta" meta_level)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__70_16;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* meta_level */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__74_5;
}
static void cont__74_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 413: $filename string(mod_filename dup(".meta" meta_level))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = frame->slots[11] /* temp__1 */;
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
  initialize_future(frame->slots[3] /* filename */, arguments->slots[0]);
  // 414: $meta_filename string(filename ".sim")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* filename */;
  arguments->slots[1] = string__70_13;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__74_7;
}
static void cont__74_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* meta_filename */, arguments->slots[0]);
  // 415: ... dup(".meta" meta_level)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__70_16;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* meta_level */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__74_8;
}
static void cont__74_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 415: $meta_c_filename string(mod_filename dup(".meta" meta_level) ".c")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = frame->slots[11] /* temp__1 */;
  arguments->slots[2] = string__74_9;
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
  initialize_future(frame->slots[5] /* meta_c_filename */, arguments->slots[0]);
  // 416: ... meta_level-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* meta_level */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__74_11;
}
static void cont__74_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__2 */ = arguments->slots[0];
  // 416: ... dup(".meta" meta_level-1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__70_16;
  arguments->slots[1] = frame->slots[12] /* temp__2 */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__74_12;
}
static void cont__74_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 416: $sim_filename string(mod_filename dup(".meta" meta_level-1) ".sim")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = frame->slots[11] /* temp__1 */;
  arguments->slots[2] = string__70_13;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__74_13;
}
static void cont__74_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* sim_filename */, arguments->slots[0]);
  // 417: $meta_info stat(meta_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* meta_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__74_14;
}
static void cont__74_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[7] /* meta_info */, arguments->slots[0]);
  // 418: $sim_info stat(sim_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* sim_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__74_15;
}
static void cont__74_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[8] /* sim_info */, arguments->slots[0]);
  // 419: $meta_c_info stat(meta_c_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* meta_c_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__74_16;
}
static void cont__74_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[9] /* meta_c_info */, arguments->slots[0]);
  frame->slots[11] /* temp__1 */ = create_closure(entry__74_17, 0);
  // 421: $$force_rebuild
  // 422:   ||
  // 423:     do_rebuild
  // 424:     sim_info.is_undefined
  // 425:     meta_c_info.is_undefined
  // 426:     modification_time_of(meta_info) > modification_time_of(meta_c_info)
  // 427:     modification_time_of(meta_c_info) > modification_time_of(sim_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_rebuild;
  arguments->slots[1] = frame->slots[11] /* temp__1 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__74_32;
}
static void entry__74_17(void) {
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
  // 424: sim_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* sim_info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__74_18;
}
static void cont__74_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  frame->slots[5] /* temp__3 */ = create_closure(entry__74_19, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__74_31;
}
static void entry__74_19(void) {
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
  // 425: meta_c_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* meta_c_info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__74_20;
}
static void cont__74_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  frame->slots[5] /* temp__3 */ = create_closure(entry__74_21, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__74_30;
}
static void entry__74_21(void) {
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
  // 426: ... modification_time_of(meta_c_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* meta_c_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__74_22;
}
static void cont__74_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 426: modification_time_of(meta_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* meta_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__74_23;
}
static void cont__74_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__4 */ = arguments->slots[0];
  // 426: modification_time_of(meta_info) > modification_time_of(meta_c_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__74_24;
}
static void cont__74_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 427: modification_time_of(meta_c_info) > modification_time_of(sim_info)
  frame->slots[7] /* temp__5 */ = create_closure(entry__74_25, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__5 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__74_29;
}
static void entry__74_25(void) {
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
  // 427: ... modification_time_of(sim_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* sim_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__74_26;
}
static void cont__74_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 427: modification_time_of(meta_c_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* meta_c_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__74_27;
}
static void cont__74_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 427: modification_time_of(meta_c_info) > modification_time_of(sim_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__74_28;
}
static void cont__74_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 427: modification_time_of(meta_c_info) > modification_time_of(sim_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__74_29(void) {
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
static void cont__74_30(void) {
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
static void cont__74_31(void) {
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
static void cont__74_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[10])->contents /* force_rebuild */ = arguments->slots[0];
  // 429: ... :
  // 430:   $modification_time modification_time_of(sim_info)
  // 431:   load $meta_c_buf meta_c_filename
  // 432:   do: (-> break)
  // 433:     for_each_line meta_c_buf: ($line)
  // 434:       $check: (data_filename)
  // 435:         $data_info stat(data_filename)
  // 436:         if
  // 437:           ||
  // 438:             data_info.is_undefined
  // ...
  frame->slots[11] /* temp__1 */ = create_closure(entry__74_33, 0);
  // 429: unless force_rebuild:
  // 430:   $modification_time modification_time_of(sim_info)
  // 431:   load $meta_c_buf meta_c_filename
  // 432:   do: (-> break)
  // 433:     for_each_line meta_c_buf: ($line)
  // 434:       $check: (data_filename)
  // 435:         $data_info stat(data_filename)
  // 436:         if
  // 437:           ||
  // 438:             data_info.is_undefined
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[10])->contents /* force_rebuild */;
  arguments->slots[1] = frame->slots[11] /* temp__1 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__74_66;
}
static void entry__74_36(void) {
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
  // 433: ... : ($line)
  // 434:   $check: (data_filename)
  // 435:     $data_info stat(data_filename)
  // 436:     if
  // 437:       ||
  // 438:         data_info.is_undefined
  // 439:         modification_time_of(data_info) > modification_time
  // 440:       :
  // 441:         !force_rebuild true
  // 442:         break
  // ...
  frame->slots[5] /* temp__1 */ = create_closure(entry__74_37, 1);
  // 433: for_each_line meta_c_buf: ($line)
  // 434:   $check: (data_filename)
  // 435:     $data_info stat(data_filename)
  // 436:     if
  // 437:       ||
  // 438:         data_info.is_undefined
  // 439:         modification_time_of(data_info) > modification_time
  // 440:       :
  // 441:         !force_rebuild true
  // 442:         break
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* meta_c_buf */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each_line();
  func = myself->type;
  frame->cont = cont__74_65;
}
static void entry__74_63(void) {
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
  // 454: ... string(path '/' argument)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* path */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[2] /* argument */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__74_64;
}
static void cont__74_64(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 454: ... check string(path '/' argument)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* check */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__74_58(void) {
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
  // 452: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__74_59;
}
static void cont__74_59(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 452: ... range(argument 2 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* argument */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__74_60;
}
static void cont__74_60(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 452: ... string(meta_path range(argument 2 -1))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* meta_path */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__74_61;
}
static void cont__74_61(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 452: check string(meta_path range(argument 2 -1))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* check */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__74_62(void) {
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
  // 454: ... : (path) check string(path '/' argument)
  frame->slots[2] /* temp__1 */ = create_closure(entry__74_63, 1);
  // 454: for_each simdatapaths: (path) check string(path '/' argument)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._simdatapaths;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__74_55(void) {
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
  // 451: argument .has_prefix. "./"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* argument */;
  arguments->slots[1] = string__74_56;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__74_57;
}
static void cont__74_57(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 451: ... :
  // 452:   check string(meta_path range(argument 2 -1))
  frame->slots[4] /* temp__2 */ = create_closure(entry__74_58, 0);
  // 453: :
  // 454:   for_each simdatapaths: (path) check string(path '/' argument)
  frame->slots[5] /* temp__3 */ = create_closure(entry__74_62, 0);
  // 450: if
  // 451:   argument .has_prefix. "./":
  // 452:     check string(meta_path range(argument 2 -1))
  // 453:   :
  // 454:     for_each simdatapaths: (path) check string(path '/' argument)
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
static void entry__74_37(void) {
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
  // 434: ... : (data_filename)
  // 435:   $data_info stat(data_filename)
  // 436:   if
  // 437:     ||
  // 438:       data_info.is_undefined
  // 439:       modification_time_of(data_info) > modification_time
  // 440:     :
  // 441:       !force_rebuild true
  // 442:       break
  frame->slots[8] /* temp__1 */ = create_closure(entry__74_38_check, 1);
  // 434: $check: (data_filename)
  // 435:   $data_info stat(data_filename)
  // 436:   if
  // 437:     ||
  // 438:       data_info.is_undefined
  // 439:       modification_time_of(data_info) > modification_time
  // 440:     :
  // 441:       !force_rebuild true
  // 442:       break
  initialize_future(frame->slots[5] /* check */, frame->slots[8] /* temp__1 */);
  // 444: ... line .has_prefix. "/// "
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  arguments->slots[1] = string__74_46;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__74_47;
}
static void entry__74_45(void) {
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
  // 441: !force_rebuild true
  ((CELL *)frame->slots[0])->contents /* force_rebuild */ = get__true();
  // 442: break
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* break */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__74_38_check(void) {
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
  // 435: $data_info stat(data_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* data_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__74_39;
}
static void cont__74_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* data_info */, arguments->slots[0]);
  // 438: data_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* data_info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__74_40;
}
static void cont__74_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 439: modification_time_of(data_info) > modification_time
  frame->slots[7] /* temp__3 */ = create_closure(entry__74_41, 0);
  // 437: ||
  // 438:   data_info.is_undefined
  // 439:   modification_time_of(data_info) > modification_time
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__74_44;
}
static void entry__74_41(void) {
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
  // 439: modification_time_of(data_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* data_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__74_42;
}
static void cont__74_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 439: modification_time_of(data_info) > modification_time
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* modification_time */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__74_43;
}
static void cont__74_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 439: modification_time_of(data_info) > modification_time
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__74_44(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 440: :
  // 441:   !force_rebuild true
  // 442:   break
  frame->slots[8] /* temp__4 */ = create_closure(entry__74_45, 0);
  // 436: if
  // 437:   ||
  // 438:     data_info.is_undefined
  // 439:     modification_time_of(data_info) > modification_time
  // 440:   :
  // 441:     !force_rebuild true
  // 442:     break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__74_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 444: unless line .has_prefix. "/// " break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* break */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__74_48;
}
static void cont__74_48(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 445: behind &line ' '
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  arguments->slots[1] = character__32;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__74_49;
}
static void cont__74_49(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* line */ = arguments->slots[0];
  // 446: trim &line
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__74_50;
}
static void cont__74_50(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* line */ = arguments->slots[0];
  // 447: $command line .truncate_from. WHITESPACE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  arguments->slots[1] = var._WHITESPACE;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__74_51;
}
static void cont__74_51(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* command */, arguments->slots[0]);
  // 448: $argument line .behind. WHITESPACE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  arguments->slots[1] = var._WHITESPACE;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__74_52;
}
static void cont__74_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[7] /* argument */, arguments->slots[0]);
  // 449: ... command == "data"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* command */;
  arguments->slots[1] = string__74_53;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__74_54;
}
static void cont__74_54(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 449: ... :
  // 450:   if
  // 451:     argument .has_prefix. "./":
  // 452:       check string(meta_path range(argument 2 -1))
  // 453:     :
  // 454:       for_each simdatapaths: (path) check string(path '/' argument)
  frame->slots[9] /* temp__2 */ = create_closure(entry__74_55, 0);
  // 449: if command == "data":
  // 450:   if
  // 451:     argument .has_prefix. "./":
  // 452:       check string(meta_path range(argument 2 -1))
  // 453:     :
  // 454:       for_each simdatapaths: (path) check string(path '/' argument)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__74_65(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__74_33(void) {
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
  // 430: $modification_time modification_time_of(sim_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* sim_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__74_34;
}
static void cont__74_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* modification_time */, arguments->slots[0]);
  // 431: load $meta_c_buf meta_c_filename
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* meta_c_filename */;
  result_count = 1;
  myself = get__load();
  func = myself->type;
  frame->cont = cont__74_35;
}
static void cont__74_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* meta_c_buf */, arguments->slots[0]);
  // 432: ... : (-> break)
  // 433:   for_each_line meta_c_buf: ($line)
  // 434:     $check: (data_filename)
  // 435:       $data_info stat(data_filename)
  // 436:       if
  // 437:         ||
  // 438:           data_info.is_undefined
  // 439:           modification_time_of(data_info) > modification_time
  // 440:         :
  // 441:           !force_rebuild true
  // ...
  frame->slots[6] /* temp__1 */ = create_closure(entry__74_36, 0);
  // 432: do: (-> break)
  // 433:   for_each_line meta_c_buf: ($line)
  // 434:     $check: (data_filename)
  // 435:       $data_info stat(data_filename)
  // 436:       if
  // 437:         ||
  // 438:           data_info.is_undefined
  // 439:           modification_time_of(data_info) > modification_time
  // 440:         :
  // 441:           !force_rebuild true
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__do();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__74_66(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 455: ... :
  // 456:   %on_top_level false
  // 457:   %%objects empty_insert_order_set
  // 458:   %%libraries empty_insert_order_set
  // 459:   %%do_link false
  // 460:   %%last_modification_time undefined
  // 461:   %do_build_static_executable false
  // 462:   %main_filename meta_filename
  // 463:   %main_info stat(main_filename)
  // 464:   build_executable
  // ...
  frame->slots[11] /* temp__1 */ = create_closure(entry__74_67, 0);
  // 455: if force_rebuild:
  // 456:   %on_top_level false
  // 457:   %%objects empty_insert_order_set
  // 458:   %%libraries empty_insert_order_set
  // 459:   %%do_link false
  // 460:   %%last_modification_time undefined
  // 461:   %do_build_static_executable false
  // 462:   %main_filename meta_filename
  // 463:   %main_info stat(main_filename)
  // 464:   build_executable
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[10])->contents /* force_rebuild */;
  arguments->slots[1] = frame->slots[11] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__74_79;
}
static void entry__74_67(void) {
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
  // 456: %on_top_level false
  initialize_maybe_future(get__on_top_level(), get__false());
  // 457: %%objects empty_insert_order_set
  set__objects(get__empty_insert_order_set());
  // 458: %%libraries empty_insert_order_set
  set__libraries(get__empty_insert_order_set());
  // 459: %%do_link false
  set__do_link(get__false());
  // 460: %%last_modification_time undefined
  set__last_modification_time(get__undefined());
  // 461: %do_build_static_executable false
  initialize_maybe_future(get__do_build_static_executable(), get__false());
  // 462: %main_filename meta_filename
  initialize_maybe_future(get__main_filename(), frame->slots[1] /* meta_filename */);
  // 463: %main_info stat(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__74_68;
}
static void cont__74_68(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(get__main_info(), arguments->slots[0]);
  // 464: build_executable
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._build_executable;
  func = myself->type;
  frame->cont = cont__74_69;
}
static void cont__74_69(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 465: $orig_path current_path()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__current_path();
  func = myself->type;
  frame->cont = cont__74_70;
}
static void cont__74_70(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* orig_path */, arguments->slots[0]);
  // 466: change_directory meta_path
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* meta_path */;
  result_count = 0;
  myself = get__change_directory();
  func = myself->type;
  frame->cont = cont__74_71;
}
static void cont__74_71(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 467: std::call $out $err $success filename
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* filename */;
  result_count = 3;
  myself = get__std__call();
  func = myself->type;
  frame->cont = cont__74_72;
}
static void cont__74_72(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  frame->slots[10] /* temp__2 */ = arguments->slots[1];
  frame->slots[11] /* temp__3 */ = arguments->slots[2];
  // 467: ... out
  initialize_future(frame->slots[6] /* out */, frame->slots[9] /* temp__1 */);
  // 467: ... err
  initialize_future(frame->slots[7] /* err */, frame->slots[10] /* temp__2 */);
  // 467: ... success
  initialize_future(frame->slots[8] /* success */, frame->slots[11] /* temp__3 */);
  // 468: change_directory orig_path
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* orig_path */;
  result_count = 0;
  myself = get__change_directory();
  func = myself->type;
  frame->cont = cont__74_73;
}
static void cont__74_73(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 469: ... : Error err.from_utf8
  frame->slots[9] /* temp__1 */ = create_closure(entry__74_74, 0);
  // 469: unless success: Error err.from_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* success */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__74_76;
}
static void entry__74_74(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // err: 0
  frame->slots[0] = myself->closure.frame->slots[7]; /* err */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 469: ... err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* err */;
  result_count = 1;
  myself = get__from_utf8();
  func = myself->type;
  frame->cont = cont__74_75;
}
static void cont__74_75(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 469: ... Error err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__74_76(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 470: ... out.to_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* out */;
  result_count = 1;
  myself = get__to_utf8();
  func = myself->type;
  frame->cont = cont__74_77;
}
static void cont__74_77(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 470: save sim_filename out.to_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* sim_filename */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__save();
  func = myself->type;
  frame->cont = cont__74_78;
}
static void cont__74_78(void) {
  myself = frame->slots[0] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__74_79(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 471: dec &meta_level
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* meta_level */;
  result_count = 1;
  myself = get__dec();
  func = myself->type;
  frame->cont = cont__74_80;
}
static void cont__74_80(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* meta_level */ = arguments->slots[0];
  // 472: ... meta_level > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* meta_level */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__74_81;
}
static void cont__74_81(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 472: -> meta_level > 0
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__74_1_compile_meta_module(void) {
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
  // 411: ... :
  // 412:   $meta_path truncate_from(mod_filename '/' -1)
  // 413:   $filename string(mod_filename dup(".meta" meta_level))
  // 414:   $meta_filename string(filename ".sim")
  // 415:   $meta_c_filename string(mod_filename dup(".meta" meta_level) ".c")
  // 416:   $sim_filename string(mod_filename dup(".meta" meta_level-1) ".sim")
  // 417:   $meta_info stat(meta_filename)
  // 418:   $sim_info stat(sim_filename)
  // 419:   $meta_c_info stat(meta_c_filename)
  // 420:   
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__74_2, 0);
  // 411: do_while:
  // 412:   $meta_path truncate_from(mod_filename '/' -1)
  // 413:   $filename string(mod_filename dup(".meta" meta_level))
  // 414:   $meta_filename string(filename ".sim")
  // 415:   $meta_c_filename string(mod_filename dup(".meta" meta_level) ".c")
  // 416:   $sim_filename string(mod_filename dup(".meta" meta_level-1) ".sim")
  // 417:   $meta_info stat(meta_filename)
  // 418:   $sim_info stat(sim_filename)
  // 419:   $meta_c_info stat(meta_c_filename)
  // 420:   
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__do_while();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__75_1_build_dependencies(void) {
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
  // 485: ... : ($line)
  // 486:   unless line .has_prefix. "/// " return
  // 487:   behind &line ' '
  // 488:   trim &line
  // 489:   $command line .truncate_from. WHITESPACE
  // 490:   $argument line .behind. WHITESPACE
  // 491:   case
  // 492:     command
  // 493:     "require":
  // 494:       if
  // ...
  frame->slots[5] /* temp__1 */ = create_closure(entry__75_2, 1);
  // 485: for_each_line c_buf: ($line)
  // 486:   unless line .has_prefix. "/// " return
  // 487:   behind &line ' '
  // 488:   trim &line
  // 489:   $command line .truncate_from. WHITESPACE
  // 490:   $argument line .behind. WHITESPACE
  // 491:   case
  // 492:     command
  // 493:     "require":
  // 494:       if
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* c_buf */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each_line();
  func = myself->type;
  frame->cont = cont__75_41;
}
static void entry__75_36(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // argument: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 513: ... !libraries(argument .truncate_from. '/') true
  frame->slots[1] /* temp__1 */ = get__true();
  // 513: ... argument .truncate_from. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* argument */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__75_37;
}
static void cont__75_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 513: ... !libraries(argument .truncate_from. '/')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__libraries();
  func = myself->type;
  frame->cont = cont__75_38;
}
static void cont__75_38(void) {
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
static void entry__75_30(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // argument: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 511: !libraries(string("sim-" argument .truncate_from. '/')) true
  frame->slots[1] /* temp__1 */ = get__true();
  // 511: ... argument .truncate_from. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* argument */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__75_31;
}
static void cont__75_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 511: ... string("sim-" argument .truncate_from. '/')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__75_32;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__75_33;
}
static void cont__75_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 511: !libraries(string("sim-" argument .truncate_from. '/'))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__libraries();
  func = myself->type;
  frame->cont = cont__75_34;
}
static void cont__75_34(void) {
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
static void entry__75_27(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // argument: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 508: ... resolve_filename(argument)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* argument */;
  result_count = 1;
  myself = var._resolve_filename;
  func = myself->type;
  frame->cont = cont__75_28;
}
static void cont__75_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 508: compile_module resolve_filename(argument) argument
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[0] /* argument */;
  result_count = frame->caller_result_count;
  myself = var._compile_module;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__75_29(void) {
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
  // 510: ... :
  // 511:   !libraries(string("sim-" argument .truncate_from. '/')) true
  frame->slots[2] /* temp__1 */ = create_closure(entry__75_30, 0);
  // 510: if do_compile_c:
  // 511:   !libraries(string("sim-" argument .truncate_from. '/')) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* do_compile_c */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__75_13(void) {
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
  // 497: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__75_14;
}
static void cont__75_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 497: $req_name range(argument 3 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* argument */;
  arguments->slots[1] = number__3;
  arguments->slots[2] = frame->slots[4] /* temp__1 */;
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
  initialize_future(frame->slots[3] /* req_name */, arguments->slots[0]);
  // 499: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__75_16;
}
static void cont__75_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 499: ... until(mod_filename '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* mod_filename */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count = 1;
  myself = get__until();
  func = myself->type;
  frame->cont = cont__75_17;
}
static void cont__75_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 499: string(until(mod_filename '/' -1) req_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* req_name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__75_18;
}
static void cont__75_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 500: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__75_19;
}
static void cont__75_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__6 */ = arguments->slots[0];
  // 500: ... until(mod_name '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* mod_name */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[9] /* temp__6 */;
  result_count = 1;
  myself = get__until();
  func = myself->type;
  frame->cont = cont__75_20;
}
static void cont__75_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__5 */ = arguments->slots[0];
  // 500: string(until(mod_name '/' -1) req_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__5 */;
  arguments->slots[1] = frame->slots[3] /* req_name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__75_21;
}
static void cont__75_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__4 */ = arguments->slots[0];
  // 498: compile_module
  // 499:   string(until(mod_filename '/' -1) req_name)
  // 500:   string(until(mod_name '/' -1) req_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = var._compile_module;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__75_11(void) {
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
  // 496: ... mode == EXE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__mode();
  arguments->slots[1] = var._EXE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__75_12;
}
static void cont__75_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 496: ... :
  // 497:   $req_name range(argument 3 -1)
  // 498:   compile_module
  // 499:     string(until(mod_filename '/' -1) req_name)
  // 500:     string(until(mod_name '/' -1) req_name)
  frame->slots[4] /* temp__2 */ = create_closure(entry__75_13, 0);
  // 496: if mode == EXE:
  // 497:   $req_name range(argument 3 -1)
  // 498:   compile_module
  // 499:     string(until(mod_filename '/' -1) req_name)
  // 500:     string(until(mod_name '/' -1) req_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__75_22(void) {
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
  arguments->slots[1] = func__75_23;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__75_26;
}
static void entry__75_23(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_build_codeblocks_project;
  arguments->slots[1] = func__75_24;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__75_25;
}
static void entry__75_24(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 506: do_list_dependencies
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._do_list_dependencies;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__75_25(void) {
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
static void cont__75_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 507: :
  // 508:   compile_module resolve_filename(argument) argument
  frame->slots[3] /* temp__2 */ = create_closure(entry__75_27, 0);
  // 509: :
  // 510:   if do_compile_c:
  // 511:     !libraries(string("sim-" argument .truncate_from. '/')) true
  frame->slots[4] /* temp__3 */ = create_closure(entry__75_29, 0);
  // 502: if
  // 503:   ||
  // 504:     do_build_static_executable
  // 505:     do_build_codeblocks_project
  // 506:     do_list_dependencies
  // 507:   :
  // 508:     compile_module resolve_filename(argument) argument
  // 509:   :
  // 510:     if do_compile_c:
  // 511:       !libraries(string("sim-" argument .truncate_from. '/')) true
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
static void entry__75_9(void) {
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
  // 495: argument .has_prefix. "./"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* argument */;
  arguments->slots[1] = string__74_56;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__75_10;
}
static void cont__75_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 495: ... :
  // 496:   if mode == EXE:
  // 497:     $req_name range(argument 3 -1)
  // 498:     compile_module
  // 499:       string(until(mod_filename '/' -1) req_name)
  // 500:       string(until(mod_name '/' -1) req_name)
  frame->slots[5] /* temp__2 */ = create_closure(entry__75_11, 0);
  // 501: :
  // 502:   if
  // 503:     ||
  // 504:       do_build_static_executable
  // 505:       do_build_codeblocks_project
  // 506:       do_list_dependencies
  // 507:     :
  // 508:       compile_module resolve_filename(argument) argument
  // 509:     :
  // 510:       if do_compile_c:
  // ...
  frame->slots[6] /* temp__3 */ = create_closure(entry__75_22, 0);
  // 494: if
  // 495:   argument .has_prefix. "./":
  // 496:     if mode == EXE:
  // 497:       $req_name range(argument 3 -1)
  // 498:       compile_module
  // 499:         string(until(mod_filename '/' -1) req_name)
  // 500:         string(until(mod_name '/' -1) req_name)
  // 501:   :
  // 502:     if
  // 503:       ||
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
static void entry__75_35(void) {
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
  // 513: ... : !libraries(argument .truncate_from. '/') true
  frame->slots[2] /* temp__1 */ = create_closure(entry__75_36, 0);
  // 513: if do_compile_c: !libraries(argument .truncate_from. '/') true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* do_compile_c */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__75_2(void) {
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
  // 486: ... line .has_prefix. "/// "
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  arguments->slots[1] = string__74_46;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__75_3;
}
static void cont__75_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 486: unless line .has_prefix. "/// " return
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* return */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__75_4;
}
static void cont__75_4(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 487: behind &line ' '
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  arguments->slots[1] = character__32;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__75_5;
}
static void cont__75_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* line */ = arguments->slots[0];
  // 488: trim &line
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__75_6;
}
static void cont__75_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* line */ = arguments->slots[0];
  // 489: $command line .truncate_from. WHITESPACE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  arguments->slots[1] = var._WHITESPACE;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__75_7;
}
static void cont__75_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* command */, arguments->slots[0]);
  // 490: $argument line .behind. WHITESPACE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  arguments->slots[1] = var._WHITESPACE;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__75_8;
}
static void cont__75_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* argument */, arguments->slots[0]);
  // 493: ... :
  // 494:   if
  // 495:     argument .has_prefix. "./":
  // 496:       if mode == EXE:
  // 497:         $req_name range(argument 3 -1)
  // 498:         compile_module
  // 499:           string(until(mod_filename '/' -1) req_name)
  // 500:           string(until(mod_name '/' -1) req_name)
  // 501:     :
  // 502:       if
  // ...
  frame->slots[7] /* temp__1 */ = create_closure(entry__75_9, 0);
  // 512: ... :
  // 513:   if do_compile_c: !libraries(argument .truncate_from. '/') true
  frame->slots[8] /* temp__2 */ = create_closure(entry__75_35, 0);
  // 491: case
  // 492:   command
  // 493:   "require":
  // 494:     if
  // 495:       argument .has_prefix. "./":
  // 496:         if mode == EXE:
  // 497:           $req_name range(argument 3 -1)
  // 498:           compile_module
  // 499:             string(until(mod_filename '/' -1) req_name)
  // 500:             string(until(mod_name '/' -1) req_name)
  // ...
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* command */;
  arguments->slots[1] = string__75_39;
  arguments->slots[2] = frame->slots[7] /* temp__1 */;
  arguments->slots[3] = string__75_40;
  arguments->slots[4] = frame->slots[8] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__75_41(void) {
  myself = frame->slots[4] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__76_1_compile_module(void) {
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
  // 524: ... :
  // 525:   (
  // 526:     submodule_names # no paths; no extensions
  // 527:     do_compile_c = true
  // 528:     suffix = "" # a hyphen followed by the platform name
  // 529:   )
  // 530:   $$modification_time undefined
  // 531:   $$sim_filenames empty_list
  // 532:   for_each submodule_names: (submodule_name)
  // 533:     $meta_level meta_levels(submodule_name)
  // ...
  frame->slots[6] /* temp__1 */ = create_closure(entry__76_2_compile_submodule, -1);
  // 524: $compile_submodule:
  // 525:   (
  // 526:     submodule_names # no paths; no extensions
  // 527:     do_compile_c = true
  // 528:     suffix = "" # a hyphen followed by the platform name
  // 529:   )
  // 530:   $$modification_time undefined
  // 531:   $$sim_filenames empty_list
  // 532:   for_each submodule_names: (submodule_name)
  // 533:     $meta_level meta_levels(submodule_name)
  // ...
  initialize_future(frame->slots[3] /* compile_submodule */, frame->slots[6] /* temp__1 */);
  // 583: lookup $mod_info mod_filename mod_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = frame->slots[1] /* mod_name */;
  result_count = 1;
  myself = var._lookup;
  func = myself->type;
  frame->cont = cont__76_78;
}
static void entry__76_2_compile_submodule(void) {
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
  // 530: $$modification_time undefined
  ((CELL *)frame->slots[6])->contents /* modification_time */ = get__undefined();
  // 531: $$sim_filenames empty_list
  ((CELL *)frame->slots[7])->contents /* sim_filenames */ = get__empty_list();
  // 532: ... : (submodule_name)
  // 533:   $meta_level meta_levels(submodule_name)
  // 534:   $submodule_filename string(until(mod_filename '/' -1) submodule_name)
  // 535:   if meta_level > 0 && not(do_omit_meta):
  // 536:     compile_meta_module submodule_filename submodule_name meta_level
  // 537:   $sim_filename string(submodule_filename ".sim")
  // 538:   push &sim_filenames sim_filename
  // 539:   $sim_info stat(sim_filename)
  // 540:   unless sim_info.is_defined:
  // 541:     Error "
  // ...
  frame->slots[11] /* temp__1 */ = create_closure(entry__76_3, 1);
  // 532: for_each submodule_names: (submodule_name)
  // 533:   $meta_level meta_levels(submodule_name)
  // 534:   $submodule_filename string(until(mod_filename '/' -1) submodule_name)
  // 535:   if meta_level > 0 && not(do_omit_meta):
  // 536:     compile_meta_module submodule_filename submodule_name meta_level
  // 537:   $sim_filename string(submodule_filename ".sim")
  // 538:   push &sim_filenames sim_filename
  // 539:   $sim_info stat(sim_filename)
  // 540:   unless sim_info.is_defined:
  // 541:     Error "
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* submodule_names */;
  arguments->slots[1] = frame->slots[11] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__76_29;
}
static void entry__76_27(void) {
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
  // 548: !modification_time modification_time_of(sim_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* sim_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__76_28;
}
static void cont__76_28(void) {
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
static void entry__76_3(void) {
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
  // 533: $meta_level meta_levels(submodule_name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* submodule_name */;
  result_count = 1;
  myself = var._meta_levels;
  func = myself->type;
  frame->cont = cont__76_4;
}
static void cont__76_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* meta_level */, arguments->slots[0]);
  // 534: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__76_5;
}
static void cont__76_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__2 */ = arguments->slots[0];
  // 534: ... until(mod_filename '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* mod_filename */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[9] /* temp__2 */;
  result_count = 1;
  myself = get__until();
  func = myself->type;
  frame->cont = cont__76_6;
}
static void cont__76_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 534: $submodule_filename string(until(mod_filename '/' -1) submodule_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = frame->slots[0] /* submodule_name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__76_7;
}
static void cont__76_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* submodule_filename */, arguments->slots[0]);
  // 535: ... meta_level > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = frame->slots[4] /* meta_level */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__76_8;
}
static void cont__76_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__2 */ = arguments->slots[0];
  // 535: ... meta_level > 0 && not(do_omit_meta)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__2 */;
  arguments->slots[1] = func__76_9;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__76_11;
}
static void entry__76_9(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 535: ... not(do_omit_meta)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._do_omit_meta;
  result_count = 1;
  myself = get__not();
  func = myself->type;
  frame->cont = cont__76_10;
}
static void cont__76_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 535: ... not(do_omit_meta)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__76_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 535: ... :
  // 536:   compile_meta_module submodule_filename submodule_name meta_level
  frame->slots[10] /* temp__3 */ = create_closure(entry__76_12, 0);
  // 535: if meta_level > 0 && not(do_omit_meta):
  // 536:   compile_meta_module submodule_filename submodule_name meta_level
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__76_13;
}
static void entry__76_12(void) {
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
  // 536: compile_meta_module submodule_filename submodule_name meta_level
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
static void cont__76_13(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 537: $sim_filename string(submodule_filename ".sim")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* submodule_filename */;
  arguments->slots[1] = string__70_13;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__76_14;
}
static void cont__76_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* sim_filename */, arguments->slots[0]);
  // 538: push &sim_filenames sim_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* sim_filenames */;
  arguments->slots[1] = frame->slots[6] /* sim_filename */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__76_15;
}
static void cont__76_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* sim_filenames */ = arguments->slots[0];
  // 539: $sim_info stat(sim_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* sim_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__76_16;
}
static void cont__76_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[7] /* sim_info */, arguments->slots[0]);
  // 540: ... sim_info.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* sim_info */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__76_17;
}
static void cont__76_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 540: ... :
  // 541:   Error "
  // 542:     Failed to open file "@(sim_filename)"!@
  frame->slots[9] /* temp__2 */ = create_closure(entry__76_18, 0);
  // 540: unless sim_info.is_defined:
  // 541:   Error "
  // 542:     Failed to open file "@(sim_filename)"!@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__76_21;
}
static void entry__76_18(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // sim_filename: 0
  frame->slots[0] = myself->closure.frame->slots[6]; /* sim_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 541: ... "
  // 542:   Failed to open file "@(sim_filename)"!@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__76_19;
  arguments->slots[1] = frame->slots[0] /* sim_filename */;
  arguments->slots[2] = string__69_22;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__76_20;
}
static void cont__76_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 541: Error "
  // 542:   Failed to open file "@(sim_filename)"!@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__76_21(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 545: modification_time.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* modification_time */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__76_22;
}
static void cont__76_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__2 */ = arguments->slots[0];
  // 546: modification_time_of(sim_info) > modification_time
  frame->slots[10] /* temp__3 */ = create_closure(entry__76_23, 0);
  // 544: ||
  // 545:   modification_time.is_undefined
  // 546:   modification_time_of(sim_info) > modification_time
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__2 */;
  arguments->slots[1] = frame->slots[10] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__76_26;
}
static void entry__76_23(void) {
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
  // 546: modification_time_of(sim_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* sim_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__76_24;
}
static void cont__76_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 546: modification_time_of(sim_info) > modification_time
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* modification_time */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__76_25;
}
static void cont__76_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 546: modification_time_of(sim_info) > modification_time
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__76_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 547: :
  // 548:   !modification_time modification_time_of(sim_info)
  frame->slots[11] /* temp__4 */ = create_closure(entry__76_27, 0);
  // 543: if
  // 544:   ||
  // 545:     modification_time.is_undefined
  // 546:     modification_time_of(sim_info) > modification_time
  // 547:   :
  // 548:     !modification_time modification_time_of(sim_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = frame->slots[11] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__76_29(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 549: $c_filename string(mod_filename suffix ".c")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* mod_filename */;
  arguments->slots[1] = frame->slots[2] /* suffix */;
  arguments->slots[2] = string__74_9;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__76_30;
}
static void cont__76_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[8] /* c_filename */, arguments->slots[0]);
  // 550: $c_info stat(c_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* c_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__76_31;
}
static void cont__76_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[9] /* c_info */, arguments->slots[0]);
  // 551: ... : !c_sources(c_filename) true
  frame->slots[11] /* temp__1 */ = create_closure(entry__76_32, 0);
  // 551: if do_compile_c: !c_sources(c_filename) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* do_compile_c */;
  arguments->slots[1] = frame->slots[11] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__76_34;
}
static void entry__76_32(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // c_filename: 0
  frame->slots[0] = myself->closure.frame->slots[8]; /* c_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 551: ... !c_sources(c_filename) true
  frame->slots[1] /* temp__1 */ = get__true();
  // 551: ... !c_sources(c_filename)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_filename */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = var._c_sources;
  func = myself->type;
  frame->cont = cont__76_33;
}
static void cont__76_33(void) {
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
static void cont__76_34(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 552: $$c_buf undefined
  ((CELL *)frame->slots[10])->contents /* c_buf */ = get__undefined();
  frame->slots[12] /* temp__2 */ = create_closure(entry__76_35, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_rebuild;
  arguments->slots[1] = frame->slots[12] /* temp__2 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__76_41;
}
static void entry__76_35(void) {
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
  // 556: c_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__76_36;
}
static void cont__76_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 557: modification_time > modification_time_of(c_info)
  frame->slots[4] /* temp__3 */ = create_closure(entry__76_37, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__76_40;
}
static void entry__76_37(void) {
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
  // 557: ... modification_time_of(c_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__76_38;
}
static void cont__76_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 557: modification_time > modification_time_of(c_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* modification_time */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__76_39;
}
static void cont__76_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 557: modification_time > modification_time_of(c_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
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
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__76_41(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 558: :
  // 559:   %sim2c::module_name replace_all(mod_name '/' = "__" '.' = "__")
  // 560:   if verbose: ewriteln "build module " module_name suffix
  // 561:   collect_output $c_source: sim2c sim_filenames
  // 562:   collect_output !c_buf: create_imports c_source
  // 563:   save c_filename c_buf.to_utf8
  // 564:   if do_compile_c: compile_c c_filename o_filename
  frame->slots[13] /* temp__3 */ = create_closure(entry__76_42, 0);
  // 565: :
  // 566:   load !c_buf c_filename
  // 567:   $o_info stat(o_filename)
  // 568:   if
  // 569:     ||
  // 570:       o_info.is_undefined
  // 571:       modification_time_of(c_info) > modification_time_of(o_info)
  // 572:     :
  // 573:       if do_compile_c: compile_c c_filename o_filename
  // 574:     :
  // ...
  frame->slots[14] /* temp__4 */ = create_closure(entry__76_58, 0);
  // 553: if
  // 554:   ||
  // 555:     do_rebuild
  // 556:     c_info.is_undefined
  // 557:     modification_time > modification_time_of(c_info)
  // 558:   :
  // 559:     %sim2c::module_name replace_all(mod_name '/' = "__" '.' = "__")
  // 560:     if verbose: ewriteln "build module " module_name suffix
  // 561:     collect_output $c_source: sim2c sim_filenames
  // 562:     collect_output !c_buf: create_imports c_source
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  arguments->slots[1] = frame->slots[13] /* temp__3 */;
  arguments->slots[2] = frame->slots[14] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__76_77;
}
static void entry__76_75(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // o_info: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* o_info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 580: !last_modification_time modification_time_of(o_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* o_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__76_76;
}
static void cont__76_76(void) {
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
static void entry__76_68(void) {
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
  // 573: ... compile_c c_filename o_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_filename */;
  arguments->slots[1] = frame->slots[1] /* o_filename */;
  result_count = frame->caller_result_count;
  myself = var._compile_c;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__76_67(void) {
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
  // 573: ... : compile_c c_filename o_filename
  frame->slots[3] /* temp__1 */ = create_closure(entry__76_68, 0);
  // 573: if do_compile_c: compile_c c_filename o_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* do_compile_c */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__76_69(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // o_info: 0
  frame->slots[0] = myself->closure.frame->slots[5]; /* o_info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 577: last_modification_time.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__last_modification_time();
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__76_70;
}
static void cont__76_70(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 578: modification_time_of(o_info) > last_modification_time
  frame->slots[3] /* temp__3 */ = create_closure(entry__76_71, 0);
  // 576: ||
  // 577:   last_modification_time.is_undefined
  // 578:   modification_time_of(o_info) > last_modification_time
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__76_74;
}
static void entry__76_71(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // o_info: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* o_info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 578: modification_time_of(o_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* o_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__76_72;
}
static void cont__76_72(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 578: modification_time_of(o_info) > last_modification_time
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__last_modification_time();
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__76_73;
}
static void cont__76_73(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 578: modification_time_of(o_info) > last_modification_time
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__76_74(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 579: :
  // 580:   !last_modification_time modification_time_of(o_info)
  frame->slots[4] /* temp__4 */ = create_closure(entry__76_75, 0);
  // 575: if
  // 576:   ||
  // 577:     last_modification_time.is_undefined
  // 578:     modification_time_of(o_info) > last_modification_time
  // 579:   :
  // 580:     !last_modification_time modification_time_of(o_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__76_42(void) {
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
  // 559: ... '/' = "__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = string__76_43;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__76_44;
}
static void cont__76_44(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 559: ... '.' = "__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__46;
  arguments->slots[1] = string__76_43;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__76_45;
}
static void cont__76_45(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__2 */ = arguments->slots[0];
  // 559: %sim2c::module_name replace_all(mod_name '/' = "__" '.' = "__")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* mod_name */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  arguments->slots[2] = frame->slots[10] /* temp__2 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__76_46;
}
static void cont__76_46(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(get__sim2c__module_name(), arguments->slots[0]);
  // 560: ... : ewriteln "build module " module_name suffix
  frame->slots[9] /* temp__1 */ = create_closure(entry__76_47, 0);
  // 560: if verbose: ewriteln "build module " module_name suffix
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__76_49;
}
static void entry__76_47(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // suffix: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* suffix */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 560: ... ewriteln "build module " module_name suffix
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__76_48;
  arguments->slots[1] = get__module_name();
  arguments->slots[2] = frame->slots[0] /* suffix */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__76_49(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 561: ... : sim2c sim_filenames
  frame->slots[9] /* temp__1 */ = create_closure(entry__76_50, 0);
  // 561: collect_output $c_source: sim2c sim_filenames
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__76_51;
}
static void entry__76_50(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // sim_filenames: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* sim_filenames */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 561: ... sim2c sim_filenames
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* sim_filenames */;
  result_count = frame->caller_result_count;
  myself = get__sim2c();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__76_51(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[8] /* c_source */, arguments->slots[0]);
  // 562: ... : create_imports c_source
  frame->slots[9] /* temp__1 */ = create_closure(entry__76_52, 0);
  // 562: collect_output !c_buf: create_imports c_source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__76_53;
}
static void entry__76_52(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // c_source: 0
  frame->slots[0] = myself->closure.frame->slots[8]; /* c_source */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 562: ... create_imports c_source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_source */;
  result_count = frame->caller_result_count;
  myself = var._create_imports;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__76_53(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* c_buf */ = arguments->slots[0];
  // 563: ... c_buf.to_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* c_buf */;
  result_count = 1;
  myself = get__to_utf8();
  func = myself->type;
  frame->cont = cont__76_54;
}
static void cont__76_54(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 563: save c_filename c_buf.to_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* c_filename */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 0;
  myself = get__save();
  func = myself->type;
  frame->cont = cont__76_55;
}
static void cont__76_55(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 564: ... : compile_c c_filename o_filename
  frame->slots[9] /* temp__1 */ = create_closure(entry__76_56, 0);
  // 564: if do_compile_c: compile_c c_filename o_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* do_compile_c */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__76_57;
}
static void entry__76_56(void) {
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
  // 564: ... compile_c c_filename o_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_filename */;
  arguments->slots[1] = frame->slots[1] /* o_filename */;
  result_count = frame->caller_result_count;
  myself = var._compile_c;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__76_57(void) {
  myself = frame->slots[0] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__76_58(void) {
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
  // 566: load !c_buf c_filename
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* c_filename */;
  result_count = 1;
  myself = get__load();
  func = myself->type;
  frame->cont = cont__76_59;
}
static void cont__76_59(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* c_buf */ = arguments->slots[0];
  // 567: $o_info stat(o_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* o_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__76_60;
}
static void cont__76_60(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* o_info */, arguments->slots[0]);
  // 570: o_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* o_info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__76_61;
}
static void cont__76_61(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 571: modification_time_of(c_info) > modification_time_of(o_info)
  frame->slots[8] /* temp__3 */ = create_closure(entry__76_62, 0);
  // 569: ||
  // 570:   o_info.is_undefined
  // 571:   modification_time_of(c_info) > modification_time_of(o_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  arguments->slots[1] = frame->slots[8] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__76_66;
}
static void entry__76_62(void) {
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
  // 571: ... modification_time_of(o_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* o_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__76_63;
}
static void cont__76_63(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 571: modification_time_of(c_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* c_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__76_64;
}
static void cont__76_64(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 571: modification_time_of(c_info) > modification_time_of(o_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__76_65;
}
static void cont__76_65(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 571: modification_time_of(c_info) > modification_time_of(o_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__76_66(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 572: :
  // 573:   if do_compile_c: compile_c c_filename o_filename
  frame->slots[9] /* temp__4 */ = create_closure(entry__76_67, 0);
  // 574: :
  // 575:   if
  // 576:     ||
  // 577:       last_modification_time.is_undefined
  // 578:       modification_time_of(o_info) > last_modification_time
  // 579:     :
  // 580:       !last_modification_time modification_time_of(o_info)
  frame->slots[10] /* temp__5 */ = create_closure(entry__76_69, 0);
  // 568: if
  // 569:   ||
  // 570:     o_info.is_undefined
  // 571:     modification_time_of(c_info) > modification_time_of(o_info)
  // 572:   :
  // 573:     if do_compile_c: compile_c c_filename o_filename
  // 574:   :
  // 575:     if
  // 576:       ||
  // 577:         last_modification_time.is_undefined
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
static void cont__76_77(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 581: build_dependencies mod_filename mod_name c_buf do_compile_c
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
static void cont__76_78(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* mod_info */, arguments->slots[0]);
  // 584: ... mod_info.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* mod_info */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__76_79;
}
static void cont__76_79(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 584: ... :
  // 585:   Error "
  // 586:     No source file(s) for module "@(mod_name)" found!@
  frame->slots[7] /* temp__2 */ = create_closure(entry__76_80, 0);
  // 584: unless mod_info.is_defined:
  // 585:   Error "
  // 586:     No source file(s) for module "@(mod_name)" found!@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__76_84;
}
static void entry__76_80(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // mod_name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* mod_name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 585: ... "
  // 586:   No source file(s) for module "@(mod_name)" found!@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__76_81;
  arguments->slots[1] = frame->slots[0] /* mod_name */;
  arguments->slots[2] = string__76_82;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__76_83;
}
static void cont__76_83(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 585: Error "
  // 586:   No source file(s) for module "@(mod_name)" found!@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__76_84(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 587: $o_filename append(mod_filename ".o")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = string__76_85;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__76_86;
}
static void cont__76_86(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* o_filename */, arguments->slots[0]);
  // 588: ... objects(o_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* o_filename */;
  result_count = 1;
  myself = get__objects();
  func = myself->type;
  frame->cont = cont__76_87;
}
static void cont__76_87(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 588: if objects(o_filename) return
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* return */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__76_88;
}
static void cont__76_88(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 589: !objects(o_filename) true
  frame->slots[6] /* temp__1 */ = get__true();
  // 589: !objects(o_filename)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* o_filename */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = get__objects();
  func = myself->type;
  frame->cont = cont__76_89;
}
static void cont__76_89(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__objects(arguments->slots[0]);
  // 591: mod_info.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* mod_info */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__76_90;
}
static void cont__76_90(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 591: ... :
  // 592:   compile_submodule list(truncate_until(mod_name '/' -1))
  // 593:   if do_list_dependencies: push &dependencies string(mod_filename ".c")
  frame->slots[7] /* temp__2 */ = create_closure(entry__76_91, 0);
  // 594: :
  // 595:   do:
  // 596:     $$best_platform undefined
  // 597:     $$best_priority 999
  // 598:     for_each mod_info: (platform _filenames)
  // 599:       $priority platform_priority(platform)
  // 600:       if priority.is_defined && priority < best_priority:
  // 601:         !best_platform platform
  // 602:         !best_priority priority
  // 603:     for_each mod_info: (platform filenames)
  // ...
  frame->slots[8] /* temp__3 */ = create_closure(entry__76_99, 0);
  // 590: if
  // 591:   mod_info.is_empty:
  // 592:     compile_submodule list(truncate_until(mod_name '/' -1))
  // 593:     if do_list_dependencies: push &dependencies string(mod_filename ".c")
  // 594:   :
  // 595:     do:
  // 596:       $$best_platform undefined
  // 597:       $$best_priority 999
  // 598:       for_each mod_info: (platform _filenames)
  // 599:         $priority platform_priority(platform)
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  arguments->slots[2] = frame->slots[8] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__76_140;
}
static void entry__76_130(void) {
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
  // 623: $$dependency string(mod_filename "-" platform ".c")
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* mod_filename */;
  arguments->slots[1] = string__70_46;
  arguments->slots[2] = frame->slots[0] /* platform */;
  arguments->slots[3] = string__74_9;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__76_131;
}
static void cont__76_131(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* dependency */ = arguments->slots[0];
  // 624: $platforms used_by(platform)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* platform */;
  result_count = 1;
  myself = ((CELL *)frame->slots[3])->contents /* used_by */;
  func = myself->type;
  frame->cont = cont__76_132;
}
static void cont__76_132(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* platforms */, arguments->slots[0]);
  // 625: ... platforms.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* platforms */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__76_133;
}
static void cont__76_133(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 625: ... :
  // 626:   for_each platforms: (plat) write_to &dependency " #" plat
  frame->slots[7] /* temp__2 */ = create_closure(entry__76_134, 0);
  // 625: if platforms.is_defined:
  // 626:   for_each platforms: (plat) write_to &dependency " #" plat
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__76_138;
}
static void entry__76_135(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // plat: 0
  // dependency: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* dependency */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 626: ... write_to &dependency " #" plat
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* dependency */;
  arguments->slots[1] = string__76_136;
  arguments->slots[2] = frame->slots[0] /* plat */;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__76_137;
}
static void cont__76_137(void) {
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
static void entry__76_134(void) {
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
  // 626: ... : (plat) write_to &dependency " #" plat
  frame->slots[2] /* temp__1 */ = create_closure(entry__76_135, 1);
  // 626: for_each platforms: (plat) write_to &dependency " #" plat
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* platforms */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__76_138(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 627: push &dependencies dependency
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._dependencies;
  arguments->slots[1] = ((CELL *)frame->slots[4])->contents /* dependency */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__76_139;
}
static void cont__76_139(void) {
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
static void entry__76_113(void) {
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
  // 609: $$used_by empty_table
  ((CELL *)frame->slots[2])->contents /* used_by */ = get__empty_table();
  // 610: ... : (supported_platform _parent_platform)
  // 611:   $$best_platform undefined
  // 612:   $$best_priority 999
  // 613:   for_each mod_info: (platform _filenames)
  // 614:     $priority platform_specific_priority(supported_platform platform)
  // 615:     if priority.is_defined && priority < best_priority:
  // 616:       !best_platform platform
  // 617:       !best_priority priority
  // 618:   if best_platform.is_defined:
  // 619:     $$ub default_value(used_by(best_platform) empty_list)
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__76_114, 2);
  // 610: for_each supported_platforms: (supported_platform _parent_platform)
  // 611:   $$best_platform undefined
  // 612:   $$best_priority 999
  // 613:   for_each mod_info: (platform _filenames)
  // 614:     $priority platform_specific_priority(supported_platform platform)
  // 615:     if priority.is_defined && priority < best_priority:
  // 616:       !best_platform platform
  // 617:       !best_priority priority
  // 618:   if best_platform.is_defined:
  // 619:     $$ub default_value(used_by(best_platform) empty_list)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._supported_platforms;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__76_129;
}
static void entry__76_124(void) {
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
  // 619: ... used_by(best_platform)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* best_platform */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* used_by */;
  func = myself->type;
  frame->cont = cont__76_125;
}
static void cont__76_125(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 619: $$ub default_value(used_by(best_platform) empty_list)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = get__empty_list();
  result_count = 1;
  myself = get__default_value();
  func = myself->type;
  frame->cont = cont__76_126;
}
static void cont__76_126(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* ub */ = arguments->slots[0];
  // 620: push &ub supported_platform
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* ub */;
  arguments->slots[1] = frame->slots[2] /* supported_platform */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__76_127;
}
static void cont__76_127(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* ub */ = arguments->slots[0];
  // 621: !used_by(best_platform) ub
  frame->slots[4] /* temp__1 */ = ((CELL *)frame->slots[3])->contents /* ub */;
  // 621: !used_by(best_platform)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* best_platform */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* used_by */;
  func = myself->type;
  frame->cont = cont__76_128;
}
static void cont__76_128(void) {
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
static void entry__76_114(void) {
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
  // 611: $$best_platform undefined
  ((CELL *)frame->slots[4])->contents /* best_platform */ = get__undefined();
  // 612: $$best_priority 999
  ((CELL *)frame->slots[5])->contents /* best_priority */ = number__999;
  // 613: ... : (platform _filenames)
  // 614:   $priority platform_specific_priority(supported_platform platform)
  // 615:   if priority.is_defined && priority < best_priority:
  // 616:     !best_platform platform
  // 617:     !best_priority priority
  frame->slots[6] /* temp__1 */ = create_closure(entry__76_115, 2);
  // 613: for_each mod_info: (platform _filenames)
  // 614:   $priority platform_specific_priority(supported_platform platform)
  // 615:   if priority.is_defined && priority < best_priority:
  // 616:     !best_platform platform
  // 617:     !best_priority priority
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* mod_info */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__76_122;
}
static void entry__76_121(void) {
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
  // 616: !best_platform platform
  ((CELL *)frame->slots[0])->contents /* best_platform */ = frame->slots[1] /* platform */;
  // 617: !best_priority priority
  ((CELL *)frame->slots[2])->contents /* best_priority */ = frame->slots[3] /* priority */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__76_115(void) {
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
  // 614: $priority platform_specific_priority(supported_platform platform)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* supported_platform */;
  arguments->slots[1] = frame->slots[0] /* platform */;
  result_count = 1;
  myself = var._platform_specific_priority;
  func = myself->type;
  frame->cont = cont__76_116;
}
static void cont__76_116(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* priority */, arguments->slots[0]);
  // 615: ... priority.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* priority */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__76_117;
}
static void cont__76_117(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 615: ... priority < best_priority
  frame->slots[8] /* temp__3 */ = create_closure(entry__76_118, 0);
  // 615: ... priority.is_defined && priority < best_priority
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  arguments->slots[1] = frame->slots[8] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__76_120;
}
static void entry__76_118(void) {
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
  // 615: ... priority < best_priority
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* priority */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* best_priority */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__76_119;
}
static void cont__76_119(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 615: ... priority < best_priority
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__76_120(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 615: ... :
  // 616:   !best_platform platform
  // 617:   !best_priority priority
  frame->slots[9] /* temp__4 */ = create_closure(entry__76_121, 0);
  // 615: if priority.is_defined && priority < best_priority:
  // 616:   !best_platform platform
  // 617:   !best_priority priority
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__76_122(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 618: ... best_platform.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* best_platform */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__76_123;
}
static void cont__76_123(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 618: ... :
  // 619:   $$ub default_value(used_by(best_platform) empty_list)
  // 620:   push &ub supported_platform
  // 621:   !used_by(best_platform) ub
  frame->slots[7] /* temp__2 */ = create_closure(entry__76_124, 0);
  // 618: if best_platform.is_defined:
  // 619:   $$ub default_value(used_by(best_platform) empty_list)
  // 620:   push &ub supported_platform
  // 621:   !used_by(best_platform) ub
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__76_129(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 622: ... : (platform _filenames)
  // 623:   $$dependency string(mod_filename "-" platform ".c")
  // 624:   $platforms used_by(platform)
  // 625:   if platforms.is_defined:
  // 626:     for_each platforms: (plat) write_to &dependency " #" plat
  // 627:   push &dependencies dependency
  frame->slots[3] /* temp__1 */ = create_closure(entry__76_130, 2);
  // 622: for_each mod_info: (platform _filenames)
  // 623:   $$dependency string(mod_filename "-" platform ".c")
  // 624:   $platforms used_by(platform)
  // 625:   if platforms.is_defined:
  // 626:     for_each platforms: (plat) write_to &dependency " #" plat
  // 627:   push &dependencies dependency
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_info */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__76_96(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // mod_filename: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* mod_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 593: ... string(mod_filename ".c")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = string__74_9;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__76_97;
}
static void cont__76_97(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 593: ... push &dependencies string(mod_filename ".c")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._dependencies;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__76_98;
}
static void cont__76_98(void) {
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
static void entry__76_91(void) {
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
  // 592: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__76_92;
}
static void cont__76_92(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 592: ... truncate_until(mod_name '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* mod_name */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__76_93;
}
static void cont__76_93(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 592: ... list(truncate_until(mod_name '/' -1))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__76_94;
}
static void cont__76_94(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 592: compile_submodule list(truncate_until(mod_name '/' -1))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = frame->slots[0] /* compile_submodule */;
  func = myself->type;
  frame->cont = cont__76_95;
}
static void cont__76_95(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 593: ... : push &dependencies string(mod_filename ".c")
  frame->slots[3] /* temp__1 */ = create_closure(entry__76_96, 0);
  // 593: if do_list_dependencies: push &dependencies string(mod_filename ".c")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_list_dependencies;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__76_99(void) {
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
  // 595: ... :
  // 596:   $$best_platform undefined
  // 597:   $$best_priority 999
  // 598:   for_each mod_info: (platform _filenames)
  // 599:     $priority platform_priority(platform)
  // 600:     if priority.is_defined && priority < best_priority:
  // 601:       !best_platform platform
  // 602:       !best_priority priority
  // 603:   for_each mod_info: (platform filenames)
  // 604:     compile_submodule
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__76_100, 0);
  // 595: do:
  // 596:   $$best_platform undefined
  // 597:   $$best_priority 999
  // 598:   for_each mod_info: (platform _filenames)
  // 599:     $priority platform_priority(platform)
  // 600:     if priority.is_defined && priority < best_priority:
  // 601:       !best_platform platform
  // 602:       !best_priority priority
  // 603:   for_each mod_info: (platform filenames)
  // 604:     compile_submodule
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__76_112;
}
static void entry__76_109(void) {
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
  // 606: platform == best_platform
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* platform */;
  arguments->slots[1] = ((CELL *)frame->slots[3])->contents /* best_platform */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__76_110;
}
static void cont__76_110(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 607: string("-" platform)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__70_46;
  arguments->slots[1] = frame->slots[0] /* platform */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__76_111;
}
static void cont__76_111(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 604: compile_submodule
  // 605:   filenames
  // 606:   platform == best_platform
  // 607:   string("-" platform)
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
static void entry__76_100(void) {
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
  // 596: $$best_platform undefined
  ((CELL *)frame->slots[2])->contents /* best_platform */ = get__undefined();
  // 597: $$best_priority 999
  ((CELL *)frame->slots[3])->contents /* best_priority */ = number__999;
  // 598: ... : (platform _filenames)
  // 599:   $priority platform_priority(platform)
  // 600:   if priority.is_defined && priority < best_priority:
  // 601:     !best_platform platform
  // 602:     !best_priority priority
  frame->slots[4] /* temp__1 */ = create_closure(entry__76_101, 2);
  // 598: for_each mod_info: (platform _filenames)
  // 599:   $priority platform_priority(platform)
  // 600:   if priority.is_defined && priority < best_priority:
  // 601:     !best_platform platform
  // 602:     !best_priority priority
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_info */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__76_108;
}
static void entry__76_107(void) {
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
  // 601: !best_platform platform
  ((CELL *)frame->slots[0])->contents /* best_platform */ = frame->slots[1] /* platform */;
  // 602: !best_priority priority
  ((CELL *)frame->slots[2])->contents /* best_priority */ = frame->slots[3] /* priority */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__76_101(void) {
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
  // 599: $priority platform_priority(platform)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* platform */;
  result_count = 1;
  myself = var._platform_priority;
  func = myself->type;
  frame->cont = cont__76_102;
}
static void cont__76_102(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* priority */, arguments->slots[0]);
  // 600: ... priority.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* priority */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__76_103;
}
static void cont__76_103(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 600: ... priority < best_priority
  frame->slots[7] /* temp__3 */ = create_closure(entry__76_104, 0);
  // 600: ... priority.is_defined && priority < best_priority
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__76_106;
}
static void entry__76_104(void) {
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
  // 600: ... priority < best_priority
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* priority */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* best_priority */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__76_105;
}
static void cont__76_105(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 600: ... priority < best_priority
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__76_106(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 600: ... :
  // 601:   !best_platform platform
  // 602:   !best_priority priority
  frame->slots[8] /* temp__4 */ = create_closure(entry__76_107, 0);
  // 600: if priority.is_defined && priority < best_priority:
  // 601:   !best_platform platform
  // 602:   !best_priority priority
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__76_108(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 603: ... : (platform filenames)
  // 604:   compile_submodule
  // 605:     filenames
  // 606:     platform == best_platform
  // 607:     string("-" platform)
  frame->slots[4] /* temp__1 */ = create_closure(entry__76_109, 2);
  // 603: for_each mod_info: (platform filenames)
  // 604:   compile_submodule
  // 605:     filenames
  // 606:     platform == best_platform
  // 607:     string("-" platform)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_info */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__76_112(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 608: ... :
  // 609:   $$used_by empty_table
  // 610:   for_each supported_platforms: (supported_platform _parent_platform)
  // 611:     $$best_platform undefined
  // 612:     $$best_priority 999
  // 613:     for_each mod_info: (platform _filenames)
  // 614:       $priority platform_specific_priority(supported_platform platform)
  // 615:       if priority.is_defined && priority < best_priority:
  // 616:         !best_platform platform
  // 617:         !best_priority priority
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__76_113, 0);
  // 608: if do_list_dependencies:
  // 609:   $$used_by empty_table
  // 610:   for_each supported_platforms: (supported_platform _parent_platform)
  // 611:     $$best_platform undefined
  // 612:     $$best_priority 999
  // 613:     for_each mod_info: (platform _filenames)
  // 614:       $priority platform_specific_priority(supported_platform platform)
  // 615:       if priority.is_defined && priority < best_priority:
  // 616:         !best_platform platform
  // 617:         !best_priority priority
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
static void cont__76_140(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__77_8(void) {
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
  // 638: ... string(path '/' name)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* path */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__77_9;
}
static void cont__77_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 638: ... string(mod_path '/' name)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* mod_path */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__77_10;
}
static void cont__77_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 638: compile_module string(path '/' name) string(mod_path '/' name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = var._compile_module;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__77_1_compile_modules(void) {
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
  // 634: ... string(mod_path '/')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* mod_path */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__77_2;
}
static void cont__77_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 634: add_module_infos $directories $modules path string(mod_path '/')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* path */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 2;
  myself = var._add_module_infos;
  func = myself->type;
  frame->cont = cont__77_3;
}
static void cont__77_3(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  frame->slots[6] /* temp__3 */ = arguments->slots[1];
  // 634: ... directories
  initialize_future(frame->slots[2] /* directories */, frame->slots[5] /* temp__2 */);
  // 634: ... modules
  initialize_future(frame->slots[3] /* modules */, frame->slots[6] /* temp__3 */);
  // 635: ... : (name)
  // 636:   compile_modules string(path '/' name) string(mod_path '/' name)
  frame->slots[4] /* temp__1 */ = create_closure(entry__77_4, 1);
  // 635: for_each directories: (name)
  // 636:   compile_modules string(path '/' name) string(mod_path '/' name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* directories */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__77_7;
}
static void entry__77_4(void) {
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
  frame->cont = cont__77_5;
}
static void cont__77_5(void) {
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
  frame->cont = cont__77_6;
}
static void cont__77_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 636: compile_modules string(path '/' name) string(mod_path '/' name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = var._compile_modules;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__77_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 637: ... : (name)
  // 638:   compile_module string(path '/' name) string(mod_path '/' name)
  frame->slots[4] /* temp__1 */ = create_closure(entry__77_8, 1);
  // 637: for_each modules: (name)
  // 638:   compile_module string(path '/' name) string(mod_path '/' name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* modules */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__79_2(void) {
  allocate_initialized_frame_gc(0, 3);
  // slot allocations:
  // path: 0
  frame->slots[0] /* path */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 646: $path environment("LD_LIBRARY_PATH")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__79_3;
  result_count = 1;
  myself = get__environment();
  func = myself->type;
  frame->cont = cont__79_4;
}
static void cont__79_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[0] /* path */, arguments->slots[0]);
  // 647: ... path.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* path */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__79_5;
}
static void cont__79_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 647: ... : ewriteln "LD_LIBRARY_PATH=@(path)"
  frame->slots[2] /* temp__2 */ = create_closure(entry__79_6, 0);
  // 647: if path.is_defined: ewriteln "LD_LIBRARY_PATH=@(path)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__79_9;
}
static void entry__79_6(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // path: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* path */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 647: ... "LD_LIBRARY_PATH=@(path)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__79_7;
  arguments->slots[1] = frame->slots[0] /* path */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__79_8;
}
static void cont__79_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 647: ... ewriteln "LD_LIBRARY_PATH=@(path)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__79_9(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 648: ... serialize(objects)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__objects();
  result_count = 1;
  myself = get__serialize();
  func = myself->type;
  frame->cont = cont__79_10;
}
static void cont__79_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 648: ewriteln "included object files: " serialize(objects)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__79_11;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 0;
  myself = get__ewriteln();
  func = myself->type;
  frame->cont = cont__79_12;
}
static void cont__79_12(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 649: ... serialize(libraries)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__libraries();
  result_count = 1;
  myself = get__serialize();
  func = myself->type;
  frame->cont = cont__79_13;
}
static void cont__79_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 649: ewriteln "needed libraries: " serialize(libraries)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__79_14;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__79_1_show_file_list(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 645: if do_show_debug_infos:
  // 646:   $path environment("LD_LIBRARY_PATH")
  // 647:   if path.is_defined: ewriteln "LD_LIBRARY_PATH=@(path)"
  // 648:   ewriteln "included object files: " serialize(objects)
  // 649:   ewriteln "needed libraries: " serialize(libraries)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_show_debug_infos();
  arguments->slots[1] = func__79_2;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__80_1_library_paths_and_file_list(void) {
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
  // 652: show_file_list
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._show_file_list;
  func = myself->type;
  frame->cont = cont__80_2;
}
static void cont__80_2(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 653: $$library_paths empty_list
  ((CELL *)frame->slots[0])->contents /* library_paths */ = get__empty_list();
  // 654: $$object_files empty_list
  ((CELL *)frame->slots[1])->contents /* object_files */ = get__empty_list();
  // 655: $$library_files empty_list
  ((CELL *)frame->slots[2])->contents /* library_files */ = get__empty_list();
  // 656: $paths environment("LD_LIBRARY_PATH")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__79_3;
  result_count = 1;
  myself = get__environment();
  func = myself->type;
  frame->cont = cont__80_3;
}
static void cont__80_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* paths */, arguments->slots[0]);
  // 657: ... paths.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* paths */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__80_4;
}
static void cont__80_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 657: ... :
  // 658:   for_each paths .split. ':': (path) push &library_paths "-L@(path)"
  frame->slots[5] /* temp__2 */ = create_closure(entry__80_5, 0);
  // 657: if paths.is_defined:
  // 658:   for_each paths .split. ':': (path) push &library_paths "-L@(path)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__80_11;
}
static void entry__80_7(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // path: 0
  // library_paths: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* library_paths */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 658: ... "-L@(path)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__80_8;
  arguments->slots[1] = frame->slots[0] /* path */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__80_9;
}
static void cont__80_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 658: ... push &library_paths "-L@(path)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* library_paths */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__80_10;
}
static void cont__80_10(void) {
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
static void entry__80_5(void) {
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
  // 658: ... paths .split. ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* paths */;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__split();
  func = myself->type;
  frame->cont = cont__80_6;
}
static void cont__80_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 658: ... : (path) push &library_paths "-L@(path)"
  frame->slots[3] /* temp__2 */ = create_closure(entry__80_7, 1);
  // 658: for_each paths .split. ':': (path) push &library_paths "-L@(path)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__80_11(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 659: ... : ewriteln "library paths: " serialize(library_paths)
  frame->slots[4] /* temp__1 */ = create_closure(entry__80_12, 0);
  // 659: if do_show_debug_infos: ewriteln "library paths: " serialize(library_paths)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_show_debug_infos();
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__80_15;
}
static void entry__80_12(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // library_paths: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* library_paths */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 659: ... serialize(library_paths)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* library_paths */;
  result_count = 1;
  myself = get__serialize();
  func = myself->type;
  frame->cont = cont__80_13;
}
static void cont__80_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 659: ... ewriteln "library paths: " serialize(library_paths)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__80_14;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__80_15(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 660: ... : (object) push &object_files object
  frame->slots[4] /* temp__1 */ = create_closure(entry__80_16, 1);
  // 660: for_each objects: (object) push &object_files object
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__objects();
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__80_18;
}
static void entry__80_16(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // object: 0
  // object_files: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* object_files */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 660: ... push &object_files object
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* object_files */;
  arguments->slots[1] = frame->slots[0] /* object */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__80_17;
}
static void cont__80_17(void) {
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
static void cont__80_18(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 661: ... : (library)
  // 662:   push
  // 663:     &library_files
  // 664:     if
  // 665:       library .has_prefix. "sim-"
  // 666:       ->
  // 667:         case
  // 668:           operating_system()
  // 669:           "linux", "bsd" -> "-l:lib@(library).so.@(MAJOR)"
  // 670:           -> "-l@(library)-@(MAJOR)"
  // ...
  frame->slots[4] /* temp__1 */ = create_closure(entry__80_19, 1);
  // 661: for_each libraries: (library)
  // 662:   push
  // 663:     &library_files
  // 664:     if
  // 665:       library .has_prefix. "sim-"
  // 666:       ->
  // 667:         case
  // 668:           operating_system()
  // 669:           "linux", "bsd" -> "-l:lib@(library).so.@(MAJOR)"
  // 670:           -> "-l@(library)-@(MAJOR)"
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__libraries();
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__80_45;
}
static void entry__80_19(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // library: 0
  // library_files: 1
  frame->slots[1] = myself->closure.frame->slots[2]; /* library_files */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 665: library .has_prefix. "sim-"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* library */;
  arguments->slots[1] = string__75_32;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__80_20;
}
static void cont__80_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 666: ->
  // 667:   case
  // 668:     operating_system()
  // 669:     "linux", "bsd" -> "-l:lib@(library).so.@(MAJOR)"
  // 670:     -> "-l@(library)-@(MAJOR)"
  frame->slots[4] /* temp__3 */ = create_closure(entry__80_21, 0);
  // 671: ->
  // 672:   if
  // 673:     library .contains. '.'
  // 674:     -> "-l:lib@(library .before. '.').so.@(library .behind. '.')"
  // 675:       # Linux only
  // 676:     -> "-l@(library)"
  frame->slots[5] /* temp__4 */ = create_closure(entry__80_34, 0);
  // 664: if
  // 665:   library .has_prefix. "sim-"
  // 666:   ->
  // 667:     case
  // 668:       operating_system()
  // 669:       "linux", "bsd" -> "-l:lib@(library).so.@(MAJOR)"
  // 670:       -> "-l@(library)-@(MAJOR)"
  // 671:   ->
  // 672:     if
  // 673:       library .contains. '.'
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  arguments->slots[2] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__80_43;
}
static void entry__80_21(void) {
  allocate_initialized_frame_gc(1, 6);
  // slot allocations:
  // library: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* library */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 668: operating_system()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__operating_system();
  func = myself->type;
  frame->cont = cont__80_22;
}
static void cont__80_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 669: "linux", "bsd"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__80_23;
  arguments->slots[1] = string__80_24;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__80_25;
}
static void cont__80_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 669: ... -> "-l:lib@(library).so.@(MAJOR)"
  frame->slots[4] /* temp__4 */ = create_closure(entry__80_26, 0);
  // 670: -> "-l@(library)-@(MAJOR)"
  frame->slots[5] /* temp__5 */ = create_closure(entry__80_30, 0);
  // 667: case
  // 668:   operating_system()
  // 669:   "linux", "bsd" -> "-l:lib@(library).so.@(MAJOR)"
  // 670:   -> "-l@(library)-@(MAJOR)"
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  arguments->slots[2] = frame->slots[4] /* temp__4 */;
  arguments->slots[3] = frame->slots[5] /* temp__5 */;
  result_count = 1;
  myself = get__case();
  func = myself->type;
  frame->cont = cont__80_33;
}
static void entry__80_26(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // library: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* library */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 669: ... "-l:lib@(library).so.@(MAJOR)"
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__80_27;
  arguments->slots[1] = frame->slots[0] /* library */;
  arguments->slots[2] = string__80_28;
  arguments->slots[3] = var._MAJOR;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__80_29;
}
static void cont__80_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 669: ... -> "-l:lib@(library).so.@(MAJOR)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__80_30(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // library: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* library */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 670: ... "-l@(library)-@(MAJOR)"
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__80_31;
  arguments->slots[1] = frame->slots[0] /* library */;
  arguments->slots[2] = string__70_46;
  arguments->slots[3] = var._MAJOR;
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
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 670: -> "-l@(library)-@(MAJOR)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__80_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 666: ->
  // 667:   case
  // 668:     operating_system()
  // 669:     "linux", "bsd" -> "-l:lib@(library).so.@(MAJOR)"
  // 670:     -> "-l@(library)-@(MAJOR)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__80_34(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // library: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* library */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 673: library .contains. '.'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* library */;
  arguments->slots[1] = character__46;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__80_35;
}
static void cont__80_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 674: -> "-l:lib@(library .before. '.').so.@(library .behind. '.')"
  // 675:   # Linux only
  frame->slots[3] /* temp__3 */ = create_closure(entry__80_36, 0);
  // 676: -> "-l@(library)"
  frame->slots[4] /* temp__4 */ = create_closure(entry__80_40, 0);
  // 672: if
  // 673:   library .contains. '.'
  // 674:   -> "-l:lib@(library .before. '.').so.@(library .behind. '.')"
  // 675:     # Linux only
  // 676:   -> "-l@(library)"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  arguments->slots[2] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__80_42;
}
static void entry__80_36(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // library: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* library */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 674: ... library .before. '.'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* library */;
  arguments->slots[1] = character__46;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__80_37;
}
static void cont__80_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 674: ... library .behind. '.'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* library */;
  arguments->slots[1] = character__46;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__80_38;
}
static void cont__80_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 674: ... "-l:lib@(library .before. '.').so.@(library .behind. '.')"
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__80_27;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  arguments->slots[2] = string__80_28;
  arguments->slots[3] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__80_39;
}
static void cont__80_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 674: -> "-l:lib@(library .before. '.').so.@(library .behind. '.')"
  // 675:   # Linux only
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__80_40(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // library: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* library */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 676: ... "-l@(library)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__80_31;
  arguments->slots[1] = frame->slots[0] /* library */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__80_41;
}
static void cont__80_41(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 676: -> "-l@(library)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__80_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 671: ->
  // 672:   if
  // 673:     library .contains. '.'
  // 674:     -> "-l:lib@(library .before. '.').so.@(library .behind. '.')"
  // 675:       # Linux only
  // 676:     -> "-l@(library)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__80_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 662: push
  // 663:   &library_files
  // 664:   if
  // 665:     library .has_prefix. "sim-"
  // 666:     ->
  // 667:       case
  // 668:         operating_system()
  // 669:         "linux", "bsd" -> "-l:lib@(library).so.@(MAJOR)"
  // 670:         -> "-l@(library)-@(MAJOR)"
  // 671:     ->
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* library_files */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__80_44;
}
static void cont__80_44(void) {
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
static void cont__80_45(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 677: ... append(object_files library_files)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* object_files */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* library_files */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__80_46;
}
static void cont__80_46(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 677: append library_paths append(object_files library_files)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* library_paths */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__append();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__81_74(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 720: ... write_timing_info "collecting imports"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__81_75;
  result_count = frame->caller_result_count;
  myself = get__write_timing_info();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__81_1_create_imports(void) {
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
  // 682: ... : (buf)
  // 683:   $$s undefined
  // 684:   for_each buf: (idx chr)
  // 685:     if
  // 686:       s.is_defined:
  // 687:         unless chr.is_a_letter || chr == '_' || chr.is_a_digit:
  // 688:           $symbol range(buf s idx-1)
  // 689:           !s undefined
  // 690:           unless already_checked(symbol):
  // 691:             !already_checked(symbol) true
  // ...
  frame->slots[5] /* temp__1 */ = create_closure(entry__81_2_collect_declarations, 1);
  // 682: $collect_declarations: (buf)
  // 683:   $$s undefined
  // 684:   for_each buf: (idx chr)
  // 685:     if
  // 686:       s.is_defined:
  // 687:         unless chr.is_a_letter || chr == '_' || chr.is_a_digit:
  // 688:           $symbol range(buf s idx-1)
  // 689:           !s undefined
  // 690:           unless already_checked(symbol):
  // 691:             !already_checked(symbol) true
  // ...
  initialize_future(frame->slots[2] /* collect_declarations */, frame->slots[5] /* temp__1 */);
  // 680: $$already_checked empty_set
  ((CELL *)frame->slots[1])->contents /* already_checked */ = get__empty_set();
  // 715: ... : collect_declarations source
  frame->slots[5] /* temp__1 */ = create_closure(entry__81_63, 0);
  // 715: collect_output $imports: collect_declarations source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__81_64;
}
static void entry__81_62(void) {
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
  // 713: ... !s idx
  ((CELL *)frame->slots[0])->contents /* s */ = frame->slots[1] /* idx */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__81_21(void) {
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
  // 696: declaration(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* declaration */;
  func = myself->type;
  frame->cont = cont__81_22;
}
static void cont__81_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 696: declaration(1) != '#'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  arguments->slots[1] = character__35;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__81_23;
}
static void cont__81_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 696: declaration(1) != '#'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__81_24;
}
static void cont__81_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  frame->slots[6] /* temp__4 */ = create_closure(entry__81_25, 0);
  // 694: $do_import
  // 695:   &&
  // 696:     declaration(1) != '#'
  // 697:     not(declaration .has_prefix. "typedef")
  // 698:     not(declaration .has_prefix. "REGISTER")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__81_34;
}
static void entry__81_25(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // declaration: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* declaration */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 697: ... declaration .has_prefix. "typedef"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* declaration */;
  arguments->slots[1] = string__81_26;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__81_27;
}
static void cont__81_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 697: not(declaration .has_prefix. "typedef")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__not();
  func = myself->type;
  frame->cont = cont__81_28;
}
static void cont__81_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 698: not(declaration .has_prefix. "REGISTER")
  frame->slots[4] /* temp__4 */ = create_closure(entry__81_29, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__81_33;
}
static void entry__81_29(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // declaration: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* declaration */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 698: ... declaration .has_prefix. "REGISTER"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* declaration */;
  arguments->slots[1] = string__81_30;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__81_31;
}
static void cont__81_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 698: not(declaration .has_prefix. "REGISTER")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__not();
  func = myself->type;
  frame->cont = cont__81_32;
}
static void cont__81_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 698: not(declaration .has_prefix. "REGISTER")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__81_33(void) {
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
static void cont__81_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* do_import */, arguments->slots[0]);
  // 701: ->
  // 702:   declaration(1) == '#' || declaration .has_prefix. "REGISTER"
  // 703:   :
  // 704:     collect_declarations declaration .truncate_from. '{'
  frame->slots[3] /* temp__1 */ = create_closure(entry__81_35, 0);
  // 705: -> declaration .has_prefix. "typedef struct":
  // 706:   for_each_line between(declaration '{' '}').trim: (line)
  // 707:     collect_declarations until(line ' ' -1)
  frame->slots[4] /* temp__2 */ = create_closure(entry__81_43, 0);
  // 708: :
  // 709:   collect_declarations declaration
  frame->slots[5] /* temp__3 */ = create_closure(entry__81_52, 0);
  // 700: cond
  // 701:   ->
  // 702:     declaration(1) == '#' || declaration .has_prefix. "REGISTER"
  // 703:     :
  // 704:       collect_declarations declaration .truncate_from. '{'
  // 705:   -> declaration .has_prefix. "typedef struct":
  // 706:     for_each_line between(declaration '{' '}').trim: (line)
  // 707:       collect_declarations until(line ' ' -1)
  // 708:   :
  // 709:     collect_declarations declaration
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = frame->slots[5] /* temp__3 */;
  result_count = 0;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__81_53;
}
static void entry__81_49(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // line: 0
  // collect_declarations: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* collect_declarations */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 707: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__81_50;
}
static void cont__81_50(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 707: ... until(line ' ' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* line */;
  arguments->slots[1] = character__32;
  arguments->slots[2] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__until();
  func = myself->type;
  frame->cont = cont__81_51;
}
static void cont__81_51(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 707: collect_declarations until(line ' ' -1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* collect_declarations */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__81_46(void) {
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
  // 706: ... between(declaration '{' '}')
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* declaration */;
  arguments->slots[1] = character__123;
  arguments->slots[2] = character__125;
  result_count = 1;
  myself = get__between();
  func = myself->type;
  frame->cont = cont__81_47;
}
static void cont__81_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 706: ... between(declaration '{' '}').trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__81_48;
}
static void cont__81_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 706: ... : (line)
  // 707:   collect_declarations until(line ' ' -1)
  frame->slots[4] /* temp__3 */ = create_closure(entry__81_49, 1);
  // 706: for_each_line between(declaration '{' '}').trim: (line)
  // 707:   collect_declarations until(line ' ' -1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__for_each_line();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__81_41(void) {
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
  // 704: ... declaration .truncate_from. '{'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* declaration */;
  arguments->slots[1] = character__123;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__81_42;
}
static void cont__81_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 704: collect_declarations declaration .truncate_from. '{'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* collect_declarations */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__81_35(void) {
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
  // 702: declaration(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* declaration */;
  func = myself->type;
  frame->cont = cont__81_36;
}
static void cont__81_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 702: declaration(1) == '#'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  arguments->slots[1] = character__35;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__81_37;
}
static void cont__81_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 702: ... declaration .has_prefix. "REGISTER"
  frame->slots[5] /* temp__4 */ = create_closure(entry__81_38, 0);
  // 702: declaration(1) == '#' || declaration .has_prefix. "REGISTER"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__81_40;
}
static void entry__81_38(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // declaration: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* declaration */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 702: ... declaration .has_prefix. "REGISTER"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* declaration */;
  arguments->slots[1] = string__81_30;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__81_39;
}
static void cont__81_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 702: ... declaration .has_prefix. "REGISTER"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__81_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 703: :
  // 704:   collect_declarations declaration .truncate_from. '{'
  frame->slots[6] /* temp__5 */ = create_closure(entry__81_41, 0);
  // 701: ->
  // 702:   declaration(1) == '#' || declaration .has_prefix. "REGISTER"
  // 703:   :
  // 704:     collect_declarations declaration .truncate_from. '{'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__5 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__81_43(void) {
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
  // 705: ... declaration .has_prefix. "typedef struct"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* declaration */;
  arguments->slots[1] = string__81_44;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__81_45;
}
static void cont__81_45(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 705: ... :
  // 706:   for_each_line between(declaration '{' '}').trim: (line)
  // 707:     collect_declarations until(line ' ' -1)
  frame->slots[3] /* temp__2 */ = create_closure(entry__81_46, 0);
  // 705: -> declaration .has_prefix. "typedef struct":
  // 706:   for_each_line between(declaration '{' '}').trim: (line)
  // 707:     collect_declarations until(line ' ' -1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__81_52(void) {
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
  // 709: collect_declarations declaration
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* declaration */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* collect_declarations */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__81_53(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 710: if do_import: write "IMPORT "
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* do_import */;
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
  // 710: ... write "IMPORT "
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__81_55;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__81_56(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 711: write declaration
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* declaration */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__81_17(void) {
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
  // 691: !already_checked(symbol) true
  frame->slots[4] /* temp__1 */ = get__true();
  // 691: !already_checked(symbol)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* symbol */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* already_checked */;
  func = myself->type;
  frame->cont = cont__81_18;
}
static void cont__81_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* already_checked */ = arguments->slots[0];
  // 692: $declaration runtime_symbols(symbol)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* symbol */;
  result_count = 1;
  myself = get__runtime_symbols();
  func = myself->type;
  frame->cont = cont__81_19;
}
static void cont__81_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* declaration */, arguments->slots[0]);
  // 693: ... declaration.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* declaration */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__81_20;
}
static void cont__81_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 693: ... :
  // 694:   $do_import
  // 695:     &&
  // 696:       declaration(1) != '#'
  // 697:       not(declaration .has_prefix. "typedef")
  // 698:       not(declaration .has_prefix. "REGISTER")
  // 699:   
  // 700:   cond
  // 701:     ->
  // 702:       declaration(1) == '#' || declaration .has_prefix. "REGISTER"
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__81_21, 0);
  // 693: if declaration.is_defined:
  // 694:   $do_import
  // 695:     &&
  // 696:       declaration(1) != '#'
  // 697:       not(declaration .has_prefix. "typedef")
  // 698:       not(declaration .has_prefix. "REGISTER")
  // 699:   
  // 700:   cond
  // 701:     ->
  // 702:       declaration(1) == '#' || declaration .has_prefix. "REGISTER"
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
static void entry__81_13(void) {
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
  // 688: ... idx-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* idx */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__81_14;
}
static void cont__81_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 688: $symbol range(buf s idx-1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* buf */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* s */;
  arguments->slots[2] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__81_15;
}
static void cont__81_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* symbol */, arguments->slots[0]);
  // 689: !s undefined
  ((CELL *)frame->slots[1])->contents /* s */ = get__undefined();
  // 690: ... already_checked(symbol)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* symbol */;
  result_count = 1;
  myself = ((CELL *)frame->slots[3])->contents /* already_checked */;
  func = myself->type;
  frame->cont = cont__81_16;
}
static void cont__81_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 690: ... :
  // 691:   !already_checked(symbol) true
  // 692:   $declaration runtime_symbols(symbol)
  // 693:   if declaration.is_defined:
  // 694:     $do_import
  // 695:       &&
  // 696:         declaration(1) != '#'
  // 697:         not(declaration .has_prefix. "typedef")
  // 698:         not(declaration .has_prefix. "REGISTER")
  // 699:     
  // ...
  frame->slots[7] /* temp__2 */ = create_closure(entry__81_17, 0);
  // 690: unless already_checked(symbol):
  // 691:   !already_checked(symbol) true
  // 692:   $declaration runtime_symbols(symbol)
  // 693:   if declaration.is_defined:
  // 694:     $do_import
  // 695:       &&
  // 696:         declaration(1) != '#'
  // 697:         not(declaration .has_prefix. "typedef")
  // 698:         not(declaration .has_prefix. "REGISTER")
  // 699:     
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
static void entry__81_5(void) {
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
  // 687: ... chr.is_a_letter
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  result_count = 1;
  myself = get__is_a_letter();
  func = myself->type;
  frame->cont = cont__81_6;
}
static void cont__81_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 687: ... chr == '_' || chr.is_a_digit
  frame->slots[8] /* temp__3 */ = create_closure(entry__81_7, 0);
  // 687: ... chr.is_a_letter || chr == '_' || chr.is_a_digit
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  arguments->slots[1] = frame->slots[8] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__81_12;
}
static void entry__81_7(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 687: ... chr == '_'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__95;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__81_8;
}
static void cont__81_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 687: ... chr.is_a_digit
  frame->slots[3] /* temp__3 */ = create_closure(entry__81_9, 0);
  // 687: ... chr == '_' || chr.is_a_digit
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__81_11;
}
static void entry__81_9(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 687: ... chr.is_a_digit
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  result_count = 1;
  myself = get__is_a_digit();
  func = myself->type;
  frame->cont = cont__81_10;
}
static void cont__81_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 687: ... chr.is_a_digit
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__81_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 687: ... chr == '_' || chr.is_a_digit
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__81_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 687: ... :
  // 688:   $symbol range(buf s idx-1)
  // 689:   !s undefined
  // 690:   unless already_checked(symbol):
  // 691:     !already_checked(symbol) true
  // 692:     $declaration runtime_symbols(symbol)
  // 693:     if declaration.is_defined:
  // 694:       $do_import
  // 695:         &&
  // 696:           declaration(1) != '#'
  // ...
  frame->slots[9] /* temp__4 */ = create_closure(entry__81_13, 0);
  // 687: unless chr.is_a_letter || chr == '_' || chr.is_a_digit:
  // 688:   $symbol range(buf s idx-1)
  // 689:   !s undefined
  // 690:   unless already_checked(symbol):
  // 691:     !already_checked(symbol) true
  // 692:     $declaration runtime_symbols(symbol)
  // 693:     if declaration.is_defined:
  // 694:       $do_import
  // 695:         &&
  // 696:           declaration(1) != '#'
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
static void entry__81_57(void) {
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
  // 713: ... chr.is_a_letter
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  result_count = 1;
  myself = get__is_a_letter();
  func = myself->type;
  frame->cont = cont__81_58;
}
static void cont__81_58(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 713: ... chr == '_'
  frame->slots[5] /* temp__3 */ = create_closure(entry__81_59, 0);
  // 713: ... chr.is_a_letter || chr == '_'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__81_61;
}
static void entry__81_59(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 713: ... chr == '_'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__95;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__81_60;
}
static void cont__81_60(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 713: ... chr == '_'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__81_61(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 713: ... : !s idx
  frame->slots[6] /* temp__4 */ = create_closure(entry__81_62, 0);
  // 713: if chr.is_a_letter || chr == '_': !s idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__81_3(void) {
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
  // 686: s.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* s */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__81_4;
}
static void cont__81_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 686: ... :
  // 687:   unless chr.is_a_letter || chr == '_' || chr.is_a_digit:
  // 688:     $symbol range(buf s idx-1)
  // 689:     !s undefined
  // 690:     unless already_checked(symbol):
  // 691:       !already_checked(symbol) true
  // 692:       $declaration runtime_symbols(symbol)
  // 693:       if declaration.is_defined:
  // 694:         $do_import
  // 695:           &&
  // ...
  frame->slots[7] /* temp__2 */ = create_closure(entry__81_5, 0);
  // 712: :
  // 713:   if chr.is_a_letter || chr == '_': !s idx
  frame->slots[8] /* temp__3 */ = create_closure(entry__81_57, 0);
  // 685: if
  // 686:   s.is_defined:
  // 687:     unless chr.is_a_letter || chr == '_' || chr.is_a_digit:
  // 688:       $symbol range(buf s idx-1)
  // 689:       !s undefined
  // 690:       unless already_checked(symbol):
  // 691:         !already_checked(symbol) true
  // 692:         $declaration runtime_symbols(symbol)
  // 693:         if declaration.is_defined:
  // 694:           $do_import
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
static void entry__81_2_collect_declarations(void) {
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
  // 683: $$s undefined
  ((CELL *)frame->slots[3])->contents /* s */ = get__undefined();
  // 684: ... : (idx chr)
  // 685:   if
  // 686:     s.is_defined:
  // 687:       unless chr.is_a_letter || chr == '_' || chr.is_a_digit:
  // 688:         $symbol range(buf s idx-1)
  // 689:         !s undefined
  // 690:         unless already_checked(symbol):
  // 691:           !already_checked(symbol) true
  // 692:           $declaration runtime_symbols(symbol)
  // 693:           if declaration.is_defined:
  // ...
  frame->slots[4] /* temp__1 */ = create_closure(entry__81_3, 2);
  // 684: for_each buf: (idx chr)
  // 685:   if
  // 686:     s.is_defined:
  // 687:       unless chr.is_a_letter || chr == '_' || chr.is_a_digit:
  // 688:         $symbol range(buf s idx-1)
  // 689:         !s undefined
  // 690:         unless already_checked(symbol):
  // 691:           !already_checked(symbol) true
  // 692:           $declaration runtime_symbols(symbol)
  // 693:           if declaration.is_defined:
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
static void entry__81_63(void) {
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
  // 715: ... collect_declarations source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* source */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* collect_declarations */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__81_64(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* imports */, arguments->slots[0]);
  // 716: $first_part source .before. "// INSERT HERE //"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  arguments->slots[1] = string__81_65;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__81_66;
}
static void cont__81_66(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* first_part */, arguments->slots[0]);
  // 717: write first_part
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* first_part */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__81_67;
}
static void cont__81_67(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 718: write imports
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* imports */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__81_68;
}
static void cont__81_68(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 719: ... length_of(first_part)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* first_part */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__81_69;
}
static void cont__81_69(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__3 */ = arguments->slots[0];
  // 719: ... length_of(first_part)+18
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__3 */;
  arguments->slots[1] = number__18;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__81_70;
}
static void cont__81_70(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 719: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__81_71;
}
static void cont__81_71(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__4 */ = arguments->slots[0];
  // 719: ... range(source length_of(first_part)+18 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  arguments->slots[2] = frame->slots[8] /* temp__4 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__81_72;
}
static void cont__81_72(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 719: write range(source length_of(first_part)+18 -1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__81_73;
}
static void cont__81_73(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 720: if do_time_passes: write_timing_info "collecting imports"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = func__81_74;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__82_1_compile_exe(void) {
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
  // 723: ... main_info.is_a_directory
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_info();
  result_count = 1;
  myself = get__is_a_directory();
  func = myself->type;
  frame->cont = cont__82_2;
}
static void cont__82_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 723: if main_info.is_a_directory: Error "Expected a source code file!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = func__82_3;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__82_5;
}
static void entry__82_3(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 723: ... Error "Expected a source code file!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__82_4;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__82_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 724: ... main_filename .has_suffix. ".sim"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  arguments->slots[1] = string__70_13;
  result_count = 1;
  myself = get__has_suffix();
  func = myself->type;
  frame->cont = cont__82_6;
}
static void cont__82_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 724: unless main_filename .has_suffix. ".sim":
  // 725:   Error "
  // 726:     Expected ".sim" file extension in source filename!@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = func__82_7;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__82_9;
}
static void entry__82_7(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 725: Error "
  // 726:   Expected ".sim" file extension in source filename!@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__82_8;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__82_9(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 728: $mod_filename main_filename .without_suffix. ".sim"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  arguments->slots[1] = string__70_13;
  result_count = 1;
  myself = get__without_suffix();
  func = myself->type;
  frame->cont = cont__82_10;
}
static void cont__82_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* mod_filename */, arguments->slots[0]);
  // 729: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__82_11;
}
static void cont__82_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 729: $mod_name truncate_until(mod_filename '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* mod_filename */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__82_12;
}
static void cont__82_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* mod_name */, arguments->slots[0]);
  // 730: body mod_filename mod_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* mod_filename */;
  arguments->slots[1] = frame->slots[3] /* mod_name */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame->cont = cont__82_13;
}
static void cont__82_13(void) {
  myself = frame->slots[1] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__83_2(void) {
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
  // 734: %sim2c::module_name mod_name
  initialize_maybe_future(get__sim2c__module_name(), frame->slots[1] /* mod_name */);
  // 735: ... list(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__83_3;
}
static void cont__83_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 735: sim2c list(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__sim2c();
  func = myself->type;
  frame->cont = cont__83_4;
}
static void cont__83_4(void) {
  myself = frame->slots[2] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__83_1_dump_source_or_check(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 733: compile_exe: (_mod_filename mod_name)
  // 734:   %sim2c::module_name mod_name
  // 735:   sim2c list(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__83_2;
  result_count = frame->caller_result_count;
  myself = var._compile_exe;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__84_18(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 745: ... write_timing_info "writing C-source"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__84_19;
  result_count = frame->caller_result_count;
  myself = get__write_timing_info();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__84_2(void) {
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
  // 739: ... module_prefix.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._module_prefix;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__84_3;
}
static void cont__84_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 739: ... : append string(module_prefix '/') &mod_name
  frame->slots[5] /* temp__2 */ = create_closure(entry__84_4, 0);
  // 739: if module_prefix.is_defined: append string(module_prefix '/') &mod_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__84_7;
}
static void entry__84_4(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // mod_name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* mod_name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 739: ... string(module_prefix '/')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._module_prefix;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__84_5;
}
static void cont__84_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 739: ... append string(module_prefix '/') &mod_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* mod_name */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__84_6;
}
static void cont__84_6(void) {
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
static void cont__84_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 740: ... :
  // 741:   %sim2c::module_name replace_all(mod_name '/' = "__" '.' = "__")
  // 742:   sim2c list(main_filename)
  frame->slots[4] /* temp__1 */ = create_closure(entry__84_8, 0);
  // 740: collect_output $c_source:
  // 741:   %sim2c::module_name replace_all(mod_name '/' = "__" '.' = "__")
  // 742:   sim2c list(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__84_14;
}
static void entry__84_8(void) {
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
  // 741: ... '/' = "__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = string__76_43;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__84_9;
}
static void cont__84_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 741: ... '.' = "__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__46;
  arguments->slots[1] = string__76_43;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__84_10;
}
static void cont__84_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 741: %sim2c::module_name replace_all(mod_name '/' = "__" '.' = "__")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* mod_name */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  arguments->slots[2] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__84_11;
}
static void cont__84_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(get__sim2c__module_name(), arguments->slots[0]);
  // 742: ... list(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__84_12;
}
static void cont__84_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 742: sim2c list(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__sim2c();
  func = myself->type;
  frame->cont = cont__84_13;
}
static void cont__84_13(void) {
  myself = frame->slots[0] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__84_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* c_source */, arguments->slots[0]);
  // 743: ... : create_imports c_source
  frame->slots[4] /* temp__1 */ = create_closure(entry__84_15, 0);
  // 743: collect_output $c_buf: create_imports c_source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__84_16;
}
static void entry__84_15(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // c_source: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* c_source */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 743: ... create_imports c_source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_source */;
  result_count = frame->caller_result_count;
  myself = var._create_imports;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__84_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* c_buf */, arguments->slots[0]);
  // 744: write c_buf
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* c_buf */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__84_17;
}
static void cont__84_17(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 745: if do_time_passes: write_timing_info "writing C-source"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = func__84_18;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__84_1_print_c(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 738: compile_exe: (_mod_filename $mod_name)
  // 739:   if module_prefix.is_defined: append string(module_prefix '/') &mod_name
  // 740:   collect_output $c_source:
  // 741:     %sim2c::module_name replace_all(mod_name '/' = "__" '.' = "__")
  // 742:     sim2c list(main_filename)
  // 743:   collect_output $c_buf: create_imports c_source
  // 744:   write c_buf
  // 745:   if do_time_passes: write_timing_info "writing C-source"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__84_2;
  result_count = frame->caller_result_count;
  myself = var._compile_exe;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__85_35(void) {
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
  // 774: without_prefix &filename prefix_path
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* filename */;
  arguments->slots[1] = frame->slots[1] /* prefix_path */;
  result_count = 1;
  myself = get__without_prefix();
  func = myself->type;
  frame->cont = cont__85_36;
}
static void cont__85_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* filename */ = arguments->slots[0];
  // 775: without_prefix &filename '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* filename */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__without_prefix();
  func = myself->type;
  frame->cont = cont__85_37;
}
static void cont__85_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* filename */ = arguments->slots[0];
  // 776: writeln filename
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* filename */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__85_1_list_dependencies(void) {
  allocate_initialized_frame_gc(0, 2);
  // slot allocations:
  // prefix_path: 0
  frame->slots[0] /* prefix_path */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 748: !platform_specific_priority multi_dimensional_table(types::table types::table)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__types__table();
  arguments->slots[1] = get__types__table();
  result_count = 1;
  myself = get__multi_dimensional_table();
  func = myself->type;
  frame->cont = cont__85_2;
}
static void cont__85_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._platform_specific_priority = arguments->slots[0];
  // 749: for_each supported_platforms: (supported_platform _parent_platform)
  // 750:   $$platform supported_platform
  // 751:   $$priority 0
  // 752:   do: (-> break)
  // 753:     forever:
  // 754:       $plat supported_platforms(platform)
  // 755:       if plat.is_undefined break
  // 756:       inc &priority
  // 757:       !platform_specific_priority(supported_platform platform) priority
  // 758:       if plat == NONE break
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._supported_platforms;
  arguments->slots[1] = func__85_3;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__85_14;
}
static void entry__85_4(void) {
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
  // 753: ... :
  // 754:   $plat supported_platforms(platform)
  // 755:   if plat.is_undefined break
  // 756:   inc &priority
  // 757:   !platform_specific_priority(supported_platform platform) priority
  // 758:   if plat == NONE break
  // 759:   !platform plat
  frame->slots[4] /* temp__1 */ = create_closure(entry__85_5, 0);
  // 753: forever:
  // 754:   $plat supported_platforms(platform)
  // 755:   if plat.is_undefined break
  // 756:   inc &priority
  // 757:   !platform_specific_priority(supported_platform platform) priority
  // 758:   if plat == NONE break
  // 759:   !platform plat
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame->cont = cont__85_13;
}
static void entry__85_5(void) {
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
  // 754: $plat supported_platforms(platform)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* platform */;
  result_count = 1;
  myself = var._supported_platforms;
  func = myself->type;
  frame->cont = cont__85_6;
}
static void cont__85_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* plat */, arguments->slots[0]);
  // 755: ... plat.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* plat */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__85_7;
}
static void cont__85_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 755: if plat.is_undefined break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* break */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__85_8;
}
static void cont__85_8(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 756: inc &priority
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* priority */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__85_9;
}
static void cont__85_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* priority */ = arguments->slots[0];
  // 757: !platform_specific_priority(supported_platform platform) priority
  frame->slots[5] /* temp__1 */ = ((CELL *)frame->slots[2])->contents /* priority */;
  // 757: !platform_specific_priority(supported_platform platform)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* supported_platform */;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* platform */;
  arguments->slots[2] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = var._platform_specific_priority;
  func = myself->type;
  frame->cont = cont__85_10;
}
static void cont__85_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._platform_specific_priority = arguments->slots[0];
  // 758: ... plat == NONE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* plat */;
  arguments->slots[1] = var._NONE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__85_11;
}
static void cont__85_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 758: if plat == NONE break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* break */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__85_12;
}
static void cont__85_12(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 759: !platform plat
  ((CELL *)frame->slots[0])->contents /* platform */ = frame->slots[4] /* plat */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__85_13(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__85_3(void) {
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
  // 750: $$platform supported_platform
  ((CELL *)frame->slots[2])->contents /* platform */ = frame->slots[0] /* supported_platform */;
  // 751: $$priority 0
  ((CELL *)frame->slots[3])->contents /* priority */ = number__0;
  // 752: ... : (-> break)
  // 753:   forever:
  // 754:     $plat supported_platforms(platform)
  // 755:     if plat.is_undefined break
  // 756:     inc &priority
  // 757:     !platform_specific_priority(supported_platform platform) priority
  // 758:     if plat == NONE break
  // 759:     !platform plat
  frame->slots[4] /* temp__1 */ = create_closure(entry__85_4, 0);
  // 752: do: (-> break)
  // 753:   forever:
  // 754:     $plat supported_platforms(platform)
  // 755:     if plat.is_undefined break
  // 756:     inc &priority
  // 757:     !platform_specific_priority(supported_platform platform) priority
  // 758:     if plat == NONE break
  // 759:     !platform plat
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__do();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__85_14(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 761: main_info.is_a_directory
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_info();
  result_count = 1;
  myself = get__is_a_directory();
  func = myself->type;
  frame->cont = cont__85_15;
}
static void cont__85_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 760: if
  // 761:   main_info.is_a_directory:
  // 762:     %mode LIB
  // 763:     if verbose: ewriteln "list dependencies for " main_filename
  // 764:     compile_modules main_filename behind(main_filename '/' -1)
  // 765:   :
  // 766:     compile_exe: (mod_filename mod_name)
  // 767:       if verbose: ewriteln "list dependencies for " mod_filename
  // 768:       compile_module mod_filename mod_name
  // 769:     writeln "runtime/linker.c"
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__85_16;
  arguments->slots[2] = func__85_23;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__85_33;
}
static void entry__85_16(void) {
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
  // 763: if verbose: ewriteln "list dependencies for " main_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = func__85_17;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__85_19;
}
static void entry__85_17(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 763: ... ewriteln "list dependencies for " main_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__85_18;
  arguments->slots[1] = get__main_filename();
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
  // 764: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__85_20;
}
static void cont__85_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 764: ... behind(main_filename '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__85_21;
}
static void cont__85_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 764: compile_modules main_filename behind(main_filename '/' -1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = var._compile_modules;
  func = myself->type;
  frame->cont = cont__85_22;
}
static void cont__85_22(void) {
  myself = frame->slots[0] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__85_23(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 766: compile_exe: (mod_filename mod_name)
  // 767:   if verbose: ewriteln "list dependencies for " mod_filename
  // 768:   compile_module mod_filename mod_name
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__85_24;
  result_count = 0;
  myself = var._compile_exe;
  func = myself->type;
  frame->cont = cont__85_27;
}
static void entry__85_24(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // mod_filename: 0
  // mod_name: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 767: ... : ewriteln "list dependencies for " mod_filename
  frame->slots[2] /* temp__1 */ = create_closure(entry__85_25, 0);
  // 767: if verbose: ewriteln "list dependencies for " mod_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__85_26;
}
static void entry__85_25(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // mod_filename: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* mod_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 767: ... ewriteln "list dependencies for " mod_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__85_18;
  arguments->slots[1] = frame->slots[0] /* mod_filename */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__85_26(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 768: compile_module mod_filename mod_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = frame->slots[1] /* mod_name */;
  result_count = frame->caller_result_count;
  myself = var._compile_module;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__85_27(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 769: writeln "runtime/linker.c"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__85_28;
  result_count = 0;
  myself = get__writeln();
  func = myself->type;
  frame->cont = cont__85_29;
}
static void cont__85_29(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 770: writeln "runtime/memory.c"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__85_30;
  result_count = 0;
  myself = get__writeln();
  func = myself->type;
  frame->cont = cont__85_31;
}
static void cont__85_31(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 771: writeln "runtime/debugger.c"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__85_32;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__85_33(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 772: $prefix_path current_path()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__current_path();
  func = myself->type;
  frame->cont = cont__85_34;
}
static void cont__85_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[0] /* prefix_path */, arguments->slots[0]);
  // 773: ... : ($filename)
  // 774:   without_prefix &filename prefix_path
  // 775:   without_prefix &filename '/'
  // 776:   writeln filename
  frame->slots[1] /* temp__1 */ = create_closure(entry__85_35, 1);
  // 773: for_each dependencies: ($filename)
  // 774:   without_prefix &filename prefix_path
  // 775:   without_prefix &filename '/'
  // 776:   writeln filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._dependencies;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__86_2(void) {
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
  // 780: $codeblocks_path string(mod_filename ".codeblocks")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = string__86_3;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__86_4;
}
static void cont__86_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* codeblocks_path */, arguments->slots[0]);
  // 781: $info stat(codeblocks_path)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* codeblocks_path */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__86_5;
}
static void cont__86_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* info */, arguments->slots[0]);
  // 782: ... info.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* info */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__86_6;
}
static void cont__86_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 782: ... :
  // 783:   ewrite "
  // 784:     The directory "@(codeblocks_path)" already exists!
  frame->slots[11] /* temp__2 */ = create_closure(entry__86_7, 0);
  // 782: if info.is_defined:
  // 783:   ewrite "
  // 784:     The directory "@(codeblocks_path)" already exists!
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__1 */;
  arguments->slots[1] = frame->slots[11] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__86_11;
}
static void entry__86_7(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // codeblocks_path: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* codeblocks_path */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 783: ... "
  // 784:   The directory "@(codeblocks_path)" already exists!
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__86_8;
  arguments->slots[1] = frame->slots[0] /* codeblocks_path */;
  arguments->slots[2] = string__86_9;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__86_10;
}
static void cont__86_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 783: ewrite "
  // 784:   The directory "@(codeblocks_path)" already exists!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewrite();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__86_11(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 785: ... : ewriteln "build Code::Blocks project in " codeblocks_path
  frame->slots[10] /* temp__1 */ = create_closure(entry__86_12, 0);
  // 785: if verbose: ewriteln "build Code::Blocks project in " codeblocks_path
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = frame->slots[10] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__86_14;
}
static void entry__86_12(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // codeblocks_path: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* codeblocks_path */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 785: ... ewriteln "build Code::Blocks project in " codeblocks_path
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__86_13;
  arguments->slots[1] = frame->slots[0] /* codeblocks_path */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__86_14(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 786: compile_module mod_filename mod_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = frame->slots[1] /* mod_name */;
  result_count = 0;
  myself = var._compile_module;
  func = myself->type;
  frame->cont = cont__86_15;
}
static void cont__86_15(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 787: show_file_list
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._show_file_list;
  func = myself->type;
  frame->cont = cont__86_16;
}
static void cont__86_16(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 788: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__86_17;
}
static void cont__86_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__2 */ = arguments->slots[0];
  // 788: ... truncate_until(main_filename '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[11] /* temp__2 */;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__86_18;
}
static void cont__86_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 788: $basename truncate_until(main_filename '/' -1) .without_suffix. ".sim"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__1 */;
  arguments->slots[1] = string__70_13;
  result_count = 1;
  myself = get__without_suffix();
  func = myself->type;
  frame->cont = cont__86_19;
}
static void cont__86_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* basename */, arguments->slots[0]);
  // 789: $prefix_path current_path()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__current_path();
  func = myself->type;
  frame->cont = cont__86_20;
}
static void cont__86_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* prefix_path */, arguments->slots[0]);
  // 790: ... codeblocks_path .without_prefix. prefix_path
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* codeblocks_path */;
  arguments->slots[1] = frame->slots[5] /* prefix_path */;
  result_count = 1;
  myself = get__without_prefix();
  func = myself->type;
  frame->cont = cont__86_21;
}
static void cont__86_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 790: $depth count_occurrences(codeblocks_path .without_prefix. prefix_path '/')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__1 */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__count_occurrences();
  func = myself->type;
  frame->cont = cont__86_22;
}
static void cont__86_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* depth */, arguments->slots[0]);
  // 791: $path_prefix dup("../" depth)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__86_23;
  arguments->slots[1] = frame->slots[6] /* depth */;
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
  initialize_future(frame->slots[7] /* path_prefix */, arguments->slots[0]);
  // 792: $cbp_filename string(codeblocks_path "/" basename ".cbp")
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* codeblocks_path */;
  arguments->slots[1] = string__86_25;
  arguments->slots[2] = frame->slots[4] /* basename */;
  arguments->slots[3] = string__86_26;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__86_27;
}
static void cont__86_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[8] /* cbp_filename */, arguments->slots[0]);
  // 793: mkdir codeblocks_path
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* codeblocks_path */;
  result_count = 0;
  myself = var._mkdir;
  func = myself->type;
  frame->cont = cont__86_28;
}
static void cont__86_28(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 794: $$buf ""
  ((CELL *)frame->slots[9])->contents /* buf */ = empty_string;
  // 795: ... "
  // 796:   <?xml version="1.0" encoding="UTF-8" standalone="yes" ?>
  // 797:   <CodeBlocks_project_file>
  // 798:     <FileVersion major="1" minor="6" />
  // 799:     <Project>
  // 800:       <Option title="@(basename)" />
  // 801:       <Option pch_mode="2" />
  // 802:       <Option compiler=c_compiler() />
  // 803:       <Build>
  // 804:         <Target title="debug">
  // ...
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__86_29;
  arguments->slots[1] = frame->slots[4] /* basename */;
  arguments->slots[2] = string__86_30;
  arguments->slots[3] = frame->slots[4] /* basename */;
  arguments->slots[4] = string__86_31;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__86_32;
}
static void cont__86_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 795: write_to &buf "
  // 796:   <?xml version="1.0" encoding="UTF-8" standalone="yes" ?>
  // 797:   <CodeBlocks_project_file>
  // 798:     <FileVersion major="1" minor="6" />
  // 799:     <Project>
  // 800:       <Option title="@(basename)" />
  // 801:       <Option pch_mode="2" />
  // 802:       <Option compiler=c_compiler() />
  // 803:       <Build>
  // 804:         <Target title="debug">
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[9])->contents /* buf */;
  arguments->slots[1] = frame->slots[10] /* temp__1 */;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__86_33;
}
static void cont__86_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[9])->contents /* buf */ = arguments->slots[0];
  // 816: ... : (filename)
  // 817:   write_to &buf "
  // 818:     @
  // 819:           <Add library="@(filename)" />
  frame->slots[10] /* temp__1 */ = create_closure(entry__86_34, 1);
  // 816: for_each libraries: (filename)
  // 817:   write_to &buf "
  // 818:     @
  // 819:           <Add library="@(filename)" />
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__libraries();
  arguments->slots[1] = frame->slots[10] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__86_39;
}
static void entry__86_34(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // filename: 0
  // buf: 1
  frame->slots[1] = myself->closure.frame->slots[9]; /* buf */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 817: ... "
  // 818:   @
  // 819:         <Add library="@(filename)" />
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__86_35;
  arguments->slots[1] = frame->slots[0] /* filename */;
  arguments->slots[2] = string__86_36;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__86_37;
}
static void cont__86_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 817: write_to &buf "
  // 818:   @
  // 819:         <Add library="@(filename)" />
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* buf */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__86_38;
}
static void cont__86_38(void) {
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
static void cont__86_39(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 830: ... c_compiler()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__c_compiler();
  func = myself->type;
  frame->cont = cont__86_40;
}
static void cont__86_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__2 */ = arguments->slots[0];
  // 833: ... c_compiler()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__c_compiler();
  func = myself->type;
  frame->cont = cont__86_41;
}
static void cont__86_41(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__3 */ = arguments->slots[0];
  // 836: ... c_compiler()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__c_compiler();
  func = myself->type;
  frame->cont = cont__86_42;
}
static void cont__86_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__4 */ = arguments->slots[0];
  // 820: ... "
  // 821:   @
  // 822:   
  // 823:       </Linker>
  // 824:       <Compiler>
  // 825:         <Add option="-Wall" />
  // 826:       </Compiler>
  // 827:       <Unit filename="@(path_prefix)runtime/common.h" />
  // 828:       <Unit filename="@(path_prefix)runtime/linker.h" />
  // 829:       <Unit filename="@(path_prefix)runtime/memory.c">
  // ...
  argument_count = 17;
  arguments = node_p;
  arguments->slots[0] = string__86_43;
  arguments->slots[1] = frame->slots[7] /* path_prefix */;
  arguments->slots[2] = string__86_44;
  arguments->slots[3] = frame->slots[7] /* path_prefix */;
  arguments->slots[4] = string__86_45;
  arguments->slots[5] = frame->slots[7] /* path_prefix */;
  arguments->slots[6] = string__86_46;
  arguments->slots[7] = frame->slots[11] /* temp__2 */;
  arguments->slots[8] = string__86_47;
  arguments->slots[9] = frame->slots[7] /* path_prefix */;
  arguments->slots[10] = string__86_48;
  arguments->slots[11] = frame->slots[12] /* temp__3 */;
  arguments->slots[12] = string__86_47;
  arguments->slots[13] = frame->slots[7] /* path_prefix */;
  arguments->slots[14] = string__86_49;
  arguments->slots[15] = frame->slots[13] /* temp__4 */;
  arguments->slots[16] = string__86_50;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__86_51;
}
static void cont__86_51(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 820: write_to &buf "
  // 821:   @
  // 822:   
  // 823:       </Linker>
  // 824:       <Compiler>
  // 825:         <Add option="-Wall" />
  // 826:       </Compiler>
  // 827:       <Unit filename="@(path_prefix)runtime/common.h" />
  // 828:       <Unit filename="@(path_prefix)runtime/linker.h" />
  // 829:       <Unit filename="@(path_prefix)runtime/memory.c">
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[9])->contents /* buf */;
  arguments->slots[1] = frame->slots[10] /* temp__1 */;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__86_52;
}
static void cont__86_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[9])->contents /* buf */ = arguments->slots[0];
  // 838: ... : ($filename)
  // 839:   without_prefix &filename prefix_path
  // 840:   without_prefix &filename '/'
  // 841:   write_to &buf "
  // 842:     @
  // 843:     
  // 844:         <Unit filename="@(path_prefix)@(filename)">
  // 845:           <Option compilerVar="@(c_compiler())" />
  // 846:         </Unit>
  frame->slots[10] /* temp__1 */ = create_closure(entry__86_53, 1);
  // 838: for_each c_sources: ($filename)
  // 839:   without_prefix &filename prefix_path
  // 840:   without_prefix &filename '/'
  // 841:   write_to &buf "
  // 842:     @
  // 843:     
  // 844:         <Unit filename="@(path_prefix)@(filename)">
  // 845:           <Option compilerVar="@(c_compiler())" />
  // 846:         </Unit>
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._c_sources;
  arguments->slots[1] = frame->slots[10] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__86_61;
}
static void entry__86_53(void) {
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
  // 839: without_prefix &filename prefix_path
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* filename */;
  arguments->slots[1] = frame->slots[1] /* prefix_path */;
  result_count = 1;
  myself = get__without_prefix();
  func = myself->type;
  frame->cont = cont__86_54;
}
static void cont__86_54(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* filename */ = arguments->slots[0];
  // 840: without_prefix &filename '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* filename */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__without_prefix();
  func = myself->type;
  frame->cont = cont__86_55;
}
static void cont__86_55(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* filename */ = arguments->slots[0];
  // 845: ... c_compiler()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__c_compiler();
  func = myself->type;
  frame->cont = cont__86_56;
}
static void cont__86_56(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 841: ... "
  // 842:   @
  // 843:   
  // 844:       <Unit filename="@(path_prefix)@(filename)">
  // 845:         <Option compilerVar="@(c_compiler())" />
  // 846:       </Unit>
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = string__86_57;
  arguments->slots[1] = frame->slots[3] /* path_prefix */;
  arguments->slots[2] = ((CELL *)frame->slots[0])->contents /* filename */;
  arguments->slots[3] = string__86_58;
  arguments->slots[4] = frame->slots[5] /* temp__2 */;
  arguments->slots[5] = string__86_50;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__86_59;
}
static void cont__86_59(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 841: write_to &buf "
  // 842:   @
  // 843:   
  // 844:       <Unit filename="@(path_prefix)@(filename)">
  // 845:         <Option compilerVar="@(c_compiler())" />
  // 846:       </Unit>
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* buf */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__86_60;
}
static void cont__86_60(void) {
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
static void cont__86_61(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 847: write_to &buf "
  // 848:       <Extensions>
  // 849:         <code_completion />
  // 850:         <debugger />
  // 851:       </Extensions>
  // 852:     </Project>
  // 853:   </CodeBlocks_project_file>
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[9])->contents /* buf */;
  arguments->slots[1] = string__86_62;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__86_63;
}
static void cont__86_63(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[9])->contents /* buf */ = arguments->slots[0];
  // 854: save cbp_filename buf
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* cbp_filename */;
  arguments->slots[1] = ((CELL *)frame->slots[9])->contents /* buf */;
  result_count = frame->caller_result_count;
  myself = get__save();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__86_1_build_codeblocks_project(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 779: compile_exe: (mod_filename mod_name)
  // 780:   $codeblocks_path string(mod_filename ".codeblocks")
  // 781:   $info stat(codeblocks_path)
  // 782:   if info.is_defined:
  // 783:     ewrite "
  // 784:       The directory "@(codeblocks_path)" already exists!
  // 785:   if verbose: ewriteln "build Code::Blocks project in " codeblocks_path
  // 786:   compile_module mod_filename mod_name
  // 787:   show_file_list
  // 788:   $basename truncate_until(main_filename '/' -1) .without_suffix. ".sim"
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__86_2;
  result_count = frame->caller_result_count;
  myself = var._compile_exe;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__87_1_build_library(void) {
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
  // 857: ... action == "simrun"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._action;
  arguments->slots[1] = string__87_2;
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
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 857: if action == "simrun": Error "Cannot run a directory!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__87_4;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__87_6;
}
static void entry__87_4(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 857: ... Error "Cannot run a directory!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__87_5;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__87_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 859: if
  // 860:   do_extract_documentation:
  // 861:     extract_documentation main_filename
  // 862:   :
  // 863:     $$version ""
  // 864:     $version_filename string(main_filename "/VERSION")
  // 865:     if file_exists(version_filename):
  // 866:       !version string('-' load(version_filename).trim)
  // 867:     $so_version version .truncate_from. '.'
  // 868:     $base_filename truncate_until(main_filename '/' -1)
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__do_extract_documentation();
  arguments->slots[1] = func__87_7;
  arguments->slots[2] = func__87_8;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__87_90;
}
static void entry__87_88(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // err: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* err */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 931: ... err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* err */;
  result_count = 1;
  myself = get__from_utf8();
  func = myself->type;
  frame->cont = cont__87_89;
}
static void cont__87_89(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 931: ... Error err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__87_83(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // err: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* err */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 923: ... err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* err */;
  result_count = 1;
  myself = get__from_utf8();
  func = myself->type;
  frame->cont = cont__87_84;
}
static void cont__87_84(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 923: ... Error err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__87_74(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // err: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* err */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 912: ... err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* err */;
  result_count = 1;
  myself = get__from_utf8();
  func = myself->type;
  frame->cont = cont__87_75;
}
static void cont__87_75(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 912: ... Error err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__87_67(void) {
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
  frame->cont = cont__87_68;
}
static void cont__87_68(void) {
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
static void entry__87_61(void) {
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
  // 899: "-Wl,-soname,libsim-@(base_filename)@(so_version).so.@(MAJOR)"
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__87_62;
  arguments->slots[1] = frame->slots[0] /* base_filename */;
  arguments->slots[2] = frame->slots[1] /* so_version */;
  arguments->slots[3] = string__80_28;
  arguments->slots[4] = var._MAJOR;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__87_63;
}
static void cont__87_63(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 900: library_paths_and_file_list()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = var._library_paths_and_file_list;
  func = myself->type;
  frame->cont = cont__87_64;
}
static void cont__87_64(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 896: CC $_out $err $success
  // 897:   ld_options*
  // 898:   "-shared"
  // 899:   "-Wl,-soname,libsim-@(base_filename)@(so_version).so.@(MAJOR)"
  // 900:   library_paths_and_file_list()*
  // 901:   "-o"
  // 902:   lib_filename
  argument_count = 0;
  arguments = node_p;
  unfold(var._ld_options);
  arguments->slots[argument_count++] = string__87_65;
  arguments->slots[argument_count++] = frame->slots[6] /* temp__1 */;
  unfold(frame->slots[7] /* temp__2 */);
  arguments->slots[argument_count++] = string__73_6;
  arguments->slots[argument_count++] = frame->slots[2] /* lib_filename */;
  result_count = 3;
  myself = var._CC;
  func = myself->type;
  frame->cont = cont__87_66;
}
static void cont__87_66(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__3 */ = arguments->slots[0];
  frame->slots[9] /* temp__4 */ = arguments->slots[1];
  frame->slots[10] /* temp__5 */ = arguments->slots[2];
  // 896: ... _out
  initialize_future(frame->slots[3] /* out */, frame->slots[8] /* temp__3 */);
  // 896: ... err
  initialize_future(frame->slots[4] /* err */, frame->slots[9] /* temp__4 */);
  // 896: ... success
  initialize_future(frame->slots[5] /* success */, frame->slots[10] /* temp__5 */);
  // 903: ... : Error err.from_utf8
  frame->slots[6] /* temp__1 */ = create_closure(entry__87_67, 0);
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
static void entry__87_69(void) {
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
  // 908: library_paths_and_file_list()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = var._library_paths_and_file_list;
  func = myself->type;
  frame->cont = cont__87_70;
}
static void cont__87_70(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 909: "-lsim-@(MAJOR)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__87_71;
  arguments->slots[1] = var._MAJOR;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__87_72;
}
static void cont__87_72(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 905: CC $_out $err $success
  // 906:   ld_options*
  // 907:   "-shared"
  // 908:   library_paths_and_file_list()*
  // 909:   "-lsim-@(MAJOR)"
  // 910:   "-o"
  // 911:   lib_filename
  argument_count = 0;
  arguments = node_p;
  unfold(var._ld_options);
  arguments->slots[argument_count++] = string__87_65;
  unfold(frame->slots[4] /* temp__1 */);
  arguments->slots[argument_count++] = frame->slots[5] /* temp__2 */;
  arguments->slots[argument_count++] = string__73_6;
  arguments->slots[argument_count++] = frame->slots[0] /* lib_filename */;
  result_count = 3;
  myself = var._CC;
  func = myself->type;
  frame->cont = cont__87_73;
}
static void cont__87_73(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  frame->slots[7] /* temp__4 */ = arguments->slots[1];
  frame->slots[8] /* temp__5 */ = arguments->slots[2];
  // 905: ... _out
  initialize_future(frame->slots[1] /* out */, frame->slots[6] /* temp__3 */);
  // 905: ... err
  initialize_future(frame->slots[2] /* err */, frame->slots[7] /* temp__4 */);
  // 905: ... success
  initialize_future(frame->slots[3] /* success */, frame->slots[8] /* temp__5 */);
  // 912: ... : Error err.from_utf8
  frame->slots[4] /* temp__1 */ = create_closure(entry__87_74, 0);
  // 912: unless success: Error err.from_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* success */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__87_76(void) {
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
  // 917: "
  // 918:   -Wl,-install_name,libsim-@(base_filename)@(so_version)-@(MAJOR).dylib@
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = string__87_77;
  arguments->slots[1] = frame->slots[0] /* base_filename */;
  arguments->slots[2] = frame->slots[1] /* so_version */;
  arguments->slots[3] = string__70_46;
  arguments->slots[4] = var._MAJOR;
  arguments->slots[5] = string__87_31;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__87_78;
}
static void cont__87_78(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 919: library_paths_and_file_list()
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
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 920: "-lsim-@(MAJOR)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__87_71;
  arguments->slots[1] = var._MAJOR;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__87_80;
}
static void cont__87_80(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__3 */ = arguments->slots[0];
  // 914: CC $_out $err $success
  // 915:   ld_options*
  // 916:   "-dynamiclib"
  // 917:   "
  // 918:     -Wl,-install_name,libsim-@(base_filename)@(so_version)-@(MAJOR).dylib@
  // 919:   library_paths_and_file_list()*
  // 920:   "-lsim-@(MAJOR)"
  // 921:   "-o"
  // 922:   lib_filename
  argument_count = 0;
  arguments = node_p;
  unfold(var._ld_options);
  arguments->slots[argument_count++] = string__87_81;
  arguments->slots[argument_count++] = frame->slots[6] /* temp__1 */;
  unfold(frame->slots[7] /* temp__2 */);
  arguments->slots[argument_count++] = frame->slots[8] /* temp__3 */;
  arguments->slots[argument_count++] = string__73_6;
  arguments->slots[argument_count++] = frame->slots[2] /* lib_filename */;
  result_count = 3;
  myself = var._CC;
  func = myself->type;
  frame->cont = cont__87_82;
}
static void cont__87_82(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__4 */ = arguments->slots[0];
  frame->slots[10] /* temp__5 */ = arguments->slots[1];
  frame->slots[11] /* temp__6 */ = arguments->slots[2];
  // 914: ... _out
  initialize_future(frame->slots[3] /* out */, frame->slots[9] /* temp__4 */);
  // 914: ... err
  initialize_future(frame->slots[4] /* err */, frame->slots[10] /* temp__5 */);
  // 914: ... success
  initialize_future(frame->slots[5] /* success */, frame->slots[11] /* temp__6 */);
  // 923: ... : Error err.from_utf8
  frame->slots[6] /* temp__1 */ = create_closure(entry__87_83, 0);
  // 923: unless success: Error err.from_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* success */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__87_85(void) {
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
  // 928: library_paths_and_file_list()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = var._library_paths_and_file_list;
  func = myself->type;
  frame->cont = cont__87_86;
}
static void cont__87_86(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 925: CC $_out $err $success
  // 926:   ld_options*
  // 927:   "-shared"
  // 928:   library_paths_and_file_list()*
  // 929:   "-o"
  // 930:   lib_filename
  argument_count = 0;
  arguments = node_p;
  unfold(var._ld_options);
  arguments->slots[argument_count++] = string__87_65;
  unfold(frame->slots[4] /* temp__1 */);
  arguments->slots[argument_count++] = string__73_6;
  arguments->slots[argument_count++] = frame->slots[0] /* lib_filename */;
  result_count = 3;
  myself = var._CC;
  func = myself->type;
  frame->cont = cont__87_87;
}
static void cont__87_87(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  frame->slots[6] /* temp__3 */ = arguments->slots[1];
  frame->slots[7] /* temp__4 */ = arguments->slots[2];
  // 925: ... _out
  initialize_future(frame->slots[1] /* out */, frame->slots[5] /* temp__2 */);
  // 925: ... err
  initialize_future(frame->slots[2] /* err */, frame->slots[6] /* temp__3 */);
  // 925: ... success
  initialize_future(frame->slots[3] /* success */, frame->slots[7] /* temp__4 */);
  // 931: ... : Error err.from_utf8
  frame->slots[4] /* temp__1 */ = create_closure(entry__87_88, 0);
  // 931: unless success: Error err.from_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* success */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__87_55(void) {
  allocate_initialized_frame_gc(3, 9);
  // slot allocations:
  // base_filename: 0
  // so_version: 1
  // lib_filename: 2
  frame->slots[0] = myself->closure.frame->slots[3]; /* base_filename */
  frame->slots[1] = myself->closure.frame->slots[2]; /* so_version */
  frame->slots[2] = myself->closure.frame->slots[4]; /* lib_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 892: if verbose: ewriteln "linking dynamic library"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = func__87_56;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__87_58;
}
static void entry__87_56(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 892: ... ewriteln "linking dynamic library"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__87_57;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__87_58(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 894: operating_system()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__operating_system();
  func = myself->type;
  frame->cont = cont__87_59;
}
static void cont__87_59(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 895: "linux", "bsd"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__80_23;
  arguments->slots[1] = string__80_24;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__87_60;
}
static void cont__87_60(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 895: ... :
  // 896:   CC $_out $err $success
  // 897:     ld_options*
  // 898:     "-shared"
  // 899:     "-Wl,-soname,libsim-@(base_filename)@(so_version).so.@(MAJOR)"
  // 900:     library_paths_and_file_list()*
  // 901:     "-o"
  // 902:     lib_filename
  // 903:   unless success: Error err.from_utf8
  frame->slots[5] /* temp__3 */ = create_closure(entry__87_61, 0);
  // 904: ... :
  // 905:   CC $_out $err $success
  // 906:     ld_options*
  // 907:     "-shared"
  // 908:     library_paths_and_file_list()*
  // 909:     "-lsim-@(MAJOR)"
  // 910:     "-o"
  // 911:     lib_filename
  // 912:   unless success: Error err.from_utf8
  frame->slots[6] /* temp__4 */ = create_closure(entry__87_69, 0);
  // 913: ... :
  // 914:   CC $_out $err $success
  // 915:     ld_options*
  // 916:     "-dynamiclib"
  // 917:     "
  // 918:       -Wl,-install_name,libsim-@(base_filename)@(so_version)-@(MAJOR).dylib@
  // 919:     library_paths_and_file_list()*
  // 920:     "-lsim-@(MAJOR)"
  // 921:     "-o"
  // 922:     lib_filename
  // ...
  frame->slots[7] /* temp__5 */ = create_closure(entry__87_76, 0);
  // 924: :
  // 925:   CC $_out $err $success
  // 926:     ld_options*
  // 927:     "-shared"
  // 928:     library_paths_and_file_list()*
  // 929:     "-o"
  // 930:     lib_filename
  // 931:   unless success: Error err.from_utf8
  frame->slots[8] /* temp__6 */ = create_closure(entry__87_85, 0);
  // 893: case
  // 894:   operating_system()
  // 895:   "linux", "bsd":
  // 896:     CC $_out $err $success
  // 897:       ld_options*
  // 898:       "-shared"
  // 899:       "-Wl,-soname,libsim-@(base_filename)@(so_version).so.@(MAJOR)"
  // 900:       library_paths_and_file_list()*
  // 901:       "-o"
  // 902:       lib_filename
  // ...
  argument_count = 8;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = frame->slots[5] /* temp__3 */;
  arguments->slots[3] = string__87_37;
  arguments->slots[4] = frame->slots[6] /* temp__4 */;
  arguments->slots[5] = string__87_38;
  arguments->slots[6] = frame->slots[7] /* temp__5 */;
  arguments->slots[7] = frame->slots[8] /* temp__6 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__87_7(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 861: extract_documentation main_filename
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  result_count = frame->caller_result_count;
  myself = get__extract_documentation();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__87_8(void) {
  allocate_initialized_frame_gc(0, 11);
  // slot allocations:
  // version: 0
  // version_filename: 1
  // so_version: 2
  // base_filename: 3
  // lib_filename: 4
  frame->slots[0] /* version */ = create_cell();
  frame->slots[1] /* version_filename */ = create_future();
  frame->slots[2] /* so_version */ = create_future();
  frame->slots[3] /* base_filename */ = create_future();
  frame->slots[4] /* lib_filename */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 863: $$version ""
  ((CELL *)frame->slots[0])->contents /* version */ = empty_string;
  // 864: $version_filename string(main_filename "/VERSION")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  arguments->slots[1] = string__87_9;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__87_10;
}
static void cont__87_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* version_filename */, arguments->slots[0]);
  // 865: ... file_exists(version_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* version_filename */;
  result_count = 1;
  myself = get__file_exists();
  func = myself->type;
  frame->cont = cont__87_11;
}
static void cont__87_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 865: ... :
  // 866:   !version string('-' load(version_filename).trim)
  frame->slots[6] /* temp__2 */ = create_closure(entry__87_12, 0);
  // 865: if file_exists(version_filename):
  // 866:   !version string('-' load(version_filename).trim)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__87_16;
}
static void entry__87_12(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // version: 0
  // version_filename: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* version */
  frame->slots[1] = myself->closure.frame->slots[1]; /* version_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 866: ... load(version_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* version_filename */;
  result_count = 1;
  myself = get__load();
  func = myself->type;
  frame->cont = cont__87_13;
}
static void cont__87_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 866: ... load(version_filename).trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__87_14;
}
static void cont__87_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 866: !version string('-' load(version_filename).trim)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__45;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__87_15;
}
static void cont__87_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* version */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__87_16(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 867: $so_version version .truncate_from. '.'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* version */;
  arguments->slots[1] = character__46;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__87_17;
}
static void cont__87_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* so_version */, arguments->slots[0]);
  // 868: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__87_18;
}
static void cont__87_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 868: $base_filename truncate_until(main_filename '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__87_19;
}
static void cont__87_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* base_filename */, arguments->slots[0]);
  // 872: operating_system()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__operating_system();
  func = myself->type;
  frame->cont = cont__87_20;
}
static void cont__87_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 873: "linux", "bsd"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__80_23;
  arguments->slots[1] = string__80_24;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__87_21;
}
static void cont__87_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 874: -> string("libsim-" base_filename version ".so.@(MAJOR)")
  frame->slots[7] /* temp__3 */ = create_closure(entry__87_22, 0);
  // 876: -> string("libsim-" base_filename version "-@(MAJOR).dll")
  frame->slots[8] /* temp__4 */ = create_closure(entry__87_26, 0);
  // 878: -> string("libsim-" base_filename version "-@(MAJOR).dylib")
  frame->slots[9] /* temp__5 */ = create_closure(entry__87_30, 0);
  // 879: -> string("libsim-" base_filename version ".so.@(MAJOR)")
  frame->slots[10] /* temp__6 */ = create_closure(entry__87_34, 0);
  // 870: $lib_filename
  // 871:   case
  // 872:     operating_system()
  // 873:     "linux", "bsd"
  // 874:     -> string("libsim-" base_filename version ".so.@(MAJOR)")
  // 875:     "cygwin"
  // 876:     -> string("libsim-" base_filename version "-@(MAJOR).dll")
  // 877:     "darwin"
  // 878:     -> string("libsim-" base_filename version "-@(MAJOR).dylib")
  // 879:     -> string("libsim-" base_filename version ".so.@(MAJOR)")
  argument_count = 8;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  arguments->slots[2] = frame->slots[7] /* temp__3 */;
  arguments->slots[3] = string__87_37;
  arguments->slots[4] = frame->slots[8] /* temp__4 */;
  arguments->slots[5] = string__87_38;
  arguments->slots[6] = frame->slots[9] /* temp__5 */;
  arguments->slots[7] = frame->slots[10] /* temp__6 */;
  result_count = 1;
  myself = get__case();
  func = myself->type;
  frame->cont = cont__87_39;
}
static void entry__87_22(void) {
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
  // 874: ... ".so.@(MAJOR)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__80_28;
  arguments->slots[1] = var._MAJOR;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__87_23;
}
static void cont__87_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 874: ... string("libsim-" base_filename version ".so.@(MAJOR)")
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__87_24;
  arguments->slots[1] = frame->slots[0] /* base_filename */;
  arguments->slots[2] = ((CELL *)frame->slots[1])->contents /* version */;
  arguments->slots[3] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__87_25;
}
static void cont__87_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 874: -> string("libsim-" base_filename version ".so.@(MAJOR)")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__87_26(void) {
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
  // 876: ... "-@(MAJOR).dll"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__70_46;
  arguments->slots[1] = var._MAJOR;
  arguments->slots[2] = string__87_27;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__87_28;
}
static void cont__87_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 876: ... string("libsim-" base_filename version "-@(MAJOR).dll")
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__87_24;
  arguments->slots[1] = frame->slots[0] /* base_filename */;
  arguments->slots[2] = ((CELL *)frame->slots[1])->contents /* version */;
  arguments->slots[3] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__87_29;
}
static void cont__87_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 876: -> string("libsim-" base_filename version "-@(MAJOR).dll")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__87_30(void) {
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
  // 878: ... "-@(MAJOR).dylib"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__70_46;
  arguments->slots[1] = var._MAJOR;
  arguments->slots[2] = string__87_31;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__87_32;
}
static void cont__87_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 878: ... string("libsim-" base_filename version "-@(MAJOR).dylib")
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__87_24;
  arguments->slots[1] = frame->slots[0] /* base_filename */;
  arguments->slots[2] = ((CELL *)frame->slots[1])->contents /* version */;
  arguments->slots[3] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__87_33;
}
static void cont__87_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 878: -> string("libsim-" base_filename version "-@(MAJOR).dylib")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__87_34(void) {
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
  // 879: ... ".so.@(MAJOR)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__80_28;
  arguments->slots[1] = var._MAJOR;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__87_35;
}
static void cont__87_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 879: ... string("libsim-" base_filename version ".so.@(MAJOR)")
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__87_24;
  arguments->slots[1] = frame->slots[0] /* base_filename */;
  arguments->slots[2] = ((CELL *)frame->slots[1])->contents /* version */;
  arguments->slots[3] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__87_36;
}
static void cont__87_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 879: -> string("libsim-" base_filename version ".so.@(MAJOR)")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__87_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* lib_filename */, arguments->slots[0]);
  // 881: ... : ewriteln "build library " lib_filename
  frame->slots[5] /* temp__1 */ = create_closure(entry__87_40, 0);
  // 881: if verbose: ewriteln "build library " lib_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__87_42;
}
static void entry__87_40(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // lib_filename: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* lib_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 881: ... ewriteln "build library " lib_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__87_41;
  arguments->slots[1] = frame->slots[0] /* lib_filename */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__87_42(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 882: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__87_43;
}
static void cont__87_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 882: ... behind(main_filename '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__87_44;
}
static void cont__87_44(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 882: compile_modules main_filename behind(main_filename '/' -1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = var._compile_modules;
  func = myself->type;
  frame->cont = cont__87_45;
}
static void cont__87_45(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 883: ... :
  // 884:   $info stat(lib_filename)
  // 885:   if
  // 886:     ||
  // 887:       info.is_undefined
  // 888:       last_modification_time > modification_time_of(info)
  // 889:     :
  // 890:       !do_link true
  frame->slots[5] /* temp__1 */ = create_closure(entry__87_46, 0);
  // 883: unless do_link:
  // 884:   $info stat(lib_filename)
  // 885:   if
  // 886:     ||
  // 887:       info.is_undefined
  // 888:       last_modification_time > modification_time_of(info)
  // 889:     :
  // 890:       !do_link true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_link();
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__87_54;
}
static void entry__87_53(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 890: !do_link true
  set__do_link(get__true());
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__87_46(void) {
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
  // 884: $info stat(lib_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* lib_filename */;
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
  initialize_future(frame->slots[1] /* info */, arguments->slots[0]);
  // 887: info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
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
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 888: last_modification_time > modification_time_of(info)
  frame->slots[4] /* temp__3 */ = create_closure(entry__87_49, 0);
  // 886: ||
  // 887:   info.is_undefined
  // 888:   last_modification_time > modification_time_of(info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__87_52;
}
static void entry__87_49(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // info: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 888: ... modification_time_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
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
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 888: last_modification_time > modification_time_of(info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = get__last_modification_time();
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__87_51;
}
static void cont__87_51(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 888: last_modification_time > modification_time_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__87_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 885: if
  // 886:   ||
  // 887:     info.is_undefined
  // 888:     last_modification_time > modification_time_of(info)
  // 889:   :
  // 890:     !do_link true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = func__87_53;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__87_54(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 891: ... :
  // 892:   if verbose: ewriteln "linking dynamic library"
  // 893:   case
  // 894:     operating_system()
  // 895:     "linux", "bsd":
  // 896:       CC $_out $err $success
  // 897:         ld_options*
  // 898:         "-shared"
  // 899:         "-Wl,-soname,libsim-@(base_filename)@(so_version).so.@(MAJOR)"
  // 900:         library_paths_and_file_list()*
  // ...
  frame->slots[5] /* temp__1 */ = create_closure(entry__87_55, 0);
  // 891: if do_link:
  // 892:   if verbose: ewriteln "linking dynamic library"
  // 893:   case
  // 894:     operating_system()
  // 895:     "linux", "bsd":
  // 896:       CC $_out $err $success
  // 897:         ld_options*
  // 898:         "-shared"
  // 899:         "-Wl,-soname,libsim-@(base_filename)@(so_version).so.@(MAJOR)"
  // 900:         library_paths_and_file_list()*
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
static void cont__87_90(void) {
  myself = frame->slots[0] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__88_18(void) {
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
  // 946: ... : ewriteln "compiling runtime module @(filename)"
  frame->slots[3] /* temp__1 */ = create_closure(entry__88_19, 0);
  // 946: if verbose: ewriteln "compiling runtime module @(filename)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__88_22;
}
static void entry__88_19(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // filename: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 946: ... "compiling runtime module @(filename)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__88_20;
  arguments->slots[1] = frame->slots[0] /* filename */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__88_21;
}
static void cont__88_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 946: ... ewriteln "compiling runtime module @(filename)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__88_22(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 947: compile_c c_filename o_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* c_filename */;
  arguments->slots[1] = frame->slots[2] /* o_filename */;
  result_count = frame->caller_result_count;
  myself = var._compile_c;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__88_1_maybe_compile_c_file(void) {
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
  // 934: $c_filename string(filename ".c")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  arguments->slots[1] = string__74_9;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__88_2;
}
static void cont__88_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* c_filename */, arguments->slots[0]);
  // 935: $o_filename string(filename ".o")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  arguments->slots[1] = string__76_85;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__88_3;
}
static void cont__88_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* o_filename */, arguments->slots[0]);
  // 936: $c_info stat(c_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* c_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__88_4;
}
static void cont__88_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* c_info */, arguments->slots[0]);
  // 937: ... c_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* c_info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__88_5;
}
static void cont__88_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 937: ... :
  // 938:   Error "
  // 939:     @quot;@(c_filename)" does not exist!
  frame->slots[6] /* temp__2 */ = create_closure(entry__88_6, 0);
  // 937: if c_info.is_undefined:
  // 938:   Error "
  // 939:     @quot;@(c_filename)" does not exist!
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__88_10;
}
static void entry__88_6(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // c_filename: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* c_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 938: ... "
  // 939:   @quot;@(c_filename)" does not exist!
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__88_7;
  arguments->slots[1] = frame->slots[0] /* c_filename */;
  arguments->slots[2] = string__88_8;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__88_9;
}
static void cont__88_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 938: Error "
  // 939:   @quot;@(c_filename)" does not exist!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__88_10(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 940: $o_info stat(o_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* o_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__88_11;
}
static void cont__88_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* o_info */, arguments->slots[0]);
  // 943: o_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* o_info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__88_12;
}
static void cont__88_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 944: modification_time_of(c_info) > modification_time_of(o_info)
  frame->slots[7] /* temp__3 */ = create_closure(entry__88_13, 0);
  // 942: ||
  // 943:   o_info.is_undefined
  // 944:   modification_time_of(c_info) > modification_time_of(o_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__88_17;
}
static void entry__88_13(void) {
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
  // 944: ... modification_time_of(o_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* o_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__88_14;
}
static void cont__88_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 944: modification_time_of(c_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* c_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__88_15;
}
static void cont__88_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 944: modification_time_of(c_info) > modification_time_of(o_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__88_16;
}
static void cont__88_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 944: modification_time_of(c_info) > modification_time_of(o_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__88_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 945: :
  // 946:   if verbose: ewriteln "compiling runtime module @(filename)"
  // 947:   compile_c c_filename o_filename
  frame->slots[8] /* temp__4 */ = create_closure(entry__88_18, 0);
  // 941: if
  // 942:   ||
  // 943:     o_info.is_undefined
  // 944:     modification_time_of(c_info) > modification_time_of(o_info)
  // 945:   :
  // 946:     if verbose: ewriteln "compiling runtime module @(filename)"
  // 947:     compile_c c_filename o_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__90_1_format_number(void) {
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
  // 957: to_string &val
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* val */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__90_2;
}
static void cont__90_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* val */ = arguments->slots[0];
  // 958: $$ac 0
  ((CELL *)frame->slots[3])->contents /* ac */ = number__0;
  // 959: ... : (-> break)
  // 960:   for_each val: (i chr)
  // 961:     if chr == '.':
  // 962:       !ac length_of(val)-i
  // 963:       if n > i-1: append dup(" " n-(i-1)) &val
  // 964:       break
  frame->slots[4] /* temp__1 */ = create_closure(entry__90_3, 0);
  // 959: do: (-> break)
  // 960:   for_each val: (i chr)
  // 961:     if chr == '.':
  // 962:       !ac length_of(val)-i
  // 963:       if n > i-1: append dup(" " n-(i-1)) &val
  // 964:       break
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__90_19;
}
static void entry__90_3(void) {
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
  // 960: ... : (i chr)
  // 961:   if chr == '.':
  // 962:     !ac length_of(val)-i
  // 963:     if n > i-1: append dup(" " n-(i-1)) &val
  // 964:     break
  frame->slots[4] /* temp__1 */ = create_closure(entry__90_4, 2);
  // 960: for_each val: (i chr)
  // 961:   if chr == '.':
  // 962:     !ac length_of(val)-i
  // 963:     if n > i-1: append dup(" " n-(i-1)) &val
  // 964:     break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* val */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__90_18;
}
static void entry__90_6(void) {
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
  // 962: ... length_of(val)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* val */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__90_7;
}
static void cont__90_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 962: !ac length_of(val)-i
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* i */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__90_8;
}
static void cont__90_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* ac */ = arguments->slots[0];
  // 963: ... i-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* i */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__90_9;
}
static void cont__90_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 963: ... n > i-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* n */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__90_10;
}
static void cont__90_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 963: ... : append dup(" " n-(i-1)) &val
  frame->slots[7] /* temp__3 */ = create_closure(entry__90_11, 0);
  // 963: if n > i-1: append dup(" " n-(i-1)) &val
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__90_17;
}
static void entry__90_11(void) {
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
  // 963: ... i-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* i */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__90_12;
}
static void cont__90_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 963: ... n-(i-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* n */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__90_13;
}
static void cont__90_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 963: ... dup(" " n-(i-1))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__90_14;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__90_15;
}
static void cont__90_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 963: ... append dup(" " n-(i-1)) &val
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* val */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__90_16;
}
static void cont__90_16(void) {
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
static void cont__90_17(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 964: break
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[4] /* break */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__90_4(void) {
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
  // 961: ... chr == '.'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* chr */;
  arguments->slots[1] = character__46;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__90_5;
}
static void cont__90_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 961: ... :
  // 962:   !ac length_of(val)-i
  // 963:   if n > i-1: append dup(" " n-(i-1)) &val
  // 964:   break
  frame->slots[7] /* temp__2 */ = create_closure(entry__90_6, 0);
  // 961: if chr == '.':
  // 962:   !ac length_of(val)-i
  // 963:   if n > i-1: append dup(" " n-(i-1)) &val
  // 964:   break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__90_18(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__90_19(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 966: m > ac
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* ac */;
  arguments->slots[1] = frame->slots[2] /* m */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__90_20;
}
static void cont__90_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 966: ... :
  // 967:   append &val dup("0" m-ac)
  frame->slots[5] /* temp__2 */ = create_closure(entry__90_21, 0);
  // 968: :
  // 969:   if ac > m: range &val 1 -(ac-m+1)
  frame->slots[6] /* temp__3 */ = create_closure(entry__90_26, 0);
  // 965: if
  // 966:   m > ac:
  // 967:     append &val dup("0" m-ac)
  // 968:   :
  // 969:     if ac > m: range &val 1 -(ac-m+1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__90_33;
}
static void entry__90_28(void) {
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
  // 969: ... ac-m
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* ac */;
  arguments->slots[1] = frame->slots[2] /* m */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__90_29;
}
static void cont__90_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 969: ... ac-m+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__90_30;
}
static void cont__90_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 969: ... ac-m+1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__90_31;
}
static void cont__90_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 969: ... range &val 1 -(ac-m+1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* val */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__90_32;
}
static void cont__90_32(void) {
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
static void entry__90_21(void) {
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
  // 967: ... m-ac
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* m */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* ac */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__90_22;
}
static void cont__90_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 967: ... dup("0" m-ac)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__90_23;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__90_24;
}
static void cont__90_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 967: append &val dup("0" m-ac)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* val */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__90_25;
}
static void cont__90_25(void) {
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
static void entry__90_26(void) {
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
  // 969: ... ac > m
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* m */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* ac */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__90_27;
}
static void cont__90_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 969: ... : range &val 1 -(ac-m+1)
  frame->slots[4] /* temp__2 */ = create_closure(entry__90_28, 0);
  // 969: if ac > m: range &val 1 -(ac-m+1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__90_33(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 970: -> val
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* val */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__91_1_sim2c__write_timing_info(void) {
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
  // 973: $new_t current_time()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__current_time();
  func = myself->type;
  frame->cont = cont__91_2;
}
static void cont__91_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* new_t */, arguments->slots[0]);
  // 975: filename.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* filename */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__91_3;
}
static void cont__91_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 975: ... :
  // 976:   truncate_until &filename '/' -1
  // 977:   ewriteln
  // 978:     description
  // 979:     ' '
  // 980:     filename
  // 981:     ':'
  // 982:     dup(" " 12-length_of(description))
  // 983:     format_number(new_t-t 2 3)
  // 984:     " s"
  frame->slots[4] /* temp__2 */ = create_closure(entry__91_4, 0);
  // 985: :
  // 986:   ewriteln description ": " format_number(new_t-t 0 3) " s"
  frame->slots[5] /* temp__3 */ = create_closure(entry__91_13, 0);
  // 974: if
  // 975:   filename.is_defined:
  // 976:     truncate_until &filename '/' -1
  // 977:     ewriteln
  // 978:       description
  // 979:       ' '
  // 980:       filename
  // 981:       ':'
  // 982:       dup(" " 12-length_of(description))
  // 983:       format_number(new_t-t 2 3)
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = frame->slots[5] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__91_17;
}
static void entry__91_4(void) {
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
  // 976: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__91_5;
}
static void cont__91_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 976: truncate_until &filename '/' -1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* filename */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__91_6;
}
static void cont__91_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* filename */ = arguments->slots[0];
  // 982: ... length_of(description)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* description */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__91_7;
}
static void cont__91_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 982: ... 12-length_of(description)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__12;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__91_8;
}
static void cont__91_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 982: dup(" " 12-length_of(description))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__90_14;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__91_9;
}
static void cont__91_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 983: ... new_t-t
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* new_t */;
  arguments->slots[1] = var._t;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__91_10;
}
static void cont__91_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__5 */ = arguments->slots[0];
  // 983: format_number(new_t-t 2 3)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__5 */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = number__3;
  result_count = 1;
  myself = var._format_number;
  func = myself->type;
  frame->cont = cont__91_11;
}
static void cont__91_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__4 */ = arguments->slots[0];
  // 977: ewriteln
  // 978:   description
  // 979:   ' '
  // 980:   filename
  // 981:   ':'
  // 982:   dup(" " 12-length_of(description))
  // 983:   format_number(new_t-t 2 3)
  // 984:   " s"
  argument_count = 7;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* description */;
  arguments->slots[1] = character__32;
  arguments->slots[2] = ((CELL *)frame->slots[0])->contents /* filename */;
  arguments->slots[3] = character__58;
  arguments->slots[4] = frame->slots[3] /* temp__1 */;
  arguments->slots[5] = frame->slots[6] /* temp__4 */;
  arguments->slots[6] = string__91_12;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__91_13(void) {
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
  // 986: ... new_t-t
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* new_t */;
  arguments->slots[1] = var._t;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__91_14;
}
static void cont__91_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 986: ... format_number(new_t-t 0 3)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = number__0;
  arguments->slots[2] = number__3;
  result_count = 1;
  myself = var._format_number;
  func = myself->type;
  frame->cont = cont__91_15;
}
static void cont__91_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 986: ewriteln description ": " format_number(new_t-t 0 3) " s"
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* description */;
  arguments->slots[1] = string__91_16;
  arguments->slots[2] = frame->slots[2] /* temp__1 */;
  arguments->slots[3] = string__91_12;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__91_17(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 987: !t current_time()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__current_time();
  func = myself->type;
  frame->cont = cont__91_18;
}
static void cont__91_18(void) {
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
static void entry__92_116(void) {
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
  // 1082: exe_filename .has_prefix. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* exe_filename */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__92_117;
}
static void cont__92_117(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 1083: -> exe_filename
  frame->slots[4] /* temp__3 */ = create_closure(entry__92_118, 0);
  // 1084: -> string("./" exe_filename)
  frame->slots[5] /* temp__4 */ = create_closure(entry__92_119, 0);
  // 1081: if
  // 1082:   exe_filename .has_prefix. '/'
  // 1083:   -> exe_filename
  // 1084:   -> string("./" exe_filename)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  arguments->slots[2] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__92_121;
}
static void entry__92_118(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // exe_filename: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* exe_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1083: -> exe_filename
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* exe_filename */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__92_119(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // exe_filename: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* exe_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1084: ... string("./" exe_filename)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__74_56;
  arguments->slots[1] = frame->slots[0] /* exe_filename */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__92_120;
}
static void cont__92_120(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1084: -> string("./" exe_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__92_121(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1080: exec
  // 1081:   if
  // 1082:     exe_filename .has_prefix. '/'
  // 1083:     -> exe_filename
  // 1084:     -> string("./" exe_filename)
  // 1085:   zz*
  // 1086:   
  // 1087:   #range(command_line_arguments 2 -1)*
  argument_count = 0;
  arguments = node_p;
  arguments->slots[argument_count++] = frame->slots[2] /* temp__1 */;
  unfold(frame->slots[1] /* zz */);
  result_count = frame->caller_result_count;
  myself = get__exec();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__92_2(void) {
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
  // 1002: operating_system()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__operating_system();
  func = myself->type;
  frame->cont = cont__92_3;
}
static void cont__92_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__2 */ = arguments->slots[0];
  // 1002: operating_system() == "cygwin"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__2 */;
  arguments->slots[1] = string__87_37;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__92_4;
}
static void cont__92_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 1003: -> string(mod_filename ".exe")
  frame->slots[11] /* temp__3 */ = create_closure(entry__92_5, 0);
  // 1004: -> mod_filename
  frame->slots[12] /* temp__4 */ = create_closure(entry__92_8, 0);
  // 1000: $exe_filename
  // 1001:   if
  // 1002:     operating_system() == "cygwin"
  // 1003:     -> string(mod_filename ".exe")
  // 1004:     -> mod_filename
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = frame->slots[11] /* temp__3 */;
  arguments->slots[2] = frame->slots[12] /* temp__4 */;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__92_9;
}
static void entry__92_5(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // mod_filename: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* mod_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1003: ... string(mod_filename ".exe")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = string__92_6;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__92_7;
}
static void cont__92_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1003: -> string(mod_filename ".exe")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__92_8(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // mod_filename: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* mod_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1004: -> mod_filename
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__92_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* exe_filename */, arguments->slots[0]);
  // 1006: ... : ewriteln "build executable " exe_filename
  frame->slots[9] /* temp__1 */ = create_closure(entry__92_10, 0);
  // 1006: if verbose: ewriteln "build executable " exe_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__92_12;
}
static void entry__92_10(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // exe_filename: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* exe_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1006: ... ewriteln "build executable " exe_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__92_11;
  arguments->slots[1] = frame->slots[0] /* exe_filename */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__92_12(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1007: $c_filename string(mod_filename ".c")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = string__74_9;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__92_13;
}
static void cont__92_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* c_filename */, arguments->slots[0]);
  // 1008: $o_filename string(mod_filename ".o")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = string__76_85;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__92_14;
}
static void cont__92_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* o_filename */, arguments->slots[0]);
  // 1009: $sim_info stat(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__92_15;
}
static void cont__92_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* sim_info */, arguments->slots[0]);
  // 1010: $c_info stat(c_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* c_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__92_16;
}
static void cont__92_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* c_info */, arguments->slots[0]);
  // 1011: $$c_buf undefined
  ((CELL *)frame->slots[7])->contents /* c_buf */ = get__undefined();
  // 1012: !objects(o_filename) true
  frame->slots[9] /* temp__1 */ = get__true();
  // 1012: !objects(o_filename)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* o_filename */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = get__objects();
  func = myself->type;
  frame->cont = cont__92_17;
}
static void cont__92_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__objects(arguments->slots[0]);
  frame->slots[10] /* temp__2 */ = create_closure(entry__92_18, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_rebuild;
  arguments->slots[1] = frame->slots[10] /* temp__2 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__92_25;
}
static void entry__92_18(void) {
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
  // 1016: c_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__92_19;
}
static void cont__92_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 1017: modification_time_of(sim_info) > modification_time_of(c_info)
  frame->slots[4] /* temp__3 */ = create_closure(entry__92_20, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__92_24;
}
static void entry__92_20(void) {
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
  // 1017: ... modification_time_of(c_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__92_21;
}
static void cont__92_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 1017: modification_time_of(sim_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* sim_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__92_22;
}
static void cont__92_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 1017: modification_time_of(sim_info) > modification_time_of(c_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__92_23;
}
static void cont__92_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1017: modification_time_of(sim_info) > modification_time_of(c_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__92_24(void) {
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
static void cont__92_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 1018: :
  // 1019:   %sim2c::module_name mod_name .without_suffix. some(".meta")
  // 1020:   if verbose: ewriteln "build main module " module_name
  // 1021:   collect_output $c_source: sim2c list(main_filename) true
  // 1022:   collect_output !c_buf: create_imports c_source
  // 1023:   save c_filename c_buf.to_utf8
  // 1024:   if do_time_passes: write_timing_info "saving" c_filename
  // 1025:   compile_c c_filename o_filename
  // 1026:   if do_time_passes: write_timing_info "compiling" c_filename
  frame->slots[11] /* temp__3 */ = create_closure(entry__92_26, 0);
  // 1027: :
  // 1028:   load !c_buf c_filename
  // 1029:   $o_info stat(o_filename)
  // 1030:   if
  // 1031:     ||
  // 1032:       o_info.is_undefined
  // 1033:       modification_time_of(c_info) > modification_time_of(o_info)
  // 1034:     :
  // 1035:       compile_c c_filename o_filename
  // 1036:     :
  // ...
  frame->slots[12] /* temp__4 */ = create_closure(entry__92_46, 0);
  // 1013: if
  // 1014:   ||
  // 1015:     do_rebuild
  // 1016:     c_info.is_undefined
  // 1017:     modification_time_of(sim_info) > modification_time_of(c_info)
  // 1018:   :
  // 1019:     %sim2c::module_name mod_name .without_suffix. some(".meta")
  // 1020:     if verbose: ewriteln "build main module " module_name
  // 1021:     collect_output $c_source: sim2c list(main_filename) true
  // 1022:     collect_output !c_buf: create_imports c_source
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = frame->slots[11] /* temp__3 */;
  arguments->slots[2] = frame->slots[12] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__92_58;
}
static void entry__92_55(void) {
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
  // 1035: compile_c c_filename o_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_filename */;
  arguments->slots[1] = frame->slots[1] /* o_filename */;
  result_count = frame->caller_result_count;
  myself = var._compile_c;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__92_56(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // o_info: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* o_info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1037: !last_modification_time modification_time_of(o_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* o_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__92_57;
}
static void cont__92_57(void) {
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
static void entry__92_26(void) {
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
  // 1019: ... some(".meta")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__70_16;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__92_27;
}
static void cont__92_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 1019: %sim2c::module_name mod_name .without_suffix. some(".meta")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* mod_name */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = get__without_suffix();
  func = myself->type;
  frame->cont = cont__92_28;
}
static void cont__92_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(get__sim2c__module_name(), arguments->slots[0]);
  // 1020: if verbose: ewriteln "build main module " module_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = func__92_29;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__92_31;
}
static void entry__92_29(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1020: ... ewriteln "build main module " module_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__92_30;
  arguments->slots[1] = get__module_name();
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__92_31(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1021: collect_output $c_source: sim2c list(main_filename) true
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__92_32;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__92_34;
}
static void entry__92_32(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1021: ... list(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__92_33;
}
static void cont__92_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1021: ... sim2c list(main_filename) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = get__true();
  result_count = frame->caller_result_count;
  myself = get__sim2c();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__92_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* c_source */, arguments->slots[0]);
  // 1022: ... : create_imports c_source
  frame->slots[6] /* temp__1 */ = create_closure(entry__92_35, 0);
  // 1022: collect_output !c_buf: create_imports c_source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__92_36;
}
static void entry__92_35(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // c_source: 0
  frame->slots[0] = myself->closure.frame->slots[5]; /* c_source */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1022: ... create_imports c_source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_source */;
  result_count = frame->caller_result_count;
  myself = var._create_imports;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__92_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* c_buf */ = arguments->slots[0];
  // 1023: ... c_buf.to_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* c_buf */;
  result_count = 1;
  myself = get__to_utf8();
  func = myself->type;
  frame->cont = cont__92_37;
}
static void cont__92_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 1023: save c_filename c_buf.to_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* c_filename */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 0;
  myself = get__save();
  func = myself->type;
  frame->cont = cont__92_38;
}
static void cont__92_38(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1024: ... : write_timing_info "saving" c_filename
  frame->slots[6] /* temp__1 */ = create_closure(entry__92_39, 0);
  // 1024: if do_time_passes: write_timing_info "saving" c_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__92_41;
}
static void entry__92_39(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // c_filename: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* c_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1024: ... write_timing_info "saving" c_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__92_40;
  arguments->slots[1] = frame->slots[0] /* c_filename */;
  result_count = frame->caller_result_count;
  myself = get__write_timing_info();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__92_41(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1025: compile_c c_filename o_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* c_filename */;
  arguments->slots[1] = frame->slots[4] /* o_filename */;
  result_count = 0;
  myself = var._compile_c;
  func = myself->type;
  frame->cont = cont__92_42;
}
static void cont__92_42(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1026: ... : write_timing_info "compiling" c_filename
  frame->slots[6] /* temp__1 */ = create_closure(entry__92_43, 0);
  // 1026: if do_time_passes: write_timing_info "compiling" c_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__92_45;
}
static void entry__92_43(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // c_filename: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* c_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1026: ... write_timing_info "compiling" c_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__92_44;
  arguments->slots[1] = frame->slots[0] /* c_filename */;
  result_count = frame->caller_result_count;
  myself = get__write_timing_info();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__92_45(void) {
  myself = frame->slots[0] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__92_46(void) {
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
  // 1028: load !c_buf c_filename
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* c_filename */;
  result_count = 1;
  myself = get__load();
  func = myself->type;
  frame->cont = cont__92_47;
}
static void cont__92_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* c_buf */ = arguments->slots[0];
  // 1029: $o_info stat(o_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* o_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__92_48;
}
static void cont__92_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* o_info */, arguments->slots[0]);
  // 1032: o_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* o_info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__92_49;
}
static void cont__92_49(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 1033: modification_time_of(c_info) > modification_time_of(o_info)
  frame->slots[7] /* temp__3 */ = create_closure(entry__92_50, 0);
  // 1031: ||
  // 1032:   o_info.is_undefined
  // 1033:   modification_time_of(c_info) > modification_time_of(o_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__92_54;
}
static void entry__92_50(void) {
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
  // 1033: ... modification_time_of(o_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* o_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__92_51;
}
static void cont__92_51(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 1033: modification_time_of(c_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* c_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__92_52;
}
static void cont__92_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 1033: modification_time_of(c_info) > modification_time_of(o_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__92_53;
}
static void cont__92_53(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1033: modification_time_of(c_info) > modification_time_of(o_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__92_54(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 1034: :
  // 1035:   compile_c c_filename o_filename
  frame->slots[8] /* temp__4 */ = create_closure(entry__92_55, 0);
  // 1036: :
  // 1037:   !last_modification_time modification_time_of(o_info)
  frame->slots[9] /* temp__5 */ = create_closure(entry__92_56, 0);
  // 1030: if
  // 1031:   ||
  // 1032:     o_info.is_undefined
  // 1033:     modification_time_of(c_info) > modification_time_of(o_info)
  // 1034:   :
  // 1035:     compile_c c_filename o_filename
  // 1036:   :
  // 1037:     !last_modification_time modification_time_of(o_info)
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
static void cont__92_58(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1038: build_dependencies mod_filename mod_name c_buf
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = frame->slots[1] /* mod_name */;
  arguments->slots[2] = ((CELL *)frame->slots[7])->contents /* c_buf */;
  result_count = 0;
  myself = var._build_dependencies;
  func = myself->type;
  frame->cont = cont__92_59;
}
static void cont__92_59(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1039: if do_build_static_executable:
  // 1040:   for_each
  // 1041:     "runtime/linker", "runtime/memory", "runtime/debugger": (filename)
  // 1042:       maybe_compile_c_file filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_build_static_executable();
  arguments->slots[1] = func__92_60;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__92_66;
}
static void entry__92_65(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // filename: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 1042: maybe_compile_c_file filename
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  result_count = frame->caller_result_count;
  myself = var._maybe_compile_c_file;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__92_60(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1041: "runtime/linker", "runtime/memory", "runtime/debugger"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__92_61;
  arguments->slots[1] = string__92_62;
  arguments->slots[2] = string__92_63;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__92_64;
}
static void cont__92_64(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1040: for_each
  // 1041:   "runtime/linker", "runtime/memory", "runtime/debugger": (filename)
  // 1042:     maybe_compile_c_file filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__92_65;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__92_66(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1043: ... :
  // 1044:   $info stat(exe_filename)
  // 1045:   if
  // 1046:     ||
  // 1047:       info.is_undefined
  // 1048:       &&
  // 1049:         last_modification_time.is_defined
  // 1050:         last_modification_time > modification_time_of(info)
  // 1051:     :
  // 1052:       !do_link true
  frame->slots[9] /* temp__1 */ = create_closure(entry__92_67, 0);
  // 1043: unless do_link:
  // 1044:   $info stat(exe_filename)
  // 1045:   if
  // 1046:     ||
  // 1047:       info.is_undefined
  // 1048:       &&
  // 1049:         last_modification_time.is_defined
  // 1050:         last_modification_time > modification_time_of(info)
  // 1051:     :
  // 1052:       !do_link true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_link();
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__92_78;
}
static void entry__92_77(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1052: !do_link true
  set__do_link(get__true());
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__92_67(void) {
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
  // 1044: $info stat(exe_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* exe_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__92_68;
}
static void cont__92_68(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* info */, arguments->slots[0]);
  // 1047: info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__92_69;
}
static void cont__92_69(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 1048: &&
  // 1049:   last_modification_time.is_defined
  // 1050:   last_modification_time > modification_time_of(info)
  frame->slots[4] /* temp__3 */ = create_closure(entry__92_70, 0);
  // 1046: ||
  // 1047:   info.is_undefined
  // 1048:   &&
  // 1049:     last_modification_time.is_defined
  // 1050:     last_modification_time > modification_time_of(info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__92_76;
}
static void entry__92_70(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // info: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1049: last_modification_time.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__last_modification_time();
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__92_71;
}
static void cont__92_71(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 1050: last_modification_time > modification_time_of(info)
  frame->slots[3] /* temp__3 */ = create_closure(entry__92_72, 0);
  // 1048: &&
  // 1049:   last_modification_time.is_defined
  // 1050:   last_modification_time > modification_time_of(info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__92_75;
}
static void entry__92_72(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // info: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1050: ... modification_time_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__92_73;
}
static void cont__92_73(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 1050: last_modification_time > modification_time_of(info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = get__last_modification_time();
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__92_74;
}
static void cont__92_74(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1050: last_modification_time > modification_time_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__92_75(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1048: &&
  // 1049:   last_modification_time.is_defined
  // 1050:   last_modification_time > modification_time_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__92_76(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1045: if
  // 1046:   ||
  // 1047:     info.is_undefined
  // 1048:     &&
  // 1049:       last_modification_time.is_defined
  // 1050:       last_modification_time > modification_time_of(info)
  // 1051:   :
  // 1052:     !do_link true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = func__92_77;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__92_78(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1053: ... :
  // 1054:   $$libs_and_files library_paths_and_file_list()
  // 1055:   if do_link_profiler: push &libs_and_files "/usr/lib/libprofiler.so.0"
  // 1056:   if
  // 1057:     do_build_static_executable:
  // 1058:       if verbose: ewriteln "linking static executable"
  // 1059:       CC $_out $err $success
  // 1060:         "runtime/linker.o"
  // 1061:         "runtime/memory.o"
  // 1062:         "runtime/debugger.o"
  // ...
  frame->slots[9] /* temp__1 */ = create_closure(entry__92_79, 0);
  // 1053: if do_link:
  // 1054:   $$libs_and_files library_paths_and_file_list()
  // 1055:   if do_link_profiler: push &libs_and_files "/usr/lib/libprofiler.so.0"
  // 1056:   if
  // 1057:     do_build_static_executable:
  // 1058:       if verbose: ewriteln "linking static executable"
  // 1059:       CC $_out $err $success
  // 1060:         "runtime/linker.o"
  // 1061:         "runtime/memory.o"
  // 1062:         "runtime/debugger.o"
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_link();
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__92_110;
}
static void entry__92_108(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // err: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* err */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1077: ... err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* err */;
  result_count = 1;
  myself = get__from_utf8();
  func = myself->type;
  frame->cont = cont__92_109;
}
static void cont__92_109(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1077: ... Error err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__92_93(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // err: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* err */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1066: ... err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* err */;
  result_count = 1;
  myself = get__from_utf8();
  func = myself->type;
  frame->cont = cont__92_94;
}
static void cont__92_94(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1066: ... Error err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__92_85(void) {
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
  // 1058: if verbose: ewriteln "linking static executable"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = func__92_86;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__92_88;
}
static void entry__92_86(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1058: ... ewriteln "linking static executable"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__92_87;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__92_88(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1059: CC $_out $err $success
  // 1060:   "runtime/linker.o"
  // 1061:   "runtime/memory.o"
  // 1062:   "runtime/debugger.o"
  // 1063:   libs_and_files*
  // 1064:   "-o"
  // 1065:   exe_filename
  argument_count = 0;
  arguments = node_p;
  arguments->slots[argument_count++] = string__92_89;
  arguments->slots[argument_count++] = string__92_90;
  arguments->slots[argument_count++] = string__92_91;
  unfold(((CELL *)frame->slots[0])->contents /* libs_and_files */);
  arguments->slots[argument_count++] = string__73_6;
  arguments->slots[argument_count++] = frame->slots[1] /* exe_filename */;
  result_count = 3;
  myself = var._CC;
  func = myself->type;
  frame->cont = cont__92_92;
}
static void cont__92_92(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  frame->slots[6] /* temp__2 */ = arguments->slots[1];
  frame->slots[7] /* temp__3 */ = arguments->slots[2];
  // 1059: ... _out
  initialize_future(frame->slots[2] /* out */, frame->slots[5] /* temp__1 */);
  // 1059: ... err
  initialize_future(frame->slots[3] /* err */, frame->slots[6] /* temp__2 */);
  // 1059: ... success
  initialize_future(frame->slots[4] /* success */, frame->slots[7] /* temp__3 */);
  // 1066: ... : Error err.from_utf8
  frame->slots[5] /* temp__1 */ = create_closure(entry__92_93, 0);
  // 1066: unless success: Error err.from_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* success */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__92_95(void) {
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
  // 1068: if verbose: ewriteln "linking executable"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = func__92_96;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__92_98;
}
static void entry__92_96(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1068: ... ewriteln "linking executable"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__92_97;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__92_98(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1072: operating_system()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__operating_system();
  func = myself->type;
  frame->cont = cont__92_99;
}
static void cont__92_99(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 1073: "linux", "bsd"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__80_23;
  arguments->slots[1] = string__80_24;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__92_100;
}
static void cont__92_100(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__3 */ = arguments->slots[0];
  // 1071: case
  // 1072:   operating_system()
  // 1073:   "linux", "bsd" -> "-l:libsim.so.@(MAJOR)"
  // 1074:   -> "-lsim-@(MAJOR)"
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  arguments->slots[2] = func__92_101;
  arguments->slots[3] = func__92_104;
  result_count = 1;
  myself = get__case();
  func = myself->type;
  frame->cont = cont__92_106;
}
static void entry__92_101(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1073: ... "-l:libsim.so.@(MAJOR)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__92_102;
  arguments->slots[1] = var._MAJOR;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__92_103;
}
static void cont__92_103(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1073: ... -> "-l:libsim.so.@(MAJOR)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__92_104(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1074: ... "-lsim-@(MAJOR)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__87_71;
  arguments->slots[1] = var._MAJOR;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__92_105;
}
static void cont__92_105(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1074: -> "-lsim-@(MAJOR)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__92_106(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 1069: CC $_out $err $success
  // 1070:   libs_and_files*
  // 1071:   case
  // 1072:     operating_system()
  // 1073:     "linux", "bsd" -> "-l:libsim.so.@(MAJOR)"
  // 1074:     -> "-lsim-@(MAJOR)"
  // 1075:   "-o"
  // 1076:   exe_filename
  argument_count = 0;
  arguments = node_p;
  unfold(((CELL *)frame->slots[0])->contents /* libs_and_files */);
  arguments->slots[argument_count++] = frame->slots[5] /* temp__1 */;
  arguments->slots[argument_count++] = string__73_6;
  arguments->slots[argument_count++] = frame->slots[1] /* exe_filename */;
  result_count = 3;
  myself = var._CC;
  func = myself->type;
  frame->cont = cont__92_107;
}
static void cont__92_107(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__4 */ = arguments->slots[0];
  frame->slots[9] /* temp__5 */ = arguments->slots[1];
  frame->slots[10] /* temp__6 */ = arguments->slots[2];
  // 1069: ... _out
  initialize_future(frame->slots[2] /* out */, frame->slots[8] /* temp__4 */);
  // 1069: ... err
  initialize_future(frame->slots[3] /* err */, frame->slots[9] /* temp__5 */);
  // 1069: ... success
  initialize_future(frame->slots[4] /* success */, frame->slots[10] /* temp__6 */);
  // 1077: ... : Error err.from_utf8
  frame->slots[5] /* temp__1 */ = create_closure(entry__92_108, 0);
  // 1077: unless success: Error err.from_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* success */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__92_79(void) {
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
  // 1054: $$libs_and_files library_paths_and_file_list()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = var._library_paths_and_file_list;
  func = myself->type;
  frame->cont = cont__92_80;
}
static void cont__92_80(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* libs_and_files */ = arguments->slots[0];
  // 1055: ... : push &libs_and_files "/usr/lib/libprofiler.so.0"
  frame->slots[2] /* temp__1 */ = create_closure(entry__92_81, 0);
  // 1055: if do_link_profiler: push &libs_and_files "/usr/lib/libprofiler.so.0"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_link_profiler;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__92_84;
}
static void entry__92_81(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // libs_and_files: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* libs_and_files */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1055: ... push &libs_and_files "/usr/lib/libprofiler.so.0"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* libs_and_files */;
  arguments->slots[1] = string__92_82;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__92_83;
}
static void cont__92_83(void) {
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
static void cont__92_84(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1057: ... :
  // 1058:   if verbose: ewriteln "linking static executable"
  // 1059:   CC $_out $err $success
  // 1060:     "runtime/linker.o"
  // 1061:     "runtime/memory.o"
  // 1062:     "runtime/debugger.o"
  // 1063:     libs_and_files*
  // 1064:     "-o"
  // 1065:     exe_filename
  // 1066:   unless success: Error err.from_utf8
  frame->slots[2] /* temp__1 */ = create_closure(entry__92_85, 0);
  // 1067: :
  // 1068:   if verbose: ewriteln "linking executable"
  // 1069:   CC $_out $err $success
  // 1070:     libs_and_files*
  // 1071:     case
  // 1072:       operating_system()
  // 1073:       "linux", "bsd" -> "-l:libsim.so.@(MAJOR)"
  // 1074:       -> "-lsim-@(MAJOR)"
  // 1075:     "-o"
  // 1076:     exe_filename
  // ...
  frame->slots[3] /* temp__2 */ = create_closure(entry__92_95, 0);
  // 1056: if
  // 1057:   do_build_static_executable:
  // 1058:     if verbose: ewriteln "linking static executable"
  // 1059:     CC $_out $err $success
  // 1060:       "runtime/linker.o"
  // 1061:       "runtime/memory.o"
  // 1062:       "runtime/debugger.o"
  // 1063:       libs_and_files*
  // 1064:       "-o"
  // 1065:       exe_filename
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
static void cont__92_110(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1078: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__92_111;
}
static void cont__92_111(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 1078: $zz range(command_line_arguments 2 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__command_line_arguments();
  arguments->slots[1] = number__2;
  arguments->slots[2] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__92_112;
}
static void cont__92_112(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[8] /* zz */, arguments->slots[0]);
  // 1079: ... on_top_level && action == "simrun"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__on_top_level();
  arguments->slots[1] = func__92_113;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__92_115;
}
static void entry__92_113(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1079: ... action == "simrun"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._action;
  arguments->slots[1] = string__87_2;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__92_114;
}
static void cont__92_114(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1079: ... action == "simrun"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__92_115(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 1079: ... :
  // 1080:   exec
  // 1081:     if
  // 1082:       exe_filename .has_prefix. '/'
  // 1083:       -> exe_filename
  // 1084:       -> string("./" exe_filename)
  // 1085:     zz*
  // 1086:     
  // 1087:     #range(command_line_arguments 2 -1)*
  frame->slots[10] /* temp__2 */ = create_closure(entry__92_116, 0);
  // 1079: if on_top_level && action == "simrun":
  // 1080:   exec
  // 1081:     if
  // 1082:       exe_filename .has_prefix. '/'
  // 1083:       -> exe_filename
  // 1084:       -> string("./" exe_filename)
  // 1085:     zz*
  // 1086:     
  // 1087:     #range(command_line_arguments 2 -1)*
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__92_1_build_executable(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  //  999: compile_exe: (mod_filename mod_name)
  // 1000:   $exe_filename
  // 1001:     if
  // 1002:       operating_system() == "cygwin"
  // 1003:       -> string(mod_filename ".exe")
  // 1004:       -> mod_filename
  // 1005:   
  // 1006:   if verbose: ewriteln "build executable " exe_filename
  // 1007:   $c_filename string(mod_filename ".c")
  // 1008:   $o_filename string(mod_filename ".o")
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__92_2;
  result_count = frame->caller_result_count;
  myself = var._compile_exe;
  func = myself->type;
  frame = frame->caller_frame;
}
EXPORT void collect__simple(void) {
  var._MAJOR = collect_node(var._MAJOR);
  var._MINOR = collect_node(var._MINOR);
  var._REVISION = collect_node(var._REVISION);
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
  var.sim2c__do_print_missing = collect_node(var.sim2c__do_print_missing);
  var.sim2c__do_print_summary = collect_node(var.sim2c__do_print_summary);
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
  var._cc_options = collect_node(var._cc_options);
  var._cpp_options = collect_node(var._cpp_options);
  var._ld_options = collect_node(var._ld_options);
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
  func__48_1_sim2c__show_compiler_debug_info = create_function(entry__48_1_sim2c__show_compiler_debug_info, -1);
  unique__EXE = register_unique_item("EXE");
  unique__LIB = register_unique_item("LIB");
  func__69_8 = create_function(entry__69_8, 1);
  func__69_4 = create_function(entry__69_4, 1);
  func__69_3 = create_function(entry__69_3, 0);
  string__69_21 = from_latin_1_string("Cannot resolve required library \042", 33);
  string__69_22 = from_latin_1_string("\042!", 2);
  func__69_1_resolve_filename = create_function(entry__69_1_resolve_filename, 1);
  string__70_13 = from_latin_1_string(".sim", 4);
  string__70_16 = from_latin_1_string(".meta", 5);
  string__70_42 = from_latin_1_string("-common", 7);
  string__70_46 = from_latin_1_string("-", 1);
  string__70_58 = from_latin_1_string("The platform \042", 14);
  string__70_59 = from_latin_1_string("\042 is not supported!", 19);
  func__70_1_add_module_infos = create_function(entry__70_1_add_module_infos, 2);
  func__71_1_lookup = create_function(entry__71_1_lookup, 2);
  func__72_1_CC = create_function(entry__72_1_CC, -1);
  func__73_2 = create_function(entry__73_2, 0);
  string__73_5 = from_latin_1_string("-c", 2);
  string__73_6 = from_latin_1_string("-o", 2);
  string__73_10 = from_latin_1_string("Failed to compile ", 18);
  string__73_11 = from_latin_1_string("\012", 1);
  func__73_1_compile_c = create_function(entry__73_1_compile_c, 2);
  string__74_9 = from_latin_1_string(".c", 2);
  string__74_46 = from_latin_1_string("/// ", 4);
  string__74_53 = from_latin_1_string("data", 4);
  string__74_56 = from_latin_1_string("./", 2);
  func__74_1_compile_meta_module = create_function(entry__74_1_compile_meta_module, 3);
  func__75_24 = create_function(entry__75_24, 0);
  func__75_23 = create_function(entry__75_23, 0);
  string__75_32 = from_latin_1_string("sim-", 4);
  string__75_39 = from_latin_1_string("require", 7);
  string__75_40 = from_latin_1_string("link", 4);
  func__75_1_build_dependencies = create_function(entry__75_1_build_dependencies, -1);
  func__76_9 = create_function(entry__76_9, 0);
  string__76_19 = from_latin_1_string("Failed to open file \042", 21);
  string__76_43 = from_latin_1_string("__", 2);
  string__76_48 = from_latin_1_string("build module ", 13);
  string__76_81 = from_latin_1_string("No source file(s) for module \042", 30);
  string__76_82 = from_latin_1_string("\042 found!", 8);
  string__76_85 = from_latin_1_string(".o", 2);
  string__76_136 = from_latin_1_string(" #", 2);
  func__76_1_compile_module = create_function(entry__76_1_compile_module, 2);
  func__77_1_compile_modules = create_function(entry__77_1_compile_modules, 2);
  string__79_3 = from_latin_1_string("LD_LIBRARY_PATH", 15);
  string__79_7 = from_latin_1_string("LD_LIBRARY_PATH=", 16);
  string__79_11 = from_latin_1_string("included object files: ", 23);
  string__79_14 = from_latin_1_string("needed libraries: ", 18);
  func__79_2 = create_function(entry__79_2, 0);
  func__79_1_show_file_list = create_function(entry__79_1_show_file_list, 0);
  string__80_8 = from_latin_1_string("-L", 2);
  string__80_14 = from_latin_1_string("library paths: ", 15);
  string__80_23 = from_latin_1_string("linux", 5);
  string__80_24 = from_latin_1_string("bsd", 3);
  string__80_27 = from_latin_1_string("-l:lib", 6);
  string__80_28 = from_latin_1_string(".so.", 4);
  string__80_31 = from_latin_1_string("-l", 2);
  func__80_1_library_paths_and_file_list = create_function(entry__80_1_library_paths_and_file_list, 0);
  string__81_26 = from_latin_1_string("typedef", 7);
  string__81_30 = from_latin_1_string("REGISTER", 8);
  string__81_44 = from_latin_1_string("typedef struct", 14);
  string__81_55 = from_latin_1_string("IMPORT ", 7);
  func__81_54 = create_function(entry__81_54, 0);
  string__81_65 = from_latin_1_string("// INSERT HERE //", 17);
  string__81_75 = from_latin_1_string("collecting imports", 18);
  func__81_74 = create_function(entry__81_74, 0);
  func__81_1_create_imports = create_function(entry__81_1_create_imports, 1);
  string__82_4 = from_latin_1_string("Expected a source code file!", 28);
  func__82_3 = create_function(entry__82_3, 0);
  string__82_8 = from_latin_1_string("Expected \042.sim\042 file extension in source filename!", 50);
  func__82_7 = create_function(entry__82_7, 0);
  func__82_1_compile_exe = create_function(entry__82_1_compile_exe, 1);
  func__83_2 = create_function(entry__83_2, 2);
  func__83_1_dump_source_or_check = create_function(entry__83_1_dump_source_or_check, 0);
  string__84_19 = from_latin_1_string("writing C-source", 16);
  func__84_18 = create_function(entry__84_18, 0);
  func__84_2 = create_function(entry__84_2, 2);
  func__84_1_print_c = create_function(entry__84_1_print_c, 0);
  func__85_3 = create_function(entry__85_3, 2);
  string__85_18 = from_latin_1_string("list dependencies for ", 22);
  func__85_17 = create_function(entry__85_17, 0);
  func__85_16 = create_function(entry__85_16, 0);
  func__85_24 = create_function(entry__85_24, 2);
  string__85_28 = from_latin_1_string("runtime/linker.c", 16);
  string__85_30 = from_latin_1_string("runtime/memory.c", 16);
  string__85_32 = from_latin_1_string("runtime/debugger.c", 18);
  func__85_23 = create_function(entry__85_23, 0);
  func__85_1_list_dependencies = create_function(entry__85_1_list_dependencies, 0);
  string__86_3 = from_latin_1_string(".codeblocks", 11);
  string__86_8 = from_latin_1_string("The directory \042", 15);
  string__86_9 = from_latin_1_string("\042 already exists!\012", 18);
  string__86_13 = from_latin_1_string("build Code::Blocks project in ", 30);
  string__86_23 = from_latin_1_string("../", 3);
  string__86_25 = from_latin_1_string("/", 1);
  string__86_26 = from_latin_1_string(".cbp", 4);
  string__86_29 = from_latin_1_string("<?xml version=\0421.0\042 encoding=\042UTF-8\042 standalone=\042yes\042 ?>\012<CodeBlocks_project_file>\012  <FileVersion major=\0421\042 minor=\0426\042 />\012  <Project>\012    <Option title=\042", 152);
  string__86_30 = from_latin_1_string("\042 />\012    <Option pch_mode=\0422\042 />\012    <Option compiler=c_compiler() />\012    <Build>\012      <Target title=\042debug\042>\012        <Option output=\042bin/debug/", 145);
  string__86_31 = from_latin_1_string("\042 prefix_auto=\0421\042 extension_auto=\0421\042 />\012        <Option object_output=\042obj/debug/\042 />\012        <Option type=\0421\042 />\012        <Option compiler=c_compiler() />\012        <Compiler>\012          <Add option=\042-g\042 />\012        </Compiler>\012      </Target>\012    </Build>\012    <Linker>\012", 266);
  string__86_35 = from_latin_1_string("      <Add library=\042", 20);
  string__86_36 = from_latin_1_string("\042 />\012", 5);
  string__86_43 = from_latin_1_string("\012    </Linker>\012    <Compiler>\012      <Add option=\042-Wall\042 />\012    </Compiler>\012    <Unit filename=\042", 95);
  string__86_44 = from_latin_1_string("runtime/common.h\042 />\012    <Unit filename=\042", 41);
  string__86_45 = from_latin_1_string("runtime/linker.h\042 />\012    <Unit filename=\042", 41);
  string__86_46 = from_latin_1_string("runtime/memory.c\042>\012      <Option compilerVar=\042", 46);
  string__86_47 = from_latin_1_string("\042 />\012    </Unit>\012    <Unit filename=\042", 37);
  string__86_48 = from_latin_1_string("runtime/debugger.c\042>\012      <Option compilerVar=\042", 48);
  string__86_49 = from_latin_1_string("runtime/linker.c\042>\012      <Option compilerVar=\042", 46);
  string__86_50 = from_latin_1_string("\042 />\012    </Unit>\012", 17);
  string__86_57 = from_latin_1_string("\012    <Unit filename=\042", 21);
  string__86_58 = from_latin_1_string("\042>\012      <Option compilerVar=\042", 30);
  string__86_62 = from_latin_1_string("    <Extensions>\012      <code_completion />\012      <debugger />\012    </Extensions>\012  </Project>\012</CodeBlocks_project_file>\012", 120);
  func__86_2 = create_function(entry__86_2, 2);
  func__86_1_build_codeblocks_project = create_function(entry__86_1_build_codeblocks_project, 0);
  string__87_2 = from_latin_1_string("simrun", 6);
  string__87_5 = from_latin_1_string("Cannot run a directory!", 23);
  func__87_4 = create_function(entry__87_4, 0);
  func__87_7 = create_function(entry__87_7, 0);
  string__87_9 = from_latin_1_string("/VERSION", 8);
  string__87_24 = from_latin_1_string("libsim-", 7);
  string__87_27 = from_latin_1_string(".dll", 4);
  string__87_31 = from_latin_1_string(".dylib", 6);
  string__87_37 = from_latin_1_string("cygwin", 6);
  string__87_38 = from_latin_1_string("darwin", 6);
  string__87_41 = from_latin_1_string("build library ", 14);
  func__87_53 = create_function(entry__87_53, 0);
  string__87_57 = from_latin_1_string("linking dynamic library", 23);
  func__87_56 = create_function(entry__87_56, 0);
  string__87_62 = from_latin_1_string("-Wl,-soname,libsim-", 19);
  string__87_65 = from_latin_1_string("-shared", 7);
  string__87_71 = from_latin_1_string("-lsim-", 6);
  string__87_77 = from_latin_1_string("-Wl,-install_name,libsim-", 25);
  string__87_81 = from_latin_1_string("-dynamiclib", 11);
  func__87_8 = create_function(entry__87_8, 0);
  func__87_1_build_library = create_function(entry__87_1_build_library, 0);
  string__88_7 = from_latin_1_string("\042", 1);
  string__88_8 = from_latin_1_string("\042 does not exist!\012", 18);
  string__88_20 = from_latin_1_string("compiling runtime module ", 25);
  func__88_1_maybe_compile_c_file = create_function(entry__88_1_maybe_compile_c_file, 1);
  string__90_14 = from_latin_1_string(" ", 1);
  string__90_23 = from_latin_1_string("0", 1);
  func__90_1_format_number = create_function(entry__90_1_format_number, -1);
  string__91_12 = from_latin_1_string(" s", 2);
  string__91_16 = from_latin_1_string(": ", 2);
  func__91_1_sim2c__write_timing_info = create_function(entry__91_1_sim2c__write_timing_info, -1);
  string__92_6 = from_latin_1_string(".exe", 4);
  string__92_11 = from_latin_1_string("build executable ", 17);
  string__92_30 = from_latin_1_string("build main module ", 18);
  func__92_29 = create_function(entry__92_29, 0);
  func__92_32 = create_function(entry__92_32, 0);
  string__92_40 = from_latin_1_string("saving", 6);
  string__92_44 = from_latin_1_string("compiling", 9);
  string__92_61 = from_latin_1_string("runtime/linker", 14);
  string__92_62 = from_latin_1_string("runtime/memory", 14);
  string__92_63 = from_latin_1_string("runtime/debugger", 16);
  func__92_65 = create_function(entry__92_65, 1);
  func__92_60 = create_function(entry__92_60, 0);
  func__92_77 = create_function(entry__92_77, 0);
  string__92_82 = from_latin_1_string("/usr/lib/libprofiler.so.0", 25);
  string__92_87 = from_latin_1_string("linking static executable", 25);
  func__92_86 = create_function(entry__92_86, 0);
  string__92_89 = from_latin_1_string("runtime/linker.o", 16);
  string__92_90 = from_latin_1_string("runtime/memory.o", 16);
  string__92_91 = from_latin_1_string("runtime/debugger.o", 18);
  string__92_97 = from_latin_1_string("linking executable", 18);
  func__92_96 = create_function(entry__92_96, 0);
  string__92_102 = from_latin_1_string("-l:libsim.so.", 13);
  func__92_101 = create_function(entry__92_101, 0);
  func__92_104 = create_function(entry__92_104, 0);
  func__92_113 = create_function(entry__92_113, 0);
  func__92_2 = create_function(entry__92_2, 2);
  func__92_1_build_executable = create_function(entry__92_1_build_executable, 0);
  string__96_1 = from_latin_1_string("Copyright (C) 2020 by\012Dipl.-Ing. Michael Niederle\012\012This program is free software; you can redistribute it and/or modify\012it under the terms of the GNU General Public License, version 2, or\012(at your option) version 3.\012\012This program is distributed in the hope that it will be useful,\012but WITHOUT ANY WARRANTY; without even the implied warranty of\012MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the\012GNU General Public License for more details.\012\012For details of the GNU General Public License see the accompanying\012files GPLv2.txt and GLPv3.txt or\012http://www.gnu.org/licenses/gpl-2.0.html\012http://www.gnu.org/licenses/gpl-3.0.html\012or write to the\012Free Software Foundation, Inc.,\01251 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.\012", 742);
  string__100_1 = from_latin_1_string(".", 1);
  string__103_1 = from_latin_1_string("mkdir", 5);
  string__104_1 = from_latin_1_string("SIMLIBPATH", 10);
  string__105_1 = from_latin_1_string("SIMDATAPATH", 11);
  func__106_2 = create_function(entry__106_2, 0);
  string__106_5 = from_latin_1_string("/usr/local/share/simplicity-", 28);
  string__106_7 = from_latin_1_string("/usr/share/simplicity-", 22);
  func__106_4 = create_function(entry__106_4, 0);
  func__107_2 = create_function(entry__107_2, 0);
  func__107_4 = create_function(entry__107_4, 0);
  string__109_1 = from_latin_1_string("posix", 5);
  string__109_6 = from_latin_1_string("all", 3);
  string__109_8 = from_latin_1_string("win", 3);
  func__111_1 = create_function(entry__111_1, 0);
  string__138_5 = from_latin_1_string("Missing command line arguments!", 31);
  func__138_4 = create_function(entry__138_4, 0);
  func__138_2 = create_function(entry__138_2, 0);
  string__138_10 = from_latin_1_string("check-only", 10);
  string__138_11 = from_latin_1_string("do not compile; just check for syntax errors\012", 45);
  func__138_9 = create_function(entry__138_9, 0);
  string__138_13 = from_latin_1_string("dump-trees", 10);
  string__138_14 = from_latin_1_string("dump abstract syntax trees\012", 27);
  func__138_12 = create_function(entry__138_12, 0);
  string__138_16 = from_latin_1_string("pretty-print", 12);
  string__138_17 = from_latin_1_string("do not compile; just pretty print the source file\012", 50);
  func__138_15 = create_function(entry__138_15, 0);
  string__138_19 = from_latin_1_string("print-simplified-source", 23);
  string__138_20 = from_latin_1_string("do not generate a C-file; just print the simplified source text\012", 64);
  func__138_18 = create_function(entry__138_18, 0);
  string__138_22 = from_latin_1_string("print-c", 7);
  string__138_23 = from_latin_1_string("print C source code for a single module\012", 40);
  func__138_21 = create_function(entry__138_21, 0);
  string__138_25 = from_latin_1_string("time-passes", 11);
  string__138_26 = from_latin_1_string("print running time for the individual compiler passes\012", 54);
  func__138_24 = create_function(entry__138_24, 0);
  string__138_28 = from_latin_1_string("module-prefix", 13);
  string__138_29 = from_latin_1_string("needed to compile a single file within a subdirectory;\012if the subdirectories are nested use slashes to separate\012the directory names\012", 132);
  func__138_27 = create_function(entry__138_27, 0);
  string__138_31 = from_latin_1_string("brief", 5);
  string__138_32 = from_latin_1_string("show brief error messages\012", 26);
  func__138_30 = create_function(entry__138_30, 0);
  string__138_34 = from_latin_1_string("warnings", 8);
  string__138_35 = from_latin_1_string("show warning messages\012", 22);
  func__138_33 = create_function(entry__138_33, 0);
  string__138_37 = from_latin_1_string("missing", 7);
  string__138_38 = from_latin_1_string("inform about missing documentation\012", 35);
  func__138_36 = create_function(entry__138_36, 0);
  string__138_40 = from_latin_1_string("summary", 7);
  string__138_41 = from_latin_1_string("show a statistical summary\012", 27);
  func__138_39 = create_function(entry__138_39, 0);
  string__138_43 = from_latin_1_string("verbose", 7);
  string__138_44 = from_latin_1_string("output verbose informations\012", 28);
  func__138_42 = create_function(entry__138_42, 0);
  string__138_46 = from_latin_1_string("debug", 5);
  string__138_47 = from_latin_1_string("show C-compiler and linker calls\012", 33);
  func__138_45 = create_function(entry__138_45, 0);
  string__138_49 = from_latin_1_string("debug_compiler", 14);
  string__138_50 = from_latin_1_string("show internal debug messages of the Simplicity compiler\012", 56);
  func__138_48 = create_function(entry__138_48, 0);
  string__138_52 = from_latin_1_string("codeblocks", 10);
  string__138_53 = from_latin_1_string("create Code::Blocks project\012", 28);
  func__138_51 = create_function(entry__138_51, 0);
  string__138_55 = from_latin_1_string("extract-documentation", 21);
  string__138_56 = from_latin_1_string("extract documentation encoded as HTML\012", 38);
  func__138_54 = create_function(entry__138_54, 0);
  string__138_58 = from_latin_1_string("list-dependencies", 17);
  string__138_59 = from_latin_1_string("list all dependencies\012", 22);
  func__138_57 = create_function(entry__138_57, 0);
  string__138_61 = from_latin_1_string("rebuild", 7);
  string__138_62 = from_latin_1_string("rebuild all source files\012", 25);
  func__138_60 = create_function(entry__138_60, 0);
  string__138_64 = from_latin_1_string("omit-meta", 9);
  string__138_65 = from_latin_1_string("do not rebuild meta files\012", 26);
  func__138_63 = create_function(entry__138_63, 0);
  string__138_67 = from_latin_1_string("static", 6);
  string__138_68 = from_latin_1_string("create statically linked executable\012", 36);
  func__138_66 = create_function(entry__138_66, 0);
  string__138_70 = from_latin_1_string("profile", 7);
  string__138_71 = from_latin_1_string("link with libprofiler\012", 22);
  func__138_69 = create_function(entry__138_69, 0);
  string__138_73 = from_latin_1_string("filename", 8);
  string__138_74 = from_latin_1_string("the name of the source file to compile\012", 39);
  func__138_72 = create_function(entry__138_72, 0);
  func__138_8 = create_function(entry__138_8, 0);
  func__142_1 = create_function(entry__142_1, 0);
  string__148_1 = from_latin_1_string("-Wall", 5);
  string__148_2 = from_latin_1_string("-Wno-unused-function", 20);
  string__148_3 = from_latin_1_string("-Wno-unused-variable", 20);
  string__148_4 = from_latin_1_string("-Wno-parentheses", 16);
  string__148_5 = from_latin_1_string("-Wno-switch", 11);
  string__148_6 = from_latin_1_string("-Wno-trigraphs", 14);
  string__148_7 = from_latin_1_string("-O1", 3);
  string__148_8 = from_latin_1_string("-fPIC", 5);
  string__148_9 = from_latin_1_string("-fno-stack-protector", 20);
  string__148_10 = from_latin_1_string("-falign-functions=16", 20);
  string__149_2 = from_latin_1_string("gcc", 3);
  string__149_5 = from_latin_1_string("-Wno-maybe-uninitialized", 24);
  func__149_4 = create_function(entry__149_4, 0);
  string__150_2 = from_latin_1_string("x86_32", 6);
  string__150_3 = from_latin_1_string("x86_64", 6);
  string__150_6 = from_latin_1_string("-msse2", 6);
  string__150_8 = from_latin_1_string("-mfpmath=sse", 12);
  func__150_5 = create_function(entry__150_5, 0);
  string__151_2 = from_latin_1_string("-I", 2);
  func__151_1 = create_function(entry__151_1, 1);
  func__153_3 = create_function(entry__153_3, 1);
  func__155_3 = create_function(entry__155_3, 1);
  string__173_3 = from_latin_1_string("Source file \042", 13);
  string__173_4 = from_latin_1_string("\042 does not exist!", 17);
  func__173_2 = create_function(entry__173_2, 0);
  func__188_1 = create_function(entry__188_1, 0);
  func__189_4 = create_function(entry__189_4, 0);
  func__189_3 = create_function(entry__189_3, 0);
  func__189_2 = create_function(entry__189_2, 0);
  func__189_1 = create_function(entry__189_1, 0);
  func__189_8 = create_function(entry__189_8, 0);
  func__189_9 = create_function(entry__189_9, 0);
  func__189_10 = create_function(entry__189_10, 0);
  func__189_11 = create_function(entry__189_11, 0);

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
  define_multi_assign_static("sim2c", "do_print_missing", get__sim2c__do_print_missing, set__sim2c__do_print_missing);
  define_multi_assign_static("sim2c", "do_print_summary", get__sim2c__do_print_summary, set__sim2c__do_print_summary);
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
  use_read_only(NULL, "CPPFLAGS", &get__CPPFLAGS, &get_value_or_future__CPPFLAGS);
  use_read_only(NULL, "Error", &get__Error, &get_value_or_future__Error);
  use_read_only(NULL, "LDFLAGS", &get__LDFLAGS, &get_value_or_future__LDFLAGS);
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
  assign_variable(&var.sim2c__show_compiler_debug_info, &func__48_1_sim2c__show_compiler_debug_info);
  maybe_initialize_future(get__mode(), get__undefined());
  maybe_initialize_future(get__on_top_level(), get__true());
  assign_variable(&var._resolve_filename, &func__69_1_resolve_filename);
  assign_variable(&var._add_module_infos, &func__70_1_add_module_infos);
  assign_variable(&var._lookup, &func__71_1_lookup);
  assign_variable(&var._CC, &func__72_1_CC);
  assign_variable(&var._compile_c, &func__73_1_compile_c);
  assign_variable(&var._compile_meta_module, &func__74_1_compile_meta_module);
  assign_variable(&var._build_dependencies, &func__75_1_build_dependencies);
  assign_variable(&var._compile_module, &func__76_1_compile_module);
  assign_variable(&var._compile_modules, &func__77_1_compile_modules);
  assign_variable(&var._show_file_list, &func__79_1_show_file_list);
  assign_variable(&var._library_paths_and_file_list, &func__80_1_library_paths_and_file_list);
  assign_variable(&var._create_imports, &func__81_1_create_imports);
  assign_variable(&var._compile_exe, &func__82_1_compile_exe);
  assign_variable(&var._dump_source_or_check, &func__83_1_dump_source_or_check);
  assign_variable(&var._print_c, &func__84_1_print_c);
  assign_variable(&var._list_dependencies, &func__85_1_list_dependencies);
  assign_variable(&var._build_codeblocks_project, &func__86_1_build_codeblocks_project);
  assign_variable(&var._build_library, &func__87_1_build_library);
  assign_variable(&var._maybe_compile_c_file, &func__88_1_maybe_compile_c_file);
  assign_variable(&var._format_number, &func__90_1_format_number);
  assign_variable(&var.sim2c__write_timing_info, &func__91_1_sim2c__write_timing_info);
  assign_variable(&var._build_executable, &func__92_1_build_executable);
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
