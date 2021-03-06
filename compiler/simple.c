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
IMPORT int runtime_patch_version(void);
IMPORT void invalid_arguments_error(void);
IMPORT NODE *empty_string;
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
IMPORT NODE *collect_node(NODE *node);
IMPORT int main_argc;
IMPORT char **main_argv;
IMPORT void initialize_runtime(void);
IMPORT void register_module_info(MODULE_INFO *info);
IMPORT void define_namespace(const char *namespace);
IMPORT void set_module(const char *name);
IMPORT NODE *from_uchar32(unsigned int chr);
IMPORT NODE *from_uint32(uint32_t val);
IMPORT NODE *create_function(FUNC func, int par_count);
IMPORT NODE *from_latin_1_string(const char *str, long len);
IMPORT NODE *register_unique_item(const char *name);
IMPORT void initialize_phase_3(void);
IMPORT void resolve_symbols(void);
IMPORT void set_used_namespaces(const char **namespaces);
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
IMPORT void use_single_assign_dynamic(
  const char *namespace, const char *name,
  NODE_GETTER *getter, NODE_SETTER *definer
);
IMPORT void use_read_write(
  const char *namespace, const char *name,
  NODE_GETTER *getter, NODE_SETTER *setter
);
IMPORT void resolve_attributes(void);
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
static NODE_GETTER get__PACKAGE_VERSION;
static NODE_GETTER get_value_or_future__PACKAGE_VERSION;
static NODE_GETTER get__PREFIX;
static NODE_GETTER get_value_or_future__PREFIX;
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
static NODE_GETTER get__compiler__module_name;
static NODE_SETTER define__compiler__module_name;
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
static NODE_GETTER get__extract_exports;
static NODE_GETTER get_value_or_future__extract_exports;
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
static NODE_GETTER get__runtime_patch_version;
static NODE_GETTER get_value_or_future__runtime_patch_version;
static NODE_GETTER get__runtime_symbols;
static NODE_GETTER get_value_or_future__runtime_symbols;
static NODE_GETTER get__save;
static NODE_GETTER get_value_or_future__save;
static NODE_GETTER get__serialize;
static NODE_GETTER get_value_or_future__serialize;
static NODE_GETTER get__sim2c;
static NODE_GETTER get_value_or_future__sim2c;
static NODE_GETTER get__some;
static NODE_GETTER get_value_or_future__some;
static NODE_GETTER get__split;
static NODE_GETTER get_value_or_future__split;
static NODE_GETTER get__stat;
static NODE_GETTER get_value_or_future__stat;
static NODE_GETTER get__std__MANDATORY_PARAMETER;
static NODE_GETTER get_value_or_future__std__MANDATORY_PARAMETER;
static NODE_GETTER get__std__SOME_PARAMETERS;
static NODE_GETTER get_value_or_future__std__SOME_PARAMETERS;
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
  NODE *_PATCH;
  NODE *_VERSION;
  NODE *_cc;
  NODE *_mkdir;
  NODE *_SIMLIBPATH;
  NODE *_SIMDATAPATH;
  NODE *_default_paths;
  NODE *_simlibpaths;
  NODE *_simdatapaths;
  NODE *_supported_platforms;
  NODE *_platform_priority;
  NODE *_platform_specific_priority;
  NODE *_module_info;
  NODE *_meta_levels;
  NODE *_do_rebuild;
  NODE *_do_omit_meta;
  NODE *_do_print_c;
  NODE *_do_extract_exports;
  NODE *_do_build_codeblocks_project;
  NODE *_do_list_dependencies;
  NODE *_do_build_static;
  NODE *_do_link_profiler;
  NODE *_module_prefix;
  NODE *_input_filename;
  NODE *_additional_libraries;
  NODE *_action;
  NODE *_WHITESPACE;
  NODE *_cc_options;
  NODE *_cpp_options;
  NODE *_ld_options;
  NODE *_c_sources;
  NODE *_dependencies;
  NODE *_resolved_libraries;
  NODE *_t;
  NODE *compiler__do_dump_trees;
  NODE *compiler__do_pretty_print;
  NODE *compiler__do_convert;
  NODE *compiler__do_print_simplified_source;
  NODE *compiler__do_show_debug_infos;
  NODE *compiler__do_show_compiler_debug_infos;
  NODE *compiler__do_check_only;
  NODE *compiler__do_show_brief_messages;
  NODE *compiler__do_print_warnings;
  NODE *compiler__do_print_missing;
  NODE *compiler__do_print_summary;
  NODE *compiler__verbose;
  NODE *compiler__do_extract_documentation;
  NODE *compiler__do_time_passes;
  NODE *compiler__show_compiler_debug_info;
  NODE *compiler__write_timing_info;
} var;
static const char *var_names[] = {
  "MAJOR",
  "MINOR",
  "PATCH",
  "VERSION",
  "cc",
  "mkdir",
  "SIMLIBPATH",
  "SIMDATAPATH",
  "default_paths",
  "simlibpaths",
  "simdatapaths",
  "supported_platforms",
  "platform_priority",
  "platform_specific_priority",
  "module_info",
  "meta_levels",
  "do_rebuild",
  "do_omit_meta",
  "do_print_c",
  "do_extract_exports",
  "do_build_codeblocks_project",
  "do_list_dependencies",
  "do_build_static",
  "do_link_profiler",
  "module_prefix",
  "input_filename",
  "additional_libraries",
  "action",
  "WHITESPACE",
  "cc_options",
  "cpp_options",
  "ld_options",
  "c_sources",
  "dependencies",
  "resolved_libraries",
  "t"
};
static NODE *get__compiler__do_dump_trees(void) {
  return var.compiler__do_dump_trees;
}
static void set__compiler__do_dump_trees(NODE *val) {
  var.compiler__do_dump_trees = val;
}
static NODE *get__compiler__do_pretty_print(void) {
  return var.compiler__do_pretty_print;
}
static void set__compiler__do_pretty_print(NODE *val) {
  var.compiler__do_pretty_print = val;
}
static NODE *get__compiler__do_convert(void) {
  return var.compiler__do_convert;
}
static void set__compiler__do_convert(NODE *val) {
  var.compiler__do_convert = val;
}
static NODE *get__compiler__do_print_simplified_source(void) {
  return var.compiler__do_print_simplified_source;
}
static void set__compiler__do_print_simplified_source(NODE *val) {
  var.compiler__do_print_simplified_source = val;
}
static NODE *get__compiler__do_show_debug_infos(void) {
  return var.compiler__do_show_debug_infos;
}
static void set__compiler__do_show_debug_infos(NODE *val) {
  var.compiler__do_show_debug_infos = val;
}
static NODE *get__compiler__do_show_compiler_debug_infos(void) {
  return var.compiler__do_show_compiler_debug_infos;
}
static void set__compiler__do_show_compiler_debug_infos(NODE *val) {
  var.compiler__do_show_compiler_debug_infos = val;
}
static NODE *get__compiler__do_check_only(void) {
  return var.compiler__do_check_only;
}
static void set__compiler__do_check_only(NODE *val) {
  var.compiler__do_check_only = val;
}
static NODE *get__compiler__do_show_brief_messages(void) {
  return var.compiler__do_show_brief_messages;
}
static void set__compiler__do_show_brief_messages(NODE *val) {
  var.compiler__do_show_brief_messages = val;
}
static NODE *get__compiler__do_print_warnings(void) {
  return var.compiler__do_print_warnings;
}
static void set__compiler__do_print_warnings(NODE *val) {
  var.compiler__do_print_warnings = val;
}
static NODE *get__compiler__do_print_missing(void) {
  return var.compiler__do_print_missing;
}
static void set__compiler__do_print_missing(NODE *val) {
  var.compiler__do_print_missing = val;
}
static NODE *get__compiler__do_print_summary(void) {
  return var.compiler__do_print_summary;
}
static void set__compiler__do_print_summary(NODE *val) {
  var.compiler__do_print_summary = val;
}
static NODE *get__compiler__verbose(void) {
  return var.compiler__verbose;
}
static void set__compiler__verbose(NODE *val) {
  var.compiler__verbose = val;
}
static NODE *get__compiler__do_extract_documentation(void) {
  return var.compiler__do_extract_documentation;
}
static void set__compiler__do_extract_documentation(NODE *val) {
  var.compiler__do_extract_documentation = val;
}
static NODE *get__compiler__do_time_passes(void) {
  return var.compiler__do_time_passes;
}
static void set__compiler__do_time_passes(NODE *val) {
  var.compiler__do_time_passes = val;
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
static NODE *func__compiler__show_compiler_debug_info;
static void entry__compiler__show_compiler_debug_info(void);
static FRAME_INFO frame__compiler__show_compiler_debug_info = {1, {"args"}};
static NODE *func__compiler__show_compiler_debug_info_2;
static void entry__compiler__show_compiler_debug_info_2(void);
static FRAME_INFO frame__compiler__show_compiler_debug_info_2 = {1, {"args"}};
static NODE *get__compiler__show_compiler_debug_info(void) {
  return var.compiler__show_compiler_debug_info;
}
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
static NODE *func__resolve_filename;
static void entry__resolve_filename(void);
static FRAME_INFO frame__resolve_filename = {3, {"filename", "libname", "libpath"}};
static void cont__resolve_filename_2(void);
static NODE *func__resolve_filename_3;
static void entry__resolve_filename_3(void);
static FRAME_INFO frame__resolve_filename_3 = {0, {}};
static NODE *func__resolve_filename_4;
static void entry__resolve_filename_4(void);
static FRAME_INFO frame__resolve_filename_4 = {1, {"path"}};
static void cont__resolve_filename_5(void);
static NODE *func__resolve_filename_6;
static void entry__resolve_filename_6(void);
static FRAME_INFO frame__resolve_filename_6 = {1, {"path"}};
static void cont__resolve_filename_7(void);
static NODE *func__resolve_filename_8;
static void entry__resolve_filename_8(void);
static FRAME_INFO frame__resolve_filename_8 = {1, {"entry"}};
static void cont__resolve_filename_9(void);
static NODE *func__resolve_filename_10;
static void entry__resolve_filename_10(void);
static FRAME_INFO frame__resolve_filename_10 = {2, {"entry", "name"}};
static void cont__resolve_filename_11(void);
static void cont__resolve_filename_12(void);
static NODE *func__resolve_filename_13;
static void entry__resolve_filename_13(void);
static FRAME_INFO frame__resolve_filename_13 = {2, {"name", "entry"}};
static void cont__resolve_filename_14(void);
static void cont__resolve_filename_15(void);
static void cont__resolve_filename_16(void);
static void cont__resolve_filename_17(void);
static void cont__resolve_filename_18(void);
static void cont__resolve_filename_19(void);
static NODE *func__resolve_filename_20;
static void entry__resolve_filename_20(void);
static FRAME_INFO frame__resolve_filename_20 = {1, {"libname"}};
static NODE *string__373a794ad67f2aca;
static NODE *string__2d7981f4e6182be4;
static void cont__resolve_filename_23(void);
static void cont__resolve_filename_24(void);
static void cont__resolve_filename_25(void);
static void cont__resolve_filename_26(void);
static NODE *func__add_module_infos;
static void entry__add_module_infos(void);
static FRAME_INFO frame__add_module_infos = {7, {"path", "mod_path", "return", "entries", "filenames", "directories", "modules"}};
static void cont__add_module_infos_2(void);
static void cont__add_module_infos_3(void);
static NODE *func__add_module_infos_4;
static void entry__add_module_infos_4(void);
static FRAME_INFO frame__add_module_infos_4 = {6, {"entry", "directories", "filenames", "modules", "mod_path", "name"}};
static void cont__add_module_infos_5(void);
static NODE *func__add_module_infos_6;
static void entry__add_module_infos_6(void);
static FRAME_INFO frame__add_module_infos_6 = {3, {"entry", "name", "directories"}};
static void cont__add_module_infos_7(void);
static NODE *func__add_module_infos_8;
static void entry__add_module_infos_8(void);
static FRAME_INFO frame__add_module_infos_8 = {2, {"name", "directories"}};
static void cont__add_module_infos_9(void);
static NODE *func__add_module_infos_10;
static void entry__add_module_infos_10(void);
static FRAME_INFO frame__add_module_infos_10 = {2, {"directories", "name"}};
static void cont__add_module_infos_11(void);
static NODE *func__add_module_infos_12;
static void entry__add_module_infos_12(void);
static FRAME_INFO frame__add_module_infos_12 = {4, {"name", "filenames", "modules", "mod_path"}};
static NODE *string__9e0aed8b5d287d54;
static void cont__add_module_infos_14(void);
static NODE *func__add_module_infos_15;
static void entry__add_module_infos_15(void);
static FRAME_INFO frame__add_module_infos_15 = {9, {"name", "filenames", "modules", "mod_path", "submodule_name", "meta_level", "stored_level", "basename", "mod_name"}};
static NODE *string__505aea43ea6cf036;
static void cont__add_module_infos_17(void);
static void cont__add_module_infos_18(void);
static void cont__add_module_infos_19(void);
static void cont__add_module_infos_20(void);
static void cont__add_module_infos_21(void);
static void cont__add_module_infos_22(void);
static void cont__add_module_infos_23(void);
static void cont__add_module_infos_24(void);
static void cont__add_module_infos_25(void);
static void cont__add_module_infos_26(void);
static void cont__add_module_infos_27(void);
static NODE *func__add_module_infos_28;
static void entry__add_module_infos_28(void);
static FRAME_INFO frame__add_module_infos_28 = {2, {"stored_level", "meta_level"}};
static void cont__add_module_infos_29(void);
static void cont__add_module_infos_30(void);
static NODE *func__add_module_infos_31;
static void entry__add_module_infos_31(void);
static FRAME_INFO frame__add_module_infos_31 = {2, {"submodule_name", "meta_level"}};
static void cont__add_module_infos_32(void);
static void cont__add_module_infos_33(void);
static void cont__add_module_infos_34(void);
static void cont__add_module_infos_35(void);
static void cont__add_module_infos_36(void);
static void cont__add_module_infos_37(void);
static void cont__add_module_infos_38(void);
static NODE *func__add_module_infos_39;
static void entry__add_module_infos_39(void);
static FRAME_INFO frame__add_module_infos_39 = {3, {"filename", "filenames", "mod_path"}};
static void cont__add_module_infos_40(void);
static NODE *func__add_module_infos_41;
static void entry__add_module_infos_41(void);
static FRAME_INFO frame__add_module_infos_41 = {3, {"filename", "filenames", "mod_path"}};
static NODE *string__a9300e9315c23094;
static void cont__add_module_infos_43(void);
static NODE *func__add_module_infos_44;
static void entry__add_module_infos_44(void);
static FRAME_INFO frame__add_module_infos_44 = {9, {"filenames", "filename", "mod_path", "maybe_push_common", "name", "mod_name", "platform", "parent", "files"}};
static NODE *func__add_module_infos_45;
static void entry__add_module_infos_45(void);
static FRAME_INFO frame__add_module_infos_45 = {5, {"plat", "name", "filenames", "files", "common_name"}};
static NODE *string__578a5af303e9ccc;
static void cont__add_module_infos_47(void);
static void cont__add_module_infos_48(void);
static NODE *func__add_module_infos_49;
static void entry__add_module_infos_49(void);
static FRAME_INFO frame__add_module_infos_49 = {2, {"files", "common_name"}};
static void cont__add_module_infos_50(void);
static void cont__add_module_infos_51(void);
static void cont__add_module_infos_52(void);
static void cont__add_module_infos_53(void);
static void cont__add_module_infos_54(void);
static void cont__add_module_infos_55(void);
static void cont__add_module_infos_56(void);
static NODE *func__add_module_infos_57;
static void entry__add_module_infos_57(void);
static FRAME_INFO frame__add_module_infos_57 = {1, {"platform"}};
static NODE *string__bf5121a1ba54e344;
static NODE *string__b566882ea60ef100;
static void cont__add_module_infos_60(void);
static void cont__add_module_infos_61(void);
static void cont__add_module_infos_62(void);
static void cont__add_module_infos_63(void);
static NODE *func__add_module_infos_64;
static void entry__add_module_infos_64(void);
static FRAME_INFO frame__add_module_infos_64 = {2, {"parent", "maybe_push_common"}};
static NODE *unique__NONE;
static void cont__add_module_infos_65(void);
static void cont__add_module_infos_66(void);
static NODE *func__add_module_infos_67;
static void entry__add_module_infos_67(void);
static FRAME_INFO frame__add_module_infos_67 = {2, {"maybe_push_common", "parent"}};
static void cont__add_module_infos_68(void);
static void cont__add_module_infos_69(void);
static void cont__add_module_infos_70(void);
static void cont__add_module_infos_71(void);
static void cont__add_module_infos_72(void);
static void cont__add_module_infos_73(void);
static void cont__add_module_infos_74(void);
static void cont__add_module_infos_75(void);
static void cont__add_module_infos_76(void);
static NODE *func__add_module_infos_77;
static void entry__add_module_infos_77(void);
static FRAME_INFO frame__add_module_infos_77 = {3, {"return", "directories", "modules"}};
static void cont__add_module_infos_78(void);
static NODE *func__lookup;
static void entry__lookup(void);
static FRAME_INFO frame__lookup = {3, {"mod_filename", "mod_name", "info"}};
static void cont__lookup_2(void);
static void cont__lookup_3(void);
static NODE *func__lookup_4;
static void entry__lookup_4(void);
static FRAME_INFO frame__lookup_4 = {1, {"info"}};
static NODE *func__lookup_5;
static void entry__lookup_5(void);
static FRAME_INFO frame__lookup_5 = {2, {"mod_filename", "mod_name"}};
static void cont__lookup_6(void);
static void cont__lookup_7(void);
static void cont__lookup_8(void);
static void cont__lookup_9(void);
static void cont__lookup_10(void);
static void cont__lookup_11(void);
static NODE *func__CC;
static void entry__CC(void);
static FRAME_INFO frame__CC = {1, {"args"}};
static NODE *func__CC_2;
static void entry__CC_2(void);
static FRAME_INFO frame__CC_2 = {1, {"args"}};
static void cont__CC_3(void);
static void cont__CC_4(void);
static void cont__CC_5(void);
static NODE *func__compile_c;
static void entry__compile_c(void);
static FRAME_INFO frame__compile_c = {2, {"c_filename", "o_filename"}};
static NODE *func__compile_c_2;
static void entry__compile_c_2(void);
static FRAME_INFO frame__compile_c_2 = {0, {}};
static void cont__compile_c_3(void);
static NODE *func__compile_c_4;
static void entry__compile_c_4(void);
static FRAME_INFO frame__compile_c_4 = {5, {"c_filename", "o_filename", "out", "err", "success"}};
static NODE *string__2d7981f4e6602ba6;
static NODE *string__2d7981f4e6602baa;
static void cont__compile_c_7(void);
static NODE *func__compile_c_8;
static void entry__compile_c_8(void);
static FRAME_INFO frame__compile_c_8 = {2, {"c_filename", "err"}};
static void cont__compile_c_9(void);
static NODE *string__ca9b4802029a5965;
static NODE *string__578a5af303e9ceb;
static void cont__compile_c_12(void);
static void cont__compile_c_13(void);
static NODE *func__compile_meta_module;
static void entry__compile_meta_module(void);
static FRAME_INFO frame__compile_meta_module = {3, {"mod_filename", "mod_name", "meta_level"}};
static NODE *func__compile_meta_module_2;
static void entry__compile_meta_module_2(void);
static FRAME_INFO frame__compile_meta_module_2 = {11, {"mod_filename", "meta_level", "meta_path", "filename", "meta_filename", "meta_c_filename", "sim_filename", "meta_info", "sim_info", "meta_c_info", "force_rebuild"}};
static void cont__compile_meta_module_3(void);
static void cont__compile_meta_module_4(void);
static void cont__compile_meta_module_5(void);
static void cont__compile_meta_module_6(void);
static void cont__compile_meta_module_7(void);
static void cont__compile_meta_module_8(void);
static NODE *string__2d7981f4e6782ba6;
static void cont__compile_meta_module_10(void);
static void cont__compile_meta_module_11(void);
static void cont__compile_meta_module_12(void);
static void cont__compile_meta_module_13(void);
static void cont__compile_meta_module_14(void);
static void cont__compile_meta_module_15(void);
static void cont__compile_meta_module_16(void);
static NODE *func__compile_meta_module_17;
static void entry__compile_meta_module_17(void);
static FRAME_INFO frame__compile_meta_module_17 = {3, {"sim_info", "meta_c_info", "meta_info"}};
static void cont__compile_meta_module_18(void);
static NODE *func__compile_meta_module_19;
static void entry__compile_meta_module_19(void);
static FRAME_INFO frame__compile_meta_module_19 = {3, {"meta_c_info", "meta_info", "sim_info"}};
static void cont__compile_meta_module_20(void);
static NODE *func__compile_meta_module_21;
static void entry__compile_meta_module_21(void);
static FRAME_INFO frame__compile_meta_module_21 = {3, {"meta_c_info", "meta_info", "sim_info"}};
static void cont__compile_meta_module_22(void);
static void cont__compile_meta_module_23(void);
static void cont__compile_meta_module_24(void);
static NODE *func__compile_meta_module_25;
static void entry__compile_meta_module_25(void);
static FRAME_INFO frame__compile_meta_module_25 = {2, {"sim_info", "meta_c_info"}};
static void cont__compile_meta_module_26(void);
static void cont__compile_meta_module_27(void);
static void cont__compile_meta_module_28(void);
static void cont__compile_meta_module_29(void);
static void cont__compile_meta_module_30(void);
static void cont__compile_meta_module_31(void);
static void cont__compile_meta_module_32(void);
static NODE *func__compile_meta_module_33;
static void entry__compile_meta_module_33(void);
static FRAME_INFO frame__compile_meta_module_33 = {6, {"sim_info", "meta_c_filename", "force_rebuild", "meta_path", "modification_time", "meta_c_buf"}};
static void cont__compile_meta_module_34(void);
static void cont__compile_meta_module_35(void);
static NODE *func__compile_meta_module_36;
static void entry__compile_meta_module_36(void);
static FRAME_INFO frame__compile_meta_module_36 = {5, {"break", "meta_c_buf", "modification_time", "force_rebuild", "meta_path"}};
static NODE *func__compile_meta_module_37;
static void entry__compile_meta_module_37(void);
static FRAME_INFO frame__compile_meta_module_37 = {8, {"line", "modification_time", "force_rebuild", "break", "meta_path", "check", "command", "argument"}};
static NODE *func__compile_meta_module_38;
static void entry__compile_meta_module_38(void);
static FRAME_INFO frame__compile_meta_module_38 = {5, {"data_filename", "modification_time", "force_rebuild", "break", "data_info"}};
static void cont__compile_meta_module_39(void);
static void cont__compile_meta_module_40(void);
static NODE *func__compile_meta_module_41;
static void entry__compile_meta_module_41(void);
static FRAME_INFO frame__compile_meta_module_41 = {2, {"modification_time", "data_info"}};
static void cont__compile_meta_module_42(void);
static void cont__compile_meta_module_43(void);
static void cont__compile_meta_module_44(void);
static NODE *func__compile_meta_module_45;
static void entry__compile_meta_module_45(void);
static FRAME_INFO frame__compile_meta_module_45 = {2, {"force_rebuild", "break"}};
static NODE *string__9c0afa8b5f187d19;
static void cont__compile_meta_module_47(void);
static void cont__compile_meta_module_48(void);
static void cont__compile_meta_module_49(void);
static void cont__compile_meta_module_50(void);
static void cont__compile_meta_module_51(void);
static void cont__compile_meta_module_52(void);
static NODE *string__a0ae90b5dc07d58;
static void cont__compile_meta_module_54(void);
static NODE *func__compile_meta_module_55;
static void entry__compile_meta_module_55(void);
static FRAME_INFO frame__compile_meta_module_55 = {3, {"argument", "check", "meta_path"}};
static NODE *string__2d7981f4e6782bea;
static void cont__compile_meta_module_57(void);
static NODE *func__compile_meta_module_58;
static void entry__compile_meta_module_58(void);
static FRAME_INFO frame__compile_meta_module_58 = {3, {"check", "meta_path", "argument"}};
static void cont__compile_meta_module_59(void);
static void cont__compile_meta_module_60(void);
static void cont__compile_meta_module_61(void);
static NODE *func__compile_meta_module_62;
static void entry__compile_meta_module_62(void);
static FRAME_INFO frame__compile_meta_module_62 = {2, {"check", "argument"}};
static NODE *func__compile_meta_module_63;
static void entry__compile_meta_module_63(void);
static FRAME_INFO frame__compile_meta_module_63 = {3, {"path", "check", "argument"}};
static void cont__compile_meta_module_64(void);
static void cont__compile_meta_module_65(void);
static void cont__compile_meta_module_66(void);
static NODE *func__compile_meta_module_67;
static void entry__compile_meta_module_67(void);
static FRAME_INFO frame__compile_meta_module_67 = {9, {"return__1", "meta_filename", "meta_path", "filename", "sim_filename", "orig_path", "out", "err", "success"}};
static void cont__compile_meta_module_68(void);
static void cont__compile_meta_module_69(void);
static void cont__compile_meta_module_70(void);
static void cont__compile_meta_module_71(void);
static void cont__compile_meta_module_72(void);
static void cont__compile_meta_module_73(void);
static NODE *func__compile_meta_module_74;
static void entry__compile_meta_module_74(void);
static FRAME_INFO frame__compile_meta_module_74 = {1, {"err"}};
static void cont__compile_meta_module_75(void);
static void cont__compile_meta_module_76(void);
static void cont__compile_meta_module_77(void);
static void cont__compile_meta_module_78(void);
static void cont__compile_meta_module_79(void);
static void cont__compile_meta_module_80(void);
static void cont__compile_meta_module_81(void);
static NODE *func__build_dependencies;
static void entry__build_dependencies(void);
static FRAME_INFO frame__build_dependencies = {5, {"mod_filename", "mod_name", "c_buf", "do_compile_c", "return"}};
static NODE *func__build_dependencies_2;
static void entry__build_dependencies_2(void);
static FRAME_INFO frame__build_dependencies_2 = {7, {"line", "return", "mod_filename", "mod_name", "do_compile_c", "command", "argument"}};
static void cont__build_dependencies_3(void);
static void cont__build_dependencies_4(void);
static void cont__build_dependencies_5(void);
static void cont__build_dependencies_6(void);
static void cont__build_dependencies_7(void);
static void cont__build_dependencies_8(void);
static NODE *func__build_dependencies_9;
static void entry__build_dependencies_9(void);
static FRAME_INFO frame__build_dependencies_9 = {4, {"argument", "mod_filename", "mod_name", "do_compile_c"}};
static void cont__build_dependencies_10(void);
static NODE *func__build_dependencies_11;
static void entry__build_dependencies_11(void);
static FRAME_INFO frame__build_dependencies_11 = {3, {"argument", "mod_filename", "mod_name"}};
static NODE *unique__EXE;
static void cont__build_dependencies_12(void);
static NODE *func__build_dependencies_13;
static void entry__build_dependencies_13(void);
static FRAME_INFO frame__build_dependencies_13 = {4, {"argument", "mod_filename", "mod_name", "req_name"}};
static void cont__build_dependencies_14(void);
static void cont__build_dependencies_15(void);
static void cont__build_dependencies_16(void);
static void cont__build_dependencies_17(void);
static void cont__build_dependencies_18(void);
static void cont__build_dependencies_19(void);
static void cont__build_dependencies_20(void);
static void cont__build_dependencies_21(void);
static NODE *func__build_dependencies_22;
static void entry__build_dependencies_22(void);
static FRAME_INFO frame__build_dependencies_22 = {2, {"argument", "do_compile_c"}};
static NODE *func__build_dependencies_23;
static void entry__build_dependencies_23(void);
static FRAME_INFO frame__build_dependencies_23 = {0, {}};
static NODE *func__build_dependencies_24;
static void entry__build_dependencies_24(void);
static FRAME_INFO frame__build_dependencies_24 = {0, {}};
static void cont__build_dependencies_25(void);
static void cont__build_dependencies_26(void);
static NODE *func__build_dependencies_27;
static void entry__build_dependencies_27(void);
static FRAME_INFO frame__build_dependencies_27 = {1, {"argument"}};
static void cont__build_dependencies_28(void);
static NODE *func__build_dependencies_29;
static void entry__build_dependencies_29(void);
static FRAME_INFO frame__build_dependencies_29 = {2, {"do_compile_c", "argument"}};
static NODE *func__build_dependencies_30;
static void entry__build_dependencies_30(void);
static FRAME_INFO frame__build_dependencies_30 = {1, {"argument"}};
static void cont__build_dependencies_31(void);
static NODE *string__240aeb0b5d087d14;
static void cont__build_dependencies_33(void);
static void cont__build_dependencies_34(void);
static NODE *func__build_dependencies_35;
static void entry__build_dependencies_35(void);
static FRAME_INFO frame__build_dependencies_35 = {2, {"do_compile_c", "argument"}};
static NODE *func__build_dependencies_36;
static void entry__build_dependencies_36(void);
static FRAME_INFO frame__build_dependencies_36 = {1, {"argument"}};
static void cont__build_dependencies_37(void);
static void cont__build_dependencies_38(void);
static NODE *string__984c0f90152bd09f;
static NODE *string__1a0aeb0b5d107d52;
static void cont__build_dependencies_41(void);
static NODE *func__compile_module;
static void entry__compile_module(void);
static FRAME_INFO frame__compile_module = {6, {"mod_filename", "mod_name", "return", "compile_submodule", "mod_info", "o_filename"}};
static NODE *func__compile_module_2;
static void entry__compile_module_2(void);
static FRAME_INFO frame__compile_module_2 = {11, {"submodule_names", "do_compile_c", "suffix", "mod_filename", "mod_name", "o_filename", "modification_time", "sim_filenames", "c_filename", "c_info", "c_buf"}};
static NODE *func__compile_module_3;
static void entry__compile_module_3(void);
static FRAME_INFO frame__compile_module_3 = {8, {"submodule_name", "mod_filename", "sim_filenames", "modification_time", "meta_level", "submodule_filename", "sim_filename", "sim_info"}};
static void cont__compile_module_4(void);
static void cont__compile_module_5(void);
static void cont__compile_module_6(void);
static void cont__compile_module_7(void);
static void cont__compile_module_8(void);
static NODE *func__compile_module_9;
static void entry__compile_module_9(void);
static FRAME_INFO frame__compile_module_9 = {0, {}};
static void cont__compile_module_10(void);
static void cont__compile_module_11(void);
static NODE *func__compile_module_12;
static void entry__compile_module_12(void);
static FRAME_INFO frame__compile_module_12 = {3, {"submodule_filename", "submodule_name", "meta_level"}};
static void cont__compile_module_13(void);
static void cont__compile_module_14(void);
static void cont__compile_module_15(void);
static void cont__compile_module_16(void);
static void cont__compile_module_17(void);
static NODE *func__compile_module_18;
static void entry__compile_module_18(void);
static FRAME_INFO frame__compile_module_18 = {1, {"sim_filename"}};
static NODE *string__52b1d7d50d05f753;
static void cont__compile_module_20(void);
static void cont__compile_module_21(void);
static void cont__compile_module_22(void);
static NODE *func__compile_module_23;
static void entry__compile_module_23(void);
static FRAME_INFO frame__compile_module_23 = {2, {"modification_time", "sim_info"}};
static void cont__compile_module_24(void);
static void cont__compile_module_25(void);
static void cont__compile_module_26(void);
static NODE *func__compile_module_27;
static void entry__compile_module_27(void);
static FRAME_INFO frame__compile_module_27 = {2, {"modification_time", "sim_info"}};
static void cont__compile_module_28(void);
static void cont__compile_module_29(void);
static void cont__compile_module_30(void);
static void cont__compile_module_31(void);
static NODE *func__compile_module_32;
static void entry__compile_module_32(void);
static FRAME_INFO frame__compile_module_32 = {1, {"c_filename"}};
static void cont__compile_module_33(void);
static void cont__compile_module_34(void);
static NODE *func__compile_module_35;
static void entry__compile_module_35(void);
static FRAME_INFO frame__compile_module_35 = {2, {"c_info", "modification_time"}};
static void cont__compile_module_36(void);
static NODE *func__compile_module_37;
static void entry__compile_module_37(void);
static FRAME_INFO frame__compile_module_37 = {2, {"c_info", "modification_time"}};
static void cont__compile_module_38(void);
static void cont__compile_module_39(void);
static void cont__compile_module_40(void);
static void cont__compile_module_41(void);
static NODE *func__compile_module_42;
static void entry__compile_module_42(void);
static FRAME_INFO frame__compile_module_42 = {9, {"return__1", "mod_name", "suffix", "sim_filenames", "c_buf", "c_filename", "do_compile_c", "o_filename", "c_source"}};
static NODE *string__2d7981f4e5f02b9a;
static void cont__compile_module_44(void);
static void cont__compile_module_45(void);
static void cont__compile_module_46(void);
static NODE *func__compile_module_47;
static void entry__compile_module_47(void);
static FRAME_INFO frame__compile_module_47 = {1, {"suffix"}};
static NODE *string__a85eb307b04e1ec9;
static void cont__compile_module_49(void);
static NODE *func__compile_module_50;
static void entry__compile_module_50(void);
static FRAME_INFO frame__compile_module_50 = {1, {"sim_filenames"}};
static void cont__compile_module_51(void);
static NODE *func__compile_module_52;
static void entry__compile_module_52(void);
static FRAME_INFO frame__compile_module_52 = {1, {"c_source"}};
static void cont__compile_module_53(void);
static void cont__compile_module_54(void);
static void cont__compile_module_55(void);
static NODE *func__compile_module_56;
static void entry__compile_module_56(void);
static FRAME_INFO frame__compile_module_56 = {2, {"c_filename", "o_filename"}};
static void cont__compile_module_57(void);
static NODE *func__compile_module_58;
static void entry__compile_module_58(void);
static FRAME_INFO frame__compile_module_58 = {6, {"c_buf", "c_filename", "o_filename", "c_info", "do_compile_c", "o_info"}};
static void cont__compile_module_59(void);
static void cont__compile_module_60(void);
static void cont__compile_module_61(void);
static NODE *func__compile_module_62;
static void entry__compile_module_62(void);
static FRAME_INFO frame__compile_module_62 = {2, {"o_info", "c_info"}};
static void cont__compile_module_63(void);
static void cont__compile_module_64(void);
static void cont__compile_module_65(void);
static void cont__compile_module_66(void);
static NODE *func__compile_module_67;
static void entry__compile_module_67(void);
static FRAME_INFO frame__compile_module_67 = {3, {"do_compile_c", "c_filename", "o_filename"}};
static NODE *func__compile_module_68;
static void entry__compile_module_68(void);
static FRAME_INFO frame__compile_module_68 = {2, {"c_filename", "o_filename"}};
static NODE *func__compile_module_69;
static void entry__compile_module_69(void);
static FRAME_INFO frame__compile_module_69 = {1, {"o_info"}};
static void cont__compile_module_70(void);
static NODE *func__compile_module_71;
static void entry__compile_module_71(void);
static FRAME_INFO frame__compile_module_71 = {1, {"o_info"}};
static void cont__compile_module_72(void);
static void cont__compile_module_73(void);
static void cont__compile_module_74(void);
static NODE *func__compile_module_75;
static void entry__compile_module_75(void);
static FRAME_INFO frame__compile_module_75 = {1, {"o_info"}};
static void cont__compile_module_76(void);
static void cont__compile_module_77(void);
static void cont__compile_module_78(void);
static void cont__compile_module_79(void);
static NODE *func__compile_module_80;
static void entry__compile_module_80(void);
static FRAME_INFO frame__compile_module_80 = {1, {"mod_name"}};
static NODE *string__1c48d17af91ab023;
static NODE *string__4594ae5504f56841;
static void cont__compile_module_83(void);
static void cont__compile_module_84(void);
static NODE *string__2d7981f4e6782baa;
static void cont__compile_module_86(void);
static void cont__compile_module_87(void);
static void cont__compile_module_88(void);
static void cont__compile_module_89(void);
static void cont__compile_module_90(void);
static NODE *func__compile_module_91;
static void entry__compile_module_91(void);
static FRAME_INFO frame__compile_module_91 = {3, {"mod_filename", "compile_submodule", "mod_name"}};
static NODE *func__compile_module_92;
static void entry__compile_module_92(void);
static FRAME_INFO frame__compile_module_92 = {1, {"mod_filename"}};
static void cont__compile_module_93(void);
static void cont__compile_module_94(void);
static void cont__compile_module_95(void);
static void cont__compile_module_96(void);
static void cont__compile_module_97(void);
static void cont__compile_module_98(void);
static NODE *func__compile_module_99;
static void entry__compile_module_99(void);
static FRAME_INFO frame__compile_module_99 = {3, {"mod_info", "compile_submodule", "mod_filename"}};
static NODE *func__compile_module_100;
static void entry__compile_module_100(void);
static FRAME_INFO frame__compile_module_100 = {4, {"mod_info", "compile_submodule", "best_platform", "best_priority"}};
static NODE *func__compile_module_101;
static void entry__compile_module_101(void);
static FRAME_INFO frame__compile_module_101 = {5, {"platform", "filenames", "best_priority", "best_platform", "priority"}};
static void cont__compile_module_102(void);
static void cont__compile_module_103(void);
static NODE *func__compile_module_104;
static void entry__compile_module_104(void);
static FRAME_INFO frame__compile_module_104 = {2, {"priority", "best_priority"}};
static void cont__compile_module_105(void);
static void cont__compile_module_106(void);
static NODE *func__compile_module_107;
static void entry__compile_module_107(void);
static FRAME_INFO frame__compile_module_107 = {4, {"best_platform", "platform", "best_priority", "priority"}};
static void cont__compile_module_108(void);
static NODE *func__compile_module_109;
static void entry__compile_module_109(void);
static FRAME_INFO frame__compile_module_109 = {4, {"platform", "filenames", "compile_submodule", "best_platform"}};
static void cont__compile_module_110(void);
static void cont__compile_module_111(void);
static void cont__compile_module_112(void);
static NODE *func__compile_module_113;
static void entry__compile_module_113(void);
static FRAME_INFO frame__compile_module_113 = {3, {"mod_info", "mod_filename", "used_by"}};
static NODE *func__compile_module_114;
static void entry__compile_module_114(void);
static FRAME_INFO frame__compile_module_114 = {6, {"supported_platform", "parent_platform", "mod_info", "used_by", "best_platform", "best_priority"}};
static NODE *func__compile_module_115;
static void entry__compile_module_115(void);
static FRAME_INFO frame__compile_module_115 = {6, {"platform", "filenames", "supported_platform", "best_priority", "best_platform", "priority"}};
static void cont__compile_module_116(void);
static void cont__compile_module_117(void);
static NODE *func__compile_module_118;
static void entry__compile_module_118(void);
static FRAME_INFO frame__compile_module_118 = {2, {"priority", "best_priority"}};
static void cont__compile_module_119(void);
static void cont__compile_module_120(void);
static NODE *func__compile_module_121;
static void entry__compile_module_121(void);
static FRAME_INFO frame__compile_module_121 = {4, {"best_platform", "platform", "best_priority", "priority"}};
static void cont__compile_module_122(void);
static void cont__compile_module_123(void);
static NODE *func__compile_module_124;
static void entry__compile_module_124(void);
static FRAME_INFO frame__compile_module_124 = {4, {"used_by", "best_platform", "supported_platform", "ub"}};
static void cont__compile_module_125(void);
static void cont__compile_module_126(void);
static void cont__compile_module_127(void);
static void cont__compile_module_128(void);
static void cont__compile_module_129(void);
static NODE *func__compile_module_130;
static void entry__compile_module_130(void);
static FRAME_INFO frame__compile_module_130 = {6, {"platform", "filenames", "mod_filename", "used_by", "dependency", "platforms"}};
static void cont__compile_module_131(void);
static void cont__compile_module_132(void);
static void cont__compile_module_133(void);
static NODE *func__compile_module_134;
static void entry__compile_module_134(void);
static FRAME_INFO frame__compile_module_134 = {2, {"platforms", "dependency"}};
static NODE *func__compile_module_135;
static void entry__compile_module_135(void);
static FRAME_INFO frame__compile_module_135 = {2, {"plat", "dependency"}};
static NODE *string__2d7981f4e6082be6;
static void cont__compile_module_137(void);
static void cont__compile_module_138(void);
static void cont__compile_module_139(void);
static void cont__compile_module_140(void);
static NODE *func__compile_modules;
static void entry__compile_modules(void);
static FRAME_INFO frame__compile_modules = {4, {"path", "mod_path", "directories", "modules"}};
static void cont__compile_modules_2(void);
static void cont__compile_modules_3(void);
static NODE *func__compile_modules_4;
static void entry__compile_modules_4(void);
static FRAME_INFO frame__compile_modules_4 = {3, {"name", "path", "mod_path"}};
static void cont__compile_modules_5(void);
static void cont__compile_modules_6(void);
static void cont__compile_modules_7(void);
static NODE *func__compile_modules_8;
static void entry__compile_modules_8(void);
static FRAME_INFO frame__compile_modules_8 = {3, {"name", "path", "mod_path"}};
static void cont__compile_modules_9(void);
static void cont__compile_modules_10(void);
static NODE *func__show_file_list;
static void entry__show_file_list(void);
static FRAME_INFO frame__show_file_list = {0, {}};
static NODE *func__show_file_list_2;
static void entry__show_file_list_2(void);
static FRAME_INFO frame__show_file_list_2 = {1, {"path"}};
static NODE *string__21dcb95c2a4f4c6f;
static void cont__show_file_list_4(void);
static void cont__show_file_list_5(void);
static NODE *func__show_file_list_6;
static void entry__show_file_list_6(void);
static FRAME_INFO frame__show_file_list_6 = {1, {"path"}};
static NODE *string__cae1527a63790ed8;
static void cont__show_file_list_8(void);
static void cont__show_file_list_9(void);
static void cont__show_file_list_10(void);
static NODE *string__4c84a8f87d97d1a3;
static void cont__show_file_list_12(void);
static void cont__show_file_list_13(void);
static NODE *string__d2a77fcc4263ea03;
static NODE *func__library_paths_and_file_list;
static void entry__library_paths_and_file_list(void);
static FRAME_INFO frame__library_paths_and_file_list = {4, {"library_paths", "object_files", "library_files", "paths"}};
static void cont__library_paths_and_file_list_2(void);
static void cont__library_paths_and_file_list_3(void);
static void cont__library_paths_and_file_list_4(void);
static NODE *func__library_paths_and_file_list_5;
static void entry__library_paths_and_file_list_5(void);
static FRAME_INFO frame__library_paths_and_file_list_5 = {2, {"paths", "library_paths"}};
static void cont__library_paths_and_file_list_6(void);
static NODE *func__library_paths_and_file_list_7;
static void entry__library_paths_and_file_list_7(void);
static FRAME_INFO frame__library_paths_and_file_list_7 = {2, {"path", "library_paths"}};
static NODE *string__2d7981f4e6602b89;
static void cont__library_paths_and_file_list_9(void);
static void cont__library_paths_and_file_list_10(void);
static void cont__library_paths_and_file_list_11(void);
static NODE *func__library_paths_and_file_list_12;
static void entry__library_paths_and_file_list_12(void);
static FRAME_INFO frame__library_paths_and_file_list_12 = {1, {"library_paths"}};
static void cont__library_paths_and_file_list_13(void);
static NODE *string__47d536100241702d;
static void cont__library_paths_and_file_list_15(void);
static NODE *func__library_paths_and_file_list_16;
static void entry__library_paths_and_file_list_16(void);
static FRAME_INFO frame__library_paths_and_file_list_16 = {2, {"object", "object_files"}};
static void cont__library_paths_and_file_list_17(void);
static void cont__library_paths_and_file_list_18(void);
static NODE *func__library_paths_and_file_list_19;
static void entry__library_paths_and_file_list_19(void);
static FRAME_INFO frame__library_paths_and_file_list_19 = {2, {"library", "library_files"}};
static void cont__library_paths_and_file_list_20(void);
static NODE *func__library_paths_and_file_list_21;
static void entry__library_paths_and_file_list_21(void);
static FRAME_INFO frame__library_paths_and_file_list_21 = {1, {"library"}};
static void cont__library_paths_and_file_list_22(void);
static NODE *string__585ae883ea60d02f;
static NODE *string__fa720c15db16ba8;
static void cont__library_paths_and_file_list_25(void);
static NODE *func__library_paths_and_file_list_26;
static void entry__library_paths_and_file_list_26(void);
static FRAME_INFO frame__library_paths_and_file_list_26 = {1, {"library"}};
static NODE *string__ec1f556601f292b5;
static NODE *string__9e0aed8b5d187d17;
static void cont__library_paths_and_file_list_29(void);
static NODE *func__library_paths_and_file_list_30;
static void entry__library_paths_and_file_list_30(void);
static FRAME_INFO frame__library_paths_and_file_list_30 = {1, {"library"}};
static NODE *string__2d7981f4e6602ba9;
static void cont__library_paths_and_file_list_32(void);
static void cont__library_paths_and_file_list_33(void);
static NODE *func__library_paths_and_file_list_34;
static void entry__library_paths_and_file_list_34(void);
static FRAME_INFO frame__library_paths_and_file_list_34 = {1, {"library"}};
static void cont__library_paths_and_file_list_35(void);
static NODE *func__library_paths_and_file_list_36;
static void entry__library_paths_and_file_list_36(void);
static FRAME_INFO frame__library_paths_and_file_list_36 = {1, {"library"}};
static void cont__library_paths_and_file_list_37(void);
static void cont__library_paths_and_file_list_38(void);
static void cont__library_paths_and_file_list_39(void);
static NODE *func__library_paths_and_file_list_40;
static void entry__library_paths_and_file_list_40(void);
static FRAME_INFO frame__library_paths_and_file_list_40 = {1, {"library"}};
static void cont__library_paths_and_file_list_41(void);
static void cont__library_paths_and_file_list_42(void);
static void cont__library_paths_and_file_list_43(void);
static void cont__library_paths_and_file_list_44(void);
static void cont__library_paths_and_file_list_45(void);
static void cont__library_paths_and_file_list_46(void);
static NODE *func__create_imports;
static void entry__create_imports(void);
static FRAME_INFO frame__create_imports = {5, {"source", "already_checked", "collect_declarations", "imports", "first_part"}};
static NODE *func__create_imports_2;
static void entry__create_imports_2(void);
static FRAME_INFO frame__create_imports_2 = {4, {"buf", "already_checked", "collect_declarations", "s"}};
static NODE *func__create_imports_3;
static void entry__create_imports_3(void);
static FRAME_INFO frame__create_imports_3 = {6, {"idx", "chr", "s", "buf", "already_checked", "collect_declarations"}};
static void cont__create_imports_4(void);
static NODE *func__create_imports_5;
static void entry__create_imports_5(void);
static FRAME_INFO frame__create_imports_5 = {6, {"chr", "buf", "s", "idx", "already_checked", "collect_declarations"}};
static void cont__create_imports_6(void);
static NODE *func__create_imports_7;
static void entry__create_imports_7(void);
static FRAME_INFO frame__create_imports_7 = {1, {"chr"}};
static void cont__create_imports_8(void);
static NODE *func__create_imports_9;
static void entry__create_imports_9(void);
static FRAME_INFO frame__create_imports_9 = {1, {"chr"}};
static void cont__create_imports_10(void);
static void cont__create_imports_11(void);
static void cont__create_imports_12(void);
static NODE *func__create_imports_13;
static void entry__create_imports_13(void);
static FRAME_INFO frame__create_imports_13 = {6, {"buf", "s", "idx", "already_checked", "collect_declarations", "symbol"}};
static void cont__create_imports_14(void);
static void cont__create_imports_15(void);
static void cont__create_imports_16(void);
static NODE *func__create_imports_17;
static void entry__create_imports_17(void);
static FRAME_INFO frame__create_imports_17 = {4, {"already_checked", "symbol", "collect_declarations", "declaration"}};
static void cont__create_imports_18(void);
static void cont__create_imports_19(void);
static void cont__create_imports_20(void);
static NODE *func__create_imports_21;
static void entry__create_imports_21(void);
static FRAME_INFO frame__create_imports_21 = {3, {"declaration", "collect_declarations", "do_import"}};
static void cont__create_imports_22(void);
static void cont__create_imports_23(void);
static void cont__create_imports_24(void);
static NODE *func__create_imports_25;
static void entry__create_imports_25(void);
static FRAME_INFO frame__create_imports_25 = {1, {"declaration"}};
static NODE *string__b8540cde1593c09c;
static void cont__create_imports_27(void);
static void cont__create_imports_28(void);
static NODE *func__create_imports_29;
static void entry__create_imports_29(void);
static FRAME_INFO frame__create_imports_29 = {1, {"declaration"}};
static NODE *string__800a0c585ff0632;
static void cont__create_imports_31(void);
static void cont__create_imports_32(void);
static void cont__create_imports_33(void);
static void cont__create_imports_34(void);
static NODE *func__create_imports_35;
static void entry__create_imports_35(void);
static FRAME_INFO frame__create_imports_35 = {2, {"declaration", "collect_declarations"}};
static void cont__create_imports_36(void);
static void cont__create_imports_37(void);
static NODE *func__create_imports_38;
static void entry__create_imports_38(void);
static FRAME_INFO frame__create_imports_38 = {1, {"declaration"}};
static void cont__create_imports_39(void);
static void cont__create_imports_40(void);
static NODE *func__create_imports_41;
static void entry__create_imports_41(void);
static FRAME_INFO frame__create_imports_41 = {2, {"collect_declarations", "declaration"}};
static void cont__create_imports_42(void);
static NODE *func__create_imports_43;
static void entry__create_imports_43(void);
static FRAME_INFO frame__create_imports_43 = {2, {"declaration", "collect_declarations"}};
static NODE *string__ee0186bb316753e3;
static void cont__create_imports_45(void);
static NODE *func__create_imports_46;
static void entry__create_imports_46(void);
static FRAME_INFO frame__create_imports_46 = {2, {"declaration", "collect_declarations"}};
static void cont__create_imports_47(void);
static void cont__create_imports_48(void);
static NODE *func__create_imports_49;
static void entry__create_imports_49(void);
static FRAME_INFO frame__create_imports_49 = {2, {"line", "collect_declarations"}};
static void cont__create_imports_50(void);
static void cont__create_imports_51(void);
static NODE *func__create_imports_52;
static void entry__create_imports_52(void);
static FRAME_INFO frame__create_imports_52 = {2, {"collect_declarations", "declaration"}};
static void cont__create_imports_53(void);
static NODE *func__create_imports_54;
static void entry__create_imports_54(void);
static FRAME_INFO frame__create_imports_54 = {0, {}};
static NODE *string__eca001441419c0da;
static void cont__create_imports_56(void);
static NODE *func__create_imports_57;
static void entry__create_imports_57(void);
static FRAME_INFO frame__create_imports_57 = {3, {"chr", "s", "idx"}};
static void cont__create_imports_58(void);
static NODE *func__create_imports_59;
static void entry__create_imports_59(void);
static FRAME_INFO frame__create_imports_59 = {1, {"chr"}};
static void cont__create_imports_60(void);
static void cont__create_imports_61(void);
static NODE *func__create_imports_62;
static void entry__create_imports_62(void);
static FRAME_INFO frame__create_imports_62 = {2, {"s", "idx"}};
static NODE *func__create_imports_63;
static void entry__create_imports_63(void);
static FRAME_INFO frame__create_imports_63 = {2, {"collect_declarations", "source"}};
static void cont__create_imports_64(void);
static NODE *string__736c99bf90749400;
static void cont__create_imports_66(void);
static void cont__create_imports_67(void);
static void cont__create_imports_68(void);
static void cont__create_imports_69(void);
static void cont__create_imports_70(void);
static void cont__create_imports_71(void);
static void cont__create_imports_72(void);
static void cont__create_imports_73(void);
static NODE *func__create_imports_74;
static void entry__create_imports_74(void);
static FRAME_INFO frame__create_imports_74 = {0, {}};
static NODE *string__868d47f2e5ba5079;
static NODE *func__compile_exe;
static void entry__compile_exe(void);
static FRAME_INFO frame__compile_exe = {4, {"body", "return__1", "mod_filename", "mod_name"}};
static void cont__compile_exe_2(void);
static NODE *func__compile_exe_3;
static void entry__compile_exe_3(void);
static FRAME_INFO frame__compile_exe_3 = {0, {}};
static NODE *string__ac6b0fa074ea65e7;
static void cont__compile_exe_5(void);
static void cont__compile_exe_6(void);
static NODE *func__compile_exe_7;
static void entry__compile_exe_7(void);
static FRAME_INFO frame__compile_exe_7 = {0, {}};
static NODE *string__e365e96bee331e9c;
static void cont__compile_exe_9(void);
static void cont__compile_exe_10(void);
static void cont__compile_exe_11(void);
static void cont__compile_exe_12(void);
static void cont__compile_exe_13(void);
static NODE *func__dump_source_or_check;
static void entry__dump_source_or_check(void);
static FRAME_INFO frame__dump_source_or_check = {0, {}};
static NODE *func__dump_source_or_check_2;
static void entry__dump_source_or_check_2(void);
static FRAME_INFO frame__dump_source_or_check_2 = {3, {"mod_filename", "mod_name", "return__1"}};
static void cont__dump_source_or_check_3(void);
static void cont__dump_source_or_check_4(void);
static NODE *func__print_c;
static void entry__print_c(void);
static FRAME_INFO frame__print_c = {0, {}};
static NODE *func__print_c_2;
static void entry__print_c_2(void);
static FRAME_INFO frame__print_c_2 = {4, {"mod_filename", "mod_name", "c_source", "c_buf"}};
static void cont__print_c_3(void);
static NODE *func__print_c_4;
static void entry__print_c_4(void);
static FRAME_INFO frame__print_c_4 = {1, {"mod_name"}};
static void cont__print_c_5(void);
static void cont__print_c_6(void);
static void cont__print_c_7(void);
static NODE *func__print_c_8;
static void entry__print_c_8(void);
static FRAME_INFO frame__print_c_8 = {2, {"return__1", "mod_name"}};
static void cont__print_c_9(void);
static void cont__print_c_10(void);
static void cont__print_c_11(void);
static void cont__print_c_12(void);
static void cont__print_c_13(void);
static void cont__print_c_14(void);
static NODE *func__print_c_15;
static void entry__print_c_15(void);
static FRAME_INFO frame__print_c_15 = {1, {"c_source"}};
static void cont__print_c_16(void);
static void cont__print_c_17(void);
static NODE *func__print_c_18;
static void entry__print_c_18(void);
static FRAME_INFO frame__print_c_18 = {0, {}};
static NODE *string__b830f06b636224ab;
static NODE *func__list_dependencies;
static void entry__list_dependencies(void);
static FRAME_INFO frame__list_dependencies = {1, {"prefix_path"}};
static void cont__list_dependencies_2(void);
static NODE *func__list_dependencies_3;
static void entry__list_dependencies_3(void);
static FRAME_INFO frame__list_dependencies_3 = {4, {"supported_platform", "parent_platform", "platform", "priority"}};
static NODE *func__list_dependencies_4;
static void entry__list_dependencies_4(void);
static FRAME_INFO frame__list_dependencies_4 = {4, {"break", "platform", "priority", "supported_platform"}};
static NODE *func__list_dependencies_5;
static void entry__list_dependencies_5(void);
static FRAME_INFO frame__list_dependencies_5 = {5, {"platform", "break", "priority", "supported_platform", "plat"}};
static void cont__list_dependencies_6(void);
static void cont__list_dependencies_7(void);
static void cont__list_dependencies_8(void);
static void cont__list_dependencies_9(void);
static void cont__list_dependencies_10(void);
static void cont__list_dependencies_11(void);
static void cont__list_dependencies_12(void);
static void cont__list_dependencies_13(void);
static void cont__list_dependencies_14(void);
static void cont__list_dependencies_15(void);
static NODE *func__list_dependencies_16;
static void entry__list_dependencies_16(void);
static FRAME_INFO frame__list_dependencies_16 = {1, {"return__1"}};
static NODE *unique__LIB;
static NODE *func__list_dependencies_17;
static void entry__list_dependencies_17(void);
static FRAME_INFO frame__list_dependencies_17 = {0, {}};
static NODE *string__7da4130a131d4ea3;
static void cont__list_dependencies_19(void);
static void cont__list_dependencies_20(void);
static void cont__list_dependencies_21(void);
static void cont__list_dependencies_22(void);
static NODE *func__list_dependencies_23;
static void entry__list_dependencies_23(void);
static FRAME_INFO frame__list_dependencies_23 = {0, {}};
static NODE *func__list_dependencies_24;
static void entry__list_dependencies_24(void);
static FRAME_INFO frame__list_dependencies_24 = {2, {"mod_filename", "mod_name"}};
static NODE *func__list_dependencies_25;
static void entry__list_dependencies_25(void);
static FRAME_INFO frame__list_dependencies_25 = {1, {"mod_filename"}};
static void cont__list_dependencies_26(void);
static void cont__list_dependencies_27(void);
static NODE *string__5aa0e0654e0a7d4d;
static void cont__list_dependencies_29(void);
static NODE *string__7490e2a4ce0a3d6d;
static void cont__list_dependencies_31(void);
static NODE *string__14e71717a54948b0;
static void cont__list_dependencies_33(void);
static void cont__list_dependencies_34(void);
static NODE *func__list_dependencies_35;
static void entry__list_dependencies_35(void);
static FRAME_INFO frame__list_dependencies_35 = {2, {"filename", "prefix_path"}};
static void cont__list_dependencies_36(void);
static void cont__list_dependencies_37(void);
static NODE *func__build_codeblocks_project;
static void entry__build_codeblocks_project(void);
static FRAME_INFO frame__build_codeblocks_project = {0, {}};
static NODE *func__build_codeblocks_project_2;
static void entry__build_codeblocks_project_2(void);
static FRAME_INFO frame__build_codeblocks_project_2 = {10, {"mod_filename", "mod_name", "codeblocks_path", "info", "basename", "prefix_path", "depth", "path_prefix", "cbp_filename", "buf"}};
static NODE *string__1ec9299aa0516bc0;
static void cont__build_codeblocks_project_4(void);
static void cont__build_codeblocks_project_5(void);
static void cont__build_codeblocks_project_6(void);
static NODE *func__build_codeblocks_project_7;
static void entry__build_codeblocks_project_7(void);
static FRAME_INFO frame__build_codeblocks_project_7 = {1, {"codeblocks_path"}};
static NODE *string__3319ecea8934288e;
static NODE *string__fb06ffd100386aab;
static void cont__build_codeblocks_project_10(void);
static void cont__build_codeblocks_project_11(void);
static NODE *func__build_codeblocks_project_12;
static void entry__build_codeblocks_project_12(void);
static FRAME_INFO frame__build_codeblocks_project_12 = {1, {"codeblocks_path"}};
static NODE *string__334eb97199863420;
static void cont__build_codeblocks_project_14(void);
static void cont__build_codeblocks_project_15(void);
static void cont__build_codeblocks_project_16(void);
static void cont__build_codeblocks_project_17(void);
static void cont__build_codeblocks_project_18(void);
static void cont__build_codeblocks_project_19(void);
static void cont__build_codeblocks_project_20(void);
static void cont__build_codeblocks_project_21(void);
static void cont__build_codeblocks_project_22(void);
static NODE *string__fa733c15f596be3;
static void cont__build_codeblocks_project_24(void);
static NODE *string__578a5af303e9cce;
static NODE *string__9e0ae98b5d707d49;
static void cont__build_codeblocks_project_27(void);
static void cont__build_codeblocks_project_28(void);
static void cont__build_codeblocks_project_29(void);
static void cont__build_codeblocks_project_30(void);
static NODE *string__ae2cb2959270f10e;
static NODE *string__1738f6ef1a56e70d;
static NODE *string__f8758d9a72c26e31;
static NODE *string__b218c1a9e3db28b9;
static NODE *string__b5364d63e076ecb2;
static void cont__build_codeblocks_project_36(void);
static void cont__build_codeblocks_project_37(void);
static NODE *func__build_codeblocks_project_38;
static void entry__build_codeblocks_project_38(void);
static FRAME_INFO frame__build_codeblocks_project_38 = {2, {"filename", "buf"}};
static NODE *string__86909867946dc27b;
static NODE *string__ca5af8c3e83c305d;
static void cont__build_codeblocks_project_41(void);
static void cont__build_codeblocks_project_42(void);
static void cont__build_codeblocks_project_43(void);
static NODE *string__eff3cb070eeaf9ca;
static NODE *string__6ec73fb9d26dad91;
static NODE *string__62c73cb6d2cd6da9;
static NODE *string__df3541444f9afcd3;
static NODE *string__6a94fbaaffa1060a;
static NODE *string__3820eb4b885b519f;
static void cont__build_codeblocks_project_50(void);
static void cont__build_codeblocks_project_51(void);
static NODE *func__build_codeblocks_project_52;
static void entry__build_codeblocks_project_52(void);
static FRAME_INFO frame__build_codeblocks_project_52 = {4, {"filename", "prefix_path", "buf", "path_prefix"}};
static void cont__build_codeblocks_project_53(void);
static void cont__build_codeblocks_project_54(void);
static NODE *string__5ce0e5ba1304a164;
static NODE *string__eddc311fc1bd57cd;
static void cont__build_codeblocks_project_57(void);
static void cont__build_codeblocks_project_58(void);
static void cont__build_codeblocks_project_59(void);
static NODE *string__1d1cedd7cdd611c4;
static void cont__build_codeblocks_project_61(void);
static NODE *func__build_library;
static void entry__build_library(void);
static FRAME_INFO frame__build_library = {1, {"return__1"}};
static NODE *string__421f52c90112c2b9;
static void cont__build_library_3(void);
static NODE *func__build_library_4;
static void entry__build_library_4(void);
static FRAME_INFO frame__build_library_4 = {0, {}};
static NODE *string__c84d9037a41e8f73;
static void cont__build_library_6(void);
static NODE *func__build_library_7;
static void entry__build_library_7(void);
static FRAME_INFO frame__build_library_7 = {0, {}};
static NODE *func__build_library_8;
static void entry__build_library_8(void);
static FRAME_INFO frame__build_library_8 = {1, {"doc_libraries"}};
static void cont__build_library_9(void);
static NODE *func__build_library_10;
static void entry__build_library_10(void);
static FRAME_INFO frame__build_library_10 = {2, {"library", "doc_libraries"}};
static void cont__build_library_11(void);
static void cont__build_library_12(void);
static void cont__build_library_13(void);
static NODE *func__build_library_14;
static void entry__build_library_14(void);
static FRAME_INFO frame__build_library_14 = {0, {}};
static NODE *func__build_library_15;
static void entry__build_library_15(void);
static FRAME_INFO frame__build_library_15 = {1, {"doc_libraries"}};
static void cont__build_library_16(void);
static NODE *func__build_library_17;
static void entry__build_library_17(void);
static FRAME_INFO frame__build_library_17 = {2, {"library", "doc_libraries"}};
static void cont__build_library_18(void);
static void cont__build_library_19(void);
static void cont__build_library_20(void);
static NODE *func__build_library_21;
static void entry__build_library_21(void);
static FRAME_INFO frame__build_library_21 = {5, {"version", "version_filename", "so_version", "base_filename", "lib_filename"}};
static NODE *string__84ca78485aeb98e;
static void cont__build_library_23(void);
static void cont__build_library_24(void);
static NODE *func__build_library_25;
static void entry__build_library_25(void);
static FRAME_INFO frame__build_library_25 = {2, {"version", "version_filename"}};
static void cont__build_library_26(void);
static void cont__build_library_27(void);
static void cont__build_library_28(void);
static void cont__build_library_29(void);
static void cont__build_library_30(void);
static void cont__build_library_31(void);
static void cont__build_library_32(void);
static void cont__build_library_33(void);
static void cont__build_library_34(void);
static NODE *func__build_library_35;
static void entry__build_library_35(void);
static FRAME_INFO frame__build_library_35 = {2, {"base_filename", "version"}};
static void cont__build_library_36(void);
static NODE *string__94340f9615d2e0d7;
static void cont__build_library_38(void);
static NODE *func__build_library_39;
static void entry__build_library_39(void);
static FRAME_INFO frame__build_library_39 = {2, {"base_filename", "version"}};
static NODE *string__9e0ae84b5d007d55;
static void cont__build_library_41(void);
static void cont__build_library_42(void);
static NODE *func__build_library_43;
static void entry__build_library_43(void);
static FRAME_INFO frame__build_library_43 = {2, {"base_filename", "version"}};
static NODE *string__6a1f556781f212b5;
static void cont__build_library_45(void);
static void cont__build_library_46(void);
static NODE *func__build_library_47;
static void entry__build_library_47(void);
static FRAME_INFO frame__build_library_47 = {2, {"base_filename", "version"}};
static void cont__build_library_48(void);
static void cont__build_library_49(void);
static NODE *string__561f538101f3c2b9;
static NODE *string__7c1f538281f242b9;
static void cont__build_library_52(void);
static NODE *func__build_library_53;
static void entry__build_library_53(void);
static FRAME_INFO frame__build_library_53 = {1, {"lib_filename"}};
static NODE *string__822587b3f48532f5;
static void cont__build_library_55(void);
static void cont__build_library_56(void);
static void cont__build_library_57(void);
static void cont__build_library_58(void);
static NODE *func__build_library_59;
static void entry__build_library_59(void);
static FRAME_INFO frame__build_library_59 = {2, {"lib_filename", "info"}};
static void cont__build_library_60(void);
static void cont__build_library_61(void);
static NODE *func__build_library_62;
static void entry__build_library_62(void);
static FRAME_INFO frame__build_library_62 = {1, {"info"}};
static void cont__build_library_63(void);
static void cont__build_library_64(void);
static void cont__build_library_65(void);
static NODE *func__build_library_66;
static void entry__build_library_66(void);
static FRAME_INFO frame__build_library_66 = {0, {}};
static void cont__build_library_67(void);
static NODE *func__build_library_68;
static void entry__build_library_68(void);
static FRAME_INFO frame__build_library_68 = {3, {"base_filename", "so_version", "lib_filename"}};
static NODE *func__build_library_69;
static void entry__build_library_69(void);
static FRAME_INFO frame__build_library_69 = {0, {}};
static NODE *string__b9aef2a4efc3a1a8;
static void cont__build_library_71(void);
static void cont__build_library_72(void);
static void cont__build_library_73(void);
static NODE *func__build_library_74;
static void entry__build_library_74(void);
static FRAME_INFO frame__build_library_74 = {6, {"base_filename", "so_version", "lib_filename", "out", "err", "success"}};
static NODE *string__f5937b2655b3cd24;
static void cont__build_library_76(void);
static void cont__build_library_77(void);
static NODE *string__b130095b1592409e;
static void cont__build_library_79(void);
static NODE *func__build_library_80;
static void entry__build_library_80(void);
static FRAME_INFO frame__build_library_80 = {1, {"err"}};
static void cont__build_library_81(void);
static NODE *func__build_library_82;
static void entry__build_library_82(void);
static FRAME_INFO frame__build_library_82 = {4, {"lib_filename", "out", "err", "success"}};
static void cont__build_library_83(void);
static NODE *string__7e1f542601d292fa;
static void cont__build_library_85(void);
static void cont__build_library_86(void);
static NODE *func__build_library_87;
static void entry__build_library_87(void);
static FRAME_INFO frame__build_library_87 = {1, {"err"}};
static void cont__build_library_88(void);
static NODE *func__build_library_89;
static void entry__build_library_89(void);
static FRAME_INFO frame__build_library_89 = {6, {"base_filename", "so_version", "lib_filename", "out", "err", "success"}};
static NODE *string__33820b08e3b95a2a;
static void cont__build_library_91(void);
static void cont__build_library_92(void);
static void cont__build_library_93(void);
static NODE *string__c6d9125d36413a91;
static void cont__build_library_95(void);
static NODE *func__build_library_96;
static void entry__build_library_96(void);
static FRAME_INFO frame__build_library_96 = {1, {"err"}};
static void cont__build_library_97(void);
static NODE *func__build_library_98;
static void entry__build_library_98(void);
static FRAME_INFO frame__build_library_98 = {4, {"lib_filename", "out", "err", "success"}};
static void cont__build_library_99(void);
static void cont__build_library_100(void);
static NODE *func__build_library_101;
static void entry__build_library_101(void);
static FRAME_INFO frame__build_library_101 = {1, {"err"}};
static void cont__build_library_102(void);
static void cont__build_library_103(void);
static NODE *func__maybe_compile_c_file;
static void entry__maybe_compile_c_file(void);
static FRAME_INFO frame__maybe_compile_c_file = {5, {"filename", "c_filename", "o_filename", "c_info", "o_info"}};
static void cont__maybe_compile_c_file_2(void);
static void cont__maybe_compile_c_file_3(void);
static void cont__maybe_compile_c_file_4(void);
static void cont__maybe_compile_c_file_5(void);
static NODE *func__maybe_compile_c_file_6;
static void entry__maybe_compile_c_file_6(void);
static FRAME_INFO frame__maybe_compile_c_file_6 = {1, {"c_filename"}};
static NODE *string__578a5af303e9cc3;
static NODE *string__7ef24f7974bbce09;
static void cont__maybe_compile_c_file_9(void);
static void cont__maybe_compile_c_file_10(void);
static void cont__maybe_compile_c_file_11(void);
static void cont__maybe_compile_c_file_12(void);
static NODE *func__maybe_compile_c_file_13;
static void entry__maybe_compile_c_file_13(void);
static FRAME_INFO frame__maybe_compile_c_file_13 = {2, {"o_info", "c_info"}};
static void cont__maybe_compile_c_file_14(void);
static void cont__maybe_compile_c_file_15(void);
static void cont__maybe_compile_c_file_16(void);
static void cont__maybe_compile_c_file_17(void);
static NODE *func__maybe_compile_c_file_18;
static void entry__maybe_compile_c_file_18(void);
static FRAME_INFO frame__maybe_compile_c_file_18 = {3, {"filename", "c_filename", "o_filename"}};
static NODE *func__maybe_compile_c_file_19;
static void entry__maybe_compile_c_file_19(void);
static FRAME_INFO frame__maybe_compile_c_file_19 = {1, {"filename"}};
static NODE *string__74150357c2230d49;
static void cont__maybe_compile_c_file_21(void);
static void cont__maybe_compile_c_file_22(void);
static NODE *func__format_number;
static void entry__format_number(void);
static FRAME_INFO frame__format_number = {4, {"val", "n", "m", "ac"}};
static void cont__format_number_2(void);
static NODE *func__format_number_3;
static void entry__format_number_3(void);
static FRAME_INFO frame__format_number_3 = {4, {"break", "val", "ac", "n"}};
static NODE *func__format_number_4;
static void entry__format_number_4(void);
static FRAME_INFO frame__format_number_4 = {6, {"i", "chr", "ac", "val", "n", "break"}};
static void cont__format_number_5(void);
static NODE *func__format_number_6;
static void entry__format_number_6(void);
static FRAME_INFO frame__format_number_6 = {5, {"ac", "val", "i", "n", "break"}};
static void cont__format_number_7(void);
static void cont__format_number_8(void);
static void cont__format_number_9(void);
static void cont__format_number_10(void);
static NODE *func__format_number_11;
static void entry__format_number_11(void);
static FRAME_INFO frame__format_number_11 = {3, {"n", "i", "val"}};
static void cont__format_number_12(void);
static void cont__format_number_13(void);
static NODE *string__578a5af303e9cc1;
static void cont__format_number_15(void);
static void cont__format_number_16(void);
static void cont__format_number_17(void);
static void cont__format_number_18(void);
static void cont__format_number_19(void);
static void cont__format_number_20(void);
static NODE *func__format_number_21;
static void entry__format_number_21(void);
static FRAME_INFO frame__format_number_21 = {3, {"val", "m", "ac"}};
static void cont__format_number_22(void);
static NODE *string__578a5af303e9cd1;
static void cont__format_number_24(void);
static void cont__format_number_25(void);
static NODE *func__format_number_26;
static void entry__format_number_26(void);
static FRAME_INFO frame__format_number_26 = {3, {"m", "ac", "val"}};
static void cont__format_number_27(void);
static NODE *func__format_number_28;
static void entry__format_number_28(void);
static FRAME_INFO frame__format_number_28 = {3, {"val", "ac", "m"}};
static void cont__format_number_29(void);
static void cont__format_number_30(void);
static void cont__format_number_31(void);
static void cont__format_number_32(void);
static void cont__format_number_33(void);
static NODE *func__compiler__write_timing_info;
static void entry__compiler__write_timing_info(void);
static FRAME_INFO frame__compiler__write_timing_info = {3, {"description", "filename", "new_t"}};
static void cont__compiler__write_timing_info_2(void);
static void cont__compiler__write_timing_info_3(void);
static NODE *func__compiler__write_timing_info_4;
static void entry__compiler__write_timing_info_4(void);
static FRAME_INFO frame__compiler__write_timing_info_4 = {3, {"filename", "description", "new_t"}};
static void cont__compiler__write_timing_info_5(void);
static void cont__compiler__write_timing_info_6(void);
static void cont__compiler__write_timing_info_7(void);
static void cont__compiler__write_timing_info_8(void);
static void cont__compiler__write_timing_info_9(void);
static void cont__compiler__write_timing_info_10(void);
static void cont__compiler__write_timing_info_11(void);
static NODE *string__2d7981f4e6082bb6;
static NODE *func__compiler__write_timing_info_13;
static void entry__compiler__write_timing_info_13(void);
static FRAME_INFO frame__compiler__write_timing_info_13 = {2, {"description", "new_t"}};
static void cont__compiler__write_timing_info_14(void);
static void cont__compiler__write_timing_info_15(void);
static NODE *string__2d7981f4e6d82be5;
static void cont__compiler__write_timing_info_17(void);
static void cont__compiler__write_timing_info_18(void);
static NODE *get__compiler__write_timing_info(void) {
  return var.compiler__write_timing_info;
}
static NODE *func__build_executable;
static void entry__build_executable(void);
static FRAME_INFO frame__build_executable = {0, {}};
static NODE *func__build_executable_2;
static void entry__build_executable_2(void);
static FRAME_INFO frame__build_executable_2 = {9, {"mod_filename", "mod_name", "exe_filename", "c_filename", "o_filename", "sim_info", "c_info", "c_buf", "zz"}};
static void cont__build_executable_3(void);
static void cont__build_executable_4(void);
static NODE *func__build_executable_5;
static void entry__build_executable_5(void);
static FRAME_INFO frame__build_executable_5 = {1, {"mod_filename"}};
static NODE *string__9e0ae80b5da07d5c;
static void cont__build_executable_7(void);
static NODE *func__build_executable_8;
static void entry__build_executable_8(void);
static FRAME_INFO frame__build_executable_8 = {1, {"mod_filename"}};
static void cont__build_executable_9(void);
static NODE *func__build_executable_10;
static void entry__build_executable_10(void);
static FRAME_INFO frame__build_executable_10 = {1, {"exe_filename"}};
static NODE *string__2f54d80c63c08867;
static void cont__build_executable_12(void);
static void cont__build_executable_13(void);
static void cont__build_executable_14(void);
static void cont__build_executable_15(void);
static void cont__build_executable_16(void);
static void cont__build_executable_17(void);
static NODE *func__build_executable_18;
static void entry__build_executable_18(void);
static FRAME_INFO frame__build_executable_18 = {2, {"c_info", "sim_info"}};
static void cont__build_executable_19(void);
static NODE *func__build_executable_20;
static void entry__build_executable_20(void);
static FRAME_INFO frame__build_executable_20 = {2, {"c_info", "sim_info"}};
static void cont__build_executable_21(void);
static void cont__build_executable_22(void);
static void cont__build_executable_23(void);
static void cont__build_executable_24(void);
static void cont__build_executable_25(void);
static NODE *func__build_executable_26;
static void entry__build_executable_26(void);
static FRAME_INFO frame__build_executable_26 = {6, {"return__1", "mod_name", "c_buf", "c_filename", "o_filename", "c_source"}};
static void cont__build_executable_27(void);
static void cont__build_executable_28(void);
static NODE *func__build_executable_29;
static void entry__build_executable_29(void);
static FRAME_INFO frame__build_executable_29 = {0, {}};
static NODE *string__b2077c434c011020;
static void cont__build_executable_31(void);
static NODE *func__build_executable_32;
static void entry__build_executable_32(void);
static FRAME_INFO frame__build_executable_32 = {0, {}};
static void cont__build_executable_33(void);
static void cont__build_executable_34(void);
static NODE *func__build_executable_35;
static void entry__build_executable_35(void);
static FRAME_INFO frame__build_executable_35 = {1, {"c_source"}};
static void cont__build_executable_36(void);
static void cont__build_executable_37(void);
static void cont__build_executable_38(void);
static NODE *func__build_executable_39;
static void entry__build_executable_39(void);
static FRAME_INFO frame__build_executable_39 = {1, {"c_filename"}};
static NODE *string__741f540901ca42b0;
static void cont__build_executable_41(void);
static void cont__build_executable_42(void);
static NODE *func__build_executable_43;
static void entry__build_executable_43(void);
static FRAME_INFO frame__build_executable_43 = {1, {"c_filename"}};
static NODE *string__768424e48173e522;
static void cont__build_executable_45(void);
static NODE *func__build_executable_46;
static void entry__build_executable_46(void);
static FRAME_INFO frame__build_executable_46 = {5, {"c_buf", "c_filename", "o_filename", "c_info", "o_info"}};
static void cont__build_executable_47(void);
static void cont__build_executable_48(void);
static void cont__build_executable_49(void);
static NODE *func__build_executable_50;
static void entry__build_executable_50(void);
static FRAME_INFO frame__build_executable_50 = {2, {"o_info", "c_info"}};
static void cont__build_executable_51(void);
static void cont__build_executable_52(void);
static void cont__build_executable_53(void);
static void cont__build_executable_54(void);
static NODE *func__build_executable_55;
static void entry__build_executable_55(void);
static FRAME_INFO frame__build_executable_55 = {2, {"c_filename", "o_filename"}};
static NODE *func__build_executable_56;
static void entry__build_executable_56(void);
static FRAME_INFO frame__build_executable_56 = {1, {"o_info"}};
static void cont__build_executable_57(void);
static void cont__build_executable_58(void);
static void cont__build_executable_59(void);
static NODE *func__build_executable_60;
static void entry__build_executable_60(void);
static FRAME_INFO frame__build_executable_60 = {0, {}};
static NODE *string__953de9f4b96a8381;
static NODE *string__933de8f439d2438a;
static NODE *string__5e90e5234c539c5c;
static void cont__build_executable_64(void);
static NODE *func__build_executable_65;
static void entry__build_executable_65(void);
static FRAME_INFO frame__build_executable_65 = {1, {"filename"}};
static void cont__build_executable_66(void);
static NODE *func__build_executable_67;
static void entry__build_executable_67(void);
static FRAME_INFO frame__build_executable_67 = {2, {"exe_filename", "info"}};
static void cont__build_executable_68(void);
static void cont__build_executable_69(void);
static NODE *func__build_executable_70;
static void entry__build_executable_70(void);
static FRAME_INFO frame__build_executable_70 = {1, {"info"}};
static void cont__build_executable_71(void);
static NODE *func__build_executable_72;
static void entry__build_executable_72(void);
static FRAME_INFO frame__build_executable_72 = {1, {"info"}};
static void cont__build_executable_73(void);
static void cont__build_executable_74(void);
static void cont__build_executable_75(void);
static void cont__build_executable_76(void);
static NODE *func__build_executable_77;
static void entry__build_executable_77(void);
static FRAME_INFO frame__build_executable_77 = {0, {}};
static void cont__build_executable_78(void);
static NODE *func__build_executable_79;
static void entry__build_executable_79(void);
static FRAME_INFO frame__build_executable_79 = {2, {"exe_filename", "libs_and_files"}};
static void cont__build_executable_80(void);
static NODE *func__build_executable_81;
static void entry__build_executable_81(void);
static FRAME_INFO frame__build_executable_81 = {1, {"libs_and_files"}};
static NODE *string__90bd5a08cc7284bc;
static void cont__build_executable_83(void);
static void cont__build_executable_84(void);
static NODE *func__build_executable_85;
static void entry__build_executable_85(void);
static FRAME_INFO frame__build_executable_85 = {5, {"libs_and_files", "exe_filename", "out", "err", "success"}};
static NODE *func__build_executable_86;
static void entry__build_executable_86(void);
static FRAME_INFO frame__build_executable_86 = {0, {}};
static NODE *string__1c7944ac5cc9c4ce;
static void cont__build_executable_88(void);
static NODE *string__5aa0e0654e0a7d41;
static NODE *string__7490e2a4ce0a3d61;
static NODE *string__14e71717a54948bc;
static void cont__build_executable_92(void);
static NODE *func__build_executable_93;
static void entry__build_executable_93(void);
static FRAME_INFO frame__build_executable_93 = {1, {"err"}};
static void cont__build_executable_94(void);
static NODE *func__build_executable_95;
static void entry__build_executable_95(void);
static FRAME_INFO frame__build_executable_95 = {5, {"libs_and_files", "exe_filename", "out", "err", "success"}};
static NODE *func__build_executable_96;
static void entry__build_executable_96(void);
static FRAME_INFO frame__build_executable_96 = {0, {}};
static NODE *string__dca31b2eba5c04a5;
static void cont__build_executable_98(void);
static void cont__build_executable_99(void);
static void cont__build_executable_100(void);
static NODE *func__build_executable_101;
static void entry__build_executable_101(void);
static FRAME_INFO frame__build_executable_101 = {0, {}};
static NODE *string__de26b034bd2c8693;
static void cont__build_executable_103(void);
static NODE *func__build_executable_104;
static void entry__build_executable_104(void);
static FRAME_INFO frame__build_executable_104 = {0, {}};
static void cont__build_executable_105(void);
static void cont__build_executable_106(void);
static void cont__build_executable_107(void);
static NODE *func__build_executable_108;
static void entry__build_executable_108(void);
static FRAME_INFO frame__build_executable_108 = {1, {"err"}};
static void cont__build_executable_109(void);
static void cont__build_executable_110(void);
static void cont__build_executable_111(void);
static void cont__build_executable_112(void);
static NODE *func__build_executable_113;
static void entry__build_executable_113(void);
static FRAME_INFO frame__build_executable_113 = {0, {}};
static void cont__build_executable_114(void);
static void cont__build_executable_115(void);
static NODE *func__build_executable_116;
static void entry__build_executable_116(void);
static FRAME_INFO frame__build_executable_116 = {2, {"exe_filename", "zz"}};
static void cont__build_executable_117(void);
static NODE *func__build_executable_118;
static void entry__build_executable_118(void);
static FRAME_INFO frame__build_executable_118 = {1, {"exe_filename"}};
static NODE *func__build_executable_119;
static void entry__build_executable_119(void);
static FRAME_INFO frame__build_executable_119 = {1, {"exe_filename"}};
static void cont__build_executable_120(void);
static void cont__build_executable_121(void);
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
static NODE *string__a5542a556fe6f2ee;
static void cont__101_2(void);
static void cont__102_1(void);
static void cont__103_1(void);
static void cont__104_1(void);
static NODE *string__578a5af303e9ccf;
static void cont__105_2(void);
static void cont__106_1(void);
static void cont__107_1(void);
static void cont__107_2(void);
static NODE *string__5c5aea03ea80c025;
static void cont__108_2(void);
static NODE *string__55d5804f0e895069;
static void cont__109_2(void);
static NODE *string__2058710183abbfe4;
static void cont__110_2(void);
static void cont__111_1(void);
static void cont__111_2(void);
static NODE *string__1057e106f655c41;
static void cont__111_4(void);
static void cont__111_5(void);
static void cont__111_6(void);
static void cont__112_1(void);
static NODE *func__112_2;
static void entry__112_2(void);
static FRAME_INFO frame__112_2 = {0, {}};
static void cont__112_3(void);
static void cont__112_4(void);
static void cont__112_5(void);
static NODE *func__112_6;
static void entry__112_6(void);
static FRAME_INFO frame__112_6 = {0, {}};
static void cont__112_7(void);
static NODE *func__112_8;
static void entry__112_8(void);
static FRAME_INFO frame__112_8 = {0, {}};
static void cont__112_9(void);
static void cont__113_1(void);
static NODE *func__113_2;
static void entry__113_2(void);
static FRAME_INFO frame__113_2 = {0, {}};
static void cont__113_3(void);
static void cont__113_4(void);
static void cont__113_5(void);
static NODE *func__113_6;
static void entry__113_6(void);
static FRAME_INFO frame__113_6 = {0, {}};
static void cont__113_7(void);
static NODE *func__113_8;
static void entry__113_8(void);
static FRAME_INFO frame__113_8 = {0, {}};
static void cont__113_9(void);
static NODE *string__545aefc3ea81102f;
static void cont__115_2(void);
static void cont__115_3(void);
static void cont__115_4(void);
static void cont__115_5(void);
static NODE *string__fa720015d496ba0;
static void cont__115_7(void);
static NODE *string__fa725815d616ba2;
static void cont__115_9(void);
static void cont__115_10(void);
static void cont__115_11(void);
static NODE *func__117_1;
static void entry__117_1(void);
static FRAME_INFO frame__117_1 = {2, {"platform", "priority"}};
static void cont__117_2(void);
static NODE *func__117_3;
static void entry__117_3(void);
static FRAME_INFO frame__117_3 = {3, {"break", "platform", "priority"}};
static NODE *func__117_4;
static void entry__117_4(void);
static FRAME_INFO frame__117_4 = {4, {"platform", "break", "priority", "plat"}};
static void cont__117_5(void);
static void cont__117_6(void);
static void cont__117_7(void);
static void cont__117_8(void);
static void cont__117_9(void);
static void cont__117_10(void);
static void cont__117_11(void);
static void cont__117_12(void);
static void cont__117_13(void);
static void cont__146_1(void);
static void cont__146_2(void);
static void cont__146_3(void);
static void cont__147_1(void);
static NODE *func__147_2;
static void entry__147_2(void);
static FRAME_INFO frame__147_2 = {0, {}};
static void cont__147_3(void);
static NODE *func__147_4;
static void entry__147_4(void);
static FRAME_INFO frame__147_4 = {0, {}};
static NODE *string__8d3c5e4b22d2f22b;
static void cont__147_6(void);
static void cont__147_7(void);
static NODE *func__147_8;
static void entry__147_8(void);
static FRAME_INFO frame__147_8 = {0, {}};
static NODE *func__147_9;
static void entry__147_9(void);
static FRAME_INFO frame__147_9 = {0, {}};
static NODE *string__2b680b9e2e4fa558;
static NODE *string__8d1eb0934cb703aa;
static NODE *func__147_12;
static void entry__147_12(void);
static FRAME_INFO frame__147_12 = {0, {}};
static NODE *string__1124317d33023452;
static NODE *string__d3c3199b9e37dd88;
static NODE *func__147_15;
static void entry__147_15(void);
static FRAME_INFO frame__147_15 = {0, {}};
static NODE *string__2eb9522bce550419;
static NODE *string__31ed31d8e6f28138;
static NODE *func__147_18;
static void entry__147_18(void);
static FRAME_INFO frame__147_18 = {0, {}};
static NODE *string__23efc30ce16df2e;
static NODE *string__c565f1870e113429;
static NODE *func__147_21;
static void entry__147_21(void);
static FRAME_INFO frame__147_21 = {0, {}};
static NODE *string__9e080c95152a208e;
static NODE *string__ef1e4341946f6b23;
static NODE *func__147_24;
static void entry__147_24(void);
static FRAME_INFO frame__147_24 = {0, {}};
static NODE *string__ae4408db97d25099;
static NODE *string__2623b8ba9cf2f994;
static NODE *func__147_27;
static void entry__147_27(void);
static FRAME_INFO frame__147_27 = {0, {}};
static NODE *string__a7e97d93a221bbf6;
static NODE *string__fa3ca2557b3c0271;
static NODE *func__147_30;
static void entry__147_30(void);
static FRAME_INFO frame__147_30 = {0, {}};
static NODE *string__c95e7978381b7632;
static NODE *string__4cca41e5ff59895a;
static NODE *func__147_33;
static void entry__147_33(void);
static FRAME_INFO frame__147_33 = {0, {}};
static NODE *string__6e5ae943eae03031;
static NODE *string__22ca0f65643a26b5;
static NODE *func__147_36;
static void entry__147_36(void);
static FRAME_INFO frame__147_36 = {0, {}};
static NODE *string__7c90ae5f04ed72b3;
static NODE *string__ea6d59fa9dcad709;
static NODE *func__147_39;
static void entry__147_39(void);
static FRAME_INFO frame__147_39 = {0, {}};
static NODE *string__94300f9615cbf09d;
static NODE *string__aa7c4ea56fedf95b;
static NODE *func__147_42;
static void entry__147_42(void);
static FRAME_INFO frame__147_42 = {0, {}};
static NODE *string__a8480d98152a1083;
static NODE *string__10671df6f7523277;
static NODE *func__147_45;
static void entry__147_45(void);
static FRAME_INFO frame__147_45 = {0, {}};
static NODE *string__b65c0e101523e09f;
static NODE *string__2ba4a5a9cdae43b8;
static NODE *func__147_48;
static void entry__147_48(void);
static FRAME_INFO frame__147_48 = {0, {}};
static NODE *string__405aeb83ea605030;
static NODE *string__977692d258cc57f;
static NODE *func__147_51;
static void entry__147_51(void);
static FRAME_INFO frame__147_51 = {0, {}};
static NODE *string__d13d993479731341;
static NODE *string__d30c0a59c3d26b04;
static NODE *func__147_54;
static void entry__147_54(void);
static FRAME_INFO frame__147_54 = {0, {}};
static NODE *string__2b7008daa973b572;
static NODE *string__99c92c9b20cfd38;
static NODE *func__147_57;
static void entry__147_57(void);
static FRAME_INFO frame__147_57 = {0, {}};
static NODE *string__7f0dce6ce0a2268e;
static NODE *string__140146cb87bc0040;
static NODE *func__147_60;
static void entry__147_60(void);
static FRAME_INFO frame__147_60 = {0, {}};
static NODE *string__4101bf3c8d3115de;
static NODE *string__7cd3f9ecb224e231;
static NODE *func__147_63;
static void entry__147_63(void);
static FRAME_INFO frame__147_63 = {0, {}};
static NODE *string__211e9dd763481194;
static NODE *string__1214925be130f2c;
static NODE *func__147_66;
static void entry__147_66(void);
static FRAME_INFO frame__147_66 = {0, {}};
static NODE *string__984c0f9015dae09e;
static NODE *string__6ce7f8f6c7e73eb4;
static NODE *func__147_69;
static void entry__147_69(void);
static FRAME_INFO frame__147_69 = {0, {}};
static NODE *string__749427e68da7a564;
static NODE *string__93608261e3431133;
static NODE *func__147_72;
static void entry__147_72(void);
static FRAME_INFO frame__147_72 = {0, {}};
static NODE *string__5a1f534901f312b4;
static NODE *string__b20e03a80d6db737;
static NODE *func__147_75;
static void entry__147_75(void);
static FRAME_INFO frame__147_75 = {0, {}};
static NODE *string__be440f9b95da309f;
static NODE *string__6f1f4f6107c9cdea;
static NODE *func__147_78;
static void entry__147_78(void);
static FRAME_INFO frame__147_78 = {0, {}};
static NODE *string__72b0ad9004bdc085;
static NODE *string__bb8770c27da8f42f;
static NODE *func__147_81;
static void entry__147_81(void);
static FRAME_INFO frame__147_81 = {0, {}};
static NODE *string__af5ae49d07a6e408;
static NODE *string__c8a7274dc08e5785;
static void cont__147_84(void);
static void cont__147_85(void);
static NODE *func__148_1;
static void entry__148_1(void);
static FRAME_INFO frame__148_1 = {0, {}};
static NODE *func__148_2;
static void entry__148_2(void);
static FRAME_INFO frame__148_2 = {0, {}};
static void cont__148_3(void);
static void cont__148_4(void);
static void cont__148_5(void);
static NODE *func__148_6;
static void entry__148_6(void);
static FRAME_INFO frame__148_6 = {0, {}};
static NODE *string__c6fd3eab70990d61;
static void cont__148_8(void);
static void cont__149_1(void);
static void cont__150_1(void);
static NODE *func__152_1;
static void entry__152_1(void);
static FRAME_INFO frame__152_1 = {0, {}};
static void cont__152_2(void);
static void cont__157_1(void);
static NODE *string__245aeb43eaacc03b;
static NODE *string__e381a5286a12b5a7;
static NODE *string__c9d1a7e66a0a17ac;
static NODE *string__1abcc193f1dac47a;
static NODE *string__d3e88c522110dabb;
static NODE *string__65a7cd1120033166;
static NODE *string__465ae703eb84c014;
static NODE *string__fa733015c516bfd;
static NODE *string__40ebeb253b72cf38;
static NODE *string__edf2e5a02a882fc3;
static void cont__158_11(void);
static void cont__159_1(void);
static NODE *string__fa721815d316baf;
static void cont__159_3(void);
static NODE *func__159_4;
static void entry__159_4(void);
static FRAME_INFO frame__159_4 = {0, {}};
static NODE *string__ecde9da404625e23;
static void cont__159_6(void);
static void cont__159_7(void);
static void cont__160_1(void);
static NODE *string__f41f598c8327d2e5;
static NODE *string__f41f598c830fd2e3;
static void cont__160_4(void);
static NODE *func__160_5;
static void entry__160_5(void);
static FRAME_INFO frame__160_5 = {0, {}};
static NODE *string__7e1f52a6019282e5;
static void cont__160_7(void);
static NODE *string__70d94c874a06872f;
static void cont__160_9(void);
static void cont__160_10(void);
static NODE *func__161_1;
static void entry__161_1(void);
static FRAME_INFO frame__161_1 = {1, {"path"}};
static NODE *string__2d7981f4e6602b8c;
static void cont__161_3(void);
static void cont__161_4(void);
static void cont__161_5(void);
static void cont__163_1(void);
static void cont__163_2(void);
static NODE *func__163_3;
static void entry__163_3(void);
static FRAME_INFO frame__163_3 = {1, {"option"}};
static void cont__163_4(void);
static void cont__163_5(void);
static void cont__165_1(void);
static void cont__165_2(void);
static NODE *func__165_3;
static void entry__165_3(void);
static FRAME_INFO frame__165_3 = {1, {"option"}};
static void cont__165_4(void);
static void cont__165_5(void);
static void cont__183_1(void);
static NODE *func__183_2;
static void entry__183_2(void);
static FRAME_INFO frame__183_2 = {0, {}};
static NODE *string__9b6a42533552c66c;
static NODE *string__79c06fde49ef2e97;
static void cont__183_5(void);
static void cont__183_6(void);
static NODE *func__198_1;
static void entry__198_1(void);
static FRAME_INFO frame__198_1 = {0, {}};
static void cont__198_2(void);
static void cont__198_3(void);
static NODE *func__199_1;
static void entry__199_1(void);
static FRAME_INFO frame__199_1 = {0, {}};
static NODE *func__199_2;
static void entry__199_2(void);
static FRAME_INFO frame__199_2 = {0, {}};
static NODE *func__199_3;
static void entry__199_3(void);
static FRAME_INFO frame__199_3 = {0, {}};
static NODE *func__199_4;
static void entry__199_4(void);
static FRAME_INFO frame__199_4 = {0, {}};
static void cont__199_5(void);
static void cont__199_6(void);
static void cont__199_7(void);
static NODE *func__199_8;
static void entry__199_8(void);
static FRAME_INFO frame__199_8 = {0, {}};
static NODE *func__199_9;
static void entry__199_9(void);
static FRAME_INFO frame__199_9 = {0, {}};
static NODE *func__199_10;
static void entry__199_10(void);
static FRAME_INFO frame__199_10 = {0, {}};
static NODE *func__199_11;
static void entry__199_11(void);
static FRAME_INFO frame__199_11 = {0, {}};
static void cont__199_12(void);
static void cont__199_13(void);
static void cont__200_1(void);
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
  {cont__run__runtime_definitions, NULL, 75, 94, 1, 62},
  {cont__101_2, NULL, 95, 95, 1, 30},
  {cont__102_1, NULL, 96, 96, 1, 30},
  {cont__103_1, NULL, 97, 97, 1, 30},
  {cont__104_1, NULL, 98, 98, 1, 37},
  {cont__105_2, NULL, 99, 99, 1, 15},
  {cont__106_1, NULL, 100, 100, 12, 23},
  {cont__107_1, NULL, 100, 100, 1, 23},
  {cont__107_2, NULL, 101, 101, 1, 72},
  {cont__108_2, NULL, 102, 102, 1, 37},
  {cont__109_2, NULL, 103, 103, 1, 39},
  {cont__110_2, NULL, 104, 104, 28, 35},
  {cont__111_1, NULL, 104, 104, 58, 74},
  {cont__111_2, NULL, 104, 104, 37, 76},
  {cont__111_4, NULL, 104, 104, 21, 77},
  {cont__111_5, NULL, 104, 104, 1, 78},
  {cont__111_6, NULL, 108, 108, 5, 25},
  {cont__112_1, NULL, 108, 108, 5, 45},
  {cont__112_5, NULL, 106, 110, 1, 21},
  {cont__112_9, NULL, 114, 114, 5, 26},
  {cont__113_1, NULL, 114, 114, 5, 47},
  {cont__113_5, NULL, 112, 116, 1, 21},
  {cont__113_9, NULL, 122, 122, 5, 19},
  {cont__115_2, NULL, 123, 123, 5, 22},
  {cont__115_3, NULL, 124, 124, 5, 22},
  {cont__115_4, NULL, 125, 125, 5, 21},
  {cont__115_5, NULL, 126, 126, 5, 19},
  {cont__115_7, NULL, 127, 127, 5, 17},
  {cont__115_9, NULL, 128, 128, 5, 16},
  {cont__115_10, NULL, 120, 128, 1, 17},
  {cont__115_11, NULL, 131, 141, 1, 22},
  {cont__117_13, NULL, 170, 170, 42, 42},
  {cont__146_1, NULL, 170, 170, 9, 43},
  {cont__146_2, NULL, 170, 170, 1, 63},
  {cont__146_3, NULL, 172, 172, 3, 20},
  {cont__147_1, NULL, 171, 264, 1, 79},
  {cont__147_85, NULL, },
  {cont__148_5, NULL, 265, 271, 1, 31},
  {cont__148_8, NULL, 272, 272, 1, 39},
  {cont__149_1, NULL, 273, 273, 1, 30},
  {cont__150_1, NULL, 275, 275, 1, 37},
  {cont__152_2, NULL, 284, 284, 1, 21},
  {cont__157_1, NULL, 286, 297, 1, 27},
  {cont__158_11, NULL, 299, 299, 4, 15},
  {cont__159_1, NULL, 299, 299, 4, 24},
  {cont__159_3, NULL, 299, 299, 1, 69},
  {cont__159_7, NULL, 300, 300, 6, 28},
  {cont__160_1, NULL, 300, 300, 30, 47},
  {cont__160_4, NULL, 300, 302, 1, 33},
  {cont__160_10, NULL, 303, 303, 1, 58},
  {cont__161_5, NULL, 305, 305, 16, 25},
  {cont__163_1, NULL, 305, 305, 10, 26},
  {cont__163_2, NULL, 305, 305, 1, 61},
  {cont__163_5, NULL, 307, 307, 16, 24},
  {cont__165_1, NULL, 307, 307, 10, 25},
  {cont__165_2, NULL, 307, 307, 1, 59},
  {cont__165_5, NULL, 656, 656, 4, 25},
  {cont__183_1, NULL, 656, 658, 1, 52},
  {cont__183_6, NULL, 1133, 1133, 1, 36},
  {cont__198_3, NULL, 1134, 1146, 1, 18},
  {cont__199_13, NULL, },
  {cont__200_1, NULL, },
  {entry__compiler__show_compiler_debug_info_2, NULL, 278, 278, 36, 49},
  {entry__compiler__show_compiler_debug_info, NULL, 278, 278, 3, 49},
  {entry__resolve_filename_13, NULL, 325, 325, 37, 80},
  {cont__resolve_filename_14, &frame__resolve_filename_13, 325, 325, 37, 61},
  {cont__resolve_filename_15, &frame__resolve_filename_13, 325, 325, 80, 80},
  {entry__resolve_filename_10, NULL, 324, 324, 13, 41},
  {cont__resolve_filename_11, &frame__resolve_filename_10, 325, 325, 16, 34},
  {cont__resolve_filename_12, &frame__resolve_filename_10, 325, 325, 13, 80},
  {entry__resolve_filename_8, NULL, 323, 323, 14, 33},
  {cont__resolve_filename_9, &frame__resolve_filename_8, 323, 325, 11, 80},
  {entry__resolve_filename_6, NULL, 322, 322, 18, 32},
  {cont__resolve_filename_7, &frame__resolve_filename_6, 322, 325, 9, 81},
  {entry__resolve_filename_4, NULL, 321, 321, 10, 26},
  {cont__resolve_filename_5, &frame__resolve_filename_4, 321, 325, 7, 82},
  {entry__resolve_filename_3, NULL, 320, 325, 5, 83},
  {entry__resolve_filename_20, NULL, 329, 330, 11, 57},
  {cont__resolve_filename_23, &frame__resolve_filename_20, 329, 330, 5, 57},
  {entry__resolve_filename, NULL, 318, 318, 6, 36},
  {cont__resolve_filename_2, &frame__resolve_filename, 318, 325, 3, 84},
  {cont__resolve_filename_16, &frame__resolve_filename, 326, 326, 3, 32},
  {cont__resolve_filename_17, &frame__resolve_filename, 327, 327, 3, 38},
  {cont__resolve_filename_18, &frame__resolve_filename, 328, 328, 6, 25},
  {cont__resolve_filename_19, &frame__resolve_filename, 328, 330, 3, 58},
  {cont__resolve_filename_24, &frame__resolve_filename, 331, 331, 21, 39},
  {cont__resolve_filename_25, &frame__resolve_filename, 331, 331, 6, 40},
  {cont__resolve_filename_26, &frame__resolve_filename, 331, 331, 3, 40},
  {entry__add_module_infos_10, NULL, 349, 349, 56, 77},
  {cont__add_module_infos_11, &frame__add_module_infos_10, 349, 349, 77, 77},
  {entry__add_module_infos_8, NULL, 349, 349, 35, 53},
  {cont__add_module_infos_9, &frame__add_module_infos_8, 349, 349, 32, 77},
  {entry__add_module_infos_6, NULL, 349, 349, 10, 29},
  {cont__add_module_infos_7, &frame__add_module_infos_6, 349, 349, 7, 77},
  {entry__add_module_infos_28, NULL, 355, 355, 41, 65},
  {cont__add_module_infos_29, &frame__add_module_infos_28, 355, 355, 41, 65},
  {entry__add_module_infos_31, NULL, 356, 356, 11, 38},
  {cont__add_module_infos_32, &frame__add_module_infos_31, 356, 356, 49, 49},
  {entry__add_module_infos_15, NULL, 351, 351, 48, 60},
  {cont__add_module_infos_17, &frame__add_module_infos_15, 351, 351, 48, 68},
  {cont__add_module_infos_18, &frame__add_module_infos_15, 351, 351, 9, 69},
  {cont__add_module_infos_19, &frame__add_module_infos_15, 352, 352, 9, 34},
  {cont__add_module_infos_20, &frame__add_module_infos_15, 353, 353, 22, 36},
  {cont__add_module_infos_21, &frame__add_module_infos_15, 353, 353, 38, 62},
  {cont__add_module_infos_22, &frame__add_module_infos_15, 353, 353, 22, 62},
  {cont__add_module_infos_23, &frame__add_module_infos_15, 353, 353, 22, 64},
  {cont__add_module_infos_24, &frame__add_module_infos_15, 353, 353, 9, 67},
  {cont__add_module_infos_25, &frame__add_module_infos_15, 354, 354, 9, 49},
  {cont__add_module_infos_26, &frame__add_module_infos_15, 355, 355, 12, 36},
  {cont__add_module_infos_27, &frame__add_module_infos_15, 355, 355, 12, 65},
  {cont__add_module_infos_30, &frame__add_module_infos_15, 355, 356, 9, 49},
  {cont__add_module_infos_33, &frame__add_module_infos_15, 357, 357, 9, 52},
  {cont__add_module_infos_34, &frame__add_module_infos_15, 358, 358, 9, 26},
  {cont__add_module_infos_35, &frame__add_module_infos_15, 359, 359, 9, 43},
  {cont__add_module_infos_36, &frame__add_module_infos_15, 360, 360, 9, 30},
  {cont__add_module_infos_37, &frame__add_module_infos_15, 360, 360, 52, 52},
  {entry__add_module_infos_12, NULL, 350, 350, 10, 33},
  {cont__add_module_infos_14, &frame__add_module_infos_12, 350, 360, 7, 52},
  {entry__add_module_infos_4, NULL, 347, 347, 5, 33},
  {cont__add_module_infos_5, &frame__add_module_infos_4, 348, 360, 5, 53},
  {entry__add_module_infos_49, NULL, 366, 366, 38, 60},
  {cont__add_module_infos_50, &frame__add_module_infos_49, 366, 366, 60, 60},
  {entry__add_module_infos_45, NULL, 365, 365, 11, 54},
  {cont__add_module_infos_47, &frame__add_module_infos_45, 366, 366, 14, 35},
  {cont__add_module_infos_48, &frame__add_module_infos_45, 366, 366, 11, 60},
  {entry__add_module_infos_57, NULL, 373, 374, 17, 57},
  {cont__add_module_infos_60, &frame__add_module_infos_57, 373, 374, 11, 57},
  {entry__add_module_infos_67, NULL, 378, 378, 11, 34},
  {cont__add_module_infos_68, &frame__add_module_infos_67, 379, 379, 11, 45},
  {cont__add_module_infos_69, &frame__add_module_infos_67, 379, 379, 45, 45},
  {entry__add_module_infos_64, NULL, 377, 377, 18, 31},
  {cont__add_module_infos_65, &frame__add_module_infos_64, 377, 377, 18, 31},
  {cont__add_module_infos_66, &frame__add_module_infos_64, 377, 379, 15, 45},
  {entry__add_module_infos_44, NULL, 368, 368, 9, 35},
  {cont__add_module_infos_51, &frame__add_module_infos_44, 369, 369, 35, 58},
  {cont__add_module_infos_52, &frame__add_module_infos_44, 369, 369, 9, 59},
  {cont__add_module_infos_53, &frame__add_module_infos_44, 370, 370, 9, 39},
  {cont__add_module_infos_54, &frame__add_module_infos_44, 371, 371, 9, 46},
  {cont__add_module_infos_55, &frame__add_module_infos_44, 372, 372, 16, 32},
  {cont__add_module_infos_56, &frame__add_module_infos_44, 372, 374, 9, 58},
  {cont__add_module_infos_61, &frame__add_module_infos_44, 375, 375, 9, 30},
  {cont__add_module_infos_62, &frame__add_module_infos_44, 376, 376, 9, 34},
  {cont__add_module_infos_63, &frame__add_module_infos_44, 377, 379, 9, 45},
  {cont__add_module_infos_70, &frame__add_module_infos_44, 380, 380, 10, 30},
  {cont__add_module_infos_71, &frame__add_module_infos_44, 380, 380, 9, 40},
  {cont__add_module_infos_72, &frame__add_module_infos_44, 380, 380, 9, 30},
  {cont__add_module_infos_73, &frame__add_module_infos_44, 380, 380, 46, 46},
  {entry__add_module_infos_41, NULL, 363, 363, 14, 44},
  {cont__add_module_infos_43, &frame__add_module_infos_41, 363, 380, 7, 46},
  {entry__add_module_infos_39, NULL, 362, 362, 8, 30},
  {cont__add_module_infos_40, &frame__add_module_infos_39, 362, 380, 5, 47},
  {entry__add_module_infos_77, NULL, 381, 381, 39, 64},
  {entry__add_module_infos, NULL, 342, 342, 22, 27},
  {cont__add_module_infos_2, &frame__add_module_infos, 342, 342, 3, 33},
  {cont__add_module_infos_3, &frame__add_module_infos, 346, 360, 3, 54},
  {cont__add_module_infos_38, &frame__add_module_infos, 361, 380, 3, 48},
  {cont__add_module_infos_74, &frame__add_module_infos, 381, 381, 6, 31},
  {cont__add_module_infos_75, &frame__add_module_infos, 381, 381, 6, 36},
  {cont__add_module_infos_76, &frame__add_module_infos, 381, 381, 3, 64},
  {cont__add_module_infos_78, &frame__add_module_infos, 381, 381, 64, 64},
  {entry__lookup_4, NULL, 394, 394, 5, 11},
  {entry__lookup_5, NULL, 396, 396, 49, 49},
  {cont__lookup_6, &frame__lookup_5, 396, 396, 24, 50},
  {cont__lookup_7, &frame__lookup_5, 396, 396, 72, 72},
  {cont__lookup_8, &frame__lookup_5, 396, 396, 52, 73},
  {cont__lookup_9, &frame__lookup_5, 396, 396, 7, 73},
  {cont__lookup_10, &frame__lookup_5, 397, 397, 10, 30},
  {cont__lookup_11, &frame__lookup_5, 397, 397, 7, 30},
  {entry__lookup, NULL, 391, 391, 3, 29},
  {cont__lookup_2, &frame__lookup, 393, 393, 5, 19},
  {cont__lookup_3, &frame__lookup, 392, 397, 3, 31},
  {entry__CC_2, NULL, 400, 400, 36, 47},
  {cont__CC_3, &frame__CC_2, 400, 400, 53, 62},
  {cont__CC_4, &frame__CC_2, 400, 400, 27, 62},
  {entry__CC, NULL, 400, 400, 3, 62},
  {cont__CC_5, &frame__CC, 401, 401, 3, 10},
  {entry__compile_c_2, NULL, 404, 404, 41, 60},
  {entry__compile_c_8, NULL, 416, 416, 51, 63},
  {cont__compile_c_9, &frame__compile_c_8, 416, 416, 13, 69},
  {cont__compile_c_12, &frame__compile_c_8, 416, 416, 7, 69},
  {entry__compile_c_4, NULL, 405, 414, 5, 16},
  {cont__compile_c_7, &frame__compile_c_4, 415, 416, 5, 69},
  {cont__compile_c_13, &frame__compile_c_4, 417, 417, 17, 17},
  {entry__compile_c, NULL, 404, 404, 10, 60},
  {cont__compile_c_3, &frame__compile_c, 404, 417, 3, 17},
  {entry__compile_meta_module_25, NULL, 444, 444, 45, 74},
  {cont__compile_meta_module_26, &frame__compile_meta_module_25, 444, 444, 9, 41},
  {cont__compile_meta_module_27, &frame__compile_meta_module_25, 444, 444, 9, 74},
  {cont__compile_meta_module_28, &frame__compile_meta_module_25, 444, 444, 9, 74},
  {entry__compile_meta_module_21, NULL, 443, 443, 43, 75},
  {cont__compile_meta_module_22, &frame__compile_meta_module_21, 443, 443, 9, 39},
  {cont__compile_meta_module_23, &frame__compile_meta_module_21, 443, 443, 9, 75},
  {cont__compile_meta_module_24, &frame__compile_meta_module_21, 444, 444, 9, 74},
  {cont__compile_meta_module_29, &frame__compile_meta_module_21, },
  {entry__compile_meta_module_19, NULL, 442, 442, 9, 32},
  {cont__compile_meta_module_20, &frame__compile_meta_module_19, },
  {cont__compile_meta_module_30, &frame__compile_meta_module_19, },
  {entry__compile_meta_module_17, NULL, 441, 441, 9, 29},
  {cont__compile_meta_module_18, &frame__compile_meta_module_17, },
  {cont__compile_meta_module_31, &frame__compile_meta_module_17, },
  {entry__compile_meta_module_41, NULL, 456, 456, 17, 47},
  {cont__compile_meta_module_42, &frame__compile_meta_module_41, 456, 456, 17, 67},
  {cont__compile_meta_module_43, &frame__compile_meta_module_41, 456, 456, 17, 67},
  {entry__compile_meta_module_45, NULL, 459, 459, 17, 21},
  {entry__compile_meta_module_38, NULL, 452, 452, 13, 42},
  {cont__compile_meta_module_39, &frame__compile_meta_module_38, 455, 455, 17, 38},
  {cont__compile_meta_module_40, &frame__compile_meta_module_38, 454, 456, 15, 67},
  {cont__compile_meta_module_44, &frame__compile_meta_module_38, 453, 459, 13, 22},
  {entry__compile_meta_module_58, NULL, 469, 469, 58, 58},
  {cont__compile_meta_module_59, &frame__compile_meta_module_58, 469, 469, 40, 59},
  {cont__compile_meta_module_60, &frame__compile_meta_module_58, 469, 469, 23, 60},
  {cont__compile_meta_module_61, &frame__compile_meta_module_58, 469, 469, 17, 60},
  {entry__compile_meta_module_63, NULL, 471, 471, 53, 77},
  {cont__compile_meta_module_64, &frame__compile_meta_module_63, 471, 471, 47, 77},
  {entry__compile_meta_module_62, NULL, 471, 471, 17, 77},
  {entry__compile_meta_module_55, NULL, 468, 468, 15, 40},
  {cont__compile_meta_module_57, &frame__compile_meta_module_55, 467, 471, 13, 78},
  {entry__compile_meta_module_37, NULL, 461, 461, 18, 41},
  {cont__compile_meta_module_47, &frame__compile_meta_module_37, 461, 461, 11, 47},
  {cont__compile_meta_module_48, &frame__compile_meta_module_37, 462, 462, 11, 26},
  {cont__compile_meta_module_49, &frame__compile_meta_module_37, 463, 463, 11, 20},
  {cont__compile_meta_module_50, &frame__compile_meta_module_37, 464, 464, 11, 50},
  {cont__compile_meta_module_51, &frame__compile_meta_module_37, 465, 465, 11, 44},
  {cont__compile_meta_module_52, &frame__compile_meta_module_37, 466, 466, 14, 30},
  {cont__compile_meta_module_54, &frame__compile_meta_module_37, 466, 471, 11, 79},
  {entry__compile_meta_module_36, NULL, 450, 471, 9, 80},
  {cont__compile_meta_module_65, &frame__compile_meta_module_36, 471, 471, 80, 80},
  {entry__compile_meta_module_33, NULL, 447, 447, 7, 55},
  {cont__compile_meta_module_34, &frame__compile_meta_module_33, 448, 448, 7, 38},
  {cont__compile_meta_module_35, &frame__compile_meta_module_33, 449, 471, 7, 81},
  {entry__compile_meta_module_74, NULL, 486, 486, 29, 41},
  {cont__compile_meta_module_75, &frame__compile_meta_module_74, 486, 486, 23, 41},
  {entry__compile_meta_module_67, NULL, 480, 480, 7, 36},
  {cont__compile_meta_module_68, &frame__compile_meta_module_67, 481, 481, 7, 22},
  {cont__compile_meta_module_69, &frame__compile_meta_module_67, 482, 482, 7, 31},
  {cont__compile_meta_module_70, &frame__compile_meta_module_67, 483, 483, 7, 32},
  {cont__compile_meta_module_71, &frame__compile_meta_module_67, 484, 484, 7, 43},
  {cont__compile_meta_module_72, &frame__compile_meta_module_67, 485, 485, 7, 32},
  {cont__compile_meta_module_73, &frame__compile_meta_module_67, 486, 486, 7, 41},
  {cont__compile_meta_module_76, &frame__compile_meta_module_67, 487, 487, 25, 35},
  {cont__compile_meta_module_77, &frame__compile_meta_module_67, 487, 487, 7, 35},
  {cont__compile_meta_module_78, &frame__compile_meta_module_67, 487, 487, 35, 35},
  {entry__compile_meta_module_2, NULL, 429, 429, 48, 48},
  {cont__compile_meta_module_3, &frame__compile_meta_module_2, 429, 429, 5, 49},
  {cont__compile_meta_module_4, &frame__compile_meta_module_2, 430, 430, 35, 57},
  {cont__compile_meta_module_5, &frame__compile_meta_module_2, 430, 430, 5, 58},
  {cont__compile_meta_module_6, &frame__compile_meta_module_2, 431, 431, 5, 42},
  {cont__compile_meta_module_7, &frame__compile_meta_module_2, 432, 432, 42, 64},
  {cont__compile_meta_module_8, &frame__compile_meta_module_2, 432, 432, 5, 70},
  {cont__compile_meta_module_10, &frame__compile_meta_module_2, 433, 433, 51, 62},
  {cont__compile_meta_module_11, &frame__compile_meta_module_2, 433, 433, 39, 63},
  {cont__compile_meta_module_12, &frame__compile_meta_module_2, 433, 433, 5, 71},
  {cont__compile_meta_module_13, &frame__compile_meta_module_2, 434, 434, 5, 34},
  {cont__compile_meta_module_14, &frame__compile_meta_module_2, 435, 435, 5, 32},
  {cont__compile_meta_module_15, &frame__compile_meta_module_2, 436, 436, 5, 38},
  {cont__compile_meta_module_16, &frame__compile_meta_module_2, 438, 444, 5, 75},
  {cont__compile_meta_module_32, &frame__compile_meta_module_2, 446, 471, 5, 82},
  {cont__compile_meta_module_66, &frame__compile_meta_module_2, 472, 487, 5, 35},
  {cont__compile_meta_module_79, &frame__compile_meta_module_2, 488, 488, 5, 19},
  {cont__compile_meta_module_80, &frame__compile_meta_module_2, 489, 489, 8, 21},
  {cont__compile_meta_module_81, &frame__compile_meta_module_2, 489, 489, 5, 21},
  {entry__compile_meta_module, NULL, 428, 489, 3, 21},
  {entry__build_dependencies_13, NULL, 513, 513, 43, 43},
  {cont__build_dependencies_14, &frame__build_dependencies_13, 513, 513, 15, 44},
  {cont__build_dependencies_15, &frame__build_dependencies_13, 515, 515, 48, 48},
  {cont__build_dependencies_16, &frame__build_dependencies_13, 515, 515, 24, 49},
  {cont__build_dependencies_17, &frame__build_dependencies_13, 515, 515, 17, 59},
  {cont__build_dependencies_18, &frame__build_dependencies_13, 516, 516, 44, 44},
  {cont__build_dependencies_19, &frame__build_dependencies_13, 516, 516, 24, 45},
  {cont__build_dependencies_20, &frame__build_dependencies_13, 516, 516, 17, 55},
  {cont__build_dependencies_21, &frame__build_dependencies_13, 514, 516, 15, 55},
  {entry__build_dependencies_11, NULL, 512, 512, 16, 26},
  {cont__build_dependencies_12, &frame__build_dependencies_11, 512, 516, 13, 56},
  {entry__build_dependencies_24, NULL, 522, 522, 17, 36},
  {entry__build_dependencies_23, NULL, },
  {cont__build_dependencies_25, &frame__build_dependencies_23, },
  {entry__build_dependencies_27, NULL, 524, 524, 32, 57},
  {cont__build_dependencies_28, &frame__build_dependencies_27, 524, 524, 17, 66},
  {entry__build_dependencies_30, NULL, 527, 527, 44, 71},
  {cont__build_dependencies_31, &frame__build_dependencies_30, 527, 527, 30, 72},
  {cont__build_dependencies_33, &frame__build_dependencies_30, 527, 527, 19, 73},
  {cont__build_dependencies_34, &frame__build_dependencies_30, 527, 527, 78, 78},
  {entry__build_dependencies_29, NULL, 526, 527, 17, 78},
  {entry__build_dependencies_22, NULL, },
  {cont__build_dependencies_26, &frame__build_dependencies_22, 518, 527, 13, 80},
  {entry__build_dependencies_9, NULL, 511, 511, 11, 36},
  {cont__build_dependencies_10, &frame__build_dependencies_9, 510, 527, 9, 82},
  {entry__build_dependencies_36, NULL, 529, 529, 37, 64},
  {cont__build_dependencies_37, &frame__build_dependencies_36, 529, 529, 26, 65},
  {cont__build_dependencies_38, &frame__build_dependencies_36, 529, 529, 70, 70},
  {entry__build_dependencies_35, NULL, 529, 529, 9, 70},
  {entry__build_dependencies_2, NULL, 503, 503, 12, 35},
  {cont__build_dependencies_3, &frame__build_dependencies_2, 503, 503, 5, 42},
  {cont__build_dependencies_4, &frame__build_dependencies_2, 504, 504, 5, 20},
  {cont__build_dependencies_5, &frame__build_dependencies_2, 505, 505, 5, 14},
  {cont__build_dependencies_6, &frame__build_dependencies_2, 506, 506, 5, 44},
  {cont__build_dependencies_7, &frame__build_dependencies_2, 507, 507, 5, 38},
  {cont__build_dependencies_8, &frame__build_dependencies_2, 508, 529, 5, 71},
  {entry__build_dependencies, NULL, 502, 529, 3, 72},
  {cont__build_dependencies_41, &frame__build_dependencies, 529, 529, 72, 72},
  {entry__compile_module_9, NULL, 551, 551, 28, 44},
  {cont__compile_module_10, &frame__compile_module_9, 551, 551, 28, 44},
  {entry__compile_module_12, NULL, 552, 552, 9, 72},
  {entry__compile_module_18, NULL, 557, 558, 15, 54},
  {cont__compile_module_20, &frame__compile_module_18, 557, 558, 9, 54},
  {entry__compile_module_23, NULL, 562, 562, 11, 40},
  {cont__compile_module_24, &frame__compile_module_23, 562, 562, 11, 60},
  {cont__compile_module_25, &frame__compile_module_23, 562, 562, 11, 60},
  {entry__compile_module_27, NULL, 564, 564, 11, 59},
  {cont__compile_module_28, &frame__compile_module_27, 564, 564, 59, 59},
  {entry__compile_module_3, NULL, 549, 549, 7, 45},
  {cont__compile_module_4, &frame__compile_module_3, 550, 550, 58, 58},
  {cont__compile_module_5, &frame__compile_module_3, 550, 550, 34, 59},
  {cont__compile_module_6, &frame__compile_module_3, 550, 550, 7, 75},
  {cont__compile_module_7, &frame__compile_module_3, 551, 551, 10, 23},
  {cont__compile_module_8, &frame__compile_module_3, 551, 551, 10, 44},
  {cont__compile_module_11, &frame__compile_module_3, 551, 552, 7, 72},
  {cont__compile_module_13, &frame__compile_module_3, 553, 553, 7, 53},
  {cont__compile_module_14, &frame__compile_module_3, 554, 554, 7, 38},
  {cont__compile_module_15, &frame__compile_module_3, 555, 555, 7, 34},
  {cont__compile_module_16, &frame__compile_module_3, 556, 556, 14, 32},
  {cont__compile_module_17, &frame__compile_module_3, 556, 558, 7, 55},
  {cont__compile_module_21, &frame__compile_module_3, 561, 561, 11, 40},
  {cont__compile_module_22, &frame__compile_module_3, 560, 562, 9, 60},
  {cont__compile_module_26, &frame__compile_module_3, 559, 564, 7, 60},
  {entry__compile_module_32, NULL, 567, 567, 22, 43},
  {cont__compile_module_33, &frame__compile_module_32, 567, 567, 48, 48},
  {entry__compile_module_37, NULL, 573, 573, 29, 56},
  {cont__compile_module_38, &frame__compile_module_37, 573, 573, 9, 56},
  {cont__compile_module_39, &frame__compile_module_37, 573, 573, 9, 56},
  {entry__compile_module_35, NULL, 572, 572, 9, 27},
  {cont__compile_module_36, &frame__compile_module_35, 573, 573, 9, 56},
  {cont__compile_module_40, &frame__compile_module_35, },
  {entry__compile_module_47, NULL, 576, 576, 21, 63},
  {entry__compile_module_50, NULL, 577, 577, 35, 53},
  {entry__compile_module_52, NULL, 578, 578, 32, 54},
  {entry__compile_module_56, NULL, 580, 580, 26, 56},
  {entry__compile_module_42, NULL, 575, 575, 53, 62},
  {cont__compile_module_44, &frame__compile_module_42, 575, 575, 64, 73},
  {cont__compile_module_45, &frame__compile_module_42, 575, 575, 9, 74},
  {cont__compile_module_46, &frame__compile_module_42, 576, 576, 9, 63},
  {cont__compile_module_49, &frame__compile_module_42, 577, 577, 9, 53},
  {cont__compile_module_51, &frame__compile_module_42, 578, 578, 9, 54},
  {cont__compile_module_53, &frame__compile_module_42, 579, 579, 25, 37},
  {cont__compile_module_54, &frame__compile_module_42, 579, 579, 9, 37},
  {cont__compile_module_55, &frame__compile_module_42, 580, 580, 9, 56},
  {cont__compile_module_57, &frame__compile_module_42, 580, 580, 56, 56},
  {entry__compile_module_62, NULL, 587, 587, 44, 71},
  {cont__compile_module_63, &frame__compile_module_62, 587, 587, 13, 40},
  {cont__compile_module_64, &frame__compile_module_62, 587, 587, 13, 71},
  {cont__compile_module_65, &frame__compile_module_62, 587, 587, 13, 71},
  {entry__compile_module_68, NULL, 589, 589, 30, 60},
  {entry__compile_module_67, NULL, 589, 589, 13, 60},
  {entry__compile_module_71, NULL, 594, 594, 17, 44},
  {cont__compile_module_72, &frame__compile_module_71, 594, 594, 17, 69},
  {cont__compile_module_73, &frame__compile_module_71, 594, 594, 17, 69},
  {entry__compile_module_75, NULL, 596, 596, 17, 68},
  {cont__compile_module_76, &frame__compile_module_75, 596, 596, 68, 68},
  {entry__compile_module_69, NULL, 593, 593, 17, 51},
  {cont__compile_module_70, &frame__compile_module_69, 592, 594, 15, 69},
  {cont__compile_module_74, &frame__compile_module_69, 591, 596, 13, 69},
  {entry__compile_module_58, NULL, 582, 582, 9, 30},
  {cont__compile_module_59, &frame__compile_module_58, 583, 583, 9, 32},
  {cont__compile_module_60, &frame__compile_module_58, 586, 586, 13, 31},
  {cont__compile_module_61, &frame__compile_module_58, 585, 587, 11, 71},
  {cont__compile_module_66, &frame__compile_module_58, 584, 596, 9, 71},
  {entry__compile_module_2, NULL, 548, 564, 5, 61},
  {cont__compile_module_29, &frame__compile_module_2, 565, 565, 5, 48},
  {cont__compile_module_30, &frame__compile_module_2, 566, 566, 5, 28},
  {cont__compile_module_31, &frame__compile_module_2, 567, 567, 5, 48},
  {cont__compile_module_34, &frame__compile_module_2, 568, 568, 5, 21},
  {cont__compile_module_41, &frame__compile_module_2, 569, 596, 5, 73},
  {cont__compile_module_77, &frame__compile_module_2, 597, 597, 5, 63},
  {entry__compile_module_80, NULL, 601, 602, 11, 56},
  {cont__compile_module_83, &frame__compile_module_80, 601, 602, 5, 56},
  {entry__compile_module_92, NULL, 608, 608, 51, 75},
  {cont__compile_module_93, &frame__compile_module_92, 608, 608, 32, 75},
  {cont__compile_module_94, &frame__compile_module_92, 608, 608, 75, 75},
  {entry__compile_module_91, NULL, 608, 608, 7, 75},
  {cont__compile_module_95, &frame__compile_module_91, 609, 609, 59, 59},
  {cont__compile_module_96, &frame__compile_module_91, 609, 609, 30, 60},
  {cont__compile_module_97, &frame__compile_module_91, 609, 609, 25, 61},
  {cont__compile_module_98, &frame__compile_module_91, 609, 609, 7, 61},
  {entry__compile_module_104, NULL, 616, 616, 37, 60},
  {cont__compile_module_105, &frame__compile_module_104, 616, 616, 37, 60},
  {entry__compile_module_107, NULL, 618, 618, 35, 35},
  {entry__compile_module_101, NULL, 615, 615, 11, 47},
  {cont__compile_module_102, &frame__compile_module_101, 616, 616, 14, 32},
  {cont__compile_module_103, &frame__compile_module_101, 616, 616, 14, 60},
  {cont__compile_module_106, &frame__compile_module_101, 616, 618, 11, 35},
  {entry__compile_module_109, NULL, 622, 622, 13, 37},
  {cont__compile_module_110, &frame__compile_module_109, 623, 623, 13, 32},
  {cont__compile_module_111, &frame__compile_module_109, 620, 623, 11, 32},
  {entry__compile_module_100, NULL, 614, 618, 9, 36},
  {cont__compile_module_108, &frame__compile_module_100, 619, 623, 9, 33},
  {entry__compile_module_118, NULL, 631, 631, 39, 62},
  {cont__compile_module_119, &frame__compile_module_118, 631, 631, 39, 62},
  {entry__compile_module_121, NULL, 633, 633, 37, 37},
  {entry__compile_module_115, NULL, 630, 630, 13, 77},
  {cont__compile_module_116, &frame__compile_module_115, 631, 631, 16, 34},
  {cont__compile_module_117, &frame__compile_module_115, 631, 631, 16, 62},
  {cont__compile_module_120, &frame__compile_module_115, 631, 633, 13, 37},
  {entry__compile_module_124, NULL, 635, 635, 32, 53},
  {cont__compile_module_125, &frame__compile_module_124, 635, 635, 13, 65},
  {cont__compile_module_126, &frame__compile_module_124, 636, 636, 13, 39},
  {cont__compile_module_127, &frame__compile_module_124, 637, 637, 13, 35},
  {cont__compile_module_128, &frame__compile_module_124, 637, 637, 38, 38},
  {entry__compile_module_114, NULL, 629, 633, 11, 38},
  {cont__compile_module_122, &frame__compile_module_114, 634, 634, 14, 37},
  {cont__compile_module_123, &frame__compile_module_114, 634, 637, 11, 38},
  {entry__compile_module_135, NULL, 642, 642, 40, 69},
  {cont__compile_module_137, &frame__compile_module_135, 642, 642, 69, 69},
  {entry__compile_module_134, NULL, 642, 642, 13, 69},
  {entry__compile_module_130, NULL, 639, 639, 11, 61},
  {cont__compile_module_131, &frame__compile_module_130, 640, 640, 11, 38},
  {cont__compile_module_132, &frame__compile_module_130, 641, 641, 14, 33},
  {cont__compile_module_133, &frame__compile_module_130, 641, 642, 11, 69},
  {cont__compile_module_138, &frame__compile_module_130, 643, 643, 11, 39},
  {cont__compile_module_139, &frame__compile_module_130, 643, 643, 39, 39},
  {entry__compile_module_113, NULL, 626, 637, 9, 39},
  {cont__compile_module_129, &frame__compile_module_113, 638, 643, 9, 39},
  {entry__compile_module_99, NULL, 611, 623, 7, 34},
  {cont__compile_module_112, &frame__compile_module_99, 624, 643, 7, 40},
  {entry__compile_module, NULL, 599, 599, 3, 40},
  {cont__compile_module_78, &frame__compile_module, 600, 600, 10, 28},
  {cont__compile_module_79, &frame__compile_module, 600, 602, 3, 57},
  {cont__compile_module_84, &frame__compile_module, 603, 603, 3, 39},
  {cont__compile_module_86, &frame__compile_module, 604, 604, 6, 24},
  {cont__compile_module_87, &frame__compile_module, 604, 604, 3, 31},
  {cont__compile_module_88, &frame__compile_module, 605, 605, 3, 22},
  {cont__compile_module_89, &frame__compile_module, 607, 607, 5, 21},
  {cont__compile_module_90, &frame__compile_module, 606, 643, 3, 42},
  {cont__compile_module_140, &frame__compile_module, 643, 643, 42, 42},
  {entry__compile_modules_4, NULL, 652, 652, 21, 41},
  {cont__compile_modules_5, &frame__compile_modules_4, 652, 652, 43, 67},
  {cont__compile_modules_6, &frame__compile_modules_4, 652, 652, 5, 67},
  {entry__compile_modules_8, NULL, 654, 654, 20, 40},
  {cont__compile_modules_9, &frame__compile_modules_8, 654, 654, 42, 66},
  {cont__compile_modules_10, &frame__compile_modules_8, 654, 654, 5, 66},
  {entry__compile_modules, NULL, 650, 650, 47, 66},
  {cont__compile_modules_2, &frame__compile_modules, 650, 650, 3, 66},
  {cont__compile_modules_3, &frame__compile_modules, 651, 652, 3, 67},
  {cont__compile_modules_7, &frame__compile_modules, 653, 654, 3, 66},
  {entry__show_file_list_6, NULL, 663, 663, 34, 58},
  {cont__show_file_list_8, &frame__show_file_list_6, 663, 663, 25, 58},
  {entry__show_file_list_2, NULL, 662, 662, 5, 40},
  {cont__show_file_list_4, &frame__show_file_list_2, 663, 663, 8, 22},
  {cont__show_file_list_5, &frame__show_file_list_2, 663, 663, 5, 58},
  {cont__show_file_list_9, &frame__show_file_list_2, 664, 664, 40, 57},
  {cont__show_file_list_10, &frame__show_file_list_2, 664, 664, 5, 57},
  {cont__show_file_list_12, &frame__show_file_list_2, 665, 665, 35, 54},
  {cont__show_file_list_13, &frame__show_file_list_2, 665, 665, 5, 54},
  {entry__show_file_list, NULL, 661, 665, 3, 54},
  {entry__library_paths_and_file_list_7, NULL, 674, 674, 60, 70},
  {cont__library_paths_and_file_list_9, &frame__library_paths_and_file_list_7, 674, 674, 40, 70},
  {cont__library_paths_and_file_list_10, &frame__library_paths_and_file_list_7, 674, 674, 70, 70},
  {entry__library_paths_and_file_list_5, NULL, 674, 674, 14, 30},
  {cont__library_paths_and_file_list_6, &frame__library_paths_and_file_list_5, 674, 674, 5, 70},
  {entry__library_paths_and_file_list_12, NULL, 675, 675, 54, 77},
  {cont__library_paths_and_file_list_13, &frame__library_paths_and_file_list_12, 675, 675, 27, 77},
  {entry__library_paths_and_file_list_16, NULL, 676, 676, 30, 54},
  {cont__library_paths_and_file_list_17, &frame__library_paths_and_file_list_16, 676, 676, 54, 54},
  {entry__library_paths_and_file_list_26, NULL, 686, 686, 16, 45},
  {cont__library_paths_and_file_list_29, &frame__library_paths_and_file_list_26, 686, 686, 13, 45},
  {entry__library_paths_and_file_list_30, NULL, 687, 687, 16, 38},
  {cont__library_paths_and_file_list_32, &frame__library_paths_and_file_list_30, 687, 687, 13, 38},
  {entry__library_paths_and_file_list_21, NULL, 684, 684, 13, 30},
  {cont__library_paths_and_file_list_22, &frame__library_paths_and_file_list_21, 685, 685, 13, 26},
  {cont__library_paths_and_file_list_25, &frame__library_paths_and_file_list_21, 687, 687, 13, 38},
  {cont__library_paths_and_file_list_33, &frame__library_paths_and_file_list_21, 682, 687, 9, 39},
  {entry__library_paths_and_file_list_36, NULL, 691, 691, 25, 44},
  {cont__library_paths_and_file_list_37, &frame__library_paths_and_file_list_36, 691, 691, 52, 71},
  {cont__library_paths_and_file_list_38, &frame__library_paths_and_file_list_36, 691, 691, 16, 73},
  {cont__library_paths_and_file_list_39, &frame__library_paths_and_file_list_36, 691, 692, 13, 26},
  {entry__library_paths_and_file_list_40, NULL, 693, 693, 16, 29},
  {cont__library_paths_and_file_list_41, &frame__library_paths_and_file_list_40, 693, 693, 13, 29},
  {entry__library_paths_and_file_list_34, NULL, 690, 690, 13, 34},
  {cont__library_paths_and_file_list_35, &frame__library_paths_and_file_list_34, 693, 693, 13, 29},
  {cont__library_paths_and_file_list_42, &frame__library_paths_and_file_list_34, 688, 693, 9, 30},
  {entry__library_paths_and_file_list_19, NULL, 681, 681, 9, 35},
  {cont__library_paths_and_file_list_20, &frame__library_paths_and_file_list_19, 688, 693, 9, 30},
  {cont__library_paths_and_file_list_43, &frame__library_paths_and_file_list_19, 678, 693, 5, 32},
  {cont__library_paths_and_file_list_44, &frame__library_paths_and_file_list_19, 693, 693, 33, 33},
  {entry__library_paths_and_file_list, NULL, 668, 668, 3, 16},
  {cont__library_paths_and_file_list_2, &frame__library_paths_and_file_list, 672, 672, 3, 39},
  {cont__library_paths_and_file_list_3, &frame__library_paths_and_file_list, 673, 673, 6, 21},
  {cont__library_paths_and_file_list_4, &frame__library_paths_and_file_list, 673, 674, 3, 70},
  {cont__library_paths_and_file_list_11, &frame__library_paths_and_file_list, 675, 675, 3, 77},
  {cont__library_paths_and_file_list_15, &frame__library_paths_and_file_list, 676, 676, 3, 54},
  {cont__library_paths_and_file_list_18, &frame__library_paths_and_file_list, 677, 693, 3, 33},
  {cont__library_paths_and_file_list_45, &frame__library_paths_and_file_list, 694, 694, 24, 57},
  {cont__library_paths_and_file_list_46, &frame__library_paths_and_file_list, 694, 694, 3, 57},
  {entry__create_imports_9, NULL, 704, 704, 51, 64},
  {cont__create_imports_10, &frame__create_imports_9, 704, 704, 51, 64},
  {entry__create_imports_7, NULL, 704, 704, 37, 46},
  {cont__create_imports_8, &frame__create_imports_7, 704, 704, 37, 64},
  {cont__create_imports_11, &frame__create_imports_7, 704, 704, 37, 64},
  {entry__create_imports_29, NULL, 715, 715, 25, 59},
  {cont__create_imports_31, &frame__create_imports_29, 715, 715, 21, 60},
  {cont__create_imports_32, &frame__create_imports_29, 715, 715, 21, 60},
  {entry__create_imports_25, NULL, 714, 714, 25, 58},
  {cont__create_imports_27, &frame__create_imports_25, 714, 714, 21, 59},
  {cont__create_imports_28, &frame__create_imports_25, 715, 715, 21, 60},
  {cont__create_imports_33, &frame__create_imports_25, },
  {entry__create_imports_38, NULL, 719, 719, 46, 80},
  {cont__create_imports_39, &frame__create_imports_38, 719, 719, 46, 80},
  {entry__create_imports_41, NULL, 721, 721, 44, 74},
  {cont__create_imports_42, &frame__create_imports_41, 721, 721, 23, 74},
  {entry__create_imports_35, NULL, 719, 719, 21, 34},
  {cont__create_imports_36, &frame__create_imports_35, 719, 719, 21, 41},
  {cont__create_imports_37, &frame__create_imports_35, 719, 719, 21, 80},
  {cont__create_imports_40, &frame__create_imports_35, 718, 721, 19, 75},
  {entry__create_imports_49, NULL, 724, 724, 60, 60},
  {cont__create_imports_50, &frame__create_imports_49, 724, 724, 44, 61},
  {cont__create_imports_51, &frame__create_imports_49, 724, 724, 23, 61},
  {entry__create_imports_46, NULL, 723, 723, 35, 62},
  {cont__create_imports_47, &frame__create_imports_46, 723, 723, 35, 67},
  {cont__create_imports_48, &frame__create_imports_46, 723, 724, 21, 61},
  {entry__create_imports_43, NULL, 722, 722, 22, 62},
  {cont__create_imports_45, &frame__create_imports_43, 722, 724, 19, 62},
  {entry__create_imports_52, NULL, 726, 726, 21, 52},
  {entry__create_imports_54, NULL, 727, 727, 31, 45},
  {entry__create_imports_21, NULL, 713, 713, 21, 34},
  {cont__create_imports_22, &frame__create_imports_21, 713, 713, 21, 41},
  {cont__create_imports_23, &frame__create_imports_21, 713, 713, 21, 41},
  {cont__create_imports_24, &frame__create_imports_21, 711, 715, 17, 61},
  {cont__create_imports_34, &frame__create_imports_21, 717, 726, 17, 53},
  {cont__create_imports_53, &frame__create_imports_21, 727, 727, 17, 45},
  {cont__create_imports_56, &frame__create_imports_21, 728, 728, 17, 33},
  {entry__create_imports_17, NULL, 708, 708, 15, 38},
  {cont__create_imports_18, &frame__create_imports_17, 709, 709, 15, 50},
  {cont__create_imports_19, &frame__create_imports_17, 710, 710, 18, 39},
  {cont__create_imports_20, &frame__create_imports_17, 710, 728, 15, 33},
  {entry__create_imports_13, NULL, 705, 705, 33, 37},
  {cont__create_imports_14, &frame__create_imports_13, 705, 705, 13, 38},
  {cont__create_imports_15, &frame__create_imports_13, 707, 707, 20, 42},
  {cont__create_imports_16, &frame__create_imports_13, 707, 728, 13, 34},
  {entry__create_imports_5, NULL, 704, 704, 18, 32},
  {cont__create_imports_6, &frame__create_imports_5, 704, 704, 18, 64},
  {cont__create_imports_12, &frame__create_imports_5, 704, 728, 11, 35},
  {entry__create_imports_59, NULL, 730, 730, 33, 42},
  {cont__create_imports_60, &frame__create_imports_59, 730, 730, 33, 42},
  {entry__create_imports_62, NULL, 730, 730, 50, 50},
  {entry__create_imports_57, NULL, 730, 730, 14, 28},
  {cont__create_imports_58, &frame__create_imports_57, 730, 730, 14, 42},
  {cont__create_imports_61, &frame__create_imports_57, 730, 730, 11, 50},
  {entry__create_imports_3, NULL, 703, 703, 9, 20},
  {cont__create_imports_4, &frame__create_imports_3, 702, 730, 7, 51},
  {entry__create_imports_2, NULL, 701, 730, 5, 52},
  {entry__create_imports_63, NULL, 732, 732, 28, 54},
  {entry__create_imports_74, NULL, 737, 737, 22, 59},
  {entry__create_imports, NULL, 732, 732, 3, 54},
  {cont__create_imports_64, &frame__create_imports, 733, 733, 3, 49},
  {cont__create_imports_66, &frame__create_imports, 734, 734, 3, 18},
  {cont__create_imports_67, &frame__create_imports, 735, 735, 3, 15},
  {cont__create_imports_68, &frame__create_imports, 736, 736, 22, 42},
  {cont__create_imports_69, &frame__create_imports, 736, 736, 22, 45},
  {cont__create_imports_70, &frame__create_imports, 736, 736, 48, 48},
  {cont__create_imports_71, &frame__create_imports, 736, 736, 9, 49},
  {cont__create_imports_72, &frame__create_imports, 736, 736, 3, 49},
  {cont__create_imports_73, &frame__create_imports, 737, 737, 3, 59},
  {entry__compile_exe_3, NULL, 740, 740, 32, 67},
  {entry__compile_exe_7, NULL, 742, 743, 5, 57},
  {entry__compile_exe, NULL, 740, 740, 6, 29},
  {cont__compile_exe_2, &frame__compile_exe, 740, 740, 3, 67},
  {cont__compile_exe_5, &frame__compile_exe, 741, 741, 10, 42},
  {cont__compile_exe_6, &frame__compile_exe, 741, 743, 3, 58},
  {cont__compile_exe_9, &frame__compile_exe, 745, 745, 3, 53},
  {cont__compile_exe_10, &frame__compile_exe, 746, 746, 46, 46},
  {cont__compile_exe_11, &frame__compile_exe, 746, 746, 3, 47},
  {cont__compile_exe_12, &frame__compile_exe, 747, 747, 3, 28},
  {cont__compile_exe_13, &frame__compile_exe, 747, 747, 28, 28},
  {entry__dump_source_or_check_2, NULL, 752, 752, 11, 29},
  {cont__dump_source_or_check_3, &frame__dump_source_or_check_2, 752, 752, 5, 29},
  {cont__dump_source_or_check_4, &frame__dump_source_or_check_2, 752, 752, 29, 29},
  {entry__dump_source_or_check, NULL, 750, 752, 3, 29},
  {entry__print_c_4, NULL, 756, 756, 41, 65},
  {cont__print_c_5, &frame__print_c_4, 756, 756, 34, 75},
  {cont__print_c_6, &frame__print_c_4, 756, 756, 75, 75},
  {entry__print_c_8, NULL, 758, 758, 51, 60},
  {cont__print_c_9, &frame__print_c_8, 758, 758, 62, 71},
  {cont__print_c_10, &frame__print_c_8, 758, 758, 7, 72},
  {cont__print_c_11, &frame__print_c_8, 759, 759, 13, 31},
  {cont__print_c_12, &frame__print_c_8, 759, 759, 7, 31},
  {cont__print_c_13, &frame__print_c_8, 759, 759, 31, 31},
  {entry__print_c_15, NULL, 760, 760, 28, 50},
  {entry__print_c_18, NULL, 762, 762, 24, 59},
  {entry__print_c_2, NULL, 756, 756, 8, 31},
  {cont__print_c_3, &frame__print_c_2, 756, 756, 5, 75},
  {cont__print_c_7, &frame__print_c_2, 757, 759, 5, 31},
  {cont__print_c_14, &frame__print_c_2, 760, 760, 5, 50},
  {cont__print_c_16, &frame__print_c_2, 761, 761, 5, 15},
  {cont__print_c_17, &frame__print_c_2, 762, 762, 5, 59},
  {entry__print_c, NULL, 755, 762, 3, 59},
  {entry__list_dependencies_5, NULL, 771, 771, 9, 43},
  {cont__list_dependencies_6, &frame__list_dependencies_5, 772, 772, 12, 28},
  {cont__list_dependencies_7, &frame__list_dependencies_5, 772, 772, 9, 34},
  {cont__list_dependencies_8, &frame__list_dependencies_5, 773, 773, 9, 21},
  {cont__list_dependencies_9, &frame__list_dependencies_5, 774, 774, 9, 64},
  {cont__list_dependencies_10, &frame__list_dependencies_5, 775, 775, 12, 23},
  {cont__list_dependencies_11, &frame__list_dependencies_5, 775, 775, 9, 29},
  {cont__list_dependencies_12, &frame__list_dependencies_5, 776, 776, 22, 22},
  {entry__list_dependencies_4, NULL, 770, 776, 7, 22},
  {cont__list_dependencies_13, &frame__list_dependencies_4, 776, 776, 22, 22},
  {entry__list_dependencies_3, NULL, 769, 776, 5, 23},
  {entry__list_dependencies_17, NULL, 780, 780, 19, 65},
  {entry__list_dependencies_16, NULL, 780, 780, 7, 65},
  {cont__list_dependencies_19, &frame__list_dependencies_16, 781, 781, 63, 63},
  {cont__list_dependencies_20, &frame__list_dependencies_16, 781, 781, 37, 64},
  {cont__list_dependencies_21, &frame__list_dependencies_16, 781, 781, 7, 64},
  {cont__list_dependencies_22, &frame__list_dependencies_16, 781, 781, 64, 64},
  {entry__list_dependencies_25, NULL, 784, 784, 21, 66},
  {entry__list_dependencies_24, NULL, 784, 784, 9, 66},
  {cont__list_dependencies_26, &frame__list_dependencies_24, 785, 785, 9, 44},
  {entry__list_dependencies_23, NULL, 783, 785, 7, 44},
  {cont__list_dependencies_27, &frame__list_dependencies_23, 786, 786, 7, 32},
  {cont__list_dependencies_29, &frame__list_dependencies_23, 787, 787, 7, 32},
  {cont__list_dependencies_31, &frame__list_dependencies_23, 788, 788, 7, 34},
  {entry__list_dependencies_35, NULL, 791, 791, 5, 40},
  {cont__list_dependencies_36, &frame__list_dependencies_35, 792, 792, 5, 32},
  {cont__list_dependencies_37, &frame__list_dependencies_35, 793, 793, 5, 20},
  {entry__list_dependencies, NULL, 765, 765, 3, 80},
  {cont__list_dependencies_2, &frame__list_dependencies, 766, 776, 3, 24},
  {cont__list_dependencies_14, &frame__list_dependencies, 778, 778, 5, 28},
  {cont__list_dependencies_15, &frame__list_dependencies, 777, 788, 3, 35},
  {cont__list_dependencies_33, &frame__list_dependencies, 789, 789, 3, 29},
  {cont__list_dependencies_34, &frame__list_dependencies, 790, 793, 3, 20},
  {entry__build_codeblocks_project_7, NULL, 800, 801, 14, 58},
  {cont__build_codeblocks_project_10, &frame__build_codeblocks_project_7, 800, 801, 7, 58},
  {entry__build_codeblocks_project_12, NULL, 802, 802, 17, 73},
  {entry__build_codeblocks_project_38, NULL, 834, 836, 21, 49},
  {cont__build_codeblocks_project_41, &frame__build_codeblocks_project_38, 834, 836, 7, 49},
  {cont__build_codeblocks_project_42, &frame__build_codeblocks_project_38, 836, 836, 50, 50},
  {entry__build_codeblocks_project_52, NULL, 857, 857, 7, 42},
  {cont__build_codeblocks_project_53, &frame__build_codeblocks_project_52, 858, 858, 7, 34},
  {cont__build_codeblocks_project_54, &frame__build_codeblocks_project_52, 859, 864, 21, 23},
  {cont__build_codeblocks_project_57, &frame__build_codeblocks_project_52, 859, 864, 7, 23},
  {cont__build_codeblocks_project_58, &frame__build_codeblocks_project_52, 864, 864, 24, 24},
  {entry__build_codeblocks_project_2, NULL, 797, 797, 5, 55},
  {cont__build_codeblocks_project_4, &frame__build_codeblocks_project_2, 798, 798, 5, 31},
  {cont__build_codeblocks_project_5, &frame__build_codeblocks_project_2, 799, 799, 8, 22},
  {cont__build_codeblocks_project_6, &frame__build_codeblocks_project_2, 799, 801, 5, 59},
  {cont__build_codeblocks_project_11, &frame__build_codeblocks_project_2, 802, 802, 5, 73},
  {cont__build_codeblocks_project_14, &frame__build_codeblocks_project_2, 803, 803, 5, 40},
  {cont__build_codeblocks_project_15, &frame__build_codeblocks_project_2, 804, 804, 5, 18},
  {cont__build_codeblocks_project_16, &frame__build_codeblocks_project_2, 805, 805, 49, 49},
  {cont__build_codeblocks_project_17, &frame__build_codeblocks_project_2, 805, 805, 15, 50},
  {cont__build_codeblocks_project_18, &frame__build_codeblocks_project_2, 805, 805, 5, 74},
  {cont__build_codeblocks_project_19, &frame__build_codeblocks_project_2, 806, 806, 5, 31},
  {cont__build_codeblocks_project_20, &frame__build_codeblocks_project_2, 807, 807, 30, 73},
  {cont__build_codeblocks_project_21, &frame__build_codeblocks_project_2, 807, 807, 5, 78},
  {cont__build_codeblocks_project_22, &frame__build_codeblocks_project_2, 808, 808, 5, 33},
  {cont__build_codeblocks_project_24, &frame__build_codeblocks_project_2, 809, 809, 5, 61},
  {cont__build_codeblocks_project_27, &frame__build_codeblocks_project_2, 810, 810, 5, 25},
  {cont__build_codeblocks_project_28, &frame__build_codeblocks_project_2, 819, 819, 35, 46},
  {cont__build_codeblocks_project_29, &frame__build_codeblocks_project_2, 826, 826, 43, 54},
  {cont__build_codeblocks_project_30, &frame__build_codeblocks_project_2, 812, 832, 19, 22},
  {cont__build_codeblocks_project_36, &frame__build_codeblocks_project_2, 812, 832, 5, 22},
  {cont__build_codeblocks_project_37, &frame__build_codeblocks_project_2, 833, 836, 5, 50},
  {cont__build_codeblocks_project_43, &frame__build_codeblocks_project_2, 837, 855, 19, 21},
  {cont__build_codeblocks_project_50, &frame__build_codeblocks_project_2, 837, 855, 5, 21},
  {cont__build_codeblocks_project_51, &frame__build_codeblocks_project_2, 856, 864, 5, 24},
  {cont__build_codeblocks_project_59, &frame__build_codeblocks_project_2, 865, 871, 5, 32},
  {cont__build_codeblocks_project_61, &frame__build_codeblocks_project_2, 872, 872, 5, 25},
  {entry__build_codeblocks_project, NULL, 796, 872, 3, 25},
  {entry__build_library_4, NULL, 875, 875, 26, 56},
  {entry__build_library_10, NULL, 881, 881, 29, 45},
  {cont__build_library_11, &frame__build_library_10, 881, 881, 9, 45},
  {cont__build_library_12, &frame__build_library_10, 881, 881, 45, 45},
  {entry__build_library_8, NULL, 879, 879, 7, 41},
  {cont__build_library_9, &frame__build_library_8, 880, 881, 7, 45},
  {cont__build_library_13, &frame__build_library_8, 882, 882, 7, 41},
  {entry__build_library_7, NULL, 878, 882, 5, 41},
  {entry__build_library_17, NULL, 886, 886, 29, 45},
  {cont__build_library_18, &frame__build_library_17, 886, 886, 9, 45},
  {cont__build_library_19, &frame__build_library_17, 886, 886, 45, 45},
  {entry__build_library_15, NULL, 884, 884, 7, 41},
  {cont__build_library_16, &frame__build_library_15, 885, 886, 7, 45},
  {cont__build_library_20, &frame__build_library_15, 887, 887, 7, 35},
  {entry__build_library_14, NULL, 883, 887, 5, 35},
  {entry__build_library_25, NULL, 892, 892, 29, 50},
  {cont__build_library_26, &frame__build_library_25, 892, 892, 29, 55},
  {cont__build_library_27, &frame__build_library_25, 892, 892, 9, 56},
  {cont__build_library_28, &frame__build_library_25, 892, 892, 56, 56},
  {entry__build_library_35, NULL, 900, 900, 53, 66},
  {cont__build_library_36, &frame__build_library_35, 900, 900, 14, 67},
  {cont__build_library_38, &frame__build_library_35, 900, 900, 11, 67},
  {entry__build_library_39, NULL, 902, 902, 53, 67},
  {cont__build_library_41, &frame__build_library_39, 902, 902, 14, 68},
  {cont__build_library_42, &frame__build_library_39, 902, 902, 11, 68},
  {entry__build_library_43, NULL, 904, 904, 53, 69},
  {cont__build_library_45, &frame__build_library_43, 904, 904, 14, 70},
  {cont__build_library_46, &frame__build_library_43, 904, 904, 11, 70},
  {entry__build_library_47, NULL, 905, 905, 53, 66},
  {cont__build_library_48, &frame__build_library_47, 905, 905, 14, 67},
  {cont__build_library_49, &frame__build_library_47, 905, 905, 11, 67},
  {entry__build_library_53, NULL, 907, 907, 19, 56},
  {entry__build_library_62, NULL, 914, 914, 38, 63},
  {cont__build_library_63, &frame__build_library_62, 914, 914, 13, 63},
  {cont__build_library_64, &frame__build_library_62, 914, 914, 13, 63},
  {entry__build_library_66, NULL, 916, 916, 25, 25},
  {entry__build_library_59, NULL, 910, 910, 9, 32},
  {cont__build_library_60, &frame__build_library_59, 913, 913, 13, 29},
  {cont__build_library_61, &frame__build_library_59, 912, 914, 11, 63},
  {cont__build_library_65, &frame__build_library_59, 911, 916, 9, 26},
  {entry__build_library_69, NULL, 918, 918, 21, 54},
  {entry__build_library_80, NULL, 931, 931, 35, 47},
  {cont__build_library_81, &frame__build_library_80, 931, 931, 29, 47},
  {entry__build_library_74, NULL, 927, 927, 15, 76},
  {cont__build_library_76, &frame__build_library_74, 928, 928, 15, 43},
  {cont__build_library_77, &frame__build_library_74, 921, 930, 13, 26},
  {cont__build_library_79, &frame__build_library_74, 931, 931, 13, 47},
  {entry__build_library_87, NULL, 943, 943, 35, 47},
  {cont__build_library_88, &frame__build_library_87, 943, 943, 29, 47},
  {entry__build_library_82, NULL, 939, 939, 15, 43},
  {cont__build_library_83, &frame__build_library_82, 940, 940, 15, 30},
  {cont__build_library_85, &frame__build_library_82, 933, 942, 13, 26},
  {cont__build_library_86, &frame__build_library_82, 943, 943, 13, 47},
  {entry__build_library_96, NULL, 957, 957, 35, 47},
  {cont__build_library_97, &frame__build_library_96, 957, 957, 29, 47},
  {entry__build_library_89, NULL, 950, 952, 29, 23},
  {cont__build_library_91, &frame__build_library_89, 953, 953, 15, 43},
  {cont__build_library_92, &frame__build_library_89, 954, 954, 15, 30},
  {cont__build_library_93, &frame__build_library_89, 945, 956, 13, 26},
  {cont__build_library_95, &frame__build_library_89, 957, 957, 13, 47},
  {entry__build_library_101, NULL, 968, 968, 35, 47},
  {cont__build_library_102, &frame__build_library_101, 968, 968, 29, 47},
  {entry__build_library_98, NULL, 965, 965, 15, 43},
  {cont__build_library_99, &frame__build_library_98, 959, 967, 13, 26},
  {cont__build_library_100, &frame__build_library_98, 968, 968, 13, 47},
  {entry__build_library_68, NULL, 918, 918, 9, 54},
  {cont__build_library_71, &frame__build_library_68, 919, 919, 14, 31},
  {cont__build_library_72, &frame__build_library_68, 920, 920, 11, 24},
  {cont__build_library_73, &frame__build_library_68, 919, 968, 9, 48},
  {entry__build_library_21, NULL, 890, 890, 7, 56},
  {cont__build_library_23, &frame__build_library_21, 891, 891, 10, 38},
  {cont__build_library_24, &frame__build_library_21, 891, 892, 7, 56},
  {cont__build_library_29, &frame__build_library_21, 893, 893, 7, 45},
  {cont__build_library_30, &frame__build_library_21, 894, 894, 56, 56},
  {cont__build_library_31, &frame__build_library_21, 894, 894, 7, 57},
  {cont__build_library_32, &frame__build_library_21, 898, 898, 11, 28},
  {cont__build_library_33, &frame__build_library_21, 899, 899, 11, 24},
  {cont__build_library_34, &frame__build_library_21, 896, 905, 7, 68},
  {cont__build_library_52, &frame__build_library_21, 907, 907, 7, 56},
  {cont__build_library_55, &frame__build_library_21, 908, 908, 63, 63},
  {cont__build_library_56, &frame__build_library_21, 908, 908, 37, 64},
  {cont__build_library_57, &frame__build_library_21, 908, 908, 7, 64},
  {cont__build_library_58, &frame__build_library_21, 909, 916, 7, 27},
  {cont__build_library_67, &frame__build_library_21, 917, 968, 7, 49},
  {entry__build_library, NULL, 875, 875, 6, 23},
  {cont__build_library_3, &frame__build_library, 875, 875, 3, 56},
  {cont__build_library_6, &frame__build_library, 877, 968, 3, 51},
  {cont__build_library_103, &frame__build_library, 968, 968, 51, 51},
  {entry__maybe_compile_c_file_6, NULL, 975, 976, 11, 42},
  {cont__maybe_compile_c_file_9, &frame__maybe_compile_c_file_6, 975, 976, 5, 42},
  {entry__maybe_compile_c_file_13, NULL, 981, 981, 38, 65},
  {cont__maybe_compile_c_file_14, &frame__maybe_compile_c_file_13, 981, 981, 7, 34},
  {cont__maybe_compile_c_file_15, &frame__maybe_compile_c_file_13, 981, 981, 7, 65},
  {cont__maybe_compile_c_file_16, &frame__maybe_compile_c_file_13, 981, 981, 7, 65},
  {entry__maybe_compile_c_file_19, NULL, 983, 983, 28, 65},
  {cont__maybe_compile_c_file_21, &frame__maybe_compile_c_file_19, 983, 983, 19, 65},
  {entry__maybe_compile_c_file_18, NULL, 983, 983, 7, 65},
  {cont__maybe_compile_c_file_22, &frame__maybe_compile_c_file_18, 984, 984, 7, 37},
  {entry__maybe_compile_c_file, NULL, 971, 971, 3, 35},
  {cont__maybe_compile_c_file_2, &frame__maybe_compile_c_file, 972, 972, 3, 35},
  {cont__maybe_compile_c_file_3, &frame__maybe_compile_c_file, 973, 973, 3, 26},
  {cont__maybe_compile_c_file_4, &frame__maybe_compile_c_file, 974, 974, 6, 24},
  {cont__maybe_compile_c_file_5, &frame__maybe_compile_c_file, 974, 976, 3, 43},
  {cont__maybe_compile_c_file_10, &frame__maybe_compile_c_file, 977, 977, 3, 26},
  {cont__maybe_compile_c_file_11, &frame__maybe_compile_c_file, 980, 980, 7, 25},
  {cont__maybe_compile_c_file_12, &frame__maybe_compile_c_file, 979, 981, 5, 65},
  {cont__maybe_compile_c_file_17, &frame__maybe_compile_c_file, 978, 984, 3, 38},
  {entry__format_number_11, NULL, 1000, 1000, 39, 41},
  {cont__format_number_12, &frame__format_number_11, 1000, 1000, 36, 41},
  {cont__format_number_13, &frame__format_number_11, 1000, 1000, 28, 43},
  {cont__format_number_15, &frame__format_number_11, 1000, 1000, 21, 48},
  {cont__format_number_16, &frame__format_number_11, 1000, 1000, 48, 48},
  {entry__format_number_6, NULL, 999, 999, 13, 26},
  {cont__format_number_7, &frame__format_number_6, 999, 999, 9, 28},
  {cont__format_number_8, &frame__format_number_6, 1000, 1000, 16, 18},
  {cont__format_number_9, &frame__format_number_6, 1000, 1000, 12, 18},
  {cont__format_number_10, &frame__format_number_6, 1000, 1000, 9, 48},
  {cont__format_number_17, &frame__format_number_6, 1001, 1001, 9, 13},
  {entry__format_number_4, NULL, 998, 998, 10, 19},
  {cont__format_number_5, &frame__format_number_4, 998, 1001, 7, 13},
  {entry__format_number_3, NULL, 997, 1001, 5, 14},
  {cont__format_number_18, &frame__format_number_3, 1001, 1001, 14, 14},
  {entry__format_number_21, NULL, 1004, 1004, 27, 30},
  {cont__format_number_22, &frame__format_number_21, 1004, 1004, 19, 31},
  {cont__format_number_24, &frame__format_number_21, 1004, 1004, 7, 31},
  {cont__format_number_25, &frame__format_number_21, 1004, 1004, 31, 31},
  {entry__format_number_28, NULL, 1006, 1006, 33, 36},
  {cont__format_number_29, &frame__format_number_28, 1006, 1006, 33, 38},
  {cont__format_number_30, &frame__format_number_28, 1006, 1006, 33, 39},
  {cont__format_number_31, &frame__format_number_28, 1006, 1006, 18, 39},
  {cont__format_number_32, &frame__format_number_28, 1006, 1006, 39, 39},
  {entry__format_number_26, NULL, 1006, 1006, 10, 15},
  {cont__format_number_27, &frame__format_number_26, 1006, 1006, 7, 39},
  {entry__format_number, NULL, 994, 994, 3, 16},
  {cont__format_number_2, &frame__format_number, 996, 1001, 3, 15},
  {cont__format_number_19, &frame__format_number, 1003, 1003, 5, 10},
  {cont__format_number_20, &frame__format_number, 1002, 1006, 3, 40},
  {cont__format_number_33, &frame__format_number, 1007, 1007, 3, 8},
  {entry__compiler__write_timing_info_4, NULL, 1013, 1013, 37, 37},
  {cont__compiler__write_timing_info_5, &frame__compiler__write_timing_info_4, 1013, 1013, 7, 37},
  {cont__compiler__write_timing_info_6, &frame__compiler__write_timing_info_4, 1019, 1019, 20, 41},
  {cont__compiler__write_timing_info_7, &frame__compiler__write_timing_info_4, 1019, 1019, 17, 41},
  {cont__compiler__write_timing_info_8, &frame__compiler__write_timing_info_4, 1019, 1019, 9, 42},
  {cont__compiler__write_timing_info_9, &frame__compiler__write_timing_info_4, 1020, 1020, 23, 29},
  {cont__compiler__write_timing_info_10, &frame__compiler__write_timing_info_4, 1020, 1020, 9, 34},
  {cont__compiler__write_timing_info_11, &frame__compiler__write_timing_info_4, 1014, 1021, 7, 12},
  {entry__compiler__write_timing_info_13, NULL, 1023, 1023, 47, 53},
  {cont__compiler__write_timing_info_14, &frame__compiler__write_timing_info_13, 1023, 1023, 33, 58},
  {cont__compiler__write_timing_info_15, &frame__compiler__write_timing_info_13, 1023, 1023, 7, 63},
  {entry__compiler__write_timing_info, NULL, 1010, 1010, 3, 23},
  {cont__compiler__write_timing_info_2, &frame__compiler__write_timing_info, 1012, 1012, 5, 23},
  {cont__compiler__write_timing_info_3, &frame__compiler__write_timing_info, 1011, 1023, 3, 64},
  {cont__compiler__write_timing_info_17, &frame__compiler__write_timing_info, 1024, 1024, 3, 19},
  {cont__compiler__write_timing_info_18, &frame__compiler__write_timing_info, 1024, 1024, 19, 19},
  {entry__build_executable_5, NULL, 1040, 1040, 12, 38},
  {cont__build_executable_7, &frame__build_executable_5, 1040, 1040, 9, 38},
  {entry__build_executable_8, NULL, 1041, 1041, 9, 23},
  {entry__build_executable_10, NULL, 1043, 1043, 17, 57},
  {entry__build_executable_20, NULL, 1054, 1054, 42, 69},
  {cont__build_executable_21, &frame__build_executable_20, 1054, 1054, 9, 38},
  {cont__build_executable_22, &frame__build_executable_20, 1054, 1054, 9, 69},
  {cont__build_executable_23, &frame__build_executable_20, 1054, 1054, 9, 69},
  {entry__build_executable_18, NULL, 1053, 1053, 9, 27},
  {cont__build_executable_19, &frame__build_executable_18, 1054, 1054, 9, 69},
  {cont__build_executable_24, &frame__build_executable_18, },
  {entry__build_executable_29, NULL, 1057, 1057, 21, 61},
  {entry__build_executable_32, NULL, 1058, 1058, 41, 59},
  {cont__build_executable_33, &frame__build_executable_32, 1058, 1058, 35, 64},
  {entry__build_executable_35, NULL, 1059, 1059, 32, 54},
  {entry__build_executable_39, NULL, 1061, 1061, 28, 64},
  {entry__build_executable_43, NULL, 1063, 1063, 28, 67},
  {entry__build_executable_26, NULL, 1056, 1056, 58, 70},
  {cont__build_executable_27, &frame__build_executable_26, 1056, 1056, 9, 70},
  {cont__build_executable_28, &frame__build_executable_26, 1057, 1057, 9, 61},
  {cont__build_executable_31, &frame__build_executable_26, 1058, 1058, 9, 64},
  {cont__build_executable_34, &frame__build_executable_26, 1059, 1059, 9, 54},
  {cont__build_executable_36, &frame__build_executable_26, 1060, 1060, 25, 37},
  {cont__build_executable_37, &frame__build_executable_26, 1060, 1060, 9, 37},
  {cont__build_executable_38, &frame__build_executable_26, 1061, 1061, 9, 64},
  {cont__build_executable_41, &frame__build_executable_26, 1062, 1062, 9, 39},
  {cont__build_executable_42, &frame__build_executable_26, 1063, 1063, 9, 67},
  {cont__build_executable_45, &frame__build_executable_26, 1063, 1063, 67, 67},
  {entry__build_executable_50, NULL, 1070, 1070, 44, 71},
  {cont__build_executable_51, &frame__build_executable_50, 1070, 1070, 13, 40},
  {cont__build_executable_52, &frame__build_executable_50, 1070, 1070, 13, 71},
  {cont__build_executable_53, &frame__build_executable_50, 1070, 1070, 13, 71},
  {entry__build_executable_55, NULL, 1072, 1072, 13, 43},
  {entry__build_executable_56, NULL, 1074, 1074, 13, 64},
  {cont__build_executable_57, &frame__build_executable_56, 1074, 1074, 64, 64},
  {entry__build_executable_46, NULL, 1065, 1065, 9, 30},
  {cont__build_executable_47, &frame__build_executable_46, 1066, 1066, 9, 32},
  {cont__build_executable_48, &frame__build_executable_46, 1069, 1069, 13, 31},
  {cont__build_executable_49, &frame__build_executable_46, 1068, 1070, 11, 71},
  {cont__build_executable_54, &frame__build_executable_46, 1067, 1074, 9, 65},
  {entry__build_executable_65, NULL, 1079, 1079, 11, 39},
  {entry__build_executable_60, NULL, 1078, 1078, 9, 62},
  {cont__build_executable_64, &frame__build_executable_60, 1077, 1079, 7, 40},
  {entry__build_executable_72, NULL, 1087, 1087, 38, 63},
  {cont__build_executable_73, &frame__build_executable_72, 1087, 1087, 13, 63},
  {cont__build_executable_74, &frame__build_executable_72, 1087, 1087, 13, 63},
  {entry__build_executable_70, NULL, 1086, 1086, 13, 45},
  {cont__build_executable_71, &frame__build_executable_70, 1085, 1087, 11, 63},
  {cont__build_executable_75, &frame__build_executable_70, 1085, 1087, 11, 63},
  {entry__build_executable_77, NULL, 1089, 1089, 23, 23},
  {entry__build_executable_67, NULL, 1081, 1081, 7, 30},
  {cont__build_executable_68, &frame__build_executable_67, 1084, 1084, 11, 27},
  {cont__build_executable_69, &frame__build_executable_67, 1083, 1087, 9, 64},
  {cont__build_executable_76, &frame__build_executable_67, 1082, 1089, 7, 24},
  {entry__build_executable_81, NULL, 1092, 1092, 28, 75},
  {cont__build_executable_83, &frame__build_executable_81, 1092, 1092, 75, 75},
  {entry__build_executable_86, NULL, 1095, 1095, 23, 58},
  {entry__build_executable_93, NULL, 1106, 1106, 33, 45},
  {cont__build_executable_94, &frame__build_executable_93, 1106, 1106, 27, 45},
  {entry__build_executable_85, NULL, 1095, 1095, 11, 58},
  {cont__build_executable_88, &frame__build_executable_85, 1096, 1105, 11, 24},
  {cont__build_executable_92, &frame__build_executable_85, 1106, 1106, 11, 45},
  {entry__build_executable_96, NULL, 1108, 1108, 23, 51},
  {entry__build_executable_101, NULL, 1117, 1117, 18, 40},
  {cont__build_executable_103, &frame__build_executable_101, 1117, 1117, 15, 40},
  {entry__build_executable_104, NULL, 1118, 1118, 18, 33},
  {cont__build_executable_105, &frame__build_executable_104, 1118, 1118, 15, 33},
  {entry__build_executable_108, NULL, 1121, 1121, 33, 45},
  {cont__build_executable_109, &frame__build_executable_108, 1121, 1121, 27, 45},
  {entry__build_executable_95, NULL, 1108, 1108, 11, 51},
  {cont__build_executable_98, &frame__build_executable_95, 1115, 1115, 15, 32},
  {cont__build_executable_99, &frame__build_executable_95, 1116, 1116, 15, 28},
  {cont__build_executable_100, &frame__build_executable_95, },
  {cont__build_executable_106, &frame__build_executable_95, 1109, 1120, 11, 24},
  {cont__build_executable_107, &frame__build_executable_95, 1121, 1121, 11, 45},
  {entry__build_executable_79, NULL, 1091, 1091, 7, 52},
  {cont__build_executable_80, &frame__build_executable_79, 1092, 1092, 7, 75},
  {cont__build_executable_84, &frame__build_executable_79, 1093, 1121, 7, 46},
  {entry__build_executable_113, NULL, 1123, 1123, 24, 41},
  {cont__build_executable_114, &frame__build_executable_113, 1123, 1123, 24, 41},
  {entry__build_executable_118, NULL, 1127, 1127, 11, 25},
  {entry__build_executable_119, NULL, 1128, 1128, 14, 38},
  {cont__build_executable_120, &frame__build_executable_119, 1128, 1128, 11, 38},
  {entry__build_executable_116, NULL, 1126, 1126, 11, 39},
  {cont__build_executable_117, &frame__build_executable_116, 1128, 1128, 11, 38},
  {cont__build_executable_121, &frame__build_executable_116, 1124, 1131, 7, 44},
  {entry__build_executable_2, NULL, 1039, 1039, 9, 26},
  {cont__build_executable_3, &frame__build_executable_2, 1039, 1039, 9, 38},
  {cont__build_executable_4, &frame__build_executable_2, 1037, 1041, 5, 24},
  {cont__build_executable_9, &frame__build_executable_2, 1043, 1043, 5, 57},
  {cont__build_executable_12, &frame__build_executable_2, 1044, 1044, 5, 41},
  {cont__build_executable_13, &frame__build_executable_2, 1045, 1045, 5, 41},
  {cont__build_executable_14, &frame__build_executable_2, 1046, 1046, 5, 33},
  {cont__build_executable_15, &frame__build_executable_2, 1047, 1047, 5, 28},
  {cont__build_executable_16, &frame__build_executable_2, 1049, 1049, 5, 24},
  {cont__build_executable_17, &frame__build_executable_2, },
  {cont__build_executable_25, &frame__build_executable_2, 1050, 1074, 5, 67},
  {cont__build_executable_58, &frame__build_executable_2, 1075, 1075, 5, 50},
  {cont__build_executable_59, &frame__build_executable_2, 1076, 1079, 5, 41},
  {cont__build_executable_66, &frame__build_executable_2, 1080, 1089, 5, 25},
  {cont__build_executable_78, &frame__build_executable_2, 1090, 1121, 5, 47},
  {cont__build_executable_110, &frame__build_executable_2, 1122, 1122, 41, 41},
  {cont__build_executable_111, &frame__build_executable_2, 1122, 1122, 5, 42},
  {cont__build_executable_112, &frame__build_executable_2, 1123, 1123, 8, 41},
  {cont__build_executable_115, &frame__build_executable_2, 1123, 1131, 5, 45},
  {entry__build_executable, NULL, 1036, 1131, 3, 46},
  {entry__112_2, NULL, 108, 108, 30, 45},
  {cont__112_3, &frame__112_2, 108, 108, 30, 45},
  {cont__112_4, &frame__112_2, 108, 108, 30, 45},
  {entry__112_6, NULL, 109, 109, 8, 28},
  {cont__112_7, &frame__112_6, 109, 109, 5, 28},
  {entry__112_8, NULL, 110, 110, 5, 20},
  {entry__113_2, NULL, 114, 114, 31, 47},
  {cont__113_3, &frame__113_2, 114, 114, 31, 47},
  {cont__113_4, &frame__113_2, 114, 114, 31, 47},
  {entry__113_6, NULL, 115, 115, 8, 29},
  {cont__113_7, &frame__113_6, 115, 115, 5, 29},
  {entry__113_8, NULL, 116, 116, 5, 20},
  {entry__117_4, NULL, 136, 136, 7, 41},
  {cont__117_5, &frame__117_4, 137, 137, 10, 26},
  {cont__117_6, &frame__117_4, 137, 137, 7, 32},
  {cont__117_7, &frame__117_4, 138, 138, 7, 19},
  {cont__117_8, &frame__117_4, 139, 139, 7, 34},
  {cont__117_9, &frame__117_4, 140, 140, 10, 21},
  {cont__117_10, &frame__117_4, 140, 140, 7, 27},
  {cont__117_11, &frame__117_4, 141, 141, 20, 20},
  {entry__117_3, NULL, 135, 141, 5, 20},
  {cont__117_12, &frame__117_3, 141, 141, 20, 20},
  {entry__117_1, NULL, 132, 132, 3, 31},
  {cont__117_2, &frame__117_1, 134, 141, 3, 21},
  {entry__147_4, NULL, 173, 173, 41, 79},
  {entry__147_2, NULL, 173, 173, 8, 38},
  {cont__147_3, &frame__147_2, 173, 173, 5, 79},
  {cont__147_6, &frame__147_2, 174, 174, 5, 45},
  {cont__147_7, &frame__147_2, 174, 174, 45, 45},
  {entry__147_9, NULL, 180, 181, 7, 52},
  {entry__147_12, NULL, 183, 184, 7, 34},
  {entry__147_15, NULL, 186, 187, 7, 57},
  {entry__147_18, NULL, 189, 190, 7, 71},
  {entry__147_21, NULL, 192, 193, 7, 38},
  {entry__147_24, NULL, 195, 196, 7, 47},
  {entry__147_27, NULL, 198, 199, 7, 61},
  {entry__147_30, NULL, 201, 204, 7, 27},
  {entry__147_33, NULL, 209, 210, 7, 33},
  {entry__147_36, NULL, 212, 213, 7, 29},
  {entry__147_39, NULL, 215, 216, 7, 42},
  {entry__147_42, NULL, 218, 219, 7, 34},
  {entry__147_45, NULL, 221, 222, 7, 35},
  {entry__147_48, NULL, 224, 225, 7, 40},
  {entry__147_51, NULL, 227, 228, 7, 63},
  {entry__147_54, NULL, 233, 234, 7, 35},
  {entry__147_57, NULL, 236, 237, 7, 45},
  {entry__147_60, NULL, 239, 240, 7, 42},
  {entry__147_63, NULL, 242, 243, 7, 29},
  {entry__147_66, NULL, 248, 249, 7, 32},
  {entry__147_69, NULL, 251, 252, 7, 33},
  {entry__147_72, NULL, 254, 255, 7, 43},
  {entry__147_75, NULL, 257, 258, 7, 29},
  {entry__147_78, NULL, 260, 261, 7, 59},
  {entry__147_81, NULL, 263, 264, 7, 76},
  {entry__147_8, NULL, 176, 264, 5, 77},
  {cont__147_84, &frame__147_8, 264, 264, 78, 78},
  {entry__148_2, NULL, 269, 269, 5, 33},
  {cont__148_3, &frame__148_2, 269, 269, 5, 33},
  {entry__148_1, NULL, },
  {cont__148_4, &frame__148_1, },
  {entry__148_6, NULL, 271, 271, 5, 30},
  {entry__152_1, NULL, 275, 275, 37, 37},
  {entry__159_4, NULL, 299, 299, 27, 69},
  {cont__159_6, &frame__159_4, 299, 299, 69, 69},
  {entry__160_5, NULL, 301, 301, 3, 27},
  {cont__160_7, &frame__160_5, 302, 302, 3, 33},
  {cont__160_9, &frame__160_5, 302, 302, 33, 33},
  {entry__161_1, NULL, 303, 303, 48, 58},
  {cont__161_3, &frame__161_1, 303, 303, 31, 58},
  {cont__161_4, &frame__161_1, 303, 303, 58, 58},
  {entry__163_3, NULL, 305, 305, 38, 61},
  {cont__163_4, &frame__163_3, 305, 305, 61, 61},
  {entry__165_3, NULL, 307, 307, 37, 59},
  {cont__165_4, &frame__165_3, 307, 307, 59, 59},
  {entry__183_2, NULL, 657, 658, 9, 51},
  {cont__183_5, &frame__183_2, 657, 658, 3, 51},
  {entry__198_1, NULL, 1133, 1133, 20, 36},
  {cont__198_2, &frame__198_1, 1133, 1133, 36, 36},
  {entry__199_4, NULL, 1140, 1140, 7, 32},
  {entry__199_3, NULL, },
  {cont__199_5, &frame__199_3, },
  {entry__199_2, NULL, },
  {cont__199_6, &frame__199_2, },
  {entry__199_1, NULL, },
  {cont__199_7, &frame__199_1, 1135, 1141, 3, 24},
  {entry__199_8, NULL, 1142, 1142, 3, 23},
  {entry__199_9, NULL, 1143, 1143, 3, 43},
  {entry__199_10, NULL, 1144, 1144, 3, 57},
  {entry__199_11, NULL, 1145, 1145, 6, 29},
  {cont__199_12, &frame__199_11, 1145, 1145, 3, 43}
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
  "compiler",
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
  // 75: copyright "
  // 76:   Copyright (C) 2020 by
  // 77:   Dipl.-Ing. Michael Niederle
  // 78:   
  // 79:   This program is free software; you can redistribute it and/or modify
  // 80:   it under the terms of the GNU General Public License, version 2, or
  // 81:   (at your option) version 3.
  // 82:   
  // 83:   This program is distributed in the hope that it will be useful,
  // 84:   but WITHOUT ANY WARRANTY; without even the implied warranty of
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__a5542a556fe6f2ee;
  result_count = 0;
  myself = get__copyright();
  func = myself->type;
  frame->cont = cont__101_2;
}
static void cont__101_2(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 95: $MAJOR runtime_major_version()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__runtime_major_version();
  func = myself->type;
  frame->cont = cont__102_1;
}
static void cont__102_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._MAJOR, arguments->slots[0]);
  // 96: $MINOR runtime_minor_version()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__runtime_minor_version();
  func = myself->type;
  frame->cont = cont__103_1;
}
static void cont__103_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._MINOR, arguments->slots[0]);
  // 97: $PATCH runtime_patch_version()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__runtime_patch_version();
  func = myself->type;
  frame->cont = cont__104_1;
}
static void cont__104_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._PATCH, arguments->slots[0]);
  // 98: $VERSION "@(MAJOR).@(MINOR).@(PATCH)"
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = var._MAJOR;
  arguments->slots[1] = string__578a5af303e9ccf;
  arguments->slots[2] = var._MINOR;
  arguments->slots[3] = string__578a5af303e9ccf;
  arguments->slots[4] = var._PATCH;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__105_2;
}
static void cont__105_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._VERSION, arguments->slots[0]);
  // 99: version VERSION
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._VERSION;
  result_count = 0;
  myself = get__version();
  func = myself->type;
  frame->cont = cont__106_1;
}
static void cont__106_1(void) {
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
  frame->cont = cont__107_1;
}
static void cont__107_1(void) {
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
  frame->cont = cont__107_2;
}
static void cont__107_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._cc, arguments->slots[0]);
  // 101: extern $mkdir "mkdir" # would be nice to have one in the system library!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__5c5aea03ea80c025;
  result_count = 1;
  myself = get__extern();
  func = myself->type;
  frame->cont = cont__108_2;
}
static void cont__108_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._mkdir, arguments->slots[0]);
  // 102: $SIMLIBPATH environment("SIMLIBPATH")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__55d5804f0e895069;
  result_count = 1;
  myself = get__environment();
  func = myself->type;
  frame->cont = cont__109_2;
}
static void cont__109_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._SIMLIBPATH, arguments->slots[0]);
  // 103: $SIMDATAPATH environment("SIMDATAPATH")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__2058710183abbfe4;
  result_count = 1;
  myself = get__environment();
  func = myself->type;
  frame->cont = cont__110_2;
}
static void cont__110_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._SIMDATAPATH, arguments->slots[0]);
  // 104: ... PREFIX()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__PREFIX();
  func = myself->type;
  frame->cont = cont__111_1;
}
static void cont__111_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 104: ... PACKAGE_VERSION()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__PACKAGE_VERSION();
  func = myself->type;
  frame->cont = cont__111_2;
}
static void cont__111_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 104: ... "/share/simplicity-@(PACKAGE_VERSION())"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__1057e106f655c41;
  arguments->slots[1] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__111_4;
}
static void cont__111_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 104: ... string(PREFIX() "/share/simplicity-@(PACKAGE_VERSION())")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  arguments->slots[1] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__111_5;
}
static void cont__111_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 104: $default_paths list(string(PREFIX() "/share/simplicity-@(PACKAGE_VERSION())"))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__111_6;
}
static void cont__111_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._default_paths, arguments->slots[0]);
  // 108: SIMLIBPATH.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._SIMLIBPATH;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__112_1;
}
static void cont__112_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 108: SIMLIBPATH.is_defined && SIMLIBPATH != ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  arguments->slots[1] = func__112_2;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__112_5;
}
static void entry__112_2(void) {
  allocate_initialized_frame_gc(0, 2);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 108: ... SIMLIBPATH != ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._SIMLIBPATH;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__112_3;
}
static void cont__112_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 108: ... SIMLIBPATH != ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__112_4;
}
static void cont__112_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 108: ... SIMLIBPATH != ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__112_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 106: $simlibpaths
  // 107:   if
  // 108:     SIMLIBPATH.is_defined && SIMLIBPATH != ""
  // 109:     -> split(SIMLIBPATH ':')
  // 110:     -> default_paths
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__112_6;
  arguments->slots[2] = func__112_8;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__112_9;
}
static void entry__112_6(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 109: ... split(SIMLIBPATH ':')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._SIMLIBPATH;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__split();
  func = myself->type;
  frame->cont = cont__112_7;
}
static void cont__112_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 109: -> split(SIMLIBPATH ':')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__112_8(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 110: -> default_paths
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._default_paths;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__112_9(void) {
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
  frame->cont = cont__113_1;
}
static void cont__113_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 114: SIMDATAPATH.is_defined && SIMDATAPATH != ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  arguments->slots[1] = func__113_2;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__113_5;
}
static void entry__113_2(void) {
  allocate_initialized_frame_gc(0, 2);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 114: ... SIMDATAPATH != ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._SIMDATAPATH;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__113_3;
}
static void cont__113_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 114: ... SIMDATAPATH != ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__113_4;
}
static void cont__113_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 114: ... SIMDATAPATH != ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__113_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 112: $simdatapaths
  // 113:   if
  // 114:     SIMDATAPATH.is_defined && SIMDATAPATH != ""
  // 115:     -> split(SIMDATAPATH ':')
  // 116:     -> default_paths
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__113_6;
  arguments->slots[2] = func__113_8;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__113_9;
}
static void entry__113_6(void) {
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
  frame->cont = cont__113_7;
}
static void cont__113_7(void) {
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
static void entry__113_8(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 116: -> default_paths
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._default_paths;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__113_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._simdatapaths, arguments->slots[0]);
  // 122: "bsd" = "posix"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__fa720c15db16ba8;
  arguments->slots[1] = string__545aefc3ea81102f;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__115_2;
}
static void cont__115_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 123: "cygwin" = "posix"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__561f538101f3c2b9;
  arguments->slots[1] = string__545aefc3ea81102f;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__115_3;
}
static void cont__115_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 124: "darwin" = "posix"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7c1f538281f242b9;
  arguments->slots[1] = string__545aefc3ea81102f;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__115_4;
}
static void cont__115_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 125: "linux" = "posix"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__585ae883ea60d02f;
  arguments->slots[1] = string__545aefc3ea81102f;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__115_5;
}
static void cont__115_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 126: "posix" = "all"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__545aefc3ea81102f;
  arguments->slots[1] = string__fa720015d496ba0;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__115_7;
}
static void cont__115_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 127: "win" = "all"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__fa725815d616ba2;
  arguments->slots[1] = string__fa720015d496ba0;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__115_9;
}
static void cont__115_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 128: "all" = NONE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__fa720015d496ba0;
  arguments->slots[1] = unique__NONE;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__115_10;
}
static void cont__115_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__7 */ = arguments->slots[0];
  // 120: $supported_platforms
  // 121:   key_order_table
  // 122:     "bsd" = "posix"
  // 123:     "cygwin" = "posix"
  // 124:     "darwin" = "posix"
  // 125:     "linux" = "posix"
  // 126:     "posix" = "all"
  // 127:     "win" = "all"
  // 128:     "all" = NONE
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
  frame->cont = cont__115_11;
}
static void cont__115_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._supported_platforms, arguments->slots[0]);
  // 130: $$platform_priority empty_table
  var._platform_priority = get__empty_table();
  // 131: do:
  // 132:   $$platform operating_system()
  // 133:   $$priority 0
  // 134:   do: (-> break)
  // 135:     forever:
  // 136:       $plat supported_platforms(platform)
  // 137:       if plat.is_undefined break
  // 138:       inc &priority
  // 139:       !platform_priority(platform) priority
  // 140:       if plat == NONE break
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__117_1;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__117_13;
}
static void entry__117_3(void) {
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
  // 135: ... :
  // 136:   $plat supported_platforms(platform)
  // 137:   if plat.is_undefined break
  // 138:   inc &priority
  // 139:   !platform_priority(platform) priority
  // 140:   if plat == NONE break
  // 141:   !platform plat
  frame->slots[3] /* temp__1 */ = create_closure(entry__117_4, 0);
  // 135: forever:
  // 136:   $plat supported_platforms(platform)
  // 137:   if plat.is_undefined break
  // 138:   inc &priority
  // 139:   !platform_priority(platform) priority
  // 140:   if plat == NONE break
  // 141:   !platform plat
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame->cont = cont__117_12;
}
static void entry__117_4(void) {
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
  // 136: $plat supported_platforms(platform)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* platform */;
  result_count = 1;
  myself = var._supported_platforms;
  func = myself->type;
  frame->cont = cont__117_5;
}
static void cont__117_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* plat */, arguments->slots[0]);
  // 137: ... plat.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* plat */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__117_6;
}
static void cont__117_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 137: if plat.is_undefined break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* break */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__117_7;
}
static void cont__117_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 138: inc &priority
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* priority */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__117_8;
}
static void cont__117_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* priority */ = arguments->slots[0];
  // 139: !platform_priority(platform)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* platform */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* priority */;
  result_count = 1;
  myself = var._platform_priority;
  func = myself->type;
  frame->cont = cont__117_9;
}
static void cont__117_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._platform_priority = arguments->slots[0];
  // 140: ... plat == NONE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* plat */;
  arguments->slots[1] = unique__NONE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__117_10;
}
static void cont__117_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 140: if plat == NONE break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* break */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__117_11;
}
static void cont__117_11(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 141: !platform plat
  ((CELL *)frame->slots[0])->contents /* platform */ = frame->slots[3] /* plat */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__117_12(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__117_1(void) {
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
  // 132: $$platform operating_system()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__operating_system();
  func = myself->type;
  frame->cont = cont__117_2;
}
static void cont__117_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* platform */ = arguments->slots[0];
  // 133: $$priority 0
  ((CELL *)frame->slots[1])->contents /* priority */ = number__0;
  // 134: ... : (-> break)
  // 135:   forever:
  // 136:     $plat supported_platforms(platform)
  // 137:     if plat.is_undefined break
  // 138:     inc &priority
  // 139:     !platform_priority(platform) priority
  // 140:     if plat == NONE break
  // 141:     !platform plat
  frame->slots[2] /* temp__1 */ = create_closure(entry__117_3, 0);
  // 134: do: (-> break)
  // 135:   forever:
  // 136:     $plat supported_platforms(platform)
  // 137:     if plat.is_undefined break
  // 138:     inc &priority
  // 139:     !platform_priority(platform) priority
  // 140:     if plat == NONE break
  // 141:     !platform plat
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__do();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__117_13(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 142: $$platform_specific_priority undefined
  var._platform_specific_priority = get__undefined();
  // 143: $$module_info empty_table
  var._module_info = get__empty_table();
  // 144: $$meta_levels empty_table # 0 -> no meta files
  var._meta_levels = get__empty_table();
  // 145: $$do_rebuild false
  var._do_rebuild = get__false();
  // 146: $$do_omit_meta false
  var._do_omit_meta = get__false();
  // 147: $$compiler::do_dump_trees false
  var.compiler__do_dump_trees = get__false();
  // 148: $$compiler::do_pretty_print false
  var.compiler__do_pretty_print = get__false();
  // 149: $$compiler::do_convert false
  var.compiler__do_convert = get__false();
  // 150: $$compiler::do_print_simplified_source false
  var.compiler__do_print_simplified_source = get__false();
  // 151: $$compiler::do_show_debug_infos false
  var.compiler__do_show_debug_infos = get__false();
  // 152: $$compiler::do_show_compiler_debug_infos false
  var.compiler__do_show_compiler_debug_infos = get__false();
  // 153: $$compiler::do_check_only false
  var.compiler__do_check_only = get__false();
  // 154: $$compiler::do_show_brief_messages false
  var.compiler__do_show_brief_messages = get__false();
  // 155: $$compiler::do_print_warnings false
  var.compiler__do_print_warnings = get__false();
  // 156: $$compiler::do_print_missing false
  var.compiler__do_print_missing = get__false();
  // 157: $$compiler::do_print_summary false
  var.compiler__do_print_summary = get__false();
  // 158: $$compiler::verbose false
  var.compiler__verbose = get__false();
  // 159: $$do_print_c false
  var._do_print_c = get__false();
  // 160: $$compiler::do_extract_documentation false
  var.compiler__do_extract_documentation = get__false();
  // 161: $$do_extract_exports false
  var._do_extract_exports = get__false();
  // 162: $$do_build_codeblocks_project false
  var._do_build_codeblocks_project = get__false();
  // 163: $$do_list_dependencies false
  var._do_list_dependencies = get__false();
  // 164: $$do_build_static false
  var._do_build_static = get__false();
  // 165: $$do_link_profiler false
  var._do_link_profiler = get__false();
  // 166: $$compiler::do_time_passes false
  var.compiler__do_time_passes = get__false();
  // 167: $$module_prefix undefined
  var._module_prefix = get__undefined();
  // 168: $$input_filename undefined
  var._input_filename = get__undefined();
  // 169: $$additional_libraries empty_list
  var._additional_libraries = get__empty_list();
  // 170: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__146_1;
}
static void cont__146_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 170: ... truncate_until(program_name '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__program_name();
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__146_2;
}
static void cont__146_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 170: $action truncate_until(program_name '/' -1) .truncate_from. '-'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = character__45;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__146_3;
}
static void cont__146_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._action, arguments->slots[0]);
  // 172: action == "simrun"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._action;
  arguments->slots[1] = string__421f52c90112c2b9;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__147_1;
}
static void cont__147_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 171: if
  // 172:   action == "simrun":
  // 173:     if command_line_arguments.is_empty: Error "Missing command line arguments!"
  // 174:     !input_filename command_line_arguments(1)
  // 175:   :
  // 176:     program_parameters
  // 177:       # the following options act on a single file only
  // 178:       
  // 179:       !compiler::do_check_only
  // 180:       -> "check-only" "
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__147_2;
  arguments->slots[2] = func__147_8;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__147_85;
}
static void entry__147_2(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 173: ... command_line_arguments.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__command_line_arguments();
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__147_3;
}
static void cont__147_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 173: if command_line_arguments.is_empty: Error "Missing command line arguments!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__147_4;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__147_6;
}
static void entry__147_4(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 173: ... Error "Missing command line arguments!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__8d3c5e4b22d2f22b;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__147_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 174: !input_filename command_line_arguments(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__command_line_arguments();
  func = myself->type;
  frame->cont = cont__147_7;
}
static void cont__147_7(void) {
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
static void entry__147_8(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 176: program_parameters
  // 177:   # the following options act on a single file only
  // 178:   
  // 179:   !compiler::do_check_only
  // 180:   -> "check-only" "
  // 181:     do not compile; just check for syntax errors
  // 182:   !compiler::do_dump_trees
  // 183:   -> "dump-trees" "
  // 184:     dump abstract syntax trees
  // 185:   !compiler::do_pretty_print
  // ...
  argument_count = 25;
  arguments = node_p;
  arguments->slots[0] = func__147_9;
  arguments->slots[1] = func__147_12;
  arguments->slots[2] = func__147_15;
  arguments->slots[3] = func__147_18;
  arguments->slots[4] = func__147_21;
  arguments->slots[5] = func__147_24;
  arguments->slots[6] = func__147_27;
  arguments->slots[7] = func__147_30;
  arguments->slots[8] = func__147_33;
  arguments->slots[9] = func__147_36;
  arguments->slots[10] = func__147_39;
  arguments->slots[11] = func__147_42;
  arguments->slots[12] = func__147_45;
  arguments->slots[13] = func__147_48;
  arguments->slots[14] = func__147_51;
  arguments->slots[15] = func__147_54;
  arguments->slots[16] = func__147_57;
  arguments->slots[17] = func__147_60;
  arguments->slots[18] = func__147_63;
  arguments->slots[19] = func__147_66;
  arguments->slots[20] = func__147_69;
  arguments->slots[21] = func__147_72;
  arguments->slots[22] = func__147_75;
  arguments->slots[23] = func__147_78;
  arguments->slots[24] = func__147_81;
  result_count = 25;
  myself = get__program_parameters();
  func = myself->type;
  frame->cont = cont__147_84;
}
static void entry__147_9(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 180: -> "check-only" "
  // 181:   do not compile; just check for syntax errors
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2b680b9e2e4fa558;
  arguments->slots[1] = string__8d1eb0934cb703aa;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__147_12(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 183: -> "dump-trees" "
  // 184:   dump abstract syntax trees
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__1124317d33023452;
  arguments->slots[1] = string__d3c3199b9e37dd88;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__147_15(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 186: -> "pretty-print" "
  // 187:   do not compile; just pretty print the source file
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2eb9522bce550419;
  arguments->slots[1] = string__31ed31d8e6f28138;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__147_18(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 189: -> "print-simplified-source" "
  // 190:   do not generate a C-file; just print the simplified source text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__23efc30ce16df2e;
  arguments->slots[1] = string__c565f1870e113429;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__147_21(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 192: -> "convert" "
  // 193:   convert pretty-printed sources
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__9e080c95152a208e;
  arguments->slots[1] = string__ef1e4341946f6b23;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__147_24(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 195: -> "print-c" "
  // 196:   print C source code for a single module
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__ae4408db97d25099;
  arguments->slots[1] = string__2623b8ba9cf2f994;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__147_27(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 198: -> "time-passes" "
  // 199:   print running time for the individual compiler passes
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__a7e97d93a221bbf6;
  arguments->slots[1] = string__fa3ca2557b3c0271;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__147_30(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 201: -> VALUED_OPTION "module-prefix" "
  // 202:   needed to compile a single file within a subdirectory;
  // 203:   if the subdirectories are nested use slashes to separate
  // 204:   the directory names
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__VALUED_OPTION();
  arguments->slots[1] = string__c95e7978381b7632;
  arguments->slots[2] = string__4cca41e5ff59895a;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__147_33(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 209: -> "brief" "
  // 210:   show brief error messages
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__6e5ae943eae03031;
  arguments->slots[1] = string__22ca0f65643a26b5;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__147_36(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 212: -> "warnings" "
  // 213:   show warning messages
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7c90ae5f04ed72b3;
  arguments->slots[1] = string__ea6d59fa9dcad709;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__147_39(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 215: -> "missing" "
  // 216:   inform about missing documentation
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__94300f9615cbf09d;
  arguments->slots[1] = string__aa7c4ea56fedf95b;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__147_42(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 218: -> "summary" "
  // 219:   show a statistical summary
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__a8480d98152a1083;
  arguments->slots[1] = string__10671df6f7523277;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__147_45(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 221: -> "verbose" "
  // 222:   output verbose informations
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__b65c0e101523e09f;
  arguments->slots[1] = string__2ba4a5a9cdae43b8;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__147_48(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 224: -> "debug" "
  // 225:   show C-compiler and linker calls
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__405aeb83ea605030;
  arguments->slots[1] = string__977692d258cc57f;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__147_51(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 227: -> "debug-compiler" "
  // 228:   show internal debug messages of the Simplicity compiler
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__d13d993479731341;
  arguments->slots[1] = string__d30c0a59c3d26b04;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__147_54(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 233: -> "codeblocks" "
  // 234:   create Code::Blocks project
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2b7008daa973b572;
  arguments->slots[1] = string__99c92c9b20cfd38;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__147_57(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 236: -> "extract-documentation" "
  // 237:   extract documentation encoded as HTML
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7f0dce6ce0a2268e;
  arguments->slots[1] = string__140146cb87bc0040;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__147_60(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 239: -> "extract-exports" "
  // 240:   extract a list of exported symbols
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__4101bf3c8d3115de;
  arguments->slots[1] = string__7cd3f9ecb224e231;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__147_63(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 242: -> "list-dependencies" "
  // 243:   list all dependencies
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__211e9dd763481194;
  arguments->slots[1] = string__1214925be130f2c;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__147_66(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 248: -> "rebuild" "
  // 249:   rebuild all source files
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__984c0f9015dae09e;
  arguments->slots[1] = string__6ce7f8f6c7e73eb4;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__147_69(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 251: -> "omit-meta" "
  // 252:   do not rebuild meta files
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__749427e68da7a564;
  arguments->slots[1] = string__93608261e3431133;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__147_72(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 254: -> "static" "
  // 255:   create statically linked executable
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__5a1f534901f312b4;
  arguments->slots[1] = string__b20e03a80d6db737;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__147_75(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 257: -> "profile" "
  // 258:   link with libprofiler
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__be440f9b95da309f;
  arguments->slots[1] = string__6f1f4f6107c9cdea;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__147_78(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 260: -> std::MANDATORY_PARAMETER "filename" "
  // 261:   the name of the source file or directory to compile
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__std__MANDATORY_PARAMETER();
  arguments->slots[1] = string__72b0ad9004bdc085;
  arguments->slots[2] = string__bb8770c27da8f42f;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__147_81(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 263: -> std::SOME_PARAMETERS "additional_libraries" "
  // 264:   the names of additional libraries (used for --extract-documentation)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__std__SOME_PARAMETERS();
  arguments->slots[1] = string__af5ae49d07a6e408;
  arguments->slots[2] = string__c8a7274dc08e5785;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__147_84(void) {
  if (argument_count != 25) {
    invalid_results_error();
    return;
  }
  var.compiler__do_check_only = arguments->slots[0];
  var.compiler__do_dump_trees = arguments->slots[1];
  var.compiler__do_pretty_print = arguments->slots[2];
  var.compiler__do_print_simplified_source = arguments->slots[3];
  var.compiler__do_convert = arguments->slots[4];
  var._do_print_c = arguments->slots[5];
  set__do_time_passes(arguments->slots[6]);
  var._module_prefix = arguments->slots[7];
  var.compiler__do_show_brief_messages = arguments->slots[8];
  var.compiler__do_print_warnings = arguments->slots[9];
  var.compiler__do_print_missing = arguments->slots[10];
  var.compiler__do_print_summary = arguments->slots[11];
  var.compiler__verbose = arguments->slots[12];
  var.compiler__do_show_debug_infos = arguments->slots[13];
  var.compiler__do_show_compiler_debug_infos = arguments->slots[14];
  var._do_build_codeblocks_project = arguments->slots[15];
  set__do_extract_documentation(arguments->slots[16]);
  var._do_extract_exports = arguments->slots[17];
  var._do_list_dependencies = arguments->slots[18];
  var._do_rebuild = arguments->slots[19];
  var._do_omit_meta = arguments->slots[20];
  var._do_build_static = arguments->slots[21];
  var._do_link_profiler = arguments->slots[22];
  var._input_filename = arguments->slots[23];
  var._additional_libraries = arguments->slots[24];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__147_85(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_extract_exports;
  arguments->slots[1] = func__148_1;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__148_5;
}
static void entry__148_1(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_extract_documentation();
  arguments->slots[1] = func__148_2;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__148_4;
}
static void entry__148_2(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 269: additional_libraries.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._additional_libraries;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__148_3;
}
static void cont__148_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 269: additional_libraries.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__148_4(void) {
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
static void cont__148_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 265: unless
  // 266:   ||
  // 267:     do_extract_exports
  // 268:     do_extract_documentation
  // 269:     additional_libraries.is_empty
  // 270:   :
  // 271:     Error "To many arguments!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__148_6;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__148_8;
}
static void entry__148_6(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 271: Error "To many arguments!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__c6fd3eab70990d61;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__148_8(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 272: %main_filename fullname(input_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._input_filename;
  result_count = 1;
  myself = get__fullname();
  func = myself->type;
  frame->cont = cont__149_1;
}
static void cont__149_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(get__main_filename(), arguments->slots[0]);
  // 273: %main_info stat(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__150_1;
}
static void cont__150_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(get__main_info(), arguments->slots[0]);
  // 274: %do_build_static_executable do_build_static
  initialize_future(get__do_build_static_executable(), var._do_build_static);
  // 275: if do_show_debug_infos: !verbose true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_show_debug_infos();
  arguments->slots[1] = func__152_1;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__152_2;
}
static void entry__152_1(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 275: ... !verbose true
  set__verbose(get__true());
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__152_2(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 283: %mode undefined # EXE or LIB
  initialize_maybe_future(get__mode(), get__undefined());
  // 284: $WHITESPACE many(' ')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__32;
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__157_1;
}
static void cont__157_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._WHITESPACE, arguments->slots[0]);
  // 286: $$cc_options
  // 287:   list
  // 288:     "-Wall"
  // 289:     "-Wno-unused-function"
  // 290:     "-Wno-unused-variable"
  // 291:     "-Wno-parentheses"
  // 292:     "-Wno-switch"
  // 293:     "-Wno-trigraphs"
  // 294:     "-fPIC"
  // 295:     "-O1"
  // ...
  argument_count = 10;
  arguments = node_p;
  arguments->slots[0] = string__245aeb43eaacc03b;
  arguments->slots[1] = string__e381a5286a12b5a7;
  arguments->slots[2] = string__c9d1a7e66a0a17ac;
  arguments->slots[3] = string__1abcc193f1dac47a;
  arguments->slots[4] = string__d3e88c522110dabb;
  arguments->slots[5] = string__65a7cd1120033166;
  arguments->slots[6] = string__465ae703eb84c014;
  arguments->slots[7] = string__fa733015c516bfd;
  arguments->slots[8] = string__40ebeb253b72cf38;
  arguments->slots[9] = string__edf2e5a02a882fc3;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__158_11;
}
static void cont__158_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._cc_options = arguments->slots[0];
  // 299: ... c_compiler()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__c_compiler();
  func = myself->type;
  frame->cont = cont__159_1;
}
static void cont__159_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 299: ... c_compiler() == "gcc"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  arguments->slots[1] = string__fa721815d316baf;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__159_3;
}
static void cont__159_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 299: if c_compiler() == "gcc": push &cc_options "-Wno-maybe-uninitialized"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__159_4;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__159_7;
}
static void entry__159_4(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 299: ... push &cc_options "-Wno-maybe-uninitialized"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._cc_options;
  arguments->slots[1] = string__ecde9da404625e23;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__159_6;
}
static void cont__159_6(void) {
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
static void cont__159_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 300: ... hardware_architecture()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__hardware_architecture();
  func = myself->type;
  frame->cont = cont__160_1;
}
static void cont__160_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 300: ... "x86_32", "x86_64"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__f41f598c8327d2e5;
  arguments->slots[1] = string__f41f598c830fd2e3;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__160_4;
}
static void cont__160_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 300: case hardware_architecture() "x86_32", "x86_64":
  // 301:   push &cc_options "-msse2"
  // 302:   push &cc_options "-mfpmath=sse"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* temp__2 */;
  arguments->slots[2] = func__160_5;
  result_count = 0;
  myself = get__case();
  func = myself->type;
  frame->cont = cont__160_10;
}
static void entry__160_5(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 301: push &cc_options "-msse2"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._cc_options;
  arguments->slots[1] = string__7e1f52a6019282e5;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__160_7;
}
static void cont__160_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._cc_options = arguments->slots[0];
  // 302: push &cc_options "-mfpmath=sse"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._cc_options;
  arguments->slots[1] = string__70d94c874a06872f;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__160_9;
}
static void cont__160_9(void) {
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
static void cont__160_10(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 303: for_each simdatapaths: (path) push &cc_options "-I@(path)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._simdatapaths;
  arguments->slots[1] = func__161_1;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__161_5;
}
static void entry__161_1(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // path: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 303: ... "-I@(path)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6602b8c;
  arguments->slots[1] = frame->slots[0] /* path */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__161_3;
}
static void cont__161_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 303: ... push &cc_options "-I@(path)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._cc_options;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__161_4;
}
static void cont__161_4(void) {
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
static void cont__161_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 304: $$cpp_options empty_list
  var._cpp_options = get__empty_list();
  // 305: ... CPPFLAGS()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__CPPFLAGS();
  func = myself->type;
  frame->cont = cont__163_1;
}
static void cont__163_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 305: ... split(CPPFLAGS())
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__split();
  func = myself->type;
  frame->cont = cont__163_2;
}
static void cont__163_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 305: for_each split(CPPFLAGS()): (option) push &cpp_options option
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__163_3;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__163_5;
}
static void entry__163_3(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // option: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 305: ... push &cpp_options option
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._cpp_options;
  arguments->slots[1] = frame->slots[0] /* option */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__163_4;
}
static void cont__163_4(void) {
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
static void cont__163_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 306: $$ld_options empty_list
  var._ld_options = get__empty_list();
  // 307: ... LDFLAGS()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__LDFLAGS();
  func = myself->type;
  frame->cont = cont__165_1;
}
static void cont__165_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 307: ... split(LDFLAGS())
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__split();
  func = myself->type;
  frame->cont = cont__165_2;
}
static void cont__165_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 307: for_each split(LDFLAGS()): (option) push &ld_options option
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__165_3;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__165_5;
}
static void entry__165_3(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // option: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 307: ... push &ld_options option
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._ld_options;
  arguments->slots[1] = frame->slots[0] /* option */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__165_4;
}
static void cont__165_4(void) {
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
static void cont__165_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 308: %on_top_level true # set to false while building meta-files
  initialize_maybe_future(get__on_top_level(), get__true());
  // 309: %%objects empty_insert_order_set
  set__objects(get__empty_insert_order_set());
  // 310: %%libraries empty_insert_order_set # contains "-lsim-..."-entries
  set__libraries(get__empty_insert_order_set());
  // 311: %%do_link false
  set__do_link(get__false());
  // 312: %%last_modification_time undefined
  set__last_modification_time(get__undefined());
  // 313: $$c_sources empty_insert_order_set
  var._c_sources = get__empty_insert_order_set();
  // 314: $$dependencies empty_list
  var._dependencies = get__empty_list();
  // 315: $$resolved_libraries undefined
  var._resolved_libraries = get__undefined();
  // 656: ... main_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_info();
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__183_1;
}
static void cont__183_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 656: if main_info.is_undefined:
  // 657:   Error "
  // 658:     Source file "@(main_filename)" does not exist!@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__183_2;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__183_6;
}
static void entry__183_2(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 657: ... "
  // 658:   Source file "@(main_filename)" does not exist!@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__9b6a42533552c66c;
  arguments->slots[1] = get__main_filename();
  arguments->slots[2] = string__79c06fde49ef2e97;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__183_5;
}
static void cont__183_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 657: Error "
  // 658:   Source file "@(main_filename)" does not exist!@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__183_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 986: $$t undefined
  var._t = get__undefined();
  // 1133: if do_time_passes: !t current_time()
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = func__198_1;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__198_3;
}
static void entry__198_1(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1133: ... !t current_time()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__current_time();
  func = myself->type;
  frame->cont = cont__198_2;
}
static void cont__198_2(void) {
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
static void cont__198_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1134: cond
  // 1135:   ->
  // 1136:     ||
  // 1137:       do_check_only
  // 1138:       do_dump_trees
  // 1139:       do_pretty_print
  // 1140:       do_print_simplified_source
  // 1141:     dump_source_or_check
  // 1142:   -> do_print_c print_c
  // 1143:   -> do_list_dependencies list_dependencies
  // ...
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = func__199_1;
  arguments->slots[1] = func__199_8;
  arguments->slots[2] = func__199_9;
  arguments->slots[3] = func__199_10;
  arguments->slots[4] = func__199_11;
  arguments->slots[5] = func__build_executable;
  result_count = 0;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__199_13;
}
static void entry__199_1(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_check_only();
  arguments->slots[1] = func__199_2;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__199_7;
}
static void entry__199_2(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_dump_trees();
  arguments->slots[1] = func__199_3;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__199_6;
}
static void entry__199_3(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_pretty_print();
  arguments->slots[1] = func__199_4;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__199_5;
}
static void entry__199_4(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1140: do_print_simplified_source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__do_print_simplified_source();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__199_5(void) {
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
static void cont__199_6(void) {
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
static void cont__199_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1135: ->
  // 1136:   ||
  // 1137:     do_check_only
  // 1138:     do_dump_trees
  // 1139:     do_pretty_print
  // 1140:     do_print_simplified_source
  // 1141:   dump_source_or_check
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__dump_source_or_check;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__199_8(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1142: -> do_print_c print_c
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_print_c;
  arguments->slots[1] = func__print_c;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__199_9(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1143: -> do_list_dependencies list_dependencies
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_list_dependencies;
  arguments->slots[1] = func__list_dependencies;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__199_10(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1144: -> do_build_codeblocks_project build_codeblocks_project
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_build_codeblocks_project;
  arguments->slots[1] = func__build_codeblocks_project;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__199_11(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1145: ... main_info.is_a_directory
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_info();
  result_count = 1;
  myself = get__is_a_directory();
  func = myself->type;
  frame->cont = cont__199_12;
}
static void cont__199_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1145: -> main_info.is_a_directory build_library
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__build_library;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__199_13(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = get__std__terminate();
  func = myself->type;
  frame->cont = cont__200_1;
}
static void cont__200_1(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  terminate(0); // should never be reached
}
static void entry__compiler__show_compiler_debug_info_2(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // args: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* args */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 278: ... ewriteln args*
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__show_compiler_debug_info(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // args: 0
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 278: ... : ewriteln args*
  frame->slots[1] /* temp__1 */ = create_closure(entry__compiler__show_compiler_debug_info_2, 0);
  // 278: if do_show_compiler_debug_infos: ewriteln args*
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_show_compiler_debug_infos();
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__resolve_filename(void) {
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
  // 318: ... resolved_libraries.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._resolved_libraries;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__resolve_filename_2;
}
static void cont__resolve_filename_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 318: if resolved_libraries.is_undefined:
  // 319:   !resolved_libraries empty_table
  // 320:   for_each simlibpaths: (path)
  // 321:     if file_exists(path):
  // 322:       for_each directory(path): (entry)
  // 323:         if entry.is_a_directory:
  // 324:           $name std::filename_of(entry)
  // 325:           if name .matches. NAME: !resolved_libraries(name) fullname_of(entry)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = func__resolve_filename_3;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__resolve_filename_16;
}
static void entry__resolve_filename_13(void) {
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
  // 325: ... !resolved_libraries(name) fullname_of(entry)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* entry */;
  result_count = 1;
  myself = get__fullname_of();
  func = myself->type;
  frame->cont = cont__resolve_filename_14;
}
static void cont__resolve_filename_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 325: ... !resolved_libraries(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = var._resolved_libraries;
  func = myself->type;
  frame->cont = cont__resolve_filename_15;
}
static void cont__resolve_filename_15(void) {
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
static void entry__resolve_filename_10(void) {
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
  // 324: $name std::filename_of(entry)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* entry */;
  result_count = 1;
  myself = get__std__filename_of();
  func = myself->type;
  frame->cont = cont__resolve_filename_11;
}
static void cont__resolve_filename_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* name */, arguments->slots[0]);
  // 325: ... name .matches. NAME
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* name */;
  arguments->slots[1] = get__NAME();
  result_count = 1;
  myself = get__matches();
  func = myself->type;
  frame->cont = cont__resolve_filename_12;
}
static void cont__resolve_filename_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 325: ... : !resolved_libraries(name) fullname_of(entry)
  frame->slots[3] /* temp__2 */ = create_closure(entry__resolve_filename_13, 0);
  // 325: if name .matches. NAME: !resolved_libraries(name) fullname_of(entry)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__resolve_filename_8(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // entry: 0
  if (argument_count != 1) {
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
  frame->cont = cont__resolve_filename_9;
}
static void cont__resolve_filename_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 323: ... :
  // 324:   $name std::filename_of(entry)
  // 325:   if name .matches. NAME: !resolved_libraries(name) fullname_of(entry)
  frame->slots[2] /* temp__2 */ = create_closure(entry__resolve_filename_10, 0);
  // 323: if entry.is_a_directory:
  // 324:   $name std::filename_of(entry)
  // 325:   if name .matches. NAME: !resolved_libraries(name) fullname_of(entry)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__resolve_filename_6(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // path: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* path */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 322: ... directory(path)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* path */;
  result_count = 1;
  myself = get__directory();
  func = myself->type;
  frame->cont = cont__resolve_filename_7;
}
static void cont__resolve_filename_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 322: for_each directory(path): (entry)
  // 323:   if entry.is_a_directory:
  // 324:     $name std::filename_of(entry)
  // 325:     if name .matches. NAME: !resolved_libraries(name) fullname_of(entry)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__resolve_filename_8;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__resolve_filename_4(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // path: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 321: ... file_exists(path)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* path */;
  result_count = 1;
  myself = get__file_exists();
  func = myself->type;
  frame->cont = cont__resolve_filename_5;
}
static void cont__resolve_filename_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 321: ... :
  // 322:   for_each directory(path): (entry)
  // 323:     if entry.is_a_directory:
  // 324:       $name std::filename_of(entry)
  // 325:       if name .matches. NAME: !resolved_libraries(name) fullname_of(entry)
  frame->slots[2] /* temp__2 */ = create_closure(entry__resolve_filename_6, 0);
  // 321: if file_exists(path):
  // 322:   for_each directory(path): (entry)
  // 323:     if entry.is_a_directory:
  // 324:       $name std::filename_of(entry)
  // 325:       if name .matches. NAME: !resolved_libraries(name) fullname_of(entry)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__resolve_filename_3(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 319: !resolved_libraries empty_table
  var._resolved_libraries = get__empty_table();
  // 320: for_each simlibpaths: (path)
  // 321:   if file_exists(path):
  // 322:     for_each directory(path): (entry)
  // 323:       if entry.is_a_directory:
  // 324:         $name std::filename_of(entry)
  // 325:         if name .matches. NAME: !resolved_libraries(name) fullname_of(entry)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._simlibpaths;
  arguments->slots[1] = func__resolve_filename_4;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__resolve_filename_16(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 326: $libname filename .before. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__resolve_filename_17;
}
static void cont__resolve_filename_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* libname */, arguments->slots[0]);
  // 327: $libpath resolved_libraries(libname)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* libname */;
  result_count = 1;
  myself = var._resolved_libraries;
  func = myself->type;
  frame->cont = cont__resolve_filename_18;
}
static void cont__resolve_filename_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* libpath */, arguments->slots[0]);
  // 328: ... libpath.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* libpath */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__resolve_filename_19;
}
static void cont__resolve_filename_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 328: ... :
  // 329:   Error "
  // 330:     Cannot resolve required library "@(libname)@quot;!@
  frame->slots[4] /* temp__2 */ = create_closure(entry__resolve_filename_20, 0);
  // 328: if libpath.is_undefined:
  // 329:   Error "
  // 330:     Cannot resolve required library "@(libname)@quot;!@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__resolve_filename_24;
}
static void entry__resolve_filename_20(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // libname: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* libname */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 329: ... "
  // 330:   Cannot resolve required library "@(libname)@quot;!@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__373a794ad67f2aca;
  arguments->slots[1] = frame->slots[0] /* libname */;
  arguments->slots[2] = string__2d7981f4e6182be4;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__resolve_filename_23;
}
static void cont__resolve_filename_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 329: Error "
  // 330:   Cannot resolve required library "@(libname)@quot;!@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__resolve_filename_24(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 331: ... filename .from. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__from();
  func = myself->type;
  frame->cont = cont__resolve_filename_25;
}
static void cont__resolve_filename_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 331: ... string(libpath filename .from. '/')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* libpath */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__resolve_filename_26;
}
static void cont__resolve_filename_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 331: -> string(libpath filename .from. '/')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__add_module_infos(void) {
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
  // 342: ... --SORT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__SORT();
  arguments->slots[1] = get__std__true();
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__add_module_infos_2;
}
static void cont__add_module_infos_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 342: $entries directory(--SORT path)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[0] /* path */;
  result_count = 1;
  myself = get__directory();
  func = myself->type;
  frame->cont = cont__add_module_infos_3;
}
static void cont__add_module_infos_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* entries */, arguments->slots[0]);
  // 343: $$filenames empty_set
  ((CELL *)frame->slots[4])->contents /* filenames */ = get__empty_set();
  // 344: $$directories empty_list
  ((CELL *)frame->slots[5])->contents /* directories */ = get__empty_list();
  // 345: $$modules empty_key_order_set
  ((CELL *)frame->slots[6])->contents /* modules */ = get__empty_key_order_set();
  // 346: ... : (entry)
  // 347:   $name std::filename_of(entry)
  // 348:   cond
  // 349:     -> entry.is_a_directory: if name .matches. NAME: push &directories name
  // 350:     -> name .has_suffix. ".sim":
  // 351:       $submodule_name name .without_suffix. (some(".meta"), ".sim")
  // 352:       !filenames(submodule_name) true
  // 353:       $meta_level (length_of(name)-length_of(submodule_name)-4)/5
  // 354:       $stored_level meta_levels(submodule_name)
  // 355:       if stored_level.is_undefined || meta_level > stored_level:
  // ...
  frame->slots[7] /* temp__1 */ = create_closure(entry__add_module_infos_4, 1);
  // 346: for_each entries: (entry)
  // 347:   $name std::filename_of(entry)
  // 348:   cond
  // 349:     -> entry.is_a_directory: if name .matches. NAME: push &directories name
  // 350:     -> name .has_suffix. ".sim":
  // 351:       $submodule_name name .without_suffix. (some(".meta"), ".sim")
  // 352:       !filenames(submodule_name) true
  // 353:       $meta_level (length_of(name)-length_of(submodule_name)-4)/5
  // 354:       $stored_level meta_levels(submodule_name)
  // 355:       if stored_level.is_undefined || meta_level > stored_level:
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* entries */;
  arguments->slots[1] = frame->slots[7] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__add_module_infos_38;
}
static void entry__add_module_infos_15(void) {
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
  // 351: ... some(".meta")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__505aea43ea6cf036;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__add_module_infos_17;
}
static void cont__add_module_infos_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__2 */ = arguments->slots[0];
  // 351: ... some(".meta"), ".sim"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__2 */;
  arguments->slots[1] = string__9e0aed8b5d287d54;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__add_module_infos_18;
}
static void cont__add_module_infos_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 351: $submodule_name name .without_suffix. (some(".meta"), ".sim")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = get__without_suffix();
  func = myself->type;
  frame->cont = cont__add_module_infos_19;
}
static void cont__add_module_infos_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* submodule_name */, arguments->slots[0]);
  // 352: !filenames(submodule_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* submodule_name */;
  arguments->slots[1] = get__true();
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* filenames */;
  func = myself->type;
  frame->cont = cont__add_module_infos_20;
}
static void cont__add_module_infos_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* filenames */ = arguments->slots[0];
  // 353: ... length_of(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__add_module_infos_21;
}
static void cont__add_module_infos_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__3 */ = arguments->slots[0];
  // 353: ... length_of(submodule_name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* submodule_name */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__add_module_infos_22;
}
static void cont__add_module_infos_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__4 */ = arguments->slots[0];
  // 353: ... length_of(name)-length_of(submodule_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__3 */;
  arguments->slots[1] = frame->slots[12] /* temp__4 */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__add_module_infos_23;
}
static void cont__add_module_infos_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__2 */ = arguments->slots[0];
  // 353: ... length_of(name)-length_of(submodule_name)-4
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__2 */;
  arguments->slots[1] = number__4;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__add_module_infos_24;
}
static void cont__add_module_infos_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 353: $meta_level (length_of(name)-length_of(submodule_name)-4)/5
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__std__over();
  func = myself->type;
  frame->cont = cont__add_module_infos_25;
}
static void cont__add_module_infos_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* meta_level */, arguments->slots[0]);
  // 354: $stored_level meta_levels(submodule_name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* submodule_name */;
  result_count = 1;
  myself = var._meta_levels;
  func = myself->type;
  frame->cont = cont__add_module_infos_26;
}
static void cont__add_module_infos_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* stored_level */, arguments->slots[0]);
  // 355: ... stored_level.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* stored_level */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__add_module_infos_27;
}
static void cont__add_module_infos_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__2 */ = arguments->slots[0];
  // 355: ... meta_level > stored_level
  frame->slots[11] /* temp__3 */ = create_closure(entry__add_module_infos_28, 0);
  // 355: ... stored_level.is_undefined || meta_level > stored_level
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__2 */;
  arguments->slots[1] = frame->slots[11] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__add_module_infos_30;
}
static void entry__add_module_infos_28(void) {
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
  // 355: ... meta_level > stored_level
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stored_level */;
  arguments->slots[1] = frame->slots[1] /* meta_level */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__add_module_infos_29;
}
static void cont__add_module_infos_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 355: ... meta_level > stored_level
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__add_module_infos_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 355: ... :
  // 356:   !meta_levels(submodule_name) meta_level
  frame->slots[12] /* temp__4 */ = create_closure(entry__add_module_infos_31, 0);
  // 355: if stored_level.is_undefined || meta_level > stored_level:
  // 356:   !meta_levels(submodule_name) meta_level
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = frame->slots[12] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__add_module_infos_33;
}
static void entry__add_module_infos_31(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // submodule_name: 0
  // meta_level: 1
  frame->slots[0] = myself->closure.frame->slots[4]; /* submodule_name */
  frame->slots[1] = myself->closure.frame->slots[5]; /* meta_level */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 356: !meta_levels(submodule_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* submodule_name */;
  arguments->slots[1] = frame->slots[1] /* meta_level */;
  result_count = 1;
  myself = var._meta_levels;
  func = myself->type;
  frame->cont = cont__add_module_infos_32;
}
static void cont__add_module_infos_32(void) {
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
static void cont__add_module_infos_33(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 357: $basename submodule_name .truncate_from. '-'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* submodule_name */;
  arguments->slots[1] = character__45;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__add_module_infos_34;
}
static void cont__add_module_infos_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[7] /* basename */, arguments->slots[0]);
  // 358: !modules(basename)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* basename */;
  arguments->slots[1] = get__true();
  result_count = 1;
  myself = ((CELL *)frame->slots[2])->contents /* modules */;
  func = myself->type;
  frame->cont = cont__add_module_infos_35;
}
static void cont__add_module_infos_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* modules */ = arguments->slots[0];
  // 359: $mod_name string(mod_path basename)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* mod_path */;
  arguments->slots[1] = frame->slots[7] /* basename */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__add_module_infos_36;
}
static void cont__add_module_infos_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[8] /* mod_name */, arguments->slots[0]);
  // 360: !module_info(mod_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* mod_name */;
  arguments->slots[1] = get__empty_key_order_table();
  result_count = 1;
  myself = var._module_info;
  func = myself->type;
  frame->cont = cont__add_module_infos_37;
}
static void cont__add_module_infos_37(void) {
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
static void entry__add_module_infos_10(void) {
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
  // 349: ... push &directories name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* directories */;
  arguments->slots[1] = frame->slots[1] /* name */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__add_module_infos_11;
}
static void cont__add_module_infos_11(void) {
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
static void entry__add_module_infos_8(void) {
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
  // 349: ... name .matches. NAME
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = get__NAME();
  result_count = 1;
  myself = get__matches();
  func = myself->type;
  frame->cont = cont__add_module_infos_9;
}
static void cont__add_module_infos_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 349: ... : push &directories name
  frame->slots[3] /* temp__2 */ = create_closure(entry__add_module_infos_10, 0);
  // 349: ... if name .matches. NAME: push &directories name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__add_module_infos_6(void) {
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
  // 349: ... entry.is_a_directory
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* entry */;
  result_count = 1;
  myself = get__is_a_directory();
  func = myself->type;
  frame->cont = cont__add_module_infos_7;
}
static void cont__add_module_infos_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 349: ... : if name .matches. NAME: push &directories name
  frame->slots[4] /* temp__2 */ = create_closure(entry__add_module_infos_8, 0);
  // 349: -> entry.is_a_directory: if name .matches. NAME: push &directories name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__add_module_infos_12(void) {
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
  // 350: ... name .has_suffix. ".sim"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = string__9e0aed8b5d287d54;
  result_count = 1;
  myself = get__has_suffix();
  func = myself->type;
  frame->cont = cont__add_module_infos_14;
}
static void cont__add_module_infos_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 350: ... :
  // 351:   $submodule_name name .without_suffix. (some(".meta"), ".sim")
  // 352:   !filenames(submodule_name) true
  // 353:   $meta_level (length_of(name)-length_of(submodule_name)-4)/5
  // 354:   $stored_level meta_levels(submodule_name)
  // 355:   if stored_level.is_undefined || meta_level > stored_level:
  // 356:     !meta_levels(submodule_name) meta_level
  // 357:   $basename submodule_name .truncate_from. '-'
  // 358:   !modules(basename) true
  // 359:   $mod_name string(mod_path basename)
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__add_module_infos_15, 0);
  // 350: -> name .has_suffix. ".sim":
  // 351:   $submodule_name name .without_suffix. (some(".meta"), ".sim")
  // 352:   !filenames(submodule_name) true
  // 353:   $meta_level (length_of(name)-length_of(submodule_name)-4)/5
  // 354:   $stored_level meta_levels(submodule_name)
  // 355:   if stored_level.is_undefined || meta_level > stored_level:
  // 356:     !meta_levels(submodule_name) meta_level
  // 357:   $basename submodule_name .truncate_from. '-'
  // 358:   !modules(basename) true
  // 359:   $mod_name string(mod_path basename)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__add_module_infos_4(void) {
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
  // 347: $name std::filename_of(entry)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* entry */;
  result_count = 1;
  myself = get__std__filename_of();
  func = myself->type;
  frame->cont = cont__add_module_infos_5;
}
static void cont__add_module_infos_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* name */, arguments->slots[0]);
  // 349: -> entry.is_a_directory: if name .matches. NAME: push &directories name
  frame->slots[6] /* temp__1 */ = create_closure(entry__add_module_infos_6, 0);
  // 350: -> name .has_suffix. ".sim":
  // 351:   $submodule_name name .without_suffix. (some(".meta"), ".sim")
  // 352:   !filenames(submodule_name) true
  // 353:   $meta_level (length_of(name)-length_of(submodule_name)-4)/5
  // 354:   $stored_level meta_levels(submodule_name)
  // 355:   if stored_level.is_undefined || meta_level > stored_level:
  // 356:     !meta_levels(submodule_name) meta_level
  // 357:   $basename submodule_name .truncate_from. '-'
  // 358:   !modules(basename) true
  // 359:   $mod_name string(mod_path basename)
  // ...
  frame->slots[7] /* temp__2 */ = create_closure(entry__add_module_infos_12, 0);
  // 348: cond
  // 349:   -> entry.is_a_directory: if name .matches. NAME: push &directories name
  // 350:   -> name .has_suffix. ".sim":
  // 351:     $submodule_name name .without_suffix. (some(".meta"), ".sim")
  // 352:     !filenames(submodule_name) true
  // 353:     $meta_level (length_of(name)-length_of(submodule_name)-4)/5
  // 354:     $stored_level meta_levels(submodule_name)
  // 355:     if stored_level.is_undefined || meta_level > stored_level:
  // 356:       !meta_levels(submodule_name) meta_level
  // 357:     $basename submodule_name .truncate_from. '-'
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
static void cont__add_module_infos_38(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 361: ... : (filename)
  // 362:   if filename .contains. '-':
  // 363:     unless filename .has_suffix. "-common":
  // 364:       $maybe_push_common: (plat)
  // 365:         $common_name string(name "-" plat "-common")
  // 366:         if filenames(common_name): push &files common_name
  // 367:       
  // 368:       $name filename .before. '-'
  // 369:       $mod_name string(mod_path name .truncate_from. '-')
  // 370:       $platform filename .behind. '-'
  // ...
  frame->slots[7] /* temp__1 */ = create_closure(entry__add_module_infos_39, 1);
  // 361: for_each filenames: (filename)
  // 362:   if filename .contains. '-':
  // 363:     unless filename .has_suffix. "-common":
  // 364:       $maybe_push_common: (plat)
  // 365:         $common_name string(name "-" plat "-common")
  // 366:         if filenames(common_name): push &files common_name
  // 367:       
  // 368:       $name filename .before. '-'
  // 369:       $mod_name string(mod_path name .truncate_from. '-')
  // 370:       $platform filename .behind. '-'
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* filenames */;
  arguments->slots[1] = frame->slots[7] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__add_module_infos_74;
}
static void entry__add_module_infos_44(void) {
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
  // 364: ... : (plat)
  // 365:   $common_name string(name "-" plat "-common")
  // 366:   if filenames(common_name): push &files common_name
  frame->slots[9] /* temp__1 */ = create_closure(entry__add_module_infos_45, 1);
  // 364: $maybe_push_common: (plat)
  // 365:   $common_name string(name "-" plat "-common")
  // 366:   if filenames(common_name): push &files common_name
  initialize_future(frame->slots[3] /* maybe_push_common */, frame->slots[9] /* temp__1 */);
  // 368: $name filename .before. '-'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* filename */;
  arguments->slots[1] = character__45;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__add_module_infos_51;
}
static void entry__add_module_infos_49(void) {
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
  // 366: ... push &files common_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* files */;
  arguments->slots[1] = frame->slots[1] /* common_name */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__add_module_infos_50;
}
static void cont__add_module_infos_50(void) {
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
static void entry__add_module_infos_45(void) {
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
  // 365: $common_name string(name "-" plat "-common")
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* name */;
  arguments->slots[1] = string__578a5af303e9ccc;
  arguments->slots[2] = frame->slots[0] /* plat */;
  arguments->slots[3] = string__a9300e9315c23094;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__add_module_infos_47;
}
static void cont__add_module_infos_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* common_name */, arguments->slots[0]);
  // 366: ... filenames(common_name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* common_name */;
  result_count = 1;
  myself = ((CELL *)frame->slots[2])->contents /* filenames */;
  func = myself->type;
  frame->cont = cont__add_module_infos_48;
}
static void cont__add_module_infos_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 366: ... : push &files common_name
  frame->slots[6] /* temp__2 */ = create_closure(entry__add_module_infos_49, 0);
  // 366: if filenames(common_name): push &files common_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__add_module_infos_51(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* name */, arguments->slots[0]);
  // 369: ... name .truncate_from. '-'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* name */;
  arguments->slots[1] = character__45;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__add_module_infos_52;
}
static void cont__add_module_infos_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 369: $mod_name string(mod_path name .truncate_from. '-')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* mod_path */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__add_module_infos_53;
}
static void cont__add_module_infos_53(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* mod_name */, arguments->slots[0]);
  // 370: $platform filename .behind. '-'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* filename */;
  arguments->slots[1] = character__45;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__add_module_infos_54;
}
static void cont__add_module_infos_54(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* platform */, arguments->slots[0]);
  // 371: $$parent supported_platforms(platform)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* platform */;
  result_count = 1;
  myself = var._supported_platforms;
  func = myself->type;
  frame->cont = cont__add_module_infos_55;
}
static void cont__add_module_infos_55(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[7])->contents /* parent */ = arguments->slots[0];
  // 372: ... parent.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[7])->contents /* parent */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__add_module_infos_56;
}
static void cont__add_module_infos_56(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 372: ... :
  // 373:   Error "
  // 374:     The platform "@(platform)" is not supported!@
  frame->slots[10] /* temp__2 */ = create_closure(entry__add_module_infos_57, 0);
  // 372: unless parent.is_defined:
  // 373:   Error "
  // 374:     The platform "@(platform)" is not supported!@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__add_module_infos_61;
}
static void entry__add_module_infos_57(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // platform: 0
  frame->slots[0] = myself->closure.frame->slots[6]; /* platform */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 373: ... "
  // 374:   The platform "@(platform)" is not supported!@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__bf5121a1ba54e344;
  arguments->slots[1] = frame->slots[0] /* platform */;
  arguments->slots[2] = string__b566882ea60ef100;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__add_module_infos_60;
}
static void cont__add_module_infos_60(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 373: Error "
  // 374:   The platform "@(platform)" is not supported!@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__add_module_infos_61(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 375: $$files list(filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* filename */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__add_module_infos_62;
}
static void cont__add_module_infos_62(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[8])->contents /* files */ = arguments->slots[0];
  // 376: maybe_push_common platform
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* platform */;
  result_count = 0;
  myself = frame->slots[3] /* maybe_push_common */;
  func = myself->type;
  frame->cont = cont__add_module_infos_63;
}
static void cont__add_module_infos_63(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 377: ... -> parent != NONE:
  // 378:   maybe_push_common parent
  // 379:   !parent supported_platforms(parent)
  frame->slots[9] /* temp__1 */ = create_closure(entry__add_module_infos_64, 0);
  // 377: while -> parent != NONE:
  // 378:   maybe_push_common parent
  // 379:   !parent supported_platforms(parent)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  result_count = 0;
  myself = get__while();
  func = myself->type;
  frame->cont = cont__add_module_infos_70;
}
static void entry__add_module_infos_67(void) {
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
  // 378: maybe_push_common parent
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* parent */;
  result_count = 0;
  myself = frame->slots[0] /* maybe_push_common */;
  func = myself->type;
  frame->cont = cont__add_module_infos_68;
}
static void cont__add_module_infos_68(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 379: !parent supported_platforms(parent)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* parent */;
  result_count = 1;
  myself = var._supported_platforms;
  func = myself->type;
  frame->cont = cont__add_module_infos_69;
}
static void cont__add_module_infos_69(void) {
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
static void entry__add_module_infos_64(void) {
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
  // 377: ... parent != NONE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parent */;
  arguments->slots[1] = unique__NONE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__add_module_infos_65;
}
static void cont__add_module_infos_65(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 377: ... parent != NONE
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__add_module_infos_66;
}
static void cont__add_module_infos_66(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 377: ... :
  // 378:   maybe_push_common parent
  // 379:   !parent supported_platforms(parent)
  frame->slots[4] /* temp__3 */ = create_closure(entry__add_module_infos_67, 0);
  // 377: ... -> parent != NONE:
  // 378:   maybe_push_common parent
  // 379:   !parent supported_platforms(parent)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__add_module_infos_70(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 380: ... module_info(mod_name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* mod_name */;
  result_count = 1;
  myself = var._module_info;
  func = myself->type;
  frame->cont = cont__add_module_infos_71;
}
static void cont__add_module_infos_71(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 380: !module_info(mod_name)(platform)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* platform */;
  arguments->slots[1] = ((CELL *)frame->slots[8])->contents /* files */;
  result_count = 1;
  myself = frame->slots[9] /* temp__1 */;
  func = myself->type;
  frame->cont = cont__add_module_infos_72;
}
static void cont__add_module_infos_72(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 380: !module_info(mod_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* mod_name */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = var._module_info;
  func = myself->type;
  frame->cont = cont__add_module_infos_73;
}
static void cont__add_module_infos_73(void) {
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
static void entry__add_module_infos_41(void) {
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
  // 363: ... filename .has_suffix. "-common"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  arguments->slots[1] = string__a9300e9315c23094;
  result_count = 1;
  myself = get__has_suffix();
  func = myself->type;
  frame->cont = cont__add_module_infos_43;
}
static void cont__add_module_infos_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 363: ... :
  // 364:   $maybe_push_common: (plat)
  // 365:     $common_name string(name "-" plat "-common")
  // 366:     if filenames(common_name): push &files common_name
  // 367:   
  // 368:   $name filename .before. '-'
  // 369:   $mod_name string(mod_path name .truncate_from. '-')
  // 370:   $platform filename .behind. '-'
  // 371:   $$parent supported_platforms(platform)
  // 372:   unless parent.is_defined:
  // ...
  frame->slots[4] /* temp__2 */ = create_closure(entry__add_module_infos_44, 0);
  // 363: unless filename .has_suffix. "-common":
  // 364:   $maybe_push_common: (plat)
  // 365:     $common_name string(name "-" plat "-common")
  // 366:     if filenames(common_name): push &files common_name
  // 367:   
  // 368:   $name filename .before. '-'
  // 369:   $mod_name string(mod_path name .truncate_from. '-')
  // 370:   $platform filename .behind. '-'
  // 371:   $$parent supported_platforms(platform)
  // 372:   unless parent.is_defined:
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
static void entry__add_module_infos_39(void) {
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
  // 362: ... filename .contains. '-'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  arguments->slots[1] = character__45;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__add_module_infos_40;
}
static void cont__add_module_infos_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 362: ... :
  // 363:   unless filename .has_suffix. "-common":
  // 364:     $maybe_push_common: (plat)
  // 365:       $common_name string(name "-" plat "-common")
  // 366:       if filenames(common_name): push &files common_name
  // 367:     
  // 368:     $name filename .before. '-'
  // 369:     $mod_name string(mod_path name .truncate_from. '-')
  // 370:     $platform filename .behind. '-'
  // 371:     $$parent supported_platforms(platform)
  // ...
  frame->slots[4] /* temp__2 */ = create_closure(entry__add_module_infos_41, 0);
  // 362: if filename .contains. '-':
  // 363:   unless filename .has_suffix. "-common":
  // 364:     $maybe_push_common: (plat)
  // 365:       $common_name string(name "-" plat "-common")
  // 366:       if filenames(common_name): push &files common_name
  // 367:     
  // 368:     $name filename .before. '-'
  // 369:     $mod_name string(mod_path name .truncate_from. '-')
  // 370:     $platform filename .behind. '-'
  // 371:     $$parent supported_platforms(platform)
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
static void cont__add_module_infos_74(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 381: ... parameter_count_of(return)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* return */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__add_module_infos_75;
}
static void cont__add_module_infos_75(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 381: ... parameter_count_of(return) == 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__2 */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__add_module_infos_76;
}
static void cont__add_module_infos_76(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 381: ... : return directories modules
  frame->slots[9] /* temp__3 */ = create_closure(entry__add_module_infos_77, 0);
  // 381: if parameter_count_of(return) == 2: return directories modules
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__add_module_infos_78;
}
static void entry__add_module_infos_77(void) {
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
  // 381: ... return directories modules
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* directories */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* modules */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__add_module_infos_78(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__lookup_4(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // info: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 394: -> info
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__lookup_5(void) {
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
  // 396: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__lookup_6;
}
static void cont__lookup_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 396: ... before(mod_filename '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__lookup_7;
}
static void cont__lookup_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 396: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__lookup_8;
}
static void cont__lookup_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 396: ... until(mod_name '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* mod_name */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = get__until();
  func = myself->type;
  frame->cont = cont__lookup_9;
}
static void cont__lookup_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 396: add_module_infos before(mod_filename '/' -1) until(mod_name '/' -1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 0;
  myself = func__add_module_infos;
  func = myself->type;
  frame->cont = cont__lookup_10;
}
static void cont__lookup_10(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 397: ... module_info(mod_name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* mod_name */;
  result_count = 1;
  myself = var._module_info;
  func = myself->type;
  frame->cont = cont__lookup_11;
}
static void cont__lookup_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 397: -> module_info(mod_name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__lookup(void) {
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
  // 391: $info module_info(mod_name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* mod_name */;
  result_count = 1;
  myself = var._module_info;
  func = myself->type;
  frame->cont = cont__lookup_2;
}
static void cont__lookup_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* info */, arguments->slots[0]);
  // 393: info.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* info */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__lookup_3;
}
static void cont__lookup_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 394: -> info
  frame->slots[4] /* temp__2 */ = create_closure(entry__lookup_4, 0);
  // 395: :
  // 396:   add_module_infos before(mod_filename '/' -1) until(mod_name '/' -1)
  // 397:   -> module_info(mod_name)
  frame->slots[5] /* temp__3 */ = create_closure(entry__lookup_5, 0);
  // 392: if
  // 393:   info.is_defined
  // 394:   -> info
  // 395:   :
  // 396:     add_module_infos before(mod_filename '/' -1) until(mod_name '/' -1)
  // 397:     -> module_info(mod_name)
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
static void entry__CC(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // args: 0
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 400: ... : ewriteln c_compiler() ' ' join(args)
  frame->slots[1] /* temp__1 */ = create_closure(entry__CC_2, 0);
  // 400: if do_show_debug_infos: ewriteln c_compiler() ' ' join(args)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_show_debug_infos();
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__CC_5;
}
static void entry__CC_2(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // args: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* args */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 400: ... c_compiler()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__c_compiler();
  func = myself->type;
  frame->cont = cont__CC_3;
}
static void cont__CC_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 400: ... join(args)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* args */;
  result_count = 1;
  myself = get__join();
  func = myself->type;
  frame->cont = cont__CC_4;
}
static void cont__CC_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 400: ... ewriteln c_compiler() ' ' join(args)
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
static void cont__CC_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 401: cc args*
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = frame->caller_result_count;
  myself = var._cc;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compile_c_4(void) {
  allocate_initialized_frame_gc(2, 6);
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
  // 405: CC
  // 406:   $_out
  // 407:   $err
  // 408:   $success
  // 409:   cpp_options*
  // 410:   cc_options*
  // 411:   "-c"
  // 412:   c_filename
  // 413:   "-o"
  // 414:   o_filename
  argument_count = 0;
  arguments = node_p;
  unfold(var._cpp_options);
  unfold(var._cc_options);
  arguments->slots[argument_count++] = string__2d7981f4e6602ba6;
  arguments->slots[argument_count++] = frame->slots[0] /* c_filename */;
  arguments->slots[argument_count++] = string__2d7981f4e6602baa;
  arguments->slots[argument_count++] = frame->slots[1] /* o_filename */;
  result_count = 3;
  myself = func__CC;
  func = myself->type;
  frame->cont = cont__compile_c_7;
}
static void cont__compile_c_7(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* out */, arguments->slots[0]);
  initialize_future(frame->slots[3] /* err */, arguments->slots[1]);
  initialize_future(frame->slots[4] /* success */, arguments->slots[2]);
  // 415: ... :
  // 416:   Error "Failed to compile @(c_filename)@nl;@(err.from_utf8)@nl;"
  frame->slots[5] /* temp__1 */ = create_closure(entry__compile_c_8, 0);
  // 415: unless success:
  // 416:   Error "Failed to compile @(c_filename)@nl;@(err.from_utf8)@nl;"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* success */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__compile_c_13;
}
static void entry__compile_c_8(void) {
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
  // 416: ... err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* err */;
  result_count = 1;
  myself = get__from_utf8();
  func = myself->type;
  frame->cont = cont__compile_c_9;
}
static void cont__compile_c_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 416: ... "Failed to compile @(c_filename)@nl;@(err.from_utf8)@nl;"
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__ca9b4802029a5965;
  arguments->slots[1] = frame->slots[0] /* c_filename */;
  arguments->slots[2] = string__578a5af303e9ceb;
  arguments->slots[3] = frame->slots[3] /* temp__2 */;
  arguments->slots[4] = string__578a5af303e9ceb;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compile_c_12;
}
static void cont__compile_c_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 416: Error "Failed to compile @(c_filename)@nl;@(err.from_utf8)@nl;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compile_c_13(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 417: !do_link true
  set__do_link(get__true());
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compile_c(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // c_filename: 0
  // o_filename: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 404: ... do_build_codeblocks_project || do_list_dependencies
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_build_codeblocks_project;
  arguments->slots[1] = func__compile_c_2;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__compile_c_3;
}
static void entry__compile_c_2(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 404: ... do_list_dependencies
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._do_list_dependencies;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compile_c_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 404: ... :
  // 405:   CC
  // 406:     $_out
  // 407:     $err
  // 408:     $success
  // 409:     cpp_options*
  // 410:     cc_options*
  // 411:     "-c"
  // 412:     c_filename
  // 413:     "-o"
  // ...
  frame->slots[3] /* temp__2 */ = create_closure(entry__compile_c_4, 0);
  // 404: unless do_build_codeblocks_project || do_list_dependencies:
  // 405:   CC
  // 406:     $_out
  // 407:     $err
  // 408:     $success
  // 409:     cpp_options*
  // 410:     cc_options*
  // 411:     "-c"
  // 412:     c_filename
  // 413:     "-o"
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
static void entry__compile_meta_module_2(void) {
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
  // 429: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__compile_meta_module_3;
}
static void cont__compile_meta_module_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 429: $meta_path truncate_from(mod_filename '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[11] /* temp__1 */;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__compile_meta_module_4;
}
static void cont__compile_meta_module_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* meta_path */, arguments->slots[0]);
  // 430: ... dup(".meta" meta_level)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__505aea43ea6cf036;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* meta_level */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__compile_meta_module_5;
}
static void cont__compile_meta_module_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 430: $filename string(mod_filename dup(".meta" meta_level))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = frame->slots[11] /* temp__1 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__compile_meta_module_6;
}
static void cont__compile_meta_module_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* filename */, arguments->slots[0]);
  // 431: $meta_filename string(filename ".sim")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* filename */;
  arguments->slots[1] = string__9e0aed8b5d287d54;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__compile_meta_module_7;
}
static void cont__compile_meta_module_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* meta_filename */, arguments->slots[0]);
  // 432: ... dup(".meta" meta_level)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__505aea43ea6cf036;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* meta_level */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__compile_meta_module_8;
}
static void cont__compile_meta_module_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 432: $meta_c_filename string(mod_filename dup(".meta" meta_level) ".c")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = frame->slots[11] /* temp__1 */;
  arguments->slots[2] = string__2d7981f4e6782ba6;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__compile_meta_module_10;
}
static void cont__compile_meta_module_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* meta_c_filename */, arguments->slots[0]);
  // 433: ... meta_level-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* meta_level */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__compile_meta_module_11;
}
static void cont__compile_meta_module_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__2 */ = arguments->slots[0];
  // 433: ... dup(".meta" meta_level-1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__505aea43ea6cf036;
  arguments->slots[1] = frame->slots[12] /* temp__2 */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__compile_meta_module_12;
}
static void cont__compile_meta_module_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 433: $sim_filename string(mod_filename dup(".meta" meta_level-1) ".sim")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = frame->slots[11] /* temp__1 */;
  arguments->slots[2] = string__9e0aed8b5d287d54;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__compile_meta_module_13;
}
static void cont__compile_meta_module_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* sim_filename */, arguments->slots[0]);
  // 434: $meta_info stat(meta_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* meta_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__compile_meta_module_14;
}
static void cont__compile_meta_module_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[7] /* meta_info */, arguments->slots[0]);
  // 435: $sim_info stat(sim_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* sim_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__compile_meta_module_15;
}
static void cont__compile_meta_module_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[8] /* sim_info */, arguments->slots[0]);
  // 436: $meta_c_info stat(meta_c_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* meta_c_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__compile_meta_module_16;
}
static void cont__compile_meta_module_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[9] /* meta_c_info */, arguments->slots[0]);
  frame->slots[11] /* temp__1 */ = create_closure(entry__compile_meta_module_17, 0);
  // 438: $$force_rebuild
  // 439:   ||
  // 440:     do_rebuild
  // 441:     sim_info.is_undefined
  // 442:     meta_c_info.is_undefined
  // 443:     modification_time_of(meta_info) > modification_time_of(meta_c_info)
  // 444:     modification_time_of(meta_c_info) > modification_time_of(sim_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_rebuild;
  arguments->slots[1] = frame->slots[11] /* temp__1 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__compile_meta_module_32;
}
static void entry__compile_meta_module_17(void) {
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
  // 441: sim_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* sim_info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__compile_meta_module_18;
}
static void cont__compile_meta_module_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  frame->slots[5] /* temp__3 */ = create_closure(entry__compile_meta_module_19, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__compile_meta_module_31;
}
static void entry__compile_meta_module_19(void) {
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
  // 442: meta_c_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* meta_c_info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__compile_meta_module_20;
}
static void cont__compile_meta_module_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  frame->slots[5] /* temp__3 */ = create_closure(entry__compile_meta_module_21, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__compile_meta_module_30;
}
static void entry__compile_meta_module_21(void) {
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
  // 443: ... modification_time_of(meta_c_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* meta_c_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__compile_meta_module_22;
}
static void cont__compile_meta_module_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 443: modification_time_of(meta_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* meta_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__compile_meta_module_23;
}
static void cont__compile_meta_module_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__4 */ = arguments->slots[0];
  // 443: modification_time_of(meta_info) > modification_time_of(meta_c_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__compile_meta_module_24;
}
static void cont__compile_meta_module_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 444: modification_time_of(meta_c_info) > modification_time_of(sim_info)
  frame->slots[7] /* temp__5 */ = create_closure(entry__compile_meta_module_25, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__5 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__compile_meta_module_29;
}
static void entry__compile_meta_module_25(void) {
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
  // 444: ... modification_time_of(sim_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* sim_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__compile_meta_module_26;
}
static void cont__compile_meta_module_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 444: modification_time_of(meta_c_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* meta_c_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__compile_meta_module_27;
}
static void cont__compile_meta_module_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 444: modification_time_of(meta_c_info) > modification_time_of(sim_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__compile_meta_module_28;
}
static void cont__compile_meta_module_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 444: modification_time_of(meta_c_info) > modification_time_of(sim_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compile_meta_module_29(void) {
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
static void cont__compile_meta_module_30(void) {
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
static void cont__compile_meta_module_31(void) {
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
static void cont__compile_meta_module_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[10])->contents /* force_rebuild */ = arguments->slots[0];
  // 446: ... :
  // 447:   $modification_time modification_time_of(sim_info)
  // 448:   load $meta_c_buf meta_c_filename
  // 449:   do: (-> break)
  // 450:     for_each_line meta_c_buf: ($line)
  // 451:       $check: (data_filename)
  // 452:         $data_info stat(data_filename)
  // 453:         if
  // 454:           ||
  // 455:             data_info.is_undefined
  // ...
  frame->slots[11] /* temp__1 */ = create_closure(entry__compile_meta_module_33, 0);
  // 446: unless force_rebuild:
  // 447:   $modification_time modification_time_of(sim_info)
  // 448:   load $meta_c_buf meta_c_filename
  // 449:   do: (-> break)
  // 450:     for_each_line meta_c_buf: ($line)
  // 451:       $check: (data_filename)
  // 452:         $data_info stat(data_filename)
  // 453:         if
  // 454:           ||
  // 455:             data_info.is_undefined
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[10])->contents /* force_rebuild */;
  arguments->slots[1] = frame->slots[11] /* temp__1 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__compile_meta_module_66;
}
static void entry__compile_meta_module_36(void) {
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
  // 450: ... : ($line)
  // 451:   $check: (data_filename)
  // 452:     $data_info stat(data_filename)
  // 453:     if
  // 454:       ||
  // 455:         data_info.is_undefined
  // 456:         modification_time_of(data_info) > modification_time
  // 457:       :
  // 458:         !force_rebuild true
  // 459:         break
  // ...
  frame->slots[5] /* temp__1 */ = create_closure(entry__compile_meta_module_37, 1);
  // 450: for_each_line meta_c_buf: ($line)
  // 451:   $check: (data_filename)
  // 452:     $data_info stat(data_filename)
  // 453:     if
  // 454:       ||
  // 455:         data_info.is_undefined
  // 456:         modification_time_of(data_info) > modification_time
  // 457:       :
  // 458:         !force_rebuild true
  // 459:         break
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* meta_c_buf */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each_line();
  func = myself->type;
  frame->cont = cont__compile_meta_module_65;
}
static void entry__compile_meta_module_63(void) {
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
  // 471: ... string(path '/' argument)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* path */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[2] /* argument */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__compile_meta_module_64;
}
static void cont__compile_meta_module_64(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 471: ... check string(path '/' argument)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* check */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compile_meta_module_58(void) {
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
  // 469: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__compile_meta_module_59;
}
static void cont__compile_meta_module_59(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 469: ... range(argument 2 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* argument */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__compile_meta_module_60;
}
static void cont__compile_meta_module_60(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 469: ... string(meta_path range(argument 2 -1))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* meta_path */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__compile_meta_module_61;
}
static void cont__compile_meta_module_61(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 469: check string(meta_path range(argument 2 -1))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* check */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compile_meta_module_62(void) {
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
  // 471: ... : (path) check string(path '/' argument)
  frame->slots[2] /* temp__1 */ = create_closure(entry__compile_meta_module_63, 1);
  // 471: for_each simdatapaths: (path) check string(path '/' argument)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._simdatapaths;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compile_meta_module_55(void) {
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
  // 468: argument .has_prefix. "./"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* argument */;
  arguments->slots[1] = string__2d7981f4e6782bea;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__compile_meta_module_57;
}
static void cont__compile_meta_module_57(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 468: ... :
  // 469:   check string(meta_path range(argument 2 -1))
  frame->slots[4] /* temp__2 */ = create_closure(entry__compile_meta_module_58, 0);
  // 470: :
  // 471:   for_each simdatapaths: (path) check string(path '/' argument)
  frame->slots[5] /* temp__3 */ = create_closure(entry__compile_meta_module_62, 0);
  // 467: if
  // 468:   argument .has_prefix. "./":
  // 469:     check string(meta_path range(argument 2 -1))
  // 470:   :
  // 471:     for_each simdatapaths: (path) check string(path '/' argument)
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
static void entry__compile_meta_module_37(void) {
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
  // 451: ... : (data_filename)
  // 452:   $data_info stat(data_filename)
  // 453:   if
  // 454:     ||
  // 455:       data_info.is_undefined
  // 456:       modification_time_of(data_info) > modification_time
  // 457:     :
  // 458:       !force_rebuild true
  // 459:       break
  frame->slots[8] /* temp__1 */ = create_closure(entry__compile_meta_module_38, 1);
  // 451: $check: (data_filename)
  // 452:   $data_info stat(data_filename)
  // 453:   if
  // 454:     ||
  // 455:       data_info.is_undefined
  // 456:       modification_time_of(data_info) > modification_time
  // 457:     :
  // 458:       !force_rebuild true
  // 459:       break
  initialize_future(frame->slots[5] /* check */, frame->slots[8] /* temp__1 */);
  // 461: ... line .has_prefix. "/// "
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  arguments->slots[1] = string__9c0afa8b5f187d19;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__compile_meta_module_47;
}
static void entry__compile_meta_module_45(void) {
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
  // 458: !force_rebuild true
  ((CELL *)frame->slots[0])->contents /* force_rebuild */ = get__true();
  // 459: break
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* break */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compile_meta_module_38(void) {
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
  // 452: $data_info stat(data_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* data_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__compile_meta_module_39;
}
static void cont__compile_meta_module_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* data_info */, arguments->slots[0]);
  // 455: data_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* data_info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__compile_meta_module_40;
}
static void cont__compile_meta_module_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 456: modification_time_of(data_info) > modification_time
  frame->slots[7] /* temp__3 */ = create_closure(entry__compile_meta_module_41, 0);
  // 454: ||
  // 455:   data_info.is_undefined
  // 456:   modification_time_of(data_info) > modification_time
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__compile_meta_module_44;
}
static void entry__compile_meta_module_41(void) {
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
  // 456: modification_time_of(data_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* data_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__compile_meta_module_42;
}
static void cont__compile_meta_module_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 456: modification_time_of(data_info) > modification_time
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* modification_time */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__compile_meta_module_43;
}
static void cont__compile_meta_module_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 456: modification_time_of(data_info) > modification_time
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compile_meta_module_44(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 457: :
  // 458:   !force_rebuild true
  // 459:   break
  frame->slots[8] /* temp__4 */ = create_closure(entry__compile_meta_module_45, 0);
  // 453: if
  // 454:   ||
  // 455:     data_info.is_undefined
  // 456:     modification_time_of(data_info) > modification_time
  // 457:   :
  // 458:     !force_rebuild true
  // 459:     break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compile_meta_module_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 461: unless line .has_prefix. "/// " break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* break */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__compile_meta_module_48;
}
static void cont__compile_meta_module_48(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 462: behind &line ' '
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  arguments->slots[1] = character__32;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__compile_meta_module_49;
}
static void cont__compile_meta_module_49(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* line */ = arguments->slots[0];
  // 463: trim &line
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__compile_meta_module_50;
}
static void cont__compile_meta_module_50(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* line */ = arguments->slots[0];
  // 464: $command line .truncate_from. WHITESPACE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  arguments->slots[1] = var._WHITESPACE;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__compile_meta_module_51;
}
static void cont__compile_meta_module_51(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* command */, arguments->slots[0]);
  // 465: $argument line .behind. WHITESPACE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  arguments->slots[1] = var._WHITESPACE;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__compile_meta_module_52;
}
static void cont__compile_meta_module_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[7] /* argument */, arguments->slots[0]);
  // 466: ... command == "data"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* command */;
  arguments->slots[1] = string__a0ae90b5dc07d58;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__compile_meta_module_54;
}
static void cont__compile_meta_module_54(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 466: ... :
  // 467:   if
  // 468:     argument .has_prefix. "./":
  // 469:       check string(meta_path range(argument 2 -1))
  // 470:     :
  // 471:       for_each simdatapaths: (path) check string(path '/' argument)
  frame->slots[9] /* temp__2 */ = create_closure(entry__compile_meta_module_55, 0);
  // 466: if command == "data":
  // 467:   if
  // 468:     argument .has_prefix. "./":
  // 469:       check string(meta_path range(argument 2 -1))
  // 470:     :
  // 471:       for_each simdatapaths: (path) check string(path '/' argument)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compile_meta_module_65(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__compile_meta_module_33(void) {
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
  // 447: $modification_time modification_time_of(sim_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* sim_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__compile_meta_module_34;
}
static void cont__compile_meta_module_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* modification_time */, arguments->slots[0]);
  // 448: load $meta_c_buf meta_c_filename
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* meta_c_filename */;
  result_count = 1;
  myself = get__load();
  func = myself->type;
  frame->cont = cont__compile_meta_module_35;
}
static void cont__compile_meta_module_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* meta_c_buf */, arguments->slots[0]);
  // 449: ... : (-> break)
  // 450:   for_each_line meta_c_buf: ($line)
  // 451:     $check: (data_filename)
  // 452:       $data_info stat(data_filename)
  // 453:       if
  // 454:         ||
  // 455:           data_info.is_undefined
  // 456:           modification_time_of(data_info) > modification_time
  // 457:         :
  // 458:           !force_rebuild true
  // ...
  frame->slots[6] /* temp__1 */ = create_closure(entry__compile_meta_module_36, 0);
  // 449: do: (-> break)
  // 450:   for_each_line meta_c_buf: ($line)
  // 451:     $check: (data_filename)
  // 452:       $data_info stat(data_filename)
  // 453:       if
  // 454:         ||
  // 455:           data_info.is_undefined
  // 456:           modification_time_of(data_info) > modification_time
  // 457:         :
  // 458:           !force_rebuild true
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__do();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compile_meta_module_66(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 472: ... :
  // 473:   %on_top_level false
  // 474:   %%objects empty_insert_order_set
  // 475:   %%libraries empty_insert_order_set
  // 476:   %%do_link false
  // 477:   %%last_modification_time undefined
  // 478:   %do_build_static_executable false
  // 479:   %main_filename meta_filename
  // 480:   %main_info stat(main_filename)
  // 481:   build_executable
  // ...
  frame->slots[11] /* temp__1 */ = create_closure(entry__compile_meta_module_67, 0);
  // 472: if force_rebuild:
  // 473:   %on_top_level false
  // 474:   %%objects empty_insert_order_set
  // 475:   %%libraries empty_insert_order_set
  // 476:   %%do_link false
  // 477:   %%last_modification_time undefined
  // 478:   %do_build_static_executable false
  // 479:   %main_filename meta_filename
  // 480:   %main_info stat(main_filename)
  // 481:   build_executable
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[10])->contents /* force_rebuild */;
  arguments->slots[1] = frame->slots[11] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compile_meta_module_79;
}
static void entry__compile_meta_module_67(void) {
  allocate_initialized_frame_gc(5, 10);
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
  // 473: %on_top_level false
  initialize_maybe_future(get__on_top_level(), get__false());
  // 474: %%objects empty_insert_order_set
  set__objects(get__empty_insert_order_set());
  // 475: %%libraries empty_insert_order_set
  set__libraries(get__empty_insert_order_set());
  // 476: %%do_link false
  set__do_link(get__false());
  // 477: %%last_modification_time undefined
  set__last_modification_time(get__undefined());
  // 478: %do_build_static_executable false
  initialize_maybe_future(get__do_build_static_executable(), get__false());
  // 479: %main_filename meta_filename
  initialize_maybe_future(get__main_filename(), frame->slots[1] /* meta_filename */);
  // 480: %main_info stat(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__compile_meta_module_68;
}
static void cont__compile_meta_module_68(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(get__main_info(), arguments->slots[0]);
  // 481: build_executable
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = func__build_executable;
  func = myself->type;
  frame->cont = cont__compile_meta_module_69;
}
static void cont__compile_meta_module_69(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 482: $orig_path current_path()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__current_path();
  func = myself->type;
  frame->cont = cont__compile_meta_module_70;
}
static void cont__compile_meta_module_70(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* orig_path */, arguments->slots[0]);
  // 483: change_directory meta_path
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* meta_path */;
  result_count = 0;
  myself = get__change_directory();
  func = myself->type;
  frame->cont = cont__compile_meta_module_71;
}
static void cont__compile_meta_module_71(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 484: std::call $out $err $success filename
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* filename */;
  result_count = 3;
  myself = get__std__call();
  func = myself->type;
  frame->cont = cont__compile_meta_module_72;
}
static void cont__compile_meta_module_72(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* out */, arguments->slots[0]);
  initialize_future(frame->slots[7] /* err */, arguments->slots[1]);
  initialize_future(frame->slots[8] /* success */, arguments->slots[2]);
  // 485: change_directory orig_path
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* orig_path */;
  result_count = 0;
  myself = get__change_directory();
  func = myself->type;
  frame->cont = cont__compile_meta_module_73;
}
static void cont__compile_meta_module_73(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 486: ... : Error err.from_utf8
  frame->slots[9] /* temp__1 */ = create_closure(entry__compile_meta_module_74, 0);
  // 486: unless success: Error err.from_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* success */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__compile_meta_module_76;
}
static void entry__compile_meta_module_74(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // err: 0
  frame->slots[0] = myself->closure.frame->slots[7]; /* err */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 486: ... err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* err */;
  result_count = 1;
  myself = get__from_utf8();
  func = myself->type;
  frame->cont = cont__compile_meta_module_75;
}
static void cont__compile_meta_module_75(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 486: ... Error err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compile_meta_module_76(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 487: ... out.to_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* out */;
  result_count = 1;
  myself = get__to_utf8();
  func = myself->type;
  frame->cont = cont__compile_meta_module_77;
}
static void cont__compile_meta_module_77(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 487: save sim_filename out.to_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* sim_filename */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__save();
  func = myself->type;
  frame->cont = cont__compile_meta_module_78;
}
static void cont__compile_meta_module_78(void) {
  myself = frame->slots[0] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__compile_meta_module_79(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 488: dec &meta_level
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* meta_level */;
  result_count = 1;
  myself = get__dec();
  func = myself->type;
  frame->cont = cont__compile_meta_module_80;
}
static void cont__compile_meta_module_80(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* meta_level */ = arguments->slots[0];
  // 489: ... meta_level > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* meta_level */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__compile_meta_module_81;
}
static void cont__compile_meta_module_81(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 489: -> meta_level > 0
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compile_meta_module(void) {
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
  // 428: ... :
  // 429:   $meta_path truncate_from(mod_filename '/' -1)
  // 430:   $filename string(mod_filename dup(".meta" meta_level))
  // 431:   $meta_filename string(filename ".sim")
  // 432:   $meta_c_filename string(mod_filename dup(".meta" meta_level) ".c")
  // 433:   $sim_filename string(mod_filename dup(".meta" meta_level-1) ".sim")
  // 434:   $meta_info stat(meta_filename)
  // 435:   $sim_info stat(sim_filename)
  // 436:   $meta_c_info stat(meta_c_filename)
  // 437:   
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__compile_meta_module_2, 0);
  // 428: do_while:
  // 429:   $meta_path truncate_from(mod_filename '/' -1)
  // 430:   $filename string(mod_filename dup(".meta" meta_level))
  // 431:   $meta_filename string(filename ".sim")
  // 432:   $meta_c_filename string(mod_filename dup(".meta" meta_level) ".c")
  // 433:   $sim_filename string(mod_filename dup(".meta" meta_level-1) ".sim")
  // 434:   $meta_info stat(meta_filename)
  // 435:   $sim_info stat(sim_filename)
  // 436:   $meta_c_info stat(meta_c_filename)
  // 437:   
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__do_while();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__build_dependencies(void) {
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
  // 502: ... : ($line)
  // 503:   unless line .has_prefix. "/// " return
  // 504:   behind &line ' '
  // 505:   trim &line
  // 506:   $command line .truncate_from. WHITESPACE
  // 507:   $argument line .behind. WHITESPACE
  // 508:   case command
  // 509:     "require":
  // 510:       if
  // 511:         argument .has_prefix. "./":
  // ...
  frame->slots[5] /* temp__1 */ = create_closure(entry__build_dependencies_2, 1);
  // 502: for_each_line c_buf: ($line)
  // 503:   unless line .has_prefix. "/// " return
  // 504:   behind &line ' '
  // 505:   trim &line
  // 506:   $command line .truncate_from. WHITESPACE
  // 507:   $argument line .behind. WHITESPACE
  // 508:   case command
  // 509:     "require":
  // 510:       if
  // 511:         argument .has_prefix. "./":
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* c_buf */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each_line();
  func = myself->type;
  frame->cont = cont__build_dependencies_41;
}
static void entry__build_dependencies_36(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // argument: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 529: ... argument .truncate_from. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* argument */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__build_dependencies_37;
}
static void cont__build_dependencies_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 529: ... !libraries(argument .truncate_from. '/')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = get__true();
  result_count = 1;
  myself = get__libraries();
  func = myself->type;
  frame->cont = cont__build_dependencies_38;
}
static void cont__build_dependencies_38(void) {
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
static void entry__build_dependencies_30(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // argument: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 527: ... argument .truncate_from. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* argument */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__build_dependencies_31;
}
static void cont__build_dependencies_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 527: ... string("sim-" argument .truncate_from. '/')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__240aeb0b5d087d14;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__build_dependencies_33;
}
static void cont__build_dependencies_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 527: !libraries(string("sim-" argument .truncate_from. '/'))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = get__true();
  result_count = 1;
  myself = get__libraries();
  func = myself->type;
  frame->cont = cont__build_dependencies_34;
}
static void cont__build_dependencies_34(void) {
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
static void entry__build_dependencies_27(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // argument: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 524: ... resolve_filename(argument)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* argument */;
  result_count = 1;
  myself = func__resolve_filename;
  func = myself->type;
  frame->cont = cont__build_dependencies_28;
}
static void cont__build_dependencies_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 524: compile_module resolve_filename(argument) argument
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[0] /* argument */;
  result_count = frame->caller_result_count;
  myself = func__compile_module;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__build_dependencies_29(void) {
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
  // 526: ... :
  // 527:   !libraries(string("sim-" argument .truncate_from. '/')) true
  frame->slots[2] /* temp__1 */ = create_closure(entry__build_dependencies_30, 0);
  // 526: if do_compile_c:
  // 527:   !libraries(string("sim-" argument .truncate_from. '/')) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* do_compile_c */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__build_dependencies_13(void) {
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
  // 513: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__build_dependencies_14;
}
static void cont__build_dependencies_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 513: $req_name range(argument 3 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* argument */;
  arguments->slots[1] = number__3;
  arguments->slots[2] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__build_dependencies_15;
}
static void cont__build_dependencies_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* req_name */, arguments->slots[0]);
  // 515: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__build_dependencies_16;
}
static void cont__build_dependencies_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 515: ... until(mod_filename '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* mod_filename */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count = 1;
  myself = get__until();
  func = myself->type;
  frame->cont = cont__build_dependencies_17;
}
static void cont__build_dependencies_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 515: string(until(mod_filename '/' -1) req_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* req_name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__build_dependencies_18;
}
static void cont__build_dependencies_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 516: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__build_dependencies_19;
}
static void cont__build_dependencies_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__6 */ = arguments->slots[0];
  // 516: ... until(mod_name '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* mod_name */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[9] /* temp__6 */;
  result_count = 1;
  myself = get__until();
  func = myself->type;
  frame->cont = cont__build_dependencies_20;
}
static void cont__build_dependencies_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__5 */ = arguments->slots[0];
  // 516: string(until(mod_name '/' -1) req_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__5 */;
  arguments->slots[1] = frame->slots[3] /* req_name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__build_dependencies_21;
}
static void cont__build_dependencies_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__4 */ = arguments->slots[0];
  // 514: compile_module
  // 515:   string(until(mod_filename '/' -1) req_name)
  // 516:   string(until(mod_name '/' -1) req_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = func__compile_module;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__build_dependencies_11(void) {
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
  // 512: ... mode == EXE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__mode();
  arguments->slots[1] = unique__EXE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__build_dependencies_12;
}
static void cont__build_dependencies_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 512: ... :
  // 513:   $req_name range(argument 3 -1)
  // 514:   compile_module
  // 515:     string(until(mod_filename '/' -1) req_name)
  // 516:     string(until(mod_name '/' -1) req_name)
  frame->slots[4] /* temp__2 */ = create_closure(entry__build_dependencies_13, 0);
  // 512: if mode == EXE:
  // 513:   $req_name range(argument 3 -1)
  // 514:   compile_module
  // 515:     string(until(mod_filename '/' -1) req_name)
  // 516:     string(until(mod_name '/' -1) req_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__build_dependencies_22(void) {
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
  arguments->slots[1] = func__build_dependencies_23;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__build_dependencies_26;
}
static void entry__build_dependencies_23(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_build_codeblocks_project;
  arguments->slots[1] = func__build_dependencies_24;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__build_dependencies_25;
}
static void entry__build_dependencies_24(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 522: do_list_dependencies
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._do_list_dependencies;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__build_dependencies_25(void) {
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
static void cont__build_dependencies_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 523: :
  // 524:   compile_module resolve_filename(argument) argument
  frame->slots[3] /* temp__2 */ = create_closure(entry__build_dependencies_27, 0);
  // 525: :
  // 526:   if do_compile_c:
  // 527:     !libraries(string("sim-" argument .truncate_from. '/')) true
  frame->slots[4] /* temp__3 */ = create_closure(entry__build_dependencies_29, 0);
  // 518: if
  // 519:   ||
  // 520:     do_build_static_executable
  // 521:     do_build_codeblocks_project
  // 522:     do_list_dependencies
  // 523:   :
  // 524:     compile_module resolve_filename(argument) argument
  // 525:   :
  // 526:     if do_compile_c:
  // 527:       !libraries(string("sim-" argument .truncate_from. '/')) true
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
static void entry__build_dependencies_9(void) {
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
  // 511: argument .has_prefix. "./"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* argument */;
  arguments->slots[1] = string__2d7981f4e6782bea;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__build_dependencies_10;
}
static void cont__build_dependencies_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 511: ... :
  // 512:   if mode == EXE:
  // 513:     $req_name range(argument 3 -1)
  // 514:     compile_module
  // 515:       string(until(mod_filename '/' -1) req_name)
  // 516:       string(until(mod_name '/' -1) req_name)
  frame->slots[5] /* temp__2 */ = create_closure(entry__build_dependencies_11, 0);
  // 517: :
  // 518:   if
  // 519:     ||
  // 520:       do_build_static_executable
  // 521:       do_build_codeblocks_project
  // 522:       do_list_dependencies
  // 523:     :
  // 524:       compile_module resolve_filename(argument) argument
  // 525:     :
  // 526:       if do_compile_c:
  // ...
  frame->slots[6] /* temp__3 */ = create_closure(entry__build_dependencies_22, 0);
  // 510: if
  // 511:   argument .has_prefix. "./":
  // 512:     if mode == EXE:
  // 513:       $req_name range(argument 3 -1)
  // 514:       compile_module
  // 515:         string(until(mod_filename '/' -1) req_name)
  // 516:         string(until(mod_name '/' -1) req_name)
  // 517:   :
  // 518:     if
  // 519:       ||
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
static void entry__build_dependencies_35(void) {
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
  // 529: ... : !libraries(argument .truncate_from. '/') true
  frame->slots[2] /* temp__1 */ = create_closure(entry__build_dependencies_36, 0);
  // 529: if do_compile_c: !libraries(argument .truncate_from. '/') true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* do_compile_c */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__build_dependencies_2(void) {
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
  // 503: ... line .has_prefix. "/// "
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  arguments->slots[1] = string__9c0afa8b5f187d19;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__build_dependencies_3;
}
static void cont__build_dependencies_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 503: unless line .has_prefix. "/// " return
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* return */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__build_dependencies_4;
}
static void cont__build_dependencies_4(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 504: behind &line ' '
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  arguments->slots[1] = character__32;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__build_dependencies_5;
}
static void cont__build_dependencies_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* line */ = arguments->slots[0];
  // 505: trim &line
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__build_dependencies_6;
}
static void cont__build_dependencies_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* line */ = arguments->slots[0];
  // 506: $command line .truncate_from. WHITESPACE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  arguments->slots[1] = var._WHITESPACE;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__build_dependencies_7;
}
static void cont__build_dependencies_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* command */, arguments->slots[0]);
  // 507: $argument line .behind. WHITESPACE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  arguments->slots[1] = var._WHITESPACE;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__build_dependencies_8;
}
static void cont__build_dependencies_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* argument */, arguments->slots[0]);
  // 509: ... :
  // 510:   if
  // 511:     argument .has_prefix. "./":
  // 512:       if mode == EXE:
  // 513:         $req_name range(argument 3 -1)
  // 514:         compile_module
  // 515:           string(until(mod_filename '/' -1) req_name)
  // 516:           string(until(mod_name '/' -1) req_name)
  // 517:     :
  // 518:       if
  // ...
  frame->slots[7] /* temp__1 */ = create_closure(entry__build_dependencies_9, 0);
  // 528: ... :
  // 529:   if do_compile_c: !libraries(argument .truncate_from. '/') true
  frame->slots[8] /* temp__2 */ = create_closure(entry__build_dependencies_35, 0);
  // 508: case command
  // 509:   "require":
  // 510:     if
  // 511:       argument .has_prefix. "./":
  // 512:         if mode == EXE:
  // 513:           $req_name range(argument 3 -1)
  // 514:           compile_module
  // 515:             string(until(mod_filename '/' -1) req_name)
  // 516:             string(until(mod_name '/' -1) req_name)
  // 517:       :
  // ...
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* command */;
  arguments->slots[1] = string__984c0f90152bd09f;
  arguments->slots[2] = frame->slots[7] /* temp__1 */;
  arguments->slots[3] = string__1a0aeb0b5d107d52;
  arguments->slots[4] = frame->slots[8] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__build_dependencies_41(void) {
  myself = frame->slots[4] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__compile_module(void) {
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
  // 540: ... :
  // 541:   (
  // 542:     submodule_names # no paths; no extensions
  // 543:     do_compile_c = true
  // 544:     suffix = "" # a hyphen followed by the platform name
  // 545:   )
  // 546:   $$modification_time undefined
  // 547:   $$sim_filenames empty_list
  // 548:   for_each submodule_names: (submodule_name)
  // 549:     $meta_level meta_levels(submodule_name)
  // ...
  frame->slots[6] /* temp__1 */ = create_closure(entry__compile_module_2, -1);
  // 540: $compile_submodule:
  // 541:   (
  // 542:     submodule_names # no paths; no extensions
  // 543:     do_compile_c = true
  // 544:     suffix = "" # a hyphen followed by the platform name
  // 545:   )
  // 546:   $$modification_time undefined
  // 547:   $$sim_filenames empty_list
  // 548:   for_each submodule_names: (submodule_name)
  // 549:     $meta_level meta_levels(submodule_name)
  // ...
  initialize_future(frame->slots[3] /* compile_submodule */, frame->slots[6] /* temp__1 */);
  // 599: lookup $mod_info mod_filename mod_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = frame->slots[1] /* mod_name */;
  result_count = 1;
  myself = func__lookup;
  func = myself->type;
  frame->cont = cont__compile_module_78;
}
static void entry__compile_module_2(void) {
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
  // 546: $$modification_time undefined
  ((CELL *)frame->slots[6])->contents /* modification_time */ = get__undefined();
  // 547: $$sim_filenames empty_list
  ((CELL *)frame->slots[7])->contents /* sim_filenames */ = get__empty_list();
  // 548: ... : (submodule_name)
  // 549:   $meta_level meta_levels(submodule_name)
  // 550:   $submodule_filename string(until(mod_filename '/' -1) submodule_name)
  // 551:   if meta_level > 0 && not(do_omit_meta):
  // 552:     compile_meta_module submodule_filename submodule_name meta_level
  // 553:   $sim_filename string(submodule_filename ".sim")
  // 554:   push &sim_filenames sim_filename
  // 555:   $sim_info stat(sim_filename)
  // 556:   unless sim_info.is_defined:
  // 557:     Error "
  // ...
  frame->slots[11] /* temp__1 */ = create_closure(entry__compile_module_3, 1);
  // 548: for_each submodule_names: (submodule_name)
  // 549:   $meta_level meta_levels(submodule_name)
  // 550:   $submodule_filename string(until(mod_filename '/' -1) submodule_name)
  // 551:   if meta_level > 0 && not(do_omit_meta):
  // 552:     compile_meta_module submodule_filename submodule_name meta_level
  // 553:   $sim_filename string(submodule_filename ".sim")
  // 554:   push &sim_filenames sim_filename
  // 555:   $sim_info stat(sim_filename)
  // 556:   unless sim_info.is_defined:
  // 557:     Error "
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* submodule_names */;
  arguments->slots[1] = frame->slots[11] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compile_module_29;
}
static void entry__compile_module_27(void) {
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
  // 564: !modification_time modification_time_of(sim_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* sim_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__compile_module_28;
}
static void cont__compile_module_28(void) {
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
static void entry__compile_module_3(void) {
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
  // 549: $meta_level meta_levels(submodule_name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* submodule_name */;
  result_count = 1;
  myself = var._meta_levels;
  func = myself->type;
  frame->cont = cont__compile_module_4;
}
static void cont__compile_module_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* meta_level */, arguments->slots[0]);
  // 550: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__compile_module_5;
}
static void cont__compile_module_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__2 */ = arguments->slots[0];
  // 550: ... until(mod_filename '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* mod_filename */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[9] /* temp__2 */;
  result_count = 1;
  myself = get__until();
  func = myself->type;
  frame->cont = cont__compile_module_6;
}
static void cont__compile_module_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 550: $submodule_filename string(until(mod_filename '/' -1) submodule_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = frame->slots[0] /* submodule_name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__compile_module_7;
}
static void cont__compile_module_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* submodule_filename */, arguments->slots[0]);
  // 551: ... meta_level > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = frame->slots[4] /* meta_level */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__compile_module_8;
}
static void cont__compile_module_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__2 */ = arguments->slots[0];
  // 551: ... meta_level > 0 && not(do_omit_meta)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__2 */;
  arguments->slots[1] = func__compile_module_9;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__compile_module_11;
}
static void entry__compile_module_9(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 551: ... not(do_omit_meta)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._do_omit_meta;
  result_count = 1;
  myself = get__not();
  func = myself->type;
  frame->cont = cont__compile_module_10;
}
static void cont__compile_module_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 551: ... not(do_omit_meta)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compile_module_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 551: ... :
  // 552:   compile_meta_module submodule_filename submodule_name meta_level
  frame->slots[10] /* temp__3 */ = create_closure(entry__compile_module_12, 0);
  // 551: if meta_level > 0 && not(do_omit_meta):
  // 552:   compile_meta_module submodule_filename submodule_name meta_level
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compile_module_13;
}
static void entry__compile_module_12(void) {
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
  // 552: compile_meta_module submodule_filename submodule_name meta_level
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* submodule_filename */;
  arguments->slots[1] = frame->slots[1] /* submodule_name */;
  arguments->slots[2] = frame->slots[2] /* meta_level */;
  result_count = frame->caller_result_count;
  myself = func__compile_meta_module;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compile_module_13(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 553: $sim_filename string(submodule_filename ".sim")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* submodule_filename */;
  arguments->slots[1] = string__9e0aed8b5d287d54;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__compile_module_14;
}
static void cont__compile_module_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* sim_filename */, arguments->slots[0]);
  // 554: push &sim_filenames sim_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* sim_filenames */;
  arguments->slots[1] = frame->slots[6] /* sim_filename */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compile_module_15;
}
static void cont__compile_module_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* sim_filenames */ = arguments->slots[0];
  // 555: $sim_info stat(sim_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* sim_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__compile_module_16;
}
static void cont__compile_module_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[7] /* sim_info */, arguments->slots[0]);
  // 556: ... sim_info.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* sim_info */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compile_module_17;
}
static void cont__compile_module_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 556: ... :
  // 557:   Error "
  // 558:     Failed to open file "@(sim_filename)@quot;!@
  frame->slots[9] /* temp__2 */ = create_closure(entry__compile_module_18, 0);
  // 556: unless sim_info.is_defined:
  // 557:   Error "
  // 558:     Failed to open file "@(sim_filename)@quot;!@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__compile_module_21;
}
static void entry__compile_module_18(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // sim_filename: 0
  frame->slots[0] = myself->closure.frame->slots[6]; /* sim_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 557: ... "
  // 558:   Failed to open file "@(sim_filename)@quot;!@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__52b1d7d50d05f753;
  arguments->slots[1] = frame->slots[0] /* sim_filename */;
  arguments->slots[2] = string__2d7981f4e6182be4;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compile_module_20;
}
static void cont__compile_module_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 557: Error "
  // 558:   Failed to open file "@(sim_filename)@quot;!@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compile_module_21(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 561: modification_time.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* modification_time */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__compile_module_22;
}
static void cont__compile_module_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__2 */ = arguments->slots[0];
  // 562: modification_time_of(sim_info) > modification_time
  frame->slots[10] /* temp__3 */ = create_closure(entry__compile_module_23, 0);
  // 560: ||
  // 561:   modification_time.is_undefined
  // 562:   modification_time_of(sim_info) > modification_time
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__2 */;
  arguments->slots[1] = frame->slots[10] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__compile_module_26;
}
static void entry__compile_module_23(void) {
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
  // 562: modification_time_of(sim_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* sim_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__compile_module_24;
}
static void cont__compile_module_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 562: modification_time_of(sim_info) > modification_time
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* modification_time */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__compile_module_25;
}
static void cont__compile_module_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 562: modification_time_of(sim_info) > modification_time
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compile_module_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 563: :
  // 564:   !modification_time modification_time_of(sim_info)
  frame->slots[11] /* temp__4 */ = create_closure(entry__compile_module_27, 0);
  // 559: if
  // 560:   ||
  // 561:     modification_time.is_undefined
  // 562:     modification_time_of(sim_info) > modification_time
  // 563:   :
  // 564:     !modification_time modification_time_of(sim_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = frame->slots[11] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compile_module_29(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 565: $c_filename string(mod_filename suffix ".c")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* mod_filename */;
  arguments->slots[1] = frame->slots[2] /* suffix */;
  arguments->slots[2] = string__2d7981f4e6782ba6;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__compile_module_30;
}
static void cont__compile_module_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[8] /* c_filename */, arguments->slots[0]);
  // 566: $c_info stat(c_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* c_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__compile_module_31;
}
static void cont__compile_module_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[9] /* c_info */, arguments->slots[0]);
  // 567: ... : !c_sources(c_filename) true
  frame->slots[11] /* temp__1 */ = create_closure(entry__compile_module_32, 0);
  // 567: if do_compile_c: !c_sources(c_filename) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* do_compile_c */;
  arguments->slots[1] = frame->slots[11] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compile_module_34;
}
static void entry__compile_module_32(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // c_filename: 0
  frame->slots[0] = myself->closure.frame->slots[8]; /* c_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 567: ... !c_sources(c_filename)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_filename */;
  arguments->slots[1] = get__true();
  result_count = 1;
  myself = var._c_sources;
  func = myself->type;
  frame->cont = cont__compile_module_33;
}
static void cont__compile_module_33(void) {
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
static void cont__compile_module_34(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 568: $$c_buf undefined
  ((CELL *)frame->slots[10])->contents /* c_buf */ = get__undefined();
  frame->slots[12] /* temp__2 */ = create_closure(entry__compile_module_35, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_rebuild;
  arguments->slots[1] = frame->slots[12] /* temp__2 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__compile_module_41;
}
static void entry__compile_module_35(void) {
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
  // 572: c_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__compile_module_36;
}
static void cont__compile_module_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 573: modification_time > modification_time_of(c_info)
  frame->slots[4] /* temp__3 */ = create_closure(entry__compile_module_37, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__compile_module_40;
}
static void entry__compile_module_37(void) {
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
  // 573: ... modification_time_of(c_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__compile_module_38;
}
static void cont__compile_module_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 573: modification_time > modification_time_of(c_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* modification_time */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__compile_module_39;
}
static void cont__compile_module_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 573: modification_time > modification_time_of(c_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compile_module_40(void) {
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
static void cont__compile_module_41(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 574: :
  // 575:   %compiler::module_name replace_all(mod_name '/' = "__" '.' = "__")
  // 576:   if verbose: ewriteln "build module " module_name suffix
  // 577:   collect_output $c_source: sim2c sim_filenames
  // 578:   collect_output !c_buf: create_imports c_source
  // 579:   save c_filename c_buf.to_utf8
  // 580:   if do_compile_c: compile_c c_filename o_filename
  frame->slots[13] /* temp__3 */ = create_closure(entry__compile_module_42, 0);
  // 581: :
  // 582:   load !c_buf c_filename
  // 583:   $o_info stat(o_filename)
  // 584:   if
  // 585:     ||
  // 586:       o_info.is_undefined
  // 587:       modification_time_of(c_info) > modification_time_of(o_info)
  // 588:     :
  // 589:       if do_compile_c: compile_c c_filename o_filename
  // 590:     :
  // ...
  frame->slots[14] /* temp__4 */ = create_closure(entry__compile_module_58, 0);
  // 569: if
  // 570:   ||
  // 571:     do_rebuild
  // 572:     c_info.is_undefined
  // 573:     modification_time > modification_time_of(c_info)
  // 574:   :
  // 575:     %compiler::module_name replace_all(mod_name '/' = "__" '.' = "__")
  // 576:     if verbose: ewriteln "build module " module_name suffix
  // 577:     collect_output $c_source: sim2c sim_filenames
  // 578:     collect_output !c_buf: create_imports c_source
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  arguments->slots[1] = frame->slots[13] /* temp__3 */;
  arguments->slots[2] = frame->slots[14] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compile_module_77;
}
static void entry__compile_module_75(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // o_info: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* o_info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 596: !last_modification_time modification_time_of(o_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* o_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__compile_module_76;
}
static void cont__compile_module_76(void) {
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
static void entry__compile_module_68(void) {
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
  // 589: ... compile_c c_filename o_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_filename */;
  arguments->slots[1] = frame->slots[1] /* o_filename */;
  result_count = frame->caller_result_count;
  myself = func__compile_c;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compile_module_67(void) {
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
  // 589: ... : compile_c c_filename o_filename
  frame->slots[3] /* temp__1 */ = create_closure(entry__compile_module_68, 0);
  // 589: if do_compile_c: compile_c c_filename o_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* do_compile_c */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compile_module_69(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // o_info: 0
  frame->slots[0] = myself->closure.frame->slots[5]; /* o_info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 593: last_modification_time.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__last_modification_time();
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__compile_module_70;
}
static void cont__compile_module_70(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 594: modification_time_of(o_info) > last_modification_time
  frame->slots[3] /* temp__3 */ = create_closure(entry__compile_module_71, 0);
  // 592: ||
  // 593:   last_modification_time.is_undefined
  // 594:   modification_time_of(o_info) > last_modification_time
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__compile_module_74;
}
static void entry__compile_module_71(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // o_info: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* o_info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 594: modification_time_of(o_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* o_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__compile_module_72;
}
static void cont__compile_module_72(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 594: modification_time_of(o_info) > last_modification_time
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__last_modification_time();
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__compile_module_73;
}
static void cont__compile_module_73(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 594: modification_time_of(o_info) > last_modification_time
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compile_module_74(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 595: :
  // 596:   !last_modification_time modification_time_of(o_info)
  frame->slots[4] /* temp__4 */ = create_closure(entry__compile_module_75, 0);
  // 591: if
  // 592:   ||
  // 593:     last_modification_time.is_undefined
  // 594:     modification_time_of(o_info) > last_modification_time
  // 595:   :
  // 596:     !last_modification_time modification_time_of(o_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compile_module_42(void) {
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
  define__compiler__module_name(create_future());
  frame->slots[8] /* c_source */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 575: ... '/' = "__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = string__2d7981f4e5f02b9a;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__compile_module_44;
}
static void cont__compile_module_44(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 575: ... '.' = "__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__46;
  arguments->slots[1] = string__2d7981f4e5f02b9a;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__compile_module_45;
}
static void cont__compile_module_45(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__2 */ = arguments->slots[0];
  // 575: %compiler::module_name replace_all(mod_name '/' = "__" '.' = "__")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* mod_name */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  arguments->slots[2] = frame->slots[10] /* temp__2 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__compile_module_46;
}
static void cont__compile_module_46(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(get__compiler__module_name(), arguments->slots[0]);
  // 576: ... : ewriteln "build module " module_name suffix
  frame->slots[9] /* temp__1 */ = create_closure(entry__compile_module_47, 0);
  // 576: if verbose: ewriteln "build module " module_name suffix
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compile_module_49;
}
static void entry__compile_module_47(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // suffix: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* suffix */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 576: ... ewriteln "build module " module_name suffix
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__a85eb307b04e1ec9;
  arguments->slots[1] = get__module_name();
  arguments->slots[2] = frame->slots[0] /* suffix */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compile_module_49(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 577: ... : sim2c sim_filenames
  frame->slots[9] /* temp__1 */ = create_closure(entry__compile_module_50, 0);
  // 577: collect_output $c_source: sim2c sim_filenames
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__compile_module_51;
}
static void entry__compile_module_50(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // sim_filenames: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* sim_filenames */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 577: ... sim2c sim_filenames
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* sim_filenames */;
  result_count = frame->caller_result_count;
  myself = get__sim2c();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compile_module_51(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[8] /* c_source */, arguments->slots[0]);
  // 578: ... : create_imports c_source
  frame->slots[9] /* temp__1 */ = create_closure(entry__compile_module_52, 0);
  // 578: collect_output !c_buf: create_imports c_source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__compile_module_53;
}
static void entry__compile_module_52(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // c_source: 0
  frame->slots[0] = myself->closure.frame->slots[8]; /* c_source */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 578: ... create_imports c_source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_source */;
  result_count = frame->caller_result_count;
  myself = func__create_imports;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compile_module_53(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* c_buf */ = arguments->slots[0];
  // 579: ... c_buf.to_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* c_buf */;
  result_count = 1;
  myself = get__to_utf8();
  func = myself->type;
  frame->cont = cont__compile_module_54;
}
static void cont__compile_module_54(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 579: save c_filename c_buf.to_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* c_filename */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 0;
  myself = get__save();
  func = myself->type;
  frame->cont = cont__compile_module_55;
}
static void cont__compile_module_55(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 580: ... : compile_c c_filename o_filename
  frame->slots[9] /* temp__1 */ = create_closure(entry__compile_module_56, 0);
  // 580: if do_compile_c: compile_c c_filename o_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* do_compile_c */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compile_module_57;
}
static void entry__compile_module_56(void) {
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
  // 580: ... compile_c c_filename o_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_filename */;
  arguments->slots[1] = frame->slots[1] /* o_filename */;
  result_count = frame->caller_result_count;
  myself = func__compile_c;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compile_module_57(void) {
  myself = frame->slots[0] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__compile_module_58(void) {
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
  // 582: load !c_buf c_filename
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* c_filename */;
  result_count = 1;
  myself = get__load();
  func = myself->type;
  frame->cont = cont__compile_module_59;
}
static void cont__compile_module_59(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* c_buf */ = arguments->slots[0];
  // 583: $o_info stat(o_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* o_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__compile_module_60;
}
static void cont__compile_module_60(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* o_info */, arguments->slots[0]);
  // 586: o_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* o_info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__compile_module_61;
}
static void cont__compile_module_61(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 587: modification_time_of(c_info) > modification_time_of(o_info)
  frame->slots[8] /* temp__3 */ = create_closure(entry__compile_module_62, 0);
  // 585: ||
  // 586:   o_info.is_undefined
  // 587:   modification_time_of(c_info) > modification_time_of(o_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  arguments->slots[1] = frame->slots[8] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__compile_module_66;
}
static void entry__compile_module_62(void) {
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
  // 587: ... modification_time_of(o_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* o_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__compile_module_63;
}
static void cont__compile_module_63(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 587: modification_time_of(c_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* c_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__compile_module_64;
}
static void cont__compile_module_64(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 587: modification_time_of(c_info) > modification_time_of(o_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__compile_module_65;
}
static void cont__compile_module_65(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 587: modification_time_of(c_info) > modification_time_of(o_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compile_module_66(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 588: :
  // 589:   if do_compile_c: compile_c c_filename o_filename
  frame->slots[9] /* temp__4 */ = create_closure(entry__compile_module_67, 0);
  // 590: :
  // 591:   if
  // 592:     ||
  // 593:       last_modification_time.is_undefined
  // 594:       modification_time_of(o_info) > last_modification_time
  // 595:     :
  // 596:       !last_modification_time modification_time_of(o_info)
  frame->slots[10] /* temp__5 */ = create_closure(entry__compile_module_69, 0);
  // 584: if
  // 585:   ||
  // 586:     o_info.is_undefined
  // 587:     modification_time_of(c_info) > modification_time_of(o_info)
  // 588:   :
  // 589:     if do_compile_c: compile_c c_filename o_filename
  // 590:   :
  // 591:     if
  // 592:       ||
  // 593:         last_modification_time.is_undefined
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
static void cont__compile_module_77(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 597: build_dependencies mod_filename mod_name c_buf do_compile_c
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* mod_filename */;
  arguments->slots[1] = frame->slots[4] /* mod_name */;
  arguments->slots[2] = ((CELL *)frame->slots[10])->contents /* c_buf */;
  arguments->slots[3] = frame->slots[1] /* do_compile_c */;
  result_count = frame->caller_result_count;
  myself = func__build_dependencies;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compile_module_78(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* mod_info */, arguments->slots[0]);
  // 600: ... mod_info.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* mod_info */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compile_module_79;
}
static void cont__compile_module_79(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 600: ... :
  // 601:   Error "
  // 602:     No source file(s) for module "@(mod_name)" found!@
  frame->slots[7] /* temp__2 */ = create_closure(entry__compile_module_80, 0);
  // 600: unless mod_info.is_defined:
  // 601:   Error "
  // 602:     No source file(s) for module "@(mod_name)" found!@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__compile_module_84;
}
static void entry__compile_module_80(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // mod_name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* mod_name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 601: ... "
  // 602:   No source file(s) for module "@(mod_name)" found!@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__1c48d17af91ab023;
  arguments->slots[1] = frame->slots[0] /* mod_name */;
  arguments->slots[2] = string__4594ae5504f56841;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compile_module_83;
}
static void cont__compile_module_83(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 601: Error "
  // 602:   No source file(s) for module "@(mod_name)" found!@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compile_module_84(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 603: $o_filename append(mod_filename ".o")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = string__2d7981f4e6782baa;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__compile_module_86;
}
static void cont__compile_module_86(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* o_filename */, arguments->slots[0]);
  // 604: ... objects(o_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* o_filename */;
  result_count = 1;
  myself = get__objects();
  func = myself->type;
  frame->cont = cont__compile_module_87;
}
static void cont__compile_module_87(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 604: if objects(o_filename) return
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* return */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compile_module_88;
}
static void cont__compile_module_88(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 605: !objects(o_filename)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* o_filename */;
  arguments->slots[1] = get__true();
  result_count = 1;
  myself = get__objects();
  func = myself->type;
  frame->cont = cont__compile_module_89;
}
static void cont__compile_module_89(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__objects(arguments->slots[0]);
  // 607: mod_info.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* mod_info */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__compile_module_90;
}
static void cont__compile_module_90(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 607: ... :
  // 608:   if do_list_dependencies: push &dependencies string(mod_filename ".c")
  // 609:   compile_submodule list(truncate_until(mod_name '/' -1))
  frame->slots[7] /* temp__2 */ = create_closure(entry__compile_module_91, 0);
  // 610: :
  // 611:   do:
  // 612:     $$best_platform undefined
  // 613:     $$best_priority 999
  // 614:     for_each mod_info: (platform _filenames)
  // 615:       $priority platform_priority(platform)
  // 616:       if priority.is_defined && priority < best_priority:
  // 617:         !best_platform platform
  // 618:         !best_priority priority
  // 619:     for_each mod_info: (platform filenames)
  // ...
  frame->slots[8] /* temp__3 */ = create_closure(entry__compile_module_99, 0);
  // 606: if
  // 607:   mod_info.is_empty:
  // 608:     if do_list_dependencies: push &dependencies string(mod_filename ".c")
  // 609:     compile_submodule list(truncate_until(mod_name '/' -1))
  // 610:   :
  // 611:     do:
  // 612:       $$best_platform undefined
  // 613:       $$best_priority 999
  // 614:       for_each mod_info: (platform _filenames)
  // 615:         $priority platform_priority(platform)
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  arguments->slots[2] = frame->slots[8] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compile_module_140;
}
static void entry__compile_module_130(void) {
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
  // 639: $$dependency string(mod_filename "-" platform ".c")
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* mod_filename */;
  arguments->slots[1] = string__578a5af303e9ccc;
  arguments->slots[2] = frame->slots[0] /* platform */;
  arguments->slots[3] = string__2d7981f4e6782ba6;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__compile_module_131;
}
static void cont__compile_module_131(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* dependency */ = arguments->slots[0];
  // 640: $platforms used_by(platform)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* platform */;
  result_count = 1;
  myself = ((CELL *)frame->slots[3])->contents /* used_by */;
  func = myself->type;
  frame->cont = cont__compile_module_132;
}
static void cont__compile_module_132(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* platforms */, arguments->slots[0]);
  // 641: ... platforms.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* platforms */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compile_module_133;
}
static void cont__compile_module_133(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 641: ... :
  // 642:   for_each platforms: (plat) write_to &dependency " #" plat
  frame->slots[7] /* temp__2 */ = create_closure(entry__compile_module_134, 0);
  // 641: if platforms.is_defined:
  // 642:   for_each platforms: (plat) write_to &dependency " #" plat
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compile_module_138;
}
static void entry__compile_module_135(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // plat: 0
  // dependency: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* dependency */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 642: ... write_to &dependency " #" plat
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* dependency */;
  arguments->slots[1] = string__2d7981f4e6082be6;
  arguments->slots[2] = frame->slots[0] /* plat */;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__compile_module_137;
}
static void cont__compile_module_137(void) {
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
static void entry__compile_module_134(void) {
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
  // 642: ... : (plat) write_to &dependency " #" plat
  frame->slots[2] /* temp__1 */ = create_closure(entry__compile_module_135, 1);
  // 642: for_each platforms: (plat) write_to &dependency " #" plat
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* platforms */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compile_module_138(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 643: push &dependencies dependency
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._dependencies;
  arguments->slots[1] = ((CELL *)frame->slots[4])->contents /* dependency */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compile_module_139;
}
static void cont__compile_module_139(void) {
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
static void entry__compile_module_113(void) {
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
  // 625: $$used_by empty_table
  ((CELL *)frame->slots[2])->contents /* used_by */ = get__empty_table();
  // 626: ... : (supported_platform _parent_platform)
  // 627:   $$best_platform undefined
  // 628:   $$best_priority 999
  // 629:   for_each mod_info: (platform _filenames)
  // 630:     $priority platform_specific_priority(supported_platform platform)
  // 631:     if priority.is_defined && priority < best_priority:
  // 632:       !best_platform platform
  // 633:       !best_priority priority
  // 634:   if best_platform.is_defined:
  // 635:     $$ub default_value(used_by(best_platform) empty_list)
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__compile_module_114, 2);
  // 626: for_each supported_platforms: (supported_platform _parent_platform)
  // 627:   $$best_platform undefined
  // 628:   $$best_priority 999
  // 629:   for_each mod_info: (platform _filenames)
  // 630:     $priority platform_specific_priority(supported_platform platform)
  // 631:     if priority.is_defined && priority < best_priority:
  // 632:       !best_platform platform
  // 633:       !best_priority priority
  // 634:   if best_platform.is_defined:
  // 635:     $$ub default_value(used_by(best_platform) empty_list)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._supported_platforms;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compile_module_129;
}
static void entry__compile_module_124(void) {
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
  // 635: ... used_by(best_platform)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* best_platform */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* used_by */;
  func = myself->type;
  frame->cont = cont__compile_module_125;
}
static void cont__compile_module_125(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 635: $$ub default_value(used_by(best_platform) empty_list)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = get__empty_list();
  result_count = 1;
  myself = get__default_value();
  func = myself->type;
  frame->cont = cont__compile_module_126;
}
static void cont__compile_module_126(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* ub */ = arguments->slots[0];
  // 636: push &ub supported_platform
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* ub */;
  arguments->slots[1] = frame->slots[2] /* supported_platform */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compile_module_127;
}
static void cont__compile_module_127(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* ub */ = arguments->slots[0];
  // 637: !used_by(best_platform)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* best_platform */;
  arguments->slots[1] = ((CELL *)frame->slots[3])->contents /* ub */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* used_by */;
  func = myself->type;
  frame->cont = cont__compile_module_128;
}
static void cont__compile_module_128(void) {
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
static void entry__compile_module_114(void) {
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
  // 627: $$best_platform undefined
  ((CELL *)frame->slots[4])->contents /* best_platform */ = get__undefined();
  // 628: $$best_priority 999
  ((CELL *)frame->slots[5])->contents /* best_priority */ = number__999;
  // 629: ... : (platform _filenames)
  // 630:   $priority platform_specific_priority(supported_platform platform)
  // 631:   if priority.is_defined && priority < best_priority:
  // 632:     !best_platform platform
  // 633:     !best_priority priority
  frame->slots[6] /* temp__1 */ = create_closure(entry__compile_module_115, 2);
  // 629: for_each mod_info: (platform _filenames)
  // 630:   $priority platform_specific_priority(supported_platform platform)
  // 631:   if priority.is_defined && priority < best_priority:
  // 632:     !best_platform platform
  // 633:     !best_priority priority
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* mod_info */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compile_module_122;
}
static void entry__compile_module_121(void) {
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
  // 632: !best_platform platform
  ((CELL *)frame->slots[0])->contents /* best_platform */ = frame->slots[1] /* platform */;
  // 633: !best_priority priority
  ((CELL *)frame->slots[2])->contents /* best_priority */ = frame->slots[3] /* priority */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compile_module_115(void) {
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
  // 630: $priority platform_specific_priority(supported_platform platform)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* supported_platform */;
  arguments->slots[1] = frame->slots[0] /* platform */;
  result_count = 1;
  myself = var._platform_specific_priority;
  func = myself->type;
  frame->cont = cont__compile_module_116;
}
static void cont__compile_module_116(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* priority */, arguments->slots[0]);
  // 631: ... priority.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* priority */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compile_module_117;
}
static void cont__compile_module_117(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 631: ... priority < best_priority
  frame->slots[8] /* temp__3 */ = create_closure(entry__compile_module_118, 0);
  // 631: ... priority.is_defined && priority < best_priority
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  arguments->slots[1] = frame->slots[8] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__compile_module_120;
}
static void entry__compile_module_118(void) {
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
  // 631: ... priority < best_priority
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* priority */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* best_priority */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__compile_module_119;
}
static void cont__compile_module_119(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 631: ... priority < best_priority
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compile_module_120(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 631: ... :
  // 632:   !best_platform platform
  // 633:   !best_priority priority
  frame->slots[9] /* temp__4 */ = create_closure(entry__compile_module_121, 0);
  // 631: if priority.is_defined && priority < best_priority:
  // 632:   !best_platform platform
  // 633:   !best_priority priority
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compile_module_122(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 634: ... best_platform.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* best_platform */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compile_module_123;
}
static void cont__compile_module_123(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 634: ... :
  // 635:   $$ub default_value(used_by(best_platform) empty_list)
  // 636:   push &ub supported_platform
  // 637:   !used_by(best_platform) ub
  frame->slots[7] /* temp__2 */ = create_closure(entry__compile_module_124, 0);
  // 634: if best_platform.is_defined:
  // 635:   $$ub default_value(used_by(best_platform) empty_list)
  // 636:   push &ub supported_platform
  // 637:   !used_by(best_platform) ub
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compile_module_129(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 638: ... : (platform _filenames)
  // 639:   $$dependency string(mod_filename "-" platform ".c")
  // 640:   $platforms used_by(platform)
  // 641:   if platforms.is_defined:
  // 642:     for_each platforms: (plat) write_to &dependency " #" plat
  // 643:   push &dependencies dependency
  frame->slots[3] /* temp__1 */ = create_closure(entry__compile_module_130, 2);
  // 638: for_each mod_info: (platform _filenames)
  // 639:   $$dependency string(mod_filename "-" platform ".c")
  // 640:   $platforms used_by(platform)
  // 641:   if platforms.is_defined:
  // 642:     for_each platforms: (plat) write_to &dependency " #" plat
  // 643:   push &dependencies dependency
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_info */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compile_module_91(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // mod_filename: 0
  // compile_submodule: 1
  // mod_name: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* mod_filename */
  frame->slots[1] = myself->closure.frame->slots[3]; /* compile_submodule */
  frame->slots[2] = myself->closure.frame->slots[1]; /* mod_name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 608: ... : push &dependencies string(mod_filename ".c")
  frame->slots[3] /* temp__1 */ = create_closure(entry__compile_module_92, 0);
  // 608: if do_list_dependencies: push &dependencies string(mod_filename ".c")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_list_dependencies;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compile_module_95;
}
static void entry__compile_module_92(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // mod_filename: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* mod_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 608: ... string(mod_filename ".c")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = string__2d7981f4e6782ba6;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__compile_module_93;
}
static void cont__compile_module_93(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 608: ... push &dependencies string(mod_filename ".c")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._dependencies;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compile_module_94;
}
static void cont__compile_module_94(void) {
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
static void cont__compile_module_95(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 609: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__compile_module_96;
}
static void cont__compile_module_96(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 609: ... truncate_until(mod_name '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* mod_name */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__compile_module_97;
}
static void cont__compile_module_97(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 609: ... list(truncate_until(mod_name '/' -1))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__compile_module_98;
}
static void cont__compile_module_98(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 609: compile_submodule list(truncate_until(mod_name '/' -1))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* compile_submodule */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compile_module_99(void) {
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
  // 611: ... :
  // 612:   $$best_platform undefined
  // 613:   $$best_priority 999
  // 614:   for_each mod_info: (platform _filenames)
  // 615:     $priority platform_priority(platform)
  // 616:     if priority.is_defined && priority < best_priority:
  // 617:       !best_platform platform
  // 618:       !best_priority priority
  // 619:   for_each mod_info: (platform filenames)
  // 620:     compile_submodule
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__compile_module_100, 0);
  // 611: do:
  // 612:   $$best_platform undefined
  // 613:   $$best_priority 999
  // 614:   for_each mod_info: (platform _filenames)
  // 615:     $priority platform_priority(platform)
  // 616:     if priority.is_defined && priority < best_priority:
  // 617:       !best_platform platform
  // 618:       !best_priority priority
  // 619:   for_each mod_info: (platform filenames)
  // 620:     compile_submodule
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__compile_module_112;
}
static void entry__compile_module_109(void) {
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
  // 622: platform == best_platform
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* platform */;
  arguments->slots[1] = ((CELL *)frame->slots[3])->contents /* best_platform */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__compile_module_110;
}
static void cont__compile_module_110(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 623: string("-" platform)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9ccc;
  arguments->slots[1] = frame->slots[0] /* platform */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__compile_module_111;
}
static void cont__compile_module_111(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 620: compile_submodule
  // 621:   filenames
  // 622:   platform == best_platform
  // 623:   string("-" platform)
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
static void entry__compile_module_100(void) {
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
  // 612: $$best_platform undefined
  ((CELL *)frame->slots[2])->contents /* best_platform */ = get__undefined();
  // 613: $$best_priority 999
  ((CELL *)frame->slots[3])->contents /* best_priority */ = number__999;
  // 614: ... : (platform _filenames)
  // 615:   $priority platform_priority(platform)
  // 616:   if priority.is_defined && priority < best_priority:
  // 617:     !best_platform platform
  // 618:     !best_priority priority
  frame->slots[4] /* temp__1 */ = create_closure(entry__compile_module_101, 2);
  // 614: for_each mod_info: (platform _filenames)
  // 615:   $priority platform_priority(platform)
  // 616:   if priority.is_defined && priority < best_priority:
  // 617:     !best_platform platform
  // 618:     !best_priority priority
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_info */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compile_module_108;
}
static void entry__compile_module_107(void) {
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
  // 617: !best_platform platform
  ((CELL *)frame->slots[0])->contents /* best_platform */ = frame->slots[1] /* platform */;
  // 618: !best_priority priority
  ((CELL *)frame->slots[2])->contents /* best_priority */ = frame->slots[3] /* priority */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compile_module_101(void) {
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
  // 615: $priority platform_priority(platform)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* platform */;
  result_count = 1;
  myself = var._platform_priority;
  func = myself->type;
  frame->cont = cont__compile_module_102;
}
static void cont__compile_module_102(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* priority */, arguments->slots[0]);
  // 616: ... priority.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* priority */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compile_module_103;
}
static void cont__compile_module_103(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 616: ... priority < best_priority
  frame->slots[7] /* temp__3 */ = create_closure(entry__compile_module_104, 0);
  // 616: ... priority.is_defined && priority < best_priority
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__compile_module_106;
}
static void entry__compile_module_104(void) {
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
  // 616: ... priority < best_priority
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* priority */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* best_priority */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__compile_module_105;
}
static void cont__compile_module_105(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 616: ... priority < best_priority
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compile_module_106(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 616: ... :
  // 617:   !best_platform platform
  // 618:   !best_priority priority
  frame->slots[8] /* temp__4 */ = create_closure(entry__compile_module_107, 0);
  // 616: if priority.is_defined && priority < best_priority:
  // 617:   !best_platform platform
  // 618:   !best_priority priority
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compile_module_108(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 619: ... : (platform filenames)
  // 620:   compile_submodule
  // 621:     filenames
  // 622:     platform == best_platform
  // 623:     string("-" platform)
  frame->slots[4] /* temp__1 */ = create_closure(entry__compile_module_109, 2);
  // 619: for_each mod_info: (platform filenames)
  // 620:   compile_submodule
  // 621:     filenames
  // 622:     platform == best_platform
  // 623:     string("-" platform)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_info */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compile_module_112(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 624: ... :
  // 625:   $$used_by empty_table
  // 626:   for_each supported_platforms: (supported_platform _parent_platform)
  // 627:     $$best_platform undefined
  // 628:     $$best_priority 999
  // 629:     for_each mod_info: (platform _filenames)
  // 630:       $priority platform_specific_priority(supported_platform platform)
  // 631:       if priority.is_defined && priority < best_priority:
  // 632:         !best_platform platform
  // 633:         !best_priority priority
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__compile_module_113, 0);
  // 624: if do_list_dependencies:
  // 625:   $$used_by empty_table
  // 626:   for_each supported_platforms: (supported_platform _parent_platform)
  // 627:     $$best_platform undefined
  // 628:     $$best_priority 999
  // 629:     for_each mod_info: (platform _filenames)
  // 630:       $priority platform_specific_priority(supported_platform platform)
  // 631:       if priority.is_defined && priority < best_priority:
  // 632:         !best_platform platform
  // 633:         !best_priority priority
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
static void cont__compile_module_140(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__compile_modules_8(void) {
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
  // 654: ... string(path '/' name)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* path */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__compile_modules_9;
}
static void cont__compile_modules_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 654: ... string(mod_path '/' name)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* mod_path */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__compile_modules_10;
}
static void cont__compile_modules_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 654: compile_module string(path '/' name) string(mod_path '/' name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = func__compile_module;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compile_modules(void) {
  allocate_initialized_frame_gc(2, 5);
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
  // 650: ... string(mod_path '/')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* mod_path */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__compile_modules_2;
}
static void cont__compile_modules_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 650: add_module_infos $directories $modules path string(mod_path '/')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* path */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 2;
  myself = func__add_module_infos;
  func = myself->type;
  frame->cont = cont__compile_modules_3;
}
static void cont__compile_modules_3(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* directories */, arguments->slots[0]);
  initialize_future(frame->slots[3] /* modules */, arguments->slots[1]);
  // 651: ... : (name)
  // 652:   compile_modules string(path '/' name) string(mod_path '/' name)
  frame->slots[4] /* temp__1 */ = create_closure(entry__compile_modules_4, 1);
  // 651: for_each directories: (name)
  // 652:   compile_modules string(path '/' name) string(mod_path '/' name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* directories */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compile_modules_7;
}
static void entry__compile_modules_4(void) {
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
  // 652: ... string(path '/' name)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* path */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__compile_modules_5;
}
static void cont__compile_modules_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 652: ... string(mod_path '/' name)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* mod_path */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__compile_modules_6;
}
static void cont__compile_modules_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 652: compile_modules string(path '/' name) string(mod_path '/' name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = func__compile_modules;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compile_modules_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 653: ... : (name)
  // 654:   compile_module string(path '/' name) string(mod_path '/' name)
  frame->slots[4] /* temp__1 */ = create_closure(entry__compile_modules_8, 1);
  // 653: for_each modules: (name)
  // 654:   compile_module string(path '/' name) string(mod_path '/' name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* modules */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__show_file_list_2(void) {
  allocate_initialized_frame_gc(0, 3);
  // slot allocations:
  // path: 0
  frame->slots[0] /* path */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 662: $path environment("LD_LIBRARY_PATH")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__21dcb95c2a4f4c6f;
  result_count = 1;
  myself = get__environment();
  func = myself->type;
  frame->cont = cont__show_file_list_4;
}
static void cont__show_file_list_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[0] /* path */, arguments->slots[0]);
  // 663: ... path.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* path */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__show_file_list_5;
}
static void cont__show_file_list_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 663: ... : ewriteln "LD_LIBRARY_PATH=@(path)"
  frame->slots[2] /* temp__2 */ = create_closure(entry__show_file_list_6, 0);
  // 663: if path.is_defined: ewriteln "LD_LIBRARY_PATH=@(path)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__show_file_list_9;
}
static void entry__show_file_list_6(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // path: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* path */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 663: ... "LD_LIBRARY_PATH=@(path)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__cae1527a63790ed8;
  arguments->slots[1] = frame->slots[0] /* path */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__show_file_list_8;
}
static void cont__show_file_list_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 663: ... ewriteln "LD_LIBRARY_PATH=@(path)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__show_file_list_9(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 664: ... serialize(objects)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__objects();
  result_count = 1;
  myself = get__serialize();
  func = myself->type;
  frame->cont = cont__show_file_list_10;
}
static void cont__show_file_list_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 664: ewriteln "included object files: " serialize(objects)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__4c84a8f87d97d1a3;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 0;
  myself = get__ewriteln();
  func = myself->type;
  frame->cont = cont__show_file_list_12;
}
static void cont__show_file_list_12(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 665: ... serialize(libraries)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__libraries();
  result_count = 1;
  myself = get__serialize();
  func = myself->type;
  frame->cont = cont__show_file_list_13;
}
static void cont__show_file_list_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 665: ewriteln "needed libraries: " serialize(libraries)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__d2a77fcc4263ea03;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__show_file_list(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 661: if do_show_debug_infos:
  // 662:   $path environment("LD_LIBRARY_PATH")
  // 663:   if path.is_defined: ewriteln "LD_LIBRARY_PATH=@(path)"
  // 664:   ewriteln "included object files: " serialize(objects)
  // 665:   ewriteln "needed libraries: " serialize(libraries)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_show_debug_infos();
  arguments->slots[1] = func__show_file_list_2;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__library_paths_and_file_list(void) {
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
  // 668: show_file_list
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = func__show_file_list;
  func = myself->type;
  frame->cont = cont__library_paths_and_file_list_2;
}
static void cont__library_paths_and_file_list_2(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 669: $$library_paths empty_list
  ((CELL *)frame->slots[0])->contents /* library_paths */ = get__empty_list();
  // 670: $$object_files empty_list
  ((CELL *)frame->slots[1])->contents /* object_files */ = get__empty_list();
  // 671: $$library_files empty_list
  ((CELL *)frame->slots[2])->contents /* library_files */ = get__empty_list();
  // 672: $paths environment("LD_LIBRARY_PATH")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__21dcb95c2a4f4c6f;
  result_count = 1;
  myself = get__environment();
  func = myself->type;
  frame->cont = cont__library_paths_and_file_list_3;
}
static void cont__library_paths_and_file_list_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* paths */, arguments->slots[0]);
  // 673: ... paths.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* paths */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__library_paths_and_file_list_4;
}
static void cont__library_paths_and_file_list_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 673: ... :
  // 674:   for_each paths .split. ':': (path) push &library_paths "-L@(path)"
  frame->slots[5] /* temp__2 */ = create_closure(entry__library_paths_and_file_list_5, 0);
  // 673: if paths.is_defined:
  // 674:   for_each paths .split. ':': (path) push &library_paths "-L@(path)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__library_paths_and_file_list_11;
}
static void entry__library_paths_and_file_list_7(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // path: 0
  // library_paths: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* library_paths */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 674: ... "-L@(path)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6602b89;
  arguments->slots[1] = frame->slots[0] /* path */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__library_paths_and_file_list_9;
}
static void cont__library_paths_and_file_list_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 674: ... push &library_paths "-L@(path)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* library_paths */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__library_paths_and_file_list_10;
}
static void cont__library_paths_and_file_list_10(void) {
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
static void entry__library_paths_and_file_list_5(void) {
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
  // 674: ... paths .split. ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* paths */;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__split();
  func = myself->type;
  frame->cont = cont__library_paths_and_file_list_6;
}
static void cont__library_paths_and_file_list_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 674: ... : (path) push &library_paths "-L@(path)"
  frame->slots[3] /* temp__2 */ = create_closure(entry__library_paths_and_file_list_7, 1);
  // 674: for_each paths .split. ':': (path) push &library_paths "-L@(path)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__library_paths_and_file_list_11(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 675: ... : ewriteln "library paths: " serialize(library_paths)
  frame->slots[4] /* temp__1 */ = create_closure(entry__library_paths_and_file_list_12, 0);
  // 675: if do_show_debug_infos: ewriteln "library paths: " serialize(library_paths)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_show_debug_infos();
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__library_paths_and_file_list_15;
}
static void entry__library_paths_and_file_list_12(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // library_paths: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* library_paths */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 675: ... serialize(library_paths)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* library_paths */;
  result_count = 1;
  myself = get__serialize();
  func = myself->type;
  frame->cont = cont__library_paths_and_file_list_13;
}
static void cont__library_paths_and_file_list_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 675: ... ewriteln "library paths: " serialize(library_paths)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__47d536100241702d;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__library_paths_and_file_list_15(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 676: ... : (object) push &object_files object
  frame->slots[4] /* temp__1 */ = create_closure(entry__library_paths_and_file_list_16, 1);
  // 676: for_each objects: (object) push &object_files object
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__objects();
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__library_paths_and_file_list_18;
}
static void entry__library_paths_and_file_list_16(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // object: 0
  // object_files: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* object_files */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 676: ... push &object_files object
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* object_files */;
  arguments->slots[1] = frame->slots[0] /* object */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__library_paths_and_file_list_17;
}
static void cont__library_paths_and_file_list_17(void) {
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
static void cont__library_paths_and_file_list_18(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 677: ... : (library)
  // 678:   push
  // 679:     &library_files
  // 680:     if
  // 681:       library .has_prefix. "sim-"
  // 682:       ->
  // 683:         case
  // 684:           operating_system()
  // 685:           "linux", "bsd"
  // 686:           -> "-l:lib@(library).so.@(MAJOR)"
  // ...
  frame->slots[4] /* temp__1 */ = create_closure(entry__library_paths_and_file_list_19, 1);
  // 677: for_each libraries: (library)
  // 678:   push
  // 679:     &library_files
  // 680:     if
  // 681:       library .has_prefix. "sim-"
  // 682:       ->
  // 683:         case
  // 684:           operating_system()
  // 685:           "linux", "bsd"
  // 686:           -> "-l:lib@(library).so.@(MAJOR)"
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__libraries();
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__library_paths_and_file_list_45;
}
static void entry__library_paths_and_file_list_19(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // library: 0
  // library_files: 1
  frame->slots[1] = myself->closure.frame->slots[2]; /* library_files */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 681: library .has_prefix. "sim-"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* library */;
  arguments->slots[1] = string__240aeb0b5d087d14;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__library_paths_and_file_list_20;
}
static void cont__library_paths_and_file_list_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 682: ->
  // 683:   case
  // 684:     operating_system()
  // 685:     "linux", "bsd"
  // 686:     -> "-l:lib@(library).so.@(MAJOR)"
  // 687:     -> "-l@(library)-@(MAJOR)"
  frame->slots[4] /* temp__3 */ = create_closure(entry__library_paths_and_file_list_21, 0);
  // 688: ->
  // 689:   if
  // 690:     library .contains. '.'
  // 691:     -> "-l:lib@(library .before. '.').so.@(library .behind. '.')"
  // 692:       # Linux only
  // 693:     -> "-l@(library)"
  frame->slots[5] /* temp__4 */ = create_closure(entry__library_paths_and_file_list_34, 0);
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  arguments->slots[2] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__library_paths_and_file_list_43;
}
static void entry__library_paths_and_file_list_21(void) {
  allocate_initialized_frame_gc(1, 6);
  // slot allocations:
  // library: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* library */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 684: operating_system()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__operating_system();
  func = myself->type;
  frame->cont = cont__library_paths_and_file_list_22;
}
static void cont__library_paths_and_file_list_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 685: "linux", "bsd"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__585ae883ea60d02f;
  arguments->slots[1] = string__fa720c15db16ba8;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__library_paths_and_file_list_25;
}
static void cont__library_paths_and_file_list_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 686: -> "-l:lib@(library).so.@(MAJOR)"
  frame->slots[4] /* temp__4 */ = create_closure(entry__library_paths_and_file_list_26, 0);
  // 687: -> "-l@(library)-@(MAJOR)"
  frame->slots[5] /* temp__5 */ = create_closure(entry__library_paths_and_file_list_30, 0);
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  arguments->slots[2] = frame->slots[4] /* temp__4 */;
  arguments->slots[3] = frame->slots[5] /* temp__5 */;
  result_count = 1;
  myself = get__case();
  func = myself->type;
  frame->cont = cont__library_paths_and_file_list_33;
}
static void entry__library_paths_and_file_list_26(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // library: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* library */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 686: ... "-l:lib@(library).so.@(MAJOR)"
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__ec1f556601f292b5;
  arguments->slots[1] = frame->slots[0] /* library */;
  arguments->slots[2] = string__9e0aed8b5d187d17;
  arguments->slots[3] = var._MAJOR;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__library_paths_and_file_list_29;
}
static void cont__library_paths_and_file_list_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 686: -> "-l:lib@(library).so.@(MAJOR)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__library_paths_and_file_list_30(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // library: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* library */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 687: ... "-l@(library)-@(MAJOR)"
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6602ba9;
  arguments->slots[1] = frame->slots[0] /* library */;
  arguments->slots[2] = string__578a5af303e9ccc;
  arguments->slots[3] = var._MAJOR;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__library_paths_and_file_list_32;
}
static void cont__library_paths_and_file_list_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 687: -> "-l@(library)-@(MAJOR)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__library_paths_and_file_list_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 682: ->
  // 683:   case
  // 684:     operating_system()
  // 685:     "linux", "bsd"
  // 686:     -> "-l:lib@(library).so.@(MAJOR)"
  // 687:     -> "-l@(library)-@(MAJOR)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__library_paths_and_file_list_34(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // library: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* library */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 690: library .contains. '.'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* library */;
  arguments->slots[1] = character__46;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__library_paths_and_file_list_35;
}
static void cont__library_paths_and_file_list_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 691: -> "-l:lib@(library .before. '.').so.@(library .behind. '.')"
  // 692:   # Linux only
  frame->slots[3] /* temp__3 */ = create_closure(entry__library_paths_and_file_list_36, 0);
  // 693: -> "-l@(library)"
  frame->slots[4] /* temp__4 */ = create_closure(entry__library_paths_and_file_list_40, 0);
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  arguments->slots[2] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__library_paths_and_file_list_42;
}
static void entry__library_paths_and_file_list_36(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // library: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* library */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 691: ... library .before. '.'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* library */;
  arguments->slots[1] = character__46;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__library_paths_and_file_list_37;
}
static void cont__library_paths_and_file_list_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 691: ... library .behind. '.'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* library */;
  arguments->slots[1] = character__46;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__library_paths_and_file_list_38;
}
static void cont__library_paths_and_file_list_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 691: ... "-l:lib@(library .before. '.').so.@(library .behind. '.')"
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__ec1f556601f292b5;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  arguments->slots[2] = string__9e0aed8b5d187d17;
  arguments->slots[3] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__library_paths_and_file_list_39;
}
static void cont__library_paths_and_file_list_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 691: -> "-l:lib@(library .before. '.').so.@(library .behind. '.')"
  // 692:   # Linux only
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__library_paths_and_file_list_40(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // library: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* library */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 693: ... "-l@(library)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6602ba9;
  arguments->slots[1] = frame->slots[0] /* library */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__library_paths_and_file_list_41;
}
static void cont__library_paths_and_file_list_41(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 693: -> "-l@(library)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__library_paths_and_file_list_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 688: ->
  // 689:   if
  // 690:     library .contains. '.'
  // 691:     -> "-l:lib@(library .before. '.').so.@(library .behind. '.')"
  // 692:       # Linux only
  // 693:     -> "-l@(library)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__library_paths_and_file_list_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 678: push
  // 679:   &library_files
  // 680:   if
  // 681:     library .has_prefix. "sim-"
  // 682:     ->
  // 683:       case
  // 684:         operating_system()
  // 685:         "linux", "bsd"
  // 686:         -> "-l:lib@(library).so.@(MAJOR)"
  // 687:         -> "-l@(library)-@(MAJOR)"
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* library_files */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__library_paths_and_file_list_44;
}
static void cont__library_paths_and_file_list_44(void) {
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
static void cont__library_paths_and_file_list_45(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 694: ... append(object_files library_files)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* object_files */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* library_files */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__library_paths_and_file_list_46;
}
static void cont__library_paths_and_file_list_46(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 694: append library_paths append(object_files library_files)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* library_paths */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__append();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__create_imports_74(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 737: ... write_timing_info "collecting imports"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__868d47f2e5ba5079;
  result_count = frame->caller_result_count;
  myself = get__write_timing_info();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__create_imports(void) {
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
  // 699: ... : (buf)
  // 700:   $$s undefined
  // 701:   for_each buf: (idx chr)
  // 702:     if
  // 703:       s.is_defined:
  // 704:         unless chr.is_a_letter || chr == '_' || chr.is_a_digit:
  // 705:           $symbol range(buf s idx-1)
  // 706:           !s undefined
  // 707:           unless already_checked(symbol):
  // 708:             !already_checked(symbol) true
  // ...
  frame->slots[5] /* temp__1 */ = create_closure(entry__create_imports_2, 1);
  // 699: $collect_declarations: (buf)
  // 700:   $$s undefined
  // 701:   for_each buf: (idx chr)
  // 702:     if
  // 703:       s.is_defined:
  // 704:         unless chr.is_a_letter || chr == '_' || chr.is_a_digit:
  // 705:           $symbol range(buf s idx-1)
  // 706:           !s undefined
  // 707:           unless already_checked(symbol):
  // 708:             !already_checked(symbol) true
  // ...
  initialize_future(frame->slots[2] /* collect_declarations */, frame->slots[5] /* temp__1 */);
  // 697: $$already_checked empty_set
  ((CELL *)frame->slots[1])->contents /* already_checked */ = get__empty_set();
  // 732: ... : collect_declarations source
  frame->slots[5] /* temp__1 */ = create_closure(entry__create_imports_63, 0);
  // 732: collect_output $imports: collect_declarations source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__create_imports_64;
}
static void entry__create_imports_62(void) {
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
  // 730: ... !s idx
  ((CELL *)frame->slots[0])->contents /* s */ = frame->slots[1] /* idx */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__create_imports_21(void) {
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
  // 713: declaration(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* declaration */;
  func = myself->type;
  frame->cont = cont__create_imports_22;
}
static void cont__create_imports_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 713: declaration(1) != '#'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  arguments->slots[1] = character__35;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__create_imports_23;
}
static void cont__create_imports_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 713: declaration(1) != '#'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__create_imports_24;
}
static void cont__create_imports_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  frame->slots[6] /* temp__4 */ = create_closure(entry__create_imports_25, 0);
  // 711: $do_import
  // 712:   &&
  // 713:     declaration(1) != '#'
  // 714:     not(declaration .has_prefix. "typedef")
  // 715:     not(declaration .has_prefix. "REGISTER")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__create_imports_34;
}
static void entry__create_imports_25(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // declaration: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* declaration */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 714: ... declaration .has_prefix. "typedef"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* declaration */;
  arguments->slots[1] = string__b8540cde1593c09c;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__create_imports_27;
}
static void cont__create_imports_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 714: not(declaration .has_prefix. "typedef")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__not();
  func = myself->type;
  frame->cont = cont__create_imports_28;
}
static void cont__create_imports_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 715: not(declaration .has_prefix. "REGISTER")
  frame->slots[4] /* temp__4 */ = create_closure(entry__create_imports_29, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__create_imports_33;
}
static void entry__create_imports_29(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // declaration: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* declaration */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 715: ... declaration .has_prefix. "REGISTER"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* declaration */;
  arguments->slots[1] = string__800a0c585ff0632;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__create_imports_31;
}
static void cont__create_imports_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 715: not(declaration .has_prefix. "REGISTER")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__not();
  func = myself->type;
  frame->cont = cont__create_imports_32;
}
static void cont__create_imports_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 715: not(declaration .has_prefix. "REGISTER")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__create_imports_33(void) {
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
static void cont__create_imports_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* do_import */, arguments->slots[0]);
  // 718: ->
  // 719:   declaration(1) == '#' || declaration .has_prefix. "REGISTER"
  // 720:   :
  // 721:     collect_declarations declaration .truncate_from. '{'
  frame->slots[3] /* temp__1 */ = create_closure(entry__create_imports_35, 0);
  // 722: -> declaration .has_prefix. "typedef struct":
  // 723:   for_each_line between(declaration '{' '}').trim: (line)
  // 724:     collect_declarations until(line ' ' -1)
  frame->slots[4] /* temp__2 */ = create_closure(entry__create_imports_43, 0);
  // 725: :
  // 726:   collect_declarations declaration
  frame->slots[5] /* temp__3 */ = create_closure(entry__create_imports_52, 0);
  // 717: cond
  // 718:   ->
  // 719:     declaration(1) == '#' || declaration .has_prefix. "REGISTER"
  // 720:     :
  // 721:       collect_declarations declaration .truncate_from. '{'
  // 722:   -> declaration .has_prefix. "typedef struct":
  // 723:     for_each_line between(declaration '{' '}').trim: (line)
  // 724:       collect_declarations until(line ' ' -1)
  // 725:   :
  // 726:     collect_declarations declaration
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = frame->slots[5] /* temp__3 */;
  result_count = 0;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__create_imports_53;
}
static void entry__create_imports_49(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // line: 0
  // collect_declarations: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* collect_declarations */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 724: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__create_imports_50;
}
static void cont__create_imports_50(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 724: ... until(line ' ' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* line */;
  arguments->slots[1] = character__32;
  arguments->slots[2] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__until();
  func = myself->type;
  frame->cont = cont__create_imports_51;
}
static void cont__create_imports_51(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 724: collect_declarations until(line ' ' -1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* collect_declarations */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__create_imports_46(void) {
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
  // 723: ... between(declaration '{' '}')
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* declaration */;
  arguments->slots[1] = character__123;
  arguments->slots[2] = character__125;
  result_count = 1;
  myself = get__between();
  func = myself->type;
  frame->cont = cont__create_imports_47;
}
static void cont__create_imports_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 723: ... between(declaration '{' '}').trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__create_imports_48;
}
static void cont__create_imports_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 723: ... : (line)
  // 724:   collect_declarations until(line ' ' -1)
  frame->slots[4] /* temp__3 */ = create_closure(entry__create_imports_49, 1);
  // 723: for_each_line between(declaration '{' '}').trim: (line)
  // 724:   collect_declarations until(line ' ' -1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__for_each_line();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__create_imports_41(void) {
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
  // 721: ... declaration .truncate_from. '{'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* declaration */;
  arguments->slots[1] = character__123;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__create_imports_42;
}
static void cont__create_imports_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 721: collect_declarations declaration .truncate_from. '{'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* collect_declarations */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__create_imports_35(void) {
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
  // 719: declaration(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* declaration */;
  func = myself->type;
  frame->cont = cont__create_imports_36;
}
static void cont__create_imports_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 719: declaration(1) == '#'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  arguments->slots[1] = character__35;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__create_imports_37;
}
static void cont__create_imports_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 719: ... declaration .has_prefix. "REGISTER"
  frame->slots[5] /* temp__4 */ = create_closure(entry__create_imports_38, 0);
  // 719: declaration(1) == '#' || declaration .has_prefix. "REGISTER"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__create_imports_40;
}
static void entry__create_imports_38(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // declaration: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* declaration */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 719: ... declaration .has_prefix. "REGISTER"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* declaration */;
  arguments->slots[1] = string__800a0c585ff0632;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__create_imports_39;
}
static void cont__create_imports_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 719: ... declaration .has_prefix. "REGISTER"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__create_imports_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 720: :
  // 721:   collect_declarations declaration .truncate_from. '{'
  frame->slots[6] /* temp__5 */ = create_closure(entry__create_imports_41, 0);
  // 718: ->
  // 719:   declaration(1) == '#' || declaration .has_prefix. "REGISTER"
  // 720:   :
  // 721:     collect_declarations declaration .truncate_from. '{'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__5 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__create_imports_43(void) {
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
  // 722: ... declaration .has_prefix. "typedef struct"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* declaration */;
  arguments->slots[1] = string__ee0186bb316753e3;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__create_imports_45;
}
static void cont__create_imports_45(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 722: ... :
  // 723:   for_each_line between(declaration '{' '}').trim: (line)
  // 724:     collect_declarations until(line ' ' -1)
  frame->slots[3] /* temp__2 */ = create_closure(entry__create_imports_46, 0);
  // 722: -> declaration .has_prefix. "typedef struct":
  // 723:   for_each_line between(declaration '{' '}').trim: (line)
  // 724:     collect_declarations until(line ' ' -1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__create_imports_52(void) {
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
  // 726: collect_declarations declaration
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* declaration */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* collect_declarations */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__create_imports_53(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 727: if do_import: write "IMPORT "
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* do_import */;
  arguments->slots[1] = func__create_imports_54;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__create_imports_56;
}
static void entry__create_imports_54(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 727: ... write "IMPORT "
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__eca001441419c0da;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__create_imports_56(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 728: write declaration
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* declaration */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__create_imports_17(void) {
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
  // 708: !already_checked(symbol)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* symbol */;
  arguments->slots[1] = get__true();
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* already_checked */;
  func = myself->type;
  frame->cont = cont__create_imports_18;
}
static void cont__create_imports_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* already_checked */ = arguments->slots[0];
  // 709: $declaration runtime_symbols(symbol)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* symbol */;
  result_count = 1;
  myself = get__runtime_symbols();
  func = myself->type;
  frame->cont = cont__create_imports_19;
}
static void cont__create_imports_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* declaration */, arguments->slots[0]);
  // 710: ... declaration.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* declaration */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__create_imports_20;
}
static void cont__create_imports_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 710: ... :
  // 711:   $do_import
  // 712:     &&
  // 713:       declaration(1) != '#'
  // 714:       not(declaration .has_prefix. "typedef")
  // 715:       not(declaration .has_prefix. "REGISTER")
  // 716:   
  // 717:   cond
  // 718:     ->
  // 719:       declaration(1) == '#' || declaration .has_prefix. "REGISTER"
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__create_imports_21, 0);
  // 710: if declaration.is_defined:
  // 711:   $do_import
  // 712:     &&
  // 713:       declaration(1) != '#'
  // 714:       not(declaration .has_prefix. "typedef")
  // 715:       not(declaration .has_prefix. "REGISTER")
  // 716:   
  // 717:   cond
  // 718:     ->
  // 719:       declaration(1) == '#' || declaration .has_prefix. "REGISTER"
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
static void entry__create_imports_13(void) {
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
  // 705: ... idx-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* idx */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__create_imports_14;
}
static void cont__create_imports_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 705: $symbol range(buf s idx-1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* buf */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* s */;
  arguments->slots[2] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__create_imports_15;
}
static void cont__create_imports_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* symbol */, arguments->slots[0]);
  // 706: !s undefined
  ((CELL *)frame->slots[1])->contents /* s */ = get__undefined();
  // 707: ... already_checked(symbol)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* symbol */;
  result_count = 1;
  myself = ((CELL *)frame->slots[3])->contents /* already_checked */;
  func = myself->type;
  frame->cont = cont__create_imports_16;
}
static void cont__create_imports_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 707: ... :
  // 708:   !already_checked(symbol) true
  // 709:   $declaration runtime_symbols(symbol)
  // 710:   if declaration.is_defined:
  // 711:     $do_import
  // 712:       &&
  // 713:         declaration(1) != '#'
  // 714:         not(declaration .has_prefix. "typedef")
  // 715:         not(declaration .has_prefix. "REGISTER")
  // 716:     
  // ...
  frame->slots[7] /* temp__2 */ = create_closure(entry__create_imports_17, 0);
  // 707: unless already_checked(symbol):
  // 708:   !already_checked(symbol) true
  // 709:   $declaration runtime_symbols(symbol)
  // 710:   if declaration.is_defined:
  // 711:     $do_import
  // 712:       &&
  // 713:         declaration(1) != '#'
  // 714:         not(declaration .has_prefix. "typedef")
  // 715:         not(declaration .has_prefix. "REGISTER")
  // 716:     
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
static void entry__create_imports_5(void) {
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
  // 704: ... chr.is_a_letter
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  result_count = 1;
  myself = get__is_a_letter();
  func = myself->type;
  frame->cont = cont__create_imports_6;
}
static void cont__create_imports_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 704: ... chr == '_' || chr.is_a_digit
  frame->slots[8] /* temp__3 */ = create_closure(entry__create_imports_7, 0);
  // 704: ... chr.is_a_letter || chr == '_' || chr.is_a_digit
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  arguments->slots[1] = frame->slots[8] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__create_imports_12;
}
static void entry__create_imports_7(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 704: ... chr == '_'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__95;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__create_imports_8;
}
static void cont__create_imports_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 704: ... chr.is_a_digit
  frame->slots[3] /* temp__3 */ = create_closure(entry__create_imports_9, 0);
  // 704: ... chr == '_' || chr.is_a_digit
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__create_imports_11;
}
static void entry__create_imports_9(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 704: ... chr.is_a_digit
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  result_count = 1;
  myself = get__is_a_digit();
  func = myself->type;
  frame->cont = cont__create_imports_10;
}
static void cont__create_imports_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 704: ... chr.is_a_digit
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__create_imports_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 704: ... chr == '_' || chr.is_a_digit
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__create_imports_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 704: ... :
  // 705:   $symbol range(buf s idx-1)
  // 706:   !s undefined
  // 707:   unless already_checked(symbol):
  // 708:     !already_checked(symbol) true
  // 709:     $declaration runtime_symbols(symbol)
  // 710:     if declaration.is_defined:
  // 711:       $do_import
  // 712:         &&
  // 713:           declaration(1) != '#'
  // ...
  frame->slots[9] /* temp__4 */ = create_closure(entry__create_imports_13, 0);
  // 704: unless chr.is_a_letter || chr == '_' || chr.is_a_digit:
  // 705:   $symbol range(buf s idx-1)
  // 706:   !s undefined
  // 707:   unless already_checked(symbol):
  // 708:     !already_checked(symbol) true
  // 709:     $declaration runtime_symbols(symbol)
  // 710:     if declaration.is_defined:
  // 711:       $do_import
  // 712:         &&
  // 713:           declaration(1) != '#'
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
static void entry__create_imports_57(void) {
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
  // 730: ... chr.is_a_letter
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  result_count = 1;
  myself = get__is_a_letter();
  func = myself->type;
  frame->cont = cont__create_imports_58;
}
static void cont__create_imports_58(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 730: ... chr == '_'
  frame->slots[5] /* temp__3 */ = create_closure(entry__create_imports_59, 0);
  // 730: ... chr.is_a_letter || chr == '_'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__create_imports_61;
}
static void entry__create_imports_59(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 730: ... chr == '_'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__95;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__create_imports_60;
}
static void cont__create_imports_60(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 730: ... chr == '_'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__create_imports_61(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 730: ... : !s idx
  frame->slots[6] /* temp__4 */ = create_closure(entry__create_imports_62, 0);
  // 730: if chr.is_a_letter || chr == '_': !s idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__create_imports_3(void) {
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
  // 703: s.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* s */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__create_imports_4;
}
static void cont__create_imports_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 703: ... :
  // 704:   unless chr.is_a_letter || chr == '_' || chr.is_a_digit:
  // 705:     $symbol range(buf s idx-1)
  // 706:     !s undefined
  // 707:     unless already_checked(symbol):
  // 708:       !already_checked(symbol) true
  // 709:       $declaration runtime_symbols(symbol)
  // 710:       if declaration.is_defined:
  // 711:         $do_import
  // 712:           &&
  // ...
  frame->slots[7] /* temp__2 */ = create_closure(entry__create_imports_5, 0);
  // 729: :
  // 730:   if chr.is_a_letter || chr == '_': !s idx
  frame->slots[8] /* temp__3 */ = create_closure(entry__create_imports_57, 0);
  // 702: if
  // 703:   s.is_defined:
  // 704:     unless chr.is_a_letter || chr == '_' || chr.is_a_digit:
  // 705:       $symbol range(buf s idx-1)
  // 706:       !s undefined
  // 707:       unless already_checked(symbol):
  // 708:         !already_checked(symbol) true
  // 709:         $declaration runtime_symbols(symbol)
  // 710:         if declaration.is_defined:
  // 711:           $do_import
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
static void entry__create_imports_2(void) {
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
  // 700: $$s undefined
  ((CELL *)frame->slots[3])->contents /* s */ = get__undefined();
  // 701: ... : (idx chr)
  // 702:   if
  // 703:     s.is_defined:
  // 704:       unless chr.is_a_letter || chr == '_' || chr.is_a_digit:
  // 705:         $symbol range(buf s idx-1)
  // 706:         !s undefined
  // 707:         unless already_checked(symbol):
  // 708:           !already_checked(symbol) true
  // 709:           $declaration runtime_symbols(symbol)
  // 710:           if declaration.is_defined:
  // ...
  frame->slots[4] /* temp__1 */ = create_closure(entry__create_imports_3, 2);
  // 701: for_each buf: (idx chr)
  // 702:   if
  // 703:     s.is_defined:
  // 704:       unless chr.is_a_letter || chr == '_' || chr.is_a_digit:
  // 705:         $symbol range(buf s idx-1)
  // 706:         !s undefined
  // 707:         unless already_checked(symbol):
  // 708:           !already_checked(symbol) true
  // 709:           $declaration runtime_symbols(symbol)
  // 710:           if declaration.is_defined:
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
static void entry__create_imports_63(void) {
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
  // 732: ... collect_declarations source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* source */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* collect_declarations */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__create_imports_64(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* imports */, arguments->slots[0]);
  // 733: $first_part source .before. "// INSERT HERE //"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  arguments->slots[1] = string__736c99bf90749400;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__create_imports_66;
}
static void cont__create_imports_66(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* first_part */, arguments->slots[0]);
  // 734: write first_part
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* first_part */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__create_imports_67;
}
static void cont__create_imports_67(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 735: write imports
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* imports */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__create_imports_68;
}
static void cont__create_imports_68(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 736: ... length_of(first_part)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* first_part */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__create_imports_69;
}
static void cont__create_imports_69(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__3 */ = arguments->slots[0];
  // 736: ... length_of(first_part)+18
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__3 */;
  arguments->slots[1] = number__18;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__create_imports_70;
}
static void cont__create_imports_70(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 736: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__create_imports_71;
}
static void cont__create_imports_71(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__4 */ = arguments->slots[0];
  // 736: ... range(source length_of(first_part)+18 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  arguments->slots[2] = frame->slots[8] /* temp__4 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__create_imports_72;
}
static void cont__create_imports_72(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 736: write range(source length_of(first_part)+18 -1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__create_imports_73;
}
static void cont__create_imports_73(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 737: if do_time_passes: write_timing_info "collecting imports"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = func__create_imports_74;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compile_exe(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // body: 0
  // return__1: 1
  // mod_filename: 2
  // mod_name: 3
  frame->slots[1] /* return__1 */ = create_continuation();
  // _define %mode .
  define__mode(unique__EXE);
  frame->slots[2] /* mod_filename */ = create_future();
  frame->slots[3] /* mod_name */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 740: ... main_info.is_a_directory
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_info();
  result_count = 1;
  myself = get__is_a_directory();
  func = myself->type;
  frame->cont = cont__compile_exe_2;
}
static void cont__compile_exe_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 740: if main_info.is_a_directory: Error "Expected a source code file!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = func__compile_exe_3;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compile_exe_5;
}
static void entry__compile_exe_3(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 740: ... Error "Expected a source code file!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__ac6b0fa074ea65e7;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compile_exe_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 741: ... main_filename .has_suffix. ".sim"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  arguments->slots[1] = string__9e0aed8b5d287d54;
  result_count = 1;
  myself = get__has_suffix();
  func = myself->type;
  frame->cont = cont__compile_exe_6;
}
static void cont__compile_exe_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 741: unless main_filename .has_suffix. ".sim":
  // 742:   Error "
  // 743:     Expected ".sim" file extension in source filename!@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = func__compile_exe_7;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__compile_exe_9;
}
static void entry__compile_exe_7(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 742: Error "
  // 743:   Expected ".sim" file extension in source filename!@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__e365e96bee331e9c;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compile_exe_9(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 745: $mod_filename main_filename .without_suffix. ".sim"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  arguments->slots[1] = string__9e0aed8b5d287d54;
  result_count = 1;
  myself = get__without_suffix();
  func = myself->type;
  frame->cont = cont__compile_exe_10;
}
static void cont__compile_exe_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* mod_filename */, arguments->slots[0]);
  // 746: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__compile_exe_11;
}
static void cont__compile_exe_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 746: $mod_name truncate_until(mod_filename '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* mod_filename */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__compile_exe_12;
}
static void cont__compile_exe_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* mod_name */, arguments->slots[0]);
  // 747: body mod_filename mod_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* mod_filename */;
  arguments->slots[1] = frame->slots[3] /* mod_name */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame->cont = cont__compile_exe_13;
}
static void cont__compile_exe_13(void) {
  myself = frame->slots[1] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__dump_source_or_check_2(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // mod_filename: 0
  // mod_name: 1
  // return__1: 2
  frame->slots[2] /* return__1 */ = create_continuation();
  // _define %compiler::module_name mod_name
  define__compiler__module_name(frame->slots[1] /* mod_name */);
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 751: %compiler::module_name mod_name
  initialize_maybe_future(get__compiler__module_name(), frame->slots[1] /* mod_name */);
  // 752: ... list(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__dump_source_or_check_3;
}
static void cont__dump_source_or_check_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 752: sim2c list(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__sim2c();
  func = myself->type;
  frame->cont = cont__dump_source_or_check_4;
}
static void cont__dump_source_or_check_4(void) {
  myself = frame->slots[2] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__dump_source_or_check(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 750: compile_exe: (_mod_filename mod_name)
  // 751:   %compiler::module_name mod_name
  // 752:   sim2c list(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__dump_source_or_check_2;
  result_count = frame->caller_result_count;
  myself = func__compile_exe;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__print_c_18(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 762: ... write_timing_info "writing C-source"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__b830f06b636224ab;
  result_count = frame->caller_result_count;
  myself = get__write_timing_info();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__print_c_2(void) {
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
  // 756: ... module_prefix.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._module_prefix;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__print_c_3;
}
static void cont__print_c_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 756: ... : append string(module_prefix '/') &mod_name
  frame->slots[5] /* temp__2 */ = create_closure(entry__print_c_4, 0);
  // 756: if module_prefix.is_defined: append string(module_prefix '/') &mod_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__print_c_7;
}
static void entry__print_c_4(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // mod_name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* mod_name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 756: ... string(module_prefix '/')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._module_prefix;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__print_c_5;
}
static void cont__print_c_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 756: ... append string(module_prefix '/') &mod_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* mod_name */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__print_c_6;
}
static void cont__print_c_6(void) {
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
static void cont__print_c_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 757: ... :
  // 758:   %compiler::module_name replace_all(mod_name '/' = "__" '.' = "__")
  // 759:   sim2c list(main_filename)
  frame->slots[4] /* temp__1 */ = create_closure(entry__print_c_8, 0);
  // 757: collect_output $c_source:
  // 758:   %compiler::module_name replace_all(mod_name '/' = "__" '.' = "__")
  // 759:   sim2c list(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__print_c_14;
}
static void entry__print_c_8(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // return__1: 0
  // mod_name: 1
  frame->slots[0] /* return__1 */ = create_continuation();
  frame->slots[1] = myself->closure.frame->slots[1]; /* mod_name */
  define__compiler__module_name(create_future());
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 758: ... '/' = "__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = string__2d7981f4e5f02b9a;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__print_c_9;
}
static void cont__print_c_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 758: ... '.' = "__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__46;
  arguments->slots[1] = string__2d7981f4e5f02b9a;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__print_c_10;
}
static void cont__print_c_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 758: %compiler::module_name replace_all(mod_name '/' = "__" '.' = "__")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* mod_name */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  arguments->slots[2] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__print_c_11;
}
static void cont__print_c_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(get__compiler__module_name(), arguments->slots[0]);
  // 759: ... list(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__print_c_12;
}
static void cont__print_c_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 759: sim2c list(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__sim2c();
  func = myself->type;
  frame->cont = cont__print_c_13;
}
static void cont__print_c_13(void) {
  myself = frame->slots[0] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__print_c_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* c_source */, arguments->slots[0]);
  // 760: ... : create_imports c_source
  frame->slots[4] /* temp__1 */ = create_closure(entry__print_c_15, 0);
  // 760: collect_output $c_buf: create_imports c_source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__print_c_16;
}
static void entry__print_c_15(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // c_source: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* c_source */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 760: ... create_imports c_source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_source */;
  result_count = frame->caller_result_count;
  myself = func__create_imports;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__print_c_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* c_buf */, arguments->slots[0]);
  // 761: write c_buf
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* c_buf */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__print_c_17;
}
static void cont__print_c_17(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 762: if do_time_passes: write_timing_info "writing C-source"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = func__print_c_18;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__print_c(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 755: compile_exe: (_mod_filename $mod_name)
  // 756:   if module_prefix.is_defined: append string(module_prefix '/') &mod_name
  // 757:   collect_output $c_source:
  // 758:     %compiler::module_name replace_all(mod_name '/' = "__" '.' = "__")
  // 759:     sim2c list(main_filename)
  // 760:   collect_output $c_buf: create_imports c_source
  // 761:   write c_buf
  // 762:   if do_time_passes: write_timing_info "writing C-source"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__print_c_2;
  result_count = frame->caller_result_count;
  myself = func__compile_exe;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__list_dependencies_35(void) {
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
  // 791: without_prefix &filename prefix_path
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* filename */;
  arguments->slots[1] = frame->slots[1] /* prefix_path */;
  result_count = 1;
  myself = get__without_prefix();
  func = myself->type;
  frame->cont = cont__list_dependencies_36;
}
static void cont__list_dependencies_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* filename */ = arguments->slots[0];
  // 792: without_prefix &filename '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* filename */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__without_prefix();
  func = myself->type;
  frame->cont = cont__list_dependencies_37;
}
static void cont__list_dependencies_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* filename */ = arguments->slots[0];
  // 793: writeln filename
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* filename */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__list_dependencies(void) {
  allocate_initialized_frame_gc(0, 2);
  // slot allocations:
  // prefix_path: 0
  frame->slots[0] /* prefix_path */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 765: !platform_specific_priority multi_dimensional_table(types::table types::table)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__types__table();
  arguments->slots[1] = get__types__table();
  result_count = 1;
  myself = get__multi_dimensional_table();
  func = myself->type;
  frame->cont = cont__list_dependencies_2;
}
static void cont__list_dependencies_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._platform_specific_priority = arguments->slots[0];
  // 766: for_each supported_platforms: (supported_platform _parent_platform)
  // 767:   $$platform supported_platform
  // 768:   $$priority 0
  // 769:   do: (-> break)
  // 770:     forever:
  // 771:       $plat supported_platforms(platform)
  // 772:       if plat.is_undefined break
  // 773:       inc &priority
  // 774:       !platform_specific_priority(supported_platform platform) priority
  // 775:       if plat == NONE break
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._supported_platforms;
  arguments->slots[1] = func__list_dependencies_3;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__list_dependencies_14;
}
static void entry__list_dependencies_4(void) {
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
  // 770: ... :
  // 771:   $plat supported_platforms(platform)
  // 772:   if plat.is_undefined break
  // 773:   inc &priority
  // 774:   !platform_specific_priority(supported_platform platform) priority
  // 775:   if plat == NONE break
  // 776:   !platform plat
  frame->slots[4] /* temp__1 */ = create_closure(entry__list_dependencies_5, 0);
  // 770: forever:
  // 771:   $plat supported_platforms(platform)
  // 772:   if plat.is_undefined break
  // 773:   inc &priority
  // 774:   !platform_specific_priority(supported_platform platform) priority
  // 775:   if plat == NONE break
  // 776:   !platform plat
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame->cont = cont__list_dependencies_13;
}
static void entry__list_dependencies_5(void) {
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
  // 771: $plat supported_platforms(platform)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* platform */;
  result_count = 1;
  myself = var._supported_platforms;
  func = myself->type;
  frame->cont = cont__list_dependencies_6;
}
static void cont__list_dependencies_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* plat */, arguments->slots[0]);
  // 772: ... plat.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* plat */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__list_dependencies_7;
}
static void cont__list_dependencies_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 772: if plat.is_undefined break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* break */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__list_dependencies_8;
}
static void cont__list_dependencies_8(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 773: inc &priority
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* priority */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__list_dependencies_9;
}
static void cont__list_dependencies_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* priority */ = arguments->slots[0];
  // 774: !platform_specific_priority(supported_platform platform)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* supported_platform */;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* platform */;
  arguments->slots[2] = ((CELL *)frame->slots[2])->contents /* priority */;
  result_count = 1;
  myself = var._platform_specific_priority;
  func = myself->type;
  frame->cont = cont__list_dependencies_10;
}
static void cont__list_dependencies_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._platform_specific_priority = arguments->slots[0];
  // 775: ... plat == NONE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* plat */;
  arguments->slots[1] = unique__NONE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__list_dependencies_11;
}
static void cont__list_dependencies_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 775: if plat == NONE break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* break */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__list_dependencies_12;
}
static void cont__list_dependencies_12(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 776: !platform plat
  ((CELL *)frame->slots[0])->contents /* platform */ = frame->slots[4] /* plat */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__list_dependencies_13(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__list_dependencies_3(void) {
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
  // 767: $$platform supported_platform
  ((CELL *)frame->slots[2])->contents /* platform */ = frame->slots[0] /* supported_platform */;
  // 768: $$priority 0
  ((CELL *)frame->slots[3])->contents /* priority */ = number__0;
  // 769: ... : (-> break)
  // 770:   forever:
  // 771:     $plat supported_platforms(platform)
  // 772:     if plat.is_undefined break
  // 773:     inc &priority
  // 774:     !platform_specific_priority(supported_platform platform) priority
  // 775:     if plat == NONE break
  // 776:     !platform plat
  frame->slots[4] /* temp__1 */ = create_closure(entry__list_dependencies_4, 0);
  // 769: do: (-> break)
  // 770:   forever:
  // 771:     $plat supported_platforms(platform)
  // 772:     if plat.is_undefined break
  // 773:     inc &priority
  // 774:     !platform_specific_priority(supported_platform platform) priority
  // 775:     if plat == NONE break
  // 776:     !platform plat
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__do();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__list_dependencies_14(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 778: main_info.is_a_directory
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_info();
  result_count = 1;
  myself = get__is_a_directory();
  func = myself->type;
  frame->cont = cont__list_dependencies_15;
}
static void cont__list_dependencies_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 777: if
  // 778:   main_info.is_a_directory:
  // 779:     %mode LIB
  // 780:     if verbose: ewriteln "list dependencies for " main_filename
  // 781:     compile_modules main_filename behind(main_filename '/' -1)
  // 782:   :
  // 783:     compile_exe: (mod_filename mod_name)
  // 784:       if verbose: ewriteln "list dependencies for " mod_filename
  // 785:       compile_module mod_filename mod_name
  // 786:     writeln "runtime/linker.c"
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__list_dependencies_16;
  arguments->slots[2] = func__list_dependencies_23;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__list_dependencies_33;
}
static void entry__list_dependencies_16(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // return__1: 0
  frame->slots[0] /* return__1 */ = create_continuation();
  // _define %mode .
  define__mode(unique__LIB);
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 780: if verbose: ewriteln "list dependencies for " main_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = func__list_dependencies_17;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__list_dependencies_19;
}
static void entry__list_dependencies_17(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 780: ... ewriteln "list dependencies for " main_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7da4130a131d4ea3;
  arguments->slots[1] = get__main_filename();
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__list_dependencies_19(void) {
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
  frame->cont = cont__list_dependencies_20;
}
static void cont__list_dependencies_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 781: ... behind(main_filename '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__list_dependencies_21;
}
static void cont__list_dependencies_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 781: compile_modules main_filename behind(main_filename '/' -1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = func__compile_modules;
  func = myself->type;
  frame->cont = cont__list_dependencies_22;
}
static void cont__list_dependencies_22(void) {
  myself = frame->slots[0] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__list_dependencies_23(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 783: compile_exe: (mod_filename mod_name)
  // 784:   if verbose: ewriteln "list dependencies for " mod_filename
  // 785:   compile_module mod_filename mod_name
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__list_dependencies_24;
  result_count = 0;
  myself = func__compile_exe;
  func = myself->type;
  frame->cont = cont__list_dependencies_27;
}
static void entry__list_dependencies_24(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // mod_filename: 0
  // mod_name: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 784: ... : ewriteln "list dependencies for " mod_filename
  frame->slots[2] /* temp__1 */ = create_closure(entry__list_dependencies_25, 0);
  // 784: if verbose: ewriteln "list dependencies for " mod_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__list_dependencies_26;
}
static void entry__list_dependencies_25(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // mod_filename: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* mod_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 784: ... ewriteln "list dependencies for " mod_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7da4130a131d4ea3;
  arguments->slots[1] = frame->slots[0] /* mod_filename */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__list_dependencies_26(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 785: compile_module mod_filename mod_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = frame->slots[1] /* mod_name */;
  result_count = frame->caller_result_count;
  myself = func__compile_module;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__list_dependencies_27(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 786: writeln "runtime/linker.c"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__5aa0e0654e0a7d4d;
  result_count = 0;
  myself = get__writeln();
  func = myself->type;
  frame->cont = cont__list_dependencies_29;
}
static void cont__list_dependencies_29(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 787: writeln "runtime/memory.c"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7490e2a4ce0a3d6d;
  result_count = 0;
  myself = get__writeln();
  func = myself->type;
  frame->cont = cont__list_dependencies_31;
}
static void cont__list_dependencies_31(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 788: writeln "runtime/debugger.c"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__14e71717a54948b0;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__list_dependencies_33(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 789: $prefix_path current_path()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__current_path();
  func = myself->type;
  frame->cont = cont__list_dependencies_34;
}
static void cont__list_dependencies_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[0] /* prefix_path */, arguments->slots[0]);
  // 790: ... : ($filename)
  // 791:   without_prefix &filename prefix_path
  // 792:   without_prefix &filename '/'
  // 793:   writeln filename
  frame->slots[1] /* temp__1 */ = create_closure(entry__list_dependencies_35, 1);
  // 790: for_each dependencies: ($filename)
  // 791:   without_prefix &filename prefix_path
  // 792:   without_prefix &filename '/'
  // 793:   writeln filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._dependencies;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__build_codeblocks_project_2(void) {
  allocate_initialized_frame_gc(2, 13);
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
  // 797: $codeblocks_path string(mod_filename ".codeblocks")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = string__1ec9299aa0516bc0;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__build_codeblocks_project_4;
}
static void cont__build_codeblocks_project_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* codeblocks_path */, arguments->slots[0]);
  // 798: $info stat(codeblocks_path)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* codeblocks_path */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__build_codeblocks_project_5;
}
static void cont__build_codeblocks_project_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* info */, arguments->slots[0]);
  // 799: ... info.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* info */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__build_codeblocks_project_6;
}
static void cont__build_codeblocks_project_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 799: ... :
  // 800:   ewrite "
  // 801:     The directory "@(codeblocks_path)" already exists!
  frame->slots[11] /* temp__2 */ = create_closure(entry__build_codeblocks_project_7, 0);
  // 799: if info.is_defined:
  // 800:   ewrite "
  // 801:     The directory "@(codeblocks_path)" already exists!
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__1 */;
  arguments->slots[1] = frame->slots[11] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__build_codeblocks_project_11;
}
static void entry__build_codeblocks_project_7(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // codeblocks_path: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* codeblocks_path */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 800: ... "
  // 801:   The directory "@(codeblocks_path)" already exists!
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__3319ecea8934288e;
  arguments->slots[1] = frame->slots[0] /* codeblocks_path */;
  arguments->slots[2] = string__fb06ffd100386aab;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__build_codeblocks_project_10;
}
static void cont__build_codeblocks_project_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 800: ewrite "
  // 801:   The directory "@(codeblocks_path)" already exists!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewrite();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__build_codeblocks_project_11(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 802: ... : ewriteln "build Code::Blocks project in " codeblocks_path
  frame->slots[10] /* temp__1 */ = create_closure(entry__build_codeblocks_project_12, 0);
  // 802: if verbose: ewriteln "build Code::Blocks project in " codeblocks_path
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = frame->slots[10] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__build_codeblocks_project_14;
}
static void entry__build_codeblocks_project_12(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // codeblocks_path: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* codeblocks_path */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 802: ... ewriteln "build Code::Blocks project in " codeblocks_path
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__334eb97199863420;
  arguments->slots[1] = frame->slots[0] /* codeblocks_path */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__build_codeblocks_project_14(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 803: compile_module mod_filename mod_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = frame->slots[1] /* mod_name */;
  result_count = 0;
  myself = func__compile_module;
  func = myself->type;
  frame->cont = cont__build_codeblocks_project_15;
}
static void cont__build_codeblocks_project_15(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 804: show_file_list
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = func__show_file_list;
  func = myself->type;
  frame->cont = cont__build_codeblocks_project_16;
}
static void cont__build_codeblocks_project_16(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 805: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__build_codeblocks_project_17;
}
static void cont__build_codeblocks_project_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__2 */ = arguments->slots[0];
  // 805: ... truncate_until(main_filename '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[11] /* temp__2 */;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__build_codeblocks_project_18;
}
static void cont__build_codeblocks_project_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 805: $basename truncate_until(main_filename '/' -1) .without_suffix. ".sim"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__1 */;
  arguments->slots[1] = string__9e0aed8b5d287d54;
  result_count = 1;
  myself = get__without_suffix();
  func = myself->type;
  frame->cont = cont__build_codeblocks_project_19;
}
static void cont__build_codeblocks_project_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* basename */, arguments->slots[0]);
  // 806: $prefix_path current_path()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__current_path();
  func = myself->type;
  frame->cont = cont__build_codeblocks_project_20;
}
static void cont__build_codeblocks_project_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* prefix_path */, arguments->slots[0]);
  // 807: ... codeblocks_path .without_prefix. prefix_path
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* codeblocks_path */;
  arguments->slots[1] = frame->slots[5] /* prefix_path */;
  result_count = 1;
  myself = get__without_prefix();
  func = myself->type;
  frame->cont = cont__build_codeblocks_project_21;
}
static void cont__build_codeblocks_project_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 807: $depth count_occurrences(codeblocks_path .without_prefix. prefix_path '/')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__1 */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__count_occurrences();
  func = myself->type;
  frame->cont = cont__build_codeblocks_project_22;
}
static void cont__build_codeblocks_project_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* depth */, arguments->slots[0]);
  // 808: $path_prefix dup("../" depth)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__fa733c15f596be3;
  arguments->slots[1] = frame->slots[6] /* depth */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__build_codeblocks_project_24;
}
static void cont__build_codeblocks_project_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[7] /* path_prefix */, arguments->slots[0]);
  // 809: $cbp_filename string(codeblocks_path "/" basename ".cbp")
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* codeblocks_path */;
  arguments->slots[1] = string__578a5af303e9cce;
  arguments->slots[2] = frame->slots[4] /* basename */;
  arguments->slots[3] = string__9e0ae98b5d707d49;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__build_codeblocks_project_27;
}
static void cont__build_codeblocks_project_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[8] /* cbp_filename */, arguments->slots[0]);
  // 810: mkdir codeblocks_path
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* codeblocks_path */;
  result_count = 0;
  myself = var._mkdir;
  func = myself->type;
  frame->cont = cont__build_codeblocks_project_28;
}
static void cont__build_codeblocks_project_28(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 811: $$buf ""
  ((CELL *)frame->slots[9])->contents /* buf */ = empty_string;
  // 819: ... c_compiler()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__c_compiler();
  func = myself->type;
  frame->cont = cont__build_codeblocks_project_29;
}
static void cont__build_codeblocks_project_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__2 */ = arguments->slots[0];
  // 826: ... c_compiler()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__c_compiler();
  func = myself->type;
  frame->cont = cont__build_codeblocks_project_30;
}
static void cont__build_codeblocks_project_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__3 */ = arguments->slots[0];
  // 812: ... "
  // 813:   <?xml version="1.0" encoding="UTF-8" standalone="yes" ?>
  // 814:   <CodeBlocks_project_file>
  // 815:     <FileVersion major="1" minor="6" />
  // 816:     <Project>
  // 817:       <Option title="@(basename)" />
  // 818:       <Option pch_mode="2" />
  // 819:       <Option compiler="@(c_compiler())" />
  // 820:       <Build>
  // 821:         <Target title="debug">
  // ...
  argument_count = 9;
  arguments = node_p;
  arguments->slots[0] = string__ae2cb2959270f10e;
  arguments->slots[1] = frame->slots[4] /* basename */;
  arguments->slots[2] = string__1738f6ef1a56e70d;
  arguments->slots[3] = frame->slots[11] /* temp__2 */;
  arguments->slots[4] = string__f8758d9a72c26e31;
  arguments->slots[5] = frame->slots[4] /* basename */;
  arguments->slots[6] = string__b218c1a9e3db28b9;
  arguments->slots[7] = frame->slots[12] /* temp__3 */;
  arguments->slots[8] = string__b5364d63e076ecb2;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__build_codeblocks_project_36;
}
static void cont__build_codeblocks_project_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 812: write_to &buf "
  // 813:   <?xml version="1.0" encoding="UTF-8" standalone="yes" ?>
  // 814:   <CodeBlocks_project_file>
  // 815:     <FileVersion major="1" minor="6" />
  // 816:     <Project>
  // 817:       <Option title="@(basename)" />
  // 818:       <Option pch_mode="2" />
  // 819:       <Option compiler="@(c_compiler())" />
  // 820:       <Build>
  // 821:         <Target title="debug">
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[9])->contents /* buf */;
  arguments->slots[1] = frame->slots[10] /* temp__1 */;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__build_codeblocks_project_37;
}
static void cont__build_codeblocks_project_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[9])->contents /* buf */ = arguments->slots[0];
  // 833: ... : (filename)
  // 834:   write_to &buf "
  // 835:     @
  // 836:           <Add library="@(filename)" />
  frame->slots[10] /* temp__1 */ = create_closure(entry__build_codeblocks_project_38, 1);
  // 833: for_each libraries: (filename)
  // 834:   write_to &buf "
  // 835:     @
  // 836:           <Add library="@(filename)" />
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__libraries();
  arguments->slots[1] = frame->slots[10] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__build_codeblocks_project_43;
}
static void entry__build_codeblocks_project_38(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // filename: 0
  // buf: 1
  frame->slots[1] = myself->closure.frame->slots[9]; /* buf */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 834: ... "
  // 835:   @
  // 836:         <Add library="@(filename)" />
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__86909867946dc27b;
  arguments->slots[1] = frame->slots[0] /* filename */;
  arguments->slots[2] = string__ca5af8c3e83c305d;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__build_codeblocks_project_41;
}
static void cont__build_codeblocks_project_41(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 834: write_to &buf "
  // 835:   @
  // 836:         <Add library="@(filename)" />
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* buf */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__build_codeblocks_project_42;
}
static void cont__build_codeblocks_project_42(void) {
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
static void cont__build_codeblocks_project_43(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 837: ... "
  // 838:   @
  // 839:   
  // 840:       </Linker>
  // 841:       <Compiler>
  // 842:         <Add option="-Wall" />
  // 843:         <Add directory=".." />
  // 844:       </Compiler>
  // 845:       <Unit filename="@(path_prefix)runtime/common.h" />
  // 846:       <Unit filename="@(path_prefix)runtime/linker.h" />
  // ...
  argument_count = 11;
  arguments = node_p;
  arguments->slots[0] = string__eff3cb070eeaf9ca;
  arguments->slots[1] = frame->slots[7] /* path_prefix */;
  arguments->slots[2] = string__6ec73fb9d26dad91;
  arguments->slots[3] = frame->slots[7] /* path_prefix */;
  arguments->slots[4] = string__62c73cb6d2cd6da9;
  arguments->slots[5] = frame->slots[7] /* path_prefix */;
  arguments->slots[6] = string__df3541444f9afcd3;
  arguments->slots[7] = frame->slots[7] /* path_prefix */;
  arguments->slots[8] = string__6a94fbaaffa1060a;
  arguments->slots[9] = frame->slots[7] /* path_prefix */;
  arguments->slots[10] = string__3820eb4b885b519f;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__build_codeblocks_project_50;
}
static void cont__build_codeblocks_project_50(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 837: write_to &buf "
  // 838:   @
  // 839:   
  // 840:       </Linker>
  // 841:       <Compiler>
  // 842:         <Add option="-Wall" />
  // 843:         <Add directory=".." />
  // 844:       </Compiler>
  // 845:       <Unit filename="@(path_prefix)runtime/common.h" />
  // 846:       <Unit filename="@(path_prefix)runtime/linker.h" />
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[9])->contents /* buf */;
  arguments->slots[1] = frame->slots[10] /* temp__1 */;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__build_codeblocks_project_51;
}
static void cont__build_codeblocks_project_51(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[9])->contents /* buf */ = arguments->slots[0];
  // 856: ... : ($filename)
  // 857:   without_prefix &filename prefix_path
  // 858:   without_prefix &filename '/'
  // 859:   write_to &buf "
  // 860:     @
  // 861:     
  // 862:         <Unit filename="@(path_prefix)@(filename)">
  // 863:           <Option compilerVar="CC" />
  // 864:         </Unit>
  frame->slots[10] /* temp__1 */ = create_closure(entry__build_codeblocks_project_52, 1);
  // 856: for_each c_sources: ($filename)
  // 857:   without_prefix &filename prefix_path
  // 858:   without_prefix &filename '/'
  // 859:   write_to &buf "
  // 860:     @
  // 861:     
  // 862:         <Unit filename="@(path_prefix)@(filename)">
  // 863:           <Option compilerVar="CC" />
  // 864:         </Unit>
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._c_sources;
  arguments->slots[1] = frame->slots[10] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__build_codeblocks_project_59;
}
static void entry__build_codeblocks_project_52(void) {
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
  // 857: without_prefix &filename prefix_path
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* filename */;
  arguments->slots[1] = frame->slots[1] /* prefix_path */;
  result_count = 1;
  myself = get__without_prefix();
  func = myself->type;
  frame->cont = cont__build_codeblocks_project_53;
}
static void cont__build_codeblocks_project_53(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* filename */ = arguments->slots[0];
  // 858: without_prefix &filename '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* filename */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__without_prefix();
  func = myself->type;
  frame->cont = cont__build_codeblocks_project_54;
}
static void cont__build_codeblocks_project_54(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* filename */ = arguments->slots[0];
  // 859: ... "
  // 860:   @
  // 861:   
  // 862:       <Unit filename="@(path_prefix)@(filename)">
  // 863:         <Option compilerVar="CC" />
  // 864:       </Unit>
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__5ce0e5ba1304a164;
  arguments->slots[1] = frame->slots[3] /* path_prefix */;
  arguments->slots[2] = ((CELL *)frame->slots[0])->contents /* filename */;
  arguments->slots[3] = string__eddc311fc1bd57cd;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__build_codeblocks_project_57;
}
static void cont__build_codeblocks_project_57(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 859: write_to &buf "
  // 860:   @
  // 861:   
  // 862:       <Unit filename="@(path_prefix)@(filename)">
  // 863:         <Option compilerVar="CC" />
  // 864:       </Unit>
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* buf */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__build_codeblocks_project_58;
}
static void cont__build_codeblocks_project_58(void) {
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
static void cont__build_codeblocks_project_59(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 865: write_to &buf "
  // 866:       <Extensions>
  // 867:         <code_completion />
  // 868:         <debugger />
  // 869:       </Extensions>
  // 870:     </Project>
  // 871:   </CodeBlocks_project_file>
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[9])->contents /* buf */;
  arguments->slots[1] = string__1d1cedd7cdd611c4;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__build_codeblocks_project_61;
}
static void cont__build_codeblocks_project_61(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[9])->contents /* buf */ = arguments->slots[0];
  // 872: save cbp_filename buf
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* cbp_filename */;
  arguments->slots[1] = ((CELL *)frame->slots[9])->contents /* buf */;
  result_count = frame->caller_result_count;
  myself = get__save();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__build_codeblocks_project(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 796: compile_exe: (mod_filename mod_name)
  // 797:   $codeblocks_path string(mod_filename ".codeblocks")
  // 798:   $info stat(codeblocks_path)
  // 799:   if info.is_defined:
  // 800:     ewrite "
  // 801:       The directory "@(codeblocks_path)" already exists!
  // 802:   if verbose: ewriteln "build Code::Blocks project in " codeblocks_path
  // 803:   compile_module mod_filename mod_name
  // 804:   show_file_list
  // 805:   $basename truncate_until(main_filename '/' -1) .without_suffix. ".sim"
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__build_codeblocks_project_2;
  result_count = frame->caller_result_count;
  myself = func__compile_exe;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__build_library(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // return__1: 0
  frame->slots[0] /* return__1 */ = create_continuation();
  // _define %mode .
  define__mode(unique__LIB);
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 875: ... action == "simrun"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._action;
  arguments->slots[1] = string__421f52c90112c2b9;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__build_library_3;
}
static void cont__build_library_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 875: if action == "simrun": Error "Cannot run a directory!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__build_library_4;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__build_library_6;
}
static void entry__build_library_4(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 875: ... Error "Cannot run a directory!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__c84d9037a41e8f73;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__build_library_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 877: cond
  // 878:   -> do_extract_documentation:
  // 879:     $$doc_libraries list(main_filename)
  // 880:     for_each additional_libraries: (library)
  // 881:       push &doc_libraries fullname(library)
  // 882:     extract_documentation doc_libraries
  // 883:   -> do_extract_exports:
  // 884:     $$doc_libraries list(main_filename)
  // 885:     for_each additional_libraries: (library)
  // 886:       push &doc_libraries fullname(library)
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = func__build_library_7;
  arguments->slots[1] = func__build_library_14;
  arguments->slots[2] = func__build_library_21;
  result_count = frame->caller_result_count;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__build_library_103;
}
static void entry__build_library_101(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // err: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* err */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 968: ... err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* err */;
  result_count = 1;
  myself = get__from_utf8();
  func = myself->type;
  frame->cont = cont__build_library_102;
}
static void cont__build_library_102(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 968: ... Error err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__build_library_96(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // err: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* err */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 957: ... err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* err */;
  result_count = 1;
  myself = get__from_utf8();
  func = myself->type;
  frame->cont = cont__build_library_97;
}
static void cont__build_library_97(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 957: ... Error err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__build_library_87(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // err: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* err */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 943: ... err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* err */;
  result_count = 1;
  myself = get__from_utf8();
  func = myself->type;
  frame->cont = cont__build_library_88;
}
static void cont__build_library_88(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 943: ... Error err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__build_library_80(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // err: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* err */
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
  frame->cont = cont__build_library_81;
}
static void cont__build_library_81(void) {
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
static void entry__build_library_74(void) {
  allocate_initialized_frame_gc(3, 8);
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
  // 927: "-Wl,-soname,libsim-@(base_filename)@(so_version).so.@(MAJOR)"
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__f5937b2655b3cd24;
  arguments->slots[1] = frame->slots[0] /* base_filename */;
  arguments->slots[2] = frame->slots[1] /* so_version */;
  arguments->slots[3] = string__9e0aed8b5d187d17;
  arguments->slots[4] = var._MAJOR;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__build_library_76;
}
static void cont__build_library_76(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 928: library_paths_and_file_list()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = func__library_paths_and_file_list;
  func = myself->type;
  frame->cont = cont__build_library_77;
}
static void cont__build_library_77(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 921: CC
  // 922:   $_out
  // 923:   $err
  // 924:   $success
  // 925:   ld_options*
  // 926:   "-shared"
  // 927:   "-Wl,-soname,libsim-@(base_filename)@(so_version).so.@(MAJOR)"
  // 928:   library_paths_and_file_list()*
  // 929:   "-o"
  // 930:   lib_filename
  argument_count = 0;
  arguments = node_p;
  unfold(var._ld_options);
  arguments->slots[argument_count++] = string__b130095b1592409e;
  arguments->slots[argument_count++] = frame->slots[6] /* temp__1 */;
  unfold(frame->slots[7] /* temp__2 */);
  arguments->slots[argument_count++] = string__2d7981f4e6602baa;
  arguments->slots[argument_count++] = frame->slots[2] /* lib_filename */;
  result_count = 3;
  myself = func__CC;
  func = myself->type;
  frame->cont = cont__build_library_79;
}
static void cont__build_library_79(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* out */, arguments->slots[0]);
  initialize_future(frame->slots[4] /* err */, arguments->slots[1]);
  initialize_future(frame->slots[5] /* success */, arguments->slots[2]);
  // 931: ... : Error err.from_utf8
  frame->slots[6] /* temp__1 */ = create_closure(entry__build_library_80, 0);
  // 931: unless success: Error err.from_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* success */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__build_library_82(void) {
  allocate_initialized_frame_gc(1, 6);
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
  // 939: library_paths_and_file_list()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = func__library_paths_and_file_list;
  func = myself->type;
  frame->cont = cont__build_library_83;
}
static void cont__build_library_83(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 940: "-lsim-@(MAJOR)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7e1f542601d292fa;
  arguments->slots[1] = var._MAJOR;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__build_library_85;
}
static void cont__build_library_85(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 933: CC
  // 934:   $_out
  // 935:   $err
  // 936:   $success
  // 937:   ld_options*
  // 938:   "-shared"
  // 939:   library_paths_and_file_list()*
  // 940:   "-lsim-@(MAJOR)"
  // 941:   "-o"
  // 942:   lib_filename
  argument_count = 0;
  arguments = node_p;
  unfold(var._ld_options);
  arguments->slots[argument_count++] = string__b130095b1592409e;
  unfold(frame->slots[4] /* temp__1 */);
  arguments->slots[argument_count++] = frame->slots[5] /* temp__2 */;
  arguments->slots[argument_count++] = string__2d7981f4e6602baa;
  arguments->slots[argument_count++] = frame->slots[0] /* lib_filename */;
  result_count = 3;
  myself = func__CC;
  func = myself->type;
  frame->cont = cont__build_library_86;
}
static void cont__build_library_86(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* out */, arguments->slots[0]);
  initialize_future(frame->slots[2] /* err */, arguments->slots[1]);
  initialize_future(frame->slots[3] /* success */, arguments->slots[2]);
  // 943: ... : Error err.from_utf8
  frame->slots[4] /* temp__1 */ = create_closure(entry__build_library_87, 0);
  // 943: unless success: Error err.from_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* success */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__build_library_89(void) {
  allocate_initialized_frame_gc(3, 9);
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
  // 950: ... "
  // 951:   -Wl,-install_name,libsim-@(base_filename)@(so_version)-@(MAJOR)@
  // 952:   .dylib@
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = string__33820b08e3b95a2a;
  arguments->slots[1] = frame->slots[0] /* base_filename */;
  arguments->slots[2] = frame->slots[1] /* so_version */;
  arguments->slots[3] = string__578a5af303e9ccc;
  arguments->slots[4] = var._MAJOR;
  arguments->slots[5] = string__6a1f556781f212b5;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__build_library_91;
}
static void cont__build_library_91(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 953: library_paths_and_file_list()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = func__library_paths_and_file_list;
  func = myself->type;
  frame->cont = cont__build_library_92;
}
static void cont__build_library_92(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 954: "-lsim-@(MAJOR)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7e1f542601d292fa;
  arguments->slots[1] = var._MAJOR;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__build_library_93;
}
static void cont__build_library_93(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__3 */ = arguments->slots[0];
  // 945: CC
  // 946:   $_out
  // 947:   $err
  // 948:   $success
  // 949:   ld_options*
  // 950:   "-dynamiclib" "
  // 951:     -Wl,-install_name,libsim-@(base_filename)@(so_version)-@(MAJOR)@
  // 952:     .dylib@
  // 953:   library_paths_and_file_list()*
  // 954:   "-lsim-@(MAJOR)"
  // ...
  argument_count = 0;
  arguments = node_p;
  unfold(var._ld_options);
  arguments->slots[argument_count++] = string__c6d9125d36413a91;
  arguments->slots[argument_count++] = frame->slots[6] /* temp__1 */;
  unfold(frame->slots[7] /* temp__2 */);
  arguments->slots[argument_count++] = frame->slots[8] /* temp__3 */;
  arguments->slots[argument_count++] = string__2d7981f4e6602baa;
  arguments->slots[argument_count++] = frame->slots[2] /* lib_filename */;
  result_count = 3;
  myself = func__CC;
  func = myself->type;
  frame->cont = cont__build_library_95;
}
static void cont__build_library_95(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* out */, arguments->slots[0]);
  initialize_future(frame->slots[4] /* err */, arguments->slots[1]);
  initialize_future(frame->slots[5] /* success */, arguments->slots[2]);
  // 957: ... : Error err.from_utf8
  frame->slots[6] /* temp__1 */ = create_closure(entry__build_library_96, 0);
  // 957: unless success: Error err.from_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* success */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__build_library_98(void) {
  allocate_initialized_frame_gc(1, 5);
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
  // 965: library_paths_and_file_list()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = func__library_paths_and_file_list;
  func = myself->type;
  frame->cont = cont__build_library_99;
}
static void cont__build_library_99(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 959: CC
  // 960:   $_out
  // 961:   $err
  // 962:   $success
  // 963:   ld_options*
  // 964:   "-shared"
  // 965:   library_paths_and_file_list()*
  // 966:   "-o"
  // 967:   lib_filename
  argument_count = 0;
  arguments = node_p;
  unfold(var._ld_options);
  arguments->slots[argument_count++] = string__b130095b1592409e;
  unfold(frame->slots[4] /* temp__1 */);
  arguments->slots[argument_count++] = string__2d7981f4e6602baa;
  arguments->slots[argument_count++] = frame->slots[0] /* lib_filename */;
  result_count = 3;
  myself = func__CC;
  func = myself->type;
  frame->cont = cont__build_library_100;
}
static void cont__build_library_100(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* out */, arguments->slots[0]);
  initialize_future(frame->slots[2] /* err */, arguments->slots[1]);
  initialize_future(frame->slots[3] /* success */, arguments->slots[2]);
  // 968: ... : Error err.from_utf8
  frame->slots[4] /* temp__1 */ = create_closure(entry__build_library_101, 0);
  // 968: unless success: Error err.from_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* success */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__build_library_68(void) {
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
  // 918: if verbose: ewriteln "linking dynamic library"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = func__build_library_69;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__build_library_71;
}
static void entry__build_library_69(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 918: ... ewriteln "linking dynamic library"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__b9aef2a4efc3a1a8;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__build_library_71(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 919: ... operating_system()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__operating_system();
  func = myself->type;
  frame->cont = cont__build_library_72;
}
static void cont__build_library_72(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 920: "linux", "bsd"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__585ae883ea60d02f;
  arguments->slots[1] = string__fa720c15db16ba8;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__build_library_73;
}
static void cont__build_library_73(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 920: ... :
  // 921:   CC
  // 922:     $_out
  // 923:     $err
  // 924:     $success
  // 925:     ld_options*
  // 926:     "-shared"
  // 927:     "-Wl,-soname,libsim-@(base_filename)@(so_version).so.@(MAJOR)"
  // 928:     library_paths_and_file_list()*
  // 929:     "-o"
  // ...
  frame->slots[5] /* temp__3 */ = create_closure(entry__build_library_74, 0);
  // 932: ... :
  // 933:   CC
  // 934:     $_out
  // 935:     $err
  // 936:     $success
  // 937:     ld_options*
  // 938:     "-shared"
  // 939:     library_paths_and_file_list()*
  // 940:     "-lsim-@(MAJOR)"
  // 941:     "-o"
  // ...
  frame->slots[6] /* temp__4 */ = create_closure(entry__build_library_82, 0);
  // 944: ... :
  // 945:   CC
  // 946:     $_out
  // 947:     $err
  // 948:     $success
  // 949:     ld_options*
  // 950:     "-dynamiclib" "
  // 951:       -Wl,-install_name,libsim-@(base_filename)@(so_version)-@(MAJOR)@
  // 952:       .dylib@
  // 953:     library_paths_and_file_list()*
  // ...
  frame->slots[7] /* temp__5 */ = create_closure(entry__build_library_89, 0);
  // 958: :
  // 959:   CC
  // 960:     $_out
  // 961:     $err
  // 962:     $success
  // 963:     ld_options*
  // 964:     "-shared"
  // 965:     library_paths_and_file_list()*
  // 966:     "-o"
  // 967:     lib_filename
  // ...
  frame->slots[8] /* temp__6 */ = create_closure(entry__build_library_98, 0);
  // 919: case operating_system()
  // 920:   "linux", "bsd":
  // 921:     CC
  // 922:       $_out
  // 923:       $err
  // 924:       $success
  // 925:       ld_options*
  // 926:       "-shared"
  // 927:       "-Wl,-soname,libsim-@(base_filename)@(so_version).so.@(MAJOR)"
  // 928:       library_paths_and_file_list()*
  // ...
  argument_count = 8;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = frame->slots[5] /* temp__3 */;
  arguments->slots[3] = string__561f538101f3c2b9;
  arguments->slots[4] = frame->slots[6] /* temp__4 */;
  arguments->slots[5] = string__7c1f538281f242b9;
  arguments->slots[6] = frame->slots[7] /* temp__5 */;
  arguments->slots[7] = frame->slots[8] /* temp__6 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__build_library_15(void) {
  allocate_initialized_frame_gc(0, 2);
  // slot allocations:
  // doc_libraries: 0
  frame->slots[0] /* doc_libraries */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 884: $$doc_libraries list(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__build_library_16;
}
static void cont__build_library_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* doc_libraries */ = arguments->slots[0];
  // 885: ... : (library)
  // 886:   push &doc_libraries fullname(library)
  frame->slots[1] /* temp__1 */ = create_closure(entry__build_library_17, 1);
  // 885: for_each additional_libraries: (library)
  // 886:   push &doc_libraries fullname(library)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._additional_libraries;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__build_library_20;
}
static void entry__build_library_17(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // library: 0
  // doc_libraries: 1
  frame->slots[1] = myself->closure.frame->slots[0]; /* doc_libraries */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 886: ... fullname(library)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* library */;
  result_count = 1;
  myself = get__fullname();
  func = myself->type;
  frame->cont = cont__build_library_18;
}
static void cont__build_library_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 886: push &doc_libraries fullname(library)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* doc_libraries */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__build_library_19;
}
static void cont__build_library_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* doc_libraries */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__build_library_20(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 887: extract_exports doc_libraries
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* doc_libraries */;
  result_count = frame->caller_result_count;
  myself = get__extract_exports();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__build_library_8(void) {
  allocate_initialized_frame_gc(0, 2);
  // slot allocations:
  // doc_libraries: 0
  frame->slots[0] /* doc_libraries */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 879: $$doc_libraries list(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__build_library_9;
}
static void cont__build_library_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* doc_libraries */ = arguments->slots[0];
  // 880: ... : (library)
  // 881:   push &doc_libraries fullname(library)
  frame->slots[1] /* temp__1 */ = create_closure(entry__build_library_10, 1);
  // 880: for_each additional_libraries: (library)
  // 881:   push &doc_libraries fullname(library)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._additional_libraries;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__build_library_13;
}
static void entry__build_library_10(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // library: 0
  // doc_libraries: 1
  frame->slots[1] = myself->closure.frame->slots[0]; /* doc_libraries */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 881: ... fullname(library)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* library */;
  result_count = 1;
  myself = get__fullname();
  func = myself->type;
  frame->cont = cont__build_library_11;
}
static void cont__build_library_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 881: push &doc_libraries fullname(library)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* doc_libraries */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__build_library_12;
}
static void cont__build_library_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* doc_libraries */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__build_library_13(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 882: extract_documentation doc_libraries
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* doc_libraries */;
  result_count = frame->caller_result_count;
  myself = get__extract_documentation();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__build_library_7(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 878: -> do_extract_documentation:
  // 879:   $$doc_libraries list(main_filename)
  // 880:   for_each additional_libraries: (library)
  // 881:     push &doc_libraries fullname(library)
  // 882:   extract_documentation doc_libraries
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_extract_documentation();
  arguments->slots[1] = func__build_library_8;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__build_library_14(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 883: -> do_extract_exports:
  // 884:   $$doc_libraries list(main_filename)
  // 885:   for_each additional_libraries: (library)
  // 886:     push &doc_libraries fullname(library)
  // 887:   extract_exports doc_libraries
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_extract_exports;
  arguments->slots[1] = func__build_library_15;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__build_library_21(void) {
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
  // 889: $$version ""
  ((CELL *)frame->slots[0])->contents /* version */ = empty_string;
  // 890: $version_filename string(main_filename "/VERSION")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  arguments->slots[1] = string__84ca78485aeb98e;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__build_library_23;
}
static void cont__build_library_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* version_filename */, arguments->slots[0]);
  // 891: ... file_exists(version_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* version_filename */;
  result_count = 1;
  myself = get__file_exists();
  func = myself->type;
  frame->cont = cont__build_library_24;
}
static void cont__build_library_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 891: ... :
  // 892:   !version string('-' load(version_filename).trim)
  frame->slots[6] /* temp__2 */ = create_closure(entry__build_library_25, 0);
  // 891: if file_exists(version_filename):
  // 892:   !version string('-' load(version_filename).trim)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__build_library_29;
}
static void entry__build_library_25(void) {
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
  // 892: ... load(version_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* version_filename */;
  result_count = 1;
  myself = get__load();
  func = myself->type;
  frame->cont = cont__build_library_26;
}
static void cont__build_library_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 892: ... load(version_filename).trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__build_library_27;
}
static void cont__build_library_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 892: !version string('-' load(version_filename).trim)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__45;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__build_library_28;
}
static void cont__build_library_28(void) {
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
static void cont__build_library_29(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 893: $so_version version .truncate_from. '.'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* version */;
  arguments->slots[1] = character__46;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__build_library_30;
}
static void cont__build_library_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* so_version */, arguments->slots[0]);
  // 894: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__build_library_31;
}
static void cont__build_library_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 894: $base_filename truncate_until(main_filename '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__build_library_32;
}
static void cont__build_library_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* base_filename */, arguments->slots[0]);
  // 898: operating_system()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__operating_system();
  func = myself->type;
  frame->cont = cont__build_library_33;
}
static void cont__build_library_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 899: "linux", "bsd"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__585ae883ea60d02f;
  arguments->slots[1] = string__fa720c15db16ba8;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__build_library_34;
}
static void cont__build_library_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 900: -> string("libsim-" base_filename version ".so.@(MAJOR)")
  frame->slots[7] /* temp__3 */ = create_closure(entry__build_library_35, 0);
  // 902: -> string("libsim-" base_filename version "-@(MAJOR).dll")
  frame->slots[8] /* temp__4 */ = create_closure(entry__build_library_39, 0);
  // 904: -> string("libsim-" base_filename version "-@(MAJOR).dylib")
  frame->slots[9] /* temp__5 */ = create_closure(entry__build_library_43, 0);
  // 905: -> string("libsim-" base_filename version ".so.@(MAJOR)")
  frame->slots[10] /* temp__6 */ = create_closure(entry__build_library_47, 0);
  // 896: $lib_filename
  // 897:   case
  // 898:     operating_system()
  // 899:     "linux", "bsd"
  // 900:     -> string("libsim-" base_filename version ".so.@(MAJOR)")
  // 901:     "cygwin"
  // 902:     -> string("libsim-" base_filename version "-@(MAJOR).dll")
  // 903:     "darwin"
  // 904:     -> string("libsim-" base_filename version "-@(MAJOR).dylib")
  // 905:     -> string("libsim-" base_filename version ".so.@(MAJOR)")
  argument_count = 8;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  arguments->slots[2] = frame->slots[7] /* temp__3 */;
  arguments->slots[3] = string__561f538101f3c2b9;
  arguments->slots[4] = frame->slots[8] /* temp__4 */;
  arguments->slots[5] = string__7c1f538281f242b9;
  arguments->slots[6] = frame->slots[9] /* temp__5 */;
  arguments->slots[7] = frame->slots[10] /* temp__6 */;
  result_count = 1;
  myself = get__case();
  func = myself->type;
  frame->cont = cont__build_library_52;
}
static void entry__build_library_35(void) {
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
  // 900: ... ".so.@(MAJOR)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__9e0aed8b5d187d17;
  arguments->slots[1] = var._MAJOR;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__build_library_36;
}
static void cont__build_library_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 900: ... string("libsim-" base_filename version ".so.@(MAJOR)")
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__94340f9615d2e0d7;
  arguments->slots[1] = frame->slots[0] /* base_filename */;
  arguments->slots[2] = ((CELL *)frame->slots[1])->contents /* version */;
  arguments->slots[3] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__build_library_38;
}
static void cont__build_library_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 900: -> string("libsim-" base_filename version ".so.@(MAJOR)")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__build_library_39(void) {
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
  // 902: ... "-@(MAJOR).dll"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9ccc;
  arguments->slots[1] = var._MAJOR;
  arguments->slots[2] = string__9e0ae84b5d007d55;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__build_library_41;
}
static void cont__build_library_41(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 902: ... string("libsim-" base_filename version "-@(MAJOR).dll")
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__94340f9615d2e0d7;
  arguments->slots[1] = frame->slots[0] /* base_filename */;
  arguments->slots[2] = ((CELL *)frame->slots[1])->contents /* version */;
  arguments->slots[3] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__build_library_42;
}
static void cont__build_library_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 902: -> string("libsim-" base_filename version "-@(MAJOR).dll")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__build_library_43(void) {
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
  // 904: ... "-@(MAJOR).dylib"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9ccc;
  arguments->slots[1] = var._MAJOR;
  arguments->slots[2] = string__6a1f556781f212b5;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__build_library_45;
}
static void cont__build_library_45(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 904: ... string("libsim-" base_filename version "-@(MAJOR).dylib")
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__94340f9615d2e0d7;
  arguments->slots[1] = frame->slots[0] /* base_filename */;
  arguments->slots[2] = ((CELL *)frame->slots[1])->contents /* version */;
  arguments->slots[3] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__build_library_46;
}
static void cont__build_library_46(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 904: -> string("libsim-" base_filename version "-@(MAJOR).dylib")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__build_library_47(void) {
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
  // 905: ... ".so.@(MAJOR)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__9e0aed8b5d187d17;
  arguments->slots[1] = var._MAJOR;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__build_library_48;
}
static void cont__build_library_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 905: ... string("libsim-" base_filename version ".so.@(MAJOR)")
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__94340f9615d2e0d7;
  arguments->slots[1] = frame->slots[0] /* base_filename */;
  arguments->slots[2] = ((CELL *)frame->slots[1])->contents /* version */;
  arguments->slots[3] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__build_library_49;
}
static void cont__build_library_49(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 905: -> string("libsim-" base_filename version ".so.@(MAJOR)")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__build_library_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* lib_filename */, arguments->slots[0]);
  // 907: ... : ewriteln "build library " lib_filename
  frame->slots[5] /* temp__1 */ = create_closure(entry__build_library_53, 0);
  // 907: if verbose: ewriteln "build library " lib_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__build_library_55;
}
static void entry__build_library_53(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // lib_filename: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* lib_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 907: ... ewriteln "build library " lib_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__822587b3f48532f5;
  arguments->slots[1] = frame->slots[0] /* lib_filename */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__build_library_55(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 908: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__build_library_56;
}
static void cont__build_library_56(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 908: ... behind(main_filename '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__build_library_57;
}
static void cont__build_library_57(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 908: compile_modules main_filename behind(main_filename '/' -1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = func__compile_modules;
  func = myself->type;
  frame->cont = cont__build_library_58;
}
static void cont__build_library_58(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 909: ... :
  // 910:   $info stat(lib_filename)
  // 911:   if
  // 912:     ||
  // 913:       info.is_undefined
  // 914:       last_modification_time > modification_time_of(info)
  // 915:     :
  // 916:       !do_link true
  frame->slots[5] /* temp__1 */ = create_closure(entry__build_library_59, 0);
  // 909: unless do_link:
  // 910:   $info stat(lib_filename)
  // 911:   if
  // 912:     ||
  // 913:       info.is_undefined
  // 914:       last_modification_time > modification_time_of(info)
  // 915:     :
  // 916:       !do_link true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_link();
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__build_library_67;
}
static void entry__build_library_66(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 916: !do_link true
  set__do_link(get__true());
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__build_library_59(void) {
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
  // 910: $info stat(lib_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* lib_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__build_library_60;
}
static void cont__build_library_60(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* info */, arguments->slots[0]);
  // 913: info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__build_library_61;
}
static void cont__build_library_61(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 914: last_modification_time > modification_time_of(info)
  frame->slots[4] /* temp__3 */ = create_closure(entry__build_library_62, 0);
  // 912: ||
  // 913:   info.is_undefined
  // 914:   last_modification_time > modification_time_of(info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__build_library_65;
}
static void entry__build_library_62(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // info: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 914: ... modification_time_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__build_library_63;
}
static void cont__build_library_63(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 914: last_modification_time > modification_time_of(info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = get__last_modification_time();
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__build_library_64;
}
static void cont__build_library_64(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 914: last_modification_time > modification_time_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__build_library_65(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 911: if
  // 912:   ||
  // 913:     info.is_undefined
  // 914:     last_modification_time > modification_time_of(info)
  // 915:   :
  // 916:     !do_link true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = func__build_library_66;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__build_library_67(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 917: ... :
  // 918:   if verbose: ewriteln "linking dynamic library"
  // 919:   case operating_system()
  // 920:     "linux", "bsd":
  // 921:       CC
  // 922:         $_out
  // 923:         $err
  // 924:         $success
  // 925:         ld_options*
  // 926:         "-shared"
  // ...
  frame->slots[5] /* temp__1 */ = create_closure(entry__build_library_68, 0);
  // 917: if do_link:
  // 918:   if verbose: ewriteln "linking dynamic library"
  // 919:   case operating_system()
  // 920:     "linux", "bsd":
  // 921:       CC
  // 922:         $_out
  // 923:         $err
  // 924:         $success
  // 925:         ld_options*
  // 926:         "-shared"
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
static void cont__build_library_103(void) {
  myself = frame->slots[0] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__maybe_compile_c_file_18(void) {
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
  // 983: ... : ewriteln "compiling runtime module @(filename)"
  frame->slots[3] /* temp__1 */ = create_closure(entry__maybe_compile_c_file_19, 0);
  // 983: if verbose: ewriteln "compiling runtime module @(filename)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__maybe_compile_c_file_22;
}
static void entry__maybe_compile_c_file_19(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // filename: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 983: ... "compiling runtime module @(filename)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__74150357c2230d49;
  arguments->slots[1] = frame->slots[0] /* filename */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__maybe_compile_c_file_21;
}
static void cont__maybe_compile_c_file_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 983: ... ewriteln "compiling runtime module @(filename)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__maybe_compile_c_file_22(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 984: compile_c c_filename o_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* c_filename */;
  arguments->slots[1] = frame->slots[2] /* o_filename */;
  result_count = frame->caller_result_count;
  myself = func__compile_c;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__maybe_compile_c_file(void) {
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
  // 971: $c_filename string(filename ".c")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  arguments->slots[1] = string__2d7981f4e6782ba6;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__maybe_compile_c_file_2;
}
static void cont__maybe_compile_c_file_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* c_filename */, arguments->slots[0]);
  // 972: $o_filename string(filename ".o")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  arguments->slots[1] = string__2d7981f4e6782baa;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__maybe_compile_c_file_3;
}
static void cont__maybe_compile_c_file_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* o_filename */, arguments->slots[0]);
  // 973: $c_info stat(c_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* c_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__maybe_compile_c_file_4;
}
static void cont__maybe_compile_c_file_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* c_info */, arguments->slots[0]);
  // 974: ... c_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* c_info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__maybe_compile_c_file_5;
}
static void cont__maybe_compile_c_file_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 974: ... :
  // 975:   Error "
  // 976:     @quot;@(c_filename)" does not exist!
  frame->slots[6] /* temp__2 */ = create_closure(entry__maybe_compile_c_file_6, 0);
  // 974: if c_info.is_undefined:
  // 975:   Error "
  // 976:     @quot;@(c_filename)" does not exist!
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__maybe_compile_c_file_10;
}
static void entry__maybe_compile_c_file_6(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // c_filename: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* c_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 975: ... "
  // 976:   @quot;@(c_filename)" does not exist!
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9cc3;
  arguments->slots[1] = frame->slots[0] /* c_filename */;
  arguments->slots[2] = string__7ef24f7974bbce09;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__maybe_compile_c_file_9;
}
static void cont__maybe_compile_c_file_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 975: Error "
  // 976:   @quot;@(c_filename)" does not exist!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__maybe_compile_c_file_10(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 977: $o_info stat(o_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* o_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__maybe_compile_c_file_11;
}
static void cont__maybe_compile_c_file_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* o_info */, arguments->slots[0]);
  // 980: o_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* o_info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__maybe_compile_c_file_12;
}
static void cont__maybe_compile_c_file_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 981: modification_time_of(c_info) > modification_time_of(o_info)
  frame->slots[7] /* temp__3 */ = create_closure(entry__maybe_compile_c_file_13, 0);
  // 979: ||
  // 980:   o_info.is_undefined
  // 981:   modification_time_of(c_info) > modification_time_of(o_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__maybe_compile_c_file_17;
}
static void entry__maybe_compile_c_file_13(void) {
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
  // 981: ... modification_time_of(o_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* o_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__maybe_compile_c_file_14;
}
static void cont__maybe_compile_c_file_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 981: modification_time_of(c_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* c_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__maybe_compile_c_file_15;
}
static void cont__maybe_compile_c_file_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 981: modification_time_of(c_info) > modification_time_of(o_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__maybe_compile_c_file_16;
}
static void cont__maybe_compile_c_file_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 981: modification_time_of(c_info) > modification_time_of(o_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__maybe_compile_c_file_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 982: :
  // 983:   if verbose: ewriteln "compiling runtime module @(filename)"
  // 984:   compile_c c_filename o_filename
  frame->slots[8] /* temp__4 */ = create_closure(entry__maybe_compile_c_file_18, 0);
  // 978: if
  // 979:   ||
  // 980:     o_info.is_undefined
  // 981:     modification_time_of(c_info) > modification_time_of(o_info)
  // 982:   :
  // 983:     if verbose: ewriteln "compiling runtime module @(filename)"
  // 984:     compile_c c_filename o_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__format_number(void) {
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
  // 994: to_string &val
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* val */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__format_number_2;
}
static void cont__format_number_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* val */ = arguments->slots[0];
  // 995: $$ac 0
  ((CELL *)frame->slots[3])->contents /* ac */ = number__0;
  //  996: ... : (-> break)
  //  997:   for_each val: (i chr)
  //  998:     if chr == '.':
  //  999:       !ac length_of(val)-i
  // 1000:       if n > i-1: append dup(" " n-(i-1)) &val
  // 1001:       break
  frame->slots[4] /* temp__1 */ = create_closure(entry__format_number_3, 0);
  //  996: do: (-> break)
  //  997:   for_each val: (i chr)
  //  998:     if chr == '.':
  //  999:       !ac length_of(val)-i
  // 1000:       if n > i-1: append dup(" " n-(i-1)) &val
  // 1001:       break
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__format_number_19;
}
static void entry__format_number_3(void) {
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
  //  997: ... : (i chr)
  //  998:   if chr == '.':
  //  999:     !ac length_of(val)-i
  // 1000:     if n > i-1: append dup(" " n-(i-1)) &val
  // 1001:     break
  frame->slots[4] /* temp__1 */ = create_closure(entry__format_number_4, 2);
  //  997: for_each val: (i chr)
  //  998:   if chr == '.':
  //  999:     !ac length_of(val)-i
  // 1000:     if n > i-1: append dup(" " n-(i-1)) &val
  // 1001:     break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* val */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__format_number_18;
}
static void entry__format_number_6(void) {
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
  // 999: ... length_of(val)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* val */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__format_number_7;
}
static void cont__format_number_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 999: !ac length_of(val)-i
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* i */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__format_number_8;
}
static void cont__format_number_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* ac */ = arguments->slots[0];
  // 1000: ... i-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* i */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__format_number_9;
}
static void cont__format_number_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 1000: ... n > i-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* n */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__format_number_10;
}
static void cont__format_number_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 1000: ... : append dup(" " n-(i-1)) &val
  frame->slots[7] /* temp__3 */ = create_closure(entry__format_number_11, 0);
  // 1000: if n > i-1: append dup(" " n-(i-1)) &val
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__format_number_17;
}
static void entry__format_number_11(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // n: 0
  // i: 1
  // val: 2
  frame->slots[0] = myself->closure.frame->slots[3]; /* n */
  frame->slots[1] = myself->closure.frame->slots[2]; /* i */
  frame->slots[2] = myself->closure.frame->slots[1]; /* val */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1000: ... i-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* i */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__format_number_12;
}
static void cont__format_number_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 1000: ... n-(i-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* n */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__format_number_13;
}
static void cont__format_number_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 1000: ... dup(" " n-(i-1))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9cc1;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__format_number_15;
}
static void cont__format_number_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1000: ... append dup(" " n-(i-1)) &val
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* val */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__format_number_16;
}
static void cont__format_number_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* val */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__format_number_17(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1001: break
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[4] /* break */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__format_number_4(void) {
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
  // 998: ... chr == '.'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* chr */;
  arguments->slots[1] = character__46;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__format_number_5;
}
static void cont__format_number_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  //  998: ... :
  //  999:   !ac length_of(val)-i
  // 1000:   if n > i-1: append dup(" " n-(i-1)) &val
  // 1001:   break
  frame->slots[7] /* temp__2 */ = create_closure(entry__format_number_6, 0);
  //  998: if chr == '.':
  //  999:   !ac length_of(val)-i
  // 1000:   if n > i-1: append dup(" " n-(i-1)) &val
  // 1001:   break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__format_number_18(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__format_number_19(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1003: m > ac
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* ac */;
  arguments->slots[1] = frame->slots[2] /* m */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__format_number_20;
}
static void cont__format_number_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 1003: ... :
  // 1004:   append &val dup("0" m-ac)
  frame->slots[5] /* temp__2 */ = create_closure(entry__format_number_21, 0);
  // 1005: :
  // 1006:   if ac > m: range &val 1 -(ac-m+1)
  frame->slots[6] /* temp__3 */ = create_closure(entry__format_number_26, 0);
  // 1002: if
  // 1003:   m > ac:
  // 1004:     append &val dup("0" m-ac)
  // 1005:   :
  // 1006:     if ac > m: range &val 1 -(ac-m+1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__format_number_33;
}
static void entry__format_number_28(void) {
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
  // 1006: ... ac-m
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* ac */;
  arguments->slots[1] = frame->slots[2] /* m */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__format_number_29;
}
static void cont__format_number_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 1006: ... ac-m+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__format_number_30;
}
static void cont__format_number_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 1006: ... ac-m+1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__format_number_31;
}
static void cont__format_number_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1006: ... range &val 1 -(ac-m+1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* val */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__format_number_32;
}
static void cont__format_number_32(void) {
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
static void entry__format_number_21(void) {
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
  // 1004: ... m-ac
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* m */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* ac */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__format_number_22;
}
static void cont__format_number_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 1004: ... dup("0" m-ac)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9cd1;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__format_number_24;
}
static void cont__format_number_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1004: append &val dup("0" m-ac)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* val */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__format_number_25;
}
static void cont__format_number_25(void) {
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
static void entry__format_number_26(void) {
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
  // 1006: ... ac > m
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* m */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* ac */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__format_number_27;
}
static void cont__format_number_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1006: ... : range &val 1 -(ac-m+1)
  frame->slots[4] /* temp__2 */ = create_closure(entry__format_number_28, 0);
  // 1006: if ac > m: range &val 1 -(ac-m+1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__format_number_33(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1007: -> val
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* val */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__write_timing_info(void) {
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
  // 1010: $new_t current_time()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__current_time();
  func = myself->type;
  frame->cont = cont__compiler__write_timing_info_2;
}
static void cont__compiler__write_timing_info_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* new_t */, arguments->slots[0]);
  // 1012: filename.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* filename */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__write_timing_info_3;
}
static void cont__compiler__write_timing_info_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1012: ... :
  // 1013:   truncate_until &filename '/' -1
  // 1014:   ewriteln
  // 1015:     description
  // 1016:     ' '
  // 1017:     filename
  // 1018:     ':'
  // 1019:     dup(" " 12-length_of(description))
  // 1020:     format_number(new_t-t 2 3)
  // 1021:     " s"
  frame->slots[4] /* temp__2 */ = create_closure(entry__compiler__write_timing_info_4, 0);
  // 1022: :
  // 1023:   ewriteln description ": " format_number(new_t-t 0 3) " s"
  frame->slots[5] /* temp__3 */ = create_closure(entry__compiler__write_timing_info_13, 0);
  // 1011: if
  // 1012:   filename.is_defined:
  // 1013:     truncate_until &filename '/' -1
  // 1014:     ewriteln
  // 1015:       description
  // 1016:       ' '
  // 1017:       filename
  // 1018:       ':'
  // 1019:       dup(" " 12-length_of(description))
  // 1020:       format_number(new_t-t 2 3)
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = frame->slots[5] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__write_timing_info_17;
}
static void entry__compiler__write_timing_info_4(void) {
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
  // 1013: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__compiler__write_timing_info_5;
}
static void cont__compiler__write_timing_info_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1013: truncate_until &filename '/' -1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* filename */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__compiler__write_timing_info_6;
}
static void cont__compiler__write_timing_info_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* filename */ = arguments->slots[0];
  // 1019: ... length_of(description)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* description */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__compiler__write_timing_info_7;
}
static void cont__compiler__write_timing_info_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 1019: ... 12-length_of(description)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__12;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__compiler__write_timing_info_8;
}
static void cont__compiler__write_timing_info_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 1019: dup(" " 12-length_of(description))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9cc1;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__compiler__write_timing_info_9;
}
static void cont__compiler__write_timing_info_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1020: ... new_t-t
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* new_t */;
  arguments->slots[1] = var._t;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__compiler__write_timing_info_10;
}
static void cont__compiler__write_timing_info_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__5 */ = arguments->slots[0];
  // 1020: format_number(new_t-t 2 3)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__5 */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = number__3;
  result_count = 1;
  myself = func__format_number;
  func = myself->type;
  frame->cont = cont__compiler__write_timing_info_11;
}
static void cont__compiler__write_timing_info_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__4 */ = arguments->slots[0];
  // 1014: ewriteln
  // 1015:   description
  // 1016:   ' '
  // 1017:   filename
  // 1018:   ':'
  // 1019:   dup(" " 12-length_of(description))
  // 1020:   format_number(new_t-t 2 3)
  // 1021:   " s"
  argument_count = 7;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* description */;
  arguments->slots[1] = character__32;
  arguments->slots[2] = ((CELL *)frame->slots[0])->contents /* filename */;
  arguments->slots[3] = character__58;
  arguments->slots[4] = frame->slots[3] /* temp__1 */;
  arguments->slots[5] = frame->slots[6] /* temp__4 */;
  arguments->slots[6] = string__2d7981f4e6082bb6;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__write_timing_info_13(void) {
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
  // 1023: ... new_t-t
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* new_t */;
  arguments->slots[1] = var._t;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__compiler__write_timing_info_14;
}
static void cont__compiler__write_timing_info_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 1023: ... format_number(new_t-t 0 3)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = number__0;
  arguments->slots[2] = number__3;
  result_count = 1;
  myself = func__format_number;
  func = myself->type;
  frame->cont = cont__compiler__write_timing_info_15;
}
static void cont__compiler__write_timing_info_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1023: ewriteln description ": " format_number(new_t-t 0 3) " s"
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* description */;
  arguments->slots[1] = string__2d7981f4e6d82be5;
  arguments->slots[2] = frame->slots[2] /* temp__1 */;
  arguments->slots[3] = string__2d7981f4e6082bb6;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__write_timing_info_17(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1024: !t current_time()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__current_time();
  func = myself->type;
  frame->cont = cont__compiler__write_timing_info_18;
}
static void cont__compiler__write_timing_info_18(void) {
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
static void entry__build_executable_116(void) {
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
  // 1126: exe_filename .has_prefix. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* exe_filename */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__build_executable_117;
}
static void cont__build_executable_117(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 1127: -> exe_filename
  frame->slots[4] /* temp__3 */ = create_closure(entry__build_executable_118, 0);
  // 1128: -> string("./" exe_filename)
  frame->slots[5] /* temp__4 */ = create_closure(entry__build_executable_119, 0);
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  arguments->slots[2] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__build_executable_121;
}
static void entry__build_executable_118(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // exe_filename: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* exe_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1127: -> exe_filename
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* exe_filename */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__build_executable_119(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // exe_filename: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* exe_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1128: ... string("./" exe_filename)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6782bea;
  arguments->slots[1] = frame->slots[0] /* exe_filename */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__build_executable_120;
}
static void cont__build_executable_120(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1128: -> string("./" exe_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__build_executable_121(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1124: exec
  // 1125:   if
  // 1126:     exe_filename .has_prefix. '/'
  // 1127:     -> exe_filename
  // 1128:     -> string("./" exe_filename)
  // 1129:   zz*
  // 1130:   
  // 1131:   #range(command_line_arguments 2 -1)*
  argument_count = 0;
  arguments = node_p;
  arguments->slots[argument_count++] = frame->slots[2] /* temp__1 */;
  unfold(frame->slots[1] /* zz */);
  result_count = frame->caller_result_count;
  myself = get__exec();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__build_executable_2(void) {
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
  // 1039: operating_system()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__operating_system();
  func = myself->type;
  frame->cont = cont__build_executable_3;
}
static void cont__build_executable_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__2 */ = arguments->slots[0];
  // 1039: operating_system() == "cygwin"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__2 */;
  arguments->slots[1] = string__561f538101f3c2b9;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__build_executable_4;
}
static void cont__build_executable_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 1040: -> string(mod_filename ".exe")
  frame->slots[11] /* temp__3 */ = create_closure(entry__build_executable_5, 0);
  // 1041: -> mod_filename
  frame->slots[12] /* temp__4 */ = create_closure(entry__build_executable_8, 0);
  // 1037: $exe_filename
  // 1038:   if
  // 1039:     operating_system() == "cygwin"
  // 1040:     -> string(mod_filename ".exe")
  // 1041:     -> mod_filename
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = frame->slots[11] /* temp__3 */;
  arguments->slots[2] = frame->slots[12] /* temp__4 */;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__build_executable_9;
}
static void entry__build_executable_5(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // mod_filename: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* mod_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1040: ... string(mod_filename ".exe")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = string__9e0ae80b5da07d5c;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__build_executable_7;
}
static void cont__build_executable_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1040: -> string(mod_filename ".exe")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__build_executable_8(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // mod_filename: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* mod_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1041: -> mod_filename
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__build_executable_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* exe_filename */, arguments->slots[0]);
  // 1043: ... : ewriteln "build executable " exe_filename
  frame->slots[9] /* temp__1 */ = create_closure(entry__build_executable_10, 0);
  // 1043: if verbose: ewriteln "build executable " exe_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__build_executable_12;
}
static void entry__build_executable_10(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // exe_filename: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* exe_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1043: ... ewriteln "build executable " exe_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2f54d80c63c08867;
  arguments->slots[1] = frame->slots[0] /* exe_filename */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__build_executable_12(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1044: $c_filename string(mod_filename ".c")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = string__2d7981f4e6782ba6;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__build_executable_13;
}
static void cont__build_executable_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* c_filename */, arguments->slots[0]);
  // 1045: $o_filename string(mod_filename ".o")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = string__2d7981f4e6782baa;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__build_executable_14;
}
static void cont__build_executable_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* o_filename */, arguments->slots[0]);
  // 1046: $sim_info stat(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__build_executable_15;
}
static void cont__build_executable_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* sim_info */, arguments->slots[0]);
  // 1047: $c_info stat(c_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* c_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__build_executable_16;
}
static void cont__build_executable_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* c_info */, arguments->slots[0]);
  // 1048: $$c_buf undefined
  ((CELL *)frame->slots[7])->contents /* c_buf */ = get__undefined();
  // 1049: !objects(o_filename)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* o_filename */;
  arguments->slots[1] = get__true();
  result_count = 1;
  myself = get__objects();
  func = myself->type;
  frame->cont = cont__build_executable_17;
}
static void cont__build_executable_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__objects(arguments->slots[0]);
  frame->slots[10] /* temp__2 */ = create_closure(entry__build_executable_18, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_rebuild;
  arguments->slots[1] = frame->slots[10] /* temp__2 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__build_executable_25;
}
static void entry__build_executable_18(void) {
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
  // 1053: c_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__build_executable_19;
}
static void cont__build_executable_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 1054: modification_time_of(sim_info) > modification_time_of(c_info)
  frame->slots[4] /* temp__3 */ = create_closure(entry__build_executable_20, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__build_executable_24;
}
static void entry__build_executable_20(void) {
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
  // 1054: ... modification_time_of(c_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__build_executable_21;
}
static void cont__build_executable_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 1054: modification_time_of(sim_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* sim_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__build_executable_22;
}
static void cont__build_executable_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 1054: modification_time_of(sim_info) > modification_time_of(c_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__build_executable_23;
}
static void cont__build_executable_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1054: modification_time_of(sim_info) > modification_time_of(c_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__build_executable_24(void) {
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
static void cont__build_executable_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 1055: :
  // 1056:   %compiler::module_name mod_name .without_suffix. some(".meta")
  // 1057:   if verbose: ewriteln "build main module " module_name
  // 1058:   collect_output $c_source: sim2c list(main_filename) true
  // 1059:   collect_output !c_buf: create_imports c_source
  // 1060:   save c_filename c_buf.to_utf8
  // 1061:   if do_time_passes: write_timing_info "saving" c_filename
  // 1062:   compile_c c_filename o_filename
  // 1063:   if do_time_passes: write_timing_info "compiling" c_filename
  frame->slots[11] /* temp__3 */ = create_closure(entry__build_executable_26, 0);
  // 1064: :
  // 1065:   load !c_buf c_filename
  // 1066:   $o_info stat(o_filename)
  // 1067:   if
  // 1068:     ||
  // 1069:       o_info.is_undefined
  // 1070:       modification_time_of(c_info) > modification_time_of(o_info)
  // 1071:     :
  // 1072:       compile_c c_filename o_filename
  // 1073:     :
  // ...
  frame->slots[12] /* temp__4 */ = create_closure(entry__build_executable_46, 0);
  // 1050: if
  // 1051:   ||
  // 1052:     do_rebuild
  // 1053:     c_info.is_undefined
  // 1054:     modification_time_of(sim_info) > modification_time_of(c_info)
  // 1055:   :
  // 1056:     %compiler::module_name mod_name .without_suffix. some(".meta")
  // 1057:     if verbose: ewriteln "build main module " module_name
  // 1058:     collect_output $c_source: sim2c list(main_filename) true
  // 1059:     collect_output !c_buf: create_imports c_source
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = frame->slots[11] /* temp__3 */;
  arguments->slots[2] = frame->slots[12] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__build_executable_58;
}
static void entry__build_executable_55(void) {
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
  // 1072: compile_c c_filename o_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_filename */;
  arguments->slots[1] = frame->slots[1] /* o_filename */;
  result_count = frame->caller_result_count;
  myself = func__compile_c;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__build_executable_56(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // o_info: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* o_info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1074: !last_modification_time modification_time_of(o_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* o_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__build_executable_57;
}
static void cont__build_executable_57(void) {
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
static void entry__build_executable_26(void) {
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
  define__compiler__module_name(create_future());
  frame->slots[5] /* c_source */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1056: ... some(".meta")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__505aea43ea6cf036;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__build_executable_27;
}
static void cont__build_executable_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 1056: %compiler::module_name mod_name .without_suffix. some(".meta")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* mod_name */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = get__without_suffix();
  func = myself->type;
  frame->cont = cont__build_executable_28;
}
static void cont__build_executable_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(get__compiler__module_name(), arguments->slots[0]);
  // 1057: if verbose: ewriteln "build main module " module_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = func__build_executable_29;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__build_executable_31;
}
static void entry__build_executable_29(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1057: ... ewriteln "build main module " module_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__b2077c434c011020;
  arguments->slots[1] = get__module_name();
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__build_executable_31(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1058: collect_output $c_source: sim2c list(main_filename) true
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__build_executable_32;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__build_executable_34;
}
static void entry__build_executable_32(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1058: ... list(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__build_executable_33;
}
static void cont__build_executable_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1058: ... sim2c list(main_filename) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = get__true();
  result_count = frame->caller_result_count;
  myself = get__sim2c();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__build_executable_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* c_source */, arguments->slots[0]);
  // 1059: ... : create_imports c_source
  frame->slots[6] /* temp__1 */ = create_closure(entry__build_executable_35, 0);
  // 1059: collect_output !c_buf: create_imports c_source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__build_executable_36;
}
static void entry__build_executable_35(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // c_source: 0
  frame->slots[0] = myself->closure.frame->slots[5]; /* c_source */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1059: ... create_imports c_source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_source */;
  result_count = frame->caller_result_count;
  myself = func__create_imports;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__build_executable_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* c_buf */ = arguments->slots[0];
  // 1060: ... c_buf.to_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* c_buf */;
  result_count = 1;
  myself = get__to_utf8();
  func = myself->type;
  frame->cont = cont__build_executable_37;
}
static void cont__build_executable_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 1060: save c_filename c_buf.to_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* c_filename */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 0;
  myself = get__save();
  func = myself->type;
  frame->cont = cont__build_executable_38;
}
static void cont__build_executable_38(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1061: ... : write_timing_info "saving" c_filename
  frame->slots[6] /* temp__1 */ = create_closure(entry__build_executable_39, 0);
  // 1061: if do_time_passes: write_timing_info "saving" c_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__build_executable_41;
}
static void entry__build_executable_39(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // c_filename: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* c_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1061: ... write_timing_info "saving" c_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__741f540901ca42b0;
  arguments->slots[1] = frame->slots[0] /* c_filename */;
  result_count = frame->caller_result_count;
  myself = get__write_timing_info();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__build_executable_41(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1062: compile_c c_filename o_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* c_filename */;
  arguments->slots[1] = frame->slots[4] /* o_filename */;
  result_count = 0;
  myself = func__compile_c;
  func = myself->type;
  frame->cont = cont__build_executable_42;
}
static void cont__build_executable_42(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1063: ... : write_timing_info "compiling" c_filename
  frame->slots[6] /* temp__1 */ = create_closure(entry__build_executable_43, 0);
  // 1063: if do_time_passes: write_timing_info "compiling" c_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__build_executable_45;
}
static void entry__build_executable_43(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // c_filename: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* c_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1063: ... write_timing_info "compiling" c_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__768424e48173e522;
  arguments->slots[1] = frame->slots[0] /* c_filename */;
  result_count = frame->caller_result_count;
  myself = get__write_timing_info();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__build_executable_45(void) {
  myself = frame->slots[0] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__build_executable_46(void) {
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
  // 1065: load !c_buf c_filename
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* c_filename */;
  result_count = 1;
  myself = get__load();
  func = myself->type;
  frame->cont = cont__build_executable_47;
}
static void cont__build_executable_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* c_buf */ = arguments->slots[0];
  // 1066: $o_info stat(o_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* o_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__build_executable_48;
}
static void cont__build_executable_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* o_info */, arguments->slots[0]);
  // 1069: o_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* o_info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__build_executable_49;
}
static void cont__build_executable_49(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 1070: modification_time_of(c_info) > modification_time_of(o_info)
  frame->slots[7] /* temp__3 */ = create_closure(entry__build_executable_50, 0);
  // 1068: ||
  // 1069:   o_info.is_undefined
  // 1070:   modification_time_of(c_info) > modification_time_of(o_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__build_executable_54;
}
static void entry__build_executable_50(void) {
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
  // 1070: ... modification_time_of(o_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* o_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__build_executable_51;
}
static void cont__build_executable_51(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 1070: modification_time_of(c_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* c_info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__build_executable_52;
}
static void cont__build_executable_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 1070: modification_time_of(c_info) > modification_time_of(o_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__build_executable_53;
}
static void cont__build_executable_53(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1070: modification_time_of(c_info) > modification_time_of(o_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__build_executable_54(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 1071: :
  // 1072:   compile_c c_filename o_filename
  frame->slots[8] /* temp__4 */ = create_closure(entry__build_executable_55, 0);
  // 1073: :
  // 1074:   !last_modification_time modification_time_of(o_info)
  frame->slots[9] /* temp__5 */ = create_closure(entry__build_executable_56, 0);
  // 1067: if
  // 1068:   ||
  // 1069:     o_info.is_undefined
  // 1070:     modification_time_of(c_info) > modification_time_of(o_info)
  // 1071:   :
  // 1072:     compile_c c_filename o_filename
  // 1073:   :
  // 1074:     !last_modification_time modification_time_of(o_info)
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
static void cont__build_executable_58(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1075: build_dependencies mod_filename mod_name c_buf
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = frame->slots[1] /* mod_name */;
  arguments->slots[2] = ((CELL *)frame->slots[7])->contents /* c_buf */;
  result_count = 0;
  myself = func__build_dependencies;
  func = myself->type;
  frame->cont = cont__build_executable_59;
}
static void cont__build_executable_59(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1076: if do_build_static_executable:
  // 1077:   for_each
  // 1078:     "runtime/linker", "runtime/memory", "runtime/debugger": (filename)
  // 1079:       maybe_compile_c_file filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_build_static_executable();
  arguments->slots[1] = func__build_executable_60;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__build_executable_66;
}
static void entry__build_executable_65(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // filename: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 1079: maybe_compile_c_file filename
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  result_count = frame->caller_result_count;
  myself = func__maybe_compile_c_file;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__build_executable_60(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1078: "runtime/linker", "runtime/memory", "runtime/debugger"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__953de9f4b96a8381;
  arguments->slots[1] = string__933de8f439d2438a;
  arguments->slots[2] = string__5e90e5234c539c5c;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__build_executable_64;
}
static void cont__build_executable_64(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1077: for_each
  // 1078:   "runtime/linker", "runtime/memory", "runtime/debugger": (filename)
  // 1079:     maybe_compile_c_file filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__build_executable_65;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__build_executable_66(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1080: ... :
  // 1081:   $info stat(exe_filename)
  // 1082:   if
  // 1083:     ||
  // 1084:       info.is_undefined
  // 1085:       &&
  // 1086:         last_modification_time.is_defined
  // 1087:         last_modification_time > modification_time_of(info)
  // 1088:     :
  // 1089:       !do_link true
  frame->slots[9] /* temp__1 */ = create_closure(entry__build_executable_67, 0);
  // 1080: unless do_link:
  // 1081:   $info stat(exe_filename)
  // 1082:   if
  // 1083:     ||
  // 1084:       info.is_undefined
  // 1085:       &&
  // 1086:         last_modification_time.is_defined
  // 1087:         last_modification_time > modification_time_of(info)
  // 1088:     :
  // 1089:       !do_link true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_link();
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__build_executable_78;
}
static void entry__build_executable_77(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1089: !do_link true
  set__do_link(get__true());
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__build_executable_67(void) {
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
  // 1081: $info stat(exe_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* exe_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__build_executable_68;
}
static void cont__build_executable_68(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* info */, arguments->slots[0]);
  // 1084: info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__build_executable_69;
}
static void cont__build_executable_69(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 1085: &&
  // 1086:   last_modification_time.is_defined
  // 1087:   last_modification_time > modification_time_of(info)
  frame->slots[4] /* temp__3 */ = create_closure(entry__build_executable_70, 0);
  // 1083: ||
  // 1084:   info.is_undefined
  // 1085:   &&
  // 1086:     last_modification_time.is_defined
  // 1087:     last_modification_time > modification_time_of(info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__build_executable_76;
}
static void entry__build_executable_70(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // info: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1086: last_modification_time.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__last_modification_time();
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__build_executable_71;
}
static void cont__build_executable_71(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 1087: last_modification_time > modification_time_of(info)
  frame->slots[3] /* temp__3 */ = create_closure(entry__build_executable_72, 0);
  // 1085: &&
  // 1086:   last_modification_time.is_defined
  // 1087:   last_modification_time > modification_time_of(info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__build_executable_75;
}
static void entry__build_executable_72(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // info: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1087: ... modification_time_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__build_executable_73;
}
static void cont__build_executable_73(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 1087: last_modification_time > modification_time_of(info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = get__last_modification_time();
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__build_executable_74;
}
static void cont__build_executable_74(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1087: last_modification_time > modification_time_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__build_executable_75(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1085: &&
  // 1086:   last_modification_time.is_defined
  // 1087:   last_modification_time > modification_time_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__build_executable_76(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1082: if
  // 1083:   ||
  // 1084:     info.is_undefined
  // 1085:     &&
  // 1086:       last_modification_time.is_defined
  // 1087:       last_modification_time > modification_time_of(info)
  // 1088:   :
  // 1089:     !do_link true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = func__build_executable_77;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__build_executable_78(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1090: ... :
  // 1091:   $$libs_and_files library_paths_and_file_list()
  // 1092:   if do_link_profiler: push &libs_and_files "/usr/lib/libprofiler.so.0"
  // 1093:   if
  // 1094:     do_build_static_executable:
  // 1095:       if verbose: ewriteln "linking static executable"
  // 1096:       CC
  // 1097:         $_out
  // 1098:         $err
  // 1099:         $success
  // ...
  frame->slots[9] /* temp__1 */ = create_closure(entry__build_executable_79, 0);
  // 1090: if do_link:
  // 1091:   $$libs_and_files library_paths_and_file_list()
  // 1092:   if do_link_profiler: push &libs_and_files "/usr/lib/libprofiler.so.0"
  // 1093:   if
  // 1094:     do_build_static_executable:
  // 1095:       if verbose: ewriteln "linking static executable"
  // 1096:       CC
  // 1097:         $_out
  // 1098:         $err
  // 1099:         $success
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_link();
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__build_executable_110;
}
static void entry__build_executable_108(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // err: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* err */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1121: ... err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* err */;
  result_count = 1;
  myself = get__from_utf8();
  func = myself->type;
  frame->cont = cont__build_executable_109;
}
static void cont__build_executable_109(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1121: ... Error err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__build_executable_93(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // err: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* err */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1106: ... err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* err */;
  result_count = 1;
  myself = get__from_utf8();
  func = myself->type;
  frame->cont = cont__build_executable_94;
}
static void cont__build_executable_94(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1106: ... Error err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__build_executable_85(void) {
  allocate_initialized_frame_gc(2, 6);
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
  // 1095: if verbose: ewriteln "linking static executable"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = func__build_executable_86;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__build_executable_88;
}
static void entry__build_executable_86(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1095: ... ewriteln "linking static executable"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__1c7944ac5cc9c4ce;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__build_executable_88(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1096: CC
  // 1097:   $_out
  // 1098:   $err
  // 1099:   $success
  // 1100:   "runtime/linker.o"
  // 1101:   "runtime/memory.o"
  // 1102:   "runtime/debugger.o"
  // 1103:   libs_and_files*
  // 1104:   "-o"
  // 1105:   exe_filename
  argument_count = 0;
  arguments = node_p;
  arguments->slots[argument_count++] = string__5aa0e0654e0a7d41;
  arguments->slots[argument_count++] = string__7490e2a4ce0a3d61;
  arguments->slots[argument_count++] = string__14e71717a54948bc;
  unfold(((CELL *)frame->slots[0])->contents /* libs_and_files */);
  arguments->slots[argument_count++] = string__2d7981f4e6602baa;
  arguments->slots[argument_count++] = frame->slots[1] /* exe_filename */;
  result_count = 3;
  myself = func__CC;
  func = myself->type;
  frame->cont = cont__build_executable_92;
}
static void cont__build_executable_92(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* out */, arguments->slots[0]);
  initialize_future(frame->slots[3] /* err */, arguments->slots[1]);
  initialize_future(frame->slots[4] /* success */, arguments->slots[2]);
  // 1106: ... : Error err.from_utf8
  frame->slots[5] /* temp__1 */ = create_closure(entry__build_executable_93, 0);
  // 1106: unless success: Error err.from_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* success */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__build_executable_95(void) {
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
  // 1108: if verbose: ewriteln "linking executable"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = func__build_executable_96;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__build_executable_98;
}
static void entry__build_executable_96(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1108: ... ewriteln "linking executable"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__dca31b2eba5c04a5;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__build_executable_98(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1115: operating_system()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__operating_system();
  func = myself->type;
  frame->cont = cont__build_executable_99;
}
static void cont__build_executable_99(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 1116: "linux", "bsd"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__585ae883ea60d02f;
  arguments->slots[1] = string__fa720c15db16ba8;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__build_executable_100;
}
static void cont__build_executable_100(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__3 */ = arguments->slots[0];
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  arguments->slots[2] = func__build_executable_101;
  arguments->slots[3] = func__build_executable_104;
  result_count = 1;
  myself = get__case();
  func = myself->type;
  frame->cont = cont__build_executable_106;
}
static void entry__build_executable_101(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1117: ... "-l:libsim.so.@(MAJOR)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__de26b034bd2c8693;
  arguments->slots[1] = var._MAJOR;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__build_executable_103;
}
static void cont__build_executable_103(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1117: -> "-l:libsim.so.@(MAJOR)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__build_executable_104(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1118: ... "-lsim-@(MAJOR)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7e1f542601d292fa;
  arguments->slots[1] = var._MAJOR;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__build_executable_105;
}
static void cont__build_executable_105(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1118: -> "-lsim-@(MAJOR)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__build_executable_106(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 1109: CC
  // 1110:   $_out
  // 1111:   $err
  // 1112:   $success
  // 1113:   libs_and_files*
  // 1114:   case
  // 1115:     operating_system()
  // 1116:     "linux", "bsd"
  // 1117:     -> "-l:libsim.so.@(MAJOR)"
  // 1118:     -> "-lsim-@(MAJOR)"
  // ...
  argument_count = 0;
  arguments = node_p;
  unfold(((CELL *)frame->slots[0])->contents /* libs_and_files */);
  arguments->slots[argument_count++] = frame->slots[5] /* temp__1 */;
  arguments->slots[argument_count++] = string__2d7981f4e6602baa;
  arguments->slots[argument_count++] = frame->slots[1] /* exe_filename */;
  result_count = 3;
  myself = func__CC;
  func = myself->type;
  frame->cont = cont__build_executable_107;
}
static void cont__build_executable_107(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* out */, arguments->slots[0]);
  initialize_future(frame->slots[3] /* err */, arguments->slots[1]);
  initialize_future(frame->slots[4] /* success */, arguments->slots[2]);
  // 1121: ... : Error err.from_utf8
  frame->slots[5] /* temp__1 */ = create_closure(entry__build_executable_108, 0);
  // 1121: unless success: Error err.from_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* success */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__build_executable_79(void) {
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
  // 1091: $$libs_and_files library_paths_and_file_list()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = func__library_paths_and_file_list;
  func = myself->type;
  frame->cont = cont__build_executable_80;
}
static void cont__build_executable_80(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* libs_and_files */ = arguments->slots[0];
  // 1092: ... : push &libs_and_files "/usr/lib/libprofiler.so.0"
  frame->slots[2] /* temp__1 */ = create_closure(entry__build_executable_81, 0);
  // 1092: if do_link_profiler: push &libs_and_files "/usr/lib/libprofiler.so.0"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_link_profiler;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__build_executable_84;
}
static void entry__build_executable_81(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // libs_and_files: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* libs_and_files */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1092: ... push &libs_and_files "/usr/lib/libprofiler.so.0"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* libs_and_files */;
  arguments->slots[1] = string__90bd5a08cc7284bc;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__build_executable_83;
}
static void cont__build_executable_83(void) {
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
static void cont__build_executable_84(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1094: ... :
  // 1095:   if verbose: ewriteln "linking static executable"
  // 1096:   CC
  // 1097:     $_out
  // 1098:     $err
  // 1099:     $success
  // 1100:     "runtime/linker.o"
  // 1101:     "runtime/memory.o"
  // 1102:     "runtime/debugger.o"
  // 1103:     libs_and_files*
  // ...
  frame->slots[2] /* temp__1 */ = create_closure(entry__build_executable_85, 0);
  // 1107: :
  // 1108:   if verbose: ewriteln "linking executable"
  // 1109:   CC
  // 1110:     $_out
  // 1111:     $err
  // 1112:     $success
  // 1113:     libs_and_files*
  // 1114:     case
  // 1115:       operating_system()
  // 1116:       "linux", "bsd"
  // ...
  frame->slots[3] /* temp__2 */ = create_closure(entry__build_executable_95, 0);
  // 1093: if
  // 1094:   do_build_static_executable:
  // 1095:     if verbose: ewriteln "linking static executable"
  // 1096:     CC
  // 1097:       $_out
  // 1098:       $err
  // 1099:       $success
  // 1100:       "runtime/linker.o"
  // 1101:       "runtime/memory.o"
  // 1102:       "runtime/debugger.o"
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
static void cont__build_executable_110(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1122: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__build_executable_111;
}
static void cont__build_executable_111(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 1122: $zz range(command_line_arguments 2 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__command_line_arguments();
  arguments->slots[1] = number__2;
  arguments->slots[2] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__build_executable_112;
}
static void cont__build_executable_112(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[8] /* zz */, arguments->slots[0]);
  // 1123: ... on_top_level && action == "simrun"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__on_top_level();
  arguments->slots[1] = func__build_executable_113;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__build_executable_115;
}
static void entry__build_executable_113(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1123: ... action == "simrun"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._action;
  arguments->slots[1] = string__421f52c90112c2b9;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__build_executable_114;
}
static void cont__build_executable_114(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1123: ... action == "simrun"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__build_executable_115(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 1123: ... :
  // 1124:   exec
  // 1125:     if
  // 1126:       exe_filename .has_prefix. '/'
  // 1127:       -> exe_filename
  // 1128:       -> string("./" exe_filename)
  // 1129:     zz*
  // 1130:     
  // 1131:     #range(command_line_arguments 2 -1)*
  frame->slots[10] /* temp__2 */ = create_closure(entry__build_executable_116, 0);
  // 1123: if on_top_level && action == "simrun":
  // 1124:   exec
  // 1125:     if
  // 1126:       exe_filename .has_prefix. '/'
  // 1127:       -> exe_filename
  // 1128:       -> string("./" exe_filename)
  // 1129:     zz*
  // 1130:     
  // 1131:     #range(command_line_arguments 2 -1)*
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__build_executable(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1036: compile_exe: (mod_filename mod_name)
  // 1037:   $exe_filename
  // 1038:     if
  // 1039:       operating_system() == "cygwin"
  // 1040:       -> string(mod_filename ".exe")
  // 1041:       -> mod_filename
  // 1042:   
  // 1043:   if verbose: ewriteln "build executable " exe_filename
  // 1044:   $c_filename string(mod_filename ".c")
  // 1045:   $o_filename string(mod_filename ".o")
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__build_executable_2;
  result_count = frame->caller_result_count;
  myself = func__compile_exe;
  func = myself->type;
  frame = frame->caller_frame;
}
EXPORT void collect__simple(void) {
  var._MAJOR = collect_node(var._MAJOR);
  var._MINOR = collect_node(var._MINOR);
  var._PATCH = collect_node(var._PATCH);
  var._VERSION = collect_node(var._VERSION);
  var._cc = collect_node(var._cc);
  var._mkdir = collect_node(var._mkdir);
  var._SIMLIBPATH = collect_node(var._SIMLIBPATH);
  var._SIMDATAPATH = collect_node(var._SIMDATAPATH);
  var._default_paths = collect_node(var._default_paths);
  var._simlibpaths = collect_node(var._simlibpaths);
  var._simdatapaths = collect_node(var._simdatapaths);
  var._supported_platforms = collect_node(var._supported_platforms);
  var._platform_priority = collect_node(var._platform_priority);
  var._platform_specific_priority = collect_node(var._platform_specific_priority);
  var._module_info = collect_node(var._module_info);
  var._meta_levels = collect_node(var._meta_levels);
  var._do_rebuild = collect_node(var._do_rebuild);
  var._do_omit_meta = collect_node(var._do_omit_meta);
  var.compiler__do_dump_trees = collect_node(var.compiler__do_dump_trees);
  var.compiler__do_pretty_print = collect_node(var.compiler__do_pretty_print);
  var.compiler__do_convert = collect_node(var.compiler__do_convert);
  var.compiler__do_print_simplified_source = collect_node(var.compiler__do_print_simplified_source);
  var.compiler__do_show_debug_infos = collect_node(var.compiler__do_show_debug_infos);
  var.compiler__do_show_compiler_debug_infos = collect_node(var.compiler__do_show_compiler_debug_infos);
  var.compiler__do_check_only = collect_node(var.compiler__do_check_only);
  var.compiler__do_show_brief_messages = collect_node(var.compiler__do_show_brief_messages);
  var.compiler__do_print_warnings = collect_node(var.compiler__do_print_warnings);
  var.compiler__do_print_missing = collect_node(var.compiler__do_print_missing);
  var.compiler__do_print_summary = collect_node(var.compiler__do_print_summary);
  var.compiler__verbose = collect_node(var.compiler__verbose);
  var._do_print_c = collect_node(var._do_print_c);
  var.compiler__do_extract_documentation = collect_node(var.compiler__do_extract_documentation);
  var._do_extract_exports = collect_node(var._do_extract_exports);
  var._do_build_codeblocks_project = collect_node(var._do_build_codeblocks_project);
  var._do_list_dependencies = collect_node(var._do_list_dependencies);
  var._do_build_static = collect_node(var._do_build_static);
  var._do_link_profiler = collect_node(var._do_link_profiler);
  var.compiler__do_time_passes = collect_node(var.compiler__do_time_passes);
  var._module_prefix = collect_node(var._module_prefix);
  var._input_filename = collect_node(var._input_filename);
  var._additional_libraries = collect_node(var._additional_libraries);
  var._action = collect_node(var._action);
  var.compiler__show_compiler_debug_info = collect_node(var.compiler__show_compiler_debug_info);
  var._WHITESPACE = collect_node(var._WHITESPACE);
  var._cc_options = collect_node(var._cc_options);
  var._cpp_options = collect_node(var._cpp_options);
  var._ld_options = collect_node(var._ld_options);
  var._c_sources = collect_node(var._c_sources);
  var._dependencies = collect_node(var._dependencies);
  var._resolved_libraries = collect_node(var._resolved_libraries);
  var._t = collect_node(var._t);
  var.compiler__write_timing_info = collect_node(var.compiler__write_timing_info);
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
  define_namespace("std");
  define_namespace("types");
  define_namespace("compiler");

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
  set_module("simple");
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
  func__compiler__show_compiler_debug_info = create_function(entry__compiler__show_compiler_debug_info, -1);
  func__resolve_filename_8 = create_function(entry__resolve_filename_8, 1);
  func__resolve_filename_4 = create_function(entry__resolve_filename_4, 1);
  func__resolve_filename_3 = create_function(entry__resolve_filename_3, 0);
  string__373a794ad67f2aca = from_latin_1_string("Cannot resolve required library \042", 33);
  string__2d7981f4e6182be4 = from_latin_1_string("\042!", 2);
  func__resolve_filename = create_function(entry__resolve_filename, 1);
  string__9e0aed8b5d287d54 = from_latin_1_string(".sim", 4);
  string__505aea43ea6cf036 = from_latin_1_string(".meta", 5);
  string__a9300e9315c23094 = from_latin_1_string("-common", 7);
  string__578a5af303e9ccc = from_latin_1_string("-", 1);
  string__bf5121a1ba54e344 = from_latin_1_string("The platform \042", 14);
  string__b566882ea60ef100 = from_latin_1_string("\042 is not supported!", 19);
  unique__NONE = register_unique_item("NONE");
  func__add_module_infos = create_function(entry__add_module_infos, 2);
  func__lookup = create_function(entry__lookup, 2);
  func__CC = create_function(entry__CC, -1);
  func__compile_c_2 = create_function(entry__compile_c_2, 0);
  string__2d7981f4e6602ba6 = from_latin_1_string("-c", 2);
  string__2d7981f4e6602baa = from_latin_1_string("-o", 2);
  string__ca9b4802029a5965 = from_latin_1_string("Failed to compile ", 18);
  string__578a5af303e9ceb = from_latin_1_string("\012", 1);
  func__compile_c = create_function(entry__compile_c, 2);
  string__2d7981f4e6782ba6 = from_latin_1_string(".c", 2);
  string__9c0afa8b5f187d19 = from_latin_1_string("/// ", 4);
  string__a0ae90b5dc07d58 = from_latin_1_string("data", 4);
  string__2d7981f4e6782bea = from_latin_1_string("./", 2);
  func__compile_meta_module = create_function(entry__compile_meta_module, 3);
  unique__EXE = register_unique_item("EXE");
  func__build_dependencies_24 = create_function(entry__build_dependencies_24, 0);
  func__build_dependencies_23 = create_function(entry__build_dependencies_23, 0);
  string__240aeb0b5d087d14 = from_latin_1_string("sim-", 4);
  string__984c0f90152bd09f = from_latin_1_string("require", 7);
  string__1a0aeb0b5d107d52 = from_latin_1_string("link", 4);
  func__build_dependencies = create_function(entry__build_dependencies, -1);
  func__compile_module_9 = create_function(entry__compile_module_9, 0);
  string__52b1d7d50d05f753 = from_latin_1_string("Failed to open file \042", 21);
  string__2d7981f4e5f02b9a = from_latin_1_string("__", 2);
  string__a85eb307b04e1ec9 = from_latin_1_string("build module ", 13);
  string__1c48d17af91ab023 = from_latin_1_string("No source file(s) for module \042", 30);
  string__4594ae5504f56841 = from_latin_1_string("\042 found!", 8);
  string__2d7981f4e6782baa = from_latin_1_string(".o", 2);
  string__2d7981f4e6082be6 = from_latin_1_string(" #", 2);
  func__compile_module = create_function(entry__compile_module, 2);
  func__compile_modules = create_function(entry__compile_modules, 2);
  string__21dcb95c2a4f4c6f = from_latin_1_string("LD_LIBRARY_PATH", 15);
  string__cae1527a63790ed8 = from_latin_1_string("LD_LIBRARY_PATH=", 16);
  string__4c84a8f87d97d1a3 = from_latin_1_string("included object files: ", 23);
  string__d2a77fcc4263ea03 = from_latin_1_string("needed libraries: ", 18);
  func__show_file_list_2 = create_function(entry__show_file_list_2, 0);
  func__show_file_list = create_function(entry__show_file_list, 0);
  string__2d7981f4e6602b89 = from_latin_1_string("-L", 2);
  string__47d536100241702d = from_latin_1_string("library paths: ", 15);
  string__585ae883ea60d02f = from_latin_1_string("linux", 5);
  string__fa720c15db16ba8 = from_latin_1_string("bsd", 3);
  string__ec1f556601f292b5 = from_latin_1_string("-l:lib", 6);
  string__9e0aed8b5d187d17 = from_latin_1_string(".so.", 4);
  string__2d7981f4e6602ba9 = from_latin_1_string("-l", 2);
  func__library_paths_and_file_list = create_function(entry__library_paths_and_file_list, 0);
  string__b8540cde1593c09c = from_latin_1_string("typedef", 7);
  string__800a0c585ff0632 = from_latin_1_string("REGISTER", 8);
  string__ee0186bb316753e3 = from_latin_1_string("typedef struct", 14);
  string__eca001441419c0da = from_latin_1_string("IMPORT ", 7);
  func__create_imports_54 = create_function(entry__create_imports_54, 0);
  string__736c99bf90749400 = from_latin_1_string("// INSERT HERE //", 17);
  string__868d47f2e5ba5079 = from_latin_1_string("collecting imports", 18);
  func__create_imports_74 = create_function(entry__create_imports_74, 0);
  func__create_imports = create_function(entry__create_imports, 1);
  string__ac6b0fa074ea65e7 = from_latin_1_string("Expected a source code file!", 28);
  func__compile_exe_3 = create_function(entry__compile_exe_3, 0);
  string__e365e96bee331e9c = from_latin_1_string("Expected \042.sim\042 file extension in source filename!", 50);
  func__compile_exe_7 = create_function(entry__compile_exe_7, 0);
  func__compile_exe = create_function(entry__compile_exe, 1);
  func__dump_source_or_check_2 = create_function(entry__dump_source_or_check_2, 2);
  func__dump_source_or_check = create_function(entry__dump_source_or_check, 0);
  string__b830f06b636224ab = from_latin_1_string("writing C-source", 16);
  func__print_c_18 = create_function(entry__print_c_18, 0);
  func__print_c_2 = create_function(entry__print_c_2, 2);
  func__print_c = create_function(entry__print_c, 0);
  func__list_dependencies_3 = create_function(entry__list_dependencies_3, 2);
  unique__LIB = register_unique_item("LIB");
  string__7da4130a131d4ea3 = from_latin_1_string("list dependencies for ", 22);
  func__list_dependencies_17 = create_function(entry__list_dependencies_17, 0);
  func__list_dependencies_16 = create_function(entry__list_dependencies_16, 0);
  func__list_dependencies_24 = create_function(entry__list_dependencies_24, 2);
  string__5aa0e0654e0a7d4d = from_latin_1_string("runtime/linker.c", 16);
  string__7490e2a4ce0a3d6d = from_latin_1_string("runtime/memory.c", 16);
  string__14e71717a54948b0 = from_latin_1_string("runtime/debugger.c", 18);
  func__list_dependencies_23 = create_function(entry__list_dependencies_23, 0);
  func__list_dependencies = create_function(entry__list_dependencies, 0);
  string__1ec9299aa0516bc0 = from_latin_1_string(".codeblocks", 11);
  string__3319ecea8934288e = from_latin_1_string("The directory \042", 15);
  string__fb06ffd100386aab = from_latin_1_string("\042 already exists!\012", 18);
  string__334eb97199863420 = from_latin_1_string("build Code::Blocks project in ", 30);
  string__fa733c15f596be3 = from_latin_1_string("../", 3);
  string__578a5af303e9cce = from_latin_1_string("/", 1);
  string__9e0ae98b5d707d49 = from_latin_1_string(".cbp", 4);
  string__ae2cb2959270f10e = from_latin_1_string(
    "<?xml version=\0421.0\042 encoding=\042UTF-8\042 standalone=\042yes\042 ?>\n"
    "<CodeBlocks_project_file>\n"
    "  <FileVersion major=\0421\042 minor=\0426\042 />\n"
    "  <Project>\n"
    "    <Option title=\042",
    152);
  string__1738f6ef1a56e70d = from_latin_1_string(
    "\042 />\n"
    "    <Option pch_mode=\0422\042 />\n"
    "    <Option compiler=\042",
    55);
  string__f8758d9a72c26e31 = from_latin_1_string(
    "\042 />\n"
    "    <Build>\n"
    "      <Target title=\042debug\042>\n"
    "        <Option output=\042bin/debug/",
    80);
  string__b218c1a9e3db28b9 = from_latin_1_string(
    "\042 prefix_auto=\0421\042 extension_auto=\0421\042 />\n"
    "        <Option object_output=\042obj/debug/\042 />\n"
    "        <Option type=\0421\042 />\n"
    "        <Option compiler=\042",
    140);
  string__b5364d63e076ecb2 = from_latin_1_string(
    "\042 />\n"
    "        <Compiler>\n"
    "          <Add option=\042-g\042 />\n"
    "        </Compiler>\n"
    "      </Target>\n"
    "    </Build>\n"
    "    <Linker>\n",
    116);
  string__86909867946dc27b = from_latin_1_string("      <Add library=\042", 20);
  string__ca5af8c3e83c305d = from_latin_1_string("\042 />\012", 5);
  string__eff3cb070eeaf9ca = from_latin_1_string(
    "\n"
    "    </Linker>\n"
    "    <Compiler>\n"
    "      <Add option=\042-Wall\042 />\n"
    "      <Add directory=\042..\042 />\n"
    "    </Compiler>\n"
    "    <Unit filename=\042",
    124);
  string__6ec73fb9d26dad91 = from_latin_1_string(
    "runtime/common.h\042 />\n"
    "    <Unit filename=\042",
    41);
  string__62c73cb6d2cd6da9 = from_latin_1_string(
    "runtime/linker.h\042 />\n"
    "    <Unit filename=\042",
    41);
  string__df3541444f9afcd3 = from_latin_1_string(
    "runtime/memory.c\042>\n"
    "      <Option compilerVar=\042CC\042 />\n"
    "    </Unit>\n"
    "    <Unit filename=\042",
    85);
  string__6a94fbaaffa1060a = from_latin_1_string(
    "runtime/debugger.c\042>\n"
    "      <Option compilerVar=\042CC\042 />\n"
    "    </Unit>\n"
    "    <Unit filename=\042",
    87);
  string__3820eb4b885b519f = from_latin_1_string(
    "runtime/linker.c\042>\n"
    "      <Option compilerVar=\042CC\042 />\n"
    "    </Unit>\n",
    65);
  string__5ce0e5ba1304a164 = from_latin_1_string(
    "\n"
    "    <Unit filename=\042",
    21);
  string__eddc311fc1bd57cd = from_latin_1_string(
    "\042>\n"
    "      <Option compilerVar=\042CC\042 />\n"
    "    </Unit>\n",
    49);
  string__1d1cedd7cdd611c4 = from_latin_1_string(
    "    <Extensions>\n"
    "      <code_completion />\n"
    "      <debugger />\n"
    "    </Extensions>\n"
    "  </Project>\n"
    "</CodeBlocks_project_file>\n",
    120);
  func__build_codeblocks_project_2 = create_function(entry__build_codeblocks_project_2, 2);
  func__build_codeblocks_project = create_function(entry__build_codeblocks_project, 0);
  string__421f52c90112c2b9 = from_latin_1_string("simrun", 6);
  string__c84d9037a41e8f73 = from_latin_1_string("Cannot run a directory!", 23);
  func__build_library_4 = create_function(entry__build_library_4, 0);
  func__build_library_8 = create_function(entry__build_library_8, 0);
  func__build_library_7 = create_function(entry__build_library_7, 0);
  func__build_library_15 = create_function(entry__build_library_15, 0);
  func__build_library_14 = create_function(entry__build_library_14, 0);
  string__84ca78485aeb98e = from_latin_1_string("/VERSION", 8);
  string__94340f9615d2e0d7 = from_latin_1_string("libsim-", 7);
  string__9e0ae84b5d007d55 = from_latin_1_string(".dll", 4);
  string__6a1f556781f212b5 = from_latin_1_string(".dylib", 6);
  string__561f538101f3c2b9 = from_latin_1_string("cygwin", 6);
  string__7c1f538281f242b9 = from_latin_1_string("darwin", 6);
  string__822587b3f48532f5 = from_latin_1_string("build library ", 14);
  func__build_library_66 = create_function(entry__build_library_66, 0);
  string__b9aef2a4efc3a1a8 = from_latin_1_string("linking dynamic library", 23);
  func__build_library_69 = create_function(entry__build_library_69, 0);
  string__f5937b2655b3cd24 = from_latin_1_string("-Wl,-soname,libsim-", 19);
  string__b130095b1592409e = from_latin_1_string("-shared", 7);
  string__7e1f542601d292fa = from_latin_1_string("-lsim-", 6);
  string__33820b08e3b95a2a = from_latin_1_string("-Wl,-install_name,libsim-", 25);
  string__c6d9125d36413a91 = from_latin_1_string("-dynamiclib", 11);
  func__build_library_21 = create_function(entry__build_library_21, 0);
  func__build_library = create_function(entry__build_library, 0);
  string__578a5af303e9cc3 = from_latin_1_string("\042", 1);
  string__7ef24f7974bbce09 = from_latin_1_string("\042 does not exist!\012", 18);
  string__74150357c2230d49 = from_latin_1_string("compiling runtime module ", 25);
  func__maybe_compile_c_file = create_function(entry__maybe_compile_c_file, 1);
  string__578a5af303e9cc1 = from_latin_1_string(" ", 1);
  string__578a5af303e9cd1 = from_latin_1_string("0", 1);
  func__format_number = create_function(entry__format_number, -1);
  string__2d7981f4e6082bb6 = from_latin_1_string(" s", 2);
  string__2d7981f4e6d82be5 = from_latin_1_string(": ", 2);
  func__compiler__write_timing_info = create_function(entry__compiler__write_timing_info, -1);
  string__9e0ae80b5da07d5c = from_latin_1_string(".exe", 4);
  string__2f54d80c63c08867 = from_latin_1_string("build executable ", 17);
  string__b2077c434c011020 = from_latin_1_string("build main module ", 18);
  func__build_executable_29 = create_function(entry__build_executable_29, 0);
  func__build_executable_32 = create_function(entry__build_executable_32, 0);
  string__741f540901ca42b0 = from_latin_1_string("saving", 6);
  string__768424e48173e522 = from_latin_1_string("compiling", 9);
  string__953de9f4b96a8381 = from_latin_1_string("runtime/linker", 14);
  string__933de8f439d2438a = from_latin_1_string("runtime/memory", 14);
  string__5e90e5234c539c5c = from_latin_1_string("runtime/debugger", 16);
  func__build_executable_65 = create_function(entry__build_executable_65, 1);
  func__build_executable_60 = create_function(entry__build_executable_60, 0);
  func__build_executable_77 = create_function(entry__build_executable_77, 0);
  string__90bd5a08cc7284bc = from_latin_1_string("/usr/lib/libprofiler.so.0", 25);
  string__1c7944ac5cc9c4ce = from_latin_1_string("linking static executable", 25);
  func__build_executable_86 = create_function(entry__build_executable_86, 0);
  string__5aa0e0654e0a7d41 = from_latin_1_string("runtime/linker.o", 16);
  string__7490e2a4ce0a3d61 = from_latin_1_string("runtime/memory.o", 16);
  string__14e71717a54948bc = from_latin_1_string("runtime/debugger.o", 18);
  string__dca31b2eba5c04a5 = from_latin_1_string("linking executable", 18);
  func__build_executable_96 = create_function(entry__build_executable_96, 0);
  string__de26b034bd2c8693 = from_latin_1_string("-l:libsim.so.", 13);
  func__build_executable_101 = create_function(entry__build_executable_101, 0);
  func__build_executable_104 = create_function(entry__build_executable_104, 0);
  func__build_executable_113 = create_function(entry__build_executable_113, 0);
  func__build_executable_2 = create_function(entry__build_executable_2, 2);
  func__build_executable = create_function(entry__build_executable, 0);
  string__a5542a556fe6f2ee = from_latin_1_string(
    "Copyright (C) 2020 by\n"
    "Dipl.-Ing. Michael Niederle\n"
    "\n"
    "This program is free software; you can redistribute it and/or modify\n"
    "it under the terms of the GNU General Public License, version 2, or\n"
    "(at your option) version 3.\n"
    "\n"
    "This program is distributed in the hope that it will be useful,\n"
    "but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
    "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the\n"
    "GNU General Public License for more details.\n"
    "\n"
    "For details of the GNU General Public License see the accompanying\n"
    "files GPLv2.txt and GLPv3.txt or\n"
    "http://www.gnu.org/licenses/gpl-2.0.html\n"
    "http://www.gnu.org/licenses/gpl-3.0.html\n"
    "or write to the\n"
    "Free Software Foundation, Inc.,\n"
    "51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.\n",
    742);
  string__578a5af303e9ccf = from_latin_1_string(".", 1);
  string__5c5aea03ea80c025 = from_latin_1_string("mkdir", 5);
  string__55d5804f0e895069 = from_latin_1_string("SIMLIBPATH", 10);
  string__2058710183abbfe4 = from_latin_1_string("SIMDATAPATH", 11);
  string__1057e106f655c41 = from_latin_1_string("/share/simplicity-", 18);
  func__112_2 = create_function(entry__112_2, 0);
  func__112_6 = create_function(entry__112_6, 0);
  func__112_8 = create_function(entry__112_8, 0);
  func__113_2 = create_function(entry__113_2, 0);
  func__113_6 = create_function(entry__113_6, 0);
  func__113_8 = create_function(entry__113_8, 0);
  string__545aefc3ea81102f = from_latin_1_string("posix", 5);
  string__fa720015d496ba0 = from_latin_1_string("all", 3);
  string__fa725815d616ba2 = from_latin_1_string("win", 3);
  func__117_1 = create_function(entry__117_1, 0);
  string__8d3c5e4b22d2f22b = from_latin_1_string("Missing command line arguments!", 31);
  func__147_4 = create_function(entry__147_4, 0);
  func__147_2 = create_function(entry__147_2, 0);
  string__2b680b9e2e4fa558 = from_latin_1_string("check-only", 10);
  string__8d1eb0934cb703aa = from_latin_1_string("do not compile; just check for syntax errors\012", 45);
  func__147_9 = create_function(entry__147_9, 0);
  string__1124317d33023452 = from_latin_1_string("dump-trees", 10);
  string__d3c3199b9e37dd88 = from_latin_1_string("dump abstract syntax trees\012", 27);
  func__147_12 = create_function(entry__147_12, 0);
  string__2eb9522bce550419 = from_latin_1_string("pretty-print", 12);
  string__31ed31d8e6f28138 = from_latin_1_string("do not compile; just pretty print the source file\012", 50);
  func__147_15 = create_function(entry__147_15, 0);
  string__23efc30ce16df2e = from_latin_1_string("print-simplified-source", 23);
  string__c565f1870e113429 = from_latin_1_string("do not generate a C-file; just print the simplified source text\012", 64);
  func__147_18 = create_function(entry__147_18, 0);
  string__9e080c95152a208e = from_latin_1_string("convert", 7);
  string__ef1e4341946f6b23 = from_latin_1_string("convert pretty-printed sources\012", 31);
  func__147_21 = create_function(entry__147_21, 0);
  string__ae4408db97d25099 = from_latin_1_string("print-c", 7);
  string__2623b8ba9cf2f994 = from_latin_1_string("print C source code for a single module\012", 40);
  func__147_24 = create_function(entry__147_24, 0);
  string__a7e97d93a221bbf6 = from_latin_1_string("time-passes", 11);
  string__fa3ca2557b3c0271 = from_latin_1_string("print running time for the individual compiler passes\012", 54);
  func__147_27 = create_function(entry__147_27, 0);
  string__c95e7978381b7632 = from_latin_1_string("module-prefix", 13);
  string__4cca41e5ff59895a = from_latin_1_string(
    "needed to compile a single file within a subdirectory;\n"
    "if the subdirectories are nested use slashes to separate\n"
    "the directory names\n",
    132);
  func__147_30 = create_function(entry__147_30, 0);
  string__6e5ae943eae03031 = from_latin_1_string("brief", 5);
  string__22ca0f65643a26b5 = from_latin_1_string("show brief error messages\012", 26);
  func__147_33 = create_function(entry__147_33, 0);
  string__7c90ae5f04ed72b3 = from_latin_1_string("warnings", 8);
  string__ea6d59fa9dcad709 = from_latin_1_string("show warning messages\012", 22);
  func__147_36 = create_function(entry__147_36, 0);
  string__94300f9615cbf09d = from_latin_1_string("missing", 7);
  string__aa7c4ea56fedf95b = from_latin_1_string("inform about missing documentation\012", 35);
  func__147_39 = create_function(entry__147_39, 0);
  string__a8480d98152a1083 = from_latin_1_string("summary", 7);
  string__10671df6f7523277 = from_latin_1_string("show a statistical summary\012", 27);
  func__147_42 = create_function(entry__147_42, 0);
  string__b65c0e101523e09f = from_latin_1_string("verbose", 7);
  string__2ba4a5a9cdae43b8 = from_latin_1_string("output verbose informations\012", 28);
  func__147_45 = create_function(entry__147_45, 0);
  string__405aeb83ea605030 = from_latin_1_string("debug", 5);
  string__977692d258cc57f = from_latin_1_string("show C-compiler and linker calls\012", 33);
  func__147_48 = create_function(entry__147_48, 0);
  string__d13d993479731341 = from_latin_1_string("debug-compiler", 14);
  string__d30c0a59c3d26b04 = from_latin_1_string("show internal debug messages of the Simplicity compiler\012", 56);
  func__147_51 = create_function(entry__147_51, 0);
  string__2b7008daa973b572 = from_latin_1_string("codeblocks", 10);
  string__99c92c9b20cfd38 = from_latin_1_string("create Code::Blocks project\012", 28);
  func__147_54 = create_function(entry__147_54, 0);
  string__7f0dce6ce0a2268e = from_latin_1_string("extract-documentation", 21);
  string__140146cb87bc0040 = from_latin_1_string("extract documentation encoded as HTML\012", 38);
  func__147_57 = create_function(entry__147_57, 0);
  string__4101bf3c8d3115de = from_latin_1_string("extract-exports", 15);
  string__7cd3f9ecb224e231 = from_latin_1_string("extract a list of exported symbols\012", 35);
  func__147_60 = create_function(entry__147_60, 0);
  string__211e9dd763481194 = from_latin_1_string("list-dependencies", 17);
  string__1214925be130f2c = from_latin_1_string("list all dependencies\012", 22);
  func__147_63 = create_function(entry__147_63, 0);
  string__984c0f9015dae09e = from_latin_1_string("rebuild", 7);
  string__6ce7f8f6c7e73eb4 = from_latin_1_string("rebuild all source files\012", 25);
  func__147_66 = create_function(entry__147_66, 0);
  string__749427e68da7a564 = from_latin_1_string("omit-meta", 9);
  string__93608261e3431133 = from_latin_1_string("do not rebuild meta files\012", 26);
  func__147_69 = create_function(entry__147_69, 0);
  string__5a1f534901f312b4 = from_latin_1_string("static", 6);
  string__b20e03a80d6db737 = from_latin_1_string("create statically linked executable\012", 36);
  func__147_72 = create_function(entry__147_72, 0);
  string__be440f9b95da309f = from_latin_1_string("profile", 7);
  string__6f1f4f6107c9cdea = from_latin_1_string("link with libprofiler\012", 22);
  func__147_75 = create_function(entry__147_75, 0);
  string__72b0ad9004bdc085 = from_latin_1_string("filename", 8);
  string__bb8770c27da8f42f = from_latin_1_string("the name of the source file or directory to compile\012", 52);
  func__147_78 = create_function(entry__147_78, 0);
  string__af5ae49d07a6e408 = from_latin_1_string("additional_libraries", 20);
  string__c8a7274dc08e5785 = from_latin_1_string("the names of additional libraries (used for --extract-documentation)\012", 69);
  func__147_81 = create_function(entry__147_81, 0);
  func__147_8 = create_function(entry__147_8, 0);
  func__148_2 = create_function(entry__148_2, 0);
  func__148_1 = create_function(entry__148_1, 0);
  string__c6fd3eab70990d61 = from_latin_1_string("To many arguments!", 18);
  func__148_6 = create_function(entry__148_6, 0);
  func__152_1 = create_function(entry__152_1, 0);
  string__245aeb43eaacc03b = from_latin_1_string("-Wall", 5);
  string__e381a5286a12b5a7 = from_latin_1_string("-Wno-unused-function", 20);
  string__c9d1a7e66a0a17ac = from_latin_1_string("-Wno-unused-variable", 20);
  string__1abcc193f1dac47a = from_latin_1_string("-Wno-parentheses", 16);
  string__d3e88c522110dabb = from_latin_1_string("-Wno-switch", 11);
  string__65a7cd1120033166 = from_latin_1_string("-Wno-trigraphs", 14);
  string__465ae703eb84c014 = from_latin_1_string("-fPIC", 5);
  string__fa733015c516bfd = from_latin_1_string("-O1", 3);
  string__40ebeb253b72cf38 = from_latin_1_string("-fno-stack-protector", 20);
  string__edf2e5a02a882fc3 = from_latin_1_string("-falign-functions=16", 20);
  string__fa721815d316baf = from_latin_1_string("gcc", 3);
  string__ecde9da404625e23 = from_latin_1_string("-Wno-maybe-uninitialized", 24);
  func__159_4 = create_function(entry__159_4, 0);
  string__f41f598c8327d2e5 = from_latin_1_string("x86_32", 6);
  string__f41f598c830fd2e3 = from_latin_1_string("x86_64", 6);
  string__7e1f52a6019282e5 = from_latin_1_string("-msse2", 6);
  string__70d94c874a06872f = from_latin_1_string("-mfpmath=sse", 12);
  func__160_5 = create_function(entry__160_5, 0);
  string__2d7981f4e6602b8c = from_latin_1_string("-I", 2);
  func__161_1 = create_function(entry__161_1, 1);
  func__163_3 = create_function(entry__163_3, 1);
  func__165_3 = create_function(entry__165_3, 1);
  string__9b6a42533552c66c = from_latin_1_string("Source file \042", 13);
  string__79c06fde49ef2e97 = from_latin_1_string("\042 does not exist!", 17);
  func__183_2 = create_function(entry__183_2, 0);
  func__198_1 = create_function(entry__198_1, 0);
  func__199_4 = create_function(entry__199_4, 0);
  func__199_3 = create_function(entry__199_3, 0);
  func__199_2 = create_function(entry__199_2, 0);
  func__199_1 = create_function(entry__199_1, 0);
  func__199_8 = create_function(entry__199_8, 0);
  func__199_9 = create_function(entry__199_9, 0);
  func__199_10 = create_function(entry__199_10, 0);
  func__199_11 = create_function(entry__199_11, 0);

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
  var._PATCH = create_future();
  var._VERSION = create_future();
  var._cc = create_future();
  var._mkdir = create_future();
  var._SIMLIBPATH = create_future();
  var._SIMDATAPATH = create_future();
  var._default_paths = create_future();
  var._simlibpaths = create_future();
  var._simdatapaths = create_future();
  var._supported_platforms = create_future();
  define_multi_assign_static("compiler", "do_dump_trees", get__compiler__do_dump_trees, set__compiler__do_dump_trees);
  define_multi_assign_static("compiler", "do_pretty_print", get__compiler__do_pretty_print, set__compiler__do_pretty_print);
  define_multi_assign_static("compiler", "do_convert", get__compiler__do_convert, set__compiler__do_convert);
  define_multi_assign_static("compiler", "do_print_simplified_source", get__compiler__do_print_simplified_source, set__compiler__do_print_simplified_source);
  define_multi_assign_static("compiler", "do_show_debug_infos", get__compiler__do_show_debug_infos, set__compiler__do_show_debug_infos);
  define_multi_assign_static("compiler", "do_show_compiler_debug_infos", get__compiler__do_show_compiler_debug_infos, set__compiler__do_show_compiler_debug_infos);
  define_multi_assign_static("compiler", "do_check_only", get__compiler__do_check_only, set__compiler__do_check_only);
  define_multi_assign_static("compiler", "do_show_brief_messages", get__compiler__do_show_brief_messages, set__compiler__do_show_brief_messages);
  define_multi_assign_static("compiler", "do_print_warnings", get__compiler__do_print_warnings, set__compiler__do_print_warnings);
  define_multi_assign_static("compiler", "do_print_missing", get__compiler__do_print_missing, set__compiler__do_print_missing);
  define_multi_assign_static("compiler", "do_print_summary", get__compiler__do_print_summary, set__compiler__do_print_summary);
  define_multi_assign_static("compiler", "verbose", get__compiler__verbose, set__compiler__verbose);
  define_multi_assign_static("compiler", "do_extract_documentation", get__compiler__do_extract_documentation, set__compiler__do_extract_documentation);
  define_multi_assign_static("compiler", "do_time_passes", get__compiler__do_time_passes, set__compiler__do_time_passes);
  var._action = create_future();
  register_dynamic(&dyna_idx__main_filename);
  define__main_filename(create_future());
  register_dynamic(&dyna_idx__main_info);
  define__main_info(create_future());
  register_dynamic(&dyna_idx__do_build_static_executable);
  define__do_build_static_executable(create_future());
  var.compiler__show_compiler_debug_info = create_future();
  define_single_assign_static("compiler", "show_compiler_debug_info", get__compiler__show_compiler_debug_info, &var.compiler__show_compiler_debug_info);
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
  var.compiler__write_timing_info = create_future();
  define_single_assign_static("compiler", "write_timing_info", get__compiler__write_timing_info, &var.compiler__write_timing_info);

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
  use_read_only(NULL, "PACKAGE_VERSION", &get__PACKAGE_VERSION, &get_value_or_future__PACKAGE_VERSION);
  use_read_only(NULL, "PREFIX", &get__PREFIX, &get_value_or_future__PREFIX);
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
  use_single_assign_dynamic("compiler", "module_name", &get__compiler__module_name, &define__compiler__module_name);
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
  use_read_only(NULL, "extract_exports", &get__extract_exports, &get_value_or_future__extract_exports);
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
  use_read_only(NULL, "runtime_patch_version", &get__runtime_patch_version, &get_value_or_future__runtime_patch_version);
  use_read_only(NULL, "runtime_symbols", &get__runtime_symbols, &get_value_or_future__runtime_symbols);
  use_read_only(NULL, "save", &get__save, &get_value_or_future__save);
  use_read_only(NULL, "serialize", &get__serialize, &get_value_or_future__serialize);
  use_read_only(NULL, "sim2c", &get__sim2c, &get_value_or_future__sim2c);
  use_read_only(NULL, "some", &get__some, &get_value_or_future__some);
  use_read_only(NULL, "split", &get__split, &get_value_or_future__split);
  use_read_only(NULL, "stat", &get__stat, &get_value_or_future__stat);
  use_read_only("std", "MANDATORY_PARAMETER", &get__std__MANDATORY_PARAMETER, &get_value_or_future__std__MANDATORY_PARAMETER);
  use_read_only("std", "SOME_PARAMETERS", &get__std__SOME_PARAMETERS, &get_value_or_future__std__SOME_PARAMETERS);
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
  initialize_future(var.compiler__show_compiler_debug_info, func__compiler__show_compiler_debug_info);
  maybe_initialize_future(get__mode(), get__undefined());
  maybe_initialize_future(get__on_top_level(), get__true());
  initialize_future(var.compiler__write_timing_info, func__compiler__write_timing_info);
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
